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
BOOST_FIXTURE_TEST_SUITE( MathVector2FloatTests, LocalFixture )

// --run_test=MathVector2FloatTests/VectorTypeTest1
BOOST_AUTO_TEST_CASE( VectorTypeTest1 )
{
    using Vector = Math::Vector<float, 2>;

    constexpr bool isVectorType1 = Math::VectorType<Vector>;
    constexpr bool isVectorType2 = Math::VectorType<Math::Normal3f>;
    constexpr bool isVectorType3 = Math::VectorType<Math::Point2f>;

    BOOST_CHECK( isVectorType1 );
    BOOST_CHECK( isVectorType2 == false );
    BOOST_CHECK( isVectorType3 == false );

    BOOST_CHECK( sizeof( Vector ) == 8 );

}



// --run_test=MathVector2FloatTests/AddTest1
BOOST_AUTO_TEST_CASE( AddTest1 )
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 1.0f, 2.0f );
    Vector v2( 1.0f, 2.0f );
    Vector v3 = v1 + v2 + v1 + v2 + v1 + v2;

    bool xAsExpected = v3.x == 6.f;
    bool yAsExpected = v3.y == 12.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}


// --run_test=MathVector2FloatTests/SubTest1
BOOST_AUTO_TEST_CASE( SubTest1 )
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 6.0f, 12.0f );
    Vector v2( 1.0f, 2.0f );
    Vector v3 = v1 - v2 - v2 - v2 - v2 - v2;

    bool xAsExpected = v3.x == 1.f;
    bool yAsExpected = v3.y == 2.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2FloatTests/MulTest1
BOOST_AUTO_TEST_CASE( MulTest1 )
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 2.0f, 3.0f );
    Vector v2( 2.0f, 3.0f );
    Vector v3 = v1 * v2;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 9.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2FloatTests/MulTest2
BOOST_AUTO_TEST_CASE( MulTest2 )
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 2.0f, 3.0f );
    Vector v2( 2.0f, 3.0f );
    Vector v3 = v1 * v2 * 2.f;

    bool xAsExpected = v3.x == 8.f;
    bool yAsExpected = v3.y == 18.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2FloatTests/MulTest3
BOOST_AUTO_TEST_CASE( MulTest3 )
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 2.0f, 3.0f );
    Vector v3 = v1 * 2.f;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2FloatTests/MulTest4
BOOST_AUTO_TEST_CASE( MulTest4 )
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 2.0f, 3.0f );
    Vector v3 = 2.f * v1;

    bool xAsExpected = v3.x == 4.f;
    bool yAsExpected = v3.y == 6.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2FloatTests/DivTest1
BOOST_AUTO_TEST_CASE( DivTest1 )
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 4.0f, 9.0f );
    Vector v2( 2.0f, 3.0f );
    Vector v3 = v1 / v2;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2FloatTests/DivTest2
BOOST_AUTO_TEST_CASE( DivTest2 )
{
    using Vector = Math::Vector<float, 2>;

    Vector v1( 4.0f, 6.0f );
    
    Vector v3 = v1 / 2.f;

    bool xAsExpected = v3.x == 2.f;
    bool yAsExpected = v3.y == 3.f;

    BOOST_CHECK( xAsExpected );
    BOOST_CHECK( yAsExpected );
}

// --run_test=MathVector2FloatTests/Basics
BOOST_AUTO_TEST_CASE( Basics )
{
    using Vector = Math::Vector<float, 2>;

    Vector vf( -1.f, 10.f );

    auto notEqual = vf != Vector( -1.f, 100.f );
    BOOST_CHECK( notEqual );

    auto equal = Vector( -2.f, 20.f ) == vf + vf;
    BOOST_CHECK( equal );

    equal = Vector( 0.f, 0.f ) == vf - vf;
    BOOST_CHECK( equal );

    equal = Vector( -2.f, 20.f ) == vf * 2.f;
    BOOST_CHECK( equal );

    equal = Vector( -2.f, 20.f ) == 2.f * vf;
    BOOST_CHECK( equal );

    equal = Vector( -0.5f, 5.f ) == vf / 2.f;
    BOOST_CHECK( equal );

    equal = Vector( 1.f, 10.f ) == Abs( vf );
    BOOST_CHECK( equal );

    equal = vf == Ceil( Vector( -1.5f, 9.9f ) );
    BOOST_CHECK( equal );

    equal = vf == Floor( Vector( -.5f, 10.01f ) );
    BOOST_CHECK( equal );

    equal = Vector( -20.f, 10.f ) == Min( vf, Vector( -20.f, 20.f ) );
    BOOST_CHECK( equal );

    equal = Vector( -1.f, 20.f ) == Max( vf, Vector( -20.f, 20.f ) );
    BOOST_CHECK( equal );

    equal = -1.f == MinComponentValue( vf );
    BOOST_CHECK( equal );

    equal = -10.f == MinComponentValue( -vf );
    BOOST_CHECK( equal );

    equal = 10.f == MaxComponentValue( vf );
    BOOST_CHECK( equal );

    equal = 1.f == MaxComponentValue( -vf );
    BOOST_CHECK( equal );

    equal = 1 == MaxComponentIndex( vf );
    BOOST_CHECK( equal );

    equal = 0 == MaxComponentIndex( -vf );
    BOOST_CHECK( equal );

    equal = 0 == MinComponentIndex( vf );
    BOOST_CHECK( equal );

    equal = 1 == MinComponentIndex( -vf );
    BOOST_CHECK( equal );

    equal = vf == Permute<0b01'00>( vf );
    BOOST_CHECK( equal );

    equal = Vector( 10, -1 ) == Permute<0b00'01>( vf );
    BOOST_CHECK( equal );

    equal = Vector( 10, 10 ) == Permute<0b01'01>( vf );
    BOOST_CHECK( equal );

    /*
    BOOST_CHECK_EQUAL( vf, Permute( vf, { 0, 1 } ) );
    BOOST_CHECK_EQUAL( Vector2f( 10, -1 ), Permute( vf, { 1, 0 } ) );
    BOOST_CHECK_EQUAL( Vector2f( 10, 10 ), Permute( vf, { 1, 1 } ) );
    */
}



BOOST_AUTO_TEST_SUITE_END( )