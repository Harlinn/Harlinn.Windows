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
#include <HCCDateTime.h>
#include <HCCLogging.h>
#include <HCCString.h>
#include <Harlinn/Math/Math.h>

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

    long long TimeSpan::TimeToTicks( int days, int hours, int minutes, int seconds, double fraction )
    {
        long long ticks = ( static_cast<long long>( days ) * 3600 * 24 +
            static_cast<long long>( hours ) * 3600 +
            static_cast< long long >( minutes ) * 60 + seconds ) * TicksPerSecond;
        if ( std::isnan( fraction ) )
        {
            throw ArgumentException( );
        }
        ticks += static_cast<long long>( fraction * TicksPerSecond );

        if ( ticks > MaxTicks || ticks < MinTicks )
        {
            throw ArgumentOutOfRangeException( );
        }
        return ticks;
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


    namespace Internal
    {
        template<typename CharT>
            requires std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>
        HCC_EXPORT bool TryParseTimeSpan( const CharT* s, size_t sLength, TimeSpan& result ) noexcept
        {
            // Local character constants
            constexpr CharT Dot = static_cast< CharT >( '.' );
            constexpr CharT Comma = static_cast< CharT >( ',' );
            constexpr CharT Plus = static_cast< CharT >( '+' );
            constexpr CharT Minus = static_cast< CharT >( '-' );
            constexpr CharT Colon = static_cast< CharT >( ':' );
            constexpr CharT Space = static_cast< CharT >( ' ' );
            constexpr CharT Tab = static_cast< CharT >( '\t' );

            auto fail = [ & ]( ) -> bool
                {
                    result = TimeSpan::Zero( );
                    return false;
                };

            if ( s == nullptr )
            {
                return fail( );
            }

            const CharT* p = s;
            const CharT* end = s + sLength;

            // skip leading simple whitespace (space and tab)
            while ( p < end && ( *p == Space || *p == Tab ) ) ++p;
            if ( p == end ) return fail( );

            // optional sign
            bool negative = false;
            if ( *p == Minus ) { negative = true; ++p; }
            else if ( *p == Plus ) { ++p; }

            // digit parser with overflow checks: accumulates into outValue, returns digit count or -1 on overflow
            auto parseDigits = [ & ]( const CharT*& it, const CharT* itEnd, long long& outValue ) -> int
                {
                    outValue = 0;
                    int digits = 0;
                    while ( it < itEnd )
                    {
                        CharT c = *it;
                        if ( c < static_cast< CharT >( '0' ) || c > static_cast< CharT >( '9' ) ) break;
                        int d = static_cast< int >( c - static_cast< CharT >( '0' ) );
                        if ( !IsMultiplicationSafe<long long>( outValue, 10 ) ) return -1;
                        long long tmp = outValue * 10;
                        if ( !IsAdditionSafe<long long>( tmp, d ) ) return -1;
                        outValue = tmp + d;
                        ++it;
                        ++digits;
                    }
                    return digits;
                };

            // Precomputed powers for scaling fractional part to 7 digits (ticks)
            // pow10Asc[k] == 10^k
            static constexpr long long Pow10_7[ ] = { 1LL, 10LL, 100LL, 1000LL, 10000LL, 100000LL, 1000000LL, 10000000LL };
            // Note: scale = 10^(7 - fracDigits) -> use Pow10_7[7 - fracDigits]

            // Parse first numeric token (could be: days OR hours depending on separators)
            const CharT* tokenStart = p;
            long long firstValue = 0;
            int firstDigits = parseDigits( p, end, firstValue );
            if ( firstDigits == -1 ) return fail( );
            if ( firstDigits == 0 ) return fail( ); // first token must have at least one digit

            // If end -> single number -> treat as days
            if ( p == end )
            {
                // firstValue -> days
                long long days = firstValue;
                // compute ticks = days * TicksPerDay
                if ( !IsMultiplicationSafe<long long>( days, TimeSpan::TicksPerDay ) ) return fail( );
                long long ticks = days * TimeSpan::TicksPerDay;
                if ( negative )
                {
                    if ( ticks == MinInt64 ) return fail( );
                    ticks = -ticks;
                }
                result = TimeSpan( ticks );
                return true;
            }

            // Look at separator after first token
            if ( *p == Dot )
            {
                // Pattern: days '.' time-part
                long long days = firstValue;
                ++p; // consume '.'

                // After dot we expect at least one digit for hours
                if ( p >= end ) return fail( );
                long long hours = 0;
                int hoursDigits = parseDigits( p, end, hours );
                if ( hoursDigits == -1 ) return fail( );
                if ( hoursDigits == 0 ) return fail( );

                long long minutes = 0;
                long long seconds = 0;
                long long fractionTicks = 0;

                if ( p < end && *p == Colon )
                {
                    // there is a colon after hours => parse minutes
                    ++p;
                    if ( p >= end ) return fail( );
                    int minuteDigits = parseDigits( p, end, minutes );
                    if ( minuteDigits == -1 ) return fail( );
                    if ( minuteDigits == 0 ) return fail( );

                    // optional :seconds
                    if ( p < end && *p == Colon )
                    {
                        ++p;
                        if ( p >= end ) return fail( );
                        int secondDigits = parseDigits( p, end, seconds );
                        if ( secondDigits == -1 ) return fail( );
                        if ( secondDigits == 0 ) return fail( );

                        // optional fractional part after seconds
                        if ( p < end && ( *p == Dot || *p == Comma ) )
                        {
                            ++p;
                            long long fracValue = 0;
                            int fracDigits = 0;
                            // accumulate up to 7 digits
                            while ( p < end && fracDigits < 7 )
                            {
                                CharT c = *p;
                                if ( c < static_cast< CharT >( '0' ) || c > static_cast< CharT >( '9' ) ) break;
                                int d = static_cast< int >( c - static_cast< CharT >( '0' ) );
                                if ( !IsMultiplicationSafe<long long>( fracValue, 10 ) ) return fail( );
                                long long tmp = fracValue * 10;
                                if ( !IsAdditionSafe<long long>( tmp, d ) ) return fail( );
                                fracValue = tmp + d;
                                ++p;
                                ++fracDigits;
                            }
                            // skip remaining fractional digits (truncate)
                            while ( p < end )
                            {
                                CharT c = *p;
                                if ( c < static_cast< CharT >( '0' ) || c > static_cast< CharT >( '9' ) ) break;
                                ++p;
                            }
                            if ( fracDigits > 0 )
                            {
                                int idx = 7 - fracDigits;
                                long long scale = Pow10_7[ idx ];
                                if ( !IsMultiplicationSafe<long long>( fracValue, scale ) ) return fail( );
                                fractionTicks = fracValue * scale;
                            }
                        }
                    }
                }
                else
                {
                    // No colon after hours -> treat as days.hours (hours only), minutes/seconds = 0
                    // (e.g. "10.20" => 10 days, 20 hours)
                }

                // skip trailing whitespace
                while ( p < end && ( *p == Space || *p == Tab ) ) ++p;
                if ( p != end ) return fail( );

                // Compose ticks with overflow checks
                long long ticks = 0;
                if ( days != 0 )
                {
                    if ( !IsMultiplicationSafe<long long>( days, TimeSpan::TicksPerDay ) ) return fail( );
                    long long dTicks = days * TimeSpan::TicksPerDay;
                    if ( !IsAdditionSafe<long long>( ticks, dTicks ) ) return fail( );
                    ticks += dTicks;
                }
                if ( hours != 0 )
                {
                    if ( !IsMultiplicationSafe<long long>( hours, TimeSpan::TicksPerHour ) ) return fail( );
                    long long hTicks = hours * TimeSpan::TicksPerHour;
                    if ( !IsAdditionSafe<long long>( ticks, hTicks ) ) return fail( );
                    ticks += hTicks;
                }
                if ( minutes != 0 )
                {
                    if ( !IsMultiplicationSafe<long long>( minutes, TimeSpan::TicksPerMinute ) ) return fail( );
                    long long mTicks = minutes * TimeSpan::TicksPerMinute;
                    if ( !IsAdditionSafe<long long>( ticks, mTicks ) ) return fail( );
                    ticks += mTicks;
                }
                if ( seconds != 0 )
                {
                    if ( !IsMultiplicationSafe<long long>( seconds, TimeSpan::TicksPerSecond ) ) return fail( );
                    long long sTicks = seconds * TimeSpan::TicksPerSecond;
                    if ( !IsAdditionSafe<long long>( ticks, sTicks ) ) return fail( );
                    ticks += sTicks;
                }
                if ( fractionTicks != 0 )
                {
                    if ( !IsAdditionSafe<long long>( ticks, fractionTicks ) ) return fail( );
                    ticks += fractionTicks;
                }

                if ( negative )
                {
                    if ( ticks == MinInt64 ) return fail( );
                    ticks = -ticks;
                }

                result = TimeSpan( ticks );
                return true;
            }
            else if ( *p == Colon )
            {
                // Pattern: time-part without days => firstValue is hours
                long long hours = firstValue;
                ++p; // consume ':'
                if ( p >= end ) return fail( );
                long long minutes = 0;
                int minuteDigits = parseDigits( p, end, minutes );
                if ( minuteDigits == -1 ) return fail( );
                if ( minuteDigits == 0 ) return fail( );

                long long seconds = 0;
                long long fractionTicks = 0;

                if ( p < end && *p == Colon )
                {
                    ++p;
                    if ( p >= end ) return fail( );
                    int secondDigits = parseDigits( p, end, seconds );
                    if ( secondDigits == -1 ) return fail( );
                    if ( secondDigits == 0 ) return fail( );

                    // optional fractional part
                    if ( p < end && ( *p == Dot || *p == Comma ) )
                    {
                        ++p;
                        long long fracValue = 0;
                        int fracDigits = 0;
                        while ( p < end && fracDigits < 7 )
                        {
                            CharT c = *p;
                            if ( c < static_cast< CharT >( '0' ) || c > static_cast< CharT >( '9' ) ) break;
                            int d = static_cast< int >( c - static_cast< CharT >( '0' ) );
                            if ( !IsMultiplicationSafe<long long>( fracValue, 10 ) ) return fail( );
                            long long tmp = fracValue * 10;
                            if ( !IsAdditionSafe<long long>( tmp, d ) ) return fail( );
                            fracValue = tmp + d;
                            ++p;
                            ++fracDigits;
                        }
                        while ( p < end )
                        {
                            CharT c = *p;
                            if ( c < static_cast< CharT >( '0' ) || c > static_cast< CharT >( '9' ) ) break;
                            ++p;
                        }
                        if ( fracDigits > 0 )
                        {
                            int idx = 7 - fracDigits;
                            long long scale = Pow10_7[ idx ];
                            if ( !IsMultiplicationSafe<long long>( fracValue, scale ) ) return fail( );
                            fractionTicks = fracValue * scale;
                        }
                    }
                }

                // skip trailing whitespace
                while ( p < end && ( *p == Space || *p == Tab ) ) ++p;
                if ( p != end ) return fail( );

                // Compose ticks
                long long ticks = 0;
                if ( hours != 0 )
                {
                    if ( !IsMultiplicationSafe<long long>( hours, TimeSpan::TicksPerHour ) ) return fail( );
                    long long hTicks = hours * TimeSpan::TicksPerHour;
                    if ( !IsAdditionSafe<long long>( ticks, hTicks ) ) return fail( );
                    ticks += hTicks;
                }
                if ( minutes != 0 )
                {
                    if ( !IsMultiplicationSafe<long long>( minutes, TimeSpan::TicksPerMinute ) ) return fail( );
                    long long mTicks = minutes * TimeSpan::TicksPerMinute;
                    if ( !IsAdditionSafe<long long>( ticks, mTicks ) ) return fail( );
                    ticks += mTicks;
                }
                if ( seconds != 0 )
                {
                    if ( !IsMultiplicationSafe<long long>( seconds, TimeSpan::TicksPerSecond ) ) return fail( );
                    long long sTicks = seconds * TimeSpan::TicksPerSecond;
                    if ( !IsAdditionSafe<long long>( ticks, sTicks ) ) return fail( );
                    ticks += sTicks;
                }
                if ( fractionTicks != 0 )
                {
                    if ( !IsAdditionSafe<long long>( ticks, fractionTicks ) ) return fail( );
                    ticks += fractionTicks;
                }

                if ( negative )
                {
                    if ( ticks == MinInt64 ) return fail( );
                    ticks = -ticks;
                }

                result = TimeSpan( ticks );
                return true;
            }
            else
            {
                // Unexpected separator after first token -> fail
                return fail( );
            }
        }


        template HCC_TEMPLATE_EXPORT bool TryParseTimeSpan<char>( const char* s, size_t sLength, TimeSpan& result ) noexcept;
        template HCC_TEMPLATE_EXPORT bool TryParseTimeSpan<wchar_t>( const wchar_t* s, size_t sLength, TimeSpan& result ) noexcept;

        template<StringLike T>
        HCC_EXPORT T TimeSpanToString( const TimeSpan& timeSpan, const typename T::value_type* formatString, const typename T::size_type formatStringLength )
        {
            using CharT = typename T::value_type;
            using StringT = std::basic_string<CharT>;

            // Treat nullptr or zero length as empty format (use default "c" behavior)
            bool formatIsEmpty = ( formatString == nullptr ) || ( formatStringLength == 0 );

            // Build format pattern when provided
            std::span<const CharT> fmt;
            if ( !formatIsEmpty )
            {
                fmt = std::span<const CharT>( formatString, formatStringLength );
            }

            const long long ticks = timeSpan.Ticks();
            const bool negative = ticks < 0;
            UInt64 absTicks = Math::UnsignedAbs( ticks );

            // Decompose into components
            const UInt64 ticksPerDay = static_cast< UInt64 >( TimeSpan::TicksPerDay );
            const UInt64 ticksPerHour = static_cast< UInt64 >( TimeSpan::TicksPerHour );
            const UInt64 ticksPerMinute = static_cast< UInt64 >( TimeSpan::TicksPerMinute );
            const UInt64 ticksPerSecond = static_cast< UInt64 >( TimeSpan::TicksPerSecond );

            const UInt64 days = absTicks / ticksPerDay;
            const UInt64 remAfterDays = absTicks % ticksPerDay;
            const unsigned hours = static_cast< unsigned >( remAfterDays / ticksPerHour );
            const UInt64 remAfterHours = remAfterDays % ticksPerHour;
            const unsigned minutes = static_cast< unsigned >( remAfterHours / ticksPerMinute );
            const UInt64 remAfterMinutes = remAfterHours % ticksPerMinute;
            const unsigned seconds = static_cast< unsigned >( remAfterMinutes / ticksPerSecond );
            const UInt64 fractionTicks = remAfterMinutes % ticksPerSecond; // ticks within current second (0..9,999,999)
            // fractionTicks as 7-digit decimal (each tick is 100ns)
            // create decimal representation zero-padded to 7 digits
            auto makeFraction7 = [ & ]( ) -> StringT
                {
                    // narrow decimal
                    char buf[ 16 ];
                    auto n = std::sprintf( buf, "%07llu", static_cast< unsigned long long >( fractionTicks ) );
                    ( void )n;
                    if constexpr ( std::is_same_v<CharT, wchar_t> )
                    {
                        return StringT( std::begin( buf ), std::begin( buf ) + static_cast< size_t >( n ) );
                    }
                    else
                    {
                        return StringT( buf, buf + static_cast< size_t >( n ) );
                    }
                };

            // Helper: append integer value with zero padding width (width==0 -> no padding)
            auto appendPadded = [ & ]( StringT& out, unsigned long long value, int width )
                {
                    if ( width <= 0 )
                    {
                        // append as-is
                        if constexpr ( std::is_same_v<CharT, wchar_t> )
                        {
                            out.append( std::to_wstring( value ) );
                        }
                        else
                        {
                            out.append( std::to_string( value ) );
                        }
                        return;
                    }
                    // convert narrow then widen if needed
                    std::string s = std::to_string( value );
                    if ( static_cast< int >( s.size( ) ) < width )
                    {
                        std::string pad( width - static_cast< int >( s.size( ) ), '0' );
                        s = pad + s;
                    }
                    if constexpr ( std::is_same_v<CharT, wchar_t> )
                    {
                        out.append( StringT( s.begin( ), s.end( ) ) );
                    }
                    else
                    {
                        out.append( s );
                    }
                };

            // Build constant ("c") format: [-][d.]hh:mm:ss[.fffffff]
            auto formatConstant = [ & ]( ) -> StringT
                {
                    StringT out;
                    if ( negative )
                    {
                        out.push_back( static_cast< CharT >( L'-' ) );
                    }

                    if ( days != 0 )
                    {
                        appendPadded( out, days, 0 );
                        out.push_back( static_cast< CharT >( '.' ) );
                    }

                    appendPadded( out, hours, 2 );
                    out.push_back( static_cast< CharT >( ':' ) );
                    appendPadded( out, minutes, 2 );
                    out.push_back( static_cast< CharT >( ':' ) );
                    appendPadded( out, seconds, 2 );

                    if ( fractionTicks != 0 )
                    {
                        out.push_back( static_cast< CharT >( '.' ) );
                        out.append( makeFraction7( ) );
                    }

                    return out;
                };

            // General "g" format: like constant but fractional trimmed of trailing zeros; days separated with ':'
            auto formatGeneral = [ & ]( ) -> StringT
                {
                    StringT out;
                    if ( negative )
                    {
                        out.push_back( static_cast< CharT >( L'-' ) );
                    }

                    if ( days != 0 )
                    {
                        appendPadded( out, days, 0 );
                        out.push_back( static_cast< CharT >( ':' ) );
                    }

                    appendPadded( out, hours, 2 );
                    out.push_back( static_cast< CharT >( ':' ) );
                    appendPadded( out, minutes, 2 );
                    out.push_back( static_cast< CharT >( ':' ) );
                    appendPadded( out, seconds, 2 );

                    if ( fractionTicks != 0 )
                    {
                        StringT frac = makeFraction7( );
                        // trim trailing zeros
                        while ( !frac.empty( ) && frac.back( ) == static_cast< CharT >( '0' ) )
                        {
                            frac.pop_back( );
                        }
                        if ( !frac.empty( ) )
                        {
                            out.push_back( static_cast< CharT >( '.' ) );
                            out.append( frac );
                        }
                    }

                    return out;
                };

            // If format is empty -> default (use constant "c")
            if ( formatIsEmpty )
            {
                return T( formatConstant( ) );
            }

            // If single-character standard format
            if ( fmt.size( ) == 1 )
            {
                CharT f = fmt[ 0 ];
                if ( f == static_cast< CharT >( 'c' ) || f == static_cast< CharT >( 'C' ) )
                {
                    return T( formatConstant( ) );
                }
                else if ( f == static_cast< CharT >( 'g' ) )
                {
                    return T( formatGeneral( ) );
                }
                else if ( f == static_cast< CharT >( 'G' ) )
                {
                    // "G" produce a constant-like result but always include fractional part with 7 digits (even if zero)
                    StringT out = formatConstant( );
                    if ( fractionTicks == 0 )
                    {
                        // append ".0000000" when no fraction and ensure not already present
                        // If formatConstant omitted fraction, append it
                        out.push_back( static_cast< CharT >( '.' ) );
                        out.append( makeFraction7( ) );
                    }
                    return T( out );
                }
            }

            // Otherwise treat as custom format string (subset) - parse tokens and produce output
            // Supported tokens: d, dd, h, hh, m, mm, s, ss, f..fffffff, F..FFFFFFF
            StringT result;
            result.reserve( 64 );

            auto appendDigits = [ & ]( unsigned long long value, int repeat )
                {
                    // repeat == 1 => no padding
                    if ( repeat <= 1 )
                    {
                        appendPadded( result, value, 0 );
                    }
                    else
                    {
                        appendPadded( result, value, repeat );
                    }
                };

            // Prepare fraction 7-digit string as narrow/wide for indexing
            StringT fraction7 = makeFraction7( );

            for ( size_t i = 0; i < fmt.size( ); )
            {
                CharT ch = fmt[ i ];

                // Handle quoted literals
                if ( ch == static_cast< CharT >( '\'' ) || ch == static_cast< CharT >( '\"' ) )
                {
                    CharT quote = ch;
                    ++i;
                    while ( i < fmt.size( ) && fmt[ i ] != quote )
                    {
                        result.push_back( fmt[ i++ ] );
                    }
                    if ( i < fmt.size( ) ) ++i; // skip closing quote
                    continue;
                }

                // Escape with backslash
                if ( ch == static_cast< CharT >( '\\' ) )
                {
                    ++i;
                    if ( i < fmt.size( ) )
                    {
                        result.push_back( fmt[ i++ ] );
                    }
                    continue;
                }

                // Percent: next char is a single custom specifier
                if ( ch == static_cast< CharT >( '%' ) )
                {
                    ++i;
                    if ( i >= fmt.size( ) ) break;
                    ch = fmt[ i++ ];
                    // treat ch as single specifier below by using a small one-char pattern
                    // we emulate by temporary parsing of single char
                    // fallthrough to handler by creating a one-char view
                    // but simpler: handle common percent cases here
                    if ( ch == static_cast< CharT >( 'd' ) )
                    {
                        appendDigits( days, 1 );
                    }
                    else if ( ch == static_cast< CharT >( 'h' ) )
                    {
                        appendDigits( hours, 1 );
                    }
                    else if ( ch == static_cast< CharT >( 'm' ) )
                    {
                        appendDigits( minutes, 1 );
                    }
                    else if ( ch == static_cast< CharT >( 's' ) )
                    {
                        appendDigits( seconds, 1 );
                    }
                    else if ( ch == static_cast< CharT >( 'f' ) || ch == static_cast< CharT >( 'F' ) )
                    {
                        // percent + f -> single fractional digit
                        if ( fractionTicks != 0 )
                        {
                            result.push_back( fraction7[ 0 ] );
                        }
                        else if ( ch == static_cast< CharT >( 'f' ) )
                        {
                            // f with zero -> output '0'
                            result.push_back( static_cast< CharT >( '0' ) );
                        }
                        // F with zero -> omit
                    }
                    else
                    {
                        result.push_back( ch );
                    }
                    continue;
                }

                // Count repeats
                size_t j = i;
                while ( j < fmt.size( ) && fmt[ j ] == ch ) ++j;
                int repeat = static_cast< int >( j - i );

                // Handle tokens
                if ( ch == static_cast< CharT >( 'd' ) )
                {
                    appendDigits( days, repeat );
                }
                else if ( ch == static_cast< CharT >( 'h' ) )
                {
                    appendDigits( hours, repeat );
                }
                else if ( ch == static_cast< CharT >( 'm' ) )
                {
                    appendDigits( minutes, repeat );
                }
                else if ( ch == static_cast< CharT >( 's' ) )
                {
                    appendDigits( seconds, repeat );
                }
                else if ( ch == static_cast< CharT >( 'f' ) )
                {
                    // take leftmost 'repeat' digits from fraction7; pad with zeros on right if needed
                    if ( repeat > 7 ) repeat = 7;
                    for ( int k = 0; k < repeat; ++k )
                    {
                        result.push_back( fraction7[ k ] );
                    }
                    // if fractionTicks == 0 and 'f' used, we must pad with zeros (already done)
                }
                else if ( ch == static_cast< CharT >( 'F' ) )
                {
                    // take leftmost 'repeat' digits and trim trailing zeros
                    if ( repeat > 7 ) repeat = 7;
                    int lastNonZero = -1;
                    for ( int k = 0; k < repeat; ++k )
                    {
                        if ( fraction7[ k ] != static_cast< CharT >( '0' ) ) lastNonZero = k;
                    }
                    if ( lastNonZero >= 0 )
                    {
                        for ( int k = 0; k <= lastNonZero; ++k )
                        {
                            result.push_back( fraction7[ k ] );
                        }
                    }
                    else
                    {
                        // all zeros -> omit output for 'F'
                    }
                }
                else
                {
                    // literal characters
                    result.append( fmt.begin( ) + static_cast< ptrdiff_t >( i ), fmt.begin( ) + static_cast< ptrdiff_t >( j ) );
                }

                i = j;
            }

            // Prepend sign if negative and not already included by pattern
            if ( negative )
            {
                // If the format produced a leading '-' already (format may include it explicitly), do not double it.
                if ( result.empty( ) || result.front( ) != static_cast< CharT >( '-' ) )
                {
                    result.insert( result.begin( ), static_cast< CharT >( '-' ) );
                }
            }

            return T( result );
        }

        template HCC_TEMPLATE_EXPORT std::string TimeSpanToString<std::string>( const TimeSpan& timeSpan, const typename std::string::value_type* formatString, const typename std::string::size_type formatStringLength );

        template HCC_TEMPLATE_EXPORT std::wstring TimeSpanToString<std::wstring>( const TimeSpan& timeSpan, const typename std::wstring::value_type* formatString, const typename std::wstring::size_type formatStringLength );

        template HCC_TEMPLATE_EXPORT AnsiString TimeSpanToString<AnsiString>( const TimeSpan& timeSpan, const typename AnsiString::value_type* formatString, const typename AnsiString::size_type formatStringLength );

        template HCC_TEMPLATE_EXPORT WideString TimeSpanToString<WideString>( const TimeSpan& timeSpan, const typename WideString::value_type* formatString, const typename WideString::size_type formatStringLength );

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
