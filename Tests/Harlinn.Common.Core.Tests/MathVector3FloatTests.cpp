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

#include "pch.h"

#include <HCCVectorMath.h>


using namespace Harlinn::Common::Core;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

}
BOOST_FIXTURE_TEST_SUITE( MathVector3FloatTests, LocalFixture )

// --run_test=MathVector3FloatTests/AddTest1
BOOST_AUTO_TEST_CASE( AddTest1 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 1.0f, 2.0f, 3.f );
    Vector v2( 1.0f, 2.0f, 3.f );
    Vector v3 = v1 + v2 + v1 + v2 + v1 + v2;

    bool xAsExpected = v3.x == 6.f;
    bool yAsExpected = v3.y == 12.f;
    bool zAsExpected = v3.z == 18.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}


// --run_test=MathVector3FloatTests/SubTest1
BOOST_AUTO_TEST_CASE( SubTest1 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 6.0f, 12.0f, 7.f );
    Vector v2( 1.0f, 2.0f, 1.f );
    Vector v3 = v1 - v2 - v2 - v2 - v2 - v2;

    bool xAsExpected = v3.x == 1.f;
    bool yAsExpected = v3.y == 2.f;
    bool zAsExpected = v3.z == 2.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}

// --run_test=MathVector3FloatTests/MulTest1
BOOST_AUTO_TEST_CASE( MulTest1 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 2.0f, 3.0f, 4.f );
    Vector v2( 2.0f, 3.0f, 4.f );
    Vector v3 = v1 * v2;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 9.f;
    bool zAsExpected = v3.z == 16.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}

// --run_test=MathVector3FloatTests/MulTest2
BOOST_AUTO_TEST_CASE( MulTest2 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 2.0f, 3.0f, 4.f );
    Vector v2( 2.0f, 3.0f, 4.f );
    Vector v3 = v1 * v2 * 2.f;

    bool xAsExpected = v3.x == 8.f;
    bool yAsExpected = v3.y == 18.f;
    bool zAsExpected = v3.z == 32.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}

// --run_test=MathVector3FloatTests/MulTest3
BOOST_AUTO_TEST_CASE( MulTest3 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 2.0f, 3.0f, 4.f );
    Vector v3 = v1 * 2.f;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;
    bool zAsExpected = v3.z == 8.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}

// --run_test=MathVector3FloatTests/MulTest4
BOOST_AUTO_TEST_CASE( MulTest4 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 2.0f, 3.0f, 4.f );
    Vector v3 = 2.f * v1;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;
    bool zAsExpected = v3.z == 8.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}

// --run_test=MathVector3FloatTests/DivTest1
BOOST_AUTO_TEST_CASE( DivTest1 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 4.0f, 9.0f, 12.f );
    Vector v2( 2.0f, 3.0f, 4.f );
    Vector v3 = v1 / v2;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;
    bool zAsExpected = v3.z == 3.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}

// --run_test=MathVector3FloatTests/DivTest2
BOOST_AUTO_TEST_CASE( DivTest2 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 4.0f, 6.0f, 8.f );

    Vector v3 = v1 / 2.f;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;
    bool zAsExpected = v3.z == 4.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}

// --run_test=MathVector3FloatTests/AngleBetweenTest2
BOOST_AUTO_TEST_CASE( AngleBetweenTest2 )
{
    using Vector = Math::Vector<float, 3>;

    Vector v1( 2.0f, 2.0f, 2.f );
    Vector v2( 2.0f, 0.0f, 2.f );

    Vector v3 = AngleBetween( v1, v2 );;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;
    bool zAsExpected = v3.z == 4.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
}



BOOST_AUTO_TEST_SUITE_END( )