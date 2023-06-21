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

BOOST_FIXTURE_TEST_SUITE( DateTimeTests, LocalFixture )



// --run_test=DateTimeTests/DateTimeConstructorTest1
BOOST_AUTO_TEST_CASE( DateTimeConstructorTest1 )
{
    DateTime dateTime;
    BOOST_CHECK( dateTime.Ticks( ) == 0 );
}

// --run_test=DateTimeTests/DateTimeConstructorTest2
BOOST_AUTO_TEST_CASE( DateTimeConstructorTest2 )
{
    DateTime dateTime(2020,1,1);
    BOOST_CHECK( dateTime.Ticks( ) == 637134336000000000 );
}

// --run_test=DateTimeTests/DateTimeConstructorTest2
BOOST_AUTO_TEST_CASE( DateTimeConstructorTest3 )
{
    DateTime dateTime( 2020, 1, 1, 12, 1, 1 );
    BOOST_CHECK( dateTime.Ticks( ) == 637134768610000000 );
}

// --run_test=DateTimeTests/DateTimeToLocalAndBackTest1
BOOST_AUTO_TEST_CASE( DateTimeToLocalAndBackTest1 )
{
    DateTime dateTime( 2020, 1, 1, 12, 1, 1 );
    auto localDateTime = dateTime.ToLocalTime( );
    auto utcDateTime = localDateTime.ToUniversalTime( );

    BOOST_CHECK( dateTime == utcDateTime );
}

// --run_test=DateTimeTests/DateTimeToUtcAndBackTest1
BOOST_AUTO_TEST_CASE( DateTimeToUtcAndBackTest1 )
{
    DateTime dateTime( 2020, 1, 1, 12, 1, 1 );
    auto utcDateTime = dateTime.ToUniversalTime( );
    auto localDateTime = utcDateTime.ToLocalTime( );

    BOOST_CHECK( dateTime == localDateTime );
}

// --run_test=DateTimeTests/DateTimeEqualTest1
BOOST_AUTO_TEST_CASE( DateTimeEqualTest1 )
{
    DateTime dateTime1( 2020, 1, 1 );
    DateTime dateTime2( 2020, 1, 1 );
    DateTime dateTime3( 2020, 2, 1 );

    BOOST_CHECK( dateTime1 == dateTime2 );
    BOOST_CHECK( (dateTime1 == dateTime3) == false );
}

// --run_test=DateTimeTests/DateTimeNotEqualTest1
BOOST_AUTO_TEST_CASE( DateTimeNotEqualTest1 )
{
    DateTime dateTime1( 2020, 1, 1 );
    DateTime dateTime2( 2020, 1, 1 );
    DateTime dateTime3( 2020, 2, 1 );

    BOOST_CHECK( dateTime1 != dateTime3 );
    BOOST_CHECK( ( dateTime1 != dateTime2 ) == false );
}

// --run_test=DateTimeTests/DateTimeLessTest1
BOOST_AUTO_TEST_CASE( DateTimeLessTest1 )
{
    DateTime dateTime1( 2020, 1, 1 );
    DateTime dateTime2( 2020, 1, 1 );
    DateTime dateTime3( 2020, 2, 1 );

    BOOST_CHECK( dateTime1 < dateTime3 );
    BOOST_CHECK( ( dateTime1 < dateTime2 ) == false );
}

// --run_test=DateTimeTests/DateTimeLessOrEqualTest1
BOOST_AUTO_TEST_CASE( DateTimeLessOrEqualTest1 )
{
    DateTime dateTime1( 2020, 1, 1 );
    DateTime dateTime2( 2020, 1, 1 );
    DateTime dateTime3( 2020, 2, 1 );

    BOOST_CHECK( dateTime1 <= dateTime3 );
    BOOST_CHECK( dateTime1 <= dateTime2 );
    BOOST_CHECK( ( dateTime3 <= dateTime2 ) == false );
}

// --run_test=DateTimeTests/DateTimeGreaterTest1
BOOST_AUTO_TEST_CASE( DateTimeGreaterTest1 )
{
    DateTime dateTime1( 2020, 1, 1 );
    DateTime dateTime2( 2020, 1, 1 );
    DateTime dateTime3( 2020, 2, 1 );

    BOOST_CHECK( dateTime3 > dateTime1 );
    BOOST_CHECK( ( dateTime2 > dateTime1 ) == false );
}

// --run_test=DateTimeTests/DateTimeGreaterOrEqualTest1
BOOST_AUTO_TEST_CASE( DateTimeGreaterOrEqualTest1 )
{
    DateTime dateTime1( 2020, 1, 1 );
    DateTime dateTime2( 2020, 1, 1 );
    DateTime dateTime3( 2020, 2, 1 );

    BOOST_CHECK( dateTime3 >= dateTime1 );
    BOOST_CHECK( dateTime2 >= dateTime1 );
    BOOST_CHECK( ( dateTime2 >= dateTime3 ) == false );
}

// --run_test=DateTimeTests/DateTimeAddTimespanTest1
BOOST_AUTO_TEST_CASE( DateTimeAddTimespanTest1 )
{
    DateTime dateTime( 2020, 1, 1 );
    DateTime dateTimeExpected( 2020, 1, 2 );
    auto timespan = TimeSpan::FromDays( 1 );
    dateTime += timespan;

    BOOST_CHECK( dateTime == dateTimeExpected );
}

// --run_test=DateTimeTests/DateTimeSubtractTimespanTest1
BOOST_AUTO_TEST_CASE( DateTimeSubtractTimespanTest1 )
{
    DateTime dateTime( 2020, 1, 2 );
    DateTime dateTimeExpected( 2020, 1, 1 );
    auto timespan = TimeSpan::FromDays( 1 );
    dateTime -= timespan;

    BOOST_CHECK( dateTime == dateTimeExpected );
}

// --run_test=DateTimeTests/DateTimeSubtractDateTimeTest1
BOOST_AUTO_TEST_CASE( DateTimeSubtractDateTimeTest1 )
{
    DateTime dateTime1( 2020, 1, 1 );
    DateTime dateTime2( 2020, 1, 2 );
    auto timespanExpected = TimeSpan::FromDays( 1 );
    auto timespan = dateTime2 - dateTime1;

    BOOST_CHECK( timespan == timespanExpected );
}


// --run_test=DateTimeTests/DateTimeYearTest1
BOOST_AUTO_TEST_CASE( DateTimeYearTest1 )
{
    DateTime dateTime( 2020, 1, 2 );

    BOOST_CHECK( dateTime.Year() == 2020 );
}

// --run_test=DateTimeTests/DateTimeMonthTest1
BOOST_AUTO_TEST_CASE( DateTimeMonthTest1 )
{
    DateTime dateTime( 2020, 1, 2 );

    BOOST_CHECK( dateTime.Month( ) == 1 );
}

// --run_test=DateTimeTests/DateTimeDayTest1
BOOST_AUTO_TEST_CASE( DateTimeDayTest1 )
{
    DateTime dateTime( 2020, 1, 2 );

    BOOST_CHECK( dateTime.Day( ) == 2 );
}

// --run_test=DateTimeTests/DateTimeHourTest1
BOOST_AUTO_TEST_CASE( DateTimeHourTest1 )
{
    DateTime dateTime( 2020, 1, 2, 12 ,30, 45, 500 );

    BOOST_CHECK( dateTime.Hour( ) == 12 );
}

// --run_test=DateTimeTests/DateTimeMinuteTest1
BOOST_AUTO_TEST_CASE( DateTimeMinuteTest1 )
{
    DateTime dateTime( 2020, 1, 2, 12, 30, 45, 500 );

    BOOST_CHECK( dateTime.Minute( ) == 30 );
}

// --run_test=DateTimeTests/DateTimeSecondTest1
BOOST_AUTO_TEST_CASE( DateTimeSecondTest1 )
{
    DateTime dateTime( 2020, 1, 2, 12, 30, 45, 500 );

    BOOST_CHECK( dateTime.Second( ) == 45 );
}

// --run_test=DateTimeTests/DateTimeMillisecondTest1
BOOST_AUTO_TEST_CASE( DateTimeMillisecondTest1 )
{
    DateTime dateTime( 2020, 1, 2, 12, 30, 45, 500 );

    BOOST_CHECK( dateTime.Millisecond( ) == 500 );
}

// --run_test=DateTimeTests/DateTimeDayOfWeekTest1
BOOST_AUTO_TEST_CASE( DateTimeDayOfWeekTest1 )
{
    DateTime dateTime( 2020, 1, 2 );
    auto dayOfWeek = dateTime.DayOfWeek( );

    BOOST_CHECK( dayOfWeek == DayOfWeek::Thursday );
}

// --run_test=DateTimeTests/DateTimeDayOfYearTest1 
BOOST_AUTO_TEST_CASE( DateTimeDayOfYearTest1 )
{
    DateTime dateTime( 2020, 1, 2 );
    auto dayOfYear = dateTime.DayOfYear( );

    BOOST_CHECK( dayOfYear == 2 );
}

// --run_test=DateTimeTests/FormatTest1
BOOST_AUTO_TEST_CASE( FormatTest1 )
{
    DateTime dateTime( 2020, 1, 2, 1, 2, 3, 345 );

    auto text = std::format( "{}", dateTime );

    bool empty = text.empty( );
    BOOST_CHECK( empty == false );

    auto text2 = std::format( "{:%Y-%m-%d %H:%M:%S}", std::chrono::floor<std::chrono::milliseconds>( dateTime.ToTimePoint() ) );
    empty = text.empty( );
    BOOST_CHECK( empty == false );
    



}





BOOST_AUTO_TEST_SUITE_END( )
