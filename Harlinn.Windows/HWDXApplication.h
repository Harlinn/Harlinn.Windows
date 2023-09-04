#pragma once
#ifndef HARLINN_WINDOWS_HWDXAPPLICATION_H_
#define HARLINN_WINDOWS_HWDXAPPLICATION_H_

#include "HWApplication.h"
#include "HWDXGI.h"
#include "HWGraphicsD3D12.h"
#include "HCCSync.h"

namespace Harlinn::Windows
{
    namespace DX = Graphics::D3D12;


    class DXRootParameter
    {

    };

    class DXRootSignature
    {

    };


    class DXPipelineState
    {
    public:
        using RootSignature = Graphics::D3D12RootSignature;
        using PipelineState = Graphics::D3D12PipelineState;

    };

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
        DXGI::Factory4 dxgiFactory_;
        DXGI::Adapter4 hardwareAdapter_;
        DX::Device device_;
        EventWaitHandle fenceEvent_;
        DX::Fence fence_;
        DX::DescriptorHeap shaderResourceViewDescHeap_;
        DX::DescriptorHeap renderTargetViewDescHeap_;
        DX::GraphicsCommandList commandList_;
        DX::CommandQueue commandQueue_;
        std::array<FrameContext, FRAMES_IN_FLIGHT_COUNT> frameContexts_ = {};
        UInt64 fenceLastSignaledValue_ = 0;
        DXGI::SwapChain4 swapChain_;
        HANDLE swapChainWaitableObject_ = nullptr;
        std::array<DX::Resource, BACK_BUFFERS_COUNT> renderTargetResources_;
        std::array<D3D12_CPU_DESCRIPTOR_HANDLE, BACK_BUFFERS_COUNT>  renderTargetDescriptors_ = {};
        D3D12_RESOURCE_BARRIER barrier_ = {};
        FrameContext* currentFrameContext_ = nullptr;
        UINT backBufferIdx_ = 0;
    public:
        boost::signals2::signal<void( DXContext* context )> OnInvalidateDeviceObjects;
        boost::signals2::signal<void( DXContext* context )> OnCreateDeviceObjects;


        DXContext()
            : fenceEvent_( false )
        { }
    
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
        const DXGI::SwapChain4& SwapChain( ) const
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
        HW_EXPORT virtual DXGI::SwapChain4 CreateSwapChain( HWND windowHandle );

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

        HW_EXPORT DXApplication( const Windows::ApplicationOptions& options, std::unique_ptr<DXContext> dxContext = std::make_unique<DXContext>() );
        HW_EXPORT virtual ~DXApplication( );

        DXContext* Context( ) const
        {
            return dxContext_.get( );
        }

        static DXApplication& Instance( )
        {
            return static_cast<DXApplication&>( Base::Instance( ) );
        }

        HW_EXPORT virtual int Run( Form& mainForm ) override;
        HW_EXPORT virtual int Run( Form& mainForm, MessageLoop& messageLoop ) override;
        HW_EXPORT virtual int Run( Form& mainForm, DXMessageLoop& messageLoop );
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
    public:

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



    };



}


#endif