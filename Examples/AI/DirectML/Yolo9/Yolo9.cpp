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

#include "yolo9.h"

#include "ATGColors.h"
#include "ControllerFont.h"
#include "FindMedia.h"
#include "ReadData.h"

#include "Polyline2D.h"


double threshold = .45;

//const wchar_t* c_videoPath = L"grca-grand-canyon-association-park-store_1280x720.mp4";
const wchar_t* c_videoPath = L"175876-854230219_tiny.mp4";
//const wchar_t* c_videoPath = L"216619_large.mp4";
//const wchar_t* c_videoPath = L"6387-191695740_large.mp4";
const wchar_t* c_imagePath = L"grca-BA-bike-shop_1280x720.jpg";

extern void ExitSample();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

namespace
{
    struct Vertex
    {
        XMFLOAT4 position;
        XMFLOAT2 texcoord;
    };

    


    std::vector<uint8_t> LoadBGRAImage( const wchar_t* filename, uint32_t& width, uint32_t& height )
    {
        width = 520;
        height = 520;
        WICPixelFormatGUID pixelFormat = GUID_WICPixelFormat32bppBGRA;

        uint32_t rowPitch = width * sizeof( uint32_t );
        uint32_t imageSize = rowPitch * height;

        std::vector<uint8_t> image;
        image.resize( size_t( imageSize ) );

        BYTE* p = ( BYTE* )image.data( );
        for ( int i = 0; i < imageSize / 4; i++ )
        {
            p[ 0 ] = p[ 1 ] = p[ 2 ] = 0;
            p[ 2 ] = 0;
            p[ 3 ] = 0;
            p += 4;
        }

        return image;
    }

}



bool Sample::CopySharedVideoTextureTensor( Binary& inputBuffer )
{

    // Record start
    auto start = std::chrono::high_resolution_clock::now( );

    const auto& device = m_player->GetDevice( );

    D3D11::Texture2D mediaTexture = device.OpenSharedResource<D3D11::Texture2D>( m_sharedVideoTexture );

    if ( mediaTexture )
    {
        // First verify that we can map the texture
        D3D11_TEXTURE2D_DESC desc;
        mediaTexture.GetDesc( &desc );

        // translate texture format to WIC format. We support only BGRA and ARGB.
        GUID wicFormatGuid;
        switch ( desc.Format )
        {
            case DXGI_FORMAT_R8G8B8A8_UNORM:
                wicFormatGuid = GUID_WICPixelFormat32bppRGBA;
                break;
            case DXGI_FORMAT_B8G8R8A8_UNORM:
                wicFormatGuid = GUID_WICPixelFormat32bppBGRA;
                break;
            default:
                throw std::exception( "Unsupported DXGI_FORMAT: %d. Only RGBA and BGRA are supported." );
        }

        // Get the device context

        D3D11::DeviceContext d3dContext = device.GetImmediateContext( );

        // map the texture
        D3D11::Texture2D mappedTexture;
        D3D11_MAPPED_SUBRESOURCE mapInfo{};

        HRESULT hr = d3dContext.Map<true>( mediaTexture,
            0,  // Subresource
            D3D11_MAP_READ,
            0,  // MapFlags
            &mapInfo );

        if ( FAILED( hr ) )
        {
            // If we failed to map the texture, copy it to a staging resource
            if ( hr == E_INVALIDARG )
            {
                D3D11_TEXTURE2D_DESC desc2;
                desc2.Width = desc.Width;
                desc2.Height = desc.Height;
                desc2.MipLevels = desc.MipLevels;
                desc2.ArraySize = desc.ArraySize;
                desc2.Format = desc.Format;
                desc2.SampleDesc = desc.SampleDesc;
                desc2.Usage = D3D11_USAGE_STAGING;
                desc2.BindFlags = 0;
                desc2.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
                desc2.MiscFlags = 0;

                D3D11::Texture2D stagingTexture = device.CreateTexture2D( &desc2 );

                // copy the texture to a staging resource
                d3dContext.CopyResource( stagingTexture, mediaTexture );

                // now, map the staging resource
                d3dContext.Map( stagingTexture, 0, D3D11_MAP_READ, 0, &mapInfo );
                mappedTexture = std::move( stagingTexture );
            }
            else
            {
                CheckHRESULT( hr );
            }
        }
        else
        {
            mappedTexture = mediaTexture;
        }
        auto unmapResource = Finally( [ & ]
            {
                d3dContext.Unmap( mappedTexture, 0 );
            } );


        const size_t inputChannels = model_->InputChannels( );
        const size_t inputHeight = model_->InputHeight( );
        const size_t inputWidth = model_->InputWidth( );

        if ( desc.Width != inputWidth || desc.Height != inputHeight )
        {
            D2D1_FACTORY_OPTIONS options = {};
            if ( m_d2d1_factory == nullptr )
            {
                // Create a Direct2D factory.
                m_d2d1_factory = D2D::CreateFactory( D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED );

                // Create D2Device 
                //auto device = m_deviceResources->GetD3DDevice();
                // DXGI::Device3 dxgiDevice = device.As<DXGI::Device3>( );

                const auto& swapChain = m_deviceResources->GetSwapChain( );
                if ( swapChain )
                {
                    auto dxgiDevice = swapChain.GetDevice<DXGI::Device>( );
                    if ( dxgiDevice )
                    {
                        m_d2d1_device = m_d2d1_factory.CreateDevice( dxgiDevice );
                        // Get Direct2D device's corresponding device context object.
                        m_d2dContext = m_d2d1_device.CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS_NONE );
                    }
                }
            }
            if ( m_d2dContext )
            {
                DXGI::Surface surface = mediaTexture.As<DXGI::Surface>( );

                auto bitmap = m_d2dContext.CreateBitmapFromDxgiSurface( surface );

                auto scaleEffect = m_d2dContext.CreateEffect( CLSID_D2D1Scale );

                scaleEffect.SetInput( 0, bitmap );


                D2D1_SCALE_INTERPOLATION_MODE interpolationMode = D2D1_SCALE_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC;
                //D2D1_SCALE_INTERPOLATION_MODE interpolationMode = D2D1_SCALE_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
                scaleEffect.SetValue( D2D1_SCALE_PROP_SCALE, D2D1::Vector2F( ( float )inputWidth / ( float )desc.Width, ( float )inputHeight / ( float )desc.Height ) );
                scaleEffect.SetValue( D2D1_SCALE_PROP_INTERPOLATION_MODE, reinterpret_cast< const BYTE* >( &interpolationMode ), sizeof( D2D1_SCALE_INTERPOLATION_MODE ) ); // Set the interpolation mode.

                auto image_out = scaleEffect.GetOutput( );

                D3D11_TEXTURE2D_DESC texDesc;
                texDesc.Width = static_cast< UINT >( inputWidth );
                texDesc.Height = static_cast< UINT >( inputHeight );
                texDesc.MipLevels = 1;
                texDesc.ArraySize = 1;
                texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                texDesc.SampleDesc.Count = 1;
                texDesc.SampleDesc.Quality = 0;
                texDesc.Usage = D3D11_USAGE_DEFAULT;
                texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
                texDesc.CPUAccessFlags = 0;
                texDesc.MiscFlags = 0;

                auto drawTexture = device.CreateTexture2D( &texDesc );

                auto drawSurface = drawTexture.As<DXGI::Surface>( );

                auto drawBitmap = m_d2dContext.CreateBitmapFromDxgiSurface( drawSurface );
                m_d2dContext.SetTarget( drawBitmap );


                // Draw the image into the device context. Output surface is set as the target of the device context.
                m_d2dContext.BeginDraw( );

                auto identityMat = D2D1::Matrix3x2F::Identity( );

                // Clear out any existing transform before drawing.
                m_d2dContext.SetTransform( identityMat );
                D2D1_POINT_2F targetOffset = { 0, 0 };
                m_d2dContext.DrawImage( image_out, targetOffset );
                D2D1_TAG tag1;
                D2D1_TAG tag2;
                m_d2dContext.EndDraw( &tag1, &tag2 );
                m_d2dContext.SetTarget( nullptr );


                // we have our scaled image in drawTexture

                // create staging texture
                D3D11_TEXTURE2D_DESC desc2;
                desc2.Width = texDesc.Width;
                desc2.Height = texDesc.Height;
                desc2.MipLevels = texDesc.MipLevels;
                desc2.ArraySize = texDesc.ArraySize;
                desc2.Format = texDesc.Format;
                desc2.SampleDesc = texDesc.SampleDesc;
                desc2.Usage = D3D11_USAGE_STAGING;
                desc2.BindFlags = 0;
                desc2.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
                desc2.MiscFlags = 0;

                auto stagingTexture = device.CreateTexture2D( &desc2 );

                // copy the texture to a staging resource
                d3dContext.CopyResource( stagingTexture, drawTexture );

                // now, map the staging resource
                d3dContext.Map( stagingTexture, 0, D3D11_MAP_READ, 0, &mapInfo );

                mappedTexture = std::move( stagingTexture );
                mappedTexture.GetDesc( &desc );

            }

        }

        inputBuffer = model_->CreateInputBuffer( ( std::byte* )mapInfo.pData, desc.Width, desc.Height, mapInfo.RowPitch );

        auto end = std::chrono::high_resolution_clock::now( );
        m_copypixels_tensor_duration += ( end - start );

        return true;
    }
    return false;
}


Sample::Sample()
    : io_( GetImGuiIO( ) ), m_ctrlConnected(false), m_run_on_gpu(false)
{
    io_.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //::ImGui::StyleColorsClassic( );
    ::ImGui::StyleColorsLight( );

    // Use gamma-correct rendering.
    // Renders only 2D, so no need for a depth buffer.
    m_deviceResources = std::make_unique<DX::DeviceResources>(DXGI::Format::B8G8R8A8_UNORM, DXGI::Format::Unknown,
        3, D3D_FEATURE_LEVEL_11_0, DX::DeviceResources::c_AllowTearing);
    m_deviceResources->RegisterDeviceNotify(this);
}

Sample::~Sample()
{
    if (m_deviceResources)
    {
        m_deviceResources->WaitForGpu();
    }
    ImGui_ImplDX12_Shutdown( );
    ImGui_ImplWin32_Shutdown( );
    ::ImPlot::DestroyContext( );
    ::ImGui::DestroyContext( );
}

// Initialize the Direct3D resources required to run.
bool Sample::Initialize(HWND window, int width, int height, bool run_on_gpu)
{

    m_run_on_gpu = run_on_gpu;

    m_gamePad = std::make_unique<GamePad>();

    m_keyboard = std::make_unique<Keyboard>();
    
    m_deviceResources->SetWindow(window, width, height);

    auto sessionOptions = std::make_shared<ONNX::SessionOptions>( );

    sessionOptions->DisableMemPattern( );
    sessionOptions->DisablePerSessionThreads( );
    sessionOptions->SetExecutionMode( ExecutionMode::ORT_SEQUENTIAL );

    computeEngine_ = std::make_shared<ONNX::DirectML::ComputeEngine>( sessionOptions );
    computeEngine_->Environment( )->DisableTelemetryEvents( );
    computeNode_ = computeEngine_->AddComputeNode( L"Compute Node" );


    // Add the DML execution provider to ORT using the DML Device and D3D12 Command Queue created above.
    InitializeDirectMLResources();

    m_deviceResources->CreateDeviceResources();  	

    const auto& d3dDevice = m_deviceResources->GetD3DDevice( );
    auto& shaderResourceViewDescHeap = m_deviceResources->ShaderResourceViewDescHeap( );
    ImGui_ImplWin32_Init( window );
    ImGui_ImplDX12_Init( static_cast< ID3D12Device* >( d3dDevice.GetInterfacePointer( ) ),
        DX::DeviceResources::MAX_BACK_BUFFER_COUNT,
        DXGI_FORMAT_R8G8B8A8_UNORM,
        static_cast< ID3D12DescriptorHeap* >( shaderResourceViewDescHeap.GetInterfacePointer( ) ),
        shaderResourceViewDescHeap.GetCPUDescriptorHandleForHeapStart( ),
        shaderResourceViewDescHeap.GetGPUDescriptorHandleForHeapStart( ) );

    ImGui_ImplDX12_CreateDeviceObjects( );

    CreateDeviceDependentResources();
   
    m_deviceResources->CreateWindowSizeDependentResources();

    CreateWindowSizeDependentResources();

    

    return true;
}

#pragma region Frame Update
// Executes basic render loop.
void Sample::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Sample::Update(DX::StepTimer const& timer)
{

    float elapsedTime = float(timer.GetElapsedSeconds());

    m_fps.Tick(elapsedTime);

    auto pad = m_gamePad->GetState(0);
    if (pad.IsConnected())
    {
        m_ctrlConnected = true;

        m_gamePadButtons.Update(pad);

        if (pad.IsViewPressed())
        {
            ExitSample();
        }

        if (m_gamePadButtons.x == DirectX::GamePad::ButtonStateTracker::PRESSED && m_player.get() != nullptr)
        {
            if (m_player->IsPlaying())
            {
                m_player->Pause();
            }
            else
            {
                m_player->Play();
            }
        }
    }
    else
    {
        m_ctrlConnected = false;
        m_gamePadButtons.Reset();
    }

    auto kb = m_keyboard->GetState();
    m_keyboardButtons.Update(kb);



    if (kb.Escape)
    {
        ExitSample();
    }

    if (m_keyboardButtons.IsKeyPressed(Keyboard::G) && m_player.get() != nullptr)
    {
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(NULL, path, sizeof(path));
        const wchar_t* para = L"-gpu";
        _wexecl(path, L"%s", para);
        ExitSample();
    }
    if (m_keyboardButtons.IsKeyPressed(Keyboard::N) && m_player.get() != nullptr)
    {
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(NULL, path, sizeof(path));
        const wchar_t* para = L"-npu";
        _wexecl(path, L"%s", para);
        ExitSample();
    }

    if (m_keyboardButtons.IsKeyPressed(Keyboard::Enter) && m_player.get() != nullptr)
    {
        if (m_player->IsPlaying())
        {
            m_player->Pause();
        }
        else
        {
            m_player->Play();
        }
    }
    int mul = 1;
    if (m_keyboardButtons.IsKeyPressed(Keyboard::LeftControl) || m_keyboardButtons.IsKeyPressed(Keyboard::RightControl))
        mul = 10;
    if (m_keyboardButtons.IsKeyPressed(Keyboard::Right) && m_player.get() != nullptr)
    {
        m_player->Pause();
        if (m_keyboardButtons.IsKeyPressed(Keyboard::LeftShift) || m_keyboardButtons.IsKeyPressed(Keyboard::RightShift))
            m_player->Skip((float)30*mul);
        else
            m_player->Skip((float)10*mul);
        m_player->Play();
    }
    if (m_keyboardButtons.IsKeyPressed(Keyboard::Left) && m_player.get() != nullptr)
    {
        m_player->Pause();
        if (m_keyboardButtons.IsKeyPressed(Keyboard::LeftShift) || m_keyboardButtons.IsKeyPressed(Keyboard::RightShift))
            m_player->Skip((float)-30*mul);
        else
            m_player->Skip((float)-10*mul);
        m_player->Play();
    }
}
#pragma endregion

void Sample::OnNewModel(const wchar_t* modelfile, bool bAddModel)
{

    if (m_player->IsPlaying())
    {
        m_player->Pause();
    }
  
    InitializeDirectMLResources(modelfile, bAddModel);

    while (!m_player->IsInfoReady())
    {
        SwitchToThread();
    }

    m_player->Play();
    m_player->Skip(-5);
}


void Sample::OnNewFile(const wchar_t* filename)
{
    if (m_player->IsPlaying())
    {
        m_player->Pause();
    }

    m_player->SetSource(filename);

    while (!m_player->IsInfoReady())
    {
        SwitchToThread();
    }

    m_player->GetNativeVideoSize(m_origTextureWidth, m_origTextureHeight);
    m_player->SetLoop(true);

    // Create texture to receive video frames.
    D3D12::ResourceDesc desc(
        D3D12::ResourceDimension::Texture2D,
        0,
        m_origTextureWidth,
        m_origTextureHeight,
        1,
        1,
        DXGI::Format::B8G8R8A8_UNORM,
        1,
        0,
        D3D12::TextureLayout::Unknown,
        D3D12::ResourceFlags::AllowRenderTarget | D3D12::ResourceFlags::AllowSimultaneousAccess );

    D3D12::HeapProperties defaultHeapProperties( D3D12::HeapType::Default );
    auto device = m_deviceResources->GetD3DDevice();

    m_videoTexture = device.CreateCommittedResource(
        defaultHeapProperties,
        D3D12::HeapFlags::Shared,
        desc,
        D3D12::ResourceStates::NonPixelShaderResource );

    m_sharedVideoTexture = device.CreateSharedHandle( m_videoTexture );

    CreateShaderResourceView(device, m_videoTexture, m_SRVDescriptorHeap->GetCpuHandle(e_descTexture));


    m_player->Play();
}


#pragma region Frame Render


void Sample::BeginCompute( )
{

    auto inputSize = model_->InputSize( );
    Binary inputBuffer;
    if ( CopySharedVideoTextureTensor( inputBuffer ) )
    {
        auto viewport = m_deviceResources->GetScreenViewport( );
        Math::Vector2f viewportSize( viewport.Width, viewport.Height );
        computeNode_->Compute( inputBuffer, viewportSize );
    }
}

// Draws the scene.
void Sample::Render()
{

    frameTime_ = DateTime::Now( );

    auto frameCount = m_timer.GetFrameCount( );
    // Don't try to render anything before the first Update.
    if ( frameCount == 0)
    {
        return;
    }

    m_preds = model_->Predictions( );
    // Get the latest video frame
    RECT r = { 0, 0, static_cast< LONG >( m_origTextureWidth ), static_cast< LONG >( m_origTextureHeight ) };
    MFVideoNormalizedRect rect = { 0.0f, 0.0f, 1.0f, 1.0f };

    if ( !m_player->TransferFrame( m_sharedVideoTexture, rect, r, m_pts ) )
    {
        return;
    }

    ImGui_ImplDX12_NewFrame( );
    ImGui_ImplWin32_NewFrame( );
    ::ImGui::NewFrame( );

    

    // 
    // Kick off the compute work that will be used to render the next frame. We do this now so that the data will be
    // ready by the time the next frame comes around.
    // 
    if ( frameTime_ > nextCompute_ )
    {
        nextCompute_ = frameTime_ + computeInterval_;
        BeginCompute( );
    }
    // Prepare the command list to render a new frame.
    m_deviceResources->Prepare();
    Clear();

    const auto& commandList = m_deviceResources->GetCommandList();

    // Render the result to the screen

    const auto& viewport = m_deviceResources->GetScreenViewport();
    const auto& scissorRect = m_deviceResources->GetScissorRect();

    {
        commandList.OMSetRenderTargets(1, m_deviceResources->GetRenderTargetView());

        commandList.SetGraphicsRootSignature(m_texRootSignatureLinear);
        commandList.SetPipelineState(m_texPipelineStateLinear);

        auto heap = m_SRVDescriptorHeap->Heap();
        commandList.SetDescriptorHeaps(heap);

        commandList.SetGraphicsRootDescriptorTable(0, m_SRVDescriptorHeap->GetGpuHandle(e_descTexture));

        // Set necessary state.
        commandList.IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        commandList.IASetIndexBuffer(m_indexBufferView);

        // Draw full screen texture
        commandList.RSSetViewports(viewport);
        commandList.RSSetScissorRects(scissorRect);
        commandList.IASetVertexBuffers(0, 1, m_vertexBufferView);

        commandList.DrawIndexedInstanced(6, 1, 0, 0, 0);

        if (m_mask.size() > 0 && m_texture)
        {

            commandList.SetGraphicsRootSignature(m_texRootSignatureLinear);
            commandList.SetPipelineState(m_texPipelineStateLinear);

            auto heap = m_SRVDescriptorHeap->Heap();
            commandList.SetDescriptorHeaps(1, &heap);

            commandList.SetGraphicsRootDescriptorTable(0, m_SRVDescriptorHeap->GetGpuHandle(e_outputTensor));

            // Set necessary state.
            commandList.IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            commandList.IASetIndexBuffer(m_indexBufferView);

            // Draw full screen texture
            commandList.RSSetViewports(viewport);
            commandList.RSSetScissorRects(1, &scissorRect);
            commandList.IASetVertexBuffers(0, 1, m_vertexBufferView);

            commandList.DrawIndexedInstanced(6, 1, 0, 0, 0);

        }
    }

    // Readback the raw data from the model, compute the model's predictions, and render the bounding boxes
    {

        commandList.RSSetViewports(viewport);
        commandList.RSSetScissorRects(scissorRect);

        // Draw bounding box outlines
        m_lineEffect->Apply(commandList);

        m_lineBatch->Begin(commandList);
        float label_height = 5.0f;
        float dx = 5.0f;

        for (auto& pred : m_preds)
        {
            if (pred.predictedClass < 0)
            {
                label_height = 1.0f;
                dx = 2.0f;
            }
            else
            {
                label_height = 5.0f;
                dx = 5.0f;

            }


            m_lineEffect->SetAlpha(0.4f /*pred.score / 5.0*/);
          
    
            int col = YoloConstants::colors[((pred.predictedClass < 0) ? 0 : pred.predictedClass) % 20];
            DirectX::XMVECTORF32 White = { { { (col >> 16) / 255.0f, ((col >> 8) & 0xff) / 255.0f, (col & 0xff) / 255.0f, 1.0f} } }; // #fafafa


            {
                for (int i = 0; i < 2; i++)
                {
                    DirectX::XMVECTORF32 White = { { { (col >> 16) / 255.0f, ((col >> 8) & 0xff) / 255.0f, (col & 0xff) / 255.0f, 1.0f} } }; // #fafafa
                    if (i == 1)
                        White = { { { (col >> 16) / 255.0f, ((col >> 8) & 0xff) / 255.0f, (col & 0xff) / 255.0f, 1.0f} } }; // #fafafa
                    {
                        VertexPositionColor upperLeft(SimpleMath::Vector3(pred.xmin, pred.ymin, 0.f), White);
                        VertexPositionColor upperRight(SimpleMath::Vector3(pred.xmax, pred.ymin, 0.f), White);
                        VertexPositionColor lowerRight(SimpleMath::Vector3(pred.xmax, pred.ymin + label_height * dx, 0.f), White);
                        VertexPositionColor lowerLeft(SimpleMath::Vector3(pred.xmin, pred.ymin + label_height * dx, 0.f), White);
                        m_lineBatch->DrawQuad(upperLeft, upperRight, lowerRight, lowerLeft);
                    }

                    {
                        VertexPositionColor upperLeft(SimpleMath::Vector3(pred.xmin, pred.ymin + dx, 0.f), White);
                        VertexPositionColor upperRight(SimpleMath::Vector3(pred.xmin + dx, pred.ymin + dx, 0.f), White);
                        VertexPositionColor lowerRight(SimpleMath::Vector3(pred.xmin + dx, pred.ymax - dx, 0.f), White);
                        VertexPositionColor lowerLeft(SimpleMath::Vector3(pred.xmin, pred.ymax - dx, 0.f), White);
                        m_lineBatch->DrawQuad(upperLeft, upperRight, lowerRight, lowerLeft);
                    }
                    {

                        VertexPositionColor upperLeft(SimpleMath::Vector3(pred.xmin, pred.ymax - dx, 0.f), White);
                        VertexPositionColor upperRight(SimpleMath::Vector3(pred.xmax - dx, pred.ymax - dx, 0.f), White);
                        VertexPositionColor lowerRight(SimpleMath::Vector3(pred.xmax - dx, pred.ymax, 0.f), White);
                        VertexPositionColor lowerLeft(SimpleMath::Vector3(pred.xmin, pred.ymax, 0.f), White);
                        m_lineBatch->DrawQuad(upperLeft, upperRight, lowerRight, lowerLeft);
                    }
                    {
                        VertexPositionColor upperLeft(SimpleMath::Vector3(pred.xmax - dx, pred.ymin + dx, 0.f), White);
                        VertexPositionColor upperRight(SimpleMath::Vector3(pred.xmax, pred.ymin + dx, 0.f), White);
                        VertexPositionColor lowerRight(SimpleMath::Vector3(pred.xmax, pred.ymax, 0.f), White);
                        VertexPositionColor lowerLeft(SimpleMath::Vector3(pred.xmax - dx, pred.ymax, 0.f), White);
                        m_lineBatch->DrawQuad(upperLeft, upperRight, lowerRight, lowerLeft);
                    }
                }
            }
        }
        m_lineBatch->End();

        // Draw bounding box outlines
        m_lineEffect2->Apply(commandList);

        // Draw predicted class labels
        m_spriteBatch->Begin(commandList);
        for (const auto& pred : m_preds)
        {
            if (pred.predictedClass >= 0)
            {
                const char* classText = YoloConstants::c_classes[pred.predictedClass];
                std::wstring classTextW(classText, classText + strlen(classText));
                wchar_t _class[128];
                swprintf_s(_class, 128, L"%s %d%%", classTextW.c_str(), (int)(pred.score * 100.0f));
                    // Render a drop shadow by drawing the text twice with a slight offset.
                    DX::DrawControllerString(m_spriteBatch.get(), m_legendFont.get(), m_ctrlFont.get(),
                        _class, SimpleMath::Vector2(pred.xmin, pred.ymin - 1.5f * dx) + SimpleMath::Vector2(2.f, 2.f), SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.25f));
                    DX::DrawControllerString(m_spriteBatch.get(), m_legendFont.get(), m_ctrlFont.get(),
                        _class, SimpleMath::Vector2(pred.xmin, pred.ymin - 1.5f * dx), ATG::Colors::DarkGrey);
            }
        }
        m_spriteBatch->End();

        // Render the UI
        RenderUI( );
        
        ::ImGui::Render( );
        ID3D12GraphicsCommandList* commandListPtr = static_cast< ID3D12GraphicsCommandList* >( commandList.GetInterfacePointer( ) );
        ImGui_ImplDX12_RenderDrawData( ::ImGui::GetDrawData( ), commandListPtr );

    }

    // Show the new frame.
    m_deviceResources->Present();


    m_graphicsMemory->Commit(m_deviceResources->GetCommandQueue());

    
}

namespace
{
    AnsiString ToString( ONNXTensorElementDataType elementDataType )
    {
        switch ( elementDataType )
        {
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_UNDEFINED:
                return "Undefined";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT:
                return "Float";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8:
                return "UInt8";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8:
                return "Int8";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT16:
                return "UInt16";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_INT16:
                return "Int16";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32:
                return "Int32";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64:
                return "Int64";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_STRING:
                return "String";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_BOOL:
                return "Bool";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16:
                return "Float16";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_DOUBLE:
                return "Double";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT32:
                return "UInt32";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT64:
                return "UInt64";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_COMPLEX64:
                return "Complex64";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_COMPLEX128:
                return "Complex128";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_BFLOAT16:
                return "BFloat16";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT8E4M3FN:
                return "Float8 E4M3FN";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT8E4M3FNUZ:
                return "Float8 E4M3FNUZ";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT8E5M2:
                return "Float8 E5M2";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT8E5M2FNUZ:
                return "Float8 E5M2FNUZ";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT4:
                return "UInt4";
            case ONNXTensorElementDataType::ONNX_TENSOR_ELEMENT_DATA_TYPE_INT4:
                return "Int4";
        }
        return "Unknown";
    }

    void RenderTypeInfo( const std::shared_ptr<ONNX::TensorTypeAndShapeInfo>& info )
    {

        auto str = Format( "Element type: {}", ToString( info->ElementType( ) ) );
        ImGui::Text( str.c_str( ) );
        const auto& dimensions = info->Dimensions( );
        const auto& symbolicDimensions = info->SymbolicDimensions( );
        auto count = dimensions.size( );
        
        if ( ImGui::TreeNode( "Dimensions" ) )
        {
            for ( size_t i = 0; i < count; i++ )
            {
                auto name = symbolicDimensions[ i ];
                if ( !name )
                {
                    name = "<unnamed>";
                }
                str = Format( "{}: {}", name, dimensions[ i ] );
                ImGui::Text( str.c_str() );
            }
            ImGui::TreePop( );
        }
    }

    void RenderTypeInfo( size_t index, const std::shared_ptr<ONNX::TypeInfo>& typeInfo )
    {
        auto name = typeInfo->Name( );
        if ( !name )
        {
            name = Format( "unnamed##{}", index );
        }
        if ( ImGui::TreeNode( name.c_str() ) )
        {
            auto type = typeInfo->Type( );
            switch ( type )
            {
                case ONNX_TYPE_UNKNOWN:
                {
                    ImGui::Text( "Type: Unknown" );
                }
                break;
                case ONNX_TYPE_TENSOR:
                {
                    ImGui::Text( "Type: Tensor" );
                    auto tensorTypeAndShapeInfo = std::static_pointer_cast< ONNX::TensorTypeAndShapeInfo >( typeInfo );
                    RenderTypeInfo( tensorTypeAndShapeInfo );
                }
                break;
                case ONNX_TYPE_SPARSETENSOR:
                {
                    ImGui::Text( "Type: Sparse Tensor" );
                }
                break;
                case ONNX_TYPE_SEQUENCE:
                {
                    ImGui::Text( "Type: Sequence" );
                }
                break;
                case ONNX_TYPE_MAP:
                {
                    ImGui::Text( "Type: Map" );
                }
                break;
                case ONNX_TYPE_OPAQUE:
                {
                    ImGui::Text( "Type: Opaque" );
                }
                break;
                case ONNX_TYPE_OPTIONAL:
                {
                    ImGui::Text( "Type: Optional" );
                }
                break;
            }
            ImGui::TreePop( );
        }

    }
    void RenderTypeInfo( const std::vector<std::shared_ptr<ONNX::TypeInfo>>& typeInfos )
    {
        auto count = typeInfos.size( );
        for ( size_t i = 0; i < count; i++ )
        {
            const auto& typeInfo = typeInfos[ i ];
            RenderTypeInfo( i, typeInfo );
        }
    }
}

void Sample::RenderUI( )
{

    ImGui::Begin( "Yolo 9" );

    const char* modelLabel = "Object detection model:";

    ImGui::Text( modelLabel );
    auto str = ToAnsiString( model_->ModelFilename() );
    ImGui::Text( str.c_str( ) );

    str = Format( "Predictions: {}", m_preds.size() );
    ImGui::Text( str.c_str( ) );

    str = Format( "{:0.2f} FPS", m_fps.GetFPS( ) );
    ImGui::Text( str.c_str( ) );
    
    str = Format( "Inference: {:0.2f} ms", model_->ComputeTime().TotalMilliseconds() );
    ImGui::Text( str.c_str( ) );

    auto metadata = model_->Metadata( );

    str = Format( "Producer: {}", metadata->ProducerName( ) );
    ImGui::Text( str.c_str( ) );

    str = Format( "Description: {}", metadata->Description( ) );
    ImGui::Text( str.c_str( ) );

    str = Format( "Domain: {}", metadata->Domain( ) );
    ImGui::Text( str.c_str( ) );

    str = Format( "Graph name: {}", metadata->GraphName( ) );
    ImGui::Text( str.c_str( ) );

    str = Format( "Graph description: {}", metadata->GraphDescription( ) );
    ImGui::Text( str.c_str( ) );


    
    if ( ImGui::TreeNode( "Custom Metadata" ) )
    {
        const auto& customMetadata = metadata->CustomMetadataMap( );
        for ( const auto& entry : customMetadata )
        {
            str = Format( "{}: {}", entry.first, entry.second );
            ImGui::TextWrapped( str.c_str( ) );
        }
        ImGui::TreePop( );
    }

    if ( ImGui::TreeNode( "Inputs" ) )
    {
        const auto& inputs = metadata->Inputs( );
        RenderTypeInfo( inputs );
        ImGui::TreePop( );
    }

    if ( ImGui::TreeNode( "Outputs" ) )
    {
        const auto& outputs = metadata->Outputs( );
        RenderTypeInfo( outputs );
        ImGui::TreePop( );
    }
    if ( ImGui::TreeNode( "Overridable Initializers" ) )
    {
        const auto& overridableInitializers = metadata->OverridableInitializers( );
        RenderTypeInfo( overridableInitializers );
        ImGui::TreePop( );
    }




    ImGui::End( );
}



void Sample::NewTexture(const uint8_t* image_data, uint32_t width, uint32_t height)
{
    auto device = m_deviceResources->GetD3DDevice();
    auto commandList = m_deviceResources->GetCommandList();
    commandList.Reset(m_deviceResources->GetCommandAllocator(), nullptr);

    D3D12::Resource textureUploadHeap;

    D3D12::ResourceDesc txtDesc = {};
    bool new_texture = false;
    auto desc = m_texture.GetDesc();
    if (desc.Width != width || desc.Height != height)
    {

        txtDesc.MipLevels = txtDesc.DepthOrArraySize = 1;
        txtDesc.Format = DXGI::Format::B8G8R8A8_UNORM;
        txtDesc.SampleDesc.Count = 1;
        txtDesc.Dimension = D3D12::ResourceDimension::Texture2D;


        txtDesc.Width = width;
        txtDesc.Height = height;

        //m_origTextureWidth = width;
        //m_origTextureHeight = height;

       // wait for gpu to create new textures
        m_deviceResources->WaitForGpu();

        m_texture = device.CreateCommittedResource( D3D12::HeapProperties(D3D12::HeapType::Default),
                D3D12::HeapFlags::None,
                txtDesc,
                D3D12::ResourceStates::CopyDest);
        new_texture = true;
        if (new_texture)
        {
            // Describe and create a SRV for the texture.
            D3D12::ShaderResourceViewDesc srvDesc = {};
            srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            srvDesc.Format = txtDesc.Format;
            srvDesc.ViewDimension = D3D12::SRVDimension::Texture2D;
            srvDesc.Texture2D.MipLevels = 1;
            device.CreateShaderResourceView(m_texture, srvDesc, m_SRVDescriptorHeap->GetCpuHandle(e_outputTensor));
        }

    }
    else
        txtDesc = desc;
    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(m_texture, 0, 1);

    // Create the GPU upload buffer.
    textureUploadHeap = device.CreateCommittedResource(
            D3D12::HeapProperties(D3D12::HeapType::Upload),
            D3D12::HeapFlags::None,
            D3D12::ResourceDesc::Buffer(uploadBufferSize),
            D3D12::ResourceStates::GenericRead);

    D3D12::SubResourceData textureData = {};
    textureData.pData = image_data;
    textureData.RowPitch = static_cast<LONG_PTR>(txtDesc.Width * sizeof(uint32_t));
    textureData.SlicePitch = width * height * 4;

    UpdateSubResources(commandList, m_texture, textureUploadHeap, 0, 0, 1, &textureData);
    commandList.ResourceBarrier(m_texture, D3D12::ResourceStates::CopyDest, D3D12::ResourceStates::GenericRead);
   
    commandList.Close();
    m_deviceResources->GetCommandQueue().ExecuteCommandLists(commandList);

    // Wait until assets have been uploaded to the GPU.
    m_deviceResources->WaitForGpu();



}

// Helper method to clear the back buffers.
void Sample::Clear()
{
    auto commandList = m_deviceResources->GetCommandList();

    // Clear the views.
    auto rtvDescriptor = m_deviceResources->GetRenderTargetView();

    commandList.OMSetRenderTargets(1, &rtvDescriptor);
    // Use linear clear color for gamma-correct rendering.
    commandList.ClearRenderTargetView(rtvDescriptor, ATG::ColorsLinear::Background, 0, nullptr);

    // Set the viewport and scissor rect.
    auto viewport = m_deviceResources->GetScreenViewport();
    auto scissorRect = m_deviceResources->GetScissorRect();
    commandList.RSSetViewports(viewport);
    commandList.RSSetScissorRects(scissorRect);

}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Sample::OnActivated()
{
}

void Sample::OnDeactivated()
{
}

void Sample::OnSuspending()
{
}

void Sample::OnResuming()
{
    m_timer.ResetElapsedTime();
    m_gamePadButtons.Reset();
    m_keyboardButtons.Reset();
}

void Sample::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Sample::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();
}

// Properties
void Sample::GetDefaultSize(int& width, int& height) const
{
    width = 1920;
    height = 1080;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Sample::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    m_graphicsMemory = std::make_unique<GraphicsMemory>(device);

    // Create descriptor heaps.
    {
        m_SRVDescriptorHeap = std::make_unique<DescriptorHeap>(
            device,
            D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
            D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
            e_srvDescCount);

        m_fontDescriptorHeap = std::make_unique<DescriptorHeap>(
            device,
            D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
            D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
            e_fontDescCount);
    }

   
    CreateTextureResources();
   
    CreateUIResources();

    
}

void Sample::CreateTextureResources()
{
    auto device = m_deviceResources->GetD3DDevice();
        
    // Create root signatures with one sampler and one texture--one for nearest neighbor sampling,
    // and one for bilinear.
    {
        D3D12::DescriptorRange descRange( D3D12::DescriptorRangeType::ShaderResourceView, 1, 0 );

        D3D12::RootParameter rp = D3D12::RootParameter::AsDescriptorTable( 1, &descRange, D3D12::ShaderVisibility::Pixel );

        // Nearest neighbor sampling
        D3D12::StaticSamplerDesc samplerDesc = {};
        samplerDesc.Filter = D3D12::Filter::Anisotropic;
        samplerDesc.AddressU = D3D12::TextureAddressMode::Wrap;
        samplerDesc.AddressV = D3D12::TextureAddressMode::Wrap;
        samplerDesc.AddressW = D3D12::TextureAddressMode::Wrap;
        samplerDesc.MaxAnisotropy = 16;
        samplerDesc.ComparisonFunc = D3D12::ComparisonFunction::LessOrEqual;
        samplerDesc.BorderColor = D3D12::StaticBorderColor::OpaqueWhite;
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
        samplerDesc.ShaderVisibility = D3D12::ShaderVisibility::Pixel;

        D3D12::RootSignatureDesc rootSignatureDesc(1, &rp, 1, &samplerDesc,
            D3D12::RootSignatureFlags::AllowInputAssemblerInputLayout
            | D3D12::RootSignatureFlags::DenyDomainShaderRootAccess
            | D3D12::RootSignatureFlags::DenyGeometryShaderRootAccess
            | D3D12::RootSignatureFlags::DenyHullShaderRootAccess);

        //m_texRootSignatureNN = device.CreateRootSignature( 0, rootSignatureDesc );

        m_texRootSignatureLinear = device.CreateRootSignature( 0, rootSignatureDesc );
    }

    // Create the pipeline state for a basic textured quad render, which includes loading shaders.

    {
        auto vertexShaderBlob = DX::ReadData(L"VertexShader.cso");
        auto pixelShaderBlob = DX::ReadData(L"PixelShader.cso");

        static const D3D12::InputElementDesc s_inputElementDesc[2] =
        {
            { "SV_Position", 0, DXGI::Format::R32G32B32A32_FLOAT, 0, 0,  D3D12::InputClassification::PerVertexData,  0 },
            { "TEXCOORD",    0, DXGI::Format::R32G32_FLOAT,       0, 16, D3D12::InputClassification::PerVertexData,  0 },
        };

        // Describe and create the graphics pipeline state objects (PSO).
        D3D12::GraphicsPipelineStateDesc psoDesc = {};
        psoDesc.InputLayout = { s_inputElementDesc, _countof(s_inputElementDesc) };
        psoDesc.pRootSignature = m_texRootSignatureNN;
        psoDesc.VS = vertexShaderBlob;
        psoDesc.PS = pixelShaderBlob;
        
       
        
        psoDesc.DepthStencilState.DepthEnable = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.DSVFormat = m_deviceResources->GetDepthBufferFormat();
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12::PrimitiveTopologyType::Triangle;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = m_deviceResources->GetBackBufferFormat();
        psoDesc.SampleDesc.Count = 1;

        D3D12::BlendDesc blendDesc{};
        blendDesc.RenderTarget[0].BlendEnable = true;
        blendDesc.RenderTarget[0].BlendOp = D3D12::BlendOperation::Add;
        blendDesc.RenderTarget[0].SrcBlend = D3D12::Blend::SourceAlpha;
        blendDesc.RenderTarget[0].DestBlend = D3D12::Blend::InvertSource1Alpha;
        blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12::Blend::One;
        blendDesc.RenderTarget[0].DestBlendAlpha = D3D12::Blend::Zero;
        blendDesc.RenderTarget[0].LogicOpEnable = false;
        blendDesc.RenderTarget[0].BlendOpAlpha = D3D12::BlendOperation::Add;
        blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12::ColorWriteEnable::All;
        psoDesc.BlendState  = blendDesc;


        //m_texPipelineStateNN = device.CreateGraphicsPipelineState(psoDesc);

        psoDesc.pRootSignature = m_texRootSignatureLinear;
        m_texPipelineStateLinear = device.CreateGraphicsPipelineState(psoDesc);
    }

    // Create vertex buffer for full screen texture render.
    {
        static const Vertex s_vertexData[4] =
        {
            { { -1.f, -1.f, 1.f, 1.0f },{ 0.f, 1.f } },
            { { 1.f, -1.f, 1.f, 1.0f },{ 1.f, 1.f } },
            { { 1.f,  1.f, 1.f, 1.0f },{ 1.f, 0.f } },
            { { -1.f,  1.f, 1.f, 1.0f },{ 0.f, 0.f } },
        };

        // Note: using upload heaps to transfer static data like vert buffers is not 
        // recommended. Every time the GPU needs it, the upload heap will be marshalled 
        // over. Please read up on Default Heap usage. An upload heap is used here for 
        // code simplicity and because there are very few verts to actually transfer.
        m_vertexBuffer =  device.CreateCommittedResource(D3D12::HeapProperties(D3D12::HeapType::Upload),
                D3D12::HeapFlags::None,
                D3D12::ResourceDesc::Buffer(sizeof(s_vertexData)),
                D3D12::ResourceStates::GenericRead);

        // Copy the quad data to the vertex buffer.
        ;
        CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
        UINT8* pVertexDataBegin = reinterpret_cast< UINT8* >(m_vertexBuffer.Map(0, readRange));
        memcpy(pVertexDataBegin, s_vertexData, sizeof(s_vertexData));
        m_vertexBuffer.Unmap(0, nullptr);

        // Initialize the vertex buffer view.
        m_vertexBufferView.BufferLocation = m_vertexBuffer.GetGPUVirtualAddress();
        m_vertexBufferView.StrideInBytes = sizeof(Vertex);
        m_vertexBufferView.SizeInBytes = sizeof(s_vertexData);
    }

    // Create index buffer.
    {
        static const uint16_t s_indexData[6] =
        {
            3,1,0,
            2,1,3,
        };

        // See note above
        m_indexBuffer = device.CreateCommittedResource(D3D12::HeapProperties(D3D12::HeapType::Upload),
                D3D12::HeapFlags::None,
                D3D12::ResourceDesc::Buffer(sizeof(s_indexData)),
                D3D12::ResourceStates::GenericRead);

        // Copy the data to the index buffer.
        UINT8* pVertexDataBegin;
        CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
        pVertexDataBegin = reinterpret_cast< UINT8* >( m_indexBuffer.Map(0, readRange));
        memcpy(pVertexDataBegin, s_indexData, sizeof(s_indexData));
        m_indexBuffer.Unmap(0, nullptr);

        // Initialize the index buffer view.
        m_indexBufferView.BufferLocation = m_indexBuffer.GetGPUVirtualAddress();
        m_indexBufferView.Format = DXGI::Format::R16_UINT;
        m_indexBufferView.SizeInBytes = sizeof(s_indexData);
    }

#if USE_VIDEO
    // Create video player.
    {
        

        auto home = Harlinn::Common::Core::Environment::EnvironmentVariable( L"HCC_HOME" );
        auto mediaDir = IO::Path::Combine( home, L"Share\\media" );
        auto media = IO::Path::Combine( mediaDir, c_videoPath );

        if ( IO::File::Exist( media ) )
        {
            m_player = std::make_unique<MediaEnginePlayer>( );
            m_player->Initialize( m_deviceResources->GetDXGIFactory( ), device, DXGI::Format::B8G8R8A8_UNORM );
            m_player->SetSource( media.c_str() );
        }
        else
        {
            wchar_t buff[ MAX_PATH ];
            DX::FindMediaFile( buff, MAX_PATH, c_videoPath );

            m_player = std::make_unique<MediaEnginePlayer>( );
            m_player->Initialize( m_deviceResources->GetDXGIFactory( ), device, DXGI::Format::B8G8R8A8_UNORM );
            m_player->SetSource( buff );
        }
        while (!m_player->IsInfoReady())
        {
            SwitchToThread();
        }

        m_player->GetNativeVideoSize(m_origTextureWidth, m_origTextureHeight);
        m_player->SetLoop(true);

        // Create texture to receive video frames.
        D3D12::ResourceDesc desc(
            D3D12::ResourceDimension::Texture2D,
            0,
            m_origTextureWidth,
            m_origTextureHeight,
            1,
            1,
            DXGI::Format::B8G8R8A8_UNORM,
            1,
            0,
            D3D12::TextureLayout::Unknown,
            D3D12::ResourceFlags::AllowRenderTarget | D3D12::ResourceFlags::AllowSimultaneousAccess);

        D3D12::HeapProperties defaultHeapProperties( D3D12::HeapType::Default );

        m_videoTexture = device.CreateCommittedResource(
                defaultHeapProperties,
                D3D12::HeapFlags::Shared,
                desc,
                D3D12::ResourceStates::NonPixelShaderResource);

        m_sharedVideoTexture = device.CreateSharedHandle( m_videoTexture);

        CreateShaderResourceView(device.GetInterfacePointer<ID3D12Device>(), m_videoTexture.GetInterfacePointer<ID3D12Resource>( ), m_SRVDescriptorHeap->GetCpuHandle( e_descTexture ) );
    }
//#else
    // Create static texture.
    {
        const auto& commandList = m_deviceResources->GetCommandList();
        commandList.Reset(m_deviceResources->GetCommandAllocator(), nullptr);

        D3D12::Resource textureUploadHeap;
    
        D3D12::ResourceDesc txtDesc = {};
        txtDesc.MipLevels = txtDesc.DepthOrArraySize = 1;
        txtDesc.Format = DXGI::Format::B8G8R8A8_UNORM;
        txtDesc.SampleDesc.Count = 1;
        txtDesc.Dimension = D3D12::ResourceDimension::Texture2D;

        wchar_t buff[MAX_PATH];
        DX::FindMediaFile(buff, MAX_PATH, c_imagePath);

        UINT width, height;
        auto image = LoadBGRAImage(buff, width, height);
        txtDesc.Width =  width;
        txtDesc.Height =  height;

        //m_origTextureWidth = width;
        //m_origTextureHeight = height;

        m_texture = device.CreateCommittedResource(
                D3D12::HeapProperties(D3D12::HeapType::Default),
                D3D12::HeapFlags::None,
                txtDesc,
                D3D12::ResourceStates::CopyDest);

        const UINT64 uploadBufferSize = GetRequiredIntermediateSize(m_texture, 0, 1);

        // Create the GPU upload buffer.
        textureUploadHeap = device.CreateCommittedResource(
                D3D12::HeapProperties(D3D12::HeapType::Upload),
                D3D12::HeapFlags::None,
                D3D12::ResourceDesc::Buffer(uploadBufferSize),
                D3D12::ResourceStates::GenericRead);

        D3D12::SubResourceData textureData = {};
        textureData.pData = image.data();
        textureData.RowPitch = static_cast<LONG_PTR>(txtDesc.Width * sizeof(uint32_t));
        textureData.SlicePitch = image.size();

        UpdateSubResources(commandList, m_texture, textureUploadHeap, 0, 0, 1, &textureData);
        commandList.ResourceBarrier(m_texture, D3D12::ResourceStates::CopyDest, D3D12::ResourceStates::GenericRead);

        // Describe and create a SRV for the texture.
        D3D12::ShaderResourceViewDesc srvDesc = {};
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Format = txtDesc.Format;
        srvDesc.ViewDimension = D3D12::SRVDimension::Texture2D;
        srvDesc.Texture2D.MipLevels = 1;
        device.CreateShaderResourceView(m_texture, srvDesc, m_SRVDescriptorHeap->GetCpuHandle(e_outputTensor));
    
        commandList.Close();
        m_deviceResources->GetCommandQueue().ExecuteCommandLists(commandList);

        // Wait until assets have been uploaded to the GPU.
        m_deviceResources->WaitForGpu();
    }
#endif
}

void Sample::CreateUIResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    const int DefaultBatchSize = 4096 * 3;
    m_lineBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(device);
    m_lineBatch2 = std::make_unique<PrimitiveBatch<VertexPositionColor>>(device, DefaultBatchSize * 3, DefaultBatchSize);

    RenderTargetState rtState( static_cast<DXGI_FORMAT>( m_deviceResources->GetBackBufferFormat() ), static_cast< DXGI_FORMAT >( m_deviceResources->GetDepthBufferFormat() ));

    EffectPipelineStateDescription epd(&VertexPositionColor::InputLayout, CommonStates::AlphaBlend,
        CommonStates::DepthDefault, CommonStates::CullNone, rtState, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE);


    m_lineEffect = std::make_unique<BasicEffect>(device, EffectFlags::VertexColor, epd);

    CD3DX12_RASTERIZER_DESC rastDesc(D3D12_FILL_MODE_SOLID,
        D3D12_CULL_MODE_NONE, FALSE,
        D3D12_DEFAULT_DEPTH_BIAS, D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, TRUE,
        0, D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF);
    EffectPipelineStateDescription epd2(&VertexPositionColor::InputLayout, CommonStates::AlphaBlend,
        CommonStates::DepthDefault, rastDesc, rtState, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
    m_lineEffect2 = std::make_unique<BasicEffect>(device, EffectFlags::VertexColor, epd2);

    SpriteBatchPipelineStateDescription spd(rtState, &CommonStates::AlphaBlend);
    ResourceUploadBatch uploadBatch(device);
    uploadBatch.Begin();

    m_spriteBatch = std::make_unique<SpriteBatch>(device, uploadBatch, spd);
    //m_sprite = std::make_unique<SpriteBatch>(device, uploadBatch, spd);

    wchar_t strFilePath[MAX_PATH] = {};
    DX::FindMediaFile(strFilePath, MAX_PATH, L"SegoeUI_30.spritefont");
    m_labelFont = std::make_unique<SpriteFont>(device, uploadBatch,
        strFilePath,
        m_fontDescriptorHeap->GetCpuHandle(FontDescriptors::e_descLabelFont),
        m_fontDescriptorHeap->GetGpuHandle(FontDescriptors::e_descLabelFont));

    DX::FindMediaFile(strFilePath, MAX_PATH, L"SegoeUI_30_Bold.spritefont");
    m_labelFontBold = std::make_unique<SpriteFont>(device, uploadBatch,
        strFilePath,
        m_fontDescriptorHeap->GetCpuHandle(FontDescriptors::e_descLabelFontBold),
        m_fontDescriptorHeap->GetGpuHandle(FontDescriptors::e_descLabelFontBold));

    DX::FindMediaFile(strFilePath, MAX_PATH, L"SegoeUI_18.spritefont");
    m_legendFont = std::make_unique<SpriteFont>(device, uploadBatch,
        strFilePath,
        m_fontDescriptorHeap->GetCpuHandle(FontDescriptors::e_descLegendFont),
        m_fontDescriptorHeap->GetGpuHandle(FontDescriptors::e_descLegendFont));

    DX::FindMediaFile(strFilePath, MAX_PATH, L"XboxOneControllerLegendSmall.spritefont");
    m_ctrlFont = std::make_unique<SpriteFont>(device, uploadBatch,
        strFilePath,
        m_fontDescriptorHeap->GetCpuHandle(FontDescriptors::e_descCtrlFont),
        m_fontDescriptorHeap->GetGpuHandle(FontDescriptors::e_descCtrlFont));

    auto finish = uploadBatch.End(m_deviceResources->GetCommandQueue());
    finish.wait();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Sample::CreateWindowSizeDependentResources()
{
    auto viewport = m_deviceResources->GetScreenViewport();

    auto proj = DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter(0.f, static_cast<float>(viewport.Width),
        static_cast<float>(viewport.Height), 0.f, 0.f, 1.f);
    m_lineEffect->SetProjection(proj);
    m_lineEffect2->SetProjection(proj);

    m_spriteBatch->SetViewport(viewport);

}




void Sample::OnDeviceLost()
{
    
    m_lineEffect.reset();
    m_lineBatch.reset();
    m_lineBatch2.reset();
    m_spriteBatch.reset();
    m_labelFont.reset();
    m_labelFontBold.reset();
    m_legendFont.reset();
    m_ctrlFont.reset();
    m_fontDescriptorHeap.reset();

    m_player.reset();

    //m_texPipelineStateNN.ResetPtr();
    m_texPipelineStateLinear.ResetPtr();
    m_texRootSignatureNN.ResetPtr();
    m_texRootSignatureLinear.ResetPtr();
    m_tensorRenderPipelineState.ResetPtr();
    m_tensorRenderRootSignature.ResetPtr();
    m_texture.ResetPtr();
    m_videoTexture.ResetPtr();
    m_indexBuffer.ResetPtr();
    m_vertexBuffer.ResetPtr();

    m_SRVDescriptorHeap.reset();

    m_graphicsMemory.reset();
}

void Sample::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
