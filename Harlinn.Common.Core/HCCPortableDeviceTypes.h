#pragma once
#ifndef HARLINN_COMMON_CORE_HCCPORTABLEDEVICETYPES_H_
#define HARLINN_COMMON_CORE_HCCPORTABLEDEVICETYPES_H_

#include <HCCDef.h>
#include <HCCCOM.h>
#include <HCCException.h>
#include <HCCVariant.h>
#include <HCCObj.h>
#include <HCCPropSys.h>
#include <PortableDeviceTypes.h>

#pragma comment(lib,"PortableDeviceGuids.lib")

namespace Harlinn::Common::Core
{
    class WpdSerializer;
    class PortableDeviceValues;
    class PortableDeviceKeyCollection;
    class PortableDevicePropVariantCollection;
    class PortableDeviceValuesCollection;

    /// <summary>
    /// Used by the device driver to serialize IPortableDeviceValues interfaces 
    /// to and from the raw data buffers used to communicate with the application.
    /// </summary>
    class WpdSerializer : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( WpdSerializer, Unknown, IWpdSerializer, IUnknown )

        static WpdSerializer Create( )
        {
            return CoCreateInstanceFromClassId<WpdSerializer>( CLSID_WpdSerializer );
        }

        /// <summary>
        /// Deserializes a byte array to an IPortableDeviceValues interface.
        /// </summary>
        /// <param name="inputBuffer">Pointer to the buffer to deserialize.</param>
        /// <param name="inputBufferLength">DWORD that specifies the size of the buffer, in bytes.</param>
        /// <param name="result">
        /// Address of a variable that receives a pointer to an IPortableDeviceValues interface created from the buffer. The application is responsible for calling Release on the interface.
        /// </param>
        void GetIPortableDeviceValuesFromBuffer( __RPC__in_ecount_full( inputBufferLength ) BYTE * inputBuffer, DWORD inputBufferLength, __RPC__deref_out_opt IPortableDeviceValues** result ) const
        { 
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetIPortableDeviceValuesFromBuffer( inputBuffer, inputBufferLength, result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        /// <summary>
        /// Deserializes a byte array to a PortableDeviceValues object.
        /// </summary>
        inline PortableDeviceValues GetPortableDeviceValuesFromBuffer( __RPC__in_ecount_full( inputBufferLength ) BYTE* inputBuffer, DWORD inputBufferLength ) const;

        /// <summary>
        /// Serializes an IPortableDeviceValues interface to a caller-allocated byte array.
        /// </summary>
        /// <param name="outputBufferLength">specifies the size of outputBuffer, in bytes.</param>
        /// <param name="values">Pointer to an IPortableDeviceValues interface to serialize.</param>
        /// <param name="outputBuffer">Pointer to a caller-allocated buffer. To learn the size of the required buffer, call GetSerializedSize.</param>
        /// <param name="bytesWritten">Pointer to a DWORD that indicates the number of bytes that were actually written to the caller-allocated buffer.</param>
        void WriteIPortableDeviceValuesToBuffer( DWORD outputBufferLength, __RPC__in_opt IPortableDeviceValues* values, __RPC__out_ecount_part( outputBufferLength, *bytesWritten ) BYTE* outputBuffer, __RPC__out DWORD* bytesWritten ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->WriteIPortableDeviceValuesToBuffer( outputBufferLength, values, outputBuffer, bytesWritten );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        /// <summary>
        /// Serializes a submitted IPortableDeviceValues interface to an allocated byte array. 
        /// The byte array returned is allocated for the caller and should be freed by the caller 
        /// using CoTaskMemFree.
        /// </summary>
        void GetBufferFromIPortableDeviceValues( __RPC__in_opt IPortableDeviceValues* sourceValues, __RPC__deref_out_ecount_full_opt( *bufferSize ) BYTE** buffer, __RPC__out DWORD* bufferSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetBufferFromIPortableDeviceValues( sourceValues, buffer, bufferSize );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        inline void GetBufferFromPortableDeviceValues( const PortableDeviceValues& sourceValues, __RPC__deref_out_ecount_full_opt( *bufferSize ) BYTE** buffer, __RPC__out DWORD* bufferSize ) const;

        ComBuffer GetBufferFromIPortableDeviceValues( __RPC__in_opt IPortableDeviceValues* sourceValues ) const
        {
            BYTE* buffer = nullptr;
            DWORD bufferSize = 0;
            GetBufferFromIPortableDeviceValues( sourceValues, &buffer, &bufferSize );
            return ComBuffer( buffer, bufferSize );
        }

        ComBuffer GetBufferFromPortableDeviceValues( const PortableDeviceValues& sourceValues ) const
        {
            BYTE* buffer = nullptr;
            DWORD bufferSize = 0;
            GetBufferFromPortableDeviceValues( sourceValues, &buffer, &bufferSize );
            return ComBuffer( buffer, bufferSize );
        }


        void GetSerializedSize( __RPC__in_opt IPortableDeviceValues* sourceValues, __RPC__out DWORD* size ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSerializedSize( sourceValues, size );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        UInt32 GetSerializedSize( __RPC__in_opt IPortableDeviceValues* sourceValues ) const
        {
            DWORD result = 0;
            GetSerializedSize( sourceValues, &result );
            return result;
        }

        inline void GetSerializedSize( const PortableDeviceValues& sourceValues, __RPC__out DWORD* size ) const;

        UInt32 GetSerializedSize( const PortableDeviceValues& sourceValues ) const
        {
            DWORD result = 0;
            GetSerializedSize( sourceValues, &result );
            return result;
        }

    };



    class PortableDeviceValues : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PortableDeviceValues, Unknown, IPortableDeviceValues, IUnknown )

        static WpdSerializer Create( )
        {
            return CoCreateInstanceFromClassId<PortableDeviceValues>( CLSID_PortableDeviceValues );
        }

        void GetCount(__RPC__in DWORD* count ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCount( count );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        UInt32 Count( ) const
        {
            DWORD result = 0;
            GetCount( &result );
            return  result;
        }


        void GetAt(const DWORD index, __RPC__inout_opt PROPERTYKEY* key, __RPC__inout_opt PROPVARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAt( index, key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        std::pair<PROPERTYKEY, PropertyVariant> GetAt( const DWORD index ) const
        {
            std::pair<PROPERTYKEY, PropertyVariant> result{};
            GetAt( index,&result.first, &result.second );
            return result;
        }
        std::pair<PROPERTYKEY, PropertyVariant> At( const DWORD index ) const
        {
            return GetAt( index );
        }
        std::pair<PROPERTYKEY, PropertyVariant> operator[]( size_t index ) const
        {
            return GetAt( static_cast<DWORD>(index) );
        }


        void SetValue( __RPC__in REFPROPERTYKEY key, __RPC__in const PROPVARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetValue( const PROPERTYKEY& key, const PROPVARIANT& value ) const
        {
            SetValue( key, &value );
        }



        void GetValue( __RPC__in REFPROPERTYKEY key, __RPC__out PROPVARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PropertyVariant GetValue( __RPC__in REFPROPERTYKEY key ) const
        {
            PropertyVariant result;
            GetValue( key, &result );
            return result;
        }

        
        void SetStringValue( __RPC__in REFPROPERTYKEY key, __RPC__in LPCWSTR value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetStringValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        void SetStringValue( __RPC__in REFPROPERTYKEY key, const std::wstring& value ) const
        {
            SetStringValue( key, value.c_str( ) );
        }

        void GetStringValue( __RPC__in REFPROPERTYKEY key, __RPC__deref_out_opt LPWSTR* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetStringValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        ComString GetStringValue( __RPC__in REFPROPERTYKEY key ) const
        {
            LPWSTR ptr = nullptr;
            GetStringValue( key, &ptr );
            return ComString( ptr );
        }



        void SetUnsignedIntegerValue(__RPC__in REFPROPERTYKEY key, const ULONG value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetUnsignedIntegerValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetUnsignedIntegerValue( __RPC__in REFPROPERTYKEY key, __RPC__out ULONG* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetUnsignedIntegerValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        UInt32 GetUnsignedIntegerValue( __RPC__in REFPROPERTYKEY key ) const
        {
            ULONG value;
            GetUnsignedIntegerValue( key, &value );
            return value;
        }


        void SetSignedIntegerValue( __RPC__in REFPROPERTYKEY key, const LONG value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSignedIntegerValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetSignedIntegerValue( __RPC__in REFPROPERTYKEY key, __RPC__out LONG* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSignedIntegerValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        Int32 GetSignedIntegerValue( __RPC__in REFPROPERTYKEY key ) const
        {
            LONG value;
            GetSignedIntegerValue( key, &value );
            return value;
        }


        void SetUnsignedLargeIntegerValue( __RPC__in REFPROPERTYKEY key, const ULONGLONG value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetUnsignedLargeIntegerValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetUnsignedLargeIntegerValue( __RPC__in REFPROPERTYKEY key, __RPC__out ULONGLONG* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetUnsignedLargeIntegerValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        UInt64 GetUnsignedLargeIntegerValue( __RPC__in REFPROPERTYKEY key ) const
        {
            ULONGLONG value;
            GetUnsignedLargeIntegerValue( key, &value );
            return value;
        }


        void SetSignedLargeIntegerValue( __RPC__in REFPROPERTYKEY key, const LONGLONG value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetSignedLargeIntegerValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetSignedLargeIntegerValue( __RPC__in REFPROPERTYKEY key, __RPC__out LONGLONG* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSignedLargeIntegerValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        Int64 GetSignedLargeIntegerValue( __RPC__in REFPROPERTYKEY key ) const
        {
            LONGLONG value;
            GetSignedLargeIntegerValue( key, &value );
            return value;
        }

        void SetFloatValue( __RPC__in REFPROPERTYKEY key, const FLOAT value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetFloatValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetFloatValue( __RPC__in REFPROPERTYKEY key, __RPC__out FLOAT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFloatValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        float GetFloatValue( __RPC__in REFPROPERTYKEY key ) const
        {
            float value;
            GetFloatValue( key, &value );
            return value;
        }


        void SetErrorValue( __RPC__in REFPROPERTYKEY key, const HRESULT value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetErrorValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetErrorValue( __RPC__in REFPROPERTYKEY key, __RPC__out HRESULT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetErrorValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        HRESULT GetErrorValue( __RPC__in REFPROPERTYKEY key ) const
        {
            HRESULT value;
            GetErrorValue( key, &value );
            return value;
        }


        void SetKeyValue( __RPC__in REFPROPERTYKEY key, __RPC__in REFPROPERTYKEY value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetKeyValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetKeyValue( __RPC__in REFPROPERTYKEY key, __RPC__out PROPERTYKEY* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetKeyValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PROPERTYKEY GetKeyValue( __RPC__in REFPROPERTYKEY key ) const
        {
            PROPERTYKEY value;
            GetKeyValue( key, &value );
            return value;
        }


        void SetBoolValue( __RPC__in REFPROPERTYKEY key, const BOOL value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetBoolValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetBoolValue( __RPC__in REFPROPERTYKEY key, __RPC__out BOOL* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetBoolValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        BOOL GetBoolValue( __RPC__in REFPROPERTYKEY key ) const
        {
            BOOL value;
            GetBoolValue( key, &value );
            return value;
        }


        void SetIUnknownValue( __RPC__in REFPROPERTYKEY key, __RPC__in_opt IUnknown* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetIUnknownValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetIUnknownValue( __RPC__in REFPROPERTYKEY key, const Unknown& value ) const
        {
            SetIUnknownValue( key, value.GetInterfacePointer( ) );
        }


        void GetIUnknownValue( __RPC__in REFPROPERTYKEY key, __RPC__deref_out_opt IUnknown** value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetIUnknownValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        Unknown GetIUnknownValue( __RPC__in REFPROPERTYKEY key ) const
        {
            IUnknown* punk = nullptr;
            GetIUnknownValue( key, &punk );
            return Unknown( punk );
        }


        void SetGuidValue( __RPC__in REFPROPERTYKEY key, __RPC__in REFGUID value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetGuidValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetGuidValue( __RPC__in REFPROPERTYKEY key, const Guid& value ) const
        {
            SetGuidValue( key, value.AsGuid());
        }

        void GetGuidValue( __RPC__in REFPROPERTYKEY key, __RPC__out GUID* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetGuidValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        Guid GetGuidValue( __RPC__in REFPROPERTYKEY key ) const
        {
            GUID result{};
            GetGuidValue( key, &result );
            return result;
        }


        void SetBufferValue( __RPC__in REFPROPERTYKEY key, __RPC__in_ecount_full( bufferSize ) BYTE* buffer, DWORD bufferSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetBufferValue( key, buffer, bufferSize );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetBufferValue( __RPC__in REFPROPERTYKEY key, __RPC__deref_out_ecount_full_opt( *bufferSize ) BYTE** buffer, __RPC__out DWORD* bufferSize ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetBufferValue( key, buffer, bufferSize );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        ComBuffer GetBufferValue( __RPC__in REFPROPERTYKEY key ) const
        {
            BYTE* buffer = nullptr;
            DWORD bufferSize = 0;
            GetBufferValue( key, &buffer, &bufferSize );
            return ComBuffer( buffer, bufferSize );
        }


        void SetIPortableDeviceValuesValue( __RPC__in REFPROPERTYKEY key, __RPC__in_opt IPortableDeviceValues* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetIPortableDeviceValuesValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetPortableDeviceValuesValue( __RPC__in REFPROPERTYKEY key, const PortableDeviceValues& value ) const
        {
            SetIPortableDeviceValuesValue( key, value.GetInterfacePointer<IPortableDeviceValues>( ) );
        }


        void GetIPortableDeviceValuesValue( __RPC__in REFPROPERTYKEY key, __RPC__deref_out_opt IPortableDeviceValues** value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetIPortableDeviceValuesValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PortableDeviceValues GetPortableDeviceValuesValue( __RPC__in REFPROPERTYKEY key ) const
        {
            IPortableDeviceValues* ptr = nullptr;
            GetIPortableDeviceValuesValue( key, &ptr );
            return PortableDeviceValues( ptr );
        }



        void SetIPortableDevicePropVariantCollectionValue( __RPC__in REFPROPERTYKEY key, __RPC__in_opt IPortableDevicePropVariantCollection* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetIPortableDevicePropVariantCollectionValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        inline void SetPortableDevicePropVariantCollectionValue( __RPC__in REFPROPERTYKEY key, const PortableDevicePropVariantCollection& value ) const;

        void GetIPortableDevicePropVariantCollectionValue( __RPC__in REFPROPERTYKEY key, __RPC__deref_out_opt IPortableDevicePropVariantCollection** value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetIPortableDevicePropVariantCollectionValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        inline PortableDevicePropVariantCollection GetPortableDevicePropVariantCollectionValue( __RPC__in REFPROPERTYKEY key ) const;


        void SetIPortableDeviceKeyCollectionValue( __RPC__in REFPROPERTYKEY key, __RPC__in_opt IPortableDeviceKeyCollection* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetIPortableDeviceKeyCollectionValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void GetIPortableDeviceKeyCollectionValue( __RPC__in REFPROPERTYKEY key, __RPC__deref_out_opt IPortableDeviceKeyCollection** value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetIPortableDeviceKeyCollectionValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetIPortableDeviceValuesCollectionValue( __RPC__in REFPROPERTYKEY key, __RPC__in_opt IPortableDeviceValuesCollection* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetIPortableDeviceValuesCollectionValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        inline void SetPortableDeviceValuesCollectionValue( __RPC__in REFPROPERTYKEY key, const PortableDeviceValuesCollection& value ) const;


        void GetIPortableDeviceValuesCollectionValue( __RPC__in REFPROPERTYKEY key, __RPC__deref_out_opt IPortableDeviceValuesCollection** value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetIPortableDeviceValuesCollectionValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        inline PortableDeviceValuesCollection GetPortableDeviceValuesCollectionValue( __RPC__in REFPROPERTYKEY key ) const;


        void RemoveValue( __RPC__in REFPROPERTYKEY key ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveValue( key );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void CopyValuesFromPropertyStore( __RPC__in_opt IPropertyStore* propertyStore ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CopyValuesFromPropertyStore( propertyStore );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void CopyValuesFromPropertyStore( const PropertyStore& propertyStore ) const
        {
            CopyValuesFromPropertyStore( propertyStore.GetInterfacePointer<IPropertyStore>() );
        }


        void CopyValuesToPropertyStore( __RPC__in_opt IPropertyStore* propertyStore ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->CopyValuesToPropertyStore( propertyStore );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void CopyValuesToPropertyStore( const PropertyStore& propertyStore ) const
        {
            CopyValuesToPropertyStore( propertyStore.GetInterfacePointer<IPropertyStore>( ) );
        }


        HRESULT Clear( void )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clear( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };


    inline PortableDeviceValues WpdSerializer::GetPortableDeviceValuesFromBuffer( __RPC__in_ecount_full( inputBufferLength ) BYTE* inputBuffer, DWORD inputBufferLength ) const
    {
        IPortableDeviceValues* itf = nullptr;
        GetIPortableDeviceValuesFromBuffer( inputBuffer, inputBufferLength, &itf );
        return PortableDeviceValues( itf );
    }

    inline void WpdSerializer::GetBufferFromPortableDeviceValues( const PortableDeviceValues& sourceValues, __RPC__deref_out_ecount_full_opt( *bufferSize ) BYTE** buffer, __RPC__out DWORD* bufferSize ) const
    {
        auto pInterface = GetInterface( );
        auto hr = pInterface->GetBufferFromIPortableDeviceValues( sourceValues.GetInterfacePointer<IPortableDeviceValues>(), buffer, bufferSize );
        if ( FAILED( hr ) )
        {
            CheckHRESULT( hr );
        }
    }

    inline void WpdSerializer::GetSerializedSize( const PortableDeviceValues& sourceValues, __RPC__out DWORD* size ) const
    {
        GetSerializedSize( sourceValues.GetInterfacePointer<IPortableDeviceValues>( ), size );
    }


    class PortableDeviceKeyCollection : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PortableDeviceKeyCollection, Unknown, IPortableDeviceKeyCollection, IUnknown )

        void GetCount( __RPC__in DWORD* count ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCount( count );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        UInt32 Count( ) const
        {
            DWORD result = 0;
            GetCount( &result );
            return  result;
        }

        void GetAt( const DWORD index, __RPC__in PROPERTYKEY* key ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAt( index, key );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PROPERTYKEY GetAt( const DWORD index ) const
        {
            PROPERTYKEY result{};
            GetAt( index, &result );
            return result;
        }
        PROPERTYKEY At( const DWORD index ) const
        {
            return GetAt( index );
        }
        PROPERTYKEY operator[]( size_t index ) const
        {
            return GetAt( static_cast<DWORD>( index ) );
        }



        void Add( __RPC__in REFPROPERTYKEY key ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Add( key );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Clear( void ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clear( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void RemoveAt( const DWORD index ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveAt( index );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };


    class PortableDevicePropVariantCollection : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PortableDevicePropVariantCollection, Unknown, IPortableDevicePropVariantCollection, IUnknown )

        void GetCount( __RPC__in DWORD* count ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCount( count );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        UInt32 Count( ) const
        {
            DWORD result = 0;
            GetCount( &result );
            return  result;
        }

        void GetAt( const DWORD index, __RPC__in PROPVARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAt( index, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PropertyVariant GetAt( const DWORD index ) const
        {
            PropertyVariant result{};
            GetAt( index, &result );
            return result;
        }
        PropertyVariant At( const DWORD index ) const
        {
            return GetAt( index );
        }
        PropertyVariant operator[]( size_t index ) const
        {
            return GetAt( static_cast<DWORD>( index ) );
        }


        void Add( __RPC__in const PROPVARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Add( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void Add( const PropertyVariant& value ) const
        {
            Add( &value );
        }

        void GetType( __RPC__out VARTYPE* type ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetType( type );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        VariantType GetType( ) const
        {
            VARTYPE type;
            GetType( &type );
            return static_cast<VariantType>( type );
        }


        void ChangeType( const VARTYPE vt ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ChangeType( vt );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void ChangeType( const VariantType vt ) const
        {
            ChangeType( static_cast<VARTYPE>( vt ) );
        }

        void Clear( void )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clear( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void RemoveAt( const DWORD index )
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveAt( index );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

    };


    class PortableDeviceValuesCollection : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( PortableDeviceValuesCollection, Unknown, IPortableDeviceValuesCollection, IUnknown )

        void GetCount( __RPC__in DWORD* count ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCount( count );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        UInt32 Count( ) const
        {
            DWORD result = 0;
            GetCount( &result );
            return  result;
        }
        
        void GetAt( const DWORD index, __RPC__deref_out_opt IPortableDeviceValues** values ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAt( index, values );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        
        void Add( __RPC__in_opt IPortableDeviceValues* values ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Add( values );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        
        void Clear( void ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clear( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        
        void RemoveAt( const DWORD index ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveAt( index );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
    };

    inline void PortableDeviceValues::SetPortableDeviceValuesCollectionValue( __RPC__in REFPROPERTYKEY key, const PortableDeviceValuesCollection& value ) const
    {
        SetIPortableDeviceValuesCollectionValue( key, value.GetInterfacePointer<IPortableDeviceValuesCollection>( ) );
    }

    inline PortableDeviceValuesCollection PortableDeviceValues::GetPortableDeviceValuesCollectionValue( __RPC__in REFPROPERTYKEY key ) const
    {
        IPortableDeviceValuesCollection* ptr = nullptr;
        GetIPortableDeviceValuesCollectionValue( key, &ptr );
        return PortableDeviceValuesCollection( ptr );
    }

    inline void PortableDeviceValues::SetPortableDevicePropVariantCollectionValue( __RPC__in REFPROPERTYKEY key, const PortableDevicePropVariantCollection& value ) const
    {
        SetIPortableDevicePropVariantCollectionValue( key, value.GetInterfacePointer<IPortableDevicePropVariantCollection>( ) );
    }

    inline PortableDevicePropVariantCollection PortableDeviceValues::GetPortableDevicePropVariantCollectionValue( __RPC__in REFPROPERTYKEY key ) const
    {
        IPortableDevicePropVariantCollection* ptr = nullptr;
        GetIPortableDevicePropVariantCollectionValue( key, &ptr );
        return PortableDevicePropVariantCollection( ptr );
    }


}


#endif
