#pragma once
#ifndef HARLINN_WINDOWS_HWDXAPPLICATION_H_
#define HARLINN_WINDOWS_HWDXAPPLICATION_H_

#include "HWApplication.h"
#include "HWDXGI.h"
#include "HWGraphicsD3D12.h"
#include "HCCSync.h"

namespace Harlinn::Windows
{
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


    class DXContext
    {
    public:
        static constexpr size_t FRAMES_IN_FLIGHT_COUNT = 3;
        static constexpr size_t BACK_BUFFERS_COUNT = 3;
        using D3D12CommandAllocator = Graphics::D3D12CommandAllocator;
        using D3D12Device = Graphics::D3D12Device;
        using D3D12DescriptorHeap = Graphics::D3D12DescriptorHeap;
        using D3D12CommandQueue = Graphics::D3D12CommandQueue;
        using D3D12GraphicsCommandList = Graphics::D3D12GraphicsCommandList;
        using D3D12Fence = Graphics::D3D12Fence;
        using D3D12Resource = Graphics::D3D12Resource;
        using SwapChain3 = DXGI::SwapChain3;

        struct FrameContext
        {
            D3D12CommandAllocator commandAllocator_;
            UInt64 fenceValue_ = 0;
        };
    private:
        UINT frameIndex_ = 0;
        D3D12Device d3dDevice_;
        EventWaitHandle fenceEvent_;
        D3D12Fence fence_;
        D3D12DescriptorHeap d3dSrvDescHeap_;
        D3D12DescriptorHeap d3dRtvDescHeap_;
        D3D12GraphicsCommandList d3dCommandList_;
        D3D12CommandQueue d3dCommandQueue_;
        std::array<FrameContext, FRAMES_IN_FLIGHT_COUNT> frameContexts_ = {};
        UInt64 fenceLastSignaledValue_ = 0;
        SwapChain3 swapChain_;
        HANDLE swapChainWaitableObject_ = nullptr;
        std::array<D3D12Resource, BACK_BUFFERS_COUNT> renderTargetResources_;
        std::array<D3D12_CPU_DESCRIPTOR_HANDLE, BACK_BUFFERS_COUNT>  renderTargetDescriptors_ = {};
        D3D12_RESOURCE_BARRIER barrier_ = {};
        FrameContext* currentFrameContext_ = nullptr;
        UINT backBufferIdx_ = 0;
    public:
        DXContext()
            : fenceEvent_( false )
        { }
    
        UINT FrameIndex( ) const
        {
            return frameIndex_;
        }
        const D3D12Device& Device( ) const
        {
            return d3dDevice_;
        }
        const EventWaitHandle& FenceEvent( ) const
        {
            return fenceEvent_;
        }
        const D3D12Fence& Fence( ) const
        {
            return fence_;
        }
        const D3D12DescriptorHeap& SrvDescHeap( ) const
        {
            return d3dSrvDescHeap_;
        }
        const D3D12DescriptorHeap& RtvDescHeap( ) const
        {
            return d3dRtvDescHeap_;
        }
        const D3D12GraphicsCommandList& CommandList( ) const
        {
            return d3dCommandList_;
        }

        const D3D12CommandQueue& CommandQueue( ) const
        {
            return d3dCommandQueue_;
        }
        const std::array<FrameContext, FRAMES_IN_FLIGHT_COUNT>& FrameContexts() const
        {
            return frameContexts_;
        }
        UInt64 FenceLastSignaledValue( ) const
        {
            return fenceLastSignaledValue_;
        }
        const SwapChain3& SwapChain( ) const
        {
            return swapChain_;
        }
        HANDLE SwapChainWaitableObject( ) const
        {
            return swapChainWaitableObject_;
        }
        const std::array<D3D12Resource, BACK_BUFFERS_COUNT>& RenderTargetResources( ) const
        {
            return renderTargetResources_;
        }
        const std::array<D3D12_CPU_DESCRIPTOR_HANDLE, BACK_BUFFERS_COUNT>& RenderTargetDescriptors( ) const
        {
            return renderTargetDescriptors_;
        }


        HW_EXPORT virtual bool CreateDeviceD3D( HWND hWnd );
        HW_EXPORT virtual void CleanupDeviceD3D( );
        HW_EXPORT virtual void CreateRenderTarget( );
        HW_EXPORT virtual void CleanupRenderTarget( );
        HW_EXPORT virtual void WaitForLastSubmittedFrame( );
        HW_EXPORT virtual FrameContext* WaitForNextFrameResources( );
        HW_EXPORT virtual void ResizeSwapChain( HWND hWnd, int width, int height );

        HW_EXPORT virtual void PrepareFrame( );
        HW_EXPORT virtual void PrepareCommandList( );
        HW_EXPORT virtual void CloseCommandList( );

        HW_EXPORT virtual void ExecuteCommandList( );

        HW_EXPORT virtual void Present( );

        HW_EXPORT virtual void FrameCompleted( );

        


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

        HW_EXPORT virtual int Run( Form& mainform ) override;
        HW_EXPORT virtual int Run( Form& mainform, MessageLoop& messageLoop ) override;
        HW_EXPORT virtual int Run( Form& mainform, DXMessageLoop& messageLoop );
    };


}


#endif