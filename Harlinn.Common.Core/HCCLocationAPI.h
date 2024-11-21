#pragma once
#ifndef HARLINN_COMMON_CORE_HCCLOCATIONAPI_H_
#define HARLINN_COMMON_CORE_HCCLOCATIONAPI_H_
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

#include "HCCSensorsAPI.h"

#pragma comment(lib,"locationapi.lib")

namespace Harlinn::Common::Core
{


    class LocationReport;
    class LatLongReport;
    class CivicAddressReport;
    class Location;
    class LocationPower;
    class DefaultLocation;
    class DispLatLongReport;
    class DispCivicAddressReport;
    class LocationReportFactory;
    class LatLongReportFactory;
    class CivicAddressReportFactory;

    class LocationReport : public Unknown
    {
    public:
        using Base = Unknown;
        HCC_COM_STANDARD_METHODS_IMPL( LocationReport, Unknown, ILocationReport, IUnknown )

        void GetSensorID( __RPC__out SENSOR_ID* sensorID ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetSensorID( sensorID );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetTimestamp( __RPC__out SYSTEMTIME* creationTime ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetTimestamp( creationTime );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetValue( __RPC__in REFPROPERTYKEY key, __RPC__out PROPVARIANT* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetValue( key, value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };


    class LatLongReport : public LocationReport
    {
    public:
        using Base = LocationReport;
        HCC_COM_STANDARD_METHODS_IMPL( LatLongReport, LocationReport, ILatLongReport, ILocationReport )

        void GetLatitude( __RPC__out DOUBLE* latitude ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLatitude( latitude );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetLongitude( __RPC__out DOUBLE* longitude ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLatitude( longitude );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetErrorRadius( __RPC__out DOUBLE* errorRadius ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetLatitude( errorRadius );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetAltitude( __RPC__out DOUBLE* altitude ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAltitude( altitude );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetAltitudeError( __RPC__out DOUBLE* altitudeError ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAltitudeError( altitudeError );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };

    class CivicAddressReport : public LocationReport
    {
    public:
        using Base = LocationReport;
        HCC_COM_STANDARD_METHODS_IMPL( CivicAddressReport, LocationReport, ICivicAddressReport, ILocationReport )

        void GetAddressLine1( __RPC__deref_out_opt BSTR *address1) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAddressLine1( address1 );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }
        
        void GetAddressLine2( __RPC__deref_out_opt BSTR *address2) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetAddressLine2( address2 );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }
        
        void GetCity( __RPC__deref_out_opt BSTR *city) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCity( city );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }
        
        void GetStateProvince( __RPC__deref_out_opt BSTR *stateProvince) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetStateProvince( stateProvince );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }
        
        void GetPostalCode( __RPC__deref_out_opt BSTR *postalCode) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetPostalCode( postalCode );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }
        
        void GetCountryRegion( __RPC__deref_out_opt BSTR *countryRegion) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetCountryRegion( countryRegion );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }
        
        void GetDetailLevel( __RPC__out DWORD *detailLevel) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDetailLevel( detailLevel );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }
        
    };


    class Location : public Unknown
    {
    public:
        using Base = Unknown;
        HCC_COM_STANDARD_METHODS_IMPL( Location, Unknown, ILocation, IUnknown )

        void RegisterForReport( __RPC__in_opt ILocationEvents* locationEvents, __RPC__in REFIID reportType, DWORD requestedReportInterval ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RegisterForReport( locationEvents, reportType, requestedReportInterval );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void UnregisterForReport( __RPC__in REFIID reportType ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->UnregisterForReport( reportType );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetReport( __RPC__in REFIID reportType, __RPC__deref_out_opt ILocationReport** locationReport ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetReport( reportType, locationReport );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetReportStatus( __RPC__in REFIID reportType, __RPC__out enum LOCATION_REPORT_STATUS* status ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetReportStatus( reportType, status );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetReportInterval( __RPC__in REFIID reportType, __RPC__out DWORD* milliseconds ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetReportInterval( reportType, milliseconds );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void SetReportInterval( __RPC__in REFIID reportType, DWORD millisecondsRequested ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetReportInterval( reportType, millisecondsRequested );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetDesiredAccuracy( __RPC__in REFIID reportType, __RPC__out enum LOCATION_DESIRED_ACCURACY* desiredAccuracy ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetDesiredAccuracy( reportType, desiredAccuracy );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void SetDesiredAccuracy( __RPC__in REFIID reportType, enum LOCATION_DESIRED_ACCURACY desiredAccuracy ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetDesiredAccuracy( reportType, desiredAccuracy );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void RequestPermissions( __RPC__in_opt HWND parentWindow, __RPC__in_ecount_full( count ) IID* reportTypes, ULONG count, BOOL displayModally ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RequestPermissions( parentWindow, reportTypes, count, displayModally );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };


    class LocationPower : public Unknown
    {
    public:
        using Base = Unknown;
        HCC_COM_STANDARD_METHODS_IMPL( LocationPower, Unknown, ILocationPower, IUnknown )

        void Connect( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Connect( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void Disconnect( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->Disconnect( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };

    class DefaultLocation : public Unknown
    {
    public:
        using Base = Unknown;
        HCC_COM_STANDARD_METHODS_IMPL( DefaultLocation, Unknown, IDefaultLocation, IUnknown )

        void SetReport( __RPC__in REFIID reportType, __RPC__in_opt ILocationReport* locationReport ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->SetReport( reportType, locationReport );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void GetReport( __RPC__in REFIID reportType, __RPC__deref_out_opt ILocationReport** locationReport ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->GetReport( reportType, locationReport );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };


    class LocationEventsSinkImpl : public Com::ObjectBase<LocationEventsSink, ILocationEvents>
    {
    public:
        using Base = Com::ObjectBase<LocationEventsSink, ILocationEvents>;
    private:
        Location location_;

    private:
        virtual HRESULT STDMETHODCALLTYPE OnLocationChanged( __RPC__in REFIID reportType, __RPC__in_opt ILocationReport* locationReport ) override
        {
        }

        virtual HRESULT STDMETHODCALLTYPE OnStatusChanged( __RPC__in REFIID reportType, LOCATION_REPORT_STATUS newStatus ) override
        {
        }

    };

    class DispLatLongReport : public Dispatch
    {
    public:
        using Base = Dispatch;
        HCC_COM_STANDARD_METHODS_IMPL( DispLatLongReport, Dispatch, IDispLatLongReport, IDispatch )

        void get_Latitude( __RPC__out DOUBLE* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Latitude( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_Longitude( __RPC__out DOUBLE* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Longitude( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_ErrorRadius( __RPC__out DOUBLE* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_ErrorRadius( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_Altitude( __RPC__out DOUBLE* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Altitude( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_AltitudeError( __RPC__out DOUBLE* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_AltitudeError( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_Timestamp( __RPC__out DATE* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Timestamp( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };

    class DispCivicAddressReport : public Dispatch
    {
    public:
        using Base = Dispatch;
        HCC_COM_STANDARD_METHODS_IMPL( DispCivicAddressReport, Dispatch, IDispCivicAddressReport, IDispatch )

        void get_AddressLine1( __RPC__deref_out_opt BSTR* address1 ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_AddressLine1( address1 );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_AddressLine2( __RPC__deref_out_opt BSTR* address2 ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_AddressLine2( address2 );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_City( __RPC__deref_out_opt BSTR* city ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_City( city );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_StateProvince( __RPC__deref_out_opt BSTR* stateProvince ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_StateProvince( stateProvince );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_PostalCode( __RPC__deref_out_opt BSTR* postalCode ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_PostalCode( postalCode );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_CountryRegion( __RPC__deref_out_opt BSTR* countryRegion ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_CountryRegion( countryRegion );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_DetailLevel( __RPC__out ULONG* detailLevel ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_DetailLevel( detailLevel );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_Timestamp( __RPC__out DATE* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Timestamp( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };

    class LocationReportFactory : public Dispatch
    {
    public:
        using Base = Dispatch;
        HCC_COM_STANDARD_METHODS_IMPL( LocationReportFactory, Dispatch, ILocationReportFactory, IDispatch )

        void ListenForReports( ULONG requestedReportInterval = 0 ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->ListenForReports( requestedReportInterval );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void StopListeningForReports( ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->StopListeningForReports( );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_Status( __RPC__out ULONG* value ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_Status( value );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_ReportInterval( __RPC__out ULONG* milliseconds ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_ReportInterval( milliseconds );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void put_ReportInterval( ULONG millisecondsRequested ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_ReportInterval( millisecondsRequested );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void get_DesiredAccuracy( __RPC__out ULONG* desiredAccuracy ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_DesiredAccuracy( desiredAccuracy );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void put_DesiredAccuracy( ULONG desiredAccuracy ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->put_DesiredAccuracy( desiredAccuracy );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

        void RequestPermissions( __RPC__in ULONG* windowHandle ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->RequestPermissions( windowHandle );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };

    class LatLongReportFactory : public LocationReportFactory
    {
    public:
        using Base = LocationReportFactory;
        HCC_COM_STANDARD_METHODS_IMPL( LatLongReportFactory, LocationReportFactory, ILatLongReportFactory, ILocationReportFactory )

        void get_LatLongReport( __RPC__deref_out_opt IDispLatLongReport** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_LatLongReport( result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };


    class CivicAddressReportFactory : public LocationReportFactory
    {
    public:
        using Base = LocationReportFactory;
        HCC_COM_STANDARD_METHODS_IMPL( CivicAddressReportFactory, LocationReportFactory, ICivicAddressReportFactory, ILocationReportFactory )

        void get_CivicAddressReport( __RPC__deref_out_opt IDispCivicAddressReport** result ) const
        {
            auto pInterface = GetInterface( );
            auto hr = pInterface->get_CivicAddressReport( result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr, pInterface );
            }
        }

    };

    class _ILatLongReportFactoryEvents_Sink : public IDispatch
    {
    };

    class _ICivicAddressReportFactoryEvents_Sink : public IDispatch
    {
    };







}



#endif
