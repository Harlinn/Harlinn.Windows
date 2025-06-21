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
BOOST_FIXTURE_TEST_SUITE( MathVector4DoubleTests, LocalFixture )

// --run_test=MathVector4DoubleTests/AddTest1
BOOST_AUTO_TEST_CASE( AddTest1 )
{
    using Vector = Math::Vector<double, 4>;

    Vector v1( 1.0, 2.0, 3., 1.0 );
    Vector v2( 1.0, 2.0, 3., 1.0 );
    Vector v3 = v1 + v2 + v1 + v2 + v1 + v2;

    bool xAsExpected = v3.x == 6.;
    bool yAsExpected = v3.y == 12.;
    bool zAsExpected = v3.z == 18.;
    bool wAsExpected = v3.w == 6.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}


// --run_test=MathVector4DoubleTests/SubTest1
BOOST_AUTO_TEST_CASE( SubTest1 )
{
    using Vector = Math::Vector<double, 4>;

    Vector v1( 6.0, 12.0, 7., 6.0 );
    Vector v2( 1.0, 2.0, 1., 1.0 );
    Vector v3 = v1 - v2 - v2 - v2 - v2 - v2;

    bool xAsExpected = v3.x == 1.;
    bool yAsExpected = v3.y == 2.;
    bool zAsExpected = v3.z == 2.;
    bool wAsExpected = v3.w == 1.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4DoubleTests/MulTest1
BOOST_AUTO_TEST_CASE( MulTest1 )
{
    using Vector = Math::Vector<double, 4>;

    Vector v1( 2.0, 3.0, 4., 2.0 );
    Vector v2( 2.0, 3.0, 4., 2.0 );
    Vector v3 = v1 * v2;

    bool xAsExpected = v3.x == 4.;
    bool yAsExpected = v3.y == 9.;
    bool zAsExpected = v3.z == 16.;
    bool wAsExpected = v3.w == 4.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4DoubleTests/MulTest2
BOOST_AUTO_TEST_CASE( MulTest2 )
{
    using Vector = Math::Vector<double, 4>;

    Vector v1( 2.0, 3.0, 4., 2.0 );
    Vector v2( 2.0, 3.0, 4., 2.0 );
    Vector v3 = v1 * v2 * 2.;

    bool xAsExpected = v3.x == 8.;
    bool yAsExpected = v3.y == 18.;
    bool zAsExpected = v3.z == 32.;
    bool wAsExpected = v3.w == 8.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4DoubleTests/MulTest3
BOOST_AUTO_TEST_CASE( MulTest3 )
{
    using Vector = Math::Vector<double, 4>;

    Vector v1( 2.0, 3.0, 4., 2.0 );
    Vector v3 = v1 * 2.;

    bool xAsExpected = v3.x == 4.;
    bool yAsExpected = v3.y == 6.;
    bool zAsExpected = v3.z == 8.;
    bool wAsExpected = v3.w == 4.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4DoubleTests/MulTest4
BOOST_AUTO_TEST_CASE( MulTest4 )
{
    using Vector = Math::Vector<double, 4>;

    Vector v1( 2.0, 3.0, 4., 2.0 );
    Vector v3 = 2. * v1;

    bool xAsExpected = v3.x == 4.;
    bool yAsExpected = v3.y == 6.;
    bool zAsExpected = v3.z == 8.;
    bool wAsExpected = v3.w == 4.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4DoubleTests/DivTest1
BOOST_AUTO_TEST_CASE( DivTest1 )
{
    using Vector = Math::Vector<double, 4>;

    Vector v1( 4.0, 9.0, 12., 4.0 );
    Vector v2( 2.0, 3.0, 4., 2.0 );
    Vector v3 = v1 / v2;

    bool xAsExpected = v3.x == 2.;
    bool yAsExpected = v3.y == 3.;
    bool zAsExpected = v3.z == 3.;
    bool wAsExpected = v3.w == 2.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}

// --run_test=MathVector4DoubleTests/DivTest2
BOOST_AUTO_TEST_CASE( DivTest2 )
{
    using Vector = Math::Vector<double, 4>;

    Vector v1( 4.0, 6.0, 8., 4.0 );

    Vector v3 = v1 / 2.;

    bool xAsExpected = v3.x == 2.;
    bool yAsExpected = v3.y == 3.;
    bool zAsExpected = v3.z == 4.;
    bool wAsExpected = v3.w == 2.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
    BOOST_CHECK( zAsExpected );
    BOOST_CHECK( wAsExpected );
}


BOOST_AUTO_TEST_SUITE_END( )