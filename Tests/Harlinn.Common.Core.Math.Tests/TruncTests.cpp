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
using namespace Harlinn::Common::Core::Math;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };


}

BOOST_FIXTURE_TEST_SUITE( TruncTests, LocalFixture )

// --run_test=TruncTests/TruncDoubleTest1
BOOST_AUTO_TEST_CASE( TruncDoubleTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = double;
    Generators::RangeGenerator<FloatT> generator( std::numeric_limits<FloatT>::lowest(), std::numeric_limits<FloatT>::max( ) );

    NumericTest test( "TruncDoubleTest1" );
    auto success = test.Run( generator,
        []( auto x )
        {
            return std::trunc( x );
        },
        []( auto x )
        {
            return Math::FloatingPoint<FloatT>::Trunc( x );
        } );
    BOOST_CHECK( success );
}

// --run_test=TruncTests/TruncFloatTest1
BOOST_AUTO_TEST_CASE( TruncFloatTest1 )
{
    using namespace Test;
    using namespace Test::Generators;
    using FloatT = float;
    Generators::RangeGenerator<FloatT> generator( std::numeric_limits<FloatT>::lowest( ), std::numeric_limits<FloatT>::max( ) );

    NumericTest test( "TruncDoubleTest1" );
    auto success = test.Run( generator,
        []( auto x )
        {
            return std::trunc( x );
        },
        []( auto x )
        {
            return Math::FloatingPoint<FloatT>::Trunc( x );
        } );
    BOOST_CHECK( success );
}


BOOST_AUTO_TEST_SUITE_END( )
