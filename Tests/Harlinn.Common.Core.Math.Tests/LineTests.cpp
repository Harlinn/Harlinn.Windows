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

#include "pch.h"

#include <Harlinn/Math/Line.h>
#include <Harlinn/Math/Distance.h>


using namespace Harlinn::Common::Core;
using namespace Harlinn::Math;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };


}

BOOST_FIXTURE_TEST_SUITE( LineTests, LocalFixture )

// --run_test=LineTests/LineDistanceTest1
BOOST_AUTO_TEST_CASE( LineDistanceTest1 )
{
    Point3f lineOrigin( 0.f, 0.f, -3.f );
    Vector3f lineDirection( Normalize( Vector3f( 2.5f, 2.5f, 2.5f ) ) );
    Point3f point( 1.f, 1.f, 1.f );

    Line3f line( lineOrigin, lineDirection );

    auto distanceResult = Distance( point, line );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint = distanceResult.ClosestPoint( );
    auto distanceFromOrigin = distanceResult.DistanceFromOrigin( );

    BOOST_CHECK( closestPoint.x == 2.f );
    BOOST_CHECK( closestPoint.y == 2.f );
    BOOST_CHECK( closestPoint.z == -1.f );
}

// --run_test=LineTests/LineDistanceTest2
BOOST_AUTO_TEST_CASE( LineDistanceTest2 )
{
    Point3f A( 4, 2, 1 );
    Point3f B( 1, 0, 1 );
    Point3f C( 1, 2, 0 );

    Line3f line( B, C );

    auto distanceResult = Distance( A, line );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint = distanceResult.ClosestPoint( );
    auto distanceFromOrigin = distanceResult.DistanceFromOrigin( );

    auto expectedX = 1.f;
    auto expectedY = 8.f / 5.f;
    auto expectedZ = 1.f / 5.f;

    BOOST_CHECK( closestPoint.x == expectedX );
    BOOST_CHECK( closestPoint.y == expectedY );
    BOOST_CHECK_CLOSE( closestPoint.z, expectedZ, 0.001f );
}

// --run_test=LineTests/LineDistanceTest3
BOOST_AUTO_TEST_CASE( LineDistanceTest3 )
{
    Point3f A( -1, -2, -2 );
    Point3f B( 1, 1, 1 );
    Point3f C( 1, 2, 2 );
    Point3f D( 1, 2, 0 );

    Line3f line1( A, B );
    Line3f line2( C, D );
    auto distanceResult = Distance( line1, line2 );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint1 = distanceResult.ClosestPoint1( );
    Point3f closestPoint2 = distanceResult.ClosestPoint2( );

    BOOST_CHECK( distance == 0.554700255f );
    
    BOOST_CHECK( closestPoint1.x == 1.46153855f );
    BOOST_CHECK( closestPoint1.y == 1.69230771f );
    BOOST_CHECK( closestPoint1.z == 1.69230771f );

    BOOST_CHECK( closestPoint2.x == 1.00000000f );
    BOOST_CHECK( closestPoint2.y == 2.00000000f );
    BOOST_CHECK( closestPoint2.z == 1.69230759f );

}

// --run_test=LineTests/LineDistanceTest4
BOOST_AUTO_TEST_CASE( LineDistanceTest4 )
{
    Point3f A( 0, 0, 0 );
    Point3f B( 1, 2, 3 );
    Point3f C( 1, 1, 1 );
    Point3f D( 2, 3, 5 );

    Line3f line1( A, B );
    Line3f line2( C, D );
    auto distanceResult = Distance( line1, line2 );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint1 = distanceResult.ClosestPoint1( );
    Point3f closestPoint2 = distanceResult.ClosestPoint2( );

    auto expectedDistance = Sqrt( 5.f ) / 5.f;

    BOOST_CHECK( distance == expectedDistance );

    BOOST_CHECK( closestPoint1.x == 1.40000772f );
    BOOST_CHECK( closestPoint1.y == 2.80001545f );
    BOOST_CHECK( closestPoint1.z == 4.20002317f );

    BOOST_CHECK( closestPoint2.x == 1.80000710f );
    BOOST_CHECK( closestPoint2.y == 2.60001421f );
    BOOST_CHECK( closestPoint2.z == 4.20002842f );

}



BOOST_AUTO_TEST_SUITE_END( )
