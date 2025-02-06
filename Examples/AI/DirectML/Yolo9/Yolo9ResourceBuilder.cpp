#include "pch.h"

#include "yolo9.h"

#include "ATGColors.h"
#include "ControllerFont.h"
#include "FindMedia.h"
#include "ReadData.h"


#include "TensorHelper.h"

#include "ssd_anchors.h"
//#include "onnx.proto3.pb.h"

#pragma comment(lib,"Microsoft.AI.MachineLearning.lib")
#pragma comment(lib,"onnxruntime.lib")

using Microsoft::WRL::ComPtr;

using namespace DirectX;

static bool TryGetProperty(const DXCore::Adapter1& adapter, DXCoreAdapterProperty prop, std::string& outputValue)
{
    if (adapter.IsPropertySupported(prop))
    {
        size_t propSize = adapter.GetPropertySize( prop );

        outputValue.resize(propSize);
        adapter.GetProperty(prop, propSize, outputValue.data());

        // Trim any trailing nul characters. 
        while (!outputValue.empty() && outputValue.back() == '\0')
        {
            outputValue.pop_back();
        }

        return true;
    }
    return false;
}

DXCore::Adapter1 Sample::GetNonGraphicsAdapter( const DXCore::AdapterList& adapterList )
{
    
    for (uint32_t i = 0, adapterCount = adapterList.GetAdapterCount(); i < adapterCount; i++)
    {
        auto possibleAdapter = adapterList.GetAdapter( i );

        std::string adapterName;
        if (TryGetProperty(possibleAdapter, DXCoreAdapterProperty::DriverDescription, adapterName))
        {
            if (m_run_on_gpu)
            {
                if (possibleAdapter.IsAttributeSupported(DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS))
                {
                    m_device_name = L"GPU";
                    return possibleAdapter;
                }
            }

            if (!possibleAdapter.IsAttributeSupported(DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS))
            {
                m_device_name = L"NPU";
                return possibleAdapter;
            }
        }
    }
    return {};
}

void Sample::InitializeDirectML(/*ID3D12Device1** d3dDeviceOut, ID3D12CommandQueue** commandQueueOut, IDMLDevice** dmlDeviceOut,
    ID3D12CommandAllocator** commandAllocatorOut,
    ID3D12GraphicsCommandList** commandListOut*/ )
{
#if 0
    // is extermely slow when createing the ort::Session
#if defined(_DEBUG)
    // Enable the debug layer (requires the Graphics Tools "optional feature").
    //
    // NOTE: Enabling the debug layer after device creation will invalidate the active device.
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
        {
            debugController->EnableDebugLayer();
        }
        else
        {
            OutputDebugStringA("WARNING: Direct3D Debug Device is not available\n");
        }

        ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
        if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiInfoQueue.GetAddressOf()))))
        {
            m_dxgiFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

            dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
            dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);

            DXGI_INFO_QUEUE_MESSAGE_ID hide[] =
            {
                80 /* IDXGISwapChain::GetContainingOutput: The swapchain's adapter does not control the output on which the swapchain's window resides. */,
            };
            DXGI_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            dxgiInfoQueue->AddStorageFilterEntries(DXGI_DEBUG_DXGI, &filter);
        }
    }
#endif
#endif

    // Create Adapter Factory
    auto factory = DXCore::CreateAdapterFactory( );

    // Create the DXCore Adapter, for the purposes of selecting NPU we look for (!GRAPHICS && (GENERIC_ML || CORE_COMPUTE))
    DXCore::Adapter1 adapter;
    DXCore::AdapterList adapterList;
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_1_0_GENERIC;

    m_run_on_gpu = true;

    if (factory)
    {
        adapterList = factory.CreateAdapterList( 1, &DXCORE_ADAPTER_ATTRIBUTE_D3D12_GENERIC_ML );
        std::array adapterPreferences = { DXCoreAdapterPreference::HighPerformance,DXCoreAdapterPreference::Hardware };
        adapterList.Sort( adapterPreferences.size( ), adapterPreferences.data( ) );
        

        if (adapterList.GetAdapterCount() > 0)
        {
            adapter = GetNonGraphicsAdapter(adapterList);
        }

        if (!adapter)
        {
            
            featureLevel = D3D_FEATURE_LEVEL_1_0_CORE;
            adapterList = factory.CreateAdapterList( 1, &DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE );
            adapter = GetNonGraphicsAdapter(adapterList);
        }
    }

    if (adapter)
    {
        std::string adapterName;
        if (TryGetProperty(adapter, DXCoreAdapterProperty::DriverDescription, adapterName))
        {
            printf("Successfully found adapter %s\n", adapterName.c_str());
        }
        else
        {
            printf("Failed to get adapter description.\n");
        }
        adapter_ = adapter;
        m_deviceResources->SetAdapter( adapter_ );
    }

    // Create the D3D12 Device
    D3D12::Device14 d3dDevice = D3D12::CreateDevice<D3D12::Device14>( adapter, featureLevel );
    

    // Create the DML Device and D3D12 Command Queue
    DML::Device dmlDevice;
    D3D12::CommandQueue commandQueue;
    D3D12::CommandAllocator commandAllocator;
    D3D12::GraphicsCommandList commandList;
    if (d3dDevice)
    {
        D3D12::CommandQueueDesc queueDesc = {};
        queueDesc.Type = D3D12::CommandListType::Compute;
        commandQueue = d3dDevice.CreateCommandQueue( queueDesc );

        commandAllocator = d3dDevice.CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COMPUTE);
        commandList = d3dDevice.CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_COMPUTE, commandAllocator );

        dmlDevice = DML::CreateDevice1( d3dDevice, DML::FeatureLevel::_6_0 );
    }

    m_d3dDevice = std::move(d3dDevice);
    m_commandQueue = std::move( commandQueue );
    m_dmlDevice = std::move( dmlDevice );
    m_commandAllocator = std::move( commandAllocator );
    m_commandList = std::move( commandList );
    m_deviceResources->SetDevice( m_d3dDevice );
}


void Sample::InitializeDirectMLResources(const wchar_t * model_path, bool bAddModel)
{
    // wait for gpu to create new textures
    m_deviceResources->WaitForGpu();

    const OrtApi& ortApi = Ort::GetApi();
    static Ort::Env s_OrtEnv{ nullptr };
    s_OrtEnv = Ort::Env(Ort::ThreadingOptions{});
    s_OrtEnv.DisableTelemetryEvents();

    auto sessionOptions = Ort::SessionOptions{};
    sessionOptions.DisableMemPattern();
    sessionOptions.DisablePerSessionThreads();
    sessionOptions.SetExecutionMode(ExecutionMode::ORT_SEQUENTIAL);

    //sessionOptions.SetExecutionMode(ExecutionMode::ORT_PARALLEL);
    //sessionOptions.AddConfigEntry("session.load_model_format", "ORT");
    //sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);

    m_ortDmlApi = nullptr;
    Ort::ThrowOnError(ortApi.GetExecutionProviderApi("DML", ORT_API_VERSION, reinterpret_cast<const void**>(&m_ortDmlApi)));
    Ort::ThrowOnError(m_ortDmlApi->SessionOptionsAppendExecutionProvider_DML1(sessionOptions, m_dmlDevice.GetInterfacePointer<IDMLDevice>(), m_commandQueue.GetInterfacePointer<ID3D12CommandQueue>()));


    if (!bAddModel)
        m_models.clear();

    std::unique_ptr<Model_t> model = std::make_unique<Model_t>();
    m_models.emplace_back(std::move(model));

    try
    {
        if (model_path == nullptr)
        {

            // Create the session

            //auto session = Ort::Session(s_OrtEnv, L"mobilenetv2-7-fp16.onnx", sessionOptions);
            // model from here:
            // https://github.com/DakeQQ/YOLO-Depth-Estimation-for-Android

            //wchar_t * modelfile = L"Model_Yolo_v9c.ort";
            const wchar_t* modelfile = L"Model_Yolo_v9c_f16.onnx";
            //wchar_t* modelfile = L"Model_Yolo_v9c_f16_h1088_w1920.onnx";
            //wchar_t* modelfile = L"yolov11_det.onnx";
            //wchar_t* modelfile = L"yolo11n.onnx";
            //wchar_t* modelfile = L"yolov10m.onnx";
            //wchar_t* modelfile = L"yolov8_det.onnx";
           //wchar_t* modelfile = L"yolov8_seg.onnx";
           // wchar_t* modelfile = L"yolo11n-seg.onnx";

            m_models.back()->m_modelfile = std::wstring(modelfile);
            auto home = Harlinn::Common::Core::Environment::EnvironmentVariable( L"HCC_HOME" );
            auto yoloDir = IO::Path::Combine( home, L"Share\\onnx\\models\\yolo" );
            auto yoloModel = IO::Path::Combine( yoloDir, m_models.back( )->m_modelfile.c_str() );

            std::wstring model_path = yoloModel.c_str();
             m_models.back()->m_session = Ort::Session(s_OrtEnv, model_path.c_str(), sessionOptions);
        }
        else
        {
            const wchar_t* pstrName = wcsrchr(model_path, '\\');
            if (!pstrName)
            {
                 m_models.back()->m_modelfile = std::wstring(model_path);
            }
            else
            {
                pstrName++;
                 m_models.back()->m_modelfile = std::wstring(pstrName);
            }

             m_models.back()->m_session = Ort::Session(s_OrtEnv, model_path, sessionOptions);
        }
        
    }
    catch (const std::runtime_error& re) {
        std::cerr << "Runtime error: " << re.what() << std::endl;
        exit(1);
    }
    catch (const std::exception& ex)
    {
        const char* err = ex.what();
        MessageBoxA(0, err, "Error loading model", MB_YESNO);
        std::cerr << "Error occurred: " << ex.what() << std::endl;
        exit(1);
    }
    // Create input tensor
    Ort::MemoryInfo memoryInfo0 = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Allocator allocator0( m_models.back()->m_session, memoryInfo0);

    auto meta =  m_models.back()->m_session.GetModelMetadata();
    auto modelname = meta.GetGraphNameAllocated(allocator0);

    auto inputName =  m_models.back()->m_session.GetInputNameAllocated(0, allocator0);
    auto inputTypeInfo =  m_models.back()->m_session.GetInputTypeInfo(0);
    auto inputTensorInfo = inputTypeInfo.GetTensorTypeAndShapeInfo();
    m_models.back()->m_inputShape = inputTensorInfo.GetShape();
    
    for (int i = 0; i < m_models.back()->m_inputShape.size(); i++)
    {
        if (i == 0 && m_models.back()->m_inputShape[i] == -1)
            m_models.back()->m_inputShape[i] = 1;
        if (i > 0 && m_models.back()->m_inputShape[i] == -1)
            m_models.back()->m_inputShape[i] = 640;
    }


    m_models.back()->m_inputDataType = inputTensorInfo.GetElementType();
    if ( m_models.back()->m_inputDataType != ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT &&  m_models.back()->m_inputDataType != ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16)
    {
        throw std::invalid_argument("Model input must be of type float32 or float16");
    }
    if ( m_models.back()->m_inputShape.size() < 3)
    {
        throw std::invalid_argument("Model input must be an image with 3 or 4 dimensions");
    }

    const size_t inputChannels =  m_models.back()->m_inputShape[ m_models.back()->m_inputShape.size() - 3];
    const size_t inputHeight =  m_models.back()->m_inputShape[ m_models.back()->m_inputShape.size() - 2];
    const size_t inputWidth =  m_models.back()->m_inputShape[ m_models.back()->m_inputShape.size() - 1];


    m_models.back()->m_inputWidth = inputWidth;
    m_models.back()->m_inputHeight = inputHeight;

    const size_t inputElementSize =  m_models.back()->m_inputDataType == ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT ? sizeof(float) : sizeof(uint16_t);

    auto outputName =  m_models.back()->m_session.GetOutputNameAllocated(0, allocator0);
    auto tensors =  m_models.back()->m_session.GetOutputCount();
    auto outputTypeInfo =  m_models.back()->m_session.GetOutputTypeInfo(0);
    auto outputTensorInfo = outputTypeInfo.GetTensorTypeAndShapeInfo();
    m_models.back()->m_outputShape = outputTensorInfo.GetShape();
    auto outputDataType = outputTensorInfo.GetElementType();
    if (outputDataType != ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT && outputDataType != ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16 
        && outputDataType != ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8)
    {
        throw std::invalid_argument("Model output must be of type float32 or float16 or int8");
    }
    if ( m_models.back()->m_outputShape.size() < 3)
    {
        throw std::invalid_argument("Model output must be an image with 3 or 4 dimensions");
    }


    // mediapipe face detection anchors
    // Anchors generation
  //https://github.com/google/mediapipe/blob/master/mediapipe/modules/face_detection/face_detection.pbtxt
    {
        onnxmediapipe::SsdAnchorsCalculatorOptions ssdAnchorsCalculatorOptions;
        ssdAnchorsCalculatorOptions.input_size_height = (int32_t)128;
        ssdAnchorsCalculatorOptions.input_size_width = (int32_t)128;
        ssdAnchorsCalculatorOptions.min_scale = 0.1484375;
       
        ssdAnchorsCalculatorOptions.max_scale = 0.75;
        ssdAnchorsCalculatorOptions.anchor_offset_x = 0.5;
        ssdAnchorsCalculatorOptions.anchor_offset_y = 0.5;
        ssdAnchorsCalculatorOptions.aspect_ratios = { 1.0 };
        ssdAnchorsCalculatorOptions.fixed_anchor_size = true;

        //192x192 implies 'full range' face detection.
        if ((inputHeight == 192) && (inputWidth == 192))
        {
            //https://github.com/google/mediapipe/blob/master/mediapipe/modules/face_detection/face_detection_full_range.pbtxt
            ssdAnchorsCalculatorOptions.num_layers = 1;
            ssdAnchorsCalculatorOptions.strides = { 4 };
            ssdAnchorsCalculatorOptions.interpolated_scale_aspect_ratio = 0.0;
        }
        else
        {
            //https://github.com/google/mediapipe/blob/master/mediapipe/modules/face_detection/face_detection_short_range.pbtxt
            ssdAnchorsCalculatorOptions.num_layers = 4;
            ssdAnchorsCalculatorOptions.strides = { 8, 16, 16, 16 };
            ssdAnchorsCalculatorOptions.interpolated_scale_aspect_ratio = 1.0;
        }
        

        m_anchors.clear();
        std::vector<onnxmediapipe::Anchor> anchors;
        onnxmediapipe::SsdAnchorsCalculator::GenerateAnchors(anchors, ssdAnchorsCalculatorOptions);
        m_anchors.push_back(anchors);

        if (true)
        {
            ssdAnchorsCalculatorOptions.input_size_height = (int32_t)256;
            ssdAnchorsCalculatorOptions.input_size_width = (int32_t)256;
            ssdAnchorsCalculatorOptions.min_scale = 0.1171875;
            ssdAnchorsCalculatorOptions.num_layers = 5;
            ssdAnchorsCalculatorOptions.strides = { 8, 16, 32, 32, 32 };
            ssdAnchorsCalculatorOptions.interpolated_scale_aspect_ratio = 1.0;

        }
        anchors.clear();
        onnxmediapipe::SsdAnchorsCalculator::GenerateAnchors(anchors, ssdAnchorsCalculatorOptions);
        m_anchors.push_back(anchors);

    }
}
