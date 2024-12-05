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


// --run_test=SIMDDoubleTests/HSum2Test1
BOOST_AUTO_TEST_CASE( HSum2Test1 )
{
    using Traits = SIMD::Traits<double, 2>;
    auto rmm1 = Traits::Set( 2, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    alignas( Traits::AlignAs ) std::array<double, 2> result;
    Traits::Store( result.data( ), rmm2 );

    BOOST_CHECK( result[ 0 ] == 3.0 );
    BOOST_CHECK( result[ 1 ] == 3.0 );
}

// --run_test=SIMDDoubleTests/HSum4Test1
BOOST_AUTO_TEST_CASE( HSum4Test1 )
{
    using Traits = SIMD::Traits<double, 4>;
    auto rmm1 = Traits::Set( 21,7, 3, 1 );
    auto rmm2 = Traits::HSum( rmm1 );
    alignas( Traits::AlignAs ) std::array<double, 4> result;
    Traits::Store( result.data( ), rmm2 );

    BOOST_CHECK( result[ 0 ] == 32.0 );
    //BOOST_CHECK( result[ 1 ] == 3.0 );
}



BOOST_AUTO_TEST_SUITE_END( )