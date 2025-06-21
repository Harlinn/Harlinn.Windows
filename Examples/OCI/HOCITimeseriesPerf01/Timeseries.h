#pragma once
#ifndef __TIMESERIES_H__
#define __TIMESERIES_H__
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


#include <HCCGuid.h>

using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;
class TimeseriesPoint
{
    DateTime timestamp_;
    UInt64 flags_;
    double value_;
public:
    constexpr TimeseriesPoint( ) noexcept
        : flags_( 0 ), value_( 0 )
    {
    }

    constexpr TimeseriesPoint( DateTime timestamp, double value ) noexcept
        : timestamp_( timestamp ), flags_( 0 ), value_( value )
    {
    }
    constexpr TimeseriesPoint( DateTime timestamp, UInt64 flags, double value ) noexcept
        : timestamp_( timestamp ), flags_( flags ), value_( value )
    {
    }

    constexpr void Assign( DateTime timestamp, double value ) noexcept
    {
        timestamp_ = timestamp;
        flags_ = 0;
        value_ = value;
    }
    constexpr void Assign( DateTime timestamp, UInt64 flags, double value ) noexcept
    {
        timestamp_ = timestamp;
        flags_ = flags;
        value_ = value;
    }

    constexpr DateTime Timestamp( ) const noexcept
    {
        return timestamp_;
    }
    constexpr UInt64 Flags( ) const noexcept
    {
        return flags_;
    }
    constexpr double Value( ) const noexcept
    {
        return value_;
    }

    auto operator<=>( const TimeseriesPoint& ) const = default;

};


using TimeseriesPointArray = std::array<TimeseriesPoint, 8192*2>;

class TimeseriesPointSegment
{
    TimeseriesPointSegment* next_ = nullptr;
    TimeseriesPointSegment* previous_ = nullptr;
    Int64 optimisticLock_ = 0;
    size_t size_ = 0;
    TimeseriesPointArray data_;
    

public:
    static constexpr size_t MaxPoints = sizeof( TimeseriesPointArray )/sizeof( TimeseriesPoint );
    static constexpr size_t BufferSize = sizeof( size_ ) + sizeof( data_ );


    constexpr TimeseriesPointSegment() noexcept
        : next_(nullptr), previous_( nullptr ), optimisticLock_( 0 ), size_( 0 )
    { }

    constexpr TimeseriesPointSegment( Int64 optimisticLock ) noexcept
        : next_( nullptr ), previous_( nullptr ), optimisticLock_( optimisticLock ), size_( 0 )
    {
    }

    constexpr TimeseriesPointSegment( TimeseriesPointSegment* next, TimeseriesPointSegment* previous ) noexcept
        : next_( next ), previous_( previous ), optimisticLock_( 0 ), size_( 0 )
    {
    }

    ~TimeseriesPointSegment( ) noexcept
    {
        if ( next_ )
        {
            delete next_;
        }
    }

    constexpr size_t Size( ) const noexcept
    {
        return size_;
    }
    void SetSize( size_t size )
    {
        size_ = size;
    }


    Byte* Buffer( ) noexcept
    {
        return reinterpret_cast<Byte*>(&size_);
    }
    const Byte* Buffer( ) const noexcept
    {
        return reinterpret_cast<const Byte*>( &size_ );
    }

    constexpr const DateTime Key( ) const noexcept
    {
        return data_[0].Timestamp( );
    }


    constexpr TimeseriesPointSegment* Next( ) const noexcept
    {
        return next_;
    }

    void SetNext( TimeseriesPointSegment* next ) noexcept
    {
        next_ = next;
    }

    constexpr TimeseriesPointSegment* Previous( ) const noexcept
    {
        return previous_;
    }

    void SetPrevious( TimeseriesPointSegment* previous ) noexcept
    {
        previous_ = previous;
    }

    constexpr const TimeseriesPoint& operator[]( size_t index ) const noexcept
    {
        return data_[index];
    }
    constexpr TimeseriesPoint& operator[]( size_t index ) noexcept
    {
        return data_[index];
    }

    constexpr void Append( const TimeseriesPoint& point ) noexcept
    {
        data_[size_] = point;
        size_++;
    }

};


class TimeseriesPoints 
{
private:
    TimeseriesPointSegment* first_ = nullptr;
    TimeseriesPointSegment* last_ = nullptr;
    size_t size_;
public:
    constexpr TimeseriesPoints( )
        : first_(nullptr), last_( nullptr ), size_(0)
    { }

    TimeseriesPoints( const TimeseriesPoints& other ) = delete;
    TimeseriesPoints( TimeseriesPoints&& other ) noexcept
        : first_( other.first_ ), last_( other.last_ ), size_( other.size_ )
    {
        other.first_ = nullptr;
        other.last_ = nullptr;
        other.size_ = 0;
    }

    ~TimeseriesPoints( )
    {
        if ( first_ )
        {
            delete first_;
        }
    }

    TimeseriesPoints& operator = ( const TimeseriesPoints& other ) = delete;
    TimeseriesPoints& operator = ( TimeseriesPoints&& other ) noexcept
    {
        if ( this != &other )
        {
            if ( first_ )
            {
                delete first_;
            }
            first_ = other.first_;
            last_ = other.last_;
            size_ = other.size_;
            other.first_ = nullptr;
            other.last_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    constexpr size_t Size( ) const noexcept
    {
        return size_;
    }

    TimeseriesPointSegment* First( ) const
    {
        return first_;
    }

    TimeseriesPointSegment* Last( ) const
    {
        return last_;
    }


    void Append( std::unique_ptr<TimeseriesPointSegment>& segment )
    {
        size_ += segment->Size( );
        if ( last_ )
        {
            segment->SetNext( nullptr );
            segment->SetPrevious( last_ );
            last_->SetNext( segment.get( ) );
            last_ = segment.release( );
        }
        else
        {
            segment->SetNext( nullptr );
            segment->SetPrevious( nullptr );
            first_ = segment.release( );
            last_ = first_;
        }
    }


};

#endif
