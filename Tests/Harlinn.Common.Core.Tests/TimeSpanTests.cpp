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


// Default ("c") format: "[-][d.]hh:mm:ss[.fffffff]"
BOOST_AUTO_TEST_CASE( ToString_Default_Format_StdString )
{
    // 01:02:03.1230000
    TimeSpan ts( 0, 1, 2, 3, 123 ); // hours, minutes, seconds, milliseconds
    auto s = ts.ToString<std::string>( nullptr, 0 );
    const std::string expected = "01:02:03.1230000";
    bool ok = ( s == expected );
    BOOST_TEST( ok );
}

BOOST_AUTO_TEST_CASE( ToString_Default_Format_WideString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<std::wstring>( nullptr, 0 );
    const std::wstring expected = L"01:02:03.1230000";
    bool ok = ( s == expected );
    BOOST_TEST( ok );
}

BOOST_AUTO_TEST_CASE( ToString_Default_Format_AnsiString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<AnsiString>( nullptr, 0 );
    const AnsiString expected( "01:02:03.1230000" );
    bool ok = ( s == expected );
    BOOST_TEST( ok );
}

BOOST_AUTO_TEST_CASE( ToString_Default_Format_WideStringType )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<WideString>( nullptr, 0 );
    const WideString expected( L"01:02:03.1230000" );
    bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Standard format 'g' trims trailing fractional zeros -> "01:02:03.123"
BOOST_AUTO_TEST_CASE( ToString_Standard_g_TrimsFractionalZeros )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<std::string>( "g", 1 );
    const std::string expected = "01:02:03.123";
    bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Standard format 'G' ensures 7 fractional digits when fraction is zero
BOOST_AUTO_TEST_CASE( ToString_Standard_G_ZeroFraction_AppendsZeros )
{
    TimeSpan ts( 0, 1, 2, 3, 0 ); // no fractional milliseconds
    auto s = ts.ToString<std::string>( "G", 1 );
    const std::string expected = "01:02:03.0000000";
    bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Custom format: "hh:mm:ss" (no fractional part)
BOOST_AUTO_TEST_CASE( ToString_Custom_hhmmss )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<std::string>( "hh:mm:ss", 8 );
    const std::string expected = "01:02:03";
    bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Ensure negative values produce leading '-' when format does not include sign explicitly
BOOST_AUTO_TEST_CASE( ToString_Negative_Default )
{
    TimeSpan ts = -TimeSpan( 0, 1, 2, 3, 5 ); // small fraction
    auto s = ts.ToString<std::string>( nullptr, 0 );
    // compute expected using existing positive formatting and prefix '-'
    TimeSpan pos( 0, 1, 2, 3, 5 );
    auto posStr = pos.ToString<std::string>( nullptr, 0 );
    const std::string expected = "-" + posStr;
    bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Default ("c") format: "[-][d.]hh:mm:ss[.fffffff]"
// std::string
BOOST_AUTO_TEST_CASE( ToString_Default_StdString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 ); // 01:02:03.1230000
    auto s = ts.ToString<std::string>( nullptr );
    const std::string expected = "01:02:03.1230000";
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// std::wstring
BOOST_AUTO_TEST_CASE( ToString_Default_StdWString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<std::wstring>( nullptr );
    const std::wstring expected = L"01:02:03.1230000";
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// AnsiString
BOOST_AUTO_TEST_CASE( ToString_Default_AnsiString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<AnsiString>( nullptr );
    const AnsiString expected( "01:02:03.1230000" );
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// WideString
BOOST_AUTO_TEST_CASE( ToString_Default_WideString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<WideString>( nullptr );
    const WideString expected( L"01:02:03.1230000" );
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Standard format 'g' -> trimmed fractional part
BOOST_AUTO_TEST_CASE( ToString_Standard_g_StdString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<std::string>( "g" );
    const std::string expected = "01:02:03.123";
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Standard format 'g' for wide string
BOOST_AUTO_TEST_CASE( ToString_Standard_g_StdWString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<std::wstring>( L"g" );
    const std::wstring expected = L"01:02:03.123";
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Standard format 'G' ensures 7 fractional digits even when zero
BOOST_AUTO_TEST_CASE( ToString_Standard_G_ZeroFraction_StdString )
{
    TimeSpan ts( 0, 1, 2, 3, 0 ); // no fractional milliseconds
    auto s = ts.ToString<std::string>( "G" );
    const std::string expected = "01:02:03.0000000";
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Custom format "hh:mm:ss" (no fraction) - std::string
BOOST_AUTO_TEST_CASE( ToString_Custom_hhmmss_StdString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<std::string>( "hh:mm:ss" );
    const std::string expected = "01:02:03";
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Custom format "hh:mm:ss" - WideString
BOOST_AUTO_TEST_CASE( ToString_Custom_hhmmss_WideString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 );
    auto s = ts.ToString<WideString>( L"hh:mm:ss" );
    const WideString expected( L"01:02:03" );
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Fractional custom "ss.fff" -> first 3 fractional digits (std::string)
BOOST_AUTO_TEST_CASE( ToString_Fraction_ss_dot_fff_StdString )
{
    TimeSpan ts( 0, 1, 2, 3, 123 ); // fraction -> "1230000" -> "123"
    auto s = ts.ToString<std::string>( "ss.fff" );
    const std::string expected = "03.123";
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

// Fractional custom "ss.FFF" trims trailing zeros (std::string)
BOOST_AUTO_TEST_CASE( ToString_Fraction_ss_dot_FFF_StdString )
{
    // 120 ms => fraction7 "1200000" -> FFF trimmed -> "12"
    TimeSpan ts( 0, 1, 2, 3, 120 );
    auto s = ts.ToString<std::string>( "ss.FFF" );
    const std::string expected = "03.12";
    const bool ok = ( s == expected );
    BOOST_TEST( ok );
}

static TimeSpan MakeSample( )
{
    // 01:02:03.123 -> hours=1, minutes=2, seconds=3, milliseconds=123
    return TimeSpan( 0, 1, 2, 3, 123 );
}

BOOST_AUTO_TEST_CASE( ToString_DefaultAndStandardFormats_AllStringTypes )
{
    TimeSpan ts = MakeSample( );

    // default ("c")
    auto sStd = ts.ToString<std::string>( nullptr );
    bool ok1 = ( sStd == "01:02:03.1230000" );
    BOOST_TEST( ok1 );

    auto sW = ts.ToString<std::wstring>( nullptr );
    bool ok2 = ( sW == L"01:02:03.1230000" );
    BOOST_TEST( ok2 );

    auto sAnsi = ts.ToString<AnsiString>( nullptr );
    bool ok3 = ( sAnsi == AnsiString( "01:02:03.1230000" ) );
    BOOST_TEST( ok3 );

    auto sWide = ts.ToString<WideString>( nullptr );
    bool ok4 = ( sWide == WideString( L"01:02:03.1230000" ) );
    BOOST_TEST( ok4 );

    // standard 'g' -> trimmed fraction
    auto gStd = ts.ToString<std::string>( "g" );
    bool ok5 = ( gStd == "01:02:03.123" );
    BOOST_TEST( ok5 );

    auto gW = ts.ToString<std::wstring>( L"g" );
    bool ok6 = ( gW == L"01:02:03.123" );
    BOOST_TEST( ok6 );

    // standard 'G' -> 7 digits (when fraction non-zero same as 'c')
    auto GStd = ts.ToString<std::string>( "G" );
    bool ok7 = ( GStd == "01:02:03.1230000" );
    BOOST_TEST( ok7 );
}

BOOST_AUTO_TEST_CASE( ToString_CustomFormats_BasicTokens )
{
    TimeSpan ts = MakeSample( );

    // "hh:mm:ss"
    auto hhmmss = ts.ToString<std::string>( "hh:mm:ss" );
    bool ok1 = ( hhmmss == "01:02:03" );
    BOOST_TEST( ok1 );

    // "ss.fff"
    auto ssfff = ts.ToString<std::string>( "ss.fff" );
    bool ok2 = ( ssfff == "03.123" );
    BOOST_TEST( ok2 );

    // "ss.FFF" with trailing-zero trimming: use a value with trailing zero in fraction
    TimeSpan ts2( 0, 1, 2, 3, 120 ); // .120 -> fraction7 = "1200000" -> FFF -> "12"
    auto ssFFF = ts2.ToString<std::string>( "ss.FFF" );
    bool ok3 = ( ssFFF == "03.12" );
    BOOST_TEST( ok3 );
}

// FormatT tests for std::wstring target (various FormatT types)
BOOST_AUTO_TEST_CASE( ToString_FormatT_WString_TargetStdWstring )
{
    TimeSpan ts = MakeSample( );

    // std::wstring_view
    std::wstring_view sv = L"g";
    auto r1 = ts.ToString<std::wstring>( sv );
    bool ok1 = ( r1 == L"01:02:03.123" );
    BOOST_TEST( ok1 );

    // std::vector<wchar_t>
    std::vector<wchar_t> vec( { L'h', L'h', L':', L'm', L'm', L':', L's', L's' } ); // "hh:mm:ss"
    auto r2 = ts.ToString<std::wstring>( vec );
    bool ok2 = ( r2 == L"01:02:03" );
    BOOST_TEST( ok2 );

    // std::span<wchar_t,N>
    static wchar_t spanBuf[ ] = { L's', L's', L'.', L'f', L'f', L'f' }; // "ss.fff"
    std::span<wchar_t, std::extent_v<decltype( spanBuf )>> sp( spanBuf );
    auto r3 = ts.ToString<std::wstring>( sp );
    bool ok3 = ( r3 == L"03.123" );
    BOOST_TEST( ok3 );

    // WideString (repository type) as format container
    WideString wf( L"G" );
    auto r4 = ts.ToString<std::wstring>( wf );
    bool ok4 = ( r4 == L"01:02:03.1230000" );
    BOOST_TEST( ok4 );
}

// FormatT tests for WideString target (various FormatT types)
BOOST_AUTO_TEST_CASE( ToString_FormatT_WideString_TargetWideString )
{
    TimeSpan ts = MakeSample( );

    // std::wstring_view -> WideString
    std::wstring_view sv = L"g";
    auto r1 = ts.ToString<WideString>( sv );
    bool ok1 = ( r1 == WideString( L"01:02:03.123" ) );
    BOOST_TEST( ok1 );

    // std::vector<wchar_t>
    std::vector<wchar_t> vec( { L's', L's', L':', L'f', L'f', L'f' } ); // "ss:fff" (typo intentionally test literal handling -> will be output literal)
    // adjust to valid: "ss.fff"
    vec = { L's', L's', L'.', L'f', L'f', L'f' };
    auto r2 = ts.ToString<WideString>( vec );
    bool ok2 = ( r2 == WideString( L"03.123" ) );
    BOOST_TEST( ok2 );

    // std::span<wchar_t,N>
    static wchar_t spanBuf[ ] = { L'h', L'h', L':', L'm', L'm', L':', L's', L's' }; // "hh:mm:ss"
    std::span<wchar_t, std::extent_v<decltype( spanBuf )>> sp( spanBuf );
    auto r3 = ts.ToString<WideString>( sp );
    bool ok3 = ( r3 == WideString( L"01:02:03" ) );
    BOOST_TEST( ok3 );

    // WideString format container
    WideString wf( L"ss.FFF" );
    TimeSpan ts2( 0, 1, 2, 3, 120 );
    auto r4 = ts2.ToString<WideString>( wf );
    bool ok4 = ( r4 == WideString( L"03.12" ) );
    BOOST_TEST( ok4 );
}

// FormatT tests for std::string target (various FormatT types)
BOOST_AUTO_TEST_CASE( ToString_FormatT_String_TargetStdString )
{
    TimeSpan ts = MakeSample( );

    // std::string_view
    std::string_view sv = "g";
    auto r1 = ts.ToString<std::string>( sv );
    bool ok1 = ( r1 == "01:02:03.123" );
    BOOST_TEST( ok1 );

    // std::vector<char>
    std::vector<char> vec( { 'h','h',':','m','m',':','s','s' } ); // "hh:mm:ss"
    auto r2 = ts.ToString<std::string>( vec );
    bool ok2 = ( r2 == "01:02:03" );
    BOOST_TEST( ok2 );

    // std::span<char,N>
    static char spanBuf[ ] = { 's','s','.','f','f','f' }; // "ss.fff"
    std::span<char, std::extent_v<decltype( spanBuf )>> sp( spanBuf );
    auto r3 = ts.ToString<std::string>( sp );
    bool ok3 = ( r3 == "03.123" );
    BOOST_TEST( ok3 );

    // AnsiString as format container (AnsiString value_type == char)
    AnsiString af( "ss.FFF" );
    TimeSpan ts2( 0, 1, 2, 3, 120 );
    auto r4 = ts2.ToString<std::string>( af );
    bool ok4 = ( r4 == "03.12" );
    BOOST_TEST( ok4 );
}

// FormatT tests for AnsiString target (various FormatT types)
BOOST_AUTO_TEST_CASE( ToString_FormatT_AnsiString_TargetAnsiString )
{
    TimeSpan ts = MakeSample( );

    // std::string_view -> AnsiString
    std::string_view sv = "g";
    auto r1 = ts.ToString<AnsiString>( sv );
    bool ok1 = ( r1 == AnsiString( "01:02:03.123" ) );
    BOOST_TEST( ok1 );

    // std::vector<char>
    std::vector<char> vec( { 's','s','.','f','f','f' } );
    auto r2 = ts.ToString<AnsiString>( vec );
    bool ok2 = ( r2 == AnsiString( "03.123" ) );
    BOOST_TEST( ok2 );

    // std::span<char,N>
    static char spanBuf[ ] = { 'h','h',':','m','m',':','s','s' };
    std::span<char, std::extent_v<decltype( spanBuf )>> sp( spanBuf );
    auto r3 = ts.ToString<AnsiString>( sp );
    bool ok3 = ( r3 == AnsiString( "01:02:03" ) );
    BOOST_TEST( ok3 );

    // AnsiString format container
    AnsiString af( "G" );
    auto r4 = ts.ToString<AnsiString>( af );
    bool ok4 = ( r4 == AnsiString( "01:02:03.1230000" ) );
    BOOST_TEST( ok4 );
}

// --run_test=TimeToTicksTests/TimeToTicks_Zero
BOOST_AUTO_TEST_CASE( TimeToTicks_Zero )
{
    const long long ticks = TimeSpan::TimeToTicks( 0, 0, 0, 0, 0 );
    const bool ok = ( ticks == 0LL );
    BOOST_TEST( ok );
}

// --run_test=TimeToTicksTests/TimeToTicks_SimpleComponents
BOOST_AUTO_TEST_CASE( TimeToTicks_SimpleComponents )
{
    const int days = 1;
    const int hours = 2;
    const int minutes = 3;
    const int seconds = 4;
    const int milliseconds = 500;

    const long long expected =
        static_cast< long long >( days ) * TimeSpan::TicksPerDay +
        static_cast< long long >( hours ) * TimeSpan::TicksPerHour +
        static_cast< long long >( minutes ) * TimeSpan::TicksPerMinute +
        static_cast< long long >( seconds ) * TimeSpan::TicksPerSecond +
        static_cast< long long >( milliseconds ) * TimeSpan::TicksPerMillisecond;

    const long long ticks = TimeSpan::TimeToTicks( days, hours, minutes, seconds, milliseconds );
    const bool ok = ( ticks == expected );
    BOOST_TEST( ok );
}

// --run_test=TimeToTicksTests/TimeToTicks_NegativeDays
BOOST_AUTO_TEST_CASE( TimeToTicks_NegativeDays )
{
    const int days = -1;
    const long long expected = static_cast< long long >( days ) * TimeSpan::TicksPerDay;
    const long long ticks = TimeSpan::TimeToTicks( days, 0, 0, 0, 0 );
    const bool ok = ( ticks == expected );
    BOOST_TEST( ok );
}

// --run_test=TimeToTicksTests/TimeToTicks_ConstructorsConsistency
BOOST_AUTO_TEST_CASE( TimeToTicks_ConstructorsConsistency )
{
    // Create with constructor that delegates to TimeToTicks and compare
    const int days = 3;
    const int hours = 4;
    const int minutes = 5;
    const int seconds = 6;
    const int milliseconds = 789;

    TimeSpan tsConstructed( days, hours, minutes, seconds, milliseconds );
    const long long ticksFromCtor = tsConstructed.Ticks( );

    const long long ticksFromFunc = TimeSpan::TimeToTicks( days, hours, minutes, seconds, milliseconds );

    const bool ok = ( ticksFromCtor == ticksFromFunc );
    BOOST_TEST( ok );
}

// --run_test=TimeToTicksTests/TimeToTicks_BoundarySmallValues
BOOST_AUTO_TEST_CASE( TimeToTicks_BoundarySmallValues )
{
    // small mixed values
    const long long expected =
        2LL * TimeSpan::TicksPerHour + 30LL * TimeSpan::TicksPerMinute + 7LL * TimeSpan::TicksPerSecond + 1LL * TimeSpan::TicksPerMillisecond;

    const long long ticks = TimeSpan::TimeToTicks( 0, 2, 30, 7, 1 );
    const bool ok = ( ticks == expected );
    BOOST_TEST( ok );
}

// Basic fractional seconds: 1 second + 0.5s -> 1.5s (ticks)
BOOST_AUTO_TEST_CASE( TimeToTicks_FractionalSeconds_Basic )
{
    const int days = 0;
    const int hours = 0;
    const int minutes = 0;
    const int seconds = 1;
    const double fraction = 0.5; // 0.5 seconds

    const long long ticksFromFunc = TimeSpan::TimeToTicks( days, hours, minutes, seconds, fraction );
    TimeSpan ts( days, hours, minutes, seconds, fraction );
    const long long ticksFromCtor = ts.Ticks( );

    const bool ok = ( ticksFromFunc == ticksFromCtor );
    BOOST_TEST( ok );
}

// Fraction with 7 digits: 0.9999999 seconds -> 9,999,999 ticks
BOOST_AUTO_TEST_CASE( TimeToTicks_FractionalSeconds_MaxPrecision )
{
    const long long expectedFractionTicks = 9999999LL; // 7 digits -> ticks
    const long long ticks = TimeSpan::TimeToTicks( 0, 0, 0, 0, 0.9999999 );
    // Should equal fraction ticks (no whole seconds)
    const bool ok = ( ticks == expectedFractionTicks );
    BOOST_TEST( ok );
}

// Negative fractional seconds produce negative tick counts
BOOST_AUTO_TEST_CASE( TimeToTicks_NegativeFraction )
{
    const long long ticksFromFunc = TimeSpan::TimeToTicks( 0, 0, 0, 0, -0.5 );
    TimeSpan ts( 0, 0, 0, 0, -0.5 );
    const long long ticksFromCtor = ts.Ticks( );
    const bool ok = ( ticksFromFunc == ticksFromCtor );
    BOOST_TEST( ok );
}

// Mixed components with fraction: days/hours/minutes/seconds + fractional
BOOST_AUTO_TEST_CASE( TimeToTicks_MixedComponents )
{
    const int days = 1;
    const int hours = 2;
    const int minutes = 3;
    const int seconds = 4;
    const double fraction = 0.25; // 250 ms

    const long long ticksFromFunc = TimeSpan::TimeToTicks( days, hours, minutes, seconds, fraction );
    TimeSpan ts( days, hours, minutes, seconds, fraction );
    const long long ticksFromCtor = ts.Ticks( );

    const bool ok = ( ticksFromFunc == ticksFromCtor );
    BOOST_TEST( ok );
}

// Passing NaN for fraction should result in an exception (argument error).
BOOST_AUTO_TEST_CASE( TimeToTicks_Fraction_NaN_Throws )
{
    const double nan = std::numeric_limits<double>::quiet_NaN( );
    // The implementation documents that NaN is invalid; expect some exception derived from std::exception.
    BOOST_CHECK_THROW( TimeSpan::TimeToTicks( 0, 0, 0, 0, nan ), std::exception );
}

// Milliseconds -> ticks (integral duration)
BOOST_AUTO_TEST_CASE( DurationToTicks_Milliseconds )
{
    using namespace std::chrono;
    const milliseconds ms{ 1500 }; // 1.5s
    const long long ticks = TimeSpan::DurationToTicks( ms );
    const long long expected = static_cast< long long >( ms.count( ) ) * TimeSpan::TicksPerMillisecond;
    BOOST_TEST( ticks == expected );
}

// Seconds as double -> truncated to integer tick count
BOOST_AUTO_TEST_CASE( DurationToTicks_Seconds_Double )
{
    using namespace std::chrono;
    const duration<double> sec{ 1.5 }; // 1.5s
    const long long ticks = TimeSpan::DurationToTicks( sec );
    const long long expected = static_cast< long long >( 1.5 * static_cast< double >( TimeSpan::TicksPerSecond ) );
    BOOST_TEST( ticks == expected );

    // Also validate constructor that delegates to DurationToTicks
    TimeSpan ts( sec );
    BOOST_TEST( ts.Ticks( ) == ticks );
}

// Nanoseconds -> ticks (100 ns units), exact and truncated cases
BOOST_AUTO_TEST_CASE( DurationToTicks_Nanoseconds_ExactAndTruncate )
{
    using namespace std::chrono;
    const nanoseconds ns100{ 100 }; // exactly 1 tick
    const long long ticks100 = TimeSpan::DurationToTicks( ns100 );
    BOOST_TEST( ticks100 == 1LL );

    const nanoseconds ns50{ 50 }; // 50 ns -> 0 ticks (truncated)
    const long long ticks50 = TimeSpan::DurationToTicks( ns50 );
    BOOST_TEST( ticks50 == 0LL );
}

// Microseconds -> ticks (1 us == 10 ticks)
BOOST_AUTO_TEST_CASE( DurationToTicks_Microseconds )
{
    using namespace std::chrono;
    const microseconds us1{ 1 }; // 1 us -> 10 ticks
    const long long ticks = TimeSpan::DurationToTicks( us1 );
    BOOST_TEST( ticks == 10LL );
}

// Hours -> ticks
BOOST_AUTO_TEST_CASE( DurationToTicks_Hours )
{
    using namespace std::chrono;
    const hours h1{ 1 };
    const long long ticks = TimeSpan::DurationToTicks( h1 );
    BOOST_TEST( ticks == TimeSpan::TicksPerHour );
}

// Negative fractional seconds -> negative ticks (truncation toward zero)
BOOST_AUTO_TEST_CASE( DurationToTicks_NegativeFractional )
{
    using namespace std::chrono;
    const duration<double> sec{ -1.5 }; // -1.5s
    const long long ticks = TimeSpan::DurationToTicks( sec );
    const long long expected = static_cast< long long >( -1.5 * static_cast< double >( TimeSpan::TicksPerSecond ) );
    BOOST_TEST( ticks == expected );

    TimeSpan ts( sec );
    BOOST_TEST( ts.Ticks( ) == ticks );
}

// Very small fractional duration that truncates to zero
BOOST_AUTO_TEST_CASE( DurationToTicks_TinyFraction_TruncatesToZero )
{
    using namespace std::chrono;
    const duration<double> tiny{ 5e-8 }; // 50 ns -> truncates to 0 ticks
    const long long ticks = TimeSpan::DurationToTicks( tiny );
    BOOST_TEST( ticks == 0LL );
}


// Milliseconds -> ticks -> back to milliseconds (integral)
BOOST_AUTO_TEST_CASE( TicksToDuration_Milliseconds )
{
    using namespace std::chrono;
    const long long millisCount = 1500LL; // 1.5 seconds
    const long long ticks = millisCount * TimeSpan::TicksPerMillisecond;
    auto dur = TimeSpan::TicksToDuration<milliseconds>( ticks );
    const bool ok = ( dur.count( ) == millisCount );
    BOOST_TEST( ok );
}

// Seconds -> ticks -> back to double seconds (fractional)
BOOST_AUTO_TEST_CASE( TicksToDuration_Seconds_Double )
{
    using namespace std::chrono;
    // 1.5 seconds expressed in integer ticks
    const long long ticks = TimeSpan::TicksPerSecond + ( TimeSpan::TicksPerSecond / 2 );
    auto d = TimeSpan::TicksToDuration<duration<double>>( ticks );
    // Allow tiny tolerance for floating conversion
    const bool ok = ( std::abs( d.count( ) - 1.5 ) < 1e-12 );
    BOOST_TEST( ok );
}

// Nanoseconds: 1 tick == 100 ns
BOOST_AUTO_TEST_CASE( TicksToDuration_Nanoseconds )
{
    using namespace std::chrono;
    const long long ticks = 1LL;
    auto ns = TimeSpan::TicksToDuration<nanoseconds>( ticks );
    const bool ok = ( ns.count( ) == 100LL ); // 1 tick == 100 ns
    BOOST_TEST( ok );

    // multiple ticks -> integer result
    const long long ticks10 = 10LL; // 10 ticks == 1000 ns
    auto ns10 = TimeSpan::TicksToDuration<nanoseconds>( ticks10 );
    const bool ok2 = ( ns10.count( ) == 1000LL );
    BOOST_TEST( ok2 );
}

// Microseconds: 10 ticks == 1 microsecond
BOOST_AUTO_TEST_CASE( TicksToDuration_Microseconds )
{
    using namespace std::chrono;
    const long long ticks = 10LL;
    auto us = TimeSpan::TicksToDuration<microseconds>( ticks );
    const bool ok = ( us.count( ) == 1LL );
    BOOST_TEST( ok );

    // truncation case: 1 tick (100 ns) -> 0 microseconds
    auto us0 = TimeSpan::TicksToDuration<microseconds>( 1LL );
    const bool ok2 = ( us0.count( ) == 0LL );
    BOOST_TEST( ok2 );
}

// Hours conversion (large integral unit)
BOOST_AUTO_TEST_CASE( TicksToDuration_Hours )
{
    using namespace std::chrono;
    const long long ticks = 2LL * TimeSpan::TicksPerHour;
    auto h = TimeSpan::TicksToDuration<hours>( ticks );
    const bool ok = ( h.count( ) == 2LL );
    BOOST_TEST( ok );
}

// Negative ticks -> negative duration (double)
BOOST_AUTO_TEST_CASE( TicksToDuration_NegativeFractional )
{
    using namespace std::chrono;
    const long long ticks = -( TimeSpan::TicksPerSecond + TimeSpan::TicksPerSecond / 2 ); // -1.5s
    auto d = TimeSpan::TicksToDuration<duration<double>>( ticks );
    const bool ok = ( std::abs( d.count( ) + 1.5 ) < 1e-12 );
    BOOST_TEST( ok );
}

// Round-trip sanity: Duration -> ticks -> TicksToDuration returns original integral duration (where representable)
BOOST_AUTO_TEST_CASE( TicksToDuration_RoundTrip_IntegralDurations )
{
    using namespace std::chrono;
    // test multiple integral duration types
    const long long msCount = 12345LL;
    const long long ticks = msCount * TimeSpan::TicksPerMillisecond;
    auto backMs = TimeSpan::TicksToDuration<milliseconds>( ticks );
    const bool ok1 = ( backMs.count( ) == msCount );
    BOOST_TEST( ok1 );

    auto backS = TimeSpan::TicksToDuration<seconds>( ticks );
    const bool ok2 = ( backS.count( ) == static_cast< long long >( msCount / 1000 ) );
    BOOST_TEST( ok2 );
}

BOOST_AUTO_TEST_SUITE_END( )