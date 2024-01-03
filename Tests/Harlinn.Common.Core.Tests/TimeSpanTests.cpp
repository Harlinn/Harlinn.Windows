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

BOOST_FIXTURE_TEST_SUITE( TimeSpanTests, LocalFixture )


// --run_test=TimeSpanTests/TimeSpanConstructorTest1
BOOST_AUTO_TEST_CASE( TimeSpanConstructorTest1 )
{
    TimeSpan timeSpan;
    BOOST_CHECK( timeSpan.Ticks( ) == 0 );
}

// --run_test=TimeSpanTests/TimeSpanConstructorTest2
BOOST_AUTO_TEST_CASE( TimeSpanConstructorTest2 )
{
    TimeSpan timeSpan(1LL);
    BOOST_CHECK( timeSpan.Ticks( ) == 1 );
}

// --run_test=TimeSpanTests/TimeSpanConstructorTest3
BOOST_AUTO_TEST_CASE( TimeSpanConstructorTest3 )
{
    TimeSpan timeSpan( 1,1,1 );
    Int64 expected = TimeSpan::TicksPerHour + TimeSpan::TicksPerMinute + TimeSpan::TicksPerSecond;
    BOOST_CHECK( timeSpan.Ticks( ) == expected );
}

// --run_test=TimeSpanTests/TimeSpanConstructorTest4
BOOST_AUTO_TEST_CASE( TimeSpanConstructorTest4 )
{
    TimeSpan timeSpan( 1, 1, 1, 1 );
    Int64 expected = TimeSpan::TicksPerDay + TimeSpan::TicksPerHour + TimeSpan::TicksPerMinute + TimeSpan::TicksPerSecond;
    BOOST_CHECK( timeSpan.Ticks( ) == expected );
}

// --run_test=TimeSpanTests/TimeSpanConstructorTest5
BOOST_AUTO_TEST_CASE( TimeSpanConstructorTest5 )
{
    TimeSpan timeSpan( 1, 1, 1, 1, 1 );
    Int64 expected = TimeSpan::TicksPerDay + TimeSpan::TicksPerHour + TimeSpan::TicksPerMinute + TimeSpan::TicksPerSecond + TimeSpan::TicksPerMillisecond;
    BOOST_CHECK( timeSpan.Ticks( ) == expected );
}

// --run_test=TimeSpanTests/TimeSpanEqualTest1
BOOST_AUTO_TEST_CASE( TimeSpanEqualTest1 )
{
    TimeSpan timeSpan1( 1, 1, 1 );
    TimeSpan timeSpan2( 1, 1, 1 );
    TimeSpan timeSpan3( 3, 3, 3 );
    
    BOOST_CHECK( timeSpan1 == timeSpan2 );
    BOOST_CHECK( (timeSpan1 == timeSpan3) == false );
}

// --run_test=TimeSpanTests/TimeSpanNotEqualTest1
BOOST_AUTO_TEST_CASE( TimeSpanNotEqualTest1 )
{
    TimeSpan timeSpan1( 1, 1, 1 );
    TimeSpan timeSpan2( 1, 1, 1 );
    TimeSpan timeSpan3( 3, 3, 3 );

    BOOST_CHECK( timeSpan1 != timeSpan3 );
    BOOST_CHECK( ( timeSpan1 != timeSpan2 ) == false );
}

// --run_test=TimeSpanTests/TimeSpanLessTest1
BOOST_AUTO_TEST_CASE( TimeSpanLessTest1 )
{
    TimeSpan timeSpan1( 1, 1, 1 );
    TimeSpan timeSpan2( 1, 1, 1 );
    TimeSpan timeSpan3( 3, 3, 3 );

    BOOST_CHECK( timeSpan1 < timeSpan3 );
    BOOST_CHECK( ( timeSpan1 < timeSpan2 ) == false );
}

// --run_test=TimeSpanTests/TimeSpanLessOrEqualTest1
BOOST_AUTO_TEST_CASE( TimeSpanLessOrEqualTest1 )
{
    TimeSpan timeSpan1( 1, 1, 1 );
    TimeSpan timeSpan2( 1, 1, 1 );
    TimeSpan timeSpan3( 3, 3, 3 );

    BOOST_CHECK( timeSpan1 <= timeSpan2 );
    BOOST_CHECK( ( timeSpan3 <= timeSpan1 ) == false );
}

// --run_test=TimeSpanTests/TimeSpanGreaterTest1
BOOST_AUTO_TEST_CASE( TimeSpanGreaterTest1 )
{
    TimeSpan timeSpan1( 1, 1, 1 );
    TimeSpan timeSpan2( 1, 1, 1 );
    TimeSpan timeSpan3( 3, 3, 3 );

    BOOST_CHECK( timeSpan3 > timeSpan1 );
    BOOST_CHECK( ( timeSpan1 > timeSpan2 ) == false );
}

// --run_test=TimeSpanTests/TimeSpanGreaterOrEqualTest1
BOOST_AUTO_TEST_CASE( TimeSpanGreaterOrEqualTest1 )
{
    TimeSpan timeSpan1( 1, 1, 1 );
    TimeSpan timeSpan2( 1, 1, 1 );
    TimeSpan timeSpan3( 3, 3, 3 );

    BOOST_CHECK( timeSpan3 >= timeSpan1 );
    BOOST_CHECK( ( timeSpan1 >= timeSpan3 ) == false );
}

// --run_test=TimeSpanTests/TimeSpanTryParseTest1
BOOST_AUTO_TEST_CASE( TimeSpanTryParseTest1 )
{
    TimeSpan timeSpan;
    bool success = TimeSpan::TryParse( L"", timeSpan );
    BOOST_CHECK( success == false );
}

// --run_test=TimeSpanTests/TimeSpanTryParseTest2
BOOST_AUTO_TEST_CASE( TimeSpanTryParseTest2 )
{
    TimeSpan timeSpan;
    bool success = TimeSpan::TryParse( L"1", timeSpan );
    BOOST_CHECK( success );
    double totalDays = timeSpan.TotalDays( );
    BOOST_CHECK( totalDays == 1.0 );
}

// --run_test=TimeSpanTests/TimeSpanTryParseTest3
BOOST_AUTO_TEST_CASE( TimeSpanTryParseTest3 )
{
    TimeSpan timeSpan;
    bool success = TimeSpan::TryParse( L"90:10:11:12", timeSpan );
    BOOST_CHECK( success );
    auto days = timeSpan.Days( );
    BOOST_CHECK( days == 90 );
    auto hours = timeSpan.Hours( );
    BOOST_CHECK( hours == 10 );
    auto minutes = timeSpan.Minutes( );
    BOOST_CHECK( minutes == 11 );
    auto seconds = timeSpan.Seconds( );
    BOOST_CHECK( seconds == 12 );

}

// --run_test=TimeSpanTests/TimeSpanTryParseTest4
BOOST_AUTO_TEST_CASE( TimeSpanTryParseTest4 )
{
    TimeSpan timeSpan;
    bool success = TimeSpan::TryParse( L"0:0:10", timeSpan );
    BOOST_CHECK( success );
    auto days = timeSpan.Days( );
    BOOST_CHECK( days == 0 );
    auto hours = timeSpan.Hours( );
    BOOST_CHECK( hours == 0 );
    auto minutes = timeSpan.Minutes( );
    BOOST_CHECK( minutes == 10 );
    printf( "Minutes: %d\n", minutes );
    auto seconds = timeSpan.Seconds( );
    BOOST_CHECK( seconds == 0 );

}






BOOST_AUTO_TEST_SUITE_END( )