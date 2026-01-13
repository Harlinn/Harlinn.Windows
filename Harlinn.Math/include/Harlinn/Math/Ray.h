#pragma once
#ifndef HARLINN_MATH_RAY_H_
#define HARLINN_MATH_RAY_H_

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
    struct Ray;

    namespace Internal
    {
        struct RaySimdBase
        {
        };
        struct RayBase
        {
        };
    }

    template<typename T>
    concept RaySimdType = std::is_base_of_v<Internal::RaySimdBase, T>;
    template<typename T>
    concept RayType = std::is_base_of_v<Internal::RayBase, T>;

    template<typename T>
    concept RayOrRaySimdType = RaySimdType<T> || RayType<T>;

    namespace Internal
    {
        template<RaySimdType T>
        const T& ToSimdType( const T& line ) noexcept
        {
            return line;
        }
        template<RayType T>
        const typename T::Simd ToSimdType( const T& line ) noexcept
        {
            return line.ToSimd( );
        }
    }


    /// <summary>
    /// A semi-infinite line starting at <c>origin<c>
    /// with direction given by the unit vector <c>direction<c>.
    /// </summary>
    /// <typeparam name="T">
    /// double or float
    /// </typeparam>
    /// <typeparam name="N">
    /// Dimension count.
    /// </typeparam>
    template<FloatingPointType T, size_t N>
    struct RaySimd : public Internal::RaySimdBase
    {
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using Ray = Math::Ray<T, N>;
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

        RaySimd( ) noexcept = default;
        RaySimd( const Point& o, const Vector& d ) noexcept
            : origin( o ), direction( d )
        {
        }

        RaySimd( const Point& p1, const Point& p2 ) noexcept
            : origin( p1 ), direction( Normalize( p1 - p2 ) )
        {
        }

        RaySimd( const Ray& r ) noexcept;
    };

    /// <summary>
    /// A semi-infinite line starting at <c>origin<c>
    /// with direction given by the unit vector <c>direction<c>.
    /// </summary>
    /// <typeparam name="T">
    /// double or float
    /// </typeparam>
    /// <typeparam name="N">
    /// Dimension count.
    /// </typeparam>
    template<FloatingPointType T, size_t N>
    struct Ray : public Internal::RayBase
    {
        using Point = Math::Point<T, N>;
        using Vector = Math::Vector<T, N>;
        using Simd = RaySimd<T, N>;
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

        Ray( ) noexcept = default;
        Ray( const Point& o, const Vector& d ) noexcept
            : origin( o ), direction( d )
        {
        }

        Ray( const Point& p1, const Point& p2 ) noexcept
            : origin( p1 ), direction( Normalize( p1 - p2 ) )
        {
        }

        Simd ToSimd( ) const noexcept
        {
            return Simd( Internal::ToSimdType( origin ), Internal::ToSimdType( direction ) );
        }

    };

    template<FloatingPointType T, size_t N>
    inline RaySimd<T, N>::RaySimd( const Ray& r ) noexcept
        : origin( r.origin ), direction( r.direction )
    { }

    template<FloatingPointType T>
    using Ray2 = Ray<T, 2>;
    using Ray2f = Ray2<float>;
    using Ray2d = Ray2<double>;

    template<FloatingPointType T>
    using Ray3 = Ray<T, 3>;
    using Ray3f = Ray3<float>;
    using Ray3d = Ray3<double>;
}

#endif
