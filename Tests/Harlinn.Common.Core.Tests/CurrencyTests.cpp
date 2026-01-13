/*
   Copyright 2024-2026 Espen Harlinn

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

BOOST_FIXTURE_TEST_SUITE( CurrencyTests, LocalFixture )


// --run_test=CurrencyTests/CurrencyConstructorTest
BOOST_AUTO_TEST_CASE( CurrencyConstructorTest )
{
    Currency currency1;
    BOOST_TEST( currency1.Value( ) == 0 );
    Currency currency2(2);
    BOOST_TEST( currency2.Value( ) == 20000 );
}

// --run_test=CurrencyTests/AssignTest
BOOST_AUTO_TEST_CASE( AssignTest )
{
    Currency currency1;
    BOOST_TEST( currency1.Value( ) == 0 );
    Currency currency2( 2 );
    BOOST_TEST( currency2.Value( ) == 20000 );

    currency2 = currency1;
    BOOST_TEST( currency2.Value( ) == 0 );
    currency1 = 1;
    BOOST_TEST( currency1.Value( ) == 10000 );
    currency2 = currency1;
    BOOST_TEST( currency2.Value( ) == 10000 );

    currency2 = 3.0;
    BOOST_TEST( currency2.Value( ) == 30000 );
    currency2 = 4ULL;
    BOOST_TEST( currency2.Value( ) == 40000 );
}

// --run_test=CurrencyTests/AddTest
BOOST_AUTO_TEST_CASE( AddTest )
{
    Currency currency1;
    BOOST_TEST( currency1.Value( ) == 0 );
    currency1++;
    BOOST_TEST( currency1.Value( ) == 10000 );
    currency1 = 0;
    BOOST_TEST( currency1.Value( ) == 0 );
    ++currency1;
    BOOST_TEST( currency1.Value( ) == 10000 );

    Currency currency2( 2 );
    BOOST_TEST( currency2.Value( ) == 20000 );

    Currency currency3 = currency1 + currency2;
    BOOST_TEST( currency3.Value( ) == 30000 );

    currency3 = 1 + currency2;
    BOOST_TEST( currency3.Value( ) == 30000 );

    currency3 = currency1 + 2;
    BOOST_TEST( currency3.Value( ) == 30000 );

    currency3 += currency1;
    BOOST_TEST( currency3.Value( ) == 40000 );

    currency3 += 1;
    BOOST_TEST( currency3.Value( ) == 50000 );

    currency3 += 1.0;
    BOOST_TEST( currency3.Value( ) == 60000 );
}

// --run_test=CurrencyTests/SubtractTest
BOOST_AUTO_TEST_CASE( SubtractTest )
{
    Currency currency1(1);
    BOOST_TEST( currency1.Value( ) == 10000 );
    currency1--;
    BOOST_TEST( currency1.Value( ) == 0 );
    currency1 = 1;
    BOOST_TEST( currency1.Value( ) == 10000 );
    --currency1;
    BOOST_TEST( currency1.Value( ) == 0 );

    currency1 = 1;
    Currency currency2( 2 );
    BOOST_TEST( currency2.Value( ) == 20000 );

    Currency currency3 = currency2 - currency1 ;
    BOOST_TEST( currency3.Value( ) == 10000 );

    currency3 = 1 - currency2;
    BOOST_TEST( currency3.Value( ) == -10000 );

    currency3 = currency1 - 2;
    BOOST_TEST( currency3.Value( ) == -10000 );

    currency3 -= currency1;
    BOOST_TEST( currency3.Value( ) == -20000 );

    currency3 -= 1;
    BOOST_TEST( currency3.Value( ) == -30000 );

    currency3 -= 1.0;
    BOOST_TEST( currency3.Value( ) == -40000 );
}

// --run_test=CurrencyTests/MultiplyTest
BOOST_AUTO_TEST_CASE( MultiplyTest )
{
    Currency currency1( 1 );

    Currency currency2 = 2 * currency1;
    BOOST_TEST( currency2.Value( ) == 20000 );
    currency2 = currency1 * 2;
    BOOST_TEST( currency2.Value( ) == 20000 );

    currency2 = currency1 * 0.5;
    BOOST_TEST( currency2.Value( ) == 5000 );
    currency2 *= 0.5;
    BOOST_TEST( currency2.Value( ) == 2500 );

    currency2 *= 4;
    BOOST_TEST( currency2.Value( ) == 10000 );
}

// --run_test=CurrencyTests/DivisionTest
BOOST_AUTO_TEST_CASE( DivisionTest )
{
    Currency currency1( 1 );

    Currency currency2 = currency1 / 2;
    BOOST_TEST( currency2.Value( ) == 5000 );
    currency2 = currency1 / 0.5;
    BOOST_TEST( currency2.Value( ) == 20000 );

    currency2 /= 0.5;
    BOOST_TEST( currency2.Value( ) == 40000 );

    currency2 /= 4;
    BOOST_TEST( currency2.Value( ) == 10000 );


}



BOOST_AUTO_TEST_SUITE_END( )
