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


BOOST_FIXTURE_TEST_SUITE( IntervalTests, LocalFixture )

// --run_test=IntervalTests/IntersectsTest
BOOST_AUTO_TEST_CASE( IntersectsTest )
{
    Interval firstInterval( DateTime( 11LL ), DateTime( 12LL ) );
    Interval secondInterval( DateTime( 12LL ), DateTime( 13LL ) );
    bool intersects1 = firstInterval.Intersects( secondInterval );
    BOOST_CHECK( intersects1 );
    bool intersects2 = secondInterval.Intersects( firstInterval );
    BOOST_CHECK( intersects2 );

    Interval thirdInterval( DateTime( 13LL ), DateTime( 14LL ) );
    bool intersects3 = firstInterval.Intersects( thirdInterval );
    BOOST_CHECK( intersects3 == false );
    bool intersects4 = thirdInterval.Intersects( firstInterval );
    BOOST_CHECK( intersects4 == false );

    Interval fourthInterval( DateTime( 10LL ), DateTime( 13LL ) );
    bool intersects5 = firstInterval.Intersects( fourthInterval );
    BOOST_CHECK( intersects5 );
    bool intersects6 = fourthInterval.Intersects( firstInterval );
    BOOST_CHECK( intersects6 );


}

BOOST_AUTO_TEST_SUITE_END( )