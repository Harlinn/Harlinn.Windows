#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12_H_
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


#include "HWGraphicsD3D12Ex.h"
#include <boost/container/small_vector.hpp>

#pragma comment(lib,"D3D12.lib")
#pragma comment(lib,"D3DCompiler.lib")

namespace Harlinn::Windows::Graphics::D3D12
{
    namespace Core = Harlinn::Common::Core;

    class Object;
    class DeviceChild;
    class RootSignature;
    class RootSignatureDeserializer;
    class VersionedRootSignatureDeserializer;
    class Pageable;
    class Heap;
    class Resource;
    class CommandAllocator;
    class Fence;
    class Fence1;
    class PipelineState;
    class DescriptorHeap;
    class QueryHeap;
    class CommandSignature;
    class CommandList;
    class GraphicsCommandList;
    class GraphicsCommandList1;
    class GraphicsCommandList2;
    class CommandQueue;
    class Device;
    class PipelineLibrary;
    class PipelineLibrary1;
    class Device1;
    class Device2;
    class Device3;
    class ProtectedSession;
    class ProtectedResourceSession;
    class Device4;
    class LifetimeOwner;
    class SwapChainAssistant;
    class LifetimeTracker;
    class StateObject;
    class StateObjectProperties;
    class Device5;
    class DeviceRemovedExtendedDataSettings;
    class DeviceRemovedExtendedDataSettings1;
    class DeviceRemovedExtendedData;
    class DeviceRemovedExtendedData1;
    class Device6;
    class ProtectedResourceSession1;
    class Device7;
    class Device8;
    class Resource1;
    class Resource2;
    class Heap1;
    class GraphicsCommandList3;
    class MetaCommand;
    class GraphicsCommandList4;
    class Tools;
    class GraphicsCommandList5;
    class GraphicsCommandList6;
}

namespace Harlinn::Windows::Graphics
{
    using D3D12Object = D3D12::Object;
    using D3D12DeviceChild = D3D12::DeviceChild;
    using D3D12RootSignature = D3D12::RootSignature;
    using D3D12RootSignatureDeserializer = D3D12::RootSignatureDeserializer;
    using D3D12VersionedRootSignatureDeserializer = D3D12::VersionedRootSignatureDeserializer;
    using D3D12Pageable = D3D12::Pageable;
    using D3D12Heap = D3D12::Heap;
    using D3D12Resource = D3D12::Resource;
    using D3D12CommandAllocator = D3D12::CommandAllocator;
    using D3D12Fence = D3D12::Fence;
    using D3D12Fence1 = D3D12::Fence1;
    using D3D12PipelineState = D3D12::PipelineState;
    using D3D12DescriptorHeap = D3D12::DescriptorHeap;
    using D3D12QueryHeap = D3D12::QueryHeap;
    using D3D12CommandSignature = D3D12::CommandSignature;
    using D3D12CommandList = D3D12::CommandList;
    using D3D12GraphicsCommandList = D3D12::GraphicsCommandList;
    using D3D12GraphicsCommandList1 = D3D12::GraphicsCommandList1;
    using D3D12GraphicsCommandList2 = D3D12::GraphicsCommandList2;
    using D3D12CommandQueue = D3D12::CommandQueue;
    using D3D12Device = D3D12::Device;
    using D3D12PipelineLibrary = D3D12::PipelineLibrary;
    using D3D12PipelineLibrary1 = D3D12::PipelineLibrary1;
    using D3D12Device1 = D3D12::Device1;
    using D3D12Device2 = D3D12::Device2;
    using D3D12Device3 = D3D12::Device3;
    using D3D12ProtectedSession = D3D12::ProtectedSession;
    using D3D12ProtectedResourceSession = D3D12::ProtectedResourceSession;
    using D3D12Device4 = D3D12::Device4;
    using D3D12LifetimeOwner = D3D12::LifetimeOwner;
    using D3D12SwapChainAssistant = D3D12::SwapChainAssistant;
    using D3D12LifetimeTracker = D3D12::LifetimeTracker;
    using D3D12StateObject = D3D12::StateObject;
    using D3D12StateObjectProperties = D3D12::StateObjectProperties;
    using D3D12Device5 = D3D12::Device5;
    using D3D12DeviceRemovedExtendedDataSettings = D3D12::DeviceRemovedExtendedDataSettings;
    using D3D12DeviceRemovedExtendedDataSettings1 = D3D12::DeviceRemovedExtendedDataSettings1;
    using D3D12DeviceRemovedExtendedData = D3D12::DeviceRemovedExtendedData;
    using D3D12DeviceRemovedExtendedData1 = D3D12::DeviceRemovedExtendedData1;
    using D3D12Device6 = D3D12::Device6;
    using D3D12ProtectedResourceSession1 = D3D12::ProtectedResourceSession1;
    using D3D12Device7 = D3D12::Device7;
    using D3D12Device8 = D3D12::Device8;
    using D3D12Resource1 = D3D12::Resource1;
    using D3D12Resource2 = D3D12::Resource2;
    using D3D12Heap1 = D3D12::Heap1;
    using D3D12GraphicsCommandList3 = D3D12::GraphicsCommandList3;
    using D3D12MetaCommand = D3D12::MetaCommand;
    using D3D12GraphicsCommandList4 = D3D12::GraphicsCommandList4;
    using D3D12Tools = D3D12::Tools;
    using D3D12GraphicsCommandList5 = D3D12::GraphicsCommandList5;
    using D3D12GraphicsCommandList6 = D3D12::GraphicsCommandList6;
}



namespace Harlinn::Windows::Graphics::D3D12
{


#define COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL_( classType, baseClassType , interfaceType, baseInterfaceType )  HCC_COM_STANDARD_METHODS_IMPL(classType, baseClassType , interfaceType, baseInterfaceType)


    /// <summary>
    /// A base class from which Device and DeviceChild inherit from. 
    /// It provides methods to associate private data and annotate object names.
    /// </summary>
    class Object : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( Object, Unknown, ID3D12Object, IUnknown )

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
        /// object if dataSizePtr points to a value that specifies a buffer large 
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

        /// <summary>
        /// Associates an IUnknown-derived interface with the device object and associates 
        /// that interface with an application-defined GUID.
        /// </summary>
        /// <param name="guid">
        /// The GUID to associate with the interface.
        /// </param>
        /// <param name="privateDatainterfacePtr">
        /// A pointer to the IUnknown-derived interface to be associated with the device object.
        /// </param>
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

        /// <summary>
        /// Associates a name with the device object. This name is for use in 
        /// debug diagnostics and tools.
        /// </summary>
        /// <param name="name">
        /// A NULL-terminated UNICODE string that contains the name to associate 
        /// with the device object.
        /// </param>
        void SetName( _In_z_  LPCWSTR name ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetName( name );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Retrieves the name associated with the device object.
        /// </summary>
        /// <typeparam name="StringT">
        /// The type of string to return.
        /// </typeparam>
        template<WideStringLike StringT = WideString>
        StringT Name() const
        {
            wchar_t buffer[ 512 ];
            UINT dataSize = sizeof( buffer );
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetPrivateData( WKPDID_D3DDebugObjectNameW, &dataSize, buffer );
            if ( SUCCEEDED( hr ) )
            {
                return StringT( buffer, static_cast<typename StringT::size_type>( dataSize / sizeof( wchar_t ) ) );
            }
            return {};
        }

        template<WideStringLike StringT>
        void SetName( const StringT& name ) const
        {
            SetName( name.c_str( ) );
        }

        template<AnsiStringLike StringT>
        void SetName( const StringT& name ) const
        {
            SetName( ToWideString( name ) );
        }

    };
    

    /// <summary>
    /// Adds the ability to get the device used to create it.
    /// </summary>
    class DeviceChild : public Object
    {
    public:
        using Base = Object;

        HCC_COM_STANDARD_METHODS_IMPL( DeviceChild, Object, ID3D12DeviceChild, ID3D12Object )

    public:
        /// <summary>
        /// Gets a pointer to the device that created this interface.
        /// </summary>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the device interface. 
        /// The REFIID, or GUID, of the interface to the device can be obtained 
        /// by using the __uuidof() macro. For example, __uuidof(ID3D12Device) 
        /// will get the GUID of the interface to a device.
        /// </param>
        /// <param name="ppvDevice">
        /// A pointer to a memory block that receives a pointer to the ID3D12Device 
        /// interface, or one of its descendants, for the device.
        /// </param>
        void GetDevice( REFIID riid, _COM_Outptr_opt_  void** ppvDevice ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetDevice( riid, ppvDevice );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }


        /// <summary>
        /// Retrieves the Device, or one of its descendants, used to
        /// create this object.
        /// </summary>
        /// <typeparam name="T">
        /// The requested type, either Device, or one of its descendants.
        /// </typeparam>
        /// <returns>
        /// The Device, or one of its descendants, used to create this object.
        /// </returns>
        template<typename T >
            requires std::is_base_of_v<Device,T>
        T GetDevice( ) const
        {
            typename T::InterfaceType* ptr = nullptr;
            constexpr auto refiid = __uuidof( typename T::InterfaceType );
            GetDevice( refiid, (void**) &ptr );
            return T( ptr, false );
        }
        inline Device4 GetDevice( ) const;

    };


    /// <summary>
    /// The root signature defines what resources are bound to the graphics pipeline. 
    /// A root signature is configured by the app and links command lists to the 
    /// resources the shaders require. Currently, there is one graphics and one compute 
    /// root signature per app.
    /// </summary>
    class RootSignature : public DeviceChild
    {
    public:
        using Base = DeviceChild;

        HCC_COM_STANDARD_METHODS_IMPL( RootSignature, DeviceChild, ID3D12RootSignature, ID3D12DeviceChild )
    public:
    };


    /// <summary>
    /// Contains a method to return the deserialized D3D12_ROOT_SIGNATURE_DESC 
    /// data structure, of a serialized root signature version 1.0.
    /// </summary>
    /// <remarks>
    /// This class has been superseded by VersionedRootSignatureDeserializer.
    /// </remarks>
    class RootSignatureDeserializer : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( RootSignatureDeserializer, Unknown, ID3D12RootSignatureDeserializer, IUnknown )

    public:
        /// <summary>
        /// Gets the layout of the root signature.
        /// </summary>
        /// <returns>
        /// This function returns a deserialized root signature in a D3D12_ROOT_SIGNATURE_DESC 
        /// structure that describes the layout of the root signature.
        /// </returns>
        const D3D12_ROOT_SIGNATURE_DESC* GetRootSignatureDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetRootSignatureDesc( );
        }
    };

    /// <summary>
    /// Contains methods to return the deserialized D3D12_ROOT_SIGNATURE_DESC1 data structure, 
    /// of any version of a serialized root signature.
    /// </summary>
    class VersionedRootSignatureDeserializer : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( VersionedRootSignatureDeserializer, Unknown, ID3D12VersionedRootSignatureDeserializer, IUnknown )

    public:
        /// <summary>
        /// Converts root signature description structures to a requested version.
        /// </summary>
        /// <param name="convertToVersion">
        /// Specifies the required D3D_ROOT_SIGNATURE_VERSION.
        /// </param>
        /// <param name="ppDesc">
        /// Contains the deserialized root signature in a D3D12_VERSIONED_ROOT_SIGNATURE_DESC structure.
        /// </param>
        /// <remarks>
        /// <para>
        /// This method allocates additional storage if needed for the converted root signature (memory 
        /// owned by the deserializer interface). If conversion is done, the deserializer interface doesn’t 
        /// free the original deserialized root signature memory – all versions the interface has been 
        /// asked to convert to are available until the deserializer is destroyed.
        /// </para>
        /// <para>
        /// Converting a root signature from 1.1 to 1.0 will drop all D3D12_DESCRIPTOR_RANGE_FLAGS 
        /// and D3D12_ROOT_DESCRIPTOR_FLAGS can be useful for generating compatible root signatures 
        /// that need to run on old operating systems, though does lose optimization opportunities. 
        /// For instance, multiple root signature versions can be serialized and stored with application 
        /// assets, with the appropriate version used at runtime based on the operating system capabilities.
        /// </para>
        /// <para>
        /// Converting a root signature from 1.0 to 1.1 just adds the appropriate flags to match 1.0 semantics.
        /// </para>
        /// </remarks>
        void GetRootSignatureDescAtVersion( D3D_ROOT_SIGNATURE_VERSION convertToVersion, _Out_  const D3D12_VERSIONED_ROOT_SIGNATURE_DESC** ppDesc ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetRootSignatureDescAtVersion( convertToVersion, ppDesc );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Gets the layout of the root signature, without converting between root signature versions.
        /// </summary>
        /// <returns>
        /// This method returns a deserialized root signature in a D3D12_VERSIONED_ROOT_SIGNATURE_DESC 
        /// structure that describes the layout of the root signature.
        /// </returns>
        const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* GetUnconvertedRootSignatureDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetUnconvertedRootSignatureDesc( );
        }
    };

    /// <summary>
    /// Classes derived from Pageable encapsulates some amount of 
    /// GPU-accessible memory.
    /// </summary>
    class Pageable : public DeviceChild
    {
    public:
        using Base = DeviceChild;

        HCC_COM_STANDARD_METHODS_IMPL( Pageable, DeviceChild, ID3D12Pageable, ID3D12DeviceChild )
    public:
    };


    /// <summary>
    /// A heap is an abstraction of contiguous memory allocation, used to manage physical memory. 
    /// This heap can be used with Resource objects to support placed resources or reserved resources.
    /// </summary>
    class Heap : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( Heap, Pageable, ID3D12Heap, ID3D12Pageable )
    public:
        /// <summary>
        /// Gets the heap description.
        /// </summary>
        /// <returns>
        /// Returns the D3D12_HEAP_DESC structure that describes the heap.
        /// </returns>
        D3D12_HEAP_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }
    };

    /// <summary>
    /// Encapsulates a generalized ability of the CPU and GPU to read and write 
    /// to physical memory, or heaps. It contains abstractions for organizing 
    /// and manipulating simple arrays of data as well as multidimensional 
    /// data optimized for shader sampling.
    /// </summary>
    class Resource : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( Resource, Pageable, ID3D12Resource, ID3D12Pageable )
    public:
        /// <summary>
        /// Gets a CPU pointer to the specified subresource in the resource, but 
        /// may not disclose the pointer value to applications. Map also invalidates 
        /// the CPU cache, when necessary, so that CPU reads to this address reflect 
        /// any modifications made by the GPU.
        /// </summary>
        /// <param name="Subresource">
        /// Specifies the index number of the subresource.
        /// </param>
        /// <param name="readRange">
        /// <para>
        /// A pointer to a <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_range">D3D12_RANGE</see> 
        /// structure that describes the range of memory to access.
        /// </para>
        /// <para>
        /// This indicates the region the CPU might read, and the coordinates are 
        /// subresource-relative. A null pointer indicates the entire subresource 
        /// might be read by the CPU. It is valid to specify the CPU won't read 
        /// any data by passing a range where End is less than or equal to Begin.
        /// </para>
        /// </param>
        /// <param name="dataPtr">
        /// <para>
        /// A pointer to a memory block that receives a pointer to the resource data.
        /// </para>
        /// <para>
        /// A null pointer is valid and is useful to cache a CPU virtual address range 
        /// for methods like WriteToSubresource. When <c>dataPtr</c> is not <c>nullptr</c>, the pointer 
        /// returned is never offset by any values in <paramref>readRange</paramref>.
        /// </para>
        /// </param>
        /// <remarks>
        /// <para>
        /// Map and Unmap can be called by multiple threads safely. Nested Map calls are 
        /// supported and are ref-counted. The first call to Map allocates a CPU virtual 
        /// address range for the resource. The last call to Unmap deallocates the CPU 
        /// virtual address range. The CPU virtual address is commonly returned to the 
        /// application; but manipulating the contents of textures with unknown layouts 
        /// precludes disclosing the CPU virtual address. See <see cref="WriteToSubresource">WriteToSubresource</see> 
        /// for more details. Applications cannot rely on the address being consistent, 
        /// unless Map is persistently nested.
        /// </para>
        /// <para>
        /// Pointers returned by Map are not guaranteed to have all the capabilities of 
        /// normal pointers, but most applications won't notice a difference in normal 
        /// usage. For example, pointers with WRITE_COMBINE behavior have weaker CPU 
        /// memory ordering guarantees than WRITE_BACK behavior. Memory accessible by 
        /// both CPU and GPU are not guaranteed to share the same atomic memory 
        /// guarantees that the CPU has, due to PCIe limitations. Use fences for synchronization.
        /// </para>
        /// <para>
        /// There are two usage model categories for Map, simple and advanced. The simple 
        /// usage models maximize tool performance, so applications are recommended to 
        /// stick with the simple models until the advanced models are proven to be 
        /// required by the app.
        /// </para>
        /// <h3>Simple Usage Models</h3>
        /// <para>
        /// Applications should stick to the heap type abstractions of UPLOAD, DEFAULT, and 
        /// READBACK, in order to support all adapter architectures reasonably well.
        /// </para>
        /// <para>
        /// Applications should avoid CPU reads from pointers to resources on UPLOAD heaps, 
        /// even accidently. CPU reads will work, but are prohibitively slow on many common 
        /// GPU architectures, so consider the following:
        /// </para>
        /// <list type="bullet">
        /// <item>
        /// Don't make the CPU read from resources associated with heaps that are 
        /// D3D12_HEAP_TYPE_UPLOAD or have D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE.
        /// </item>
        /// <item>
        /// The memory region to which pData points can be allocated with 
        /// PAGE_WRITECOMBINE, and your app must honor all restrictions that are 
        /// associated with such memory.
        /// </item>
        /// <item>
        /// <para>
        /// Even the following C++ code can read from memory and trigger the performance 
        /// penalty because the code can expand to the following x86 assembly code.
        /// </para>
        /// <para>
        /// C++ code:
        /// </para>
        /// <code>
        /// *((int*)MappedResource.pData) = 0;
        /// </code>
        /// <para>
        /// x86 assembly code:
        /// </para>
        /// <code>
        /// AND DWORD PTR [EAX],0
        /// </code>
        /// </item>
        /// <item>
        /// Use the appropriate optimization settings and language constructs to help 
        /// avoid this performance penalty. For example, you can avoid the xor optimization 
        /// by using a volatile pointer or by optimizing for code speed instead of code size.
        /// </item>
        /// </list>
        /// <para>
        /// Applications are encouraged to leave resources unmapped while the CPU will not 
        /// modify them, and use tight, accurate ranges at all times. This enables the 
        /// fastest modes for tools, like Graphics Debugging and the debug layer. Such 
        /// tools need to track all CPU modifications to memory that the GPU could read.
        /// </para>
        /// <h3>Advanced Usage Models</h3>
        /// <para>
        /// Resources on CPU-accessible heaps can be persistently mapped, meaning Map can 
        /// be called once, immediately after resource creation. Unmap never needs to be 
        /// called, but the address returned from Map must no longer be used after the 
        /// last reference to the resource is released. When using persistent map, the 
        /// application must ensure the CPU finishes writing data into memory before the 
        /// GPU executes a command list that reads or writes the memory. In common scenarios, 
        /// the application merely must write to memory before calling ExecuteCommandLists; 
        /// but using a fence to delay command list execution works as well.
        /// </para>
        /// <para>
        /// All CPU-accessible memory types support persistent mapping usage, where the 
        /// resource is mapped but then never unmapped, provided the application does not 
        /// access the pointer after the resource has been disposed.
        /// </para>
        /// <remarks>
        void Map( UINT Subresource, _In_opt_ const D3D12_RANGE* readRange, _Outptr_opt_result_bytebuffer_( _Inexpressible_( "Dependent on resource" ) )  void** dataPtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Map( Subresource, readRange, dataPtr );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Map( UINT Subresource, _In_opt_ const D3D12_RANGE& readRange, _Outptr_opt_result_bytebuffer_( _Inexpressible_( "Dependent on resource" ) )  void** dataPtr ) const
        {
            Map( Subresource, &readRange, dataPtr );
        }

        void* Map( UINT Subresource, _In_opt_ const D3D12_RANGE* readRange = nullptr ) const
        {
            void* result = nullptr;
            Map( Subresource, readRange, &result );
            return result;
        }
        void* Map( UINT Subresource, _In_opt_ const D3D12_RANGE& readRange ) const
        {
            return Map( Subresource, &readRange );
        }

        void* Map( UINT Subresource, _In_opt_ const Range& readRange ) const
        {
            return Map( Subresource, reinterpret_cast< const D3D12_RANGE* >( &readRange ) );
        }

        template<SimpleSpanLike T>
        void Assign( UINT Subresource, const T& resourceData )
        {
            auto bufferSize = resourceData.size( ) * sizeof( typename T::value_type );

            auto dest = Map( Subresource, Range() );
            memcpy( dest, resourceData.data( ), bufferSize );
            Unmap( Subresource, nullptr );
        }

        /// <summary>
        /// Invalidates the CPU pointer to the specified subresource in the resource.
        /// </summary>
        /// <param name="Subresource">
        /// Specifies the index of the subresource.
        /// </param>
        /// <param name="writtenRange">
        /// <para>
        /// A pointer to a <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_range">D3D12_RANGE</see> 
        /// structure that describes the range of memory to unmap.
        /// </para>
        /// <para>
        /// This indicates the region the CPU might have modified, and the coordinates are 
        /// subresource-relative. A null pointer indicates the entire subresource might have 
        /// been modified by the CPU. It is valid to specify the CPU didn't write any data 
        /// by passing a range where End is less than or equal to Begin.
        /// </para>
        /// <para>
        /// This parameter is only used by tooling, and not for correctness of the actual unmap operation.
        /// </para>
        /// </param>
        void Unmap( UINT Subresource, _In_opt_  const D3D12_RANGE* writtenRange = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Unmap( Subresource, writtenRange );
        }

        void Unmap( UINT Subresource, const D3D12_RANGE& writtenRange ) const
        {
            Unmap( Subresource, &writtenRange );
        }

        void Unmap( UINT Subresource, const D3D12::Range& writtenRange ) const
        {
            Unmap( Subresource, reinterpret_cast< const D3D12_RANGE* >( &writtenRange ) );
        }

        /// <summary>
        /// Gets the resource description.
        /// </summary>
        /// <returns>
        /// A Direct3D 12 resource description structure.
        /// </returns>
        D3D12_RESOURCE_DESC GetDesc_( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }

        /// <summary>
        /// Gets the resource description.
        /// </summary>
        /// <returns>
        /// A Direct3D 12 resource description structure.
        /// </returns>
        ResourceDesc GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }


        /// <summary>
        /// This method returns the GPU virtual address of a buffer resource.
        /// </summary>
        /// <returns>
        /// This method returns the GPU virtual address. D3D12_GPU_VIRTUAL_ADDRESS is a typedef'd synonym of UINT64.
        /// </returns>
        /// <remarks>
        /// <para>
        /// This method is only useful for buffer resources, it will return zero for all texture resources.
        /// </para>
        /// <para>
        /// For more information on the use of GPU virtual addresses, refer to 
        /// <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d12/indirect-drawing">Indirect Drawing</see>.
        /// </para>
        /// <remarks>
        D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetGPUVirtualAddress( );
        }

        /// <summary>
        /// Uses the CPU to copy data into a subresource, enabling the CPU to modify 
        /// the contents of most textures with undefined layouts.
        /// </summary>
        /// <param name="destinationSubresource">
        /// Specifies the index of the subresource.
        /// </param>
        /// <param name="destinationBox">
        /// A pointer to a box that defines the portion of the destination subresource 
        /// to copy the resource data into. If NULL, the data is written to the destination 
        /// subresource with no offset. The dimensions of the source must fit the destination 
        /// (see <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_box">D3D12_BOX</see>).
        /// </param>
        /// <param name="sourceData">
        /// A pointer to the source data in memory.
        /// </param>
        /// <param name="sourceRowPitch">
        /// The distance from one row of source data to the next row.
        /// </param>
        /// <param name="sourceDepthPitch">
        /// The distance from one depth slice of source data to the next.
        /// </param>
        /// <remarks>
        /// <para>
        /// The resource should first be mapped using Map. Textures must be in the 
        /// D3D12_RESOURCE_STATE_COMMON state for CPU access through WriteToSubresource 
        /// and ReadFromSubresource to be legal; but buffers do not.
        /// </para>
        /// <para>
        /// For efficiency, ensure the bounds and alignment of the extents within the box are 
        /// ( 64 / [bytes per pixel] ) pixels horizontally. Vertical bounds and alignment should 
        /// be 2 rows, except when 1-byte-per-pixel formats are used, in which case 4 rows are 
        /// recommended. Single depth slices per call are handled efficiently. It is recommended but 
        /// not necessary to provide pointers and strides which are 128-byte aligned.
        /// </para>
        /// <para>
        /// When writing to sub mipmap levels, it is recommended to use larger width and heights 
        /// than described above. This is because small mipmap levels may actually be stored 
        /// within a larger block of memory, with an opaque amount of offsetting which can 
        /// interfere with alignment to cache lines.
        /// </para>
        /// <para>
        /// WriteToSubresource and ReadFromSubresource enable near zero-copy optimizations for UMA 
        /// adapters, but can prohibitively impair the efficiency of discrete/ NUMA adapters as the 
        /// texture data cannot reside in local video memory. Typical applications should stick to 
        /// discrete-friendly upload techniques, unless they recognize the adapter architecture is UMA. 
        /// For more details on uploading, refer to CopyTextureRegion, and for more details on UMA, 
        /// refer to D3D12_FEATURE_DATA_ARCHITECTURE.
        /// </para>
        /// <para>
        /// On UMA systems, this routine can be used to minimize the cost of memory copying through 
        /// the loop optimization known as loop tiling. By breaking up the upload into chucks that 
        /// comfortably fit in the CPU cache, the effective bandwidth between the CPU and main memory 
        /// more closely achieves theoretical maximums.
        /// </para>
        /// </remarks>
        void WriteToSubresource(UINT destinationSubresource, _In_opt_ const D3D12_BOX* destinationBox, _In_ const void* sourceData, UINT sourceRowPitch, UINT sourceDepthPitch ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->WriteToSubresource( destinationSubresource, destinationBox, sourceData, sourceRowPitch, sourceDepthPitch );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void WriteToSubresource( UINT destinationSubresource, _In_ const void* sourceData, UINT sourceRowPitch, UINT sourceDepthPitch ) const
        {
            WriteToSubresource( destinationSubresource, nullptr ,sourceData, sourceRowPitch, sourceDepthPitch );
        }

        void WriteToSubresource( UINT destinationSubresource, const D3D12_BOX& destinationBox, _In_ const void* sourceData, UINT sourceRowPitch, UINT sourceDepthPitch ) const
        {
            WriteToSubresource( destinationSubresource, &destinationBox, sourceData, sourceRowPitch, sourceDepthPitch );
        }



        /// <summary>
        /// Uses the CPU to copy data from a subresource, enabling the CPU to read the contents 
        /// of most textures with undefined layouts.
        /// </summary>
        /// <param name="destinationData">
        /// A pointer to the destination data in memory.
        /// </param>
        /// <param name="destinationRowPitch">
        /// The distance from one row of destination data to the next row.
        /// </param>
        /// <param name="destinationDepthPitch">
        /// The distance from one depth slice of destination data to the next.
        /// </param>
        /// <param name="sourceSubresource">
        /// Specifies the index of the subresource to read from.
        /// </param>
        /// <param name="sourceBox">
        /// <para>
        /// A pointer to a box that defines the portion of the destination subresource to copy 
        /// the resource data from. If NULL, the data is read from the destination subresource 
        /// with no offset. The dimensions of the destination must fit the destination 
        /// (see <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_box">D3D12_BOX</see>).
        /// </para>
        /// <para>
        /// An empty box results in a no-op. A box is empty if the top value is greater than or 
        /// equal to the bottom value, or the left value is greater than or equal to the right 
        /// value, or the front value is greater than or equal to the back value. When the box is 
        /// empty, this method doesn't perform any operation.
        /// </para>
        /// </param>
        void ReadFromSubresource( _Out_ void* destinationData, UINT destinationRowPitch, UINT destinationDepthPitch, UINT sourceSubresource, _In_opt_ const D3D12_BOX* sourceBox = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->ReadFromSubresource( destinationData, destinationRowPitch, destinationDepthPitch, sourceSubresource, sourceBox );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ReadFromSubresource( _Out_ void* destinationData, UINT destinationRowPitch, UINT destinationDepthPitch, UINT sourceSubresource, const D3D12_BOX& sourceBox ) const
        {
            ReadFromSubresource( destinationData, destinationRowPitch, destinationDepthPitch, sourceSubresource, &sourceBox );
        }

        /// <summary>
        /// Retrieves the properties of the resource heap, for placed and committed resources.
        /// </summary>
        /// <param name="heapProperties">
        /// Pointer to a <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_heap_properties">D3D12_HEAP_PROPERTIES</see> 
        /// structure, that on successful completion of the method will contain the resource heap properties.
        /// </param>
        /// <param name="heapFlags">
        /// Specifies a <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ne-d3d12-d3d12_heap_flags">D3D12_HEAP_FLAGS variable</see>, 
        /// that on successful completion of the method will contain any miscellaneous heap flags.
        /// </param>
        void GetHeapProperties( _Out_opt_ D3D12_HEAP_PROPERTIES* heapProperties, _Out_opt_ D3D12_HEAP_FLAGS* heapFlags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->GetHeapProperties( heapProperties, heapFlags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents the allocations of storage for graphics processing unit (GPU) commands.
    /// </summary>
    /// <remarks>
    /// <para>
    /// Use <see cref="Device::CreateCommandAllocator">Device::CreateCommandAllocator</see> to create a command allocator object.
    /// </para>
    /// <para>
    /// The command allocator object corresponds to the underlying allocations in which 
    /// GPU commands are stored. The command allocator object applies to both direct command 
    /// lists and bundles. You must use a command allocator object in a DirectX 12 app.
    /// </para>
    /// </remarks>
    class CommandAllocator : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( CommandAllocator, Pageable, ID3D12CommandAllocator, ID3D12Pageable )
    public:

        /// <summary>
        /// Indicates to re-use the memory that is associated with the command allocator.
        /// </summary>
        /// <remarks>
        /// <para>
        /// Apps call Reset to re-use the memory that is associated with a command allocator. 
        /// From this call to Reset, the runtime and driver determine that the graphics processing 
        /// unit (GPU) is no longer executing any command lists that have recorded commands with 
        /// the command allocator.
        /// </para>
        /// <para>
        /// Unlike <see cref="GraphicsCommandList::Reset">GraphicsCommandList::Reset</see>, it 
        /// is not recommended that you call Reset on the command allocator while a command 
        /// list is still being executed.
        /// </para>
        /// <para>
        /// The debug layer will issue a warning if it can't prove that there are no pending GPU 
        /// references to command lists that have recorded commands in the allocator.
        /// </para>
        /// <para>
        /// The debug layer will issue an error if Reset is called concurrently by multiple threads (on the same allocator object).
        /// </para>
        /// </remarks>
        void Reset( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Reset( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Represents a fence, an object used for synchronization of the CPU and one or more GPUs.
    /// </summary>
    class Fence : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( Fence, Pageable, ID3D12Fence, ID3D12Pageable )
    public:

        /// <summary>
        /// Gets the current value of the fence.
        /// </summary>
        /// <returns>
        /// Returns the current value of the fence. If the device has been removed, the return 
        /// value will be UINT64_MAX.
        /// </returns>
        UINT64 GetCompletedValue( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCompletedValue( );
        }

        /// <summary>
        /// Specifies an event that's raised when the fence reaches a certain value.
        /// </summary>
        /// <param name="value">
        /// The fence value when the event is to be signaled.
        /// </param>
        /// <param name="eventHandle">
        /// A handle to the event object.
        /// </param>
        void SetEventOnCompletion( UINT64 value, HANDLE eventHandle ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->SetEventOnCompletion( value, eventHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetEventOnCompletion( UINT64 value, const EventWaitHandle& eventHandle ) const
        {
            SetEventOnCompletion( value, eventHandle.GetHandle( ) );
        }

        /// <summary>
        /// Sets the fence to the specified value.
        /// </summary>
        /// <param name="value">
        /// The value to set the fence to.
        /// </param>
        /// <remarks>
        /// Use this method to set a fence value from the CPU side. Use 
        /// <see cref="CommandQueue::Signal">CommandQueue::Signal</see> to 
        /// set a fence from the GPU side.
        /// </remarks>
        void Signal( UINT64 value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Signal( value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Adds the ability to retrie the flags used to create the fence. 
    /// This feature is useful primarily for opening shared fences.
    /// </summary>
    class Fence1 : public Fence
    {
    public:
        using Base = Fence;

        HCC_COM_STANDARD_METHODS_IMPL( Fence1, Fence, ID3D12Fence1, ID3D12Fence )
    public:

        /// <summary>
        /// Gets the flags used to create the fence represented by the current instance.
        /// </summary>
        /// <returns>
        /// The flags used to create the fence.
        /// </returns>
        D3D12_FENCE_FLAGS GetCreationFlags( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCreationFlags( );
        }
    };


    /// <summary>
    /// Represents the state of all currently set shaders as well as certain fixed function state objects.
    /// </summary>
    class PipelineState : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( PipelineState, Pageable, ID3D12PipelineState, ID3D12Pageable )
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

    /// <summary>
    /// A descriptor heap is a collection of contiguous allocations of descriptors, 
    /// one allocation for every descriptor. Descriptor heaps contain many object 
    /// types that are not part of a Pipeline State Object (PSO), such as Shader 
    /// Resource Views (SRVs), Unordered Access Views (UAVs), Constant Buffer Views 
    /// (CBVs), and Samplers.
    /// </summary>
    class DescriptorHeap : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( DescriptorHeap, Pageable, ID3D12DescriptorHeap, ID3D12Pageable )
    public:

        /// <summary>
        /// Gets the descriptor heap description.
        /// </summary>
        /// <returns>
        /// The description of the descriptor heap, as a 
        /// <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_descriptor_heap_desc">D3D12_DESCRIPTOR_HEAP_DESC</see> 
        /// structure.
        /// </returns>
        D3D12_DESCRIPTOR_HEAP_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }

        /// <summary>
        /// Gets the CPU descriptor handle that represents the start of the heap.
        /// </summary>
        /// <returns>
        /// Returns the CPU descriptor handle that represents the start of the heap.
        /// </returns>
        D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandleForHeapStart_( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetCPUDescriptorHandleForHeapStart( );
        }

        D3D12::CPUDescriptorHandle GetCPUDescriptorHandleForHeapStart( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return std::bit_cast< D3D12::CPUDescriptorHandle >( pInterface->GetCPUDescriptorHandleForHeapStart( ) );
        }

        /// <summary>
        /// Gets the GPU descriptor handle that represents the start of the heap.
        /// </summary>
        /// <returns>
        /// Returns the GPU descriptor handle that represents the start of the heap. 
        /// If the descriptor heap is not shader-visible, a null handle is returned.
        /// </returns>
        D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandleForHeapStart_( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetGPUDescriptorHandleForHeapStart( );
        }

        D3D12::GPUDescriptorHandle GetGPUDescriptorHandleForHeapStart( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return std::bit_cast< D3D12::GPUDescriptorHandle >( pInterface->GetGPUDescriptorHandleForHeapStart( ) );
        }
    };


    /// <summary>
    /// Manages a query heap. A query heap holds an array of queries, referenced by indexes.
    /// </summary>
    class QueryHeap : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( QueryHeap, Pageable, ID3D12QueryHeap, ID3D12Pageable )
    public:
    };

    /// <summary>
    /// A command signature object enables apps to specify indirect drawing, 
    /// including the buffer format, command type and resource bindings to be used.
    /// </summary>
    class CommandSignature : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( CommandSignature, Pageable, ID3D12CommandSignature, ID3D12Pageable )
    public:
    };

    /// <summary>
    /// The base class for the GraphicsCommandList class. It represents 
    /// an ordered set of commands that the GPU executes, while allowing for 
    /// extension to support other command lists than just those for graphics 
    /// (such as compute and copy).
    /// </summary>
    class CommandList : public DeviceChild
    {
    public:
        using Base = DeviceChild;

        HCC_COM_STANDARD_METHODS_IMPL( CommandList, DeviceChild, ID3D12CommandList, ID3D12DeviceChild )
    public:
        /// <summary>
        /// Gets the type of the command list, such as direct, bundle, compute, or copy.
        /// </summary>
        /// <returns>
        /// This method returns the type of the command list, as a D3D12_COMMAND_LIST_TYPE enumeration constant, such as direct, bundle, compute, or copy.
        /// </returns>
        D3D12_COMMAND_LIST_TYPE GetType( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetType( );
        }
    };

    /// <summary>
    /// Encapsulates a list of graphics commands for rendering. Includes APIs for 
    /// instrumenting the command list execution, and for setting and clearing the pipeline state.
    /// </summary>
    class GraphicsCommandList : public CommandList
    {
    public:
        using Base = CommandList;

        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList, CommandList, ID3D12GraphicsCommandList, ID3D12CommandList )
    public:

        /// <summary>
        /// Indicates that recording to the command list has finished.
        /// </summary>
        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Close( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Resets a command list back to its initial state as if a new command list was just created.
        /// </summary>
        /// <param name="pAllocator">
        /// A pointer to the ID3D12CommandAllocator object that the device creates command lists from.
        /// </param>
        /// <param name="pInitialState">
        /// <p>
        /// A pointer to the ID3D12PipelineState object that contains the initial pipeline state for 
        /// the command list. This is optional and can be NULL. If NULL, the runtime sets a dummy initial 
        /// pipeline state so that drivers don't have to deal with undefined state. The overhead for this 
        /// is low, particularly for a command list, for which the overall cost of recording the command 
        /// list likely dwarfs the cost of one initial state setting. So there is little cost in not setting 
        /// the initial pipeline state parameter if it isn't convenient.
        /// </p>
        /// <p>
        /// For bundles on the other hand, it might make more sense to try to set the initial state parameter 
        /// since bundles are likely smaller overall and can be reused frequently.
        /// </p>
        /// </param>
        void Reset( _In_  ID3D12CommandAllocator* pAllocator, _In_opt_  ID3D12PipelineState* pInitialState = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            HRESULT hr = pInterface->Reset( pAllocator, pInitialState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        /// <summary>
        /// Resets a command list back to its initial state as if a new command list was just created.
        /// </summary>
        void Reset( const CommandAllocator& allocator, const PipelineState& initialState ) const
        {
            Reset( allocator.GetInterfacePointer<ID3D12CommandAllocator>(), initialState.GetInterfacePointer<ID3D12PipelineState>() );
        }
        /// <summary>
        /// Resets a command list back to its initial state as if a new command list was just created.
        /// </summary>
        void Reset( const CommandAllocator& allocator ) const
        {
            Reset( allocator.GetInterfacePointer<ID3D12CommandAllocator>( ), nullptr );
        }


        /// <summary>
        /// Resets the state of a direct command list back to the state it was in when the command list was created.
        /// </summary>
        /// <param name="pipelineState">
        /// A pointer to the ID3D12PipelineState object that contains the initial pipeline state for the command list.
        /// </param>
        void ClearState( _In_opt_  ID3D12PipelineState* pipelineState = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearState( pipelineState );
        }

        /// <summary>
        /// Resets the state of a direct command list back to the state it was in when the command list was created.
        /// </summary>
        /// <param name="pipelineState">
        /// A reference to the PipelineState object that contains the initial pipeline state for the command list.
        /// </param>
        void ClearState( const PipelineState& pipelineState ) const
        {
            ClearState( pipelineState.GetInterfacePointer<ID3D12PipelineState>() );
        }

        /// <summary>
        /// Draws non-indexed, instanced primitives.
        /// </summary>
        /// <param name="vertexCountPerInstance">
        /// Number of vertices to draw.
        /// </param>
        /// <param name="instanceCount">
        /// Number of instances to draw.
        /// </param>
        /// <param name="startVertexLocation">
        /// Index of the first vertex.
        /// </param>
        /// <param name="startInstanceLocation">
        /// A value added to each index before reading per-instance data from a vertex buffer.
        /// </param>
        /// <remarks>
        /// <p>
        /// A draw API submits work to the rendering pipeline.
        /// </p>
        /// <p>
        /// Instancing might extend performance by reusing the same geometry to draw multiple 
        /// objects in a scene.One example of instancing could be to draw the same object with 
        /// different positions and colors.
        /// </p>
        /// <p>
        /// The vertex data for an instanced draw call typically comes from a vertex buffer 
        /// that is bound to the pipeline.But, you could also provide the vertex data from 
        /// a shader that has instanced data identified with a system-value semantic( SV_InstanceID ).
        /// </p>
        /// </remarks>
        void DrawInstanced(_In_ UINT vertexCountPerInstance, _In_ UINT instanceCount, _In_ UINT startVertexLocation, _In_ UINT startInstanceLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawInstanced( vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation );
        }

        /// <summary>
        /// Draws indexed, instanced primitives.
        /// </summary>
        /// <param name="indexCountPerInstance">
        /// Number of indices read from the index buffer for each instance.
        /// </param>
        /// <param name="instanceCount">
        /// Number of instances to draw.
        /// </param>
        /// <param name="startIndexLocation">
        /// he location of the first index read by the GPU from the index buffer.
        /// </param>
        /// <param name="baseVertexLocation">
        /// A value added to each index before reading a vertex from the vertex buffer.
        /// </param>
        /// <param name="startInstanceLocation">
        /// A value added to each index before reading per-instance data from a vertex buffer.
        /// </param>
        void DrawIndexedInstanced( _In_ UINT indexCountPerInstance, _In_ UINT instanceCount, _In_ UINT startIndexLocation, _In_ INT baseVertexLocation, _In_ UINT startInstanceLocation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DrawIndexedInstanced( indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation );
        }

        /// <summary>
        /// Executes a command list from a thread group.
        /// </summary>
        /// <param name="threadGroupCountX">
        /// The number of groups dispatched in the x direction. ThreadGroupCountX must be less 
        /// than or equal to D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535).
        /// </param>
        /// <param name="threadGroupCountY">
        /// The number of groups dispatched in the y direction. ThreadGroupCountY must be less 
        /// than or equal to D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535).
        /// </param>
        /// <param name="threadGroupCountZ">
        /// The number of groups dispatched in the z direction. ThreadGroupCountZ must be less 
        /// than or equal to D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION (65535). In 
        /// feature level 10 the value for ThreadGroupCountZ must be 1.
        /// </param>
        /// <remarks>
        /// You call the Dispatch method to execute commands in a compute shader. A compute 
        /// shader can be run on many threads in parallel, within a thread group. Index a 
        /// particular thread, within a thread group using a 3D vector given by (x,y,z).
        /// </remarks>
        void Dispatch( _In_ UINT threadGroupCountX, _In_ UINT threadGroupCountY, _In_ UINT threadGroupCountZ ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Dispatch( threadGroupCountX, threadGroupCountY, threadGroupCountZ );
        }


        /// <summary>
        /// Copies a region of a buffer from one resource to another.
        /// </summary>
        /// <param name="dstBuffer">
        /// Specifies the destination ID3D12Resource.
        /// </param>
        /// <param name="dstOffset">
        /// Specifies a UINT64 offset (in bytes) into the destination resource.
        /// </param>
        /// <param name="srcBuffer">
        /// Specifies the source ID3D12Resource.
        /// </param>
        /// <param name="srcOffset">
        /// Specifies a UINT64 offset (in bytes) into the source resource, to start the copy from.
        /// </param>
        /// <param name="numBytes">
        /// Specifies the number of bytes to copy.
        /// </param>
        void CopyBufferRegion( _In_ ID3D12Resource* dstBuffer, UINT64 dstOffset, _In_ ID3D12Resource* srcBuffer, UINT64 srcOffset, UINT64 numBytes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyBufferRegion( dstBuffer, dstOffset, srcBuffer, srcOffset, numBytes );
        }

        /// <summary>
        /// Copies a region of a buffer from one resource to another.
        /// </summary>
        /// <param name="dstBuffer">
        /// Specifies the destination Resource.
        /// </param>
        /// <param name="dstOffset">
        /// Specifies a UINT64 offset (in bytes) into the destination resource.
        /// </param>
        /// <param name="srcBuffer">
        /// Specifies the source Resource.
        /// </param>
        /// <param name="srcOffset">
        /// Specifies a UINT64 offset (in bytes) into the source resource, to start the copy from.
        /// </param>
        /// <param name="numBytes">
        /// Specifies the number of bytes to copy.
        /// </param>
        void CopyBufferRegion( const Resource& dstBuffer, UINT64 dstOffset, const Resource& srcBuffer, UINT64 srcOffset, UINT64 numBytes ) const
        {
            CopyBufferRegion( dstBuffer.GetInterfacePointer<ID3D12Resource>(), dstOffset, srcBuffer.GetInterfacePointer<ID3D12Resource>( ), srcOffset, numBytes );
        }

        /// <summary>
        /// This function uses the GPU to copy texture data between two locations. Both 
        /// the source and the destination may reference texture data located within either 
        /// a buffer resource or a texture resource.
        /// </summary>
        /// <param name="destination">
        /// Specifies the destination <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_texture_copy_location">D3D12_TEXTURE_COPY_LOCATION</see>. 
        /// The subresource referred to must be in the D3D12_RESOURCE_STATE_COPY_DEST state.
        /// </param>
        /// <param name="destinationX">
        /// The x-coordinate of the upper left corner of the destination region.
        /// </param>
        /// <param name="destinationY">
        /// The y-coordinate of the upper left corner of the destination region. For a 1D subresource, this must be zero.
        /// </param>
        /// <param name="destinationZ">
        /// The z-coordinate of the upper left corner of the destination region. For a 1D or 2D subresource, this must be zero.
        /// </param>
        /// <param name="source">
        /// Specifies the source <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_texture_copy_location">D3D12_TEXTURE_COPY_LOCATION</see>. 
        /// The subresource referred to must be in the D3D12_RESOURCE_STATE_COPY_SOURCE state.
        /// </param>
        /// <param name="sourceBox">
        /// Specifies an optional <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_box">D3D12_BOX</see> that sets the size of the source texture to copy.
        /// </param>
        /// <remarks>
        /// <p>
        /// The source box must be within the size of the source resource. The destination offsets, 
        /// (x, y, and z), allow the source box to be offset when writing into the destination resource; 
        /// however, the dimensions of the source box and the offsets must be within the size of the 
        /// resource. If you try and copy outside the destination resource or specify a source box that 
        /// is larger than the source resource, the behavior of CopyTextureRegion is undefined. If you 
        /// created a device that supports the debug layer, the debug output reports an error on this 
        /// invalid CopyTextureRegion call. Invalid parameters to CopyTextureRegion cause undefined 
        /// behavior and might result in incorrect rendering, clipping, no copy, or even the removal 
        /// of the rendering device.
        /// </p>
        /// <p>
        /// If the resources are buffers, all coordinates are in bytes; if the resources are textures, 
        /// all coordinates are in texels.
        /// </p>
        /// <p>
        /// CopyTextureRegion performs the copy on the GPU (similar to a memcpy by the CPU). As a consequence, the source and destination resources:
        /// <list type="bullet">
        ///     <item>
        ///     Must be different subresources (although they can be from the same resource).
        ///     </item>
        ///     <item>
        ///     Must have compatible DXGI_FORMATs (identical or from the same type group). For example, 
        ///     a DXGI_FORMAT_R32G32B32_FLOAT texture can be copied to a DXGI_FORMAT_R32G32B32_UINT 
        ///     texture since both of these formats are in the DXGI_FORMAT_R32G32B32_TYPELESS group. 
        ///     CopyTextureRegion can copy between a few format types. For more info, 
        ///     see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-graphics-programming-guide-resources-block-compression">Format Conversion using Direct3D 10.1</see>.
        ///     </item>
        /// </list>
        /// </p>
        /// <p>
        /// CopyTextureRegion only supports copy; it does not support any stretch, color key, or blend. 
        /// CopyTextureRegion can reinterpret the resource data between a few format types.
        /// </p>
        /// <p>
        /// Note that for a depth-stencil buffer, the depth and stencil planes are separate subresources within the buffer.
        /// </p>
        /// <p>
        /// To copy an entire resource, rather than just a region of a subresource, we recommend to use CopyResource instead.
        /// </p>
        /// </remarks>
        void CopyTextureRegion( _In_ const D3D12_TEXTURE_COPY_LOCATION* destination, UINT destinationX, UINT destinationY, UINT destinationZ, _In_ const D3D12_TEXTURE_COPY_LOCATION* source, _In_opt_ const D3D12_BOX* sourceBox ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyTextureRegion( destination, destinationX, destinationY, destinationZ, source, sourceBox );
        }

        /// <summary>
        /// This function uses the GPU to copy texture data between two locations. Both 
        /// the source and the destination may reference texture data located within either 
        /// a buffer resource or a texture resource.
        /// </summary>
        /// <param name="destination">
        /// Specifies the destination <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_texture_copy_location">D3D12_TEXTURE_COPY_LOCATION</see>. 
        /// The subresource referred to must be in the D3D12_RESOURCE_STATE_COPY_DEST state.
        /// </param>
        /// <param name="destinationX">
        /// The x-coordinate of the upper left corner of the destination region.
        /// </param>
        /// <param name="destinationY">
        /// The y-coordinate of the upper left corner of the destination region. For a 1D subresource, this must be zero.
        /// </param>
        /// <param name="destinationZ">
        /// The z-coordinate of the upper left corner of the destination region. For a 1D or 2D subresource, this must be zero.
        /// </param>
        /// <param name="source">
        /// Specifies the source <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_texture_copy_location">D3D12_TEXTURE_COPY_LOCATION</see>. 
        /// The subresource referred to must be in the D3D12_RESOURCE_STATE_COPY_SOURCE state.
        /// </param>
        /// <param name="sourceBox">
        /// Specifies an optional <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_box">D3D12_BOX</see> that sets the size of the source texture to copy.
        /// </param>
        /// <remarks>
        /// <p>
        /// The source box must be within the size of the source resource. The destination offsets, 
        /// (x, y, and z), allow the source box to be offset when writing into the destination resource; 
        /// however, the dimensions of the source box and the offsets must be within the size of the 
        /// resource. If you try and copy outside the destination resource or specify a source box that 
        /// is larger than the source resource, the behavior of CopyTextureRegion is undefined. If you 
        /// created a device that supports the debug layer, the debug output reports an error on this 
        /// invalid CopyTextureRegion call. Invalid parameters to CopyTextureRegion cause undefined 
        /// behavior and might result in incorrect rendering, clipping, no copy, or even the removal 
        /// of the rendering device.
        /// </p>
        /// <p>
        /// If the resources are buffers, all coordinates are in bytes; if the resources are textures, 
        /// all coordinates are in texels.
        /// </p>
        /// <p>
        /// CopyTextureRegion performs the copy on the GPU (similar to a memcpy by the CPU). As a consequence, the source and destination resources:
        /// <list type="bullet">
        ///     <item>
        ///     Must be different subresources (although they can be from the same resource).
        ///     </item>
        ///     <item>
        ///     Must have compatible DXGI_FORMATs (identical or from the same type group). For example, 
        ///     a DXGI_FORMAT_R32G32B32_FLOAT texture can be copied to a DXGI_FORMAT_R32G32B32_UINT 
        ///     texture since both of these formats are in the DXGI_FORMAT_R32G32B32_TYPELESS group. 
        ///     CopyTextureRegion can copy between a few format types. For more info, 
        ///     see <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-graphics-programming-guide-resources-block-compression">Format Conversion using Direct3D 10.1</see>.
        ///     </item>
        /// </list>
        /// </p>
        /// <p>
        /// CopyTextureRegion only supports copy; it does not support any stretch, color key, or blend. 
        /// CopyTextureRegion can reinterpret the resource data between a few format types.
        /// </p>
        /// <p>
        /// Note that for a depth-stencil buffer, the depth and stencil planes are separate subresources within the buffer.
        /// </p>
        /// <p>
        /// To copy an entire resource, rather than just a region of a subresource, we recommend to use CopyResource instead.
        /// </p>
        /// </remarks>
        void CopyTextureRegion( _In_ const TextureCopyLocation* destination, UINT destinationX, UINT destinationY, UINT destinationZ, _In_ const TextureCopyLocation* source, _In_opt_ const Box* sourceBox ) const
        {
            CopyTextureRegion( reinterpret_cast<const D3D12_TEXTURE_COPY_LOCATION *>( destination ), destinationX, destinationY, destinationZ, reinterpret_cast< const D3D12_TEXTURE_COPY_LOCATION* >( source ), reinterpret_cast< const D3D12_BOX* >( sourceBox ) );
        }

        /// <summary>
        /// Copies the entire contents of the source resource to the destination resource.
        /// </summary>
        /// <param name="destinationResource">
        /// Specifies the destination ID3D12Resource.
        /// </param>
        /// <param name="sourceResource">
        /// Specifies the source ID3D12Resource.
        /// </param>
        void CopyResource( _In_ ID3D12Resource* destinationResource, _In_ ID3D12Resource* sourceResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyResource( destinationResource, sourceResource );
        }

        /// <summary>
        /// Copies the entire contents of the source resource to the destination resource.
        /// </summary>
        /// <param name="destinationResource">
        /// Specifies the destination Resource.
        /// </param>
        /// <param name="sourceResource">
        /// Specifies the source Resource.
        /// </param>
        void CopyResource( const Resource& dstResource, const Resource& srcResource ) const
        {
            CopyResource( dstResource.GetInterfacePointer<ID3D12Resource>( ), srcResource.GetInterfacePointer<ID3D12Resource>( ) );
        }

        /// <summary>
        /// Copies tiles from buffer to tiled resource or vice versa.
        /// </summary>
        /// <param name="tiledResource">
        /// Specifies a tiled resource.
        /// </param>
        /// <param name="tileRegionStartCoordinate">
        /// A pointer to a <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_tiled_resource_coordinate">D3D12_TILED_RESOURCE_COORDINATE</see> 
        /// structure that describes the starting coordinates of the tiled resource.
        /// </param>
        /// <param name="tileRegionSize">
        /// A pointer to a <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_tile_region_size">D3D12_TILE_REGION_SIZE</see> 
        /// structure that describes the size of the tiled region.
        /// </param>
        /// <param name="buffer">
        /// Specifies an ID3D12Resource that represents a default, dynamic, or staging buffer.
        /// </param>
        /// <param name="bufferStartOffsetInBytes">
        /// The offset in bytes into the buffer to start the operation.
        /// </param>
        /// <param name="flags">
        /// A combination of <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ne-d3d12-d3d12_tile_copy_flags">D3D12_TILE_COPY_FLAGS</see>-typed 
        /// values that are combined by using a bitwise OR operation and that identifies how to copy tiles.
        /// </param>
        /// <remarks>
        /// <p>
        /// CopyTiles drops write operations to unmapped areas and handles read operations from 
        /// unmapped areas (except on Tier_1 tiled resources, where reading and writing unmapped 
        /// areas is invalid - refer to D3D12_TILED_RESOURCES_TIER).
        /// </p>
        /// <p>
        /// If a copy operation involves writing to the same memory location multiple times because 
        /// multiple locations in the destination resource are mapped to the same tile memory, the 
        /// resulting write operations to multi-mapped tiles are non-deterministic and non-repeatable; 
        /// that is, accesses to the tile memory happen in whatever order the hardware happens to 
        /// execute the copy operation.
        /// </p>
        /// <p>
        /// The tiles involved in the copy operation can't include tiles that contain packed mipmaps or 
        /// results of the copy operation are undefined. To transfer data to and from mipmaps that the 
        /// hardware packs into the one-or-more tiles that constitute the packed mips, you must use 
        /// the standard (that is, non-tile specific) copy APIs like CopyTextureRegion.
        /// </p>
        /// <p>
        /// CopyTiles does copy data in a slightly different pattern than the standard copy methods.
        /// </p>
        /// <p>
        /// The memory layout of the tiles in the non-tiled buffer resource side of the copy operation 
        /// is linear in memory within 64 KB tiles, which the hardware and driver swizzle and de-swizzle 
        /// per tile as appropriate when they transfer to and from a tiled resource. For multisample 
        /// antialiasing (MSAA) surfaces, the hardware and driver traverse each pixel's samples in 
        /// sample-index order before they move to the next pixel. For tiles that are partially filled 
        /// on the right side (for a surface that has a width not a multiple of tile width in pixels), 
        /// the pitch and stride to move down a row is the full size in bytes of the number pixels that 
        /// would fit across the tile if the tile was full. So, there can be a gap between each row of 
        /// pixels in memory. Mipmaps that are smaller than a tile are not packed together in the linear 
        /// layout, which might seem to be a waste of memory space, but as mentioned you can't use 
        /// CopyTiles to copy to mipmaps that the hardware packs together. You can just use generic copy 
        /// APIs, like CopyTextureRegion, to copy small mipmaps individually.
        /// </p>
        /// </remarks>
        void CopyTiles( _In_ ID3D12Resource* tiledResource, _In_ const D3D12_TILED_RESOURCE_COORDINATE* tileRegionStartCoordinate, _In_ const D3D12_TILE_REGION_SIZE* tileRegionSize, _In_ ID3D12Resource* buffer, UINT64 bufferStartOffsetInBytes, D3D12_TILE_COPY_FLAGS flags = D3D12_TILE_COPY_FLAGS::D3D12_TILE_COPY_FLAG_NONE ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CopyTiles( tiledResource, tileRegionStartCoordinate, tileRegionSize, buffer, bufferStartOffsetInBytes, flags );
        }

        /// <summary>
        /// Copies tiles from buffer to tiled resource or vice versa.
        /// </summary>
        /// <param name="tiledResource">
        /// Specifies a tiled resource.
        /// </param>
        /// <param name="tileRegionStartCoordinate">
        /// A pointer to a <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_tiled_resource_coordinate">D3D12_TILED_RESOURCE_COORDINATE</see> 
        /// structure that describes the starting coordinates of the tiled resource.
        /// </param>
        /// <param name="tileRegionSize">
        /// A pointer to a <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_tile_region_size">D3D12_TILE_REGION_SIZE</see> 
        /// structure that describes the size of the tiled region.
        /// </param>
        /// <param name="buffer">
        /// Specifies a Resource that represents a default, dynamic, or staging buffer.
        /// </param>
        /// <param name="bufferStartOffsetInBytes">
        /// The offset in bytes into the buffer to start the operation.
        /// </param>
        /// <param name="flags">
        /// A combination of <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ne-d3d12-d3d12_tile_copy_flags">D3D12_TILE_COPY_FLAGS</see>-typed 
        /// values that are combined by using a bitwise OR operation and that identifies how to copy tiles.
        /// </param>
        /// <remarks>
        /// <p>
        /// CopyTiles drops write operations to unmapped areas and handles read operations from 
        /// unmapped areas (except on Tier_1 tiled resources, where reading and writing unmapped 
        /// areas is invalid - refer to D3D12_TILED_RESOURCES_TIER).
        /// </p>
        /// <p>
        /// If a copy operation involves writing to the same memory location multiple times because 
        /// multiple locations in the destination resource are mapped to the same tile memory, the 
        /// resulting write operations to multi-mapped tiles are non-deterministic and non-repeatable; 
        /// that is, accesses to the tile memory happen in whatever order the hardware happens to 
        /// execute the copy operation.
        /// </p>
        /// <p>
        /// The tiles involved in the copy operation can't include tiles that contain packed mipmaps or 
        /// results of the copy operation are undefined. To transfer data to and from mipmaps that the 
        /// hardware packs into the one-or-more tiles that constitute the packed mips, you must use 
        /// the standard (that is, non-tile specific) copy APIs like CopyTextureRegion.
        /// </p>
        /// <p>
        /// CopyTiles does copy data in a slightly different pattern than the standard copy methods.
        /// </p>
        /// <p>
        /// The memory layout of the tiles in the non-tiled buffer resource side of the copy operation 
        /// is linear in memory within 64 KB tiles, which the hardware and driver swizzle and de-swizzle 
        /// per tile as appropriate when they transfer to and from a tiled resource. For multisample 
        /// antialiasing (MSAA) surfaces, the hardware and driver traverse each pixel's samples in 
        /// sample-index order before they move to the next pixel. For tiles that are partially filled 
        /// on the right side (for a surface that has a width not a multiple of tile width in pixels), 
        /// the pitch and stride to move down a row is the full size in bytes of the number pixels that 
        /// would fit across the tile if the tile was full. So, there can be a gap between each row of 
        /// pixels in memory. Mipmaps that are smaller than a tile are not packed together in the linear 
        /// layout, which might seem to be a waste of memory space, but as mentioned you can't use 
        /// CopyTiles to copy to mipmaps that the hardware packs together. You can just use generic copy 
        /// APIs, like CopyTextureRegion, to copy small mipmaps individually.
        /// </p>
        /// </remarks>
        void CopyTiles( const Resource& tiledResource, _In_ const D3D12_TILED_RESOURCE_COORDINATE* tileRegionStartCoordinate, _In_ const D3D12_TILE_REGION_SIZE* tileRegionSize, const Resource& buffer, UINT64 bufferStartOffsetInBytes, D3D12_TILE_COPY_FLAGS flags = D3D12_TILE_COPY_FLAGS::D3D12_TILE_COPY_FLAG_NONE ) const
        {
            CopyTiles( tiledResource.GetInterfacePointer<ID3D12Resource>( ), tileRegionStartCoordinate, tileRegionSize, buffer.GetInterfacePointer<ID3D12Resource>( ), bufferStartOffsetInBytes, flags );
        }


        /// <summary>
        /// Copy a multi-sampled resource into a non-multi-sampled resource.
        /// </summary>
        /// <param name="destinationResource">
        /// Destination resource. Must be a created on a D3D12_HEAP_TYPE_DEFAULT heap and be single-sampled.
        /// </param>
        /// <param name="destinationSubresource">
        /// A zero-based index, that identifies the destination subresource. 
        /// Use D3D12CalcSubresource to calculate the subresource index if the parent 
        /// resource is complex.
        /// </param>
        /// <param name="sourceResource">
        /// Source resource. Must be multisampled.
        /// </param>
        /// <param name="sourceSubresource">
        /// The source subresource of the source resource.
        /// </param>
        /// <param name="format">
        /// A DXGI_FORMAT that indicates how the multisampled resource will be resolved to a single-sampled resource. 
        /// </param>
        void ResolveSubresource( _In_ ID3D12Resource* destinationResource, _In_ UINT destinationSubresource, _In_ ID3D12Resource* sourceResource, _In_ UINT sourceSubresource, _In_ DXGI_FORMAT format ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ResolveSubresource( destinationResource, destinationSubresource, sourceResource, sourceSubresource, format );
        }

        void ResolveSubresource( const Resource& destinationResource, _In_ UINT destinationSubresource, const Resource& sourceResource, _In_ UINT sourceSubresource, _In_ DXGI_FORMAT format ) const
        {
            ResolveSubresource( destinationResource.GetInterfacePointer<ID3D12Resource>( ), destinationSubresource, sourceResource.GetInterfacePointer<ID3D12Resource>( ), sourceSubresource, format );
        }

        /// <summary>
        /// Bind information about the primitive type, and data order 
        /// that describes input data for the input assembler stage.
        /// </summary>
        /// <param name="primitiveTopology">
        /// The type of primitive and ordering of the primitive data 
        /// (see <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3dcommon/ne-d3dcommon-d3d_primitive_topology">D3D_PRIMITIVE_TOPOLOGY</see> ).
        /// </param>
        void IASetPrimitiveTopology( _In_ D3D12_PRIMITIVE_TOPOLOGY primitiveTopology ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->IASetPrimitiveTopology( primitiveTopology );
        }

        /// <summary>
        /// Bind an array of viewports to the rasterizer stage of the pipeline.
        /// </summary>
        /// <param name="numberOfViewports">
        /// Number of viewports to bind.
        /// </param>
        /// <param name="viewports">
        /// An array of <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ns-d3d12-d3d12_viewport">D3D12_VIEWPORT</see> 
        /// structures to bind to the device.
        /// </param>
        /// <remarks>
        /// <para>
        /// All viewports must be set atomically as one operation. Any viewports not 
        /// defined by the call are disabled.
        /// </para>
        /// <para>
        /// Which viewport to use is determined by the <see href="https://learn.microsoft.com/en-us/windows/desktop/direct3dhlsl/dx-graphics-hlsl-semantics">SV_ViewportArrayIndex</see> 
        /// semantic output by a geometry shader; if a geometry shader does not specify 
        /// the semantic, Direct3D will use the first viewport in the array.
        /// </para>
        /// </remarks>
        void RSSetViewports( _In_range_( 0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )  UINT numberOfViewports, _In_reads_( numberOfViewports )  const D3D12_VIEWPORT* viewports ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RSSetViewports( numberOfViewports, viewports );
        }

        template<SimpleSpanLike SpanT>
            requires std::is_convertible_v<typename SpanT::value_type, const D3D12_VIEWPORT>
        void RSSetViewports( const SpanT& viewports ) const
        {
            RSSetViewports( static_cast<UINT>( viewports.size() ), viewports.data() );
        }

        /// <summary>
        /// Binds an array of scissor rectangles to the rasterizer stage.
        /// </summary>
        /// <param name="numberOfScissorRectangles">
        /// The number of scissor rectangles to bind.
        /// </param>
        /// <param name="scissorRectangles">
        /// An array of scissor rectangles.
        /// </param>
        /// <remarks>
        /// <para>
        /// All scissor rectangles must be set atomically as one operation. 
        /// Any scissor rectangles not defined by the call are disabled.
        /// </para>
        /// <para>
        /// Which scissor rectangle to use is determined by the SV_ViewportArrayIndex semantic 
        /// output by a geometry shader (see shader semantic syntax). If a geometry shader does 
        /// not make use of the SV_ViewportArrayIndex semantic then Direct3D will use the first 
        /// scissor rectangle in the array.
        /// </para>
        /// <para>
        /// Each scissor rectangle in the array corresponds to a viewport in an array of viewports.
        /// </para>
        /// </remarks>
        void RSSetScissorRects( _In_range_( 0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )  UINT numberOfScissorRectangles, _In_reads_( numberOfScissorRectangles )  const D3D12_RECT* scissorRectangles ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RSSetScissorRects( numberOfScissorRectangles, scissorRectangles );
        }

        void RSSetScissorRects( _In_range_( 0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )  UINT numberOfScissorRectangles, _In_reads_( numberOfScissorRectangles )  const Rectangle* scissorRectangles ) const
        {
            RSSetScissorRects( numberOfScissorRectangles, reinterpret_cast< const D3D12_RECT* >( scissorRectangles ) );
        }


        template<SimpleSpanLike SpanT>
            requires std::is_convertible_v<typename SpanT::value_type, const D3D12_RECT>
        void RSSetViewports( const SpanT& scissorRectangles ) const
        {
            RSSetViewports( static_cast< UINT >( scissorRectangles.size( ) ), scissorRectangles.data( ) );
        }

        /// <summary>
        /// Sets the blend factors that modulate values for a pixel shader, render target, or both.
        /// </summary>
        /// <param name="blendFactors">
        /// Array of blend factors, one for each RGBA component.
        /// </param>
        /// <remarks>
        /// <para>
        /// If you created the blend-state object with D3D12_BLEND_BLEND_FACTOR 
        /// or D3D12_BLEND_INV_BLEND_FACTOR, then the blending stage uses the 
        /// non-NULL array of blend factors. Otherwise,the blending stage doesn't use 
        /// the non-NULL array of blend factors; the runtime stores the blend factors.
        /// </para>
        /// <para>
        /// If you pass nullptr, then the runtime uses or stores a blend factor equal to <c>{ 1, 1, 1, 1 }</c>.
        /// </para>
        /// </remarks>
        void OMSetBlendFactor( _In_reads_opt_( 4 ) const FLOAT blendFactors[4] ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OMSetBlendFactor( blendFactors );
        }

        /// <summary>
        /// Sets the reference value for depth stencil tests.
        /// </summary>
        /// <param name="stencilRef">
        /// Reference value to perform against when doing a depth-stencil test.
        /// </param>
        void OMSetStencilRef( _In_ UINT stencilRef ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OMSetStencilRef( stencilRef );
        }

        /// <summary>
        /// Sets all shaders and programs most of the fixed-function state of the graphics processing unit (GPU) pipeline.
        /// </summary>
        /// <param name="pipelineState">
        /// Pointer to the ID3D12PipelineState containing the pipeline state data.
        /// </param>
        void SetPipelineState( _In_  ID3D12PipelineState* pipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetPipelineState( pipelineState );
        }

        void SetPipelineState( const PipelineState& pipelineState ) const
        {
            SetPipelineState( pipelineState.GetInterfacePointer<ID3D12PipelineState>( ) );
        }

        /// <summary>
        /// Notifies the driver that it needs to synchronize multiple accesses to resources.
        /// </summary>
        /// <param name="numberOfBarriers">
        /// The number of submitted barrier descriptions.
        /// </param>
        /// <param name="barriers">
        /// Pointer to an array of barrier descriptions.
        /// </param>
        void ResourceBarrier( _In_ UINT numberOfBarriers, _In_reads_( numberOfBarriers )  const D3D12_RESOURCE_BARRIER* barriers ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ResourceBarrier( numberOfBarriers, barriers );
        }

        void ResourceBarrier( _In_ UINT numberOfBarriers, _In_reads_( numberOfBarriers )  const D3D12::ResourceBarrier* barriers ) const
        {
            ResourceBarrier( numberOfBarriers, reinterpret_cast< const D3D12_RESOURCE_BARRIER* >( barriers ) );
        }


        template<SimpleSpanLike SpanT>
            requires ( std::is_convertible_v<typename SpanT::value_type, const D3D12_RESOURCE_BARRIER> || std::is_convertible_v<typename SpanT::value_type, const D3D12::ResourceBarrier> )
        void ResourceBarrier( const SpanT& barriers ) const
        {
            ResourceBarrier( static_cast< UINT >( barriers.size( ) ), barriers.data( ) );
        }

        /// <summary>
        /// Creates a ResourceBarrier that describes the transition of subresources between different usages.
        /// </summary>
        /// <param name="resource">
        /// The resource used in the transition.
        /// </param>
        /// <param name="stateBefore">
        /// The "before" usages of the subresources, as a bitwise-OR'd combination of <c>ResourceStates</c> enumeration constants.
        /// </param>
        /// <param name="stateAfter">
        /// The "after" usages of the subresources, as a bitwise-OR'd combination of <c>ResourceStates</c> enumeration constants.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource for the transition. Defaults to the 
        /// D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES flag ( 0xffffffff ) which 
        /// transitions all subresources in a resource at the same time.
        /// </param>
        void ResourceBarrier( ID3D12Resource* resource, ResourceStates stateBefore, ResourceStates stateAfter, ResourceBarrierFlags flags = ResourceBarrierFlags::None, UInt32 subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES ) noexcept
        {
            D3D12::ResourceBarrier resourceBarrier( resource, stateBefore, stateAfter, flags, subresource );
            ResourceBarrier( 1, &resourceBarrier );
        }

        /// <summary>
        /// Creates a ResourceBarrier that describes the transition of subresources between different usages.
        /// </summary>
        /// <param name="resource">
        /// The resource used in the transition.
        /// </param>
        /// <param name="stateBefore">
        /// The "before" usages of the subresources, as a bitwise-OR'd combination of <c>ResourceStates</c> enumeration constants.
        /// </param>
        /// <param name="stateAfter">
        /// The "after" usages of the subresources, as a bitwise-OR'd combination of <c>ResourceStates</c> enumeration constants.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        /// <param name="subresource">
        /// The index of the subresource for the transition. Defaults to the 
        /// D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES flag ( 0xffffffff ) which 
        /// transitions all subresources in a resource at the same time.
        /// </param>
        void ResourceBarrier( const Resource& resource, ResourceStates stateBefore, ResourceStates stateAfter, ResourceBarrierFlags flags = ResourceBarrierFlags::None, UInt32 subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES ) noexcept
        {
            D3D12::ResourceBarrier resourceBarrier( resource, stateBefore, stateAfter, flags, subresource );
            ResourceBarrier( 1, &resourceBarrier );
        }

        /// <summary>
        /// Creates a ResourceBarrier that describes the transition 
        /// between usages of two different resources that have 
        /// mappings into the same heap.
        /// </summary>
        /// <param name="resourceBefore">
        /// Represents the before resource used in the transition.
        /// </param>
        /// <param name="resourceAfter">
        /// Represents the after resource used in the transition.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        /// <remarks>
        /// Both the before and the after resources can be specified 
        /// or one or both resources can be NULL, which indicates that 
        /// any placed or reserved resource could cause aliasing.
        /// </remarks>
        void ResourceBarrier( ID3D12Resource* resourceBefore, ID3D12Resource* resourceAfter, ResourceBarrierFlags flags = ResourceBarrierFlags::None ) noexcept
        {
            D3D12::ResourceBarrier resourceBarrier( resourceBefore, resourceAfter, flags );
            ResourceBarrier( 1, &resourceBarrier );
        }

        /// <summary>
        /// Creates a ResourceBarrier that describes the transition 
        /// between usages of two different resources that have 
        /// mappings into the same heap.
        /// </summary>
        /// <param name="resourceBefore">
        /// Represents the before resource used in the transition.
        /// </param>
        /// <param name="resourceAfter">
        /// Represents the after resource used in the transition.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        /// <remarks>
        /// Both the before and the after resources can be specified 
        /// or one or both resources can be NULL, which indicates that 
        /// any placed or reserved resource could cause aliasing.
        /// </remarks>
        void ResourceBarrier( const Resource& resourceBefore, const Resource& resourceAfter, ResourceBarrierFlags flags = ResourceBarrierFlags::None ) noexcept
        {
            D3D12::ResourceBarrier resourceBarrier( resourceBefore, resourceAfter, flags );
            ResourceBarrier( 1, &resourceBarrier );
        }

        /// <summary>
        /// Creates a ResourceBarrier representing a resource for 
        /// which all UAV accesses must complete before any future UAV accesses can begin.
        /// </summary>
        /// <param name="resource">
        /// The resource used in the transition.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        void ResourceBarrier( ID3D12Resource* resource, ResourceBarrierFlags flags = ResourceBarrierFlags::None ) noexcept
        {
            D3D12::ResourceBarrier resourceBarrier( resource, flags );
            ResourceBarrier( 1, &resourceBarrier );
        }
        /// <summary>
        /// Creates a ResourceBarrier representing a resource for 
        /// which all UAV accesses must complete before any future UAV accesses can begin.
        /// </summary>
        /// <param name="resource">
        /// The resource used in the transition.
        /// </param>
        /// <param name="flags">
        /// Specifies a value from the ResourceBarrierFlags enumeration.
        /// </param>
        void ResourceBarrier( const Resource& resource, ResourceBarrierFlags flags = ResourceBarrierFlags::None ) noexcept
        {
            D3D12::ResourceBarrier resourceBarrier( resource, flags );
            ResourceBarrier( 1, &resourceBarrier );
        }



        void ExecuteBundle( _In_ ID3D12GraphicsCommandList* commandList ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ExecuteBundle( commandList );
        }

        void ExecuteBundle( const GraphicsCommandList& commandList ) const
        {
            ExecuteBundle( commandList.GetInterfacePointer<ID3D12GraphicsCommandList>( ) );
        }

        void SetDescriptorHeaps( _In_  UINT numDescriptorHeaps, _In_reads_( numDescriptorHeaps )  ID3D12DescriptorHeap* const* descriptorHeapsPtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetDescriptorHeaps( numDescriptorHeaps, descriptorHeapsPtr );
        }

        void SetDescriptorHeaps( _In_  UINT numDescriptorHeaps, _In_reads_( numDescriptorHeaps ) const DescriptorHeap* descriptorHeapsPtr ) const
        {
            SetDescriptorHeaps( numDescriptorHeaps, reinterpret_cast< ID3D12DescriptorHeap* const* >(descriptorHeapsPtr) );
        }


        template<size_t N>
        void SetDescriptorHeaps( const std::array<DescriptorHeap,N>& descriptorHeaps ) const
        {
            std::array<ID3D12DescriptorHeap*, N> heaps;
            for ( size_t i = 0; i < N; i++ )
            {
                heaps[i] = descriptorHeaps[i].GetInterfacePointer<ID3D12DescriptorHeap>( );
            }
            SetDescriptorHeaps(static_cast<UINT>(N), heaps.data() );
        }
        template<size_t N>
        void SetDescriptorHeaps( DescriptorHeap( &descriptorHeaps )[N] ) const
        {
            std::array<ID3D12DescriptorHeap*, N> heaps;
            for ( size_t i = 0; i < N; i++ )
            {
                heaps[i] = descriptorHeaps[i].GetInterfacePointer<ID3D12DescriptorHeap>( );
            }
            SetDescriptorHeaps( static_cast<UINT>( N ), heaps.data( ) );
        }
        void SetDescriptorHeaps( const DescriptorHeap& descriptorHeap ) const
        {
            ID3D12DescriptorHeap* ptr = descriptorHeap.GetInterfacePointer<ID3D12DescriptorHeap>( );
            SetDescriptorHeaps( 1, &ptr );
        }

        void SetComputeRootSignature( _In_opt_ ID3D12RootSignature* rootSignature = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetComputeRootSignature( rootSignature );
        }

        void SetComputeRootSignature( const RootSignature& rootSignature ) const
        {
            SetComputeRootSignature( rootSignature.GetInterfacePointer<ID3D12RootSignature>( ) );
        }

        void SetGraphicsRootSignature( _In_opt_ ID3D12RootSignature* rootSignature = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetGraphicsRootSignature( rootSignature );
        }

        void SetGraphicsRootSignature( const RootSignature& rootSignature ) const
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

        void ClearUnorderedAccessViewUint( _In_ D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap, _In_ D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle, const Resource& resource, _In_ const UINT values[4], _In_ UINT numRects, _In_reads_( numRects ) const D3D12_RECT* rectsPtr ) const
        {
            ClearUnorderedAccessViewUint( viewGPUHandleInCurrentHeap, viewCPUHandle, resource.GetInterfacePointer<ID3D12Resource>(), values, numRects, rectsPtr );
        }

        void ClearUnorderedAccessViewFloat( _In_ D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap, _In_ D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle, _In_ ID3D12Resource* resource, _In_ const FLOAT values[4], _In_ UINT numRects, _In_reads_( numRects ) const D3D12_RECT* rectsPtr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ClearUnorderedAccessViewFloat( viewGPUHandleInCurrentHeap, viewCPUHandle, resource, values, numRects, rectsPtr );
        }

        void ClearUnorderedAccessViewFloat( _In_ D3D12_GPU_DESCRIPTOR_HANDLE viewGPUHandleInCurrentHeap, _In_ D3D12_CPU_DESCRIPTOR_HANDLE viewCPUHandle, const Resource& resource, _In_ const FLOAT values[4], _In_ UINT numRects, _In_reads_( numRects ) const D3D12_RECT* rectsPtr ) const
        {
            ClearUnorderedAccessViewFloat( viewGPUHandleInCurrentHeap, viewCPUHandle, resource.GetInterfacePointer<ID3D12Resource>( ), values, numRects, rectsPtr );
        }

        void DiscardResource( _In_ ID3D12Resource* resource, _In_opt_ const D3D12_DISCARD_REGION* region = nullptr ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DiscardResource( resource, region );
        }

        void DiscardResource( const Resource& resource, _In_opt_ const D3D12_DISCARD_REGION* region = nullptr ) const
        {
            DiscardResource( resource.GetInterfacePointer<ID3D12Resource>( ), region );
        }

        void BeginQuery( _In_ ID3D12QueryHeap* queryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT index ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->BeginQuery( queryHeap, type, index );
        }

        void BeginQuery( const QueryHeap& queryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT index ) const
        {
            BeginQuery( queryHeap.GetInterfacePointer<ID3D12QueryHeap>( ), type, index );
        }


        void EndQuery( _In_ ID3D12QueryHeap* queryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT index ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->EndQuery( queryHeap, type, index );
        }

        void EndQuery( const QueryHeap& queryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT index ) const
        {
            EndQuery( queryHeap.GetInterfacePointer<ID3D12QueryHeap>( ), type, index );
        }

        void ResolveQueryData( _In_ ID3D12QueryHeap* pQueryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT startIndex, _In_ UINT numQueries, _In_ ID3D12Resource* pDestinationBuffer, _In_ UINT64 alignedDestinationBufferOffset ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ResolveQueryData( pQueryHeap, type, startIndex, numQueries, pDestinationBuffer, alignedDestinationBufferOffset );
        }

        void ResolveQueryData( const QueryHeap& pQueryHeap, _In_ D3D12_QUERY_TYPE type, _In_ UINT startIndex, _In_ UINT numQueries, const Resource& pDestinationBuffer, _In_ UINT64 alignedDestinationBufferOffset ) const
        {
            ResolveQueryData( pQueryHeap.GetInterfacePointer<ID3D12QueryHeap>(), type, startIndex, numQueries, pDestinationBuffer.GetInterfacePointer<ID3D12Resource>(), alignedDestinationBufferOffset );
        }


        void SetPredication( _In_opt_ ID3D12Resource* pBuffer, _In_ UINT64 alignedBufferOffset, _In_ D3D12_PREDICATION_OP operation ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetPredication( pBuffer, alignedBufferOffset, operation );
        }

        void SetPredication( const Resource& pBuffer, _In_ UINT64 alignedBufferOffset, _In_ D3D12_PREDICATION_OP operation ) const
        {
            SetPredication( pBuffer.GetInterfacePointer<ID3D12Resource>(), alignedBufferOffset, operation );
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

        void ExecuteIndirect( const CommandSignature& commandSignature, _In_ UINT maxCommandCount, const Resource& argumentBuffer, _In_ UINT64 argumentBufferOffset, const Resource& countBuffer, _In_ UINT64 countBufferOffset ) const
        {
            ID3D12CommandSignature* pCommandSignature = commandSignature.GetInterfacePointer<ID3D12CommandSignature>( );
            ID3D12Resource* pArgumentBuffer = argumentBuffer.GetInterfacePointer<ID3D12Resource>( );
            ID3D12Resource* pCountBuffer = countBuffer.GetInterfacePointer<ID3D12Resource>( );
            ExecuteIndirect( pCommandSignature, maxCommandCount, pArgumentBuffer, argumentBufferOffset, pCountBuffer, countBufferOffset );
        }

        void ExecuteIndirect( const CommandSignature& commandSignature, _In_ UINT maxCommandCount, const Resource& argumentBuffer, _In_ UINT64 argumentBufferOffset ) const
        {
            ID3D12CommandSignature* pCommandSignature = commandSignature.GetInterfacePointer<ID3D12CommandSignature>( );
            ID3D12Resource* pArgumentBuffer = argumentBuffer.GetInterfacePointer<ID3D12Resource>( );
            ExecuteIndirect( pCommandSignature, maxCommandCount, pArgumentBuffer, argumentBufferOffset, nullptr, 0 );
        }


    };


    /// <summary>
    /// Encapsulates a list of graphics commands for rendering, extending the 
    /// GraphicsCommandList class to support programmable sample positions, atomic copies for implementing 
    /// late-latch techniques, and optional depth-bounds testing.
    /// </summary>
    class GraphicsCommandList1 : public GraphicsCommandList
    {
    public:
        using Base = GraphicsCommandList;

        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList1, GraphicsCommandList, ID3D12GraphicsCommandList1, ID3D12GraphicsCommandList )
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

    /// <summary>
    /// Encapsulates a list of graphics commands for rendering, extending 
    /// the GraphicsCommandList1 class to support writing immediate values 
    /// directly to a buffer.
    /// </summary>
    class GraphicsCommandList2 : public GraphicsCommandList1
    {
    public:
        using Base = GraphicsCommandList1;

        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList2, GraphicsCommandList1, ID3D12GraphicsCommandList2, ID3D12GraphicsCommandList1 )
    public:
        void WriteBufferImmediate( UINT count, _In_reads_( count ) const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* pParams, _In_reads_opt_( count ) const D3D12_WRITEBUFFERIMMEDIATE_MODE* pModes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->WriteBufferImmediate( count, pParams, pModes );
        }
    };


    /// <summary>
    /// Provides methods for submitting command lists, synchronizing 
    /// command list execution, instrumenting the command queue, and 
    /// updating resource tile mappings.
    /// </summary>
    class CommandQueue : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( CommandQueue, Pageable, ID3D12CommandQueue, ID3D12Pageable )
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

        void ExecuteCommandLists( const CommandList& commandList ) const
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

        void Signal( const Fence& fence, UINT64 value ) const
        {
            Signal( fence.GetInterfacePointer<ID3D12Fence>( ), value );
        }

        void Wait( ID3D12Fence* pFence, UINT64 value ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->Wait( pFence, value );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Wait( const Fence& fence, UINT64 value ) const
        {
            Wait( fence.GetInterfacePointer<ID3D12Fence>( ), value );
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

    /// <summary>
    /// Represents a virtual adapter; it is used to create command allocators, 
    /// command lists, command queues, fences, resources, pipeline state objects, 
    /// heaps, root signatures, samplers, and many resource views.
    /// </summary>
    class Device : public Object
    {
    public:
        using Base = Object;

        HCC_COM_STANDARD_METHODS_IMPL( Device, Object, ID3D12Device, ID3D12Object )
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
        template<typename T = CommandQueue>
            requires std::is_base_of_v< CommandQueue, T>
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

        template <typename T = CommandAllocator>
            requires std::is_base_of_v<CommandAllocator, T>
        T CreateCommandAllocator( _In_ D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateCommandAllocator( type, refiid, (void**)&ptr );
            return T( ptr, false );
        }


        void CreateGraphicsPipelineState( _In_ const D3D12_GRAPHICS_PIPELINE_STATE_DESC* graphicsPipelineStateDesc, REFIID riid, _COM_Outptr_ void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateGraphicsPipelineState( graphicsPipelineStateDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T = PipelineState>
            requires std::is_base_of_v<PipelineState, T>
        T CreateGraphicsPipelineState( _In_ const D3D12_GRAPHICS_PIPELINE_STATE_DESC* graphicsPipelineStateDesc ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateGraphicsPipelineState( graphicsPipelineStateDesc, refiid, ( void** )&ptr );
            return T( ptr, false );
        }


        void CreateComputePipelineState(_In_ const D3D12_COMPUTE_PIPELINE_STATE_DESC* computePipelineStateDesc, REFIID riid, _COM_Outptr_ void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateComputePipelineState( computePipelineStateDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T = PipelineState>
            requires std::is_base_of_v<PipelineState, T>
        T CreateComputePipelineState( _In_ const D3D12_COMPUTE_PIPELINE_STATE_DESC* computePipelineStateDesc ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateComputePipelineState( computePipelineStateDesc, refiid, ( void** )&ptr );
            return T( ptr, false );
        }


        void CreateCommandList( _In_ UINT nodeMask, _In_ D3D12_COMMAND_LIST_TYPE type, _In_ ID3D12CommandAllocator* pCommandAllocator, _In_opt_ ID3D12PipelineState* pInitialState, REFIID riid, _COM_Outptr_ void** ppCommandList ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandList( nodeMask, type, pCommandAllocator, pInitialState, riid, ppCommandList );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateCommandList( _In_ UINT nodeMask, _In_ CommandListType type, _In_ ID3D12CommandAllocator* pCommandAllocator, _In_opt_ ID3D12PipelineState* pInitialState, REFIID riid, _COM_Outptr_ void** ppCommandList ) const
        {
            CreateCommandList( nodeMask, static_cast< D3D12_COMMAND_LIST_TYPE >(type), pCommandAllocator, pInitialState, riid, ppCommandList );
        }

        template <typename T = GraphicsCommandList>
            requires std::is_base_of_v<GraphicsCommandList, T>
        T CreateCommandList( _In_ UINT nodeMask, _In_ D3D12_COMMAND_LIST_TYPE type, const CommandAllocator& commandAllocator, const PipelineState& initialState ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateCommandList( nodeMask, type, commandAllocator.GetInterfacePointer<ID3D12CommandAllocator>(), initialState.GetInterfacePointer<ID3D12PipelineState>( ), refiid, (void**)&ptr );
            return T( ptr, false );
        }

        template <typename T = GraphicsCommandList>
            requires std::is_base_of_v<GraphicsCommandList, T>
        T CreateCommandList( _In_ UINT nodeMask, _In_ CommandListType type, const CommandAllocator& commandAllocator, const PipelineState& initialState ) const
        {
            return CreateCommandList<T>( nodeMask, static_cast< D3D12_COMMAND_LIST_TYPE >( type ), commandAllocator, initialState );
        }

        template <typename T = GraphicsCommandList>
            requires std::is_base_of_v<GraphicsCommandList, T>
        T CreateCommandList( _In_ UINT nodeMask, _In_ D3D12_COMMAND_LIST_TYPE type, const CommandAllocator& commandAllocator ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateCommandList( nodeMask, type, commandAllocator.GetInterfacePointer<ID3D12CommandAllocator>( ), nullptr, refiid, (void**)&ptr );
            return T( ptr, false );
        }
        template <typename T = GraphicsCommandList>
            requires std::is_base_of_v<GraphicsCommandList, T>
        T CreateCommandList( _In_ UINT nodeMask, CommandListType type, const CommandAllocator& commandAllocator ) const
        {
            return CreateCommandList<T>( nodeMask, static_cast< D3D12_COMMAND_LIST_TYPE >( type ), commandAllocator );
        }


        void CheckFeatureSupport( D3D12_FEATURE feature, _Inout_updates_bytes_( featureSupportDataSize )  void* pFeatureSupportData, UINT featureSupportDataSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CheckFeatureSupport( feature, pFeatureSupportData, featureSupportDataSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool CheckFeatureSupport( D3D12_FEATURE_DATA_D3D12_OPTIONS& options ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CheckFeatureSupport( D3D12_FEATURE_D3D12_OPTIONS, &options, sizeof( D3D12_FEATURE_DATA_D3D12_OPTIONS ) );
            return SUCCEEDED( hr );
        }

        bool CheckFeatureSupport( D3D12_FEATURE_DATA_FEATURE_LEVELS& options ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CheckFeatureSupport( D3D12_FEATURE_FEATURE_LEVELS, &options, sizeof( D3D12_FEATURE_DATA_FEATURE_LEVELS ) );
            return SUCCEEDED( hr );
        }

        
        bool CheckFeatureSupport( D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CheckFeatureSupport( D3D12_FEATURE_FORMAT_SUPPORT, &formatSupport, sizeof( D3D12_FEATURE_DATA_FORMAT_SUPPORT ) );
            return SUCCEEDED( hr );
        }

        bool CheckFeatureSupport( D3D12_FEATURE_DATA_D3D12_OPTIONS5& options ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CheckFeatureSupport( D3D12_FEATURE_D3D12_OPTIONS5, &options, sizeof( D3D12_FEATURE_DATA_D3D12_OPTIONS5 ) );
            return SUCCEEDED( hr );
        }

        bool IsRaytracingSupported( D3D12_RAYTRACING_TIER raytracingTier = D3D12_RAYTRACING_TIER_1_0 ) const
        {
            D3D12_FEATURE_DATA_D3D12_OPTIONS5 options = {};
            if ( CheckFeatureSupport( options ) )
            {
                return options.RaytracingTier == raytracingTier;
            }
            return false;
        }



        void CreateDescriptorHeap( _In_ const D3D12_DESCRIPTOR_HEAP_DESC* descriptorHeapDesc, REFIID riid, _COM_Outptr_ void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDescriptorHeap( descriptorHeapDesc, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T = DescriptorHeap>
            requires std::is_base_of_v<DescriptorHeap,T>
        T CreateDescriptorHeap( _In_ const D3D12_DESCRIPTOR_HEAP_DESC& descriptorHeapDesc ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateDescriptorHeap( &descriptorHeapDesc, refiid, (void**)&ptr );
            return T( ptr, false );
        }


        /// <summary>
        /// Gets the size of the handle increment for the given type of descriptor heap. 
        /// This value is typically used to increment a handle into a descriptor array 
        /// by the correct amount.
        /// </summary>
        /// <param name="descriptorHeapType">
        /// The <see href="https://learn.microsoft.com/en-us/windows/desktop/api/d3d12/ne-d3d12-d3d12_descriptor_heap_type">D3D12_DESCRIPTOR_HEAP_TYPE</see>-typed 
        /// value that specifies the type of descriptor heap to get the size 
        /// of the handle increment for.
        /// </param>
        /// <returns>
        /// Returns the size of the handle increment for the given type of descriptor heap, 
        /// including any necessary padding.
        /// </returns>
        UINT GetDescriptorHandleIncrementSize( _In_ D3D12_DESCRIPTOR_HEAP_TYPE descriptorHeapType ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDescriptorHandleIncrementSize( descriptorHeapType );
        }

        void CreateRootSignature( _In_ UINT nodeMask, _In_reads_( blobLengthInBytes )  const void* blobWithRootSignature, _In_ SIZE_T blobLengthInBytes, REFIID riid, _COM_Outptr_ void** ppvRootSignature ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateRootSignature( nodeMask, blobWithRootSignature, blobLengthInBytes, riid, ppvRootSignature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T = RootSignature>
            requires std::is_base_of_v<RootSignature, T>
        T CreateRootSignature( _In_ UINT nodeMask, _In_reads_( blobLengthInBytes )  const void* blobWithRootSignature, _In_ SIZE_T blobLengthInBytes ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto refiid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateRootSignature( nodeMask, blobWithRootSignature, blobLengthInBytes, refiid, reinterpret_cast< void** >( &ptr ) );
            return T( ptr );
        }

        template <typename T = RootSignature>
            requires std::is_base_of_v<RootSignature, T>
        T CreateRootSignature( RootSignatureFlags flags ) const
        {
            Graphics::D3D12::RootSignatureDesc rootSignatureDesc;
            rootSignatureDesc.Flags = flags;
            ID3DBlob* signaturePtr = nullptr;
            ID3DBlob* errorPtr = nullptr;

            auto hr = D3D12SerializeRootSignature( rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signaturePtr, &errorPtr );
            HCC_COM_CHECK_HRESULT( hr );
            D3DBlob signature( signaturePtr );
            D3DBlob error( errorPtr );

            return CreateRootSignature( 0, signature.GetBufferPointer( ), signature.GetBufferSize( ) );
        }


        void CreateConstantBufferView( _In_opt_ const D3D12_CONSTANT_BUFFER_VIEW_DESC* pDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateConstantBufferView( pDesc, destDescriptor );
        }

        void CreateShaderResourceView(_In_opt_ ID3D12Resource* pResource, _In_opt_ const D3D12_SHADER_RESOURCE_VIEW_DESC* shaderResourceViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateShaderResourceView( pResource, shaderResourceViewDesc, destDescriptor );
        }

        void CreateShaderResourceView( const Resource& resource, _In_opt_ const D3D12_SHADER_RESOURCE_VIEW_DESC* shaderResourceViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateShaderResourceView( resource.GetInterfacePointer<ID3D12Resource>( ), shaderResourceViewDesc, destDescriptor );
        }
        void CreateShaderResourceView( const Resource& resource, _In_opt_ const D3D12_SHADER_RESOURCE_VIEW_DESC& shaderResourceViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateShaderResourceView( resource.GetInterfacePointer<ID3D12Resource>( ), &shaderResourceViewDesc, destDescriptor );
        }
        void CreateShaderResourceView( const Resource& resource, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateShaderResourceView( resource.GetInterfacePointer<ID3D12Resource>( ), nullptr, destDescriptor );
        }



        void CreateUnorderedAccessView(_In_opt_ ID3D12Resource* resource, _In_opt_ ID3D12Resource* counterResource, _In_opt_ const D3D12_UNORDERED_ACCESS_VIEW_DESC* unorderedAccessViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateUnorderedAccessView( resource, counterResource, unorderedAccessViewDesc, destDescriptor );
        }

        void CreateUnorderedAccessView( const Resource& resource, const Resource& counterResource, _In_opt_ const D3D12_UNORDERED_ACCESS_VIEW_DESC* unorderedAccessViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateUnorderedAccessView( resource.GetInterfacePointer<ID3D12Resource>( ), counterResource.GetInterfacePointer<ID3D12Resource>( ), unorderedAccessViewDesc, destDescriptor );
        }
        void CreateUnorderedAccessView( const Resource& resource, _In_opt_ const D3D12_UNORDERED_ACCESS_VIEW_DESC* unorderedAccessViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateUnorderedAccessView( resource.GetInterfacePointer<ID3D12Resource>( ), nullptr, unorderedAccessViewDesc, destDescriptor );
        }
        void CreateUnorderedAccessView( const Resource& resource, const Resource& counterResource, _In_opt_ const D3D12_UNORDERED_ACCESS_VIEW_DESC& unorderedAccessViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateUnorderedAccessView( resource.GetInterfacePointer<ID3D12Resource>( ), counterResource.GetInterfacePointer<ID3D12Resource>( ), &unorderedAccessViewDesc, destDescriptor );
        }
        void CreateUnorderedAccessView( const Resource& resource, _In_opt_ const D3D12_UNORDERED_ACCESS_VIEW_DESC& unorderedAccessViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateUnorderedAccessView( resource.GetInterfacePointer<ID3D12Resource>( ), nullptr, &unorderedAccessViewDesc, destDescriptor );
        }
        void CreateUnorderedAccessView( const Resource& resource, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateUnorderedAccessView( resource.GetInterfacePointer<ID3D12Resource>( ), nullptr, nullptr, destDescriptor );
        }



        void CreateRenderTargetView(_In_opt_ ID3D12Resource* resource, _In_opt_ const D3D12_RENDER_TARGET_VIEW_DESC* renderTargetViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateRenderTargetView( resource, renderTargetViewDesc, destDescriptor );
        }
        void CreateRenderTargetView( const Resource& resource, _In_opt_ const D3D12_RENDER_TARGET_VIEW_DESC* renderTargetViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateRenderTargetView( resource.GetInterfacePointer<ID3D12Resource>(), renderTargetViewDesc, destDescriptor );
        }
        void CreateRenderTargetView( const Resource& resource, const D3D12_RENDER_TARGET_VIEW_DESC& renderTargetViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateRenderTargetView( resource.GetInterfacePointer<ID3D12Resource>(), &renderTargetViewDesc, destDescriptor );
        }
        void CreateRenderTargetView( const Resource& resource, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateRenderTargetView( resource.GetInterfacePointer<ID3D12Resource>( ), nullptr, destDescriptor );
        }


        void CreateDepthStencilView( _In_opt_ ID3D12Resource* resource, _In_opt_ const D3D12_DEPTH_STENCIL_VIEW_DESC* depthStencilViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateDepthStencilView( resource, depthStencilViewDesc, destDescriptor );
        }

        void CreateDepthStencilView( const Resource& resource, _In_opt_ const D3D12_DEPTH_STENCIL_VIEW_DESC* depthStencilViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateDepthStencilView( resource.GetInterfacePointer<ID3D12Resource>( ), depthStencilViewDesc, destDescriptor );
        }
        void CreateDepthStencilView( const Resource& resource, const D3D12_DEPTH_STENCIL_VIEW_DESC& depthStencilViewDesc, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateDepthStencilView( resource.GetInterfacePointer<ID3D12Resource>( ), &depthStencilViewDesc, destDescriptor );
        }
        void CreateDepthStencilView( const Resource& resource, _In_ D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            CreateDepthStencilView( resource.GetInterfacePointer<ID3D12Resource>( ), nullptr, destDescriptor );
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

        void CreateCommittedResource( _In_ const D3D12_HEAP_PROPERTIES* heapProperties, D3D12_HEAP_FLAGS heapFlags, _In_ const D3D12_RESOURCE_DESC* resourceDesc, D3D12_RESOURCE_STATES initialResourceState, _In_opt_ const D3D12_CLEAR_VALUE* optimizedClearValue, REFIID riidResource, _COM_Outptr_opt_  void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommittedResource( heapProperties, heapFlags, resourceDesc, initialResourceState, optimizedClearValue, riidResource, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        Resource CreateCommittedResource( _In_ const D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS heapFlags, _In_ const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES initialResourceState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue = nullptr ) const
        {
            ID3D12Resource* itf = nullptr;
            CreateCommittedResource( pHeapProperties, heapFlags, pDesc, initialResourceState, pOptimizedClearValue, __uuidof( ID3D12Resource ), reinterpret_cast<void**>( &itf ) );
            return Resource(itf);
        }

        Resource CreateCommittedResource( _In_ const D3D12_HEAP_PROPERTIES* pHeapProperties, HeapFlags heapFlags, _In_ const D3D12_RESOURCE_DESC* pDesc, ResourceStates initialResourceState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue = nullptr ) const
        {
            return CreateCommittedResource( pHeapProperties, static_cast< D3D12_HEAP_FLAGS >( heapFlags ), pDesc, static_cast< D3D12_RESOURCE_STATES>( initialResourceState ), pOptimizedClearValue );
        }

        Resource CreateCommittedResource( _In_ const HeapProperties& heapProperties, HeapFlags heapFlags, _In_ const ResourceDesc& desc, ResourceStates initialResourceState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue = nullptr ) const
        {
            return CreateCommittedResource( reinterpret_cast< const D3D12_HEAP_PROPERTIES* >( &heapProperties ), static_cast< D3D12_HEAP_FLAGS >( heapFlags ), reinterpret_cast< const D3D12_RESOURCE_DESC*>(&desc), static_cast< D3D12_RESOURCE_STATES >( initialResourceState ), pOptimizedClearValue );
        }



        void CreateHeap( _In_ const D3D12_HEAP_DESC* pDesc, REFIID riid, _COM_Outptr_opt_  void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateHeap( pDesc, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T = Heap>
            requires std::is_base_of_v< Heap, T>
        T CreateHeap( _In_ const D3D12_HEAP_DESC& heapDesc )
        {
            using HeapInterfaceType = typename T::InterfaceType;
            HeapInterfaceType* itf = nullptr;
            CreateHeap( &heapDesc, __uuidof( HeapInterfaceType ), reinterpret_cast< void** >( &itf ) );
            return T( itf );
        }



        void CreatePlacedResource( _In_ ID3D12Heap* pHeap, UINT64 heapOffset, _In_ const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES initialState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue, REFIID riid, _COM_Outptr_opt_  void** ppvResource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreatePlacedResource( pHeap, heapOffset, pDesc, initialState, pOptimizedClearValue, riid, ppvResource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T = Resource>
            requires std::is_base_of_v< Resource, T>
        T CreatePlacedResource( _In_ ID3D12Heap* pHeap, UINT64 heapOffset, _In_ const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES initialState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue ) const
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto riid = __uuidof( ItfT );
            ItfT* itf = nullptr;
            CreatePlacedResource( pHeap, heapOffset, pDesc, initialState, pOptimizedClearValue, riid, reinterpret_cast< void** >( &itf ) );
            return T( itf );
        }

        template<typename T = Resource>
            requires std::is_base_of_v< Resource, T>
        T CreatePlacedResource( const Heap& heap, UINT64 heapOffset, _In_ const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES initialState, _In_opt_ const D3D12_CLEAR_VALUE* pOptimizedClearValue ) const
        {
            return CreatePlacedResource<T>( heap.GetInterfacePointer<ID3D12Heap>(), heapOffset, pDesc, initialState, pOptimizedClearValue );
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

        template<typename T = Fence>
            requires std::is_base_of_v<Fence,T>
        T CreateFence( UINT64 initialValue = 0, D3D12_FENCE_FLAGS flags = D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE ) const
        {
            using IntfT = typename T::InterfaceType;
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

        void GetCopyableFootprints( _In_ const ResourceDesc* pResourceDesc, _In_range_( 0, D3D12_REQ_SUBRESOURCES ) UINT FirstSubresource, _In_range_( 0, D3D12_REQ_SUBRESOURCES - FirstSubresource ) UINT NumSubresources, UINT64 BaseOffset, _Out_writes_opt_( NumSubresources ) PlacedSubresourceFootprint* pLayouts, _Out_writes_opt_( NumSubresources ) UINT* pNumRows, _Out_writes_opt_( NumSubresources ) UINT64* pRowSizeInBytes, _Out_opt_  UINT64* pTotalBytes ) const
        {
            GetCopyableFootprints( reinterpret_cast< const D3D12_RESOURCE_DESC* >( pResourceDesc ), FirstSubresource, NumSubresources, BaseOffset, reinterpret_cast< D3D12_PLACED_SUBRESOURCE_FOOTPRINT* >( pLayouts ), pNumRows, pRowSizeInBytes, pTotalBytes );
        }

        void CreateQueryHeap( _In_ const D3D12_QUERY_HEAP_DESC* pDesc, REFIID riid, _COM_Outptr_opt_  void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateQueryHeap( pDesc, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T = QueryHeap>
            requires std::is_base_of_v<QueryHeap,T>
        T CreateQueryHeap( _In_ const D3D12_QUERY_HEAP_DESC* queryHeapDesc )
        {
            using ItfT = typename T::InterfaceType;
            constexpr auto riid = __uuidof( ItfT );
            ItfT* ptr = nullptr;
            CreateQueryHeap( queryHeapDesc, riid, reinterpret_cast< void** >( &ptr ) );
            return T( ptr );
        }

        template<typename T = QueryHeap>
            requires std::is_base_of_v<QueryHeap, T>
        T CreateQueryHeap( const D3D12_QUERY_HEAP_DESC& queryHeapDesc )
        {
            return CreateQueryHeap<T>( &queryHeapDesc );
        }



        void SetStablePowerState( BOOL enable ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetStablePowerState( enable );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateCommandSignature( _In_ const D3D12_COMMAND_SIGNATURE_DESC* pDesc, _In_opt_ ID3D12RootSignature* pRootSignature, REFIID riid, _COM_Outptr_opt_  void** ppvCommandSignature ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandSignature( pDesc, pRootSignature, riid, ppvCommandSignature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T = CommandSignature>
            requires std::is_base_of_v<CommandSignature,T>
        T CreateCommandSignature( _In_ const D3D12_COMMAND_SIGNATURE_DESC* pDesc, _In_opt_ ID3D12RootSignature* pRootSignature = nullptr )
        {
            using ItfT = typename T::InterfaceType;
            ItfT* ptr = nullptr;
            constexpr auto riid = __uuidof( ItfT );
            CreateCommandSignature( pDesc, pRootSignature, riid, reinterpret_cast<void**>( &ptr ) );
            return T( ptr );
        }

        template<typename T = CommandSignature>
            requires std::is_base_of_v<CommandSignature, T>
        T CreateCommandSignature( _In_ const D3D12_COMMAND_SIGNATURE_DESC* pDesc, const RootSignature& rootSignature  )
        {
            return CreateCommandSignature<T>( pDesc, rootSignature.GetInterfacePointer<ID3D12RootSignature>() );
        }
        template<typename T = CommandSignature>
            requires std::is_base_of_v<CommandSignature, T>
        T CreateCommandSignature( _In_ const D3D12_COMMAND_SIGNATURE_DESC& pDesc, const RootSignature& rootSignature )
        {
            return CreateCommandSignature<T>( pDesc, rootSignature.GetInterfacePointer<ID3D12RootSignature>( ) );
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

    /// <summary>
    /// Manages a pipeline library, in particular loading and retrieving individual PSOs.
    /// </summary>
    class PipelineLibrary : public DeviceChild
    {
    public:
        using Base = DeviceChild;

        HCC_COM_STANDARD_METHODS_IMPL( PipelineLibrary, DeviceChild, ID3D12PipelineLibrary, ID3D12DeviceChild )
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

    /// <summary>
    /// Manages a pipeline library. This class extends the PipelineLibrary 
    /// class to load PSOs from a pipeline state stream description.
    /// </summary>
    class PipelineLibrary1 : public PipelineLibrary
    {
    public:
        using Base = PipelineLibrary;

        HCC_COM_STANDARD_METHODS_IMPL( PipelineLibrary1, PipelineLibrary, ID3D12PipelineLibrary1, ID3D12PipelineLibrary )
    public:
        void LoadPipeline( _In_  LPCWSTR pName, _In_  const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc, REFIID riid, _COM_Outptr_  void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->LoadPipeline( pName, pDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents a virtual adapter, and expands on the range of 
    /// methods provided by the Device class.
    /// </summary>
    class Device1 : public Device
    {
    public:
        using Base = Device;

        HCC_COM_STANDARD_METHODS_IMPL( Device1, Device, ID3D12Device1, ID3D12Device )
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

    /// <summary>
    /// Represents a virtual adapter. This class extends the Device1 class 
    /// to create pipeline state objects from pipeline state stream descriptions.
    /// </summary>
    class Device2 : public Device1
    {
    public:
        using Base = Device1;

        HCC_COM_STANDARD_METHODS_IMPL( Device2, Device1, ID3D12Device2, ID3D12Device1 )
    public:
        void CreatePipelineState( const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc, REFIID riid, _COM_Outptr_  void** ppPipelineState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreatePipelineState( pDesc, riid, ppPipelineState );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents a virtual adapter. This class extends the Device2 class 
    /// to support the creation of special-purpose diagnostic heaps in system 
    /// memory that persist even in the event of a GPU-fault or device-removed scenario.
    /// </summary>
    class Device3 : public Device2
    {
    public:
        using Base = Device2;

        HCC_COM_STANDARD_METHODS_IMPL( Device3, Device2, ID3D12Device3, ID3D12Device2 )
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

    /// <summary>
    /// Offers base functionality that allows for a consistent way to 
    /// monitor the validity of a session across the different types 
    /// of sessions. The only type of session currently available is 
    /// of type ProtectedResourceSession.
    /// </summary>
    class ProtectedSession : public DeviceChild
    {
    public:
        using Base = DeviceChild;

        HCC_COM_STANDARD_METHODS_IMPL( ProtectedSession, DeviceChild, ID3D12ProtectedSession, ID3D12DeviceChild )
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

    /// <summary>
    /// Monitors the validity of a protected resource session. 
    /// </summary>
    class ProtectedResourceSession : public ProtectedSession
    {
    public:
        using Base = ProtectedSession;

        HCC_COM_STANDARD_METHODS_IMPL( ProtectedResourceSession, ProtectedSession, ID3D12ProtectedResourceSession, ID3D12ProtectedSession )
    public:
        D3D12_PROTECTED_RESOURCE_SESSION_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }
    };

    /// <summary>
    /// Represents a virtual adapter.
    /// </summary>
    class Device4 : public Device3
    {
    public:
        using Base = Device3;

        HCC_COM_STANDARD_METHODS_IMPL( Device4, Device3, ID3D12Device4, ID3D12Device3 )
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

    /// <summary>
    /// Represents an application-defined callback used for being notified of lifetime changes of an object.
    /// </summary>
    class LifetimeOwner : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( LifetimeOwner, Unknown, ID3D12LifetimeOwner, IUnknown )
    public:
        void LifetimeStateUpdated( D3D12_LIFETIME_STATE newState ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->LifetimeStateUpdated( newState );
        }
    };

    class SwapChainAssistant : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( SwapChainAssistant, Unknown, ID3D12SwapChainAssistant, IUnknown )
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

    /// <summary>
    /// Represents facilities for controlling the lifetime a lifetime-tracked object.
    /// </summary>
    class LifetimeTracker : public DeviceChild
    {
    public:
        using Base = DeviceChild;

        HCC_COM_STANDARD_METHODS_IMPL( LifetimeTracker, DeviceChild, ID3D12LifetimeTracker, ID3D12DeviceChild )
    public:
        void DestroyOwnedObject( _In_ ID3D12DeviceChild* pObject ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->DestroyOwnedObject( pObject );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Represents a variable amount of configuration state, including shaders, 
    /// that an application manages as a single unit and which is given to a 
    /// driver atomically to process, such as compile or optimize. 
    /// Create a state object by calling Device5::CreateStateObject.
    /// </summary>
    class StateObject : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( StateObject, Pageable, ID3D12StateObject, ID3D12Pageable )
    public:

    };

    /// <summary>
    /// Provides methods for getting and setting the properties of an StateObject. 
    /// To retrieve an instance of this type, call StateObject::As&lt;StateObjectProperties&gt;().
    /// </summary>
    class StateObjectProperties : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( StateObjectProperties, Unknown, ID3D12StateObjectProperties, IUnknown )
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

    /// <summary>
    /// Provides methods for getting and setting the properties of an StateObject. 
    /// To retrieve an instance of this type, call StateObject::As&lt;StateObjectProperties1&gt;().
    /// </summary>
    class StateObjectProperties1 : public StateObjectProperties
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( StateObjectProperties1, StateObjectProperties, ID3D12StateObjectProperties1, ID3D12StateObjectProperties )
    public:
        D3D12_PROGRAM_IDENTIFIER GetProgramIdentifier( LPCWSTR programName ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetProgramIdentifier( programName );
        }
        template<WideStringLike T>
        D3D12_PROGRAM_IDENTIFIER GetProgramIdentifier( const T& programName ) const
        {
            return GetProgramIdentifier( programName.c_str( ) );
        }
    };

    /// <summary>
    /// Wraps ID3D12WorkGraphProperties, an interface exported by ID3D12StateObject/StateObject, 
    /// focused on reflecting information about work graphs that might be relevant to the API user.
    /// </summary>
    class WorkGraphProperties : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( WorkGraphProperties, Unknown, ID3D12WorkGraphProperties, IUnknown )
    public:
        UINT GetNumWorkGraphs( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumWorkGraphs( );
        }

        LPCWSTR GetProgramName( UINT WorkGraphIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetProgramName( WorkGraphIndex );
        }

        UINT GetWorkGraphIndex( LPCWSTR programName ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetWorkGraphIndex( programName );
        }

        UINT GetNumNodes( UINT WorkGraphIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumNodes( WorkGraphIndex );
        }

#if defined(_MSC_VER) || !defined(_WIN32)
        D3D12_NODE_ID GetNodeID( UINT workGraphIndex, UINT nodeIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNodeID( workGraphIndex, nodeIndex );
        }
#else
        D3D12_NODE_ID* GetNodeID( D3D12_NODE_ID* retVal, UINT workGraphIndex, UINT nodeIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNodeID( retVal, workGraphIndex, nodeIndex );
        }
        D3D12_NODE_ID GetNodeID( UINT workGraphIndex, UINT nodeIndex ) const
        {
            D3D12_NODE_ID result{};
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetNodeID( &result, workGraphIndex, nodeIndex );
            return result;
        }
#endif

        UINT GetNodeIndex( UINT workGraphIndex, const D3D12_NODE_ID& nodeID ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNodeIndex( workGraphIndex, nodeID );
        }

        UINT GetNodeLocalRootArgumentsTableIndex( UINT workGraphIndex, UINT nodeIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNodeLocalRootArgumentsTableIndex( workGraphIndex, nodeIndex );
        }

        UINT GetNumEntrypoints( UINT workGraphIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetNumEntrypoints( workGraphIndex );
        }

#if defined(_MSC_VER) || !defined(_WIN32)
        D3D12_NODE_ID GetEntrypointID( UINT workGraphIndex, UINT entrypointIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetEntrypointID( workGraphIndex, entrypointIndex );
        }
#else
        D3D12_NODE_ID* GetEntrypointID( D3D12_NODE_ID* retVal, UINT workGraphIndex, UINT entrypointIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetEntrypointID( retVal, workGraphIndex, entrypointIndex );
        }
        D3D12_NODE_ID GetEntrypointID( UINT workGraphIndex, UINT entrypointIndex ) const
        {
            D3D12_NODE_ID retVal{}
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetEntrypointID( &retVal, workGraphIndex, entrypointIndex );
            return retVal;
        }
#endif

        UINT GetEntrypointIndex( UINT workGraphIndex, const D3D12_NODE_ID& nodeID ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetEntrypointIndex( workGraphIndex, nodeID );
        }

        UINT GetEntrypointRecordSizeInBytes( UINT workGraphIndex, UINT entrypointIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetEntrypointRecordSizeInBytes( workGraphIndex, entrypointIndex );
        }

        void GetWorkGraphMemoryRequirements( UINT workGraphIndex, _Out_  D3D12_WORK_GRAPH_MEMORY_REQUIREMENTS* workGraphMemoryRequirements ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetWorkGraphMemoryRequirements( workGraphIndex, workGraphMemoryRequirements );
        }
    };

    /// <summary>
    /// Represents a virtual adapter.
    /// </summary>
    class Device5 : public Device4
    {
    public:
        using Base = Device4;

        HCC_COM_STANDARD_METHODS_IMPL( Device5, Device4, ID3D12Device5, ID3D12Device4 )
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

    /// <summary>
    /// This class controls Device Removed Extended Data (DRED) settings.
    /// </summary>
    class DeviceRemovedExtendedDataSettings : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( DeviceRemovedExtendedDataSettings, Unknown, ID3D12DeviceRemovedExtendedDataSettings, IUnknown )
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

    class DeviceRemovedExtendedDataSettings1 : public DeviceRemovedExtendedDataSettings
    {
    public:
        using Base = DeviceRemovedExtendedDataSettings;

        HCC_COM_STANDARD_METHODS_IMPL( DeviceRemovedExtendedDataSettings1, DeviceRemovedExtendedDataSettings, ID3D12DeviceRemovedExtendedDataSettings1, ID3D12DeviceRemovedExtendedDataSettings )
    public:
        void SetBreadcrumbContextEnablement( D3D12_DRED_ENABLEMENT Enablement ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetBreadcrumbContextEnablement( Enablement );
        }
    };

    class DeviceRemovedExtendedDataSettings2 : public DeviceRemovedExtendedDataSettings1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DeviceRemovedExtendedDataSettings2, DeviceRemovedExtendedDataSettings1, ID3D12DeviceRemovedExtendedDataSettings2, ID3D12DeviceRemovedExtendedDataSettings1 )
    public:
        void UseMarkersOnlyAutoBreadcrumbs( BOOL markersOnly = TRUE ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->UseMarkersOnlyAutoBreadcrumbs( markersOnly );
        }
    };


    /// <summary>
    /// Provides runtime access to Device Removed Extended Data (DRED) data.
    /// </summary>
    class DeviceRemovedExtendedData : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( DeviceRemovedExtendedData, Unknown, ID3D12DeviceRemovedExtendedData, IUnknown )
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

    class DeviceRemovedExtendedData1 : public DeviceRemovedExtendedData
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DeviceRemovedExtendedData1, DeviceRemovedExtendedData, ID3D12DeviceRemovedExtendedData1, ID3D12DeviceRemovedExtendedData )
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


    class DeviceRemovedExtendedData2 : public DeviceRemovedExtendedData1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DeviceRemovedExtendedData2, DeviceRemovedExtendedData1, ID3D12DeviceRemovedExtendedData2, ID3D12DeviceRemovedExtendedData1 )
    public:
        void GetPageFaultAllocationOutput2( _Out_  D3D12_DRED_PAGE_FAULT_OUTPUT2* pOutput ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetPageFaultAllocationOutput2( pOutput );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D3D12_DRED_DEVICE_STATE GetDeviceState( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDeviceState( );
        }
    };

    /// <summary>
    /// Represents a virtual adapter.
    /// </summary>
    class Device6 : public Device5
    {
    public:
        using Base = Device5;

        HCC_COM_STANDARD_METHODS_IMPL( Device6, Device5, ID3D12Device6, ID3D12Device5 )
    public:
        void SetBackgroundProcessingMode( D3D12_BACKGROUND_PROCESSING_MODE Mode, D3D12_MEASUREMENTS_ACTION MeasurementsAction, _In_opt_  HANDLE hEventToSignalUponCompletion, _Out_opt_  BOOL* pbFurtherMeasurementsDesired ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetBackgroundProcessingMode( Mode, MeasurementsAction, _In_opt_  hEventToSignalUponCompletion, pbFurtherMeasurementsDesired );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Monitors the validity of a protected resource session.
    /// </summary>
    class ProtectedResourceSession1 : public ProtectedResourceSession
    {
    public:
        using Base = ProtectedResourceSession;

        HCC_COM_STANDARD_METHODS_IMPL( ProtectedResourceSession1, ProtectedResourceSession, ID3D12ProtectedResourceSession1, ID3D12ProtectedResourceSession )
    public:
        D3D12_PROTECTED_RESOURCE_SESSION_DESC1 GetDesc1( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc1( );
        }
    };

    /// <summary>
    /// Represents a virtual adapter
    /// </summary>
    class Device7 : public Device6
    {
    public:
        using Base = Device6;

        HCC_COM_STANDARD_METHODS_IMPL( Device7, Device6, ID3D12Device7, ID3D12Device6 )
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

    /// <summary>
    /// Represents a virtual adapter.
    /// </summary>
    class Device8 : public Device7
    {
    public:
        using Base = Device7;

        HCC_COM_STANDARD_METHODS_IMPL( Device8, Device7, ID3D12Device8, ID3D12Device7 )
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

    class Resource1 : public Resource
    {
    public:
        using Base = Resource;

        HCC_COM_STANDARD_METHODS_IMPL( Resource1, Resource, ID3D12Resource1, ID3D12Resource )
    public:
        void GetProtectedResourceSession( REFIID riid, _COM_Outptr_opt_  void** ppProtectedSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetProtectedResourceSession( riid, ppProtectedSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class Resource2 : public Resource1
    {
    public:
        using Base = Resource1;

        HCC_COM_STANDARD_METHODS_IMPL( Resource2, Resource1, ID3D12Resource2, ID3D12Resource1 )
    public:
        D3D12_RESOURCE_DESC1 GetDesc1( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc1( );
        }
    };

    class Heap1 : public Heap
    {
    public:
        using Base = Heap;

        HCC_COM_STANDARD_METHODS_IMPL( Heap1, Heap, ID3D12Heap1, ID3D12Heap )
    public:
        void GetProtectedResourceSession( REFIID riid, _COM_Outptr_opt_  void** ppProtectedSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetProtectedResourceSession( riid, ppProtectedSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// Encapsulates a list of graphics commands for rendering.
    /// </summary>
    class GraphicsCommandList3 : public GraphicsCommandList2
    {
    public:
        using Base = GraphicsCommandList2;

        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList3, GraphicsCommandList2, ID3D12GraphicsCommandList3, ID3D12GraphicsCommandList2 )
    public:
        void SetProtectedResourceSession( _In_opt_  ID3D12ProtectedResourceSession* pProtectedResourceSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetProtectedResourceSession( pProtectedResourceSession );
        }
    };

    /// <summary>
    /// <para>
    /// Represents a meta command. A meta command is a Direct3D 12 object representing 
    /// an algorithm that is accelerated by independent hardware vendors (IHVs). It's 
    /// an opaque reference to a command generator that is implemented by the driver.
    /// </para>
    /// <para>
    /// The lifetime of a meta command is tied to the lifetime of the command list that 
    /// references it. So, you should only free a meta command if no command list referencing 
    /// it is currently executing on the GPU.
    /// </para>
    /// <para>
    /// A meta command can encapsulate a set of pipeline state objects (PSOs), bindings, 
    /// intermediate resource states, and Draw/Dispatch calls. You can think of the signature 
    /// of a meta command as being similar to a C-style function, with multiple in/out 
    /// parameters, and no return value.
    /// </para>
    /// </summary>
    class MetaCommand : public Pageable
    {
    public:
        using Base = Pageable;

        HCC_COM_STANDARD_METHODS_IMPL( MetaCommand, Pageable, ID3D12MetaCommand, ID3D12Pageable )
    public:
        UINT64 GetRequiredParameterResourceSize(_In_  D3D12_META_COMMAND_PARAMETER_STAGE Stage, _In_  UINT ParameterIndex ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetRequiredParameterResourceSize( Stage, ParameterIndex );
        }
    };


    /// <summary>
    /// Encapsulates a list of graphics commands for rendering, extending the 
    /// GraphicsCommandList3 class to support ray tracing and render passes.
    /// </summary>
    class GraphicsCommandList4 : public GraphicsCommandList3
    {
    public:
        using Base = GraphicsCommandList3;

        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList4, GraphicsCommandList3, ID3D12GraphicsCommandList4, ID3D12GraphicsCommandList3 )
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

    class ShaderCacheSession : public DeviceChild
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( ShaderCacheSession, DeviceChild, ID3D12ShaderCacheSession, ID3D12DeviceChild )
    public:
        /// <summary>
        /// <para>
        /// Looks up an entry in the cache whose key exactly matches the provided key.
        /// </para>
        /// </summary>
        /// <param name="key">
        /// The key of the entry to look up.
        /// </param>
        /// <param name="keySize">
        /// The size of the key, in bytes.
        /// </param>
        /// <param name="value">
        /// A pointer to a memory block that receives the cached entry.
        /// </param>
        /// <param name="valueSize">
        /// A pointer to a UINT that receives the size of the cached entry, in bytes.
        /// </param>
        /// <returns>
        /// <c>true</c> if the requested value was found, otherwise <c>false</c>.
        /// </returns>
        bool FindValue( _In_reads_bytes_( leySize )  const void* key, UINT keySize, _Out_writes_bytes_( *valueSize )  void* value, _Inout_  UINT* valueSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->FindValue( key, keySize, value, valueSize );
            if ( hr != DXGI_ERROR_NOT_FOUND )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            return hr != DXGI_ERROR_NOT_FOUND;
        }

        Binary FindValue( _In_reads_bytes_( leySize )  const void* key, UINT keySize )
        {
            InterfaceType* pInterface = GetInterface( );
            UINT valueSize = 0;
            auto hr = pInterface->FindValue( key, keySize, nullptr, &valueSize );
            if ( hr != DXGI_ERROR_NOT_FOUND )
            {
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            if ( hr != DXGI_ERROR_NOT_FOUND )
            {
                Binary result;
                result.resize( valueSize );
                hr = pInterface->FindValue( key, keySize, result.data(), &valueSize );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
            return Binary( );
        }

        template<SimpleSpanLike T>
        Binary FindValue( const T& key )
        {
            return FindValue( key.data( ), static_cast< UINT >( key.size( ) * sizeof( typename T::value_type ) ) );
        }



        /// <summary>
        /// Adds an entry to the cache.
        /// </summary>
        /// <param name="key">
        /// The key of the entry to add.
        /// </param>
        /// <param name="keySize">
        /// The size of the key, in bytes.
        /// </param>
        /// <param name="value">
        /// A pointer to a memory block containing the entry to add.
        /// </param>
        /// <param name="valueSize">
        /// The size of the entry to add, in bytes.
        /// </param>
        /// <returns></returns>
        HRESULT StoreValue( _In_reads_bytes_( keySize )  const void* key, UINT keySize, _In_reads_bytes_( valueSize )  const void* value, UINT valueSize ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->StoreValue( key, keySize, value, valueSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );

        }

        void SetDeleteOnDestroy( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetDeleteOnDestroy( );
        }

#if defined(_MSC_VER) || !defined(_WIN32)
        D3D12_SHADER_CACHE_SESSION_DESC GetDesc( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }
#else
        D3D12_SHADER_CACHE_SESSION_DESC* GetDesc( D3D12_SHADER_CACHE_SESSION_DESC* retVal ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( retVal );
        }

        D3D12_SHADER_CACHE_SESSION_DESC GetDesc( * retVal ) const
        {
            D3D12_SHADER_CACHE_SESSION_DESC retVal{};
            InterfaceType* pInterface = GetInterface( );
            pInterface->GetDesc( &retVal );
            return retVal;
        }
#endif
    };

    class Device9 : public Device8
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Device9, Device8, ID3D12Device9, ID3D12Device8 )
    public:

        void CreateShaderCacheSession( _In_  const D3D12_SHADER_CACHE_SESSION_DESC* pDesc, REFIID riid, _COM_Outptr_opt_  void** ppvSession ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateShaderCacheSession( pDesc, riid, ppvSession );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T= ShaderCacheSession>
            requires std::is_base_of_v< ShaderCacheSession,T>
        T CreateShaderCacheSession( _In_  const D3D12_SHADER_CACHE_SESSION_DESC* pDesc )
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateShaderCacheSession( pDesc, __uuidof( ItfType ), ( void** )&itf );
            return T( itf );
        }


        void ShaderCacheControl( D3D12_SHADER_CACHE_KIND_FLAGS kinds, D3D12_SHADER_CACHE_CONTROL_FLAGS control ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ShaderCacheControl( kinds, control );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void ShaderCacheControl( ShaderCacheKindFlags kinds, ShaderCacheControlFlags control ) const
        {
            ShaderCacheControl( static_cast< D3D12_SHADER_CACHE_KIND_FLAGS >( kinds ), static_cast< D3D12_SHADER_CACHE_CONTROL_FLAGS >( control ) );
        }


        void CreateCommandQueue1( _In_  const D3D12_COMMAND_QUEUE_DESC* pDesc, REFIID CreatorID, REFIID riid, _COM_Outptr_  void** ppCommandQueue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommandQueue1( pDesc, CreatorID, riid, ppCommandQueue );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
            requires std::is_base_of_v<CommandQueue,T>
        T CreateCommandQueue1( _In_  const D3D12_COMMAND_QUEUE_DESC* pDesc, REFIID CreatorID ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateCommandQueue1( pDesc, CreatorID, __uuidof( ItfType ), ( void** )&itf );
            return T( itf );
        }
    };

    class Device10 : public Device9
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Device10, Device9, ID3D12Device10, ID3D12Device9 )
    public:
        /// <summary>
        /// Creates a committed resource with an initial layout rather than an initial state.
        /// </summary>
        /// <param name="heapProperties">
        /// A pointer to a D3D12_HEAP_PROPERTIES structure that provides properties for the resource's heap.
        /// </param>
        /// <param name="heapFlags">
        /// Heap options, as a bitwise-OR'd combination of D3D12_HEAP_FLAGS, or HeapFlags, enumeration constants.
        /// </param>
        /// <param name="pDesc">
        /// A pointer to a D3D12_RESOURCE_DESC1 structure that describes the resource, including a mip region.
        /// </param>
        /// <param name="initialLayout">
        /// The initial layout of the texture resource; 
        /// D3D12_BARRIER_LAYOUT::D3D12_BARRIER_LAYOUT_UNDEFINED/BarrierLayout::Undefined for buffers.
        /// </param>
        /// <param name="optimizedClearValue">
        /// Specifies a D3D12_CLEAR_VALUE structure that describes the default value for a clear color.
        /// </param>
        /// <param name="protectedSession">
        /// An optional pointer to an object that represents a session for content protection.
        /// </param>
        /// <param name="numCastableFormats">
        /// The number of elements in castableFormats.
        /// </param>
        /// <param name="castableFormats">
        /// A contiguous array of DXGI_FORMAT/DXGI::Format structures that this resource can be cast to.
        /// </param>
        /// <param name="riidResource">
        /// A reference to the globally unique identifier (GUID) of the resource interface to return in resource.
        /// </param>
        /// <param name="resource">
        /// An optional pointer to a memory block that receives the requested interface pointer to the created resource object.
        /// </param>
        void CreateCommittedResource3(
            _In_  const D3D12_HEAP_PROPERTIES* heapProperties,
            D3D12_HEAP_FLAGS heapFlags,
            _In_  const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            _In_opt_  ID3D12ProtectedResourceSession* protectedSession,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI_FORMAT* castableFormats,
            REFIID riidResource,
            _COM_Outptr_opt_  void** resource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateCommittedResource3( heapProperties, heapFlags, pDesc, initialLayout, optimizedClearValue, protectedSession, numCastableFormats, castableFormats, riidResource, resource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateCommittedResource3(
            _In_  const D3D12_HEAP_PROPERTIES* heapProperties,
            HeapFlags heapFlags,
            _In_  const D3D12_RESOURCE_DESC1* pDesc,
            BarrierLayout initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            _In_opt_  ID3D12ProtectedResourceSession* protectedSession,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI::Format* castableFormats,
            REFIID riidResource,
            _COM_Outptr_opt_  void** resource ) const
        {
            CreateCommittedResource3( heapProperties, static_cast< D3D12_HEAP_FLAGS >(heapFlags), pDesc, static_cast< D3D12_BARRIER_LAYOUT >(initialLayout), optimizedClearValue, protectedSession, numCastableFormats, reinterpret_cast< const DXGI_FORMAT* >( castableFormats ), riidResource, resource );
        }


        template<typename T>
            requires std::is_base_of_v<Resource, T>
        T CreateCommittedResource3( 
            _In_  const D3D12_HEAP_PROPERTIES* heapProperties,
            D3D12_HEAP_FLAGS heapFlags,
            _In_  const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            _In_opt_  ID3D12ProtectedResourceSession* protectedSession,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI_FORMAT* castableFormats ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateCommittedResource3( heapProperties, static_cast< D3D12_HEAP_FLAGS >( heapFlags ), pDesc, static_cast< D3D12_BARRIER_LAYOUT >( initialLayout ), optimizedClearValue, protectedSession, numCastableFormats, reinterpret_cast< const DXGI_FORMAT* >( castableFormats ), __uuidof( ItfType ), ( void** )&itf );
            return T( itf );
        }

        template<typename T>
            requires std::is_base_of_v<Resource, T>
        T CreateCommittedResource3( 
            _In_  const D3D12_HEAP_PROPERTIES* heapProperties,
            HeapFlags heapFlags,
            _In_  const D3D12_RESOURCE_DESC1* pDesc,
            BarrierLayout initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            _In_opt_  ID3D12ProtectedResourceSession* protectedSession,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI::Format* castableFormats ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateCommittedResource3( heapProperties, static_cast< D3D12_HEAP_FLAGS >( heapFlags ), pDesc, static_cast< D3D12_BARRIER_LAYOUT >( initialLayout ), optimizedClearValue, protectedSession, numCastableFormats, reinterpret_cast< const DXGI_FORMAT* >( castableFormats ), __uuidof( ItfType ), ( void** )&itf );
            return T( itf );
        }


        void CreatePlacedResource2(
            _In_  ID3D12Heap* heap,
            UINT64 heapOffset,
            _In_  const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI_FORMAT* castableFormats,
            REFIID riid,
            _COM_Outptr_opt_  void** resource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreatePlacedResource2( heap, heapOffset, pDesc, initialLayout, optimizedClearValue, numCastableFormats, castableFormats, riid, resource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreatePlacedResource2(
            _In_  ID3D12Heap* heap,
            UINT64 heapOffset,
            _In_  const D3D12_RESOURCE_DESC1* pDesc,
            BarrierLayout initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI::Format* castableFormats,
            REFIID riid,
            _COM_Outptr_opt_  void** resource ) const
        {
            CreatePlacedResource2( heap, heapOffset, pDesc, static_cast< D3D12_BARRIER_LAYOUT >( initialLayout ), optimizedClearValue, numCastableFormats, reinterpret_cast< const DXGI_FORMAT* >( castableFormats ), riid, resource );
        }


        template<typename T>
            requires std::is_base_of_v<Resource, T>
        T CreatePlacedResource2(
            _In_  ID3D12Heap* heap,
            UINT64 heapOffset,
            _In_  const D3D12_RESOURCE_DESC1* pDesc,
            D3D12_BARRIER_LAYOUT initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI_FORMAT* castableFormats ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreatePlacedResource2( heap, heapOffset, pDesc, initialLayout, optimizedClearValue, numCastableFormats, castableFormats, __uuidof( ItfType ), ( void** )&itf );
            return T( itf );
        }

        template<typename T>
            requires std::is_base_of_v<Resource, T>
        T CreatePlacedResource2(
            _In_  ID3D12Heap* heap,
            UINT64 heapOffset,
            _In_  const D3D12_RESOURCE_DESC1* pDesc,
            BarrierLayout initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI::Format* castableFormats ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreatePlacedResource2( heap, heapOffset, pDesc, static_cast< D3D12_BARRIER_LAYOUT >( initialLayout ), optimizedClearValue, numCastableFormats, reinterpret_cast< const DXGI_FORMAT* >( castableFormats ), __uuidof( ItfType ), ( void** )&itf );
            return T( itf );
        }


        void CreateReservedResource2(
            _In_  const D3D12_RESOURCE_DESC* pDesc,
            D3D12_BARRIER_LAYOUT initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            _In_opt_  ID3D12ProtectedResourceSession* protectedSession,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI_FORMAT* castableFormats,
            REFIID riid,
            _COM_Outptr_opt_  void** resource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateReservedResource2( pDesc, initialLayout, optimizedClearValue, protectedSession, numCastableFormats, castableFormats, riid, resource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateReservedResource2(
            _In_  const D3D12_RESOURCE_DESC* pDesc,
            BarrierLayout initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            _In_opt_  ID3D12ProtectedResourceSession* protectedSession,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI::Format* castableFormats,
            REFIID riid,
            _COM_Outptr_opt_  void** resource ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateReservedResource2( pDesc, static_cast< D3D12_BARRIER_LAYOUT >(initialLayout), optimizedClearValue, protectedSession, numCastableFormats, reinterpret_cast< const DXGI_FORMAT* >( castableFormats ), riid, resource );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
            requires std::is_base_of_v<Resource, T>
        T CreateReservedResource2(
            _In_  const D3D12_RESOURCE_DESC* pDesc,
            D3D12_BARRIER_LAYOUT initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            _In_opt_  ID3D12ProtectedResourceSession* protectedSession,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI_FORMAT* castableFormats ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateReservedResource2( pDesc, initialLayout, optimizedClearValue, protectedSession, numCastableFormats, castableFormats, __uuidof( ItfType ), ( void** )&itf );
            return T( itf );
        }

        template<typename T>
            requires std::is_base_of_v<Resource, T>
        T CreateReservedResource2(
            _In_  const D3D12_RESOURCE_DESC* pDesc,
            BarrierLayout initialLayout,
            _In_opt_  const D3D12_CLEAR_VALUE* optimizedClearValue,
            _In_opt_  ID3D12ProtectedResourceSession* protectedSession,
            UINT32 numCastableFormats,
            _In_opt_count_( numCastableFormats )  const DXGI::Format* castableFormats ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateReservedResource2( pDesc, initialLayout, optimizedClearValue, protectedSession, numCastableFormats, castableFormats, __uuidof( ItfType ), ( void** )&itf );
            return T( itf );
        }


    };


    class Device11 : public Device10
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Device11, Device10, ID3D12Device11, ID3D12Device10 )
    public:
        void CreateSampler2( _In_  const D3D12_SAMPLER_DESC2* pDesc, _In_  D3D12_CPU_DESCRIPTOR_HANDLE destDescriptor ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->CreateSampler2( pDesc, destDescriptor );
        }
    };

    class Device12 : public Device11
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Device12, Device11, ID3D12Device12, ID3D12Device11 )
    public:
        D3D12_RESOURCE_ALLOCATION_INFO GetResourceAllocationInfo3(
            UINT visibleMask,
            UINT numResourceDescs,
            _In_reads_( numResourceDescs )  const D3D12_RESOURCE_DESC1* pResourceDescs,
            _In_opt_count_( numResourceDescs )  const UINT32* pNumCastableFormats,
            _In_opt_count_( numResourceDescs )  const DXGI_FORMAT* const* ppCastableFormats,
            _Out_writes_opt_( numResourceDescs )  D3D12_RESOURCE_ALLOCATION_INFO1* pResourceAllocationInfo1 ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetResourceAllocationInfo3( visibleMask, numResourceDescs, pResourceDescs, pNumCastableFormats, ppCastableFormats, pResourceAllocationInfo1 );
        }
    };

    class Device13 : public Device12
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Device13, Device12, ID3D12Device13, ID3D12Device12 )
    public:
        HRESULT OpenExistingHeapFromAddress1( _In_  const void* pAddress, SIZE_T size, REFIID riid, _COM_Outptr_  void** ppvHeap ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->OpenExistingHeapFromAddress1( pAddress, size, riid, ppvHeap );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class Device14 : public Device13
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Device14, Device13, ID3D12Device14, ID3D12Device13 )
    public:
        HRESULT CreateRootSignatureFromSubobjectInLibrary(
            _In_  UINT nodeMask,
            _In_reads_( blobLengthInBytes )  const void* pLibraryBlob,
            _In_  SIZE_T blobLengthInBytes,
            _In_opt_  LPCWSTR subobjectName,
            REFIID riid,
            _COM_Outptr_  void** ppvRootSignature ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateRootSignatureFromSubobjectInLibrary( nodeMask, pLibraryBlob, blobLengthInBytes, subobjectName, riid, ppvRootSignature );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class VirtualizationGuestDevice : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( VirtualizationGuestDevice, Unknown, ID3D12VirtualizationGuestDevice, IUnknown )
    public:
        void ShareWithHost( _In_  ID3D12DeviceChild* pObject, _Out_  HANDLE* pHandle ) CONST
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ShareWithHost( pObject, pHandle );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateFenceFd( _In_  ID3D12Fence* pFence, UINT64 FenceValue, _Out_  int* pFenceFd ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateFenceFd( pFence, FenceValue, pFenceFd );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };




    /// <summary>
    /// This class is used to configure the runtime for tools such as PIX. 
    /// Its not intended or supported for any other scenario
    /// </summary>
    class Tools : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( Tools, Unknown, ID3D12Tools, IUnknown )
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


    class SDKConfiguration : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( SDKConfiguration, Unknown, ID3D12SDKConfiguration, IUnknown )
    public:
        void SetSDKVersion( UINT SDKVersion, _In_z_  LPCSTR SDKPath ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetSDKVersion( SDKVersion, SDKPath );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class SDKConfiguration1 : public SDKConfiguration
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( SDKConfiguration1, SDKConfiguration, ID3D12SDKConfiguration1, ID3D12SDKConfiguration )
    public:
        void CreateDeviceFactory( UINT SDKVersion, _In_  LPCSTR SDKPath, REFIID riid, _COM_Outptr_  void** ppvFactory ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDeviceFactory( SDKVersion, SDKPath, riid, ppvFactory );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void FreeUnusedSDKs( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->FreeUnusedSDKs( );
        }
    };

    class DeviceFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DeviceFactory, Unknown, ID3D12DeviceFactory, IUnknown )
    public:
        void InitializeFromGlobalState( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->InitializeFromGlobalState( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void ApplyToGlobalState( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->ApplyToGlobalState( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void SetFlags( D3D12_DEVICE_FACTORY_FLAGS flags ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SetFlags( flags );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        D3D12_DEVICE_FACTORY_FLAGS GetFlags( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetFlags( );
        }

        void GetConfigurationInterface( REFCLSID clsid, REFIID iid, _COM_Outptr_  void** ppv )
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetConfigurationInterface( clsid, iid, ppv );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void EnableExperimentalFeatures( UINT NumFeatures, _In_reads_( NumFeatures )  const IID* pIIDs, _In_reads_opt_( NumFeatures )  void* pConfigurationStructs, _In_reads_opt_( NumFeatures )  UINT* pConfigurationStructSizes ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->EnableExperimentalFeatures( NumFeatures, pIIDs, pConfigurationStructs, pConfigurationStructSizes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void CreateDevice( _In_opt_  IUnknown* adapter, D3D_FEATURE_LEVEL FeatureLevel, REFIID riid, _COM_Outptr_opt_  void** ppvDevice ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateDevice( adapter, FeatureLevel, riid, ppvDevice );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class DeviceConfiguration : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DeviceConfiguration, Unknown, ID3D12DeviceConfiguration, IUnknown )
    public:
        D3D12_DEVICE_CONFIGURATION_DESC STDMETHODCALLTYPE GetDesc( void ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetDesc( );
        }
        void GetEnabledExperimentalFeatures( _Out_writes_( NumGuids )  GUID* pGuids, UINT NumGuids ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->GetEnabledExperimentalFeatures( pGuids, NumGuids );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void SerializeVersionedRootSignature( _In_  const D3D12_VERSIONED_ROOT_SIGNATURE_DESC* pDesc, _COM_Outptr_  ID3DBlob** ppResult, _Always_( _Outptr_opt_result_maybenull_ )  ID3DBlob** ppError ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->SerializeVersionedRootSignature( pDesc, ppResult, ppError );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
        void CreateVersionedRootSignatureDeserializer( _In_reads_bytes_( Size )  const void* pBlob, SIZE_T Size, REFIID riid, _COM_Outptr_  void** ppvDeserializer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateVersionedRootSignatureDeserializer( pBlob, Size, riid, ppvDeserializer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    class DeviceConfiguration1 : public DeviceConfiguration
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( DeviceConfiguration1, DeviceConfiguration, ID3D12DeviceConfiguration1, ID3D12DeviceConfiguration )
    public:
        void CreateVersionedRootSignatureDeserializerFromSubobjectInLibrary( _In_reads_bytes_( Size )  const void* pLibraryBlob, SIZE_T Size, LPCWSTR RootSignatureSubobjectName, REFIID riid, _COM_Outptr_  void** ppvDeserializer ) const
        {
            InterfaceType* pInterface = GetInterface( );
            auto hr = pInterface->CreateVersionedRootSignatureDeserializerFromSubobjectInLibrary( pLibraryBlob, Size, RootSignatureSubobjectName, riid, ppvDeserializer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };


    /// <summary>
    /// Encapsulates a list of graphics commands for rendering, extending 
    /// the GraphicsCommandList4 class to support variable-rate shading (VRS).
    /// </summary>
    class GraphicsCommandList5 : public GraphicsCommandList4
    {
    public:
        using Base = GraphicsCommandList4;

        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList5, GraphicsCommandList4, ID3D12GraphicsCommandList5, ID3D12GraphicsCommandList4 )
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

    class GraphicsCommandList6 : public GraphicsCommandList5
    {
    public:
        using Base = GraphicsCommandList5;

        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList6, GraphicsCommandList5, ID3D12GraphicsCommandList6, ID3D12GraphicsCommandList5 )
    public:
        void DispatchMesh( _In_ UINT ThreadGroupCountX, _In_ UINT ThreadGroupCountY, _In_ UINT ThreadGroupCountZ ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DispatchMesh( ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ );
        }
    };

    class GraphicsCommandList7 : public GraphicsCommandList6
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList7, GraphicsCommandList6, ID3D12GraphicsCommandList7, ID3D12GraphicsCommandList6 )
    public:
        void Barrier( UINT32 NumBarrierGroups, _In_reads_( NumBarrierGroups )  const D3D12_BARRIER_GROUP* pBarrierGroups ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->Barrier( NumBarrierGroups, pBarrierGroups );
        }
    };


    class GraphicsCommandList8 : public GraphicsCommandList7
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList8, GraphicsCommandList7, ID3D12GraphicsCommandList8, ID3D12GraphicsCommandList7 )
    public:
        void OMSetFrontAndBackStencilRef( _In_  UINT FrontStencilRef, _In_  UINT BackStencilRef ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->OMSetFrontAndBackStencilRef( FrontStencilRef, BackStencilRef );
        }
    };

    class GraphicsCommandList9 : public GraphicsCommandList8
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList9, GraphicsCommandList8, ID3D12GraphicsCommandList9, ID3D12GraphicsCommandList8 )
    public:
        void RSSetDepthBias( _In_  FLOAT DepthBias, _In_  FLOAT DepthBiasClamp, _In_  FLOAT SlopeScaledDepthBias ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->RSSetDepthBias( DepthBias, DepthBiasClamp, SlopeScaledDepthBias );
        }

        void IASetIndexBufferStripCutValue( _In_  D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBStripCutValue ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->IASetIndexBufferStripCutValue( IBStripCutValue );

        }
    };

    class GraphicsCommandList10 : public GraphicsCommandList9
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( GraphicsCommandList10, GraphicsCommandList9, ID3D12GraphicsCommandList10, ID3D12GraphicsCommandList9 )
    public:
        void SetProgram( _In_  const D3D12_SET_PROGRAM_DESC* pDesc ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->SetProgram( pDesc );
        }

        void DispatchGraph( _In_  const D3D12_DISPATCH_GRAPH_DESC* pDesc ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->DispatchGraph( pDesc );
        }
    };

    /// <summary>
    /// Creates a device that represents the display adapter.
    /// </summary>
    /// <typeparam name="T">
    /// The type of device to create, which must be Device or a class  
    /// that inherits the Device class.
    /// </typeparam>
    /// <param name="adapter">
    /// A pointer to the video adapter to use when creating a device. 
    /// Pass NULL to use the default adapter, which is the first adapter 
    /// that is enumerated by DXGI::Factory1::EnumAdapters.
    /// </param>
    /// <param name="minimumFeatureLevel">
    /// The minimum D3D_FEATURE_LEVEL required for successful device creation.
    /// </param>
    /// <returns>
    /// The newly created device.
    /// </returns>
    template<typename T = Device>
        requires std::is_base_of_v<Device, T>
    inline T CreateDevice( IUnknown* adapter, D3D_FEATURE_LEVEL minimumFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1 )
    {
        using InterfaceType = T::InterfaceType;
        auto InterfaceId = __uuidof( InterfaceType );
        InterfaceType* intf = nullptr;
        auto hr = D3D12CreateDevice( adapter, minimumFeatureLevel, InterfaceId, ( void** )&intf );
        HCC_COM_CHECK_HRESULT( hr );
        T result( intf );
        return result;
    }

    template<typename T = Device>
        requires std::is_base_of_v<Device, T>
    inline T CreateDevice( Unknown adapter, D3D_FEATURE_LEVEL minimumFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1 )
    {
        return CreateDevice<T>( adapter.GetInterfacePointer( ), minimumFeatureLevel );
    }

    inline Device4 DeviceChild::GetDevice( ) const
    {
        return GetDevice<Device4>( );
    }


    
    inline D3DBlob CompileFromFile( _In_ LPCWSTR fileName,
            _In_reads_opt_( _Inexpressible_( pDefines->Name != NULL ) ) CONST D3D_SHADER_MACRO* defines,
            _In_opt_ ID3DInclude* include,
            _In_ LPCSTR entrypoint,
            _In_ LPCSTR target,
            _In_ UINT flags1,
            _In_ UINT flags2 = 0,
            _Always_( _Outptr_opt_result_maybenull_ ) ID3DBlob** errorMessages = nullptr )
    {
        ID3DBlob* code = nullptr;
        auto hr = D3DCompileFromFile( fileName,
            defines,
            include,
            entrypoint,
            target,
            flags1,
            flags2,
            &code,
            errorMessages );
        HCC_COM_CHECK_HRESULT( hr );
        return D3DBlob( code );
    }

    inline D3DBlob CompileFromFile( _In_ LPCWSTR fileName,
        _In_ LPCSTR entrypoint,
        _In_ LPCSTR target,
        _In_ UINT flags1,
        _In_ UINT flags2 = 0,
        _Always_( _Outptr_opt_result_maybenull_ ) ID3DBlob** errorMessages = nullptr )
    {
        return CompileFromFile( fileName,
            nullptr,
            nullptr,
            entrypoint,
            target,
            flags1,
            flags2,
            errorMessages );
    }
    template <SimpleWideStringLike T>
    inline D3DBlob CompileFromFile( const T& fileName,
        _In_reads_opt_( _Inexpressible_( pDefines->Name != NULL ) ) CONST D3D_SHADER_MACRO* defines,
        _In_opt_ ID3DInclude* include,
        _In_ LPCSTR entrypoint,
        _In_ LPCSTR target,
        _In_ UINT flags1,
        _In_ UINT flags2 = 0,
        _Always_( _Outptr_opt_result_maybenull_ ) ID3DBlob** errorMessages = nullptr )
    {
        return CompileFromFile( fileName.c_str(),
            defines,
            include,
            entrypoint,
            target,
            flags1,
            flags2,
            errorMessages );
    }

    template <SimpleWideStringLike T>
    inline D3DBlob CompileFromFile( const T& fileName,
        _In_ LPCSTR entrypoint,
        _In_ LPCSTR target,
        _In_ UINT flags1,
        _In_ UINT flags2 = 0,
        _Always_( _Outptr_opt_result_maybenull_ ) ID3DBlob** errorMessages = nullptr )
    {
        return CompileFromFile( fileName.c_str( ),
            nullptr,
            nullptr,
            entrypoint,
            target,
            flags1,
            flags2,
            errorMessages );
    }

    

    //------------------------------------------------------------------------------------------------
    // Row-by-row memcpy
    inline void MemcpySubresource(
        _In_ const MemCopyDest* pDest,
        _In_ const SubResourceData* pSrc,
        SIZE_T RowSizeInBytes,
        UINT NumRows,
        UINT NumSlices )
    {
        for ( UINT z = 0; z < NumSlices; ++z )
        {
            BYTE* pDestSlice = reinterpret_cast< BYTE* >( pDest->pData ) + pDest->SlicePitch * z;
            const BYTE* pSrcSlice = reinterpret_cast< const BYTE* >( pSrc->pData ) + pSrc->SlicePitch * z;
            for ( UINT y = 0; y < NumRows; ++y )
            {
                memcpy( pDestSlice + pDest->RowPitch * y,
                    pSrcSlice + pSrc->RowPitch * y,
                    RowSizeInBytes );
            }
        }
    }


    //------------------------------------------------------------------------------------------------
    // All arrays must be populated (e.g. by calling GetCopyableFootprints)
    inline UINT64 UpdateSubResources(
        const GraphicsCommandList& cmdList,
        const Resource& destinationResource,
        const Resource& intermediate,
        _In_range_( 0, D3D12_REQ_SUBRESOURCES ) UInt32 firstSubResource,
        _In_range_( 0, D3D12_REQ_SUBRESOURCES - firstSubResource ) UInt32 numSubResources,
        UInt64 requiredSize,
        _In_reads_( numSubResources ) const PlacedSubresourceFootprint* layouts,
        _In_reads_( numSubResources ) const UInt32* numRows,
        _In_reads_( numSubResources ) const UInt64* rowSizesInBytes,
        _In_reads_( numSubResources ) const SubResourceData* srcData )
    {
        // Minor validation
        auto intermediateDesc = intermediate.GetDesc( );
        auto destinationDesc = destinationResource.GetDesc( );
        if ( intermediateDesc.Dimension != ResourceDimension::Buffer ||
            intermediateDesc.Width < requiredSize + layouts[ 0 ].Offset ||
            requiredSize > SIZE_T( -1 ) ||
            ( destinationDesc.Dimension == ResourceDimension::Buffer &&
                ( firstSubResource != 0 || numSubResources != 1 ) ) )
        {
            return 0;
        }

        BYTE* pData = reinterpret_cast< BYTE* >( intermediate.Map( 0 ) );
        

        for ( UINT i = 0; i < numSubResources; ++i )
        {
            if ( rowSizesInBytes[ i ] > SIZE_T( -1 ) )
            {
                return 0;
            }
            MemCopyDest DestData 
            ( 
                pData + layouts[ i ].Offset, 
                layouts[ i ].Footprint.RowPitch, 
                SIZE_T( layouts[ i ].Footprint.RowPitch ) * SIZE_T( numRows[ i ] ) 
            );
            MemcpySubresource( &DestData, &srcData[ i ], static_cast< SIZE_T >( rowSizesInBytes[ i ] ), numRows[ i ], layouts[ i ].Footprint.Depth );
        }
        intermediate.Unmap( 0, nullptr );

        if ( destinationDesc.Dimension == ResourceDimension::Buffer )
        {
            cmdList.CopyBufferRegion( destinationResource, 0, intermediate, layouts[ 0 ].Offset, layouts[ 0 ].Footprint.Width );
        }
        else
        {
            for ( UINT i = 0; i < numSubResources; ++i )
            {
                TextureCopyLocation Dst( destinationResource, i + firstSubResource );
                TextureCopyLocation Src( intermediate, layouts[ i ] );

                cmdList.CopyTextureRegion( &Dst, 0, 0, 0, &Src, nullptr );
            }
        }
        return requiredSize;
    }

    //------------------------------------------------------------------------------------------------
    // Heap-allocating UpdateSubresources implementation
    inline UInt64 UpdateSubResources(
        const GraphicsCommandList& cmdList,
        const Resource& destinationResource,
        const Resource& intermediate,
        UINT64 intermediateOffset,
        _In_range_( 0, D3D12_REQ_SUBRESOURCES ) UINT firstSubResource,
        _In_range_( 0, D3D12_REQ_SUBRESOURCES - firstSubResource ) UINT numSubResources,
        _In_reads_( numSubResources ) SubResourceData* srcData )
    {
        UInt64 RequiredSize = 0;
        UInt64 MemToAlloc = static_cast< UInt64 >( sizeof( PlacedSubresourceFootprint ) + sizeof( UInt32 ) + sizeof( UInt64 ) ) * numSubResources;
        if ( MemToAlloc > SIZE_MAX )
        {
            return 0;
        }
        void* pMem = HeapAlloc( GetProcessHeap( ), 0, static_cast< SIZE_T >( MemToAlloc ) );
        if ( pMem == nullptr )
        {
            return 0;
        }
        auto pLayouts = reinterpret_cast< PlacedSubresourceFootprint* >( pMem );
        UInt64* pRowSizesInBytes = reinterpret_cast< UInt64* >( pLayouts + numSubResources );
        UInt32* pNumRows = reinterpret_cast< UInt32* >( pRowSizesInBytes + numSubResources );

        auto Desc = destinationResource.GetDesc( );
        auto device = destinationResource.GetDevice( );
        
        device.GetCopyableFootprints( &Desc, firstSubResource, numSubResources, intermediateOffset, pLayouts, pNumRows, pRowSizesInBytes, &RequiredSize );

        UInt64 Result = UpdateSubResources( cmdList, destinationResource, intermediate, firstSubResource, numSubResources, RequiredSize, pLayouts, pNumRows, pRowSizesInBytes, srcData );
        HeapFree( GetProcessHeap( ), 0, pMem );
        return Result;
    }

    //------------------------------------------------------------------------------------------------
    // Stack-allocating UpdateSubresources implementation
    template <UINT MaxSubresources>
    inline UINT64 UpdateSubResources(
        const GraphicsCommandList& cmdList,
        const Resource& destinationResource,
        const Resource& intermediate,
        UInt64 intermediateOffset,
        _In_range_( 0, MaxSubresources ) UINT firstSubResource,
        _In_range_( 1, MaxSubresources - firstSubResource ) UInt32 numSubResources,
        _In_reads_( numSubResources ) SubResourceData* srcData )
    {
        UInt64 RequiredSize = 0;
        PlacedSubresourceFootprint Layouts[ MaxSubresources ];
        UINT NumRows[ MaxSubresources ];
        UINT64 RowSizesInBytes[ MaxSubresources ];

        auto Desc = destinationResource.GetDesc( );
        auto device = destinationResource.GetDevice( );
        
        device.GetCopyableFootprints( &Desc, firstSubResource, numSubResources, intermediateOffset, Layouts, NumRows, RowSizesInBytes, &RequiredSize );

        return UpdateSubresources( cmdList, destinationResource, intermediate, firstSubResource, numSubResources, RequiredSize, Layouts, NumRows, RowSizesInBytes, srcData );
    }

}

#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12EX_INL_
#include "HWGraphicsD3D12Ex.inl"
#endif


#endif
