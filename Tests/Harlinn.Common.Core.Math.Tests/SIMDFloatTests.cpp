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

#include <HCCMath.h>


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
BOOST_FIXTURE_TEST_SUITE( SIMDFloatTests, LocalFixture )

// --run_test=SIMDFloatTests/Set1Test1
BOOST_AUTO_TEST_CASE( Set1Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<float, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 0.0 );
    BOOST_CHECK( result[ 2 ] == 0.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set1Test2
BOOST_AUTO_TEST_CASE( Set1Test2 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<float, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 0.0 );
    BOOST_CHECK( result[ 2 ] == 0.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
    BOOST_CHECK( result[ 4 ] == 0.0 );
    BOOST_CHECK( result[ 5 ] == 0.0 );
    BOOST_CHECK( result[ 6 ] == 0.0 );
    BOOST_CHECK( result[ 7 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set2Test1
BOOST_AUTO_TEST_CASE( Set2Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 0.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set2Test2
BOOST_AUTO_TEST_CASE( Set2Test2 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 0.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
    BOOST_CHECK( result[ 4 ] == 0.0 );
    BOOST_CHECK( result[ 5 ] == 0.0 );
    BOOST_CHECK( result[ 6 ] == 0.0 );
    BOOST_CHECK( result[ 7 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set3Test1
BOOST_AUTO_TEST_CASE( Set3Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set3Test2
BOOST_AUTO_TEST_CASE( Set3Test2 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
    BOOST_CHECK( result[ 4 ] == 0.0 );
    BOOST_CHECK( result[ 5 ] == 0.0 );
    BOOST_CHECK( result[ 6 ] == 0.0 );
    BOOST_CHECK( result[ 7 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set4Test1
BOOST_AUTO_TEST_CASE( Set4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 4.0 );
}

// --run_test=SIMDFloatTests/Set4Test2
BOOST_AUTO_TEST_CASE( Set4Test2 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 4.0 );
    BOOST_CHECK( result[ 4 ] == 0.0 );
    BOOST_CHECK( result[ 5 ] == 0.0 );
    BOOST_CHECK( result[ 6 ] == 0.0 );
    BOOST_CHECK( result[ 7 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set5Test1
BOOST_AUTO_TEST_CASE( Set5Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 4.0 );
    BOOST_CHECK( result[ 4 ] == 5.0 );
    BOOST_CHECK( result[ 5 ] == 0.0 );
    BOOST_CHECK( result[ 6 ] == 0.0 );
    BOOST_CHECK( result[ 7 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set6Test1
BOOST_AUTO_TEST_CASE( Set6Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 4.0 );
    BOOST_CHECK( result[ 4 ] == 5.0 );
    BOOST_CHECK( result[ 5 ] == 6.0 );
    BOOST_CHECK( result[ 6 ] == 0.0 );
    BOOST_CHECK( result[ 7 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set7Test1
BOOST_AUTO_TEST_CASE( Set7Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 7, 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 4.0 );
    BOOST_CHECK( result[ 4 ] == 5.0 );
    BOOST_CHECK( result[ 5 ] == 6.0 );
    BOOST_CHECK( result[ 6 ] == 7.0 );
    BOOST_CHECK( result[ 7 ] == 0.0 );
}

// --run_test=SIMDFloatTests/Set8Test1
BOOST_AUTO_TEST_CASE( Set8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 8, 7, 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<float, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 4.0 );
    BOOST_CHECK( result[ 4 ] == 5.0 );
    BOOST_CHECK( result[ 5 ] == 6.0 );
    BOOST_CHECK( result[ 6 ] == 7.0 );
    BOOST_CHECK( result[ 7 ] == 8.0 );
}



// --run_test=SIMDFloatTests/HorizontalMin1Test1
BOOST_AUTO_TEST_CASE( HorizontalMin1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    auto rmm1 = Traits::Set( -3 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}


// --run_test=SIMDFloatTests/HorizontalMin2Test1
BOOST_AUTO_TEST_CASE( HorizontalMin2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    auto rmm1 = Traits::Set( -3, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}

// --run_test=SIMDFloatTests/HorizontalMin3Test1
BOOST_AUTO_TEST_CASE( HorizontalMin3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    auto rmm1 = Traits::Set( -3, 100 ,1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}

// --run_test=SIMDFloatTests/HorizontalMin4Test1
BOOST_AUTO_TEST_CASE( HorizontalMin4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    auto rmm1 = Traits::Set( -3, 0 ,100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}

// --run_test=SIMDFloatTests/HorizontalMin5Test1
BOOST_AUTO_TEST_CASE( HorizontalMin5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    auto rmm1 = Traits::Set( -3, 15 ,0, 100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}

// --run_test=SIMDFloatTests/HorizontalMin6Test1
BOOST_AUTO_TEST_CASE( HorizontalMin6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    auto rmm1 = Traits::Set( -3, -4 ,15, 0, 100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -4.f );
}

// --run_test=SIMDFloatTests/HorizontalMin7Test1
BOOST_AUTO_TEST_CASE( HorizontalMin7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    auto rmm1 = Traits::Set( 8, -3, -4, 15, 0, 100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -4.f );
}

// --run_test=SIMDFloatTests/HorizontalMin8Test1
BOOST_AUTO_TEST_CASE( HorizontalMin8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 8, -3, -4, 15, 0, -34 ,100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -34.f );
}

// --run_test=SIMDFloatTests/HorizontalMax1Test1
BOOST_AUTO_TEST_CASE( HorizontalMax1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    auto rmm1 = Traits::Set( -3 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == -3.f );
}


// --run_test=SIMDFloatTests/HorizontalMax2Test1
BOOST_AUTO_TEST_CASE( HorizontalMax2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    auto rmm1 = Traits::Set( -3, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 1.f );
}

// --run_test=SIMDFloatTests/HorizontalMax3Test1
BOOST_AUTO_TEST_CASE( HorizontalMax3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    auto rmm1 = Traits::Set( -3, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 100.f );
}

// --run_test=SIMDFloatTests/HorizontalMax4Test1
BOOST_AUTO_TEST_CASE( HorizontalMax4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    auto rmm1 = Traits::Set( 101, -40, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 101.f );
}

// --run_test=SIMDFloatTests/HorizontalMax5Test1
BOOST_AUTO_TEST_CASE( HorizontalMax5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    auto rmm1 = Traits::Set( 101, -15, 0, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 101.f );
}

// --run_test=SIMDFloatTests/HorizontalMax6Test1
BOOST_AUTO_TEST_CASE( HorizontalMax6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    auto rmm1 = Traits::Set( 101, -4, 102, 0, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 102.f );
}

// --run_test=SIMDFloatTests/HorizontalMax7Test1
BOOST_AUTO_TEST_CASE( HorizontalMax7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    auto rmm1 = Traits::Set( 8, 105, -4, 15, 0, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 105.f );
}

// --run_test=SIMDFloatTests/HorizontalMax8Test1
BOOST_AUTO_TEST_CASE( HorizontalMax8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( 8, -3, 104, 15, 0, -34, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 104.f );
}

// --run_test=SIMDFloatTests/HSum1Test1
BOOST_AUTO_TEST_CASE( HSum1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    auto expected = -3.f;
    auto rmm1 = Traits::Set( expected );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[0] == expected );
}

// --run_test=SIMDFloatTests/HSum2Test1
BOOST_AUTO_TEST_CASE( HSum2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    auto expected = -3.f + 5;
    auto rmm1 = Traits::Set( -3.f, 5.f );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
    BOOST_CHECK( result[ 1 ] == expected );
}

// --run_test=SIMDFloatTests/HSum3Test1
BOOST_AUTO_TEST_CASE( HSum3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    auto rmm1 = Traits::Set( 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == 11.0 );
    BOOST_CHECK( result[ 1 ] == 11.0 );
    BOOST_CHECK( result[ 2 ] == 11.0 );
}


// --run_test=SIMDFloatTests/HSum4Test1
BOOST_AUTO_TEST_CASE( HSum4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    auto rmm1 = Traits::Set( 21, 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == 32.0 );
    BOOST_CHECK( result[ 1 ] == 32.0 );
    BOOST_CHECK( result[ 2 ] == 32.0 );
    BOOST_CHECK( result[ 3 ] == 32.0 );
}

// --run_test=SIMDFloatTests/HSum5Test1
BOOST_AUTO_TEST_CASE( HSum5Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    auto rmm1 = Traits::Set( 33, 21, 7, 3, 1 );
    auto expected = 33 + 21 + 7 + 3 + 1;
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
    BOOST_CHECK( result[ 1 ] == expected );
    BOOST_CHECK( result[ 2 ] == expected );
    BOOST_CHECK( result[ 3 ] == expected );
    BOOST_CHECK( result[ 4 ] == expected );
}


// --run_test=SIMDFloatTests/HSum6Test1
BOOST_AUTO_TEST_CASE( HSum6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    auto rmm1 = Traits::Set( 66, 33, 21, 7, 3, 1 );
    auto expected = 66 + 33 + 21 + 7 + 3 + 1;
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
    BOOST_CHECK( result[ 1 ] == expected );
    BOOST_CHECK( result[ 2 ] == expected );
    BOOST_CHECK( result[ 3 ] == expected );
    BOOST_CHECK( result[ 4 ] == expected );
    BOOST_CHECK( result[ 5 ] == expected );
}


// --run_test=SIMDFloatTests/HSum7Test1
BOOST_AUTO_TEST_CASE( HSum7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    auto rmm1 = Traits::Set( 133, 66, 33, 21, 7, 3, 1 );
    auto expected = 133 + 66 + 33 + 21 + 7 + 3 + 1;
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
    BOOST_CHECK( result[ 1 ] == expected );
    BOOST_CHECK( result[ 2 ] == expected );
    BOOST_CHECK( result[ 3 ] == expected );
    BOOST_CHECK( result[ 4 ] == expected );
    BOOST_CHECK( result[ 5 ] == expected );
    BOOST_CHECK( result[ 6 ] == expected );
}

// --run_test=SIMDFloatTests/HSum8Test1
BOOST_AUTO_TEST_CASE( HSum8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    auto rmm1 = Traits::Set( -234, 133, 66, 33, 21, 7, 3, 1 );
    auto expected = -234 + 133 + 66 + 33 + 21 + 7 + 3 + 1;
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
    BOOST_CHECK( result[ 1 ] == expected );
    BOOST_CHECK( result[ 2 ] == expected );
    BOOST_CHECK( result[ 3 ] == expected );
    BOOST_CHECK( result[ 4 ] == expected );
    BOOST_CHECK( result[ 5 ] == expected );
    BOOST_CHECK( result[ 6 ] == expected );
    BOOST_CHECK( result[ 7 ] == expected );
}

// --run_test=SIMDFloatTests/Add1Test1
BOOST_AUTO_TEST_CASE( Add1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Add2Test1
BOOST_AUTO_TEST_CASE( Add2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}


// --run_test=SIMDFloatTests/Add3Test1
BOOST_AUTO_TEST_CASE( Add3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Add4Test1
BOOST_AUTO_TEST_CASE( Add4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Add5Test1
BOOST_AUTO_TEST_CASE( Add5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Add6Test1
BOOST_AUTO_TEST_CASE( Add6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Add7Test1
BOOST_AUTO_TEST_CASE( Add7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Add8Test1
BOOST_AUTO_TEST_CASE( Add8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 15, 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 16, 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] + arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Sub1Test1
BOOST_AUTO_TEST_CASE( Sub1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Sub2Test1
BOOST_AUTO_TEST_CASE( Sub2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}


// --run_test=SIMDFloatTests/Sub3Test1
BOOST_AUTO_TEST_CASE( Sub3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Sub4Test1
BOOST_AUTO_TEST_CASE( Sub4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Sub5Test1
BOOST_AUTO_TEST_CASE( Sub5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Sub6Test1
BOOST_AUTO_TEST_CASE( Sub6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Sub7Test1
BOOST_AUTO_TEST_CASE( Sub7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Sub8Test1
BOOST_AUTO_TEST_CASE( Sub8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 15, 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 16, 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Sub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Mul1Test1
BOOST_AUTO_TEST_CASE( Mul1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Mul2Test1
BOOST_AUTO_TEST_CASE( Mul2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}


// --run_test=SIMDFloatTests/Mul3Test1
BOOST_AUTO_TEST_CASE( Mul3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Mul4Test1
BOOST_AUTO_TEST_CASE( Mul4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Mul5Test1
BOOST_AUTO_TEST_CASE( Mul5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Mul6Test1
BOOST_AUTO_TEST_CASE( Mul6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Mul7Test1
BOOST_AUTO_TEST_CASE( Mul7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Mul8Test1
BOOST_AUTO_TEST_CASE( Mul8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 15, 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 16, 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] * arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Mul( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Div1Test1
BOOST_AUTO_TEST_CASE( Div1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Div2Test1
BOOST_AUTO_TEST_CASE( Div2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}


// --run_test=SIMDFloatTests/Div3Test1
BOOST_AUTO_TEST_CASE( Div3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Div4Test1
BOOST_AUTO_TEST_CASE( Div4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Div5Test1
BOOST_AUTO_TEST_CASE( Div5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Div6Test1
BOOST_AUTO_TEST_CASE( Div6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Div7Test1
BOOST_AUTO_TEST_CASE( Div7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Div8Test1
BOOST_AUTO_TEST_CASE( Div8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 15, 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 16, 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = arg1[ i ] / arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Div( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/AddSub1Test1
BOOST_AUTO_TEST_CASE( AddSub1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/AddSub2Test1
BOOST_AUTO_TEST_CASE( AddSub2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 1 } );
    ArrayType arg2( { 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}


// --run_test=SIMDFloatTests/AddSub3Test1
BOOST_AUTO_TEST_CASE( AddSub3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 3, 1 } );
    ArrayType arg2( { 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/AddSub4Test1
BOOST_AUTO_TEST_CASE( AddSub4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 7, 5, 3, 1 } );
    ArrayType arg2( { 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/AddSub5Test1
BOOST_AUTO_TEST_CASE( AddSub5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/AddSub6Test1
BOOST_AUTO_TEST_CASE( AddSub6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/AddSub7Test1
BOOST_AUTO_TEST_CASE( AddSub7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/AddSub8Test1
BOOST_AUTO_TEST_CASE( AddSub8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 15, 13, 11, 9, 7, 5, 3, 1 } );
    ArrayType arg2( { 16, 14, 12, 10, 8, 6, 4, 2 } );
    ArrayType expected{};
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = i % 2 ? arg1[ i ] + arg2[ i ] : arg1[ i ] - arg2[ i ];
    }
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::AddSub( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Abs1Test1
BOOST_AUTO_TEST_CASE( Abs1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1 } );
    ArrayType expected{ 1 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Abs2Test1
BOOST_AUTO_TEST_CASE( Abs2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, (- 0.f) } );
    ArrayType expected{ 1, 0 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Abs3Test1
BOOST_AUTO_TEST_CASE( Abs3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity() } );
    ArrayType expected{ 1, 0, std::numeric_limits<typename Traits::Type>::infinity( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Abs4Test1
BOOST_AUTO_TEST_CASE( Abs4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN()} );
    ArrayType expected{ 1, 0, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Abs5Test1
BOOST_AUTO_TEST_CASE( Abs5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5 } );
    ArrayType expected{ 1, 0, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Abs6Test1
BOOST_AUTO_TEST_CASE( Abs6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6 } );
    ArrayType expected{ 1, 0, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Abs7Test1
BOOST_AUTO_TEST_CASE( Abs7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6, -7 } );
    ArrayType expected{ 1, 0, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6, 7 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Abs8Test1
BOOST_AUTO_TEST_CASE( Abs8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6, -7, 8 } );
    ArrayType expected{ 1, 0, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6, 7, 8 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Min1Test1
BOOST_AUTO_TEST_CASE( Min1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1 } );
    ArrayType arg2( { 1 } );
    ArrayType expected{ -1 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Min2Test1
BOOST_AUTO_TEST_CASE( Min2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ) } );
    ArrayType arg2( { -1, ( 0.f ) } );
    ArrayType expected{ -1, -0.f };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Min3Test1
BOOST_AUTO_TEST_CASE( Min3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType arg2( { -1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType expected{ -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Min4Test1
BOOST_AUTO_TEST_CASE( Min4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType expected{ -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Min5Test1
BOOST_AUTO_TEST_CASE( Min5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5 } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5 } );
    ArrayType expected{ -1, -0.f, -std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Min6Test1
BOOST_AUTO_TEST_CASE( Min6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6 } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6 } );
    ArrayType expected{ -1, -0.f, -std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Min7Test1
BOOST_AUTO_TEST_CASE( Min7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6, -7 } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6, 7 } );
    ArrayType expected{ -1, -0.f, -std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6, -7 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Min8Test1
BOOST_AUTO_TEST_CASE( Min8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6, -7, 8 } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6, 7, 9 } );
    ArrayType expected{ -1, -0.f, -std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6, -7, 8 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Min( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Max1Test1
BOOST_AUTO_TEST_CASE( Max1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1 } );
    ArrayType arg2( { 1 } );
    ArrayType expected{ 1 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Max2Test1
BOOST_AUTO_TEST_CASE( Max2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ) } );
    ArrayType arg2( { 1, ( 0.f ) } );
    ArrayType expected{ 1, 0.f };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Max3Test1
BOOST_AUTO_TEST_CASE( Max3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ) } );
    ArrayType expected{ 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Max4Test1
BOOST_AUTO_TEST_CASE( Max4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
    ArrayType expected{ 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ) };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Max5Test1
BOOST_AUTO_TEST_CASE( Max5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5 } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5 } );
    ArrayType expected{ 1, 0.f, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Max6Test1
BOOST_AUTO_TEST_CASE( Max6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6 } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6 } );
    ArrayType expected{ 1, 0.f, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Max7Test1
BOOST_AUTO_TEST_CASE( Max7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6, -7 } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6, 7 } );
    ArrayType expected{ 1, 0.f, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6, 7 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Max8Test1
BOOST_AUTO_TEST_CASE( Max8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), -5, -6, -7, 8 } );
    ArrayType arg2( { 1, ( 0.f ), std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6, 7, 9 } );
    ArrayType expected{ 1, 0.f, std::numeric_limits<typename Traits::Type>::infinity( ),std::numeric_limits<typename Traits::Type>::quiet_NaN( ), 5, 6, 7, 9 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Max( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );
    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Lerp1Test1
BOOST_AUTO_TEST_CASE( Lerp1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12 } );
    ArrayType arg2( { 0 } );
    ArrayType arg3( { 0.5 } );
    ArrayType expected{ 6 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Lerp2Test1
BOOST_AUTO_TEST_CASE( Lerp2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 0 } );
    ArrayType arg2( { 0, 12 } );
    ArrayType arg3( { 0.5, 1 } );
    ArrayType expected{ 6, 12 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < expected.size( ); i++ )
    {
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( expected[ i ] ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == expected[ i ] );
        }
    }
}

// --run_test=SIMDFloatTests/Lerp3Test1
BOOST_AUTO_TEST_CASE( Lerp3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 5, 12 } );
    ArrayType arg2( { 34, 12, 3 } );
    ArrayType arg3( { 0.5, 1.5, .5f } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( val ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == val );
        }
    }
}

// --run_test=SIMDFloatTests/Lerp4Test1
BOOST_AUTO_TEST_CASE( Lerp4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 5, 12, 5 } );
    ArrayType arg2( { 34, 12, 3, -4 } );
    ArrayType arg3( { 0.5, 1.5, .5f, -0.5f } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( val ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == val );
        }
    }
}

// --run_test=SIMDFloatTests/Lerp5Test1
BOOST_AUTO_TEST_CASE( Lerp5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 5, 12, 5, -10 } );
    ArrayType arg2( { 34, 12, 3, -4, -3 } );
    ArrayType arg3( { 0.5, 1.5, .5f, -0.5f, 4 } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( val ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == val );
        }
    }
}

// --run_test=SIMDFloatTests/Lerp6Test1
BOOST_AUTO_TEST_CASE( Lerp6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 5, 12, 5, -10, -7 } );
    ArrayType arg2( { 34, 12, 3, -4, -3, -3 } );
    ArrayType arg3( { 0.5, 1.5, .5f, -0.5f, 4, -2 } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( val ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == val );
        }
    }
}

// --run_test=SIMDFloatTests/Lerp7Test1
BOOST_AUTO_TEST_CASE( Lerp7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 5, 12, 5, -10, -7, 0.5 } );
    ArrayType arg2( { 34, 12, 3, -4, -3, -3, 4 } );
    ArrayType arg3( { 0.5, 1.5, .5f, -0.5f, 4, -2, 13 } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( val ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == val );
        }
    }
}

// --run_test=SIMDFloatTests/Lerp8Test1
BOOST_AUTO_TEST_CASE( Lerp8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 5, 12, 5, -10, -7, 0.5, 20 } );
    ArrayType arg2( { 34, 12, 3, -4, -3, -3, 4, 10 } );
    ArrayType arg3( { 0.5, 1.5, .5f, -0.5f, 4, -2, 13, 3 } );
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto rmm4 = Traits::Lerp( rmm1, rmm2, rmm3 );

    auto result = Traits::ToArray( rmm4 );

    for ( size_t i = 0; i < result.size( ); i++ )
    {
        auto val = std::lerp( arg1[ i ], arg2[ i ], arg3[ i ] );
        if ( Math::IsNaN( result[ i ] ) )
        {
            BOOST_CHECK( Math::IsNaN( val ) );
        }
        else
        {
            BOOST_CHECK( result[ i ] == val );
        }
    }
}


// --run_test=SIMDFloatTests/HasNaN1Test1
BOOST_AUTO_TEST_CASE( HasNaN1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { NaN } );
    ArrayType arg2( { 1 } );
    
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;


    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HasNaN2Test1
BOOST_AUTO_TEST_CASE( HasNaN2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2, NaN } );
    ArrayType arg2( { 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;


    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HasNaN3Test1
BOOST_AUTO_TEST_CASE( HasNaN3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 3, 2, NaN } );
    ArrayType arg2( { 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;


    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HasNaN4Test1
BOOST_AUTO_TEST_CASE( HasNaN4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 4, 3, 2, NaN } );
    ArrayType arg2( { 4, 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;

    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HasNaN5Test1
BOOST_AUTO_TEST_CASE( HasNaN5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 5, 4, 3, 2, NaN } );
    ArrayType arg2( { 5, 4, 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;

    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HasNaN5Test2
BOOST_AUTO_TEST_CASE( HasNaN5Test2 )
{
    using Traits = SIMD::Traits<float, 5>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { NaN, 4, 3, 2, 1 } );
    ArrayType arg2( { 5, 4, 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;

    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HasNaN6Test1
BOOST_AUTO_TEST_CASE( HasNaN6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 6, NaN, 4, 3, 2, 1 } );
    ArrayType arg2( { 6, 5, 4, 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;

    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}


// --run_test=SIMDFloatTests/HasNaN6Test2
BOOST_AUTO_TEST_CASE( HasNaN6Test2 )
{
    using Traits = SIMD::Traits<float, 6>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { NaN, 5, 4, 3, 2, 1 } );
    ArrayType arg2( { 6, 5, 4, 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;

    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HasNaN7Test1
BOOST_AUTO_TEST_CASE( HasNaN7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { NaN, 6, 5, 4, 3, 2, 1 } );
    ArrayType arg2( { 7, 6, 5, 4, 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;

    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HasNaN8Test1
BOOST_AUTO_TEST_CASE( HasNaN8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { NaN, 7, 6, 5, 4, 3, 2, 1 } );
    ArrayType arg2( { 8, 7, 6, 5, 4, 3, 2, 1 } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto hasNaN = Traits::HasNaN( rmm1 );
    auto hasNotNaN = Traits::HasNaN( rmm2 ) == false;

    BOOST_CHECK( hasNaN );
    BOOST_CHECK( hasNotNaN );
}

// --run_test=SIMDFloatTests/HProd1Test1
BOOST_AUTO_TEST_CASE( HProd1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[i] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/HProd2Test1
BOOST_AUTO_TEST_CASE( HProd2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, 3.1f } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/HProd3Test1
BOOST_AUTO_TEST_CASE( HProd3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, 3.1f, -1.7f } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/HProd4Test1
BOOST_AUTO_TEST_CASE( HProd4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, 3.1f, -1.7f, -3.9f } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/HProd5Test1
BOOST_AUTO_TEST_CASE( HProd5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, 3.1f, -1.7f, -3.9f, 2.8f } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/HProd6Test1
BOOST_AUTO_TEST_CASE( HProd6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, 3.1f, -1.7f, -3.9f, 2.8f, 2.54f } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/HProd7Test1
BOOST_AUTO_TEST_CASE( HProd7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, 3.1f, -1.7f, -3.9f, 2.8f, 2.54f, 1.84f } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        BOOST_CHECK_CLOSE( expected[ i ], result[i],0.001f );
    }

    
}

// --run_test=SIMDFloatTests/HProd8Test1
BOOST_AUTO_TEST_CASE( HProd8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, 3.1f, -1.7f, -3.9f, 2.8f, 2.54f, 1.84f, 0.77f } );
    auto one = static_cast< Type >( 1 );
    Type value = one;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        value *= arg1[ i ];
    }
    ArrayType expected;
    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        expected[ i ] = value;
    }

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::HProd( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Dot1Test1
BOOST_AUTO_TEST_CASE( Dot1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f } );
    ArrayType arg2( { 3.0f } );

    auto dotProduct = inner_product( arg1.begin( ), arg1.end( ), arg2.begin( ), 0.f );

    ArrayType expected;
    std::fill( expected.begin( ), expected.end( ), dotProduct );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Dot( rmm1, rmm2 );
    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Dot2Test1
BOOST_AUTO_TEST_CASE( Dot2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, -1.0f } );
    ArrayType arg2( { 3.0f, -2.0f } );

    auto dotProduct = inner_product( arg1.begin( ), arg1.end( ), arg2.begin( ), 0.f );

    ArrayType expected;
    std::fill( expected.begin( ), expected.end( ), dotProduct );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Dot( rmm1, rmm2 );
    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Dot3Test1
BOOST_AUTO_TEST_CASE( Dot3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, -1.0f, 2.f } );
    ArrayType arg2( { 3.0f, -2.0f, 4.f } );

    auto dotProduct = inner_product( arg1.begin( ), arg1.end( ), arg2.begin( ), 0.f );

    ArrayType expected;
    std::fill( expected.begin( ), expected.end( ), dotProduct );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Dot( rmm1, rmm2 );
    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Dot4Test1
BOOST_AUTO_TEST_CASE( Dot4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, -1.0f, 2.f, 1.0f } );
    ArrayType arg2( { 3.0f, -2.0f, 4.f, 1.2f } );

    auto dotProduct = inner_product( arg1.begin( ), arg1.end( ), arg2.begin( ), 0.f );

    ArrayType expected;
    std::fill( expected.begin( ), expected.end( ), dotProduct );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Dot( rmm1, rmm2 );
    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Dot5Test1
BOOST_AUTO_TEST_CASE( Dot5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, -1.0f, 2.f, 1.0f, -5.f } );
    ArrayType arg2( { 3.0f, -2.0f, 4.f, 1.2f, 5.f } );

    auto dotProduct = inner_product( arg1.begin( ), arg1.end( ), arg2.begin( ), 0.f );

    ArrayType expected;
    std::fill( expected.begin( ), expected.end( ), dotProduct );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Dot( rmm1, rmm2 );
    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDFloatTests/Dot6Test1
BOOST_AUTO_TEST_CASE( Dot6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, -1.0f, 2.f, 1.0f, -5.f, 1.6f } );
    ArrayType arg2( { 3.0f, -2.0f, 4.f, 1.2f, 5.f, 1.7f } );

    auto dotProduct = inner_product( arg1.begin( ), arg1.end( ), arg2.begin( ), 0.f );

    ArrayType expected;
    std::fill( expected.begin( ), expected.end( ), dotProduct );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Dot( rmm1, rmm2 );
    auto result = Traits::ToArray( rmm3 );

    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        BOOST_CHECK_CLOSE( expected[ i ], result[ i ], 0.001f );
    }
}

// --run_test=SIMDFloatTests/Dot7Test1
BOOST_AUTO_TEST_CASE( Dot7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, -1.0f, 2.f, 1.0f, -5.f, 1.6f, 2.f } );
    ArrayType arg2( { 3.0f, -2.0f, 4.f, 1.2f, 5.f, 1.7f, 2.f } );

    auto dotProduct = inner_product( arg1.begin( ), arg1.end( ), arg2.begin( ), 0.f );

    ArrayType expected;
    std::fill( expected.begin( ), expected.end( ), dotProduct );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Dot( rmm1, rmm2 );
    auto result = Traits::ToArray( rmm3 );

    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        BOOST_CHECK_CLOSE( expected[ i ], result[ i ], 0.001f );
    }
}

// --run_test=SIMDFloatTests/Dot8Test1
BOOST_AUTO_TEST_CASE( Dot8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0f, -1.0f, 2.f, 1.0f, -5.f, 1.6f, 2.f, 3.f } );
    ArrayType arg2( { 3.0f, -2.0f, 4.f, 1.2f, 5.f, 1.7f, 2.f, 3.f } );

    auto dotProduct = inner_product( arg1.begin( ), arg1.end( ), arg2.begin( ), 0.f );

    ArrayType expected;
    std::fill( expected.begin( ), expected.end( ), dotProduct );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Dot( rmm1, rmm2 );
    auto result = Traits::ToArray( rmm3 );

    for ( size_t i = 0; i < arg1.size( ); i++ )
    {
        BOOST_CHECK_CLOSE( expected[ i ], result[ i ], 0.001f );
    }
}

// --run_test=SIMDFloatTests/At1Test1
BOOST_AUTO_TEST_CASE( At1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f } );
    auto expected = Traits::Fill( 1.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected );
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/At2Test1
BOOST_AUTO_TEST_CASE( At2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f } );
    auto expected1 = SIMD::Traits<float, 4>::Fill( 1.f );
    auto expected2 = SIMD::Traits<float, 4>::Fill( 2.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/At3Test1
BOOST_AUTO_TEST_CASE( At3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f } );
    auto expected1 = SIMD::Traits<float, 4>::Fill( 1.f );
    auto expected2 = SIMD::Traits<float, 4>::Fill( 2.f );
    auto expected3 = SIMD::Traits<float, 4>::Fill( 3.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<2>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected3 );
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/At4Test1
BOOST_AUTO_TEST_CASE( At4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f } );
    auto expected1 = SIMD::Traits<float, 4>::Fill( 1.f );
    auto expected2 = SIMD::Traits<float, 4>::Fill( 2.f );
    auto expected3 = SIMD::Traits<float, 4>::Fill( 3.f );
    auto expected4 = SIMD::Traits<float, 4>::Fill( 4.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<2>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected3 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<3>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected4 );
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/At5Test1
BOOST_AUTO_TEST_CASE( At5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f, 5.f } );
    auto expected1 = SIMD::Traits<float, 8>::Fill( 1.f );
    auto expected2 = SIMD::Traits<float, 8>::Fill( 2.f );
    auto expected3 = SIMD::Traits<float, 8>::Fill( 3.f );
    auto expected4 = SIMD::Traits<float, 8>::Fill( 4.f );
    auto expected5 = SIMD::Traits<float, 8>::Fill( 5.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<2>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected3 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<3>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected4 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<4>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected5 );
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/At6Test1
BOOST_AUTO_TEST_CASE( At6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f } );
    auto expected1 = SIMD::Traits<float, 8>::Fill( 1.f );
    auto expected2 = SIMD::Traits<float, 8>::Fill( 2.f );
    auto expected3 = SIMD::Traits<float, 8>::Fill( 3.f );
    auto expected4 = SIMD::Traits<float, 8>::Fill( 4.f );
    auto expected5 = SIMD::Traits<float, 8>::Fill( 5.f );
    auto expected6 = SIMD::Traits<float, 8>::Fill( 6.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<2>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected3 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<3>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected4 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<4>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected5 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<5>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected6 );
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/At7Test1
BOOST_AUTO_TEST_CASE( At7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f } );
    auto expected1 = SIMD::Traits<float, 8>::Fill( 1.f );
    auto expected2 = SIMD::Traits<float, 8>::Fill( 2.f );
    auto expected3 = SIMD::Traits<float, 8>::Fill( 3.f );
    auto expected4 = SIMD::Traits<float, 8>::Fill( 4.f );
    auto expected5 = SIMD::Traits<float, 8>::Fill( 5.f );
    auto expected6 = SIMD::Traits<float, 8>::Fill( 6.f );
    auto expected7 = SIMD::Traits<float, 8>::Fill( 7.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<2>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected3 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<3>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected4 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<4>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected5 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<5>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected6 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<6>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected7 );
    BOOST_CHECK( equal );
}


// --run_test=SIMDFloatTests/At8Test1
BOOST_AUTO_TEST_CASE( At8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f } );
    auto expected1 = SIMD::Traits<float, 8>::Fill( 1.f );
    auto expected2 = SIMD::Traits<float, 8>::Fill( 2.f );
    auto expected3 = SIMD::Traits<float, 8>::Fill( 3.f );
    auto expected4 = SIMD::Traits<float, 8>::Fill( 4.f );
    auto expected5 = SIMD::Traits<float, 8>::Fill( 5.f );
    auto expected6 = SIMD::Traits<float, 8>::Fill( 6.f );
    auto expected7 = SIMD::Traits<float, 8>::Fill( 7.f );
    auto expected8 = SIMD::Traits<float, 8>::Fill( 8.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<2>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected3 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<3>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected4 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<4>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected5 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<5>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected6 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<6>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected7 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<7>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected8 );
    BOOST_CHECK( equal );

}

// --run_test=SIMDFloatTests/Extract1Test1
BOOST_AUTO_TEST_CASE( Extract1Test1 )
{
    using Traits = SIMD::Traits<float, 1>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f } );
    auto expected = 1.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected == extracted;
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/Extract2Test1
BOOST_AUTO_TEST_CASE( Extract2Test1 )
{
    using Traits = SIMD::Traits<float, 2>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    BOOST_CHECK( equal );
}


// --run_test=SIMDFloatTests/Extract3Test1
BOOST_AUTO_TEST_CASE( Extract3Test1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto expected3 = 3.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<2>( rmm1 );
    equal = expected3 == extracted;
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/Extract4Test1
BOOST_AUTO_TEST_CASE( Extract4Test1 )
{
    using Traits = SIMD::Traits<float, 4>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto expected3 = 3.f;
    auto expected4 = 4.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<2>( rmm1 );
    equal = expected3 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<3>( rmm1 );
    equal = expected4 == extracted;
    BOOST_CHECK( equal );
}


// --run_test=SIMDFloatTests/Extract5Test1
BOOST_AUTO_TEST_CASE( Extract5Test1 )
{
    using Traits = SIMD::Traits<float, 5>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f, 5.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto expected3 = 3.f;
    auto expected4 = 4.f;
    auto expected5 = 5.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<2>( rmm1 );
    equal = expected3 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<3>( rmm1 );
    equal = expected4 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<4>( rmm1 );
    equal = expected5 == extracted;
    BOOST_CHECK( equal );
}

// --run_test=SIMDFloatTests/Extract6Test1
BOOST_AUTO_TEST_CASE( Extract6Test1 )
{
    using Traits = SIMD::Traits<float, 6>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto expected3 = 3.f;
    auto expected4 = 4.f;
    auto expected5 = 5.f;
    auto expected6 = 6.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<2>( rmm1 );
    equal = expected3 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<3>( rmm1 );
    equal = expected4 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<4>( rmm1 );
    equal = expected5 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<5>( rmm1 );
    equal = expected6 == extracted;
    BOOST_CHECK( equal );

}

// --run_test=SIMDFloatTests/Extract7Test1
BOOST_AUTO_TEST_CASE( Extract7Test1 )
{
    using Traits = SIMD::Traits<float, 7>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto expected3 = 3.f;
    auto expected4 = 4.f;
    auto expected5 = 5.f;
    auto expected6 = 6.f;
    auto expected7 = 7.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<2>( rmm1 );
    equal = expected3 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<3>( rmm1 );
    equal = expected4 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<4>( rmm1 );
    equal = expected5 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<5>( rmm1 );
    equal = expected6 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<6>( rmm1 );
    equal = expected7 == extracted;
    BOOST_CHECK( equal );

}

// --run_test=SIMDFloatTests/Extract8Test1
BOOST_AUTO_TEST_CASE( Extract8Test1 )
{
    using Traits = SIMD::Traits<float, 8>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f } );
    auto expected1 = 1.f;
    auto expected2 = 2.f;
    auto expected3 = 3.f;
    auto expected4 = 4.f;
    auto expected5 = 5.f;
    auto expected6 = 6.f;
    auto expected7 = 7.f;
    auto expected8 = 8.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected1 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<1>( rmm1 );
    equal = expected2 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<2>( rmm1 );
    equal = expected3 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<3>( rmm1 );
    equal = expected4 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<4>( rmm1 );
    equal = expected5 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<5>( rmm1 );
    equal = expected6 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<6>( rmm1 );
    equal = expected7 == extracted;
    BOOST_CHECK( equal );

    extracted = Traits::Extract<7>( rmm1 );
    equal = expected8 == extracted;
    BOOST_CHECK( equal );

}


// --run_test=SIMDFloatTests/Shuffle2x4Test1
BOOST_AUTO_TEST_CASE( ShuffleTest1 )
{
    using Traits = SIMD::Traits<float, 3>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;

    ArrayType arg1( { 1.f, 2.f, 3.f } );
    ArrayType arg2( { 4.f, 5.f, 6.f } );
    ArrayType arg3( { 7.f, 8.f, 9.f } );

    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );

    auto rmm4 = Traits::Shuffle<1, 0, 1, 0>( rmm1, rmm2 );
    auto rmm5 = Traits::Shuffle<2, 2, 2, 2>( rmm1, rmm2 );

    auto rmm6 = Traits::Shuffle<3, 0, 2, 0>( rmm4, rmm3 );
    auto rmm7 = Traits::Shuffle<3, 1, 3, 1>( rmm4, rmm3 );
    auto rmm8 = Traits::Shuffle<3, 2, 2, 0>( rmm5, rmm3 );

    auto result1 = Traits::ToArray( rmm6 );
    auto result2 = Traits::ToArray( rmm7 );
    auto result3 = Traits::ToArray( rmm8 );
    
    ArrayType expected1( { 1.f, 4.f, 7.f } );
    ArrayType expected2( { 2.f, 5.f, 8.f } );
    ArrayType expected3( { 3.f, 6.f, 9.f } );

    bool equal = result1 == expected1;
    BOOST_CHECK( equal );

    equal = result2 == expected2;
    BOOST_CHECK( equal );

    equal = result3 == expected3;
    BOOST_CHECK( equal );



}



BOOST_AUTO_TEST_SUITE_END( )