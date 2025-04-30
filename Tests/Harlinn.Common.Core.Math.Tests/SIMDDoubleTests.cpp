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
BOOST_FIXTURE_TEST_SUITE( SIMDDoubleTests, LocalFixture )

// --run_test=SIMDDoubleTests/Set1Test1
BOOST_AUTO_TEST_CASE( Set1Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<double, 2> result;
    Traits::Store( result.data( ), rmm1 );
    
    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 0.0 );
}

// --run_test=SIMDDoubleTests/Set1Test2
BOOST_AUTO_TEST_CASE( Set1Test2 )
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 0.0 );
    BOOST_CHECK( result[ 2 ] == 0.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
}

// --run_test=SIMDDoubleTests/Set2Test1
BOOST_AUTO_TEST_CASE( Set2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<double, 2> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
}

// --run_test=SIMDDoubleTests/Set2Test2
BOOST_AUTO_TEST_CASE( Set2Test2 )
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 0.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
}

// --run_test=SIMDDoubleTests/Set3Test1
BOOST_AUTO_TEST_CASE( Set3Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 0.0 );
}

// --run_test=SIMDDoubleTests/Set4Test1
BOOST_AUTO_TEST_CASE( Set4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1.0 );
    BOOST_CHECK( result[ 1 ] == 2.0 );
    BOOST_CHECK( result[ 2 ] == 3.0 );
    BOOST_CHECK( result[ 3 ] == 4.0 );
}


// --run_test=SIMDDoubleTests/HorizontalMin1Test1
BOOST_AUTO_TEST_CASE( HorizontalMin1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    auto rmm1 = Traits::Set( -3 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}

// --run_test=SIMDDoubleTests/HorizontalMin2Test1
BOOST_AUTO_TEST_CASE( HorizontalMin2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( -3, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}

// --run_test=SIMDDoubleTests/HorizontalMin3Test1
BOOST_AUTO_TEST_CASE( HorizontalMin3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
    auto rmm1 = Traits::Set( -3, 100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}

// --run_test=SIMDDoubleTests/HorizontalMin4Test1
BOOST_AUTO_TEST_CASE( HorizontalMin4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( -3, 0, 100, 1 );
    auto minValue = Traits::HorizontalMin( rmm1 );

    BOOST_CHECK( minValue == -3.f );
}

// --run_test=SIMDDoubleTests/HorizontalMax1Test1
BOOST_AUTO_TEST_CASE( HorizontalMax1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    auto rmm1 = Traits::Set( -3 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == -3.f );
}


// --run_test=SIMDDoubleTests/HorizontalMax2Test1
BOOST_AUTO_TEST_CASE( HorizontalMax2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( -3, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 1.f );
}

// --run_test=SIMDDoubleTests/HorizontalMax3Test1
BOOST_AUTO_TEST_CASE( HorizontalMax3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
    auto rmm1 = Traits::Set( -3, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 100.f );
}

// --run_test=SIMDDoubleTests/HorizontalMax4Test1
BOOST_AUTO_TEST_CASE( HorizontalMax4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 101, -40, 100, 1 );
    auto maxValue = Traits::HorizontalMax( rmm1 );

    BOOST_CHECK( maxValue == 101.f );
}


// --run_test=SIMDDoubleTests/HSum1Test1
BOOST_AUTO_TEST_CASE( HSum1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    auto expected = -3.f;
    auto rmm1 = Traits::Set( expected );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
}

// --run_test=SIMDDoubleTests/HSum2Test1
BOOST_AUTO_TEST_CASE( HSum2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    auto expected = -3.f + 5;
    auto rmm1 = Traits::Set( -3.f, 5.f );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
    BOOST_CHECK( result[ 1 ] == expected );
}

// --run_test=SIMDDoubleTests/HSum3Test1
BOOST_AUTO_TEST_CASE( HSum3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
    auto rmm1 = Traits::Set( 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == 11.0 );
    BOOST_CHECK( result[ 1 ] == 11.0 );
    BOOST_CHECK( result[ 2 ] == 11.0 );
}


// --run_test=SIMDDoubleTests/HSum4Test1
BOOST_AUTO_TEST_CASE( HSum4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 21, 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == 32.0 );
    BOOST_CHECK( result[ 1 ] == 32.0 );
    BOOST_CHECK( result[ 2 ] == 32.0 );
    BOOST_CHECK( result[ 3 ] == 32.0 );
}

// --run_test=SIMDDoubleTests/Equal1Test1
BOOST_AUTO_TEST_CASE( Equal1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1 } );
    ArrayType arg2( { 1 } );
    ArrayType arg3( { -1 } );

    
    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto equal = Traits::AllEqual( rmm1, rmm2 );

    BOOST_CHECK( equal );

    equal = Traits::AllEqual( rmm1, rmm3 );

    BOOST_CHECK( equal == false );
}

// --run_test=SIMDDoubleTests/Equal2Test1
BOOST_AUTO_TEST_CASE( Equal2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1, 2 } );
    ArrayType arg2( { 1, 2 } );
    ArrayType arg3( { -1, 2 } );


    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto equal = Traits::AllEqual( rmm1, rmm2 );

    BOOST_CHECK( equal );

    equal = Traits::AllEqual( rmm1, rmm3 );

    BOOST_CHECK( equal == false );
}

// --run_test=SIMDDoubleTests/Equal3Test1
BOOST_AUTO_TEST_CASE( Equal3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1, 2, 3 } );
    ArrayType arg2( { 1, 2, 3 } );
    ArrayType arg3( { -1, 2, 3 } );


    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto equal = Traits::AllEqual( rmm1, rmm2 );

    BOOST_CHECK( equal );

    equal = Traits::AllEqual( rmm1, rmm3 );

    BOOST_CHECK( equal == false );
}

// --run_test=SIMDDoubleTests/Equal4Test1
BOOST_AUTO_TEST_CASE( Equal4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1, 2, 3, 4 } );
    ArrayType arg2( { 1, 2, 3, 4 } );
    ArrayType arg3( { -1, 2, 3, 4 } );


    auto rmm1 = Traits::Load( arg1 );
    auto rmm2 = Traits::Load( arg2 );
    auto rmm3 = Traits::Load( arg3 );
    auto equal = Traits::AllEqual( rmm1, rmm2 );

    BOOST_CHECK( equal );

    equal = Traits::AllEqual( rmm1, rmm3 );

    BOOST_CHECK( equal == false );
}

// --run_test=SIMDDoubleTests/Add1Test1
BOOST_AUTO_TEST_CASE( Add1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
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

// --run_test=SIMDDoubleTests/Add2Test1
BOOST_AUTO_TEST_CASE( Add2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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


// --run_test=SIMDDoubleTests/Add3Test1
BOOST_AUTO_TEST_CASE( Add3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/Add4Test1
BOOST_AUTO_TEST_CASE( Add4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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

// --run_test=SIMDDoubleTests/Sub1Test1
BOOST_AUTO_TEST_CASE( Sub1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
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

// --run_test=SIMDDoubleTests/Sub2Test1
BOOST_AUTO_TEST_CASE( Sub2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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


// --run_test=SIMDDoubleTests/Sub3Test1
BOOST_AUTO_TEST_CASE( Sub3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/Sub4Test1
BOOST_AUTO_TEST_CASE( Sub4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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

// --run_test=SIMDDoubleTests/Mul1Test1
BOOST_AUTO_TEST_CASE( Mul1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
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

// --run_test=SIMDDoubleTests/Mul2Test1
BOOST_AUTO_TEST_CASE( Mul2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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


// --run_test=SIMDDoubleTests/Mul3Test1
BOOST_AUTO_TEST_CASE( Mul3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/Mul4Test1
BOOST_AUTO_TEST_CASE( Mul4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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


// --run_test=SIMDDoubleTests/Div1Test1
BOOST_AUTO_TEST_CASE( Div1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
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

// --run_test=SIMDDoubleTests/Div2Test1
BOOST_AUTO_TEST_CASE( Div2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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


// --run_test=SIMDDoubleTests/Div3Test1
BOOST_AUTO_TEST_CASE( Div3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/Div4Test1
BOOST_AUTO_TEST_CASE( Div4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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

// --run_test=SIMDDoubleTests/AddSub1Test1
BOOST_AUTO_TEST_CASE( AddSub1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
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

// --run_test=SIMDDoubleTests/AddSub2Test1
BOOST_AUTO_TEST_CASE( AddSub2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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


// --run_test=SIMDDoubleTests/AddSub3Test1
BOOST_AUTO_TEST_CASE( AddSub3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/AddSub4Test1
BOOST_AUTO_TEST_CASE( AddSub4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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

// --run_test=SIMDDoubleTests/Abs1Test1
BOOST_AUTO_TEST_CASE( Abs1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1 } );
    ArrayType expected{ 1 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDDoubleTests/Abs2Test1
BOOST_AUTO_TEST_CASE( Abs2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ) } );
    ArrayType expected{ 1, 0 };
    auto rmm1 = Traits::Load( arg1 );
    auto rmm3 = Traits::Abs( rmm1 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result == expected );
}

// --run_test=SIMDDoubleTests/Abs3Test1
BOOST_AUTO_TEST_CASE( Abs3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ) } );
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

// --run_test=SIMDDoubleTests/Abs4Test1
BOOST_AUTO_TEST_CASE( Abs4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { -1, ( -0.f ), -std::numeric_limits<typename Traits::Type>::infinity( ), std::numeric_limits<typename Traits::Type>::quiet_NaN( ) } );
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

// --run_test=SIMDDoubleTests/Min1Test1
BOOST_AUTO_TEST_CASE( Min1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
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

// --run_test=SIMDDoubleTests/Min2Test1
BOOST_AUTO_TEST_CASE( Min2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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

// --run_test=SIMDDoubleTests/Min3Test1
BOOST_AUTO_TEST_CASE( Min3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/Min4Test1
BOOST_AUTO_TEST_CASE( Min4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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

// --run_test=SIMDDoubleTests/Max1Test1
BOOST_AUTO_TEST_CASE( Max1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
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

// --run_test=SIMDDoubleTests/Max2Test1
BOOST_AUTO_TEST_CASE( Max2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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

// --run_test=SIMDDoubleTests/Max3Test1
BOOST_AUTO_TEST_CASE( Max3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/Max4Test1
BOOST_AUTO_TEST_CASE( Max4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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

// --run_test=SIMDDoubleTests/Lerp1Test1
BOOST_AUTO_TEST_CASE( Lerp1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12 } );
    ArrayType arg2( { 0 } );
    ArrayType arg3( { 0.5 } );
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

// --run_test=SIMDDoubleTests/Lerp2Test1
BOOST_AUTO_TEST_CASE( Lerp2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 12, 0 } );
    ArrayType arg2( { 0, 12 } );
    ArrayType arg3( { 0.5, 1 } );
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

// --run_test=SIMDDoubleTests/Lerp3Test1
BOOST_AUTO_TEST_CASE( Lerp3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/Lerp4Test1
BOOST_AUTO_TEST_CASE( Lerp4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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

// --run_test=SIMDDoubleTests/HasNaN1Test1
BOOST_AUTO_TEST_CASE( HasNaN1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
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

// --run_test=SIMDDoubleTests/HasNaN2Test1
BOOST_AUTO_TEST_CASE( HasNaN2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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

// --run_test=SIMDDoubleTests/HasNaN3Test1
BOOST_AUTO_TEST_CASE( HasNaN3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/HasNaN4Test1
BOOST_AUTO_TEST_CASE( HasNaN4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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

// --run_test=SIMDDoubleTests/HProd1Test1
BOOST_AUTO_TEST_CASE( HProd1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0 } );
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

// --run_test=SIMDDoubleTests/HProd2Test1
BOOST_AUTO_TEST_CASE( HProd2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0, 3.1 } );
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

// --run_test=SIMDDoubleTests/HProd3Test1
BOOST_AUTO_TEST_CASE( HProd3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0, 3.1, -1.7 } );
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

// --run_test=SIMDDoubleTests/HProd4Test1
BOOST_AUTO_TEST_CASE( HProd4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    using Type = typename Traits::Type;
    constexpr auto NaN = std::numeric_limits<Type>::quiet_NaN( );
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 2.0, 3.1, -1.7, -3.9 } );
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
        BOOST_CHECK_CLOSE( expected[ i ], result[ i ], 0.001f );
    }
}

// --run_test=SIMDDoubleTests/At1Test1
BOOST_AUTO_TEST_CASE( At1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f } );
    auto expected = Traits::Fill( 1.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected );
    BOOST_CHECK( equal );
}

// --run_test=SIMDDoubleTests/At2Test1
BOOST_AUTO_TEST_CASE( At2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f } );
    auto expected1 = SIMD::Traits<double, 2>::Fill( 1.f );
    auto expected2 = SIMD::Traits<double, 2>::Fill( 2.f );
    auto rmm1 = Traits::Load( arg1 );
    auto rmmAt = Traits::At<0>( rmm1 );
    auto equal = Traits::AllEqual( rmmAt, expected1 );
    BOOST_CHECK( equal );

    rmmAt = Traits::At<1>( rmm1 );
    equal = Traits::AllEqual( rmmAt, expected2 );
    BOOST_CHECK( equal );
}

// --run_test=SIMDDoubleTests/At3Test1
BOOST_AUTO_TEST_CASE( At3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f } );
    auto expected1 = SIMD::Traits<double, 4>::Fill( 1.f );
    auto expected2 = SIMD::Traits<double, 4>::Fill( 2.f );
    auto expected3 = SIMD::Traits<double, 4>::Fill( 3.f );
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

// --run_test=SIMDDoubleTests/At4Test1
BOOST_AUTO_TEST_CASE( At4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f, 2.f, 3.f, 4.f } );
    auto expected1 = SIMD::Traits<double, 4>::Fill( 1.f );
    auto expected2 = SIMD::Traits<double, 4>::Fill( 2.f );
    auto expected3 = SIMD::Traits<double, 4>::Fill( 3.f );
    auto expected4 = SIMD::Traits<double, 4>::Fill( 4.f );
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


// --run_test=SIMDDoubleTests/Extract1Test1
BOOST_AUTO_TEST_CASE( Extract1Test1 )
{
    using Traits = SIMD::Traits<double, 1>;
    using Type = typename Traits::Type;
    using ArrayType = typename Traits::ArrayType;
    ArrayType arg1( { 1.f } );
    auto expected = 1.f;
    auto rmm1 = Traits::Load( arg1 );
    auto extracted = Traits::Extract<0>( rmm1 );
    auto equal = expected == extracted;
    BOOST_CHECK( equal );
}

// --run_test=SIMDDoubleTests/Extract2Test1
BOOST_AUTO_TEST_CASE( Extract2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
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


// --run_test=SIMDDoubleTests/Extract3Test1
BOOST_AUTO_TEST_CASE( Extract3Test1 )
{
    using Traits = SIMD::Traits<double, 3>;
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

// --run_test=SIMDDoubleTests/Extract4Test1
BOOST_AUTO_TEST_CASE( Extract4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
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


BOOST_AUTO_TEST_SUITE_END( )