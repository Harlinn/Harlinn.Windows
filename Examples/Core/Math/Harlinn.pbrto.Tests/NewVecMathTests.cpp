#include "pch.h"

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

#include <pbrto/util/NewRng.h>
#include <pbrto/util/rng.h>
#include <pbrto/util/NewSampling.h>
#include <pbrto/NewShapes.h>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Util::Test;

namespace
{
    pbrto::DirectionCone RandomCone( pbrto::RNG& rng )
    {
        pbrto::Vector3f w = pbrto::SampleUniformSphere( { rng.Uniform<float>( ), rng.Uniform<float>( ) } );
        return pbrto::DirectionCone( w, -1 + 2 * rng.Uniform<float>( ) );
    }
}


BOOST_FIXTURE_TEST_SUITE( NewVecMathTests, LocalFixture )

// --run_test=NewVecMathTests/Vector2BasicTest1
BOOST_AUTO_TEST_CASE( Vector2BasicTest1 )
{
    using Vector2f = pbrto::Vector2f;
    using Vector2i = pbrto::Vector2i;

    Vector2f vf( -1, 10 );
    BOOST_CHECK_EQUAL( vf, Vector2f( Vector2i( -1, 10 ) ) );
    BOOST_CHECK_NE( vf, Vector2f( -1, 100 ) );
    BOOST_CHECK_EQUAL( Vector2f( -2, 20 ), vf + vf );
    BOOST_CHECK_EQUAL( Vector2f( 0, 0 ), vf - vf );
    BOOST_CHECK_EQUAL( Vector2f( -2, 20 ), vf * 2 );
    BOOST_CHECK_EQUAL( Vector2f( -2, 20 ), 2 * vf );
    BOOST_CHECK_EQUAL( Vector2f( -0.5, 5 ), vf / 2 );
    BOOST_CHECK_EQUAL( Vector2f( 1, 10 ), Abs( vf ) );
    BOOST_CHECK_EQUAL( vf, Ceil( Vector2f( -1.5, 9.9 ) ) );
    BOOST_CHECK_EQUAL( vf, Floor( Vector2f( -.5, 10.01 ) ) );
    BOOST_CHECK_EQUAL( Vector2f( -20, 10 ), Min( vf, Vector2f( -20, 20 ) ) );
    BOOST_CHECK_EQUAL( Vector2f( -1, 20 ), Max( vf, Vector2f( -20, 20 ) ) );
    BOOST_CHECK_EQUAL( -1, MinComponentValue( vf ) );
    BOOST_CHECK_EQUAL( -10, MinComponentValue( -vf ) );
    BOOST_CHECK_EQUAL( 10, MaxComponentValue( vf ) );
    BOOST_CHECK_EQUAL( 1, MaxComponentValue( -vf ) );
    BOOST_CHECK_EQUAL( 1, MaxComponentIndex( vf ) );
    BOOST_CHECK_EQUAL( 0, MaxComponentIndex( -vf ) );
    BOOST_CHECK_EQUAL( 0, MinComponentIndex( vf ) );
    BOOST_CHECK_EQUAL( 1, MinComponentIndex( -vf ) );
    BOOST_CHECK_EQUAL( vf, pbrto::Permute( vf, { 0, 1 } ) );
    BOOST_CHECK_EQUAL( Vector2f( 10, -1 ), pbrto::Permute( vf, { 1, 0 } ) );
    BOOST_CHECK_EQUAL( Vector2f( 10, 10 ), pbrto::Permute( vf, { 1, 1 } ) );
}

// --run_test=NewVecMathTests/Vector3BasicTest1
BOOST_AUTO_TEST_CASE( Vector3BasicTest1 )
{
    using Vector3f = pbrto::Vector3f;
    using Vector3i = pbrto::Vector3i;

    Vector3f vf( -1, 10, 2 );
    BOOST_CHECK_EQUAL( vf, Vector3f( Vector3i( -1, 10, 2 ) ) );
    BOOST_CHECK_NE( vf, Vector3f( -1, 100, 2 ) );
    BOOST_CHECK_EQUAL( Vector3f( -2, 20, 4 ), vf + vf );
    BOOST_CHECK_EQUAL( Vector3f( 0, 0, 0 ), vf - vf );
    BOOST_CHECK_EQUAL( Vector3f( -2, 20, 4 ), vf * 2 );
    BOOST_CHECK_EQUAL( Vector3f( -2, 20, 4 ), 2 * vf );
    BOOST_CHECK_EQUAL( Vector3f( -0.5, 5, 1 ), vf / 2 );
    BOOST_CHECK_EQUAL( Vector3f( 1, 10, 2 ), Abs( vf ) );
    BOOST_CHECK_EQUAL( vf, Ceil( Vector3f( -1.5, 9.9, 1.01 ) ) );
    BOOST_CHECK_EQUAL( vf, Floor( Vector3f( -.5, 10.01, 2.99 ) ) );
    BOOST_CHECK_EQUAL( Vector3f( -20, 10, 1.5 ), Min( vf, Vector3f( -20, 20, 1.5 ) ) );
    BOOST_CHECK_EQUAL( Vector3f( -1, 20, 2 ), Max( vf, Vector3f( -20, 20, 0 ) ) );
    BOOST_CHECK_EQUAL( -1, MinComponentValue( vf ) );
    BOOST_CHECK_EQUAL( -10, MinComponentValue( -vf ) );
    BOOST_CHECK_EQUAL( 10, MaxComponentValue( vf ) );
    BOOST_CHECK_EQUAL( 1, MaxComponentValue( -vf ) );
    BOOST_CHECK_EQUAL( 1, MaxComponentIndex( vf ) );
    BOOST_CHECK_EQUAL( 0, MaxComponentIndex( -vf ) );
    BOOST_CHECK_EQUAL( 0, MinComponentIndex( vf ) );
    BOOST_CHECK_EQUAL( 1, MinComponentIndex( -vf ) );
    BOOST_CHECK_EQUAL( vf, Permute( vf, { 0, 1, 2 } ) );
    BOOST_CHECK_EQUAL( Vector3f( 10, -1, 2 ), Permute( vf, { 1, 0, 2 } ) );
    BOOST_CHECK_EQUAL( Vector3f( 2, -1, 10 ), Permute( vf, { 2, 0, 1 } ) );
    BOOST_CHECK_EQUAL( Vector3f( 10, 10, -1 ), Permute( vf, { 1, 1, 0 } ) );

}


// --run_test=NewVecMathTests/InvertBilinearTest1
BOOST_AUTO_TEST_CASE( InvertBilinearTest1 )
{
    auto bilerp = []( Point2f u, const Point2f* v ) 
        {
        return Lerp2( u[ 0 ], 
            Lerp2( u[ 1 ], v[ 0 ], v[ 2 ] ), 
            Lerp2( u[ 1 ], v[ 1 ], v[ 3 ] ) );
        };

    pbrto::RNG rng;
    std::array<Point2f,4> vRealSimple = { Point2f( 0, 0 ), Point2f( 1, 0 ), Point2f( 0, 1 ), Point2f( 1, 1 ) };
    for ( int i = 0; i < 100; ++i )
    {
        Point2f u{ rng.Uniform<float>( ), rng.Uniform<float>( ) };
        Point2f up = bilerp( u, vRealSimple.data() );
        auto distance1 = ScalarDistance( u, up );
        BOOST_CHECK_LT( distance1, 1e-5f );  // check bilerp
        auto distance2 = ScalarDistance( u, InvertBilinear( up, vRealSimple ) );
        BOOST_CHECK_LT( distance2, 1e-5f );
    }

    std::array<Point2f, 4> vSimple = { Point2f( 10, -4 ), Point2f( 10, -9 ), Point2f( 15, -4 ),
                          Point2f( 15, -9 ) };
    for ( int i = 0; i < 100; ++i )
    {
        Point2f u{ rng.Uniform<float>( ), rng.Uniform<float>( ) };
        Point2f up = bilerp( u, vSimple.data() );
        Point2f uinv = InvertBilinear( up, vSimple );
        BOOST_CHECK_LT( ScalarDistance( u, uinv ), 1e-5f );
    }

    for ( int i = 0; i < 100; ++i )
    {
        for ( int j = 0; j < 100; ++j )
        {
            Point2f u{ rng.Uniform<float>( ), rng.Uniform<float>( ) };
            Point2f up = bilerp( u, vSimple.data() );
            Point2f uinv = InvertBilinear( up, vSimple );
            BOOST_CHECK_LT( ScalarDistance( u, uinv ), 1e-5f );
        }
    }
}

// --run_test=NewVecMathTests/AngleBetweenTest1
BOOST_AUTO_TEST_CASE( AngleBetweenTest1 )
{
    BOOST_CHECK_EQUAL( 0, ScalarAngleBetween( Vector3f( 1, 0, 0 ), Vector3f( 1, 0, 0 ) ) );

    auto nearly = AreNearlyEqual( std::abs( ScalarAngleBetween( Vector3f( 0, 0, 1 ), Vector3f( 0, 0, -1 ) ) ), pbrto::Pi );
    BOOST_CHECK( nearly );
    nearly = AreNearlyEqual( std::abs( ScalarAngleBetween( Vector3f( 1, 0, 0 ), Vector3f( 0, 1, 0 ) ) ), static_cast< float >( pbrto::Pi ) / 2.f );
    BOOST_CHECK( nearly );

    Vector3f x = Normalize( Vector3f( 1, -3, 10 ) );
    BOOST_CHECK_EQUAL( 0, ScalarAngleBetween( x, x ) );
    BOOST_CHECK_LT( std::abs( ScalarAngleBetween( x, -x ) - pbrto::Pi ), 3e-7 );

    float maxErr = 0, sumErr = 0;
    for ( int i = 0; i < 100000; ++i )
    {
        pbrto::RNG rng( i );
        Vector3f a = Normalize( Vector3f( -1 + 2 * rng.Uniform<float>( ),
            -1 + 2 * rng.Uniform<float>( ),
            -1 + 2 * rng.Uniform<float>( ) ) );
        Vector3f b = Normalize( Vector3f( -1 + 2 * rng.Uniform<float>( ),
            -1 + 2 * rng.Uniform<float>( ),
            -1 + 2 * rng.Uniform<float>( ) ) );

        pbrto::Vector3<double> ad( a.x, a.y, a.z ), bd( b.x, b.y, b.z );
        ad = Normalize( ad );
        bd = Normalize( bd );

        float v[ 2 ] = { float( std::acos( ScalarDot( ad, bd ) ) ), ScalarAngleBetween( a, b ) };
        float err = std::abs( v[ 0 ] - v[ 1 ] ) / v[ 0 ];
        maxErr = std::max( err, maxErr );
        sumErr += err;
        BOOST_CHECK_LT( err, 5e-6 );
    }
    // CO    LOG(WARNING) << "MAXERR " << maxErr << ", sum " << sumErr;
    maxErr = 0;
    sumErr = 0;

    for ( int i = 0; i < 100000; ++i )
    {
        pbrto::RNG rng( i + 10000000 );
        Vector3f a = Normalize( Vector3f( -1 + 2 * rng.Uniform<float>( ),
            -1 + 2 * rng.Uniform<float>( ),
            -1 + 2 * rng.Uniform<float>( ) ) );
        Vector3f b = Normalize( Vector3f( -1 + 2 * rng.Uniform<float>( ),
            -1 + 2 * rng.Uniform<float>( ),
            -1 + 2 * rng.Uniform<float>( ) ) );
        // Make them face in opposite-ish directions
        a.x = std::copysign( a.x, -b.x );
        a.y = std::copysign( a.y, -b.y );
        a.z = std::copysign( a.z, -b.z );

        pbrto::Vector3<double> ad( a.x, a.y, a.z ), bd( b.x, b.y, b.z );
        ad = Normalize( ad );
        bd = Normalize( bd );

        float v[ 2 ] = { float( std::acos( ScalarDot( ad, bd ) ) ), ScalarAngleBetween( a, b ) };
        float err = std::abs( v[ 0 ] - v[ 1 ] ) / v[ 0 ];
        maxErr = std::max( err, maxErr );
        sumErr += err;
        BOOST_CHECK_LT( err, 5e-6 );
    }
    // CO    LOG(WARNING) << "MAXERR " << maxErr << ", sum " << sumErr;

    Vector3f a( 1, 1, 1 ), b( -1, -1.0001, -1 );
    a = Normalize( a );
    b = Normalize( b );
    pbrto::Vector3<long double> ad( 1, 1, 1 ), bd( -1, -1.0001, -1 );
    ad = Normalize( ad );
    bd = Normalize( bd );

    float naive = SafeACos( ScalarDot( a, b ) );
    float precise = std::acos( Clamp( ScalarDot( ad, bd ), -1, 1 ) );
    float abet = ScalarAngleBetween( a, b );
    BOOST_CHECK_EQUAL( abet, precise );
}

// --run_test=NewVecMathTests/CoordinateSystemTest1
BOOST_AUTO_TEST_CASE( CoordinateSystemTest1 )
{
    
    using Point2f = pbrto::Point2f;
    using Vector3f = pbrto::Vector3f;
    // Duff et al 2017 footnote 1
    auto error = []( Vector3f a, Vector3f b, Vector3f c ) 
        {
            return ( Sqr( ScalarLength( a ) - 1 ) + Sqr( ScalarLength( b ) - 1 ) + Sqr( ScalarLength( c ) - 1 ) +
                Sqr( ScalarDot( a, b ) ) + Sqr( ScalarDot( b, c ) ) + Sqr( ScalarDot( c, a ) ) ) / 6;
        };

    // Coordinate axes.
    Vector3f a, b;
    for ( Vector3f v : {Vector3f( 1, 0, 0 ), Vector3f( -1, 0, 0 ), Vector3f( 0, 1, 0 ),
        Vector3f( 0, -1, 0 ), Vector3f( 0, 0, 1 ), Vector3f( 0, 0, -1 )} )
    {
        pbrto::CoordinateSystem( v, &a, &b );
        for ( int c = 0; c < 3; ++c )
        {
            if ( v[ c ] != 0 )
            {
                BOOST_CHECK_EQUAL( 0, a[ c ] );
                BOOST_CHECK_EQUAL( 0, b[ c ] );
            }
        }
    }

    // Bad vectors from Duff et al
    for ( Vector3f v : {Vector3f( 0.00038527316, 0.00038460016, -0.99999988079 ),
        Vector3f( -0.00019813581, -0.00008946839, -0.99999988079 )} )
    {
        CoordinateSystem( v, &a, &b );
        BOOST_CHECK_LT( error( v, a, b ), 1e-10 );
    }

    // Random vectors
    pbrto::RNG rng;
    for ( int i = 0; i < 1000; ++i )
    {
        Point2f u = { rng.Uniform<float>( ), rng.Uniform<float>( ) };
        Vector3f v = pbrto::SampleUniformSphere( u );
        CoordinateSystem( v, &a, &b );
        BOOST_CHECK_LT( error( v, a, b ), 1e-10 );
    }
}

// --run_test=NewVecMathTests/IteratorBasicTest1
BOOST_AUTO_TEST_CASE( IteratorBasicTest1 )
{
    using Bounds2i = pbrto::Bounds2i;
    using Point2i = pbrto::Point2i;
    Bounds2i b{ {0, 1}, {2, 3} };
    Point2i e[ ] = { {0, 1}, {1, 1}, {0, 2}, {1, 2} };
    int offset = 0;
    for ( auto p : b )
    {
        BOOST_CHECK_LT( offset, PBRT_ARRAYSIZE( e ) );
        BOOST_CHECK_EQUAL( e[ offset ], p );
        ++offset;
    }
}

// --run_test=NewVecMathTests/IteratorDegenerateTest1
BOOST_AUTO_TEST_CASE( IteratorDegenerateTest1 )
{
    using Bounds2i = pbrto::Bounds2i;
    Bounds2i b{ {0, 0}, {0, 10} };
    for ( auto p : b )
    {
        // This loop should never run.
        bool reached = true;
        BOOST_CHECK( !reached );
        break;
    }

    Bounds2i b2{ {0, 0}, {4, 0} };
    for ( auto p : b2 )
    {
        // This loop should never run.
        bool reached = true;
        BOOST_CHECK( !reached );
        break;
    }

    Bounds2i b3;
    for ( auto p : b3 )
    {
        // This loop should never run.
        bool reached = true;
        BOOST_CHECK( !reached );
        break;
    }
}

// --run_test=NewVecMathTests/Bounds3PointDistanceTest1
BOOST_AUTO_TEST_CASE( Bounds3PointDistanceTest1 )
{
    using Bounds3f = pbrto::Bounds3f;
    using Point3f = pbrto::Point3f;
    {
        Bounds3f b( Point3f( 0, 0, 0 ), Point3f( 1, 1, 1 ) );

        // Points inside the bounding box or on faces
        BOOST_CHECK_EQUAL( 0., ScalarDistance( Point3f( .5, .5, .5 ), b ) );
        BOOST_CHECK_EQUAL( 0., ScalarDistance( Point3f( 0, 1, 1 ), b ) );
        BOOST_CHECK_EQUAL( 0., ScalarDistance( Point3f( .25, .8, 1 ), b ) );
        BOOST_CHECK_EQUAL( 0., ScalarDistance( Point3f( 0, .25, .8 ), b ) );
        BOOST_CHECK_EQUAL( 0., ScalarDistance( Point3f( .7, 0, .8 ), b ) );

        // Aligned with the plane of one of the faces
        BOOST_CHECK_EQUAL( 5., ScalarDistance( Point3f( 6, 1, 1 ), b ) );
        BOOST_CHECK_EQUAL( 10., ScalarDistance( Point3f( 0, -10, 1 ), b ) );

        // 2 of the dimensions inside the box's extent
        BOOST_CHECK_EQUAL( 2., ScalarDistance( Point3f( 0.5, 0.5, 3 ), b ) );
        BOOST_CHECK_EQUAL( 3., ScalarDistance( Point3f( 0.5, 0.5, -3 ), b ) );
        BOOST_CHECK_EQUAL( 2., ScalarDistance( Point3f( 0.5, 3, 0.5 ), b ) );
        BOOST_CHECK_EQUAL( 3., ScalarDistance( Point3f( 0.5, -3, 0.5 ), b ) );
        BOOST_CHECK_EQUAL( 2., ScalarDistance( Point3f( 3, 0.5, 0.5 ), b ) );
        BOOST_CHECK_EQUAL( 3., ScalarDistance( Point3f( -3, 0.5, 0.5 ), b ) );

        // General points
        BOOST_CHECK_EQUAL( 3 * 3 + 7 * 7 + 10 * 10, ScalarDistanceSquared( Point3f( 4, 8, -10 ), b ) );
        BOOST_CHECK_EQUAL( 6 * 6 + 10 * 10 + 7 * 7, ScalarDistanceSquared( Point3f( -6, -10, 8 ), b ) );
    }

    {
        // A few with a more irregular box, just to be sure
        Bounds3f b( Point3f( -1, -3, 5 ), Point3f( 2, -2, 18 ) );
        BOOST_CHECK_EQUAL( 0., ScalarDistance( Point3f( -.99, -2, 5 ), b ) );
        BOOST_CHECK_EQUAL( 2 * 2 + 6 * 6 + 4 * 4, ScalarDistanceSquared( Point3f( -3, -9, 22 ), b ) );
    }
}

// --run_test=NewVecMathTests/Bounds2UnionTest1
BOOST_AUTO_TEST_CASE( Bounds2UnionTest1 )
{
    using Bounds2f = pbrto::Bounds2f;
    using Point2f = pbrto::Point2f;
    Bounds2f a( Point2f( -10, -10 ), Point2f( 0, 20 ) );
    Bounds2f b;  // degenerate
    Bounds2f c = Union( a, b );
    BOOST_CHECK_EQUAL( a, c );

    BOOST_CHECK_EQUAL( b, Union( b, b ) );

    Bounds2f d( Point2f( -15, 10 ) );
    Bounds2f e = Union( a, d );
    BOOST_CHECK_EQUAL( Bounds2f( Point2f( -15, -10 ), Point2f( 0, 20 ) ), e );
}

// --run_test=NewVecMathTests/Bounds3UnionTest1
BOOST_AUTO_TEST_CASE( Bounds3UnionTest1 )
{
    using Bounds3f = pbrto::Bounds3f;
    using Point3f = pbrto::Point3f;
    Bounds3f a( Point3f( -10, -10, 5 ), Point3f( 0, 20, 10 ) );
    Bounds3f b;  // degenerate
    Bounds3f c = Union( a, b );
    BOOST_CHECK_EQUAL( a, c );

    BOOST_CHECK_EQUAL( b, Union( b, b ) );

    Bounds3f d( Point3f( -15, 10, 30 ) );
    Bounds3f e = Union( a, d );
    BOOST_CHECK_EQUAL( Bounds3f( Point3f( -15, -10, 5 ), Point3f( 0, 20, 30 ) ), e );
}

// --run_test=NewVecMathTests/EqualAreaRandomsTest1
BOOST_AUTO_TEST_CASE( EqualAreaRandomsTest1 )
{
    using Point2f = pbrto::Point2f;
    using Vector3f = pbrto::Vector3f;
    for ( Point2f u : pbrto::Uniform2D( 100 ) )
    {
        Vector3f v = pbrto::SampleUniformSphere( u );
        Point2f c = pbrto::EqualAreaSphereToSquare( v );
        Vector3f vp = pbrto::EqualAreaSquareToSphere( c );
        BOOST_CHECK( ScalarLength( vp ) > 0.9999 && ScalarLength( vp ) < 1.0001 );
        BOOST_CHECK_GT( ScalarDot( v, vp ), 0.9999 );
    }
}

// --run_test=NewVecMathTests/EqualAreaRemapEdgesTest1
BOOST_AUTO_TEST_CASE( EqualAreaRemapEdgesTest1 )
{
    using Vector3f = pbrto::Vector3f;
    using Point2f = pbrto::Point2f;

    auto checkClose = [ & ]( Point2f a, Point2f b ) 
        {
            Vector3f av = pbrto::EqualAreaSquareToSphere( a );
            b = pbrto::WrapEqualAreaSquare( b );
            Vector3f bv = pbrto::EqualAreaSquareToSphere( b );
            BOOST_CHECK_GT( ScalarDot( av, bv ), .99 );
        };

    checkClose( Point2f( .25, .01 ), Point2f( .25, -.01 ) );
    checkClose( Point2f( .89, .01 ), Point2f( .89, -.01 ) );

    checkClose( Point2f( .25, .99 ), Point2f( .25, 1.01 ) );
    checkClose( Point2f( .89, .99 ), Point2f( .89, 1.01 ) );

    checkClose( Point2f( .01, .66 ), Point2f( -.01, .66 ) );
    checkClose( Point2f( .01, .15 ), Point2f( -.01, .15 ) );

    checkClose( Point2f( .99, .66 ), Point2f( 1.01, .66 ) );
    checkClose( Point2f( .99, .15 ), Point2f( 1.01, .15 ) );

    checkClose( Point2f( .01, .01 ), Point2f( -.01, -.01 ) );
    checkClose( Point2f( .99, .01 ), Point2f( 1.01, -.01 ) );
    checkClose( Point2f( .01, .99 ), Point2f( -.01, 1.01 ) );
    checkClose( Point2f( .99, .99 ), Point2f( 1.01, 1.01 ) );
}

// --run_test=NewVecMathTests/DirectionConeUnionBasicsTest1
BOOST_AUTO_TEST_CASE( DirectionConeUnionBasicsTest1 )
{
    using pbrto::Pi;
    using Vector3f = pbrto::Vector3f;
    using Point2f = pbrto::Point2f;
    using DirectionCone = pbrto::DirectionCone;

    // First encloses second
    DirectionCone c = Union( DirectionCone( Vector3f( 0, 0, 1 ), std::cos( Pi / 2 ) ),
        DirectionCone( Vector3f( .1, .1, 1 ), std::cos( .1 ) ) );
    BOOST_CHECK_EQUAL( c.w, Vector3f( 0, 0, 1 ) );
    BOOST_CHECK_EQUAL( c.cosTheta, std::cos( Pi / 2 ) );

    // Second encloses first
    c = Union( DirectionCone( Vector3f( .1, .1, 1 ), std::cos( .1 ) ),
        DirectionCone( Vector3f( 0, 0, 1 ), std::cos( Pi / 2 ) ) );
    BOOST_CHECK_EQUAL( c.w, Vector3f( 0, 0, 1 ) );
    BOOST_CHECK_EQUAL( c.cosTheta, std::cos( Pi / 2 ) );

    // Same direction, first wider
    Vector3f w( 1, .5, -.25 );
    c = Union( DirectionCone( w, std::cos( .12 ) ), DirectionCone( w, std::cos( .03 ) ) );
    BOOST_CHECK_EQUAL( Normalize( w ), c.w );
    BOOST_CHECK( AreNearlyEqual( std::cos( .12f ), c.cosTheta ));

    // Same direction, second wider
    c = Union( DirectionCone( w, std::cos( .1 ) ), DirectionCone( w, std::cos( .2 ) ) );
    BOOST_CHECK_EQUAL( Normalize( w ), c.w );
    BOOST_CHECK( AreNearlyEqual( std::cos( .2f ), c.cosTheta ) );

    // Exactly pointing in opposite directions and covering the sphere when
    // it's all said and done.
    c = Union( DirectionCone( Vector3f( -1, -1, -1 ), std::cos( Pi / 2 ) ),
        DirectionCone( Vector3f( 1, 1, 1 ), std::cos( Pi / 2 ) ) );
    BOOST_CHECK_EQUAL( c.cosTheta, std::cos( Pi ) );

    // Basically opposite and a bit more than pi/2: should also be the
    // whole sphere.
    c = Union( DirectionCone( Vector3f( -1, -1, -1 ), std::cos( 1.01 * Pi / 2 ) ),
        DirectionCone( Vector3f( 1.001, 1, 1 ), std::cos( 1.01 * Pi / 2 ) ) );
    BOOST_CHECK_EQUAL( c.cosTheta, std::cos( Pi ) );

    // Narrow and at right angles; angle should be their midpoint
    c = Union( DirectionCone( Vector3f( 1, 0, 0 ), std::cos( 1e-3 ) ),
        DirectionCone( Vector3f( 0, 1, 0 ), std::cos( 1e-3 ) ) );
    BOOST_CHECK( AreNearlyEqual( 1.f, ScalarDot( c.w, Normalize( Vector3f( 1, 1, 0 ) ) ) ) );
    BOOST_CHECK_LT( std::abs( std::cos( ( Pi / 2 + 2e-3 ) / 2 ) - c.cosTheta ), 1e-3 );
}


// --run_test=NewVecMathTests/DirectionConeUnionRandomsTest1
BOOST_AUTO_TEST_CASE( DirectionConeUnionRandomsTest1 )
{
    using pbrto::Pi;
    using Vector3f = pbrto::Vector3f;
    using Point2f = pbrto::Point2f;
    using DirectionCone = pbrto::DirectionCone;
    using RNG = pbrto::RNG;

    RNG rng( 16 );

    for ( int i = 0; i < 100; ++i )
    {
        DirectionCone a = RandomCone( rng ), b = RandomCone( rng );
        DirectionCone c = Union( a, b );

        for ( int j = 0; j < 100; ++j )
        {
            Vector3f w = pbrto::SampleUniformSphere( { rng.Uniform<float>( ), rng.Uniform<float>( ) } );
            if ( Inside( a, w ) || Inside( b, w ) )
                BOOST_CHECK( Inside( c, w ) );
        }
    }
}

// --run_test=NewVecMathTests/DirectionConeBoundBoundsTest1
BOOST_AUTO_TEST_CASE( DirectionConeBoundBoundsTest1 )
{
    using Float = float;
    using pbrto::Pi;
    using Vector3f = pbrto::Vector3f;
    using Point2f = pbrto::Point2f;
    using Point3f = pbrto::Point3f;
    using Bounds3f = pbrto::Bounds3f;
    using Ray = pbrto::Ray;
    using DirectionCone = pbrto::DirectionCone;
    using RNG = pbrto::RNG;

    Bounds3f b( Point3f( 0, 0, 0 ), Point3f( 1, 1, 1 ) );

    // Point inside the bbox
    DirectionCone c = BoundSubtendedDirections( b, Point3f( .1, .2, .3 ) );
    BOOST_CHECK_EQUAL( std::cos( Pi ), c.cosTheta );

    // Outside, .5 units away in the middle (so using the direction to the
    // center gives the best bound).
    //
    // tan theta = (sqrt(.5^2 + .5^2)) / .5
    c = BoundSubtendedDirections( b, Point3f( -.5, .5, .5 ) );
    Float theta = std::acos( c.cosTheta );
    Float precise = std::atan( std::sqrt( .5 * .5 + .5 * .5 ) / .5 );
    // Make sure the returned bound isn't too small.
    BOOST_CHECK_GE( theta, 1.0001 * precise );
    // It's fine for it to be a bit big (as it is in practice due to
    // approximations for performance), but it shouldn't be too big.
    BOOST_CHECK_LT( theta, 1.1 * precise );

    RNG rng( 512 );
    for ( int i = 0; i < 1000; ++i )
    {
        Bounds3f b(
            Point3f( pbrto::Lerp2( rng.Uniform<Float>( ), -1, 1 ), pbrto::Lerp2( rng.Uniform<Float>( ), -1, 1 ),
                pbrto::Lerp2( rng.Uniform<Float>( ), -1, 1 ) ),
            Point3f( pbrto::Lerp2( rng.Uniform<Float>( ), -1, 1 ), pbrto::Lerp2( rng.Uniform<Float>( ), -1, 1 ),
                pbrto::Lerp2( rng.Uniform<Float>( ), -1, 1 ) ) );

        Point3f p( pbrto::Lerp2( rng.Uniform<Float>( ), -4, 4 ), pbrto::Lerp2( rng.Uniform<Float>( ), -4, 4 ),
            pbrto::Lerp2( rng.Uniform<Float>( ), -4, 4 ) );

        c = BoundSubtendedDirections( b, p );
        if ( Inside( p, b ) )
        {
            BOOST_CHECK_EQUAL( std::cos( Pi ), c.cosTheta );
        }
        else
        {
            Vector3f wx, wy;
            CoordinateSystem( Vector3f(c.w), &wx, &wy );
            for ( int j = 0; j < 1000; ++j )
            {
                Point2f u( rng.Uniform<Float>( ), rng.Uniform<Float>( ) );
                Vector3f w = SampleUniformSphere( u );
                Ray r( p, w );
                bool hit = b.IntersectP( r.o, r.d );
                if ( hit )
                {
                    BOOST_CHECK( Inside( c, w ) );
                }
                if ( !Inside( c, w ) )
                {
                    BOOST_CHECK( !hit );
                }
            }
        }
    }
}

// --run_test=NewVecMathTests/DirectionConeVectorInConeTest1
BOOST_AUTO_TEST_CASE( DirectionConeVectorInConeTest1 )
{
    using Float = float;
    using pbrto::Pi;
    using Vector3f = pbrto::Vector3f;
    using Point2f = pbrto::Point2f;
    using Point3f = pbrto::Point3f;
    using Bounds3f = pbrto::Bounds3f;
    using Frame = pbrto::Frame;
    using DirectionCone = pbrto::DirectionCone;
    using RNG = pbrto::RNG;

    RNG rng;
    for ( int i = 0; i < 100; ++i )
    {
        DirectionCone dc = RandomCone( rng );

        for ( int j = 0; j < 100; ++j )
        {
            Vector3f wRandom = pbrto::SampleUniformSphere( { rng.Uniform<Float>( ), rng.Uniform<Float>( ) } );
            Vector3f wClosest = dc.ClosestVectorInCone( wRandom );

            if ( Inside( dc, wRandom ) )
                BOOST_CHECK_GT( ScalarDot( wClosest, wRandom ), .999 );
            else
            {
                // Uniformly sample the circle at the cone's boundary and
                // keep the vector that's closest to wRandom.
                Float sinTheta = SafeSqrt( 1 - dc.cosTheta * dc.cosTheta );
                Frame f = Frame::FromZ( dc.w );

                Vector3f wBest;
                Float bestDot = -1;
                const int nk = 1000;
                for ( int k = 0; k < nk; ++k )
                {
                    Float phi = ( k + .5 ) / nk * 2 * Pi;
                    Vector3f w = pbrto::SphericalDirection( sinTheta, dc.cosTheta, phi );
                    w = f.FromLocal( w );
                    if ( ScalarDot( w, wRandom ) > bestDot )
                    {
                        wBest = w;
                        bestDot = ScalarDot( w, wRandom );
                    }
                }
                BOOST_CHECK_GT( ScalarDot( wBest, wClosest ), .999 );
            }
        }
    }
}

// --run_test=NewVecMathTests/SphericalTriangleAreaBasicsTest1
BOOST_AUTO_TEST_CASE( SphericalTriangleAreaBasicsTest1 )
{
    using Float = float;
    using pbrto::Pi;
    using Vector3f = pbrto::Vector3f;
    using Point2f = pbrto::Point2f;
    using Point3f = pbrto::Point3f;
    using Transform = pbrto::Transform;
    using RNG = pbrto::RNG;

    {
        Float a = pbrto::SphericalTriangleArea( Vector3f( 1, 0, 0 ), Vector3f( 0, 1, 0 ), Vector3f( 0, 0, 1 ) );
        BOOST_CHECK( a >= .9999 * Pi / 2 && a <= 1.00001 * Pi / 2 );
    }

    {
        Float a = SphericalTriangleArea( Vector3f( 1, 0, 0 ), Normalize( Vector3f( 1, 1, 0 ) ), Vector3f( 0, 0, 1 ) );
        BOOST_CHECK( a >= .9999 * Pi / 4 && a <= 1.00001 * Pi / 4 );
    }

    // Random rotations
    RNG rng;
    for ( int i = 0; i < 100; ++i )
    {
        Vector3f axis = pbrto::SampleUniformSphere( { rng.Uniform<Float>( ), rng.Uniform<Float>( ) } );
        Float theta = 2 * Pi * rng.Uniform<Float>( );
        Transform t = Rotate( theta, axis );
        Vector3f va = t( Vector3f::Simd( 1, 0, 0 ) );
        Vector3f vb = t( Vector3f::Simd( 0, 1, 0 ) );
        Vector3f vc = t( Vector3f::Simd( 0, 0, 1 ) );
        Float a = pbrto::SphericalTriangleArea( va, vb, vc );
        BOOST_CHECK( a >= .9999 * Pi / 2 && a <= 1.0001 * Pi / 2 );
    }

    for ( int i = 0; i < 100; ++i )
    {
        Vector3f axis = pbrto::SampleUniformSphere( { rng.Uniform<Float>( ), rng.Uniform<Float>( ) } );
        Float theta = 2 * Pi * rng.Uniform<Float>( );
        Transform t = Rotate( theta, axis );
        Vector3f va = t( Vector3f::Simd( 1, 0, 0 ) );
        Vector3f vb = t( Normalize( Vector3f::Simd( 1, 1, 0 ) ) );
        Vector3f vc = t( Vector3f::Simd( 0, 0, 1 ) );
        Float a = SphericalTriangleArea( va, vb, vc );
        BOOST_CHECK( a >= .9999 * Pi / 4 && a <= 1.0001 * Pi / 4 );
    }
}

// --run_test=NewVecMathTests/SphericalTriangleAreaRandomSamplingTest1
BOOST_AUTO_TEST_CASE( SphericalTriangleAreaRandomSamplingTest1 )
{
    using Float = float;
    using pbrto::Pi;
    using pbrto::Infinity;
    using Vector3f = pbrto::Vector3f;
    using Point2f = pbrto::Point2f;
    using Point3f = pbrto::Point3f;
    using Frame = pbrto::Frame;
    using Ray = pbrto::Ray;
    using Transform = pbrto::Transform;
    using RNG = pbrto::RNG;

    for ( int i = 0; i < 100; ++i )
    {
        RNG rng( i );
        Vector3f a = pbrto::SampleUniformSphere( { rng.Uniform<Float>( ), rng.Uniform<Float>( ) } );
        Vector3f b = pbrto::SampleUniformSphere( { rng.Uniform<Float>( ), rng.Uniform<Float>( ) } );
        Vector3f c = pbrto::SampleUniformSphere( { rng.Uniform<Float>( ), rng.Uniform<Float>( ) } );

        Vector3f axis = Normalize( a + b + c );
        Frame frame = Frame::FromZ( axis );
        Float cosTheta = std::min( { ScalarDot( a, axis ), ScalarDot( b, axis ), ScalarDot( c, axis ) } );

        Float area = SphericalTriangleArea( a, b, c );
        bool sampleSphere = area > Pi;
        int sqrtN = 200;
        int count = 0;
        for ( Point2f u : pbrto::Hammersley2D( sqrtN* sqrtN ) )
        {
            Vector3f v;
            if ( sampleSphere )
                v = pbrto::SampleUniformSphere( u );
            else
            {
                v = pbrto::SampleUniformCone( u, cosTheta );
                v = frame.FromLocal( v );
            }

            if ( pbrto::IntersectTriangle( Ray( Point3f( 0, 0, 0 ), v ), Infinity, Point3f( a ), Point3f( b ), Point3f( c ) ) )
                ++count;
        }

        Float pdf = sampleSphere ? pbrto::UniformSpherePDF( ) : pbrto::UniformConePDF( cosTheta );
        Float estA = Float( count ) / ( sqrtN * sqrtN * pdf );

        Float error = std::abs( ( estA - area ) / area );
        BOOST_CHECK_LT( error, 0.035f );
    }
}


// --run_test=NewVecMathTests/OctahedralVectorEncodeDecodeTest1
BOOST_AUTO_TEST_CASE( OctahedralVectorEncodeDecodeTest1 )
{
    for ( pbrto::Point2 u : pbrto::Hammersley2D( 65535 ) )
    {
        Vector3f::Simd v = pbrto::SampleUniformSphere( u );

        pbrto::OctahedralVector ov( v );
        pbrto::Vector3f v2 = pbrto::Vector3f( ov );

        BOOST_CHECK_GT( ScalarLength( v2 ), .999f );
        BOOST_CHECK_LT( ScalarLength( v2 ), 1.001f );
        BOOST_CHECK_LT( std::abs( 1 - ScalarDot( v2, v ) ), .001f );
    }
}


BOOST_AUTO_TEST_SUITE_END( )