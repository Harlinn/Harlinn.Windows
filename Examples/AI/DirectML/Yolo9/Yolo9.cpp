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

#include "TensorExtents.h"
#include "TensorHelper.h"
#include "earcut.hpp"
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

    int colors[] = { 0xf0fafa, 0x3588d1, 0x4ad59b, 0x399283, 0x97f989, 0x57b230, 0xd8e9b2, 0xff1c5d, 0xf1bb99, 0xf7794f, 0x987d7b, 0xf4f961, 0x1dfee1, 0x9382e9, 0xc052e4, 0xf3c5fa, 0xd6709b, 0xfe16f4, 0x34f50e, 0xab7b05, 0xfbbd13 };
 
    std::vector<uint8_t> LoadBGRAImage(const wchar_t* filename, uint32_t& width, uint32_t& height)
    {
        width = 520;
        height = 520;
        WICPixelFormatGUID pixelFormat = GUID_WICPixelFormat32bppBGRA;

        uint32_t rowPitch = width * sizeof(uint32_t);
        uint32_t imageSize = rowPitch * height;

        std::vector<uint8_t> image;
        image.resize(size_t(imageSize));
        
        BYTE* p = (BYTE *) image.data();
        for (int i = 0; i < imageSize/4; i++)
        {
            p[0] = p[1] = p[2] = 0;
            p[2] = 0;
            p[3] = 0;
            p += 4;
        }

        return image;
    }

    // Returns true if any of the supplied floats are inf or NaN, false otherwise.
    static bool IsInfOrNan( float arg )
    {
        if ( std::isinf( arg ) || std::isnan( arg ) )
        {
            return true;
        }
        return false;
    }
    template<typename ... Args>
    static bool IsInfOrNan( float arg, Args&& ... args )
    {
        if (std::isinf( arg ) || std::isnan( arg ))
        {
            return true;
        }

        return IsInfOrNan( args ... );
    }

    // Given two axis-aligned bounding boxes, computes the area of intersection divided by the area of the union of
    // the two boxes.
    static float ComputeIntersectionOverUnion(const Prediction& a, const Prediction& b)
    {
        float aArea = (a.xmax - a.xmin) * (a.ymax - a.ymin);
        float bArea = (b.xmax - b.xmin) * (b.ymax - b.ymin);

        // Determine the bounds of the intersection rectangle
        float interXMin = std::max(a.xmin, b.xmin);
        float interYMin = std::max(a.ymin, b.ymin);
        float interXMax = std::min(a.xmax, b.xmax);
        float interYMax = std::min(a.ymax, b.ymax);

        float intersectionArea = std::max(0.0f, interXMax - interXMin) * std::max(0.0f, interYMax - interYMin);
        float unionArea = aArea + bArea - intersectionArea;

        return (intersectionArea / unionArea);
    }

    // Given a set of predictions, applies the non-maximal suppression (NMS) algorithm to select the "best" of
    // multiple overlapping predictions.
    static std::vector<Prediction> ApplyNonMaximalSuppression(std::span<const Prediction> allPredictions, float threshold)
    {
        std::unordered_map<uint32_t, std::vector<Prediction>> predsByClass;
        for (const auto& pred : allPredictions)
        {
            predsByClass[pred.predictedClass].push_back(pred);
        }

        std::vector<Prediction> selected;

        for (auto& kvp : predsByClass)
        {
            std::vector<Prediction>& proposals = kvp.second;

            while (!proposals.empty())
            {
                // Find the proposal with the highest score
                auto max_iter = std::max_element(proposals.begin(), proposals.end(), [](const Prediction& lhs, const Prediction& rhs) 
                    {
                        return lhs.score < rhs.score;
                    });

                // Move it into the "selected" array
                selected.push_back(*max_iter);
                proposals.erase(max_iter);

                // Compare this selected prediction with all the remaining propsals. Compute their IOU and remove any
                // that are greater than the threshold.
                for (auto it = proposals.begin(); it != proposals.end(); it)
                {
                    float iou = ComputeIntersectionOverUnion(selected.back(), *it);

                    if (iou > threshold)
                    {
                        // Remove this element
                        it = proposals.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }

        return selected;
    }

    enum class ChannelOrder
    {
        RGB,
        BGR,
        M
    };

    template <typename T>
    void CopyTensorToPixelsByte(
        uint8_t * src,
        uint8_t* dst,
        uint32_t height,
        uint32_t width,
        uint32_t channels)
    {
        std::span<const T> srcT(reinterpret_cast<const T*>(src), height*width / sizeof(T));

        for (size_t pixelIndex = 0; pixelIndex < height * width; pixelIndex++)
        {
            BYTE m = (BYTE)srcT[pixelIndex + 0 * height * width];
            if (m)
                volatile int a = 0;
            dst[pixelIndex * channels + 0] = m;
           
        }
    }


    // Converts an NCHW tensor buffer (batch size 1) to a pixel buffer.
// Source: buffer of RGB planes (CHW) using float32/float16 components.
// Target: buffer of RGB pixels (HWC) using uint8 components.
    template <typename T>
    void CopyTensorToPixels( const uint8_t * src, uint8_t * dst, uint32_t height, uint32_t width, uint32_t channels)
    {
        std::span<const T> srcT(reinterpret_cast<const T*>(src), (height*width) / sizeof(T));

        for (size_t pixelIndex = 0; pixelIndex < height * width; pixelIndex++)
        {
            BYTE r = static_cast<BYTE>(std::max(0.0f, std::min(1.0f, (float)srcT[pixelIndex + 0 * height * width])) * 255.0f);
            BYTE g = static_cast<BYTE>(std::max(0.0f, std::min(1.0f, (float)srcT[pixelIndex + 1 * height * width])) * 255.0f);
            BYTE b = static_cast<BYTE>(std::max(0.0f, std::min(1.0f, (float)srcT[pixelIndex + 2 * height * width])) * 255.0f);

            dst[pixelIndex * channels + 0] = b;
            dst[pixelIndex * channels + 1] = g;
            dst[pixelIndex * channels + 2] = r;
            dst[pixelIndex * channels + 3] = 128;
        }
    }

    inline unsigned char* pixel(unsigned char* Img, int i, int j, int width, int height, int bpp)
    {
        return (Img + ((i * width + j) * bpp));
    }


    // Converts a pixel buffer to an NCHW tensor (batch size 1).
    // Source: buffer of RGB pixels (HWC) using uint8 components.
    // Target: buffer of RGB planes (CHW) using float32/float16 components.
    template <typename T>
    void CopyPixelsToTensor(
        std::byte*  src,
        uint32_t srcWidth, uint32_t srcHeight, uint32_t rowPitch,
        std::span<std::byte> dst,
        uint32_t height,
        uint32_t width,
        uint32_t channels)
    {
        uint32_t srcChannels = rowPitch / srcWidth;
        uint32_t rowWidth = rowPitch / srcChannels;
        std::span<T> dstT(reinterpret_cast<T*>(dst.data()), dst.size_bytes() / sizeof(T));

        if (srcWidth != width || srcHeight != height)
        {
            unsigned char* Img = (uint8_t*)src;
            float ScaledWidthRatio = srcWidth / (float)width;
            float ScaledHeightRatio = srcHeight / (float)height;
            uint32_t pixelIndex = 0;

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    float mappedheight = i * ScaledHeightRatio;  //rf
                    float mappedwidth = j * ScaledWidthRatio;   //cf
                    int   OriginalPosHeight = (int)mappedheight;         //ro
                    int   OriginalPosWidth =(int) mappedwidth;          //co
                    float deltaheight = mappedheight - OriginalPosHeight; //delta r
                    float deltawidth = mappedwidth - OriginalPosWidth;   //delta c

                    unsigned char* temp1 = pixel(Img, OriginalPosHeight, OriginalPosWidth, rowWidth, srcHeight, srcChannels);
                    unsigned char* temp2 = pixel(Img, ((OriginalPosHeight + 1) >= height ? OriginalPosHeight : OriginalPosHeight + 1),
                        OriginalPosWidth, rowWidth, srcHeight, srcChannels);
                    unsigned char* temp3 = pixel(Img, OriginalPosHeight, OriginalPosWidth + 1, rowWidth, srcHeight, srcChannels);
                    unsigned char* temp4 = pixel(Img, ((OriginalPosHeight + 1) >= srcHeight ? OriginalPosHeight : OriginalPosHeight + 1),
                        (OriginalPosWidth + 1) >= rowWidth ? OriginalPosWidth : (OriginalPosWidth + 1), rowWidth, srcHeight, srcChannels);

                    float b =
                        ( *(temp1 + 0) * (1 - deltaheight) * (1 - deltawidth) 
                        + *(temp2 + 0) * (deltaheight) * (1 - deltawidth) 
                        + *(temp3 + 0) * (1 - deltaheight) * (deltawidth) 
                        + *(temp4 + 0) * (deltaheight) * (deltawidth)) / 255.0f;

                    float g =
                        ( *(temp1 + 1) * (1 - deltaheight) * (1 - deltawidth) 
                        + *(temp2 + 1) * (deltaheight) * (1 - deltawidth) 
                        + *(temp3 + 1) * (1 - deltaheight) * (deltawidth) 
                        + *(temp4 + 1) * (deltaheight) * (deltawidth)) / 255.0f;

                    float r =
                        (*(temp1 + 2) * (1 - deltaheight) * (1 - deltawidth) 
                        + *(temp2 + 2) * (deltaheight) * (1 - deltawidth) 
                        + *(temp3 + 2) * (1 - deltaheight) * (deltawidth) 
                        + *(temp4 + 2) * (deltaheight) * (deltawidth)) / 255.0f;


                    dstT[pixelIndex + 0 * height * width] = r;
                    dstT[pixelIndex + 1 * height * width] = g;
                    dstT[pixelIndex + 2 * height * width] = b;
                    pixelIndex++;
                }
            }
        }
        else
        {
            size_t pixelIndex = 0;
            for (size_t line = 0; line < height; line++)
            {
                auto _src = src + line * rowPitch;
                for (size_t x = 0; x < width; x++)
                {
                    float b = static_cast<float>(_src[x * srcChannels + 0]) / 255.0f;
                    float g = static_cast<float>(_src[x * srcChannels + 1]) / 255.0f;
                    float r = static_cast<float>(_src[x * srcChannels + 2]) / 255.0f;

                    dstT[pixelIndex + 0 * height * width] = r;
                    dstT[pixelIndex + 1 * height * width] = g;
                    dstT[pixelIndex + 2 * height * width] = b;

                    pixelIndex++;
                }
            }
        }
    }


}


bool Sample::CopySharedVideoTextureTensor(std::vector<std::byte> & inputBuffer, Model_t * model)
{

    // Record start
    auto start = std::chrono::high_resolution_clock::now();

    const auto& device = m_player->GetDevice( );

    D3D11::Texture2D mediaTexture = device.OpenSharedResource<D3D11::Texture2D>( m_sharedVideoTexture );

    if ( mediaTexture )
    {
        // First verify that we can map the texture
        D3D11_TEXTURE2D_DESC desc;
        mediaTexture.GetDesc(&desc);

        // translate texture format to WIC format. We support only BGRA and ARGB.
        GUID wicFormatGuid;
        switch (desc.Format) 
        {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            wicFormatGuid = GUID_WICPixelFormat32bppRGBA;
            break;
        case DXGI_FORMAT_B8G8R8A8_UNORM:
            wicFormatGuid = GUID_WICPixelFormat32bppBGRA;
            break;
        default:
            throw std::exception("Unsupported DXGI_FORMAT: %d. Only RGBA and BGRA are supported.");
        }

        // Get the device context
        
        D3D11::DeviceContext d3dContext = device.GetImmediateContext();

        // map the texture
        D3D11::Texture2D mappedTexture;
        D3D11_MAPPED_SUBRESOURCE mapInfo{};
        
        HRESULT hr = d3dContext.Map<true>( mediaTexture,
                0,  // Subresource
                D3D11_MAP_READ,
                0,  // MapFlags
                &mapInfo );

        if (FAILED(hr)) 
        {
            // If we failed to map the texture, copy it to a staging resource
            if (hr == E_INVALIDARG) 
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

                D3D11::Texture2D stagingTexture = device.CreateTexture2D(&desc2);

                // copy the texture to a staging resource
                d3dContext.CopyResource(stagingTexture, mediaTexture);

                // now, map the staging resource
                d3dContext.Map( stagingTexture, 0, D3D11_MAP_READ, 0, &mapInfo);
                mappedTexture = std::move(stagingTexture);
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
        auto unmapResource = Finally([&] 
            {
            d3dContext.Unmap(mappedTexture, 0);
            });

       
      
        const size_t inputChannels = model->m_inputShape[model->m_inputShape.size() - 3];
        const size_t inputHeight = model->m_inputShape[model->m_inputShape.size() - 2];
        const size_t inputWidth = model->m_inputShape[model->m_inputShape.size() - 1];

        if (desc.Width != inputWidth || desc.Height != inputHeight)
        {
            D2D1_FACTORY_OPTIONS options = {};
            if (m_d2d1_factory == nullptr)
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
            if (m_d2dContext)
            {
                DXGI::Surface surface = mediaTexture.As<DXGI::Surface>( );

                auto bitmap = m_d2dContext.CreateBitmapFromDxgiSurface( surface );

                auto scaleEffect = m_d2dContext.CreateEffect( CLSID_D2D1Scale );

                scaleEffect.SetInput(0, bitmap );


                D2D1_SCALE_INTERPOLATION_MODE interpolationMode = D2D1_SCALE_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC;
                //D2D1_SCALE_INTERPOLATION_MODE interpolationMode = D2D1_SCALE_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
                scaleEffect.SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F((float)inputWidth / (float)desc.Width, (float)inputHeight / (float)desc.Height));
                scaleEffect.SetValue(D2D1_SCALE_PROP_INTERPOLATION_MODE, reinterpret_cast<const BYTE*>(&interpolationMode), sizeof(D2D1_SCALE_INTERPOLATION_MODE)); // Set the interpolation mode.

                auto image_out = scaleEffect.GetOutput( );

                D3D11_TEXTURE2D_DESC texDesc;
                texDesc.Width = static_cast<UINT>(inputWidth);
                texDesc.Height = static_cast<UINT>(inputHeight);
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
                m_d2dContext.BeginDraw();

                auto identityMat = D2D1::Matrix3x2F::Identity();

                // Clear out any existing transform before drawing.
                m_d2dContext.SetTransform(identityMat);
                D2D1_POINT_2F targetOffset = { 0, 0 };
                m_d2dContext.DrawImage(image_out, targetOffset);
                D2D1_TAG tag1;
                D2D1_TAG tag2;
                m_d2dContext.EndDraw(&tag1, &tag2);
                m_d2dContext.SetTarget(nullptr);


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
                d3dContext.CopyResource(stagingTexture, drawTexture);

                // now, map the staging resource
                d3dContext.Map( stagingTexture, 0, D3D11_MAP_READ, 0, &mapInfo);

                mappedTexture = std::move(stagingTexture);
                mappedTexture.GetDesc(&desc);

            }

        }


        switch (model->m_inputDataType)
        {
        case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT:
            CopyPixelsToTensor<float>((std::byte*)mapInfo.pData, desc.Width, desc.Height, mapInfo.RowPitch, inputBuffer, inputHeight, inputWidth, inputChannels);
            break;

        case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16:
            CopyPixelsToTensor<half_float::half>((std::byte*)mapInfo.pData, desc.Width, desc.Height, mapInfo.RowPitch, inputBuffer, inputHeight, inputWidth, inputChannels);
            break;

        default:
            throw std::invalid_argument("Unsupported data type");
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        m_copypixels_tensor_duration += (end - start);

        return true;
    }
    return false;
}



void Sample::GetMask(const std::byte* outputData, std::vector<int64_t>& shape, Model_t* model, ONNXTensorElementDataType outputDataType)
{
    if (shape.size() != 3)
        return;

    const uint32_t outputChannels = 1;
    const uint32_t outputHeight = shape[shape.size() - 2];
    const uint32_t outputWidth = shape[shape.size() - 1];
    uint32_t outputElementSize = 1;
    auto co = ChannelOrder::RGB;
    switch (outputDataType)
    {
        case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT:
            outputElementSize = sizeof(float);
            break;

        case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16:
            outputElementSize = sizeof(uint16_t);
            break;
        case ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8:
        case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8:
            outputElementSize = sizeof(uint8_t);
            co = ChannelOrder::M;
            break;
    }

    // convert mask to BGRA data
    if (m_mask.size() != outputWidth * outputHeight * 4)
        m_mask.resize(outputWidth * outputHeight * 4);

    m_mask_ready = true;
    m_mask_width = outputWidth;
    m_mask_height = outputHeight;

    int channels = 4;
    for (size_t pixelIndex = 0; pixelIndex < outputHeight * outputWidth; pixelIndex++)
    {
        BYTE m = (BYTE)outputData[pixelIndex + 0 * outputWidth * outputHeight];
        if (m)
            volatile int a = 0;
        m = m % sizeof(colors);

        m_mask[pixelIndex * channels + 0] = (uint8_t) ((colors[m] & 0xff0000) >> 16);
        m_mask[pixelIndex * channels + 1] = (uint8_t) ((colors[m] & 0xff00) >> 8);
        m_mask[pixelIndex * channels + 2] = (uint8_t) (colors[m] & 0xff);
        m_mask[pixelIndex * channels + 3] = (uint8_t)0x80;
    }
}


void Sample::GetImage(const std::byte* outputData, std::vector<int64_t>& shape, Model_t* model, ONNXTensorElementDataType outputDataType)
{
    if (shape.size() != 4)
        return;

    const uint32_t outputChannels = shape[shape.size() - 3];
    const uint32_t outputHeight = shape[shape.size() - 2];
    const uint32_t outputWidth = shape[shape.size() - 1];
    uint32_t outputElementSize = outputDataType == ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT ? sizeof(float) : sizeof(uint16_t);

    auto co = ChannelOrder::RGB;
    switch (outputDataType)
    {
    case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT:
        outputElementSize = sizeof(float);
        break;

    case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16:
        outputElementSize = sizeof(uint16_t);
        break;
    case ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8:
    case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8:
        outputElementSize = sizeof(uint8_t);
        co = ChannelOrder::M;
        break;
    }
    int channels = 4;
    // convert mask to BGRA data
    if (m_mask.size() != outputWidth * outputHeight * channels)
        m_mask.resize(outputWidth * outputHeight * channels);

    m_mask_ready = true;
    m_mask_width = outputWidth;
    m_mask_height = outputHeight;

    switch (outputDataType)
    {
    case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT:
        CopyTensorToPixels<float>((uint8_t*)outputData, m_mask.data(), outputHeight, outputWidth, channels);
        break;

    case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16:
        CopyTensorToPixels<half_float::half>((uint8_t*)outputData, m_mask.data(), outputHeight, outputWidth, channels);
        break;

    case ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8:
    case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8:
        CopyTensorToPixelsByte<std::byte>((uint8_t*)outputData, m_mask.data(), outputHeight, outputWidth, channels);
        break;

    default:
        throw std::invalid_argument("Unsupported data type");
    }

}


void Sample::GetFaces(std::vector<const std::byte*>& outputData, std::vector<std::vector<int64_t>>& shapes, Model_t* model)
{
    if (outputData.size() != 2)
        return;


    Vec3<float> value1((float*)outputData[0], shapes[0][0], shapes[0][1], shapes[0][2]);
    Vec3<float> value2((float*)outputData[1], shapes[1][0], shapes[1][1], shapes[1][2]);
 
    // Scale the boxes to be relative to the original image size
    auto viewport = m_deviceResources->GetScreenViewport();
    float xScale = (float)viewport.Width;
    float yScale = (float)viewport.Height;

    const float x_scale = (float)model->m_inputWidth;
    const float y_scale = (float)model->m_inputHeight;
    const float h_scale = (float)model->m_inputWidth;
    const float w_scale = (float)model->m_inputHeight;

    Anchors * _anchors =  &m_anchors[0];
    if (value1.y != _anchors->size())
        _anchors = &m_anchors[1];
    if (value1.y != _anchors->size())
    {
        MessageBox(0, L"anchors size error", L"Error", MB_OK);
        ExitProcess(1);
    }
    const Anchors& anchors = *_anchors;
    for (Int64 i = 0; i < value1.z; ++i)
    {
        for (Int64 j = 0; j < value1.y;++j)
        {
            auto ptr2 = value2[i][j];
            if (ptr2[0] < threshold) continue;

            auto ptr = value1[i][j];

            Detection result;
            result.x = ptr[0];
            result.y = ptr[1];
            result.w = ptr[2];
            result.h = ptr[3];
            result.index = -1; // face, no label
            result.confidence = (float)ptr2[0];

            result.x = result.x / x_scale * anchors[j].w + anchors[j].x_center;
            result.y = result.y / y_scale * anchors[j].h + anchors[j].y_center;

            result.h = result.h / h_scale * anchors[j].h;
            result.w = result.w / w_scale * anchors[j].w;

            // We need to do some postprocessing on the raw values before we return them

            // Convert x,y,w,h to xmin,ymin,xmax,ymax
            
            float xmin = result.x - result.w / 2;
            float ymin = result.y - result.h / 2;
            float xmax = result.x + result.w / 2;
            float ymax = result.y + result.h / 2;

            xmin *= xScale;
            ymin *= yScale;
            xmax *= xScale;
            ymax *= yScale;

            // Clip values out of range
            xmin = std::clamp(xmin, 0.0f, (float)viewport.Width);
            ymin = std::clamp(ymin, 0.0f, (float)viewport.Height);
            xmax = std::clamp(xmax, 0.0f, (float)viewport.Width);
            ymax = std::clamp(ymax, 0.0f, (float)viewport.Height);

            // Discard invalid boxes
            if (xmax <= xmin || ymax <= ymin || IsInfOrNan( xmin, ymin, xmax, ymax ))
            {
                continue;
            }

            Prediction pred = {};
            pred.xmin = xmin;
            pred.ymin = ymin;
            pred.xmax = xmax;
            pred.ymax = ymax;
            pred.score = result.confidence;
            pred.predictedClass = result.index;

            for (int i = 0; i < 6; i++)
            {
                float keypoint_x = ptr[4 + i * 2];
                float keypoint_y = ptr[5 + i * 2];

                float x = keypoint_x / x_scale * anchors[j].w + anchors[j].x_center;
                float y = keypoint_y / y_scale * anchors[j].h + anchors[j].y_center;
                x *= xScale;
                y *= yScale;
                pred.m_keypoints.push_back(std::pair<float, float>(x, y));
            }

            m_preds.emplace_back(pred);
        }
    }
    // Apply NMS to select the best boxes
    m_preds = ApplyNonMaximalSuppression(m_preds, YoloV4Constants::c_nmsThreshold);
}

void Sample::GetPredictions2(std::vector<const std::byte*>& outputData, std::vector<std::vector<int64_t>>& shapes, const std::vector<std::string>& output_names, Model_t* model)
{
    if (outputData.size() != 2)
        return;
    // get outpunt indices
    int output0_i = 0;
    int output1_i = 1;
   
    int i = 0;
    for (const auto& name : output_names)
    {
        if (name == "output0")
            output0_i = i;
        else if (name == "output0")
            output0_i = i;
        i++;
    }
    if (output0_i == -1 || output1_i == -1)
        return;

    Vec3<float> value1((float*)outputData[output0_i], shapes[output0_i][0], shapes[output0_i][1], shapes[output0_i][2]);
    Vec4<float> value2((float*)outputData[output1_i], shapes[output1_i][0], shapes[output1_i][1], shapes[output1_i][2], shapes[output1_i][3]);
    std::vector<float> out;
    out.resize(value1.x * value1.y);


    // Scale the boxes to be relative to the original image size
    auto viewport = m_deviceResources->GetScreenViewport();
    float xScale = (float)viewport.Width / model->m_inputWidth;
    float yScale = (float)viewport.Height / model->m_inputHeight;


    std::vector<int> class_ids;
    std::vector<float> accus;
    std::vector<Detection> boxes;

    for (Int64 i = 0; i < value1.z; ++i)
    {
        for (Int64 j = 0; j < value1.x; ++j)
        {
            int classes = value1.y - 32 - 4;
            float max_confidence = 0.0f;
            int max_confidence_class = -1;
            if (classes >  1)
            {
                //auto ptr = value1[i][j];
                max_confidence = 0.0f;
                max_confidence_class = -1;

                for (int c = 4; c < classes + 4; c++)
                {
                    float conf = value1[i][c][j];
                    if (conf > max_confidence)
                    {
                        max_confidence = conf;
                        max_confidence_class = c - 4;
                    }
                }
            }
            else if (classes == 1)
            {
                max_confidence = value1[i][4][j];
                max_confidence_class = 0;
            }
          

            if (max_confidence < threshold) continue;

            Detection result;
            result.x = value1[i][0][j];
            result.y = value1[i][1][j];
            result.w = value1[i][2][j];
            result.h = value1[i][3][j];
            result.index = max_confidence_class;
            result.confidence = max_confidence;

            // We need to do some postprocessing on the raw values before we return them

            // Convert x,y,w,h to xmin,ymin,xmax,ymax
            float xmin = result.x - result.w / 2.0f;
            float ymin = result.y - result.h / 2.0f;
            float xmax = result.x + result.w / 2.0f;
            float ymax = result.y + result.h / 2.0f;

            xmin *= xScale;
            ymin *= yScale;
            xmax *= xScale;
            ymax *= yScale;

            // Clip values out of range
            xmin = std::clamp(xmin, 0.0f, (float)viewport.Width);
            ymin = std::clamp(ymin, 0.0f, (float)viewport.Height);
            xmax = std::clamp(xmax, 0.0f, (float)viewport.Width);
            ymax = std::clamp(ymax, 0.0f, (float)viewport.Height);

            // Discard invalid boxes
            if (xmax <= xmin || ymax <= ymin || IsInfOrNan( xmin, ymin, xmax, ymax ))
            {
                continue;
            }

            Prediction pred = {};
            pred.xmin = xmin;
            pred.ymin = ymin;
            pred.xmax = xmax;
            pred.ymax = ymax;
            pred.score = result.confidence;
            pred.predictedClass = result.index;
            pred.i = i;
            pred.j = j;

            m_preds.push_back(pred);

            accus.push_back(result.confidence);
            class_ids.push_back(result.index);

        }
    }
    // Apply NMS to select the best boxes
    m_preds = ApplyNonMaximalSuppression(m_preds, YoloV4Constants::c_nmsThreshold);

   // return;
    // convert mask to BGRA data
    if (m_mask.size() != value2.y * value2.x * 4)
        m_mask.resize(value2.y * value2.x * 4);
    std::fill(m_mask.begin(), m_mask.end(), 0);
    m_mask_ready = true;
    m_mask_width = value2.y;
    m_mask_height = value2.x;
    int channels = 4;

    if (m_pred_mask.size() != value2.y * value2.x)
        m_pred_mask.resize(value2.y * value2.x);


    xScale = (float)viewport.Width / value2.x;
    yScale = (float)viewport.Height / value2.y;

    int start_mask_index = value1.y - 32;
   

    for (auto& pred : m_preds)
    {
        std::fill(m_pred_mask.begin(), m_pred_mask.end(), 0);

        pred.mask_weights.resize(value2.z);
        for (Int64 k = start_mask_index; k < value1.y; ++k)
            pred.mask_weights[k- start_mask_index] = value1[pred.i][k][pred.j];

        for (Int64 i = 0; i < value2.w; ++i)
        {
            int pixelIndex = 0;
            for (Int64 k = 0; k < value2.y; ++k)
            {

                for (Int64 l = 0; l < value2.x; ++l)
                {

                    // inside bbox?
                    // 
                    float y = k * yScale;
                    float x = l * xScale;

                    if (x >= pred.xmin && x <= pred.xmax && y >= pred.ymin && y <= pred.ymax)
                    {
                        // for classes
                        float sum = 0.0f;
                        for (Int64 j = 0; j < value2.z; ++j)
                        {
                            auto v = value2[i][j][k][l];
                            sum += pred.mask_weights[j] * v;
                        }


                        sum = sum / (1.0f + exp(-sum));
                        BYTE m = 0;
                        if (sum > 0.001)
                        {

                            m_pred_mask[k * value2.x + l] = 1;
                            
                            m = pred.predictedClass % 20;
                            m_mask[pixelIndex * channels + 0] = (uint8_t)(colors[m] & 0xff);
                            m_mask[pixelIndex * channels + 1] = (uint8_t)((colors[m] & 0xff00) >> 8);
                            m_mask[pixelIndex * channels + 2] = (uint8_t)((colors[m] & 0xff0000) >> 16);
                            m_mask[pixelIndex * channels + 3] = (uint8_t)0x80;
                        }

                    }
                    pixelIndex++;
                }
            }
        }
        // get contour from m_pred_mask
        depixelator::Bitmap bmap;
        bmap.data = m_pred_mask.data();
        bmap.height = m_mask_height;
        bmap.width = m_mask_width;
        bmap.stride = m_mask_width;
        pred.m_polylines = depixelator::findContours(bmap);
        //pred.m_polylines = depixelator::simplify(pred.m_polylines, 0.1f);
        //pred.m_polylines = depixelator::simplifyRDP(pred.m_polylines, 0.1f);
        pred.m_polylines = depixelator::traceSlopes(pred.m_polylines);
        pred.m_polylines = depixelator::smoothen(pred.m_polylines, 0.1f, 4);

        for (auto& polyline : pred.m_polylines)
        {
            for (auto& p : polyline)
            {
                p.x *= xScale, p.y *= yScale;
            }
        }
    }
}


void Sample::GetPredictions(std::vector<const std::byte*>& outputData, std::vector<std::vector<int64_t>>& shapes, const std::vector<std::string>& output_names, Model_t* model)
{
    // get outpunt indices
    int boxes_i = -0;
    int scores_i = -1;
    int class_idx_i = -1;
    int masks_i = -1;
    int protos_i = -1;
    int i = 0;
    for (auto name : output_names)
    {
        if (name == "boxes")
            boxes_i = i;
        else if (name == "scores")
            scores_i = i;
        else if (name == "class_idx")
            class_idx_i = i;
        else if (name == "masks")
            masks_i = i;
        else if (name == "protos")
            protos_i = i;
        i++;
    }
    if (boxes_i == -1 || scores_i == -1 || class_idx_i == -1)
        return;
    if (outputData.size() >= 5)
    {
        if (masks_i == -1 || protos_i == -1)
            return;
    }


    Vec3<float> value1((float*)outputData[boxes_i], shapes[boxes_i][0], shapes[boxes_i][1], shapes[boxes_i][2]);
    Vec2<float> value2((float*)outputData[scores_i], shapes[scores_i][0], shapes[scores_i][1]);
    Vec2<float> value3((float*)outputData[class_idx_i], shapes[class_idx_i][0], shapes[class_idx_i][1]);
 
    // Scale the boxes to be relative to the original image size
    auto viewport = m_deviceResources->GetScreenViewport();
    float xScale = (float)viewport.Width / model->m_inputWidth;
    float yScale = (float)viewport.Height / model->m_inputHeight;

    for (Int64 i = 0; i < value1.z; ++i)
    {
        for (Int64 j = 0; j < value1.y; ++j)
        {
            auto ptr2 = value2[i][j];
            if (ptr2 < threshold) continue;

            auto ptr = value1[i][j];
           
            Detection result;
            result.x = ptr[0];
            result.y = ptr[1];
            result.w = ptr[2];
            result.h = ptr[3];
            result.index = (Int64)value3[i][j];
            result.confidence = (float)ptr2;

            // We need to do some postprocessing on the raw values before we return them

            // Convert x,y,w,h to xmin,ymin,xmax,ymax
            float xmin = result.x;
            float ymin = result.y;
            float xmax = result.w;
            float ymax = result.h;
            // Convert x,y,w,h to xmin,ymin,xmax,ymax
             //xmin = result.x - result.w / 2;
             //ymin = result.y - result.h / 2;
             //xmax = result.x + result.w / 2;
             //ymax = result.y + result.h / 2;


            xmin *= xScale;
            ymin *= yScale;
            xmax *= xScale;
            ymax *= yScale;

            // Clip values out of range
            xmin = std::clamp(xmin, 0.0f, (float)viewport.Width);
            ymin = std::clamp(ymin, 0.0f, (float)viewport.Height);
            xmax = std::clamp(xmax, 0.0f, (float)viewport.Width);
            ymax = std::clamp(ymax, 0.0f, (float)viewport.Height);

            // Discard invalid boxes
            if (xmax <= xmin || ymax <= ymin || IsInfOrNan( xmin, ymin, xmax, ymax ))
            {
                continue;
            }

            Prediction pred = {};
            pred.xmin = xmin;
            pred.ymin = ymin;
            pred.xmax = xmax;
            pred.ymax = ymax;
            pred.score = result.confidence;
            pred.predictedClass = result.index;
            pred.i = i;
            pred.j = j;
          
            m_preds.push_back(pred);
        }
    }
    // Apply NMS to select the best boxes
    m_preds = ApplyNonMaximalSuppression(m_preds, YoloV4Constants::c_nmsThreshold);

    if (outputData.size() >= 5)
    {

        Vec3<float> value4((float*)outputData[masks_i], shapes[masks_i][0], shapes[masks_i][1], shapes[masks_i][2]);
        Vec4<float> value5((float*)outputData[protos_i], shapes[protos_i][0], shapes[protos_i][1], shapes[protos_i][2], shapes[protos_i][3]);

        // convert mask to BGRA data
        if (m_mask.size() != value5.y * value5.x * 4)
            m_mask.resize(value5.y * value5.x * 4);
        std::fill(m_mask.begin(), m_mask.end(), 0);
        m_mask_ready = false;
        m_mask_width = value5.y;
        m_mask_height = value5.x;
        int channels = 4;
        if (m_pred_mask.size() != value5.y * value5.x)
            m_pred_mask.resize(value5.y * value5.x);

        float xScale = (float)viewport.Width / value5.x;
        float yScale = (float)viewport.Height / value5.y;

        for (auto& pred : m_preds)
        {
            std::fill(m_pred_mask.begin(), m_pred_mask.end(), 0);

            pred.mask_weights.resize(value4.x);
            for (Int64 k = 0; k < value4.x; ++k)
                pred.mask_weights[k] = value4[pred.i][pred.j][k];

            for (Int64 i = 0; i < value5.w; ++i)
            {
                int pixelIndex = 0;
                for (Int64 k = 0; k < value5.y; ++k)
                {
                    for (Int64 l = 0; l < value5.x; ++l)
                    {
                        // inside bbox?
                        // 
                        float y = k * yScale;
                        float x = l * xScale;

                        if (x >= pred.xmin && x <= pred.xmax && y >= pred.ymin && y <= pred.ymax)
                        {
                            // for classes
                            float sum = 0.0f;
                            for (Int64 j = 0; j < value5.z; ++j)
                            {
                                auto v = value5[i][j][k][l];
                                sum += pred.mask_weights[j] * v;
                            }

                            sum = sum / (1.0f + exp(-sum));
                            BYTE m = 0;
                            if (sum > 0.2)
                            {
                                m_pred_mask[k * value5.x + l] = 1;

                                m = pred.predictedClass % 20;
                                m_mask[pixelIndex * channels + 0] = (uint8_t)(colors[m] & 0xff); 
                                m_mask[pixelIndex * channels + 1] = (uint8_t)((colors[m] & 0xff00) >> 8);
                                m_mask[pixelIndex * channels + 2] = (uint8_t)((colors[m] & 0xff0000) >> 16);
                                m_mask[pixelIndex * channels + 3] = (uint8_t)0x80;
                            }
                           
                        }
                        pixelIndex++;
                    }
                }
            }

            // get contour from m_pred_mask
            depixelator::Bitmap bmap;
            bmap.data = m_pred_mask.data();
            bmap.height = m_mask_height;
            bmap.width = m_mask_width;
            bmap.stride = m_mask_width;
            pred.m_polylines = depixelator::findContours(bmap);
            //pred.m_polylines = depixelator::simplify(pred.m_polylines, 0.1f);
            //pred.m_polylines = depixelator::simplifyRDP(pred.m_polylines, 0.1f);
            pred.m_polylines = depixelator::traceSlopes(pred.m_polylines);
            pred.m_polylines = depixelator::smoothen(pred.m_polylines, 0.1f, 4);
           
            for (auto& polyline : pred.m_polylines)
            {
                for (auto& p : polyline)
                {
                    p.x *= xScale, p.y *= yScale;
                }
            }
        }
    }
}


void Sample::GetPredictions(const std::byte *  outputData, std::vector<int64_t> & shape, const std::vector<std::string>& output_names, Model_t * model)
{
    Vec3<float> value((float*)outputData, shape[0], shape[1], shape[2]);

    // Scale the boxes to be relative to the original image size
    auto viewport = m_deviceResources->GetScreenViewport();
    float xScale = (float)viewport.Width / YoloV4Constants::c_inputWidth;
    float yScale = (float)viewport.Height / YoloV4Constants::c_inputHeight;

    float* _ptr = (float*)outputData;
    for (Int64 i = 0; i < value.z; ++i)
    {
        for (Int64 j = 0; j < value.y; ++j)
        {
            auto ptr = value[i][j];
            Detection result;
            if (value.x == 85)
            {
                float max = 0.0f;
                int max_loc = 0;
                float box_confidence = ptr[4];
                //if (box_confidence == 0.0f)
                //    continue;
                box_confidence = 1.0f;
                for (int ii = 0; ii < 80; ii++)
                {
                    auto class_conf = ptr[i + 5] * box_confidence;
                    if (class_conf > max)
                    {
                        max = class_conf;
                        max_loc = i;
                    }
                }
                result.confidence = max;
                result.index = max_loc;

            }
            else
            {
                //float* _ptr = (float*)ptr.data();
                if (ptr[4] < threshold) continue;
                result.confidence = (float)ptr[4];
                result.index = (Int64)ptr[5];

            }
          
            result.x = ptr[0];
            result.y = ptr[1];
            result.w = ptr[2];
            result.h = ptr[3];
           
            

            // We need to do some postprocessing on the raw values before we return them

            // Convert x,y,w,h to xmin,ymin,xmax,ymax
            float xmin = result.x - result.w / 2;
            float ymin = result.y - result.h / 2;
            float xmax = result.x + result.w / 2;
            float ymax = result.y + result.h / 2;

            xmin *= xScale;
            ymin *= yScale;
            xmax *= xScale;
            ymax *= yScale;

            // Clip values out of range
            xmin = std::clamp(xmin, 0.0f, (float)viewport.Width);
            ymin = std::clamp(ymin, 0.0f, (float)viewport.Height);
            xmax = std::clamp(xmax, 0.0f, (float)viewport.Width);
            ymax = std::clamp(ymax, 0.0f, (float)viewport.Height);

            // Discard invalid boxes
            if (xmax <= xmin || ymax <= ymin || IsInfOrNan( xmin, ymin, xmax, ymax ))
            {
                continue;
            }

            Prediction pred = {};
            pred.xmin = xmin;
            pred.ymin = ymin;
            pred.xmax = xmax;
            pred.ymax = ymax;
            pred.score = result.confidence;
            pred.predictedClass = result.index;
            m_preds.push_back(pred);
        }
    }
    // Apply NMS to select the best boxes
    m_preds = ApplyNonMaximalSuppression(m_preds, YoloV4Constants::c_nmsThreshold);
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

    InitializeDirectML( );
    
    if (!m_dmlDevice)
    {
        m_run_on_gpu = true;
        InitializeDirectML( );
      
    }
    if (!m_dmlDevice)
    {
        MessageBox(0, L"No ML device found", L"Error", MB_OK);
        ExitProcess(1);
    }

    // Add the DML execution provider to ORT using the DML Device and D3D12 Command Queue created above.
    InitializeDirectMLResources();
    CheckDevice( );

    m_deviceResources->CreateDeviceResources();  	
    CheckDevice( );

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
    PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");

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

    PIXEndEvent();
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
    
    
    
    m_copypixels_tensor_duration = std::chrono::duration<double, std::milli>( 0 );
    m_inference_duration = std::chrono::duration<double, std::milli>( 0 );
    m_output_duration = std::chrono::duration<double, std::milli>( 0 );
    m_preds.clear( );
    //m_output_texture.Reset();

    for ( auto& model : m_models )
    {
        // Convert image to tensor format (original texture -> model input)
        const size_t inputChannels = model->m_inputShape[ model->m_inputShape.size( ) - 3 ];
        const size_t inputHeight = model->m_inputHeight;
        const size_t inputWidth = model->m_inputWidth;
        const size_t inputElementSize = model->m_inputDataType == ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT ? sizeof( float ) : sizeof( uint16_t );

        if ( model->m_inputBuffer.size( ) != inputChannels * inputHeight * inputWidth * inputElementSize )
        {
            model->m_inputBuffer.resize( inputChannels * inputHeight * inputWidth * inputElementSize );
        }
        if ( CopySharedVideoTextureTensor( model->m_inputBuffer, model.get( ) ) )
        {
            // Record start
            auto start = std::chrono::high_resolution_clock::now( );

            // Create input tensor
            Ort::MemoryInfo memoryInfo2 = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
            auto inputTensor = Ort::Value::CreateTensor(
                memoryInfo2,
                model->m_inputBuffer.data( ),
                model->m_inputBuffer.size( ),
                model->m_inputShape.data( ),
                model->m_inputShape.size( ),
                model->m_inputDataType
            );

            // Bind tensors
            Ort::MemoryInfo memoryInfo0 = Ort::MemoryInfo::CreateCpu( OrtArenaAllocator, OrtMemTypeDefault );
            Ort::Allocator allocator0( model->m_session, memoryInfo0 );
            auto inputName = model->m_session.GetInputNameAllocated( 0, allocator0 );
            auto bindings = Ort::IoBinding::IoBinding( model->m_session );
            try
            {
                bindings.BindInput( inputName.get( ), inputTensor );
            }
            catch ( const std::runtime_error& re )
            {
                const char* err = re.what( );
                MessageBoxA( 0, err, "Error loading model", MB_YESNO );
                std::cerr << "Runtime error: " << re.what( ) << std::endl;
                exit( 1 );
            }
            // Create output tensor(s) and bind
            auto tensors = model->m_session.GetOutputCount( );
            std::vector<std::string> output_names;
            std::vector<std::vector<int64_t>> output_shapes;
            std::vector<ONNXTensorElementDataType> output_datatypes;
            for ( int i = 0; i < tensors; i++ )
            {
                auto output_name = model->m_session.GetOutputNameAllocated( i, allocator0 );
                output_names.push_back( output_name.get( ) );
                auto type_info = model->m_session.GetOutputTypeInfo( i );
                auto tensor_info = type_info.GetTensorTypeAndShapeInfo( );
                auto shape = tensor_info.GetShape( );

                for ( int i = 0; i < shape.size( ); i++ )
                {
                    if ( i == 0 && shape[ i ] == -1 )
                        shape[ i ] = 1;
                    if ( i > 0 && shape[ i ] == -1 )
                        shape[ i ] = 640;
                }

                output_shapes.push_back( shape );

                output_datatypes.push_back( tensor_info.GetElementType( ) );

                bindings.BindOutput( output_names.back( ).c_str( ), memoryInfo2 );
            }
            try
            {
                // Run the session to get inference results.
                Ort::RunOptions runOpts;
                model->m_session.Run( runOpts, bindings );

                CheckDevice( );

                bindings.SynchronizeOutputs( );

                CheckDevice( );
            }
            catch ( const std::exception& ex )
            {
                const char* err = ex.what( );
                MessageBoxA( 0, err, "Error loading model", MB_YESNO );
                std::cerr << "Error occurred: " << ex.what( ) << std::endl;
                exit( 1 );
            }


            std::vector<const std::byte*> outputData;
            int  i = 0;
            for ( int i = 0; i < tensors; i++ )
            {
                const std::byte* outputBuffer = reinterpret_cast< const std::byte* >( bindings.GetOutputValues( )[ i ].GetTensorRawData( ) );
                outputData.push_back( outputBuffer );
            }

            auto end = std::chrono::high_resolution_clock::now( );
            m_inference_duration += ( end - start );

            if ( outputData.size( ) > 0 )
            {
                // Record start
                auto start = std::chrono::high_resolution_clock::now( );

                if ( outputData.size( ) == 1 && output_shapes[ 0 ].size( ) == 3 && output_datatypes[ 0 ] != ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8 )
                {
                    GetPredictions( outputData[ 0 ], output_shapes[ 0 ], output_names, model.get( ) );
                }
                else  if ( outputData.size( ) == 1 && output_shapes[ 0 ].size( ) == 4 )
                {
                    GetImage( outputData[ 0 ], output_shapes[ 0 ], model.get( ), output_datatypes[ 0 ] );
                }
                else  if ( outputData.size( ) == 1 && output_shapes[ 0 ].size( ) == 3 && output_datatypes[ 0 ] == ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8 )
                {
                    GetMask( outputData[ 0 ], output_shapes[ 0 ], model.get( ), output_datatypes[ 0 ] );
                }
                else if ( outputData.size( ) == 2 && output_names[ 0 ] == "box_coords" && output_names[ 1 ] == "box_scores" )
                {
                    GetFaces( outputData, output_shapes, model.get( ) );
                }
                else if ( outputData.size( ) == 2 )
                {
                    GetPredictions2( outputData, output_shapes, output_names, model.get( ) );
                }
                else if ( outputData.size( ) >= 3 )
                {
                    GetPredictions( outputData, output_shapes, output_names, model.get( ) );
                }

                if ( !m_mask_ready )
                {
                    m_mask.clear( );
                }

                auto end = std::chrono::high_resolution_clock::now( );
                m_output_duration += ( end - start );
            }
        }
    }
    
    if ( m_mask_ready )
    {
        m_mask_ready = false;
        NewTexture( m_mask.data( ), m_mask_width, m_mask_height );
    }
}

// Draws the scene.
void Sample::Render()
{
    auto frameCount = m_timer.GetFrameCount( );
    // Don't try to render anything before the first Update.
    if ( frameCount == 0)
    {
        return;
    }

    ImGui_ImplDX12_NewFrame( );
    ImGui_ImplWin32_NewFrame( );
    ::ImGui::NewFrame( );

    // Get the latest video frame
    RECT r = { 0, 0, static_cast< LONG >( m_origTextureWidth ), static_cast< LONG >( m_origTextureHeight ) };
    MFVideoNormalizedRect rect = { 0.0f, 0.0f, 1.0f, 1.0f };

    m_player->TransferFrame( m_sharedVideoTexture, rect, r, m_pts );

    // 
    // Kick off the compute work that will be used to render the next frame. We do this now so that the data will be
    // ready by the time the next frame comes around.
    // 
    if ( ( frameCount % 100 ) == 0 )
    {
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
        PIXBeginEvent(commandList.GetInterfacePointer<ID3D12GraphicsCommandList>( ), PIX_COLOR_DEFAULT, L"Render to screen" );

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

        PIXEndEvent(commandList.GetInterfacePointer<ID3D12GraphicsCommandList>( ) );
    }

    // Readback the raw data from the model, compute the model's predictions, and render the bounding boxes
    {
        PIXBeginEvent(commandList.GetInterfacePointer<ID3D12GraphicsCommandList>( ), PIX_COLOR_DEFAULT, L"Render predictions");

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

          

            //DirectX::XMVECTORF32 White = { { { 0.980392158f, 0.980392158f, 0.980392158f, 1.0f} } }; // #fafafa
            //DirectX::XMVECTORF32 White = { { { .0f, 0.980392158f, .0f, 1.0f} } }; // #fafafa
            int col = colors[((pred.predictedClass < 0) ? 0 : pred.predictedClass) % 20];
            DirectX::XMVECTORF32 White = { { { (col >> 16) / 255.0f, ((col >> 8) & 0xff) / 255.0f, (col & 0xff) / 255.0f, 1.0f} } }; // #fafafa

            if (pred.m_polylines.size() == 0)
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
            for (auto p : pred.m_keypoints)
            {
                DirectX::XMVECTORF32 KeyColor = { {  {0.0f, 1.0f, .0f, 1.0f} } }; // # green
                float dx = 3.0f;
                VertexPositionColor upperLeft(SimpleMath::Vector3(p.first - dx, p.second - dx, 0.f), KeyColor);
                VertexPositionColor upperRight(SimpleMath::Vector3(p.first + dx, p.second - dx, 0.f), KeyColor);
                VertexPositionColor lowerRight(SimpleMath::Vector3(p.first + dx, p.second + dx, 0.f), KeyColor);
                VertexPositionColor lowerLeft(SimpleMath::Vector3(p.first - dx, p.second + dx, 0.f), KeyColor);
                m_lineBatch->DrawQuad(upperLeft, upperRight, lowerRight, lowerLeft);


            }

            for (auto& polyline : pred.m_polylines)
            {
                // The number type to use for tessellation
                using Coord = double;

                // The index type. Defaults to uint32_t, but you can also pass uint16_t if you know that your
                // data won't have more than 65536 vertices.
                using N = uint32_t;

                // Create array
                using Point = std::array<Coord, 2>;
                std::vector<std::vector<Point>> polygon;
                polygon.push_back(std::vector<Point>());
                int  i = 0;
                for (auto& p : polyline)
                {
                    polygon[0].push_back(Point{ p.x, p.y });
                }
                auto indices = mapbox::earcut<int32_t>(polygon);
                int size = indices.size();
                std::vector< VertexPositionColor> vertices;
                vertices.reserve(size);
               
                for (auto n : indices)
                {
                    Point& p = polygon[0][n];
                    VertexPositionColor e(SimpleMath::Vector3(p[0], p[1], 0.f), White);
                    vertices.push_back(e);
                }
                m_lineBatch->Draw(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, vertices.data(), size);

            }
        }
        m_lineBatch->End();

        // Draw bounding box outlines
        m_lineEffect2->Apply(commandList);

        m_lineBatch2->Begin(commandList);
      
        m_lineEffect2->SetAlpha(0.9f /*pred.score / 5.0*/);
        for (auto& pred : m_preds)
        {
            int col = colors[((pred.predictedClass < 0) ? 0 : pred.predictedClass) % 20];
            DirectX::XMVECTORF32 White = { { { (col >> 16) / 255.0f, ((col >> 8) & 0xff) / 255.0f, (col & 0xff) / 255.0f, 1.0f} } }; // #fafafa

            for (auto& polyline : pred.m_polylines)
            {
                std::vector<crushedpixel::Vec2> points;

                for (auto& p : polyline)
                {
                    points.push_back(crushedpixel::Vec2{ p.x, p.y });
                }

                auto thickness = 10.0f;
                auto thick_line_vertices = crushedpixel::Polyline2D::create(points, thickness,
                    crushedpixel::Polyline2D::JointStyle::MITER,
                    crushedpixel::Polyline2D::EndCapStyle::SQUARE);

                std::vector< VertexPositionColor> vertices;
                vertices.reserve(thick_line_vertices.size());

                //White.f[0] = 1.0f;
                for (auto p : thick_line_vertices)
                {
                    VertexPositionColor e(SimpleMath::Vector3(p.x, p.y, 0.f), White);
                    vertices.push_back(e);
                }
                m_lineBatch2->Draw(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, vertices.data(), vertices.size());

            }
        }


        m_lineBatch2->End();
        
        // Draw predicted class labels
        m_spriteBatch->Begin(commandList);
        for (const auto& pred : m_preds)
        {
            if (pred.predictedClass >= 0)
            {
                const char* classText = YoloV4Constants::c_classes[pred.predictedClass];
                std::wstring classTextW(classText, classText + strlen(classText));
                wchar_t _class[128];
                swprintf_s(_class, 128, L"%s %d%%", classTextW.c_str(), (int)(pred.score * 100.0f));
                if (pred.m_polylines.size() == 0)
                {
                    // Render a drop shadow by drawing the text twice with a slight offset.
                    DX::DrawControllerString(m_spriteBatch.get(), m_legendFont.get(), m_ctrlFont.get(),
                        _class, SimpleMath::Vector2(pred.xmin, pred.ymin - 1.5f * dx) + SimpleMath::Vector2(2.f, 2.f), SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.25f));
                    DX::DrawControllerString(m_spriteBatch.get(), m_legendFont.get(), m_ctrlFont.get(),
                        _class, SimpleMath::Vector2(pred.xmin, pred.ymin - 1.5f * dx), ATG::Colors::DarkGrey);
                }
                else
                {
                    // center
                    SimpleMath::Vector2 _classSize = m_legendFont->MeasureString(_class);
                     // Render a drop shadow by drawing the text twice with a slight offset.
                    DX::DrawControllerString(m_spriteBatch.get(), m_legendFont.get(), m_ctrlFont.get(),
                        _class,
                        SimpleMath::Vector2((pred.xmin + pred.xmax) / 2.0f - _classSize.x/2.0f, (pred.ymin + pred.ymax) / 2.0f) + SimpleMath::Vector2(2.f, 2.f),
                        SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.25f));

                    DX::DrawControllerString(m_spriteBatch.get(), m_legendFont.get(), m_ctrlFont.get(),
                        _class,
                        SimpleMath::Vector2((pred.xmin + pred.xmax) /2.0f - _classSize.x / 2.0f, (pred.ymin + pred.ymax) / 2.0f ),
                        ATG::Colors::DarkGrey);

                }
            }
        }
        m_spriteBatch->End();

        // Render the UI
        RenderUI( );
        
        ::ImGui::Render( );
        ID3D12GraphicsCommandList* commandListPtr = static_cast< ID3D12GraphicsCommandList* >( commandList.GetInterfacePointer( ) );
        ImGui_ImplDX12_RenderDrawData( ::ImGui::GetDrawData( ), commandListPtr );


        PIXEndEvent(commandList.GetInterfacePointer<ID3D12GraphicsCommandList>( ) );
    }

    // Show the new frame.
    PIXBeginEvent(m_deviceResources->GetCommandQueue().GetInterfacePointer<ID3D12CommandQueue>( ), PIX_COLOR_DEFAULT, L"Present");

    m_deviceResources->Present();

    PIXEndEvent(m_deviceResources->GetCommandQueue().GetInterfacePointer<ID3D12CommandQueue>( ) );

    m_graphicsMemory->Commit(m_deviceResources->GetCommandQueue());

    
}


void Sample::RenderUI( )
{
    ImGui::Begin( "Yolo 9" );

    const char* modelLabel = "Object detection model:";
    if ( m_models.size( ) > 1 )
        modelLabel = "Object detection models:";
    ImGui::Text( modelLabel );

    for ( auto& _model : m_models )
    {
        auto modelFile = ToAnsiString( _model->m_modelfile );
        auto deviceName = ToAnsiString( m_device_name );
        auto model = Format("{} {}", modelFile, deviceName );
        ImGui::Text( model.c_str() );
    }

    auto fps = Format( "{:0.2f} FPS", m_fps.GetFPS( ) );
    ImGui::Text( fps.c_str( ) );
    auto scaleCopy = Format( "Scale/copy: {:0.2f} ms", m_copypixels_tensor_duration.count( ) );
    ImGui::Text( scaleCopy.c_str( ) );
    auto inference = Format( "Inference: {:0.2f} ms", m_inference_duration.count( ) );
    ImGui::Text( inference.c_str( ) );
    auto output = Format( "Output: {:0.2f} ms", m_output_duration.count( ) );
    ImGui::Text( output.c_str( ) );
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
    PIXBeginEvent(commandList.GetInterfacePointer<ID3D12GraphicsCommandList>(), PIX_COLOR_DEFAULT, L"Clear" );

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

    PIXEndEvent(commandList.GetInterfacePointer<ID3D12GraphicsCommandList>( ) );
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

        m_texRootSignatureNN = device.CreateRootSignature( 0, rootSignatureDesc );

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


        m_texPipelineStateNN = device.CreateGraphicsPipelineState(psoDesc);

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
    m_sprite = std::make_unique<SpriteBatch>(device, uploadBatch, spd);

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

    m_texPipelineStateNN.ResetPtr();
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

    m_computePSO.ResetPtr();
    m_computeRootSignature.ResetPtr();

    m_dmlDevice.ResetPtr();
    m_dmlCommandRecorder.ResetPtr();

    m_modelInput.ResetPtr();
    m_modelSOutput = {};
    m_modelMOutput = {};
    m_modelLOutput = {};
    m_dmlOpInitializer.ResetPtr();
    m_dmlGraph.ResetPtr();
    m_modelTemporaryResource.ResetPtr();
    m_modelPersistentResource.ResetPtr();

    m_dmlDescriptorHeap.reset();

    m_graphicsMemory.reset();
}

void Sample::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
