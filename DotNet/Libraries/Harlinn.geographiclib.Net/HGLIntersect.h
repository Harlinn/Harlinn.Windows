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

using namespace System;

#pragma managed(push)
#include <GeographicLib/Intersect.hpp>
#include <GeographicLib/Gnomonic.hpp>

class vector3
{
public:
    double _x, _y, _z;
    vector3( double x, double y, double z = 1 ) throw( )
        : _x( x )
        , _y( y )
        , _z( z )
    {
    }
    vector3 cross( const vector3& b ) const throw( )
    {
        return vector3( _y * b._z - _z * b._y,
            _z * b._x - _x * b._z,
            _x * b._y - _y * b._x );
    }
    void norm( ) throw( )
    {
        _x /= _z;
        _y /= _z;
        _z = 1;
    }
};

inline std::pair<double, double> ClosestImpl( double lata1, double lona1, double lata2, double lona2, double latb1, double lonb1 )
{
    const ::GeographicLib::Geodesic& geod = ::GeographicLib::Geodesic::WGS84( );
    const ::GeographicLib::Gnomonic gn( geod );
    double lat0 = ( lata1 + lata2 ) / 2;
    // Possibly need to deal with longitudes wrapping around
    double lon0 = ( lona1 + lona2 ) / 2;

    for ( int i = 0; i < 10; ++i )
    {
        double xa1, ya1, xa2, ya2;
        double xb1, yb1;
        gn.Forward( lat0, lon0, lata1, lona1, xa1, ya1 );
        gn.Forward( lat0, lon0, lata2, lona2, xa2, ya2 );
        gn.Forward( lat0, lon0, latb1, lonb1, xb1, yb1 );
        // See Hartley and Zisserman, Multiple View Geometry, Sec. 2.2.1
        vector3 va1( xa1, ya1 ); vector3 va2( xa2, ya2 );
        // la is homogeneous representation of line A1,A2
        vector3 la = va1.cross( va2 );
        vector3 vb1( xb1, yb1 );
        // lb is homogeneous representation of line thru B1 perpendicular to la
        vector3 lb( la._y, -la._x, la._x * yb1 - la._y * xb1 );
        // p0 is homogeneous representation of intersection of la and lb
        vector3 p0 = la.cross( lb );
        p0.norm( );
        double lat1, lon1;
        gn.Reverse( lat0, lon0, p0._x, p0._y, lat1, lon1 );
        lat0 = lat1;
        lon0 = lon1;
    }
    return { lat0, lon0 };
}

#pragma managed(pop)

#include "HGLPoint.h"
#include "HGLGeoPoint.h"
#include "HGLGeodesicLine.h"
#include "HGLGeodesic.h"
#include "HGLLocalCartesian.h"

namespace Harlinn::GeographicLib::Net
{
    public ref class Intersect
    {
        ::GeographicLib::Intersect* impl_ = nullptr;
        bool _disposed = false;
    public:
        Intersect( )
        {
            impl_ = new ::GeographicLib::Intersect( ::GeographicLib::Geodesic::WGS84( ) );
        }

        ~Intersect( )
        {
            if ( !_disposed )
            {
                _disposed = true;
                delete impl_;
            }
        }

        !Intersect( )
        {
            if ( !_disposed )
            {
                _disposed = true;
                delete impl_;
            }
        }

        GeoPoint^ Closest( double latX, double lonX, double aziX, double latY, double lonY, double aziY )
        {
            auto point = impl_->Closest( latX, lonX, aziX, latY, lonY, aziY );
            return gcnew GeoPoint( point.first, point.second );
        }

        GeoPoint^ ClosestPoint( double lata1, double lona1, double lata2, double lona2, double latb1, double lonb1 )
        {
            auto result = ClosestImpl( lata1, lona1, lata2, lona2, latb1, lonb1 );
            return gcnew GeoPoint( result.first, result.second );
        }

    };
}

