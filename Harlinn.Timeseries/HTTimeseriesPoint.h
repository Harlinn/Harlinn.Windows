#pragma once
#ifndef __HTTIMESERIESPOINT_H__
#define __HTTIMESERIESPOINT_H__
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

#include <HTDef.h>

namespace Harlinn::Timeseries
{
    class TimeseriesPoint
    {
        DateTime timestamp_;
        Int64 flags_;
        double value_;
    public:
        using TypeList = Timeseries::TypeList<DateTime, Int64, double>;

        constexpr TimeseriesPoint( ) noexcept
            : flags_( 0 ), value_( 0.0 )
        {
        }

        constexpr explicit TimeseriesPoint( const DateTime& timestamp, double value = 0.0 ) noexcept
            : timestamp_( timestamp ), flags_( 0 ), value_( value )
        {
        }

        constexpr explicit TimeseriesPoint( const DateTime& timestamp, Int64 flags, double value ) noexcept
            : timestamp_( timestamp ), flags_( flags ), value_( value )
        {
        }

        auto operator<=>( const TimeseriesPoint& ) const = default;

        constexpr const DateTime& Timestamp( ) const noexcept
        {
            return timestamp_;
        }
        void SetTimesetamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }

        constexpr Int64 Flags( ) const noexcept
        {
            return flags_;
        }
        void SetFlags( Int64 flags ) noexcept
        {
            flags_ = flags;
        }

        constexpr double Value( ) const noexcept
        {
            return value_;
        }
        void SetValue( double value ) noexcept
        {
            value_ = value;
        }

        void Assign( Int64 flags, double value ) noexcept
        {
            flags_ = flags;
            value_ = value;
        }
    };
}

#endif 

