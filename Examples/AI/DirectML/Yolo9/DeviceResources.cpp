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

//
// DeviceResources.cpp - A wrapper for the Direct3D 12 device and swapchain
//

#include "pch.h"
#include "DeviceResources.h"
#include <HWGraphicsD3D12SdkLayers.h>

using namespace DX;



namespace
{
    inline DXGI::Format NoSRGB( DXGI::Format fmt)
    {
        switch (fmt)
        {
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:   return DXGI::Format::R8G8B8A8_UNORM;
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:   return DXGI::Format::B8G8R8A8_UNORM;
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:   return DXGI::Format::B8G8R8X8_UNORM;
        default:                                return fmt;
        }
    }
};

// Constructor for DeviceResources.
DeviceResources::DeviceResources( DXGI::Format backBufferFormat,
                        DXGI::Format depthBufferFormat,
                        UINT backBufferCount,
                        D3D_FEATURE_LEVEL minFeatureLevel,
                        unsigned int flags) noexcept(false) 
    : m_backBufferIndex(0),
      m_fenceValues{},
      m_rtvDescriptorSize(0),
      m_screenViewport{},
      m_scissorRect{},
      m_backBufferFormat(backBufferFormat),
      m_depthBufferFormat(depthBufferFormat),
      m_backBufferCount(backBufferCount),
      m_d3dMinFeatureLevel(minFeatureLevel),
      m_window(nullptr),
      m_d3dFeatureLevel(D3D_FEATURE_LEVEL_11_0),
      m_dxgiFactoryFlags(0),
      m_outputSize{0, 0, 1, 1},
      m_colorSpace(DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709),
      m_options(flags),
      m_deviceNotify(nullptr)
{
    if (backBufferCount > MAX_BACK_BUFFER_COUNT)
    {
        throw std::out_of_range("backBufferCount too large");
    }

    if (minFeatureLevel < D3D_FEATURE_LEVEL_11_0)
    {
        throw std::out_of_range("minFeatureLevel too low");
    }
}

// Destructor for DeviceResources.
DeviceResources::~DeviceResources()
{
    // Ensure that the GPU is no longer referencing resources that are about to be destroyed.
    WaitForGpu();
}

void MyDeviceRemovedHandler(const D3D12::Device& device)
{
    auto pDred = device.As<D3D12::DeviceRemovedExtendedData>( );

    D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT DredAutoBreadcrumbsOutput;
    D3D12_DRED_PAGE_FAULT_OUTPUT DredPageFaultOutput;
    pDred.GetAutoBreadcrumbsOutput(&DredAutoBreadcrumbsOutput);
    pDred.GetPageFaultAllocationOutput(&DredPageFaultOutput);

    // Custom processing of DRED data can be done here.
    // Produce telemetry...
    // Log information to console...
    // break into a debugger...
}

// Configures the Direct3D device, and stores handles to it and the device context.
void DeviceResources::CreateDeviceResources()
{
#ifdef _DEBUG
    /*
    auto debugController = D3D12::GetDebugInterface<D3D12::D3D12Debug>( );
    if ( debugController )
    {
        debugController.EnableDebugLayer( );
    }
    */
#endif

    m_dxgiFactory = DXGI::CreateFactory( );

    // Determines whether tearing support is available for fullscreen borderless windows.
    if (m_options & c_AllowTearing)
    {
        auto allowTearing = FALSE;
        
        m_dxgiFactory.CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing));
        

        if (!allowTearing)
        {
            m_options &= ~c_AllowTearing;
#ifdef _DEBUG
            OutputDebugStringA("WARNING: Variable refresh rate displays not supported");
#endif
        }
    }

#ifdef _DEBUG
    /*
    auto dredSettings = D3D12::GetDebugInterface<D3D12::DeviceRemovedExtendedDataSettings>( );
    if ( dredSettings )
    {
        dredSettings.SetAutoBreadcrumbsEnablement( D3D12_DRED_ENABLEMENT_FORCED_ON );
        dredSettings.SetPageFaultEnablement( D3D12_DRED_ENABLEMENT_FORCED_ON );
    }
    */
#endif

    if ( !m_d3dDevice )
    {
        DXGI::Adapter1 adapter = GetAdapter( );
        m_d3dDevice = D3D12::CreateDevice( adapter, m_d3dMinFeatureLevel );
    }


    m_d3dDevice.SetName(L"DeviceResources");

#ifndef NDEBUG
    auto d3dInfoQueue = m_d3dDevice.As<D3D12::D3D12InfoQueue>( );
    if ( d3dInfoQueue )
    {
#ifdef _DEBUG
        d3dInfoQueue.SetBreakOnSeverity( D3D12_MESSAGE_SEVERITY_CORRUPTION, true );
        d3dInfoQueue.SetBreakOnSeverity( D3D12_MESSAGE_SEVERITY_ERROR, true );
#endif
        D3D12_MESSAGE_ID hide[ ] =
        {
            D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,
            D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,
            D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_WRONGSWAPCHAINBUFFERREFERENCE
        };
        D3D12_INFO_QUEUE_FILTER filter = {};
        filter.DenyList.NumIDs = _countof( hide );
        filter.DenyList.pIDList = hide;
        d3dInfoQueue.AddStorageFilterEntries( &filter );
    }
#endif    

    // Determine maximum supported feature level for this device
    static const D3D_FEATURE_LEVEL s_featureLevels[] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

    D3D12_FEATURE_DATA_FEATURE_LEVELS featLevels =
    {
        _countof(s_featureLevels), s_featureLevels, D3D_FEATURE_LEVEL_11_0
    };

    auto success = m_d3dDevice.CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &featLevels, sizeof(featLevels));
    if ( success )
    {
        m_d3dFeatureLevel = featLevels.MaxSupportedFeatureLevel;
    }
    else
    {
        m_d3dFeatureLevel = m_d3dMinFeatureLevel;
    }

    // Create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    auto hr = m_d3dDevice.GetDeviceRemovedReason( );
    CheckHRESULT( hr );

    m_commandQueue = m_d3dDevice.CreateCommandQueue( );

    m_commandQueue.SetName(L"DeviceResources");

    // Create descriptor heaps for render target views and depth stencil views.
    D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc = {};
    rtvDescriptorHeapDesc.NumDescriptors = m_backBufferCount;
    rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

    m_rtvDescriptorHeap = m_d3dDevice.CreateDescriptorHeap( rtvDescriptorHeapDesc );

    m_rtvDescriptorHeap.SetName(L"DeviceResources");

    m_rtvDescriptorSize = m_d3dDevice.GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    if (m_depthBufferFormat != DXGI_FORMAT_UNKNOWN)
    {
        D3D12_DESCRIPTOR_HEAP_DESC dsvDescriptorHeapDesc = {};
        dsvDescriptorHeapDesc.NumDescriptors = 1;
        dsvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

        m_dsvDescriptorHeap = m_d3dDevice.CreateDescriptorHeap( dsvDescriptorHeapDesc );
        m_dsvDescriptorHeap.SetName(L"DeviceResources");
    }

    // Create a command allocator for each back buffer that will be rendered to.
    for (UINT n = 0; n < m_backBufferCount; n++)
    {
        m_commandAllocators[ n ] = m_d3dDevice.CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT );

        wchar_t name[25] = {};
        swprintf_s(name, L"Render target %u", n);
        m_commandAllocators[n].SetName(name);
    }

    // Create a command list for recording graphics commands.

    m_commandList = m_d3dDevice.CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[ 0 ] );
    m_commandList.Close( );
    m_commandList.SetName(L"DeviceResources");

    // Create a fence for tracking GPU execution progress.
    m_fence = m_d3dDevice.CreateFence( m_fenceValues[ m_backBufferIndex ] );
    m_fenceValues[m_backBufferIndex]++;

    m_fence.SetName(L"DeviceResources");

    m_fenceEvent.SetHandle(CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE));
    if (!m_fenceEvent)
    {
        throw std::exception("CreateEvent");
    }
}

// These resources need to be recreated every time the window size is changed.
void DeviceResources::CreateWindowSizeDependentResources()
{
    if (!m_window)
    {
        throw std::exception("Call SetWindow with a valid Win32 window handle");
    }

    // Wait until all previous GPU work is complete.
    WaitForGpu();

    // Release resources that are tied to the swap chain and update fence values.
    for (UINT n = 0; n < m_backBufferCount; n++)
    {
        m_renderTargets[n].ResetPtr();
        m_fenceValues[n] = m_fenceValues[m_backBufferIndex];
    }

    // Determine the render target size in pixels.
    UINT backBufferWidth = std::max<UINT>(static_cast<UINT>(m_outputSize.right - m_outputSize.left), 1u);
    UINT backBufferHeight = std::max<UINT>(static_cast<UINT>(m_outputSize.bottom - m_outputSize.top), 1u);
    DXGI::Format backBufferFormat = NoSRGB(m_backBufferFormat);

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = S_OK;
        try
        {
            // If the swap chain already exists, resize it.
            m_swapChain.ResizeBuffers(
                m_backBufferCount,
                backBufferWidth,
                backBufferHeight,
                backBufferFormat,
                ( m_options & c_AllowTearing ) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u
            );
        }
        catch ( const Exception& exc )
        {
            hr = exc.GetHRESULT( );
        }

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
#ifdef _DEBUG
            char buff[64] = {};
            sprintf_s(buff, "Device Lost on ResizeBuffers: Reason code 0x%08X\n", (hr == DXGI_ERROR_DEVICE_REMOVED) ? m_d3dDevice.GetDeviceRemovedReason() : hr);
            OutputDebugStringA(buff);
#endif
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            HandleDeviceLost();

            // Everything is set up now. Do not continue execution of this method. HandleDeviceLost will reenter this method
            // and correctly set up the new device.
            return;
        }
        else
        {
            CheckHRESULT( hr );
        }
    }
    else
    {
        // Create a descriptor for the swap chain.
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = backBufferWidth;
        swapChainDesc.Height = backBufferHeight;
        swapChainDesc.Format = static_cast<DXGI_FORMAT>( backBufferFormat );
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = m_backBufferCount;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
        swapChainDesc.Flags = (m_options & c_AllowTearing) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
        fsSwapChainDesc.Windowed = TRUE;

        // Create a swap chain for the window.
        m_swapChain = m_dxgiFactory.CreateSwapChainForHwnd<DXGI::SwapChain3>(
            m_commandQueue,
            m_window,
            &swapChainDesc,
            &fsSwapChainDesc,
            nullptr);


        // This class does not support exclusive full-screen mode and prevents DXGI from responding to the ALT+ENTER shortcut
        m_dxgiFactory.MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER);
    }

    // Handle color space settings for HDR
    UpdateColorSpace();

    // Obtain the back buffers for this window which will be the final render targets
    // and create render target views for each of them.
    for (UINT n = 0; n < m_backBufferCount; n++)
    {
        m_renderTargets[ n ] = m_swapChain.GetBuffer<D3D12::Resource>( n );

        wchar_t name[25] = {};
        swprintf_s(name, L"Render target %u", n);
        m_renderTargets[n].SetName(name);

        D3D12::RenderTargetViewDesc rtvDesc = {};
        rtvDesc.Format = m_backBufferFormat;
        rtvDesc.ViewDimension = D3D12::RenderTargetViewType::Texture2D;

        D3D12::CPUDescriptorHandle rtvDescriptor( m_rtvDescriptorHeap.GetCPUDescriptorHandleForHeapStart( ), static_cast< INT >( n ), m_rtvDescriptorSize );
        
        m_d3dDevice.CreateRenderTargetView(m_renderTargets[n], rtvDesc, rtvDescriptor);
    }

    // Reset the index to the current back buffer.
    m_backBufferIndex = m_swapChain.GetCurrentBackBufferIndex();

    if (m_depthBufferFormat != DXGI_FORMAT_UNKNOWN)
    {
        // Allocate a 2-D surface as the depth/stencil buffer and create a depth/stencil view
        // on this surface.
        D3D12::HeapProperties depthHeapProperties;

        D3D12::ResourceDesc depthStencilDesc = D3D12::ResourceDesc::Tex2D(
            m_depthBufferFormat,
            backBufferWidth,
            backBufferHeight,
            1, // This depth stencil view has only one texture.
            1,  // Use a single mipmap level.
            1, 0, D3D12::ResourceFlags::AllowDepthStencil );


        D3D12::ClearValue depthOptimizedClearValue = {};
        depthOptimizedClearValue.Format = m_depthBufferFormat;
        depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
        depthOptimizedClearValue.DepthStencil.Stencil = 0;

        m_depthStencil = m_d3dDevice.CreateCommittedResource(
            depthHeapProperties,
            D3D12::HeapFlags::None,
            depthStencilDesc,
            D3D12::ResourceStates::DepthWrite,
            depthOptimizedClearValue );

        m_depthStencil.SetName(L"Depth stencil");

        D3D12::DepthStencilViewDesc dsvDesc = {};
        dsvDesc.Format = m_depthBufferFormat;
        dsvDesc.ViewDimension = D3D12::DSVDimension::Texture2D;

        m_d3dDevice.CreateDepthStencilView(m_depthStencil, &dsvDesc, m_dsvDescriptorHeap.GetCPUDescriptorHandleForHeapStart());
    }

    // Set the 3D rendering viewport and scissor rectangle to target the entire window.
    m_screenViewport.TopLeftX = m_screenViewport.TopLeftY = 0.f;
    m_screenViewport.Width = static_cast<float>(backBufferWidth);
    m_screenViewport.Height = static_cast<float>(backBufferHeight);
    m_screenViewport.MinDepth = D3D12_MIN_DEPTH;
    m_screenViewport.MaxDepth = D3D12_MAX_DEPTH;

    m_scissorRect.Assign( 0, 0, static_cast< LONG >( backBufferWidth ), static_cast< LONG >( backBufferHeight ) );

}

// This method is called when the Win32 window is created (or re-created).
void DeviceResources::SetWindow(HWND window, int width, int height)
{
    m_window = window;

    m_outputSize.left = m_outputSize.top = 0;
    m_outputSize.right = width;
    m_outputSize.bottom = height;
}

// This method is called when the Win32 window changes size.
bool DeviceResources::WindowSizeChanged(int width, int height)
{
    RECT newRc;
    newRc.left = newRc.top = 0;
    newRc.right = width;
    newRc.bottom = height;
    if (newRc.left == m_outputSize.left
        && newRc.top == m_outputSize.top
        && newRc.right == m_outputSize.right
        && newRc.bottom == m_outputSize.bottom)
    {
        // Handle color space settings for HDR
        UpdateColorSpace();

        return false;
    }

    m_outputSize = newRc;
    CreateWindowSizeDependentResources();
    return true;
}

// Recreate all device resources and set them back to the current state.
void DeviceResources::HandleDeviceLost()
{
    if (m_deviceNotify)
    {
        m_deviceNotify->OnDeviceLost();
    }

    for (UINT n = 0; n < m_backBufferCount; n++)
    {
        m_commandAllocators[n].ResetPtr();
        m_renderTargets[n].ResetPtr();
    }

    m_depthStencil.ResetPtr();
    m_commandQueue.ResetPtr();
    m_commandList.ResetPtr();
    m_fence.ResetPtr();
    m_rtvDescriptorHeap.ResetPtr();
    m_dsvDescriptorHeap.ResetPtr();
    m_swapChain.ResetPtr();
    m_d3dDevice.ResetPtr();
    m_dxgiFactory.ResetPtr();

#ifdef _DEBUG
    {
        
        Harlinn::Common::Core::ComPtr<IDXGIDebug1> dxgiDebug;
        if (SUCCEEDED(DXGIGetDebugInterface1(0, __uuidof( IDXGIDebug1 ), reinterpret_cast<void**>(&dxgiDebug ) ) ) )
        {
            dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
        }
    }
#endif

    CreateDeviceResources();
    CreateWindowSizeDependentResources();

    if (m_deviceNotify)
    {
        m_deviceNotify->OnDeviceRestored();
    }
}

// Prepare the command list and render target for rendering.
void DeviceResources::Prepare( D3D12::ResourceStates beforeState)
{
    // Reset command list and allocator.
    m_commandAllocators[m_backBufferIndex].Reset();
    m_commandList.Reset(m_commandAllocators[m_backBufferIndex], nullptr);

    if (beforeState != D3D12_RESOURCE_STATE_RENDER_TARGET)
    {
        // Transition the render target into the correct state to allow for drawing into it.
        m_commandList.ResourceBarrier( m_renderTargets[ m_backBufferIndex ], beforeState, D3D12::ResourceStates::RenderTarget );
    }
}

// Present the contents of the swap chain to the screen.
void DeviceResources::Present( D3D12::ResourceStates beforeState)
{
    if (beforeState != D3D12::ResourceStates::Present)
    {
        // Transition the render target to the state that allows it to be presented to the display.
        m_commandList.ResourceBarrier( m_renderTargets[ m_backBufferIndex ], beforeState, D3D12::ResourceStates::Present );
    }

    // Send the command list off to the GPU for processing.
    m_commandList.Close();
    m_commandQueue.ExecuteCommandLists(m_commandList);

    HRESULT hr = S_OK;
    try
    {
        if ( m_options & c_AllowTearing )
        {
            // Recommended to always use tearing if supported when using a sync interval of 0.
            // Note this will fail if in true 'fullscreen' mode.
            m_swapChain.Present( 0, DXGI_PRESENT_ALLOW_TEARING );
        }
        else
        {
            // The first argument instructs DXGI to block until VSync, putting the application
            // to sleep until the next VSync. This ensures we don't waste any cycles rendering
            // frames that will never be displayed to the screen.
            m_swapChain.Present( 1, 0 );
        }
    }
    catch ( const Exception& exc )
    {
        hr = exc.GetHRESULT( );
    }

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
#ifdef _DEBUG
        char buff[64] = {};
        sprintf_s(buff, "Device Lost on Present: Reason code 0x%08X\n", (hr == DXGI_ERROR_DEVICE_REMOVED) ? m_d3dDevice.GetDeviceRemovedReason() : hr);
        OutputDebugStringA(buff);
#endif
        HandleDeviceLost();
    }
    else
    {
        CheckHRESULT(hr);

        MoveToNextFrame();

        if (!m_dxgiFactory.IsCurrent())
        {
            // Output information is cached on the DXGI Factory. If it is stale we need to create a new factory.
            m_dxgiFactory = DXGI::CreateFactory( m_dxgiFactoryFlags );
        }
    }
}

// Wait for pending GPU work to complete.
void DeviceResources::WaitForGpu() noexcept
{
    if (m_commandQueue && m_fence && m_fenceEvent)
    {
        // Schedule a Signal command in the GPU queue.
        UINT64 fenceValue = m_fenceValues[m_backBufferIndex];
        m_commandQueue.Signal( m_fence, fenceValue );
        m_fence.SetEventOnCompletion( fenceValue, m_fenceEvent );
        m_fenceEvent.Wait( );
        // Increment the fence value for the current frame.
        m_fenceValues[ m_backBufferIndex ]++;
        m_fenceEvent.ResetEvent( );
    }
}

// Prepare to render the next frame.
void DeviceResources::MoveToNextFrame()
{
    // Schedule a Signal command in the queue.
    const UINT64 currentFenceValue = m_fenceValues[m_backBufferIndex];
    m_commandQueue.Signal(m_fence, currentFenceValue);

    // Update the back buffer index.
    m_backBufferIndex = m_swapChain.GetCurrentBackBufferIndex();

    // If the next frame is not ready to be rendered yet, wait until it is ready.
    if (m_fence.GetCompletedValue() < m_fenceValues[m_backBufferIndex])
    {
        m_fence.SetEventOnCompletion(m_fenceValues[m_backBufferIndex], m_fenceEvent);
        m_fenceEvent.Wait( );
        m_fenceEvent.ResetEvent( );
    }

    // Set the fence value for the next frame.
    m_fenceValues[m_backBufferIndex] = currentFenceValue + 1;
}

// This method acquires the first available hardware adapter that supports Direct3D 12.
// If no such adapter can be found, try WARP. Otherwise throw an exception.
DXGI::Adapter4 DeviceResources::GetAdapter( )
{
    DXGI::Adapter4 adapter = m_dxgiFactory.FindAdapter( DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, m_d3dMinFeatureLevel );
    
    if ( !adapter )
    {
        adapter = m_dxgiFactory.EnumWarpAdapter<DXGI::Adapter4>( );
    }
    if (!adapter)
    {
        throw std::exception("No Direct3D 12 device found");
    }
    if ( adapter )
    {
        auto desc = adapter.GetDesc( );
        PrintLn( L"Adapter: {}", desc.Description );

    }
    return adapter;
}

// Sets the color space for the swap chain in order to handle HDR output.
void DeviceResources::UpdateColorSpace()
{
    DXGI_COLOR_SPACE_TYPE colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;

    bool isDisplayHDR10 = false;

    if (m_swapChain)
    {
        auto output = m_swapChain.GetContainingOutput<DXGI::Output6>( );
        auto desc = output.GetDesc1( );
        if ( desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 )
        {
            // Display output is HDR10.
            isDisplayHDR10 = true;
        }
    
    if ((m_options & c_EnableHDR) && isDisplayHDR10)
    {
        switch (m_backBufferFormat)
        {
        case DXGI_FORMAT_R10G10B10A2_UNORM:
            // The application creates the HDR10 signal.
            colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;
            break;

        case DXGI_FORMAT_R16G16B16A16_FLOAT:
            // The system creates the HDR10 signal; application uses linear values.
            colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709;
            break;

        default:
            break;
        }
    }

    m_colorSpace = colorSpace;

    UINT colorSpaceSupport = 0;
    if ( m_swapChain.CheckColorSpaceSupport( colorSpace, &colorSpaceSupport )
        && ( colorSpaceSupport & DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT ) )
    {
        m_swapChain.SetColorSpace1( colorSpace );
    }
    }

}
