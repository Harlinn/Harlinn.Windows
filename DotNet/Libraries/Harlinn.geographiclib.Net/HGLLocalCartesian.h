#pragma once
/*
   Copyright 2024-2026 Espen Harlinn

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
#include <GeographicLib/LocalCartesian.hpp>
#pragma managed(pop)

#include "HGLPoint.h"
#include "HGLGeoPoint.h"

namespace Harlinn::GeographicLib::Net
{
    public ref class LocalCartesian
    {
        ::GeographicLib::LocalCartesian* impl_ = nullptr;
        bool _disposed = false;
    public:
        LocalCartesian( double latitude0, double longitude0, double altitude0 )
        {
            impl_ = new ::GeographicLib::LocalCartesian( latitude0, longitude0, altitude0 );
        }

        ~LocalCartesian( )
        {
            if ( !_disposed )
            {
                _disposed = true;
                delete impl_;
            }
        }

        !LocalCartesian( )
        {
            if ( !_disposed )
            {
                _disposed = true;
                delete impl_;
            }
        }

        void Forward( double latitude, double longitude, double altitude, [ Runtime::InteropServices::Out ] double% x, [ Runtime::InteropServices::Out ] double% y, [ Runtime::InteropServices::Out ] double% z )
        {
            ::GeographicLib::Math::real lx, ly, lz;
            impl_->Forward( latitude, longitude, altitude, lx, ly, lz );
            x = lx;
            y = ly;
            z = lz;
        }

        Point3D^ Forward( GeoPoint3D^ point )
        {
            ::GeographicLib::Math::real lx, ly, lz;
            impl_->Forward( point->Latitude, point->Longitude, point->Altitude, lx, ly, lz );
            return gcnew Point3D( lx, ly, lz );
        }

        void ToCartesian( double latitude, double longitude, double altitude, [ Runtime::InteropServices::Out ] double% x, [ Runtime::InteropServices::Out ] double% y, [ Runtime::InteropServices::Out ] double% z )
        {
            ::GeographicLib::Math::real lx, ly, lz;
            impl_->Forward( latitude, longitude, altitude, lx, ly, lz );
            x = lx;
            y = ly;
            z = lz;
        }
        Point3D^ ToCartesian( GeoPoint3D^ point )
        {
            ::GeographicLib::Math::real lx, ly, lz;
            impl_->Forward( point->Latitude, point->Longitude, point->Altitude, lx, ly, lz );
            return gcnew Point3D( lx, ly, lz );
        }



        void Reverse( double x, double y, double z, [ Runtime::InteropServices::Out ] double% latitude, [ Runtime::InteropServices::Out ] double% longitude, [ Runtime::InteropServices::Out ] double% altitude )
        {
            ::GeographicLib::Math::real llatitude, llongitude, laltitude;
            impl_->Reverse( x, y, z, llatitude, llongitude, laltitude );
            latitude = llatitude;
            longitude = llongitude;
            altitude = laltitude;
        }

        void FromCartesian( double x, double y, double z, [ Runtime::InteropServices::Out ] double% latitude, [ Runtime::InteropServices::Out ] double% longitude, [ Runtime::InteropServices::Out ] double% altitude )
        {
            ::GeographicLib::Math::real llatitude, llongitude, laltitude;
            impl_->Reverse( x, y, z, llatitude, llongitude, laltitude );
            latitude = llatitude;
            longitude = llongitude;
            altitude = laltitude;
        }

        GeoPoint3D^ Reverse( Point3D^ point )
        {
            ::GeographicLib::Math::real llatitude, llongitude, laltitude;
            impl_->Forward( point->X, point->Y, point->Z, llatitude, llongitude, laltitude );
            return gcnew GeoPoint3D( llatitude, llongitude, laltitude );
        }

        GeoPoint3D^ FromCartesian( Point3D^ point )
        {
            ::GeographicLib::Math::real llatitude, llongitude, laltitude;
            impl_->Forward( point->X, point->Y, point->Z, llatitude, llongitude, laltitude );
            return gcnew GeoPoint3D( llatitude, llongitude, laltitude );
        }

    };
}

