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

    auto angle = ScalarAngleBetween( v1, v2 );

    bool angleAsExpected = AreNearlyEqual( angle, Math::Constants<float>::Pi);

    BOOST_CHECK( angleAsExpected );
}

// --run_test=MathVector3FloatTests/HSumTest1
BOOST_AUTO_TEST_CASE( HSumTest1 )
{
    constexpr float MaxDeviation = 1e-4f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        

        Vector result = Math::HSum( Vector::Simd( v1 ) );
        Vector expected(
            ( v1.x + v1.y + v1.z ),
            ( v1.x + v1.y + v1.z ),
            ( v1.x + v1.y + v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/HProdTest1
BOOST_AUTO_TEST_CASE( HProdTest1 )
{
    constexpr float MaxDeviation = 1e-4f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );


        Vector result = Math::HProd( Vector::Simd( v1 ) );
        Vector expected(
            ( v1.x * v1.y * v1.z ),
            ( v1.x * v1.y * v1.z ),
            ( v1.x * v1.y * v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/AbsTest1
BOOST_AUTO_TEST_CASE( AbsTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-20f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );


        Vector result = Math::Abs( Vector::Simd( v1 ) );
        Vector expected(
            std::abs( v1.x ),
            std::abs( v1.y ),
            std::abs( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/MinTest1
BOOST_AUTO_TEST_CASE( MinTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-20f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );


        Vector result = Math::Min( v1, v2 );
        Vector expected(
            std::min( v1.x, v2.x ),
            std::min( v1.y, v2.y ),
            std::min( v1.z, v2.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/MaxTest1
BOOST_AUTO_TEST_CASE( MaxTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-20f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );


        Vector result = Math::Max( v1, v2 );
        Vector expected(
            std::max( v1.x, v2.x ),
            std::max( v1.y, v2.y ),
            std::max( v1.z, v2.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/SqrTest1
BOOST_AUTO_TEST_CASE( SqrTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-20f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );


        Vector result = Math::Sqr( v1 );
        Vector expected(
            ( v1.x * v1.x ),
            ( v1.y * v1.y ),
            ( v1.z * v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/CeilTest1
BOOST_AUTO_TEST_CASE( CeilTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-20f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );


        Vector result = Math::Ceil( v1 );
        Vector expected(
            std::ceil( v1.x ),
            std::ceil( v1.y ),
            std::ceil( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/FloorTest1
BOOST_AUTO_TEST_CASE( FloorTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-20f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );


        Vector result = Math::Floor( v1 );
        Vector expected(
            std::floor( v1.x ),
            std::floor( v1.y ),
            std::floor( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/TruncTest1
BOOST_AUTO_TEST_CASE( TruncTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-20f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );


        Vector result = Math::Trunc( v1 );
        Vector expected(
            std::trunc( v1.x ),
            std::trunc( v1.y ),
            std::trunc( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/RoundTest1
BOOST_AUTO_TEST_CASE( RoundTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-20f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );


        Vector result = Math::Round( v1 );
        Vector expected(
            std::round( v1.x ),
            std::round( v1.y ),
            std::round( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/LerpTest1
BOOST_AUTO_TEST_CASE( LerpTest1 )
{
    constexpr float MaxDeviation = 1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );

        Vector result = Math::Lerp( v1, v2, v3 );
        Vector expected(
            std::lerp( v1.x, v2.x, v3.x),
            std::lerp( v1.y, v2.y, v3.y ),
            std::lerp( v1.z, v2.z, v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }

}

// --run_test=MathVector3FloatTests/ClampTest1
BOOST_AUTO_TEST_CASE( ClampTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( -100.f, -100.f, -100.f );
        Vector v3( 100.f, 100.f, 100.f );

        Vector result = Math::Clamp( v1, v2, v3 );
        Vector expected(
            std::clamp( v1.x, v2.x, v3.x ),
            std::clamp( v1.y, v2.y, v3.y ),
            std::clamp( v1.z, v2.z, v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/ClampLengthTest1
BOOST_AUTO_TEST_CASE( ClampLengthTest1 )
{
    constexpr float MaxDeviation = 1e-6f; // 1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( 10.f, 10.f, 10.f );
        Vector v3( 100.f, 100.f, 100.f );

        Vector result = Math::ClampLength( v1, v2, v3 );

        DirectX::XMFLOAT3 dv1( v1.x, v1.y, v1.z );
        DirectX::XMFLOAT3 dv2( v2.x, v2.y, v2.z );
        DirectX::XMFLOAT3 dv3( v3.x, v3.y, v3.z );

        auto ldv1 = DirectX::XMLoadFloat3( &dv1 );
        auto ldv2 = DirectX::XMLoadFloat3( &dv2 );
        auto ldv3 = DirectX::XMLoadFloat3( &dv3 );

        auto clampLengthV = DirectX::XMVector3ClampLengthV( ldv1, ldv2, ldv3 );

        DirectX::XMFLOAT3 clampLength;
        DirectX::XMStoreFloat3( &clampLength, clampLengthV );

        Vector expected( clampLength.x, clampLength.y, clampLength.z );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/SaturateTest1
BOOST_AUTO_TEST_CASE( SaturateTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( 0.f, 0.f, 0.f );
        Vector v3( 1.f, 1.f, 1.f );

        Vector result = Math::Saturate( v1 );
        Vector expected(
            std::clamp( v1.x, v2.x, v3.x ),
            std::clamp( v1.y, v2.y, v3.y ),
            std::clamp( v1.z, v2.z, v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/SqrtTest1
BOOST_AUTO_TEST_CASE( SqrtTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( 0, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );

        Vector result = Math::Sqrt( v1 );
        Vector expected(
            std::sqrt( v1.x ),
            std::sqrt( v1.y ),
            std::sqrt( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/ReciprocalSqrtTest1
BOOST_AUTO_TEST_CASE( ReciprocalSqrtTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( 1e-18f, 1e10f );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );

        Vector result = Math::ReciprocalSqrt( v1 );
        Vector expected(
            1.f / std::sqrt( v1.x ),
            1.f / std::sqrt( v1.y ),
            1.f / std::sqrt( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/ReciprocalTest1
BOOST_AUTO_TEST_CASE( ReciprocalTest1 )
{
    constexpr float MaxDeviation = 0; // 1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( 1e-18f, 1e10f );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );

        Vector result = Math::Reciprocal( v1 );
        Vector expected(
            1.f / v1.x,
            1.f / v1.y,
            1.f / v1.z );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/FMATest1
BOOST_AUTO_TEST_CASE( FMATest1 )
{
    constexpr float MaxDeviation = 0.f;//1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );

        Vector result = Math::FMA( v1, v2, v3 );
        Vector expected(
            std::fma( v1.x, v2.x, v3.x ),
            std::fma( v1.y, v2.y, v3.y ),
            std::fma( v1.z, v2.z, v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }

}

// --run_test=MathVector3FloatTests/FMSubTest1
BOOST_AUTO_TEST_CASE( FMSubTest1 )
{
    constexpr float MaxDeviation = 0.f;//1e-3f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );

        Vector result = Math::FMSub( v1, v2, v3 );
        Vector expected(
            std::fma( v1.x, v2.x, -v3.x ),
            std::fma( v1.y, v2.y, -v3.y ),
            std::fma( v1.z, v2.z, -v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/FMAddSubTest1
BOOST_AUTO_TEST_CASE( FMAddSubTest1 )
{
    constexpr float MaxDeviation = 1e-5f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );

        Vector result = Math::FMAddSub( v1, v2, v3 );
        Vector expected(
            std::fma( v1.x, v2.x, v3.x ),
            std::fma( v1.y, v2.y, -v3.y ),
            std::fma( v1.z, v2.z, v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/FMSubAddTest1
BOOST_AUTO_TEST_CASE( FMSubAddTest1 )
{
    constexpr float MaxDeviation = 1e-5f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );

        Vector result = Math::FMSubAdd( v1, v2, v3 );
        Vector expected(
            std::fma( v1.x, v2.x, -v3.x ),
            std::fma( v1.y, v2.y, v3.y ),
            std::fma( v1.z, v2.z, -v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/FNMAddTest1
BOOST_AUTO_TEST_CASE( FNMAddTest1 )
{
    constexpr float MaxDeviation = 1e-5f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );

        Vector result = Math::FNMAdd( v1, v2, v3 );
        Vector expected(
            std::fma( -v1.x, v2.x, v3.x ),
            std::fma( -v1.y, v2.y, v3.y ),
            std::fma( -v1.z, v2.z, v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/FNMSubTest1
BOOST_AUTO_TEST_CASE( FNMSubTest1 )
{
    constexpr float MaxDeviation = 1e-5f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );

        Vector result = Math::FNMSub( v1, v2, v3 );
        Vector expected(
            std::fma( -v1.x, v2.x, -v3.x ),
            std::fma( -v1.y, v2.y, -v3.y ),
            std::fma( -v1.z, v2.z, -v3.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/SinTest1
BOOST_AUTO_TEST_CASE( SinTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange() )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Sin( v1 );
        Vector expected(
            std::sin( v1.x ),
            std::sin( v1.y ),
            std::sin( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/CosTest1
BOOST_AUTO_TEST_CASE( CosTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Cos( v1 );
        Vector expected(
            std::cos( v1.x ),
            std::cos( v1.y ),
            std::cos( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/TanTest1
BOOST_AUTO_TEST_CASE( TanTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Tan( v1 );
        Vector expected(
            std::tan( v1.x ),
            std::tan( v1.y ),
            std::tan( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/ASinTest1
BOOST_AUTO_TEST_CASE( ASinTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::ASin( v1 );
        Vector expected(
            std::asin( v1.x ),
            std::asin( v1.y ),
            std::asin( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/ACosTest1
BOOST_AUTO_TEST_CASE( ACosTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::ACos( v1 );
        Vector expected(
            std::acos( v1.x ),
            std::acos( v1.y ),
            std::acos( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/ATanTest1
BOOST_AUTO_TEST_CASE( ATanTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::ATan( v1 );
        Vector expected(
            std::atan( v1.x ),
            std::atan( v1.y ),
            std::atan( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/ATan2Test1
BOOST_AUTO_TEST_CASE( ATan2Test1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator1( -1e10, 1e10 );
    RandomGenerator<float, 20000> generator2( -1e10, 1e10 );
#else
    Test::Generators::RangeGenerator<float> generator1( -1e10, 1e10 );
    RandomGenerator<float, 20000> generator2( -1e10, 1e10 );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value1 = generator1( );
        auto value2 = generator2( );
#else
    while ( generator1.InRange( ) )
    {
        auto value1 = generator1( );
        auto value2 = generator2( );
#endif
        Vector v1( value1, value1, value1 );
        Vector v2( value2, value2, value2 );

        Vector result = Math::ATan2( v1, v2 );
        Vector expected(
            std::atan2( v1.x, v2.x ),
            std::atan2( v1.y, v2.y ),
            std::atan2( v1.z, v2.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/ModAnglesTest1
BOOST_AUTO_TEST_CASE( ModAnglesTest1 )
{
    constexpr float MaxDeviation = 0; //1e-3f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e5f * Math::Constants<float>::Pi, 1e5f * Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator( -1e5f * Math::Constants<float>::Pi, 1e5f * Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::ModAngles( v1 );
        auto modAngles = DirectX::XMVectorModAngles( DirectX::XMLoadFloat3( reinterpret_cast< DirectX::XMFLOAT3* >( v1.data( ) ) ) );
        Vector expected;
        DirectX::XMStoreFloat3( reinterpret_cast< DirectX::XMFLOAT3* >( expected.data( ) ), modAngles );
        

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/AddAnglesTest1
BOOST_AUTO_TEST_CASE( AddAnglesTest1 )
{
    constexpr float MaxDeviation = 0; //1e-3f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator1( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
    RandomGenerator<float, 20000> generator2( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator1( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
    RandomGenerator<float, 20000> generator2( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value1 = generator1( );
        auto value2 = generator2( );
#else
    while ( generator1.InRange( ) )
    {
        auto value1 = generator1( );
        auto value2 = generator2( );
#endif
        Vector v1( value1, value1, value1 );
        Vector v2( value2, value2, value2 );

        Vector result = Math::AddAngles( v1, v2 );
        auto modAngles = DirectX::XMVectorAddAngles( DirectX::XMLoadFloat3( reinterpret_cast< DirectX::XMFLOAT3* >( v1.data( ) ) ),
            DirectX::XMLoadFloat3( reinterpret_cast< DirectX::XMFLOAT3* >( v2.data( ) ) ) );
        Vector expected;
        DirectX::XMStoreFloat3( reinterpret_cast< DirectX::XMFLOAT3* >( expected.data( ) ), modAngles );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );

        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }
    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/SubtractAnglesTest1
BOOST_AUTO_TEST_CASE( SubtractAnglesTest1 )
{
    constexpr float MaxDeviation = 0; //1e-3f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator1( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
    RandomGenerator<float, 20000> generator2( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator1( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
    RandomGenerator<float, 20000> generator2( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value1 = generator1( );
        auto value2 = generator2( );
#else
    while ( generator1.InRange( ) )
    {
        auto value1 = generator1( );
        auto value2 = generator2( );
#endif
        Vector v1( value1, value1, value1 );
        Vector v2( value2, value2, value2 );

        Vector result = Math::SubtractAngles( v1, v2 );
        auto modAngles = DirectX::XMVectorSubtractAngles( DirectX::XMLoadFloat3( reinterpret_cast< DirectX::XMFLOAT3* >( v1.data( ) ) ),
            DirectX::XMLoadFloat3( reinterpret_cast< DirectX::XMFLOAT3* >( v2.data( ) ) ) );
        Vector expected;
        DirectX::XMStoreFloat3( reinterpret_cast< DirectX::XMFLOAT3* >( expected.data( ) ), modAngles );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );

        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }
    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/SinHTest1
BOOST_AUTO_TEST_CASE( SinHTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::SinH( v1 );
        Vector expected(
            std::sinh( v1.x ),
            std::sinh( v1.y ),
            std::sinh( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/CosHTest1
BOOST_AUTO_TEST_CASE( CosHTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::CosH( v1 );
        Vector expected(
            std::cosh( v1.x ),
            std::cosh( v1.y ),
            std::cosh( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/TanHTest1
BOOST_AUTO_TEST_CASE( TanHTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::Pi, Math::Constants<float>::Pi );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::TanH( v1 );
        Vector expected(
            std::tanh( v1.x ),
            std::tanh( v1.y ),
            std::tanh( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/ASinHTest1
BOOST_AUTO_TEST_CASE( ASinHTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::ASinH( v1 );
        Vector expected(
            std::asinh( v1.x ),
            std::asinh( v1.y ),
            std::asinh( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/ACosHTest1
BOOST_AUTO_TEST_CASE( ACosHTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::ACosH( v1 );
        Vector expected(
            std::acosh( v1.x ),
            std::acosh( v1.y ),
            std::acosh( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/ATanHTest1
BOOST_AUTO_TEST_CASE( ATanHTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#else
    Test::Generators::RangeGenerator<float> generator( -Math::Constants<float>::One, Math::Constants<float>::One );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::ATanH( v1 );
        Vector expected(
            std::atanh( v1.x ),
            std::atanh( v1.y ),
            std::atanh( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/LogTest1
BOOST_AUTO_TEST_CASE( LogTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( 0.f, 100000.f );
#else
    Test::Generators::RangeGenerator<float> generator( 0.f, 100000.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Log( v1 );
        Vector expected(
            std::log( v1.x ),
            std::log( v1.y ),
            std::log( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/Log1PTest1
BOOST_AUTO_TEST_CASE( Log1PTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( 0.f, 100000.f );
#else
    Test::Generators::RangeGenerator<float> generator( 0.f, 100000.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Log1P( v1 );
        Vector expected(
            std::log1p( v1.x ),
            std::log1p( v1.y ),
            std::log1p( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/Log10Test1
BOOST_AUTO_TEST_CASE( Log10Test1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( 0.f, 100000.f );
#else
    Test::Generators::RangeGenerator<float> generator( 0.f, 100000.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Log10( v1 );
        Vector expected(
            std::log10( v1.x ),
            std::log10( v1.y ),
            std::log10( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/Log2Test1
BOOST_AUTO_TEST_CASE( Log2Test1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( 0.f, 100000.f );
#else
    Test::Generators::RangeGenerator<float> generator( 0.f, 100000.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Log2( v1 );
        Vector expected(
            std::log2( v1.x ),
            std::log2( v1.y ),
            std::log2( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/ExpTest1
BOOST_AUTO_TEST_CASE( ExpTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -89.f, 89.f );
#else
    Test::Generators::RangeGenerator<float> generator( -89.f, 89.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Exp( v1 );
        Vector expected(
            std::exp( v1.x ),
            std::exp( v1.y ),
            std::exp( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/Exp10Test1
BOOST_AUTO_TEST_CASE( Exp10Test1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -38.f, 38.f );
#else
    Test::Generators::RangeGenerator<float> generator( -38.f, 38.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Exp10( v1 );
        Vector expected(
            std::pow(10.f, v1.x ),
            std::pow(10.f, v1.y ),
            std::pow(10.f, v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/Exp2Test1
BOOST_AUTO_TEST_CASE( Exp2Test1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -120.f, 127.f );
#else
    Test::Generators::RangeGenerator<float> generator( -38.f, 38.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::Exp2( v1 );
        Vector expected(
            std::exp2(v1.x ),
            std::exp2(v1.y ),
            std::exp2(v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/ExpM1Test1
BOOST_AUTO_TEST_CASE( ExpM1Test1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -89.f, 89.f );
#else
    Test::Generators::RangeGenerator<float> generator( -89.f, 89.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value = generator( );
#else
    while ( generator.InRange( ) )
    {
        auto value = generator( );
#endif
        Vector v1( value, value, value );

        Vector result = Math::ExpM1( v1 );
        Vector expected(
            std::expm1( v1.x ),
            std::expm1( v1.y ),
            std::expm1( v1.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/PowTest1
BOOST_AUTO_TEST_CASE( PowTest1 )
{
    constexpr float MaxDeviation = 1e-6f;
#ifdef _DEBUG
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator1( -2.f, 2.f );
    RandomGenerator<float, 20000> generator2( -120.f, 127.f );
#else
    Test::Generators::RangeGenerator<float> generator1( -2.f, 2.f );
    RandomGenerator<float, 20000> generator2( -120.f, 127.f );
#endif
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;

#ifdef _DEBUG
    for ( size_t i = 0; i < Iterations; i++ )
    {
        auto value1 = generator1( );
        auto value2 = generator2( );
#else
    while ( generator1.InRange( ) )
    {
        auto value1 = generator1( );
        auto value2 = generator2( );
#endif
        Vector v1( value1, value1, value1 );
        Vector v2( value1, value1, value1 );

        Vector result = Math::Pow( v1, v2 );
        Vector expected(
            std::pow( v1.x, v2.x ),
            std::pow( v1.y, v2.y ),
            std::pow( v1.z, v2.z ) );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}


// --run_test=MathVector3FloatTests/DotTest1
BOOST_AUTO_TEST_CASE( DotTest1 )
{
    constexpr float MaxDeviation = 1e-5f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    double maxDeviation = 0.;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );

        auto result = Math::ScalarDot( v1, v2 );
        auto expected = std::inner_product( v1.begin( ), v1.end( ), v2.begin( ), 0.f );

        auto deviation = Test::Deviation( expected, result );

        if ( deviation > maxDeviation )
        {
            maxDeviation = Math::Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}

// --run_test=MathVector3FloatTests/CrossTest1
BOOST_AUTO_TEST_CASE( CrossTest1 )
{
    constexpr float MaxDeviation = 1e-5f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );

        Vector result = Math::Cross( v1, v2 );

        auto CrossProduct = []( const Vector& v1, const Vector& v2 )
            {
                Vector result;
                result[ 0 ] = v1[ 1 ] * v2[ 2 ] - v1[ 2 ] * v2[ 1 ];
                result[ 1 ] = v1[ 2 ] * v2[ 0 ] - v1[ 0 ] * v2[ 2 ];
                result[ 2 ] = v1[ 0 ] * v2[ 1 ] - v1[ 1 ] * v2[ 0 ];
                return result;
            };
        Vector expected = CrossProduct( v1, v2 );

        Vector deviation(
            static_cast< float >( Test::Deviation( expected.x, result.x ) ),
            static_cast< float >( Test::Deviation( expected.y, result.y ) ),
            static_cast< float >( Test::Deviation( expected.z, result.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }
}




// --run_test=MathVector3FloatTests/DifferenceOfProductsTest1
BOOST_AUTO_TEST_CASE( DifferenceOfProductsTest1 )
{
    // The point of DifferenceOfProducts is that differences are expected
    constexpr float MaxDeviation = 1e-2f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );
        Vector v4( generator( ), generator( ), generator( ) );

        Vector differenceOfProducts = Math::DifferenceOfProducts(v1,v2,v3,v4);
        Vector naive( 
            (v1.x * v2.x) - (v3.x * v4.x),
            (v1.y * v2.y) - (v3.y * v4.y),
            (v1.z * v2.z) - (v3.z * v4.z) );

        Vector deviation(
            static_cast< float >( Test::Deviation( naive.x, differenceOfProducts.x ) ),
            static_cast< float >( Test::Deviation( naive.y, differenceOfProducts.y ) ),
            static_cast< float >( Test::Deviation( naive.z, differenceOfProducts.z ) ) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }
        
    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }

}

// --run_test=MathVector3FloatTests/SumOfProductsTest1
BOOST_AUTO_TEST_CASE( SumOfProductsTest1 )
{
    // The point of SumOfProducts is that differences are expected
    constexpr float MaxDeviation = 1e-2f;
    constexpr size_t Iterations = 20000;
    RandomGenerator<float, 20000> generator( -1e10, 1e10 );
    using Vector = Math::Vector<float, 3>;
    Vector maxDeviation;
    for ( size_t i = 0; i < Iterations; i++ )
    {
        Vector v1( generator( ), generator( ), generator( ) );
        Vector v2( generator( ), generator( ), generator( ) );
        Vector v3( generator( ), generator( ), generator( ) );
        Vector v4( generator( ), generator( ), generator( ) );

        Vector differenceOfProducts = Math::SumOfProducts( v1, v2, v3, v4 );
        Vector naive(
            ( v1.x * v2.x ) + ( v3.x * v4.x ),
            ( v1.y * v2.y ) + ( v3.y * v4.y ),
            ( v1.z * v2.z ) + ( v3.z * v4.z ) );

        Vector deviation(
            static_cast<float>(Test::Deviation( naive.x, differenceOfProducts.x )),
            static_cast< float >( Test::Deviation( naive.y, differenceOfProducts.y )),
            static_cast< float >( Test::Deviation( naive.z, differenceOfProducts.z )) );


        if ( deviation.x > MaxDeviation || deviation.y > MaxDeviation || deviation.z > MaxDeviation )
        {
            maxDeviation = Max( maxDeviation, deviation );
        }

    }

    if ( maxDeviation.x > MaxDeviation || maxDeviation.y > MaxDeviation || maxDeviation.z > MaxDeviation )
    {
        BOOST_CHECK( false );
    }

}



BOOST_AUTO_TEST_SUITE_END( )