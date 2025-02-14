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

    /**
     * \brief A geodesic line
     *
     * GeodesicLine facilitates the determination of a series of points on a
     * single geodesic.  The starting point (\e lat1, \e lon1) and the azimuth \e
     * azi1 are specified in the constructor; alternatively, the Geodesic::Line
     * method can be used to create a GeodesicLine.  GeodesicLine.Position
     * returns the location of point 2 a distance \e s12 along the geodesic.  In
     * addition, GeodesicLine.ArcPosition gives the position of point 2 an arc
     * length \e a12 along the geodesic.
     *
     * You can register the position of a reference point 3 a distance (arc
     * length), \e s13 (\e a13) along the geodesic with the
     * GeodesicLine.SetDistance (GeodesicLine.SetArc) functions.  Points a
     * fractional distance along the line can be found by providing, for example,
     * 0.5 * Distance() as an argument to GeodesicLine.Position.  The
     * Geodesic::InverseLine or Geodesic::DirectLine methods return GeodesicLine
     * objects with point 3 set to the point 2 of the corresponding geodesic
     * problem.  GeodesicLine objects created with the public constructor or with
     * Geodesic::Line have \e s13 and \e a13 set to NaNs.
     *
     * The default copy constructor and assignment operators work with this
     * class.  Similarly, a vector can be used to hold GeodesicLine objects.
     *
     * The calculations are accurate to better than 15 nm (15 nanometers).  See
     * Sec. 9 of
     * <a href="https://arxiv.org/abs/1102.1215v1">arXiv:1102.1215v1</a> for
     * details.  With \e exact = false (the default) in the constructor for the
     * Geodesic object, the algorithms used by this class are based on series
     * expansions using the flattening \e f as a small parameter.  These are only
     * accurate for |<i>f</i>| &lt; 0.02; however reasonably accurate results
     * will be obtained for |<i>f</i>| &lt; 0.2.  For very eccentric ellipsoids,
     * set \e exact = true in the constructor for the Geodesic object; this will
     * delegate the calculations to GeodesicLineExact.
     *
     * The algorithms are described in
     * - C. F. F. Karney,
     *   <a href="https://doi.org/10.1007/s00190-012-0578-z">
     *   Algorithms for geodesics</a>,
     *   J. Geodesy <b>87</b>, 43--55 (2013);
     *   DOI: <a href="https://doi.org/10.1007/s00190-012-0578-z">
     *   10.1007/s00190-012-0578-z</a>;
     *   addenda:
     *   <a href="https://geographiclib.sourceforge.io/geod-addenda.html">
     *   geod-addenda.html</a>.
     * .
     * For more information on geodesics see \ref geodesic.
     *
     * Example of use:
     * \include example-GeodesicLine.cpp
     *
     * <a href="GeodSolve.1.html">GeodSolve</a> is a command-line utility
     * providing access to the functionality of Geodesic and GeodesicLine.
     **********************************************************************/
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
        /**
         * Constructor for a geodesic line staring at latitude \e lat1, longitude
         * \e lon1, and azimuth \e azi1 (all in degrees).
         *
         * @param[in] g A Geodesic object used to compute the necessary information
         *   about the GeodesicLine.
         * @param[in] lat1 latitude of point 1 (degrees).
         * @param[in] lon1 longitude of point 1 (degrees).
         * @param[in] azi1 azimuth at point 1 (degrees).
         * @param[in] caps bitor'ed combination of GeodesicLine::mask values
         *   specifying the capabilities the GeodesicLine object should possess,
         *   i.e., which quantities can be returned in calls to
         *   GeodesicLine::Position.
         *
         * \e lat1 should be in the range [&minus;90&deg;, 90&deg;].
         *
         * The default value of \e caps is GeodesicLineMask::All.
         *
         * If the point is at a pole, the azimuth is defined by keeping \e lon1
         * fixed, writing \e lat1 = &plusmn;(90&deg; &minus; &epsilon;), and taking
         * the limit &epsilon; &rarr; 0+.
         **********************************************************************/
        GeodesicLine( Geodesic^ g, double lat1, double lon1, double azi1, GeodesicLineMask caps )
        {
            if ( g == nullptr || g->Impl() == nullptr )
            {
                throw gcnew System::ArgumentNullException( L"g" );
            }
            impl_ = new ::GeographicLib::GeodesicLine( *(g->Impl( )), lat1, lon1, azi1, static_cast< unsigned >( caps ) );
        }

        GeodesicLine( Geodesic^ g, double lat1, double lon1, double azi1 )
            : GeodesicLine( g, lat1, lon1, azi1, GeodesicLineMask::All )
        {

        }


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
    internal:
        ::GeographicLib::GeodesicLine* Impl( )
        {
            return impl_;
        }
    public:

        /**
         * point 1.
         *
         * @param[in] s12 distance from point 1 to point 2 (meters); it can be
         *   negative.
         * @param[out] lat2 latitude of point 2 (degrees).
         * @param[out] lon2 longitude of point 2 (degrees); requires that the
         *   GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::LONGITUDE.
         * @param[out] azi2 (forward) azimuth at point 2 (degrees).
         * @param[out] m12 reduced length of geodesic (meters); requires that the
         *   GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::REDUCEDLENGTH.
         * @param[out] M12 geodesic scale of point 2 relative to point 1
         *   (dimensionless); requires that the GeodesicLine object was constructed
         *   with \e caps |= GeodesicLine::GEODESICSCALE.
         * @param[out] M21 geodesic scale of point 1 relative to point 2
         *   (dimensionless); requires that the GeodesicLine object was constructed
         * Compute the position of point 2 which is a distance \e s12 (meters) from
         *   with \e caps |= GeodesicLine::GEODESICSCALE.
         * @param[out] S12 area under the geodesic (meters<sup>2</sup>); requires
         *   that the GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::AREA.
         * @return \e a12 arc length from point 1 to point 2 (degrees).
         *
         * The values of \e lon2 and \e azi2 returned are in the range
         * [&minus;180&deg;, 180&deg;].
         *
         * The GeodesicLine object \e must have been constructed with \e caps |=
         * GeodesicLine::DISTANCE_IN; otherwise Math::NaN() is returned and no
         * parameters are set.  Requesting a value which the GeodesicLine object is
         * not capable of computing is not an error; the corresponding argument
         * will not be altered.
         *
         * The following functions are overloaded versions of
         * GeodesicLine::Position which omit some of the output parameters.  Note,
         * however, that the arc length is always computed and returned as the
         * function value.
         **********************************************************************/
        double Position( double s12,
            [ Runtime::InteropServices::Out ] double% lat2, 
            [ Runtime::InteropServices::Out ] double% lon2, 
            [ Runtime::InteropServices::Out ] double% azi2,
            [ Runtime::InteropServices::Out ] double% m12, 
            [ Runtime::InteropServices::Out ] double% M12, 
            [ Runtime::InteropServices::Out ] double% M21,
            [ Runtime::InteropServices::Out ] double% S12 )
        {
            try
            {
                double _lat2;
                double _lon2;
                double _azi2;
                double _m12;
                double _M12;
                double _M21;
                double _S12;

                auto result = impl_->Position( s12, _lat2, _lon2, _azi2, _m12, _M12, _M21, _S12 );

                lat2 = _lat2;
                lon2 = _lon2;
                azi2 = _azi2;
                m12 = _m12;
                M12 = _M12;
                M21 = _M21;
                S12 = _S12;

                return result;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }

        }


        double Position( double distance, 
            [ Runtime::InteropServices::Out ] double% latitude, 
            [ Runtime::InteropServices::Out ] double% longitude, 
            [ Runtime::InteropServices::Out ] double% forwardAzimuth )
        {
            try
            {
                double lat;
                double lon;
                double azi;
                auto result = impl_->Position( distance, lat, lon, azi );
                latitude = lat;
                longitude = lon;
                forwardAzimuth = azi;
                return result;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        double Position( double distance, [ Runtime::InteropServices::Out ] double% latitude, [ Runtime::InteropServices::Out ] double% longitude )
        {
            try
            {
                double lat;
                double lon;
                auto result = impl_->Position( distance, lat, lon );
                latitude = lat;
                longitude = lon;
                return result;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        /**
         * Compute the position of point 2 which is an arc length \e a12 (degrees)
         * from point 1.
         *
         * @param[in] a12 arc length from point 1 to point 2 (degrees); it can
         *   be negative.
         * @param[out] lat2 latitude of point 2 (degrees).
         * @param[out] lon2 longitude of point 2 (degrees); requires that the
         *   GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::LONGITUDE.
         * @param[out] azi2 (forward) azimuth at point 2 (degrees).
         * @param[out] s12 distance from point 1 to point 2 (meters); requires
         *   that the GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::DISTANCE.
         * @param[out] m12 reduced length of geodesic (meters); requires that the
         *   GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::REDUCEDLENGTH.
         * @param[out] M12 geodesic scale of point 2 relative to point 1
         *   (dimensionless); requires that the GeodesicLine object was constructed
         *   with \e caps |= GeodesicLine::GEODESICSCALE.
         * @param[out] M21 geodesic scale of point 1 relative to point 2
         *   (dimensionless); requires that the GeodesicLine object was constructed
         *   with \e caps |= GeodesicLine::GEODESICSCALE.
         * @param[out] S12 area under the geodesic (meters<sup>2</sup>); requires
         *   that the GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::AREA.
         *
         * The values of \e lon2 and \e azi2 returned are in the range
         * [&minus;180&deg;, 180&deg;].
         *
         * Requesting a value which the GeodesicLine object is not capable of
         * computing is not an error; the corresponding argument will not be
         * altered.
         *
         * The following functions are overloaded versions of
         * GeodesicLine::ArcPosition which omit some of the output parameters.
         **********************************************************************/
        void ArcPosition( double a12, 
            [ Runtime::InteropServices::Out ] double% lat2, 
            [ Runtime::InteropServices::Out ] double% lon2, 
            [ Runtime::InteropServices::Out ] double% azi2,
            [ Runtime::InteropServices::Out ] double% s12, 
            [ Runtime::InteropServices::Out ] double% m12, 
            [ Runtime::InteropServices::Out ] double% M12, 
            [ Runtime::InteropServices::Out ] double% M21,
            [ Runtime::InteropServices::Out ] double% S12 )
        {
            try
            {
                double _lat2;
                double _lon2;
                double _azi2;
                double _s12;
                double _m12;
                double _M12;
                double _M21;
                double _S12;

                impl_->ArcPosition( a12, _lat2, _lon2, _azi2, _s12, _m12, _M12, _M21, _S12 );

                lat2 = _lat2;
                lon2 = _lon2;
                azi2 = _azi2;
                s12 = _s12;
                m12 = _m12;
                M12 = _M12;
                M21 = _M21;
                S12 = _S12;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        /**
         * The general position function.  GeodesicLine::Position and
         * GeodesicLine::ArcPosition are defined in terms of this function.
         *
         * @param[in] arcmode boolean flag determining the meaning of the second
         *   parameter; if \e arcmode is false, then the GeodesicLine object must
         *   have been constructed with \e caps |= GeodesicLine::DISTANCE_IN.
         * @param[in] s12_a12 if \e arcmode is false, this is the distance between
         *   point 1 and point 2 (meters); otherwise it is the arc length between
         *   point 1 and point 2 (degrees); it can be negative.
         * @param[in] outmask a bitor'ed combination of GeodesicLine::mask values
         *   specifying which of the following parameters should be set.
         * @param[out] lat2 latitude of point 2 (degrees).
         * @param[out] lon2 longitude of point 2 (degrees); requires that the
         *   GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::LONGITUDE.
         * @param[out] azi2 (forward) azimuth at point 2 (degrees).
         * @param[out] s12 distance from point 1 to point 2 (meters); requires
         *   that the GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::DISTANCE.
         * @param[out] m12 reduced length of geodesic (meters); requires that the
         *   GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::REDUCEDLENGTH.
         * @param[out] M12 geodesic scale of point 2 relative to point 1
         *   (dimensionless); requires that the GeodesicLine object was constructed
         *   with \e caps |= GeodesicLine::GEODESICSCALE.
         * @param[out] M21 geodesic scale of point 1 relative to point 2
         *   (dimensionless); requires that the GeodesicLine object was constructed
         *   with \e caps |= GeodesicLine::GEODESICSCALE.
         * @param[out] S12 area under the geodesic (meters<sup>2</sup>); requires
         *   that the GeodesicLine object was constructed with \e caps |=
         *   GeodesicLine::AREA.
         * @return \e a12 arc length from point 1 to point 2 (degrees).
         *
         * The GeodesicLine::mask values possible for \e outmask are
         * - \e outmask |= GeodesicLine::LATITUDE for the latitude \e lat2;
         * - \e outmask |= GeodesicLine::LONGITUDE for the latitude \e lon2;
         * - \e outmask |= GeodesicLine::AZIMUTH for the latitude \e azi2;
         * - \e outmask |= GeodesicLine::DISTANCE for the distance \e s12;
         * - \e outmask |= GeodesicLine::REDUCEDLENGTH for the reduced length \e
         *   m12;
         * - \e outmask |= GeodesicLine::GEODESICSCALE for the geodesic scales \e
         *   M12 and \e M21;
         * - \e outmask |= GeodesicLine::AREA for the area \e S12;
         * - \e outmask |= GeodesicLine::ALL for all of the above;
         * - \e outmask |= GeodesicLine::LONG_UNROLL to unroll \e lon2 instead of
         *   reducing it into the range [&minus;180&deg;, 180&deg;].
         * .
         * Requesting a value which the GeodesicLine object is not capable of
         * computing is not an error; the corresponding argument will not be
         * altered.  Note, however, that the arc length is always computed and
         * returned as the function value.
         *
         * With the GeodesicLine::LONG_UNROLL bit set, the quantity \e lon2 &minus;
         * \e lon1 indicates how many times and in what sense the geodesic
         * encircles the ellipsoid.
         **********************************************************************/
        double GenPosition( bool arcmode, 
            double s12_a12, GeodesicLineMask outmask,
            [ Runtime::InteropServices::Out ] double% lat2, 
            [ Runtime::InteropServices::Out ] double% lon2, 
            [ Runtime::InteropServices::Out ] double% azi2,
            [ Runtime::InteropServices::Out ] double% s12, 
            [ Runtime::InteropServices::Out ] double% m12, 
            [ Runtime::InteropServices::Out ] double% M12, 
            [ Runtime::InteropServices::Out ] double% M21,
            [ Runtime::InteropServices::Out ] double% S12 )
        {
            try
            {
                double _lat2;
                double _lon2;
                double _azi2;
                double _s12;
                double _m12;
                double _M12;
                double _M21;
                double _S12;

                auto result = impl_->GenPosition( arcmode, s12_a12, static_cast< unsigned >( outmask ), _lat2, _lon2, _azi2, _s12, _m12, _M12, _M21, _S12 );

                lat2 = _lat2;
                lon2 = _lon2;
                azi2 = _azi2;
                s12 = _s12;
                m12 = _m12;
                M12 = _M12;
                M21 = _M21;
                S12 = _S12;
                return result;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        /**
         * Specify position of point 3 in terms of distance.
         *
         * @param[in] s13 the distance from point 1 to point 3 (meters); it
         *   can be negative.
         *
         * This is only useful if the GeodesicLine object has been constructed
         * with \e caps |= GeodesicLineMask::DistanceIn.
         **********************************************************************/
        void SetDistance( double s13 )
        {
            try
            {
                impl_->SetDistance( s13 );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        /**
         * Specify position of point 3 in terms of arc length.
         *
         * @param[in] a13 the arc length from point 1 to point 3 (degrees); it
         *   can be negative.
         *
         * The distance \e s13 is only set if the GeodesicLine object has been
         * constructed with \e caps |= GeodesicLineMask::Distance.
         **********************************************************************/
        void SetArc( double a13 )
        {
            try
            {
                impl_->SetArc( a13 );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        /**
         * Specify position of point 3 in terms of either distance or arc length.
         *
         * @param[in] arcmode boolean flag determining the meaning of the second
         *   parameter; if \e arcmode is false, then the GeodesicLine object must
         *   have been constructed with \e caps |= GeodesicLineMask::DistanceIn.
         * @param[in] s13_a13 if \e arcmode is false, this is the distance from
         *   point 1 to point 3 (meters); otherwise it is the arc length from
         *   point 1 to point 3 (degrees); it can be negative.
         **********************************************************************/
        void GenSetDistance( bool arcmode, double s13_a13 )
        {
            try
            {
                impl_->GenSetDistance( arcmode, s13_a13 );
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        /**
         * @return true if the object has been initialized.
         **********************************************************************/
        bool Init( )
        {
            if ( impl_ != nullptr )
            {
                return impl_->Init( );
            }
            return false;
        }

        /**
         * @return \e lat1 the latitude of point 1 (degrees).
         **********************************************************************/
        property double Latitude
        {
            double get()
            { 
                return impl_->Latitude( );
            }
        }

        /**
         * @return \e lon1 the longitude of point 1 (degrees).
         **********************************************************************/
        property double Longitude
        {
            double get( )
            {
                return impl_->Longitude( );
            }
        }

        /**
         * @return \e azi1 the azimuth (degrees) of the geodesic line at point 1.
         **********************************************************************/
        property double Azimuth
        {
            double get( )
            {
                return impl_->Azimuth( );
            }
        }

        /**
         * The sine and cosine of \e azi1.
         *
         * @param[out] sazi1 the sine of \e azi1.
         * @param[out] cazi1 the cosine of \e azi1.
         **********************************************************************/
        void AzimuthValues( [ Runtime::InteropServices::Out ] double% sazi1, [ Runtime::InteropServices::Out ] double% cazi1 )
        {
            double _sazi1;
            double _cazi1;
            try
            {
                impl_->Azimuth( _sazi1, _cazi1 );
                sazi1 = _sazi1;
                cazi1 = _cazi1;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        /**
         * @return \e azi0 the azimuth (degrees) of the geodesic line as it crosses
         *   the equator in a northward direction.
         *
         * The result lies in [&minus;90&deg;, 90&deg;].
         **********************************************************************/
        property double EquatorialAzimuth
        {
            double get( )
            {
                return impl_->EquatorialAzimuth( );
            }
        }

        /**
         * The sine and cosine of \e azi0.
         *
         * @param[out] sazi0 the sine of \e azi0.
         * @param[out] cazi0 the cosine of \e azi0.
         **********************************************************************/
        void EquatorialAzimuthValues( [ Runtime::InteropServices::Out ] double% sazi0, [ Runtime::InteropServices::Out ] double% cazi0 )
        {
            double _sazi0;
            double _cazi0;
            try
            {
                impl_->EquatorialAzimuth( _sazi0, _cazi0 );
                sazi0 = _sazi0;
                cazi0 = _cazi0;
            }
            catch ( ::GeographicLib::GeographicErr& exc )
            {
                ThrowGeographicErr( exc );
            }
        }

        /**
         * @return \e a1 the arc length (degrees) between the northward equatorial
         *   crossing and point 1.
         *
         * The result lies in [&minus;180&deg;, 180&deg;].
         **********************************************************************/
        property double EquatorialArc
        {
            double get( )
            {
                return impl_->EquatorialArc( );
            }
        }

        /**
         * @return \e a the equatorial radius of the ellipsoid (meters).  This is
         *   the value inherited from the Geodesic object used in the constructor.
         **********************************************************************/
        property double EquatorialRadius
        {
            double get( )
            {
                return impl_->EquatorialRadius( );
            }
        }

        /**
         * @return \e f the flattening of the ellipsoid.  This is the value
         *   inherited from the Geodesic object used in the constructor.
         **********************************************************************/
        property double Flattening
        {
            double get( )
            {
                return impl_->Flattening( );
            }
        }

        /**
         * @return \e exact whether the exact formulation is used.  This is the
         *   value returned by the Geodesic object used in the constructor.
         **********************************************************************/
        property bool Exact
        {
            bool get( )
            {
                return impl_->Exact( );
            }
        }

        /**
         * @return \e caps the computational capabilities that this object was
         *   constructed with.  LATITUDE and AZIMUTH are always included.
         **********************************************************************/
        property GeodesicLineMask Capabilities
        {
            GeodesicLineMask get( )
            {
                return static_cast< GeodesicLineMask >( impl_->Capabilities( ) );
            }
        }

        /**
         * Test what capabilities are available.
         *
         * @param[in] testcaps a set of bitor'ed GeodesicLine::mask values.
         * @return true if the GeodesicLine object has all these capabilities.
         **********************************************************************/
        bool CheckCapabilities( GeodesicLineMask testCaps )
        {
            return impl_->Capabilities( static_cast< unsigned >( testCaps ) );
        }

        /**
         * The distance or arc length to point 3.
         *
         * @param[in] arcmode boolean flag determining the meaning of returned
         *   value.
         * @return \e s13 if \e arcmode is false; \e a13 if \e arcmode is true.
         **********************************************************************/
        double GenDistance( bool arcmode )
        {
            return impl_->GenDistance( arcmode );
        }

        /**
         * @return \e s13, the distance to point 3 (meters).
         **********************************************************************/
        property double Distance
        {
            double get( )
            {
                return impl_->Distance( );
            }
            void set( double value )
            {
                impl_->SetDistance( value );
            }
        }

        /**
         * @return \e a13, the arc length to point 3 (degrees).
         **********************************************************************/
        property double Arc
        {
            double get( )
            {
                return impl_->Arc( );
            }
            void set( double value )
            {
                impl_->SetArc( value );
            }
        }


    };
}
