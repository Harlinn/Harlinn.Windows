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

#include "pch.h"

#include <Harlinn/Math/VectorMath.h>

using namespace Harlinn;
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
BOOST_FIXTURE_TEST_SUITE( MathVector4FloatTests, LocalFixture )

// --run_test=MathVector4FloatTests/AddTest1
BOOST_AUTO_TEST_CASE( AddTest1 )
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 1.0f, 2.0f, 3.f, 1.0f );
    Vector v2( 1.0f, 2.0f, 3.f, 1.0f );
    Vector v3 = v1 + v2 + v1 + v2 + v1 + v2;

    bool xAsExpected = v3.x == 6.f;
    bool yAsExpected = v3.y == 12.f;
    bool zAsExpected = v3.z == 18.f;
    bool wAsExpected = v3.w == 6.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}


// --run_test=MathVector4FloatTests/SubTest1
BOOST_AUTO_TEST_CASE( SubTest1 )
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 6.0f, 12.0f, 7.f, 6.0f );
    Vector v2( 1.0f, 2.0f, 1.f, 1.0f );
    Vector v3 = v1 - v2 - v2 - v2 - v2 - v2;

    bool xAsExpected = v3.x == 1.f;
    bool yAsExpected = v3.y == 2.f;
    bool zAsExpected = v3.z == 2.f;
    bool wAsExpected = v3.w == 1.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4FloatTests/MulTest1
BOOST_AUTO_TEST_CASE( MulTest1 )
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v2( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = v1 * v2;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 9.f;
    bool zAsExpected = v3.z == 16.f;
    bool wAsExpected = v3.w == 4.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4FloatTests/MulTest2
BOOST_AUTO_TEST_CASE( MulTest2 )
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v2( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = v1 * v2 * 2.f;

    bool xAsExpected = v3.x == 8.f;
    bool yAsExpected = v3.y == 18.f;
    bool zAsExpected = v3.z == 32.f;
    bool wAsExpected = v3.w == 8.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4FloatTests/MulTest3
BOOST_AUTO_TEST_CASE( MulTest3 )
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = v1 * 2.f;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;
    bool zAsExpected = v3.z == 8.f;
    bool wAsExpected = v3.w == 4.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4FloatTests/MulTest4
BOOST_AUTO_TEST_CASE( MulTest4 )
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = 2.f * v1;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;
    bool zAsExpected = v3.z == 8.f;
    bool wAsExpected = v3.w == 4.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4FloatTests/DivTest1
BOOST_AUTO_TEST_CASE( DivTest1 )
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 4.0f, 9.0f, 12.f, 4.0f );
    Vector v2( 2.0f, 3.0f, 4.f, 2.0f );
    Vector v3 = v1 / v2;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;
    bool zAsExpected = v3.z == 3.f;
    bool wAsExpected = v3.w == 2.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4FloatTests/DivTest2
BOOST_AUTO_TEST_CASE( DivTest2 )
{
    using Vector = Math::Vector<float, 4>;

    Vector v1( 4.0f, 6.0f, 8.f, 4.0f );

    Vector v3 = v1 / 2.f;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;
    bool zAsExpected = v3.z == 4.f;
    bool wAsExpected = v3.w == 2.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4FloatTests/OuterProductTest
BOOST_AUTO_TEST_CASE( OuterProductTest )
{
    Vector4f a( 5, 4, 3, 2 );
    Vector4f b( 3, 5, 7, 9 );
    SquareMatrix<float, 4> m = OuterProduct( a, b );
    Vector4f r1 = m[ 0 ];
    Vector4f r2 = m[ 1 ];
    Vector4f r3 = m[ 2 ];
    Vector4f r4 = m[ 3 ];


    Vector4f expectedR1( 15, 25, 35, 45 );
    Vector4f expectedR2( 12, 20, 28, 36 );
    Vector4f expectedR3( 9, 15, 21, 27 );
    Vector4f expectedR4( 6, 10, 14,	18 );



    BOOST_CHECK( r1 == expectedR1 );
    BOOST_CHECK( r2 == expectedR2 );
    BOOST_CHECK( r3 == expectedR3 );
    BOOST_CHECK( r4 == expectedR4 );
}


BOOST_AUTO_TEST_SUITE_END( )