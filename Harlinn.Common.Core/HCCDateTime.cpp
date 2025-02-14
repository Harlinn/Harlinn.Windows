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
#include <HCCDateTime.h>
#include <HCCLogging.h>
#include <HCCString.h>

extern "C"
{
    typedef struct _caldatetime
    {
        CALID CalId;
        UINT  Era;
        UINT  Year;
        UINT  Month;
        UINT  Day;
        UINT  DayOfWeek;
        UINT  Hour;
        UINT  Minute;
        UINT  Second;
        ULONG Tick;
    } CALDATETIME, * LPCALDATETIME;

    typedef BOOL( __stdcall* GetCalendarDateFormatExProc )( LPCWSTR lpszLocale, DWORD dwFlags, const LPCALDATETIME lpCalDateTime, LPCWSTR lpFormat, LPWSTR lpDateStr, int cchDate );
}

namespace
{
    GetCalendarDateFormatExProc LoadGetCalendarDateFormatEx( )
    {
        auto module = LoadLibraryW( L"Kernel32.dll" );
        if ( !module )
        {
            Harlinn::Common::Core::ThrowLastOSError( );
        }
        auto result = (GetCalendarDateFormatExProc)GetProcAddress( module, "GetCalendarDateFormatEx" );
        return result;
    }

    GetCalendarDateFormatExProc GetCalendarDateFormatEx = LoadGetCalendarDateFormatEx( );
}


namespace Harlinn::Common::Core
{


    // ----------------------------------------------------------------------
    // TimeSpan
    // ----------------------------------------------------------------------

    long long TimeSpan::TimeToTicks( int days, int hours, int minutes, int seconds, int milliseconds )
    {
        long long milliSeconds = ( static_cast<long long>(days) * 3600 * 24 +
            static_cast<long long>( hours ) * 3600 +
            static_cast<long long>( minutes ) * 60 + seconds ) * 1000 +
            milliseconds;

        if ( milliSeconds > MaxMilliSeconds || milliSeconds < MinMilliSeconds )
        {
            throw ArgumentOutOfRangeException( );
        }
        long long result = milliSeconds * TicksPerMillisecond;
        return result;
    }

    TimeSpan TimeSpan::Interval( double value, int scale )
    {
        if ( _isnan( value ) )
        {
            throw ArgumentException( );
        }
        double milliSeconds = value * scale;
        milliSeconds = milliSeconds + ( value >= 0 ? 0.5 : -0.5 );

        if ( ( milliSeconds > MAXINT64 / TicksPerMillisecond ) || ( milliSeconds < MININT64 / TicksPerMillisecond ) )
        {
            throw OverflowException( );
        }
        return TimeSpan( (long long)milliSeconds * TicksPerMillisecond );
    }


    WideString TimeSpan::ToWideString( ) const
    {
        wchar_t buffer[128];
        size_t length = GetDurationFormat( LOCALE_USER_DEFAULT, 0, nullptr, ticks_, L"d:hh:mm:ss:fffffff", buffer, 128 );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        return WideString( buffer, length );
    }

    WideString TimeSpan::ToWideString( const WideString& theFormat ) const
    {
        wchar_t buffer[256];
        size_t length = GetDurationFormat( LOCALE_USER_DEFAULT, 0, nullptr, ticks_, theFormat.c_str( ), buffer, 256 );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        return WideString( buffer, length );
    }

    AnsiString TimeSpan::ToAnsiString( ) const
    {
        auto ws = ToWideString( );
        return Core::ToAnsiString( ws );
    }

    AnsiString TimeSpan::ToAnsiString( const AnsiString& format ) const
    {
        auto wsFormat = Core::ToWideString( format );
        auto ws = ToWideString( wsFormat );
        return Core::ToAnsiString( ws );
    }


    WideString TimeSpan::ToString( ) const
    {
        return ToWideString( );
    }
    WideString TimeSpan::ToString( const WideString& theFormat ) const
    {
        return ToWideString( theFormat );
    }

    namespace
    {
        inline Int32 ToInt32( const char* start, char** end, int radix )
        {
            return strtoul( start, end, 10 );
        }
        inline Int32 ToInt32( const wchar_t* start, wchar_t** end, int radix )
        {
            return wcstoul( start, end, 10 );
        }

        inline double ToDouble( const char* start, char** end )
        {
            return strtod( start, end );
        }
        inline double ToDouble( const wchar_t* start, wchar_t** end )
        {
            return wcstod( start, end );
        }


        template <typename CharType >
        bool TryParseImpl( const CharType* text, TimeSpan& result )
        {
            constexpr wchar_t timeSeparator = ':';
            constexpr wchar_t fractionSeparator = '.';
            constexpr wchar_t minus = '-';


            const CharType* start = text;
            // eat white space
            while ( *start && iswblank( *start ) )
            {
                start++;
            }
            if ( *start )
            {
                bool negative = false;
                if ( *start == minus )
                {
                    negative = true;
                    start++;
                }
                if ( *start )
                {
                    _set_errno( 0 );
                    CharType* end = nullptr;
                    int days = ToInt32( start, &end, 10 );
                    if ( days || errno == 0 )
                    {
                        if ( *end == timeSeparator )
                        {
                            start = end + 1;
                            int hours = ToInt32( start, &end, 10 );
                            if ( hours || errno == 0 )
                            {
                                if ( *end == timeSeparator )
                                {
                                    start = end + 1;
                                    int minutes = ToInt32( start, &end, 10 );
                                    if ( minutes || errno == 0 )
                                    {
                                        if ( *end == timeSeparator )
                                        {
                                            start = end + 1;
                                            int seconds = ToInt32( start, &end, 10 );
                                            if ( seconds || errno == 0 )
                                            {
                                                if ( *end == fractionSeparator )
                                                {
                                                    double fraction = ToDouble( start, &end );
                                                    if ( fraction || errno == 0 )
                                                    {
                                                        result = ( negative ? TimeSpan( -days, hours, minutes, seconds ) : TimeSpan( days, hours, minutes, seconds ) ) + TimeSpan::FromSeconds( fraction );
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        return false;
                                                    }
                                                }
                                                else
                                                {
                                                    result = negative ? TimeSpan( -days, hours, minutes, seconds ) : TimeSpan( days, hours, minutes, seconds );
                                                    return true;
                                                }
                                            }
                                            else
                                            {
                                                return false;
                                            }
                                        }
                                        else
                                        {
                                            result = negative ? TimeSpan( -days, hours, minutes, 0 ) : TimeSpan( days, hours, minutes, 0 );
                                            return true;
                                        }
                                    }
                                    else
                                    {
                                        return false;
                                    }
                                }
                                else
                                {
                                    result = negative ? TimeSpan( -days, hours, 0, 0 ) : TimeSpan( days, hours, 0, 0 );
                                    return true;
                                }
                            }
                            else
                            {
                                return false;
                            }
                        }
                        else
                        {
                            result = negative ? TimeSpan( -days, 0, 0, 0 ) : TimeSpan( days, 0, 0, 0 );
                            return true;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    // nothing useful
                    return false;
                }
            }
            else
            {
                // Only white space
                return false;
            }
        }
    }

    bool TimeSpan::TryParse( const wchar_t* text, TimeSpan& result )
    {
        return TryParseImpl( text, result );
    }


    bool TimeSpan::TryParse( const char* text, TimeSpan& result )
    {
        return TryParseImpl( text, result );
    }

    bool TimeSpan::TryParse( const WideString& text, TimeSpan& result )
    {
        return TryParse( text.c_str( ), result );
    }
    bool TimeSpan::TryParse( const AnsiString& text, TimeSpan& result )
    {
        return TryParse( text.c_str( ), result );
    }


    TimeSpan TimeSpan::Parse( const wchar_t* text )
    {
        TimeSpan timeSpan;
        if ( TryParse( text, timeSpan ) )
        {
            return timeSpan;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid timespan" );
        }
    }

    TimeSpan TimeSpan::Parse( const char* text )
    {
        TimeSpan timeSpan;
        if ( TryParse( text, timeSpan ) )
        {
            return timeSpan;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid timespan" );
        }
    }

    TimeSpan TimeSpan::Parse( const WideString& text )
    {
        return Parse( text.c_str( ) );
    }
    TimeSpan TimeSpan::Parse( const AnsiString& text )
    {
        return Parse( text.c_str( ) );
    }

    HCC_EXPORT std::ostream& operator << ( std::ostream& stream, const TimeSpan& timeSpan )
    {
        auto str = timeSpan.ToAnsiString( );
        stream << str;
        return stream;
    }


    // ----------------------------------------------------------------------
    // DateTime
    // ----------------------------------------------------------------------
    long long DateTime::ToLocalTicks( long long ticksInUtc )
    {
        auto fileTime = ticksInUtc - FileTimeOffset;
        long long localFileTime = 0;
        if ( FileTimeToLocalFileTime( (FILETIME*)&fileTime, (FILETIME*)&localFileTime ) == 0 )
        {
            ThrowLastOSError( );
        }
        return localFileTime + FileTimeOffset;
    }
    long long DateTime::ToUniversalTicks( long long ticksInLocalTime )
    {
        auto localFileTime = ticksInLocalTime - FileTimeOffset;
        long long fileTime = 0;
        if ( LocalFileTimeToFileTime( (FILETIME*)&localFileTime, (FILETIME*)&fileTime ) )
        {
            ThrowLastOSError( );
        }
        return fileTime + FileTimeOffset;
    }








    long long DateTime::ToTicks( int year, int month, int day, int hour, int minute, int second, int millisecond )
    {
        if ( millisecond < 0 || millisecond >= MillisPerSecond )
        {
            throw ArgumentOutOfRangeException( "millisecond" );
        }
        long long ticks = DateToTicks( year, month, day ) + TimeToTicks( hour, minute, second );
        ticks += millisecond * TicksPerMillisecond;
        if ( ticks < MinTicks || ticks > MaxTicks )
        {
            throw ArgumentException( );
        }
        return ticks;
    }


    long long DateTime::JulianDateToTicks( int year, int month, int day )
    {
        const auto& days = ( year % 4 == 0 ) ? DaysToMonth366 : DaysToMonth365;
        long long y = year - 1;
        long long daysUntilMonth = days[month - 1];
        long long n = y * 365 + y / 4 + daysUntilMonth + day - 1;

        // Gregorian 1/1/0001 is Julian 1/3/0001 and n * TicksPerDay 
        // is the ticks in JulianCalendar. So by subtracting two days in 
        // the following we convert the ticks in JulianCalendar 
        // to ticks in Gregorian calendar.
        long long result = ( n - 2 ) * TicksPerDay;

        return result;

    }

    long long DateTime::DateToTicks( int year, int month, int day )
    {
        if ( year >= 1 && year <= 9999 && month >= 1 && month <= 12 )
        {
            const auto& days = IsLeapYear( year ) ? DaysToMonth366 : DaysToMonth365;
            long long daysUntilNextMonth = days[month];
            long long daysUntilMonth = days[month - 1];
            if ( day >= 1 && day <= daysUntilNextMonth - daysUntilMonth )
            {
                long long y = year - 1;
                long long n = y * 365 + y / 4 - y / 100 + y / 400 + daysUntilMonth + day - 1;
                return n * TicksPerDay;
            }
        }
        auto message = Format( L"Argument out of range. Year: {}, Month: {}, Day: {}", year, month, day );
        throw ArgumentOutOfRangeException( static_cast<wchar_t*>( nullptr ), message );
    }

    long long DateTime::SystemTimeToTicks( const SYSTEMTIME& systemTime )
    {
        if ( systemTime.wMilliseconds >= MillisPerSecond )
        {
            throw ArgumentOutOfRangeException( L"systemTime.wMilliseconds");
        }
        auto ticks = DateToTicks( systemTime.wYear, systemTime.wMonth, systemTime.wDay ) + TimeToTicks( systemTime.wHour, systemTime.wMinute, systemTime.wSecond );
        ticks += systemTime.wMilliseconds * TicksPerMillisecond;
        if ( ticks < MinTicks || ticks > MaxTicks )
        {
            throw new ArgumentException( );
        }
        return ticks;
    }

    long long DateTime::TimeToTicks( int hour, int minute, int second )
    {
        if ( hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60 )
        {
            return TimeSpan::TimeToTicks( 0, hour, minute, second );
        }
        throw ArgumentOutOfRangeException( );
    }

    DateTime::DateTime( int year, int month, int day, int hour, int minute, int second, int millisecond )
        : ticks_(0)
    {
        if ( millisecond < 0 || millisecond >= MillisPerSecond )
        {
            throw ArgumentOutOfRangeException( "millisecond" );
        }
        long long ticks = DateToTicks( year, month, day ) + TimeToTicks( hour, minute, second );
        ticks += millisecond * TicksPerMillisecond;
        if ( ticks < MinTicks || ticks > MaxTicks )
        {
            throw new ArgumentException( );
        }
        ticks_ = ticks;
    }




    DateTime DateTime::Add( const TimeSpan& value ) const
    {
        return AddTicks( value.ticks_ );
    }

    DateTime DateTime::Add( double value, int scale ) const
    {
        long long millis = (long long)( value * scale + ( value >= 0 ? 0.5 : -0.5 ) );
        if ( millis <= -MaxMillis || millis >= MaxMillis )
        {
            throw ArgumentOutOfRangeException( "value" );
        }
        return AddTicks( millis * TicksPerMillisecond );
    }

    DateTime DateTime::AddDays( double value ) const
    {
        return Add( value, MillisPerDay );
    }

    DateTime DateTime::AddHours( double value ) const
    {
        return Add( value, MillisPerHour );
    }

    DateTime DateTime::AddMilliseconds( double value ) const
    {
        return Add( value, 1 );
    }

    DateTime DateTime::AddMinutes( double value ) const
    {
        return Add( value, MillisPerMinute );
    }

    DateTime DateTime::AddMonths( int months ) const
    {
        if ( months < -120000 || months > 120000 )
        {
            throw ArgumentOutOfRangeException( "months" );
        }
        int y, m, d;

        GetYearMonthDay( y, m, d );

        int i = m - 1 + months;
        if ( i >= 0 )
        {
            m = i % 12 + 1;
            y = y + i / 12;
        }
        else
        {
            m = 12 + ( i + 1 ) % 12;
            y = y + ( i - 11 ) / 12;
        }
        if ( y < 1 || y > 9999 )
        {
            throw ArgumentOutOfRangeException( "months" );
        }
        int days = DaysInMonth( y, m );
        if ( d > days )
        {
            d = days;
        }
        return DateTime( DateToTicks( y, m, d ) + ticks_ % TicksPerDay );
    }

    DateTime DateTime::AddSeconds( double value ) const
    {
        return Add( value, MillisPerSecond );
    }

    DateTime DateTime::AddTicks( long long value ) const
    {
        if ( value > MaxTicks - ticks_ || value < MinTicks - ticks_ )
        {
            throw ArgumentOutOfRangeException( L"value" );
        }
        return DateTime( ticks_ + value );
    }

    DateTime DateTime::AddYears( int value ) const
    {
        if ( value < -10000 || value > 10000 )
        {
            throw ArgumentOutOfRangeException( L"years" );
        }
        return AddMonths( value * 12 );
    }

    const DateTime& DateTime::AssingTo( SYSTEMTIME& systemTime ) const
    {
        long long filetime = ticks_ - FileTimeOffset;
        FileTimeToSystemTime( (FILETIME*)&filetime, &systemTime );
        return *this;
    }

    AnsiString DateTime::DateToAnsiString( ) const
    {
        char buffer[128];
        SYSTEMTIME systemTime;
        AssingTo( systemTime );
        size_t length = GetDateFormatA( LOCALE_USER_DEFAULT, 0, &systemTime, nullptr, buffer, 128 );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        AnsiString result( buffer, length );
        return result;
    }
    WideString DateTime::DateToString( ) const
    {
        wchar_t buffer[128];
        SYSTEMTIME systemTime;
        AssingTo( systemTime );
        size_t length = GetDateFormatW( LOCALE_USER_DEFAULT, 0, &systemTime, nullptr, buffer, 128 );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        WideString result( buffer, length );
        return result;
    }

    AnsiString DateTime::TimeToAnsiString( ) const
    {
        char buffer[128];
        SYSTEMTIME systemTime;
        AssingTo( systemTime );
        size_t length = GetTimeFormatA( LOCALE_USER_DEFAULT, 0, &systemTime, nullptr, buffer, 128 );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        AnsiString result( buffer, length );
        return result;
    }
    WideString DateTime::TimeToString( ) const
    {
        wchar_t buffer[128];
        SYSTEMTIME systemTime;
        AssingTo( systemTime );
        size_t length = GetTimeFormatW( LOCALE_USER_DEFAULT, 0, &systemTime, nullptr, buffer, 128 );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        WideString result( buffer, length );
        return result;
    }

    AnsiString DateTime::ToAnsiString( ) const
    {
        char buffer[128];
        SYSTEMTIME systemTime;
        AssingTo( systemTime );
        int length = GetDateFormatA( LOCALE_USER_DEFAULT, 0, &systemTime, nullptr, buffer, 128 );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        buffer[length - 1] = '\x20';

        int length2 = GetTimeFormatA( LOCALE_USER_DEFAULT, 0, &systemTime, nullptr, &buffer[length], 128 - ( length ) );
        if ( length2 == 0 )
        {
            ThrowLastOSError( );
        }

        AnsiString result( buffer, size_t( length + length2 - 1 ) );
        return result;
    }

    WideString DateTime::ToString( ) const
    {
        wchar_t buffer[128];
        SYSTEMTIME systemTime;
        AssingTo( systemTime );
        int length = GetDateFormatW( LOCALE_USER_DEFAULT, 0, &systemTime, nullptr, buffer, 128 );
        if ( length == 0 )
        {
            ThrowLastOSError( );
        }
        buffer[length - 1] = '\x20';

        int length2 = GetTimeFormatW( LOCALE_USER_DEFAULT, 0, &systemTime, nullptr, &buffer[length], 128 - ( length ) );
        if ( length2 == 0 )
        {
            ThrowLastOSError( );
        }

        WideString result( buffer, size_t( length + length2 - 1 ) );
        return result;
    }

    WideString DateTime::ToString( const std::wstring_view& format ) const
    {
        auto timePoint = ToTimePoint( );
        std::wformat_args args = std::make_wformat_args( timePoint );

        WideString result;
        std::vformat_to( std::back_insert_iterator{ result }, format, args );
        return result;
    }




    int DateTime::DaysInMonth( int year, int month )
    {
        if ( month < 1 || month > 12 )
        {
            throw ArgumentOutOfRangeException( L"month" );
        }
        const auto& days = IsLeapYear( year ) ? DaysToMonth366 : DaysToMonth365;
        return static_cast<int>(days[month] - days[month - 1]);
    }

    long long DateTime::DoubleDateToTicks( double value )
    {
        if ( value >= OADateMaxAsDouble || value <= OADateMinAsDouble )
        {
            throw new ArgumentException( L"value" );
        }
        long long millis = (long long)( value * MillisPerDay + ( value >= 0 ? 0.5 : -0.5 ) );

        // fixup for negative milliseconds
        if ( millis < 0 )
        {
            millis -= ( millis % MillisPerDay ) * 2;
        }

        millis += DoubleDateOffset / TicksPerMillisecond;

        if ( millis < 0 || millis >= MaxMillis )
        {
            throw new ArgumentException( L"value" );
        }
        return millis * TicksPerMillisecond;
    }



    DateTime DateTime::FromBinary( long long data )
    {
        DateTime result;
        return DateTime( data );
    }


    DateTime DateTime::FromFileTime( long long fileTime )
    {
        if ( fileTime < 0 || fileTime > MaxTicks - FileTimeOffset )
        {
            throw new ArgumentOutOfRangeException( "fileTime" );
        }

        return DateTime( fileTime + FileTimeOffset );
    }

    DateTime DateTime::FromOADate( double d )
    {
        return DateTime( DoubleDateToTicks( d ) );
    }

    DateTime DateTime::FromUDate( double d )
    {
        auto ticks = static_cast<long long>( d * TicksPerSecond ) + UnixEpoch;
        return DateTime( DoubleDateToTicks( d ) );
    }

    bool DateTime::IsDaylightSavingTime( ) const
    {
        USHORT year = USHORT( Year( ) );
        TIME_ZONE_INFORMATION tzi;
        if ( GetTimeZoneInformationForYear( year, nullptr, &tzi ) == FALSE )
        {
            ThrowLastOSError( );
        }

        tzi.DaylightDate.wYear = year;
        tzi.StandardDate.wYear = year;

        long long daylightDateInTicks = SystemTimeToTicks( tzi.DaylightDate );
        long long standardDateInTicks = SystemTimeToTicks( tzi.StandardDate );

        if ( daylightDateInTicks > standardDateInTicks )
        {
            if ( ticks_ > standardDateInTicks && ticks_ < daylightDateInTicks )
            {
                return true;
            }
        }
        else if ( daylightDateInTicks < standardDateInTicks )
        {
            if ( ticks_ > daylightDateInTicks && ticks_ < standardDateInTicks  )
            {
                return true;
            }
        }
        return false;
    }

    int DateTime::GetDatePart( DatePart part ) const noexcept
    {
        int n = (int)( ticks_ / TicksPerDay );
        int periodsOf400years = n / DaysPer400Years;
        n -= periodsOf400years * DaysPer400Years;
        int periodsOf100years = n / DaysPer100Years;
        if ( periodsOf100years == 4 )
        {
            periodsOf100years = 3;
        }
        n -= periodsOf100years * DaysPer100Years;
        int periodsOf4years = n / DaysPer4Years;
        n -= periodsOf4years * DaysPer4Years;
        int y1 = n / DaysPerYear;
        if ( y1 == 4 )
        {
            y1 = 3;
        }

        if ( part == DatePart::Year )
        {
            return periodsOf400years * 400 + periodsOf100years * 100 + periodsOf4years * 4 + y1 + 1;
        }
        n -= y1 * DaysPerYear;
        if ( part == DatePart::DayOfYear )
        {
            return n + 1;
        }

        bool leapYear = y1 == 3 && ( periodsOf4years != 24 || periodsOf100years == 3 );

        const auto& days = leapYear ? DaysToMonth366 : DaysToMonth365;

        int m = ( n >> 5 ) + 1;

        while ( n >= days[m] )
        {
            m++;
        }
        if ( part == DatePart::Month )
        {
            return m;
        }
        return static_cast<int>(n - days[m - 1] + 1);
    }

    void DateTime::GetYearMonthDay( int& year, int& month, int& day ) const
    {
        int n = (int)( ticks_ / TicksPerDay );
        int periodsOf400years = n / DaysPer400Years;
        n -= periodsOf400years * DaysPer400Years;
        int periodsOf100years = n / DaysPer100Years;
        if ( periodsOf100years == 4 )
        {
            periodsOf100years = 3;
        }
        n -= periodsOf100years * DaysPer100Years;
        int periodsOf4years = n / DaysPer4Years;
        n -= periodsOf4years * DaysPer4Years;
        int y1 = n / DaysPerYear;
        if ( y1 == 4 )
        {
            y1 = 3;
        }

        year = periodsOf400years * 400 + periodsOf100years * 100 + periodsOf4years * 4 + y1 + 1;

        n -= y1 * DaysPerYear;

        bool leapYear = y1 == 3 && ( periodsOf4years != 24 || periodsOf100years == 3 );

        const auto& days = leapYear ? DaysToMonth366 : DaysToMonth365;

        int m = ( n >> 5 ) + 1;

        while ( n >= days[m] )
        {
            m++;
        }
        month = m;

        day = static_cast<int>(n - days[m - 1] + 1);
    }



    bool DateTime::IsLeapYear( int year )
    {
        if ( year < 1 || year > 9999 )
        {
            throw ArgumentOutOfRangeException( "year" );
        }
        return year % 4 == 0 && ( year % 100 != 0 || year % 400 == 0 );
    }

    TimeSpan DateTime::Subtract( const DateTime& value ) const
    {
        return TimeSpan( ticks_ - value.ticks_ );
    }

    DateTime DateTime::Subtract( const TimeSpan& value ) const
    {
        if ( ticks_ - MinTicks < value.ticks_ || ticks_ - MaxTicks > value.ticks_ )
        {
            throw ArgumentOutOfRangeException( "value" );
        }
        return DateTime( ticks_ - value.ticks_ );
    }

    double DateTime::TicksToOADate( long long value )
    {
        if ( value == 0 )
        {
            return 0.0;
        }
        if ( value < TicksPerDay )
        {
            value += DoubleDateOffset;
        }
        if ( value < OADateMinAsTicks )
        {
            throw OverflowException( );
        }
        long long millis = ( value - DoubleDateOffset ) / TicksPerMillisecond;
        if ( millis < 0 )
        {
            long long frac = millis % MillisPerDay;
            if ( frac != 0 )
            {
                millis -= ( MillisPerDay + frac ) * 2;
            }
        }
        return ( (double)millis ) / MillisPerDay;
    }

    long long DateTime::ToFileTime( ) const
    {
        long long ticks = ticks_ - FileTimeOffset;
        if ( ticks < 0 )
        {
            throw ArgumentOutOfRangeException( static_cast<wchar_t*>( nullptr ) );
        }
        return ticks;
    }

    DateTime DateTime::ToLocalTime( ) const
    {
        DYNAMIC_TIME_ZONE_INFORMATION dynamicTimeZoneInformation;
        GetDynamicTimeZoneInformation( &dynamicTimeZoneInformation );

        SYSTEMTIME systemtime = { 0, };
        long long ft = ticks_ - FileTimeOffset;
        FileTimeToSystemTime( (const FILETIME*)&ft, &systemtime );

        SYSTEMTIME localSystemtime = { 0, };
        SystemTimeToTzSpecificLocalTimeEx( &dynamicTimeZoneInformation, &systemtime, &localSystemtime );

        SystemTimeToFileTime( &localSystemtime, (FILETIME*)&ft );
        long long ticks = ft + FileTimeOffset;
        return DateTime( ticks );
    }

    DateTime DateTime::ToUniversalTime( ) const
    {
        DYNAMIC_TIME_ZONE_INFORMATION dynamicTimeZoneInformation;
        GetDynamicTimeZoneInformation( &dynamicTimeZoneInformation );

        SYSTEMTIME localSystemtime = { 0, };
        long long ft = ticks_ - FileTimeOffset;
        FileTimeToSystemTime( (const FILETIME*)&ft, &localSystemtime );

        SYSTEMTIME systemtime = { 0, };
        TzSpecificLocalTimeToSystemTimeEx( &dynamicTimeZoneInformation, &localSystemtime, &systemtime );

        SystemTimeToFileTime( &systemtime, (FILETIME*)&ft );
        long long ticks = ft + FileTimeOffset;
        return DateTime( ticks );
    }

    bool DateTime::TryCreate( int year, int month, int day, int hour, int minute, int second, int millisecond, DateTime& result )
    {
        result = MinValue( );
        if ( year < 1 || year > 9999 || month < 1 || month > 12 )
        {
            return false;
        }
        const auto& days = IsLeapYear( year ) ? DaysToMonth366 : DaysToMonth365;
        if ( day < 1 || day > days[month] - days[month - 1] )
        {
            return false;
        }

        if ( hour < 0 || hour >= 24 || minute < 0 || minute >= 60 || second < 0 || second >= 60 )
        {
            return false;
        }
        if ( millisecond < 0 || millisecond >= MillisPerSecond )
        {
            return false;
        }
        long long ticks = DateToTicks( year, month, day ) + TimeToTicks( hour, minute, second );

        ticks += millisecond * TicksPerMillisecond;
        if ( ticks < MinTicks || ticks > MaxTicks )
        {
            return false;
        }
        result = DateTime( ticks );
        return true;
    }

    bool DateTime::TryParse( const std::locale& locale, const wchar_t* text, size_t textLength, const wchar_t* format, DateTime& result )
    {
        const auto* ptr = text;
        while ( Internal::IsSpace( *ptr ) && textLength )
        {
            ptr++;
            textLength--;
        }
        if ( textLength )
        {
            boost::iostreams::stream<boost::iostreams::basic_array_source<wchar_t>> stream( text, textLength );
            stream.imbue( locale );

            std::chrono::system_clock::time_point timePoint;
            stream >> std::chrono::parse( format, timePoint );
            if ( !stream.fail( ) )
            {
                result = FromTimePoint( timePoint );
                return true;
            }
        }
        return false;
    }
    bool DateTime::TryParse( const std::locale& locale, const char* text, size_t textLength, const char* format, DateTime& result )
    {
        const auto* ptr = text;
        while ( Internal::IsSpace( *ptr ) && textLength )
        {
            ptr++;
            textLength--;
        }
        if ( textLength )
        {
            boost::iostreams::stream<boost::iostreams::basic_array_source<char>> stream( text, textLength );
            stream.imbue( locale );

            std::chrono::system_clock::time_point timePoint;
            stream >> std::chrono::parse( format, timePoint );
            if ( !stream.fail( ) )
            {
                result = FromTimePoint( timePoint );
                return true;
            }
        }
        return false;
    }


    



    DateTime DateTime::Parse( const wchar_t* text )
    {
        DateTime dateTime;
        if ( TryParse( text, dateTime ) )
        {
            return dateTime;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid datetime" );
        }
    }

    DateTime DateTime::Parse( const char* text )
    {
        DateTime dateTime;
        if ( TryParse( text, dateTime ) )
        {
            return dateTime;
        }
        else
        {
            HCC_THROW( ArgumentException, L"Invalid datetime" );
        }
    }

    DateTime DateTime::Parse( const WideString& text )
    {
        return Parse( text.c_str( ) );
    }
    DateTime DateTime::Parse( const AnsiString& text )
    {
        return Parse( text.c_str( ) );
    }

    std::ostream& operator << ( std::ostream& stream, const DateTime& dateTime )
    {
        auto str = dateTime.ToAnsiString( );
        stream << str;
        return stream;
    }


    // ----------------------------------------------------------------------
    // Stopwatch
    // ----------------------------------------------------------------------
    long long Stopwatch::frequency_( TimeBase::TicksPerSecond );
    const bool Stopwatch::IsHighResolution = Stopwatch::InitializeStopwatch( );
    double Stopwatch::tickFrequency_ = 1.0;

    bool Stopwatch::InitializeStopwatch( )
    {
        long long frq = 0;
        bool result = QueryPerformanceFrequency( (LARGE_INTEGER*)&frq ) != FALSE;
        if ( result )
        {
            frequency_ = frq;
            tickFrequency_ = static_cast<double>( TimeBase::TicksPerSecond ) / static_cast<double>( frequency_ );
        }
        return result;
    }

    long long Stopwatch::Frequency( )
    {
        return frequency_;
    }


    Stopwatch::Stopwatch( )
        : elapsedTicks_( 0 ),
          isRunning_( false ),
          startedAt_( 0 )
    {

    }

    void Stopwatch::Start( )
    {
        if ( !isRunning_ )
        {
            startedAt_ = GetTimestamp( );
            isRunning_ = true;
        }
    }

    void Stopwatch::Restart( )
    {
        elapsedTicks_ = 0;
        startedAt_ = GetTimestamp( );
        isRunning_ = true;
    }

    void Stopwatch::Stop( )
    {
        if ( isRunning_ )
        {
            isRunning_ = false;

            long long endTimeStamp = GetTimestamp( );
            long long elapsedThisPeriod = endTimeStamp - startedAt_;
            elapsedTicks_ += elapsedThisPeriod;

            if ( elapsedTicks_ < 0 )
            {
                elapsedTicks_ = 0;
            }
        }
    }

    void Stopwatch::Reset( )
    {
        elapsedTicks_ = 0;
        isRunning_ = false;
        startedAt_ = 0;
    }


    bool Stopwatch::IsRunning( ) const
    {
        return isRunning_;
    }

    TimeSpan Stopwatch::Elapsed( ) const
    {
        return TimeSpan( GetElapsedDateTimeTicks( ) );
    }

    long long Stopwatch::ElapsedMilliseconds( ) const
    {
        return GetElapsedDateTimeTicks( ) / TimeBase::TicksPerMillisecond;
    }

    long long Stopwatch::ElapsedTicks( ) const
    {
        long long timeElapsed = elapsedTicks_;

        if ( isRunning_ )
        {
            long long currentTimeStamp = GetTimestamp( );
            long long elapsedUntilNow = currentTimeStamp - startedAt_;
            timeElapsed += elapsedUntilNow;
        }
        return timeElapsed;
    }

    double Stopwatch::TotalSeconds( ) const
    {
        TimeSpan timeSpan( GetElapsedDateTimeTicks( ) );
        return timeSpan.TotalSeconds( );
    }

    long long Stopwatch::GetTimestamp( )
    {
        if ( IsHighResolution )
        {
            long long timestamp = 0;
            QueryPerformanceCounter( (LARGE_INTEGER*)&timestamp );
            return timestamp;
        }
        else
        {
            return DateTime::UtcNow( ).Ticks( );
        }
    }

    double Stopwatch::GetTimestampInSeconds( )
    {
        double ts = tickFrequency_ * double( Stopwatch::GetTimestamp( ) ) * TimeBase::SecondsPerTick;
        return ts;
    }
    double Stopwatch::GetTimestampInMilliseconds( )
    {
        double ts = tickFrequency_ * double( Stopwatch::GetTimestamp( ) ) * TimeBase::MillisecondsPerTick;
        return ts;
    }

    long long Stopwatch::GetElapsedDateTimeTicks( ) const
    {
        long long ticks = ElapsedTicks( );
        if ( IsHighResolution )
        {
            double dticks = double( ticks );
            dticks *= tickFrequency_;
            return long long( dticks );
        }
        else
        {
            return ticks;
        }
    }
}
