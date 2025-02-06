//
// DeviceResources.h - A wrapper for the Direct3D 12 device and swapchain
//

#pragma once

#include <HAIDirectML.h>

namespace DX
{
    using namespace Harlinn::AI;
    using namespace Harlinn::Windows::Graphics;

    // Provides an interface for an application that owns DeviceResources to be notified of the device being lost or created.
    interface IDeviceNotify
    {
        virtual void OnDeviceLost() = 0;
        virtual void OnDeviceRestored() = 0;

    protected:
        ~IDeviceNotify() = default;
    };

    // Controls all the DirectX device resources.
    class DeviceResources
    {
        DXCore::Adapter1 adapter_;
        static const size_t MAX_BACK_BUFFER_COUNT = 3;

        UInt32 m_backBufferIndex;

        // Direct3D objects.
        D3D12::Device14 m_d3dDevice;
        D3D12::CommandQueue m_commandQueue;
        D3D12::GraphicsCommandList m_commandList;
        D3D12::CommandAllocator m_commandAllocators[ MAX_BACK_BUFFER_COUNT ];

        // Swap chain objects.
        DXGI::Factory7 m_dxgiFactory;
        DXGI::SwapChain3 m_swapChain;
        D3D12::Resource m_renderTargets[ MAX_BACK_BUFFER_COUNT ];
        D3D12::Resource m_depthStencil;

        // Presentation fence objects.
        D3D12::Fence m_fence;
        UInt64 m_fenceValues[ MAX_BACK_BUFFER_COUNT ];

        EventWaitHandle m_fenceEvent;

        // Direct3D rendering objects.
        D3D12::DescriptorHeap m_rtvDescriptorHeap;
        D3D12::DescriptorHeap m_dsvDescriptorHeap;
        UINT m_rtvDescriptorSize;
        D3D12::Viewport m_screenViewport;
        D3D12::Rectangle m_scissorRect;

        // Direct3D properties.
        DXGI::Format m_backBufferFormat;
        DXGI::Format m_depthBufferFormat;
        UINT m_backBufferCount;
        D3D_FEATURE_LEVEL m_d3dMinFeatureLevel;

        // Cached device properties.
        HWND m_window;
        D3D_FEATURE_LEVEL m_d3dFeatureLevel;
        DWORD m_dxgiFactoryFlags;
        RECT m_outputSize;

        // HDR Support
        DXGI_COLOR_SPACE_TYPE                               m_colorSpace;

        // DeviceResources options (see flags above)
        unsigned int                                        m_options;

        // The IDeviceNotify can be held directly as it owns the DeviceResources.
        IDeviceNotify* m_deviceNotify;

    public:
        static const unsigned int c_AllowTearing    = 0x1;
        static const unsigned int c_EnableHDR       = 0x2;

        DeviceResources( DXGI::Format backBufferFormat = DXGI::Format::B8G8R8A8_UNORM,
                        DXGI::Format depthBufferFormat = DXGI::Format::D32_FLOAT,
                        UINT backBufferCount = 2,
                        D3D_FEATURE_LEVEL minFeatureLevel = D3D_FEATURE_LEVEL_11_0,
                        unsigned int flags = 0) noexcept(false);
        ~DeviceResources();

        void SetAdapter( DXCore::Adapter1 adapter )
        {
            adapter_ = adapter;
        }

        void SetDevice( const D3D12::Device14& device )
        {
            m_d3dDevice = device;
        }

        void CreateDeviceResources();
        void CreateWindowSizeDependentResources();
        void SetWindow(HWND window, int width, int height);
        bool WindowSizeChanged(int width, int height);
        void HandleDeviceLost();
        void RegisterDeviceNotify(IDeviceNotify* deviceNotify) { m_deviceNotify = deviceNotify; }
        void Prepare( D3D12::ResourceStates beforeState = D3D12::ResourceStates::Present);
        void Present( D3D12::ResourceStates beforeState = D3D12::ResourceStates::RenderTarget);
        void WaitForGpu() noexcept;

        // Device Accessors.
        RECT GetOutputSize() const { return m_outputSize; }

        // Direct3D Accessors.
        const D3D12::Device& GetD3DDevice() const
        { 
            return m_d3dDevice; 
        }
        const DXGI::SwapChain3& GetSwapChain() const
        { 
            return m_swapChain; 
        }
        const DXGI::Factory4& GetDXGIFactory() const
        { 
            return m_dxgiFactory; 
        }
        D3D_FEATURE_LEVEL GetDeviceFeatureLevel() const
        { 
            return m_d3dFeatureLevel;
        }
        const D3D12::Resource& GetRenderTarget() const 
        { 
            return m_renderTargets[m_backBufferIndex]; 
        }
        const D3D12::Resource& GetDepthStencil() const 
        { 
            return m_depthStencil; 
        }
        const D3D12::CommandQueue& GetCommandQueue() const
        { 
            return m_commandQueue; 
        }
        const D3D12::CommandAllocator& GetCommandAllocator() const
        { 
            return m_commandAllocators[m_backBufferIndex]; 
        }
        const D3D12::GraphicsCommandList& GetCommandList() const 
        { 
            return m_commandList; 
        }
        DXGI::Format GetBackBufferFormat() const
        { 
            return m_backBufferFormat; 
        }
        DXGI::Format GetDepthBufferFormat() const
        { 
            return m_depthBufferFormat; 
        }
        const D3D12::Viewport& GetScreenViewport() const 
        { 
            return m_screenViewport; 
        }
        const D3D12::Rectangle& GetScissorRect() const
        { 
            return m_scissorRect; 
        }
        UInt32 GetCurrentFrameIndex() const
        { 
            return m_backBufferIndex; 
        }
        UInt32 GetBackBufferCount() const
        { 
            return m_backBufferCount; 
        }
        DXGI_COLOR_SPACE_TYPE GetColorSpace() const 
        { 
            return m_colorSpace; 
        }
        unsigned int GetDeviceOptions() const 
        { 
            return m_options; 
        }

        D3D12::CPUDescriptorHandle GetRenderTargetView() const
        {
            return D3D12::CPUDescriptorHandle( m_rtvDescriptorHeap.GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(m_backBufferIndex), m_rtvDescriptorSize);
        }
        D3D12::CPUDescriptorHandle GetDepthStencilView() const
        {
            return D3D12::CPUDescriptorHandle(m_dsvDescriptorHeap.GetCPUDescriptorHandleForHeapStart());
        }

    private:
        void MoveToNextFrame();
        DXGI::Adapter4 GetAdapter( );
        void UpdateColorSpace();

        
    };
}
