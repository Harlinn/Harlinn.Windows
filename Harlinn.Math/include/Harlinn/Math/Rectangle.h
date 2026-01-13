#pragma once
#ifndef HARLINN_MATH_RECTANGLE_H_
#define HARLINN_MATH_RECTANGLE_H_

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
    struct Rectangle;

    namespace Internal
    {
        struct RectangleSimdBase
        {
        };
        struct RectangleBase
        {
        };
    }

    template<typename T>
    concept RectangleSimdType = std::is_base_of_v<Internal::RectangleSimdBase, T>;
    template<typename T>
    concept RectangleType = std::is_base_of_v<Internal::RectangleBase, T>;

    template<typename T>
    concept RectangleOrRectangleSimdType = RectangleSimdType<T> || RectangleType<T>;

    namespace Internal
    {
        template<RectangleSimdType T>
        const T& ToSimdType( const T& line ) noexcept
        {
            return line;
        }
        template<RectangleType T>
        const typename T::Simd ToSimdType( const T& line ) noexcept
        {
            return line.ToSimd( );
        }
    }


    template<FloatingPointType T, size_t N>
    struct RectangleSimd : public Internal::RectangleSimdBase
    {
    public:
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using Axis = std::array<Vector, 2>;
        using Extent = std::array<T, 2>;
        using Rectangle = Math::Rectangle<T, N>;
        using Vertices = std::array<Point, 4>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );

        Point center;
        Axis axis;
        Extent extent;

        RectangleSimd( ) noexcept
            : axis{ Vector::UnitX(), Vector::UnitY( ) }, extent( One )
        { }

        RectangleSimd( const Point& center, const Axis& axis, const Extent& extent )
            : center( center ), axis( axis ), extent( extent )
        { }

        RectangleSimd( const Rectangle& other ) noexcept;

        void ComputeVertices( Vertices& vertex ) const
        {
            Vector product0 = extent[ 0 ] * axis[ 0 ];
            Vector product1 = extent[ 1 ] * axis[ 1 ];
            Vector sum = product0 + product1;
            Vector dif = product0 - product1;

            vertex[ 0 ] = center - sum;
            vertex[ 1 ] = center + dif;
            vertex[ 2 ] = center - dif;
            vertex[ 3 ] = center + sum;
        }


    };


    template<FloatingPointType T, size_t N>
    struct Rectangle : public Internal::RectangleBase
    {
    public:
        using Point = Math::Point<T, N>;
        using Vector = Math::Vector<T, N>;
        using Axis = std::array<Vector, 2>;
        using Extent = std::array<T, 2>;
        using Simd = RectangleSimd<T, N>;
        using Vertices = std::array<Point, 4>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );

        Point center;
        Axis axis;
        Extent extent;

        Rectangle( ) noexcept
            : axis{ Vector::UnitX( ), Vector::UnitY( ) }, extent( One )
        { }

        Rectangle( const Point& center, const Axis& axis, const Extent& extent )
            : center( center ), axis( axis ), extent( extent )
        { }

        Rectangle( const Simd& simd ) noexcept
            : center( simd.center ), axis( simd.axis ), extent( simd.extent )
        { }

        Simd ToSimd( ) const noexcept
        {
            return Simd( Internal::ToSimdType( center ), Internal::ToSimdType( axis ), Internal::ToSimdType( extent ) );
        }

        void ComputeVertices( Vertices& vertex ) const
        {
            using V = typename Vector::Simd;
            V product0 = extent[ 0 ] * axis[ 0 ];
            V product1 = extent[ 1 ] * axis[ 1 ];
            V sum = product0 + product1;
            V dif = product0 - product1;

            V c = center;

            vertex[ 0 ] = c - sum;
            vertex[ 1 ] = c + dif;
            vertex[ 2 ] = c - dif;
            vertex[ 3 ] = c + sum;
        }


    };

    template<FloatingPointType T, size_t N>
    inline RectangleSimd<T, N>::RectangleSimd( const Rectangle& other ) noexcept
        : center( other.center ), axis( other.axis ), extent( other.extent )
    { }


    template<FloatingPointType T>
    using Rectangle2 = Rectangle<T, 2>;
    using Rectangle2f = Rectangle2<float>;
    using Rectangle2d = Rectangle2<double>;

    template<FloatingPointType T>
    using Rectangle3 = Rectangle<T, 3>;
    using Rectangle3f = Rectangle3<float>;
    using Rectangle3d = Rectangle3<double>;

}

#endif
