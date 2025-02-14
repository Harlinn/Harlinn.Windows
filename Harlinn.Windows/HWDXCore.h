#pragma once
#ifndef HARLINN_WINDOWS_HWDXCORE_H_
#define HARLINN_WINDOWS_HWDXCORE_H_
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

#include <HWDef.h>
#include <HCCCOM.h>

#pragma comment( lib, "dxcore.lib")

namespace Harlinn::Windows::Graphics::DXCore
{
    class Adapter1;
    class AdapterList;
    class AdapterFactory;
    class AdapterFactory1;


    enum class GraphicsPreemptionGranularity
    {
        None = 0,
        DmaBufferBoundary = 100,
        PrimitiveBoundary = 200,
        TriangleBoundary = 300,
        PixelBoundary = 400,
        ShaderBoundary = 500,
    };

    enum class ComputePreemptionGranularity
    {
        None = 0,
        DmaBufferBoundary = 100,
        DispatchBoundary = 200,
        ThreadGroupBoundary = 300,
        ThreadBoundary = 400,
        ShaderBoundary = 500,
    };


    class Adapter : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Adapter, Unknown, IDXCoreAdapter, IUnknown )
    public:
        bool IsValid( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsValid( );
        }

        bool IsAttributeSupported( REFGUID attributeGUID ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsAttributeSupported( attributeGUID );
        }

        bool IsD3D11Supported( ) const
        {
            return IsAttributeSupported( DXCORE_ADAPTER_ATTRIBUTE_D3D11_GRAPHICS );
        }

        bool IsD3D12Supported( ) const
        {
            return IsAttributeSupported( DXCORE_ADAPTER_ATTRIBUTE_D3D12_GRAPHICS );
        }

        bool IsCoreComputeSupported( ) const
        {
            return IsAttributeSupported( DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE );
        }

        bool IsMachineLearningSupported( ) const
        {
            return IsAttributeSupported( DXCORE_ADAPTER_ATTRIBUTE_D3D12_GENERIC_ML );
        }

        bool IsVideoProcessingSupported( ) const
        {
            return IsAttributeSupported( DXCORE_ADAPTER_ATTRIBUTE_D3D12_GENERIC_MEDIA );
        }

        bool IsNPU( ) const
        {
            return IsAttributeSupported( DXCORE_HARDWARE_TYPE_ATTRIBUTE_NPU );
        }

        bool IsGPU( ) const
        {
            return IsAttributeSupported( DXCORE_HARDWARE_TYPE_ATTRIBUTE_GPU );
        }

        bool IsComputeAccelerator( ) const
        {
            return IsAttributeSupported( DXCORE_HARDWARE_TYPE_ATTRIBUTE_COMPUTE_ACCELERATOR );
        }

        bool IsMediaAccelerator( ) const
        {
            return IsAttributeSupported( DXCORE_HARDWARE_TYPE_ATTRIBUTE_MEDIA_ACCELERATOR );
        }




        bool IsPropertySupported( DXCoreAdapterProperty property ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsPropertySupported( property );
        }

        void GetProperty( DXCoreAdapterProperty property, size_t bufferSize, _Out_writes_bytes_( bufferSize )  void* propertyData ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetProperty( property, bufferSize, propertyData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <class T>
        void GetProperty( DXCoreAdapterProperty property, _Out_writes_bytes_( sizeof( T ) )  T* propertyData ) const
        {
            return GetProperty( property, sizeof( T ), ( void* )propertyData );
        }

        void GetPropertySize( DXCoreAdapterProperty property, _Out_ size_t* bufferSize ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPropertySize( property, bufferSize );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        size_t GetPropertySize( DXCoreAdapterProperty property ) const
        {
            size_t result = 0;
            GetPropertySize( property, &result );
            return result;
        }

        bool IsQueryStateSupported( DXCoreAdapterState property ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsQueryStateSupported( property );
        }

        void QueryState( DXCoreAdapterState state, size_t inputStateDetailsSize, _In_reads_bytes_opt_( inputStateDetailsSize ) const void* inputStateDetails,
                        size_t outputBufferSize, _Out_writes_bytes_( outputBufferSize ) void* outputBuffer ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->QueryState( state, inputStateDetailsSize, inputStateDetails, outputBufferSize, outputBuffer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T1, typename T2>
        void QueryState( DXCoreAdapterState state, _In_reads_bytes_opt_( sizeof( T1 ) ) const T1* inputStateDetails, _Out_writes_bytes_( sizeof( T2 ) ) T2* outputBuffer ) const
        {
            QueryState( state, sizeof( T1 ), ( const void* )inputStateDetails, sizeof( T2 ), ( void* )outputBuffer );
        }

        template <typename T>
        void QueryState( DXCoreAdapterState state, _Out_writes_bytes_( sizeof( T ) ) T* outputBuffer ) const
        {
            QueryState( state, 0, nullptr, sizeof( T ), ( void* )outputBuffer );
        }

        bool IsSetStateSupported( DXCoreAdapterState property )  const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsSetStateSupported( property );
        }

        void SetState( DXCoreAdapterState state, size_t inputStateDetailsSize, _In_reads_bytes_opt_( inputStateDetailsSize ) const void* inputStateDetails,
            size_t inputDataSize, _In_reads_bytes_( inputDataSize ) const void* inputData ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->SetState( state, inputStateDetailsSize, inputStateDetails, inputDataSize, inputData );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T1, typename T2>
        void SetState( DXCoreAdapterState state, const T1* inputStateDetails, const T2* inputData ) const
        {
            return SetState( state, sizeof( T1 ), ( const void* )inputStateDetails, sizeof( T2 ), ( const void* )inputData );
        }

        void GetFactory( REFIID riid, _COM_Outptr_ void** factory ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFactory( riid, factory );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T>
        void GetFactory( _COM_Outptr_ T** factory ) const
        {
            GetFactory( __uuidof(T), reinterpret_cast<void**>( factory ) );
        }

        template<typename T>
            requires std::is_base_of_v<AdapterFactory,T>
        T GetFactory( ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            GetFactory( &itf );
            return T( itf );
        }

        LUID InstanceLUID( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::InstanceLuid ) )
            {
                LUID result;
                GetProperty( DXCoreAdapterProperty::InstanceLuid, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"InstanceLuid not supported" );
            }
        }

        UInt64 DriverVersion( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::DriverVersion ) )
            {
                UInt64 result;
                GetProperty( DXCoreAdapterProperty::DriverVersion, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"DriverVersion not supported" );
            }
        }

        WideString DriverDescription( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::DriverDescription ) )
            {
                auto propertySize = GetPropertySize( DXCoreAdapterProperty::DriverDescription );
                boost::container::small_vector<char,512> tmp;
                tmp.resize( propertySize );
                
                GetProperty( DXCoreAdapterProperty::DriverVersion, tmp.size(),  tmp.data() );
                WideString result;
                ToWideString( tmp.data( ), tmp.size( ) - 1, CP_UTF8, 0, result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"DriverDescription not supported" );
            }
        }

        DXCoreHardwareID HardwareID( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::HardwareID ) )
            {
                DXCoreHardwareID result{};
                GetProperty( DXCoreAdapterProperty::HardwareID, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"HardwareID not supported" );
            }
        }

        Int32 KmdModelVersion( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::KmdModelVersion ) )
            {
                Int32 result{};
                GetProperty( DXCoreAdapterProperty::KmdModelVersion, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"KmdModelVersion not supported" );
            }
        }

        DXCore::ComputePreemptionGranularity ComputePreemptionGranularity( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::ComputePreemptionGranularity ) )
            {
                DXCore::ComputePreemptionGranularity result{};
                GetProperty( DXCoreAdapterProperty::ComputePreemptionGranularity, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"ComputePreemptionGranularity not supported" );
            }
        }

        DXCore::GraphicsPreemptionGranularity GraphicsPreemptionGranularity( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::GraphicsPreemptionGranularity ) )
            {
                DXCore::GraphicsPreemptionGranularity result{};
                GetProperty( DXCoreAdapterProperty::GraphicsPreemptionGranularity, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"GraphicsPreemptionGranularity not supported" );
            }
        }

        UInt64 DedicatedAdapterMemory( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::DedicatedAdapterMemory ) )
            {
                UInt64 result{};
                GetProperty( DXCoreAdapterProperty::DedicatedAdapterMemory, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"DedicatedAdapterMemory not supported" );
            }
        }

        UInt64 DedicatedSystemMemory( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::DedicatedSystemMemory ) )
            {
                UInt64 result{};
                GetProperty( DXCoreAdapterProperty::DedicatedSystemMemory, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"DedicatedSystemMemory not supported" );
            }
        }

        UInt64 SharedSystemMemory( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::SharedSystemMemory ) )
            {
                UInt64 result{};
                GetProperty( DXCoreAdapterProperty::SharedSystemMemory, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"SharedSystemMemory not supported" );
            }
        }

        bool AcgCompatible( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::AcgCompatible ) )
            {
                bool result{};
                GetProperty( DXCoreAdapterProperty::AcgCompatible, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"AcgCompatible not supported" );
            }
        }

        bool IsHardware( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::IsHardware ) )
            {
                bool result{};
                GetProperty( DXCoreAdapterProperty::IsHardware, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"IsHardware not supported" );
            }
        }

        bool IsIntegrated( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::IsIntegrated ) )
            {
                bool result{};
                GetProperty( DXCoreAdapterProperty::IsIntegrated, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"IsIntegrated not supported" );
            }
        }

        bool IsDetachable( ) const
        {
            if ( IsPropertySupported( DXCoreAdapterProperty::IsDetachable ) )
            {
                bool result{};
                GetProperty( DXCoreAdapterProperty::IsDetachable, &result );
                return result;
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"IsDetachable not supported" );
            }
        }


    };

    class Adapter1 : public Adapter
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( Adapter1, Adapter, IDXCoreAdapter1, IDXCoreAdapter )
    public:
        void GetPropertyWithInput( DXCoreAdapterProperty property, size_t inputPropertyDetailsSize, _In_reads_bytes_opt_( inputPropertyDetailsSize ) const void* inputPropertyDetails,
                                    size_t outputBufferSize, _Out_writes_bytes_( outputBufferSize ) void* outputBuffer ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPropertyWithInput( property, inputPropertyDetailsSize, inputPropertyDetails, outputBufferSize, outputBuffer );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T1, typename T2>
        void GetPropertyWithInput( DXCoreAdapterProperty property, _In_reads_bytes_opt_( sizeof( T1 ) ) const T1* inputPropertyDetails, _Out_writes_bytes_( sizeof( T2 ) ) T2* outputBuffer )
        {
            return GetPropertyWithInput( property, sizeof( T1 ), ( const void* )inputPropertyDetails, sizeof( T2 ), ( void* )outputBuffer );
        }
    };

    class AdapterList : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( AdapterList, Unknown, IDXCoreAdapterList, IUnknown )
    public:
        void GetAdapter( uint32_t index, REFIID riid, _COM_Outptr_ void** ppvAdapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetAdapter( index, riid, ppvAdapter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
        void GetAdapter( uint32_t index, _COM_Outptr_ T** ppvAdapter ) const
        {
            GetAdapter( index, IID_PPV_ARGS( ppvAdapter ) );
        }
        template<typename T = Adapter1>
            requires std::is_base_of_v<Adapter,T>
        T GetAdapter( uint32_t index ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            GetAdapter( index, &itf );
            return T( itf );
        }

        UInt32 GetAdapterCount( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->GetAdapterCount( );
        }

        bool IsStale( ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsStale( );
        }

        void GetFactory( REFIID riid, _COM_Outptr_ void** factory ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetFactory( riid, factory );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template <typename T>
        void GetFactory( _COM_Outptr_ T** factory ) const
        {
            GetFactory( __uuidof( T ), reinterpret_cast< void** >( factory ) );
        }

        template<typename T>
            requires std::is_base_of_v<AdapterFactory, T>
        T GetFactory( ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            GetFactory( &itf );
            return T( itf );
        }

        void Sort( uint32_t numPreferences, _In_reads_( numPreferences ) const DXCoreAdapterPreference* preferences ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Sort( numPreferences, preferences );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        bool IsAdapterPreferenceSupported( DXCoreAdapterPreference preference ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsAdapterPreferenceSupported( preference );
        }
    };

    class AdapterFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( AdapterFactory, Unknown, IDXCoreAdapterFactory, IUnknown )
    public:
        void CreateAdapterList( uint32_t numAttributes, _In_reads_( numAttributes ) const GUID* filterAttributes, REFIID riid, _COM_Outptr_ void** ppvAdapterList ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateAdapterList( numAttributes, filterAttributes, riid, ppvAdapterList );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
        void CreateAdapterList( uint32_t numAttributes, _In_reads_( numAttributes ) const GUID* filterAttributes, _COM_Outptr_ T** ppvAdapterList ) const
        {
            CreateAdapterList( numAttributes, filterAttributes, IID_PPV_ARGS( ppvAdapterList ) );
        }

        template<typename T= AdapterList>
            requires std::is_base_of_v<AdapterList,T>
        T CreateAdapterList( uint32_t numAttributes, _In_reads_( numAttributes ) const GUID* filterAttributes ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateAdapterList( numAttributes, filterAttributes, &itf );
            return T( itf );
        }

        void GetAdapterByLuid( const LUID& adapterLUID, REFIID riid, _COM_Outptr_ void** ppvAdapter ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetAdapterByLuid( adapterLUID, riid, ppvAdapter );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
        void GetAdapterByLuid( const LUID& adapterLUID, _COM_Outptr_ T** ppvAdapter ) const
        {
            GetAdapterByLuid( adapterLUID, IID_PPV_ARGS( ppvAdapter ) );
        }

        template<typename T>
            requires std::is_base_of_v<Adapter1, T>
        T GetAdapterByLuid( const LUID& adapterLUID ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            GetAdapterByLuid( adapterLUID, &itf );
            return T( itf );
        }

        bool IsNotificationTypeSupported( DXCoreNotificationType notificationType ) const
        {
            auto* pInterface = GetInterface( );
            return pInterface->IsNotificationTypeSupported( notificationType );
        }

        void RegisterEventNotification( _In_ IUnknown* dxCoreObject, DXCoreNotificationType notificationType, _In_ PFN_DXCORE_NOTIFICATION_CALLBACK callbackFunction, _In_opt_ void* callbackContext, _Out_ uint32_t* eventCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->RegisterEventNotification( dxCoreObject, notificationType, callbackFunction, callbackContext, eventCookie );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        uint32_t RegisterEventNotification( _In_ IUnknown* dxCoreObject, DXCoreNotificationType notificationType, _In_ PFN_DXCORE_NOTIFICATION_CALLBACK callbackFunction, _In_opt_ void* callbackContext ) const
        {
            uint32_t result = 0;
            RegisterEventNotification( dxCoreObject, notificationType, callbackFunction, callbackContext, &result );
            return result;
        }
        template<typename T>
            requires std::is_base_of_v<Adapter,T> || std::is_base_of_v<AdapterList, T>
        uint32_t RegisterEventNotification( _In_ const T& dxCoreObject, DXCoreNotificationType notificationType, _In_ PFN_DXCORE_NOTIFICATION_CALLBACK callbackFunction, _In_opt_ void* callbackContext ) const
        {
            return RegisterEventNotification( dxCoreObject.GetInterfacePointer( ), notificationType, callbackFunction, callbackContext );
        }

        void UnregisterEventNotification( uint32_t eventCookie ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->UnregisterEventNotification( eventCookie );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    class AdapterFactory1 : public AdapterFactory
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL( AdapterFactory1, AdapterFactory, IDXCoreAdapterFactory1, IDXCoreAdapterFactory )
    public:
        void CreateAdapterListByWorkload( DXCoreWorkload workload, DXCoreRuntimeFilterFlags runtimeFilter, DXCoreHardwareTypeFilterFlags hardwareTypeFilter, REFIID riid, _COM_Outptr_ void** ppvAdapterList ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateAdapterListByWorkload( workload, runtimeFilter, hardwareTypeFilter, riid, ppvAdapterList );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        template<typename T>
        void CreateAdapterListByWorkload( DXCoreWorkload workload, DXCoreRuntimeFilterFlags runtimeFilter, DXCoreHardwareTypeFilterFlags hardwareTypeFilter, _COM_Outptr_ T** ppvAdapterList ) const
        {
            CreateAdapterListByWorkload( workload, runtimeFilter, hardwareTypeFilter, IID_PPV_ARGS( ppvAdapterList ) );
        }

        template<typename T>
            requires std::is_base_of_v<AdapterList, T>
        T CreateAdapterListByWorkload( DXCoreWorkload workload, DXCoreRuntimeFilterFlags runtimeFilter, DXCoreHardwareTypeFilterFlags hardwareTypeFilter ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateAdapterListByWorkload( workload, runtimeFilter, hardwareTypeFilter, &itf );
            return T( itf );
        }

    };

    template<typename T = AdapterFactory1>
        requires std::is_base_of_v<AdapterFactory, T>
    T CreateAdapterFactory( )
    {
        using ItfType = typename T::InterfaceType;
        ItfType* itf = nullptr;
        auto hr = DXCoreCreateAdapterFactory( __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
        HCC_COM_CHECK_HRESULT( hr );
        return T( itf );
    }



}

#endif
