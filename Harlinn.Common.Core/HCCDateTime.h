#pragma once
#ifndef __HCCDATETIME_H__
#define __HCCDATETIME_H__
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

#include <HCCLib.h>
#include <HCCExport.h>
#include <HCCString.h>

namespace Harlinn::Common::Core
{
    enum class DayOfWeek
    {
        Sunday = 0,
        Monday = 1,
        Tuesday = 2,
        Wednesday = 3,
        Thursday = 4,
        Friday = 5,
        Saturday = 6
    };

    enum class DatePart
    {
        Year = 0,
        DayOfYear = 1,
        Month = 2,
        Day = 3
    };



    class TimeBase
    {
    public:
        static constexpr long long TicksPerMicrosecond = 10;
        static constexpr long long TicksPerMillisecond = 10000;
        static constexpr long long TicksPerSecond = TicksPerMillisecond * 1000;
        static constexpr long long TicksPerMinute = TicksPerSecond * 60;
        static constexpr long long TicksPerHour = TicksPerMinute * 60;
        
        static constexpr long long TicksPerDay = TicksPerHour * 24;
        
        static constexpr long long TicksPerYear = TicksPerDay * 365;

        static constexpr double MillisecondsPerTick = 1.0 / TicksPerMillisecond;
        
        static constexpr double SecondsPerTick = 1.0 / TicksPerSecond;
        
        static constexpr double MinutesPerTick = 1.0 / TicksPerMinute;
        
        static constexpr double HoursPerTick = 1.0 / TicksPerHour;
        
        static constexpr double DaysPerTick = 1.0 / TicksPerDay;
        
        static constexpr double OADateMinAsDouble =  -657435.0;
        
        static constexpr double OADateMaxAsDouble = 2958466.0;
        

        using DaysToMonth = std::array<int, 13>;

        static constexpr DaysToMonth DaysToMonth365{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

        static constexpr DaysToMonth DaysToMonth366{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };


        static constexpr int MillisPerSecond = 1000;
        
        static constexpr int MillisPerMinute = MillisPerSecond * 60;
        
        static constexpr int MillisPerHour = MillisPerMinute * 60;
        
        static constexpr int MillisPerDay = MillisPerHour * 24;
        

        static constexpr long long MaxSeconds = MaxInt64 / TicksPerSecond;
        
        static constexpr long long MinSeconds = MinInt64 / TicksPerSecond;
        

        static constexpr long long MaxMilliSeconds = MaxInt64 / TicksPerMillisecond;
        
        static constexpr long long MinMilliSeconds = MinInt64 / TicksPerMillisecond;

        static constexpr long long UnixEpoch = 621355968000000000LL;
        static constexpr long long NtpEpoch = UnixEpoch - ( 2208988800 * TicksPerSecond );
        

        static constexpr int DaysPerYear= 365;
        
        static constexpr int DaysPer4Years = DaysPerYear * 4 + 1;
        
        static constexpr int DaysPer100Years = DaysPer4Years * 25 - 1;
        
        static constexpr int DaysPer400Years = DaysPer100Years * 4 + 1;


        static constexpr int DaysTo1601 = DaysPer400Years * 4;
        
        static constexpr int DaysTo1899 = DaysPer400Years * 4 + DaysPer100Years * 3 - 367;
        
        static constexpr int DaysTo10000 = DaysPer400Years * 25 - 366;
        

        static constexpr long long MinTicks = 0;
        
        static constexpr long long MaxTicks = DaysTo10000 * TicksPerDay - 1;
        
        static constexpr long long MaxMillis = static_cast<long long>( DaysTo10000 )* MillisPerDay;
        

        static constexpr long long FileTimeOffset = static_cast<long long>( DaysTo1601 ) * TicksPerDay;

        static constexpr long long DoubleDateOffset = static_cast<long long>( DaysTo1899 ) * TicksPerDay;

        static constexpr long long OADateMinAsTicks = ( static_cast<long long>( DaysPer100Years ) - DaysPerYear ) * TicksPerDay;
        

    };


    namespace Internal
    {
        template<typename CharT>
            requires std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>
        HCC_EXPORT bool TryParseTimeSpan( const CharT* s, size_t sLength, TimeSpan& result ) noexcept;

        template HCC_TEMPLATE_EXPORT_DECL bool TryParseTimeSpan<char>( const char* s, size_t sLength, TimeSpan& result ) noexcept;
        template HCC_TEMPLATE_EXPORT_DECL bool TryParseTimeSpan<wchar_t>( const wchar_t* s, size_t sLength, TimeSpan& result ) noexcept;

        template<StringLike T>
        HCC_EXPORT T TimeSpanToString( const TimeSpan& timeSpan, const typename T::value_type* formatString, const typename T::size_type formatStringLength );

        template HCC_TEMPLATE_EXPORT_DECL std::string TimeSpanToString<std::string>( const TimeSpan& timeSpan, const typename std::string::value_type* formatString, const typename std::string::size_type formatStringLength );

        template HCC_TEMPLATE_EXPORT_DECL std::wstring TimeSpanToString<std::wstring>( const TimeSpan& timeSpan, const typename std::wstring::value_type* formatString, const typename std::wstring::size_type formatStringLength );

        template HCC_TEMPLATE_EXPORT_DECL AnsiString TimeSpanToString<AnsiString>( const TimeSpan& timeSpan, const typename AnsiString::value_type* formatString, const typename AnsiString::size_type formatStringLength );

        template HCC_TEMPLATE_EXPORT_DECL WideString TimeSpanToString<WideString>( const TimeSpan& timeSpan, const typename WideString::value_type* formatString, const typename WideString::size_type formatStringLength );

    }


    class DateTime;
    /// <summary>
    /// TimeSpan represents a time interval stored as an integer 
    /// count of "ticks" (ticks_), where one tick = 100 ns (like .NET).
    /// </summary>
    class TimeSpan : public TimeBase
    {
        friend class DateTime;
    public:
        static constexpr long long MinTicks = MinInt64;

        static constexpr long long MaxTicks = MaxInt64;

        static constexpr TimeSpan Zero( )
        {
            return TimeSpan( 0 );
        }
        static constexpr TimeSpan MaxValue( )
        {
            return TimeSpan( MaxInt64 );
        }
        static constexpr TimeSpan MinValue( )
        {
            return TimeSpan( MinInt64 );
        }

    private:
        long long ticks_;

        /// <summary>
        /// Converts a floating-point interval value, scaled by <paramref name="theScale"/>, into a <see cref="TimeSpan"/>.
        /// The value is converted to whole milliseconds by rounding to nearest millisecond, then multiplied by
        /// <c>TicksPerMillisecond</c> (1 tick = 100 ns) to produce the internal tick count stored by <see cref="TimeSpan"/>.
        /// </summary>
        /// <param name="theValue">The interval value (may be fractional). Must not be NaN.</param>
        /// <param name="theScale">
        /// Scale factor applied to <paramref name="theValue"/> to obtain milliseconds. 
        /// Examples: <c>TimeSpan::MillisPerSecond</c> to convert seconds -> milliseconds, <c>TimeSpan::MillisPerDay</c> to convert days -> milliseconds.
        /// </param>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing the interval. Fractional milliseconds are rounded to the nearest millisecond
        /// before conversion to ticks.
        /// </returns>
        /// <remarks>
        /// <para>
        /// Implementation details:
        /// - Computes <c>milliSeconds = theValue * theScale</c>.
        /// - Rounds to nearest integer millisecond by adding <c>+0.5</c> for non-negative values and <c>-0.5</c> for negative values,
        ///   then truncates to a 64-bit integer and multiplies by <c>TicksPerMillisecond</c>.
        /// </para>
        /// <para>
        /// Range considerations:
        /// - The function checks that the computed millisecond value fits in the library's allowed range
        ///   (see <c>TimeBase::MaxMilliSeconds</c> / <c>TimeBase::MinMilliSeconds</c>). If the millisecond value would
        ///   overflow 64-bit ticks it throws <see cref="OverflowException"/>.
        /// </para>
        /// <para>
        /// Thread-safety: function is pure (no side effects) and safe to call concurrently.
        /// </para>
        /// </remarks>
        /// <exception cref="ArgumentException">Thrown when <paramref name="theValue"/> is NaN.</exception>
        /// <exception cref="OverflowException">Thrown when the computed millisecond value is outside the representable range and would overflow ticks.</exception>
        /// <example>
        /// <code language="cpp">
        /// // 1.5 seconds -> milliseconds = 1.5 * TimeSpan::MillisPerSecond (1500), rounded -> TimeSpan of 1500 ms
        /// TimeSpan ts = TimeSpan::Interval( 1.5, TimeSpan::MillisPerSecond );
        ///
        /// // Equivalent convenience helper:
        /// TimeSpan ts2 = TimeSpan::FromSeconds( 1.5 );
        ///
        /// // Use ToTimeout() when passing to Windows wait APIs:
        /// DWORD timeout = ts.ToTimeout();
        /// WaitForSingleObject(handle, timeout);
        /// </code>
        /// </example>
        HCC_EXPORT static TimeSpan Interval( double value, int scale );
    public:

        /// <summary>
        /// Converts an interval expressed as days, hours, minutes, seconds and milliseconds
        /// into the internal tick count used by this library (1 tick = 100 nanoseconds).
        /// </summary>
        /// <param name="days">
        /// Number of days comprising the interval. May be negative to represent a negative interval.
        /// The value is treated as whole days and combined with the other components to form the total interval.
        /// </param>
        /// <param name="hours">
        /// Number of hours (0..23 in typical usage). The function does not enforce per-field limits;
        /// the components are combined into a total millisecond count before range checks are applied.
        /// </param>
        /// <param name="minutes">
        /// Number of minutes (0..59 in typical usage). See remarks for behavior when components exceed usual bounds.
        /// </param>
        /// <param name="seconds">
        /// Number of seconds (0..59 in typical usage).
        /// </param>
        /// <param name="milliseconds">
        /// Number of milliseconds (0..999 in typical usage).
        /// </param>
        /// <returns>
        /// The total interval expressed in ticks (100 ns units). The returned tick count uses the same
        /// epoch/unit convention as `DateTime` and Windows `FILETIME` when combined with the library's
        /// `FileTimeOffset` constant.
        /// </returns>
        /// <remarks>
        /// - Computation: the components are first combined to produce a total number of milliseconds:
        ///   totalMillis = ((days * 24 + hours) * 3600 + minutes * 60 + seconds) * 1000 + milliseconds.
        ///   The final result is totalMillis * `TicksPerMillisecond` (where `TicksPerMillisecond` == 10,000).
        /// - The function performs a range check on the total millisecond value and throws
        ///   `ArgumentOutOfRangeException` if the total milliseconds fall outside the representable range
        ///   (see `TimeBase::MaxMilliSeconds` and `TimeBase::MinMilliSeconds`).
        /// - Typical callers pass small, non-negative values for hours/minutes/seconds/milliseconds and
        ///   use `days` for multi-day intervals. If callers supply component values outside the usual
        ///   per-field ranges (for example `hours >= 24`), those values are still incorporated into the
        ///   total interval arithmetic (no per-field normalization is performed here).
        /// - The returned tick value is suitable for use with this library's `DateTime` APIs and can be
        ///   converted to a Windows `FILETIME` representation by subtracting/adding the `FileTimeOffset`
        ///   constant where appropriate. Windows API functions that accept timeouts (for example
        ///   `WaitForSingleObject`) use milliseconds (DWORD), not ticks — convert ticks to milliseconds
        ///   before calling such APIs.
        /// - The function is thread-safe and has no side-effects; it uses only integer arithmetic.
        /// </remarks>
        /// <exception cref="ArgumentOutOfRangeException">
        /// Thrown when the computed total interval in milliseconds is outside the allowed range.
        /// </exception>
        HCC_EXPORT static long long TimeToTicks( int days, int hours, int minutes, int seconds = 0, int milliseconds = 0 );

        /// <summary>
        /// Converts separate time components (days, hours, minutes, seconds and fractional seconds)
        /// into the library's internal tick count (1 tick == 100 nanoseconds).
        /// </summary>
        /// <param name="days">Whole days component. May be negative to represent a negative interval.</param>
        /// <param name="hours">Hours component (typical range 0..23). Values outside the usual range are accepted and incorporated arithmetically.</param>
        /// <param name="minutes">Minutes component (typical range 0..59). Values outside the usual range are accepted and incorporated arithmetically.</param>
        /// <param name="seconds">Seconds component (typical range 0..59). Values outside the usual range are accepted and incorporated arithmetically.</param>
        /// <param name="fraction">
        /// Fractional seconds expressed in seconds (for example, 0.5 represents 500 ms).
        /// The sign of <paramref name="fraction"/> contributes to the overall interval sign when combined with the other components.
        /// Must not be NaN.
        /// </param>
        /// <returns>
        /// The total interval expressed in ticks (100-nanosecond units) as a <c>long long</c>.
        /// The result is suitable for storage in <see cref="TimeSpan"/> internal representation.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Computation:
        ///   - The integer components are combined arithmetically (days -> hours -> minutes -> seconds) into whole seconds and scaled
        ///     to ticks using the compile-time constants <c>TicksPerSecond</c>, <c>TicksPerMinute</c>, <c>TicksPerHour</c>, <c>TicksPerDay</c>.
        ///   - The <paramref name="fraction"/> value is converted to ticks by multiplying with <c>TicksPerSecond</c> and truncating toward zero
        ///     (no rounding). Sub-tick fractions are discarded.
        /// - Precision & rounding: fractional seconds are converted to whole ticks by truncation. Callers that require a different rounding
        ///   policy should perform rounding before calling this function.
        /// - Range & overflow: the function performs range checks and will throw <see cref="ArgumentOutOfRangeException"/> when the computed
        ///   tick count would fall outside the representable range of <c>long long</c> (or the library limits). All intermediate multiplications
        ///   and additions are checked for overflow to avoid undefined behavior.
        /// - Semantics for out-of-range component values: this routine does not normalize per-field ranges (for example hours &gt;= 24).
        ///   Component values are combined arithmetically; normalizing/validating per-field limits is the caller's responsibility.
        /// - Thread-safety: pure function with no side-effects; safe for concurrent use.
        /// - Complexity: O(1).
        /// </para>
        /// </remarks>
        /// <exception cref="ArgumentException">Thrown when <paramref name="fraction"/> is NaN.</exception>
        /// <exception cref="ArgumentOutOfRangeException">Thrown when the computed tick count would overflow the representable range.</exception>
        /// <example>
        /// <code language="cpp">
        /// // 1 day, 2 hours, 3 minutes, 4.5 seconds -> ticks
        /// long long ticks = TimeSpan::TimeToTicks( 1, 2, 3, 4, 0.5 );
        /// // Equivalent convenience usage:
        /// TimeSpan ts = TimeSpan::FromDays( 1 ) + TimeSpan::FromHours( 2 ) + TimeSpan::FromMinutes( 3 ) + TimeSpan::FromSeconds( 4.5 );
        /// </code>
        /// </example>
        HCC_EXPORT static long long TimeToTicks( int days, int hours, int minutes, int seconds, double fraction );

        /// <summary>
        /// Converts an arbitrary `std::chrono` duration to the internal tick representation used by `TimeSpan`.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy `IsStdChronoDuration`.</typeparam>
        /// <param name="duration">The duration to convert. May be negative to represent a negative interval.</param>
        /// <returns>
        /// The number of ticks (100-nanosecond units) corresponding to `duration`, returned as a <c>long long</c>.
        /// The conversion is performed using `std::chrono::duration_cast` to a duration with period 1 / 10,000,000
        /// seconds (100 ns), then the underlying count is returned.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Precision & rounding: `std::chrono::duration_cast` performs a narrowing conversion. When converting
        ///   from a duration with finer resolution or a floating-point representation the result is truncated
        ///   toward zero (fractional sub-tick parts are discarded). Callers that require specific rounding
        ///   should perform that rounding before calling this function.
        /// </para>
        /// <para>
        /// - Range & overflow: No runtime overflow checking is performed. If the converted tick count does not fit
        ///   in a `long long` the result may overflow or wrap depending on the implementation. Callers should ensure
        ///   the `duration` value is within an acceptable range (for example relative to `TimeBase::MinTicks` / `TimeBase::MaxTicks`)
        ///   before calling this function if overflow must be avoided.
        /// </para>
        /// <para>
        /// - Thread-safety: function is pure and has no side effects.
        /// </para>
        /// </remarks>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        static constexpr long long DurationToTicks( const DurationT& duration )
        {
            return std::chrono::duration_cast<std::chrono::duration<long long, std::ratio<1, 10000000>>>( duration ).count();
        }

        /// <summary>
        /// Converts an internal tick count (100-nanosecond units) into a `std::chrono` duration.
        /// </summary>
        /// <typeparam name="DurationT">
        /// Target `std::chrono::duration` type. Defaults to `std::chrono::system_clock::duration`.
        /// </typeparam>
        /// <param name="ticks">
        /// Number of ticks (1 tick = 100 ns). May be negative to represent a negative interval.
        /// </param>
        /// <returns>
        /// A value of type <paramref name="DurationT"/> representing the same interval as <paramref name="ticks"/>.
        /// The conversion is implemented with `std::chrono::duration_cast` from a 
        /// 100-ns tick duration to the requested duration type.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Rounding/Precision: `std::chrono::duration_cast` truncates toward zero when converting to a coarser-grained
        ///   duration. Sub-tick fractions are discarded. If callers require a different rounding policy they should
        ///   perform rounding before calling this function.
        /// </para>
        /// <para>
        /// - Range and overflow: There is no built-in runtime check for overflow when converting the constructed
        ///   100-ns duration to the target type. If the resulting count does not fit in the representation of
        ///   <c>DurationT::rep</c> the behavior is implementation-defined (possible wrap/overflow). Callers should
        ///   ensure the tick value is within acceptable bounds before converting when overflow must be avoided.
        /// </para>
        /// <para>Thread-safety: the function is pure and has no side-effects.</para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Convert TimeSpan ticks to std::chrono::milliseconds
        /// long long ticks = ts.Ticks();
        /// auto ms = TimeSpan::TicksToDuration<std::chrono::milliseconds>(ticks);
        ///
        /// // Default template (system_clock::duration)
        /// auto dur = TimeSpan::TicksToDuration( ticks );
        /// </code>
        /// </example>
        template<typename DurationT = std::chrono::system_clock::duration>
            requires IsStdChronoDuration < DurationT >
        static constexpr DurationT TicksToDuration( long long ticks )
        {
            return std::chrono::duration_cast<DurationT>( std::chrono::duration<long long, std::ratio<1, 10000000>>( ticks ) );
        }


        /// <summary>
        /// Initializes a new <see cref="TimeSpan"/> representing a zero-length interval.
        /// </summary>
        /// <remarks>
        /// - This constexpr, noexcept constructor sets the internal tick count (<c>ticks_</c>) to zero,
        ///   which corresponds to an interval of 0 (see <see cref="TimeSpan::Zero"/>).
        /// - The object is trivially constructible and safe for use in constant-evaluated contexts.
        /// - No allocation or I/O is performed and no exceptions are thrown.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Default constructed TimeSpan is zero
        /// TimeSpan t;                // t.Ticks() == 0
        /// auto z = TimeSpan::Zero(); // equivalent
        /// </code>
        /// </example>
        constexpr TimeSpan( ) noexcept
            : ticks_( 0 )
        { }

        /// <summary>
        /// Initializes a new <see cref="TimeSpan"/> with the specified number of ticks.
        /// </summary>
        /// <param name="ticks">
        /// The number of ticks to store in the TimeSpan. One tick equals 100 nanoseconds (0.1 microsecond).
        /// The value may be negative to represent a negative time interval.
        /// </param>
        /// <remarks>
        /// - This constructor is declared <c>constexpr</c> so it can be used in constant-evaluated contexts.
        /// - No range validation is performed by this constructor; callers that need to ensure the value
        ///   fits DateTime-related ranges should validate against <see cref="TimeBase::MinTicks"/> /
        ///   <see cref="TimeBase::MaxTicks"/> or use higher-level factory functions.
        /// - The stored value is the internal representation used throughout the library and matches the
        ///   100-nanosecond tick unit used by Windows FILETIME/SYSTEMTIME conversions.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Create a TimeSpan representing one millisecond:
        /// TimeSpan oneMs( TimeSpan::TicksPerMillisecond );
        /// </code>
        /// </example>
        constexpr explicit TimeSpan( long long ticks )
            : ticks_( ticks )
        { }

        /// <summary>
        /// Constructs a <see cref="TimeSpan"/> from a `std::chrono` duration by converting the duration
        /// to the internal tick representation (1 tick = 100 ns).
        /// </summary>
        /// <typeparam name="DurationT">The `std::chrono::duration` type. Must satisfy `IsStdChronoDuration`.</typeparam>
        /// <param name="duration">The duration to convert. May be negative to represent a negative interval.</param>
        /// <remarks>
        /// - Conversion is implemented by `DurationToTicks` which uses `std::chrono::duration_cast` to a
        ///   duration with a period of 1/10,000,000 (100 ns) and stores the resulting count in the internal
        ///   tick field (`ticks_`).
        /// - `std::chrono::duration_cast` truncates toward zero; fractional sub-tick parts are discarded.
        /// - This constructor is `constexpr` and `noexcept`, and performs no runtime range checking. Callers
        ///   that require validation against `TimeBase::MinTicks`/`TimeBase::MaxTicks` should perform those
        ///   checks before constructing or use higher-level helpers.
        /// - The tick unit matches Windows `FILETIME`/`SYSTEMTIME` 100-nanosecond units; when passing timeouts to
        ///   Windows APIs that expect milliseconds (for example `WaitForSingleObject`) convert ticks to milliseconds
        ///   (divide by `TicksPerMillisecond`) and clamp to the API's range (use `TimeSpan::ToTimeout()`).
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Construct from std::chrono::milliseconds
        /// TimeSpan ts = TimeSpan( std::chrono::milliseconds(1500) ); // 1.5 seconds
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr explicit TimeSpan( const DurationT& duration ) noexcept
            : ticks_( DurationToTicks( duration ) )
        { }

        /// <summary>
        /// Initializes a new <see cref="TimeSpan"/> that represents the interval specified by hours, minutes and seconds.
        /// </summary>
        /// <param name="hours">
        /// Number of whole hours in the interval. The value may be negative to produce a negative interval.
        /// </param>
        /// <param name="minutes">
        /// Number of whole minutes in the interval. Typical callers pass values in 0..59; values outside that range
        /// are accepted and will be incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <param name="seconds">
        /// Number of whole seconds in the interval. Typical callers pass values in 0..59; values outside that range
        /// are accepted and will be incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <remarks>
        /// - The constructor computes the internal tick count by calling `TimeToTicks(0, hours, minutes, seconds)` and
        ///   stores the resulting tick count in the object (<c>ticks_</c>).
        /// - The unit used is ticks where 1 tick = 100 nanoseconds. The combination of components is converted to
        ///   total milliseconds and then to ticks.
        /// - If the resulting total milliseconds falls outside the representable range (see <c>TimeBase::MaxMilliSeconds</c>
        ///   / <c>TimeBase::MinMilliSeconds</c>), an <see cref="ArgumentOutOfRangeException"/> is thrown.
        /// - This constructor does not perform per-field range normalization (for example hours >= 24); callers that need
        ///   normalized component semantics should normalize before calling.
        /// </remarks>
        /// <exception cref="ArgumentOutOfRangeException">Thrown when the computed total interval is outside the allowed range.</exception>
        /// <example>
        /// <code language="cpp">
        /// // 1 hour 30 minutes:
        /// TimeSpan ts(1, 30, 0);
        /// </code>
        /// </example>
        TimeSpan( int hours, int minutes, int seconds )
            : ticks_( TimeToTicks( 0, hours, minutes, seconds ) )
        { }

        /// <summary>
        /// Initializes a new <see cref="TimeSpan"/> that represents the interval specified by days, hours, minutes and seconds.
        /// </summary>
        /// <param name="days">
        /// Number of whole days in the interval. May be negative to represent a negative interval.
        /// </param>
        /// <param name="hours">
        /// Number of whole hours in the interval. Typical callers pass values in 0..23; values outside that range
        /// are accepted and will be incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <param name="minutes">
        /// Number of whole minutes in the interval. Typical callers pass values in 0..59; values outside that range
        /// are accepted and will be incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <param name="seconds">
        /// Number of whole seconds in the interval. Typical callers pass values in 0..59; values outside that range
        /// are accepted and will be incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <remarks>
        /// - The constructor calls <see cref="TimeToTicks(int,int,int,int)"/> to compute the internal tick count
        ///   (1 tick = 100 nanoseconds) from the supplied components. The combination is converted to total milliseconds
        ///   and then to ticks.
        /// - No per-field normalization is performed; if callers need normalized fields (for example hours >= 24)
        ///   they should normalize before calling this constructor.
        /// - The resulting tick value corresponds to the same 100-nanosecond unit used by Windows <c>FILETIME</c>.
        ///   When passing intervals to Windows APIs that accept milliseconds (for example <c>WaitForSingleObject</c>),
        ///   convert ticks to milliseconds (divide by <see cref="TicksPerMillisecond"/>) and clamp to the API's range
        ///   (use <see cref="TimeSpan::ToTimeout"/> for a safe conversion to a DWORD timeout).
        /// - The constructor is not constexpr and may throw when the computed total interval is out of range.
        /// - Thread-safety: the constructor is pure (no global state) and safe to call concurrently.
        /// </remarks>
        /// <exception cref="ArgumentOutOfRangeException">Thrown when the computed total interval in milliseconds is outside the allowed range.</exception>
        /// <example>
        /// <code language="cpp">
        /// // Two days, 3 hours, 15 minutes and 30 seconds:
        /// TimeSpan ts(2, 3, 15, 30);
        /// </code>
        /// </example>
        TimeSpan( int days, int hours, int minutes, int seconds )
            : ticks_( TimeToTicks( days, hours, minutes, seconds ) )
        { }

        /// <summary>
        /// Initializes a new <see cref="TimeSpan"/> that represents the interval specified by
        /// days, hours, minutes, seconds and milliseconds.
        /// </summary>
        /// <param name="days">
        /// Number of whole days in the interval. May be negative to represent a negative interval.
        /// </param>
        /// <param name="hours">
        /// Number of whole hours in the interval. Typical callers use 0..23; values outside that range
        /// are accepted and incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <param name="minutes">
        /// Number of whole minutes in the interval. Typical callers use 0..59; values outside that range
        /// are accepted and incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <param name="seconds">
        /// Number of whole seconds in the interval. Typical callers use 0..59; values outside that range
        /// are accepted and incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <param name="milliseconds">
        /// Number of whole milliseconds in the interval. Typical callers use 0..999; values outside that range
        /// are accepted and incorporated into the total interval arithmetic.
        /// </param>
        /// <remarks>
        /// - The constructor computes the internal tick count by calling
        ///   <see cref="TimeToTicks(int,int,int,int,int)"/> and stores the resulting tick count in <c>ticks_</c>.
        /// - Units: 1 tick = 100 nanoseconds. The supplied components are combined to total milliseconds,
        ///   then converted to ticks (no fractional-millisecond rounding is performed).
        /// - No per-field normalization is performed (for example hours >= 24); callers that require normalized
        ///   component semantics should normalize before calling this constructor.
        /// - The resulting tick value corresponds to the 100-nanosecond units used by Windows <c>FILETIME</c>.
        ///   When passing intervals to Windows APIs that accept milliseconds (for example <c>WaitForSingleObject</c>),
        ///   convert ticks to milliseconds (divide by <see cref="TicksPerMillisecond"/>) and clamp to the API's range
        ///   (use <see cref="TimeSpan::ToTimeout"/> for a safe conversion to a DWORD timeout).
        /// - This constructor may throw when the computed total interval is out of the representable range.
        /// - Thread-safety: the constructor performs only local computations and is safe to call concurrently.
        /// </remarks>
        /// <exception cref="ArgumentOutOfRangeException">Thrown when the computed total interval in milliseconds is outside the allowed range.</exception>
        /// <example>
        /// <code language="cpp">
        /// // 1 day, 2 hours, 3 minutes, 4 seconds, 500 milliseconds
        /// TimeSpan ts(1, 2, 3, 4, 500);
        /// </code>
        /// </example>
        TimeSpan( int days, int hours, int minutes, int seconds, int milliseconds )
            : ticks_( TimeToTicks( days, hours, minutes, seconds, milliseconds ) )
        { }

        /// <summary>
        /// Initializes a new <see cref="TimeSpan"/> that represents the interval specified by
        /// days, hours, minutes, seconds and a fractional second component.
        /// </summary>
        /// <param name="days">
        /// Number of whole days in the interval. May be negative to represent a negative interval.
        /// </param>
        /// <param name="hours">
        /// Number of whole hours in the interval. Typical callers use 0..23; values outside that range
        /// are accepted and will be incorporated into the total interval arithmetic (no per-field normalization is performed).
        /// </param>
        /// <param name="minutes">
        /// Number of whole minutes in the interval. Typical callers use 0..59; values outside that range
        /// are accepted and will be incorporated into the total interval arithmetic.
        /// </param>
        /// <param name="seconds">
        /// Number of whole seconds in the interval. Typical callers use 0..59; values outside that range
        /// are accepted and will be incorporated into the total interval arithmetic.
        /// </param>
        /// <param name="fraction">
        /// Fractional seconds expressed in seconds (for example, 0.5 represents 500 ms). The fractional value is
        /// converted to ticks by multiplying with <c>TicksPerSecond</c> and truncating toward zero (no rounding).
        /// The sign of <paramref name="fraction"/> contributes to the overall interval sign when combined with the other components.
        /// </param>
        /// <remarks>
        /// <para>
        /// - This constructor delegates to <see cref="TimeToTicks(int,int,int,int,double)"/> to compute the internal
        ///   tick count (1 tick = 100 ns) and stores the resulting value in <c>ticks_</c>.
        /// - No per-field normalization is performed (for example hours >= 24); the components are combined arithmetically
        ///   into a total interval before conversion to ticks.
        /// - Fractional seconds are truncated to whole ticks (no rounding). Callers that require a specific rounding policy
        ///   should convert/round prior to construction or construct from ticks directly.
        /// - Range &amp; overflow: if the computed tick count is outside the representable range
        ///   (<see cref="TimeBase::MinTicks"/> .. <see cref="TimeBase::MaxTicks"/>), an <see cref="ArgumentOutOfRangeException"/>
        ///   is thrown by <see cref="TimeToTicks(int,int,int,int,double)"/>.
        /// - Thread-safety: constructor performs only local computations and is safe to call concurrently.
        /// </para>
        /// </remarks>
        /// <exception cref="ArgumentOutOfRangeException">Thrown when the computed total interval in ticks is outside the allowed range.</exception>
        /// <example>
        /// <code language="cpp">
        /// // 1 day, 2 hours, 3 minutes, 4.5 seconds
        /// TimeSpan ts(1, 2, 3, 4, 0.5);
        /// </code>
        /// </example>
        TimeSpan( int days, int hours, int minutes, int seconds, double fraction )
            : ticks_( TimeToTicks( days, hours, minutes, seconds, fraction ) )
        { }

        /// <summary>
        /// Computes a non-cryptographic hash value for this <see cref="TimeSpan"/> instance.
        /// </summary>
        /// <returns>
        /// A <c>size_t</c> hash value derived from the internal tick count (<c>ticks_</c>).
        /// The value is suitable for use with <c>std::hash</c>-based containers (for example <c>std::unordered_map</c>
        /// and <c>std::unordered_set</c>).
        /// </returns>
        /// <remarks>
        /// <para>
        /// Implementation details:
        /// - The function mixes the 64-bit tick value using a well-known 64-bit integer mixing/finalizer
        ///   sequence (the SplitMix64 / fmix64 style finalizer constants) to produce a uniformly-distributed
        ///   64-bit result before returning it as <c>size_t</c>.
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, allowing compile-time evaluation where possible.
        /// - The hash is deterministic and repeatable within the same platform and implementation, but it is
        ///   intentionally non-cryptographic. Do not use this value for security-sensitive purposes.
        /// - On platforms where <c>size_t</c> is narrower than 64 bits (for example 32-bit targets), the
        ///   computed 64-bit mixed value will be truncated to fit <c>size_t</c>. The project targets x64 by default,
        ///   so truncation is not expected in typical builds.
        /// - The function reads only object-local state (<c>ticks_</c>) and has no side-effects; it is thread-safe.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Use TimeSpan in an unordered_set (std::hash specialization is provided in this header).
        /// std::unordered_set<TimeSpan> set;
        /// set.insert( TimeSpan::FromSeconds(1.0) );
        /// </code>
        /// </example>
        constexpr size_t hash( ) const noexcept
        {
            auto x = ( ticks_ ^ ( ticks_ >> 30 ) ) * UINT64_C( 0xbf58476d1ce4e5b9 );
            x = ( x ^ ( x >> 27 ) ) * UINT64_C( 0x94d049bb133111eb );
            x = x ^ ( x >> 31 );
            return x;
        }

        /// <summary>
        /// Retrieves the amount of time the calling thread has executed in kernel mode and
        /// returns that time as a <see cref="TimeSpan"/> (ticks = 100 ns).
        /// </summary>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing the cumulative kernel-mode execution time for
        /// the calling thread. The value is constructed directly from the Windows <c>FILETIME</c>
        /// kernel-time value returned by <c>GetThreadTimes</c>, which reports time in 100-nanosecond
        /// intervals (the same tick unit used by this library).
        /// </returns>
        /// <remarks>
        /// <para>
        /// This function calls the Windows API <c>GetThreadTimes</c> with a pseudo-handle returned
        /// by <c>GetCurrentThread()</c>. The API fills four <c>FILETIME</c> values:
        /// creation time, exit time, kernel time and user time. Each <c>FILETIME</c> is a 64-bit
        /// value expressing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
        /// The implementation here reinterprets the kernel-time <c>FILETIME</c> as a 64-bit
        /// integer and constructs a <see cref="TimeSpan"/> directly from that tick count.
        /// </para>
        /// <para>
        /// Platform/availability: this function requires the Windows API <c>GetThreadTimes</c>
        /// and therefore is only meaningful on Windows. The call uses the calling thread's
        /// pseudo-handle and does not require closing a handle.
        /// </para>
        /// <para>
        /// Thread-safety: the function queries the calling thread's kernel time and has no
        /// side-effects; it is safe to call from multiple threads concurrently.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Example: obtain kernel time for the calling thread and print milliseconds
        /// auto kt = TimeSpan::KernelTime();
        /// std::cout &lt;&lt; "Kernel time (ms): " &lt;&lt; kt.ToMilliseconds() &lt;&lt; std::endl;
        ///
        /// // Equivalent direct Windows usage (illustrative) replaced by the above:
        /// // FILETIME creation, exit, kernel, user;
        /// // if ( GetThreadTimes( GetCurrentThread(), &creation, &exit, &kernel, &user ) )
        /// // {
        /// //     ULARGE_INTEGER ku{};
        /// //     ku.LowPart = kernel.dwLowDateTime;
        /// //     ku.HighPart = kernel.dwHighDateTime;
        /// //     TimeSpan kernelTime( static_cast<long long>( ku.QuadPart ) );
        /// //     std::cout << "Kernel time (ms): " << kernelTime.ToMilliseconds() << std::endl;
        /// // }
        /// </code>
        /// </example>
        static TimeSpan KernelTime( )
        {
            Int64 creationTime;
            Int64 exitTime;
            Int64 kernelTime;
            Int64 userTime;
            GetThreadTimes( GetCurrentThread( ), ( LPFILETIME )&creationTime, ( LPFILETIME )&exitTime, ( LPFILETIME )&kernelTime, ( LPFILETIME )&userTime );
            return TimeSpan( kernelTime );
        }

        /// <summary>
        /// Retrieves the amount of time the calling thread has executed in user mode and
        /// returns that time as a <see cref="TimeSpan"/> (ticks = 100 ns).
        /// </summary>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing the cumulative user-mode execution time for
        /// the calling thread. The value is constructed from the 64-bit FILETIME value returned
        /// by <c>GetThreadTimes</c> for the thread's user-time field. FILETIME values are expressed
        /// in 100-nanosecond units (the same tick unit used by this library).
        /// </returns>
        /// <remarks>
        /// <para>
        /// This function calls the Windows API <c>GetThreadTimes</c> using the calling thread's
        /// pseudo-handle returned by <c>GetCurrentThread()</c>. The API expects four <c>LPFILETIME</c>
        /// pointers for creation time, exit time, kernel time and user time. The implementation here
        /// reinterprets local 64-bit integers as <c>FILETIME</c> structures (via pointer cast) and
        /// constructs a <see cref="TimeSpan"/> from the resulting 64-bit tick count.
        /// </para>
        /// <para>
        /// Platform: requires Windows API <c>GetThreadTimes</c>; meaningful only on Windows targets.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Preferred usage: query user-mode CPU time for the calling thread
        /// TimeSpan userTime = TimeSpan::UserTime();
        /// std::cout &lt;&lt; "User time (ms): " &lt;&lt; userTime.ToMilliseconds() &lt;&lt; std::endl;
        ///
        /// // Equivalent low-level Windows usage (illustrative; the above call replaces this):
        /// // FILETIME creation, exit, kernel, user;
        /// // if ( GetThreadTimes( GetCurrentThread(), &creation, &exit, &kernel, &user ) )
        /// // {
        /// //     ULARGE_INTEGER u{};
        /// //     u.LowPart = user.dwLowDateTime;
        /// //     u.HighPart = user.dwHighDateTime;
        /// //     TimeSpan userTimeDirect( static_cast<long long>( u.QuadPart ) );
        /// //     std::cout << "User time (ms): " << userTimeDirect.ToMilliseconds() << std::endl;
        /// // }
        /// </code>
        /// </example>
        static TimeSpan UserTime( )
        {
            Int64 creationTime;
            Int64 exitTime;
            Int64 kernelTime;
            Int64 userTime;
            GetThreadTimes( GetCurrentThread( ), (LPFILETIME)&creationTime, (LPFILETIME)&exitTime, (LPFILETIME)&kernelTime, (LPFILETIME)&userTime );
            return TimeSpan( userTime );
        }

        /// <summary>
        /// Gets the raw tick count stored by this <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// The number of ticks (1 tick = 100 nanoseconds) represented by this <see cref="TimeSpan"/>.
        /// The returned value may be negative to represent a negative interval.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The value is the internal representation used throughout the library and matches the 100-nanosecond
        ///   unit used by Windows <c>FILETIME</c> and .NET <c>TimeSpan</c>.
        /// - This function is <c>constexpr</c> and <c>noexcept</c>; it performs no allocation or I/O.
        /// - The call has no side effects and is safe to use concurrently from multiple threads.
        /// - To convert ticks to milliseconds, divide the result by <see cref="TicksPerMillisecond"/> or
        ///   use the convenience functions such as <see cref="ToMilliseconds"/> / <see cref="TotalMilliseconds"/>.
        /// - When passing timeouts to Win32 APIs that expect a DWORD timeout (milliseconds), convert and clamp
        ///   appropriately (see <see cref="ToTimeout"/>).
        /// </para>
        /// </remarks>
        constexpr long long Ticks( ) const noexcept
        {
            return ticks_;
        }

        /// <summary>
        /// Gets the number of whole days represented by this <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// The total number of whole days in the interval, computed as <c>ticks_ / TicksPerDay</c>.
        /// The returned value may be negative for negative intervals. If the computed day count does not
        /// fit in an <c>int</c> the result is clamped to <c>std::numeric_limits<int>::max()</c> or
        /// <c>std::numeric_limits<int>::min()</c> to avoid narrowing-induced implementation-defined behavior.
        /// </returns>
        /// <remarks>
        /// - This function performs integer division and discards fractional day parts (truncates toward zero).
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, has O(1) complexity and no side-effects.
        /// - Use <see cref="ToDays"/> if the full 64-bit day count is required.
        /// </remarks>
        constexpr int Days( ) const noexcept
        {
            const long long d = ticks_ / TicksPerDay;
            constexpr long long IntMaxLL = static_cast< long long >( std::numeric_limits<int>::max( ) );
            constexpr long long IntMinLL = static_cast< long long >( std::numeric_limits<int>::min( ) );

            const long long maskPos = -static_cast< long long >( d > IntMaxLL );
            const long long maskNeg = -static_cast< long long >( d < IntMinLL );

            const long long selected = ( d & ~( maskPos | maskNeg ) )
                | ( IntMaxLL & maskPos )
                | ( IntMinLL & maskNeg );

            return static_cast< int >( selected );
        }

        /// <summary>
        /// Gets the hours component of this <see cref="TimeSpan"/> within a 24-hour day.
        /// </summary>
        /// <returns>
        /// The number of whole hours represented by this <see cref="TimeSpan"/> modulo 24.
        /// - For non-negative intervals the result is in the range 0..23.
        /// - For negative intervals the result may be negative (range -23..23) because the computation uses
        ///   integer division and the signed remainder operator.
        /// </returns>
        /// <remarks>
        /// - Computation: the value is computed as <c>static_cast<int>((ticks_ / TicksPerHour) % 24)</c>.
        ///   Integer division discards any fractional hour (truncates toward zero), so fractional-hour parts are lost.
        /// - The returned value is the hour component of the interval when expressed in days/hours/minutes/seconds:
        ///   it does not represent the total hours in the interval (use <see cref="TotalHours"/> for that).
        /// - For negative intervals the hour component follows C++ signed remainder semantics; callers that require
        ///   a non-negative hour component for negative intervals should normalize the value explicitly.
        /// - This function is <c>constexpr</c> and <c>noexcept</c> and has no side-effects.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 36 hours -> Days() == 1, Hours() == 12
        /// TimeSpan ts = TimeSpan( 0, 36, 0, 0 );
        /// int hours = ts.Hours(); // 12
        ///
        /// // -3 hours -> Days() == 0, Hours() == -3
        /// TimeSpan neg = TimeSpan::FromHours( -3.0 );
        /// int negHours = neg.Hours(); // -3
        /// </code>
        /// </example>
        constexpr int Hours( ) const noexcept
        {
            const long long rem = ticks_ % TicksPerDay;
            return static_cast< int >( rem / TicksPerHour );
        }

        /// <summary>
        /// Gets the minutes component of this <see cref="TimeSpan"/> within an hour.
        /// </summary>
        /// <returns>
        /// The number of whole minutes represented by this <see cref="TimeSpan"/> modulo 60.
        /// - For non-negative intervals the result is in the range 0..59.
        /// - For negative intervals the result may be negative (range -59..59) because the computation uses
        ///   integer division and the signed remainder operator.
        /// </returns>
        /// <remarks>
        /// - Computation: the value is computed as <c>static_cast<int>((ticks_ / TicksPerMinute) % 60)</c>.
        ///   Integer division discards any fractional minute (truncates toward zero), so fractional-minute parts are lost.
        /// - The returned value is the minute component when the interval is expressed as days/hours/minutes/seconds:
        ///   it does not represent the total minutes in the interval (use <see cref="TotalMinutes"/> for that).
        /// - For negative intervals the minute component follows C++ signed remainder semantics; callers that require
        ///   a non-negative minute component for negative intervals should normalize the value explicitly.
        /// - This function is <c>constexpr</c> and <c>noexcept</c> and has no side-effects.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 90 minutes -> 1 hour 30 minutes
        /// TimeSpan ts = TimeSpan::FromMinutes( 90.0 );
        /// int minutes = ts.Minutes(); // 30
        /// int hours = ts.Hours();     // 1
        /// </code>
        /// </example>
        constexpr int Minutes( ) const noexcept
        {
            const long long rem = ticks_ % TicksPerHour;
            return static_cast< int >( rem / TicksPerMinute );
        }

        /// <summary>
        /// Gets the seconds component of this <see cref="TimeSpan"/> within a minute.
        /// </summary>
        /// <returns>
        /// The number of whole seconds represented by this <see cref="TimeSpan"/> modulo 60.
        /// - For non-negative intervals the result is in the range 0..59.
        /// - For negative intervals the result may be negative (range -59..59) because the computation uses
        ///   integer division and the signed remainder operator.
        /// </returns>
        /// <remarks>
        /// - Computation: the value is computed as <c>static_cast<int>((ticks_ / TicksPerSecond) % 60)</c>.
        ///   Integer division discards any fractional second (truncates toward zero), so fractional-second parts are lost.
        /// - The returned value is the seconds component when the interval is expressed as
        ///   days/hours/minutes/seconds; it does not represent the total seconds in the interval
        ///   (use <see cref="TotalSeconds"/> or <see cref="ToSeconds"/> for that).
        /// - For negative intervals the seconds component follows C++ signed remainder semantics; callers that require
        ///   a non-negative seconds component for negative intervals should normalize the value explicitly.
        /// - This function is <c>constexpr</c> and <c>noexcept</c> and has no side-effects.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 90 seconds -> 1 minute 30 seconds
        /// TimeSpan ts = TimeSpan::FromSeconds( 90.0 );
        /// int seconds = ts.Seconds(); // 30
        /// int minutes = ts.Minutes(); // 1
        /// </code>
        /// </example>
        constexpr int Seconds( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerSecond ) % 60 );
        }

        /// <summary>
        /// Gets the milliseconds component of this <see cref="TimeSpan"/> within a second.
        /// </summary>
        /// <returns>
        /// The number of whole milliseconds represented by this <see cref="TimeSpan"/> modulo 1000.
        /// - For non-negative intervals the result is in the range 0..999.
        /// - For negative intervals the result may be negative (range -999..999) because the computation uses
        ///   integer division and the signed remainder operator.
        /// </returns>
        /// <remarks>
        /// - Computation: the value is computed as <c>static_cast<int>((ticks_ / TicksPerMillisecond) % 1000)</c>.
        ///   Integer division discards any fractional millisecond (truncates toward zero), so fractional-millisecond parts are lost.
        /// - The returned value is the millisecond component when the interval is expressed as
        ///   days/hours/minutes/seconds/milliseconds; it does not represent the total milliseconds in the interval
        ///   (use <see cref="ToMilliseconds"/> or <see cref="TotalMilliseconds"/> for that).
        /// - For negative intervals the millisecond component follows C++ signed remainder semantics; callers that require
        ///   a non-negative millisecond component for negative intervals should normalize the value explicitly.
        /// - This function is <c>constexpr</c> and <c>noexcept</c> and has no side-effects.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1500 milliseconds -> 1 second 500 milliseconds
        /// TimeSpan ts = TimeSpan::FromMilliseconds(1500.0);
        /// int ms = ts.Milliseconds(); // 500
        /// </code>
        /// </example>
        constexpr int Milliseconds( ) const noexcept
        {
            const long long rem = ticks_ % TicksPerSecond;
            return static_cast< int >( rem / TicksPerMillisecond );
        }

        /// <summary>
        /// Gets the microseconds component of this <see cref="TimeSpan"/> within the current second.
        /// </summary>
        /// <returns>
        /// The number of whole microseconds within the second.
        /// For non-negative intervals the result is in the range 0..999999.
        /// For negative intervals the value follows C++ signed-remainder semantics and may be negative (range -999999..999999).
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Implementation extracts the tick remainder modulo <c>TicksPerSecond</c> and converts that remainder to microseconds
        ///   by dividing by <c>TicksPerMicrosecond</c>. This keeps intermediate values bounded (within one second) and avoids
        ///   large intermediate quotients (safer and often more optimizer-friendly than computing <c>(ticks_ / TicksPerMicrosecond) % 1000000</c>).
        /// - The method is <c>constexpr</c> and <c>noexcept</c>, has constant time complexity O(1), and has no side-effects.
        /// - For formatting or display where a non-negative component is required for negative intervals, callers should normalize
        ///   the interval (for example by taking the absolute value) before extracting components.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromMilliseconds(1500.123); // 1.500123 seconds
        /// int us = ts.Microseconds(); // 500123 for positive ts
        /// </code>
        /// </example>
        constexpr int Microseconds( ) const noexcept
        {
            const long long rem = ticks_ % TicksPerSecond;
            return static_cast< int >( rem / TicksPerMicrosecond );
        }

        /// <summary>
        /// Gets the nanoseconds component of this <see cref="TimeSpan"/> within the current second.
        /// </summary>
        /// <returns>
        /// The number of whole nanoseconds within the second, expressed as an <c>int</c>.
        /// - For non-negative intervals the value is in the range 0..999,999,900 and is always a multiple of 100 (ticks are 100 ns).
        /// - For negative intervals the value follows C++ signed-remainder semantics and may be negative (range -999,999,900..999,999,900).
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Implementation: extracts the tick remainder modulo <c>TicksPerSecond</c> and multiplies that remainder by 100
        ///   to convert ticks (100 ns units) to nanoseconds. Each tick equals 100 nanoseconds.
        /// - No rounding is performed; sub-tick precision is not representable (nanosecond result is always a multiple of 100).
        /// - Safety and overflow: intermediate values are bounded (|rem| &lt; <c>TicksPerSecond</c>), so multiplying by 100 fits comfortably
        ///   in a 64-bit signed integer and the final <c>int</c> conversion is safe because the result magnitude &lt; 1e9 &lt;&lt; <c>INT_MAX</c>.
        /// - Semantics for negative intervals: the function returns a signed nanosecond component. If a non-negative component is required
        ///   for display of negative intervals, normalize the interval (for example, take the absolute value or decompose using normalized helpers).
        /// - Complexity: O(1). The method is <c>constexpr</c>, <c>noexcept</c> and has no side-effects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1.500000900 seconds -> nanoseconds component = 900
        /// TimeSpan ts = TimeSpan::FromMilliseconds(1500.0);
        /// // add 9 ticks (9 * 100 ns = 900 ns)
        /// ts += 9;
        /// int ns = ts.Nanoseconds(); // 900
        /// </code>
        /// </example>
        constexpr int Nanoseconds( ) const noexcept
        {
            const long long rem = ticks_ % TicksPerSecond;
            return static_cast< int >( rem * 100 );
        }





        /// <summary>
        /// Gets the number of whole days represented by this <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// The total number of whole days in the interval, computed as <c>ticks_ / TicksPerDay</c>.
        /// The returned value may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - Computation: integer division is used and fractional day parts are discarded (truncated toward zero).
        /// - Use <see cref="TotalDays"/> to obtain the interval expressed as a fractional number of days.
        /// - The value is derived from the internal tick unit (1 tick = 100 nanoseconds). When interoperating
        ///   with OS APIs that expect timeouts in milliseconds, convert ticks to milliseconds (divide by
        ///   <see cref="TicksPerMillisecond"/>) and clamp as appropriate (see <see cref="ToTimeout"/>).
        /// - This function is <c>constexpr</c>, <c>noexcept</c> and has no side-effects; it is safe to call from multiple threads.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 36 hours -> 1 whole day
        /// TimeSpan ts = TimeSpan::FromHours(36.0);
        /// long long days = ts.ToDays(); // 1
        /// </code>
        /// </example>
        constexpr long long ToDays( ) const noexcept
        {
            return ticks_ / TicksPerDay;
        }

        /// <summary>
        /// Gets the number of whole hours represented by this <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// The total number of whole hours in the interval, computed as <c>ticks_ / TicksPerHour</c>.
        /// The returned value may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - Computation: integer division is used and fractional hour parts are discarded (truncated toward zero).
        /// - Use <see cref="TotalHours"/> to obtain the interval expressed as a fractional number of hours.
        /// - The value is derived from the internal tick unit (1 tick = 100 nanoseconds). When interoperating
        ///   with OS APIs that expect timeouts in milliseconds, convert ticks to milliseconds (divide by
        ///   <see cref="TicksPerMillisecond"/>) and clamp as appropriate (see <see cref="ToTimeout"/>).
        /// - This function is <c>constexpr</c>, <c>noexcept</c> and has no side-effects; it is safe to call from multiple threads.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 36 hours -> 36 whole hours
        /// TimeSpan ts = TimeSpan::FromHours(36.0);
        /// long long hours = ts.ToHours(); // 36
        /// // For components use Days()/Hours(): Days()==1, Hours()==12
        /// </code>
        /// </example>
        constexpr long long ToHours( ) const noexcept
        {
            return ticks_ / TicksPerHour;
        }

        /// <summary>
        /// Gets the number of whole seconds represented by this <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// The total number of whole seconds in the interval, computed as <c>ticks_ / TicksPerSecond</c>.
        /// The returned value may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - Computation uses integer division; any fractional second portion is discarded (truncated toward zero).
        /// - For a fractional number of seconds use <see cref="TotalSeconds"/> which returns a <c>double</c>.
        /// - The internal unit is ticks (1 tick = 100 nanoseconds). Converting to seconds loses sub-second precision.
        /// - No additional overflow checking is performed; when interoperating with APIs that expect different units
        ///   (for example Windows timeouts in milliseconds) convert and clamp appropriately (see <see cref="ToTimeout"/>).
        /// - This function is <c>constexpr</c>, <c>noexcept</c> and has no side-effects; it is safe to call concurrently.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 90 seconds -> ToSeconds() == 90
        /// TimeSpan ts = TimeSpan::FromSeconds(90.0);
        /// long long seconds = ts.ToSeconds(); // 90
        /// </code>
        /// </example>
        constexpr long long ToSeconds( ) const noexcept
        {
            return ticks_ / TicksPerSecond;
        }

        /// <summary>
        /// Gets the number of whole milliseconds represented by this <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// The total number of whole milliseconds in the interval, computed as <c>ticks_ / TicksPerMillisecond</c>.
        /// The returned value may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - Computation uses integer division; any fractional millisecond portion is discarded (truncated toward zero).
        /// - For a fractional number of milliseconds use <see cref="TotalMilliseconds"/> which returns a <c>double</c>
        ///   and applies clamping to the representable range.
        /// - The internal unit is ticks (1 tick = 100 nanoseconds). Converting to milliseconds loses sub-millisecond precision.
        /// - No additional overflow checking is performed by this method. When interoperating with APIs that expect
        ///   different units (for example Windows timeouts in milliseconds) convert and clamp appropriately (see <see cref="ToTimeout"/>).
        /// - This function is <c>constexpr</c>, <c>noexcept</c> and has no side-effects; it is safe to call concurrently.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1500 milliseconds -> ToMilliseconds() == 1500
        /// TimeSpan ts = TimeSpan::FromMilliseconds(1500.0);
        /// long long ms = ts.ToMilliseconds(); // 1500
        /// </code>
        /// </example>
        constexpr long long ToMilliseconds( ) const noexcept
        {
            return ticks_ / TicksPerMillisecond;
        }

        /// <summary>
        /// Gets the number of whole microseconds represented by this <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// The total number of whole microseconds in the interval, computed as <c>ticks_ / TicksPerMicrosecond</c>.
        /// The returned value may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - Computation: integer division is used and any fractional microsecond portion is discarded (truncated toward zero).
        /// - Units: 1 tick == 100 nanoseconds, and <c>TicksPerMicrosecond</c> == 10, so the result is effectively <c>ticks_ / 10</c>.
        /// - Range & overflow: no runtime overflow checking is performed. If the underlying tick count is large enough
        ///   that the computed microsecond value does not fit in a 64-bit signed integer, behavior depends on the platform
        ///   (possible wrap/overflow). Callers that require guaranteed range safety must validate before calling.
        /// - Interoperability: most Windows wait/timeout APIs (for example __WaitForSingleObject__, __Sleep__) accept timeouts
        ///   in milliseconds (DWORD). To pass an interval derived from microseconds to such APIs, convert microseconds to
        ///   milliseconds (divide by 1000) and clamp to the API's expected range (use <see cref="ToTimeout"/> for safe conversion
        ///   to a DWORD timeout). For high-resolution timing on Windows use QueryPerformanceCounter/QueryPerformanceFrequency
        ///   or multimedia/high-resolution timer APIs as appropriate.
        /// - Thread-safety: the method is pure, has no side-effects and is safe to call concurrently.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1.5 milliseconds -> 1500 microseconds
        /// TimeSpan ts = TimeSpan::FromMilliseconds(1.5);
        /// long long us = ts.ToMicroseconds(); // 1500
        /// </code>
        /// </example>
        constexpr long long ToMicroseconds( ) const noexcept
        {
            return ticks_ / TicksPerMicrosecond;
        }


        /// <summary>
        /// Returns the total number of nanoseconds represented by this <see cref="TimeSpan"/>.
        /// The internal representation is ticks where 1 tick == 100 nanoseconds; this function
        /// converts ticks -> nanoseconds with saturation to avoid signed overflow.
        /// </summary>
        /// <returns>
        /// The interval expressed in nanoseconds (1 tick == 100 ns). If the exact product
        /// (ticks * 100) would exceed <c>std::numeric_limits<long long>::max()</c> the function
        /// returns <c>std::numeric_limits<long long>::max()</c>. If the exact product would be
        /// less than <c>std::numeric_limits<long long>::min()</c> the function returns
        /// <c>std::numeric_limits<long long>::min()</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// Implementation notes:
        /// - The routine is branchless and overflow-safe. It avoids signed overflow (undefined behavior)
        ///   by performing the multiplication in unsigned arithmetic and using branchless masks to
        ///   select either the computed product or the appropriate saturated limit.
        /// - Masks are produced from relational tests (converted to -1/0) so selection is done with
        ///   bitwise operations only. The selected unsigned result is then cast back to <c>long long</c>.
        /// - Using unsigned multiplication is well-defined modulo 2^64; selection logic guarantees the
        ///   final chosen value is representable as a signed 64-bit integer before casting.
        /// - Complexity: O(1). The method is <c>constexpr</c>, <c>noexcept</c>, has no side-effects,
        ///   and is thread-safe (reads only object-local state).
        /// - Rationale: saturating semantics are chosen to provide well-defined behavior at the limits
        ///   instead of performing a signed multiply that could invoke undefined behavior on overflow.
        /// </para>
        /// <para>
        /// Performance:
        /// - Branchless form helps reduce branch-misprediction cost on hot code paths.
        /// - Modern compilers will optimize the constant arithmetic; on x64 this pattern maps to a small
        ///   number of integer operations and logical instructions.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromMilliseconds(1500.0); // 1.5 seconds == 15,000,000 nanoseconds
        /// long long ns = ts.ToNanoseconds(); // ns == 1500000000
        /// </code>
        /// </example>
        constexpr long long ToNanoseconds( ) const noexcept
        {
            const long long ticks = ticks_;
            constexpr long long MaxDiv = std::numeric_limits<long long>::max( ) / 100;
            constexpr long long MinDiv = std::numeric_limits<long long>::min( ) / 100;

            const long long maskPos = -static_cast< long long >( ticks > MaxDiv );
            const long long maskNeg = -static_cast< long long >( ticks < MinDiv );

            const unsigned long long uprod = static_cast< unsigned long long >( ticks ) * 100ULL;

            const unsigned long long umask = ~( static_cast< unsigned long long >( maskPos ) | static_cast< unsigned long long >( maskNeg ) );

            const unsigned long long uselectedProd = uprod & umask;

            constexpr unsigned long long ullMax = static_cast< unsigned long long >( std::numeric_limits<long long>::max( ) );
            constexpr unsigned long long ullMin = static_cast< unsigned long long >( std::numeric_limits<long long>::min( ) );

            const unsigned long long uresult =
                ( uselectedProd )
                | ( ullMax & static_cast< unsigned long long >( maskPos ) )
                | ( ullMin & static_cast< unsigned long long >( maskNeg ) );

            return static_cast< long long >( uresult );
        }


        /// <summary>
        /// Gets the interval represented by this <see cref="TimeSpan"/> expressed as a fractional number of days.
        /// </summary>
        /// <returns>
        /// A <c>double</c> containing the total number of days represented by this <see cref="TimeSpan"/>.
        /// Computed as <c>static_cast<double>(ticks_) / static_cast<double>(TicksPerDay)</c>. The value preserves
        /// fractional days and may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - This method performs floating-point division and therefore returns fractional days (for example 36 hours -> 1.5 days).
        /// - The internal representation uses ticks (1 tick = 100 ns). Converting large tick counts to <c>double</c> may lose precision
        ///   due to the limits of IEEE-754 double precision; callers that require integer accuracy should use <see cref="ToDays"/> or
        ///   work with the raw tick count via <see cref="Ticks"/>.
        /// - No range clamping is performed by this method. If callers require bounded results, they should clamp the returned value themselves.
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, has no side-effects and is safe for concurrent use.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 36 hours -> 1.5 days
        /// TimeSpan ts = TimeSpan::FromHours(36.0);
        /// double days = ts.TotalDays(); // 1.5
        /// </code>
        /// </example>
        constexpr double TotalDays( ) const noexcept
        {
            const long long wholeDays = ticks_ / TicksPerDay;
            const long long remTicks = ticks_ % TicksPerDay; 
            return static_cast< double >( wholeDays ) + static_cast< double >( remTicks ) * DaysPerTick;
        }

        /// <summary>
        /// Gets the interval represented by this <see cref="TimeSpan"/> expressed as a fractional number of hours.
        /// </summary>
        /// <returns>
        /// A <c>double</c> containing the total number of hours represented by this <see cref="TimeSpan"/>.
        /// Computed as <c>static_cast<double>(ticks_) / static_cast<double>(TicksPerHour)</c>. The value preserves
        /// fractional hours and may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - This method performs floating-point division and therefore returns fractional hours (for example 90 minutes -> 1.5 hours).
        /// - The internal representation uses ticks (1 tick = 100 ns). Converting large tick counts to <c>double</c> may lose precision
        ///   due to the limits of IEEE-754 double precision; callers that require integer accuracy should use <see cref="ToHours"/> or
        ///   work with the raw tick count via <see cref="Ticks"/>.
        /// - No range clamping is performed by this method. If callers require bounded results, they should clamp the returned value themselves.
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, has no side-effects and is safe for concurrent use.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 90 minutes -> 1.5 hours
        /// TimeSpan ts = TimeSpan::FromMinutes(90.0);
        /// double hours = ts.TotalHours(); // 1.5
        /// </code>
        /// </example>
        constexpr double TotalHours( ) const noexcept
        {
            const long long wholeHours = ticks_ / TicksPerHour;
            const long long remTicks = ticks_ % TicksPerHour; 
            return static_cast< double >( wholeHours ) + static_cast< double >( remTicks ) * HoursPerTick;
        }


        /// <summary>
        /// Gets the interval represented by this <see cref="TimeSpan"/> expressed as a fractional number of minutes.
        /// </summary>
        /// <returns>
        /// A <c>double</c> containing the total number of minutes represented by this <see cref="TimeSpan"/>.
        /// Computed as <c>static_cast<double>(ticks_) / static_cast<double>(TicksPerMinute)</c>. The value preserves
        /// fractional minutes and may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - This method performs floating-point division and therefore returns fractional minutes (for example 90 seconds -> 1.5 minutes).
        /// - The internal representation uses ticks (1 tick = 100 ns). Converting large tick counts to <c>double</c> may lose precision
        ///   due to the limits of IEEE-754 double precision; callers that require integer accuracy should use <see cref="ToMinutes"/> or
        ///   work with the raw tick count via <see cref="Ticks"/>.
        /// - No range clamping is performed by this method. If callers require bounded results, they should clamp the returned value themselves.
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, has no side-effects and is safe for concurrent use.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 90 seconds -> 1.5 minutes
        /// TimeSpan ts = TimeSpan::FromSeconds(90.0);
        /// double minutes = ts.TotalMinutes(); // 1.5
        /// </code>
        /// </example>
        constexpr double TotalMinutes( ) const noexcept
        {
            const long long wholeMinutes = ticks_ / TicksPerMinute;
            const long long remTicks = ticks_ % TicksPerMinute;
            return static_cast< double >( wholeMinutes ) + static_cast< double >( remTicks ) * MinutesPerTick;
        }

        /// <summary>
        /// Gets the interval represented by this <see cref="TimeSpan"/> expressed as a fractional number of seconds.
        /// </summary>
        /// <returns>
        /// A <c>double</c> containing the total number of seconds represented by this <see cref="TimeSpan"/>.
        /// Computed as <c>static_cast<double>(ticks_) / static_cast<double>(TicksPerSecond)</c>. The value preserves
        /// fractional seconds and may be negative for negative intervals.
        /// </returns>
        /// <remarks>
        /// - This method performs floating-point division and therefore returns fractional seconds (for example 1500 milliseconds -> 1.5 seconds).
        /// - The internal representation uses ticks (1 tick = 100 ns). Converting large tick counts to <c>double</c> may lose precision
        ///   due to the limits of IEEE-754 double precision; callers that require integer accuracy should use <see cref="ToSeconds"/> or
        ///   work with the raw tick count via <see cref="Ticks"/>.
        /// - No range clamping is performed by this method. If callers require bounded results, they should clamp the returned value themselves.
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, has no side-effects and is safe for concurrent use.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 90 seconds -> 90.0
        /// TimeSpan ts = TimeSpan::FromSeconds(90.0);
        /// double seconds = ts.TotalSeconds(); // 90.0
        ///
        /// // 1500 milliseconds -> 1.5 seconds
        /// TimeSpan ts2 = TimeSpan::FromMilliseconds(1500.0);
        /// double sec = ts2.TotalSeconds(); // 1.5
        /// </code>
        /// </example>
        constexpr double TotalSeconds( ) const noexcept
        {
            const long long wholeSeconds = ticks_ / TicksPerSecond;
            const long long remTicks = ticks_ % TicksPerSecond;
            return static_cast< double >( wholeSeconds ) + static_cast< double >( remTicks ) * SecondsPerTick;
        }

        /// <summary>
        /// Gets the total number of milliseconds represented by this <see cref="TimeSpan"/> as a <c>double</c>.
        /// </summary>
        /// <returns>
        /// The total number of whole milliseconds in the interval returned as a <c>double</c>. The value may be negative
        /// for negative intervals. If the computed millisecond value is outside the representable millisecond range
        /// (<see cref="TimeBase::MinMilliSeconds"/> .. <see cref="TimeBase::MaxMilliSeconds"/>), the result is clamped
        /// to the corresponding limit.
        /// </returns>
        /// <remarks>
        /// - The function converts the internal tick count (<c>ticks_</c>; 1 tick = 100 ns) to milliseconds using
        ///   integer division: <c>result = ticks_ / TicksPerMillisecond</c>. Any fractional-millisecond component is
        ///   discarded (truncation toward zero).
        /// - This implementation is branchless: it uses bit masks derived from relational tests to select either the
        ///   computed millisecond value or the appropriate saturated limit without explicit branching.
        /// - This method is <c>constexpr</c> and <c>noexcept</c>, has no side-effects and is safe to call concurrently.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1500 milliseconds -> TotalMilliseconds() == 1500.0
        /// TimeSpan ts = TimeSpan::FromMilliseconds(1500.0);
        /// double ms = ts.TotalMilliseconds(); // 1500.0
        /// 
        /// // To obtain fractional milliseconds from ticks:
        /// double fractionalMs = static_cast<double>( ts.Ticks() ) * TimeSpan::MillisecondsPerTick;
        /// </code>
        /// </example>
        constexpr double TotalMilliseconds( ) const noexcept
        {
            const long long ms = ticks_ / TicksPerMillisecond;
            constexpr long long maxMs = MaxMilliSeconds;
            constexpr long long minMs = MinMilliSeconds;

            // masks: all-ones (-1) when condition true, 0 when false
            const long long maskPos = -static_cast< long long >( ms > maxMs ); // overflow to +inf
            const long long maskNeg = -static_cast< long long >( ms < minMs ); // overflow to -inf

            // select: when ms > maxMs -> maxMs, when ms < minMs -> minMs, otherwise ms
            const long long selected = ( ms & ~( maskPos | maskNeg ) )
                | ( maxMs & maskPos )
                | ( minMs & maskNeg );

            return static_cast< double >( selected );
        }


        /// <summary>
        /// <summary>
        /// Converts this TimeSpan to a Windows-style timeout value expressed in milliseconds.
        /// </summary>
        /// <returns>
        /// A timeout value as a <c>UInt32</c> suitable for APIs that accept a DWORD timeout (for example
        /// <see cref="WaitForSingleObject"/>, <see cref="WaitForMultipleObjects"/> and <see cref="Sleep"/>).
        /// - If the interval is larger than the special Windows value <c>INFINITE</c> (<c>0xFFFFFFFF</c>), this method returns <c>INFINITE</c>.
        /// - If the interval is negative, this method returns <c>0</c> (an immediate/non-blocking timeout).
        /// - Otherwise the method returns the interval truncated to whole milliseconds.
        /// </returns>
        /// <remarks>
        /// - The TimeSpan internal unit is ticks (100 ns). Conversion to milliseconds discards any fractional
        ///   millisecond component (integer division), so sub-millisecond precision is lost.
        /// - The returned <c>UInt32</c> is compatible with the DWORD timeout parameters used by the Windows API.
        /// - Use <c>INFINITE</c> to request an indefinite wait; this method clamps values larger than <c>INFINITE</c> to that value.
        /// - A return value of <c>0</c> means "do not wait" when passed to the Windows wait APIs (poll).
        /// - This function is noexcept and constexpr; it performs only integer arithmetic and comparisons.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromMilliseconds(500);
        /// DWORD timeout = ts.ToWindowsAPITimeout(); // 500
        /// WaitForSingleObject(handle, timeout);
        /// </code>
        /// </example>
        constexpr UInt32 ToWindowsAPITimeout( ) const noexcept
        {
            const long long millis = ticks_ / TicksPerMillisecond;
            constexpr long long inf = static_cast< long long >( INFINITE );

            // Branchless masks: -1 (all ones) when condition true, 0 when false
            const long long maskPos = -static_cast< long long >( millis > inf ); // saturate to INFINITE
            const long long maskNeg = -static_cast< long long >( millis < 0 );   // saturate to 0

            // selected = millis when in-range, INFINITE when >inf, 0 when <0
            const long long selected = ( millis & ~( maskPos | maskNeg ) )
                | ( inf & maskPos );

            return static_cast< UInt32 >( selected );
        }

        /// <summary>
        /// Compares two <see cref="TimeSpan"/> values and returns an integer that indicates
        /// their relative ordering.
        /// </summary>
        /// <param name="t1">The left operand to compare.</param>
        /// <param name="t2">The right operand to compare.</param>
        /// <returns>
        /// - A value less than zero (<c>-1</c>) when <paramref name="t1"/> is less than <paramref name="t2"/>;
        /// - Zero (<c>0</c>) when they are equal;
        /// - A value greater than zero (<c>1</c>) when <paramref name="t1"/> is greater than <paramref name="t2"/>.
        /// </returns>
        /// <remarks>
        /// - The function is <c>constexpr</c> and <c>noexcept</c> and may be evaluated in constant expressions.
        /// - Implementation uses only comparisons (no subtraction) so it cannot overflow and exhibits defined behavior
        ///   for all valid <see cref="TimeSpan"/> values.
        /// - The return values are canonicalized to -1/0/+1 using boolean-to-integer conversion:
        ///   <c>static_cast<int>(t1.ticks_ > t2.ticks_) - static_cast<int>(t1.ticks_ < t2.ticks_)</c>.
        /// - Complexity: constant time O(1). Thread-safe and has no side-effects.
        /// - Note: callers that prefer C++20 three-way comparison semantics can use the <c>operator&lt;&gt;&gt;()</c>
        ///   or the free comparison operators provided by this type.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan a = TimeSpan::FromSeconds(1.0);
        /// TimeSpan b = TimeSpan::FromSeconds(2.0);
        /// int cmp = TimeSpan::Compare(a, b); // cmp == -1
        /// if ( cmp &lt; 0 ) { /* a &lt; b */ }
        /// </code>
        /// </example>
        static constexpr int Compare( const TimeSpan& t1, const TimeSpan& t2 ) noexcept
        {
            const bool gt = t1.ticks_ > t2.ticks_;
            const bool lt = t1.ticks_ < t2.ticks_;
            return static_cast< int >( gt ) - static_cast< int >( lt );
        }

        /// <summary>
        /// Compares a <see cref="TimeSpan"/> with a `std::chrono` duration and returns an integer that indicates their relative ordering.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.</typeparam>
        /// <param name="t1">The <see cref="TimeSpan"/> left operand to compare.</param>
        /// <param name="t2">The `std::chrono` duration right operand to compare.</param>
        /// <returns>
        /// - A value less than zero (<c>-1</c>) when <paramref name="t1"/> is less than <paramref name="t2"/>; 
        /// - Zero (<c>0</c>) when they are equal;
        /// - A value greater than zero (<c>1</c>) when <paramref name="t1"/> is greater than <paramref name="t2"/>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The duration <paramref name="t2"/> is converted to the library internal tick unit (100 ns) using <c>DurationToTicks</c>.
        ///   That conversion uses <c>std::chrono::duration_cast</c> and therefore truncates fractional sub-tick parts toward zero.
        /// </para>
        /// <para>
        /// - If the converted tick count for <paramref name="t2"/> does not fit in a <c>long long</c> the result may overflow;
        ///   callers that require full range-safety should validate the duration before calling or use a checked conversion.
        /// </para>
        /// <para>
        /// - The implementation uses comparisons only (no subtraction) to avoid signed overflow and is therefore defined
        ///   for all representable tick values. The function is <c>constexpr</c> and <c>noexcept</c>.
        /// </para>
        /// <para>
        /// - Thread-safety: pure function with no side-effects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Compare TimeSpan with std::chrono::milliseconds
        /// TimeSpan ts = TimeSpan::FromSeconds(1.0); // 1 second
        /// using namespace std::chrono;
        /// int cmp = TimeSpan::Compare( ts, milliseconds(1500) ); // cmp == -1 (1s < 1.5s)
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        static constexpr int Compare( const TimeSpan& t1, const DurationT& t2 ) noexcept
        {
            auto t2Ticks = DurationToTicks( t2 );
            const bool gt = t1.ticks_ > t2Ticks;
            const bool lt = t1.ticks_ < t2Ticks;
            return static_cast< int >( gt ) - static_cast< int >( lt );
        }

        /// <summary>
        /// Compares a `std::chrono` duration with a <see cref="TimeSpan"/> and returns an integer that indicates their relative ordering.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.</typeparam>
        /// <param name="t1">The `std::chrono` duration left operand to compare.</param>
        /// <param name="t2">The <see cref="TimeSpan"/> right operand to compare.</param>
        /// <returns>
        /// - A value less than zero (<c>-1</c>) when <paramref name="t1"/> is less than <paramref name="t2"/>; 
        /// - Zero (<c>0</c>) when they are equal;
        /// - A value greater than zero (<c>1</c>) when <paramref name="t1"/> is greater than <paramref name="t2"/>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The duration <paramref name="t1"/> is converted to the library internal tick unit (100 ns) using <c>DurationToTicks</c>.
        ///   That conversion uses <c>std::chrono::duration_cast</c> and therefore truncates fractional sub-tick parts toward zero.
        /// </para>
        /// <para>
        /// - If the converted tick count for <paramref name="t1"/> does not fit in a <c>long long</c> the result may overflow;
        ///   callers that require full range-safety should validate the duration before calling or use a checked conversion.
        /// </para>
        /// <para>
        /// - The implementation uses comparisons only (no subtraction) to avoid signed overflow and is therefore defined
        ///   for all representable tick values. The function is <c>constexpr</c> and <c>noexcept</c>.
        /// </para>
        /// <para>
        /// - Thread-safety: pure function with no side-effects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Compare std::chrono::seconds with TimeSpan
        /// using namespace std::chrono;
        /// int cmp = TimeSpan::Compare( seconds(2), TimeSpan::FromSeconds(1.5) ); // cmp == 1 (2s > 1.5s)
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        static constexpr int Compare( const DurationT& t1, const TimeSpan& t2 ) noexcept
        {
            auto t1Ticks = DurationToTicks( t1 );
            const bool gt = t1Ticks > t2.ticks_;
            const bool lt = t1Ticks < t2.ticks_;
            return static_cast< int >( gt ) - static_cast< int >( lt );
        }


        /// <summary>
        /// Compares this <see cref="TimeSpan"/> instance to another <see cref="TimeSpan"/> and returns an integer
        /// that indicates the relative ordering.
        /// </summary>
        /// <param name="value">The <see cref="TimeSpan"/> to compare with this instance.</param>
        /// <returns>
        /// - A value less than zero (<c>-1</c>) when this instance is less than <paramref name="value"/>;
        /// - Zero (<c>0</c>) when this instance equals <paramref name="value"/>;
        /// - A value greater than zero (<c>1</c>) when this instance is greater than <paramref name="value"/>.
        /// </returns>
        /// <remarks>
        /// - The method is <c>constexpr</c> and <c>noexcept</c> and may be evaluated in constant expressions.
        /// - Implementation uses boolean comparisons only (no subtraction) to avoid overflow:
        ///   <c>static_cast<int>(ticks_ > value.ticks_) - static_cast<int>(ticks_ < value.ticks_)</c>.
        /// - Returns canonicalized -1/0/+1 results. Complexity is O(1). The call has no side-effects and is thread-safe.
        /// - For C++20 three-way comparison semantics prefer using <c>operator&lt;&gt;&gt;()</c> which is also provided.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan a = TimeSpan::FromSeconds(1.0);
        /// TimeSpan b = TimeSpan::FromSeconds(2.0);
        /// int cmp = a.CompareTo(b); // cmp == -1
        /// </code>
        /// </example>
        constexpr int CompareTo( const TimeSpan& value ) const noexcept
        {
            const bool gt = ticks_ > value.ticks_;
            const bool lt = ticks_ < value.ticks_;
            return static_cast< int >( gt ) - static_cast< int >( lt );
        }

        /// <summary>
        /// Compares this <see cref="TimeSpan"/> instance to a `std::chrono` duration and returns an integer
        /// that indicates their relative ordering.
        /// </summary>
        /// <typeparam name="DurationT">
        /// A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.
        /// </typeparam>
        /// <param name="value">
        /// The duration to compare with this <see cref="TimeSpan"/>. May be negative.
        /// </param>
        /// <returns>
        /// - A value less than zero (<c>-1</c>) when this <see cref="TimeSpan"/> is less than <paramref name="value"/>;
        /// - Zero (<c>0</c>) when they are equal;
        /// - A value greater than zero (<c>1</c>) when this <see cref="TimeSpan"/> is greater than <paramref name="value"/>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The provided duration is converted to the library internal tick unit (100 ns) using <c>DurationToTicks</c>.
        ///   That conversion uses <c>std::chrono::duration_cast</c> to a 100-ns tick duration and therefore truncates
        ///   fractional sub-tick parts toward zero (no rounding).
        /// </para>
        /// <para>
        /// - The conversion result is stored in a <c>long long</c>. If the duration magnitude exceeds the range
        ///   representable by <c>long long</c> the converted value may overflow; callers that require full range safety
        ///   should validate the duration prior to calling or use a checked conversion.
        /// </para>
        /// <para>
        /// - To avoid signed overflow this comparison implementation uses only relational comparisons of the underlying
        ///   tick counts (no subtraction). The result is canonicalized to -1/0/+1.
        /// </para>
        /// <para>
        /// - The method is <c>constexpr</c> and <c>noexcept</c>. It is pure and has no side-effects and is safe for
        ///   concurrent use.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromSeconds(1.0); // 1 second
        /// int cmp = ts.CompareTo( milliseconds(1500) ); // cmp == -1 (1s < 1.5s)
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr int CompareTo( const DurationT& value ) const noexcept
        {
            auto valueTicks = DurationToTicks( value );
            const bool gt = ticks_ > valueTicks;
            const bool lt = ticks_ < valueTicks;
            return static_cast< int >( gt ) - static_cast< int >( lt );
        }

        /// <summary>
        /// Returns the magnitude (absolute value) of this <see cref="TimeSpan"/> as a <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals the absolute magnitude of this instance's
        /// internal tick count (<c>ticks_</c>). For non-negative intervals the returned value equals this instance.
        /// For negative intervals the returned value is produced by clearing the sign bit of the underlying
        /// two's‑complement representation.
        /// </returns>
        /// <remarks>
        /// - The method is <c>constexpr</c> and <c>noexcept</c> and implemented in a branchless, well-defined manner:
        ///   it casts <c>ticks_</c> to an unsigned 64-bit value, applies the mask <c>0x7FFFFFFFFFFFFFFF</c> to clear
        ///   the sign bit, and constructs a <see cref="TimeSpan"/> from the masked value.
        /// - Casting to <c>UInt64</c> before the bitwise-and makes the operation fully defined by the C++ standard
        ///   (bitwise operations on signed negative integers are implementation-defined). The masked result is
        ///   guaranteed to fit in a signed 64-bit value (<= <c>LLONG_MAX</c>) so the conversion back to
        ///   <c>long long</c> is well-defined.
        /// - Special-case: the minimum two's‑complement value (INT64_MIN / −2^63) cannot be represented as a positive
        ///   signed 64-bit value. With this implementation the masked result for that input becomes zero. If callers
        ///   require a different policy for that extreme value (for example saturate to <c>LLONG_MAX</c> or throw),
        ///   implement an explicit branch to detect and handle <c>ticks_ == std::numeric_limits<long long>::min()</c>.
        /// - Complexity: O(1). The method has no side-effects and is thread-safe.
        /// - Rationale: using the unsigned-mask approach avoids a signed negation which would overflow for INT64_MIN,
        ///   preserving <c>noexcept</c> and <c>constexpr</c> guarantees.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan positive = TimeSpan::FromSeconds(5.0);    // positive.Ticks() >= 0
        /// TimeSpan absPos = positive.Duration();             // absPos == positive
        ///
        /// TimeSpan negative = TimeSpan::FromSeconds(-5.0);   // negative.Ticks() < 0
        /// TimeSpan absNeg = negative.Duration();             // absNeg == magnitude of negative
        ///
        /// // Extreme case: INT64_MIN
        /// TimeSpan minVal = TimeSpan::MinValue();
        /// TimeSpan absMin = minVal.Duration();               // implementation-defined policy: masked result -> 0
        /// </code>
        /// </example>
        constexpr TimeSpan Duration( ) const noexcept
        {
            constexpr UInt64 Mask = 0x7FFFFFFFFFFFFFFFULL;
            auto unsignedTicks = static_cast< UInt64 >( ticks_ );
            return TimeSpan( static_cast< long long >( unsignedTicks & Mask ) );
        }

        /// <summary>
        /// Creates a <see cref="TimeSpan"/> that represents the specified number of days.
        /// </summary>
        /// <param name="value">Number of days, may be fractional. The value is converted to milliseconds by multiplying
        /// with <c>MillisPerDay</c> and then rounded to the nearest whole millisecond before conversion to ticks.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing <paramref name="value"/> days. Fractional-day portions are preserved
        /// by first converting to milliseconds and rounding to the nearest millisecond; the resulting millisecond value
        /// is converted to ticks (1 tick = 100 ns).
        /// </returns>
        /// <remarks>
        /// - Implementation delegates to <see cref="Interval(double,int)"/> using the scale factor <c>MillisPerDay</c>.
        /// - The conversion uses rounding to the nearest millisecond. Callers requiring different rounding semantics
        ///   should perform the rounding themselves and use <see cref="TimeSpan::FromMilliseconds(double)"/> or
        ///   construct from ticks directly.
        /// - Exceptions:
        ///   - <see cref="ArgumentException"/> is thrown by <see cref="Interval(double,int)"/> when <paramref name="value"/> is NaN.
        ///   - <see cref="OverflowException"/> is thrown when the computed millisecond value is outside the representable range
        ///     (see <c>TimeBase::MaxMilliSeconds</c> / <c>TimeBase::MinMilliSeconds</c>).
        /// - Complexity: O(1). The function is thread-safe and has no side-effects other than constructing the result.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1.5 days -> 36 hours
        /// TimeSpan ts = TimeSpan::FromDays(1.5); // equivalent to FromHours(36.0)
        /// </code>
        /// </example>
        static TimeSpan FromDays( double value )
        {
            return Interval( value, MillisPerDay );
        }

        /// <summary>
        /// Creates a <see cref="TimeSpan"/> that represents the specified number of hours.
        /// </summary>
        /// <param name="value">Number of hours, may be fractional. The value is converted to milliseconds by multiplying
        /// with <c>MillisPerHour</c> and then rounded to the nearest whole millisecond before conversion to ticks.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing <paramref name="value"/> hours. Fractional-hour portions are preserved
        /// by first converting to milliseconds and rounding to the nearest millisecond; the resulting millisecond value
        /// is converted to ticks (1 tick = 100 ns).
        /// </returns>
        /// <remarks>
        /// - Implementation delegates to <see cref="Interval(double,int)"/> using the scale factor <c>MillisPerHour</c>.
        /// - The conversion uses rounding to the nearest millisecond. Callers requiring different rounding semantics
        ///   should perform the rounding themselves and use <see cref="TimeSpan::FromMilliseconds(double)"/> or
        ///   construct from ticks directly.
        /// - Exceptions:
        ///   - <see cref="ArgumentException"/> is thrown by <see cref="Interval(double,int)"/> when <paramref name="value"/> is NaN.
        ///   - <see cref="OverflowException"/> is thrown when the computed millisecond value is outside the representable range
        ///     (see <c>TimeBase::MaxMilliSeconds</c> / <c>TimeBase::MinMilliSeconds</c>).
        /// - Complexity: O(1). The function is thread-safe and has no side-effects other than constructing the result.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1.5 hours -> 90 minutes
        /// TimeSpan ts = TimeSpan::FromHours(1.5); // equivalent to FromMinutes(90.0)
        /// </code>
        /// </example>
        static TimeSpan FromHours( double value )
        {
            return Interval( value, MillisPerHour );
        }

        /// <summary>
        /// Creates a <see cref="TimeSpan"/> that represents the specified number of minutes.
        /// </summary>
        /// <param name="value">Number of minutes, may be fractional. The value is converted to milliseconds by multiplying
        /// with <c>MillisPerMinute</c> and then rounded to the nearest whole millisecond before conversion to ticks.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing <paramref name="value"/> minutes. Fractional-minute portions are preserved
        /// by first converting to milliseconds and rounding to the nearest millisecond; the resulting millisecond value
        /// is converted to ticks (1 tick = 100 ns).
        /// </returns>
        /// <remarks>
        /// - Implementation delegates to <see cref="Interval(double,int)"/> using the scale factor <c>MillisPerMinute</c>.
        /// - The conversion uses rounding to the nearest millisecond. Callers requiring different rounding semantics
        ///   should perform the rounding themselves and use <see cref="TimeSpan::FromMilliseconds(double)"/> or
        ///   construct from ticks directly.
        /// - Exceptions:
        ///   - <see cref="ArgumentException"/> is thrown by <see cref="Interval(double,int)"/> when <paramref name="value"/> is NaN.
        ///   - <see cref="OverflowException"/> is thrown when the computed millisecond value is outside the representable range
        ///     (see <c>TimeBase::MaxMilliSeconds</c> / <c>TimeBase::MinMilliSeconds</c>).
        /// - Complexity: O(1). The function is thread-safe and has no side-effects other than constructing the result.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1.5 minutes -> 90 seconds
        /// TimeSpan ts = TimeSpan::FromMinutes(1.5); // equivalent to FromSeconds(90.0)
        /// </code>
        /// </example>
        static TimeSpan FromMinutes( double value )
        {
            return Interval( value, MillisPerMinute );
        }

        /// <summary>
        /// Creates a <see cref="TimeSpan"/> that represents the specified number of seconds.
        /// </summary>
        /// <param name="value">Number of seconds, may be fractional. The value is converted to milliseconds by multiplying
        /// with <c>MillisPerSecond</c> and then rounded to the nearest whole millisecond before conversion to ticks.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing <paramref name="value"/> seconds. Fractional-second portions are preserved
        /// by first converting to milliseconds and rounding to the nearest millisecond; the resulting millisecond value
        /// is converted to ticks (1 tick = 100 ns).
        /// </returns>
        /// <remarks>
        /// - Implementation delegates to <see cref="Interval(double,int)"/> using the scale factor <c>MillisPerSecond</c>.
        /// - The conversion uses rounding to the nearest millisecond. Callers requiring different rounding semantics
        ///   should perform the rounding themselves and use <see cref="TimeSpan::FromMilliseconds(double)"/> or
        ///   construct from ticks directly.
        /// - Exceptions:
        ///   - <see cref="ArgumentException"/> is thrown by <see cref="Interval(double,int)"/> when <paramref name="value"/> is NaN.
        ///   - <see cref="OverflowException"/> is thrown when the computed millisecond value is outside the representable range
        ///     (see <c>TimeBase::MaxMilliSeconds</c> / <c>TimeBase::MinMilliSeconds</c>).
        /// - Complexity: O(1). The function is thread-safe and has no side-effects other than constructing the result.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1.5 seconds -> 1500 milliseconds
        /// TimeSpan ts = TimeSpan::FromSeconds(1.5); // equivalent to FromMilliseconds(1500.0)
        /// </code>
        /// </example>
        static TimeSpan FromSeconds( double value )
        {
            return Interval( value, MillisPerSecond );
        }

        /// <summary>
        /// Creates a <see cref="TimeSpan"/> that represents the specified number of milliseconds.
        /// </summary>
        /// <param name="value">Number of milliseconds, may be fractional. The value is rounded to the nearest whole millisecond before conversion to ticks (1 tick = 100 ns).</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing <paramref name="value"/> milliseconds. Fractional-millisecond portions are rounded
        /// to the nearest millisecond and converted to ticks.
        /// </returns>
        /// <remarks>
        /// - Implementation delegates to <see cref="Interval(double,int)"/> using a scale factor of <c>1</c> (milliseconds).
        /// - Rounding behavior: fractional milliseconds are rounded to the nearest whole millisecond by <see cref="Interval(double,int)"/>.
        /// - Exceptions:
        ///   - <see cref="ArgumentException"/> is thrown by <see cref="Interval(double,int)"/> when <paramref name="value"/> is NaN.
        ///   - <see cref="OverflowException"/> is thrown when the computed millisecond value is outside the representable range
        ///     (see <c>TimeBase::MaxMilliSeconds</c> / <c>TimeBase::MinMilliSeconds</c>).
        /// - Complexity: O(1). The function is thread-safe and has no side-effects other than constructing the result.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // 1500 milliseconds -> 1.5 seconds
        /// TimeSpan ts = TimeSpan::FromMilliseconds(1500.0);
        /// </code>
        /// </example>
        static TimeSpan FromMilliseconds( double value )
        {
            return Interval( value, 1 );
        }

        /// <summary>
        /// Creates a <see cref="TimeSpan"/> from a `std::chrono::duration`.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the `IsStdChronoDuration` constraint.</typeparam>
        /// <param name="value">The duration value to convert. May be negative to represent a negative interval.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> that represents the same interval as <paramref name="value"/>.
        /// The conversion maps the duration to the library's internal 100-nanosecond tick unit using
        /// `DurationToTicks` (100 ns ticks = 1 / 10,000,000 second).
        /// </returns>
        /// <remarks>
        /// - The conversion is implemented using `DurationToTicks`, which performs a `std::chrono::duration_cast`
        ///   to a 100‑ns tick duration and returns the underlying integer count. Fractional sub-tick parts are
        ///   discarded (truncated toward zero).
        /// - No runtime range checking is performed here. If the converted tick count does not fit in a
        ///   <c>long long</c> the result may overflow. Callers that require range-safety should validate
        ///   <paramref name="value"/> relative to <see cref="TimeBase::MinTicks"/> / <see cref="TimeBase::MaxTicks"/>
        ///   before calling this function.
        /// - The function is <c>constexpr</c> and has no side-effects; it is safe to call in constant expressions
        ///   and concurrently from multiple threads.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Construct a TimeSpan of 1.5 seconds from std::chrono::milliseconds
        /// TimeSpan ts = TimeSpan::FromDuration( std::chrono::milliseconds(1500) );
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        static constexpr TimeSpan FromDuration( const DurationT& value )
        {
            auto ticks = DurationToTicks( value );
            return TimeSpan( ticks );
        }

        /// <summary>
        /// Creates a <see cref="TimeSpan"/> that represents the specified number of ticks.
        /// </summary>
        /// <param name="value">The number of ticks (100-nanosecond units) to store in the resulting <see cref="TimeSpan"/>. May be negative to represent a negative interval.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose internal tick count equals <paramref name="value"/>.
        /// </returns>
        /// <remarks>
        /// - This factory is a trivial wrapper around the explicit <see cref="TimeSpan(long long)"/> constructor and performs no validation or range checking.
        /// - One tick equals 100 nanoseconds (0.1 microsecond). Use <see cref="TimeSpan::TicksPerMillisecond"/>, <see cref="TicksPerSecond"/>, etc. to convert between units.
        /// - The function does not adjust or clamp values; callers that require values constrained to <see cref="TimeBase::MinTicks"/> / <see cref="TimeBase::MaxTicks"/>
        ///   must validate or clamp before calling this function.
        /// - Thread-safety: the function is pure and has no side-effects; it is safe to call concurrently.
        /// - For convenience when converting from `std::chrono::duration` use <see cref="FromDuration"/> which performs an appropriate conversion to ticks.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Create a TimeSpan representing 1 millisecond (TicksPerMillisecond == 10000)
        /// TimeSpan ts = TimeSpan::FromTicks( TimeSpan::TicksPerMillisecond );
        /// </code>
        /// </example>
        static TimeSpan FromTicks( long long value )
        {
            return TimeSpan( value );
        }

        /// <summary>
        /// Returns a <see cref="TimeSpan"/> whose tick count is the negation of this instance's tick count.
        /// </summary>
        /// <returns>
        /// A <see cref="TimeSpan"/> representing the arithmetic negation of this instance.
        /// If this instance contains the minimum two's‑complement 64-bit value (<c>std::numeric_limits<long long>::min()</c>)
        /// negation would overflow; this function explicitly handles that case and saturates the result to
        /// <see cref="TimeSpan::MaxValue()"/> to avoid undefined behavior.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The implementation performs a well-defined, branch-efficient unsigned two's‑complement negation:
        ///   it casts the underlying tick value to <c>UInt64</c>, computes the negation in unsigned arithmetic and
        ///   conditionally selects <c>MaxInt64</c> when the original value equals <c>MinInt64</c>.
        /// </para>
        /// <para>
        /// - This guarantees there is no signed overflow (undefined behavior) when negating the most-negative 64-bit value.
        ///   The chosen policy is saturation to <c>MaxInt64</c> for that extreme input.
        /// </para>
        /// <para>
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, has O(1) complexity and no side-effects.
        ///   It is safe to call from multiple threads concurrently.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan t = TimeSpan::FromSeconds(5.0);      // +5s
        /// TimeSpan neg = t.Negate();                   // -5s
        ///
        /// TimeSpan minVal = TimeSpan::MinValue();
        /// TimeSpan saturated = minVal.Negate();        // saturated == TimeSpan::MaxValue()
        /// </code>
        /// </example>
        constexpr TimeSpan Negate( ) const noexcept
        {
            using U = UInt64;
            constexpr U MinTicksU = static_cast< U >( MinInt64 );
            constexpr U MaxTicksU = static_cast< U >( MaxInt64 );

            const U ut = static_cast< U >( ticks_ );
            // 0 or 1
            const U isMin = static_cast< U >( ut == MinTicksU ); 
            // 0 or all-ones
            const U mask = static_cast< U >( 0ULL - isMin );

            // two's-complement negation (unsigned)
            const U uneg = static_cast< U >( ~ut ) + 1ULL;
            const U selected = ( uneg & ~mask ) | ( MaxTicksU & mask );

            return TimeSpan( std::bit_cast< long long >( selected ) );
        }

        /// <summary>
        /// Returns the unary negation of this <see cref="TimeSpan"/>.
        /// </summary>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals the negation of this instance's tick count.
        /// The operation delegates to <c>Negate()</c>, which explicitly handles the extreme two's‑complement
        /// minimum value to avoid signed overflow (it saturates to <c>TimeSpan::MaxValue()</c>).
        /// </returns>
        /// <remarks>
        /// <para>
        /// - This operator is <c>constexpr</c> and <c>noexcept</c>.
        /// - Delegating to <c>Negate()</c> guarantees defined behavior for <c>std::numeric_limits<long long>::min()</c>
        ///   instead of producing undefined signed overflow.
        /// - The operator has no side-effects and is safe to call concurrently on distinct objects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan t = TimeSpan::FromSeconds(5.0); // +5s
        /// TimeSpan neg = -t;                       // neg == TimeSpan::FromSeconds(-5.0)
        /// </code>
        /// </example>
        constexpr TimeSpan operator-( ) const noexcept
        {
            return Negate( );
        }


        /// <summary>
        /// Adds the specified <see cref="TimeSpan"/> to this instance and returns the sum.
        /// </summary>
        /// <param name="other">The <see cref="TimeSpan"/> to add. May be negative to perform subtraction.</param>
        /// <returns>
        /// A new <see cref="TimeSpan"/> whose tick count equals the sum of this instance's tick count
        /// and <paramref name="other"/>'s tick count.
        /// </returns>
        /// <remarks>
        /// - The method is <c>constexpr</c> and <c>noexcept</c> and performs a pure arithmetic addition of the
        ///   internal tick counts: <c>ticks_ + other.ticks_</c>.
        /// - No runtime overflow detection is performed in release builds. Signed overflow of 64-bit ticks
        ///   is undefined behavior in C++; therefore callers must ensure the operands are in a safe range
        ///   before calling this method. In debug builds the implementation asserts that the addition is safe
        ///   by calling <c>IsAdditionSafe(ticks_, other.ticks_)</c>.
        /// - Complexity: O(1). Thread-safe for distinct objects; the call has no side-effects and reads only
        ///   object-local state.
        /// - If callers require guaranteed overflow-safe semantics, validate operands against
        ///   <c>TimeBase::MinTicks</c>/<c>TimeBase::MaxTicks</c> or provide a checked wrapper that handles
        ///   overflow (for example saturate or return an error).
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan a = TimeSpan::FromSeconds(30.0);
        /// TimeSpan b = TimeSpan::FromMinutes(1.0);
        /// TimeSpan result = a.Add(b); // result represents 90 seconds
        /// </code>
        /// </example>
        constexpr TimeSpan Add( const TimeSpan& other ) const noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( ticks_, other.ticks_ ) );
            }
#endif
            return TimeSpan( ticks_ + other.ticks_ );
        }

        /// <summary>
        /// Adds a `std::chrono` duration to this <see cref="TimeSpan"/> and returns the resulting interval.
        /// </summary>
        /// <typeparam name="DurationT">
        /// A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.
        /// </typeparam>
        /// <param name="duration">
        /// The duration to add. May be negative to subtract time.
        /// </param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals the sum of this instance's ticks and the converted
        /// <paramref name="duration"/> measured in ticks (1 tick = 100 ns).
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The supplied <paramref name="duration"/> is converted to the library internal tick unit using
        ///   <c>DurationToTicks</c>. That conversion uses <c>std::chrono::duration_cast</c> to a 100 ns tick
        ///   duration and therefore truncates fractional sub-tick parts toward zero.
        /// </para>
        /// <para>
        /// - No runtime overflow checking is performed in this call. If the converted tick count for
        ///   <paramref name="duration"/> causes the sum to overflow a signed 64-bit value, the behavior would be
        ///   undefined in C++. In debug builds the implementation asserts that the addition is safe
        ///   by calling <c>IsAdditionSafe(ticks_, durationTicks)</c>.
        /// </para>
        /// <para>
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, pure (no side-effects) and safe to call concurrently.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromSeconds(1.0);         // 1 second
        /// auto result = ts.Add( milliseconds(1500) );      // result == TimeSpan::FromMilliseconds(2500.0)
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr TimeSpan Add( const DurationT& duration ) const noexcept
        {
            auto durationTicks = DurationToTicks( duration );
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( ticks_, durationTicks ) );
            }
#endif
            return TimeSpan( ticks_ + durationTicks );
        }


        /// <summary>
        /// Subtracts the specified <see cref="TimeSpan"/> from this instance and returns the difference.
        /// </summary>
        /// <param name="other">
        /// The <see cref="TimeSpan"/> to subtract. May be negative to perform addition.
        /// </param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals <c>ticks_ - other.ticks_</c>.
        /// The result may be negative if the subtrahend is larger than this instance.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - This method is <c>constexpr</c> and <c>noexcept</c> and performs a plain signed subtraction of
        ///   the internal 64-bit tick counts (1 tick = 100 ns).
        /// </para>
        /// <para>
        /// - No runtime overflow detection is performed in release builds. Signed overflow of 64-bit integers
        ///   is undefined behavior in C++; therefore callers MUST ensure the operands are in a safe range
        ///   before calling this method. In debug builds the implementation asserts the subtraction is safe
        ///   by calling <c>IsSubtractionSafe(ticks_, other.ticks_)</c>.
        /// </para>
        /// <para>
        /// - Thread-safety: the method has no side-effects and is safe to call concurrently on distinct objects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Subtract two TimeSpan values
        /// TimeSpan a = TimeSpan::FromMinutes(5.0);   // 5 minutes
        /// TimeSpan b = TimeSpan::FromMinutes(2.0);   // 2 minutes
        /// TimeSpan diff = a.Subtract(b);             // diff == TimeSpan::FromMinutes(3.0)
        ///
        /// // If you are unsure about overflow, validate first:
        /// // assert( IsSubtractionSafe( a.Ticks(), b.Ticks() ) );
        /// </code>
        /// </example>
        constexpr TimeSpan Subtract( const TimeSpan& other ) const noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( ticks_, other.ticks_ ) );
            }
#endif
            return TimeSpan( ticks_ - other.ticks_ );
        }

        /// <summary>
        /// Subtracts a `std::chrono` duration from this <see cref="TimeSpan"/> and returns the resulting interval.
        /// </summary>
        /// <typeparam name="DurationT">
        /// A <c>std::chrono::duration</c> type. Must satisfy the <c>IsStdChronoDuration</c> constraint.
        /// </typeparam>
        /// <param name="duration">The duration to subtract. May be negative to perform addition.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals this instance's tick count minus the converted
        /// <paramref name="duration"/> measured in ticks (1 tick = 100 ns).
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The supplied <paramref name="duration"/> is converted to the library internal tick unit using
        ///   <c>DurationToTicks</c>. That conversion uses <c>std::chrono::duration_cast</c> to a 100-ns tick
        ///   duration and therefore truncates fractional sub-tick parts toward zero.
        /// </para>
        /// <para>
        /// - No runtime overflow checking is performed in release builds. If the converted tick count for
        ///   <paramref name="duration"/> causes the subtraction to overflow a signed 64-bit value, the behavior is
        ///   undefined in C++. In debug builds the implementation asserts that the subtraction is safe
        ///   by calling <c>IsSubtractionSafe(ticks_, durationTicks)</c>.
        /// </para>
        /// <para>
        /// - The method is <c>constexpr</c> and <c>noexcept</c>, pure (no side-effects) and safe to call concurrently.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromMinutes(5.0);          // 5 minutes
        /// auto result = ts.Subtract( seconds(30) );         // result == TimeSpan::FromMinutes(4.5)
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr TimeSpan Subtract( const DurationT& duration ) const noexcept
        {
            auto durationTicks = DurationToTicks( duration );
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( ticks_, durationTicks ) );
            }
#endif
            return TimeSpan( ticks_ - durationTicks );
        }

        

        /// <summary>
        /// Adds the specified <see cref="TimeSpan"/> to this instance in-place.
        /// </summary>
        /// <param name="other">
        /// The <see cref="TimeSpan"/> to add. May be negative to perform subtraction.
        /// </param>
        /// <returns>Reference to this instance after the addition (<c>*this</c>).
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The operation performs a plain signed 64-bit addition of the internal tick counts:
        ///   <c>ticks_ += other.ticks_</c>. One tick equals 100 nanoseconds.
        /// </para>
        /// <para>
        /// - No runtime overflow checking is performed in release builds. Signed overflow of a 64-bit integer
        ///   is undefined behavior in C++; therefore callers MUST ensure the operands are in a safe range
        ///   before invoking this operator. In debug builds the implementation asserts the addition is safe
        ///   by calling <c>IsAdditionSafe(ticks_, other.ticks_)</c> when not evaluated in a constant expression.
        /// </para>
        /// <para>
        /// - The method is <c>constexpr</c> and <c>noexcept</c>. It mutates the object and is therefore not
        ///   thread-safe for concurrent callers that access the same instance; calling on distinct objects is safe.
        /// </para>
        /// <para>
        /// - Complexity: O(1). No allocations are performed.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan a = TimeSpan::FromMinutes(5.0); // 5 minutes
        /// TimeSpan b = TimeSpan::FromMinutes(2.0); // 2 minutes
        /// a += b; // a now represents 7 minutes
        /// </code>
        /// </example>
        constexpr TimeSpan& operator += ( const TimeSpan& other ) noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( ticks_, other.ticks_ ) );
            }
#endif
            ticks_ += other.ticks_;
            return *this;
        }

        /// <summary>
        /// Adds the specified `std::chrono` duration to this instance in-place.
        /// </summary>
        /// <typeparam name="DurationT">
        /// A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.
        /// </typeparam>
        /// <param name="duration">
        /// The duration to add. May be negative to perform subtraction. The duration is converted to the internal tick unit (1 tick = 100 ns) using <c>DurationToTicks</c>.
        /// </param>
        /// <returns>
        /// Reference to this instance after the addition (<c>*this</c>).
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The provided <paramref name="duration"/> is converted to ticks via <c>DurationToTicks</c>, which uses
        ///   <c>std::chrono::duration_cast</c> to a 100-ns tick duration and therefore truncates fractional sub-tick parts toward zero.
        /// </para>
        /// <para>
        /// - This operation performs a plain signed 64-bit addition of the underlying tick counts:
        ///   <c>ticks_ += durationTicks</c>. No runtime overflow checking is performed in release builds.
        ///   Signed overflow of a 64-bit integer is undefined behavior in C++; callers MUST ensure the operands are
        ///   in a safe range before invoking this operator. In debug builds an assertion verifies safety by calling
        ///   <c>IsAdditionSafe(ticks_, durationTicks)</c> when not evaluated in a constant expression.
        /// </para>
        /// <para>
        /// - The method is <c>constexpr</c> and <c>noexcept</c>. It mutates the object and therefore is not thread-safe
        ///   for concurrent callers that access the same instance; calling on distinct objects is safe.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromMinutes(5.0);   // 5 minutes
        /// ts += seconds(30);                          // ts now represents 5 minutes 30 seconds
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr TimeSpan& operator += ( const DurationT& duration ) noexcept
        {
            const auto durationTicks = DurationToTicks( duration );
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( ticks_, durationTicks ) );
            }
#endif
            ticks_ += durationTicks;
            return *this;
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> representing the sum of this instance and the specified <see cref="TimeSpan"/>.
        /// </summary>
        /// <param name="other">The <see cref="TimeSpan"/> to add. May be negative to perform subtraction.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose internal tick count equals <c>ticks_ + other.ticks_</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Performs a plain signed 64-bit addition of the internal tick counts (1 tick = 100 ns).
        /// - No runtime overflow checking is performed in release builds. Signed overflow of a 64-bit integer
        ///   is undefined behavior in C++; callers MUST ensure the operands are in a safe range before calling.
        ///   In debug builds the implementation asserts that the addition is safe by calling
        ///   <c>IsAdditionSafe(ticks_, other.ticks_)</c> when not evaluated in a constant expression.
        /// </para>
        /// <para>
        /// - The method is <c>constexpr</c> and <c>noexcept</c>, has no side-effects (does not mutate *this),
        ///   and is safe to call concurrently on distinct objects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Add two TimeSpan values
        /// TimeSpan a = TimeSpan::FromMinutes(5.0); // 5 minutes
        /// TimeSpan b = TimeSpan::FromMinutes(2.0); // 2 minutes
        /// TimeSpan sum = a + b;                    // sum == TimeSpan::FromMinutes(7.0)
        /// </code>
        /// </example>
        constexpr TimeSpan operator + ( const TimeSpan& other ) const noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( ticks_, other.ticks_ ) );
            }
#endif
            return TimeSpan(ticks_ + other.ticks_ );
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> obtained by adding the specified `std::chrono` duration to this instance.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.</typeparam>
        /// <param name="duration">The duration to add. May be negative to perform subtraction. The duration is converted to the internal tick unit (1 tick = 100 ns) using <c>DurationToTicks</c>.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose internal tick count equals <c>ticks_ + DurationToTicks(duration)</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The <paramref name="duration"/> is converted to ticks by <c>DurationToTicks</c>, which uses
        ///   <c>std::chrono::duration_cast</c> to a 100-nanosecond tick duration; fractional sub-tick parts are truncated toward zero.
        /// </para>
        /// <para>
        /// - No runtime overflow checking is performed in release builds. Signed overflow of the 64-bit tick count is
        ///   undefined behavior in C++; callers MUST ensure the operands are in a safe range before calling this operator.
        ///   In debug builds an assertion verifies safety by calling <c>IsAdditionSafe(ticks_, durationTicks)</c> when not evaluated in a constant expression.
        /// </para>
        /// <para>
        /// - The operator is <c>constexpr</c> and <c>noexcept</c>. It does not mutate this instance and is safe to call concurrently on distinct objects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromMinutes(5.0);   // 5 minutes
        /// auto result = ts + seconds(30);             // result == TimeSpan::FromMinutes(5.5)
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr TimeSpan operator + ( const DurationT& duration ) const noexcept
        {
            const auto durationTicks = DurationToTicks( duration );
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( ticks_, durationTicks ) );
            }
#endif
            return TimeSpan( ticks_ + durationTicks );
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to the sum of the specified `std::chrono` duration and the given <see cref="TimeSpan"/>.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.</typeparam>
        /// <param name="duration">The duration to add. May be negative to perform subtraction. Converted to internal ticks (100 ns) via <c>DurationToTicks</c>.</param>
        /// <param name="timeSpan">The <see cref="TimeSpan"/> to add to.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose internal tick count equals <c>DurationToTicks(duration) + timeSpan.Ticks()</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The conversion from <paramref name="duration"/> to ticks uses <c>std::chrono::duration_cast</c> inside <c>DurationToTicks</c>;
        ///   fractional sub-tick parts are truncated toward zero.
        /// </para>
        /// <para>
        /// - No runtime overflow checking is performed in release builds. Signed 64-bit overflow when adding the converted ticks
        ///   is undefined behavior in C++. In debug builds an assertion calls <c>IsAdditionSafe(durationTicks, timeSpan.ticks_)</c>
        ///   when not evaluated in a constant expression to help detect potential overflow.
        /// </para>
        /// <para>
        /// - The operator is <c>constexpr</c> and <c>noexcept</c>. It does not modify its operands and is safe to call concurrently on distinct objects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan base = TimeSpan::FromMinutes(5.0);      // 5 minutes
        /// auto result = seconds(30) + base;                // result == 5 minutes 30 seconds
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr friend TimeSpan operator + ( const DurationT& duration, const TimeSpan& timeSpan ) noexcept
        {
            const auto durationTicks = DurationToTicks( duration );
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( durationTicks, timeSpan.ticks_ ) );
            }
#endif
            return TimeSpan( durationTicks + timeSpan.ticks_ );
        }



        /// <summary>
        /// Subtracts the specified <see cref="TimeSpan"/> from this instance in-place.
        /// </summary>
        /// <param name="other">The <see cref="TimeSpan"/> to subtract. May be negative to perform addition.</param>
        /// <returns>Reference to this instance after the subtraction (<c>*this</c>).</returns>
        /// <remarks>
        /// <para>
        /// - Performs a plain signed 64-bit subtraction of the internal tick counts:
        ///   <c>ticks_ -= other.ticks_</c> (1 tick = 100 ns).
        /// </para>
        /// <para>
        /// - No runtime overflow checking is performed in release builds. Signed overflow of a 64-bit integer
        ///   is undefined behavior in C++; callers MUST ensure the operands are in a safe range before invoking
        ///   this operator. In debug builds the implementation asserts that the subtraction is safe by calling
        ///   <c>IsSubtractionSafe(ticks_, other.ticks_)</c> when not evaluated in a constant expression.
        /// </para>
        /// <para>
        /// - The operator is <c>constexpr</c> and <c>noexcept</c>. It mutates the object and therefore is not
        ///   thread-safe for concurrent modifications of the same instance; calling on distinct objects is safe.
        /// </para>
        /// <para>
        /// - Complexity: O(1). No allocations are performed.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Subtract two TimeSpan values in-place
        /// TimeSpan a = TimeSpan::FromMinutes(5.0); // 5 minutes
        /// TimeSpan b = TimeSpan::FromMinutes(2.0); // 2 minutes
        /// a -= b; // a now represents 3 minutes
        /// </code>
        /// </example>
        constexpr TimeSpan& operator -= ( const TimeSpan& other ) noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( ticks_, other.ticks_ ) );
            }
#endif
            ticks_ -= other.ticks_;
            return *this;
        }

        /// <summary>
        /// Subtracts the specified `std::chrono` duration from this <see cref="TimeSpan"/> in-place.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.</typeparam>
        /// <param name="duration">Duration to subtract. May be negative to perform addition.</param>
        /// <returns>Reference to this instance after the subtraction (<c>*this</c>).</returns>
        /// <remarks>
        /// <para>
        /// - The supplied <paramref name="duration"/> is converted to the library internal tick unit (100 ns) using
        ///   <c>DurationToTicks</c>. That conversion uses <c>std::chrono::duration_cast</c> and therefore truncates
        ///   fractional sub-tick parts toward zero.
        /// </para>
        /// <para>
        /// - No runtime overflow checking is performed in release builds. If the converted tick count for
        ///   <paramref name="duration"/> causes the subtraction to overflow a signed 64-bit value, the behavior is
        ///   undefined in C++. In debug builds the implementation asserts that the subtraction is safe by calling
        ///   <c>IsSubtractionSafe(ticks_, durationTicks)</c> when not evaluated in a constant expression.
        ///   Callers that require defined overflow semantics should validate with <c>IsSubtractionSafe</c> or use
        ///   a checked/clamping helper prior to calling.
        /// </para>
        /// <para>
        /// - The method is <c>constexpr</c> and <c>noexcept</c>. It mutates the object and therefore is not thread-safe
        ///   for concurrent modifications of the same instance; calling on distinct objects is safe.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromMinutes(5.0);   // 5 minutes
        /// ts -= seconds(30);                          // ts now represents 4 minutes 30 seconds
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr TimeSpan& operator -= ( const DurationT& duration ) noexcept
        {
            const auto durationTicks = DurationToTicks( duration );
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( ticks_, durationTicks ) );
            }
#endif
            ticks_ -= durationTicks;
            return *this;
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> that is the result of subtracting <paramref name="other"/> from this instance.
        /// </summary>
        /// <param name="other">The <see cref="TimeSpan"/> to subtract. May be negative to perform addition.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose internal tick count equals <c>ticks_ - other.ticks_</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The operation performs a plain signed 64-bit subtraction of the internal tick counts (1 tick = 100 ns).
        /// - No runtime overflow checking is performed in release builds. Signed overflow of 64-bit integers is undefined
        ///   behaviour in C++; callers MUST ensure the operands are in a safe range before calling. In debug builds the
        ///   implementation asserts safety via <c>IsSubtractionSafe(ticks_, other.ticks_)</c> when not evaluated in a constant expression.
        /// - The method is <c>constexpr</c> and <c>noexcept</c>, has no side-effects and does not mutate this instance.
        /// - Complexity: O(1). Thread-safe when called on distinct objects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Subtract two TimeSpan values
        /// TimeSpan a = TimeSpan::FromMinutes(5.0);   // 5 minutes
        /// TimeSpan b = TimeSpan::FromMinutes(2.0);   // 2 minutes
        /// TimeSpan diff = a - b;                     // diff == TimeSpan::FromMinutes(3.0)
        /// </code>
        /// </example>
        constexpr TimeSpan operator - ( const TimeSpan& other ) const noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( ticks_, other.ticks_ ) );
            }
#endif
            return TimeSpan( ticks_ - other.ticks_ );
        }

        /// <summary>
        /// Subtracts the specified `std::chrono` duration from this <see cref="TimeSpan"/> and returns the resulting interval.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.</typeparam>
        /// <param name="duration">
        /// The duration to subtract. May be negative to perform addition. The duration is converted to the library's
        /// internal tick unit (100 ns) using <c>DurationToTicks</c>.
        /// </param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose internal tick count equals <c>ticks_ - DurationToTicks(duration)</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Conversion: <c>DurationToTicks</c> uses <c>std::chrono::duration_cast</c> to convert the supplied duration
        ///   to 100-nanosecond ticks. This is a narrowing conversion and truncates fractional sub-tick parts toward zero.
        /// </para>
        /// <para>
        /// - Overflow safety: this operator performs a plain signed 64-bit subtraction of tick counts. Signed overflow of a
        ///   64-bit integer is undefined behavior in C++; therefore no automatic runtime overflow checking is performed in
        ///   release builds. In debug builds an assertion checks <c>IsSubtractionSafe(ticks_, durationTicks)</c> (when not
        ///   evaluated in a constant expression) to help catch unsafe usage.
        /// </para>
        /// <para>
        /// - Behavior on exceptional inputs:
        ///   <list type="bullet">
        ///     <item><description>If the converted tick count for <c>duration</c> is outside the range representable by <c>long long</c>,
        ///     the conversion may overflow; callers that require full range-safety should validate the duration before calling.</description></item>
        ///     <item><description>If overflow would occur during the subtraction and assertions are disabled, the result is undefined
        ///     (program behaviour is undefined). Use a checked/clamped helper if defined semantics are required.</description></item>
        ///   </list>
        /// </para>
        /// <para>
        /// - The method is <c>constexpr</c> and <c>noexcept</c>, has O(1) complexity, and has no side-effects. It is safe for concurrent
        ///   use on distinct objects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromSeconds(2.0);      // 2 seconds
        /// auto result = ts - milliseconds(500);         // result == TimeSpan::FromMilliseconds(1500.0)
        ///
        /// // If unsure about overflow, validate beforehand:
        /// auto durTicks = TimeSpan::DurationToTicks(milliseconds(500));
        /// assert( IsSubtractionSafe( ts.Ticks(), durTicks ) );
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr TimeSpan operator - ( const DurationT& duration ) const noexcept
        {
            const auto durationTicks = DurationToTicks( duration );
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( ticks_, durationTicks ) );
            }
#endif
            return TimeSpan( ticks_ - durationTicks );
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to the result of subtracting the specified <paramref name="timeSpan"/>
        /// from the supplied `std::chrono` <paramref name="duration"/>.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.</typeparam>
        /// <param name="duration">
        /// The left-hand operand duration. Converted to the library internal tick unit (100 ns) using <c>DurationToTicks</c>.
        /// May be negative to represent a negative interval.
        /// </param>
        /// <param name="timeSpan">The right-hand operand <see cref="TimeSpan"/> to subtract from <paramref name="duration"/>.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose internal tick count equals <c>DurationToTicks(duration) - timeSpan.Ticks()</c>.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Conversion: <c>DurationToTicks</c> calls <c>std::chrono::duration_cast</c> to convert <paramref name="duration"/>
        ///   to 100-nanosecond ticks. This is a narrowing conversion: fractional sub-tick parts are truncated toward zero.
        /// </para>
        /// <para>
        /// - Overflow safety: the operator performs a plain signed 64-bit subtraction of the converted tick count and the
        ///   <see cref="TimeSpan"/>'s tick count. Signed overflow of 64-bit integers is undefined behaviour in C++; no runtime
        ///   overflow checking is performed in release builds. In debug builds an assertion verifies <c>IsSubtractionSafe(durationTicks, timeSpan.ticks_)</c>
        ///   when not evaluated in a constant expression.
        /// </para>
        /// <para>
        /// - Error conditions:
        ///   <list type="bullet">
        ///     <item><description>If <c>DurationToTicks(duration)</c> produces a value outside the range of <c>long long</c>, the conversion may overflow;</description></item>
        ///     <item><description>If the subtraction would overflow and assertions are disabled, the result is undefined. Use a checked or clamping helper if defined semantics are required.</description></item>
        ///   </list>
        /// </para>
        /// <para>
        /// - The function is <c>constexpr</c> and <c>noexcept</c>, pure (no side-effects) and safe to call concurrently on distinct objects.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// // 2.0 seconds - 1.5 seconds -> 0.5 seconds
        /// auto result = seconds(2) - TimeSpan::FromSeconds(1.5); // result == TimeSpan::FromMilliseconds(500)
        ///
        /// // Validate before calling when unsure about overflow:
        /// auto durTicks = TimeSpan::DurationToTicks(seconds(2));
        /// assert( IsSubtractionSafe( durTicks, TimeSpan::FromSeconds(1.5).Ticks() ) );
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        friend constexpr TimeSpan operator - ( const DurationT& duration, const TimeSpan& timeSpan ) noexcept
        {
            const auto durationTicks = DurationToTicks( duration );
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( durationTicks, timeSpan.ticks_ ) );
            }
#endif
            return TimeSpan( durationTicks - timeSpan.ticks_ );
        }

        /// <summary>
        /// Assigns a `std::chrono` duration to this <see cref="TimeSpan"/> by converting the duration
        /// to the library internal tick unit (1 tick = 100 ns) and storing the resulting tick count.
        /// </summary>
        /// <typeparam name="DurationT">A `std::chrono::duration` type. Must satisfy the <c>IsStdChronoDuration</c> constraint.</typeparam>
        /// <param name="value">The duration to assign. May be negative to represent a negative interval.</param>
        /// <returns>
        /// A reference to this <see cref="TimeSpan"/> instance after assignment (<c>*this</c>).
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Conversion is performed by <c>DurationToTicks(value)</c>, which uses <c>std::chrono::duration_cast</c>
        ///   to convert the supplied duration to 100-nanosecond ticks. That conversion truncates fractional sub-tick
        ///   parts toward zero.
        /// </para>
        /// <para>
        /// - No runtime range checking is performed. If the converted tick count is outside the representable
        ///   range of <c>long long</c> or unacceptable for the receiving <see cref="TimeSpan"/>, the behavior
        ///   may be implementation-defined or lead to overflow. Callers that require range-safety should validate
        ///   the input duration before assignment or use a checked/clamping helper.
        /// </para>
        /// <para>
        /// - The assignment is <c>constexpr</c> and does not allocate; it is a simple conversion and store operation.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts;
        /// ts = milliseconds(1500); // ts now represents 1.5 seconds
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr TimeSpan& operator = ( const DurationT& value )
        {
            ticks_ = DurationToTicks( value );
            return *this;
        }

        /// <summary>
        /// Converts this <see cref="TimeSpan"/> to a `std::chrono` duration type.
        /// </summary>
        /// <typeparam name="DurationT">Target `std::chrono::duration` type. Must satisfy <c>IsStdChronoDuration</c>.</typeparam>
        /// <returns>
        /// A value of type <typeparamref name="DurationT"/> that represents the same interval as this <see cref="TimeSpan"/>.
        /// The conversion is implemented by <c>TicksToDuration</c>, which performs a <c>std::chrono::duration_cast</c>
        /// from the internal 100-nanosecond tick duration to the requested duration type.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Precision and rounding: <c>std::chrono::duration_cast</c> performs a narrowing conversion. When converting
        ///   to a coarser-grained duration fractional sub-tick parts are truncated toward zero (no rounding).
        /// </para>
        /// <para>
        /// - Range and overflow: No runtime overflow checking is performed. If the resulting count does not fit in
        ///   <c>DurationT::rep</c> the conversion may overflow or wrap depending on the implementation. Callers that
        ///   require guaranteed range-safety should validate the tick value against the target representation before
        ///   converting or use a checked helper.
        /// </para>
        /// <para>
        /// - The operator is <c>constexpr</c> and <c>noexcept</c> and has no side-effects; it is safe for concurrent use.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromSeconds(1.5); // 1.5 seconds
        /// milliseconds ms = static_cast<milliseconds>( ts ); // ms == 1500ms
        /// seconds s = static_cast<seconds>( ts ); // s == 1s (fraction truncated)
        /// </code>
        /// </example>
        template<typename DurationT>
            requires IsStdChronoDuration<DurationT>
        constexpr explicit operator DurationT( ) const noexcept
        {
            return TicksToDuration<DurationT>( ticks_ );
        }

        /// <summary>
        /// Converts this <see cref="TimeSpan"/> to a `std::chrono` duration of the specified type.
        /// </summary>
        /// <typeparam name="DurationT">
        /// Target `std::chrono::duration` type. Must satisfy the `IsStdChronoDuration` constraint.
        /// Defaults to `std::chrono::system_clock::duration`.
        /// </typeparam>
        /// <returns>
        /// A value of type <typeparamref name="DurationT"/> that represents the same interval as this <see cref="TimeSpan"/>.
        /// Conversion is performed by `TicksToDuration`, which uses `std::chrono::duration_cast` from the library's
        /// 100-nanosecond tick duration to the requested duration type.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - Precision & rounding: `std::chrono::duration_cast` performs a narrowing conversion. When converting
        ///   to a coarser-grained duration fractional sub-tick parts (fractions of 100 ns) are truncated toward zero
        ///   (no rounding).
        /// </para>
        /// <para>
        /// - Range & overflow: There is no built-in runtime check for overflow. If the resulting count does not fit
        ///   in `DurationT::rep` the conversion may overflow or wrap depending on the implementation. Callers that
        ///   require guaranteed range-safety should validate the tick value against the target representation before
        ///   converting or use a checked helper.
        /// </para>
        /// <para>
        /// - Thread-safety: the function is pure and has no side-effects; it is safe to call concurrently.
        /// - The function is `constexpr` and `noexcept`.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromSeconds(1.5); // 1.5s
        /// milliseconds ms = ts.ToDuration<milliseconds>(); // ms == 1500ms
        /// seconds s = ts.ToDuration<seconds>(); // s == 1s (fraction truncated)
        /// </code>
        /// </example>
        template<typename DurationT = std::chrono::system_clock::duration>
            requires IsStdChronoDuration<DurationT>
        constexpr DurationT ToDuration( ) const noexcept
        {
            return TicksToDuration<DurationT>( ticks_ );
        }


        /// <summary>
        /// Adds an integral tick count to this <see cref="TimeSpan"/> in-place.
        /// </summary>
        /// <typeparam name="T">An integral type convertible to <c>long long</c> (e.g. <c>int</c>, <c>long</c>, <c>long long</c>).</typeparam>
        /// <param name="value">The value to add, interpreted as a number of ticks (1 tick = 100 ns). May be negative to subtract ticks.</param>
        /// <returns>Reference to this <see cref="TimeSpan"/> after the addition (<c>*this</c>).</returns>
        /// <remarks>
        /// <para>
        /// - The parameter <paramref name="value"/> is converted to <c>long long</c> via <c>static_cast</c> and added to the internal tick count.
        /// - In debug builds an assertion verifies the operation is safe using <c>IsAdditionSafe</c>. There is no automatic overflow
        ///   detection in release builds; callers MUST ensure the operation does not overflow the 64-bit tick range.
        /// - This operation mutates the object and therefore is not thread-safe for concurrent access to the same instance.
        /// - Complexity: O(1).
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromMilliseconds(500); // 500 ms
        /// ts += TimeSpan::TicksPerMillisecond;           // add 1 ms (10000 ticks)
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan& operator += ( const T& value ) noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( ticks_, static_cast< long long >( value ) ) );
            }
#endif
            ticks_ += static_cast<long long>( value );
            return *this;
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to this instance plus an integral tick count.
        /// </summary>
        /// <typeparam name="T">An integral type convertible to <c>long long</c>.</typeparam>
        /// <param name="value">The value to add, interpreted as a number of ticks (1 tick = 100 ns). May be negative to subtract ticks.</param>
        /// <returns>A <see cref="TimeSpan"/> whose tick count equals <c>this->Ticks() + static_cast<long long>(value)</c>.</returns>
        /// <remarks>
        /// <para>
        /// - The parameter <paramref name="value"/> is converted to <c>long long</c> and added to the internal tick count to produce a
        ///   new <see cref="TimeSpan"/>; the original instance is not modified.
        /// - In debug builds an assertion verifies the addition is safe using <c>IsAdditionSafe</c>. No runtime overflow checks are performed
        ///   in release builds; callers MUST ensure the addition does not overflow the representable tick range.
        /// - Thread-safety: this method is const and safe to call concurrently on distinct objects.
        /// - Complexity: O(1).
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromSeconds(1.0); // 1 second
        /// TimeSpan result = ts + (TimeSpan::TicksPerSecond / 2); // +0.5s
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan operator + ( const T& value ) const noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( ticks_, static_cast< long long >( value ) ) );
            }
#endif
            return TimeSpan( ticks_ + static_cast<long long>( value ) );
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to an integral tick count plus a <see cref="TimeSpan"/>.
        /// </summary>
        /// <typeparam name="T">An integral type convertible to <c>long long</c>.</typeparam>
        /// <param name="value">Left-hand operand, interpreted as a number of ticks (1 tick = 100 ns).</param>
        /// <param name="timeSpan">Right-hand operand <see cref="TimeSpan"/> to add.</param>
        /// <returns>A <see cref="TimeSpan"/> whose tick count equals <c>static_cast<long long>(value) + timeSpan.Ticks()</c>.</returns>
        /// <remarks>
        /// <para>
        /// - This friend operator implements the commutative addition form (<c>T + TimeSpan</c>).
        /// - In debug builds an assertion verifies the operation is safe via <c>IsAdditionSafe</c>. No runtime overflow checks are performed
        ///   in release builds; callers MUST ensure operands produce a representable tick value.
        /// - Complexity: O(1). The function is noexcept and does not modify its operands.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromMilliseconds(250);
        /// TimeSpan sum = TimeSpan::TicksPerMillisecond * 10 + ts; // add 10 ms + 250 ms
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        friend constexpr TimeSpan operator + ( const T& value, const TimeSpan& timeSpan ) noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsAdditionSafe( static_cast< long long >( value ), ticks_ ) );
            }
#endif
            return TimeSpan( static_cast<long long>( value ) + timeSpan.ticks_ );
        }

        /// <summary>
        /// Subtracts an integral tick count from this <see cref="TimeSpan"/> in-place.
        /// </summary>
        /// <typeparam name="T">An integral type convertible to <c>long long</c> (for example <c>int</c>, <c>long</c>, <c>long long</c>).</typeparam>
        /// <param name="value">The value to subtract, interpreted as a number of ticks (1 tick = 100 ns). May be negative to add ticks.</param>
        /// <returns>Reference to this <see cref="TimeSpan"/> after the subtraction (<c>*this</c>).</returns>
        /// <remarks>
        /// <para>
        /// - The parameter <paramref name="value"/> is converted to <c>long long</c> via <c>static_cast</c> and subtracted from the internal tick count.
        /// - In debug builds an assertion verifies the operation is safe using <c>IsSubtractionSafe</c>.
        ///   There is no automatic overflow detection in release builds; callers MUST ensure the operation does not overflow the 64-bit tick range.
        /// - This operation mutates the object and therefore is not thread-safe for concurrent access to the same instance.
        /// - Complexity: O(1).
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromMilliseconds(500); // 500 ms
        /// ts -= TimeSpan::TicksPerMillisecond;           // subtract 1 ms (10000 ticks)
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan& operator -= ( const T& value ) noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( ticks_, static_cast< long long >( value ) ) );
            }
#endif
            ticks_ -= static_cast<long long>( value );
            return *this;
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to this instance minus an integral tick count.
        /// </summary>
        /// <typeparam name="T">An integral type convertible to <c>long long</c>.</typeparam>
        /// <param name="value">The value to subtract, interpreted as a number of ticks (1 tick = 100 ns). May be negative to add ticks.</param>
        /// <returns>A <see cref="TimeSpan"/> whose tick count equals <c>this->Ticks() - static_cast<long long>(value)</c>.</returns>
        /// <remarks>
        /// <para>
        /// - The parameter <paramref name="value"/> is converted to <c>long long</c> and subtracted from the internal tick count to produce a new <see cref="TimeSpan"/>.
        /// - In debug builds an assertion verifies the subtraction is safe using <c>IsSubtractionSafe</c>. No runtime overflow checks are performed
        ///   in release builds; callers MUST ensure the subtraction does not overflow the representable tick range.
        /// - Thread-safety: this method is const and safe to call concurrently on distinct objects.
        /// - Complexity: O(1).
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromSeconds(1.0); // 1 second
        /// TimeSpan result = ts - (TimeSpan::TicksPerSecond / 2); // -0.5s
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan operator - ( const T& value ) const noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( ticks_, static_cast< long long >( value ) ) );
            }
#endif
            return TimeSpan( ticks_ - static_cast<long long>( value ) );
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to an integral tick count minus the given <see cref="TimeSpan"/>.
        /// </summary>
        /// <typeparam name="T">An integral type convertible to <c>long long</c>.</typeparam>
        /// <param name="value">Left-hand operand, interpreted as a number of ticks (1 tick = 100 ns).</param>
        /// <param name="timeSpan">Right-hand operand <see cref="TimeSpan"/> to subtract.</param>
        /// <returns>A <see cref="TimeSpan"/> whose tick count equals <c>static_cast<long long>(value) - timeSpan.Ticks()</c>.</returns>
        /// <remarks>
        /// <para>
        /// - This friend operator implements the subtraction form (<c>T - TimeSpan</c>).
        /// - In debug builds an assertion verifies the operation is safe via <c>IsSubtractionSafe</c>. No runtime overflow checks are performed
        ///   in release builds; callers MUST ensure operands produce a representable tick value.
        /// - Complexity: O(1). The function is <c>noexcept</c> and does not modify its operands.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromMilliseconds(250);
        /// TimeSpan result = TimeSpan::TicksPerMillisecond * 10 - ts; // 10 ms - 250 ms
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        friend constexpr TimeSpan operator - ( const T& value, const TimeSpan& timeSpan ) noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsSubtractionSafe( static_cast< long long >( value ), ticks_ ) );
            }
#endif
            return TimeSpan( static_cast<long long>( value ) - timeSpan.ticks_ );
        }

        /// <summary>
        /// Multiplies this <see cref="TimeSpan"/> by an integral factor in-place.
        /// </summary>
        /// <typeparam name="T">An integral type. The declaration requires <c>std::is_integral_v&lt;T&gt;</c>.</typeparam>
        /// <param name="value">Factor to multiply this instance by. May be negative to produce a negative interval.</param>
        /// <returns>Reference to this instance after multiplication (<c>*this</c>).</returns>
        /// <remarks>
        /// - The operation performs signed 64-bit multiplication of the internal tick count (<c>ticks_</c>).
        /// - In debug builds an assertion verifies the multiplication is safe via <c>IsMultiplicationSafe(ticks_, static_cast<long long>(value))</c>.
        /// - In release builds no overflow checks are performed; signed overflow of a 64-bit integer is undefined behavior in C++.
        ///   Callers MUST ensure the result fits in the representable range (see <see cref="TimeBase::MinTicks"/> / <see cref="TimeBase::MaxTicks"/>)
        ///   before calling this method if defined semantics are required.
        /// - Complexity: O(1). The method is <c>constexpr</c> and <c>noexcept</c> and mutates the object; it is not thread-safe for concurrent mutation.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromSeconds(2.0); // 2s
        /// ts *= 3;                                   // ts == 6s
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan& operator *= ( const T& value ) const noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsMultiplicationSafe( ticks_, static_cast< long long >( value ) ) );
            }
#endif
            ticks_ *= static_cast<long long>( value );
            return *this;
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to this instance multiplied by an integral factor.
        /// </summary>
        /// <typeparam name="T">An integral type. The declaration requires <c>std::is_integral_v&lt;T&gt;</c>.</typeparam>
        /// <param name="value">Factor to multiply this instance by. May be negative.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals <c>ticks_ * static_cast<long long>(value)</c>.
        /// </returns>
        /// <remarks>
        /// - The operation computes the product using signed 64-bit arithmetic.
        /// - In debug builds an assertion verifies safety via <c>IsMultiplicationSafe(ticks_, static_cast<long long>(value))</c>.
        /// - In release builds no overflow checks are performed; signed overflow is undefined behavior. Validate operands beforehand
        ///   when overflow must be avoided.
        /// - Complexity: O(1). The method is <c>constexpr</c> and <c>noexcept</c>.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromMilliseconds(500); // 500 ms
        /// TimeSpan doubled = ts * 2;                      // 1000 ms
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan operator * ( const T& value ) const noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsMultiplicationSafe( ticks_, static_cast< long long >( value ) ) );
            }
#endif
            return TimeSpan( ticks_ * static_cast<long long>( value ) );
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to an integral factor multiplied by a <see cref="TimeSpan"/>.
        /// </summary>
        /// <typeparam name="T">An integral type. The declaration requires <c>std::is_integral_v&lt;T&gt;</c>.</typeparam>
        /// <param name="value">Left-hand integral factor.</param>
        /// <param name="timeSpan">Right-hand <see cref="TimeSpan"/> operand.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals <c>static_cast<long long>(value) * timeSpan.ticks_</c>.
        /// </returns>
        /// <remarks>
        /// - This friend overload provides the commutative multiplication form (<c>T * TimeSpan</c>).
        /// - In debug builds an assertion verifies safety via <c>IsMultiplicationSafe(static_cast<long long>(value), ticks_)</c>.
        /// - In release builds no overflow checks are performed; signed overflow is undefined behavior. Callers must ensure the multiplication
        ///   result fits in a signed 64-bit value when defined behavior is required.
        /// - Complexity: O(1). The function is <c>constexpr</c> and <c>noexcept</c>.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromSeconds(1.0); // 1s
        /// TimeSpan tripled = 3 * ts;                // 3s
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        friend constexpr TimeSpan operator * ( const T& value, const TimeSpan& timeSpan ) noexcept
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsMultiplicationSafe( static_cast< long long >( value ), ticks_ ) );
            }
#endif
            return TimeSpan( static_cast<long long>( value ) * timeSpan.ticks_ );
        }

        /// <summary>
        /// Divides this <see cref="TimeSpan"/>'s tick count by an integral divisor in-place.
        /// </summary>
        /// <typeparam name="T">An integral type. The declaration requires <c>std::is_integral_v&lt;T&gt;</c>.</typeparam>
        /// <param name="value">Divisor. Must not be zero. Integer division truncates toward zero.</param>
        /// <returns>Reference to this instance after division (<c>*this</c>).</returns>
        /// <remarks>
        /// - Behavior: performs signed 64-bit division of the internal tick count (<c>ticks_</c>) by <paramref name="value"/>.
        /// - Debug checks: in debug builds an assertion verifies safety via <c>IsDivisionSafe(ticks_, static_cast<long long>(value))</c>.
        /// - Release builds: no runtime safety checks are performed; division by zero or division that triggers undefined behavior
        ///   (for example <c>INT64_MIN / -1</c>) is undefined. Callers MUST ensure the divisor is valid before calling.
        /// - The operation is <c>constexpr</c> and <c>noexcept</c> by declaration. It mutates the object and therefore is not
        ///   thread-safe for concurrent modification of the same instance.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromSeconds(4.0); // 4s
        /// ts /= 2; // ts now represents 2s
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan& operator /= ( const T& value ) const
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsDivisionSafe( ticks_, static_cast< long long >( value ) ) );
            }
#endif
            ticks_ /= static_cast<long long>( value );
            return *this;
        }

        /// <summary>
        /// Returns a new <see cref="TimeSpan"/> equal to this instance divided by an integral divisor.
        /// </summary>
        /// <typeparam name="T">An integral type. The declaration requires <c>std::is_integral_v&lt;T&gt;</c>.</typeparam>
        /// <param name="value">Divisor. Must not be zero. Integer division truncates toward zero.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals <c>ticks_ / static_cast&lt;long long&gt;(value)</c>.
        /// </returns>
        /// <remarks>
        /// - Behavior: computes the quotient using signed 64-bit division; fractional remainder is discarded.
        /// - Debug checks: in debug builds an assertion verifies safety via <c>IsDivisionSafe(ticks_, static_cast<long long>(value))</c>.
        /// - Release builds: no runtime checks are performed; division by zero or UB-causing divisons are the caller's responsibility to avoid.
        /// - Complexity: O(1). The method is <c>constexpr</c> and <c>noexcept</c>.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan ts = TimeSpan::FromSeconds(5.0); // 5s
        /// TimeSpan half = ts / 2; // half == 2.5s truncated to 2s (integer millisecond/tick semantics)
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan operator / ( const T& value ) const
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsDivisionSafe( ticks_, static_cast< long long >( value ) ) );
            }
#endif
            return TimeSpan( ticks_ / static_cast<long long>( value ) );
        }

        /// <summary>
        /// Returns a <see cref="TimeSpan"/> constructed from the quotient of an integral left-hand operand divided by a <see cref="TimeSpan"/>'s ticks.
        /// </summary>
        /// <typeparam name="T">An integral type. The declaration requires <c>std::is_integral_v&lt;T&gt;</c>.</typeparam>
        /// <param name="value">Left-hand integral operand.</param>
        /// <param name="timeSpan">Right-hand <see cref="TimeSpan"/> divisor. Its <c>ticks_</c> must not be zero.</param>
        /// <returns>
        /// A <see cref="TimeSpan"/> whose tick count equals <c>static_cast&lt;long long&gt;(value) / timeSpan.ticks_</c>.
        /// </returns>
        /// <remarks>
        /// - Semantics: performs signed 64-bit division of the provided integral <paramref name="value"/> by the internal tick count
        ///   of <paramref name="timeSpan"/>. The result is used directly as a tick count for the returned <see cref="TimeSpan"/>.
        /// - Debug checks: in debug builds an assertion verifies safety via <c>IsDivisionSafe(static_cast<long long>(value), timeSpan.ticks_)</c>.
        /// - Release builds: no runtime checks are performed; dividing by zero or other UB-causing divisons is undefined behavior.
        /// - This overload is provided to allow the commutative-style expression <c>T / TimeSpan</c> and follows integer truncation semantics.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// TimeSpan divisor = TimeSpan::FromSeconds(2.0); // 2s -> ticks
        /// TimeSpan result = 10 / divisor; // result ticks == 10 / divisor.Ticks()
        /// </code>
        /// </example>
        template<typename T>
            requires std::is_integral_v<T>
        friend constexpr TimeSpan operator / ( const T& value, const TimeSpan& timeSpan )
        {
#ifdef _DEBUG
            if !consteval
            {
                assert( IsDivisionSafe( static_cast< long long >( value ), ticks_ ) );
            }
#endif
            return TimeSpan( static_cast<long long>( value ) / timeSpan.ticks_ );
        }

        /// <summary>
        /// Converts this <see cref="TimeSpan"/> to a <c>bool</c> indicating whether the interval is non-zero.
        /// </summary>
        /// <returns>
        /// <c>true</c> when this <see cref="TimeSpan"/> represents a non-zero interval (i.e. <c>ticks_ != 0</c>); otherwise <c>false</c>.
        /// </returns>
        /// <remarks>
        /// - This operator is declared <c>explicit</c> to avoid accidental implicit conversions to <c>bool</c>.
        /// - The check is performed on the internal tick count (<c>ticks_</c>) and has no side-effects.
        /// - The operator is <c>constexpr</c> and <c>noexcept</c>; it is safe to use in constant-evaluated contexts and from multiple threads.
        /// </remarks>
        constexpr explicit operator bool( ) const noexcept
        {
            return ticks_ != 0;
        }

        /// <summary>
        /// Three-way comparison (strong ordering) between this <see cref="TimeSpan"/> and another.
        /// </summary>
        /// <param name="other">The other <see cref="TimeSpan"/> to compare with.</param>
        /// <returns>
        /// A <see cref="std::strong_ordering"/> value describing the ordering:
        /// - less when this &lt; other,
        /// - equal when this == other,
        /// - greater when this &gt; other.
        /// </returns>
        /// <remarks>
        /// - Comparison is performed on the internal tick counts (<c>ticks_</c>) using the C++20 three-way operator.
        /// - The operation is <c>constexpr</c> and <c>noexcept</c> and cannot overflow.
        /// - Complexity: O(1). Thread-safe and has no side-effects.
        /// </remarks>
        constexpr std::strong_ordering operator<=>( const TimeSpan& other ) const noexcept
        {
            return ticks_ <=> other.ticks_;
        }

        /// <summary>
        /// Equality comparison between this <see cref="TimeSpan"/> and another.
        /// </summary>
        /// <param name="other">The other <see cref="TimeSpan"/> to compare with.</param>
        /// <returns><c>true</c> when the underlying tick counts are different; otherwise <c>false</c>.</returns>
        /// <remarks>
        /// - Implemented as a simple comparison of the internal tick counts (<c>ticks_ != other.ticks_</c>).
        /// - The function is <c>constexpr</c> and <c>noexcept</c>.
        /// </remarks>
        constexpr bool operator !=( const TimeSpan& other ) const noexcept
        {
            return ticks_ != other.ticks_;
        }

        /// <summary>
        /// Equality comparison between this <see cref="TimeSpan"/> and another.
        /// </summary>
        /// <param name="other">The other <see cref="TimeSpan"/> to compare with.</param>
        /// <returns><c>true</c> when the underlying tick counts are equal; otherwise <c>false</c>.</returns>
        /// <remarks>
        /// - Implemented as a simple comparison of the internal tick counts (<c>ticks_ == other.ticks_</c>).
        /// - The function is <c>constexpr</c> and <c>noexcept</c>.
        /// </remarks>
        constexpr bool operator ==( const TimeSpan& other ) const noexcept
        {
            return ticks_ == other.ticks_;
        }


        /// <summary>
        /// Three-way comparison (strong ordering) between this <see cref="TimeSpan"/> and a <c>std::chrono</c> duration.
        /// </summary>
        /// <typeparam name="DurationT">Target <c>std::chrono::duration</c> type. Must satisfy <c>IsStdChronoDuration</c>.</typeparam>
        /// <param name="other">The duration to compare with this <see cref="TimeSpan"/>.</param>
        /// <returns>
        /// A <see cref="std::strong_ordering"/> value describing the ordering:
        /// - less when this &lt; other,
        /// - equal when this == other,
        /// - greater when this &gt; other.
        /// </returns>
        /// <remarks>
        /// <para>
        /// - The supplied duration is converted to the library internal tick unit (100 ns) using <c>DurationToTicks</c>.
        ///   That conversion uses <c>std::chrono::duration_cast</c> and therefore truncates fractional sub-tick parts toward zero.
        /// </para>
        /// <para>
        /// - If the conversion of <paramref name="other"/> to ticks produces a value outside the range of <c>long long</c>,
        ///   the converted value may overflow. Callers that require full range-safety should validate the duration before calling.
        /// </para>
        /// <para>
        /// - The comparison is <c>constexpr</c> and <c>noexcept</c>. It is implemented via the three-way comparison of the internal
        ///   tick count and the converted ticks: <c>ticks_ <=> DurationToTicks(other)</c>.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// using namespace std::chrono;
        /// TimeSpan ts = TimeSpan::FromSeconds(1.5); // 1.5s
        /// auto ordering = ts <=> milliseconds(1500); // ordering == std::strong_ordering::equal
        /// </code>
        /// </example>
        template<typename DurationT = std::chrono::system_clock::duration>
            requires IsStdChronoDuration<DurationT>
        constexpr std::strong_ordering operator<=>( const DurationT& other ) const noexcept
        {
            return ticks_ <=> DurationToTicks( other );
        }


        

        /// <summary>
        /// Attempts to parse a character buffer into a <see cref="TimeSpan"/> using formats
        /// compatible with .NET/C# <c>TimeSpan.TryParse</c> (for example: "[-][d.]hh:mm[:ss[.fffffff]]").
        /// </summary>
        /// <typeparam name="CharT">Character type: <c>char</c> or <c>wchar_t</c>.</typeparam>
        /// <param name="s">Pointer to the character buffer to parse (not required to be null terminated).</param>
        /// <param name="sLength">Length of the buffer in characters.</param>
        /// <param name="result">Out parameter that receives the parsed <see cref="TimeSpan"/> on success.
        /// On failure it is set to <c>TimeSpan::Zero()</c>.</param>
        /// <returns><c>true</c> when parsing succeeds and the value fits in the representable range;
        /// otherwise <c>false</c>.</returns>
        /// <remarks>
        /// <para>
        /// - Supported input (subset of .NET TimeSpan patterns):
        ///   <list type="bullet">
        ///     <item><description><c>[-][d.]hh:mm</c></description></item>
        ///     <item><description><c>[-][d.]hh:mm:ss</c></description></item>
        ///     <item><description><c>[-][d.]hh:mm:ss.fffffff</c> where fraction has up to 7 digits (100 ns ticks).</description></item>
        ///   </list>
        /// - Leading and trailing white-space is ignored. The sign (<c>'-'</c>) may precede the entire value.
        /// - Fractional seconds are converted to ticks (1 tick = 100 ns). Fractional digits are truncated/padded
        ///   to 7 digits (no rounding).
        /// - The routine performs overflow-safe checks using the library helpers. If any intermediate multiplication
        ///   or addition would overflow a signed 64-bit value the function fails and returns <c>false</c>.
        /// - This function is <c>constexpr</c> and <c>noexcept</c>. On failure <paramref name="result"/> is set to <c>TimeSpan::Zero()</c>.
        /// </para>
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // char example
        /// const char* s = "1.02:03:04.500"; // 1 day, 2 hours, 3 minutes, 4.5 seconds
        /// TimeSpan ts;
        /// bool ok = TimeSpan::TryParse( s, strlen( s ), ts );
        /// // ok == true, ts represents 1d 2h 3m 4.5s
        ///
        /// // wchar_t example
        /// const wchar_t* ws = L"-00:30:00"; // negative 30 minutes
        /// ok = TimeSpan::TryParse( ws, wcslen( ws ), ts );
        /// // ok == true, ts == -30 minutes
        /// </code>
        /// </example>
        template<typename CharT>
            requires std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>
        static bool TryParse( const CharT* s, size_t sLength, TimeSpan& result ) noexcept
        { 
            return Internal::TryParseTimeSpan<CharT>( s, sLength, result );
        }
        template<typename CharT>
            requires std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>
        static bool TryParse( const CharT* text, TimeSpan& result )
        {
            auto length = LengthOf( text );
            return TryParse<CharT>( text, length, result );
        }
        template<ContiguousContainerLike T>
            requires std::is_same_v<typename T::value_type, char> || std::is_same_v<typename T::value_type, wchar_t>
        bool TryParse( const T& text, TimeSpan& result )
        {
            return TryParse<typename T::value_type>( text.data( ), text.size( ), result );
        }
        
        template<typename CharT>
            requires std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>
        static TimeSpan Parse( const CharT* text )
        {
            TimeSpan result;
            if ( TryParse( text, result ) )
            {
                return result;
            }
            throw std::invalid_argument( "Invalid TimeSpan format" );
        }
        
        template<ContiguousContainerLike T>
            requires std::is_same_v<typename T::value_type, char> || std::is_same_v<typename T::value_type, wchar_t>
        static TimeSpan Parse( const T& text )
        {
            TimeSpan result;
            if ( TryParse( text, result ) )
            {
                return result;
            }
            throw std::invalid_argument( "Invalid TimeSpan format" );
        }

        /// <summary>
        /// Converts this <see cref="TimeSpan"/> to a string using the specified format string.
        /// </summary>
        /// <typeparam name="T">String-like return type (limited to: <c>WideString</c>, <c>AnsiString</c>, <c>std::wstring</c> or <c>std::string</c>).
        /// The character type of <typeparamref name="T"/> determines whether wide or narrow formatting is produced.</typeparam>
        /// <param name="formatString">
        /// Pointer to a format string. If <c>nullptr</c> or <c>formatStringLength == 0</c> the function formats the value
        /// using the default .NET/C# TimeSpan semantics (the constant "c" format).
        /// When non-empty the function implements a subset of .NET TimeSpan custom format patterns:
        /// tokens supported: <c>d</c>, <c>dd</c> (days), <c>h</c>, <c>hh</c> (hours component), <c>m</c>, <c>mm</c> (minutes),
        /// <c>s</c>, <c>ss</c> (seconds), <c>f</c>.. <c>fffffff</c> (fractional seconds digits), <c>F</c>.. <c>FFFFFFF</c> (fractional with trailing zero trim).
        /// Escaping with backslash (<c>\</c>) and quoted literals (single or double quotes) is supported. Standard format specifiers
        /// <c>'c'</c>, <c>'g'</c>, <c>'G'</c> are recognized when the format string length is one.
        /// </param>
        /// <param name="formatStringLength">Length of <paramref name="formatString"/>. When zero formatting falls back to the default.</param>
        /// <returns>
        /// A string of type <typeparamref name="T"/> containing the formatted TimeSpan.
        /// </returns>
        /// <remarks>
        /// - Default (empty format) matches .NET's constant ("c") format: optional leading '-' for negative values,
        ///   optional days followed by '.' when days != 0, then two-digit hours, minutes and seconds separated by ':',
        ///   and an optional fractional seconds part prefixed by '.' with exactly 7 digits when fractional ticks != 0.
        /// - The custom format implementation implements a commonly-used subset of .NET TimeSpan custom format patterns
        ///   and mirrors .NET behavior for those tokens (padding, fractional digits, and <c>F</c> trimming). It attempts
        ///   to be compatible with .NET for typical usages. Edge-case and culture-specific behaviors of .NET
        ///   implementation are not implemented here.
        /// </remarks>
        
        template<typename T = WideString>
            requires std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> || std::is_same_v<T, AnsiString> || std::is_same_v<T, WideString>
        T ToString( const typename T::value_type* formatString, const typename T::size_type formatStringLength ) const
        {
            return Internal::TimeSpanToString<T>( *this, formatString, formatStringLength );
        }

        template<typename T = WideString>
            requires std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> || std::is_same_v<T, AnsiString> || std::is_same_v<T, WideString>
        T ToString( ) const
        {
            return ToString<T>( nullptr, 0 );
        }

        template<typename T = WideString>
            requires std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> || std::is_same_v<T, AnsiString> || std::is_same_v<T, WideString>
        T ToString( const typename T::value_type* formatString ) const
        {
            auto length = LengthOf( formatString );
            return ToString<T>( formatString, length );
        }


        template<typename T = WideString, ContiguousContainerLike FormatT>
            requires (std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> || std::is_same_v<T, AnsiString> || std::is_same_v<T, WideString>) &&
                std::is_same_v<typename T::value_type, typename FormatT::value_type >
        T ToString( const FormatT& formatString ) const
        {
            return ToString<T>( formatString.data(), formatString.size() );
        }

        template<typename CharT, typename CharTraitsT = std::char_traits<CharT>>
        friend std::basic_ostream<CharT, CharTraitsT>& operator << ( std::basic_ostream<CharT, CharTraitsT>& stream, const TimeSpan& timeSpan )
        {
            stream << timeSpan.ToString<std::basic_string<CharT>>();
            return stream;
        }

    };

    template<typename T>
    inline constexpr bool IsTimeSpan = std::is_same_v<std::remove_cv_t<T>, TimeSpan>;

    template<typename T>
        requires IsTimeSpan<T>
    inline constexpr T ByteSwap( const T value ) noexcept
    {
        return std::bit_cast<TimeSpan>( ByteSwap( std::bit_cast<UInt64>( value ) ) );
    }

    class DateTime : public TimeBase
    {
    private:
        long long ticks_;
    public:
        static constexpr wchar_t DEFAULT_WIDE_FORMAT[ ] = L"%FT%T%Z";
        static constexpr char DEFAULT_FORMAT[ ] = "%FT%T%Z";

        HCC_EXPORT static long long ToLocalTicks( long long ticksInUtc );
        HCC_EXPORT static long long ToUniversalTicks( long long ticksInLocalTime );
        HCC_EXPORT static long long ToTicks( int year, int month, int day, int hour, int minute, int second, int millisecond );
        HCC_EXPORT static bool TryCreate( int year, int month, int day, int hour, int minute, int second, int millisecond, DateTime& result );

        static constexpr long long ToTicks(const timeval& tv)
        {
            return ((static_cast<Int64>(tv.tv_sec) * TicksPerSecond) + UnixEpoch) + (static_cast<Int64>(tv.tv_usec) * TicksPerMicrosecond);
        }



        HCC_EXPORT static long long DateToTicks( int year, int month, int day );
        HCC_EXPORT static long long JulianDateToTicks( int year, int month, int day );
        HCC_EXPORT static long long TimeToTicks( int hour, int minute, int second );
        HCC_EXPORT static long long SystemTimeToTicks( const SYSTEMTIME& systemTime );

        constexpr DateTime( ) noexcept
            : ticks_( 0 )
        {
        }

        constexpr explicit DateTime( long long ticks ) noexcept
            : ticks_( ticks )
        {
        }

        constexpr explicit DateTime( const std::chrono::system_clock::time_point& timePoint ) noexcept
            : ticks_( timePoint.time_since_epoch( ).count( ) + UnixEpoch )
        {
        }

        constexpr explicit DateTime(const timeval& tv) noexcept
            : ticks_(ToTicks(tv))
        {
        }

        explicit DateTime( double days )
            : ticks_( DoubleDateToTicks( days ) )
        {
        }


        DateTime( int year, int month, int day )
            : ticks_( DateToTicks( year, month, day ) )
        {
        }
        DateTime( int year, int month, int day, int hour, int minute, int second )
            : ticks_( DateToTicks( year, month, day ) + TimeToTicks( hour, minute, second ) )
        {
        }
        HCC_EXPORT DateTime( int year, int month, int day, int hour, int minute, int second, int millisecond );


        static constexpr DateTime MinValue( ) noexcept
        {
            return DateTime( MinTicks );
        }
        static constexpr DateTime MaxValue( ) noexcept
        {
            return DateTime( MaxTicks );
        }

        constexpr size_t hash( ) const noexcept
        {
            auto x = ( ticks_ ^ ( ticks_ >> 30 ) ) * UINT64_C( 0xbf58476d1ce4e5b9 );
            x = ( x ^ ( x >> 27 ) ) * UINT64_C( 0x94d049bb133111eb );
            x = x ^ ( x >> 31 );
            return x;
        }

        constexpr long long Ticks( ) const noexcept
        {
            return ticks_;
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return ticks_ != 0;
        }


        HCC_EXPORT DateTime Add( const TimeSpan& value ) const;
        HCC_EXPORT DateTime Add( double value, int scale ) const;
        HCC_EXPORT DateTime AddDays( double value ) const;
        HCC_EXPORT DateTime AddHours( double value ) const;
        HCC_EXPORT DateTime AddMilliseconds( double value ) const;
        HCC_EXPORT DateTime AddMinutes( double value ) const;
        HCC_EXPORT DateTime AddMonths( int months ) const;
        HCC_EXPORT DateTime AddSeconds( double value ) const;
        HCC_EXPORT DateTime AddTicks( long long value ) const;
        HCC_EXPORT DateTime AddYears( int value ) const;

        HCC_EXPORT const DateTime& AssingTo( SYSTEMTIME& systemTime ) const;

        HCC_EXPORT AnsiString DateToAnsiString( ) const;
        HCC_EXPORT WideString DateToString( ) const;

        HCC_EXPORT AnsiString TimeToAnsiString( ) const;
        HCC_EXPORT WideString TimeToString( ) const;

        HCC_EXPORT AnsiString ToAnsiString( ) const;
        HCC_EXPORT WideString ToString( ) const;
        HCC_EXPORT WideString ToString( const std::wstring_view& format ) const;

        HCC_EXPORT TimeSpan Subtract( const DateTime& value ) const;
        HCC_EXPORT DateTime Subtract( const TimeSpan& value ) const;

        static constexpr int Compare( const DateTime& first, const DateTime& second) noexcept
        {
            if ( first.ticks_ < second.ticks_ )
            {
                return -1;
            }
            else if ( first.ticks_ > second.ticks_ )
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        constexpr int CompareTo( const DateTime& other ) const noexcept
        {
            if ( ticks_ < other.ticks_ )
            {
                return -1;
            }
            else if ( ticks_ > other.ticks_ )
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        constexpr DateTime& operator = ( const std::chrono::system_clock::time_point& timePoint ) noexcept
        {
            ticks_ = timePoint.time_since_epoch( ).count( ) + UnixEpoch;
            return *this;
        }

        constexpr bool operator == ( const DateTime& other ) const noexcept
        {
            return ticks_ == other.ticks_;
        }
        constexpr bool operator != ( const DateTime& other ) const noexcept
        {
            return ticks_ != other.ticks_;
        }
        constexpr bool operator <  ( const DateTime& other ) const noexcept
        {
            return ticks_ < other.ticks_;
        }
        constexpr bool operator <= ( const DateTime& other ) const noexcept
        {
            return ticks_ <= other.ticks_;
        }
        constexpr bool operator >  ( const DateTime& other ) const noexcept
        {
            return ticks_ > other.ticks_;
        }
        constexpr bool operator >= ( const DateTime& other ) const noexcept
        {
            return ticks_ >= other.ticks_;
        }

        constexpr DateTime& operator += ( const TimeSpan& timeSpan ) noexcept
        {
            ticks_ += timeSpan.ticks_;
            return *this;
        }

        constexpr DateTime operator + ( const TimeSpan& timeSpan ) const noexcept
        {
            return DateTime(ticks_ + timeSpan.ticks_ );
        }

        constexpr DateTime& operator -= ( const TimeSpan& timeSpan ) noexcept
        {
            ticks_ -= timeSpan.ticks_;
            return *this;
        }

        constexpr DateTime operator - ( const TimeSpan& timeSpan ) const noexcept
        {
            return DateTime( ticks_ - timeSpan.ticks_ );
        }

        TimeSpan operator - ( const DateTime& other ) const
        {
            return TimeSpan(ticks_ - other.ticks_ );
        }

        HCC_EXPORT static int DaysInMonth( int year, int month );

        HCC_EXPORT static long long DoubleDateToTicks( double value );

        HCC_EXPORT static DateTime FromBinary( long long dateData );
        HCC_EXPORT static DateTime FromFileTime( long long fileTime );
        static DateTime FromFileTime( FILETIME fileTime )
        {
            return FromFileTime( *reinterpret_cast<Int64*>(&fileTime) );
        }

        HCC_EXPORT static DateTime FromOADate( double d );
        HCC_EXPORT bool IsDaylightSavingTime( ) const;
        HCC_EXPORT static DateTime FromUDate( double d );

        constexpr long long ToBinary( ) const noexcept
        {
            return ticks_;
        }

        HCC_EXPORT int GetDatePart( DatePart datePart ) const noexcept;
        HCC_EXPORT void GetYearMonthDay( int& year, int& month, int& day ) const;

        constexpr DateTime Date( ) const noexcept
        {
            return DateTime( ticks_ - ( ticks_ % TicksPerDay ) );
        }

        int Year( ) const noexcept
        {
            return GetDatePart( DatePart::Year );
        }
        int Month( ) const noexcept
        {
            return GetDatePart( DatePart::Month );
        }
        int Day( ) const noexcept
        {
            return GetDatePart( DatePart::Day );
        }
        DayOfWeek DayOfWeek( ) const noexcept
        {
            return static_cast<Core::DayOfWeek>( ( ticks_ / TicksPerDay + 1 ) % 7 );
        }
        int DayOfYear( ) const noexcept
        {
            return GetDatePart( DatePart::DayOfYear );
        }

        constexpr int Hour( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerHour ) % 24 );
        }

        constexpr int Minute( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerMinute ) % 60 );
        }

        constexpr int Second( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerSecond ) % 60 );
        }
        constexpr int Millisecond( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerMillisecond ) % 1000 );
        }

        constexpr TimeSpan TimeOfDay( ) const noexcept
        {
            return TimeSpan( ticks_ % TicksPerDay );
        }

        static DateTime Now( )
        {
            DateTime utc = UtcNow( );
            return utc.ToLocalTime( );
        }
        static DateTime UtcNow( ) noexcept
        {
            long long ticks = 0;
            GetSystemTimePreciseAsFileTime( (FILETIME*)&ticks );
            return DateTime( ticks + FileTimeOffset );
        }
        static DateTime Today( )
        {
            return DateTime::Now( ).Date( );
        }

        HCC_EXPORT static bool IsLeapYear( int year );

        HCC_EXPORT static double TicksToOADate( long long value );

        double ToOADate( ) const
        {
            return TicksToOADate( ticks_ );
        }

        HCC_EXPORT long long ToFileTime( ) const;

        HCC_EXPORT DateTime ToLocalTime( ) const;

        HCC_EXPORT DateTime ToUniversalTime( ) const;

        HCC_EXPORT static bool TryParse( const std::locale& locale, const wchar_t* text, size_t textLength, const wchar_t* format, DateTime& result );
        HCC_EXPORT static bool TryParse( const std::locale& locale, const char* text, size_t textLength, const char* format, DateTime& result );

        static bool TryParse( const wchar_t* text, size_t textLength, const wchar_t* format, DateTime& result )
        {
            const auto& locale = std::locale::classic( );
            return TryParse( locale, text, textLength, format, result );
        }
        static bool TryParse( const char* text, size_t textLength, const char* format, DateTime& result )
        {
            const auto& locale = std::locale::classic( );
            return TryParse( locale, text, textLength, format, result );
        }

        template<SimpleStringLike StringT>
        static bool TryParse( const std::locale& locale, const StringT& text, const wchar_t* format, DateTime& result )
        {
            return TryParse( locale, text.c_str( ), text.size( ), format, result );
        }

        template<typename StringT>
            requires std::is_same_v<StringT, std::wstring_view> || std::is_same_v<StringT, std::string_view>
        static bool TryParse( const std::locale& locale, const StringT& text, const wchar_t* format, DateTime& result )
        {
            return TryParse( locale, text.data( ), text.size( ), format, result );
        }

        template<SimpleStringLike StringT>
        static bool TryParse( const StringT& text, const wchar_t* format, DateTime& result )
        {
            return TryParse( text.c_str( ), text.size( ), format, result );
        }

        template<SimpleStringLike StringT>
        static bool TryParse( const StringT& text, DateTime& result )
        {
            return TryParse( text.c_str( ), text.size( ), DEFAULT_WIDE_FORMAT, result );
        }

        template<typename StringT>
            requires std::is_same_v<StringT, std::wstring_view> || std::is_same_v<StringT, std::string_view>
        static bool TryParse( const StringT& text, const wchar_t* format, DateTime& result )
        {
            return TryParse( text.data( ), text.size( ), format, result );
        }

        template<typename StringT>
            requires std::is_same_v<StringT, std::wstring_view> || std::is_same_v<StringT, std::string_view>
        static bool TryParse( const StringT& text, DateTime& result )
        {
            return TryParse( text.data( ), text.size( ), DEFAULT_FORMAT, result );
        }
        
        static bool TryParse( const std::locale& locale, const wchar_t* text, size_t textLength, DateTime& result )
        {
            return TryParse( locale, text, textLength, DEFAULT_WIDE_FORMAT, result );
        }
        static bool TryParse( const std::locale& locale, const char* text, size_t textLength, DateTime& result )
        {
            return TryParse( locale, text, textLength, DEFAULT_FORMAT, result );
        }

        static bool TryParse( const wchar_t* text, size_t textLength, DateTime& result )
        {
            return TryParse( text, textLength, DEFAULT_WIDE_FORMAT, result );
        }
        static bool TryParse( const char* text, size_t textLength, DateTime& result )
        {
            return TryParse( text, textLength, DEFAULT_FORMAT, result );
        }

        static bool TryParse( const std::locale& locale, const wchar_t* text, DateTime& result )
        {
            size_t textLength = wcslen( text );
            return TryParse( locale, text, textLength, DEFAULT_WIDE_FORMAT, result );
        }
        static bool TryParse( const std::locale& locale, const char* text, DateTime& result )
        {
            size_t textLength = strlen( text );
            return TryParse( locale, text, textLength, DEFAULT_FORMAT, result );
        }

        static bool TryParse( const wchar_t* text, DateTime& result )
        {
            size_t textLength = wcslen( text );
            return TryParse( text, textLength, DEFAULT_WIDE_FORMAT, result );
        }
        static bool TryParse( const char* text, DateTime& result )
        {
            size_t textLength = strlen( text );
            return TryParse( text, textLength, DEFAULT_FORMAT, result );
        }





        HCC_EXPORT static DateTime Parse( const wchar_t* text );
        HCC_EXPORT static DateTime Parse( const char* text );

        HCC_EXPORT static DateTime Parse( const WideString& text );
        HCC_EXPORT static DateTime Parse( const AnsiString& text );



        time_t ToTimeT( ) const noexcept
        {
            return static_cast<time_t>( ( ticks_ - UnixEpoch ) / TicksPerSecond );
        }
        timeval ToTimeval() const noexcept
        {
            auto seconds = static_cast<long>(static_cast<time_t>((ticks_ - UnixEpoch) / TicksPerSecond));
            auto useconds = static_cast<long>((ticks_ % TicksPerSecond) / TicksPerMicrosecond);
            return { seconds, useconds };
        }
        static DateTime FromTimeval(const timeval& tv)
        {
            return DateTime(ToTicks(tv));
        }

        // 64-bit NTP time will wrap in 2036
        //
        // Since the conversion to/from NTP timestamps uses
        // floating point arithmetic it is not 100% accurate.
        // 
        // When converting to NTP time and back again, the result 
        // may be different. While testing this difference was 
        // never found to be greater than 1 tick. 
        Int64 ToNTP( ) const
        {
            Int64 result = (ticks_ - NtpEpoch) / TicksPerSecond;
            result <<= 32;  
            double p = ldexp( static_cast< double >( ticks_ % TicksPerSecond ), 32 ) / static_cast<double>( TicksPerSecond );
            UInt32 frac = static_cast< UInt32 >( p );
            result |= frac;
            return result;
        }

        // 64-bit NTP time will wrap in 2036
        //
        // Since the conversion to/from NTP timestamps uses
        // floating point arithmetic it is not 100% accurate.
        // 
        // When converting to NTP time and back again, the result 
        // may be different. While testing this difference was 
        // never found to be greater than 1 tick. 
        static DateTime FromNTP( UInt32 secondsSince1900, UInt32 fraction )
        {
            Int64 ticks = ( static_cast<Int64>( secondsSince1900 ) * TicksPerSecond) + NtpEpoch;
            Int64 fractionTicks = static_cast< Int64 >( ( static_cast< double >( fraction ) * static_cast< double >( TicksPerSecond ) / static_cast< double >( 1LL << 32 ) ) );
            ticks += fractionTicks;
            return DateTime( ticks );
        }

        // 64-bit NTP time will wrap in 2036
        //
        // Since the conversion to/from NTP timestamps uses
        // floating point arithmetic it is not 100% accurate.
        // 
        // When converting to NTP time and back again, the result 
        // may be different. While testing this difference was 
        // never found to be greater than 1 tick. 
        static DateTime FromNTP( Int64 ntpTime )
        {
            Int64 ticks = ( ( std::bit_cast<UInt64>(ntpTime) >> 32 ) * TicksPerSecond ) + NtpEpoch;
            UInt64 fraction = ntpTime & 0xFFFFFFFF;
            Int64 fractionTicks = static_cast< Int64 >( ( static_cast< double >( fraction ) * static_cast< double >( TicksPerSecond ) / static_cast< double >( 1LL << 32 ) ) );
            ticks += fractionTicks;
            return DateTime( ticks );
        }



        constexpr std::chrono::system_clock::time_point ToTimePoint( ) const noexcept
        {
            return std::chrono::system_clock::time_point( std::chrono::system_clock::duration( Ticks( ) - UnixEpoch ) );
        }

        static DateTime FromTimePoint( std::chrono::system_clock::time_point timePoint ) noexcept
        {
            return DateTime( timePoint.time_since_epoch( ).count( ) + UnixEpoch );
        }


        timespec ToTimespec( ) const noexcept
        {
            Int64 adjustedTime = ticks_ - UnixEpoch;
            timespec result
            {
                static_cast<time_t>( adjustedTime / TicksPerSecond ),
                static_cast<long>( adjustedTime % TicksPerSecond ) * 100
            };
            return result;
        }


        constexpr double ToUDate( ) const noexcept
        {
            return static_cast<double>( ticks_ - UnixEpoch ) / TicksPerSecond;
        }

        HCC_EXPORT friend std::ostream& operator << ( std::ostream& stream, const DateTime& dateTime );
    };

    template<typename T>
    inline constexpr bool IsDateTime = std::is_same_v<std::remove_cv_t<T>, DateTime>;

    template<typename T>
        requires IsDateTime<T>
    inline constexpr T ByteSwap( const T value ) noexcept
    {
        return std::bit_cast<DateTime>( ByteSwap( std::bit_cast<UInt64>( value ) ) );
    }



    /// <summary>
    /// A closed/open interval that works well with the boost Interval Container Library.
    /// 
    /// boost::icl::interval_set<DateTime,std::less,Interval>
    /// </summary>
    class Interval : public boost::icl::right_open_interval<DateTime>
    {
    public:
        using Base = boost::icl::right_open_interval<DateTime>;
        using value_type = DateTime;

        Interval( )
            : Base( )
        { }

        explicit Interval( const DateTime& dateTime )
            : Base( dateTime, DateTime( dateTime.Ticks() + 1 ) )
        {
        }

        Interval( const DateTime& lowerBound, const DateTime& upperBound )
            : Base( lowerBound, upperBound )
        {
        }

        static Interval Infinite( )
        {
            return Interval( DateTime( DateTime::MinTicks ), DateTime( DateTime::MaxTicks ) );
        }

        static Interval From( const DateTime& lowerBound )
        {
            return Interval( lowerBound, DateTime( DateTime::MaxTicks ) );
        }

        static Interval Until( const DateTime& upperBound )
        {
            return Interval( DateTime( DateTime::MinTicks ), upperBound );
        }

        constexpr bool IsInfinite( ) const noexcept
        {
            return ( lower( ).Ticks( ) == DateTime::MinTicks ) && ( upper( ).Ticks( ) == DateTime::MaxTicks );
        }

        constexpr bool IsUntil( ) const noexcept
        {
            return ( lower( ).Ticks( ) == DateTime::MinTicks ) && ( upper( ).Ticks( ) != DateTime::MaxTicks );
        }

        constexpr bool IsFrom( ) const noexcept
        {
            return ( lower( ).Ticks( ) != DateTime::MinTicks ) && ( upper( ).Ticks( ) == DateTime::MaxTicks );
        }

        constexpr bool IsOver( ) const noexcept
        {
            return ( lower( ).Ticks( ) != DateTime::MinTicks ) && ( upper( ).Ticks( ) != DateTime::MaxTicks );
        }


        TimeSpan Duration( ) const noexcept
        {
            return upper( ).Ticks( ) >= lower( ).Ticks( ) ? TimeSpan( upper( ).Ticks( ) - lower( ).Ticks( ) ) : TimeSpan( );
        }

        bool Intersects( const Interval& other ) const noexcept
        {
            return ( lower() <= other.upper() && upper( ) >= other.lower( ) ) ||
                ( upper( ) >= other.lower( ) && lower( ) <= other.upper( ) );
        }

        bool Intersects( const DateTime& dateTime ) const noexcept
        {
            return lower( ) <= dateTime && upper( ) > dateTime;
        }

        bool Contains( const DateTime& dateTime ) const noexcept
        {
            return lower( ) <= dateTime && upper( ) > dateTime;
        }

        bool contains( const DateTime& dateTime ) const noexcept
        {
            return lower( ) <= dateTime && upper( ) > dateTime;
        }

        bool Contains( const Interval& other ) const noexcept
        {
            return lower( ) <= other.lower() && upper( ) >= other.upper();
        }

        bool contains( const Interval& other ) const noexcept
        {
            return lower( ) <= other.lower( ) && upper( ) >= other.upper( );
        }

        Interval Union( const Interval& other ) const noexcept
        {
            if ( Intersects( other ) )
            {
                auto start = lower( ) <= other.lower( ) ? lower( ) : other.lower( );
                auto end = upper( ) >= other.upper( ) ? upper( ) : other.upper( );
                return { start, end };
            }
            return {};
        }

        Interval Combine( const Interval& other ) const noexcept
        {
            auto start = lower( ) <= other.lower( ) ? lower( ) : other.lower( );
            auto end = upper( ) >= other.upper( ) ? upper( ) : other.upper( );
            return { start, end };
        }
        
    };
}

namespace boost::icl
{
    template<>
    struct interval_traits< Harlinn::Common::Core::Interval >
    {
        using interval_type = Harlinn::Common::Core::Interval;
        using domain_type = Harlinn::Common::Core::DateTime;
        using domain_compare = std::less<domain_type>;
        static interval_type construct( const domain_type& lo, const domain_type& up )
        {
            return interval_type( lo, up );
        }
        
        static domain_type lower( const interval_type& inter_val ) 
        { 
            return inter_val.lower( ); 
        };
        static domain_type upper( const interval_type& inter_val ) 
        { 
            return inter_val.upper( ); 
        };
    };

    template<>
    struct interval_bound_type<Harlinn::Common::Core::Interval>
    {
        using type = interval_bound_type;
        BOOST_STATIC_CONSTANT( bound_type, value = interval_bounds::static_right_open );
    };
}

namespace Harlinn::Common::Core
{

    class Stopwatch
    {
        long long elapsedTicks_;
        long long startedAt_;
        bool isRunning_;

        static long long frequency_;
    public:

        HCC_EXPORT static const bool IsHighResolution;
    private:
        static double tickFrequency_;
        static bool InitializeStopwatch( );

        long long GetElapsedDateTimeTicks( ) const;

    public:
        HCC_EXPORT static long long GetTimestamp( );
        HCC_EXPORT static double GetTimestampInSeconds( );
        HCC_EXPORT static double GetTimestampInMilliseconds( );
        HCC_EXPORT static long long Frequency( );
        HCC_EXPORT Stopwatch( );
        HCC_EXPORT void Start( );
        static Stopwatch StartNew( )
        {
            Stopwatch result;
            result.Start( );
            return result;
        }

        HCC_EXPORT void Stop( );
        HCC_EXPORT void Reset( );
        HCC_EXPORT void Restart( );
        HCC_EXPORT bool IsRunning( ) const;

        HCC_EXPORT TimeSpan Elapsed( ) const;
        HCC_EXPORT double TotalSeconds( ) const;
        HCC_EXPORT long long ElapsedMilliseconds( ) const;
        HCC_EXPORT long long ElapsedTicks( ) const;
    };
}

namespace std
{
    template<> struct hash<Harlinn::Common::Core::TimeSpan>
    {
        std::size_t operator()( const Harlinn::Common::Core::TimeSpan& timeSpan ) const noexcept
        {
            return timeSpan.hash( );
        }
    };

    template<> struct hash<Harlinn::Common::Core::DateTime>
    {
        std::size_t operator()( const Harlinn::Common::Core::DateTime& dateTime ) const noexcept
        {
            return dateTime.hash( );
        }
    };

    template<typename CharT> 
    struct formatter<Harlinn::Common::Core::DateTime, CharT> 
    {
        using ChronoFormatter = std::formatter<std::chrono::system_clock::time_point,CharT>;
        ChronoFormatter chronoFormatter_;

        constexpr auto parse( std::basic_format_parse_context<CharT>& ctx )
        {
            return chronoFormatter_.parse( ctx );
        }

        template<typename FormatContextT>
        auto format( const Harlinn::Common::Core::DateTime& dateTime, FormatContextT& ctx ) const
        {
            auto timePoint = dateTime.ToTimePoint( );
            return chronoFormatter_.format( timePoint, ctx );
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::TimeSpan, CharT>
    {
        using ChronoFormatter = std::formatter<std::chrono::system_clock::duration, CharT>;
        ChronoFormatter chronoFormatter_;

        constexpr auto parse( std::basic_format_parse_context<CharT>& ctx )
        {
            return chronoFormatter_.parse( ctx );
        }

        template<typename FormatContextT>
        auto format( const Harlinn::Common::Core::TimeSpan& timeSpan, FormatContextT& ctx ) const
        {
            std::chrono::system_clock::duration duration( timeSpan.Ticks() - Harlinn::Common::Core::TimeSpan::UnixEpoch );
            return chronoFormatter_.format( duration, ctx );
        }
    };




}


#endif
