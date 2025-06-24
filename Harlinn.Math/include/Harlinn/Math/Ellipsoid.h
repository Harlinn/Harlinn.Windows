#pragma once
#ifndef HARLINN_MATH_ELLIPSOID_H_
#define HARLINN_MATH_ELLIPSOID_H_

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
    struct Hyperellipsoid;

    namespace Internal
    {
        struct HyperellipsoidSimdBase
        {
        };
        struct HyperellipsoidBase
        {
        };
    }

    template<typename T>
    concept HyperellipsoidSimdType = std::is_base_of_v<Internal::HyperellipsoidSimdBase, T>;
    template<typename T>
    concept HyperellipsoidType = std::is_base_of_v<Internal::HyperellipsoidBase, T>;

    template<typename T>
    concept HyperellipsoidOrHyperellipsoidSimdType = HyperellipsoidSimdType<T> || HyperellipsoidType<T>;

    namespace Internal
    {
        template<HyperellipsoidSimdType T>
        const T& ToSimdType( const T& line ) noexcept
        {
            return line;
        }
        template<HyperellipsoidType T>
        const typename T::Simd ToSimdType( const T& line ) noexcept
        {
            return line.ToSimd( );
        }
    }


    template<FloatingPointType T, size_t N>
    struct HyperellipsoidSimd : public Internal::HyperellipsoidSimdBase
    {
    public:
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using Axis = std::array<Vector, N>;
        using Extent = std::array<T, N>;
        using Hyperellipsoid = Math::Hyperellipsoid<T, N>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );

        Point center;
        Axis axis;
        Extent extent;

        HyperellipsoidSimd( ) noexcept
            : axis{ Vector::UnitX( ), Vector::UnitY( ) }, extent( One )
        {
        }

        HyperellipsoidSimd( const Point& center, const Axis& axis, const Extent& extent )
            : center( center ), axis( axis ), extent( extent )
        {
        }

        HyperellipsoidSimd( const Hyperellipsoid& other ) noexcept;

    };


    template<FloatingPointType T, size_t N>
    struct Hyperellipsoid : public Internal::HyperellipsoidBase
    {
    public:
        using Point = Math::Point<T, N>;
        using Vector = Math::Vector<T, N>;
        using Axis = std::array<Vector, N>;
        using Extent = std::array<T, N>;
        using Simd = HyperellipsoidSimd<T, N>;
        
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );

        Point center;
        Axis axis;
        Extent extent;

        Hyperellipsoid( ) noexcept
            : axis{ Vector::UnitX( ), Vector::UnitY( ) }, extent( One )
        {
        }

        Hyperellipsoid( const Point& center, const Axis& axis, const Extent& extent )
            : center( center ), axis( axis ), extent( extent )
        {
        }

        Hyperellipsoid( const Simd& simd ) noexcept
            : center( simd.center ), axis( simd.axis ), extent( simd.extent )
        {
        }

        Simd ToSimd( ) const noexcept
        {
            return Simd( Internal::ToSimdType( center ), Internal::ToSimdType( axis ), Internal::ToSimdType( extent ) );
        }

    };

    template<FloatingPointType T, size_t N>
    inline HyperellipsoidSimd<T, N>::HyperellipsoidSimd( const Hyperellipsoid& other ) noexcept
        : center( other.center ), axis( other.axis ), extent( other.extent )
    {
    }


    template<FloatingPointType T>
    using Ellipse2 = Hyperellipsoid<T, 2>;
    using Ellipse2f = Ellipse2<float>;
    using Ellipse2d = Ellipse2<double>;

    template<FloatingPointType T>
    using Ellipsoid3 = Hyperellipsoid<T, 3>;
    using Ellipsoid3f = Ellipsoid3<float>;
    using Ellipsoid3d = Ellipsoid3<double>;

}

#endif
