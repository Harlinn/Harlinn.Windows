#pragma once
#ifndef __HTSEGMENT_H__
#define __HTSEGMENT_H__
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

#include <HCCDateTime.h>
#include <HCCException.h>
#include <HCCBinaryReader.h>
#include <HCCBinaryWriter.h>


namespace Harlinn::Timeseries
{
    template<typename T>
    concept PointType = requires( T t )
    {
        { t.Timestamp( ) } ->std::convertible_to<DateTime>;
        std::is_default_constructible_v<T>;
        std::is_standard_layout_v<T>;
    };



    enum class CompareResult
    {
        /// <summary>
        /// Timestamp of found element is less
        /// </summary>
        Less = -1,
        /// <summary>
        /// Timestamp of found element is equal
        /// </summary>
        Equal = 0,
        /// <summary>
        /// Timestamp of found element is greater
        /// Either the first timeseries point in the
        /// timeseseries or segment
        /// </summary>
        Greater = 1,
        /// <summary>
        /// Timeseries or segment is empty
        /// </summary>
        Empty = 2
    };


    class SearchResult
    {
        CompareResult compareResult_;
        size_t index_;
    public:
        constexpr SearchResult( ) noexcept
            : compareResult_( CompareResult::Empty ), index_( 0 )
        {
        }

        constexpr explicit SearchResult( CompareResult compareResult, size_t index = 0 ) noexcept
            : compareResult_( compareResult ), index_( index )
        {
        }

        constexpr explicit operator bool( ) const noexcept
        {
            return compareResult_ != CompareResult::Empty;
        }

        auto operator <=>( CompareResult compareResult ) const noexcept
        {
            return compareResult_ <=> compareResult;
        }

        constexpr CompareResult Result( ) const noexcept
        {
            return compareResult_;
        }
        void SetResult( CompareResult result ) noexcept
        {
            compareResult_ = result;
        }

        constexpr size_t Index( ) const noexcept
        {
            return index_;
        }
        void SetIndex( size_t index ) noexcept
        {
            index_ = index;
        }
        void Assign( CompareResult compareResult, size_t index = 0 ) noexcept
        {
            compareResult_ = compareResult;
            index_ = index;
        }
        constexpr bool IsLess( ) const noexcept
        {
            return compareResult_ == CompareResult::Less;
        }
        constexpr bool IsEqual( ) const noexcept
        {
            return compareResult_ == CompareResult::Equal;
        }
        constexpr bool IsGreater( ) const noexcept
        {
            return compareResult_ == CompareResult::Greater;
        }
        constexpr bool IsEmpty( ) const noexcept
        {
            return compareResult_ == CompareResult::Empty;
        }
    };




    template<PointType TP, size_t maxSegmentSize >
    class Segment
    {
    public:
        constexpr static size_t MaxSize = maxSegmentSize;
        using Point = TP;
        using ArrayType = std::array<Point, MaxSize>;
        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;


    private:
        size_t size_;
        ArrayType points_;
    public:
        Segment( )
            : size_( 0 )
        {
        }

        void reset( )
        {
            size_ = 0;
        }

        void Assign( const Segment& other )
        {
            size_ = other.size_;
            std::copy( other.begin( ), other.end( ), begin( ) );
        }

        constexpr bool IntervalContains( const DateTime& timestamp ) const noexcept
        {
            return size_ ?
                timestamp >= points_[0].Timestamp( ) && timestamp <= points_[size_ - 1].Timestamp( )
                : false;
        }
        constexpr bool IntervalContains( const Point& point ) const noexcept
        {
            return IntervalContains( point.Timestamp( ) );
        }


        /// <summary>
        /// Returns a reference to the first element in the container.
        /// </summary>
        /// <remarks>
        /// Calling front on an empty container is undefined.
        /// </remarks>
        /// <returns>first element in the container</returns>
        Point& front( )
        {
            return points_[0];
        }
        /// <summary>
        /// Returns a reference to the last element in the container.
        /// </summary>
        /// <remarks>
        /// Calling back on an empty container is undefined.
        /// </remarks>
        /// <returns>last element in the container</returns>
        Point& back( )
        {
            return points_[size_ - 1];
        }
        /// <summary>
        /// Returns a reference to the first element in the container.
        /// </summary>
        /// <remarks>
        /// Calling front on an empty container is undefined.
        /// </remarks>
        /// <returns>first element in the container</returns>
        const Point& front( ) const
        {
            return points_[0];
        }
        /// <summary>
        /// Returns a reference to the last element in the container.
        /// </summary>
        /// <remarks>
        /// Calling back on an empty container is undefined.
        /// </remarks>
        /// <returns>last element in the container</returns>
        const Point& back( ) const
        {
            return points_[size_ - 1];
        }

        /// <summary>
        /// Returns the number of elements in the container
        /// </summary>
        /// <returns>The number of elements in the container</returns>
        constexpr size_t size( ) const noexcept
        {
            return size_;
        }

        constexpr bool empty( ) const noexcept
        {
            return size_ == 0;
        }
        constexpr bool full( ) const noexcept
        {
            return size_ == MaxSize;
        }

        Point* data( )
        {
            return points_.data( );
        }
        const Point* data( ) const
        {
            return points_.data( );
        }


        Point& operator[]( size_t index )
        {
            return points_[index];
        }
        const Point& operator[]( size_t index ) const
        {
            return points_[index];
        }


        constexpr iterator begin( ) noexcept
        {
            return points_.begin( );
        }
        constexpr const_iterator begin( ) const noexcept
        {
            return points_.begin( );
        }
        constexpr const_iterator cbegin( ) const noexcept
        {
            return points_.cbegin( );
        }

        constexpr iterator end( ) noexcept
        {
            return points_.begin( ) + size_;
        }
        constexpr const_iterator end( ) const noexcept
        {
            return points_.begin( ) + size_;
        }
        constexpr const_iterator cend( ) const noexcept
        {
            return points_.begin( ) + size_;
        }

        iterator find( const DateTime& timestamp )
        {
            return std::lower_bound( begin( ), end( ), timestamp,
                []( const Point& point, const DateTime& timestamp )
            {
                return point.Timestamp( ) < timestamp;
            } );
        }
        const_iterator find( const DateTime& timestamp ) const
        {
            return std::lower_bound( begin( ), end( ), timestamp,
                []( const Point& point, const DateTime& timestamp )
            {
                return point.Timestamp( ) < timestamp;
            } );
        }




        SearchResult Search( const DateTime& timestamp )
        {
            if ( size_ )
            {
                Point& last = points_[size_ - 1];
                if ( last.Timestamp( ) < timestamp )
                {
                    return SearchResult( CompareResult::Less, size_ - 1 );
                }
                else if ( last.Timestamp( ) == timestamp )
                {
                    return SearchResult( CompareResult::Equal, size_ - 1 );
                }
                else
                {
                    auto it = find( timestamp );
                    if ( it->Timestamp( ) == timestamp )
                    {
                        size_t offset = std::distance( begin( ), it );
                        return SearchResult( CompareResult::Equal, offset );
                    }
                    else if ( it != begin( ) )
                    {
                        size_t offset = std::distance( begin( ), it - 1 );
                        return SearchResult( CompareResult::Less, offset );
                    }
                    else
                    {
                        return SearchResult( CompareResult::Greater, 0 );
                    }
                }
            }
            else
            {
                return SearchResult( CompareResult::Empty, 0 );
            }
        }


        void insert( const Point& point, std::optional<Point>& overflow )
        {
            if ( size_ )
            {
                Point& last = points_[size_ - 1];
                if ( size_ < MaxSize )
                {
                    if ( last.Timestamp( ) < point.Timestamp( ) )
                    {
                        points_[size_] = point;
                        size_++;
                    }
                    else if ( last.Timestamp( ) == point.Timestamp( ) )
                    {
                        points_[size_ - 1] = point;
                    }
                    else if ( point.Timestamp( ) < points_[0].Timestamp( ) )
                    {
                        std::copy_backward( begin( ), end( ), end( ) + 1 );
                        points_[0] = point;
                        ++size_;
                    }
                    else if ( point.Timestamp( ) == points_[0].Timestamp( ) )
                    {
                        points_[0] = point;
                    }
                    else
                    {
                        auto it = find( point.Timestamp( ) );
                        if ( it->Timestamp( ) > point.Timestamp( ) )
                        {
                            std::copy_backward( it, end( ), end( ) + 1 );
                            ++size_;
                        }
                        *it = point;
                    }
                }
                else
                {
                    if ( last.Timestamp( ) < point.Timestamp( ) )
                    {
                        overflow = point;
                    }
                    else if ( last.Timestamp( ) == point.Timestamp( ) )
                    {
                        points_[size_ - 1] = point;
                    }
                    else if ( point.Timestamp( ) < points_[0].Timestamp( ) )
                    {
                        overflow = last;
                        std::copy_backward( begin( ), end( ) - 1, end( ) );
                        points_[0] = point;
                    }
                    else if ( point.Timestamp( ) == points_[0].Timestamp( ) )
                    {
                        points_[0] = point;
                    }
                    else
                    {
                        auto it = find( point.Timestamp( ) );
                        if ( it->Timestamp( ) > point.Timestamp( ) )
                        {
                            overflow = last;
                            std::copy_backward( it, end( ) - 1, end( ) );
                        }
                        *it = point;
                    }
                }
            }
            else
            {
                points_[0] = point;
                size_++;
            }
        }

        void insert( const Point& point )
        {
            if ( size_ )
            {
                Point& last = points_[size_ - 1];
                if ( size_ < MaxSize )
                {
                    if ( last.Timestamp( ) < point.Timestamp( ) )
                    {
                        points_[size_] = point;
                        size_++;
                    }
                    else if ( last.Timestamp( ) == point.Timestamp( ) )
                    {
                        points_[size_ - 1] = point;
                    }
                    else if ( point.Timestamp( ) < points_[0].Timestamp( ) )
                    {
                        std::copy_backward( begin( ), end( ), end( ) + 1 );
                        points_[0] = point;
                        ++size_;
                    }
                    else if ( point.Timestamp( ) == points_[0].Timestamp( ) )
                    {
                        points_[0] = point;
                    }
                    else
                    {
                        auto it = find( point.Timestamp( ) );
                        if ( it->Timestamp( ) > point.Timestamp( ) )
                        {
                            std::copy_backward( it, end( ), end( ) + 1 );
                            ++size_;
                        }
                        *it = point;
                    }
                }
                else
                {
                    if ( last.Timestamp( ) == point.Timestamp( ) )
                    {
                        points_[size_ - 1] = point;
                    }
                    else if ( point.Timestamp( ) == points_[0].Timestamp( ) )
                    {
                        points_[0] = point;
                    }
                    else
                    {
                        auto it = find( point.Timestamp( ) );
                        if ( it->Timestamp( ) > point.Timestamp( ) )
                        {
                            throw Exception( "Segment is full" );
                        }
                        *it = point;
                    }
                }
            }
            else
            {
                points_[0] = point;
                size_++;
            }
        }

        __forceinline void Append( const Point& point )
        {
            points_[size_] = point;
            size_++;
        }


        template<typename Func, typename ...Args>
        requires std::is_invocable_v<Func, const Point&, Args...>
            __forceinline size_t ForEach( Func&& func, Args&& ...args )
        {
            if ( full( ) )
            {
                for ( size_t i = 0; i < MaxSize; i++ )
                {
                    func( points_[i], std::forward<Args>( args )... );
                }
            }
            else
            {
                for ( size_t i = 0; i < size_; i++ )
                {
                    func( points_[i], std::forward<Args>( args )... );
                }
            }
            return size_;
        }

        template<typename Func, typename ...Args>
        requires std::is_invocable_v<Func, const Point&, Args...>
            __forceinline size_t ForEach1st( size_t index, Func&& func, Args&& ...args )
        {
            if ( index < size_ )
            {
                if ( full( ) )
                {
                    for ( size_t i = index; i < MaxSize; i++ )
                    {
                        func( points_[i], std::forward<Args>( args )... );
                    }
                }
                else
                {
                    for ( size_t i = index; i < size_; i++ )
                    {
                        func( points_[i], std::forward<Args>( args )... );
                    }
                }
                return size_ - index;
            }
            else
            {
                return 0;
            }
        }

        template<typename Func, typename ...Args>
        requires std::is_invocable_v<Func, const Point&, Args...>
            __forceinline size_t ForEach( const DateTime& end, Func&& func, Args&& ...args )
        {
            size_t result = 0;
            if ( full( ) )
            {
                for ( size_t i = 0; i < MaxSize; i++ )
                {
                    const Point& point = points_[i];
                    if ( point.Timestamp( ) < end )
                    {
                        func( points_[i], std::forward<Args>( args )... );
                        result++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                for ( size_t i = 0; i < size_; i++ )
                {
                    const Point& point = points_[i];
                    if ( point.Timestamp( ) < end )
                    {
                        func( points_[i], std::forward<Args>( args )... );
                        result++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return result;
        }

        template<typename Func, typename ...Args>
        requires std::is_invocable_v<Func, const Point&, Args...>
            __forceinline size_t ForEach1st( size_t index, const DateTime& end, Func&& func, Args&& ...args )
        {
            size_t result = 0;
            if ( index < size_ )
            {
                if ( full( ) )
                {
                    for ( size_t i = index; i < MaxSize; i++ )
                    {
                        const Point& point = points_[i];
                        if ( point.Timestamp( ) < end )
                        {
                            func( points_[i], std::forward<Args>( args )... );
                            result++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    for ( size_t i = index; i < size_; i++ )
                    {
                        const Point& point = points_[i];
                        if ( point.Timestamp( ) < end )
                        {
                            func( points_[i], std::forward<Args>( args )... );
                            result++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            return result;
        }



    };

    template<typename TimeseriesKeyT>
    class SegmentKey
    {
    public:
        using TimeseriesKeyType = TimeseriesKeyT;
    private:
        TimeseriesKeyType timeseries_;
        DateTime timestamp_;
    public:
        constexpr SegmentKey( ) noexcept
            : timeseries_( ), timestamp_( )
        {
        }

        constexpr explicit SegmentKey( const TimeseriesKeyType& timeseries ) noexcept
            : timeseries_( timeseries ), timestamp_( )
        {
        }

        constexpr explicit SegmentKey( const TimeseriesKeyType& timeseries, const DateTime& timestamp ) noexcept
            : timeseries_( timeseries ), timestamp_( timestamp )
        {
        }

        template<PointType T>
        constexpr SegmentKey( const TimeseriesKeyType& timeseries, const T& point ) noexcept
            : timeseries_( timeseries ), timestamp_( point.Timestamp( ) )
        {
        }


        auto operator<=>( const SegmentKey& ) const = default;
        auto operator<=>( const Guid& id ) const
        {
            return timeseries_ <=> id;
        }
        constexpr bool operator == ( const Guid& id ) const noexcept
        {
            return timeseries_ == id;
        }
        constexpr bool operator != ( const Guid& id ) const noexcept
        {
            return timeseries_ != id;
        }



        const TimeseriesKeyType& Timeseries( ) const noexcept
        {
            return timeseries_;
        }
        void SetTimeseries( const TimeseriesKeyType& timeseries ) noexcept
        {
            timeseries_ = timeseries;
        }

        const DateTime& Timestamp( ) const noexcept
        {
            return timestamp_;
        }
        void SetTimestamp( const DateTime& timestamp )
        {
            timestamp_ = timestamp;
        }

        void Assign( const TimeseriesKeyType& timeseries, const DateTime& timestamp )
        {
            timeseries_ = timeseries;
            timestamp_ = timestamp;
        }


    };


    template<typename DerivedT, typename TimeseriesKeyT, PointType TP, size_t maxSegmentSize >
    class SegmentContainer
    {
    public:
        using KeyType = SegmentKey<TimeseriesKeyT>;
        constexpr static size_t KeySize = sizeof( KeyType );
        using DataType = Segment<TP, maxSegmentSize>;
        constexpr static size_t DataSize = sizeof( DataType );

        constexpr static size_t MaxSegmentSize = maxSegmentSize;
        using Point = TP;
        using ArrayType = typename DataType::ArrayType;
        using DerivedType = DerivedT;
    public:
        SegmentContainer( )
        {
        }




    };


}

#endif
