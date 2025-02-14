#pragma once
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

#pragma managed(push)
#include <GeographicLib/Geodesic.hpp>
#pragma managed(pop)

#include "HGLDistanceAndBearing.h"
#include "HGLDMS.h"
#include "HGLPoint.h"


namespace Harlinn::GeographicLib::Net
{
    public value class GeoPoint
    {
        double latitude_;
        double longitude_;
    public:

        GeoPoint( double latitude, double longitude )
            : latitude_( latitude ), longitude_( longitude )
        {
        }

        static bool operator==( GeoPoint lhs, GeoPoint rhs )
        {
            return lhs.latitude_ == rhs.latitude_ && lhs.longitude_ == rhs.longitude_;
        }

        static bool operator!=( GeoPoint lhs, GeoPoint rhs )
        {
            return lhs.latitude_ != rhs.latitude_ || lhs.longitude_ != rhs.longitude_;
        }

        property double Latitude
        {
            double get( )
            {
                return latitude_;
            }

            void set( double value )
            {
                latitude_ = value;
            }
        }

        property double Longitude
        {
            double get( )
            {
                return longitude_;
            }

            void set( double value )
            {
                longitude_ = value;
            }
        }

        static [[nodiscard]] double Distance( double latitude1, double longitude1, double latitude2, double longitude2 )
        {
            static const ::GeographicLib::Geodesic& geod = ::GeographicLib::Geodesic::WGS84( );
            double result;
            geod.Inverse( latitude1, longitude1, latitude2, longitude2, result );
            return result;
        }

        static [[nodiscard]] GeographicLib::Net::DistanceAndBearing DistanceAndBearing( double latitude1, double longitude1, double latitude2, double longitude2 )
        {
            static const ::GeographicLib::Geodesic& geod = ::GeographicLib::Geodesic::WGS84( );
            double distance;
            double azi1;
            double azi2;
            geod.Inverse( latitude1, longitude1, latitude2, longitude2, distance, azi1, azi2 );
            return GeographicLib::Net::DistanceAndBearing{ distance, azi1, azi2 };
        }

        static [[nodiscard]] GeoPoint PositionFromLocationDistanceAndBearing( double latitude, double longitude, double distance, double bearing )
        {
            static const ::GeographicLib::Geodesic& geod = ::GeographicLib::Geodesic::WGS84( );
            double newLatitude;
            double newLongitude;
            geod.Direct( latitude, longitude, bearing, distance, newLatitude, newLongitude );
            GeoPoint result( newLatitude, newLongitude );
            return result;
        }

        double DistanceTo( double otherLatitude, double otherLongitude )
        {
            return Distance( latitude_, longitude_, otherLatitude, otherLongitude );
        }

        double DistanceTo( GeoPoint other )
        {
            return Distance( latitude_, longitude_, other.latitude_, other.longitude_ );
        }

        GeographicLib::Net::DistanceAndBearing DistanceAndBearingTo( double otherLatitude, double otherLongitude )
        {
            return DistanceAndBearing( latitude_, longitude_, otherLatitude, otherLongitude );
        }

        GeographicLib::Net::DistanceAndBearing DistanceAndBearingTo( const GeoPoint other )
        {
            return DistanceAndBearing( latitude_, longitude_, other.latitude_, other.longitude_ );
        }

        GeoPoint PositionFromDistanceAndBearing( double distance, double bearing )
        {
            return PositionFromLocationDistanceAndBearing( latitude_, longitude_, distance, bearing );
        }

        [[nodiscard]] static GeoPoint Parse( String^ string )
        {
            if ( string == nullptr )
            {
                throw gcnew ArgumentNullException( "string" );
            }
            auto strings = string->Split( ',' );
            if ( strings->Length != 2 )
            {
                throw gcnew ArgumentException( "Missing \',\'", "string" );
            }
            auto latStr = ToUtf8( strings[ 0 ]->Trim( ) );
            auto lonStr = ToUtf8( strings[ 1 ]->Trim( ) );
            try
            {
                ::GeographicLib::DMS::flag lflag;
                double lon = 0.0;
                auto lat = ::GeographicLib::DMS::Decode( latStr, lflag );
                if ( lflag == ::GeographicLib::DMS::LONGITUDE )
                {
                    lon = lat;
                    lat = ::GeographicLib::DMS::Decode( lonStr, lflag );
                }
                else
                {
                    lon = ::GeographicLib::DMS::Decode( lonStr, lflag );
                }
                return GeoPoint( lat, lon );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        [[nodiscard]] static bool TryParse( String^ string, [ System::Runtime::InteropServices::Out ] GeoPoint% value )
        {
            try
            {
                value = Parse( string );
            }
            catch ( ... )
            {
                return false;
            }
            return true;
        }

        virtual String^ ToString( ) override
        {
            auto latStr = DMS::Encode( Latitude, 7UL );
            auto lonStr = DMS::Encode( Longitude, 7UL );
            return String::Format( "{0},{1}", latStr, lonStr );
        }



    };


    public value class GeoPoint3D
    {
        double latitude_;
        double longitude_;
        double altitude_;
    public:

        GeoPoint3D( double latitude, double longitude, double altitude )
            : latitude_( latitude ), longitude_( longitude ), altitude_( altitude )
        {
        }

        static bool operator==( GeoPoint3D lhs, GeoPoint3D rhs )
        {
            return lhs.latitude_ == rhs.latitude_ && lhs.longitude_ == rhs.longitude_ && lhs.altitude_ == rhs.altitude_;
        }

        static bool operator!=( GeoPoint3D lhs, GeoPoint3D rhs )
        {
            return lhs.latitude_ != rhs.latitude_ || lhs.longitude_ != rhs.longitude_ || lhs.altitude_ != rhs.altitude_;
        }

        property double Latitude
        {
            double get( )
            {
                return latitude_;
            }

            void set( double value )
            {
                latitude_ = value;
            }
        }

        property double Longitude
        {
            double get( )
            {
                return longitude_;
            }

            void set( double value )
            {
                longitude_ = value;
            }
        }


        property double Altitude
        {
            double get( )
            {
                return altitude_;
            }

            void set( double value )
            {
                altitude_ = value;
            }
        }
    };
}



