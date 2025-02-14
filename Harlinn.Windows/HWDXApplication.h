#pragma once
#ifndef HARLINN_WINDOWS_HWDXAPPLICATION_H_
#define HARLINN_WINDOWS_HWDXAPPLICATION_H_
/*
   Copyright 2024-2025 Espen Harlinn

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

#include "HWApplication.h"
#include "HWDXGI.h"
#include "HWGraphicsD3D12.h"
#include "HCCSync.h"

namespace Harlinn::Windows
{
    namespace DX = Graphics::D3D12;

    class DXContext
    {
    public:
        static constexpr size_t FRAMES_IN_FLIGHT_COUNT = 3;
        static constexpr size_t BACK_BUFFERS_COUNT = 3;
        

        struct FrameContext
        {
            DX::CommandAllocator commandAllocator_;
            UInt64 fenceValue_ = 0;
        };
    private:
        UINT frameIndex_ = 0;
        Graphics::DXGI::Format format_ = Graphics::DXGI::Format::R8G8B8A8_UNORM;
        Graphics::DXGI::Factory4 dxgiFactory_;
        Graphics::DXGI::Adapter4 hardwareAdapter_;
        DX::Device device_;
        DX::Viewport viewport_;
        DX::Rectangle scissorRect_;
        EventWaitHandle fenceEvent_;
        DX::Fence fence_;
        DX::DescriptorHeap shaderResourceViewDescHeap_;
        DX::DescriptorHeap renderTargetViewDescHeap_;
        DX::RootSignature rootSignature_;
        DX::PipelineState pipelineState_;
        DX::GraphicsCommandList commandList_;
        DX::CommandQueue commandQueue_;
        std::array<FrameContext, FRAMES_IN_FLIGHT_COUNT> frameContexts_ = {};
        UInt64 fenceLastSignaledValue_ = 0;
        Graphics::DXGI::SwapChain4 swapChain_;
        HANDLE swapChainWaitableObject_ = nullptr;
        std::array<DX::Resource, BACK_BUFFERS_COUNT> renderTargetResources_;
        std::array<D3D12_CPU_DESCRIPTOR_HANDLE, BACK_BUFFERS_COUNT>  renderTargetDescriptors_ = {};
        D3D12_RESOURCE_BARRIER barrier_ = {};
        FrameContext* currentFrameContext_ = nullptr;
        UINT backBufferIdx_ = 0;
    public:
        boost::signals2::signal<void( DXContext* context )> OnInvalidateDeviceObjects;
        boost::signals2::signal<void( DXContext* context )> OnCreateDeviceObjects;
        boost::signals2::signal<void( DXContext* context, Graphics::D3D12::RootSignature& rootSignature )> OnCreateRootSignature;
        boost::signals2::signal<void( DXContext* context, Graphics::D3D12::PipelineState& pipelineState )> OnCreatePipelineState;


        DXContext()
            : fenceEvent_( false )
        { }
    
        Graphics::DXGI::Format Format( ) const
        {
            return format_;
        }

        UINT FrameIndex( ) const
        {
            return frameIndex_;
        }
        const DX::Device& Device( ) const
        {
            return device_;
        }
        const EventWaitHandle& FenceEvent( ) const
        {
            return fenceEvent_;
        }
        const DX::Fence& Fence( ) const
        {
            return fence_;
        }
        const DX::DescriptorHeap& ShaderResourceViewDescHeap( ) const
        {
            return shaderResourceViewDescHeap_;
        }
        const DX::DescriptorHeap& RenderTargetViewDescHeap( ) const
        {
            return renderTargetViewDescHeap_;
        }

        const DX::RootSignature& RootSignature( ) const
        {
            return rootSignature_;
        }
        const DX::PipelineState& PipelineState( ) const
        {
            return pipelineState_;
        }

        const DX::GraphicsCommandList& CommandList( ) const
        {
            return commandList_;
        }

        const DX::CommandQueue& CommandQueue( ) const
        {
            return commandQueue_;
        }
        const std::array<FrameContext, FRAMES_IN_FLIGHT_COUNT>& FrameContexts() const
        {
            return frameContexts_;
        }
        UInt64 FenceLastSignaledValue( ) const
        {
            return fenceLastSignaledValue_;
        }
        const Graphics::DXGI::SwapChain4& SwapChain( ) const
        {
            return swapChain_;
        }
        HANDLE SwapChainWaitableObject( ) const
        {
            return swapChainWaitableObject_;
        }
        const std::array<DX::Resource, BACK_BUFFERS_COUNT>& RenderTargetResources( ) const
        {
            return renderTargetResources_;
        }
        const std::array<D3D12_CPU_DESCRIPTOR_HANDLE, BACK_BUFFERS_COUNT>& RenderTargetDescriptors( ) const
        {
            return renderTargetDescriptors_;
        }


        HW_EXPORT virtual bool CreateDeviceD3D( HWND hWnd );
    protected:
        HW_EXPORT virtual DX::DescriptorHeap CreateRenderTargetViewDescriptorHeap( );
        HW_EXPORT void SetupRenderTargetDescriptors( );
        HW_EXPORT virtual DX::DescriptorHeap CreateShaderResourceViewDescriptorHeap( );
        HW_EXPORT virtual DX::CommandQueue CreateCommandQueue( );
        HW_EXPORT void SetupFrameContexts( );
        HW_EXPORT virtual DX::GraphicsCommandList CreateCommandList( const DX::CommandAllocator& commandAllocator );
        HW_EXPORT virtual Graphics::DXGI::SwapChain4 CreateSwapChain( HWND windowHandle );

    public:
        HW_EXPORT virtual void CleanupDeviceD3D( );
        HW_EXPORT virtual void CreateRenderTargetViews( );
        HW_EXPORT virtual void CleanupRenderTarget( );
        HW_EXPORT virtual void WaitForLastSubmittedFrame( );
        HW_EXPORT virtual FrameContext* WaitForNextFrameResources( );
        HW_EXPORT virtual void ResizeSwapChain( HWND hWnd, int width, int height );

        void Resize( HWND hWnd, int width, int height )
        {
            this->WaitForLastSubmittedFrame( );
            this->DoOnInvalidateDeviceObjects( );
            this->CleanupRenderTarget( );
            this->ResizeSwapChain( hWnd, width, height );
            viewport_.Width = static_cast< float >( width );
            viewport_.Height = static_cast< float >( height );
            scissorRect_.SetWidth( static_cast< UInt32 >( width ) );
            scissorRect_.SetHeight( static_cast< UInt32 >( height ) );
            this->CreateRenderTargetViews( );
            this->DoOnCreateDeviceObjects( );
        }

        HW_EXPORT virtual void PrepareFrame( );
        HW_EXPORT virtual void PrepareCommandList( );
        HW_EXPORT virtual void CloseCommandList( );

        HW_EXPORT virtual void ExecuteCommandList( );

        HW_EXPORT virtual void Present( );

        HW_EXPORT virtual void FrameCompleted( );

    protected:

        virtual void DoOnInvalidateDeviceObjects( )
        {
            OnInvalidateDeviceObjects( this );
        }

        virtual void DoOnCreateDeviceObjects( )
        {
            OnCreateDeviceObjects( this );
        }

        virtual Graphics::D3D12::RootSignature DoOnCreateRootSignature( )
        {
            DX::RootSignature rootSignature;
            OnCreateRootSignature( this, rootSignature );
            if ( !rootSignature )
            {
                rootSignature = device_.CreateRootSignature( DX::RootSignatureFlags::AllowInputAssemblerInputLayout );
            }
            return rootSignature;
        }

        virtual DX::PipelineState DoOnCreatePipelineState( )
        {
            DX::PipelineState pipelineState;
            OnCreatePipelineState( this, pipelineState );
            return pipelineState;
        }

    };


    /// <summary>
    /// A message loop implementation that uses idle 
    /// time to perform rendering
    /// </summary>
    class DXMessageLoop : public MessageLoop
    {
        bool done_ = false;
        bool onFirstRenderCalled_ = false;
        static DXMessageLoop* instance_;
    public:
        boost::signals2::signal<void( DXMessageLoop* sender )> OnFirstRender;
        boost::signals2::signal<void( DXMessageLoop* sender )> OnRender;
        boost::signals2::signal<void( DXMessageLoop* sender )> OnQuit;

        HW_EXPORT DXMessageLoop( );
        HW_EXPORT virtual ~DXMessageLoop( );
        HW_EXPORT virtual int Run( ) override;
        HW_EXPORT static DXMessageLoop* Instance( );
    protected:
        HW_EXPORT virtual int GetMessage( Message& message );
        HW_EXPORT virtual void DoOnFirstRender( );
        HW_EXPORT virtual void DoOnRender( );
        HW_EXPORT virtual void DoOnQuit( );
    };


    class DXApplication : public Windows::Application
    {
        std::unique_ptr<DXContext> dxContext_;
        DXMessageLoop* messageLoop_ = nullptr;
    public:
        using Base = Windows::Application;
        boost::signals2::signal<void( DXApplication* sender )> OnInit;
        boost::signals2::signal<void( DXApplication* sender )> OnExit;

        HW_EXPORT DXApplication( const std::shared_ptr<Windows::ApplicationOptions>& options, std::unique_ptr<DXContext> dxContext = std::make_unique<DXContext>() );
        HW_EXPORT DXApplication( std::unique_ptr<DXContext> dxContext = std::make_unique<DXContext>( ) );
        HW_EXPORT virtual ~DXApplication( );

        DXContext* Context( ) const
        {
            return dxContext_.get( );
        }

        static DXApplication& Instance( )
        {
            return static_cast<DXApplication&>( Base::Instance( ) );
        }

        HW_EXPORT virtual WideString GetAssetsDirectory( );
        HW_EXPORT virtual WideString GetAssetPath( const WideString& assetName, bool checkExist = true );


        HW_EXPORT virtual int Run( Form& mainForm ) override;
        HW_EXPORT virtual int Run( Form& mainForm, MessageLoop& messageLoop ) override;
        HW_EXPORT virtual int Run( Form& mainForm, DXMessageLoop& messageLoop );
    protected:
        HW_EXPORT virtual void DoOnInit( );
        HW_EXPORT virtual void DoOnExit( bool dontThrow = false );

    };


    class DXForm : public Form
    {
    public:
        using Base = Windows::Form;
        boost::signals2::signal<void( DXForm* sender )> OnRender;
    private:
        DXContext* context_ = nullptr;
        boost::signals2::connection onRenderConnection_;
        boost::signals2::connection onInvalidateDeviceObjectsConnection_;
        boost::signals2::connection onCreateDeviceObjectsConnection_;
        boost::signals2::connection onCreateRootSignatureConnection_;
        boost::signals2::connection onCreatePipelineStateConnection_;
    public:
        HW_EXPORT virtual WideString GetAssetPath( const WideString& assetName, bool checkExist = true );

        DXContext* Context( ) const
        {
            return context_;
        }
    protected:
        virtual void DoOnHandleCreated( )
        {
            auto& application = DXApplication::Instance( );
            auto context = application.Context( );
            if ( context )
            {
                context_ = context;
                onInvalidateDeviceObjectsConnection_ = context->OnInvalidateDeviceObjects.connect( [ this ]( DXContext* sender )
                    {
                        this->DoOnInvalidateDeviceObjects( sender );
                    } );

                onCreateDeviceObjectsConnection_ = context->OnCreateDeviceObjects.connect( [ this ]( DXContext* sender )
                    {
                        this->DoOnCreateDeviceObjects( sender );
                    } );
                onCreateRootSignatureConnection_ = context->OnCreateRootSignature.connect( [ this ]( DXContext* sender, Graphics::D3D12::RootSignature& rootSignature )
                    {
                        this->DoOnCreateRootSignature( sender, rootSignature );
                    } );
                onCreatePipelineStateConnection_ = context->OnCreatePipelineState.connect( [ this ]( DXContext* sender, Graphics::D3D12::PipelineState& pipelineState )
                    {
                        this->DoOnCreatePipelineState( sender, pipelineState );
                    } );
                context->CreateDeviceD3D( this->GetHandle( ) );
            }
            Base::DoOnHandleCreated( );
        }


        virtual void DoOnSize( Message& message ) override
        {
            Base::DoOnSize( message );
            if ( context_ )
            {
                context_->Resize( message.hwnd, ( UINT )LOWORD( message.lParam ), ( UINT )HIWORD( message.lParam ) );
            }
        }

        virtual void DoOnShown( ) override
        {
            auto messageLoop = DXMessageLoop::Instance( );
            if ( messageLoop )
            {
                onRenderConnection_ = messageLoop->OnRender.connect( [ this ]( DXMessageLoop* sender )
                    {
                        this->DoOnRenderFrame( );
                    } );
            }
            Base::DoOnShown( );
            
        }


        virtual void DoOnRenderFrame( )
        {
            this->DoOnNewFrame( );
            this->DoOnRender( );
            this->DoOnFrameDone( );
        }

        virtual void DoOnNewFrame( )
        {
            if ( context_ )
            {
                context_->PrepareFrame( );
                context_->PrepareCommandList( );
            }
        }

        virtual void DoOnRender( )
        {
            OnRender( this );
        }

        virtual void DoOnFrameDone( )
        {
            if ( context_ )
            {
                context_->CloseCommandList( );
                context_->ExecuteCommandList( );
                context_->Present( );
                context_->FrameCompleted( );
            }

        }

        virtual void DoOnInvalidateDeviceObjects( DXContext* context )
        {

        }

        virtual void DoOnCreateDeviceObjects( DXContext* context )
        {

        }

        virtual void DoOnCreateRootSignature( DXContext* context, Graphics::D3D12::RootSignature& rootSignature )
        {

        }
        virtual void DoOnCreatePipelineState( DXContext* context, Graphics::D3D12::PipelineState& pipelineState )
        {

        }

    };



}


#endif