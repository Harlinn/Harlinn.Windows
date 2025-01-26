// EWD312HelloTriangle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HWDXApplication.h>
#include <HCCVectorMath.h>

using namespace Harlinn;
using namespace Harlinn::Windows;
namespace m = Harlinn::Common::Core::Math;

class HelloTriangleForm : public Windows::DXForm
{
public:
    using Base = Windows::DXForm;
    using DXContext = Windows::DXContext;
    using PipelineState = Windows::Graphics::D3D12::PipelineState;
    using Resource = Windows::Graphics::D3D12::Resource;
    using VertexBufferView = Windows::Graphics::D3D12::VertexBufferView;
protected:
    float aspectRatio_ = 1.f;
    ComPtr<ID3D12Resource> m_vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

    struct Vertex
    {
        m::Point3f position;
        m::Vector<float, 4> color;
    };

    virtual void DoOnSize( Windows::Message& message ) override
    {
        Base::DoOnSize( message );
        auto width = ( UInt32 )LOWORD( message.lParam );
        auto height = ( UInt32 )HIWORD( message.lParam );
        if ( height )
        {
            aspectRatio_ = static_cast< float >( width ) / static_cast< float >( height );
        }
    }

    virtual void DoOnRender( ) override
    {

    }

    virtual void DoOnCreatePipelineState( DXContext* context, PipelineState& pipelineState ) override
    {
        using namespace Windows::Graphics::D3D12;
        using Format = Windows::Graphics::DXGI::Format;
        const auto& device = context->Device( );
        const auto& rootSignature = context->RootSignature( );
        // Get the path of shaders.hlsl 
        auto shadersAssetPath = GetAssetPath( L"shaders.hlsl" );

#if defined(_DEBUG)
        // Enable better shader debugging with the graphics debugging tools.
        UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
        UINT compileFlags = 0;
#endif


        auto vertexShader = CompileFromFile( shadersAssetPath, "VSMain", "vs_5_0", compileFlags );
        auto pixelShader = CompileFromFile( shadersAssetPath, "PSMain", "ps_5_0", compileFlags );

        // Define the vertex input layout.
        std::array<InputElementDesc,2> inputElementDescs =
        {
            InputElementDesc{"POSITION", 0, Format::R32G32B32_FLOAT, 0, 0, InputClassification::PerVertexData, 0},
            InputElementDesc{"COLOR", 0, Format::R32G32B32A32_FLOAT, 0, 12, InputClassification::PerVertexData, 0}
        };

        // Describe and create the graphics pipeline state object (PSO).
        GraphicsPipelineStateDesc psoDesc;
        psoDesc.InputLayout = inputElementDescs;
        psoDesc.pRootSignature = rootSignature;
        psoDesc.VS = vertexShader;
        psoDesc.PS = pixelShader;
        psoDesc.DepthStencilState.DepthEnable = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = PrimitiveTopologyType::Triangle;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[ 0 ] = context->Format( );
        psoDesc.SampleDesc.Count = 1;

        pipelineState = device.CreateGraphicsPipelineState( psoDesc );
    }

    

    std::vector<Vertex> GetVertices( )
    {
        std::vector<Vertex> vertices =
        {
            { { 0.0f, 0.25f * aspectRatio_, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
            { { 0.25f, -0.25f * aspectRatio_, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
            { { -0.25f, -0.25f * aspectRatio_, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
        };
        return vertices;
    }

    virtual void DoOnInvalidateDeviceObjects( DXContext* context ) override
    {
        Base::DoOnInvalidateDeviceObjects( context );
    }

    virtual void DoOnCreateDeviceObjects( DXContext* context ) override
    {
        Base::DoOnCreateDeviceObjects( context );
    }


private:
    

};

int main()
{
    try
    {
        auto application = std::make_shared<Windows::DXApplication>();
        application->Start( );

        HelloTriangleForm form;
        form.SetText( L"Hello Triangle Demo" );

        auto result = application->Run( form );

        application->Stop( );

        return result;
    }
    catch ( std::exception& exc )
    {
        std::cout << exc.what( ) << std::endl;
    }
    catch ( ... )
    {
        std::cout << "Unknown exception" << std::endl;
    }
    return 0;
}

