#pragma once
#ifndef PBRT_UTIL_NEWMATH_H_
#define PBRT_UTIL_NEWMATH_H_

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

// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewFloat.h>
#include <pbrto/util/NewPStd.h>

#include <HCCVectorMath.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <string>
#include <type_traits>

#ifdef PBRT_HAS_INTRIN_H
#include <intrin.h>
#endif  // PBRT_HAS_INTRIN_H

namespace pbrto
{
    using Math::AbsDot;
    using Math::AngleBetween;
    using Math::Clamp;
    using Math::DifferenceOfProducts;
    using Math::FastExp;
    using Math::FMA;
    using Math::InnerProduct;
    using Math::Inverse;
    using Math::IsInf;
    using Math::IsNaN;
    using Math::IsSameValue;
    using Math::Log2;
    using Math::LogI0;
    using Math::Max;
    using Math::Min;
    using Math::Pow;
    using Math::Sqr;
    using Math::SafeSqrt;
    using Math::SumOfProducts;


    // Mathematical Constants
    constexpr Float ShadowEpsilon = 0.0001f;

    constexpr Float Pi = static_cast< Float >( 3.14159265358979323846 );
    constexpr Float InvPi = static_cast< Float >( 0.31830988618379067154 );
    constexpr Float Inv2Pi = static_cast< Float >( 0.15915494309189533577 );
    constexpr Float Inv4Pi = static_cast< Float >( 0.07957747154594766788 );
    constexpr Float PiOver2 = static_cast< Float >( 1.57079632679489661923 );
    constexpr Float PiOver4 = static_cast< Float >( 0.78539816339744830961 );
    constexpr Float Sqrt2 = static_cast< Float >( 1.41421356237309504880 );


    // Bit Operation Inline Functions
    inline uint32_t ReverseBits32( uint32_t n )
    {
        n = ( n << 16 ) | ( n >> 16 );
        n = ( ( n & 0x00ff00ff ) << 8 ) | ( ( n & 0xff00ff00 ) >> 8 );
        n = ( ( n & 0x0f0f0f0f ) << 4 ) | ( ( n & 0xf0f0f0f0 ) >> 4 );
        n = ( ( n & 0x33333333 ) << 2 ) | ( ( n & 0xcccccccc ) >> 2 );
        n = ( ( n & 0x55555555 ) << 1 ) | ( ( n & 0xaaaaaaaa ) >> 1 );
        return n;
    }

    inline uint64_t ReverseBits64( uint64_t n )
    {
    uint64_t n0 = ReverseBits32( ( uint32_t )n );
    uint64_t n1 = ReverseBits32( ( uint32_t )( n >> 32 ) );
    return ( n0 << 32 ) | n1;
    }

    // https://fgiesen.wordpress.com/2009/12/13/decoding-morton-codes/
    // updated to 64 bits.
    inline uint64_t LeftShift2( uint64_t x )
    {
        x &= 0xffffffff;
        x = ( x ^ ( x << 16 ) ) & 0x0000ffff0000ffff;
        x = ( x ^ ( x << 8 ) ) & 0x00ff00ff00ff00ff;
        x = ( x ^ ( x << 4 ) ) & 0x0f0f0f0f0f0f0f0f;
        x = ( x ^ ( x << 2 ) ) & 0x3333333333333333;
        x = ( x ^ ( x << 1 ) ) & 0x5555555555555555;
        return x;
    }

    inline uint64_t EncodeMorton2( uint32_t x, uint32_t y )
    {
        return ( LeftShift2( y ) << 1 ) | LeftShift2( x );
    }

    inline uint32_t LeftShift3( uint32_t x )
    {
        NDCHECK_LE( x, ( 1u << 10 ) );
        if ( x == ( 1 << 10 ) )
            --x;
        x = ( x | ( x << 16 ) ) & 0b00000011000000000000000011111111;
        // x = ---- --98 ---- ---- ---- ---- 7654 3210
        x = ( x | ( x << 8 ) ) & 0b00000011000000001111000000001111;
        // x = ---- --98 ---- ---- 7654 ---- ---- 3210
        x = ( x | ( x << 4 ) ) & 0b00000011000011000011000011000011;
        // x = ---- --98 ---- 76-- --54 ---- 32-- --10
        x = ( x | ( x << 2 ) ) & 0b00001001001001001001001001001001;
        // x = ---- 9--8 --7- -6-- 5--4 --3- -2-- 1--0
        return x;
    }

    inline uint32_t EncodeMorton3( float x, float y, float z )
    {
        NDCHECK_GE( x, 0 );
        NDCHECK_GE( y, 0 );
        NDCHECK_GE( z, 0 );
        return ( LeftShift3( std::bit_cast< uint32_t >( z ) ) << 2 ) | ( LeftShift3( std::bit_cast< uint32_t >( y ) ) << 1 ) | LeftShift3( std::bit_cast< uint32_t >( x ) );
    }

    inline uint32_t Compact1By1( uint64_t x )
    {
        // TODO: as of Haswell, the PEXT instruction could do all this in a
        // single instruction.
        // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
        x &= 0x5555555555555555;
        // x = --fe --dc --ba --98 --76 --54 --32 --10
        x = ( x ^ ( x >> 1 ) ) & 0x3333333333333333;
        // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
        x = ( x ^ ( x >> 2 ) ) & 0x0f0f0f0f0f0f0f0f;
        // x = ---- ---- fedc ba98 ---- ---- 7654 3210
        x = ( x ^ ( x >> 4 ) ) & 0x00ff00ff00ff00ff;
        // x = ---- ---- ---- ---- fedc ba98 7654 3210
        x = ( x ^ ( x >> 8 ) ) & 0x0000ffff0000ffff;
        // ...
        x = ( x ^ ( x >> 16 ) ) & 0xffffffff;
        return static_cast< uint32_t >( x );
    }

    inline void DecodeMorton2( uint64_t v, uint32_t* x, uint32_t* y )
    {
        *x = Compact1By1( v );
        *y = Compact1By1( v >> 1 );
    }

    inline uint32_t Compact1By2( uint32_t x )
    {
        x &= 0x09249249;                   // x = ---- 9--8 --7- -6-- 5--4 --3- -2-- 1--0
        x = ( x ^ ( x >> 2 ) ) & 0x030c30c3;   // x = ---- --98 ---- 76-- --54 ---- 32-- --10
        x = ( x ^ ( x >> 4 ) ) & 0x0300f00f;   // x = ---- --98 ---- ---- 7654 ---- ---- 3210
        x = ( x ^ ( x >> 8 ) ) & 0xff0000ff;   // x = ---- --98 ---- ---- ---- ---- 7654 3210
        x = ( x ^ ( x >> 16 ) ) & 0x000003ff;  // x = ---- ---- ---- ---- ---- --98 7654 3210
        return x;
    }

    template <typename Float>
    using CompensatedSum = Math::CompensatedSum<Float>;

    using CompensatedFloat = Math::CompensatedFloat<Float>;

    template <int N>
    using SquareMatrix = Math::SquareMatrix<Float, N>;


    // Math Inline Functions
    inline Float Lerp( Float x, Float a, Float b )
    {
        return ( 1 - x ) * a + x * b;
    }

    template <typename T>
    inline T Mod( T a, T b )
    {
        T result = a - ( a / b ) * b;
        return ( T )( ( result < 0 ) ? result + b : result );
    }

    template <>
    inline Float Mod( Float a, Float b )
    {
        return Math::FMod( a, b );
    }

    template <typename Tresult, int N, typename T>
    inline Tresult Mul( const SquareMatrix<N>& m, const T& v )
    {
        Tresult result;
        for ( int i = 0; i < N; ++i )
        {
            result[ i ] = 0;
            for ( int j = 0; j < N; ++j )
                result[ i ] += m[ i ][ j ] * v[ j ];
        }
        return result;
    }


    template <int N, typename T>
        requires ( std::is_same_v<SquareMatrix<N>, T> == false )
    inline T operator*( const SquareMatrix<N>& m, const T& v )
    {
        return Mul<T>( m, v );
    }


    template <int N>
    pstdo::optional<SquareMatrix<N>> LinearLeastSquares( const Float A[ ][ N ], const Float B[ ][ N ], int rows )
    {
        SquareMatrix<N> AtA = SquareMatrix<N>::Zero( );
        SquareMatrix<N> AtB = SquareMatrix<N>::Zero( );

        for ( int i = 0; i < N; ++i )
        {
            for ( int j = 0; j < N; ++j )
            {
                for ( int r = 0; r < rows; ++r )
                {
                    AtA[ i ][ j ] += A[ r ][ i ] * A[ r ][ j ];
                    AtB[ i ][ j ] += A[ r ][ i ] * B[ r ][ j ];
                }
            }
        }
        typename Math::Vector<Float, N>::Simd determinant;
        using Traits = typename Math::Vector<Float, N>::Traits;
        auto AtAi = Inverse( AtA, &determinant );
        if ( Traits::First( determinant.simd ) == 0.f )
        {
            return {};
        }
        return SquareMatrix<N>( Math::Transpose( AtAi * AtB ) );
    }

    // Math Function Declarations
    int NextPrime( int x );

    // Permutation Inline Function Declarations
    PBRT_CPU_GPU inline int PermutationElement( uint32_t i, uint32_t n, uint32_t seed );

    PBRT_CPU_GPU
        inline int PermutationElement( uint32_t i, uint32_t l, uint32_t p )
    {
        uint32_t w = l - 1;
        w |= w >> 1;
        w |= w >> 2;
        w |= w >> 4;
        w |= w >> 8;
        w |= w >> 16;
        do
        {
            i ^= p;
            i *= 0xe170893d;
            i ^= p >> 16;
            i ^= ( i & w ) >> 4;
            i ^= p >> 8;
            i *= 0x0929eb3f;
            i ^= p >> 23;
            i ^= ( i & w ) >> 1;
            i *= 1 | p >> 27;
            i *= 0x6935fa69;
            i ^= ( i & w ) >> 11;
            i *= 0x74dcb303;
            i ^= ( i & w ) >> 2;
            i *= 0x9e501cc3;
            i ^= ( i & w ) >> 2;
            i *= 0xc860a3df;
            i &= w;
            i ^= i >> 5;
        } while ( i >= l );
        return ( i + p ) % l;
    }

    inline Float ErfInv( Float a )
    {
#ifdef PBRT_IS_GPU_CODE
        return erfinv( a );
#else
        // https://stackoverflow.com/a/49743348
        float p;
        float t = Math::Log( std::max( FMA( a, -a, 1.f ), std::numeric_limits<Float>::min( ) ) );

        NCHECK( !IsNaN( t ) && !IsInf( t ) );
        if ( std::abs( t ) > 6.125f )
        {          // maximum ulp error = 2.35793
            p = 3.03697567e-10f;             //  0x1.4deb44p-32
            p = FMA( p, t, 2.93243101e-8f );   //  0x1.f7c9aep-26
            p = FMA( p, t, 1.22150334e-6f );   //  0x1.47e512p-20
            p = FMA( p, t, 2.84108955e-5f );   //  0x1.dca7dep-16
            p = FMA( p, t, 3.93552968e-4f );   //  0x1.9cab92p-12
            p = FMA( p, t, 3.02698812e-3f );   //  0x1.8cc0dep-9
            p = FMA( p, t, 4.83185798e-3f );   //  0x1.3ca920p-8
            p = FMA( p, t, -2.64646143e-1f );  // -0x1.0eff66p-2
            p = FMA( p, t, 8.40016484e-1f );   //  0x1.ae16a4p-1
        }
        else
        {                             // maximum ulp error = 2.35456
            p = 5.43877832e-9f;              //  0x1.75c000p-28
            p = FMA( p, t, 1.43286059e-7f );   //  0x1.33b458p-23
            p = FMA( p, t, 1.22775396e-6f );   //  0x1.49929cp-20
            p = FMA( p, t, 1.12962631e-7f );   //  0x1.e52bbap-24
            p = FMA( p, t, -5.61531961e-5f );  // -0x1.d70c12p-15
            p = FMA( p, t, -1.47697705e-4f );  // -0x1.35be9ap-13
            p = FMA( p, t, 2.31468701e-3f );   //  0x1.2f6402p-9
            p = FMA( p, t, 1.15392562e-2f );   //  0x1.7a1e4cp-7
            p = FMA( p, t, -2.32015476e-1f );  // -0x1.db2aeep-3
            p = FMA( p, t, 8.86226892e-1f );   //  0x1.c5bf88p-1
        }
        return a * p;
#endif  // PBRT_IS_GPU_CODE
    }

    PBRT_CPU_GPU
        inline Float I0( Float x )
    {
        Float val = 0;
        Float x2i = 1;
        int64_t ifact = 1;
        int i4 = 1;
        // I0(x) \approx Sum_i x^(2i) / (4^i (i!)^2)
        for ( int i = 0; i < 10; ++i )
        {
            if ( i > 1 )
                ifact *= i;
            val += x2i / ( i4 * Math::Sqr( ifact ) );
            x2i *= x * x;
            i4 *= 4;
        }
        return val;
    }

    PBRT_CPU_GPU
        inline Float LogI0( Float x )
    {
        if ( x > 12 )
        {
            return x + 0.5f * ( -Math::Log( 2 * Pi ) + Math::Log( 1 / x ) + 1 / ( 8 * x ) );
        }
        else
        {
            return Math::Log( I0( x ) );
        }
    }

    class Interval : public Math::Interval<Float>
    {
    public:
        static const Interval Pi;
        using Base = Math::Interval<Float>;

        constexpr Interval( ) = default;
        constexpr explicit Interval( Float v )
            : Base( v, v )
        {
        }
        constexpr Interval( Float a, Float b )
            : Base( a, b )
        {
        }

        constexpr Interval( const Base& other )
            : Base( other )
        {
        }

        constexpr Interval& operator = ( const Base& other )
        {
            Base::operator = ( other );
            return *this;
        }

        constexpr Interval& operator = ( const Float& value )
        {
            Base::operator = ( Interval( value ) );
            return *this;
        }


        std::string ToString( ) const;
    };




    using Math::InRange;

    inline Interval Sqr( const Interval& i )
    {
        return std::bit_cast< Interval >( Math::Sqr( i ) );
    }



    PBRT_CPU_GPU
        Vector3f EqualAreaSquareToSphere( Point2f p );
    PBRT_CPU_GPU
        Point2f EqualAreaSphereToSquare( Vector3f v );
    PBRT_CPU_GPU
        Point2f WrapEqualAreaSquare( Point2f p );

    // Spline Interpolation Declarations
    PBRT_CPU_GPU
        Float CatmullRom( pstdo::span<const Float> nodes, pstdo::span<const Float> values, Float x );
    PBRT_CPU_GPU
        bool CatmullRomWeights( pstdo::span<const Float> nodes, Float x, int* offset,
            pstdo::span<Float> weights );
    PBRT_CPU_GPU
        Float IntegrateCatmullRom( pstdo::span<const Float> nodes, pstdo::span<const Float> values,
            pstdo::span<Float> cdf );
    PBRT_CPU_GPU
        Float InvertCatmullRom( pstdo::span<const Float> x, pstdo::span<const Float> values,
            Float u );



}

#endif
