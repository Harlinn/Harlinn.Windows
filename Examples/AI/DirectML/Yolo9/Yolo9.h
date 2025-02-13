#pragma once

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


#include "DeviceResources.h"
#include "StepTimer.h"
#include "MediaEnginePlayer.h"




using UniqueNativePtr = std::unique_ptr<void, void (*)(void*)>;

template <typename T>
struct Vec1
{
    const T* data;
    Int64 x;
    Vec1(const T* data, Int64 x) : data(data), x(x) {}
    const T& operator[](Int64 i) const { return data[i]; }
};
template <typename T>
struct Vec2
{
    const T* data;
    Int64 y, x;
    Vec2(const T* data, Int64 y, Int64 x) : data(data), y(y), x(x) {}
    Vec1<T> operator[](Int64 i) const { return Vec1<T>(data + i * x, x); }
};

template <typename T>
struct Vec3
{
    const T* data;
    Int64 z, y, x;
    Vec3(const T* data, Int64 z, Int64 y, Int64 x) : data(data), z(z), y(y), x(x) {}
    Vec2<T> operator[](Int64 i) const { return Vec2<T>(data + i * y * x, y, x); }
};

template <typename T>
struct Vec4
{
    const T* data;
    Int64 w, z, y, x;
    Vec4(const T* data, Int64 w, Int64 z, Int64 y, Int64 x) : data(data), w(w), z(z), y(y), x(x) {}
    Vec3<T> operator[](Int64 i) const { return Vec3<T>(data + i * z * y * x, z, y, x); }
};

struct Detection
{
    /// @brief The x-coordinate of the top-left corner of the bounding box.
    float x;

    /// @brief The y-coordinate of the top-left corner of the bounding box.
    float y;

    /// @brief The width of the bounding box.
    float w;

    /// @brief The height of the bounding box.
    float h;

    /// @brief The index of the detected object, typically corresponding to the class index in the model.
    Int64 index;

    /// @brief The confidence level of the detection.
    float confidence;
};

using Detections = std::vector<Detection>;




namespace YoloConstants
{
    constexpr int colors[ ] = { 0xf0fafa, 0x3588d1, 0x4ad59b, 0x399283, 0x97f989, 0x57b230, 0xd8e9b2, 0xff1c5d, 0xf1bb99, 0xf7794f, 0x987d7b, 0xf4f961, 0x1dfee1, 0x9382e9, 0xc052e4, 0xf3c5fa, 0xd6709b, 0xfe16f4, 0x34f50e, 0xab7b05, 0xfbbd13 };
    
    // The classes of objects that yolov4 can detect
    static const char* const c_classes[] =
    {
        "person", "bicycle", "car", "motorbike", "airplane", "bus", "train", "truck", "boat", "traffic light",
        "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow",
        "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee",
        "skis", "snowboard", "ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard",
        "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
        "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "sofa",
        "potted plant", "bed", "dining table", "toilet", "monitor", "laptop", "mouse", "remote", "keyboard",
        "cell phone", "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors",
        "teddy bear", "hair drier", "toothbrush",
    };
    

    static const uint32_t c_numClasses = ARRAYSIZE(c_classes);

    // texture size the input tensor expects
    static  uint32_t t_inputWidth = 1280;
    static  uint32_t t_inputHeight = 720;

    // Input images are rescaled to 512x288 before being fed into the model
    static uint32_t c_inputWidth = 512;
    static uint32_t c_inputHeight = 288;

    // Discard any predictions which have a low score (i.e. predictions that the model isn't very confident about)
    static const float c_scoreThreshold = 0.25f;

    // Threshold for non-maximal suppression (NMS) which determines how much overlap between bounding boxes is needed
    // before they're eliminated
    static const float c_nmsThreshold = 0.213f;

    // YoloV4 produces bounding boxes on different scales (small, medium, large) and the outputs of the model need
    // to be scaled according to their appropriate constants.
    struct BBoxData
    {
        float xyScale;
        float stride;
        std::array<float, 6> anchors;

        static BBoxData Small()
        {
            BBoxData data;
            data.xyScale = 1.2f;
            data.stride = 8;
            data.anchors = { 12,16,   19,36,   40,28   };
            return data;
        }

        static BBoxData Medium()
        {
            BBoxData data;
            data.xyScale = 1.1f;
            data.stride = 16;
            data.anchors = { 36,75,   76,55,   72,146  };
            return data;
        }

        static BBoxData Large()
        {
            BBoxData data;
            data.xyScale = 1.05f;
            data.stride = 32;
            data.anchors = { 142,110, 192,243, 459,401 };
            return data;
        }
    };
};

class SmoothedFPS
{
public:
    SmoothedFPS(float secondsInterval = 1.f)
    {
        Initialize(secondsInterval);
    }

    void Initialize(float secondsInterval = 1.f)
    {
        m_secondsInterval = secondsInterval;
        m_timeAccumulator = 0.0f;
        m_frameAccumulator = 0;
        m_smoothedFPS = 0.0f;
    }

    void Tick(float DeltaTime)
    {
        m_timeAccumulator += DeltaTime;
        ++m_frameAccumulator;

        if (m_timeAccumulator >= m_secondsInterval)
        {
            m_smoothedFPS = (float)m_frameAccumulator / m_timeAccumulator;
            m_timeAccumulator = 0.0f;
            m_frameAccumulator = 0;
        }
    }

    float GetFPS() const { return m_smoothedFPS; }

private:
    float m_smoothedFPS;
    float m_timeAccumulator;
    uint32_t m_frameAccumulator;
    float m_secondsInterval;
};

enum class TensorLayout
{
    Default,
    NHWC
};


using Prediction = ONNX::Prediction;


#define USE_VIDEOTEXTURE 1

// A basic sample implementation that creates a D3D12 device and
// provides a render loop.
class Sample final : public DX::IDeviceNotify
{
    ImGuiIO& io_;
    static ImGuiIO& GetImGuiIO( )
    {
        ::ImGui::CreateContext( );
        ::ImPlot::CreateContext( );
        return ::ImGui::GetIO( );
    }

    std::shared_ptr<ONNX::DirectML::ComputeEngine > computeEngine_;
    std::shared_ptr<ONNX::DirectML::ComputeNode > computeNode_;
    std::shared_ptr<ONNX::DirectML::Model > model_;
    DateTime frameTime_;
    DateTime nextCompute_;
    TimeSpan computeInterval_{ TimeSpan::TicksPerSecond / 3 };
    

public:

    Sample() noexcept(false);
    ~Sample();

    // Initialization and management
    bool Initialize(HWND window, int width, int height, bool run_on_gpu = false);

    // Basic render loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);
    void OnNewFile(const wchar_t* filename);
    void OnNewModel(const wchar_t* modelfile, bool bAddModel);

    // Properties
    void GetDefaultSize(int& width, int& height) const;

private:
    
    void CheckDeviceResources( std::source_location caller = std::source_location::current( ) );
    void Update(const DX::StepTimer& timer);
    void Render();
    void BeginCompute( );

    void RenderUI( );


    void Clear();

    void CreateDeviceDependentResources();
    void CreateTextureResources();
    void InitializeDirectMLResources(const wchar_t* model_path = nullptr, bool Addmdodel = false);
    void CreateUIResources();
    void CreateWindowSizeDependentResources();


    bool CopySharedVideoTextureTensor( Binary& inputbuffer );

    
    void NewTexture(const uint8_t * image_data, uint32_t width, uint32_t height);
    // 
    // 
    bool m_run_on_gpu;
    // 
    // Device resources
    std::unique_ptr<DX::DeviceResources> m_deviceResources;

    // Rendering loop timer
    DX::StepTimer m_timer;

    // Input devices
    std::unique_ptr<DirectX::GamePad> m_gamePad;
    std::unique_ptr<DirectX::Keyboard> m_keyboard;
    DirectX::GamePad::ButtonStateTracker m_gamePadButtons;
    DirectX::Keyboard::KeyboardStateTracker m_keyboardButtons;
    bool m_ctrlConnected;

    // DirectXTK objects
    std::unique_ptr<DirectX::GraphicsMemory> m_graphicsMemory;
    std::unique_ptr<DirectX::DescriptorHeap> m_SRVDescriptorHeap;

    // UI
    SmoothedFPS                                     m_fps;
    std::unique_ptr<DirectX::BasicEffect>           m_lineEffect;
    std::unique_ptr<DirectX::BasicEffect>           m_lineEffect2;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_lineBatch;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_lineBatch2;
    std::unique_ptr<DirectX::DescriptorHeap>        m_fontDescriptorHeap;
    std::unique_ptr<DirectX::SpriteBatch>           m_spriteBatch;
    std::unique_ptr<DirectX::SpriteFont>            m_labelFont;
    std::unique_ptr<DirectX::SpriteFont>            m_labelFontBold;
    std::unique_ptr<DirectX::SpriteFont>            m_legendFont;
    std::unique_ptr<DirectX::SpriteFont>            m_ctrlFont;

    // Video player
public:
    std::unique_ptr<MediaEnginePlayer>              m_player;
private:
    HANDLE                                          m_sharedVideoTexture = 0;
    LONGLONG                                        m_pts = 0;

    // Direct3D 12 objects for rendering texture to screen
    // Nearest-neighbor texture upscale
    D3D12::RootSignature m_texRootSignatureNN;
    //D3D12::PipelineState m_texPipelineStateNN;
    // Bilinear texture upscale
    D3D12::RootSignature m_texRootSignatureLinear;
    D3D12::PipelineState m_texPipelineStateLinear;
    // Render from DML tensor format to texture
    D3D12::RootSignature m_tensorRenderRootSignature;
    D3D12::PipelineState m_tensorRenderPipelineState;
    // Static input texture to render, if USE_VIDEO == 0
    D3D12::Resource m_texture;
    // Input video frame to render, if USE_VIDEO == 1
    D3D12::Resource m_videoTexture;
    uint32_t m_origTextureHeight;
    uint32_t m_origTextureWidth;
    D3D12::Resource m_vertexBuffer;
    D3D12::Resource m_indexBuffer;
    D3D12::VertexBufferView m_vertexBufferView;
    D3D12::IndexBufferView m_indexBufferView;


    // DirectML objects

    std::vector<Prediction> m_preds;

    std::vector<byte> m_Out;
    std::chrono::duration<double, std::milli> m_copypixels_tensor_duration;
    std::chrono::duration<double, std::milli> m_inference_duration;
    std::chrono::duration<double, std::milli> m_output_duration;
    
    D2D::Factory8 m_d2d1_factory;
    D2D::Device7 m_d2d1_device;
    D2D::DeviceContext m_d2dContext;

    //std::unique_ptr<DirectX::SpriteBatch> m_sprite; // output tensor image
    D3D12::Resource m_output_texture;
    std::vector<uint8_t> m_mask;
    std::vector<uint8_t> m_pred_mask;
    bool m_mask_ready = false;
    int m_mask_width;
    int m_mask_height;
    //wil::unique_handle                              m_fenceEvent{ nullptr };

    // DirectX index enums
    enum SrvDescriptors : uint32_t
    {
        e_descTexture,
        e_descModelInput,
        e_outputTensor,
        e_srvDescCount
    };

    enum FontDescriptors : uint32_t
    {
        e_descLabelFont,
        e_descLabelFontBold,
        e_descLegendFont,
        e_descCtrlFont,
        e_fontDescCount,
    };

    enum ComputeRootParameters : uint32_t
    {
        e_crpIdxCB = 0,
        e_crpIdxSRV,
        e_crpIdxUAV,
        e_crpIdxCount
    };

    enum TensorRenderRootParameters : uint32_t
    {
        e_rrpIdxCB = 0,
        e_rrpIdxSRV,
        e_rrpIdxCount
    };
};