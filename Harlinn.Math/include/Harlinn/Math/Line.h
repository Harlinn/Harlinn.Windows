#pragma once
#ifndef HARLINN_MATH_LINE_H_
#define HARLINN_MATH_LINE_H_

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


#include "VectorMath.h"

namespace Harlinn::Math
{
    template<FloatingPointType T, size_t N>
    struct Line;

    namespace Internal
    {
        struct LineBase
        { };
    }

    /// <summary>
    /// An infinite line passing through <c>origin<c>
    /// with direction given by the unit vector <c>direction<c>.
    /// </summary>
    /// <typeparam name="T">
    /// double or float
    /// </typeparam>
    /// <typeparam name="N">
    /// Dimension count.
    /// </typeparam>
    template<FloatingPointType T, size_t N>
    struct LineSimd : public Internal::LineBase
    {
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using Line = Math::Line<T, N>;
        using value_type = T;

        static constexpr value_type Zero = static_cast< value_type >( 0 );

        /// <summary>
        /// Origin point
        /// </summary>
        Point origin;
        /// <summary>
        /// Unit length direction vector
        /// </summary>
        Vector direction;

        LineSimd( ) noexcept = default;
        LineSimd( const Point& o, const Vector& d ) noexcept
            : origin( o ), direction( d )
        { }

        LineSimd( const Point& p1, const Point& p2 ) noexcept
            : origin( p1 ), direction( Normalize( p1 - p2 ) )
        { }

        LineSimd( const Line& l ) noexcept;

        /// <summary>
        /// Calculates the distance and the closest point on a line from a point. 
        /// </summary>
        class PointDistanceResult
        {
            Point closestPoint_;
            value_type distanceSquared_{};
            value_type distanceFromOrigin_{};
        public:
            PointDistanceResult( ) noexcept = default;
            PointDistanceResult( const LineSimd& line, const Point& point ) noexcept
            {
                Vector diff = point - line.origin;
                distanceFromOrigin_ = ScalarDot( line.direction, diff ) / ScalarDot( line.direction, line.direction );
                closestPoint_ = line.origin + distanceFromOrigin_ * line.direction;
                diff = point - closestPoint_;
                distanceSquared_ = ScalarDot( diff, diff );
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
                return Sqrt(distanceSquared_);
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
        /// Retrieves the closest point and distance to <c>point</c> on the line.
        /// </summary>
        PointDistanceResult Distance( const Point& point ) const noexcept
        {
            return PointDistanceResult( *this, point );
        }

        /// <summary>
        /// Calculates the closest points and shortest distance between two lines. 
        /// </summary>
        class LineDistanceResult
        {
            Point closestPoint1_;
            Point closestPoint2_;
            value_type distanceSquared_{};
            value_type distanceFromOrigin1_{};
            value_type distanceFromOrigin2_{};
        public:
            LineDistanceResult( const LineSimd& line1, const LineSimd& line2 ) noexcept
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
                }
                else
                {
                    // Lines are parallel. Select any pair of closest points.
                    s0 = -b0 / a00;
                    s1 = Zero;
                }

                distanceFromOrigin1_ = s0;
                distanceFromOrigin2_ = s1;
                closestPoint1_ = line1.origin + s0 * line1.direction;
                closestPoint2_ = line2.origin + s1 * line2.direction;
                diff = closestPoint1_ - closestPoint2_;
                distanceSquared_ = ScalarLengthSquared( diff );
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
        };


        /// <summary>
        /// Retrieves the closest points and shortest distance between two lines.
        /// </summary>
        LineDistanceResult Distance( const LineSimd& other ) const noexcept
        {
            return LineDistanceResult( *this, other );
        }

        /// <summary>
        /// Retrieves the closest points and shortest distance between two lines.
        /// </summary>
        LineDistanceResult Distance( const Line& other ) const noexcept;


    };

    /// <summary>
    /// An infinite line passing through <c>origin<c>
    /// with direction given by the unit vector <c>direction<c>.
    /// </summary>
    /// <typeparam name="T">
    /// double or float
    /// </typeparam>
    /// <typeparam name="N">
    /// Dimension count.
    /// </typeparam>
    template<FloatingPointType T, size_t N>
    struct Line : public Internal::LineBase
    {
        using Point = Math::Point<T, N>;
        using Vector = Math::Vector<T, N>;
        using Simd = LineSimd<T, N>;
        using value_type = T;
        using PointDistanceResult = typename Simd::PointDistanceResult;
        using LineDistanceResult = typename Simd::LineDistanceResult;

        /// <summary>
        /// Origin point
        /// </summary>
        Point origin;
        /// <summary>
        /// Unit length direction vector
        /// </summary>
        Vector direction;

        Line( ) noexcept = default;
        Line( const Point& o, const Vector& d ) noexcept
            : origin( o ), direction( d )
        { }

        Line( const Point& p1, const Point& p2 ) noexcept
            : origin( p1 ), direction( Normalize( p1 - p2 ) )
        { }

        Simd ToSimd( ) const noexcept
        {
            return Simd( Internal::ToSimdType( origin ), Internal::ToSimdType( direction ) );
        }

        /// <summary>
        /// Retrieves the closest point and distance to <c>point</c> on the line.
        /// </summary>
        template<PointOrPointSimdType PT>
            requires (PT::Size == N)
        PointDistanceResult Distance( const PT& point ) const noexcept
        {
            auto simd = ToSimd( );
            return simd.Distance( Internal::ToSimdType( point ) );
        }

        /// <summary>
        /// Retrieves the closest points and shortest distance between two lines.
        /// </summary>
        LineDistanceResult Distance( const Simd& other ) const noexcept
        {
            auto simd = ToSimd( );
            return simd.Distance( other );
        }

        /// <summary>
        /// Retrieves the closest points and shortest distance between two lines.
        /// </summary>
        LineDistanceResult Distance( const Line& other ) const noexcept
        {
            auto simd = ToSimd( );
            return simd.Distance( other.ToSimd( ) );
        }

    };

    template<FloatingPointType T, size_t N>
    inline LineSimd<T,N>::LineSimd( const Line& l ) noexcept
        : origin( l.origin ), direction( l.direction )
    { }

    template<FloatingPointType T, size_t N>
    LineSimd<T, N>::LineDistanceResult LineSimd<T, N>::Distance( const Line& other ) const noexcept
    {
        return Distance( other.ToSimd( ) );
    }


    template<FloatingPointType T>
    using Line2 = Line<T, 2>;
    using Line2f = Line2<float>;
    using Line2d = Line2<double>;

    template<FloatingPointType T>
    using Line3 = Line<T, 3>;
    using Line3f = Line3<float>;
    using Line3d = Line3<double>;
}


#endif