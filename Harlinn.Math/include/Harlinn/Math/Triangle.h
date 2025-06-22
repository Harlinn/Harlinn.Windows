#pragma once
#ifndef HARLINN_MATH_TRIANGLE_H_
#define HARLINN_MATH_TRIANGLE_H_

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
    struct Triangle;

    namespace Internal
    {
        struct TriangleSimdBase
        {
        };
        struct TriangleBase
        {
        };
    }

    template<typename T>
    concept TriangleSimdType = std::is_base_of_v<Internal::TriangleSimdBase, T>;
    template<typename T>
    concept TriangleType = std::is_base_of_v<Internal::TriangleBase, T>;

    template<typename T>
    concept TriangleOrTriangleSimdType = TriangleSimdType<T> || TriangleType<T>;

    namespace Internal
    {
        template<TriangleSimdType T>
        const T& ToSimdType( const T& line ) noexcept
        {
            return line;
        }
        template<TriangleType T>
        const typename T::Simd ToSimdType( const T& line ) noexcept
        {
            return line.ToSimd( );
        }
    }


    template<FloatingPointType T, size_t N>
    struct TriangleSimd : public Internal::TriangleSimdBase
    {
    public:
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using ArrayType = Point::ArrayType;
        using Triangle = Math::Triangle<T, N>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );
        static constexpr value_type Half = static_cast< value_type >( .5 );

        std::array<Point, 3> v;

        TriangleSimd( ) noexcept
            : v{ Point( ArrayType{ Zero, Zero, } ), Point( ArrayType{ One, Zero, } ), Point( ArrayType{ Zero, One, } ) }
        {
        }

        TriangleSimd( const std::array<Point, 3>& pts ) noexcept
            : v( pts )
        {
        }

        TriangleSimd( const Point& p1, const Point& p2, const Point& p3 ) noexcept
            : v{ p1, p2, p3 }
        {
        }

        TriangleSimd( const Triangle& triangle ) noexcept;


    };


    template<FloatingPointType T, size_t N>
    struct Triangle : public Internal::TriangleBase
    {
    public:
        using Point = Math::Point<T, N>;
        using Vector = Math::Vector<T, N>;
        using ArrayType = Point::ArrayType;
        using Simd = TriangleSimd<T, N>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );

        std::array<Point, 3> v;

        Triangle( ) noexcept
            : v{ Point( ArrayType{ Zero, Zero, } ), Point( ArrayType{ One, Zero, } ), Point( ArrayType{ Zero, One, } ) }
        { }

        Triangle( const std::array<Point, 3>& pts ) noexcept
            : v( pts )
        { }

        Triangle( const Point& p1, const Point& p2, const Point& p3 ) noexcept
            : v{ p1, p2, p3 }
        { }

        Triangle( const Simd& simd ) noexcept
            : v{ simd.v[ 0 ], simd.v[ 1 ], simd.v[ 2 ] }
        { }

        Simd ToSimd( ) const noexcept
        {
            return Simd( Internal::ToSimdType( v[ 0 ] ), Internal::ToSimdType( v[ 1 ] ), Internal::ToSimdType( v[ 2 ] ) );
        }


    };

    template<FloatingPointType T, size_t N>
    inline TriangleSimd<T, N>::TriangleSimd( const Triangle& triangle ) noexcept
        : v{ triangle.v[ 0 ], triangle.v[ 1 ], triangle.v[ 2 ] }
    { }


    template<FloatingPointType T>
    using Triangle2 = Triangle<T, 2>;
    using Triangle2f = Triangle2<float>;
    using Triangle2d = Triangle2<double>;

    template<FloatingPointType T>
    using Triangle3 = Triangle<T, 3>;
    using Triangle3f = Triangle3<float>;
    using Triangle3d = Triangle3<double>;

}

#endif
