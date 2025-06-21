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
BOOST_FIXTURE_TEST_SUITE( MathVector2DoubleTests, LocalFixture )

// --run_test=MathVector2DoubleTests/AddTest1
BOOST_AUTO_TEST_CASE( AddTest1 )
{
    using Vector = Math::Vector<double, 2>;

    Vector v1( 1.0, 2.0 );
    Vector v2( 1.0, 2.0 );
    Vector v3 = v1 + v2 + v1 + v2 + v1 + v2;

    bool xAsExpected = v3.x == 6;
    bool yAsExpected = v3.y == 12;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}


// --run_test=MathVector2DoubleTests/SubTest1
BOOST_AUTO_TEST_CASE( SubTest1 )
{
    using Vector = Math::Vector<double, 2>;

    Vector v1( 6.0, 12.0 );
    Vector v2( 1.0, 2.0 );
    Vector v3 = v1 - v2 - v2 - v2 - v2 - v2;

    bool xAsExpected = v3.x == 1.;
    bool yAsExpected = v3.y == 2.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2DoubleTests/MulTest1
BOOST_AUTO_TEST_CASE( MulTest1 )
{
    using Vector = Math::Vector<double, 2>;

    Vector v1( 2.0, 3.0 );
    Vector v2( 2.0, 3.0 );
    Vector v3 = v1 * v2;

    bool xAsExpected = v3.x == 4.;
    bool yAsExpected = v3.y == 9.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2DoubleTests/MulTest2
BOOST_AUTO_TEST_CASE( MulTest2 )
{
    using Vector = Math::Vector<double, 2>;

    Vector v1( 2.0, 3.0 );
    Vector v2( 2.0, 3.0 );
    Vector v3 = v1 * v2 * 2.;

    bool xAsExpected = v3.x == 8.;
    bool yAsExpected = v3.y == 18.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2DoubleTests/MulTest3
BOOST_AUTO_TEST_CASE( MulTest3 )
{
    using Vector = Math::Vector<double, 2>;

    Vector v1( 2.0, 3.0 );
    Vector v3 = v1 * 2.;

    bool xAsExpected = v3.x == 4.;
    bool yAsExpected = v3.y == 6.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2DoubleTests/MulTest4
BOOST_AUTO_TEST_CASE( MulTest4 )
{
    using Vector = Math::Vector<double, 2>;

    Vector v1( 2.0, 3.0 );
    Vector v3 = 2. * v1;

    bool xAsExpected = v3.x == 4.;
    bool yAsExpected = v3.y == 6.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2DoubleTests/DivTest1
BOOST_AUTO_TEST_CASE( DivTest1 )
{
    using Vector = Math::Vector<double, 2>;

    Vector v1( 4.0, 9.0 );
    Vector v2( 2.0, 3.0 );
    Vector v3 = v1 / v2;

    bool xAsExpected = v3.x == 2.;
    bool yAsExpected = v3.y == 3.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2DoubleTests/DivTest2
BOOST_AUTO_TEST_CASE( DivTest2 )
{
    using Vector = Math::Vector<double, 2>;

    Vector v1( 4.0, 6.0 );

    Vector v3 = v1 / 2.;

    bool xAsExpected = v3.x == 2.;
    bool yAsExpected = v3.y == 3.;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2DoubleTests/Basics
BOOST_AUTO_TEST_CASE( Basics )
{
    using Vector = Math::Vector<double, 2>;

    Vector vf( -1., 10. );

    auto notEqual = vf != Vector( -1., 100. );
    BOOST_CHECK( notEqual );

    auto equal = Vector( -2., 20. ) == vf + vf;
    BOOST_CHECK( equal );

    equal = Vector( 0., 0. ) == vf - vf;
    BOOST_CHECK( equal );

    equal = Vector( -2., 20. ) == vf * 2.;
    BOOST_CHECK( equal );

    equal = Vector( -2., 20. ) == 2. * vf;
    BOOST_CHECK( equal );

    equal = Vector( -0.5f, 5. ) == vf / 2.;
    BOOST_CHECK( equal );

    equal = Vector( 1., 10. ) == Abs( vf );
    BOOST_CHECK( equal );

    equal = vf == Ceil( Vector( -1.5f, 9.9 ) );
    BOOST_CHECK( equal );

    equal = vf == Floor( Vector( -.5, 10.01 ) );
    BOOST_CHECK( equal );

    equal = Vector( -20., 10. ) == Min( vf, Vector( -20., 20. ) );
    BOOST_CHECK( equal );

    equal = Vector( -1., 20. ) == Max( vf, Vector( -20., 20. ) );
    BOOST_CHECK( equal );

    equal = -1. == MinComponentValue( vf );
    BOOST_CHECK( equal );

    equal = -10. == MinComponentValue( -vf );
    BOOST_CHECK( equal );

    equal = 10. == MaxComponentValue( vf );
    BOOST_CHECK( equal );

    equal = 1. == MaxComponentValue( -vf );
    BOOST_CHECK( equal );

    equal = 1 == MaxComponentIndex( vf );
    BOOST_CHECK( equal );

    equal = 0 == MaxComponentIndex( -vf );
    BOOST_CHECK( equal );

    equal = 0 == MinComponentIndex( vf );
    BOOST_CHECK( equal );

    equal = 1 == MinComponentIndex( -vf );
    BOOST_CHECK( equal );

    equal = vf == Permute<0b10>( vf );
    BOOST_CHECK( equal );

    equal = Vector( 10, -1 ) == Permute<1>( vf );
    BOOST_CHECK( equal );

    equal = Vector( 10, 10 ) == Permute<0b11>( vf );
    BOOST_CHECK( equal );

    /*
    BOOST_CHECK_EQUAL( vf, Permute( vf, { 0, 1 } ) );
    BOOST_CHECK_EQUAL( Vector2f( 10, -1 ), Permute( vf, { 1, 0 } ) );
    BOOST_CHECK_EQUAL( Vector2f( 10, 10 ), Permute( vf, { 1, 1 } ) );
    */
}



BOOST_AUTO_TEST_SUITE_END( )