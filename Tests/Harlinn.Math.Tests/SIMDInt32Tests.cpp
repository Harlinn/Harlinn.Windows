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