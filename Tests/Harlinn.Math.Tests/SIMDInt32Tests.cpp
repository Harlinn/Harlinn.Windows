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

#include <Harlinn/Math/Math.h>


using namespace Harlinn::Common::Core;
namespace SIMD = Harlinn::Math::SIMD;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        { }
        ~LocalFixture( )
        { }
    };

}

BOOST_FIXTURE_TEST_SUITE( SIMDInt32Tests, LocalFixture )

// --run_test=SIMDInt32Tests/Set1Test1
BOOST_AUTO_TEST_CASE( Set1Test1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 0 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set1Test2
BOOST_AUTO_TEST_CASE( Set1Test2 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 0 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 0 );
    BOOST_CHECK( result[ 4 ] == 0 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set2Test1
BOOST_AUTO_TEST_CASE( Set2Test1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set2Test2
BOOST_AUTO_TEST_CASE( Set2Test2 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 0 );
    BOOST_CHECK( result[ 4 ] == 0 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set3Test1
BOOST_AUTO_TEST_CASE( Set3Test1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 3 );
    BOOST_CHECK( result[ 3 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set3Test2
BOOST_AUTO_TEST_CASE( Set3Test2 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 3 );
    BOOST_CHECK( result[ 3 ] == 0 );
    BOOST_CHECK( result[ 4 ] == 0 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set4Test1
BOOST_AUTO_TEST_CASE( Set4Test1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 3);
    BOOST_CHECK( result[ 3 ] == 4 );
}

// --run_test=SIMDInt32Tests/Set4Test2
BOOST_AUTO_TEST_CASE( Set4Test2 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 3 );
    BOOST_CHECK( result[ 3 ] == 4 );
    BOOST_CHECK( result[ 4 ] == 0 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set5Test1
BOOST_AUTO_TEST_CASE( Set5Test1 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 3 );
    BOOST_CHECK( result[ 3 ] == 4 );
    BOOST_CHECK( result[ 4 ] == 5 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set6Test1
BOOST_AUTO_TEST_CASE( Set6Test1 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 3 );
    BOOST_CHECK( result[ 3 ] == 4 );
    BOOST_CHECK( result[ 4 ] == 5 );
    BOOST_CHECK( result[ 5 ] == 6 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set7Test1
BOOST_AUTO_TEST_CASE( Set7Test1 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 7, 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 3 );
    BOOST_CHECK( result[ 3 ] == 4 );
    BOOST_CHECK( result[ 4 ] == 5 );
    BOOST_CHECK( result[ 5 ] == 6 );
    BOOST_CHECK( result[ 6 ] == 7 );
    BOOST_CHECK( result[ 7 ] == 0 );
}

// --run_test=SIMDInt32Tests/Set8Test1
BOOST_AUTO_TEST_CASE( Set8Test1 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 8, 7, 6, 5, 4, 3, 2, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 2 );
    BOOST_CHECK( result[ 2 ] == 3 );
    BOOST_CHECK( result[ 3 ] == 4 );
    BOOST_CHECK( result[ 4 ] == 5 );
    BOOST_CHECK( result[ 5 ] == 6 );
    BOOST_CHECK( result[ 6 ] == 7 );
    BOOST_CHECK( result[ 7 ] == 8 );
}


// --run_test=SIMDInt32Tests/SetXTest1
BOOST_AUTO_TEST_CASE( SetXTest1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetX( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 0 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 0 );
}

// --run_test=SIMDInt32Tests/SetXTest2
BOOST_AUTO_TEST_CASE( SetXTest2 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetX( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 1 );
    BOOST_CHECK( result[ 1 ] == 0 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 0 );
    BOOST_CHECK( result[ 4 ] == 0 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}


// --run_test=SIMDInt32Tests/SetYTest1
BOOST_AUTO_TEST_CASE( SetYTest1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetY( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 0 );
    BOOST_CHECK( result[ 1 ] == 1 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 0 );
}

// --run_test=SIMDInt32Tests/SetYTest2
BOOST_AUTO_TEST_CASE( SetYTest2 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetY( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 0 );
    BOOST_CHECK( result[ 1 ] == 1 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 0 );
    BOOST_CHECK( result[ 4 ] == 0 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}


// --run_test=SIMDInt32Tests/SetZTest1
BOOST_AUTO_TEST_CASE( SetZTest1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetZ( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 0 );
    BOOST_CHECK( result[ 1 ] == 0 );
    BOOST_CHECK( result[ 2 ] == 1 );
    BOOST_CHECK( result[ 3 ] == 0 );
}

// --run_test=SIMDInt32Tests/SetZTest2
BOOST_AUTO_TEST_CASE( SetZTest2 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetZ( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 0 );
    BOOST_CHECK( result[ 1 ] == 0 );
    BOOST_CHECK( result[ 2 ] == 1 );
    BOOST_CHECK( result[ 3 ] == 0 );
    BOOST_CHECK( result[ 4 ] == 0 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}

// --run_test=SIMDInt32Tests/SetWTest1
BOOST_AUTO_TEST_CASE( SetWTest1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetW( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 4> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 0 );
    BOOST_CHECK( result[ 1 ] == 0 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 1 );
}

// --run_test=SIMDInt32Tests/SetWTest2
BOOST_AUTO_TEST_CASE( SetWTest2 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Zero( );
    rmm1 = Traits::SetW( rmm1, 1 );
    alignas( Traits::AlignAs ) std::array<int, 8> result;
    Traits::Store( result.data( ), rmm1 );

    BOOST_CHECK( result[ 0 ] == 0 );
    BOOST_CHECK( result[ 1 ] == 0 );
    BOOST_CHECK( result[ 2 ] == 0 );
    BOOST_CHECK( result[ 3 ] == 1 );
    BOOST_CHECK( result[ 4 ] == 0 );
    BOOST_CHECK( result[ 5 ] == 0 );
    BOOST_CHECK( result[ 6 ] == 0 );
    BOOST_CHECK( result[ 7 ] == 0 );
}


// --run_test=SIMDInt32Tests/Add1Test1
BOOST_AUTO_TEST_CASE( Add1Test1 )
{
    using Traits = SIMD::Traits<int, 1>;
    auto rmm1 = Traits::Set( 1 );
    auto rmm2 = Traits::Set( 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result.size( ) == 1 );
    BOOST_CHECK( result[ 0 ] == 3 );
}

// --run_test=SIMDInt32Tests/Add2Test1
BOOST_AUTO_TEST_CASE( Add2Test1 )
{
    using Traits = SIMD::Traits<int, 2>;
    auto rmm1 = Traits::Set( 2, 1 );
    auto rmm2 = Traits::Set( 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result.size( ) == 2 );
    BOOST_CHECK( result[ 0 ] == 3 );
    BOOST_CHECK( result[ 1 ] == 5 );
}

// --run_test=SIMDInt32Tests/Add3Test1
BOOST_AUTO_TEST_CASE( Add3Test1 )
{
    using Traits = SIMD::Traits<int, 3>;
    auto rmm1 = Traits::Set( 3, 2, 1 );
    auto rmm2 = Traits::Set( 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result.size( ) == 3 );
    BOOST_CHECK( result[ 0 ] == 3 );
    BOOST_CHECK( result[ 1 ] == 5 );
    BOOST_CHECK( result[ 2 ] == 7 );
}

// --run_test=SIMDInt32Tests/Add4Test1
BOOST_AUTO_TEST_CASE( Add4Test1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result.size( ) == 4 );
    BOOST_CHECK( result[ 0 ] == 3 );
    BOOST_CHECK( result[ 1 ] == 5 );
    BOOST_CHECK( result[ 2 ] == 7 );
    BOOST_CHECK( result[ 3 ] == 9 );
}

// --run_test=SIMDInt32Tests/Add5Test1
BOOST_AUTO_TEST_CASE( Add5Test1 )
{
    using Traits = SIMD::Traits<int, 5>;
    auto rmm1 = Traits::Set( 5, 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 6, 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result.size( ) == 5 );
    BOOST_CHECK( result[ 0 ] == 3 );
    BOOST_CHECK( result[ 1 ] == 5 );
    BOOST_CHECK( result[ 2 ] == 7 );
    BOOST_CHECK( result[ 3 ] == 9 );
    BOOST_CHECK( result[ 4 ] == 11 );
}

// --run_test=SIMDInt32Tests/Add6Test1
BOOST_AUTO_TEST_CASE( Add6Test1 )
{
    using Traits = SIMD::Traits<int, 6>;
    auto rmm1 = Traits::Set( 6, 5, 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 7, 6, 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result.size( ) == 6 );
    BOOST_CHECK( result[ 0 ] == 3 );
    BOOST_CHECK( result[ 1 ] == 5 );
    BOOST_CHECK( result[ 2 ] == 7 );
    BOOST_CHECK( result[ 3 ] == 9 );
    BOOST_CHECK( result[ 4 ] == 11 );
    BOOST_CHECK( result[ 5 ] == 13 );
}

// --run_test=SIMDInt32Tests/Add7Test1
BOOST_AUTO_TEST_CASE( Add7Test1 )
{
    using Traits = SIMD::Traits<int, 7>;
    auto rmm1 = Traits::Set( 7, 6, 5, 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 8, 7, 6, 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result.size( ) == 7 );
    BOOST_CHECK( result[ 0 ] == 3 );
    BOOST_CHECK( result[ 1 ] == 5 );
    BOOST_CHECK( result[ 2 ] == 7 );
    BOOST_CHECK( result[ 3 ] == 9 );
    BOOST_CHECK( result[ 4 ] == 11 );
    BOOST_CHECK( result[ 5 ] == 13 );
    BOOST_CHECK( result[ 6 ] == 15 );
}

// --run_test=SIMDInt32Tests/Add8Test1
BOOST_AUTO_TEST_CASE( Add8Test1 )
{
    using Traits = SIMD::Traits<int, 8>;
    auto rmm1 = Traits::Set( 8, 7, 6, 5, 4, 3, 2, 1 );
    auto rmm2 = Traits::Set( 9, 8, 7, 6, 5, 4, 3, 2 );
    auto rmm3 = Traits::Add( rmm1, rmm2 );

    auto result = Traits::ToArray( rmm3 );

    BOOST_CHECK( result.size( ) == 8 );
    BOOST_CHECK( result[ 0 ] == 3 );
    BOOST_CHECK( result[ 1 ] == 5 );
    BOOST_CHECK( result[ 2 ] == 7 );
    BOOST_CHECK( result[ 3 ] == 9 );
    BOOST_CHECK( result[ 4 ] == 11 );
    BOOST_CHECK( result[ 5 ] == 13 );
    BOOST_CHECK( result[ 6 ] == 15 );
    BOOST_CHECK( result[ 7 ] == 17 );
}



// --run_test=SIMDInt32Tests/HSum1Test1
BOOST_AUTO_TEST_CASE( HSum1Test1 )
{
    using Traits = SIMD::Traits<int, 1>;
    auto expected = -3.f;
    auto rmm1 = Traits::Set( expected );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
}

// --run_test=SIMDInt32Tests/HSum2Test1
BOOST_AUTO_TEST_CASE( HSum2Test1 )
{
    using Traits = SIMD::Traits<int, 2>;
    auto expected = -3 + 5;
    auto rmm1 = Traits::Set( -3, 5 );
    auto rmm2 = Traits::HSum( rmm1 );

    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == expected );
    BOOST_CHECK( result[ 1 ] == expected );
}

// --run_test=SIMDInt32Tests/HSum3Test1
BOOST_AUTO_TEST_CASE( HSum3Test1 )
{
    using Traits = SIMD::Traits<int, 3>;
    auto rmm1 = Traits::Set( 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == 11 );
    BOOST_CHECK( result[ 1 ] == 11 );
    BOOST_CHECK( result[ 2 ] == 11 );
}


// --run_test=SIMDInt32Tests/HSum4Test1
BOOST_AUTO_TEST_CASE( HSum4Test1 )
{
    using Traits = SIMD::Traits<int, 4>;
    auto rmm1 = Traits::Set( 21, 7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    auto result = Traits::ToArray( rmm2 );

    BOOST_CHECK( result[ 0 ] == 32 );
    BOOST_CHECK( result[ 1 ] == 32 );
    BOOST_CHECK( result[ 2 ] == 32 );
    BOOST_CHECK( result[ 3 ] == 32 );
}

// --run_test=SIMDInt32Tests/HSum5Test1
BOOST_AUTO_TEST_CASE( HSum5Test1 )
{
    using Traits = SIMD::Traits<int, 6>;
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


// --run_test=SIMDInt32Tests/HSum6Test1
BOOST_AUTO_TEST_CASE( HSum6Test1 )
{
    using Traits = SIMD::Traits<int, 6>;
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


// --run_test=SIMDInt32Tests/HSum7Test1
BOOST_AUTO_TEST_CASE( HSum7Test1 )
{
    using Traits = SIMD::Traits<int, 7>;
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

// --run_test=SIMDInt32Tests/HSum8Test1
BOOST_AUTO_TEST_CASE( HSum8Test1 )
{
    using Traits = SIMD::Traits<int, 8>;
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


BOOST_AUTO_TEST_SUITE_END( )