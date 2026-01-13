#pragma once
#ifndef HARLINN_MATH_HYPERSPHERE_H_
#define HARLINN_MATH_HYPERSPHERE_H_

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
    struct Hypersphere;

    namespace Internal
    {
        struct HypersphereSimdBase
        {
        };
        struct HypersphereBase
        {
        };
    }

    template<typename T>
    concept HypersphereSimdType = std::is_base_of_v<Internal::HypersphereSimdBase, T>;
    template<typename T>
    concept HypersphereType = std::is_base_of_v<Internal::HypersphereBase, T>;

    template<typename T>
    concept HypersphereOrHypersphereSimdType = HypersphereSimdType<T> || HypersphereType<T>;

    namespace Internal
    {
        template<HypersphereSimdType T>
        const T& ToSimdType( const T& line ) noexcept
        {
            return line;
        }
        template<HypersphereType T>
        const typename T::Simd ToSimdType( const T& line ) noexcept
        {
            return line.ToSimd( );
        }
    }


    template<FloatingPointType T, size_t N>
    struct HypersphereSimd : public Internal::HypersphereSimdBase
    {
    public:
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using Hypersphere = Math::Hypersphere<T, N>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type One = static_cast< value_type >( 1 );

        Point center;
        value_type radius;

        HypersphereSimd( ) noexcept
            : radius( One )
        {
        }

        HypersphereSimd( const Point& center, value_type radius ) noexcept
            : center( center ), radius( radius )
        {
        }

        HypersphereSimd( const Hypersphere& other ) noexcept;


    };


    template<FloatingPointType T, size_t N>
    struct Hypersphere : public Internal::HypersphereBase
    {
    public:
        using Point = Math::Point<T, N>;
        using Vector = Math::Vector<T, N>;
        using Simd = HypersphereSimd<T, N>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );

        Point center;
        value_type radius;

        Hypersphere( ) noexcept
            : radius( One )
        {
        }

        Hypersphere( const Point& center, value_type radius ) noexcept
            : center( center ), radius( radius )
        {
        }


        Hypersphere( const Simd& simd ) noexcept
            : center( simd.center ), radius( simd.radius )
        {
        }

        Simd ToSimd( ) const noexcept
        {
            return Simd( Internal::ToSimdType( center ), radius );
        }


    };

    template<FloatingPointType T, size_t N>
    inline HypersphereSimd<T, N>::HypersphereSimd( const Hypersphere& other ) noexcept
        : center( other.center ), radius( other.radius )
    {
    }


    template<FloatingPointType T>
    using Circle2 = Hypersphere<T, 2>;
    using Circle2f = Circle2<float>;
    using Circle2d = Circle2<double>;

    template<FloatingPointType T>
    using Sphere3 = Hypersphere<T, 3>;
    using Sphere3f = Sphere3<float>;
    using Sphere3d = Sphere3<double>;

}

#endif
