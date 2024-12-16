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