#pragma once
#ifndef __HOCITYPES_H__
#define __HOCITYPES_H__
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

#include <HOCITraits.h>

namespace Harlinn::OCI
{
    typedef Int32( __cdecl* FailoverCallbackFunction )( void* svcctx, void* envctx, void* fo_ctx, UInt32 fo_type, UInt32 fo_event );

    struct FailoverCallback
    {
        FailoverCallbackFunction failoverCallback;
        void* fo_ctx;
    };

    /// <summary>
    /// Number
    /// </summary>
    struct Number
    {
        static constexpr UInt32 Size = 22;
        Byte OCINumberPart[Size];

        constexpr Number( ) noexcept
            : OCINumberPart{}
        {
        }

    };

    /// <summary>
    /// Binary compatible with OCITime
    /// </summary>
    struct Time
    {
        /// <summary>
        /// hours; range is 0 <= hours <=23 
        /// </summary>
        Byte Hours;
        /// <summary>
        /// minutes; range is 0 <= minutes <= 59 
        /// </summary>
        Byte Minutes;
        /// <summary>
        /// seconds; range is 0 <= seconds <= 59 
        /// </summary>
        Byte Seconds;

        constexpr Time( ) noexcept
            : Hours( 0 ), Minutes( 0 ), Seconds( 0 )
        {
        }

        constexpr Time( const DateTime& datetime ) noexcept
            : Hours( static_cast<Byte>( datetime.Hour( ) ) ), Minutes( static_cast<Byte>( datetime.Minute( ) ) ), Seconds( static_cast<Byte>( datetime.Second( ) ) )
        {
        }

        Time& operator = ( const DateTime& datetime ) noexcept
        {
            Assign( datetime );
            return *this;
        }

        Common::Core::DateTime ToTime( ) const
        {
            return DateTime( 0, 0, 0, Hours, Minutes, Seconds, 0 );
        }

        constexpr bool IsEmpty( ) const noexcept
        {
            return Hours == 0 && Minutes == 0 && Seconds == 0;
        }

        void Assign( const DateTime& datetime ) noexcept
        {
            Hours = static_cast<Byte>( datetime.Hour( ) );
            Minutes = static_cast<Byte>( datetime.Minute( ) );
            Seconds = static_cast<Byte>( datetime.Second( ) );
        }

        void Assign( Byte hour, Byte minute, Byte second ) noexcept
        {
            Hours = hour;
            Minutes = minute;
            Seconds = second;
        }

        void GetTime( Byte& hour, Byte& minute, Byte& second ) const noexcept
        {
            hour = Hours;
            minute = Minutes;
            second = Seconds;
        }

    };

    /// <summary>
    /// Binary compatible with OCIDate
    /// </summary>
    struct Date
    {
        /// <summary>
        /// gregorian year; range is -4712 <= year <= 9999
        /// </summary>
        Int16 Year;
        /// <summary>
        /// month; range is 1 <= month < 12 
        /// </summary>
        Byte Month;
        /// <summary>
        /// day; range is 1 <= day <= 31 
        /// </summary>
        Byte Day;
        /// <summary>
        /// time
        /// </summary>
        OCI::Time Time;

        constexpr Date( ) noexcept
            : Year( 0 ), Month( 0 ), Day( 0 )
        {
        }

        Date( const DateTime& datetime ) noexcept
            : Year( 0 ), Month( 0 ), Day( 0 )
        {
            Assign( datetime );
        }

        Date& operator = ( const DateTime& datetime )
        {
            Assign( datetime );
            return *this;
        }

        Common::Core::DateTime ToDateTime( ) const
        {
            return DateTime( Year, Month, Day, Time.Hours, Time.Minutes, Time.Seconds, 0 );
        }

        void Assign( const DateTime& datetime ) noexcept
        {
            Int32 year, month, day;
            datetime.GetYearMonthDay( year, month, day );
            Year = static_cast<Int16>( year );
            Month = static_cast<Byte>( month );
            Day = static_cast<Byte>( day );
            Time.Assign( datetime );
        }

        constexpr bool IsEmpty( ) const noexcept
        {
            return Year == 0 && Month == 0 && Day == 0 && Time.IsEmpty( );
        }

        void GetTime( Byte& hour, Byte& minute, Byte& second ) const noexcept
        {
            Time.GetTime( hour, minute, second );
        }
        void SetTime( Byte hour, Byte minute, Byte second )
        {
            Time.Assign( hour, minute, second );
        }

        void GetDateTime( short& year, Byte& month, Byte& day, Byte& hour, Byte& minute, Byte& second ) const noexcept
        {
            year = Year;
            month = Month;
            day = Day;
            Time.GetTime( hour, minute, second );
        }

        void SetDateTime( short year, Byte month, Byte day, Byte hour, Byte minute, Byte second ) noexcept
        {
            year = Year;
            month = Month;
            day = Day;
            Time.Assign( hour, minute, second );
        }

        void GetDate( short& year, Byte& month, Byte& day ) const noexcept
        {
            year = Year;
            month = Month;
            day = Day;
        }

        void SetDate( short year, Byte month, Byte day ) noexcept
        {
            Year = year;
            Month = month;
            Day = day;
        }

        Int64 Ticks( ) const
        {
            auto ticks = DateTime::DateToTicks( static_cast<Int32>( Year ), static_cast<Int32>( Month ), static_cast<Int32>( Day ) );
            ticks += ( static_cast<long long>( Time.Hours ) * TimeSpan::TicksPerHour ) +
                ( static_cast<long long>( Time.Minutes ) * TimeSpan::TicksPerMinute ) +
                ( static_cast<long long>( Time.Seconds ) * TimeSpan::TicksPerSecond );
            return ticks;
        }

        void SetTicks( Int64 ticks )
        {
            DateTime dt( ticks );
            int year, month, day;
            dt.GetYearMonthDay( year, month, day );
            auto hour = static_cast<Byte>( dt.Hour( ) );
            auto minute = static_cast<Byte>( dt.Minute( ) );
            auto second = static_cast<Byte>( dt.Second( ) );

            SetDateTime( year, month, day, hour, minute, second );
        }
    };



}

#endif
