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
#include <GeographicLib/Geodesic.hpp>
#pragma managed(pop)

#include "HGLGeoPoint.h"

namespace Harlinn::GeographicLib::Net
{
    [System::Flags]
    public enum class GeodesicMask : unsigned
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

    ref class GeodesicLine;

    public ref class Geodesic
    {
        ::GeographicLib::Geodesic* impl_ = nullptr;
        bool disposed_ = false;
        bool ownsImpl_ = true;

        static Geodesic^ WGS84_ = nullptr;
        Geodesic( ::GeographicLib::Geodesic* impl, bool ownsImpl )
            : impl_( impl ), ownsImpl_( ownsImpl )
        {
        }
    public:
        Geodesic( double a, double f, bool exact )
        {
            impl_ = new ::GeographicLib::Geodesic( a, f, exact );
        }
        Geodesic( double a, double f )
        {
            impl_ = new ::GeographicLib::Geodesic( a, f, false );
        }

        ~Geodesic( )
        {
            if ( !disposed_ )
            {
                disposed_ = true;
                if ( ownsImpl_ )
                {
                    delete impl_;
                }
            }
        }

        !Geodesic( )
        {
            if ( !disposed_ )
            {
                disposed_ = true;
                if ( ownsImpl_ )
                {
                    delete impl_;
                }
            }
        }

        static property Geodesic^ WGS84
        {
            Geodesic^ get( )
            {
                if ( WGS84_ == nullptr )
                {
                    auto& wgs84 = const_cast< ::GeographicLib::Geodesic& >( ::GeographicLib::Geodesic::WGS84( ) );
                    WGS84_ = gcnew Geodesic( &wgs84, false );
                }
                return WGS84_;
            }
        }


        double Direct( double lat1, double lon1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2,
            [ Runtime::InteropServices::Out ] double% m12, [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21, [ Runtime::InteropServices::Out ] double% S12 )
        {
            double llat2, llon2, lazi2,
                lm12, lM12, lM21, lS12;
            double result = impl_->Direct( lat1, lon1, azi1, s12, llat2, llon2, lazi2, lm12, lM12, lM21, lS12 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            m12 = lm12;
            M12 = lM12;
            M21 = lM21;
            S12 = lS12;
            return result;
        }

        double Direct( GeoPoint^ point1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2,
            [ Runtime::InteropServices::Out ] double% m12, [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21, [ Runtime::InteropServices::Out ] double% S12 )
        {
            if ( point1 == nullptr )
            {
                throw gcnew System::ArgumentNullException( L"point1" );
            }
            double llat2, llon2, lazi2,
                lm12, lM12, lM21, lS12;
            double result = impl_->Direct( point1->Latitude, point1->Longitude, azi1, s12, llat2, llon2, lazi2, lm12, lM12, lM21, lS12 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            m12 = lm12;
            M12 = lM12;
            M21 = lM21;
            S12 = lS12;
            return result;
        }

        double Direct( double lat1, double lon1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2 )
        {
            double llat2, llon2;
            double result = impl_->Direct( lat1, lon1, azi1, s12, llat2, llon2 );
            lat2 = llat2;
            lon2 = llon2;
            return result;
        }

        double Direct( GeoPoint^ point1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2 )
        {
            if ( point1 == nullptr )
            {
                throw gcnew System::ArgumentNullException( L"point1" );
            }
            double llat2, llon2;
            double result = impl_->Direct( point1->Latitude, point1->Longitude, azi1, s12, llat2, llon2 );
            lat2 = llat2;
            lon2 = llon2;
            return result;
        }

        double Direct( double lat1, double lon1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2 )
        {
            double llat2, llon2, lazi2;

            double result = impl_->Direct( lat1, lon1, azi1, s12, llat2, llon2, lazi2 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            return result;
        }

        double Direct( GeoPoint^ point1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2 )
        {
            if ( point1 == nullptr )
            {
                throw gcnew System::ArgumentNullException( L"point1" );
            }
            double llat2, llon2, lazi2;

            double result = impl_->Direct( point1->Latitude, point1->Longitude, azi1, s12, llat2, llon2, lazi2 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            return result;
        }


        double Direct( double lat1, double lon1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% m12 )
        {
            double llat2, llon2, lazi2, lm12;

            double result = impl_->Direct( lat1, lon1, azi1, s12, llat2, llon2, lazi2, lm12 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            m12 = lm12;
            return result;
        }

        double Direct( GeoPoint^ point1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% m12 )
        {
            if ( point1 == nullptr )
            {
                throw gcnew System::ArgumentNullException( L"point1" );
            }
            double llat2, llon2, lazi2, lm12;

            double result = impl_->Direct( point1->Latitude, point1->Longitude, azi1, s12, llat2, llon2, lazi2, lm12 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            m12 = lm12;
            return result;
        }

        double Direct( double lat1, double lon1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21 )
        {
            double llat2, llon2, lazi2, lM12, lM21;

            double result = impl_->Direct( lat1, lon1, azi1, s12, llat2, llon2, lazi2, lM12, lM21 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            M12 = lM12;
            M21 = lM21;
            return result;
        }

        double Direct( GeoPoint^ point1, double azi1, double s12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21 )
        {
            if ( point1 == nullptr )
            {
                throw gcnew System::ArgumentNullException( L"point1" );
            }
            double llat2, llon2, lazi2, lM12, lM21;

            double result = impl_->Direct( point1->Latitude, point1->Longitude, azi1, s12, llat2, llon2, lazi2, lM12, lM21 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            M12 = lM12;
            M21 = lM21;
            return result;
        }

        void ArcDirect( double lat1, double lon1, double azi1, double a12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% s12,
            [ Runtime::InteropServices::Out ] double% m12, [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21, [ Runtime::InteropServices::Out ] double% S12 )
        {
            double llat2, llon2, lazi2, ls12, lm12, lM12, lM21, lS12;
            impl_->ArcDirect( lat1, lon1, azi1, a12, llat2, llon2, lazi2, ls12, lm12, lM12, lM21, lS12 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            s12 = ls12;
            m12 = lm12;
            M12 = lM12;
            M21 = lM21;
            S12 = lS12;
        }

        void ArcDirect( double lat1, double lon1, double azi1, double a12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2 )
        {
            double llat2, llon2;
            impl_->ArcDirect( lat1, lon1, azi1, a12, llat2, llon2 );
            lat2 = llat2;
            lon2 = llon2;
        }

        void ArcDirect( double lat1, double lon1, double azi1, double a12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2 )
        {
            double llat2, llon2, lazi2;
            impl_->ArcDirect( lat1, lon1, azi1, a12, llat2, llon2, lazi2 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
        }

        void ArcDirect( double lat1, double lon1, double azi1, double a12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% s12 )
        {
            double llat2, llon2, lazi2, ls12;
            impl_->ArcDirect( lat1, lon1, azi1, a12, llat2, llon2, lazi2, ls12 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            s12 = ls12;
        }

        void ArcDirect( double lat1, double lon1, double azi1, double a12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% s12,
            [ Runtime::InteropServices::Out ] double% m12 )
        {
            double llat2, llon2, lazi2, ls12, lm12;
            impl_->ArcDirect( lat1, lon1, azi1, a12, llat2, llon2, lazi2, ls12, lm12 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            s12 = ls12;
            m12 = lm12;
        }

        void ArcDirect( double lat1, double lon1, double azi1, double a12,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% s12,
            [ Runtime::InteropServices::Out ] double% m12, [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21 )
        {
            double llat2, llon2, lazi2, ls12, lm12, lM12, lM21;
            impl_->ArcDirect( lat1, lon1, azi1, a12, llat2, llon2, lazi2, ls12, lm12, lM12, lM21 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            s12 = ls12;
            m12 = lm12;
            M12 = lM12;
            M21 = lM21;
        }

        double GenDirect( double lat1, double lon1, double azi1,
            bool arcmode, double s12_a12, GeodesicMask outmask,
            [ Runtime::InteropServices::Out ] double% lat2, [ Runtime::InteropServices::Out ] double% lon2, [ Runtime::InteropServices::Out ] double% azi2,
            [ Runtime::InteropServices::Out ] double% s12, [ Runtime::InteropServices::Out ] double% m12, [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21,
            [ Runtime::InteropServices::Out ] double% S12 )
        {
            double llat2, llon2, lazi2, ls12, lm12, lM12, lM21, lS12;
            double result = impl_->GenDirect( lat1, lon1, azi1,
                arcmode, s12_a12, static_cast< unsigned >( outmask ), llat2, llon2, lazi2, ls12, lm12, lM12, lM21, lS12 );
            lat2 = llat2;
            lon2 = llon2;
            azi2 = lazi2;
            s12 = ls12;
            m12 = lm12;
            M12 = lM12;
            M21 = lM21;
            S12 = lS12;
            return result;
        }

        double Inverse( double lat1, double lon1, double lat2, double lon2,
            [ Runtime::InteropServices::Out ] double% s12, [ Runtime::InteropServices::Out ] double% azi1, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% m12,
            [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21, [ Runtime::InteropServices::Out ] double% S12 )
        {
            double ls12, lazi1, lazi2, lm12, lM12, lM21, lS12;
            double result = impl_->Inverse( lat1, lon1, lat2, lon2, ls12, lazi1, lazi2, lm12, lM12, lM21, lS12 );
            s12 = ls12;
            azi1 = lazi1;
            azi2 = lazi2;
            m12 = lm12;
            M12 = lM12;
            M21 = lM21;
            S12 = lS12;
            return result;
        }

        double Inverse( double lat1, double lon1, double lat2, double lon2,
            [ Runtime::InteropServices::Out ] double% s12 )
        {
            double ls12;
            double result = impl_->Inverse( lat1, lon1, lat2, lon2, ls12 );
            s12 = ls12;
            return result;
        }

        double Inverse( double lat1, double lon1, double lat2, double lon2,
            [ Runtime::InteropServices::Out ] double% azi1, [ Runtime::InteropServices::Out ] double% azi2 )
        {
            double lazi1, lazi2;
            double result = impl_->Inverse( lat1, lon1, lat2, lon2, lazi1, lazi2 );
            azi1 = lazi1;
            azi2 = lazi2;
            return result;
        }

        double Inverse( double lat1, double lon1, double lat2, double lon2,
            [ Runtime::InteropServices::Out ] double% s12, [ Runtime::InteropServices::Out ] double% azi1, [ Runtime::InteropServices::Out ] double% azi2 )
        {
            double ls12, lazi1, lazi2;
            double result = impl_->Inverse( lat1, lon1, lat2, lon2, ls12, lazi1, lazi2 );
            s12 = ls12;
            azi1 = lazi1;
            azi2 = lazi2;
            return result;
        }

        double Inverse( double lat1, double lon1, double lat2, double lon2,
            [ Runtime::InteropServices::Out ] double% s12, [ Runtime::InteropServices::Out ] double% azi1, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% m12 )
        {
            double ls12, lazi1, lazi2, lm12;
            double result = impl_->Inverse( lat1, lon1, lat2, lon2, ls12, lazi1, lazi2, lm12 );
            s12 = ls12;
            azi1 = lazi1;
            azi2 = lazi2;
            m12 = lm12;
            return result;
        }

        double Inverse( double lat1, double lon1, double lat2, double lon2,
            [ Runtime::InteropServices::Out ] double% s12, [ Runtime::InteropServices::Out ] double% azi1, [ Runtime::InteropServices::Out ] double% azi2,
            [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21 )
        {
            double ls12, lazi1, lazi2, lM12, lM21;
            double result = impl_->Inverse( lat1, lon1, lat2, lon2, ls12, lazi1, lazi2, lM12, lM21 );
            s12 = ls12;
            azi1 = lazi1;
            azi2 = lazi2;
            M12 = lM12;
            M21 = lM21;
            return result;
        }

        double Inverse( double lat1, double lon1, double lat2, double lon2,
            [ Runtime::InteropServices::Out ] double% s12, [ Runtime::InteropServices::Out ] double% azi1, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% m12,
            [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21 )
        {
            double ls12, lazi1, lazi2, lm12, lM12, lM21;
            double result = impl_->Inverse( lat1, lon1, lat2, lon2, ls12, lazi1, lazi2, lm12, lM12, lM21 );
            s12 = ls12;
            azi1 = lazi1;
            azi2 = lazi2;
            m12 = lm12;
            M12 = lM12;
            M21 = lM21;
            return result;
        }

        double GenInverse( double lat1, double lon1, double lat2, double lon2,
            GeodesicMask outmask,
            [ Runtime::InteropServices::Out ] double% s12, [ Runtime::InteropServices::Out ] double% azi1, [ Runtime::InteropServices::Out ] double% azi2, [ Runtime::InteropServices::Out ] double% m12,
            [ Runtime::InteropServices::Out ] double% M12, [ Runtime::InteropServices::Out ] double% M21, [ Runtime::InteropServices::Out ] double% S12 )
        {
            double ls12, lazi1, lazi2, lm12, lM12, lM21, lS12;
            double result = impl_->GenInverse( lat1, lon1, lat2, lon2, static_cast< unsigned >( outmask ), ls12, lazi1, lazi2, lm12, lM12, lM21, lS12 );
            s12 = ls12;
            azi1 = lazi1;
            azi2 = lazi2;
            m12 = lm12;
            M12 = lM12;
            M21 = lM21;
            S12 = lS12;
            return result;
        }

        GeodesicLine^ InverseLine( double lat1, double lon1, double lat2, double lon2, GeodesicMask caps );
        GeodesicLine^ InverseLine( double lat1, double lon1, double lat2, double lon2 );

        GeodesicLine^ DirectLine( double lat1, double lon1, double azi1, double s12, GeodesicMask caps );
        GeodesicLine^ DirectLine( double lat1, double lon1, double azi1, double s12 );

        GeodesicLine^ ArcDirectLine( double lat1, double lon1, double azi1, double a12, GeodesicMask caps );
        GeodesicLine^ ArcDirectLine( double lat1, double lon1, double azi1, double a12 );

        GeodesicLine^ GenDirectLine( double lat1, double lon1, double azi1, bool arcmode, double s12_a12, GeodesicMask caps );
        GeodesicLine^ GenDirectLine( double lat1, double lon1, double azi1, bool arcmode, double s12_a12 );



    };
}

