#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D11_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D11_H_
/*
   Copyright 2024-2025 Espen Harlinn

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

#include "HWGraphicsD3Common.h"
#include <boost/container/small_vector.hpp>

#pragma comment(lib,"D3D11.lib")


namespace Harlinn::Windows::Graphics::D3D11
{
    class DeviceChild;
    class DepthStencilState;
    class BlendState;
    class RasterizerState;
    class Resource;
    class Buffer;
    class Texture1D;
    class Texture2D;
    class Texture3D;
    class View;
    class ShaderResourceView;
    class RenderTargetView;
    class DepthStencilView;
    class UnorderedAccessView;
    class VertexShader;
    class HullShader;
    class DomainShader;
    class GeometryShader;
    class PixelShader;
    class ComputeShader;
    class InputLayout;
    class SamplerState;
    class Asynchronous;
    class Query;
    class Predicate;
    class Counter;
    class ClassInstance;
    class ClassLinkage;
    class CommandList;
    class DeviceContext;
    class VideoDecoder;
    class VideoProcessorEnumerator;
    class VideoProcessor;
    class AuthenticatedChannel;
    class CryptoSession;
    class VideoDecoderOutputView;
    class VideoProcessorInputView;
    class VideoProcessorOutputView;
    class VideoContext;
    class VideoDevice;
    class Device;
    class BlendState1;
    class RasterizerState1;
    class DeviceContextState;
    class DeviceContext1;
    class VideoContext1;
    class VideoDevice1;
    class VideoProcessorEnumerator1;
    class Device1;
    class UserDefinedAnnotation;
    class DeviceContext2;
    class Device2;
    class Texture2D1;
    class Texture3D1;
    class RasterizerState2;
    class ShaderResourceView1;
    class RenderTargetView1;
    class UnorderedAccessView1;
    class Query1;
    class DeviceContext3;
    class Fence;
    class DeviceContext4;
    class Device3;
    class Device4;
    class Device5;
    class Multithread;
    class VideoContext2;
    class VideoDevice2;
    class VideoContext3;


    /// <summary>
    /// A device-child object accesses data used by a device.
    /// </summary>
    class DeviceChild : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DeviceChild, Unknown, ID3D11DeviceChild, IUnknown )
    public:
        void GetDevice(ID3D11Device** device) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDevice(device);
            
        }

        void GetPrivateData( const Guid& guid, UINT* dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPrivateData(guid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPrivateData( const Guid& guid, UINT dataSize, const void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPrivateData(guid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPrivateDataInterface(const Guid& guid, const IUnknown* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPrivateDataInterface(guid, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// The depth-stencil-state object holds a description for depth-stencil 
    /// state that you can bind to the output-merger stage.
    /// </summary>
    class DepthStencilState : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DepthStencilState, DeviceChild, ID3D11DepthStencilState, ID3D11DeviceChild )
    public:
        void GetDesc(D3D11_DEPTH_STENCIL_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };


    /// <summary>
    /// The blend-state object holds a description for blending state 
    /// that you can bind to the output-merger stage.
    /// </summary>
    class BlendState : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(BlendState, DeviceChild, ID3D11BlendState, ID3D11DeviceChild )
    public:
        void GetDesc(D3D11_BLEND_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// The rasterizer-state object holds a description for rasterizer 
    /// state that you can bind to the rasterizer stage.
    /// </summary>
    class RasterizerState : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(RasterizerState, DeviceChild, ID3D11RasterizerState, ID3D11DeviceChild )
    public:
        void GetDesc(D3D11_RASTERIZER_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A resource object provides common actions on all resources.
    /// </summary>
    class Resource : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Resource, DeviceChild, ID3D11Resource, ID3D11DeviceChild )
    public:
        void GetType(D3D11_RESOURCE_DIMENSION* resourceDimension) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetType(resourceDimension);
        }

        void SetEvictionPriority( UINT evictionPriority) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetEvictionPriority(evictionPriority);
        }

        UINT GetEvictionPriority( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetEvictionPriority();
        }
    };

    /// <summary>
    /// A buffer object accesses a buffer resource, which is unstructured 
    /// memory. Buffers typically store vertex or index data.
    /// </summary>
    class Buffer : public Resource
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Buffer, Resource, ID3D11Buffer, ID3D11Resource )
    public:
        void GetDesc(D3D11_BUFFER_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A 1D texture object accesses texel data, which is structured memory.
    /// </summary>
    class Texture1D : public Resource
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Texture1D, Resource, ID3D11Texture1D, ID3D11Resource )
    public:
        void GetDesc(D3D11_TEXTURE1D_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A 2D texture object manages texel data, which is structured memory.
    /// </summary>
    class Texture2D : public Resource
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Texture2D, Resource, ID3D11Texture2D, ID3D11Resource )
    public:
        void GetDesc(D3D11_TEXTURE2D_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A 3D texture object accesses texel data, which is structured memory.
    /// </summary>
    class Texture3D : public Resource
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Texture3D, Resource, ID3D11Texture3D, ID3D11Resource )
    public:
        void GetDesc(D3D11_TEXTURE3D_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };


    /// <summary>
    /// A view object specifies the parts of a resource the pipeline can access during rendering.
    /// </summary>
    class View : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(View, DeviceChild, ID3D11View, ID3D11DeviceChild )
    public:
        void GetResource(ID3D11Resource** resource) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetResource(resource);
        }
    };

    /// <summary>
    /// A shader-resource-view object specifies the sub-resources a shader 
    /// can access during rendering. Examples of shader resources include 
    /// a constant buffer, a texture buffer, and a texture.
    /// </summary>
    class ShaderResourceView : public View
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ShaderResourceView, View, ID3D11ShaderResourceView, ID3D11View )
    public:
        void GetDesc(D3D11_SHADER_RESOURCE_VIEW_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A render-target-view object identifies the render-target 
    /// sub-resources that can be accessed during rendering.
    /// </summary>
    class RenderTargetView : public View
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(RenderTargetView, View, ID3D11RenderTargetView, ID3D11View )
    public:
        void GetDesc(D3D11_RENDER_TARGET_VIEW_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A depth-stencil-view object accesses a texture resource during 
    /// depth-stencil testing.
    /// </summary>
    class DepthStencilView : public View
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DepthStencilView, View, ID3D11DepthStencilView, ID3D11View )
    public:
        void GetDesc(D3D11_DEPTH_STENCIL_VIEW_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A view object specifies the parts of a resource the pipeline can 
    /// access during rendering.
    /// </summary>
    class UnorderedAccessView : public View
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(UnorderedAccessView, View, ID3D11UnorderedAccessView, ID3D11View )
    public:
        void GetDesc(D3D11_UNORDERED_ACCESS_VIEW_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A vertex-shader object manages an executable program (a vertex shader) 
    /// that controls the vertex-shader stage.
    /// </summary>
    class VertexShader : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VertexShader, DeviceChild, ID3D11VertexShader, ID3D11DeviceChild )
    public:

    };

    /// <summary>
    /// A hull-shader object manages an executable program (a hull shader) 
    /// that controls the hull-shader stage.
    /// </summary>
    class HullShader : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(HullShader, DeviceChild, ID3D11HullShader, ID3D11DeviceChild )
    public:

    };

    /// <summary>
    /// A domain-shader object manages an executable program (a domain shader) 
    /// that controls the domain-shader stage.
    /// </summary>
    class DomainShader : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DomainShader, DeviceChild, ID3D11DomainShader, ID3D11DeviceChild )
    public:

    };

    /// <summary>
    /// A geometry-shader object manages an executable program (a geometry shader) 
    /// that controls the geometry-shader stage.
    /// </summary>
    class GeometryShader : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(GeometryShader, DeviceChild, ID3D11GeometryShader, ID3D11DeviceChild )
    public:

    };

    /// <summary>
    /// A pixel-shader object manages an executable program (a pixel shader) 
    /// that controls the pixel-shader stage.
    /// </summary>
    class PixelShader : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(PixelShader, DeviceChild, ID3D11PixelShader, ID3D11DeviceChild )
    public:

    };

    /// <summary>
    /// A compute-shader object manages an executable program (a compute shader) 
    /// that controls the compute-shader stage.
    /// </summary>
    class ComputeShader : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ComputeShader, DeviceChild, ID3D11ComputeShader, ID3D11DeviceChild )
    public:

    };

    /// <summary>
    /// An input-layout interface holds a definition of how to feed 
    /// vertex data that is laid out in memory into the input-assembler 
    /// stage of the graphics pipeline.
    /// </summary>
    class InputLayout : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(InputLayout, DeviceChild, ID3D11InputLayout, ID3D11DeviceChild )
    public:

    };

    /// <summary>
    /// The sampler-state object holds a description for sampler state 
    /// that you can bind to any shader stage of the pipeline for 
    /// reference by texture sample operations.
    /// </summary>
    class SamplerState : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(SamplerState, DeviceChild, ID3D11SamplerState, ID3D11DeviceChild )
    public:
        void GetDesc(D3D11_SAMPLER_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// This object encapsulates methods for retrieving data from the GPU asynchronously.
    /// </summary>
    class Asynchronous : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Asynchronous, DeviceChild, ID3D11Asynchronous, ID3D11DeviceChild )
    public:
        UINT GetDataSize() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetDataSize();
        }
    };

    /// <summary>
    /// A query object queries information from the GPU.
    /// </summary>
    class Query : public Asynchronous
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Query, Asynchronous, ID3D11Query, ID3D11Asynchronous )
    public:
        void GetDesc(D3D11_QUERY_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// A predicate object determines whether geometry should be processed 
    /// depending on the results of a previous draw call.
    /// </summary>
    class Predicate : public Query
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Predicate, Query, ID3D11Predicate, ID3D11Query )
    public:
    };

    /// <summary>
    /// This object encapsulates methods for measuring GPU performance.
    /// </summary>
    class Counter : public Asynchronous
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Counter, Asynchronous, ID3D11Counter, ID3D11Asynchronous )
    public:
        void GetDesc(D3D11_COUNTER_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// This object encapsulates an HLSL class.
    /// </summary>
    class ClassInstance : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ClassInstance, DeviceChild, ID3D11ClassInstance, ID3D11DeviceChild )
    public:
        void GetClassLinkage(ID3D11ClassLinkage** ppLinkage) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetClassLinkage(ppLinkage);
        }

        void GetDesc(D3D11_CLASS_INSTANCE_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }

        void GetInstanceName(LPSTR instanceNameBuffer, SIZE_T* instanceNameBufferLength) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetInstanceName(instanceNameBuffer, instanceNameBufferLength);
        }

        void GetTypeName(LPSTR typeNameBuffer, SIZE_T* typeNameBufferLength) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetTypeName(typeNameBuffer, typeNameBufferLength);
        }
    };

    /// <summary>
    /// This object encapsulates an HLSL dynamic linkage.
    /// </summary>
    class ClassLinkage : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ClassLinkage, DeviceChild, ID3D11ClassLinkage, ID3D11DeviceChild )
    public:
        void GetClassInstance( LPCSTR classInstanceName, UINT instanceIndex, ID3D11ClassInstance** instance) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetClassInstance(classInstanceName, instanceIndex, instance);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateClassInstance( LPCSTR classTypeName, UINT constantBufferOffset, UINT constantVectorOffset, UINT textureOffset, UINT samplerOffset, ID3D11ClassInstance** instance) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateClassInstance(classTypeName, constantBufferOffset, constantVectorOffset, textureOffset, samplerOffset, instance);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// This object encapsulates a list of graphics commands for play back.
    /// </summary>
    class CommandList : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CommandList, DeviceChild, ID3D11CommandList, ID3D11DeviceChild )
    public:
        UINT GetContextFlags() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetContextFlags();
        }
    };

    /// <summary>
    /// Represents a device context which generates rendering commands.
    /// </summary>
    class DeviceContext : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DeviceContext, DeviceChild, ID3D11DeviceContext, ID3D11DeviceChild )
    public:
        void VSSetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer* const* constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSSetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void PSSetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView* const* shaderResourceViews) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSSetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void PSSetShader( ID3D11PixelShader* pixelShader, ID3D11ClassInstance* const* classInstances, UINT numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSSetShader(pixelShader, classInstances, numberOfClassInstances);
        }

        void PSSetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState* const* samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSSetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void VSSetShader( ID3D11VertexShader* vertexShader, ID3D11ClassInstance* const* classInstances, UINT numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSSetShader(vertexShader, classInstances, numberOfClassInstances);
        }

        void DrawIndexed( UINT indexCount, UINT startIndexLocation, INT baseVertexLocation) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
        }

        void Draw( UINT vertexCount, UINT startVertexLocation) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Draw(vertexCount, startVertexLocation);
        }

        template<bool NoExeptionOnInvalidArg = false>
        HRESULT Map( ID3D11Resource* resource, UINT subresource, D3D11_MAP mapType, UINT mapFlags, D3D11_MAPPED_SUBRESOURCE* mappedResource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Map(resource, subresource, mapType, mapFlags, mappedResource);
            if constexpr ( NoExeptionOnInvalidArg )
            {
                if ( hr == E_INVALIDARG )
                {
                    return E_INVALIDARG;
                }
            }
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return hr;
        }

        void Unmap( ID3D11Resource* resource, UINT subresource) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Unmap(resource, subresource);
        }

        void PSSetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer* const* constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSSetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void IASetInputLayout( ID3D11InputLayout* inputLayout) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->IASetInputLayout(inputLayout);
        }

        void IASetVertexBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer* const* vertexBuffers, const UINT* strides, const UINT* offsets) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->IASetVertexBuffers(startSlot, numberOfBuffers, vertexBuffers, strides, offsets);
        }

        void IASetIndexBuffer( ID3D11Buffer* indexBuffer, DXGI_FORMAT format, UINT offset) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->IASetIndexBuffer(indexBuffer, format, offset);
        }

        void DrawIndexedInstanced( UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
        }

        void DrawInstanced( UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation, UINT StartInstanceLocation) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation, StartInstanceLocation);
        }

        void GSSetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer* const* constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSSetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void GSSetShader( ID3D11GeometryShader* shader, ID3D11ClassInstance* const* classInstances, UINT numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSSetShader(shader, classInstances, numberOfClassInstances);
        }

        void IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->IASetPrimitiveTopology(topology);
        }

        void VSSetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView* const* shaderResourceViews) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSSetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void VSSetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState* const* samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSSetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void Begin( ID3D11Asynchronous* async) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Begin(async);
        }

        void End( ID3D11Asynchronous* async) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->End(async);
        }

        void GetData( ID3D11Asynchronous* async, void* data, UINT dataSize, UINT dataFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetData(async, data, dataSize, dataFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPredication( ID3D11Predicate* predicate, BOOL predicateValue) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetPredication(predicate, predicateValue);
        }

        void GSSetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView* const* shaderResourceViews) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSSetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void GSSetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState* const* samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSSetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void OMSetRenderTargets( UINT numberOfViews, ID3D11RenderTargetView* const* renderTargetViews, ID3D11DepthStencilView* depthStencilView) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OMSetRenderTargets(numberOfViews, renderTargetViews, depthStencilView);
        }

        void OMSetRenderTargetsAndUnorderedAccessViews( UINT numberOfRenderTargetViews, ID3D11RenderTargetView* const* renderTargetViews, ID3D11DepthStencilView* depthStencilView, UINT unorderedAccessViewsStartSlot, UINT numberOfUnorderedAccessViews, ID3D11UnorderedAccessView* const* unorderedAccessViews, const UINT* unorderedAccessViewsInitialCounts) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OMSetRenderTargetsAndUnorderedAccessViews(numberOfRenderTargetViews, renderTargetViews, depthStencilView, unorderedAccessViewsStartSlot, numberOfUnorderedAccessViews, unorderedAccessViews, unorderedAccessViewsInitialCounts);
        }

        void OMSetBlendState( ID3D11BlendState* blendState, const FLOAT blendFactor[4], UINT sampleMask) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OMSetBlendState(blendState, blendFactor, sampleMask);
        }

        void OMSetDepthStencilState( ID3D11DepthStencilState* depthStencilState, UINT stencilRef) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OMSetDepthStencilState(depthStencilState, stencilRef);
        }

        void SOSetTargets( UINT numberOfBuffers, ID3D11Buffer* const* streamOutputTargets, const UINT* offsets) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SOSetTargets(numberOfBuffers, streamOutputTargets, offsets);
        }

        void DrawAuto( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DrawAuto();
        }

        void DrawIndexedInstancedIndirect( ID3D11Buffer* bufferForArgs, UINT alignedByteOffsetForArgs) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DrawIndexedInstancedIndirect(bufferForArgs, alignedByteOffsetForArgs);
        }

        void DrawInstancedIndirect( ID3D11Buffer* bufferForArgs, UINT alignedByteOffsetForArgs) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DrawInstancedIndirect(bufferForArgs, alignedByteOffsetForArgs);
        }

        void Dispatch( UINT threadGroupCountX, UINT threadGroupCountY, UINT threadGroupCountZ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Dispatch(threadGroupCountX, threadGroupCountY, threadGroupCountZ);
        }

        void DispatchIndirect( ID3D11Buffer* bufferForArgs, UINT alignedByteOffsetForArgs) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DispatchIndirect(bufferForArgs, alignedByteOffsetForArgs);
        }

        void RSSetState( ID3D11RasterizerState* rasterizerState) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->RSSetState(rasterizerState);
        }

        void RSSetViewports( UINT numberOfViewports, const D3D11_VIEWPORT* viewports) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->RSSetViewports(numberOfViewports, viewports);
        }

        void RSSetScissorRects( UINT numberOfRects, const D3D11_RECT* rects) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->RSSetScissorRects(numberOfRects, rects);
        }

        void CopySubresourceRegion( ID3D11Resource* destinationResource, UINT destinationSubresource, UINT destinationX, UINT destinationY, UINT destinationZ, ID3D11Resource* sourceResource, UINT sourceSubresource, const D3D11_BOX* sourceBox) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CopySubresourceRegion(destinationResource, destinationSubresource, destinationX, destinationY, destinationZ, sourceResource, sourceSubresource, sourceBox);
        }

        void CopyResource( ID3D11Resource* destinationResource, ID3D11Resource* sourceResource) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CopyResource(destinationResource, sourceResource);
        }

        void UpdateSubresource( ID3D11Resource* destinationResource, UINT destinationSubresource, const D3D11_BOX* destinationBox, const void* sourceData, UINT sourceRowPitch, UINT sourceDepthPitch) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->UpdateSubresource(destinationResource, destinationSubresource, destinationBox, sourceData, sourceRowPitch, sourceDepthPitch);
        }

        void CopyStructureCount( ID3D11Buffer* destinationBuffer, UINT destinationAlignedByteOffset, ID3D11UnorderedAccessView* sourceView) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CopyStructureCount(destinationBuffer, destinationAlignedByteOffset, sourceView);
        }

        void ClearRenderTargetView( ID3D11RenderTargetView* renderTargetView, const FLOAT colorRGBA[4]) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearRenderTargetView(renderTargetView, colorRGBA);
        }

        void ClearUnorderedAccessViewUint( ID3D11UnorderedAccessView* unorderedAccessView, const UINT values[4]) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearUnorderedAccessViewUint(unorderedAccessView, values);
        }

        void ClearUnorderedAccessViewFloat( ID3D11UnorderedAccessView* unorderedAccessView, const FLOAT values[4]) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearUnorderedAccessViewFloat(unorderedAccessView, values);
        }

        void ClearDepthStencilView( ID3D11DepthStencilView* depthStencilView, UINT clearFlags, FLOAT depth, UINT8 stencil) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearDepthStencilView(depthStencilView, clearFlags, depth, stencil);
        }

        void GenerateMips( ID3D11ShaderResourceView* shaderResourceView) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GenerateMips(shaderResourceView);
        }

        void SetResourceMinLOD( ID3D11Resource* resource, FLOAT minLOD) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetResourceMinLOD(resource, minLOD);
        }

        FLOAT GetResourceMinLOD( ID3D11Resource* resource) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetResourceMinLOD(resource);
        }

        void ResolveSubresource( ID3D11Resource* destinationResource, UINT destinationSubresource, ID3D11Resource* sourceResource, UINT sourceSubresource, DXGI_FORMAT format) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResolveSubresource(destinationResource, destinationSubresource, sourceResource, sourceSubresource, format);
        }

        void ExecuteCommandList( ID3D11CommandList* commandList, BOOL restoreContextState) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ExecuteCommandList(commandList, restoreContextState);
        }

        void HSSetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView* const* shaderResourceViews) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSSetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void HSSetShader( ID3D11HullShader* hullShader, ID3D11ClassInstance* const* classInstances, UINT numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSSetShader(hullShader, classInstances, numberOfClassInstances);
        }

        void HSSetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState* const* samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSSetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void HSSetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer* const* constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSSetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void DSSetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView* const* shaderResourceViews) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSSetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void DSSetShader( ID3D11DomainShader* domainShader, ID3D11ClassInstance* const* classInstances, UINT numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSSetShader(domainShader, classInstances, numberOfClassInstances);
        }

        void DSSetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState* const* samplers) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSSetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void DSSetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer* const* constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSSetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void CSSetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView* const* shaderResourceViews) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSSetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void CSSetUnorderedAccessViews( UINT startSlot, UINT numberOfunorderedAccessViews, ID3D11UnorderedAccessView* const* unorderedAccessViews, const UINT* unorderedAccessViewsInitialCounts) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSSetUnorderedAccessViews(startSlot, numberOfunorderedAccessViews, unorderedAccessViews, unorderedAccessViewsInitialCounts);
        }

        void CSSetShader( ID3D11ComputeShader* computeShader, ID3D11ClassInstance* const* classInstances, UINT numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSSetShader(computeShader, classInstances, numberOfClassInstances);
        }

        void CSSetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState* const* samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSSetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void CSSetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer* const* constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSSetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void VSGetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer** constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSGetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void PSGetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView** shaderResourceViews) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSGetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void PSGetShader( ID3D11PixelShader** pixelShader, ID3D11ClassInstance** classInstances, UINT* numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSGetShader(pixelShader, classInstances, numberOfClassInstances);
        }

        void PSGetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState** samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSGetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void VSGetShader( ID3D11VertexShader** ppVertexShader, ID3D11ClassInstance** classInstances, UINT* numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSGetShader(ppVertexShader, classInstances, numberOfClassInstances);
        }

        void PSGetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer** constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSGetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void IAGetInputLayout( ID3D11InputLayout** inputLayout) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->IAGetInputLayout(inputLayout);
        }

        void IAGetVertexBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer** vertexBuffers, UINT* strides, UINT* offsets) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->IAGetVertexBuffers(startSlot, numberOfBuffers, vertexBuffers, strides, offsets);
        }

        void IAGetIndexBuffer( ID3D11Buffer** indexBuffer, DXGI_FORMAT* format, UINT* offset) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->IAGetIndexBuffer(indexBuffer, format, offset);
        }

        void GSGetConstantBuffers( UINT startSlot, UINT numberOfBuffers, ID3D11Buffer** constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSGetConstantBuffers(startSlot, numberOfBuffers, constantBuffers);
        }

        void GSGetShader( ID3D11GeometryShader** geometryShader, ID3D11ClassInstance** classInstances, UINT* numberOfClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSGetShader(geometryShader, classInstances, numberOfClassInstances);
        }

        void IAGetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY* topology) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->IAGetPrimitiveTopology(topology);
        }

        void VSGetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView** shaderResourceViews) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSGetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void VSGetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState** samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSGetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void GetPredication( ID3D11Predicate** predicate, BOOL* predicateValue) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetPredication(predicate, predicateValue);
        }

        void GSGetShaderResources( UINT startSlot, UINT numberOfViews, ID3D11ShaderResourceView** shaderResourceViews) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSGetShaderResources(startSlot, numberOfViews, shaderResourceViews);
        }

        void GSGetSamplers( UINT startSlot, UINT numberOfSamplers, ID3D11SamplerState** samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSGetSamplers(startSlot, numberOfSamplers, samplers);
        }

        void OMGetRenderTargets( UINT numberOfViews, ID3D11RenderTargetView** renderTargetViews, ID3D11DepthStencilView** depthStencilView) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OMGetRenderTargets(numberOfViews, renderTargetViews, depthStencilView);
        }

        void OMGetRenderTargetsAndUnorderedAccessViews( UINT numberOfRenderTargetViews, ID3D11RenderTargetView** renderTargetViews, ID3D11DepthStencilView** depthStencilView, UINT unorderedAccessViewsStartSlot, UINT numberOfUnorderedAccessViews, ID3D11UnorderedAccessView** unorderedAccessViews) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OMGetRenderTargetsAndUnorderedAccessViews(numberOfRenderTargetViews, renderTargetViews, depthStencilView, unorderedAccessViewsStartSlot, numberOfUnorderedAccessViews, unorderedAccessViews);
        }

        void OMGetBlendState( ID3D11BlendState** blendState, FLOAT blendFactor[4], UINT* sampleMask) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OMGetBlendState(blendState, blendFactor, sampleMask);
        }

        void OMGetDepthStencilState( ID3D11DepthStencilState** depthStencilState, UINT* stencilRef) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OMGetDepthStencilState(depthStencilState, stencilRef);
        }

        void SOGetTargets( UINT numBuffers, ID3D11Buffer** soTargets) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SOGetTargets(numBuffers, soTargets);
        }

        void RSGetState( ID3D11RasterizerState** rasterizerState) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->RSGetState(rasterizerState);
        }

        void RSGetViewports( UINT* numViewports, D3D11_VIEWPORT* viewports) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->RSGetViewports(numViewports, viewports);
        }

        void RSGetScissorRects( UINT* numRects, D3D11_RECT* rects) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->RSGetScissorRects(numRects, rects);
        }

        void HSGetShaderResources( UINT startSlot, UINT numViews, ID3D11ShaderResourceView** shaderResourceViews) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSGetShaderResources(startSlot, numViews, shaderResourceViews);
        }

        void HSGetShader( ID3D11HullShader** hullShader, ID3D11ClassInstance** classInstances, UINT* numClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSGetShader(hullShader, classInstances, numClassInstances);
        }

        void HSGetSamplers( UINT startSlot, UINT numSamplers, ID3D11SamplerState** samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSGetSamplers(startSlot, numSamplers, samplers);
        }

        void HSGetConstantBuffers( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSGetConstantBuffers(startSlot, numBuffers, constantBuffers);
        }

        void DSGetShaderResources( UINT startSlot, UINT numViews, ID3D11ShaderResourceView** shaderResourceViews) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSGetShaderResources(startSlot, numViews, shaderResourceViews);
        }

        void DSGetShader( ID3D11DomainShader** domainShader, ID3D11ClassInstance** classInstances, UINT* numClassInstances) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSGetShader(domainShader, classInstances, numClassInstances);
        }

        void DSGetSamplers( UINT startSlot, UINT numSamplers, ID3D11SamplerState** samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSGetSamplers(startSlot, numSamplers, samplers);
        }

        void DSGetConstantBuffers( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSGetConstantBuffers(startSlot, numBuffers, constantBuffers);
        }

        void CSGetShaderResources( UINT startSlot, UINT numViews, ID3D11ShaderResourceView** shaderResourceViews) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSGetShaderResources(startSlot, numViews, shaderResourceViews);
        }

        void CSGetUnorderedAccessViews( UINT startSlot, UINT numUAVs, ID3D11UnorderedAccessView** unorderedAccessViews) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSGetUnorderedAccessViews(startSlot, numUAVs, unorderedAccessViews);
        }

        void CSGetShader( ID3D11ComputeShader** computeShader, ID3D11ClassInstance** classInstances, UINT* numClassInstances) const 
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSGetShader(computeShader, classInstances, numClassInstances);
        }

        void CSGetSamplers( UINT startSlot, UINT numSamplers, ID3D11SamplerState** samplers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSGetSamplers(startSlot, numSamplers, samplers);
        }

        void CSGetConstantBuffers( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSGetConstantBuffers(startSlot, numBuffers, constantBuffers);
        }

        void ClearState( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearState();
        }

        void Flush( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Flush();
        }

        D3D11_DEVICE_CONTEXT_TYPE GetType( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetType();
        }

        UINT GetContextFlags( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetContextFlags();
        }

        void FinishCommandList( BOOL restoreDeferredContextState, ID3D11CommandList** commandList) const 
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FinishCommandList(restoreDeferredContextState, commandList);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Represents a hardware-accelerated video decoder for Microsoft Direct3D 11.
    /// </summary>
    class VideoDecoder : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoDecoder, DeviceChild, ID3D11VideoDecoder, ID3D11DeviceChild )
    public:
        void GetCreationParameters( D3D11_VIDEO_DECODER_DESC* videoDecoderDesc, D3D11_VIDEO_DECODER_CONFIG* videoDecoderConfig) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCreationParameters(videoDecoderDesc, videoDecoderConfig);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDriverHandle( HANDLE* driverHandle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDriverHandle(driverHandle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Enumerates the video processor capabilities of a Microsoft Direct3D 11 device.
    /// </summary>
    class VideoProcessorEnumerator : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoProcessorEnumerator, DeviceChild, ID3D11VideoProcessorEnumerator, ID3D11DeviceChild )
    public:
        void GetVideoProcessorContentDesc( D3D11_VIDEO_PROCESSOR_CONTENT_DESC* contentDesc) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorContentDesc(contentDesc);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckVideoProcessorFormat( DXGI_FORMAT format, UINT* flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckVideoProcessorFormat(format, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorCaps( D3D11_VIDEO_PROCESSOR_CAPS* caps) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorCaps(caps);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorRateConversionCaps( UINT typeIndex, D3D11_VIDEO_PROCESSOR_RATE_CONVERSION_CAPS* caps) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorRateConversionCaps(typeIndex, caps);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorCustomRate( UINT typeIndex, UINT customRateIndex, D3D11_VIDEO_PROCESSOR_CUSTOM_RATE* rate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorCustomRate(typeIndex, customRateIndex, rate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorFilterRange( D3D11_VIDEO_PROCESSOR_FILTER filter, D3D11_VIDEO_PROCESSOR_FILTER_RANGE* range) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorFilterRange(filter, range);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Represents a video processor for Microsoft Direct3D 11.
    /// </summary>
    class VideoProcessor : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoProcessor, DeviceChild, ID3D11VideoProcessor, ID3D11DeviceChild )
    public:
        void GetContentDesc(D3D11_VIDEO_PROCESSOR_CONTENT_DESC* videoProcessorContentDesc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetContentDesc(videoProcessorContentDesc);
        }

        void GetRateConversionCaps( D3D11_VIDEO_PROCESSOR_RATE_CONVERSION_CAPS* caps) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetRateConversionCaps(caps);
        }
    };

    /// <summary>
    /// Provides a communication channel with the graphics driver or the Microsoft Direct3D runtime.
    /// </summary>
    class AuthenticatedChannel : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AuthenticatedChannel, DeviceChild, ID3D11AuthenticatedChannel, ID3D11DeviceChild )
    public:
        void GetCertificateSize(UINT* certificateSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCertificateSize(certificateSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCertificate( UINT certificateSize, BYTE* certificate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCertificate(certificateSize, certificate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetChannelHandle( HANDLE* channelHandle) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetChannelHandle(channelHandle);
        }
    };

    /// <summary>
    /// Represents a cryptographic session.
    /// </summary>
    class CryptoSession : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CryptoSession, DeviceChild, ID3D11CryptoSession, ID3D11DeviceChild )
    public:
        void GetCryptoType(Guid* cryptoType) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetCryptoType((GUID*)cryptoType);
        }

        void GetDecoderProfile(Guid* decoderProfile) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDecoderProfile((GUID*)decoderProfile);
        }

        void GetCertificateSize(UINT* certificateSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCertificateSize(certificateSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCertificate(UINT certificateSize, BYTE* certificate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCertificate(certificateSize, certificate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCryptoSessionHandle(HANDLE* cryptoSessionHandle) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetCryptoSessionHandle(cryptoSessionHandle);
        }
    };

    /// <summary>
    /// Identifies the output surfaces that can be accessed during video decoding.
    /// </summary>
    class VideoDecoderOutputView : public View
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoDecoderOutputView, View, ID3D11VideoDecoderOutputView, ID3D11View )
    public:
        void GetDesc(D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// Identifies the input surfaces that can be accessed during video processing.
    /// </summary>
    class VideoProcessorInputView : public View
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoProcessorInputView, View, ID3D11VideoProcessorInputView, ID3D11View )
    public:
        void GetDesc(D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// Identifies the output surfaces that can be accessed during video processing.
    /// </summary>
    class VideoProcessorOutputView : public View
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoProcessorOutputView, View, ID3D11VideoProcessorOutputView, ID3D11View )
    public:
        void GetDesc(D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc(desc);
        }
    };

    /// <summary>
    /// Provides the video functionality of a Microsoft Direct3D 11 device.
    /// </summary>
    class VideoContext : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoContext, DeviceChild, ID3D11VideoContext, ID3D11DeviceChild )
    public:
        void GetDecoderBuffer( ID3D11VideoDecoder* decoder, D3D11_VIDEO_DECODER_BUFFER_TYPE type, UINT* bufferSize, void** buffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDecoderBuffer(decoder, type, bufferSize, buffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReleaseDecoderBuffer( ID3D11VideoDecoder* decoder, D3D11_VIDEO_DECODER_BUFFER_TYPE type) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReleaseDecoderBuffer(decoder, type);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DecoderBeginFrame( ID3D11VideoDecoder* decoder, ID3D11VideoDecoderOutputView* view, UINT contentKeySize, const void* contentKey) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DecoderBeginFrame(decoder, view, contentKeySize, contentKey);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DecoderEndFrame( ID3D11VideoDecoder* decoder) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DecoderEndFrame(decoder);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SubmitDecoderBuffers( ID3D11VideoDecoder* decoder, UINT numBuffers, const D3D11_VIDEO_DECODER_BUFFER_DESC* bufferDesc) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SubmitDecoderBuffers(decoder, numBuffers, bufferDesc);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DecoderExtension( ID3D11VideoDecoder* decoder, const D3D11_VIDEO_DECODER_EXTENSION* extensionData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DecoderExtension(decoder, extensionData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void VideoProcessorSetOutputTargetRect( ID3D11VideoProcessor* videoProcessor, BOOL enable, const RECT* rect) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputTargetRect(videoProcessor, enable, rect);
        }

        void VideoProcessorSetOutputBackgroundColor( ID3D11VideoProcessor* videoProcessor, BOOL YCbCr, const D3D11_VIDEO_COLOR* color) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputBackgroundColor(videoProcessor, YCbCr, color);
        }

        void VideoProcessorSetOutputColorSpace( ID3D11VideoProcessor* videoProcessor, const D3D11_VIDEO_PROCESSOR_COLOR_SPACE* colorSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputColorSpace(videoProcessor, colorSpace);
        }

        void VideoProcessorSetOutputAlphaFillMode( ID3D11VideoProcessor* videoProcessor, D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE alphaFillMode, UINT streamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputAlphaFillMode(videoProcessor, alphaFillMode, streamIndex);
        }

        void VideoProcessorSetOutputConstriction( ID3D11VideoProcessor* videoProcessor, BOOL enable, SIZE size) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputConstriction(videoProcessor, enable, size);
        }

        void VideoProcessorSetOutputStereoMode( ID3D11VideoProcessor* videoProcessor, BOOL enable) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputStereoMode(videoProcessor, enable);
        }

        void VideoProcessorSetOutputExtension( ID3D11VideoProcessor* videoProcessor, const GUID* extensionGuid, UINT dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->VideoProcessorSetOutputExtension(videoProcessor, extensionGuid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void VideoProcessorGetOutputTargetRect( ID3D11VideoProcessor* videoProcessor, BOOL* enabled, RECT* rect) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputTargetRect(videoProcessor, enabled, rect);
        }

        void VideoProcessorGetOutputBackgroundColor( ID3D11VideoProcessor* videoProcessor, BOOL* YCbCr, D3D11_VIDEO_COLOR* color) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputBackgroundColor(videoProcessor, YCbCr, color);
        }

        void VideoProcessorGetOutputColorSpace( ID3D11VideoProcessor* videoProcessor, D3D11_VIDEO_PROCESSOR_COLOR_SPACE* colorSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputColorSpace(videoProcessor, colorSpace);
        }

        void VideoProcessorGetOutputAlphaFillMode( ID3D11VideoProcessor* videoProcessor, D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE* alphaFillMode, UINT* streamIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputAlphaFillMode(videoProcessor, alphaFillMode, streamIndex);
        }

        void VideoProcessorGetOutputConstriction( ID3D11VideoProcessor* videoProcessor, BOOL* enabled, SIZE* size) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputConstriction(videoProcessor, enabled, size);
        }

        void VideoProcessorGetOutputStereoMode( ID3D11VideoProcessor* videoProcessor, BOOL* enabled) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputStereoMode(videoProcessor, enabled);
        }

        void VideoProcessorGetOutputExtension( ID3D11VideoProcessor* videoProcessor, const GUID* extensionGuid, UINT dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->VideoProcessorGetOutputExtension(videoProcessor, extensionGuid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void VideoProcessorSetStreamFrameFormat( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, D3D11_VIDEO_FRAME_FORMAT frameFormat) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamFrameFormat(videoProcessor, streamIndex, frameFormat);
        }

        void VideoProcessorSetStreamColorSpace( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, const D3D11_VIDEO_PROCESSOR_COLOR_SPACE* colorSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamColorSpace(videoProcessor, streamIndex, colorSpace);
        }

        void VideoProcessorSetStreamOutputRate( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, D3D11_VIDEO_PROCESSOR_OUTPUT_RATE outputRate, BOOL repeatFrame, const DXGI_RATIONAL* customRate) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamOutputRate(videoProcessor, streamIndex, outputRate, repeatFrame, customRate);
        }

        void VideoProcessorSetStreamSourceRect( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable, const RECT* rect) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamSourceRect(videoProcessor, streamIndex, enable, rect);
        }

        void VideoProcessorSetStreamDestRect( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable, const RECT* rect) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamDestRect(videoProcessor, streamIndex, enable, rect);
        }

        void VideoProcessorSetStreamAlpha( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable, FLOAT alpha) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamAlpha(videoProcessor, streamIndex, enable, alpha);
        }

        void VideoProcessorSetStreamPalette( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, UINT count, const UINT* entries) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamPalette(videoProcessor, streamIndex, count, entries);
        }

        void VideoProcessorSetStreamPixelAspectRatio( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable, const DXGI_RATIONAL* sourceAspectRatio, const DXGI_RATIONAL* destinationAspectRatio) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamPixelAspectRatio(videoProcessor, streamIndex, enable, sourceAspectRatio, destinationAspectRatio);
        }

        void VideoProcessorSetStreamLumaKey( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable, FLOAT lower, FLOAT upper) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamLumaKey(videoProcessor, streamIndex, enable, lower, upper);
        }

        void VideoProcessorSetStreamStereoFormat( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable, D3D11_VIDEO_PROCESSOR_STEREO_FORMAT format, BOOL leftViewFrame0, BOOL baseViewFrame0, D3D11_VIDEO_PROCESSOR_STEREO_FLIP_MODE flipMode, int monoOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamStereoFormat(videoProcessor, streamIndex, enable, format, leftViewFrame0, baseViewFrame0, flipMode, monoOffset);
        }

        void VideoProcessorSetStreamAutoProcessingMode( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamAutoProcessingMode(videoProcessor, streamIndex, enable);
        }

        void VideoProcessorSetStreamFilter( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, D3D11_VIDEO_PROCESSOR_FILTER filter, BOOL enable, int level) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamFilter(videoProcessor, streamIndex, filter, enable, level);
        }

        void VideoProcessorSetStreamExtension( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, const GUID* extensionGuid, UINT dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->VideoProcessorSetStreamExtension(videoProcessor, streamIndex, extensionGuid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void VideoProcessorGetStreamFrameFormat( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, D3D11_VIDEO_FRAME_FORMAT* frameFormat) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamFrameFormat(videoProcessor, streamIndex, frameFormat);
        }

        void VideoProcessorGetStreamColorSpace( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, D3D11_VIDEO_PROCESSOR_COLOR_SPACE* colorSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamColorSpace(videoProcessor, streamIndex, colorSpace);
        }

        void VideoProcessorGetStreamOutputRate( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, D3D11_VIDEO_PROCESSOR_OUTPUT_RATE* outputRate, BOOL* repeatFrame, DXGI_RATIONAL* customRate) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamOutputRate(videoProcessor, streamIndex, outputRate, repeatFrame, customRate);
        }

        void VideoProcessorGetStreamSourceRect( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enabled, RECT* rect) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamSourceRect(videoProcessor, streamIndex, enabled, rect);
        }

        void VideoProcessorGetStreamDestRect( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enabled, RECT* rect) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamDestRect(videoProcessor, streamIndex, enabled, rect);
        }

        void VideoProcessorGetStreamAlpha( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enabled, FLOAT* alpha) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamAlpha(videoProcessor, streamIndex, enabled, alpha);
        }

        void VideoProcessorGetStreamPalette( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, UINT count, UINT* entries) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamPalette(videoProcessor, streamIndex, count, entries);
        }

        void VideoProcessorGetStreamPixelAspectRatio( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enabled, DXGI_RATIONAL* sourceAspectRatio, DXGI_RATIONAL* destinationAspectRatio) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamPixelAspectRatio(videoProcessor, streamIndex, enabled, sourceAspectRatio, destinationAspectRatio);
        }

        void VideoProcessorGetStreamLumaKey( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enabled, FLOAT* lower, FLOAT* upper) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamLumaKey(videoProcessor, streamIndex, enabled, lower, upper);
        }

        void VideoProcessorGetStreamStereoFormat( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enable, D3D11_VIDEO_PROCESSOR_STEREO_FORMAT* format, BOOL* leftViewFrame0, BOOL* baseViewFrame0, D3D11_VIDEO_PROCESSOR_STEREO_FLIP_MODE* flipMode, int* monoOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamStereoFormat(videoProcessor, streamIndex, enable, format, leftViewFrame0, baseViewFrame0, flipMode, monoOffset);
        }

        void VideoProcessorGetStreamAutoProcessingMode( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enabled) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamAutoProcessingMode(videoProcessor, streamIndex, enabled);
        }

        void VideoProcessorGetStreamFilter( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, D3D11_VIDEO_PROCESSOR_FILTER filter, BOOL* enabled, int* level) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamFilter(videoProcessor, streamIndex, filter, enabled, level);
        }

        void VideoProcessorGetStreamExtension( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, const GUID* extensionGuid, UINT dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->VideoProcessorGetStreamExtension(videoProcessor, streamIndex, extensionGuid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void VideoProcessorBlt( ID3D11VideoProcessor* videoProcessor, ID3D11VideoProcessorOutputView* view, UINT outputFrame, UINT streamCount, const D3D11_VIDEO_PROCESSOR_STREAM* streams) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->VideoProcessorBlt(videoProcessor, view, outputFrame, streamCount, streams);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NegotiateCryptoSessionKeyExchange( ID3D11CryptoSession* cryptoSession, UINT dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NegotiateCryptoSessionKeyExchange(cryptoSession, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EncryptionBlt( ID3D11CryptoSession* cryptoSession, ID3D11Texture2D* srcSurface, ID3D11Texture2D* dstSurface, UINT ivSize, void* pIV) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EncryptionBlt(cryptoSession, srcSurface, dstSurface, ivSize, pIV);
        }

        void DecryptionBlt( ID3D11CryptoSession* cryptoSession, ID3D11Texture2D* srcSurface, ID3D11Texture2D* dstSurface, D3D11_ENCRYPTED_BLOCK_INFO* encryptedBlockInfo, UINT contentKeySize, const void* contentKey, UINT ivSize, void* pIV) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DecryptionBlt(cryptoSession, srcSurface, dstSurface, encryptedBlockInfo, contentKeySize, contentKey, ivSize, pIV);
        }

        void StartSessionKeyRefresh( ID3D11CryptoSession* cryptoSession, UINT randomNumberSize, void* randomNumber) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->StartSessionKeyRefresh(cryptoSession, randomNumberSize, randomNumber);
        }

        void FinishSessionKeyRefresh( ID3D11CryptoSession* cryptoSession) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->FinishSessionKeyRefresh(cryptoSession);
        }

        void GetEncryptionBltKey( ID3D11CryptoSession* cryptoSession, UINT keySize, void* readbackKey) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetEncryptionBltKey(cryptoSession, keySize, readbackKey);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NegotiateAuthenticatedChannelKeyExchange( ID3D11AuthenticatedChannel* channel, UINT dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NegotiateAuthenticatedChannelKeyExchange(channel, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryAuthenticatedChannel( ID3D11AuthenticatedChannel* channel, UINT inputSize, const void* input, UINT outputSize, void* output) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryAuthenticatedChannel(channel, inputSize, input, outputSize, output);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ConfigureAuthenticatedChannel( ID3D11AuthenticatedChannel* channel, UINT inputSize, const void* input, D3D11_AUTHENTICATED_CONFIGURE_OUTPUT* output) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ConfigureAuthenticatedChannel(channel, inputSize, input, output);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void VideoProcessorSetStreamRotation( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable, D3D11_VIDEO_PROCESSOR_ROTATION rotation) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamRotation(videoProcessor, streamIndex, enable, rotation);
        }

        void VideoProcessorGetStreamRotation( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enable, D3D11_VIDEO_PROCESSOR_ROTATION* rotation) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamRotation(videoProcessor, streamIndex, enable, rotation);
        }
    };

    /// <summary>
    /// Provides the video decoding and video processing capabilities of a Microsoft Direct3D 11 device.
    /// </summary>
    class VideoDevice : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoDevice, Unknown, ID3D11VideoDevice, IUnknown )
    public:
        void CreateVideoDecoder( const D3D11_VIDEO_DECODER_DESC* videoDesc, const D3D11_VIDEO_DECODER_CONFIG* config, ID3D11VideoDecoder** decoder) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVideoDecoder(videoDesc, config, decoder);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoProcessor( ID3D11VideoProcessorEnumerator* videoProcessorEnumerator, UINT rateConversionIndex, ID3D11VideoProcessor** videoProcessor) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVideoProcessor(videoProcessorEnumerator, rateConversionIndex, videoProcessor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateAuthenticatedChannel( D3D11_AUTHENTICATED_CHANNEL_TYPE channelType, ID3D11AuthenticatedChannel** authenticatedChannel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateAuthenticatedChannel(channelType, authenticatedChannel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateCryptoSession( const GUID* cryptoType, const GUID* decoderProfile, const GUID* keyExchangeType, ID3D11CryptoSession** cryptoSession) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateCryptoSession(cryptoType, decoderProfile, keyExchangeType, cryptoSession);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoDecoderOutputView( ID3D11Resource* resource, const D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC* videoDecoderOutputViewDesc, ID3D11VideoDecoderOutputView** ppVDOVView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVideoDecoderOutputView(resource, videoDecoderOutputViewDesc, ppVDOVView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoProcessorInputView( ID3D11Resource* resource, ID3D11VideoProcessorEnumerator* videoProcessorEnumerator, const D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC* videoProcessorInputViewDesc, ID3D11VideoProcessorInputView** videoProcessorInputView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVideoProcessorInputView(resource, videoProcessorEnumerator, videoProcessorInputViewDesc, videoProcessorInputView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoProcessorOutputView( ID3D11Resource* resource, ID3D11VideoProcessorEnumerator* videoProcessorEnumerator, const D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC* videoProcessorOutputViewDesc, ID3D11VideoProcessorOutputView** videoProcessorOutputView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVideoProcessorOutputView(resource, videoProcessorEnumerator, videoProcessorOutputViewDesc, videoProcessorOutputView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoProcessorEnumerator( const D3D11_VIDEO_PROCESSOR_CONTENT_DESC* videoProcessorContentDesc, ID3D11VideoProcessorEnumerator** videoProcessorEnumerator) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVideoProcessorEnumerator(videoProcessorContentDesc, videoProcessorEnumerator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        UINT GetVideoDecoderProfileCount() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetVideoDecoderProfileCount();
        }

        void GetVideoDecoderProfile( UINT index, GUID* decoderProfileId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoDecoderProfile(index, decoderProfileId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckVideoDecoderFormat( const GUID* decoderProfileId, DXGI_FORMAT format, BOOL* supported) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckVideoDecoderFormat(decoderProfileId, format, supported);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoDecoderConfigCount( const D3D11_VIDEO_DECODER_DESC* videoDecoderDesc, UINT* count) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoDecoderConfigCount(videoDecoderDesc, count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoDecoderConfig( const D3D11_VIDEO_DECODER_DESC* videoDecoderDesc, UINT index, D3D11_VIDEO_DECODER_CONFIG* videoDecoderConfig) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoDecoderConfig(videoDecoderDesc, index, videoDecoderConfig);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetContentProtectionCaps( const GUID* cryptoTypeId, const GUID* decoderProfileId, D3D11_VIDEO_CONTENT_PROTECTION_CAPS* caps) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetContentProtectionCaps(cryptoTypeId, decoderProfileId, caps);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckCryptoKeyExchange( const GUID* cryptoTypeId, const GUID* decoderProfileId, UINT index, GUID* keyExchangeTypeId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckCryptoKeyExchange(cryptoTypeId, decoderProfileId, index, keyExchangeTypeId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPrivateData( const Guid& guid, UINT dataSize, const void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPrivateData(guid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPrivateDataInterface( const Guid& guid, const IUnknown* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPrivateDataInterface(guid, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// The device object represents a virtual adapter; it is used to create resources.
    /// </summary>
    class Device : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device, Unknown, ID3D11Device, IUnknown )
    public:
        void CreateBuffer( const D3D11_BUFFER_DESC* bufferDesc, const D3D11_SUBRESOURCE_DATA* initialData, ID3D11Buffer** buffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateBuffer(bufferDesc, initialData, buffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        Buffer CreateBuffer( const D3D11_BUFFER_DESC* bufferDesc, const D3D11_SUBRESOURCE_DATA* initialData = nullptr ) const
        {
            ID3D11Buffer* itf = nullptr;
            CreateBuffer( bufferDesc, initialData, &itf );
            return Buffer( itf );
        }


        void CreateTexture1D( const D3D11_TEXTURE1D_DESC* texture1dDesc, const D3D11_SUBRESOURCE_DATA* initialData, ID3D11Texture1D** texture1D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTexture1D(texture1dDesc, initialData, texture1D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        Texture1D CreateTexture1D( const D3D11_TEXTURE1D_DESC* texture1dDesc, const D3D11_SUBRESOURCE_DATA* initialData = nullptr ) const
        {
            ID3D11Texture1D* itf = nullptr;
            CreateTexture1D( texture1dDesc, initialData, &itf );
            return Texture1D( itf );
        }

        void CreateTexture2D( const D3D11_TEXTURE2D_DESC* texture2dDesc, const D3D11_SUBRESOURCE_DATA* initialData, ID3D11Texture2D** texture2D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTexture2D(texture2dDesc, initialData, texture2D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        Texture2D CreateTexture2D( const D3D11_TEXTURE2D_DESC* texture2dDesc, const D3D11_SUBRESOURCE_DATA* initialData = nullptr ) const
        {
            ID3D11Texture2D* itf = nullptr;
            CreateTexture2D( texture2dDesc, initialData, &itf );
            return Texture2D( itf );
        }


        void CreateTexture3D( const D3D11_TEXTURE3D_DESC* texture3dDesc, const D3D11_SUBRESOURCE_DATA* initialData, ID3D11Texture3D** texture3D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTexture3D(texture3dDesc, initialData, texture3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        Texture3D CreateTexture3D( const D3D11_TEXTURE3D_DESC* texture3dDesc, const D3D11_SUBRESOURCE_DATA* initialData = nullptr ) const
        {
            ID3D11Texture3D* itf = nullptr;
            CreateTexture3D( texture3dDesc, initialData, &itf );
            return Texture3D( itf );
        }


        void CreateShaderResourceView( ID3D11Resource* resource, const D3D11_SHADER_RESOURCE_VIEW_DESC* shaderResourceViewDesc, ID3D11ShaderResourceView** shaderResourceView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateShaderResourceView(resource, shaderResourceViewDesc, shaderResourceView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        ShaderResourceView CreateShaderResourceView( const Resource& resource, const D3D11_SHADER_RESOURCE_VIEW_DESC* shaderResourceViewDesc ) const
        {
            ID3D11ShaderResourceView* itf = nullptr;
            CreateShaderResourceView( resource.GetInterfacePointer<ID3D11Resource>(), shaderResourceViewDesc, &itf );
            return ShaderResourceView( itf );
        }


        void CreateUnorderedAccessView( ID3D11Resource* resource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* unorderedAccessViewDesc, ID3D11UnorderedAccessView** unorderedAccessView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateUnorderedAccessView(resource, unorderedAccessViewDesc, unorderedAccessView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        UnorderedAccessView CreateUnorderedAccessView( const Resource& resource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* unorderedAccessViewDesc ) const
        {
            ID3D11UnorderedAccessView* itf = nullptr;
            CreateUnorderedAccessView( resource.GetInterfacePointer<ID3D11Resource>( ), unorderedAccessViewDesc, &itf );
            return UnorderedAccessView( itf );
        }


        void CreateRenderTargetView( ID3D11Resource* resource, const D3D11_RENDER_TARGET_VIEW_DESC* renderTargetViewDesc, ID3D11RenderTargetView** renderTargetView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRenderTargetView(resource, renderTargetViewDesc, renderTargetView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        RenderTargetView CreateRenderTargetView( const Resource& resource, const D3D11_RENDER_TARGET_VIEW_DESC* renderTargetViewDesc ) const
        {
            ID3D11RenderTargetView* itf = nullptr;
            CreateRenderTargetView( resource.GetInterfacePointer<ID3D11Resource>( ), renderTargetViewDesc, &itf );
            return RenderTargetView( itf );
        }


        void CreateDepthStencilView( ID3D11Resource* resource, const D3D11_DEPTH_STENCIL_VIEW_DESC* depthStencilViewDesc, ID3D11DepthStencilView** depthStencilView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDepthStencilView(resource, depthStencilViewDesc, depthStencilView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        DepthStencilView CreateDepthStencilView( const Resource& resource, const D3D11_DEPTH_STENCIL_VIEW_DESC* depthStencilViewDesc ) const
        {
            ID3D11DepthStencilView* itf = nullptr;
            CreateDepthStencilView( resource.GetInterfacePointer<ID3D11Resource>( ), depthStencilViewDesc, &itf );
            return DepthStencilView( itf );
        }

        void CreateInputLayout( const D3D11_INPUT_ELEMENT_DESC* inputElementDescs, UINT numElements, const void* shaderBytecodeWithInputSignature, SIZE_T bytecodeLength, ID3D11InputLayout** inputLayout) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateInputLayout(inputElementDescs, numElements, shaderBytecodeWithInputSignature, bytecodeLength, inputLayout);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        InputLayout CreateInputLayout( const D3D11_INPUT_ELEMENT_DESC* inputElementDescs, UINT numElements, const void* shaderBytecodeWithInputSignature, SIZE_T bytecodeLength ) const
        {
            ID3D11InputLayout* itf = nullptr;
            CreateInputLayout( inputElementDescs, numElements, shaderBytecodeWithInputSignature, bytecodeLength, &itf );
            return InputLayout( itf );
        }

        void CreateVertexShader( const void* shaderBytecode, SIZE_T bytecodeLength, ID3D11ClassLinkage* classLinkage, ID3D11VertexShader** vertexShader) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVertexShader(shaderBytecode, bytecodeLength, classLinkage, vertexShader);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        VertexShader CreateVertexShader( const void* shaderBytecode, SIZE_T bytecodeLength, const ClassLinkage& classLinkage ) const
        {
            ID3D11VertexShader* vertexShader = nullptr;
            CreateVertexShader( shaderBytecode, bytecodeLength, classLinkage.GetInterfacePointer<ID3D11ClassLinkage>( ), &vertexShader );
            return VertexShader( vertexShader );
        }

        void CreateGeometryShader( const void* shaderBytecode, SIZE_T bytecodeLength, ID3D11ClassLinkage* classLinkage, ID3D11GeometryShader** geometryShader) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateGeometryShader(shaderBytecode, bytecodeLength, classLinkage, geometryShader);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        GeometryShader CreateGeometryShader( const void* shaderBytecode, SIZE_T bytecodeLength, const ClassLinkage& classLinkage ) const
        {
            ID3D11GeometryShader* geometryShader = nullptr;
            CreateGeometryShader( shaderBytecode, bytecodeLength, classLinkage.GetInterfacePointer<ID3D11ClassLinkage>(), &geometryShader );
            return GeometryShader( geometryShader );
        }

        void CreateGeometryShaderWithStreamOutput( const void* shaderBytecode, SIZE_T bytecodeLength, const D3D11_SO_DECLARATION_ENTRY* streamOutputDeclarationEntry, UINT numEntries, const UINT* bufferStrides, UINT numStrides, UINT rasterizedStream, ID3D11ClassLinkage* classLinkage, ID3D11GeometryShader** geometryShader) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateGeometryShaderWithStreamOutput(shaderBytecode, bytecodeLength, streamOutputDeclarationEntry, numEntries, bufferStrides, numStrides, rasterizedStream, classLinkage, geometryShader);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        GeometryShader CreateGeometryShaderWithStreamOutput( const void* shaderBytecode, SIZE_T bytecodeLength, const D3D11_SO_DECLARATION_ENTRY* streamOutputDeclarationEntry, UINT numEntries, const UINT* bufferStrides, UINT numStrides, UINT rasterizedStream, const ClassLinkage& classLinkage ) const
        {
            ID3D11GeometryShader* geometryShader = nullptr;
            CreateGeometryShaderWithStreamOutput( shaderBytecode, bytecodeLength, streamOutputDeclarationEntry, numEntries, bufferStrides, numStrides, rasterizedStream, classLinkage.GetInterfacePointer<ID3D11ClassLinkage>( ), &geometryShader );
            return GeometryShader( geometryShader );
        }

        void CreatePixelShader( const void* shaderBytecode, SIZE_T bytecodeLength, ID3D11ClassLinkage* classLinkage, ID3D11PixelShader** pixelShader) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreatePixelShader(shaderBytecode, bytecodeLength, classLinkage, pixelShader);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        PixelShader CreatePixelShader( const void* shaderBytecode, SIZE_T bytecodeLength, const ClassLinkage& classLinkage ) const
        {
            ID3D11PixelShader* pixelShader = nullptr;
            CreatePixelShader( shaderBytecode, bytecodeLength, classLinkage.GetInterfacePointer<ID3D11ClassLinkage>( ), &pixelShader );
            return PixelShader( pixelShader );
        }

        void CreateHullShader( const void* shaderBytecode, SIZE_T bytecodeLength, ID3D11ClassLinkage* classLinkage, ID3D11HullShader** hullShader) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateHullShader(shaderBytecode, bytecodeLength, classLinkage, hullShader);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateDomainShader( const void* shaderBytecode, SIZE_T bytecodeLength, ID3D11ClassLinkage* classLinkage, ID3D11DomainShader** domainShader) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDomainShader(shaderBytecode, bytecodeLength, classLinkage, domainShader);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateComputeShader( const void* shaderBytecode, SIZE_T bytecodeLength, ID3D11ClassLinkage* classLinkage, ID3D11ComputeShader** computeShader) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateComputeShader(shaderBytecode, bytecodeLength, classLinkage, computeShader);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateClassLinkage( ID3D11ClassLinkage** classLinkage) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateClassLinkage(classLinkage);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateBlendState( const D3D11_BLEND_DESC* blendStateDesc, ID3D11BlendState** blendState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateBlendState(blendStateDesc, blendState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateDepthStencilState( const D3D11_DEPTH_STENCIL_DESC* depthStencilDesc, ID3D11DepthStencilState** depthStencilState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDepthStencilState(depthStencilDesc, depthStencilState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateRasterizerState( const D3D11_RASTERIZER_DESC* rasterizerDesc, ID3D11RasterizerState** rasterizerState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRasterizerState(rasterizerDesc, rasterizerState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateSamplerState( const D3D11_SAMPLER_DESC* samplerDesc, ID3D11SamplerState** samplerState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSamplerState(samplerDesc, samplerState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateQuery( const D3D11_QUERY_DESC* queryDesc, ID3D11Query** query) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateQuery(queryDesc, query);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreatePredicate( const D3D11_QUERY_DESC* predicateDesc, ID3D11Predicate** predicate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreatePredicate(predicateDesc, predicate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateCounter( const D3D11_COUNTER_DESC* counterDesc, ID3D11Counter** counter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateCounter(counterDesc, counter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateDeferredContext( UINT contextFlags, ID3D11DeviceContext** deferredContext) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDeferredContext(contextFlags, deferredContext);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OpenSharedResource( HANDLE resourceHandle, const Guid& returnedInterface, void** resource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenSharedResource(resourceHandle, returnedInterface, resource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckFormatSupport( DXGI_FORMAT format, UINT* formatSupport) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckFormatSupport(format, formatSupport);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckMultisampleQualityLevels( DXGI_FORMAT format, UINT sampleCount, UINT* numQualityLevels) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckMultisampleQualityLevels(format, sampleCount, numQualityLevels);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckCounterInfo( D3D11_COUNTER_INFO* counterInfo) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CheckCounterInfo(counterInfo);
        }

        void CheckCounter( const D3D11_COUNTER_DESC* counterDesc, D3D11_COUNTER_TYPE* counterType, UINT* activeCounters, LPSTR name, UINT* nameLength, LPSTR units, UINT* unitsLength, LPSTR description, UINT* descriptionLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckCounter(counterDesc, counterType, activeCounters, name, nameLength, units, unitsLength, description, descriptionLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckFeatureSupport( D3D11_FEATURE feature, void* featureSupportData, UINT featureSupportDataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckFeatureSupport(feature, featureSupportData, featureSupportDataSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPrivateData( const Guid& guid, UINT* dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPrivateData(guid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPrivateData( const Guid& guid, UINT dataSize, const void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPrivateData(guid, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPrivateDataInterface( const Guid& guid, const IUnknown* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPrivateDataInterface(guid, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        D3D_FEATURE_LEVEL GetFeatureLevel( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetFeatureLevel();
        }

        UINT GetCreationFlags( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetCreationFlags();
        }

        void GetDeviceRemovedReason( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDeviceRemovedReason();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetImmediateContext( ID3D11DeviceContext** immediateContext) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetImmediateContext(immediateContext);
        }

        DeviceContext GetImmediateContext( ) const
        {
            ID3D11DeviceContext* itf = nullptr;
            GetImmediateContext( &itf );
            return DeviceContext( itf );
        }

        void SetExceptionMode( UINT raiseFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetExceptionMode(raiseFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        UINT GetExceptionMode() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetExceptionMode();
        }
    };

    /// <summary>
    /// The blend-state object holds a description for blending state that 
    /// you can bind to the output-merger stage. This blend-state object 
    /// supports logical operations as well as blending operations.
    /// </summary>
    class BlendState1 : public BlendState
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(BlendState1, BlendState, ID3D11BlendState1, ID3D11BlendState )
    public:
        void GetDesc1(D3D11_BLEND_DESC1* blendDesc1) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc1(blendDesc1);
        }
    };

    /// <summary>
    /// The rasterizer-state object holds a description for rasterizer 
    /// state that you can bind to the rasterizer stage. This rasterizer-state 
    /// class supports forced sample count.
    /// </summary>
    class RasterizerState1 : public RasterizerState
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(RasterizerState1, RasterizerState, ID3D11RasterizerState1, ID3D11RasterizerState )
    public:
        void GetDesc1(D3D11_RASTERIZER_DESC1* rasterizerDesc1) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc1(rasterizerDesc1);
        }
    };

    /// <summary>
    /// Represents a context state object, which holds state and 
    /// behavior information about a Microsoft Direct3D device.
    /// </summary>
    class DeviceContextState : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DeviceContextState, DeviceChild, ID3DDeviceContextState, ID3D11DeviceChild )
    public:
    };

    /// <summary>
    /// Represents a device context; it is used to render commands.
    /// </summary>
    class DeviceContext1 : public DeviceContext
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DeviceContext1, DeviceContext, ID3D11DeviceContext1, ID3D11DeviceContext )
    public:
        void CopySubresourceRegion1( ID3D11Resource* dstResource, UINT dstSubresource, UINT dstX, UINT dstY, UINT dstZ, ID3D11Resource* srcResource, UINT srcSubresource, const D3D11_BOX* srcBox, UINT copyFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CopySubresourceRegion1(dstResource, dstSubresource, dstX, dstY, dstZ, srcResource, srcSubresource, srcBox, copyFlags);
        }

        void UpdateSubresource1( ID3D11Resource* dstResource, UINT dstSubresource, const D3D11_BOX* dstBox, const void* srcData, UINT srcRowPitch, UINT srcDepthPitch, UINT copyFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->UpdateSubresource1(dstResource, dstSubresource, dstBox, srcData, srcRowPitch, srcDepthPitch, copyFlags);
        }

        void DiscardResource( ID3D11Resource* resource) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DiscardResource(resource);
        }

        void DiscardView( ID3D11View* resourceView) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DiscardView(resourceView);
        }

        void VSSetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers, const UINT* firstConstant, const UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSSetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void HSSetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers, const UINT* firstConstant, const UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSSetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void DSSetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers, const UINT* firstConstant, const UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSSetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void GSSetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers, const UINT* firstConstant, const UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSSetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void PSSetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers, const UINT* firstConstant, const UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSSetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void CSSetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers, const UINT* firstConstant, const UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSSetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void VSGetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers, UINT* firstConstant, UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VSGetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void HSGetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers, UINT* firstConstant, UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->HSGetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void DSGetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers, UINT* firstConstant, UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DSGetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void GSGetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers, UINT* firstConstant, UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GSGetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void PSGetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers, UINT* firstConstant, UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->PSGetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void CSGetConstantBuffers1( UINT startSlot, UINT numBuffers, ID3D11Buffer** constantBuffers, UINT* firstConstant, UINT* numConstants) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CSGetConstantBuffers1(startSlot, numBuffers, constantBuffers, firstConstant, numConstants);
        }

        void SwapDeviceContextState( ID3DDeviceContextState* state, ID3DDeviceContextState** previousState) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SwapDeviceContextState(state, previousState);
        }

        void ClearView( ID3D11View* view, const FLOAT color[4], const D3D11_RECT* rect, UINT numRects) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearView(view, color, rect, numRects);
        }

        void DiscardView1( ID3D11View* resourceView, const D3D11_RECT* rects, UINT numRects) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DiscardView1(resourceView, rects, numRects);
        }
    };

    /// <summary>
    /// Provides the video functionality of a Microsoft Direct3D 11 device.
    /// </summary>
    class VideoContext1 : public VideoContext
    {
    public:                                                
        HCC_COM_STANDARD_METHODS_IMPL(VideoContext1, VideoContext, ID3D11VideoContext1, ID3D11VideoContext )
    public:
        void SubmitDecoderBuffers1( ID3D11VideoDecoder* decoder, UINT numBuffers, const D3D11_VIDEO_DECODER_BUFFER_DESC1* bufferDesc) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SubmitDecoderBuffers1(decoder, numBuffers, bufferDesc);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDataForNewHardwareKey( ID3D11CryptoSession* cryptoSession, UINT privateInputSize, const void* privatInputData, UINT64* privateOutputData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDataForNewHardwareKey(cryptoSession, privateInputSize, privatInputData, privateOutputData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckCryptoSessionStatus( ID3D11CryptoSession* cryptoSession, D3D11_CRYPTO_SESSION_STATUS* status) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckCryptoSessionStatus(cryptoSession, status);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DecoderEnableDownsampling( ID3D11VideoDecoder* decoder, DXGI_COLOR_SPACE_TYPE inputColorSpace, const D3D11_VIDEO_SAMPLE_DESC* outputDesc, UINT referenceFrameCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DecoderEnableDownsampling(decoder, inputColorSpace, outputDesc, referenceFrameCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void DecoderUpdateDownsampling( ID3D11VideoDecoder* decoder, const D3D11_VIDEO_SAMPLE_DESC* outputDesc) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DecoderUpdateDownsampling(decoder, outputDesc);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void VideoProcessorSetOutputColorSpace1( ID3D11VideoProcessor* videoProcessor, DXGI_COLOR_SPACE_TYPE colorSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputColorSpace1(videoProcessor, colorSpace);
        }

        void VideoProcessorSetOutputShaderUsage( ID3D11VideoProcessor* videoProcessor, BOOL shaderUsage) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputShaderUsage(videoProcessor, shaderUsage);
        }

        void VideoProcessorGetOutputColorSpace1( ID3D11VideoProcessor* videoProcessor, DXGI_COLOR_SPACE_TYPE* colorSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputColorSpace1(videoProcessor, colorSpace);
        }

        void VideoProcessorGetOutputShaderUsage( ID3D11VideoProcessor* videoProcessor, BOOL* shaderUsage) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputShaderUsage(videoProcessor, shaderUsage);
        }

        void VideoProcessorSetStreamColorSpace1( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, DXGI_COLOR_SPACE_TYPE colorSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamColorSpace1(videoProcessor, streamIndex, colorSpace);
        }

        void VideoProcessorSetStreamMirror( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL enable, BOOL flipHorizontal, BOOL flipVertical) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamMirror(videoProcessor, streamIndex, enable, flipHorizontal, flipVertical);
        }

        void VideoProcessorGetStreamColorSpace1( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, DXGI_COLOR_SPACE_TYPE* colorSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamColorSpace1(videoProcessor, streamIndex, colorSpace);
        }

        void VideoProcessorGetStreamMirror( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, BOOL* enable, BOOL* flipHorizontal, BOOL* flipVertical) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamMirror(videoProcessor, streamIndex, enable, flipHorizontal, flipVertical);
        }

        void VideoProcessorGetBehaviorHints( ID3D11VideoProcessor* videoProcessor, UINT outputWidth, UINT outputHeight, DXGI_FORMAT outputFormat, UINT streamCount, const D3D11_VIDEO_PROCESSOR_STREAM_BEHAVIOR_HINT* videoProcessorStreamBehaviorHint, UINT* behaviorHints) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->VideoProcessorGetBehaviorHints(videoProcessor, outputWidth, outputHeight, outputFormat, streamCount, videoProcessorStreamBehaviorHint, behaviorHints);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Provides the video decoding and video processing capabilities of a Microsoft Direct3D 11 device.
    /// </summary>
    class VideoDevice1 : public VideoDevice
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoDevice1, VideoDevice, ID3D11VideoDevice1, ID3D11VideoDevice )
    public:
        void GetCryptoSessionPrivateDataSize( const GUID* cryptoType, const GUID* decoderProfile, const GUID* keyExchangeType, UINT* privateInputSize, UINT* privateOutputSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCryptoSessionPrivateDataSize(cryptoType, decoderProfile, keyExchangeType, privateInputSize, privateOutputSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoDecoderCaps( const GUID* decoderProfile, UINT sampleWidth, UINT sampleHeight, const DXGI_RATIONAL* frameRate, UINT bitRate, const GUID* cryptoType, UINT* decoderCaps) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoDecoderCaps(decoderProfile, sampleWidth, sampleHeight, frameRate, bitRate, cryptoType, decoderCaps);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckVideoDecoderDownsampling( const D3D11_VIDEO_DECODER_DESC* inputDesc, DXGI_COLOR_SPACE_TYPE inputColorSpace, const D3D11_VIDEO_DECODER_CONFIG* inputConfig, const DXGI_RATIONAL* frameRate, const D3D11_VIDEO_SAMPLE_DESC* outputDesc, BOOL* supported, BOOL* realTimeHint) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckVideoDecoderDownsampling(inputDesc, inputColorSpace, inputConfig, frameRate, outputDesc, supported, realTimeHint);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RecommendVideoDecoderDownsampleParameters( const D3D11_VIDEO_DECODER_DESC* inputDesc, DXGI_COLOR_SPACE_TYPE inputColorSpace, const D3D11_VIDEO_DECODER_CONFIG* inputConfig, const DXGI_RATIONAL* frameRate, D3D11_VIDEO_SAMPLE_DESC* recommendedOutputDesc) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RecommendVideoDecoderDownsampleParameters(inputDesc, inputColorSpace, inputConfig, frameRate, recommendedOutputDesc);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Enumerates the video processor capabilities of a Microsoft Direct3D 11 device.
    /// </summary>
    class VideoProcessorEnumerator1 : public VideoProcessorEnumerator
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoProcessorEnumerator1, VideoProcessorEnumerator, ID3D11VideoProcessorEnumerator1, ID3D11VideoProcessorEnumerator )
    public:
        void CheckVideoProcessorFormatConversion( DXGI_FORMAT inputFormat, DXGI_COLOR_SPACE_TYPE inputColorSpace, DXGI_FORMAT outputFormat, DXGI_COLOR_SPACE_TYPE outputColorSpace, BOOL* supported) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckVideoProcessorFormatConversion(inputFormat, inputColorSpace, outputFormat, outputColorSpace, supported);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// The device interface represents a virtual adapter; it is used to create resources.
    /// </summary>
    class Device1 : public Device
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device1, Device, ID3D11Device1, ID3D11Device )
    public:
        void GetImmediateContext1(ID3D11DeviceContext1** immediateContext) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetImmediateContext1(immediateContext);
        }

        void CreateDeferredContext1( UINT contextFlags, ID3D11DeviceContext1** deferredContext) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDeferredContext1(contextFlags, deferredContext);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateBlendState1( const D3D11_BLEND_DESC1* blendStateDesc, ID3D11BlendState1** blendState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateBlendState1(blendStateDesc, blendState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateRasterizerState1( const D3D11_RASTERIZER_DESC1* rasterizerDesc, ID3D11RasterizerState1** rasterizerState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRasterizerState1(rasterizerDesc, rasterizerState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateDeviceContextState( UINT flags, const D3D_FEATURE_LEVEL* featureLevels, UINT numberOfFeatureLevels, UINT sdkVersion, const Guid& emulatedInterface, D3D_FEATURE_LEVEL* chosenFeatureLevel, ID3DDeviceContextState** contextState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDeviceContextState(flags, featureLevels, numberOfFeatureLevels, sdkVersion, emulatedInterface, chosenFeatureLevel, contextState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OpenSharedResource1( HANDLE resourceHandle, const Guid& returnedInterface, void** resource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenSharedResource1(resourceHandle, returnedInterface, resource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        template<typename T>
            requires std::is_base_of_v<Resource,T>
        T OpenSharedResource( HANDLE resourceHandle ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            OpenSharedResource1( resourceHandle, __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
            return T( itf );
        }


        void OpenSharedResourceByName( LPCWSTR name, DWORD desiredAccess, const Guid& returnedInterface, void** resource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenSharedResourceByName(name, desiredAccess, returnedInterface, resource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Enables an application to describe conceptual sections and markers within the application's code flow. 
    /// </summary>
    class UserDefinedAnnotation : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(UserDefinedAnnotation, Unknown, ID3DUserDefinedAnnotation, IUnknown )
    public:
        INT BeginEvent(LPCWSTR name) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->BeginEvent(name);
        }

        INT EndEvent( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->EndEvent();
        }

        void SetMarker( LPCWSTR name) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetMarker(name);
        }

        BOOL GetStatus( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetStatus();
        }
    };

    /// <summary>
    /// The device context interface represents a device context; it is used to render commands.
    /// </summary>
    class DeviceContext2 : public DeviceContext1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DeviceContext2, DeviceContext1, ID3D11DeviceContext2, ID3D11DeviceContext1 )
    public:
        void UpdateTileMappings( ID3D11Resource* tiledResource, UINT numTiledResourceRegions, const D3D11_TILED_RESOURCE_COORDINATE* tiledResourceRegionStartCoordinates, const D3D11_TILE_REGION_SIZE* tiledResourceRegionSizes, ID3D11Buffer* tilePool, UINT numRanges, const UINT* rangeFlags, const UINT* tilePoolStartOffsets, const UINT* rangeTileCounts, UINT flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UpdateTileMappings(tiledResource, numTiledResourceRegions, tiledResourceRegionStartCoordinates, tiledResourceRegionSizes, tilePool, numRanges, rangeFlags, tilePoolStartOffsets, rangeTileCounts, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CopyTileMappings( ID3D11Resource* destTiledResource, const D3D11_TILED_RESOURCE_COORDINATE* destRegionStartCoordinate, ID3D11Resource* sourceTiledResource, const D3D11_TILED_RESOURCE_COORDINATE* sourceRegionStartCoordinate, const D3D11_TILE_REGION_SIZE* tileRegionSize, UINT flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CopyTileMappings(destTiledResource, destRegionStartCoordinate, sourceTiledResource, sourceRegionStartCoordinate, tileRegionSize, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CopyTiles( ID3D11Resource* tiledResource, const D3D11_TILED_RESOURCE_COORDINATE* tileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE* tileRegionSize, ID3D11Buffer* buffer, UINT64 bufferStartOffsetInBytes, UINT flags) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->CopyTiles(tiledResource, tileRegionStartCoordinate, tileRegionSize, buffer, bufferStartOffsetInBytes, flags);
        }

        void UpdateTiles( ID3D11Resource* destTiledResource, const D3D11_TILED_RESOURCE_COORDINATE* destTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE* destTileRegionSize, const void* sourceTileData, UINT flags) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->UpdateTiles(destTiledResource, destTileRegionStartCoordinate, destTileRegionSize, sourceTileData, flags);
        }

        void ResizeTilePool( ID3D11Buffer* tilePool, UINT64 newSizeInBytes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ResizeTilePool(tilePool, newSizeInBytes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void TiledResourceBarrier( ID3D11DeviceChild* tiledResourceOrViewAccessBeforeBarrier, ID3D11DeviceChild* tiledResourceOrViewAccessAfterBarrier) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->TiledResourceBarrier(tiledResourceOrViewAccessBeforeBarrier, tiledResourceOrViewAccessAfterBarrier);
        };

        BOOL IsAnnotationEnabled( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->IsAnnotationEnabled();
        }

        void SetMarkerInt( LPCWSTR label, INT data) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetMarkerInt(label, data);
        }

        void BeginEventInt( LPCWSTR label, INT data) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->BeginEventInt(label, data);
        }

        void EndEvent( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EndEvent();
        }
    };

    /// <summary>
    /// The Device2 class represents a virtual adapter; it is used to create resources.
    /// </summary>
    class Device2 : public Device1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device2, Device1, ID3D11Device2, ID3D11Device1 )
    public:
        void GetImmediateContext2( ID3D11DeviceContext2** immediateContext) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetImmediateContext2(immediateContext);
        }

        void CreateDeferredContext2( UINT contextFlags, ID3D11DeviceContext2** deferredContext) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDeferredContext2(contextFlags, deferredContext);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetResourceTiling( ID3D11Resource* tiledResource, UINT* numTilesForEntireResource, D3D11_PACKED_MIP_DESC* packedMipDesc, D3D11_TILE_SHAPE* standardTileShapeForNonPackedMips, UINT* numSubresourceTilings, UINT firstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING* subresourceTilingsForNonPackedMips) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetResourceTiling(tiledResource, numTilesForEntireResource, packedMipDesc, standardTileShapeForNonPackedMips, numSubresourceTilings, firstSubresourceTilingToGet, subresourceTilingsForNonPackedMips);
        }

        void CheckMultisampleQualityLevels1( DXGI_FORMAT format, UINT sampleCount, UINT flags, UINT* numQualityLevels) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckMultisampleQualityLevels1(format, sampleCount, flags, numQualityLevels);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Represents texel data, which is structured memory.
    /// </summary>
    class Texture2D1 : public Texture2D
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Texture2D1, Texture2D, ID3D11Texture2D1, ID3D11Texture2D )
    public:
        void GetDesc1(D3D11_TEXTURE2D_DESC1* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc1(desc);
        }
    };

    /// <summary>
    /// A 3D texture object represents texel data, which is structured memory.
    /// </summary>
    class Texture3D1 : public Texture3D
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Texture3D1, Texture3D, ID3D11Texture3D1, ID3D11Texture3D )
    public:
        void GetDesc1(D3D11_TEXTURE3D_DESC1* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc1(desc);
        }
    };

    /// <summary>
    /// The rasterizer-state object holds a description for rasterizer 
    /// state that you can bind to the rasterizer stage. This rasterizer-state 
    /// class supports forced sample count and conservative rasterization mode.
    /// </summary>
    class RasterizerState2 : public RasterizerState1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(RasterizerState2, RasterizerState1, ID3D11RasterizerState2, ID3D11RasterizerState1 )
    public:
        void GetDesc2(D3D11_RASTERIZER_DESC2* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc2(desc);
        }
    };

    /// <summary>
    /// A shader-resource-view object represents the subresources a shader 
    /// can access during rendering. Examples of shader resources include 
    /// a constant buffer, a texture buffer, and a texture.
    /// </summary>
    class ShaderResourceView1 : public ShaderResourceView
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ShaderResourceView1, ShaderResourceView, ID3D11ShaderResourceView1, ID3D11ShaderResourceView )
    public:
        void GetDesc1(D3D11_SHADER_RESOURCE_VIEW_DESC1* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc1(desc);
        }
    };

    /// <summary>
    /// A render-target-view object represents the render-target subresources 
    /// that can be accessed during rendering.
    /// </summary>
    class RenderTargetView1 : public RenderTargetView
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(RenderTargetView1, RenderTargetView, ID3D11RenderTargetView1, ID3D11RenderTargetView )
    public:
        void GetDesc1(D3D11_RENDER_TARGET_VIEW_DESC1* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc1(desc);
        }
    };

    /// <summary>
    /// An unordered-access-view object represents the parts of a 
    /// resource the pipeline can access during rendering.
    /// </summary>
    class UnorderedAccessView1 : public UnorderedAccessView
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(UnorderedAccessView1, UnorderedAccessView, ID3D11UnorderedAccessView1, ID3D11UnorderedAccessView )
    public:
        void GetDesc1(D3D11_UNORDERED_ACCESS_VIEW_DESC1* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc1(desc);
        }
    };

    /// <summary>
    /// Represents a query object for querying information from the graphics processing unit (GPU).
    /// </summary>
    class Query1 : public Query
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Query1, Query, ID3D11Query1, ID3D11Query )
    public:
        void GetDesc1(D3D11_QUERY_DESC1* desc) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetDesc1(desc);
        }
    };

    /// <summary>
    /// The device context class represents a device context; it is used to render commands.
    /// </summary>
    class DeviceContext3 : public DeviceContext2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DeviceContext3, DeviceContext2, ID3D11DeviceContext3, ID3D11DeviceContext2 )
    public:
        void Flush1(D3D11_CONTEXT_TYPE contextType, HANDLE hEvent) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Flush1(contextType, hEvent);
        }

        void SetHardwareProtectionState( BOOL hardwareProtectionEnable) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetHardwareProtectionState(hardwareProtectionEnable);
        }

        void GetHardwareProtectionState( BOOL* hardwareProtectionEnabled) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetHardwareProtectionState(hardwareProtectionEnabled);
        }
    };

    /// <summary>
    /// Represents a fence, an object used for synchronization of the CPU and one or more GPUs.
    /// </summary>
    class Fence : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Fence, DeviceChild, ID3D11Fence, ID3D11DeviceChild )
    public:
        void CreateSharedHandle( const SECURITY_ATTRIBUTES* securityAttributes, DWORD access, LPCWSTR name, HANDLE* handle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSharedHandle(securityAttributes, access, name, handle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        UINT64 GetCompletedValue() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetCompletedValue();
        }

        void SetEventOnCompletion(UINT64 value, HANDLE hEvent) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetEventOnCompletion(value, hEvent);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// The device context interface represents a device context; it is used to render commands.
    /// </summary>
    class DeviceContext4 : public DeviceContext3
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DeviceContext4, DeviceContext3, ID3D11DeviceContext4, ID3D11DeviceContext3 )
    public:
        void Signal( ID3D11Fence* fence, UINT64 Value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Signal(fence, Value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Wait( ID3D11Fence* fence, UINT64 Value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Wait(fence, Value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// The device interface represents a virtual adapter; it is used to create resources.
    /// </summary>
    class Device3 : public Device2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device3, Device2, ID3D11Device3, ID3D11Device2 )
    public:
        void CreateTexture2D1( const D3D11_TEXTURE2D_DESC1* desc, const D3D11_SUBRESOURCE_DATA* initialData, ID3D11Texture2D1** texture2D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTexture2D1(desc, initialData, texture2D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateTexture3D1( const D3D11_TEXTURE3D_DESC1* desc, const D3D11_SUBRESOURCE_DATA* initialData, ID3D11Texture3D1** texture3D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTexture3D1(desc, initialData, texture3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateRasterizerState2( const D3D11_RASTERIZER_DESC2* rasterizerDesc, ID3D11RasterizerState2** rasterizerState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRasterizerState2(rasterizerDesc, rasterizerState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateShaderResourceView1( ID3D11Resource* resource, const D3D11_SHADER_RESOURCE_VIEW_DESC1* desc, ID3D11ShaderResourceView1** shaderResourceView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateShaderResourceView1(resource, desc, shaderResourceView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateUnorderedAccessView1( ID3D11Resource* resource, const D3D11_UNORDERED_ACCESS_VIEW_DESC1* desc, ID3D11UnorderedAccessView1** unorderedAccessView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateUnorderedAccessView1(resource, desc, unorderedAccessView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateRenderTargetView1( ID3D11Resource* resource, const D3D11_RENDER_TARGET_VIEW_DESC1* desc, ID3D11RenderTargetView1** renderTargetView) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRenderTargetView1(resource, desc, renderTargetView);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateQuery1( const D3D11_QUERY_DESC1* queryDesc, ID3D11Query1** query) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateQuery1(queryDesc, query);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetImmediateContext3( ID3D11DeviceContext3** immediateContext) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->GetImmediateContext3(immediateContext);
        }

        void CreateDeferredContext3( UINT contextFlags, ID3D11DeviceContext3** deferredContext) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDeferredContext3(contextFlags, deferredContext);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void WriteToSubresource( ID3D11Resource* dstResource, UINT dstSubresource, const D3D11_BOX* dstBox, const void* srcData, UINT srcRowPitch, UINT srcDepthPitch) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->WriteToSubresource(dstResource, dstSubresource, dstBox, srcData, srcRowPitch, srcDepthPitch);
        }

        void ReadFromSubresource( void* dstData, UINT dstRowPitch, UINT dstDepthPitch, ID3D11Resource* srcResource, UINT srcSubresource, const D3D11_BOX* srcBox) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ReadFromSubresource(dstData, dstRowPitch, dstDepthPitch, srcResource, srcSubresource, srcBox);
        }
    };

    /// <summary>
    /// The device class represents a virtual adapter; it is used to create resources.
    /// </summary>
    class Device4 : public Device3
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device4, Device3, ID3D11Device4, ID3D11Device3 )
    public:
        void RegisterDeviceRemovedEvent(HANDLE hEvent, DWORD* cookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterDeviceRemovedEvent(hEvent, cookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterDeviceRemoved(DWORD cookie) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->UnregisterDeviceRemoved(cookie);
        }
    };


    /// <summary>
    /// The device class represents a virtual adapter; it is used to create resources.
    /// </summary>
    class Device5 : public Device4
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device5, Device4, ID3D11Device5, ID3D11Device4 )
    public:
        void OpenSharedFence( HANDLE hFence, const Guid& returnedInterfaceId, void** fence) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenSharedFence(hFence, returnedInterfaceId, fence);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateFence( UINT64 initialValue, D3D11_FENCE_FLAG flags, const Guid& returnedInterfaceId, void** fence) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateFence(initialValue, flags, returnedInterfaceId, fence);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Provides threading protection for critical sections of a multi-threaded application.
    /// </summary>
    class Multithread : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Multithread, Unknown, ID3D11Multithread, IUnknown )
    public:
        void Enter() const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Enter();
        }

        void Leave( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->Leave();
        }

        BOOL SetMultithreadProtected( BOOL multithreadProtected) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->SetMultithreadProtected(multithreadProtected);
        }

        BOOL GetMultithreadProtected( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetMultithreadProtected();
        }
    };

    /// <summary>
    /// Provides the video functionality of a Microsoft Direct3D 11 device.
    /// </summary>
    class VideoContext2 : public VideoContext1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoContext2, VideoContext1, ID3D11VideoContext2, ID3D11VideoContext1 )
    public:
        void VideoProcessorSetOutputHDRMetaData( ID3D11VideoProcessor* videoProcessor, DXGI_HDR_METADATA_TYPE type, UINT metaDataSize, const void* metaData) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetOutputHDRMetaData(videoProcessor, type, metaDataSize, metaData);
        }

        void VideoProcessorGetOutputHDRMetaData( ID3D11VideoProcessor* videoProcessor, DXGI_HDR_METADATA_TYPE* type, UINT metaDataBufferSize, void* metaDataBuffer) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetOutputHDRMetaData(videoProcessor, type, metaDataBufferSize, metaDataBuffer);
        }

        void VideoProcessorSetStreamHDRMetaData( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, DXGI_HDR_METADATA_TYPE type, UINT metaDataSize, const void* metaData) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorSetStreamHDRMetaData(videoProcessor, streamIndex, type, metaDataSize, metaData);
        }

        void VideoProcessorGetStreamHDRMetaData( ID3D11VideoProcessor* videoProcessor, UINT streamIndex, DXGI_HDR_METADATA_TYPE* type, UINT metaDataBufferSize, void* metaDataBuffer) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->VideoProcessorGetStreamHDRMetaData(videoProcessor, streamIndex, type, metaDataBufferSize, metaDataBuffer);
        }
    };

    /// <summary>
    /// Provides the video decoding and video processing capabilities of a Microsoft 
    /// Direct3D 11 device. Adds the CheckFeatureSupport method for querying for 
    /// decoding capabilities.
    /// </summary>
    class VideoDevice2 : public VideoDevice1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoDevice2, VideoDevice1, ID3D11VideoDevice2, ID3D11VideoDevice1 )
    public:
        void CheckFeatureSupport(D3D11_FEATURE_VIDEO feature, void* featureSupportData, UINT featureSupportDataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckFeatureSupport(feature, featureSupportData, featureSupportDataSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NegotiateCryptoSessionKeyExchangeMT( ID3D11CryptoSession* cryptoSession, D3D11_CRYPTO_SESSION_KEY_EXCHANGE_FLAGS flags, UINT dataSize, void* data) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NegotiateCryptoSessionKeyExchangeMT(cryptoSession, flags, dataSize, data);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    /// <summary>
    /// Provides the video functionality of a Microsoft Direct3D 11 device. This class provides 
    /// the DecoderBeginFrame1 method, which provides support for decode histograms.
    /// </summary>
    class VideoContext3 : public VideoContext2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(VideoContext3, VideoContext2, ID3D11VideoContext3, ID3D11VideoContext2 )
    public:
        void DecoderBeginFrame1( ID3D11VideoDecoder* decoder, ID3D11VideoDecoderOutputView* videoDecoderOutputView, UINT contentKeySize, const void* contentKey, UINT numComponentHistograms, const UINT* histogramOffsets, ID3D11Buffer* const* histogramBuffers) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DecoderBeginFrame1(decoder, videoDecoderOutputView, contentKeySize, contentKey, numComponentHistograms, histogramOffsets, histogramBuffers);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SubmitDecoderBuffers2(ID3D11VideoDecoder* decoder, UINT numBuffers, const D3D11_VIDEO_DECODER_BUFFER_DESC2* bufferDesc) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SubmitDecoderBuffers2(decoder, numBuffers, bufferDesc);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    template<typename T = Device>
        requires std::is_base_of_v<Device,T>
    T CreateDevice( _In_opt_ IDXGIAdapter* adapter,
        D3D_DRIVER_TYPE driverType,
        UINT flags,
        _In_reads_opt_( numberOfFeatureLevels ) CONST D3D_FEATURE_LEVEL* featureLevels,
        UINT numberOfFeatureLevels,
        _COM_Outptr_opt_ ID3D11DeviceContext** immediateContext = nullptr, _Out_opt_ D3D_FEATURE_LEVEL* selectedFeatureLevel = nullptr, HMODULE software = nullptr, UINT sdkVersion = D3D11_SDK_VERSION )
    {
        ID3D11Device* deviceItf = nullptr;
        auto hr = D3D11CreateDevice( adapter, driverType, software, flags, featureLevels, numberOfFeatureLevels, sdkVersion, &deviceItf, selectedFeatureLevel, immediateContext );
        HCC_COM_CHECK_HRESULT( hr );
        Device device( deviceItf );
        if constexpr ( std::is_same_v<Device, T > == false )
        {
            return device.As<T>( );
        }
        return device;
    }

}


#endif
