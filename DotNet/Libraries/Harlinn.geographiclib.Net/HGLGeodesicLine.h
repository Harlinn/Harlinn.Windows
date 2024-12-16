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
#include <GeographicLib/GeodesicLine.hpp>
#pragma managed(pop)

#include "HGLGeoPoint.h"
#include "HGLGeodesic.h"

namespace Harlinn::GeographicLib::Net
{
    /**
     * Bit masks for what calculations to do.  They signify to the
     * GeodesicLine::GeodesicLine constructor and to Geodesic::Line what
     * capabilities should be included in the GeodesicLine object.  This is
     * merely a duplication of Geodesic::mask.
     **********************************************************************/
    [ System::Flags ]
        public enum class GeodesicLineMask : unsigned
    {
        /**
         * No capabilities, no output.
         * @hideinitializer
         **********************************************************************/
        None = ::GeographicLib::Geodesic::NONE,
        /**
         * Calculate latitude \e lat2.  (It's not necessary to include this as a
         * capability to GeodesicLine because this is included by default.)
         * @hideinitializer
         **********************************************************************/
        Latitude = ::GeographicLib::Geodesic::LATITUDE,
        /**
         * Calculate longitude \e lon2.
         * @hideinitializer
         **********************************************************************/
        Longitude = ::GeographicLib::Geodesic::LONGITUDE,
        /**
         * Calculate azimuths \e azi1 and \e azi2.  (It's not necessary to
         * include this as a capability to GeodesicLine because this is included
         * by default.)
         * @hideinitializer
         **********************************************************************/
        Azimuth = ::GeographicLib::Geodesic::AZIMUTH,
        /**
         * Calculate distance \e s12.
         * @hideinitializer
         **********************************************************************/
        Distance = ::GeographicLib::Geodesic::DISTANCE,
        /**
         * A combination of the common capabilities: GeodesicLine::LATITUDE,
         * GeodesicLine::LONGITUDE, GeodesicLine::AZIMUTH, GeodesicLine::DISTANCE.
         * @hideinitializer
         **********************************************************************/
        Standard = ::GeographicLib::Geodesic::STANDARD,
        /**
         * Allow distance \e s12 to be used as input in the direct geodesic
         * problem.
         * @hideinitializer
         **********************************************************************/
        DistanceIn = ::GeographicLib::Geodesic::DISTANCE_IN,
        /**
         * Calculate reduced length \e m12.
         * @hideinitializer
         **********************************************************************/
        ReducedLength = ::GeographicLib::Geodesic::REDUCEDLENGTH,
        /**
         * Calculate geodesic scales \e M12 and \e M21.
         * @hideinitializer
         **********************************************************************/
        GeodesicScale = ::GeographicLib::Geodesic::GEODESICSCALE,
        /**
         * Calculate area \e S12.
         * @hideinitializer
         **********************************************************************/
        Area = ::GeographicLib::Geodesic::AREA,
        /**
         * Unroll \e lon2 in the direct calculation.
         * @hideinitializer
         **********************************************************************/
        LongUnroll = ::GeographicLib::Geodesic::LONG_UNROLL,
        /**
         * All capabilities, calculate everything.  (GeodesicLine::LONG_UNROLL is
         * not included in this mask.)
         * @hideinitializer
         **********************************************************************/
        All = ::GeographicLib::Geodesic::ALL,
    };

    public ref class GeodesicLine
    {
        ::GeographicLib::GeodesicLine* impl_ = nullptr;
        bool _disposed = false;
    public:
        GeodesicLine( ::GeographicLib::GeodesicLine* other )
        {
            impl_ = new ::GeographicLib::GeodesicLine( *other );
        }
    public:
        GeodesicLine( double lat1, double lon1, double azi1 )
        {
            impl_ = new ::GeographicLib::GeodesicLine( ::GeographicLib::Geodesic::WGS84( ), lat1, lon1, azi1, static_cast< unsigned >( GeodesicLineMask::All ) );
        }

        GeodesicLine( double lat1, double lon1, double azi1, GeodesicLineMask caps )
        {
            impl_ = new ::GeographicLib::GeodesicLine( ::GeographicLib::Geodesic::WGS84( ), lat1, lon1, azi1, static_cast< unsigned >( caps ) );
        }

        GeodesicLine( GeoPoint^ startPosition, double azi1 )
        {
            impl_ = new ::GeographicLib::GeodesicLine( ::GeographicLib::Geodesic::WGS84( ), startPosition->Latitude, startPosition->Longitude, azi1, static_cast< unsigned >( GeodesicLineMask::All ) );
        }

        GeodesicLine( GeoPoint^ startPosition, double azi1, GeodesicLineMask caps )
        {
            impl_ = new ::GeographicLib::GeodesicLine( ::GeographicLib::Geodesic::WGS84( ), startPosition->Latitude, startPosition->Longitude, azi1, static_cast< unsigned >( caps ) );
        }


        ~GeodesicLine( )
        {
            if ( !_disposed )
            {
                _disposed = true;
                delete impl_;
            }
        }

        !GeodesicLine( )
        {
            if ( !_disposed )
            {
                _disposed = true;
                delete impl_;
            }
        }


        void Position( double distance, [ Runtime::InteropServices::Out ] double% latitude, [ Runtime::InteropServices::Out ] double% longitude, [ Runtime::InteropServices::Out ] double% forwardAzimuth )
        {
            double lat;
            double lon;
            double azi;
            impl_->Position( distance, lat, lon, azi );
            latitude = lat;
            longitude = lon;
            forwardAzimuth = azi;
        }

        void Position( double distance, [ Runtime::InteropServices::Out ] double% latitude, [ Runtime::InteropServices::Out ] double% longitude )
        {
            double lat;
            double lon;
            impl_->Position( distance, lat, lon );
            latitude = lat;
            longitude = lon;
        }


    };
}
