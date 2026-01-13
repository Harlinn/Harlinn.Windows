#pragma once
#ifndef HARLINN_MATH_DISTANCE_H_
#define HARLINN_MATH_DISTANCE_H_

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

#include "Primitives.h"

namespace Harlinn::Math
{
    /// <summary>
    /// Calculates the distance and the closest point on a line from a point. 
    /// </summary>
    template<FloatingPointType T, size_t dimensions> 
    class DistanceFromPointToLineResult
    {
    public:
        static constexpr size_t Dimensions = dimensions;
        using value_type = T;
        using Point = typename Math::Point<value_type, Dimensions>::Simd;
        using Line = typename Math::Line<value_type, Dimensions>::Simd;
    private:
        using Vector = Math::Vector<value_type, Dimensions>::Simd;
        Point closestPoint_;
        value_type distanceSquared_{};
        value_type distanceFromOrigin_{};
    public:
        DistanceFromPointToLineResult( ) noexcept = default;
        DistanceFromPointToLineResult( const Line& line, const Point& point ) noexcept
        {
            Vector diff = point - line.origin;
            distanceFromOrigin_ = ScalarDot( line.direction, diff ) / ScalarDot( line.direction, line.direction );
            closestPoint_ = line.origin + distanceFromOrigin_ * line.direction;
            distanceSquared_ = ScalarDistanceSquared( point, closestPoint_ );
        }

        /// <summary>
        /// The closest point on the line
        /// </summary>
        const Point& ClosestPoint( ) const
        {
            return closestPoint_;
        }

        /// <summary>
        /// Shortest distance squared between the line and the point.
        /// </summary>
        value_type DistanceSquared( ) const noexcept
        {
            return distanceSquared_;
        }

        /// <summary>
        /// Shortest distance between the line and the point.
        /// </summary>
        value_type Distance( ) const noexcept
        {
            return Sqrt( distanceSquared_ );
        }

        /// <summary>
        /// Distance from line origin to the closest point.
        /// </summary>
        value_type DistanceFromOrigin( ) const
        {
            return distanceFromOrigin_;
        }
    };

    /// <summary>
    /// Calculates the distance and the closest point on a line from a point. 
    /// </summary>
    template<PointOrPointSimdType PointT,LineOrLineSimdType LineT>
        requires std::is_same_v<typename PointT::value_type, typename LineT::value_type> && ( PointT::Size == LineT::Dimensions )
    DistanceFromPointToLineResult<typename PointT::value_type, PointT::Size> Distance( const PointT& point, const LineT& line ) noexcept
    {
        return DistanceFromPointToLineResult<typename PointT::value_type, PointT::Size>( Internal::ToSimdType( line ), Internal::ToSimdType( point ) );
    }

    /// <summary>
    /// Calculates the distance and the closest point on a line from a point. 
    /// </summary>
    template<PointOrPointSimdType PointT, LineOrLineSimdType LineT>
        requires std::is_same_v<typename PointT::value_type, typename LineT::value_type> && ( PointT::Size == LineT::Dimensions )
    DistanceFromPointToLineResult<typename PointT::value_type, PointT::Size> Distance( const LineT& line, const PointT& point ) noexcept
    {
        return DistanceFromPointToLineResult<typename PointT::value_type, PointT::Size>( Internal::ToSimdType( line ), Internal::ToSimdType( point ) );
    }

    /// <summary>
    /// Calculates the closest points and shortest distance between two lines. 
    /// </summary>
    template<FloatingPointType T, size_t dimensions>
    class DistanceFromLineToLineResult
    {
    public:
        static constexpr size_t Dimensions = dimensions;
        using value_type = T;
        using Point = typename Math::Point<value_type, Dimensions>::Simd;
        using Line = typename Math::Line<value_type, Dimensions>::Simd;
    private:
        using Vector = Math::Vector<value_type, Dimensions>::Simd;
        static constexpr value_type Zero = static_cast< value_type >( 0 );
        Point closestPoint1_;
        Point closestPoint2_;
        value_type distanceSquared_{};
        value_type distanceFromOrigin1_{};
        value_type distanceFromOrigin2_{};
        bool parallel_{};
    public:
        DistanceFromLineToLineResult( const Line& line1, const Line& line2 ) noexcept
        {
            Vector diff = line1.origin - line2.origin;
            value_type a00 = ScalarDot( line1.direction, line1.direction );
            value_type a01 = -ScalarDot( line1.direction, line2.direction );
            value_type a11 = ScalarDot( line2.direction, line2.direction );
            value_type b0 = ScalarDot( line1.direction, diff );
            value_type det = std::max( a00 * a11 - a01 * a01, Zero );
            value_type s0{}, s1{};

            if ( det > Zero )
            {
                // The lines are not parallel.
                T b1 = -ScalarDot( line2.direction, diff );
                s0 = ( a01 * b1 - a11 * b0 ) / det;
                s1 = ( a01 * b0 - a00 * b1 ) / det;
                parallel_ = false;
            }
            else
            {
                // Lines are parallel. Select any pair of closest points.
                s0 = -b0 / a00;
                s1 = Zero;
                parallel_ = true;
            }

            distanceFromOrigin1_ = s0;
            distanceFromOrigin2_ = s1;
            closestPoint1_ = line1.origin + s0 * line1.direction;
            closestPoint2_ = line2.origin + s1 * line2.direction;
            distanceSquared_ = ScalarDistanceSquared( closestPoint1_, closestPoint2_ );
        }

        /// <summary>
        /// The point on line1 closest to line2
        /// </summary>
        const Point& ClosestPoint1( ) const noexcept
        {
            return closestPoint1_;
        }
        /// <summary>
        /// The point on line2 closest to line1
        /// </summary>
        const Point& ClosestPoint2( ) const noexcept
        {
            return closestPoint2_;
        }

        /// <summary>
        /// Shortest distance squared between line1 and line2.
        /// </summary>
        value_type DistanceSquared( ) const noexcept
        {
            return distanceSquared_;
        }

        /// <summary>
        /// Shortest distance between line1 and line2.
        /// </summary>
        value_type Distance( ) const noexcept
        {
            return Sqrt( distanceSquared_ );
        }

        /// <summary>
        /// The distance from line1.origin to the point on line1 closest to line2
        /// </summary>
        value_type DistanceFromOrigin1( ) const noexcept
        {
            return distanceFromOrigin1_;
        }
        /// <summary>
        /// The distance from line2.origin to the point on line2 closest to line1
        /// </summary>
        value_type DistanceFromOrigin2( ) const noexcept
        {
            return distanceFromOrigin2_;
        }

        /// <summary>
        /// <c>true</c> if the lines are parallel, otherwise <c>false</c>.
        /// </summary>
        bool Parallel( ) const noexcept
        {
            return parallel_;
        }
    };

    /// <summary>
    /// Calculates the closest points and shortest distance between two lines. 
    /// </summary>
    template<LineOrLineSimdType LineT1, LineOrLineSimdType LineT2>
        requires std::is_same_v<typename LineT1::value_type, typename LineT2::value_type> && ( LineT1::Dimensions == LineT2::Dimensions )
    DistanceFromLineToLineResult<typename LineT1::value_type, LineT1::Dimensions> Distance( const LineT1& line1, const LineT2& line2 ) noexcept
    {
        return DistanceFromLineToLineResult<typename LineT1::value_type, LineT1::Dimensions>( Internal::ToSimdType( line1 ), Internal::ToSimdType( line2 ) );
    }


    /// <summary>
    /// Calculates the distance and the closest point on a segment from a point. 
    /// </summary>
    template<FloatingPointType T, size_t dimensions>
    class DistanceFromPointToSegmentResult
    {
    public:
        static constexpr size_t Dimensions = dimensions;
        using value_type = T;
        using Point = typename Math::Point<value_type, Dimensions>::Simd;
        using Segment = typename Math::Segment<value_type, Dimensions>::Simd;
    private:
        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );
        using Vector = Math::Vector<value_type, Dimensions>::Simd;
        Point closestPoint_;
        value_type distanceSquared_;
        value_type fraction_;
    public:
        DistanceFromPointToSegmentResult( const Segment& segment, const Point& point )
        {
            Vector direction = segment.points[ 1 ] - segment.points[ 0 ];
            Vector diff = point - segment.points[ 1 ];
            value_type t = ScalarDot( direction, diff );
            if ( t >= Zero )
            {
                fraction_ = One;
                closestPoint_ = segment.points[ 1 ];
            }
            else
            {
                diff = point - segment.points[ 0 ];
                t = ScalarDot( direction, diff );
                if ( t <= Zero )
                {
                    fraction_ = Zero;
                    closestPoint_ = segment.points[ 0 ];
                }
                else
                {
                    value_type lengthSquared = ScalarLengthSquared( direction );
                    if ( lengthSquared > Zero )
                    {
                        t /= lengthSquared;
                        fraction_ = t;
                        closestPoint_ = segment.points[ 0 ] + t * direction;
                    }
                    else
                    {
                        fraction_ = Zero;
                        closestPoint_ = segment.points[ 0 ];
                    }
                }
            }

            distanceSquared_ = ScalarDistanceSquared( point, closestPoint_ );
        }

        /// <summary>
        /// The closest point on the segment
        /// </summary>
        const Point& ClosestPoint( ) const
        {
            return closestPoint_;
        }

        /// <summary>
        /// Shortest distance squared between the segment and the point.
        /// </summary>
        value_type DistanceSquared( ) const noexcept
        {
            return distanceSquared_;
        }
        /// <summary>
        /// Shortest distance between the segment and the point.
        /// </summary>
        value_type Distance( ) const noexcept
        {
            return Sqrt( distanceSquared_ );
        }

        /// <summary>
        /// Returns the fractional position of the closest point on the segment.
        /// If 0 then segment.points[ 0 ] is the closest point, or if 1
        /// then segment.points[ 1 ] is the closest point.
        /// </summary>
        value_type Fraction( ) const
        {
            return fraction_;
        }
    };

    /// <summary>
    /// Calculates the distance and the closest point on a segment from a point. 
    /// </summary>
    template<PointOrPointSimdType PointT, SegmentOrSegmentSimdType SegmentT>
        requires std::is_same_v<typename PointT::value_type, typename SegmentT::value_type> && ( PointT::Size == SegmentT::Dimensions )
    DistanceFromPointToSegmentResult<typename PointT::value_type, PointT::Size> Distance( const PointT& point, const SegmentT& segment ) noexcept
    {
        return DistanceFromPointToSegmentResult<typename PointT::value_type, PointT::Size>( Internal::ToSimdType( segment ), Internal::ToSimdType( point ) );
    }

    /// <summary>
    /// Calculates the distance and the closest point on a segment from a point. 
    /// </summary>
    template<SegmentOrSegmentSimdType SegmentT, PointOrPointSimdType PointT>
        requires std::is_same_v<typename PointT::value_type, typename SegmentT::value_type> && ( PointT::Size == SegmentT::Dimensions )
    DistanceFromPointToSegmentResult<typename PointT::value_type, PointT::Size> Distance( const SegmentT& segment, const PointT& point ) noexcept
    {
        return DistanceFromPointToSegmentResult<typename PointT::value_type, PointT::Size>( Internal::ToSimdType( segment ), Internal::ToSimdType( point ) );
    }

    /// <summary>
    /// Calculates the closest points and shortest distance between two segments. 
    /// </summary>
    template<FloatingPointType T, size_t dimensions>
    class DistanceFromSegmentToSegmentResult
    {
    public:
        static constexpr size_t Dimensions = dimensions;
        using value_type = T;
        using Point = typename Math::Point<value_type, Dimensions>::Simd;
        using Segment = typename Math::Segment<value_type, Dimensions>::Simd;
    private:
        using Vector = Math::Vector<value_type, Dimensions>::Simd;
        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );
        Point closestPoint1_;
        Point closestPoint2_;
        value_type distanceSquared_{};
        value_type fraction1_{};
        value_type fraction2_{};
        bool parallel_{};
    public:

        DistanceFromSegmentToSegmentResult( const Segment& segment1, const Segment& segment2 ) noexcept
        {
            Vector v1 = segment1.points[ 1 ] - segment1.points[ 0 ];
            Vector v2 = segment2.points[ 1 ] - segment2.points[ 0 ];
            Vector vs = segment1.points[ 0 ] - segment2.points[ 0 ];
            value_type a = ScalarDot( v1, v1 );
            value_type b = ScalarDot( v1, v2 );
            value_type c = ScalarDot( v2, v2 );
            value_type d = ScalarDot( v1, vs );
            value_type e = ScalarDot( v2, vs );
            value_type det = a * c - b * b;
            value_type s, t; 

            
            if ( det > Zero )
            {
                parallel_ = false;
                auto bte = b * e;
                auto ctd = c * d;
                if ( bte <= ctd )
                {
                    s = Zero;
                    if ( e <= Zero )
                    {
                        t = Zero;
                        auto nd = -d;
                        if ( nd >= a )
                        {
                            s = One;
                        }
                        else if ( nd > Zero )
                        {
                            s = nd / a;
                        }
                    }
                    else if ( e < c )
                    {
                        t = e / c;
                    }
                    else
                    {
                        t = One;
                        auto bmd = b - d;
                        if ( bmd >= a )
                        {
                            s = One;
                        }
                        else if ( bmd > Zero )
                        {
                            s = bmd / a;
                        }
                    }
                }
                else
                {
                    s = bte - ctd;
                    if ( s >= det )
                    {
                        s = One;
                        auto bpe = b + e;
                        if ( bpe <= Zero )
                        {
                            t = Zero;
                            auto nd = -d;
                            if ( nd <= Zero )
                            {
                                s = Zero;
                            }
                            else if ( nd < a )
                            {
                                s = nd / a;
                            }
                        }
                        else if ( bpe < c )
                        {
                            t = bpe / c;
                        }
                        else
                        {
                            t = One;
                            auto bmd = b - d;
                            if ( bmd <= Zero )
                            {
                                s = Zero;
                            }
                            else if ( bmd < a )
                            {
                                s = bmd / a;
                            }
                        }
                    }
                    else
                    {
                        auto ate = a * e;
                        auto btd = b * d;
                        if ( ate <= btd )
                        {
                            t = Zero;
                            auto nd = -d;
                            if ( nd <= Zero )
                            {
                                s = Zero;
                            }
                            else if ( nd >= a )
                            {
                                s = One;
                            }
                            else
                            {
                                s = nd / a;
                            }
                        }
                        else
                        {
                            t = ate - btd;
                            if ( t >= det )
                            {
                                t = One;
                                auto bmd = b - d;
                                if ( bmd <= Zero )
                                {
                                    s = Zero;
                                }
                                else if ( bmd >= a )
                                {
                                    s = One;
                                }
                                else
                                {
                                    s = bmd / a;
                                }
                            }
                            else
                            {
                                s /= det;
                                t /= det;
                            }
                        }
                    }
                }
            }
            else
            {
                parallel_ = true;
                if ( e <= Zero )
                {
                    t = Zero;
                    auto nd = -d;
                    if ( nd <= Zero )
                    {
                        s = Zero;
                    }
                    else if ( nd >= a )
                    {
                        s = One;
                    }
                    else
                    {
                        s = nd / a;
                    }
                }
                else if ( e >= c )
                {
                    t = One;
                    auto bmd = b - d;
                    if ( bmd <= Zero )
                    {
                        s = Zero;
                    }
                    else if ( bmd >= a )
                    {
                        s = One;
                    }
                    else
                    {
                        s = bmd / a;
                    }
                }
                else
                {
                    s = Zero;
                    t = e / c;
                }
            }

            fraction1_ = s;
            fraction2_ = t;
            closestPoint1_ = segment1.points[ 0 ] + s * v1;
            closestPoint2_ = segment2.points[ 0 ] + t * v2;
            distanceSquared_ = ScalarDistanceSquared( closestPoint1_, closestPoint2_ );
        }

        /// <summary>
        /// The point on segment1 closest to segment2
        /// </summary>
        const Point& ClosestPoint1( ) const noexcept
        {
            return closestPoint1_;
        }
        /// <summary>
        /// The point on segment2 closest to segment1
        /// </summary>
        const Point& ClosestPoint2( ) const noexcept
        {
            return closestPoint2_;
        }

        /// <summary>
        /// Shortest distance squared between segment1 and segment2.
        /// </summary>
        value_type DistanceSquared( ) const noexcept
        {
            return distanceSquared_;
        }

        /// <summary>
        /// Shortest distance between segment1 and segment2.
        /// </summary>
        value_type Distance( ) const noexcept
        {
            return Sqrt( distanceSquared_ );
        }

        /// <summary>
        /// Returns the fractional position of the closest point on the first segment.
        /// If 0 then segment1.points[ 0 ] is the closest point, or if 1
        /// then segment1.points[ 1 ] is the closest point.
        /// </summary>
        value_type Fraction1( ) const noexcept
        {
            return fraction1_;
        }
        /// <summary>
        /// Returns the fractional position of the closest point on the first segment.
        /// If 0 then segment2.points[ 0 ] is the closest point, or if 1
        /// then segment2.points[ 1 ] is the closest point.
        /// </summary>
        value_type Fraction2( ) const noexcept
        {
            return fraction2_;
        }

        /// <summary>
        /// <c>true</c> if the segments are parallel, otherwise <c>false</c>.
        /// </summary>
        bool Parallel( ) const noexcept
        {
            return parallel_;
        }
    };

    /// <summary>
    /// Calculates the closest points and shortest distance between two segments. 
    /// </summary>
    template<SegmentOrSegmentSimdType SegmentT1, SegmentOrSegmentSimdType SegmentT2>
        requires std::is_same_v<typename SegmentT1::value_type, typename SegmentT2::value_type> && ( SegmentT1::Dimensions == SegmentT2::Dimensions )
    DistanceFromSegmentToSegmentResult<typename SegmentT1::value_type, SegmentT1::Dimensions> Distance( const SegmentT1& segment1, const SegmentT2& segment2 ) noexcept
    {
        return DistanceFromSegmentToSegmentResult<typename SegmentT1::value_type, SegmentT1::Dimensions>( Internal::ToSimdType( segment1 ), Internal::ToSimdType( segment2 ) );
    }


}


#endif
