/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "pch.h"
#include "HWDXApplication.h"
#include <dxgidebug.h>

namespace Harlinn::Windows
{
    using namespace Harlinn::Windows::Graphics;
    


    // ------------------------------------------------------------------------
    // DXContext
    // ------------------------------------------------------------------------
    bool DXContext::CreateDeviceD3D( HWND hWnd )
    {
        // [DEBUG] Enable debug interface
#ifdef DX12_ENABLE_DEBUG_LAYER
        ID3D12Debug* pdx12Debug = NULL;
        if ( SUCCEEDED( D3D12GetDebugInterface( IID_PPV_ARGS( &pdx12Debug ) ) ) )
        {
            pdx12Debug->EnableDebugLayer( );
        }
        dxgiFactory_ = DXGI::CreateFactory<DXGI::Factory4>( true );
#else
        dxgiFactory_ = Graphics::DXGI::CreateFactory<Graphics::DXGI::Factory4>( false );
#endif
        hardwareAdapter_ = dxgiFactory_.FindAdapter( D3D_FEATURE_LEVEL_12_1 );
        device_ = Graphics::D3D12::CreateDevice( hardwareAdapter_, D3D_FEATURE_LEVEL_12_1 );


#ifdef DX12_ENABLE_DEBUG_LAYER
        if ( pdx12Debug != NULL )
        {
            // Setup debug interface to break on any warnings/errors
            ID3D12InfoQueue* pInfoQueue = nullptr;
            d3dDevice_.GetInterfacePointer( )->QueryInterface( IID_PPV_ARGS( &pInfoQueue ) );
            pInfoQueue->SetBreakOnSeverity( D3D12_MESSAGE_SEVERITY_ERROR, true );
            pInfoQueue->SetBreakOnSeverity( D3D12_MESSAGE_SEVERITY_CORRUPTION, true );
            pInfoQueue->SetBreakOnSeverity( D3D12_MESSAGE_SEVERITY_WARNING, true );
            pInfoQueue->Release( );
            pdx12Debug->Release( );
        }
#endif

        
        renderTargetViewDescHeap_ = this->CreateRenderTargetViewDescriptorHeap( );
        SetupRenderTargetDescriptors( );

        shaderResourceViewDescHeap_ = this->CreateShaderResourceViewDescriptorHeap( );

        commandQueue_ = this->CreateCommandQueue( );
        SetupFrameContexts( );

        rootSignature_ = this->DoOnCreateRootSignature( );
        pipelineState_ = this->DoOnCreatePipelineState( );

        commandList_ = this->CreateCommandList( frameContexts_[ 0 ].commandAllocator_ );

        fence_ = device_.CreateFence( );

        swapChain_ = this->CreateSwapChain( hWnd );

        swapChainWaitableObject_ = swapChain_.GetFrameLatencyWaitableObject( );

        CreateRenderTargetViews( );
        return true;
    }

    DX::DescriptorHeap DXContext::CreateRenderTargetViewDescriptorHeap( )
    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        desc.NumDescriptors = BACK_BUFFERS_COUNT;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        desc.NodeMask = 1;
        return device_.CreateDescriptorHeap( desc );
    }

    void DXContext::SetupRenderTargetDescriptors( )
    {
        SIZE_T renderTargetViewDescriptorSize = device_.GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );
        D3D12_CPU_DESCRIPTOR_HANDLE renderTargetViewHandle = renderTargetViewDescHeap_.GetCPUDescriptorHandleForHeapStart( );
        for ( UINT i = 0; i < BACK_BUFFERS_COUNT; i++ )
        {
            renderTargetDescriptors_[ i ] = renderTargetViewHandle;
            renderTargetViewHandle.ptr += renderTargetViewDescriptorSize;
        }
    }

    DX::DescriptorHeap DXContext::CreateShaderResourceViewDescriptorHeap( )
    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        desc.NumDescriptors = 1;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        return device_.CreateDescriptorHeap( desc );
    }

    DX::CommandQueue DXContext::CreateCommandQueue( )
    {
        D3D12_COMMAND_QUEUE_DESC desc = {};
        desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        desc.NodeMask = 1;
        return device_.CreateCommandQueue( desc );
    }

    void DXContext::SetupFrameContexts( )
    {
        for ( UINT i = 0; i < FRAMES_IN_FLIGHT_COUNT; i++ )
        {
            frameContexts_[ i ].commandAllocator_ = device_.CreateCommandAllocator( );
        }
    }

    DX::GraphicsCommandList DXContext::CreateCommandList( const DX::CommandAllocator& commandAllocator )
    {
        auto result = device_.CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameContexts_[ 0 ].commandAllocator_, pipelineState_ );
        result.Close( );
        return result;
    }

    Graphics::DXGI::SwapChain4 DXContext::CreateSwapChain( HWND windowHandle )
    {
        RECT clientRect{};
        GetClientRect( windowHandle, &clientRect );

        UInt32 width = static_cast< UInt32 >( clientRect.right - clientRect.left );
        UInt32 height = static_cast< UInt32 >( clientRect.bottom - clientRect.top );

        if ( width == CW_USEDEFAULT )
        {
            width = 0;
        }
        if ( height == CW_USEDEFAULT )
        {
            height = 0;
        }

        DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
        swapChainDesc.BufferCount = BACK_BUFFERS_COUNT;
        swapChainDesc.Width = width;
        swapChainDesc.Height = height;
        swapChainDesc.Format = static_cast< DXGI_FORMAT >(format_);
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        swapChainDesc.Scaling = DXGI_SCALING_NONE;
        swapChainDesc.Stereo = FALSE;

        auto result = dxgiFactory_.CreateSwapChainForHwnd<Graphics::DXGI::SwapChain4>( commandQueue_, windowHandle, &swapChainDesc );
        result.SetMaximumFrameLatency( BACK_BUFFERS_COUNT );
        return result;
    }


    void DXContext::CreateRenderTargetViews( )
    {
        for ( UINT i = 0; i < BACK_BUFFERS_COUNT; i++ )
        {
            auto backBuffer = swapChain_.GetBuffer<DX::Resource>( i );
            device_.CreateRenderTargetView( backBuffer, renderTargetDescriptors_[ i ] );
            renderTargetResources_[ i ] = std::move( backBuffer );
        }
    }

    void DXContext::CleanupDeviceD3D( )
    {
        CleanupRenderTarget( );
        static_cast<Unknown&>( swapChain_ ).ResetPtr( );
        if ( swapChainWaitableObject_ )
        {
            CloseHandle( swapChainWaitableObject_ );
        }
        for ( auto& frameContext : frameContexts_ )
        {
            frameContext.commandAllocator_.ResetPtr( );
        }
        commandQueue_.ResetPtr( );
        commandList_.ResetPtr( );
        renderTargetViewDescHeap_.ResetPtr( );
        shaderResourceViewDescHeap_.ResetPtr( );
        fence_.ResetPtr( );
        device_.ResetPtr( );

        hardwareAdapter_.ResetPtr( );
        dxgiFactory_.ResetPtr( );

#ifdef DX12_ENABLE_DEBUG_LAYER
        IDXGIDebug1* pDebug = NULL;
        if ( SUCCEEDED( DXGIGetDebugInterface1( 0, IID_PPV_ARGS( &pDebug ) ) ) )
        {
            pDebug->ReportLiveObjects( DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY );
            pDebug->Release( );
        }
#endif
    }
    
    void DXContext::CleanupRenderTarget( )
    {
        this->WaitForLastSubmittedFrame( );

        for ( auto& renderTargetResource : renderTargetResources_ )
        {
            if ( renderTargetResource )
            {
                renderTargetResource.ResetPtr( );
            }
        }
    }
    void DXContext::WaitForLastSubmittedFrame( )
    {
        FrameContext& frameContext = frameContexts_[frameIndex_ % FRAMES_IN_FLIGHT_COUNT];

        UINT64 fenceValue = frameContext.fenceValue_;
        if ( fenceValue != 0 )
        {
            frameContext.fenceValue_ = 0;
            if ( fence_.GetCompletedValue( ) < fenceValue )
            {
                fence_.SetEventOnCompletion( fenceValue, fenceEvent_.GetHandle() );
                fenceEvent_.Wait( );
            }
        }
    }
    DXContext::FrameContext* DXContext::WaitForNextFrameResources( )
    {
        UINT nextFrameIndex = frameIndex_ + 1;
        frameIndex_ = nextFrameIndex;

        HANDLE waitableObjects[] = { swapChainWaitableObject_, NULL };
        DWORD numWaitableObjects = 1;

        FrameContext* frameContext = &frameContexts_[frameIndex_ % FRAMES_IN_FLIGHT_COUNT];
        UINT64 fenceValue = frameContext->fenceValue_;
        if ( fenceValue != 0 ) 
        {
            frameContext->fenceValue_ = 0;
            fence_.SetEventOnCompletion( fenceValue, fenceEvent_.GetHandle( ) );
            waitableObjects[1] = fenceEvent_.GetHandle( );
            numWaitableObjects = 2;
        }

        WaitForMultipleObjects( numWaitableObjects, waitableObjects, TRUE, INFINITE );

        return frameContext;
    }
    void DXContext::ResizeSwapChain( HWND hWnd, int width, int height )
    {
        DXGI_SWAP_CHAIN_DESC1 sd;
        swapChain_.GetDesc1( &sd );
        sd.Width = width;
        sd.Height = height;

        auto dxgiFactory = swapChain_.GetParent<Graphics::DXGI::Factory4>( );

        swapChain_.ResetPtr();
        CloseHandle( swapChainWaitableObject_ );

        swapChain_ = dxgiFactory.CreateSwapChainForHwnd( commandQueue_, hWnd, &sd );
        swapChain_.SetMaximumFrameLatency( BACK_BUFFERS_COUNT );
        swapChainWaitableObject_ = swapChain_.GetFrameLatencyWaitableObject( );
    }

    void DXContext::PrepareFrame( )
    {
        currentFrameContext_ = this->WaitForNextFrameResources( );
        auto& commandAllocator = currentFrameContext_->commandAllocator_;
        backBufferIdx_ = swapChain_.GetCurrentBackBufferIndex( );
        commandAllocator.Reset( );

        barrier_ = {};
        barrier_.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier_.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        barrier_.Transition.pResource = static_cast<ID3D12Resource*>(renderTargetResources_[backBufferIdx_]);
        barrier_.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

        commandList_.Reset( commandAllocator, pipelineState_ );

        commandList_.SetGraphicsRootSignature( rootSignature_ );
        commandList_.RSSetViewports( 1, viewport_ );
        commandList_.RSSetScissorRects( 1, &scissorRect_ );

        commandList_.ResourceBarrier( 1, &barrier_ );

        
    }

    void DXContext::PrepareCommandList( )
    {
        constexpr float clearColor[] = { 0.01f, 0.01f, 0.05f, 1.00f };
        constexpr float clearColorWithAlpha[4] = { clearColor[0] * clearColor[3], clearColor[1] * clearColor[3], clearColor[2] * clearColor[3], clearColor[3] };

        commandList_.ClearRenderTargetView( renderTargetDescriptors_[backBufferIdx_], clearColorWithAlpha );
        commandList_.OMSetRenderTargets( 1, &renderTargetDescriptors_[backBufferIdx_] );

        commandList_.SetDescriptorHeaps( shaderResourceViewDescHeap_ );

    }
    void DXContext::CloseCommandList( )
    {
        barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        commandList_.ResourceBarrier( 1, &barrier_ );
        commandList_.Close( );
    }

    void DXContext::ExecuteCommandList( )
    {
        commandQueue_.ExecuteCommandLists( commandList_ );
    }

    void DXContext::Present( )
    {
        swapChain_.Present( 1, 0 );
    }


    void DXContext::FrameCompleted( )
    {
        UINT64 fenceValue = fenceLastSignaledValue_ + 1;
        commandQueue_.Signal( fence_, fenceValue );
        fenceLastSignaledValue_ = fenceValue;
        currentFrameContext_->fenceValue_ = fenceValue;
    }


    // ------------------------------------------------------------------------
    // DXApplication
    // ------------------------------------------------------------------------

    DXApplication::DXApplication( const std::shared_ptr<Windows::ApplicationOptions>& options, std::unique_ptr<DXContext> dxContext )
        : Base( options ), dxContext_( std::move( dxContext ) )
    { 
        
    }

    DXApplication::DXApplication( std::unique_ptr<DXContext> dxContext )
        : DXApplication( Windows::ApplicationOptions::LoadFromFile<Windows::ApplicationOptions>( ), std::move( dxContext ) )
    {
    }

    DXApplication::~DXApplication( )
    {
    }

    WideString DXApplication::GetAssetsDirectory( )
    {
        return Base::ExecutableDirectory( );
    }

    WideString DXApplication::GetAssetPath( const WideString& assetName, bool checkExist )
    {
        auto assetsDirectory = this->GetAssetsDirectory( );
        auto path = IO::Path::Combine( assetsDirectory, assetName );
        if ( checkExist )
        {
            if ( IO::File::Exist( path ) == false )
            {
                auto message = Format( L"The asset {} cannot be found in {}.", assetName, assetsDirectory );
                HCC_THROW( IO::FileNotFoundException, message );
            }
        }
        return path;
    }

    int DXApplication::Run( Form& mainForm )
    {
        DXMessageLoop messageLoop;
        int result = this->Run( mainForm, messageLoop );
        return result;
    }

    int DXApplication::Run( Form& mainForm, MessageLoop& messageLoop )
    {
        DXMessageLoop& dxMessageLoop = dynamic_cast<DXMessageLoop&>( messageLoop );
        return this->Run( mainForm, dxMessageLoop );
    }

    int DXApplication::Run( Form& mainForm, DXMessageLoop& messageLoop )
    {
        messageLoop_ = &messageLoop;
        mainForm.OnDestroy.connect( []( Control* sender, Windows::Message& message )
        {
            ::PostQuitMessage( -1 );
        } );

        this->DoOnInit( );
        try
        {
            mainForm.Show( );

            int result = messageLoop.Run( );

            messageLoop_ = nullptr;
            this->DoOnExit( );
            return result;
        }
        catch ( ... )
        {
            messageLoop_ = nullptr;
            this->DoOnExit( true );
            throw;
        }
    }

    void DXApplication::DoOnInit( )
    {
        this->OnInit( this );
    }
    void DXApplication::DoOnExit( bool dontThrow )
    {
        try
        {
            this->OnExit( this );
        }
        catch ( ... )
        {
            if ( dontThrow == false )
            {
                throw;
            }
        }
    }

    // ------------------------------------------------------------------------
    // DXForm
    // ------------------------------------------------------------------------
    WideString DXForm::GetAssetPath( const WideString& assetName, bool checkExist )
    {
        return DXApplication::Instance( ).GetAssetPath( assetName, checkExist );
    }

    // ------------------------------------------------------------------------
    // DXMessageLoop
    // ------------------------------------------------------------------------
    DXMessageLoop* DXMessageLoop::instance_ = nullptr;

    DXMessageLoop::DXMessageLoop( )
    {
        instance_ = this;
    }
    DXMessageLoop::~DXMessageLoop( )
    {
        instance_ = nullptr;
    }

    int DXMessageLoop::Run( )
    {
        Message message;
        done_ = false;
        while ( !done_ )
        {
            while ( this->GetMessage( message ) )
            {
                this->TranslateMessage( message );
                this->DispatchMessage( message );
                if ( message.message == WM_QUIT )
                {
                    done_ = true;
                }
            }
            if ( !done_ )
            {
                if ( !onFirstRenderCalled_ )
                {
                    onFirstRenderCalled_ = true;
                    this->DoOnFirstRender( );
                }
                this->DoOnRender( );
            }
        }
        return ( int )message.wParam;
    }

    DXMessageLoop* DXMessageLoop::Instance( )
    {
        return instance_;
    }

    int DXMessageLoop::GetMessage( Message& message )
    {
        return ::PeekMessage( &message, NULL, 0U, 0U, PM_REMOVE );
    }

    void DXMessageLoop::DoOnFirstRender( )
    {
        OnFirstRender( this );
    }

    void DXMessageLoop::DoOnRender( )
    {
        OnRender( this );
    }

    void DXMessageLoop::DoOnQuit( )
    {
        OnQuit( this );
    }

}