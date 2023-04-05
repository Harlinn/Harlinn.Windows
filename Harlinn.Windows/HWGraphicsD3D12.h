#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12_H_

#include "HWGraphicsD3Common.h"
#include <boost/container/small_vector.hpp>

#pragma comment(lib,"D3D12.lib")


namespace Harlinn::Windows::Graphics
{
    using namespace Harlinn::Common::Core;



    class D3D12Object;
    class D3D12DeviceChild;
    class D3D12RootSignature;
    class D3D12RootSignatureDeserializer;
    class D3D12VersionedRootSignatureDeserializer;
    class D3D12Pageable;
    class D3D12Heap;
    class D3D12Resource;
    class D3D12CommandAllocator;
    class D3D12Fence;
    class D3D12Fence1;
    class D3D12PipelineState;
    class D3D12DescriptorHeap;
    class D3D12QueryHeap;
    class D3D12CommandSignature;
    class D3D12CommandList;
    class D3D12GraphicsCommandList;
    class D3D12GraphicsCommandList1;
    class D3D12GraphicsCommandList2;
    class D3D12CommandQueue;
    class D3D12Device;
    class D3D12PipelineLibrary;
    class D3D12PipelineLibrary1;
    class D3D12Device1;
    class D3D12Device2;
    class D3D12Device3;
    class D3D12ProtectedSession;
    class D3D12ProtectedResourceSession;
    class D3D12Device4;
    class D3D12LifetimeOwner;
    class D3D12SwapChainAssistant;
    class D3D12LifetimeTracker;
    class D3D12StateObject;
    class D3D12StateObjectProperties;
    class D3D12Device5;
    class D3D12DeviceRemovedExtendedDataSettings;
    class D3D12DeviceRemovedExtendedDataSettings1;
    class D3D12DeviceRemovedExtendedData;
    class D3D12DeviceRemovedExtendedData1;
    class D3D12Device6;
    class D3D12ProtectedResourceSession1;
    class D3D12Device7;
    class D3D12Device8;
    class D3D12Resource1;
    class D3D12Resource2;
    class D3D12Heap1;
    class D3D12GraphicsCommandList3;
    class D3D12MetaCommand;
    class D3D12GraphicsCommandList4;
    class D3D12Tools;
    class D3D12GraphicsCommandList5;
    class D3D12GraphicsCommandList6;


#define COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( classType, baseClassType , interfaceType, baseInterfaceType )  HCC_COM_STANDARD_METHODS_IMPL(classType, baseClassType , interfaceType, baseInterfaceType)


    /// <summary>
    /// A base class from which D3D12Device and D3D12DeviceChild inherit from. 
    /// It provides methods to associate private data and annotate object names.
    /// </summary>
    class D3D12Object : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Object, Unknown, ID3D12Object, IUnknown )

    public:
        /// <summary>
        /// Gets application-defined data from a device object.
        /// </summary>
        /// <param name="guid">The GUID to associate with the data.</param>
        /// <param name="dataSizePtr">
        /// A pointer to a variable that on input contains the size, in bytes, 
        /// of the buffer that pData points to, and on output contains the size, 
        /// in bytes, of the amount of data that GetPrivateData retrieved.
        /// </param>
        /// <param name="dataPtr">
        /// A pointer to a memory block that receives the data from the device 
        /// object if pDataSize points to a value that specifies a buffer large 
        /// enough to hold the data.
        /// </param>
        void GetPrivateData( _In_ REFGUID guid, _Inout_ UINT* dataSizePtr, _Out_writes_bytes_opt_( *dataSizePtr )  void* dataPtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetPrivateData( guid, dataSizePtr, dataPtr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Sets application-defined data to a device object and associates that data with an application-defined GUID.
        /// </summary>
        /// <param name="guid">The GUID to associate with the data.</param>
        /// <param name="dataSize">The size in bytes of the data.</param>
        /// <param name="dataPtr">
        /// A pointer to a memory block that contains the data to be stored with this device object. 
        /// If pData is NULL, DataSize must also be 0, and any data that was previously associated 
        /// with the GUID specified in guid will be destroyed.
        /// </param>
        void SetPrivateData( _In_ REFGUID guid, _In_  UINT dataSize, _In_reads_bytes_opt_( dataSize )  const void* dataPtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetPrivateData( guid, dataSize, dataPtr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetPrivateDataInterface( REFGUID guid, const IUnknown* privateDatainterfacePtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetPrivateDataInterface( guid, privateDatainterfacePtr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetPrivateDataInterface( Guid& guid, const Unknown& privateDatainterface ) const
        {
            SetPrivateDataInterface( guid.AsGuid(), privateDatainterface.GetInterfacePointer() );
        }

        void SetName( _In_z_  LPCWSTR name ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetName( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SetName( const std::wstring& name ) const
        {
            SetName( name.c_str( ) );
        }
        void SetName( const std::string& name ) const
        {
            SetName( ToWideString( name ) );
        }

    };
    

    class D3D12Device;

    class D3D12DeviceChild : public D3D12Object
    {
    public:
        using Base = D3D12Object;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DeviceChild, D3D12Object, ID3D12DeviceChild, ID3D12Object )

    public:
        void GetDevice( REFIID riid, _COM_Outptr_opt_  void** ppvDevice ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDevice( riid, ppvDevice );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }



        template<typename T >
            requires std::is_base_of_v<D3D12Device,T>
        T GetDevice( ) const
        {
            typename T::InterfaceType* ptr = nullptr;
            constexpr auto refiid = __uuidof( typename T::InterfaceType );
            GetDevice( refiid, (void**) &ptr );
            return T( ptr, false );
        }
        inline D3D12Device4 GetDevice( ) const;

    };


    class D3D12RootSignature : public D3D12DeviceChild
    {
    public:
        using Base = D3D12DeviceChild;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12RootSignature, D3D12DeviceChild, ID3D12RootSignature, ID3D12DeviceChild )
    public:
    };


    class D3D12RootSignatureDeserializer : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12RootSignatureDeserializer, Unknown, ID3D12RootSignatureDeserializer, IUnknown )

    public:
        const D3D12_ROOT_SIGNATURE_DESC* GetRootSignatureDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetRootSignatureDesc( );
        }
    };

    class D3D12VersionedRootSignatureDeserializer : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12VersionedRootSignatureDeserializer, Unknown, ID3D12VersionedRootSignatureDeserializer, IUnknown )

    public:
        void GetRootSignatureDescAtVersion( D3D_ROOT_SIGNATURE_VERSION convertToVersion, _Out_  const D3D12_VERSIONED_ROOT_SIGNATURE_DESC** ppDesc ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetRootSignatureDescAtVersion( convertToVersion, ppDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* GetUnconvertedRootSignatureDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetUnconvertedRootSignatureDesc( );
        }
    };


    class D3D12Pageable : public D3D12DeviceChild
    {
    public:
        using Base = D3D12DeviceChild;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Pageable, D3D12DeviceChild, ID3D12Pageable, ID3D12DeviceChild )
    public:
    };


    class D3D12Heap : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Heap, D3D12Pageable, ID3D12Heap, ID3D12Pageable )
    public:
        D3D12_HEAP_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }
    };

    class D3D12Resource : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Resource, D3D12Pageable, ID3D12Resource, ID3D12Pageable )
    public:
        void Map( UINT Subresource, _In_opt_ const D3D12_RANGE* pReadRange, _Outptr_opt_result_bytebuffer_( _Inexpressible_( "Dependent on resource" ) )  void** ppData ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Map( Subresource, pReadRange, ppData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Unmap( UINT Subresource, _In_opt_  const D3D12_RANGE* pWrittenRange ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Unmap( Subresource, pWrittenRange );
        }

        D3D12_RESOURCE_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }

        D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetGPUVirtualAddress( );
        }

        void WriteToSubresource(UINT DstSubresource, _In_opt_ const D3D12_BOX* pDstBox, _In_ const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->WriteToSubresource( DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReadFromSubresource( _Out_ void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, UINT SrcSubresource, _In_opt_ const D3D12_BOX* pSrcBox ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ReadFromSubresource( pDstData, DstRowPitch, DstDepthPitch, SrcSubresource, pSrcBox );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetHeapProperties( _Out_opt_ D3D12_HEAP_PROPERTIES* pHeapProperties, _Out_opt_ D3D12_HEAP_FLAGS* pHeapFlags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetHeapProperties( pHeapProperties, pHeapFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12CommandAllocator : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12CommandAllocator, D3D12Pageable, ID3D12CommandAllocator, ID3D12Pageable )
    public:
        void Reset( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class D3D12Fence : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Fence, D3D12Pageable, ID3D12Fence, ID3D12Pageable )
    public:
        UINT64 GetCompletedValue( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCompletedValue( );
        }

        void SetEventOnCompletion( UINT64 value, HANDLE eventHandle ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetEventOnCompletion( value, eventHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Signal( UINT64 value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Signal( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class D3D12Fence1 : public D3D12Fence
    {
    public:
        using Base = D3D12Fence;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Fence1, D3D12Fence, ID3D12Fence1, ID3D12Fence )
    public:
        D3D12_FENCE_FLAGS GetCreationFlags( void ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCreationFlags( );
        }
    };


    class D3D12PipelineState : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12PipelineState, D3D12Pageable, ID3D12PipelineState, ID3D12Pageable )
    public:
        void GetCachedBlob( _COM_Outptr_  ID3DBlob** ppBlob ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetCachedBlob( ppBlob );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D3D10Blob GetCachedBlob( ) const
        {
            ID3D10Blob* ptr = nullptr;
            GetCachedBlob( &ptr );
            return D3D10Blob( ptr, false );
        }

    };

    class D3D12DescriptorHeap : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DescriptorHeap, D3D12Pageable, ID3D12DescriptorHeap, ID3D12Pageable )
    public:
        D3D12_DESCRIPTOR_HEAP_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }

        D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCPUDescriptorHandleForHeapStart( );
        }

        D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandleForHeapStart( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetGPUDescriptorHandleForHeapStart( );
        }
    };

    class D3D12QueryHeap : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12QueryHeap, D3D12Pageable, ID3D12QueryHeap, ID3D12Pageable )
    public:
    };

    class D3D12CommandSignature : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12CommandSignature, D3D12Pageable, ID3D12CommandSignature, ID3D12Pageable )
    public:
    };


    class D3D12CommandList : public D3D12DeviceChild
    {
    public:
        using Base = D3D12DeviceChild;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12CommandList, D3D12DeviceChild, ID3D12CommandList, ID3D12DeviceChild )
    public:
        D3D12_COMMAND_LIST_TYPE GetType( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetType( );
        }
    };


    class D3D12GraphicsCommandList : public D3D12CommandList
    {
    public:
        using Base = D3D12CommandList;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12GraphicsCommandList, D3D12CommandList, ID3D12GraphicsCommandList, ID3D12CommandList )
    public:
        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Close( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( _In_  ID3D12CommandAllocator* pAllocator, _In_opt_  ID3D12PipelineState* pInitialState = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Reset( pAllocator, pInitialState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Reset( const D3D12CommandAllocator& allocator, const D3D12PipelineState& initialState ) const
        {
            Reset( allocator.GetInterfacePointer<ID3D12CommandAllocator>(), initialState.GetInterfacePointer<ID3D12PipelineState>() );
        }
        void Reset( const D3D12CommandAllocator& allocator ) const
        {
            Reset( allocator.GetInterfacePointer<ID3D12CommandAllocator>( ), nullptr );
        }


        void ClearState( _In_opt_  ID3D12PipelineState* pPipelineState = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearState( pPipelineState );
        }
        void ClearState( const D3D12PipelineState& pipelineState ) const
        {
            ClearState( pipelineState.GetInterfacePointer<ID3D12PipelineState>() );
        }


        void DrawInstanced(_In_ UINT VertexCountPerInstance, _In_ UINT InstanceCount, _In_ UINT StartVertexLocation, _In_ UINT StartInstanceLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawInstanced( VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation );
        }

        void DrawIndexedInstanced( _In_ UINT IndexCountPerInstance, _In_ UINT InstanceCount, _In_ UINT StartIndexLocation, _In_ INT BaseVertexLocation, _In_ UINT StartInstanceLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawIndexedInstanced( IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation );
        }

        void Dispatch( _In_ UINT threadGroupCountX, _In_ UINT threadGroupCountY, _In_ UINT threadGroupCountZ ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Dispatch( threadGroupCountX, threadGroupCountY, threadGroupCountZ );
        }

        void CopyBufferRegion( _In_ ID3D12Resource* dstBuffer, UINT64 dstOffset, _In_ ID3D12Resource* srcBuffer, UINT64 srcOffset, UINT64 numBytes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyBufferRegion( dstBuffer, dstOffset, srcBuffer, srcOffset, numBytes );
        }

        void CopyBufferRegion( const D3D12Resource& dstBuffer, UINT64 dstOffset, const D3D12Resource& srcBuffer, UINT64 srcOffset, UINT64 numBytes ) const
        {
            CopyBufferRegion( dstBuffer.GetInterfacePointer<ID3D12Resource>(), dstOffset, srcBuffer.GetInterfacePointer<ID3D12Resource>( ), srcOffset, numBytes );
        }


        void CopyTextureRegion( _In_ const D3D12_TEXTURE_COPY_LOCATION* pDst, UINT dstX, UINT dstY, UINT dstZ, _In_ const D3D12_TEXTURE_COPY_LOCATION* pSrc, _In_opt_ const D3D12_BOX* pSrcBox ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyTextureRegion( pDst, dstX, dstY, dstZ, pSrc, pSrcBox );
        }

        void CopyResource( _In_ ID3D12Resource* dstResource, _In_ ID3D12Resource* srcResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyResource( dstResource, srcResource );
        }

        void CopyResource( const D3D12Resource& dstResource, const D3D12Resource& srcResource ) const
        {
            CopyResource( dstResource.GetInterfacePointer<ID3D12Resource>( ), srcResource.GetInterfacePointer<ID3D12Resource>( ) );
        }

        void CopyTiles( _In_ ID3D12Resource* tiledResource, _In_ const D3D12_TILED_RESOURCE_COORDINATE* tileRegionStartCoordinate, _In_ const D3D12_TILE_REGION_SIZE* tileRegionSize, _In_ ID3D12Resource* buffer, UINT64 bufferStartOffsetInBytes, D3D12_TILE_COPY_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyTiles( tiledResource, tileRegionStartCoordinate, tileRegionSize, buffer, bufferStartOffsetInBytes, flags );
        }

        void CopyTiles( const D3D12Resource& tiledResource, _In_ const D3D12_TILED_RESOURCE_COORDINATE* tileRegionStartCoordinate, _In_ const D3D12_TILE_REGION_SIZE* tileRegionSize, const D3D12Resource& buffer, UINT64 bufferStartOffsetInBytes, D3D12_TILE_COPY_FLAGS flags ) const
        {
            CopyTiles( tiledResource.GetInterfacePointer<ID3D12Resource>( ), tileRegionStartCoordinate, tileRegionSize, buffer.GetInterfacePointer<ID3D12Resource>( ), bufferStartOffsetInBytes, flags );
        }

        void ResolveSubresource( _In_ ID3D12Resource* dstResource, _In_ UINT dstSubresource, _In_ ID3D12Resource* srcResource, _In_ UINT srcSubresource, _In_ DXGI_FORMAT format ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ResolveSubresource( dstResource, dstSubresource, srcResource, srcSubresource, format );
        }

        void ResolveSubresource( const D3D12Resource& dstResource, _In_ UINT dstSubresource, const D3D12Resource& srcResource, _In_ UINT srcSubresource, _In_ DXGI_FORMAT format ) const
        {
            ResolveSubresource( dstResource.GetInterfacePointer<ID3D12Resource>( ), dstSubresource, srcResource.GetInterfacePointer<ID3D12Resource>( ), srcSubresource, format );
        }

        void IASetPrimitiveTopology( _In_ D3D12_PRIMITIVE_TOPOLOGY primitiveTopology ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->IASetPrimitiveTopology( primitiveTopology );
        }

        void RSSetViewports( _In_range_( 0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )  UINT numViewports, _In_reads_( numViewports )  const D3D12_VIEWPORT* pViewports ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RSSetViewports( numViewports, pViewports );
        }

        void RSSetScissorRects( _In_range_( 0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )  UINT numRects, _In_reads_( numRects )  const D3D12_RECT* pRects ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RSSetScissorRects( numRects, pRects );
        }

        void OMSetBlendFactor( _In_reads_opt_( 4 ) const FLOAT BlendFactor[4] ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OMSetBlendFactor( BlendFactor );
        }

        void OMSetStencilRef( _In_ UINT stencilRef ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OMSetStencilRef( stencilRef );
        }

        void SetPipelineState( _In_  ID3D12PipelineState* pipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetPipelineState( pipelineState );
        }

        void SetPipelineState( const D3D12PipelineState& pipelineState ) const
        {
            SetPipelineState( pipelineState.GetInterfacePointer<ID3D12PipelineState>( ) );
        }

        void ResourceBarrier( _In_ UINT numBarriers, _In_reads_( numBarriers )  const D3D12_RESOURCE_BARRIER* pBarriers ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ResourceBarrier( numBarriers, pBarriers );
        }

        void ExecuteBundle( _In_ ID3D12GraphicsCommandList* commandList ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ExecuteBundle( commandList );
        }

        void ExecuteBundle( const D3D12GraphicsCommandList& commandList ) const
        {
            ExecuteBundle( commandList.GetInterfacePointer<ID3D12GraphicsCommandList>( ) );
        }

        void SetDescriptorHeaps( _In_  UINT numDescriptorHeaps, _In_reads_( numDescriptorHeaps )  ID3D12DescriptorHeap* const* descriptorHeapsPtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetDescriptorHeaps( numDescriptorHeaps, descriptorHeapsPtr );
        }

        template<size_t N>
        void SetDescriptorHeaps( const std::array<D3D12DescriptorHeap,N>& descriptorHeaps ) const
        {
            std::array<ID3D12DescriptorHeap*, N> heaps;
            for ( size_t i = 0; i < N; i++ )
            {
                heaps[i] = descriptorHeaps[i].GetInterfacePointer<ID3D12DescriptorHeap>( );
            }
            SetDescriptorHeaps(static_cast<UINT>(N), heaps.data() );
        }
        template<size_t N>
        void SetDescriptorHeaps( D3D12DescriptorHeap( &descriptorHeaps )[N] ) const
        {
            std::array<ID3D12DescriptorHeap*, N> heaps;
            for ( size_t i = 0; i < N; i++ )
            {
                heaps[i] = descriptorHeaps[i].GetInterfacePointer<ID3D12DescriptorHeap>( );
            }
            SetDescriptorHeaps( static_cast<UINT>( N ), heaps.data( ) );
        }
        void SetDescriptorHeaps( const D3D12DescriptorHeap& descriptorHeap ) const
        {
            ID3D12DescriptorHeap* ptr = descriptorHeap.GetInterfacePointer<ID3D12DescriptorHeap>( );
            SetDescriptorHeaps( 1, &ptr );
        }

        void SetComputeRootSignature( _In_opt_ ID3D12RootSignature* rootSignature = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetComputeRootSignature( rootSignature );
        }

        void SetComputeRootSignature( const D3D12RootSignature& rootSignature ) const
        {
            SetComputeRootSignature( rootSignature.GetInterfacePointer<ID3D12RootSignature>( ) );
        }

        void SetGraphicsRootSignature( _In_opt_ ID3D12RootSignature* rootSignature = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGraphicsRootSignature( rootSignature );
        }

        void SetGraphicsRootSignature( const D3D12RootSignature& rootSignature ) const
        {
            SetGraphicsRootSignature( rootSignature.GetInterfacePointer<ID3D12RootSignature>( ) );
        }

        void SetComputeRootDescriptorTable( _In_ UINT rootParameterIndex, _In_ D3D12_GPU_DESCRIPTOR_HANDLE baseDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetComputeRootDescriptorTable( rootParameterIndex, baseDescriptor );
        }

        void SetGraphicsRootDescriptorTable( _In_ UINT rootParameterIndex, _In_ D3D12_GPU_DESCRIPTOR_HANDLE baseDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGraphicsRootDescriptorTable( rootParameterIndex, baseDescriptor );
        }

        void SetComputeRoot32BitConstant( _In_ UINT rootParameterIndex, _In_ UINT srcData, _In_ UINT destOffsetIn32BitValues ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetComputeRoot32BitConstant( rootParameterIndex, srcData, destOffsetIn32BitValues );
        }

        void SetGraphicsRoot32BitConstant( _In_ UINT rootParameterIndex, _In_ UINT srcData, _In_ UINT destOffsetIn32BitValues ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGraphicsRoot32BitConstant( rootParameterIndex, srcData, destOffsetIn32BitValues );
        }

        void SetComputeRoot32BitConstants( _In_ UINT rootParameterIndex, _In_ UINT num32BitValuesToSet, _In_reads_( num32BitValuesToSet * sizeof( UINT ) )  const void* pSrcData, _In_  UINT destOffsetIn32BitValues ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetComputeRoot32BitConstants( rootParameterIndex, num32BitValuesToSet, pSrcData, destOffsetIn32BitValues );
        }

        void SetGraphicsRoot32BitConstants( _In_ UINT rootParameterIndex, _In_ UINT num32BitValuesToSet, _In_reads_( num32BitValuesToSet * sizeof( UINT ) )  const void* pSrcData, _In_  UINT destOffsetIn32BitValues ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGraphicsRoot32BitConstants( rootParameterIndex, num32BitValuesToSet, pSrcData, destOffsetIn32BitValues );
        }

        void SetComputeRootConstantBufferView( _In_ UINT rootParameterIndex, _In_ D3D12_GPU_VIRTUAL_ADDRESS bufferLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetComputeRootConstantBufferView( rootParameterIndex, bufferLocation );
        }

        void SetGraphicsRootConstantBufferView( _In_ UINT rootParameterIndex, _In_ D3D12_GPU_VIRTUAL_ADDRESS bufferLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGraphicsRootConstantBufferView( rootParameterIndex, bufferLocation );
        }

        void SetComputeRootShaderResourceView( _In_ UINT rootParameterIndex, _In_ D3D12_GPU_VIRTUAL_ADDRESS bufferLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetComputeRootShaderResourceView( rootParameterIndex, bufferLocation );
        }

        void SetGraphicsRootShaderResourceView( _In_ UINT rootParameterIndex, _In_ D3D12_GPU_VIRTUAL_ADDRESS bufferLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGraphicsRootShaderResourceView( rootParameterIndex, bufferLocation );
        }

        void SetComputeRootUnorderedAccessView( _In_ UINT rootParameterIndex, _In_ D3D12_GPU_VIRTUAL_ADDRESS bufferLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetComputeRootUnorderedAccessView( rootParameterIndex, bufferLocation );
        }

        void SetGraphicsRootUnorderedAccessView( _In_ UINT rootParameterIndex, _In_ D3D12_GPU_VIRTUAL_ADDRESS bufferLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGraphicsRootUnorderedAccessView( rootParameterIndex, bufferLocation );
        }

        void IASetIndexBuffer( _In_opt_ const D3D12_INDEX_BUFFER_VIEW* pView ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->IASetIndexBuffer( pView );
        }

        void IASetVertexBuffers( _In_ UINT startSlot, _In_ UINT numViews, _In_reads_opt_( numViews ) const D3D12_VERTEX_BUFFER_VIEW* pViews ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->IASetVertexBuffers( startSlot, numViews, pViews );
        }

        void SOSetTargets( _In_ UINT startSlot, _In_ UINT numViews, _In_reads_opt_( numViews )  const D3D12_STREAM_OUTPUT_BUFFER_VIEW* pViews ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SOSetTargets( startSlot, numViews, pViews );
        }

        void OMSetRenderTargets( _In_ UINT numRenderTargetDescriptors, _In_opt_ const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors, _In_ bool rtsSingleHandleToDescriptorRange = false, _In_opt_ const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OMSetRenderTargets( numRenderTargetDescriptors, pRenderTargetDescriptors, rtsSingleHandleToDescriptorRange, pDepthStencilDescriptor );
        }

        void ClearDepthStencilView( _In_ D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView, _In_ D3D12_CLEAR_FLAGS clearFlags, _In_ FLOAT depth, _In_ UINT8 stencil, _In_ UINT numRects, _In_reads_( numRects ) const D3D12_RECT* pRects ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearDepthStencilView( depthStencilView, clearFlags, depth, stencil, numRects, pRects );
        }

        void ClearRenderTargetView( _In_ D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView, _In_ const FLOAT colorRGBA[4], _In_ UINT numRects = 0, _In_reads_( numRects ) const D3D12_RECT* pRects = nullptr) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearRenderTargetView( renderTargetView, colorRGBA, numRects, pRects );
        }

        void ClearUnorderedAccessViewUint( _In_ D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap, _In_ D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle, _In_ ID3D12Resource* resource, _In_ const UINT values[4], _In_ UINT numRects, _In_reads_( numRects ) const D3D12_RECT* rectsPtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearUnorderedAccessViewUint( viewGPUHandleInCurrentHeap, viewCPUHandle, resource, values, numRects, rectsPtr );
        }

        void ClearUnorderedAccessViewUint( _In_ D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap, _In_ D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle, const D3D12Resource& resource, _In_ const UINT values[4], _In_ UINT numRects, _In_reads_( numRects ) const D3D12_RECT* rectsPtr ) const
        {
            ClearUnorderedAccessViewUint( viewGPUHandleInCurrentHeap, viewCPUHandle, resource.GetInterfacePointer<ID3D12Resource>(), values, numRects, rectsPtr );
        }

        void ClearUnorderedAccessViewFloat( _In_ D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap, _In_ D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle, _In_ ID3D12Resource* resource, _In_ const FLOAT values[4], _In_ UINT numRects, _In_reads_( numRects ) const D3D12_RECT* rectsPtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearUnorderedAccessViewFloat( viewGPUHandleInCurrentHeap, viewCPUHandle, resource, values, numRects, rectsPtr );
        }

        void ClearUnorderedAccessViewFloat( _In_ D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap, _In_ D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle, const D3D12Resource& resource, _In_ const FLOAT values[4], _In_ UINT numRects, _In_reads_( numRects ) const D3D12_RECT* rectsPtr ) const
        {
            ClearUnorderedAccessViewFloat( viewGPUHandleInCurrentHeap, viewCPUHandle, resource.GetInterfacePointer<ID3D12Resource>( ), values, numRects, rectsPtr );
        }

        void DiscardResource( _In_ ID3D12Resource* resource, _In_opt_ const D3D12_DISCARD_REGION* region = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DiscardResource( resource, region );
        }

        void DiscardResource( const D3D12Resource& resource, _In_opt_ const D3D12_DISCARD_REGION* region = nullptr ) const
        {
            DiscardResource( resource.GetInterfacePointer<ID3D12Resource>( ), region );
        }

        void BeginQuery( _In_ ID3D12QueryHeap* queryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT index ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginQuery( queryHeap, type, index );
        }

        void BeginQuery( const D3D12QueryHeap& queryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT index ) const
        {
            BeginQuery( queryHeap.GetInterfacePointer<ID3D12QueryHeap>( ), type, index );
        }


        void EndQuery( _In_ ID3D12QueryHeap* queryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT index ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EndQuery( queryHeap, type, index );
        }

        void EndQuery( const D3D12QueryHeap& queryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT index ) const
        {
            EndQuery( queryHeap.GetInterfacePointer<ID3D12QueryHeap>( ), type, index );
        }

        void ResolveQueryData( _In_ ID3D12QueryHeap* pQueryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT startIndex, _In_ UINT numQueries, _In_ ID3D12Resource* pDestinationBuffer, _In_ UINT64 alignedDestinationBufferOffset ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ResolveQueryData( pQueryHeap, type, startIndex, numQueries, pDestinationBuffer, alignedDestinationBufferOffset );
        }

        void SetPredication( _In_opt_ ID3D12Resource* pBuffer, _In_ UINT64 alignedBufferOffset, _In_ D3D12_PREDICATION_OP operation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetPredication( pBuffer, alignedBufferOffset, operation );
        }

        void SetMarker( UINT metadata, _In_reads_bytes_opt_( size )  const void* pData, UINT size ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetMarker( metadata, pData, size );
        }

        void BeginEvent( UINT metadata, _In_reads_bytes_opt_( size )  const void* pData, UINT size ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginEvent( metadata, pData, size );
        }

        void EndEvent( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EndEvent( );
        }

        void ExecuteIndirect( _In_ ID3D12CommandSignature* pCommandSignature, _In_ UINT maxCommandCount, _In_ ID3D12Resource* pArgumentBuffer, _In_ UINT64 argumentBufferOffset, _In_opt_ ID3D12Resource* pCountBuffer, _In_ UINT64 countBufferOffset ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ExecuteIndirect( pCommandSignature, maxCommandCount, pArgumentBuffer, argumentBufferOffset, pCountBuffer, countBufferOffset );
        }
    };


    class D3D12GraphicsCommandList1 : public D3D12GraphicsCommandList
    {
    public:
        using Base = D3D12GraphicsCommandList;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12GraphicsCommandList1, D3D12GraphicsCommandList, ID3D12GraphicsCommandList1, ID3D12GraphicsCommandList )
    public:
        void AtomicCopyBufferUINT(_In_ ID3D12Resource* pDstBuffer, UINT64 dstOffset, _In_ ID3D12Resource* pSrcBuffer, UINT64 srcOffset, UINT dependencies, _In_reads_( dependencies )  ID3D12Resource* const* ppDependentResources, _In_reads_( dependencies )  const D3D12_SUBRESOURCE_RANGE_UINT64* pDependentSubresourceRanges ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AtomicCopyBufferUINT( pDstBuffer, dstOffset, pSrcBuffer, srcOffset, dependencies, ppDependentResources, pDependentSubresourceRanges );
        }

        void AtomicCopyBufferUINT64( _In_ ID3D12Resource* pDstBuffer, UINT64 dstOffset, _In_ ID3D12Resource* pSrcBuffer, UINT64 srcOffset, UINT dependencies, _In_reads_( dependencies ) ID3D12Resource* const* ppDependentResources, _In_reads_( dependencies ) const D3D12_SUBRESOURCE_RANGE_UINT64* pDependentSubresourceRanges ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AtomicCopyBufferUINT64( pDstBuffer, dstOffset, pSrcBuffer, srcOffset, dependencies, ppDependentResources, pDependentSubresourceRanges );
        }

        void OMSetDepthBounds( _In_ FLOAT min, _In_ FLOAT max ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OMSetDepthBounds( min, max );
        }

        void SetSamplePositions( _In_ UINT numSamplesPerPixel, _In_ UINT numPixels, _In_reads_( numSamplesPerPixel* numPixels )  D3D12_SAMPLE_POSITION* pSamplePositions ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetSamplePositions( numSamplesPerPixel, numPixels, pSamplePositions );
        }

        void ResolveSubresourceRegion( _In_ ID3D12Resource* pDstResource, _In_ UINT dstSubresource, _In_ UINT dstX, _In_ UINT dstY, _In_ ID3D12Resource* pSrcResource, _In_ UINT srcSubresource, _In_opt_ D3D12_RECT* pSrcRect, _In_ DXGI_FORMAT format, _In_ D3D12_RESOLVE_MODE resolveMode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ResolveSubresourceRegion( pDstResource, dstSubresource, dstX, dstY, pSrcResource, srcSubresource, pSrcRect, format, resolveMode );
        }

        void SetViewInstanceMask( _In_ UINT mask ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetViewInstanceMask( mask );
        }
    };

    class D3D12GraphicsCommandList2 : public D3D12GraphicsCommandList1
    {
    public:
        using Base = D3D12GraphicsCommandList1;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12GraphicsCommandList2, D3D12GraphicsCommandList1, ID3D12GraphicsCommandList2, ID3D12GraphicsCommandList1 )
    public:
        void WriteBufferImmediate( UINT count, _In_reads_( count ) const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* pParams, _In_reads_opt_( count ) const D3D12_WRITEBUFFERIMMEDIATE_MODE* pModes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->WriteBufferImmediate( count, pParams, pModes );
        }
    };


    class D3D12CommandQueue : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12CommandQueue, D3D12Pageable, ID3D12CommandQueue, ID3D12Pageable )
    public:
        
        void UpdateTileMappings( _In_ ID3D12Resource* pResource, UINT numResourceRegions, _In_reads_opt_( numResourceRegions ) const D3D12_TILED_RESOURCE_COORDINATE* pResourceRegionStartCoordinates, _In_reads_opt_( numResourceRegions ) const D3D12_TILE_REGION_SIZE* pResourceRegionSizes, _In_opt_  ID3D12Heap* pHeap, UINT numRanges, _In_reads_opt_( numRanges ) const D3D12_TILE_RANGE_FLAGS* pRangeFlags, _In_reads_opt_( numRanges ) const UINT* pHeapRangeStartOffsets, _In_reads_opt_( numRanges ) const UINT* pRangeTileCounts, D3D12_TILE_MAPPING_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->UpdateTileMappings( pResource, numResourceRegions, pResourceRegionStartCoordinates, pResourceRegionSizes, pHeap, numRanges, pRangeFlags, pHeapRangeStartOffsets, pRangeTileCounts, flags );
        }

        void CopyTileMappings( _In_ ID3D12Resource* pDstResource, _In_ const D3D12_TILED_RESOURCE_COORDINATE* pDstRegionStartCoordinate, _In_ ID3D12Resource* pSrcResource, _In_ const D3D12_TILED_RESOURCE_COORDINATE* pSrcRegionStartCoordinate, _In_ const D3D12_TILE_REGION_SIZE* pRegionSize, D3D12_TILE_MAPPING_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyTileMappings( pDstResource, pDstRegionStartCoordinate, pSrcResource, pSrcRegionStartCoordinate, pRegionSize, flags );
        }

        void ExecuteCommandLists( _In_ UINT numCommandLists, _In_reads_( numCommandLists ) ID3D12CommandList* const* ppCommandLists ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ExecuteCommandLists( numCommandLists, ppCommandLists );
        }

        void ExecuteCommandLists( const D3D12CommandList& commandList ) const
        {
            ID3D12CommandList* ptr = commandList.GetInterfacePointer<ID3D12CommandList>( );
            ExecuteCommandLists(1, &ptr );
        }


        void SetMarker( UINT metadata, _In_reads_bytes_opt_( size ) const void* pData, UINT size ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetMarker( metadata, pData, size );
        }

        void BeginEvent( UINT metadata, _In_reads_bytes_opt_( size )  const void* pData, UINT size ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginEvent( metadata, pData, size );
        }

        void EndEvent( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EndEvent( );
        }

        void Signal( ID3D12Fence* pFence, UINT64 value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Signal( pFence, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Wait( ID3D12Fence* pFence, UINT64 value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Wait( pFence, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetTimestampFrequency( _Out_ UINT64* pFrequency ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetTimestampFrequency( pFrequency );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetClockCalibration( _Out_ UINT64* pGpuTimestamp, _Out_ UINT64* pCpuTimestamp ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetClockCalibration( pGpuTimestamp, pCpuTimestamp );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D3D12_COMMAND_QUEUE_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }

    };

    class D3D12Device : public D3D12Object
    {
    public:
        using Base = D3D12Object;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device, D3D12Object, ID3D12Device, ID3D12Object )
    public:
        UINT GetNodeCount( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNodeCount( );
        }

        void CreateCommandQueue(_In_ const D3D12_COMMAND_QUEUE_DESC* pDesc, REFIID riid, _COM_Outptr_ void** ppCommandQueue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandQueue( pDesc, riid, ppCommandQueue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        template<typename T = D3D12CommandQueue>
            requires std::is_base_of_v< D3D12CommandQueue, T>
        T CreateCommandQueue( _In_ const D3D12_COMMAND_QUEUE_DESC& desc ) const
        {
            using IntfT = T::InterfaceType;
            IID IntfTId = __uuidof( IntfT );

            IntfT* intf = nullptr;

            CreateCommandQueue( &desc, IntfTId, (void**)&intf );
            T result( intf );
            return result;
        }


        void CreateCommandAllocator( _In_ D3D12_COMMAND_LIST_TYPE type, REFIID riid, _COM_Outptr_ void** ppCommandAllocator ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandAllocator( type, riid, ppCommandAllocator );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T = D3D12CommandAllocator>
            requires std::is_base_of_v<D3D12CommandAllocator, T>
        T CreateCommandAllocator( _In_ D3D12_COMMAND_LIST_TYPE type ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateCommandAllocator( type, refiid, (void**)&ptr );
            return T( ptr, false );
        }


        void CreateGraphicsPipelineState( _In_ const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc, REFIID riid, _COM_Outptr_ void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateGraphicsPipelineState( pDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateComputePipelineState(_In_ const D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc, REFIID riid, _COM_Outptr_ void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateComputePipelineState( pDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateCommandList( _In_ UINT nodeMask, _In_ D3D12_COMMAND_LIST_TYPE type, _In_ ID3D12CommandAllocator* pCommandAllocator, _In_opt_ ID3D12PipelineState* pInitialState, REFIID riid, _COM_Outptr_ void** ppCommandList ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandList( nodeMask, type, pCommandAllocator, pInitialState, riid, ppCommandList );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T = D3D12GraphicsCommandList>
            requires std::is_base_of_v<D3D12GraphicsCommandList, T>
        T CreateCommandList( _In_ UINT nodeMask, _In_ D3D12_COMMAND_LIST_TYPE type, const D3D12CommandAllocator& commandAllocator, const D3D12PipelineState& initialState ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateCommandList( nodeMask, type, commandAllocator.GetInterfacePointer<ID3D12CommandAllocator>(), initialState.GetInterfacePointer<ID3D12PipelineState>( ), refiid, (void**)&ptr );
            return T( ptr, false );
        }
        template <typename T = D3D12GraphicsCommandList>
            requires std::is_base_of_v<D3D12GraphicsCommandList, T>
        T CreateCommandList( _In_ UINT nodeMask, _In_ D3D12_COMMAND_LIST_TYPE type, const D3D12CommandAllocator& commandAllocator ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateCommandList( nodeMask, type, commandAllocator.GetInterfacePointer<ID3D12CommandAllocator>( ), nullptr, refiid, (void**)&ptr );
            return T( ptr, false );
        }


        void CheckFeatureSupport( D3D12_FEATURE feature, _Inout_updates_bytes_( featureSupportDataSize )  void* pFeatureSupportData, UINT featureSupportDataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CheckFeatureSupport( feature, pFeatureSupportData, featureSupportDataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateDescriptorHeap( _In_ const D3D12_DESCRIPTOR_HEAP_DESC* descriptorHeapDesc, REFIID riid, _COM_Outptr_ void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDescriptorHeap( descriptorHeapDesc, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T = D3D12DescriptorHeap>
            requires std::is_base_of_v<D3D12DescriptorHeap,T>
        T CreateDescriptorHeap( _In_ const D3D12_DESCRIPTOR_HEAP_DESC& descriptorHeapDesc ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateDescriptorHeap( &descriptorHeapDesc, refiid, (void**)&ptr );
            return T( ptr, false );
        }



        UINT GetDescriptorHandleIncrementSize( _In_ D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDescriptorHandleIncrementSize( descriptorHeapType );
        }

        void CreateRootSignature( _In_ UINT nodeMask, _In_reads_( blobLengthInBytes )  const void* pBlobWithRootSignature, _In_ SIZE_T blobLengthInBytes, REFIID riid, _COM_Outptr_ void** ppvRootSignature ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateRootSignature( nodeMask, pBlobWithRootSignature, blobLengthInBytes, riid, ppvRootSignature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateConstantBufferView( _In_opt_ const D3D12_CONSTANT_BUFFER_VIEW_DESC* pDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateConstantBufferView( pDesc, destDescriptor );
        }

        void CreateShaderResourceView(_In_opt_ ID3D12Resource* pResource, _In_opt_ const D3D12_SHADER_RESOURCE_VIEW_DESC* pDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateShaderResourceView( pResource, pDesc, destDescriptor );
        }

        void CreateUnorderedAccessView(_In_opt_ ID3D12Resource* pResource, _In_opt_ ID3D12Resource* pCounterResource, _In_opt_ const D3D12_UNORDERED_ACCESS_VIEW_DESC* pDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateUnorderedAccessView( pResource, pCounterResource, pDesc, destDescriptor );
        }

        void CreateRenderTargetView(_In_opt_ ID3D12Resource* resource, _In_opt_ const D3D12_RENDER_TARGET_VIEW_DESC* desc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateRenderTargetView( resource, desc, destDescriptor );
        }

        void CreateRenderTargetView( const D3D12Resource& resource, _In_opt_ const D3D12_RENDER_TARGET_VIEW_DESC& desc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateRenderTargetView( resource.GetInterfacePointer<ID3D12Resource>(), &desc, destDescriptor );
        }
        void CreateRenderTargetView( const D3D12Resource& resource, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateRenderTargetView( resource.GetInterfacePointer<ID3D12Resource>( ), nullptr, destDescriptor );
        }


        void CreateDepthStencilView( _In_opt_ ID3D12Resource* pResource, _In_opt_ const D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateDepthStencilView( pResource, pDesc, destDescriptor );
        }

        void CreateSampler( _In_ const D3D12_SAMPLER_DESC* pDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateSampler( pDesc, destDescriptor );
        }

        void CopyDescriptors( _In_ UINT numDestDescriptorRanges, _In_reads_( numDestDescriptorRanges ) const D3D12_CPU_DESCRIPTOR_HANDLE* pDestDescriptorRangeStarts, _In_reads_opt_( numDestDescriptorRanges ) const UINT* pDestDescriptorRangeSizes, _In_ UINT numSrcDescriptorRanges, _In_reads_( numSrcDescriptorRanges ) const D3D12_CPU_DESCRIPTOR_HANDLE* pSrcDescriptorRangeStarts, _In_reads_opt_( numSrcDescriptorRanges ) const UINT* pSrcDescriptorRangeSizes, _In_ D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapsType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyDescriptors( numDestDescriptorRanges, pDestDescriptorRangeStarts, pDestDescriptorRangeSizes, numSrcDescriptorRanges, pSrcDescriptorRangeStarts, pSrcDescriptorRangeSizes, descriptorHeapsType );
        }

        void CopyDescriptorsSimple( _In_ UINT numDescriptors, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptorRangeStart, _In_ D3D12_CPU_DESCRIPTOR_HANDLE srcDescriptorRangeStart, _In_ D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapsType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyDescriptorsSimple( numDescriptors, destDescriptorRangeStart, srcDescriptorRangeStart, descriptorHeapsType );
        }

        D3D12_RESOURCE_ALLOCATION_INFO GetResourceAllocationInfo( _In_ UINT visibleMask, _In_ UINT numResourceDescs, _In_reads_( numResourceDescs )  const D3D12_RESOURCE_DESC* pResourceDescs ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetResourceAllocationInfo( visibleMask, numResourceDescs, pResourceDescs );
        }

        D3D12_HEAP_PROPERTIES GetCustomHeapProperties(_In_ UINT nodeMask, D3D12_HEAP_TYPE heapType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCustomHeapProperties( nodeMask, heapType );
        }

        void CreateCommittedResource( _In_ const D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS heapFlags, _In_ const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES initialResourceState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue, REFIID riidResource, _COM_Outptr_opt_  void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommittedResource( pHeapProperties, heapFlags, pDesc, initialResourceState, pOptimizedClearValue, riidResource, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateHeap( _In_ const D3D12_HEAP_DESC* pDesc, REFIID riid, _COM_Outptr_opt_  void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateHeap( pDesc, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreatePlacedResource( _In_ ID3D12Heap* pHeap, UINT64 heapOffset, _In_ const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES initialState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue, REFIID riid, _COM_Outptr_opt_  void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreatePlacedResource( pHeap, heapOffset, pDesc, initialState, pOptimizedClearValue, riid, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateReservedResource( _In_ const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES initialState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue, REFIID riid, _COM_Outptr_opt_ void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateReservedResource( pDesc, initialState, pOptimizedClearValue, riid, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateSharedHandle( _In_ ID3D12DeviceChild* pObject, _In_opt_ const SECURITY_ATTRIBUTES* pAttributes, DWORD access, _In_opt_ LPCWSTR name, _Out_  HANDLE* pHandle ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateSharedHandle( pObject, pAttributes, access, name, pHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OpenSharedHandle( _In_ HANDLE NTHandle, REFIID riid, _COM_Outptr_opt_  void** ppvObj ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->OpenSharedHandle( NTHandle, riid, ppvObj );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OpenSharedHandleByName( _In_ LPCWSTR Name, DWORD Access, _Out_  HANDLE* pNTHandle ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->OpenSharedHandleByName( Name, Access, pNTHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void MakeResident( UINT NumObjects, _In_reads_( NumObjects )  ID3D12Pageable* const* ppObjects ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->MakeResident( NumObjects, ppObjects );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Evict( UINT NumObjects, _In_reads_( NumObjects )  ID3D12Pageable* const* ppObjects ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Evict( NumObjects, ppObjects );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateFence( UINT64 InitialValue, D3D12_FENCE_FLAGS Flags, REFIID riid, _COM_Outptr_ void** ppFence ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateFence( InitialValue, Flags, riid, ppFence );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T = D3D12Fence>
            requires std::is_base_of_v<D3D12Fence,T>
        T CreateFence( UINT64 initialValue, D3D12_FENCE_FLAGS flags ) const
        {
            using IntfT = T::InterfaceType;
            IID IntfTId = __uuidof( IntfT );

            IntfT* intf = nullptr;

            CreateFence( initialValue, flags, IntfTId, (void**)&intf );
            T result( intf );
            return result;
        }


        void GetDeviceRemovedReason( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetDeviceRemovedReason( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCopyableFootprints( _In_ const D3D12_RESOURCE_DESC* pResourceDesc, _In_range_( 0, D3D12_REQ_SUBRESOURCES ) UINT FirstSubresource, _In_range_( 0, D3D12_REQ_SUBRESOURCES - FirstSubresource ) UINT NumSubresources, UINT64 BaseOffset, _Out_writes_opt_( NumSubresources ) D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts, _Out_writes_opt_( NumSubresources ) UINT* pNumRows, _Out_writes_opt_( NumSubresources ) UINT64* pRowSizeInBytes, _Out_opt_  UINT64* pTotalBytes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetCopyableFootprints( pResourceDesc, FirstSubresource, NumSubresources, BaseOffset, pLayouts, pNumRows, pRowSizeInBytes, pTotalBytes );
        }

        void CreateQueryHeap( _In_ const D3D12_QUERY_HEAP_DESC* pDesc, REFIID riid, _COM_Outptr_opt_  void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateQueryHeap( pDesc, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetStablePowerState( BOOL enable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetStablePowerState( enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HRESULT CreateCommandSignature( _In_ const D3D12_COMMAND_SIGNATURE_DESC* pDesc, _In_opt_ ID3D12RootSignature* pRootSignature, REFIID riid, _COM_Outptr_opt_  void** ppvCommandSignature ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandSignature( pDesc, pRootSignature, riid, ppvCommandSignature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetResourceTiling( _In_ ID3D12Resource* pTiledResource, _Out_opt_  UINT* pNumTilesForEntireResource, _Out_opt_  D3D12_PACKED_MIP_INFO* pPackedMipDesc, _Out_opt_  D3D12_TILE_SHAPE* pStandardTileShapeForNonPackedMips, _Inout_opt_  UINT* pNumSubresourceTilings, _In_ UINT FirstSubresourceTilingToGet, _Out_writes_( *pNumSubresourceTilings )  D3D12_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetResourceTiling( pTiledResource, pNumTilesForEntireResource, pPackedMipDesc, pStandardTileShapeForNonPackedMips, pNumSubresourceTilings, FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips );
        }

        LUID GetAdapterLuid( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetAdapterLuid( );
        }
    };

    class D3D12PipelineLibrary : public D3D12DeviceChild
    {
    public:
        using Base = D3D12DeviceChild;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12PipelineLibrary, D3D12DeviceChild, ID3D12PipelineLibrary, ID3D12DeviceChild )
    public:
        void StorePipeline( _In_opt_  LPCWSTR pName, _In_  ID3D12PipelineState* pPipeline ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->StorePipeline( pName, pPipeline );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void LoadGraphicsPipeline( _In_  LPCWSTR pName, _In_  const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc, REFIID riid, _COM_Outptr_  void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->LoadGraphicsPipeline( pName, pDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void LoadComputePipeline( _In_  LPCWSTR pName, _In_  const D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc, REFIID riid, _COM_Outptr_  void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->LoadComputePipeline( pName, pDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        SIZE_T GetSerializedSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSerializedSize( );
        }

        void Serialize( _Out_writes_( DataSizeInBytes )  void* pData, SIZE_T DataSizeInBytes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Serialize( pData, DataSizeInBytes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12PipelineLibrary1 : public D3D12PipelineLibrary
    {
    public:
        using Base = D3D12PipelineLibrary;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12PipelineLibrary1, D3D12PipelineLibrary, ID3D12PipelineLibrary1, ID3D12PipelineLibrary )
    public:
        void LoadPipeline( _In_  LPCWSTR pName, _In_  const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc, REFIID riid, _COM_Outptr_  void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->LoadPipeline( pName, pDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class D3D12Device1 : public D3D12Device
    {
    public:
        using Base = D3D12Device;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device1, D3D12Device, ID3D12Device1, ID3D12Device )
    public:
        void CreatePipelineLibrary( _In_reads_( BlobLength )  const void* pLibraryBlob, SIZE_T BlobLength, REFIID riid, _COM_Outptr_  void** ppPipelineLibrary ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreatePipelineLibrary( pLibraryBlob, BlobLength, riid, ppPipelineLibrary );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetEventOnMultipleFenceCompletion( _In_reads_( NumFences )  ID3D12Fence* const* ppFences, _In_reads_( NumFences )  const UINT64* pFenceValues, UINT NumFences, D3D12_MULTIPLE_FENCE_WAIT_FLAGS Flags, HANDLE hEvent ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetEventOnMultipleFenceCompletion( ppFences, pFenceValues, NumFences, Flags, hEvent );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetResidencyPriority( UINT NumObjects, _In_reads_( NumObjects ) ID3D12Pageable* const* ppObjects, _In_reads_( NumObjects ) const D3D12_RESIDENCY_PRIORITY* pPriorities ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetResidencyPriority( NumObjects, ppObjects, pPriorities );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class D3D12Device2 : public D3D12Device1
    {
    public:
        using Base = D3D12Device1;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device2, D3D12Device1, ID3D12Device2, ID3D12Device1 )
    public:
        void CreatePipelineState( const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc, REFIID riid, _COM_Outptr_  void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreatePipelineState( pDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12Device3 : public D3D12Device2
    {
    public:
        using Base = D3D12Device2;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device3, D3D12Device2, ID3D12Device3, ID3D12Device2 )
    public:
        void OpenExistingHeapFromAddress( _In_  const void* pAddress, REFIID riid, _COM_Outptr_  void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->OpenExistingHeapFromAddress( pAddress, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void OpenExistingHeapFromFileMapping( _In_  HANDLE hFileMapping, REFIID riid, _COM_Outptr_  void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->OpenExistingHeapFromFileMapping( hFileMapping, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EnqueueMakeResident( D3D12_RESIDENCY_FLAGS Flags, UINT NumObjects, _In_reads_( NumObjects )  ID3D12Pageable* const* ppObjects, _In_  ID3D12Fence* pFenceToSignal, UINT64 FenceValueToSignal ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EnqueueMakeResident( Flags, NumObjects, ppObjects, _In_  pFenceToSignal, FenceValueToSignal );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

    };


    class D3D12ProtectedSession : public D3D12DeviceChild
    {
    public:
        using Base = D3D12DeviceChild;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12ProtectedSession, D3D12DeviceChild, ID3D12ProtectedSession, ID3D12DeviceChild )
    public:
        void GetStatusFence( REFIID riid, _COM_Outptr_opt_  void** ppFence ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetStatusFence( riid, ppFence );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D3D12_PROTECTED_SESSION_STATUS GetSessionStatus( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetSessionStatus( );
        }
    };

    class D3D12ProtectedResourceSession : public D3D12ProtectedSession
    {
    public:
        using Base = D3D12ProtectedSession;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12ProtectedResourceSession, D3D12ProtectedSession, ID3D12ProtectedResourceSession, ID3D12ProtectedSession )
    public:
        D3D12_PROTECTED_RESOURCE_SESSION_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }
    };

    class D3D12Device4 : public D3D12Device3
    {
    public:
        using Base = D3D12Device3;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device4, D3D12Device3, ID3D12Device4, ID3D12Device3 )
    public:
        void CreateCommandList1( _In_  UINT nodeMask, _In_  D3D12_COMMAND_LIST_TYPE type, _In_  D3D12_COMMAND_LIST_FLAGS flags, REFIID riid, _COM_Outptr_  void** ppCommandList ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandList1( nodeMask, type, flags, riid, ppCommandList );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateProtectedResourceSession( _In_  const D3D12_PROTECTED_RESOURCE_SESSION_DESC* pDesc, _In_  REFIID riid, _COM_Outptr_  void** ppSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateProtectedResourceSession( pDesc, riid, ppSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateCommittedResource1( _In_  const D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS HeapFlags, _In_  const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialResourceState, _In_opt_  const D3D12_CLEAR_VALUE* pOptimizedClearValue, _In_opt_  ID3D12ProtectedResourceSession* pProtectedSession, REFIID riidResource, _COM_Outptr_opt_  void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommittedResource1( pHeapProperties, HeapFlags, pDesc, InitialResourceState, pOptimizedClearValue, pProtectedSession, riidResource, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateHeap1( _In_  const D3D12_HEAP_DESC* pDesc, _In_opt_  ID3D12ProtectedResourceSession* pProtectedSession, REFIID riid, _COM_Outptr_opt_  void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateHeap1( pDesc, pProtectedSession, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateReservedResource1( _In_  const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialState, _In_opt_  const D3D12_CLEAR_VALUE* pOptimizedClearValue, _In_opt_  ID3D12ProtectedResourceSession* pProtectedSession, REFIID riid, _COM_Outptr_opt_  void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateReservedResource1( pDesc, InitialState, pOptimizedClearValue, pProtectedSession, riid, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D3D12_RESOURCE_ALLOCATION_INFO GetResourceAllocationInfo1( UINT visibleMask, UINT numResourceDescs, _In_reads_( numResourceDescs )  const D3D12_RESOURCE_DESC* pResourceDescs, _Out_writes_opt_( numResourceDescs )  D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1 ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetResourceAllocationInfo1( visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1 );
        }
    };

    class D3D12LifetimeOwner : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12LifetimeOwner, Unknown, ID3D12LifetimeOwner, IUnknown )
    public:
        void LifetimeStateUpdated( D3D12_LIFETIME_STATE newState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->LifetimeStateUpdated( newState );
        }
    };

    class D3D12SwapChainAssistant : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12SwapChainAssistant, Unknown, ID3D12SwapChainAssistant, IUnknown )
    public:
        LUID GetLUID( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetLUID( );
        }

        void GetSwapChainObject( REFIID riid, _COM_Outptr_  void** ppv ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetSwapChainObject( riid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetCurrentResourceAndCommandQueue( REFIID riidResource, _COM_Outptr_  void** ppvResource, REFIID riidQueue, _COM_Outptr_  void** ppvQueue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetCurrentResourceAndCommandQueue( riidResource, ppvResource, riidQueue, ppvQueue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void InsertImplicitSync( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InsertImplicitSync( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12LifetimeTracker : public D3D12DeviceChild
    {
    public:
        using Base = D3D12DeviceChild;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12LifetimeTracker, D3D12DeviceChild, ID3D12LifetimeTracker, ID3D12DeviceChild )
    public:
        void DestroyOwnedObject( _In_ ID3D12DeviceChild* pObject ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->DestroyOwnedObject( pObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12StateObject : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12StateObject, D3D12Pageable, ID3D12StateObject, ID3D12Pageable )
    public:

    };

    class D3D12StateObjectProperties : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12StateObjectProperties, Unknown, ID3D12StateObjectProperties, IUnknown )
    public:
        void* GetShaderIdentifier( _In_  LPCWSTR pExportName ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetShaderIdentifier( pExportName );
        }

        UINT64 GetShaderStackSize( _In_  LPCWSTR pExportName ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetShaderStackSize( pExportName );
        }

        UINT64 GetPipelineStackSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetPipelineStackSize( );
        }

        void SetPipelineStackSize( UINT64 PipelineStackSizeInBytes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetPipelineStackSize( PipelineStackSizeInBytes );
        }
    };

    class D3D12Device5 : public D3D12Device4
    {
    public:
        using Base = D3D12Device4;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device5, D3D12Device4, ID3D12Device5, ID3D12Device4 )
    public:
        HRESULT CreateLifetimeTracker( _In_  ID3D12LifetimeOwner* pOwner, REFIID riid, _COM_Outptr_  void** ppvTracker ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateLifetimeTracker( pOwner, riid, ppvTracker );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void RemoveDevice( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RemoveDevice( );
        }

        HRESULT EnumerateMetaCommands( _Inout_  UINT* pNumMetaCommands, _Out_writes_opt_( *pNumMetaCommands )  D3D12_META_COMMAND_DESC* pDescs ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EnumerateMetaCommands( pNumMetaCommands, pDescs );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HRESULT EnumerateMetaCommandParameters( _In_  REFGUID CommandId, _In_  D3D12_META_COMMAND_PARAMETER_STAGE Stage, _Out_opt_  UINT* pTotalStructureSizeInBytes, _Inout_  UINT* pParameterCount, _Out_writes_opt_( *pParameterCount )  D3D12_META_COMMAND_PARAMETER_DESC* pParameterDescs ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EnumerateMetaCommandParameters( CommandId, Stage, pTotalStructureSizeInBytes, pParameterCount, pParameterDescs );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HRESULT CreateMetaCommand( _In_  REFGUID CommandId, _In_  UINT NodeMask, _In_reads_bytes_opt_( CreationParametersDataSizeInBytes )  const void* pCreationParametersData, _In_  SIZE_T CreationParametersDataSizeInBytes, REFIID riid, _COM_Outptr_  void** ppMetaCommand ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateMetaCommand( CommandId, NodeMask, pCreationParametersData, CreationParametersDataSizeInBytes, riid, ppMetaCommand );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        HRESULT CreateStateObject( const D3D12_STATE_OBJECT_DESC* pDesc, REFIID riid, _COM_Outptr_  void** ppStateObject ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateStateObject( pDesc, riid, ppStateObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetRaytracingAccelerationStructurePrebuildInfo( _In_  const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS* pDesc, _Out_  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO* pInfo ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetRaytracingAccelerationStructurePrebuildInfo( pDesc, pInfo );
        }

        D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS CheckDriverMatchingIdentifier( _In_  D3D12_SERIALIZED_DATA_TYPE SerializedDataType, _In_  const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER* pIdentifierToCheck ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->CheckDriverMatchingIdentifier( SerializedDataType, pIdentifierToCheck );
        }
    };

    class D3D12DeviceRemovedExtendedDataSettings : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DeviceRemovedExtendedDataSettings, Unknown, ID3D12DeviceRemovedExtendedDataSettings, IUnknown )
    public:
        void SetAutoBreadcrumbsEnablement( D3D12_DRED_ENABLEMENT Enablement ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetAutoBreadcrumbsEnablement( Enablement );
        }

        void SetPageFaultEnablement( D3D12_DRED_ENABLEMENT Enablement ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetPageFaultEnablement( Enablement );
        }

        void SetWatsonDumpEnablement( D3D12_DRED_ENABLEMENT Enablement ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetWatsonDumpEnablement( Enablement );
        }
    };

    class D3D12DeviceRemovedExtendedDataSettings1 : public D3D12DeviceRemovedExtendedDataSettings
    {
    public:
        using Base = D3D12DeviceRemovedExtendedDataSettings;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DeviceRemovedExtendedDataSettings1, D3D12DeviceRemovedExtendedDataSettings, ID3D12DeviceRemovedExtendedDataSettings1, ID3D12DeviceRemovedExtendedDataSettings )
    public:
        void SetBreadcrumbContextEnablement( D3D12_DRED_ENABLEMENT Enablement ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetBreadcrumbContextEnablement( Enablement );
        }
    };

    class D3D12DeviceRemovedExtendedData : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DeviceRemovedExtendedData, Unknown, ID3D12DeviceRemovedExtendedData, IUnknown )
    public:
        void GetAutoBreadcrumbsOutput( _Out_  D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT* pOutput ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetAutoBreadcrumbsOutput( pOutput );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPageFaultAllocationOutput( _Out_  D3D12_DRED_PAGE_FAULT_OUTPUT* pOutput ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPageFaultAllocationOutput( pOutput );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12DeviceRemovedExtendedData1 : public D3D12DeviceRemovedExtendedData
    {
    public:
        using Base = D3D12DeviceRemovedExtendedData;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12DeviceRemovedExtendedData1, D3D12DeviceRemovedExtendedData, ID3D12DeviceRemovedExtendedData1, ID3D12DeviceRemovedExtendedData )
    public:
        void GetAutoBreadcrumbsOutput1(_Out_  D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1* pOutput ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetAutoBreadcrumbsOutput1( pOutput );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPageFaultAllocationOutput1(_Out_  D3D12_DRED_PAGE_FAULT_OUTPUT1* pOutput ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPageFaultAllocationOutput1( pOutput );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12Device6 : public D3D12Device5
    {
    public:
        using Base = D3D12Device5;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device6, D3D12Device5, ID3D12Device6, ID3D12Device5 )
    public:
        void SetBackgroundProcessingMode( D3D12_BACKGROUND_PROCESSING_MODE Mode, D3D12_MEASUREMENTS_ACTION MeasurementsAction, _In_opt_  HANDLE hEventToSignalUponCompletion, _Out_opt_  BOOL* pbFurtherMeasurementsDesired ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetBackgroundProcessingMode( Mode, MeasurementsAction, _In_opt_  hEventToSignalUponCompletion, pbFurtherMeasurementsDesired );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12ProtectedResourceSession1 : public D3D12ProtectedResourceSession
    {
    public:
        using Base = D3D12ProtectedResourceSession;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12ProtectedResourceSession1, D3D12ProtectedResourceSession, ID3D12ProtectedResourceSession1, ID3D12ProtectedResourceSession )
    public:
        D3D12_PROTECTED_RESOURCE_SESSION_DESC1 GetDesc1( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc1( );
        }
    };


    class D3D12Device7 : public D3D12Device6
    {
    public:
        using Base = D3D12Device6;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device7, D3D12Device6, ID3D12Device7, ID3D12Device6 )
    public:
        void AddToStateObject( const D3D12_STATE_OBJECT_DESC* pAddition, ID3D12StateObject* pStateObjectToGrowFrom, REFIID riid, _COM_Outptr_  void** ppNewStateObject ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->AddToStateObject( pAddition, pStateObjectToGrowFrom, riid, ppNewStateObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateProtectedResourceSession1( _In_  const D3D12_PROTECTED_RESOURCE_SESSION_DESC1* pDesc, _In_  REFIID riid, _COM_Outptr_  void** ppSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateProtectedResourceSession1( pDesc, riid, ppSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12Device8 : public D3D12Device7
    {
    public:
        using Base = D3D12Device7;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Device8, D3D12Device7, ID3D12Device8, ID3D12Device7 )
    public:
        D3D12_RESOURCE_ALLOCATION_INFO GetResourceAllocationInfo2( UINT visibleMask, UINT numResourceDescs, _In_reads_( numResourceDescs )  const D3D12_RESOURCE_DESC1* pResourceDescs, _Out_writes_opt_( numResourceDescs )  D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1 ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetResourceAllocationInfo2( visibleMask, numResourceDescs, pResourceDescs, pResourceAllocationInfo1 );
        }

        void CreateCommittedResource2( _In_  const D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS HeapFlags, _In_  const D3D12_RESOURCE_DESC1* pDesc, D3D12_RESOURCE_STATES InitialResourceState, _In_opt_  const D3D12_CLEAR_VALUE* pOptimizedClearValue, _In_opt_  ID3D12ProtectedResourceSession* pProtectedSession, REFIID riidResource, _COM_Outptr_opt_  void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommittedResource2( pHeapProperties, HeapFlags, pDesc, InitialResourceState, pOptimizedClearValue, pProtectedSession, riidResource, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreatePlacedResource1( _In_  ID3D12Heap* pHeap, UINT64 HeapOffset, _In_  const D3D12_RESOURCE_DESC1* pDesc, D3D12_RESOURCE_STATES InitialState, _In_opt_  const D3D12_CLEAR_VALUE* pOptimizedClearValue, REFIID riid, _COM_Outptr_opt_  void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreatePlacedResource1( pHeap, HeapOffset, pDesc, InitialState, pOptimizedClearValue, riid, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateSamplerFeedbackUnorderedAccessView( _In_opt_  ID3D12Resource* pTargetedResource, _In_opt_  ID3D12Resource* pFeedbackResource, _In_  D3D12_CPU_DESCRIPTOR_HANDLE DestDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateSamplerFeedbackUnorderedAccessView( pTargetedResource, pFeedbackResource, DestDescriptor );
        }

        void GetCopyableFootprints1( _In_  const D3D12_RESOURCE_DESC1* pResourceDesc, _In_range_( 0, D3D12_REQ_SUBRESOURCES )  UINT FirstSubresource, _In_range_( 0, D3D12_REQ_SUBRESOURCES - FirstSubresource )  UINT NumSubresources, UINT64 BaseOffset, _Out_writes_opt_( NumSubresources )  D3D12_PLACED_SUBRESOURCE_FOOTPRINT* pLayouts, _Out_writes_opt_( NumSubresources )  UINT* pNumRows, _Out_writes_opt_( NumSubresources )  UINT64* pRowSizeInBytes, _Out_opt_  UINT64* pTotalBytes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetCopyableFootprints1( pResourceDesc, FirstSubresource, NumSubresources, BaseOffset, pLayouts, pNumRows, pRowSizeInBytes, pTotalBytes );
        }
    };

    class D3D12Resource1 : public D3D12Resource
    {
    public:
        using Base = D3D12Resource;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Resource1, D3D12Resource, ID3D12Resource1, ID3D12Resource )
    public:
        void GetProtectedResourceSession( REFIID riid, _COM_Outptr_opt_  void** ppProtectedSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetProtectedResourceSession( riid, ppProtectedSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12Resource2 : public D3D12Resource1
    {
    public:
        using Base = D3D12Resource1;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Resource2, D3D12Resource1, ID3D12Resource2, ID3D12Resource1 )
    public:
        D3D12_RESOURCE_DESC1 GetDesc1( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc1( );
        }
    };

    class D3D12Heap1 : public D3D12Heap
    {
    public:
        using Base = D3D12Heap;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Heap1, D3D12Heap, ID3D12Heap1, ID3D12Heap )
    public:
        void GetProtectedResourceSession( REFIID riid, _COM_Outptr_opt_  void** ppProtectedSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetProtectedResourceSession( riid, ppProtectedSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class D3D12GraphicsCommandList3 : public D3D12GraphicsCommandList2
    {
    public:
        using Base = D3D12GraphicsCommandList2;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12GraphicsCommandList3, D3D12GraphicsCommandList2, ID3D12GraphicsCommandList3, ID3D12GraphicsCommandList2 )
    public:
        void SetProtectedResourceSession( _In_opt_  ID3D12ProtectedResourceSession* pProtectedResourceSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetProtectedResourceSession( pProtectedResourceSession );
        }
    };

    class D3D12MetaCommand : public D3D12Pageable
    {
    public:
        using Base = D3D12Pageable;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12MetaCommand, D3D12Pageable, ID3D12MetaCommand, ID3D12Pageable )
    public:
        UINT64 GetRequiredParameterResourceSize(_In_  D3D12_META_COMMAND_PARAMETER_STAGE Stage, _In_  UINT ParameterIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetRequiredParameterResourceSize( Stage, ParameterIndex );
        }
    };

    class D3D12GraphicsCommandList4 : public D3D12GraphicsCommandList3
    {
    public:
        using Base = D3D12GraphicsCommandList3;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12GraphicsCommandList4, D3D12GraphicsCommandList3, ID3D12GraphicsCommandList4, ID3D12GraphicsCommandList3 )
    public:
        void BeginRenderPass( _In_  UINT NumRenderTargets, _In_reads_opt_( NumRenderTargets )  const D3D12_RENDER_PASS_RENDER_TARGET_DESC* pRenderTargets, _In_opt_  const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC* pDepthStencil, D3D12_RENDER_PASS_FLAGS Flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginRenderPass( NumRenderTargets, pRenderTargets, pDepthStencil, Flags );
        }

        void EndRenderPass( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EndRenderPass( );
        }

        void InitializeMetaCommand( _In_  ID3D12MetaCommand* pMetaCommand, _In_reads_bytes_opt_( InitializationParametersDataSizeInBytes )  const void* pInitializationParametersData, _In_  SIZE_T InitializationParametersDataSizeInBytes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->InitializeMetaCommand( pMetaCommand, pInitializationParametersData, InitializationParametersDataSizeInBytes );
        }

        void ExecuteMetaCommand( _In_  ID3D12MetaCommand* pMetaCommand, _In_reads_bytes_opt_( ExecutionParametersDataSizeInBytes )  const void* pExecutionParametersData, _In_  SIZE_T ExecutionParametersDataSizeInBytes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ExecuteMetaCommand( pMetaCommand, pExecutionParametersData, ExecutionParametersDataSizeInBytes );
        }

        void BuildRaytracingAccelerationStructure( _In_  const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* pDesc, _In_  UINT NumPostbuildInfoDescs, _In_reads_opt_( NumPostbuildInfoDescs )  const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* pPostbuildInfoDescs ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BuildRaytracingAccelerationStructure( pDesc, NumPostbuildInfoDescs, pPostbuildInfoDescs );
        }

        void EmitRaytracingAccelerationStructurePostbuildInfo( _In_  const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* pDesc, _In_  UINT NumSourceAccelerationStructures, _In_reads_( NumSourceAccelerationStructures )  const D3D12_GPU_VIRTUAL_ADDRESS* pSourceAccelerationStructureData ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EmitRaytracingAccelerationStructurePostbuildInfo( pDesc, NumSourceAccelerationStructures, pSourceAccelerationStructureData );
        }

        void CopyRaytracingAccelerationStructure( _In_  D3D12_GPU_VIRTUAL_ADDRESS DestAccelerationStructureData, _In_  D3D12_GPU_VIRTUAL_ADDRESS SourceAccelerationStructureData, _In_  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyRaytracingAccelerationStructure( DestAccelerationStructureData, SourceAccelerationStructureData, Mode );
        }

        void SetPipelineState1( _In_  ID3D12StateObject* pStateObject ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetPipelineState1( pStateObject );
        }

        void DispatchRays( _In_  const D3D12_DISPATCH_RAYS_DESC* pDesc ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DispatchRays( pDesc );
        }
    };


    class D3D12Tools : public Unknown
    {
    public:
        using Base = Unknown;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12Tools, Unknown, ID3D12Tools, IUnknown )
    public:
        void EnableShaderInstrumentation( BOOL bEnable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EnableShaderInstrumentation( bEnable );
        }

        BOOL ShaderInstrumentationEnabled( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->ShaderInstrumentationEnabled( );
        }
    };

    class D3D12GraphicsCommandList5 : public D3D12GraphicsCommandList4
    {
    public:
        using Base = D3D12GraphicsCommandList4;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12GraphicsCommandList5, D3D12GraphicsCommandList4, ID3D12GraphicsCommandList5, ID3D12GraphicsCommandList4 )
    public:
        void RSSetShadingRate( _In_  D3D12_SHADING_RATE baseShadingRate, _In_reads_opt_( D3D12_RS_SET_SHADING_RATE_COMBINER_COUNT )  const D3D12_SHADING_RATE_COMBINER* combiners ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RSSetShadingRate( baseShadingRate, combiners );
        }

        void RSSetShadingRateImage( _In_opt_  ID3D12Resource* shadingRateImage ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RSSetShadingRateImage( shadingRateImage );
        }
    };

    class D3D12GraphicsCommandList6 : public D3D12GraphicsCommandList5
    {
    public:
        using Base = D3D12GraphicsCommandList5;

        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL( D3D12GraphicsCommandList6, D3D12GraphicsCommandList5, ID3D12GraphicsCommandList6, ID3D12GraphicsCommandList5 )
    public:
        void DispatchMesh( _In_ UINT ThreadGroupCountX, _In_ UINT ThreadGroupCountY, _In_ UINT ThreadGroupCountZ ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DispatchMesh( ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ );
        }
    };


    template<typename T = D3D12Device>
        requires std::is_base_of_v<D3D12Device, T>
    inline T CreateDevice( Unknown adapter, D3D_FEATURE_LEVEL minimumFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1 )
    {
        using InterfaceType = T::InterfaceType;
        auto InterfaceId = __uuidof( InterfaceType );
        InterfaceType* intf = nullptr;
        auto hr = D3D12CreateDevice( adapter.GetInterfacePointer(), minimumFeatureLevel, InterfaceId, (void**)&intf );
        HCC_COM_CHECK_HRESULT( hr );
        T result( intf );
        return result;
    }

    inline D3D12Device4 D3D12DeviceChild::GetDevice( ) const
    {
        return GetDevice<D3D12Device4>( );
    }

}


#endif
