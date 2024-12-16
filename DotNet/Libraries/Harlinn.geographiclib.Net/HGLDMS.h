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

#pragma managed(push)
#include <GeographicLib/DMS.hpp>
#pragma managed(pop)

#include "HGLUtility.h"

namespace Harlinn::GeographicLib::Net
{
    public enum class DMSFlags
    {
        /**
         * No indicator present.
         * @hideinitializer
         **********************************************************************/
        None = ::GeographicLib::DMS::NONE,
        /**
         * Latitude indicator (N/S) present.
         * @hideinitializer
         **********************************************************************/
        Latitude = ::GeographicLib::DMS::LATITUDE,
        /**
         * Longitude indicator (E/W) present.
         * @hideinitializer
         **********************************************************************/
        Longitude = ::GeographicLib::DMS::LONGITUDE,
        /**
         * Used in Encode to indicate output of an azimuth in [000, 360) with no
         * letter indicator.
         * @hideinitializer
         **********************************************************************/
        Azimuth = ::GeographicLib::DMS::AZIMUTH,
        /**
         * Used in Encode to indicate output of a plain number.
         * @hideinitializer
         **********************************************************************/
        number = ::GeographicLib::DMS::NUMBER,
    };

    public enum class DMSComponent
    {
        /**
         * Trailing unit is degrees.
         * @hideinitializer
         **********************************************************************/
        DEGREE = ::GeographicLib::DMS::DEGREE,
        /**
         * Trailing unit is arc minutes.
         * @hideinitializer
         **********************************************************************/
        MINUTE = ::GeographicLib::DMS::MINUTE,
        /**
         * Trailing unit is arc seconds.
         * @hideinitializer
         **********************************************************************/
        SECOND = ::GeographicLib::DMS::SECOND,
    };


    public ref class DMS
    {


    public:
        static double Decode( System::String^ string, [ System::Runtime::InteropServices::Out ] DMSFlags% flag )
        {
            try
            {
                auto dms = ToUtf8( string );
                ::GeographicLib::DMS::flag lflag;
                auto result = ::GeographicLib::DMS::Decode( dms, lflag );
                flag = static_cast< DMSFlags >( lflag );
                return result;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static double Decode( double d, double m, double s )
        {
            return ::GeographicLib::DMS::Decode( d, m, s );
        }

        void DecodeLatLon( System::String^ dmsa, System::String^ dmsb, [ System::Runtime::InteropServices::Out ] double% lat, [ System::Runtime::InteropServices::Out ] double% lon, bool longFirst )
        {
            try
            {
                auto ldmsa = ToUtf8( dmsa );
                auto ldmsb = ToUtf8( dmsb );
                double llat = 0;
                double llon = 0;
                ::GeographicLib::DMS::DecodeLatLon( ldmsa, ldmsb, llat, llon, longFirst );
                lat = llat;
                lon = llon;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        void DecodeLatLon( System::String^ dmsa, System::String^ dmsb, [ System::Runtime::InteropServices::Out ] double% lat, [ System::Runtime::InteropServices::Out ] double% lon )
        {
            try
            {
                auto ldmsa = ToUtf8( dmsa );
                auto ldmsb = ToUtf8( dmsb );
                double llat = 0;
                double llon = 0;
                ::GeographicLib::DMS::DecodeLatLon( ldmsa, ldmsb, llat, llon, false );
                lat = llat;
                lon = llon;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static double DecodeAngle( System::String^ string )
        {
            try
            {
                auto str = ToUtf8( string );
                return ::GeographicLib::DMS::DecodeAngle( str );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static double DecodeAzimuth( System::String^ string )
        {
            try
            {
                auto str = ToUtf8( string );
                return ::GeographicLib::DMS::DecodeAzimuth( str );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static String^ Encode( double angle, DMSComponent trailing, unsigned prec, DMSFlags ind, wchar_t dmssep )
        {
            try
            {
                auto str = ::GeographicLib::DMS::Encode( angle, static_cast< ::GeographicLib::DMS::component >( trailing ), prec, static_cast< ::GeographicLib::DMS::flag >( ind ), static_cast< char >( dmssep ) );
                return FromUtf8( str );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static String^ Encode( double angle, DMSComponent trailing, unsigned prec, DMSFlags ind )
        {
            try
            {
                auto str = ::GeographicLib::DMS::Encode( angle, static_cast< ::GeographicLib::DMS::component >( trailing ), prec, static_cast< ::GeographicLib::DMS::flag >( ind ) );
                return FromUtf8( str );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static String^ Encode( double angle, DMSComponent trailing, unsigned prec )
        {
            try
            {
                auto str = ::GeographicLib::DMS::Encode( angle, static_cast< ::GeographicLib::DMS::component >( trailing ), prec );
                return FromUtf8( str );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static String^ Encode( double angle, unsigned prec, DMSFlags ind, wchar_t dmssep )
        {
            try
            {
                auto str = ::GeographicLib::DMS::Encode( angle, prec, static_cast< ::GeographicLib::DMS::flag >( ind ), static_cast< char >( dmssep ) );
                return FromUtf8( str );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static String^ Encode( double angle, unsigned prec, DMSFlags ind )
        {
            try
            {
                auto str = ::GeographicLib::DMS::Encode( angle, prec, static_cast< ::GeographicLib::DMS::flag >( ind ) );
                return FromUtf8( str );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static String^ Encode( double angle, unsigned prec )
        {
            try
            {
                auto str = ::GeographicLib::DMS::Encode( angle, prec );
                return FromUtf8( str );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        static void Encode( double angle, [ System::Runtime::InteropServices::Out ] double% d, [ System::Runtime::InteropServices::Out ] double% m )
        {
            double ld, lm;
            ::GeographicLib::DMS::Encode( angle, ld, lm );
            d = ld;
            m = lm;
        }

        static void Encode( double angle, [ System::Runtime::InteropServices::Out ] double% d, [ System::Runtime::InteropServices::Out ] double% m, [ System::Runtime::InteropServices::Out ] double% s )
        {
            double ld, lm, ls;
            ::GeographicLib::DMS::Encode( angle, ld, lm, ls );
            d = ld;
            m = lm;
            s = ls;
        }
    };
}

