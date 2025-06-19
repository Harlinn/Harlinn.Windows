#pragma once
#ifndef HCCLINE_H_
#define HCCLINE_H_

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


#include <HCCVectorMath.h>

namespace Harlinn::Common::Core::Math
{
    template<FloatingPointType T, size_t N>
    struct Line;

    namespace Internal
    {
        struct LineBase
        { };
    }

    template<FloatingPointType T, size_t N>
    struct LineSimd : public Internal::LineBase
    {
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using Line = Math::Line<T, N>;
        using value_type = T;

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

        class DistanceResult
        {
            value_type distanceSquared_;
            value_type distanceFromOrigin_;
            Point closestPoint_;
        public:
            DistanceResult( ) noexcept = default;
            DistanceResult( const LineSimd& line, const Point& point ) noexcept
            {
                Vector diff = point - line.origin;
                distanceFromOrigin_ = ScalarDot( line.direction, diff ) / ScalarDot( line.direction, line.direction );
                closestPoint_ = line.origin + distanceFromOrigin_ * line.direction;
                diff = point - closestPoint_;
                distanceSquared_ = ScalarDot( diff, diff );
            }

            value_type DistanceSquared( ) const noexcept
            {
                return distanceSquared_;
            }
            value_type Distance( ) const noexcept
            {
                return Sqrt(distanceSquared_);
            }

            value_type DistanceFromOrigin( ) const
            {
                return distanceFromOrigin_;
            }

            const Point& ClosestPoint( ) const
            {
                return closestPoint_;
            }
            
        };

        /// <summary>
        /// Retrieves the closest point and distance to <c>point</c> on the line.
        /// </summary>
        DistanceResult Distance( const Point& point ) const noexcept
        {
            return DistanceResult( *this, point );
        }

    };

    
    template<FloatingPointType T, size_t N>
    struct Line : public Internal::LineBase
    {
        using Point = Math::Point<T, N>;
        using Vector = Math::Vector<T, N>;
        using Simd = LineSimd<T, N>;
        using value_type = T;
        using DistanceResult = typename Simd::DistanceResult;

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
        DistanceResult Distance( const PT& point ) const noexcept
        {
            auto simd = ToSimd( );
            return simd.Distance( Internal::ToSimdType( point ) );
        }

    };

    template<FloatingPointType T, size_t N>
    inline LineSimd<T,N>::LineSimd( const Line& l ) noexcept
        : origin( l.origin ), direction( l.direction )
    { }

    template<FloatingPointType T>
    using Line2 = Line<T, 2>;

    template<FloatingPointType T>
    using Line3 = Line<T, 3>;

}


#endif