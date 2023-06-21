#pragma once
#ifndef __HCCDATETIME_H__
#define __HCCDATETIME_H__

#include <HCCLib.h>

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


    class DateTime;
    class TimeSpan : public TimeBase
    {
        friend class DateTime;
    public:

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

        HCC_EXPORT static TimeSpan Interval( double theValue, int theScale );
    public:
        HCC_EXPORT static long long TimeToTicks( int days, int hours, int minutes, int seconds = 0, int milliseconds = 0 );

        constexpr TimeSpan( ) noexcept
            : ticks_( 0 )
        {

        }

        constexpr explicit TimeSpan( long long ticks )
            : ticks_( ticks )
        {

        }

        TimeSpan( int hours, int minutes, int seconds )
            : ticks_( TimeToTicks( 0, hours, minutes, seconds ) )
        {

        }

        TimeSpan( int days, int hours, int minutes, int seconds )
            : ticks_( TimeToTicks( days, hours, minutes, seconds ) )
        {

        }

        TimeSpan( int days, int hours, int minutes, int seconds, int milliseconds )
            : ticks_( TimeToTicks( days, hours, minutes, seconds, milliseconds ) )
        {

        }

        constexpr size_t hash( ) const noexcept
        {
            auto x = ( ticks_ ^ ( ticks_ >> 30 ) ) * UINT64_C( 0xbf58476d1ce4e5b9 );
            x = ( x ^ ( x >> 27 ) ) * UINT64_C( 0x94d049bb133111eb );
            x = x ^ ( x >> 31 );
            return x;
        }

        static TimeSpan UserTime( )
        {
            Int64 creationTime;
            Int64 exitTime;
            Int64 kernelTime;
            Int64 userTime;
            GetThreadTimes( GetCurrentThread( ), (LPFILETIME)&creationTime, (LPFILETIME)&exitTime, (LPFILETIME)&kernelTime, (LPFILETIME)&userTime );
            return TimeSpan( userTime );
        }

        constexpr long long Ticks( ) const noexcept
        {
            return ticks_;
        }

        constexpr int Days( ) const noexcept
        {
            return static_cast<int>( ticks_ / TicksPerDay );
        }

        constexpr int Hours( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerHour ) % 24 );
        }

        constexpr int Milliseconds( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerMillisecond ) % 1000 );
        }

        constexpr int Minutes( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerMinute ) % 60 );
        }

        constexpr int Seconds( ) const noexcept
        {
            return static_cast<int>( ( ticks_ / TicksPerSecond ) % 60 );
        }

        constexpr double TotalDays( ) const noexcept
        {
            return ( static_cast<double>( ticks_ ) ) / static_cast<double>( TicksPerDay );
        }

        constexpr double TotalHours( ) const noexcept
        {
            return ( static_cast<double>( ticks_ ) ) / static_cast<double>( TicksPerHour );
        }

        constexpr long long ToMilliseconds( ) const noexcept
        {
            return ticks_ / TicksPerMillisecond;
        }

        constexpr double TotalMilliseconds( ) const noexcept
        {
            auto result = ticks_ / TicksPerMillisecond;
            if ( result > MaxMilliSeconds )
            {
                return static_cast<double>( MaxMilliSeconds );
            }

            if ( result < MinMilliSeconds )
            {
                return static_cast<double>( MinMilliSeconds );
            }

            return static_cast<double>( result );
        }

        constexpr double TotalMinutes( ) const noexcept
        {
            return ( static_cast<double>( ticks_ ) ) / static_cast<double>( TicksPerMinute );
        }

        constexpr double TotalSeconds( ) const noexcept
        {
            return ( static_cast<double>( ticks_ ) ) / static_cast<double>( TicksPerSecond );
        }

        constexpr TimeSpan Add( const TimeSpan& other ) const noexcept
        {
            return TimeSpan( ticks_ + other.ticks_ );
        }

        static constexpr int Compare( const TimeSpan& t1, const TimeSpan& t2 ) noexcept
        {
            if ( t1.ticks_ > t2.ticks_ )
            {
                return 1;
            }
            if ( t1.ticks_ < t2.ticks_ )
            {
                return -1;
            }
            return 0;
        }

        constexpr int CompareTo( const TimeSpan& value ) const noexcept
        {
            if ( ticks_ > value.ticks_ )
            {
                return 1;
            }
            if ( ticks_ < value.ticks_ )
            {
                return -1;
            }
            return 0;
        }

        static TimeSpan FromDays( double value )
        {
            return Interval( value, MillisPerDay );
        }

        constexpr TimeSpan Duration( ) const noexcept
        {
            return TimeSpan( ticks_ >= 0 ? ticks_ : -ticks_ );
        }


        static TimeSpan FromHours( double value )
        {
            return Interval( value, MillisPerHour );
        }

        static TimeSpan FromMilliseconds( double value )
        {
            return Interval( value, 1 );
        }

        static TimeSpan FromMinutes( double value )
        {
            return Interval( value, MillisPerMinute );
        }

        constexpr TimeSpan Negate( ) const noexcept
        {
            return TimeSpan( -ticks_ );
        }

        static TimeSpan FromSeconds( double value )
        {
            return Interval( value, MillisPerSecond );
        }

        constexpr TimeSpan Subtract( const TimeSpan& other ) const noexcept
        {
            return TimeSpan( ticks_ - other.ticks_ );
        }

        static TimeSpan FromTicks( long long value )
        {
            return TimeSpan( value );
        }

        constexpr TimeSpan& operator += ( const TimeSpan& other ) noexcept
        {
            ticks_ += other.ticks_;
            return *this;
        }

        constexpr TimeSpan operator + ( const TimeSpan& other ) const noexcept
        {
            return TimeSpan(ticks_ + other.ticks_ );
        }

        constexpr TimeSpan& operator -= ( const TimeSpan& other ) noexcept
        {
            ticks_ -= other.ticks_;
            return *this;
        }

        constexpr TimeSpan operator - ( const TimeSpan& other ) const noexcept
        {
            return TimeSpan( ticks_ - other.ticks_ );
        }


        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan& operator += ( const T& value ) const noexcept
        {
            ticks_ += static_cast<long long>( value );
            return *this;
        }

        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan operator + ( const T& value ) const noexcept
        {
            return TimeSpan( ticks_ + static_cast<long long>( value ) );
        }

        template<typename T>
            requires std::is_integral_v<T>
        friend constexpr TimeSpan operator + ( const T& value, const TimeSpan& timeSpan ) noexcept
        {
            return TimeSpan( static_cast<long long>( value ) + timeSpan.ticks_ );
        }

        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan& operator -= ( const T& value ) const noexcept
        {
            ticks_ -= static_cast<long long>( value );
            return *this;
        }

        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan operator - ( const T& value ) const noexcept
        {
            return TimeSpan( ticks_ - static_cast<long long>( value ) );
        }

        template<typename T>
            requires std::is_integral_v<T>
        friend constexpr TimeSpan operator - ( const T& value, const TimeSpan& timeSpan ) noexcept
        {
            return TimeSpan( static_cast<long long>( value ) - timeSpan.ticks_ );
        }

        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan& operator *= ( const T& value ) const noexcept
        {
            ticks_ *= static_cast<long long>( value );
            return *this;
        }

        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan operator * ( const T& value ) const noexcept
        {
            return TimeSpan( ticks_ * static_cast<long long>( value ) );
        }

        template<typename T>
            requires std::is_integral_v<T>
        friend constexpr TimeSpan operator * ( const T& value, const TimeSpan& timeSpan ) noexcept
        {
            return TimeSpan( static_cast<long long>( value ) * timeSpan.ticks_ );
        }

        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan& operator /= ( const T& value ) const
        {
            ticks_ /= static_cast<long long>( value );
            return *this;
        }

        template<typename T>
            requires std::is_integral_v<T>
        constexpr TimeSpan operator / ( const T& value ) const
        {
            return TimeSpan( ticks_ / static_cast<long long>( value ) );
        }

        template<typename T>
            requires std::is_integral_v<T>
        friend constexpr TimeSpan operator / ( const T& value, const TimeSpan& timeSpan )
        {
            return TimeSpan( static_cast<long long>( value ) / timeSpan.ticks_ );
        }

        explicit constexpr operator bool( ) const noexcept
        {
            return ticks_ != 0;
        }

        constexpr bool operator == ( const TimeSpan& other ) const noexcept
        {
            return ticks_ == other.ticks_;
        }
        constexpr bool operator != ( const TimeSpan& other ) const noexcept
        {
            return ticks_ != other.ticks_;
        }
        constexpr bool operator <  ( const TimeSpan& other ) const noexcept
        {
            return ticks_ < other.ticks_;
        }
        constexpr bool operator <= ( const TimeSpan& other ) const noexcept
        {
            return ticks_ <= other.ticks_;
        }
        constexpr bool operator >  ( const TimeSpan& other ) const noexcept
        {
            return ticks_ > other.ticks_;
        }
        constexpr bool operator >= ( const TimeSpan& other ) const noexcept
        {
            return ticks_ >= other.ticks_;
        }

        constexpr std::chrono::system_clock::duration ToDuration( ) const noexcept
        {
            return std::chrono::system_clock::duration( Ticks( ) - UnixEpoch );
        }


        HCC_EXPORT std::string ToAnsiString( ) const;
        HCC_EXPORT std::string ToAnsiString( const std::string& format ) const;

        HCC_EXPORT WideString ToWideString( ) const;
        HCC_EXPORT WideString ToWideString( const WideString& format ) const;

        HCC_EXPORT WideString ToString( ) const;
        HCC_EXPORT WideString ToString( const WideString& format ) const;

        HCC_EXPORT static bool TryParse( const wchar_t* text, TimeSpan& result );
        HCC_EXPORT static bool TryParse( const char* text, TimeSpan& result );
        HCC_EXPORT bool TryParse( const WideString& text, TimeSpan& result );
        HCC_EXPORT bool TryParse( const std::string& text, TimeSpan& result );

        HCC_EXPORT static TimeSpan Parse( const wchar_t* text );
        HCC_EXPORT static TimeSpan Parse( const char* text );
        HCC_EXPORT static TimeSpan Parse( const WideString& text );
        HCC_EXPORT static TimeSpan Parse( const std::string& text );


        friend std::ostream& operator << ( std::ostream& stream, const TimeSpan& timeSpan )
        {
            auto str = timeSpan.ToAnsiString( );
            stream << str;
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

        HCC_EXPORT std::string DateToAnsiString( ) const;
        HCC_EXPORT WideString DateToString( ) const;

        HCC_EXPORT std::string TimeToAnsiString( ) const;
        HCC_EXPORT WideString TimeToString( ) const;

        HCC_EXPORT std::string ToAnsiString( ) const;
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

        HCC_EXPORT static bool TryParse( const wchar_t* text, DateTime& result );
        HCC_EXPORT static bool TryParse( const char* text, DateTime& result );
        HCC_EXPORT static DateTime Parse( const wchar_t* text );
        HCC_EXPORT static DateTime Parse( const char* text );

        HCC_EXPORT static bool TryParse( const WideString& text, DateTime& result );
        HCC_EXPORT static bool TryParse( const std::string& text, DateTime& result );
        HCC_EXPORT static DateTime Parse( const WideString& text );
        HCC_EXPORT static DateTime Parse( const std::string& text );



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

        constexpr std::chrono::system_clock::time_point ToTimePoint( ) const noexcept
        {
            return std::chrono::system_clock::time_point( std::chrono::system_clock::duration( Ticks( ) - UnixEpoch ) );
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

        friend std::ostream& operator << ( std::ostream& stream, const DateTime& dateTime )
        {
            auto str = dateTime.ToAnsiString( );
            stream << str;
            return stream;
        }
    };

    template<typename T>
    inline constexpr bool IsDateTime = std::is_same_v<std::remove_cv_t<T>, DateTime>;

    template<typename T>
        requires IsDateTime<T>
    inline constexpr T ByteSwap( const T value ) noexcept
    {
        return std::bit_cast<DateTime>( ByteSwap( std::bit_cast<UInt64>( value ) ) );
    }

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

    template<> struct formatter<Harlinn::Common::Core::DateTime>
    {
        using ChronoFormatter = std::formatter<std::chrono::system_clock::time_point>;
        ChronoFormatter chronoFormatter_;

        constexpr auto parse( std::format_parse_context& ctx )
        {
            return chronoFormatter_.parse( ctx );
        }

        auto format( const Harlinn::Common::Core::DateTime& dateTime, std::format_context& ctx )
        {
            auto timePoint = dateTime.ToTimePoint( );
            return chronoFormatter_.format( timePoint, ctx );
        }
    };


}


#endif
