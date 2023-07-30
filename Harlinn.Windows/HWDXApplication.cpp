#include "pch.h"
#include "HWDXApplication.h"
#include <dxgidebug.h>

namespace Harlinn::Windows
{
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
        return (int)message.wParam;
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

    // ------------------------------------------------------------------------
    // DXContext
    // ------------------------------------------------------------------------
    bool DXContext::CreateDeviceD3D( HWND hWnd )
    {
        RECT clientRect{};
        GetClientRect( hWnd, &clientRect );

        UInt32 width = static_cast<UInt32>( clientRect.right - clientRect.left );
        UInt32 height = static_cast<UInt32>( clientRect.bottom - clientRect.top );


        if ( width == CW_USEDEFAULT )
        {
            width = 0;
        }
        if ( height == CW_USEDEFAULT )
        {
            height = 0;
        }

        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC1 sd{};
        sd.BufferCount = BACK_BUFFERS_COUNT;
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        sd.Scaling = DXGI_SCALING_NONE;
        sd.Stereo = FALSE;

        // [DEBUG] Enable debug interface
#ifdef DX12_ENABLE_DEBUG_LAYER
        ID3D12Debug* pdx12Debug = NULL;
        if ( SUCCEEDED( D3D12GetDebugInterface( IID_PPV_ARGS( &pdx12Debug ) ) ) )
        {
            pdx12Debug->EnableDebugLayer( );
        }
        auto dxgiFactory = DXGI::CreateFactory<DXGI::Factory4>( true );
#else
        auto dxgiFactory = DXGI::CreateFactory<DXGI::Factory4>( false );
#endif
        auto hardwareAdapter = dxgiFactory.FindAdapter( D3D_FEATURE_LEVEL_12_1 );
        d3dDevice_ = Graphics::CreateDevice( hardwareAdapter, D3D_FEATURE_LEVEL_12_1 );

        
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

        
        {
            D3D12_DESCRIPTOR_HEAP_DESC desc = {};
            desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
            desc.NumDescriptors = BACK_BUFFERS_COUNT;
            desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
            desc.NodeMask = 1;
            d3dRtvDescHeap_ = d3dDevice_.CreateDescriptorHeap( desc );

            SIZE_T rtvDescriptorSize = d3dDevice_.GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );
            D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = d3dRtvDescHeap_.GetCPUDescriptorHandleForHeapStart( );
            for ( UINT i = 0; i < BACK_BUFFERS_COUNT; i++ )
            {
                renderTargetDescriptors_[i] = rtvHandle;
                rtvHandle.ptr += rtvDescriptorSize;
            }
        }
        {
            D3D12_DESCRIPTOR_HEAP_DESC desc = {};
            desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
            desc.NumDescriptors = 1;
            desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
            d3dSrvDescHeap_ = d3dDevice_.CreateDescriptorHeap( desc );
        }

        {
            D3D12_COMMAND_QUEUE_DESC desc = {};
            desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
            desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
            desc.NodeMask = 1;
            d3dCommandQueue_ = d3dDevice_.CreateCommandQueue( desc );
        }
        for ( UINT i = 0; i < FRAMES_IN_FLIGHT_COUNT; i++ )
        {
            frameContexts_[i].commandAllocator_ = d3dDevice_.CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT );
        }
        d3dCommandList_ = d3dDevice_.CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameContexts_[0].commandAllocator_ );
        d3dCommandList_.Close( );

        fence_ = d3dDevice_.CreateFence( 0, D3D12_FENCE_FLAG_NONE );

        {
            swapChain_ = dxgiFactory.CreateSwapChainForHwnd<DXGI::SwapChain3>( d3dCommandQueue_, hWnd, &sd );
            swapChain_.SetMaximumFrameLatency( BACK_BUFFERS_COUNT );
            swapChainWaitableObject_ = swapChain_.GetFrameLatencyWaitableObject( );
        }

        CreateRenderTarget( );
        return true;
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
        d3dCommandQueue_.ResetPtr( );
        d3dCommandList_.ResetPtr( );
        d3dRtvDescHeap_.ResetPtr( );
        d3dSrvDescHeap_.ResetPtr( );
        fence_.ResetPtr( );
        d3dDevice_.ResetPtr( );

#ifdef DX12_ENABLE_DEBUG_LAYER
        IDXGIDebug1* pDebug = NULL;
        if ( SUCCEEDED( DXGIGetDebugInterface1( 0, IID_PPV_ARGS( &pDebug ) ) ) )
        {
            pDebug->ReportLiveObjects( DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY );
            pDebug->Release( );
        }
#endif
    }
    void DXContext::CreateRenderTarget( )
    {
        for ( UINT i = 0; i < BACK_BUFFERS_COUNT; i++ )
        {
            auto backBuffer = swapChain_.GetBuffer<D3D12Resource>( i );
            d3dDevice_.CreateRenderTargetView( backBuffer, renderTargetDescriptors_[i] );
            renderTargetResources_[i] = std::move( backBuffer );
        }
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

        auto dxgiFactory = swapChain_.GetParent<DXGI::Factory4>( );

        swapChain_.ResetPtr();
        CloseHandle( swapChainWaitableObject_ );

        swapChain_ = dxgiFactory.CreateSwapChainForHwnd( d3dCommandQueue_, hWnd, &sd );
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

        d3dCommandList_.Reset( commandAllocator );
        d3dCommandList_.ResourceBarrier( 1, &barrier_ );

        
    }

    void DXContext::PrepareCommandList( )
    {
        constexpr float clearColor[] = { 0.01f, 0.01f, 0.05f, 1.00f };
        constexpr float clearColorWithAlpha[4] = { clearColor[0] * clearColor[3], clearColor[1] * clearColor[3], clearColor[2] * clearColor[3], clearColor[3] };

        d3dCommandList_.ClearRenderTargetView( renderTargetDescriptors_[backBufferIdx_], clearColorWithAlpha );
        d3dCommandList_.OMSetRenderTargets( 1, &renderTargetDescriptors_[backBufferIdx_] );

        d3dCommandList_.SetDescriptorHeaps( d3dSrvDescHeap_ );

    }
    void DXContext::CloseCommandList( )
    {
        barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        d3dCommandList_.ResourceBarrier( 1, &barrier_ );
        d3dCommandList_.Close( );
    }

    void DXContext::ExecuteCommandList( )
    {
        d3dCommandQueue_.ExecuteCommandLists( d3dCommandList_ );
    }

    void DXContext::Present( )
    {
        swapChain_.Present( 1, 0 );
    }


    void DXContext::FrameCompleted( )
    {
        UINT64 fenceValue = fenceLastSignaledValue_ + 1;
        d3dCommandQueue_.Signal( fence_, fenceValue );
        fenceLastSignaledValue_ = fenceValue;
        currentFrameContext_->fenceValue_ = fenceValue;
    }


    // ------------------------------------------------------------------------
    // DXApplication
    // ------------------------------------------------------------------------

    DXApplication::DXApplication( const Windows::ApplicationOptions& options, std::unique_ptr<DXContext> dxContext )
        : Base( options ), dxContext_( std::move( dxContext ) )
    { 
    }
    DXApplication::~DXApplication( )
    {
    }

    int DXApplication::Run( Form& mainform )
    {
        DXMessageLoop messageLoop;
        int result = this->Run( mainform, messageLoop );
        return result;
    }

    int DXApplication::Run( Form& mainform, MessageLoop& messageLoop )
    {
        DXMessageLoop& dxMessageLoop = dynamic_cast<DXMessageLoop&>( messageLoop );
        return this->Run( mainform, dxMessageLoop );
    }

    int DXApplication::Run( Form& mainform, DXMessageLoop& messageLoop )
    {
        messageLoop_ = &messageLoop;
        mainform.OnDestroy.connect( []( Control* sender, Windows::Message& message )
        {
            ::PostQuitMessage( -1 );
        } );

        mainform.Show( );

        int result = messageLoop.Run( );

        messageLoop_ = nullptr;

        return result;
    }



}