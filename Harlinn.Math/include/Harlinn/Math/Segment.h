#pragma once
#ifndef HARLINN_MATH_SEGMENT_H_
#define HARLINN_MATH_SEGMENT_H_

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
    struct Segment;

    namespace Internal
    {
        struct SegmentSimdBase
        {
        };
        struct SegmentBase
        {
        };
    }

    template<typename T>
    concept SegmentSimdType = std::is_base_of_v<Internal::SegmentSimdBase, T>;
    template<typename T>
    concept SegmentType = std::is_base_of_v<Internal::SegmentBase, T>;

    template<typename T>
    concept SegmentOrSegmentSimdType = SegmentSimdType<T> || SegmentType<T>;

    namespace Internal
    {
        template<SegmentSimdType T>
        const T& ToSimdType( const T& line ) noexcept
        {
            return line;
        }
        template<SegmentType T>
        const typename T::Simd ToSimdType( const T& line ) noexcept
        {
            return line.ToSimd( );
        }
    }


    template<FloatingPointType T, size_t N>
    struct SegmentSimd : public Internal::SegmentSimdBase
    {
    public:
        using Point = typename Math::Point<T, N>::Simd;
        using Vector = Math::Vector<T, N>::Simd;
        using ArrayType = Point::ArrayType;
        using Segment = Math::Segment<T, N>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );
        static constexpr value_type Half = static_cast< value_type >( .5 );

        std::array<Point, 2> points;

        SegmentSimd( ) noexcept
            : points{ Point( ArrayType{ -One, Zero, } ), Point( ArrayType{ One, Zero, } ) }
        { }

        SegmentSimd( const std::array<Point, 2>& pts ) noexcept
            : points( pts )
        { }

        SegmentSimd( const Point& p1, const Point& p2 ) noexcept
            : points{ p1, p2 }
        { }

        SegmentSimd( const Segment& segment ) noexcept;

        void Assign( const Point& center, const Vector& direction, value_type extent ) noexcept
        {
            points[ 0 ] = center - extent * direction;
            points[ 1 ] = center + extent * direction;
        }

        void Extract( Point& center, Vector& direction, value_type& extent ) const noexcept
        {
            center = Half * ( points[ 0 ] + points[ 1 ] );
            direction = points[ 1 ] - points[ 0 ];
            auto length = Length( direction );
            direction = direction / length;
            extent = Half * length.x( );
        }

    };


    template<FloatingPointType T, size_t N>
    struct Segment : public Internal::SegmentBase
    {
    public:
        using Point = Math::Point<T, N>;
        using Vector = Math::Vector<T, N>;
        using ArrayType = Point::ArrayType;
        using Simd = SegmentSimd<T, N>;
        using value_type = T;

        static constexpr size_t Dimensions = N;

        static constexpr value_type Zero = static_cast< value_type >( 0 );
        static constexpr value_type One = static_cast< value_type >( 1 );
        static constexpr value_type Half = static_cast< value_type >( .5 );

        std::array<Point, 2> points;

        Segment( ) noexcept
            : points{ Point( ArrayType{ -One, Zero, } ), Point( ArrayType{ One, Zero, } ) }
        { }

        Segment( const std::array<Point, 2>& pts ) noexcept
            : points( pts )
        { }

        Segment( const Point& p1, const Point& p2 ) noexcept
            : points{ p1, p2 }
        { }

        Segment( const Simd& simd ) noexcept
            : points{ simd.points[ 0 ], simd.points[ 1 ] }
        { }

        Simd ToSimd( ) const noexcept
        {
            return Simd( Internal::ToSimdType( points[ 0 ] ), Internal::ToSimdType( points[ 1 ] ) );
        }

        void Assign( const Point& center, const Vector& direction, value_type extent ) noexcept
        {
            points[ 0 ] = center - extent * direction;
            points[ 1 ] = center + extent * direction;
        }

        void Extract( Point& center, Vector& direction, value_type& extent ) const noexcept
        {
            center = Half * ( points[ 0 ] + points[ 1 ] );
            direction = points[ 1 ] - points[ 0 ];
            auto length = Length( direction );
            direction = direction / length;
            extent = Half * length.x( );
        }

    };

    template<FloatingPointType T, size_t N>
    inline SegmentSimd<T, N>::SegmentSimd( const Segment& segment ) noexcept
        : points{ segment.points[ 0 ], segment.points[ 1 ] }
    { }

    template<FloatingPointType T, size_t N>
    Vector<T, N> Length( const SegmentSimd<T, N>& segment ) noexcept
    {
        return Length( segment.points[ 1 ] - segment.points[ 0 ] );
    }

    template<FloatingPointType T>
    using Segment2 = Segment<T, 2>;
    using Segment2f = Segment2<float>;
    using Segment2d = Segment2<double>;

    template<FloatingPointType T>
    using Segment3 = Segment<T, 3>;
    using Segment3f = Segment3<float>;
    using Segment3d = Segment3<double>;

}


#endif
