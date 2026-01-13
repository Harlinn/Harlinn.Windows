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
#include "HGLGeodesicLine.h"

namespace Harlinn::GeographicLib::Net
{
    GeodesicLine^ Geodesic::InverseLine( double lat1, double lon1, double lat2, double lon2, GeodesicMask caps )
    {
        auto geodesicLine = impl_->InverseLine( lat1, lon1, lat2, lon2, static_cast< unsigned >( caps ) );
        return gcnew GeodesicLine( &geodesicLine );
    }
    GeodesicLine^ Geodesic::InverseLine( double lat1, double lon1, double lat2, double lon2 )
    {
        auto geodesicLine = impl_->InverseLine( lat1, lon1, lat2, lon2 );
        return gcnew GeodesicLine( &geodesicLine );
    }

    GeodesicLine^ Geodesic::DirectLine( double lat1, double lon1, double azi1, double s12, GeodesicMask caps )
    {
        auto geodesicLine = impl_->DirectLine( lat1, lon1, azi1, s12, static_cast< unsigned >( caps ) );
        return gcnew GeodesicLine( &geodesicLine );
    }
    GeodesicLine^ Geodesic::DirectLine( double lat1, double lon1, double azi1, double s12 )
    {
        auto geodesicLine = impl_->DirectLine( lat1, lon1, azi1, s12 );
        return gcnew GeodesicLine( &geodesicLine );
    }

    GeodesicLine^ Geodesic::ArcDirectLine( double lat1, double lon1, double azi1, double a12, GeodesicMask caps )
    {
        auto geodesicLine = impl_->ArcDirectLine( lat1, lon1, azi1, a12, static_cast< unsigned >( caps ) );
        return gcnew GeodesicLine( &geodesicLine );
    }
    GeodesicLine^ Geodesic::ArcDirectLine( double lat1, double lon1, double azi1, double a12 )
    {
        auto geodesicLine = impl_->ArcDirectLine( lat1, lon1, azi1, a12 );
        return gcnew GeodesicLine( &geodesicLine );
    }

    GeodesicLine^ Geodesic::GenDirectLine( double lat1, double lon1, double azi1, bool arcmode, double s12_a12, GeodesicMask caps )
    {
        auto geodesicLine = impl_->GenDirectLine( lat1, lon1, azi1, arcmode, s12_a12, static_cast< unsigned >( caps ) );
        return gcnew GeodesicLine( &geodesicLine );
    }
    GeodesicLine^ Geodesic::GenDirectLine( double lat1, double lon1, double azi1, bool arcmode, double s12_a12 )
    {
        auto geodesicLine = impl_->GenDirectLine( lat1, lon1, azi1, arcmode, s12_a12 );
        return gcnew GeodesicLine( &geodesicLine );
    }
}