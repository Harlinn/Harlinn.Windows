#pragma once
#ifndef HARLINN_MATH_LINE_H_
#define HARLINN_MATH_LINE_H_

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


#include "VectorMath.h"

namespace Harlinn::Math
{
    template<FloatingPointType T, size_t N>
    struct Line;

    namespace Internal
    {
        struct LineSimdBase
        { };
        struct LineBase
        { };
    }

    template<typename T>
    concept LineSimdType = std::is_base_of_v<Internal::LineSimdBase, T>;
    template<typename T>
    concept LineType = std::is_base_of_v<Internal::LineBase, T>;

    template<typename T>
    concept LineOrLineSimdType = LineSimdType<T> || LineType<T>;

    namespace Internal
    {
        template<LineSimdType T>
        const T& ToSimdType( const T& line ) noexcept
        {
            return line;
        }
        template<LineType T>
        const typename T::Simd ToSimdType( const T& line ) noexcept
        {
            return line.ToSimd( );
        }
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
    struct LineSimd : public Internal::LineSimdBase
    {
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using Line = Math::Line<T, N>;
        using value_type = T;

        static constexpr size_t Dimensions = N;
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

        static constexpr size_t Dimensions = N;

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

    };

    template<FloatingPointType T, size_t N>
    inline LineSimd<T,N>::LineSimd( const Line& l ) noexcept
        : origin( l.origin ), direction( l.direction )
    { }

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