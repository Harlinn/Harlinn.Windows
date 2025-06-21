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

#include <Harlinn/Math/Segment.h>


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

BOOST_FIXTURE_TEST_SUITE( SegmentTests, LocalFixture )

// --run_test=SegmentTests/SegmentDistanceTest1
BOOST_AUTO_TEST_CASE( SegmentDistanceTest1 )
{
    Point3f A( 4, 2, 1 );
    Point3f B( 1, 0, 1 );
    Point3f C( 1, 2, 0 );

    Segment3<float> segment( B, C );

    auto distanceResult = segment.Distance( A );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint = distanceResult.ClosestPoint( );
    auto fraction = distanceResult.Fraction( );

    auto expectedX = 1.f;
    auto expectedY = 8.f / 5.f;
    auto expectedZ = 1.f / 5.f;

    BOOST_CHECK( closestPoint.x == expectedX );
    BOOST_CHECK( closestPoint.y == expectedY );
    BOOST_CHECK_CLOSE( closestPoint.z, expectedZ, 0.001f );
}

// --run_test=SegmentTests/SegmentDistanceTest2
BOOST_AUTO_TEST_CASE( SegmentDistanceTest2 )
{
    Point3f A( 2, 3, 6 );
    Point3f B( 1, 2, 1 );
    Point3f C( 1, 2, 5 );

    Segment3<float> segment( B, C );

    auto distanceResult = segment.Distance( A );

    auto distance = distanceResult.Distance( );
    Point3f closestPoint = distanceResult.ClosestPoint( );
    auto fraction = distanceResult.Fraction( );
    BOOST_CHECK( closestPoint == C );
}



BOOST_AUTO_TEST_SUITE_END( )