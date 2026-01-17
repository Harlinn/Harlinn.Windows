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

using namespace Harlinn::Common;
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
    bool success = TimeSpan::TryParse( L"90.10:11:12", timeSpan );
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
    BOOST_CHECK( minutes == 0 );
    printf( "Minutes: %d\n", minutes );
    auto seconds = timeSpan.Seconds( );
    BOOST_CHECK( seconds == 10 );

}


// --run_test=TimeSpanTests/TimeSpanTryParseCases
BOOST_AUTO_TEST_CASE( TimeSpanTryParseCases )
{
    struct Case
    {
        const wchar_t* input;
        TimeSpan expected;
    };

    std::vector<Case> cases =
    {
        // "1" -> 1 day
        { L"1", TimeSpan::FromDays( 1 ) },

        // "14" -> 14 days
        { L"14", TimeSpan::FromDays( 14 ) },

        // "1:2:3" -> 1 hour, 2 minutes and 3 seconds
        { L"1:2:3", TimeSpan(0, 1, 2, 3, 0) },

        // "0:0:0.250" -> 250 milliseconds -> 250ms * 10,000 ticks/ms = 2,500,000 ticks
        { L"0:0:0.250", TimeSpan(0,0,0,0,.250) },

        // "10.20:30:40.50" -> 10 days, 20 hours, 30 minutes, 40 seconds and .50 -> 50 with 2 digits -> 50 * 10^(7-2) ticks
        { L"10.20:30:40.50", TimeSpan(10, 20, 30, 40, .50) },

        // "99.23:59:59.9999999" -> 7 fractional digits -> directly ticks = 9,999,999
        { L"99.23:59:59.9999999", TimeSpan(99, 23, 59, 59, .9999999) },

        // "0023:0059:0059.0099" -> hours=23, minutes=59, seconds=59, fraction "0099" -> value 99, digits 4
        { L"0023:0059:0059.0099", TimeSpan( 0, 23, 59, 59, .0099 ) },

        // "23:0:0" -> 23 hours
        { L"23:0:0", TimeSpan(0, 23, 0, 0, 0) },

        // "0:59:0" -> 59 minutes
        { L"0:59:0", TimeSpan(0, 0, 59, 0, 0) },

        // "0:0:59" -> 59 seconds
        { L"0:0:59", TimeSpan(0, 0, 0, 59, 0) },

        // "10:0" -> 10 hours (hh:mm)
        { L"10:0", TimeSpan(0, 10, 0, 0, 0) },

        // "0:10" -> 10 minutes (hh:mm)
        { L"0:10", TimeSpan(0, 0, 10, 0, 0) },

        // "10:20:0" -> 10 hours and 20 minutes
        { L"10:20:0", TimeSpan(0, 10, 20, 0, 0) },

        // "10:20" -> 10 hours and 20 minutes (hh:mm)
        { L"10:20", TimeSpan(0, 10, 20, 0, 0) },

        // "10.20" -> 10 days and 20 hours (days.hours)
        { L"10.20", TimeSpan(10, 20, 0, 0, 0) },

        // "0.12:00" -> 12 hours
        { L"0.12:00", TimeSpan(0, 12, 0, 0, 0) },

        // "3.12:00" -> 3 days and 12 hours
        { L"3.12:00", TimeSpan(3, 12, 0, 0, 0) },

        // "-1" -> -1 day
        { L"-1", -TimeSpan::FromDays( 1 ) },

        // "-14" -> -14 days
        { L"-14", -TimeSpan::FromDays( 14 ) },

        // "-1:2:3" -> -1 hour, 2 minutes and 3 seconds
        { L"-1:2:3", -TimeSpan( 0, 1, 2, 3, 0 ) },

        // "-0:0:0.250" -> -250 milliseconds -> 250ms * 10,000 ticks/ms = 2,500,000 ticks
        { L"-0:0:0.250", -TimeSpan( 0,0,0,0,.250 ) },

        // "-10.20:30:40.50" -> -10 days, 20 hours, 30 minutes, 40 seconds and .50 -> 50 with 2 digits -> 50 * 10^(7-2) ticks
        { L"-10.20:30:40.50", -TimeSpan( 10, 20, 30, 40, .50 ) },

        // "-99.23:59:59.9999999" -> 7 fractional digits -> directly ticks = 9,999,999
        { L"-99.23:59:59.9999999", -TimeSpan( 99, 23, 59, 59, .9999999 ) },

        // "-0023:0059:0059.0099" -> - hours=23, minutes=59, seconds=59, fraction "0099" -> value 99, digits 4
        { L"-0023:0059:0059.0099", -TimeSpan( 0, 23, 59, 59, .0099 ) },

        // "-23:0:0" -> -23 hours
        { L"-23:0:0", -TimeSpan( 0, 23, 0, 0, 0 ) },

        // "-0:59:0" -> -59 minutes
        { L"-0:59:0", -TimeSpan( 0, 0, 59, 0, 0 ) },

        // "-0:0:59" -> -59 seconds
        { L"-0:0:59", -TimeSpan( 0, 0, 0, 59, 0 ) },

        // "-10:0" -> -10 hours (hh:mm)
        { L"-10:0", -TimeSpan( 0, 10, 0, 0, 0 ) },

        // "-0:10" -> -10 minutes (hh:mm)
        { L"-0:10", -TimeSpan( 0, 0, 10, 0, 0 ) },

        // "-10:20:0" -> -10 hours and 20 minutes
        { L"-10:20:0", -TimeSpan( 0, 10, 20, 0, 0 ) },

        // "-10:20" -> -10 hours and 20 minutes (hh:mm)
        { L"-10:20", -TimeSpan( 0, 10, 20, 0, 0 ) },

        // "-10.20" -> -10 days and 20 hours (days.hours)
        { L"-10.20", -TimeSpan( 10, 20, 0, 0, 0 ) },

        // "-0.12:00" -> -12 hours
        { L"-0.12:00", -TimeSpan( 0, 12, 0, 0, 0 ) },

        // "-3.12:00" -> -3 days and 12 hours
        { L"-3.12:00", -TimeSpan( 3, 12, 0, 0, 0 ) }
    };

    for ( const auto& tc : cases )
    {
        TimeSpan ts;
        bool success = TimeSpan::TryParse( tc.input, ts );
        BOOST_TEST( success );

        // compute expected ticks from components
        long long expectedTicks = tc.expected.Ticks( );
        long long ticks = ts.Ticks( );
        long long difference = std::max( expectedTicks, ticks ) - std::min( expectedTicks, ticks );


        bool okTicks = ( ticks == expectedTicks );
        BOOST_TEST( okTicks );
    }
}

BOOST_AUTO_TEST_SUITE_END( )