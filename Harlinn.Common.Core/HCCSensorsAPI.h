#pragma once
#ifndef HARLINN_COMMON_CORE_HCCSENSORSAPI_H_
#define HARLINN_COMMON_CORE_HCCSENSORSAPI_H_
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

#include <HCCDef.h>
#include <HCCCom.h>
#include <HCCComImpl.h>
#include <HCCException.h>
#include <HCCVariant.h>
#include <HCCPropSys.h>
#include <HCCPortableDeviceTypes.h>

#include <Sensors.h>


#pragma comment(lib,"sensorsapi.lib")


namespace Harlinn::Common::Core
{

    class SensorManager;
    class LocationPermissions;
    class SensorCollection;
    class Sensor;
    class SensorDataReport;
    class SensorManagerEvents;
    class SensorEvents;

    enum class RequestPermissionsResult
    {

        Ok,
        /// <summary>
        /// The user chose to disable the sensors.
        /// </summary>
        AccessDenied,
        /// <summary>
        /// The user canceled the dialog box or refused elevation of permission to show the dialog box.
        /// </summary>
        Cancelled
    };

    /// <summary>
    /// Provides methods for discovering and retrieving available sensors and a method to request sensor manager events.
    /// </summary>
    class SensorManager : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( SensorManager, Unknown, ISensorManager, IUnknown )

        static SensorManager Create( )
        {
            return CoCreateInstanceFromClassId<SensorManager>( CLSID_SensorManager );
        }

        /// <summary>
        /// Retrieves a collection containing all sensors associated with the specified category.
        /// </summary>
        /// <param name="sensorCategory">ID of the sensor category to retrieve.</param>
        /// <param name="sensors">Address of an ISensorCollection interface pointer that receives a pointer to the sensor collection requested.</param>
        void GetSensorsByCategory( __RPC__in REFSENSOR_CATEGORY_ID sensorCategory, __RPC__deref_out_opt ISensorCollection** sensors ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSensorsByCategory( sensorCategory, sensors );
            if ( FAILED( hr ) )
            {
                if ( hr != HRESULT_FROM_WIN32( ERROR_NOT_FOUND ) )
                {
                    CheckHRESULT( hr );
                }
                else
                {
                    *sensors = nullptr;
                }
            }
        }

        /// <summary>
        /// Retrieves a collection containing all sensors associated with the specified category.
        /// </summary>
        /// <param name="sensorCategory">ID of the sensor category to retrieve.</param>
        /// <returns>A SensorCollection containing the requested sensors.</returns>
        inline SensorCollection GetSensorsByCategory( __RPC__in REFSENSOR_CATEGORY_ID sensorCategory ) const;

        /// <summary>
        /// Retrieves a collection containing all sensors associated with the specified type.
        /// </summary>
        /// <param name="sensorType">ID of the type of sensors to retrieve.</param>
        /// <param name="sensors">Address of an ISensorCollection interface pointer that receives the pointer to the sensor collection requested.</param>
        void GetSensorsByType( __RPC__in REFSENSOR_TYPE_ID sensorType, __RPC__deref_out_opt ISensorCollection** sensors ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSensorsByType( sensorType, sensors );
            if ( FAILED( hr ) )
            {
                if ( hr != HRESULT_FROM_WIN32( ERROR_NOT_FOUND ) )
                {
                    CheckHRESULT( hr );
                }
                else
                {
                    *sensors = nullptr;
                }
            }
        }
        
        /// <summary>
        /// Retrieves a collection containing all sensors associated with the specified type.
        /// </summary>
        /// <param name="sensorType">ID of the type of sensors to retrieve.</param>
        /// <returns>A SensorCollection containing the requested sensors.</returns>
        inline SensorCollection GetSensorsByType( __RPC__in REFSENSOR_TYPE_ID sensorType ) const;

        /// <summary>
        /// Retrieves a pointer to the specified sensor.
        /// </summary>
        /// <param name="sensorID">The ID of the sensor to retrieve.</param>
        /// <param name="sensor">Address of an ISensor interface pointer that receives a pointer to the requested sensor. Will be NULL if the requested sensor cannot be found.</param>
        void GetSensorByID( __RPC__in REFSENSOR_ID sensorID, __RPC__deref_out_opt ISensor** sensor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSensorByID( sensorID, sensor );
            if ( FAILED( hr ) )
            {
                if ( hr != HRESULT_FROM_WIN32( ERROR_NOT_FOUND ) )
                {
                    CheckHRESULT( hr );
                }
                else
                {
                    *sensor = nullptr;
                }
            }
        }

        /// <summary>
        /// Retrieves the specified sensor.
        /// </summary>
        /// <param name="sensorID">The ID of the sensor to retrieve.</param>
        /// <returns>The requested sensor.</returns>
        inline Sensor GetSensorByID( __RPC__in REFSENSOR_ID sensorID ) const;
        
        void SetEventSink( __RPC__in_opt ISensorManagerEvents *eventSink ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetEventSink( eventSink );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        
        /// <summary>
        /// Opens a system dialog box to request user permission to access sensor data.
        /// </summary>
        /// <param name="parentWindow"></param>
        /// <param name="sensors"></param>
        /// <param name="displayModally"></param>
        RequestPermissionsResult RequestPermissions( __RPC__in HWND parentWindow, __RPC__in_opt ISensorCollection *sensors, BOOL displayModally = true ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RequestPermissions( parentWindow, sensors, displayModally );
            if ( FAILED( hr ) )
            {
                if ( hr == HRESULT_FROM_WIN32( ERROR_ACCESS_DENIED ) )
                {
                    return RequestPermissionsResult::AccessDenied;
                }
                else if ( hr == HRESULT_FROM_WIN32( ERROR_CANCELLED ) )
                {
                    return RequestPermissionsResult::Cancelled;
                }
                else
                {
                    CheckHRESULT( hr );
                }
            }
            return RequestPermissionsResult::Ok;
        }

        inline RequestPermissionsResult RequestPermissions( __RPC__in HWND parentWindow, const SensorCollection& sensors, BOOL displayModally = true ) const;
        
    };

    class LocationPermissions : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( LocationPermissions, Unknown, ILocationPermissions, IUnknown )

        void GetGlobalLocationPermission( __RPC__out BOOL* enabled ) const
        {
        }

        virtual HRESULT CheckLocationCapability( DWORD clientThreadId ) const
        {
        }

    };


    class SensorCollection : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( SensorCollection, Unknown, ISensorCollection, IUnknown )

        void GetAt( ULONG index, __RPC__deref_out_opt ISensor** sensor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAt( index, sensor );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        inline Sensor GetAt( const DWORD index ) const;

        inline Sensor At( const DWORD index ) const;
        inline Sensor operator[]( size_t index ) const;


        void GetCount( __RPC__out ULONG* count ) const
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

        void Add( __RPC__in_opt ISensor* sensor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Add( sensor );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        inline void Add( const Sensor& sensor ) const;


        /// <summary>
        /// Removes a sensor from the collection.
        /// </summary>
        /// <param name="">The sensor is specified by a pointer to the ISensor interface to be removed.</param>
        /// <returns>True if the sensor was removed from the collection, false if the specified sensor is not part of the collection.</returns>
        bool Remove( __RPC__in_opt ISensor* sensor ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Remove( sensor );
            if ( FAILED( hr ) )
            {
                if ( hr == E_INVALIDARG )
                {
                    return false;
                }
                CheckHRESULT( hr );
            }
            return true;
        }

        /// <summary>
        /// Removes a sensor from the collection. The sensor to be removed is specified by its ID.
        /// </summary>
        /// <param name="pFriendlyName"></param>
        /// <returns>True if the sensor was removed from the collection, false if the specified sensor is not part of the collection.</returns>
        bool RemoveByID( __RPC__in REFSENSOR_ID sensorID ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RemoveByID( sensorID );
            if ( FAILED( hr ) )
            {
                if ( hr == E_INVALIDARG )
                {
                    return false;
                }
                CheckHRESULT( hr );
            }
            return true;
        }

        /// <summary>
        /// Empties the sensor collection.
        /// </summary>
        void Clear( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Clear( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

    };

    inline SensorCollection SensorManager::GetSensorsByCategory( __RPC__in REFSENSOR_CATEGORY_ID sensorCategory ) const
    {
        ISensorCollection* ptr = nullptr;
        GetSensorsByCategory( sensorCategory, &ptr );
        return SensorCollection( ptr );
    }

    inline SensorCollection SensorManager::GetSensorsByType( __RPC__in REFSENSOR_TYPE_ID sensorType ) const
    {
        ISensorCollection* ptr = nullptr;
        GetSensorsByType( sensorType, &ptr );
        return SensorCollection( ptr );
    }

    inline RequestPermissionsResult SensorManager::RequestPermissions( __RPC__in HWND parentWindow, const SensorCollection& sensors, BOOL displayModally ) const
    {
        return RequestPermissions( parentWindow, sensors.GetInterfacePointer<ISensorCollection>(), displayModally );
    }



    /// <summary>
    /// Represents a sensor.
    /// </summary>
    class Sensor : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( Sensor, Unknown, ISensor, IUnknown )

        void GetID( __RPC__out SENSOR_ID *id) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetID( id );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        SENSOR_ID Id( ) const
        {
            SENSOR_ID result{};
            GetID( &result );
            return result;
        }

        
        void GetCategory( __RPC__out SENSOR_CATEGORY_ID *sensorCategory) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCategory( sensorCategory );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        SENSOR_CATEGORY_ID Category( ) const
        {
            SENSOR_CATEGORY_ID result{};
            GetCategory( &result );
            return result;
        }

        
        void GetType( __RPC__out SENSOR_TYPE_ID *sensorType) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetType( sensorType );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        SENSOR_TYPE_ID Type( ) const
        {
            SENSOR_TYPE_ID result{};
            GetType( &result );
            return result;
        }

        
        void GetFriendlyName( __RPC__deref_out_opt BSTR *friendlyName) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetFriendlyName( friendlyName );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        SysString FriendlyName( ) const
        {
            BSTR ptr = nullptr;
            GetFriendlyName( &ptr );
            return SysString( ptr, true );
        }
        
        void GetProperty( __RPC__in REFPROPERTYKEY key, __RPC__out PROPVARIANT *property) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetProperty( key, property );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PropertyVariant GetProperty( __RPC__in REFPROPERTYKEY key ) const
        {
            PropertyVariant result;
            GetProperty( key, &result );
            return result;
        }

        
        void GetProperties( __RPC__in_opt IPortableDeviceKeyCollection *keys, __RPC__deref_out_opt IPortableDeviceValues **properties) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetProperties( keys, properties );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PortableDeviceValues Properties( IPortableDeviceKeyCollection* keys = nullptr ) const
        {
            IPortableDeviceValues* ptr = nullptr;
            GetProperties( keys, &ptr );
            return PortableDeviceValues( ptr );
        }

        PortableDeviceValues Properties( const PortableDeviceKeyCollection& keys ) const
        {
            return Properties( keys.GetInterfacePointer<IPortableDeviceKeyCollection>( ) );
        }

        
        void GetSupportedDataFields( __RPC__deref_out_opt IPortableDeviceKeyCollection **dataFields) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSupportedDataFields( dataFields );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PortableDeviceKeyCollection SupportedDataFields( ) const
        {
            IPortableDeviceKeyCollection* ptr = nullptr;
            GetSupportedDataFields( &ptr );
            return PortableDeviceKeyCollection( ptr );
        }

        
        void SetProperties( __RPC__in_opt IPortableDeviceValues *properties, __RPC__deref_out_opt IPortableDeviceValues **results) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetProperties( properties, results );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PortableDeviceValues SetProperties( __RPC__in_opt IPortableDeviceValues* properties ) const
        {
            IPortableDeviceValues* ptr = nullptr;
            SetProperties( properties, &ptr );
            return PortableDeviceValues( ptr );
        }

        PortableDeviceValues SetProperties( const PortableDeviceValues& properties ) const
        {
            return SetProperties( properties.GetInterfacePointer<IPortableDeviceValues>() );
        }


        
        void SupportsDataField( __RPC__in REFPROPERTYKEY key, __RPC__out VARIANT_BOOL *isSupported) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SupportsDataField( key, isSupported );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        bool SupportsDataField( __RPC__in REFPROPERTYKEY key ) const
        {
            VARIANT_BOOL val = VARIANT_FALSE;
            SupportsDataField( key, &val );
            return val != VARIANT_FALSE;
        }

        
        void GetState( __RPC__out SensorState *state) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetState( state );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        SensorState State( ) const
        {
            SensorState sensorState;
            GetState( &sensorState );
            return sensorState;
        }

        
        void GetData( __RPC__deref_out_opt ISensorDataReport **dataReport) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetData( dataReport );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        inline SensorDataReport Data( ) const;
        
        void SupportsEvent( __RPC__in REFGUID eventGuid, __RPC__out VARIANT_BOOL *isSupported) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SupportsEvent( eventGuid, isSupported );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        bool SupportsEvent( __RPC__in REFGUID eventGuid ) const
        {
            VARIANT_BOOL val = VARIANT_FALSE;
            SupportsEvent( eventGuid, &val );
            return val != VARIANT_FALSE;
        }

        
        void GetEventInterest( __RPC__deref_out_ecount_full_opt(*count) GUID **values, __RPC__out ULONG *count) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetEventInterest( values, count );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        std::vector<Guid> GetEventInterest( ) const
        {
            GUID* values = nullptr;
            ULONG count = 0;
            GetEventInterest(&values, &count );
            std::vector<Guid> result;
            if ( values )
            {
                if ( count )
                {
                    result.resize( count );
                    for ( ULONG i = 0; i < count; i++ )
                    {
                        result[i] = values[i];
                    }
                }
                CoTaskMemFree( values );
            }
            return result;
        }

        
        void SetEventInterest( __RPC__in_ecount_full_opt(count) GUID * eventGuids, ULONG count) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetEventInterest( eventGuids, count );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        void SetEventInterest( const std::vector<Guid>& eventGuids ) const
        {
            SetEventInterest( const_cast<GUID*>( reinterpret_cast<const GUID*>( eventGuids.data( ) ) ), static_cast<ULONG>( eventGuids.size( ) ) );
        }

        
        virtual HRESULT SetEventSink( __RPC__in_opt ISensorEvents *eventSink) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetEventSink( eventSink );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }
        
    };

    inline Sensor SensorManager::GetSensorByID( __RPC__in REFSENSOR_ID sensorID ) const
    {
        ISensor* ptr = nullptr;
        GetSensorByID( sensorID, &ptr );
        return Sensor( ptr );
    }

    inline Sensor SensorCollection::GetAt( const DWORD index ) const
    {
        ISensor* ptr = nullptr;
        GetAt( index, &ptr );
        return Sensor( ptr );
    }

    inline Sensor SensorCollection::At( const DWORD index ) const
    {
        return GetAt( index );
    }
    inline Sensor SensorCollection::operator[]( size_t index ) const
    {
        return GetAt( static_cast<DWORD>( index ) );
    }

    inline void SensorCollection::Add( const Sensor& sensor ) const
    {
        Add( sensor.GetInterfacePointer<ISensor>() );
    }


    class SensorDataReport : public Unknown
    {
    public:
        typedef Unknown Base;
        HCC_COM_STANDARD_METHODS_IMPL( SensorDataReport, Unknown, ISensorDataReport, IUnknown )

        void GetTimestamp( __RPC__out SYSTEMTIME* timeStamp ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetTimestamp( timeStamp );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        DateTime GetTimestamp( ) const
        {
            SYSTEMTIME systemtime{};
            GetTimestamp( &systemtime );
            FILETIME fileTime;
            SystemTimeToFileTime( &systemtime, &fileTime );
            return DateTime::FromFileTime( fileTime );
        }


        void GetSensorValue( __RPC__in REFPROPERTYKEY key, __RPC__out PROPVARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSensorValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PropertyVariant GetSensorValue( __RPC__in REFPROPERTYKEY key ) const
        {
            PropertyVariant result;
            GetSensorValue( key, &result );
            return result;
        }


        void GetSensorValues( __RPC__in_opt IPortableDeviceKeyCollection* keys, __RPC__deref_out_opt IPortableDeviceValues** values ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSensorValues( keys, values );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
        }

        PortableDeviceValues GetSensorValues( __RPC__in_opt IPortableDeviceKeyCollection* keys ) const
        {
            IPortableDeviceValues* ptr = nullptr;
            GetSensorValues( keys, &ptr );
            return PortableDeviceValues( ptr );
        }

        PortableDeviceValues GetSensorValues( const PortableDeviceKeyCollection& keys ) const
        {
            return GetSensorValues( keys.GetInterfacePointer<IPortableDeviceKeyCollection>() );
        }


    };

    inline SensorDataReport Sensor::Data( ) const
    {
        ISensorDataReport* ptr = nullptr;
        GetData( &ptr );
        return SensorDataReport( ptr );
    }

    class SensorManagerEventSinkBase : public Com::ObjectBase<SensorManagerEventSinkBase, ISensorManagerEvents>
    {
        Core::SensorManager sensorManager_;
    public:
        using Base = Com::ObjectBase<SensorManagerEventSinkBase, ISensorManagerEvents>;

        SensorManagerEventSinkBase( const SensorManager& sensorManager )
            : sensorManager_( sensorManager )
        { }

        SensorManagerEventSinkBase( ISensorManager* sensorManager, bool addRef )
            : sensorManager_( sensorManager, addRef )
        { }

        const Core::SensorManager& SensorManager( ) const
        {
            return sensorManager_;
        }
    private:
        virtual HRESULT STDMETHODCALLTYPE OnSensorEnter( __RPC__in_opt ISensor* pSensor, SensorState state ) override
        {
            bool failed = true;
            Sensor sensor( pSensor, true );
            try
            {
                this->HandleOnSensorEnter( sensor, state );
                failed = false;
            }
            HCC_CATCH_ALL_AND_REPORT_EXCEPTION
            return failed == false ? S_OK : E_FAIL;
        }
    protected:
        virtual void HandleOnSensorEnter( const Sensor& sensor, SensorState state )
        {
        }
    };

    class SensorManagerEventSink : public SensorManagerEventSinkBase
    {
    public:
        using Base = SensorManagerEventSinkBase;

        boost::signals2::signal<void( const Sensor& sensor, SensorState state )> OnSensorEnter;

        SensorManagerEventSink( const Core::SensorManager& sensorManager )
            : Base( sensorManager )
        { }

        SensorManagerEventSink( ISensorManager* sensorManager, bool addRef )
            : Base( sensorManager, addRef )
        { }
    protected:
        virtual void HandleOnSensorEnter( const Sensor& sensor, SensorState state ) override
        {
            OnSensorEnter( sensor, state );
        }
    };

    class SensorEventSinkBase : public Com::ObjectBase<SensorEventSinkBase, ISensorEvents>
    {
        Sensor sensor_;
    public:
        using Base = Com::ObjectBase<SensorEventSinkBase, ISensorEvents>;

        SensorEventSinkBase( const Core::Sensor& sensor )
            : sensor_( sensor )
        {
        }

        SensorEventSinkBase( ISensor* sensor, bool addRef )
            : sensor_( sensor, addRef )
        {
        }

        const Core::Sensor& Sensor( ) const
        {
            return sensor_;
        }
    private:
        virtual HRESULT STDMETHODCALLTYPE OnStateChanged( __RPC__in_opt ISensor* pSensor, SensorState state ) override
        {
            bool failed = true;
            Core::Sensor sensor( pSensor, true );
            try
            {
                this->HandleOnStateChanged( sensor, state );
                failed = false;
            }
            HCC_CATCH_ALL_AND_REPORT_EXCEPTION
            return failed == false ? S_OK : E_FAIL;
        }

        virtual HRESULT STDMETHODCALLTYPE OnDataUpdated( __RPC__in_opt ISensor* pSensor, __RPC__in_opt ISensorDataReport* pNewData ) override
        {
            bool failed = true;
            Core::Sensor sensor( pSensor, true );
            SensorDataReport sensorDataReport( pNewData, true );
            try
            {
                this->HandleOnDataUpdated( sensor, sensorDataReport );
                failed = false;
            }
            HCC_CATCH_ALL_AND_REPORT_EXCEPTION
            return failed == false ? S_OK : E_FAIL;
        }

        virtual HRESULT STDMETHODCALLTYPE OnEvent( __RPC__in_opt ISensor* pSensor, __RPC__in REFGUID eventID, __RPC__in_opt IPortableDeviceValues* pEventData ) override
        {
            bool failed = true;
            Core::Sensor sensor( pSensor, true );
            PortableDeviceValues eventData( pEventData, true );
            try
            {
                this->HandleOnEvent( sensor, eventID, eventData );
                failed = false;
            }
            HCC_CATCH_ALL_AND_REPORT_EXCEPTION
            return failed == false ? S_OK : E_FAIL;
        }

        virtual HRESULT STDMETHODCALLTYPE OnLeave( __RPC__in REFSENSOR_ID ID ) override
        {
            bool failed = true;
            try
            {
                this->HandleOnLeave( ID );
                failed = false;
            }
            HCC_CATCH_ALL_AND_REPORT_EXCEPTION
            return failed == false ? S_OK : E_FAIL;
        }
    protected:
        void HandleOnStateChanged( const Core::Sensor& sensor, SensorState state )
        {
        }

        void HandleOnDataUpdated( const Core::Sensor& sensor, const SensorDataReport& newData )
        {
        }

        void HandleOnEvent( const Core::Sensor& sensor, const Guid& eventID, const PortableDeviceValues& eventData )
        {
        }

        void HandleOnLeave( const Guid& sensorId )
        {
        }
    };

    class SensorEventSink : public SensorEventSinkBase
    {
    public:
        boost::signals2::signal<void( const Core::Sensor& sensor, SensorState state )> OnStateChanged;
        boost::signals2::signal<void( const Core::Sensor& sensor, const SensorDataReport& newData )> OnDataUpdated;
        boost::signals2::signal<void( const Core::Sensor& sensor, const Guid& eventID, const PortableDeviceValues& eventData )> OnEvent;
        boost::signals2::signal<void( const Guid& sensorId )> OnLeave;

        using Base = SensorEventSinkBase;

        SensorEventSink( const Core::Sensor& sensor )
            : Base( sensor )
        {
        }

        SensorEventSink( ISensor* sensor, bool addRef )
            : Base( sensor, addRef )
        {
        }
    protected:
        void HandleOnStateChanged( const Core::Sensor& sensor, SensorState state )
        {
            OnStateChanged( sensor, state );
        }

        void HandleOnDataUpdated( const Core::Sensor& sensor, const SensorDataReport& newData )
        {
            OnDataUpdated( sensor, newData );
        }

        void HandleOnEvent( const Core::Sensor& sensor, const Guid& eventID, const PortableDeviceValues& eventData )
        {
            OnEvent( sensor, eventID, eventData );
        }

        void HandleOnLeave( const Guid& sensorId )
        {
            OnLeave( sensorId );
        }
    };




}


#endif

