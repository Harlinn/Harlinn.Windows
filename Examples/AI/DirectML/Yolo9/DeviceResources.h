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

#pragma once

#include <HAIDirectML.h>

#define USE_COMPUTE_ENGINE 1

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

    class FrameResources
    {
        D3D12::CommandAllocator commandAllocator_;
        D3D12::Resource renderTarget_;
        D3D11::Resource wrappedRenderTarget_;
        D2D::Bitmap1 d2dRenderTarget_;
        UInt64 fenceValue_ = 0;
    public:
        FrameResources( ) = default;
        FrameResources( const FrameResources& ) = delete;
        FrameResources( FrameResources&& ) = delete;
        FrameResources& operator = ( const FrameResources& ) = delete;
        FrameResources& operator = ( FrameResources&& ) = delete;

        const D3D12::CommandAllocator& CommandAllocator( ) const noexcept
        {
            return commandAllocator_;
        }
        void SetCommandAllocator( const D3D12::CommandAllocator& commandAllocator )
        {
            commandAllocator_ = commandAllocator;
        }
        const D3D12::Resource& RenderTarget( ) const noexcept
        {
            return renderTarget_;
        }
        void SetRenderTarget( const D3D12::Resource& renderTarget )
        {
            renderTarget_ = renderTarget;
        }

        const D3D11::Resource& WrappedRenderTarget( ) const
        {
            return wrappedRenderTarget_;
        }

        void SetWrappedRenderTarget( const D3D11::Resource& wrappedRenderTarget )
        {
            wrappedRenderTarget_ = wrappedRenderTarget;
        }

        const D2D::Bitmap1& D2DRenderTarget( ) const noexcept
        {
            return d2dRenderTarget_;
        }

        void SetD2DRenderTarget( const D2D::Bitmap1& d2dRenderTarget )
        {
            d2dRenderTarget_ = d2dRenderTarget;
        }

        UInt64 FenceValue( ) const noexcept
        {
            return fenceValue_;
        }
        void Increment( )
        {
            fenceValue_++;
        }
        void SetFenceValue( UInt64 fenceValue )
        {
            fenceValue_ = fenceValue;
        }
        void Reset( )
        {
            d2dRenderTarget_.ResetPtr( );
            wrappedRenderTarget_.ResetPtr( );
            renderTarget_.ResetPtr( );
            commandAllocator_.ResetPtr( );
        }

        void ResetSizeDependentResources( UInt64 fenceValue )
        {
            d2dRenderTarget_.ResetPtr( );
            wrappedRenderTarget_.ResetPtr( );
            renderTarget_.ResetPtr( );
            fenceValue_ = fenceValue;
        }

    };

    // Controls all the DirectX device resources.
    class DeviceResources
    {
    public:
        static const size_t MAX_BACK_BUFFER_COUNT = 3;
    private:
        UInt32 m_backBufferIndex;

        // Direct3D objects.
        D3D12::Device14 m_d3dDevice;
        D3D12::CommandQueue m_commandQueue;
        D3D12::GraphicsCommandList m_commandList;

        std::array<FrameResources, MAX_BACK_BUFFER_COUNT> frameResources_;
        //D3D12::CommandAllocator m_commandAllocators[ MAX_BACK_BUFFER_COUNT ];

        D3D11::Device5 d3d11Device_;
        D3D11::DeviceContext d3d11DeviceContext_;
        D3D11On12::Device2 d3d11On12Device_;


        // Swap chain objects.
        DXGI::Factory7 m_dxgiFactory;
        DXGI::SwapChain3 m_swapChain;
        //D3D12::Resource m_renderTargets[ MAX_BACK_BUFFER_COUNT ];
        D3D12::Resource m_depthStencil;

        // Presentation fence objects.
        D3D12::Fence m_fence;
        //UInt64 m_fenceValues[ MAX_BACK_BUFFER_COUNT ];

        EventWaitHandle m_fenceEvent;

        D2D::Factory8 d2dFactory_;
        D2D::Device7 d2dDevice_;
        D2D::DeviceContext d2dDeviceContext_;
        DirectWrite::Factory dwriteFactory_;



        // Direct3D rendering objects.
        D3D12::DescriptorHeap m_srvDescriptorHeap;
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
        const D3D12::Device14& GetD3DDevice() const
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

        const D2D::Factory8& D2DFactory( ) const
        {
            return d2dFactory_;
        }
        const D2D::Device7& D2DDevice( ) const
        {
            return d2dDevice_;
        }
        const D2D::DeviceContext& D2DDeviceContext( ) const
        {
            return d2dDeviceContext_;
        }
        const DirectWrite::Factory& DirectWriteFactory( ) const
        {
            return dwriteFactory_;
        }

        void AcquireRenderTarget( ) const
        {
            d3d11On12Device_.AcquireWrappedResources( frameResources_[ m_backBufferIndex ].WrappedRenderTarget( ) );
        }
        void ReleaseRenderTarget( ) const
        {
            d3d11On12Device_.ReleaseWrappedResources( frameResources_[ m_backBufferIndex ].WrappedRenderTarget( ) );
        }

        D3D_FEATURE_LEVEL GetDeviceFeatureLevel() const
        { 
            return m_d3dFeatureLevel;
        }
        const D3D12::Resource& GetRenderTarget() const 
        { 
            return frameResources_[m_backBufferIndex].RenderTarget( );
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
            return frameResources_[ m_backBufferIndex ].CommandAllocator( );
        }
        const D3D12::GraphicsCommandList& GetCommandList() const 
        { 
            return m_commandList; 
        }

        const D3D11::Device5& D3D11Device( ) const
        {
            return d3d11Device_;
        }
        const D3D11::DeviceContext& D3D11DeviceContext( ) const
        {
            return d3d11DeviceContext_;
        }
        const D3D11On12::Device2& D3D11On12Device( ) const
        {
            return d3d11On12Device_;
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

        const D3D12::DescriptorHeap& ShaderResourceViewDescHeap( ) const
        {
            return m_srvDescriptorHeap;
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
