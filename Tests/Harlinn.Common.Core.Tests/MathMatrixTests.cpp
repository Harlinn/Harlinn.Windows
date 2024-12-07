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

BOOST_FIXTURE_TEST_SUITE( MathMatixTests, LocalFixture )

// --run_test=MathMatixTests/ConstexprVector1DTest1
BOOST_AUTO_TEST_CASE( ConstexprVector1DTest1 )
{
    using VectorType = Math::Vector<double, 1>;
    constexpr VectorType v1( 1.0 );
    constexpr VectorType v2( 100.0 );
    constexpr VectorType v3( 10000.0 );
    constexpr VectorType v4( 1000000.0 );
    constexpr auto v5 = v1 + v2;
    constexpr auto v5Size = v5.size( );
    BOOST_CHECK( v5Size == 1 );
    constexpr auto v5Capacity = v5.capacity( );
    BOOST_CHECK( v5Capacity == 2 );
    constexpr auto v5_0 = v5[0];

    BOOST_CHECK( v5_0 == 101.0);
    constexpr auto v6 = v3 * 2.0;
    constexpr auto v6_0 = v6[0];
    BOOST_CHECK( v6_0 == 20000.0 );
    constexpr auto v7 = v3 / 2;
    constexpr auto v7_0 = v7[0];
    BOOST_CHECK( v7_0 == 5000.0 );

    constexpr auto v8 = v4 + 1.0;
    constexpr auto v8_0 = v8[0];
    BOOST_CHECK( v8_0 == 1000001.0 );
    constexpr auto v9 = v4 - 1.0;
    constexpr auto v9_0 = v9[0];
    BOOST_CHECK( v9_0 == 999999.0 );
}

// --run_test=MathMatixTests/ConstexprVector1DTest2
BOOST_AUTO_TEST_CASE( ConstexprVector1DTest2 )
{
    using VectorType = Math::Vector<double, 2>;
    constexpr VectorType v1( 1.0 );
    constexpr VectorType v2( 100.0 );
    constexpr VectorType v3( 10000.0 );
    constexpr VectorType v4( 1000000.0 );
    constexpr auto v5 = v1 + v2;
    constexpr auto v5Size = v5.size( );
    BOOST_CHECK( v5Size == 2 );
    constexpr auto v5Capacity = v5.capacity( );
    BOOST_CHECK( v5Capacity == 2 );

    constexpr auto v5_0 = v5[0];
    BOOST_CHECK( v5_0 == 101.0 );

    constexpr auto v5_1 = v5[1];
    BOOST_CHECK( v5_1 == 101.0 );

    constexpr auto v6 = v3 * 2.0;
    constexpr auto v6_0 = v6[0];
    BOOST_CHECK( v6_0 == 20000.0 );
    constexpr auto v6_1 = v6[1];
    BOOST_CHECK( v6_1 == 20000.0 );

    constexpr auto v7 = v3 / 2;
    constexpr auto v7_0 = v7[0];
    BOOST_CHECK( v7_0 == 5000.0 );

    constexpr auto v7_1 = v7[1];
    BOOST_CHECK( v7_1 == 5000.0 );


    constexpr auto v8 = v4 + 1.0;
    constexpr auto v8_0 = v8[0];
    BOOST_CHECK( v8_0 == 1000001.0 );
    constexpr auto v8_1 = v8[1];
    BOOST_CHECK( v8_1 == 1000001.0 );


    constexpr auto v9 = v4 - 1.0;
    constexpr auto v9_0 = v9[0];
    BOOST_CHECK( v9_0 == 999999.0 );

    constexpr auto v9_1 = v9[1];
    BOOST_CHECK( v9_1 == 999999.0 );

    constexpr auto v10 = v4 + v3 + v2 + v1;
    constexpr auto v10_0 = v10[0];
    BOOST_CHECK( v10_0 == 1010101.0 );

    constexpr auto v11 = v4 - v3 - v2 - v1;
    constexpr auto v11_0 = v11[0];
    BOOST_CHECK( v11_0 == ( 1000000.0 - 10000.0 - 100.0 - 1.0 ) );

}


BOOST_AUTO_TEST_SUITE_END( )