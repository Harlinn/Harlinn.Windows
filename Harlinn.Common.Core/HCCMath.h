#pragma once
#ifndef __HCCMATH_H__
#define __HCCMATH_H__
/*
   Copyright 2024 Espen Harlinn

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

#include <HCCLib.h>

namespace Harlinn::Common::Core::Math
{
    /// <summary>
    /// Tests whether two double precision floating
    /// point values holds the same value. This function
    /// returns true if both hold the same NaN value.
    /// </summary>
    /// <param name="first">
    /// A double precision floating point value.
    /// </param>
    /// <param name="second">
    /// A double precision floating point value.
    /// </param>
    /// <returns>
    /// true if both arguments are binary equivalent, otherwise false.
    /// </returns>
    constexpr bool IsSameValue( double first, double second ) noexcept
    {
        return std::bit_cast<Int64>( first ) == std::bit_cast<Int64>( second );
    }
    /// <summary>
    /// Tests whether two single precision floating
    /// point values holds the same value. This function
    /// returns true if both hold the same NaN value.
    /// </summary>
    /// <param name="first">
    /// A single precision floating point value.
    /// </param>
    /// <param name="second">
    /// A single precision floating point value.
    /// </param>
    /// <returns>
    /// true if both arguments are binary equivalent, otherwise false.
    /// </returns>
    constexpr bool IsSameValue( float x, float y ) noexcept
    {
        return std::bit_cast<Int32>( x ) == std::bit_cast<Int32>( y );
    }

    
    /// <summary>
    /// Tests if a double precision floating value is zero.
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value.
    /// </param>
    /// <returns>
    /// true if the argument is zero, otherwise false.
    /// </returns>
    constexpr bool IsZero( double x ) noexcept
    {
        return ( std::bit_cast<Int64>( x ) & 0x7FFFFFFFFFFFFFFF ) == 0;
    }
    /// <summary>
    /// Tests if a double precision floating value is zero.
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value.
    /// </param>
    /// <returns>
    /// true if the argument is zero, otherwise false.
    /// </returns>
    constexpr bool IsZero( float x ) noexcept
    {
        return ( std::bit_cast<Int32>( x ) & 0x7FFFFFFF ) == 0;
    }


    /// <summary>
    /// <para>
    /// Returns the sign of a value for a bool or an unsigned integer type.
    /// </para>
    /// <para>
    /// This function treats bool as an unsigned integer.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// bool or an unsigned integer type.
    /// </typeparam>
    /// <param name="val">
    /// The value to test.
    /// </param>
    /// <returns>
    /// <para>
    /// If invoked with a bool this function returns true if the value is not false, otherwise false.
    /// </para>
    /// <para>
    /// If invoked with an unsigned integer type this function returns 1 if the value is greater than 0, otherwise 0.
    /// </para>
    /// </returns>
    template< typename T>
        requires IsUnsignedInteger<std::remove_cvref_t<T>> || IsBoolean<std::remove_cvref_t<T>>
    inline constexpr T signum( T val ) noexcept
    {
        constexpr T zero = static_cast<T>( 0 );
        return static_cast<T>( val > zero ? 1 : 0 );
    }

    /// <summary>
    /// Returns the sign of a value for a signed integer type.
    /// </summary>
    /// <typeparam name="T">
    /// Any signed integer type.
    /// </typeparam>
    /// <param name="val">
    /// The value to test.
    /// </param>
    /// <returns>
    /// Returns:
    /// <list type="bullet">
    /// <item>-1 if val is less than zero.</item>
    /// <item>0 if val is equal to zero.</item>
    /// <item>1 if val is greater than zero.</item>
    /// </list>
    /// </returns>
    template< typename T>
        requires IsSignedInteger<std::remove_cvref_t<T>>
    inline constexpr T signum( T val ) noexcept
    {
        constexpr T zero = static_cast< T >( 0 );
        constexpr T one = static_cast< T >( 1 );
        constexpr T minusOne = static_cast< T >( -1 );
        return val > zero ? one : ( val < zero ? minusOne : zero );
    }

    /// <summary>
    /// Returns the sign of a value for a floating point type.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// The value to test.
    /// </param>
    /// <returns>
    /// Returns:
    /// <list type="bullet">
    /// <item>-1.0 if val is less than zero.</item>
    /// <item>0.0 if val is equal to zero.</item>
    /// <item>1.0 if val is greater than zero.</item>
    /// </list>
    /// </returns>
    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    inline constexpr T signum( T val ) noexcept
    {
        constexpr T zero = static_cast<T>( 0 );
        constexpr T one = static_cast<T>( 1 );
        constexpr T minusOne = static_cast<T>( -1 );
        if constexpr ( sizeof( std::remove_cvref_t<T> ) == 4 )
        {
            UInt32 bits = std::bit_cast<UInt32, T>( val );
            return bits & 0x7FFFFFFF ? bits & 0x80000000 ? minusOne : one : zero;
        }
        else
        {
            UInt64 bits = std::bit_cast<UInt64, T>( val );
            return bits & 0x7FFFFFFFFFFFFFFF ? bits & 0x8000000000000000 ? minusOne : one : zero;
        }
    }

    inline constexpr double ScaleByN( double x, int n ) noexcept;
    inline constexpr float ScaleByN( float x, int n ) noexcept;
    inline constexpr double FMod( double x, double y ) noexcept;
    inline constexpr float FMod( float x, float y ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Exp( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> CopySign( T magnitude, T signValue ) noexcept;


    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsNaN( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsNaN( T val ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsInf( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsInf( T val ) noexcept;

    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;
    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;

    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept;
    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool SignBit( T val ) noexcept;


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::pair<double, int> FRExp( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int* exp ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int& exp ) noexcept;

    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>> 
    constexpr inline std::pair<std::remove_cvref_t<ValueT>, std::remove_cvref_t<ValueT>> ModF( ValueT val ) noexcept;
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT* integerPart ) noexcept;
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT& integerPart ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept;


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T value ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T value ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept;




    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextDown( T x ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextUp( T x ) noexcept;

    /// <summary>
    /// Converts an angle in degrees into the corresponding
    /// angle in radians.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="angleInDegrees">
    /// The angle in degrees.
    /// </param>
    /// <returns>
    /// The angle in radians.
    /// </returns>
    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    inline constexpr std::remove_cvref_t<T> Deg2Rad( T angleInDegrees ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        constexpr FloatT factor = static_cast<FloatT>( M_PI_4/45.0 );
        return angleInDegrees * factor;
    }
    /// <summary>
    /// Converts an angle in radians into the corresponding
    /// angle in degrees.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="angleInRadians">
    /// The angle in radians.
    /// </param>
    /// <returns>
    /// The angle in degrees.
    /// </returns>
    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    inline constexpr std::remove_cvref_t<T> Rad2Deg( T angleInRadians ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        constexpr FloatT factor = static_cast<FloatT>( 45.0/M_PI_4 );
        return angleInRadians * factor;
    }

    /// <summary>
    /// <para>
    /// Returns the next representable value of x in the direction of y. If x equals to y, y is returned.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and at runtime
    /// if performs 740.07 % better than std::nextafter for double
    /// precision values,
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value.
    /// </param>
    /// <param name="y">
    /// A double precision floating point value.
    /// </param>
    /// <returns>
    /// The next representable value of x in the direction of y. is returned. If x equals y, then y is returned
    /// </returns>
    inline constexpr double NextAfter( double x, double y ) noexcept
    {
        double t;

        Int32 hx = GetHigh32Bits<Int32>( x );
        UInt32 lx = GetLow32Bits<UInt32>( x );

        Int32 hy = GetHigh32Bits<Int32>( y );
        UInt32 ly = GetLow32Bits<UInt32>( y );

        // |x| 
        Int32 ix = hx & 0x7fffffff;
        // |y| 
        Int32 iy = hy & 0x7fffffff;

        // Are x or y NaN?
        if ( ( ( ix >= 0x7ff00000 ) && ( ( ix - 0x7ff00000 ) | lx ) != 0 ) || ( ( iy >= 0x7ff00000 ) && ( ( iy - 0x7ff00000 ) | ly ) != 0 ) )
        {
            return x + y;
        }
        if ( x == y )
        {
            // x=y, return y 
            return y;
        }
        if ( ( ix | lx ) == 0 )
        {			
            // x == 0 
            // return +-minsubnormal 
            x = From32BitsTo64Bits<double>( hy & 0x80000000, 1 );
            t = x * x;
            if ( t == x )
            {
                return t;
            }
            else
            {
                // raise underflow flag 
                return x;
            }
        }
        if ( hx >= 0 )
        {	
            // x > 0 
            if ( hx > hy || ( ( hx == hy ) && ( lx > ly ) ) )
            {	
                // x > y, x -= ulp 
                if ( lx == 0 )
                {
                    hx -= 1;
                }
                lx -= 1;
            }
            else
            {
                // x < y, x += ulp 
                lx += 1;
                if ( lx == 0 )
                {
                    hx += 1;
                }
            }
        }
        else
        {
            // x < 0 
            if ( hy >= 0 || hx > hy || ( ( hx == hy ) && ( lx > ly ) ) )
            {
                // x < y, x -= ulp 
                if ( lx == 0 )
                {
                    hx -= 1;
                }
                lx -= 1;
            }
            else
            {
                // x > y, x += ulp 
                lx += 1;
                if ( lx == 0 )
                {
                    hx += 1;
                }
            }
        }
        hy = hx & 0x7ff00000;
        if ( hy >= 0x7ff00000 )
        {
            // overflow  
            return x + x;
        }
        if ( hy < 0x00100000 )
        {
            // underflow 
            t = x * x;
            if ( t != x )
            {
                // raise underflow flag 
                y = From32BitsTo64Bits<double>( hx, lx );
                return y;
            }
        }
        x = From32BitsTo64Bits<double>( hx, lx );
        return x;
    }

    /// <summary>
    /// <para>
    /// Returns the next representable value of x in the direction of y. If x equals to y, y is returned.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and at runtime
    /// if performs 232.39 % better than std::nextafter for double
    /// precision values,
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A single precision floating point value.
    /// </param>
    /// <param name="y">
    /// A single precision floating point value.
    /// </param>
    /// <returns>
    /// The next representable value of x in the direction of y. is returned. If x equals y, then y is returned
    /// </returns>
    inline constexpr float NextAfter( float x, float y ) noexcept
    {
        volatile float t;
        int32_t hx, hy, ix, iy;

        hx = std::bit_cast<Int32>( x );
        hy = std::bit_cast<Int32>( y );
        // |x| 
        ix = hx & 0x7fffffff;
        // |y| 
        iy = hy & 0x7fffffff;

        // Are x or y NaN?
        if ( ( ix > 0x7f800000 ) || ( iy > 0x7f800000 ) )
        {
            return x + y;
        }
        if ( x == y )
        {
            // x=y, return y 
            return y;
        }
        if ( ix == 0 )
        {
            // x == 0 
            // return +-minsubnormal 
            x = std::bit_cast<float>( ( hy & 0x80000000 ) | 1 );
            t = x * x;
            if ( t == x )
            {
                return t;
            }
            else
            {
                // raise underflow flag 
                return x;
            }
        }
        if ( hx >= 0 )
        {
            // x > 0 
            if ( hx > hy )
            {
                // x > y, x -= ulp 
                hx -= 1;
            }
            else
            {
                // x < y, x += ulp 
                hx += 1;
            }
        }
        else
        {
            // x < 0 
            if ( hy >= 0 || hx > hy )
            {
                // x < y, x -= ulp 
                hx -= 1;
            }
            else
            {
                // x > y, x += ulp 
                hx += 1;
            }
        }
        hy = hx & 0x7f800000;
        if ( hy >= 0x7f800000 )
        {
            // overflow  
            return x + x;
        }
        if ( hy < 0x00800000 )
        {
            // underflow 
            t = x * x;
            if ( t != x )
            {
                // raise underflow flag 
                y = std::bit_cast<float>( hx );
                return y;
            }
        }
        x = std::bit_cast<float>( hx );
        return x;
    }





    namespace Internal
    {
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr double SqrtImpl( double x )
        {
            constexpr double one = 1.0;
            constexpr double tiny = 1.0e-300;
            constexpr Int32 sign = 0x80000000;
            double z;

            Int32 s0, q, m, t, i;
            UInt32 r, t1, s1, q1;

            Int64 ax = std::bit_cast<Int64>( x );
            Int32 ix0 = static_cast<Int32>( ax >> 32 );
            UInt32 ix1 = static_cast<UInt32>( ax );

            // take care of Inf and NaN 
            if ( ( ix0 & 0x7ff00000 ) == 0x7ff00000 )
            {
                // sqrt(NaN)=NaN 
                // sqrt(+inf)=+inf
                // sqrt( -inf ) = sNaN 
                return x * x + x;

            }
            // take care of zero 
            if ( ix0 <= 0 )
            {
                if ( ( ( ix0 & ( ~sign ) ) | ix1 ) == 0 )
                {
                    // sqrt(+-0) = +-0 
                    return x;
                }
                else if ( ix0 < 0 )
                {
                    // sqrt(-ve) = sNaN 
                    return ( x - x ) / ( x - x );
                }
            }
            // normalize x 
            m = ( ix0 >> 20 );
            if ( m == 0 )
            {
                // subnormal x 
                while ( ix0 == 0 )
                {
                    m -= 21;
                    ix0 |= ( ix1 >> 11 ); ix1 <<= 21;
                }
                for ( i = 0; ( ix0 & 0x00100000 ) == 0; i++ )
                {
                    ix0 <<= 1;
                }
                m -= i - 1;
                ix0 |= ( ix1 >> ( 32 - i ) );
                ix1 <<= i;
            }

            // unbias exponent 
            m -= 1023;
            ix0 = ( ix0 & 0x000fffff ) | 0x00100000;
            if ( m & 1 )
            {
                // odd m, double x to make it even 
                ix0 += ix0 + ( ( ix1 & sign ) >> 31 );
                ix1 += ix1;
            }
            // m = [m/2] 
            m >>= 1;

            // generate sqrt(x) bit by bit 
            ix0 += ix0 + ( ( ix1 & sign ) >> 31 );
            ix1 += ix1;
            // [q,q1] = sqrt(x) 
            q = q1 = s0 = s1 = 0;
            // r = moving bit from right to left 
            r = 0x00200000;

            while ( r != 0 )
            {
                t = s0 + r;
                if ( t <= ix0 )
                {
                    s0 = t + r;
                    ix0 -= t;
                    q += r;
                }
                ix0 += ix0 + ( ( ix1 & sign ) >> 31 );
                ix1 += ix1;
                r >>= 1;
            }

            r = sign;
            while ( r != 0 )
            {
                t1 = s1 + r;
                t = s0;
                if ( ( t < ix0 ) || ( ( t == ix0 ) && ( t1 <= ix1 ) ) )
                {
                    s1 = t1 + r;
                    if ( ( ( t1 & sign ) == sign ) && ( s1 & sign ) == 0 ) s0 += 1;
                    ix0 -= t;
                    if ( ix1 < t1 ) ix0 -= 1;
                    ix1 -= t1;
                    q1 += r;
                }
                ix0 += ix0 + ( ( ix1 & sign ) >> 31 );
                ix1 += ix1;
                r >>= 1;
            }

            // use floating add to find out rounding direction 
            if ( ( ix0 | ix1 ) != 0 )
            {
                // trigger inexact flag 
                z = one - tiny;
                if ( z >= one )
                {
                    z = one + tiny;
                    if ( q1 == (UInt32)0xffffffff )
                    {
                        q1 = 0;
                        q += 1;
                    }
                    else if ( z > one )
                    {
                        if ( q1 == (UInt32)0xfffffffe )
                        {
                            q += 1;
                        }
                        q1 += 2;
                    }
                    else
                        q1 += ( q1 & 1 );
                }
            }
            ix0 = ( q >> 1 ) + 0x3fe00000;
            ix1 = q1 >> 1;
            if ( ( q & 1 ) == 1 ) 
                ix1 |= sign;
            ix0 += ( m << 20 );
            z = std::bit_cast<double>( ( static_cast<UInt64>( ix0 ) << 32 ) + static_cast<UInt64>( ix1 ) );
            return z;
        }

        /* e_sqrtf.c -- float version of e_sqrt.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         */

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr float SqrtImpl( float x )
        {
            constexpr float	one = 1.0f; 
            constexpr float	tiny = 1.0e-30f;
            constexpr Int32 sign = (int)0x80000000;

            float z;
            Int32 ix, s, q, m, t, i;
            UInt32 r;

            ix = std::bit_cast<Int32>( x );

            // take care of Inf and NaN 
            if ( ( ix & 0x7f800000 ) == 0x7f800000 )
            {
                // sqrt(NaN)=NaN 
                // sqrt(+inf)=+inf
                // sqrt(-inf)=sNaN 
                return x * x + x;
                               
            }
            // take care of zero 
            if ( ix <= 0 )
            {
                if ( ( ix & ( ~sign ) ) == 0 )
                {
                    // sqrt(+-0) = +-0 
                    return x;
                }
                else if ( ix < 0 )
                {
                    // sqrt(-ve) = sNaN 
                    return ( x - x ) / ( x - x );
                }
            }
            // normalize x 
            m = ( ix >> 23 );
            if ( m == 0 )
            {				
                // subnormal x 
                for ( i = 0; ( ix & 0x00800000 ) == 0; i++ )
                {
                    ix <<= 1;
                }
                m -= i - 1;
            }
            // unbias exponent 
            m -= 127;
            ix = ( ix & 0x007fffff ) | 0x00800000;
            // odd m, double x to make it even 
            if ( m & 1 )
            {
                ix += ix;
            }
            // m = [m/2] 
            m >>= 1;

            // generate sqrt(x) bit by bit 
            ix += ix;
            // q = sqrt(x) 
            q = s = 0;
            // r = moving bit from right to left 
            r = 0x01000000;

            while ( r != 0 )
            {
                t = s + r;
                if ( t <= ix )
                {
                    s = t + r;
                    ix -= t;
                    q += r;
                }
                ix += ix;
                r >>= 1;
            }

            // use floating add to find out rounding direction 
            if ( ix != 0 )
            {
                // trigger inexact flag 
                z = one - tiny; 
                if ( z >= one )
                {
                    z = one + tiny;
                    if ( z > one )
                        q += 2;
                    else
                        q += ( q & 1 );
                }
            }
            ix = ( q >> 1 ) + 0x3f000000;
            ix += ( m << 23 );
            z = std::bit_cast<float>( ix );
            return z;
        }
    }

    /// <summary>
    /// <para>
    /// Computes the square root of x.  
    /// </para>
    /// <para>
    /// The runtime performance of this implementation
    /// is equivalent to the runtime performance of std::sqrt.
    /// </para>
    /// <para>
    /// Unlike std::sqrt this implementation can be constexpr 
    /// evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point value.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// Returns the square root of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Sqrt( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::SqrtImpl( x );
        }
        else
        {
            using FloatType = std::remove_cvref_t<T>;
            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_sqrt_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_sqrt_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }
    static_assert( Sqrt(2.0) > 0.0 );


    namespace Internal
    {
        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr bool IsNaNImpl( T val ) noexcept
        {
            using FloatType = std::remove_cvref_t<T>;
            using UnsignedType = MakeUnsigned<FloatType>;
            static constexpr UnsignedType fractionMask = FractionMask<FloatType>;
            static constexpr UnsignedType exponentMask = ExponentMask<FloatType>;

            UnsignedType value = std::bit_cast<UnsignedType>( val );

            if ( ( value & exponentMask ) != exponentMask )
            {
                return false;
            }
            else
            {
                return value & fractionMask ? true : false;
            }
        }



        template <typename T>
        struct FractionWidth;

        template <>
        struct FractionWidth<float>
        {
            static constexpr UInt32 value = 23;
        };
        template <>
        struct FractionWidth<double>
        {
            static constexpr UInt32 value = 52;
        };


        template <typename T>
        struct ExponentWidth;
        template <>
        struct ExponentWidth<float>
        {
            static constexpr UInt32 value = 8;
        };
        template <>
        struct ExponentWidth<double>
        {
            static constexpr UInt32 value = 11;
        };

        template <typename T>
        struct ExponenBias;
        template <>
        struct ExponenBias<float>
        {
            static constexpr UInt32 value = _FBIAS;
        };
        template <>
        struct ExponenBias<double>
        {
            static constexpr UInt32 value = _DBIAS;
        };

        template <typename T>
        struct InfinityUnsignedValue;
        template <>
        struct InfinityUnsignedValue<float>
        {
            static constexpr UInt32 value = 0X7F800000UL;
        };
        template <>
        struct InfinityUnsignedValue<double>
        {
            static constexpr UInt64 value = 0x7FF0000000000000ULL;
        };

        template <typename T>
        struct NegativeInfinityUnsignedValue;
        template <>
        struct NegativeInfinityUnsignedValue<float>
        {
            static constexpr UInt32 value = 0xFF800000UL;
        };
        template <>
        struct NegativeInfinityUnsignedValue<double>
        {
            static constexpr UInt64 value = 0xFFF0000000000000ULL;
        };
        template <typename T>
        struct QuietNaNUnsignedValue;
        template <>
        struct QuietNaNUnsignedValue<float>
        {
            static constexpr UInt32 value = 0XFFC00001UL;
        };
        template <>
        struct QuietNaNUnsignedValue<double>
        {
            static constexpr UInt64 value = 0x7FF0000000000001ULL;
        };


#pragma pack(push,1)
        template<typename T>
        struct FloatingPoint
        {
            using ValueType = std::remove_cvref_t<T>;
            using UIntType = MakeUnsigned<ValueType>;
            using IntType = std::make_signed_t<UIntType>;

            static constexpr Int32 FractionWidth = static_cast<Int32>( Internal::FractionWidth<ValueType>::value );
            static constexpr Int32 ExponentWidth = static_cast<Int32>( Internal::ExponentWidth<ValueType>::value );

            static constexpr Int32 ExponentBias = ( 1 << ( ExponentWidth - 1 ) ) - 1;

            static constexpr Int32 MaxExponentValue = ( 1 << ExponentWidth ) - 1;

            static constexpr UIntType MaxExponent = static_cast<UIntType>( MaxExponentValue ) << FractionWidth;

            static constexpr UIntType MinSubnormal = UIntType( 1 );
            static constexpr UIntType MaxSubnormal = ( UIntType( 1 ) << FractionWidth ) - 1;
            static constexpr UIntType MinNormal = ( UIntType( 1 ) << FractionWidth );
            static constexpr UIntType MaxNormal = ( ( UIntType( MaxExponentValue ) - 1 ) << FractionWidth ) | MaxSubnormal;

            static constexpr UIntType FractionMask = FractionMask<ValueType, UIntType>;
            static constexpr UIntType ExponentMask = ExponentMask<ValueType, UIntType>;
            static constexpr UIntType SignMask = ~( FractionMask | ExponentMask );

            static constexpr UIntType InfinityValue = InfinityUnsignedValue<ValueType>::value;
            static constexpr UIntType NegativeInfinityValue = NegativeInfinityUnsignedValue<ValueType>::value;
            static constexpr UIntType QuietNaNValue = QuietNaNUnsignedValue<ValueType>::value;
            static constexpr UIntType ZeroValue = static_cast<UIntType>( 0 );
            static constexpr UIntType NegativeZeroValue = SignMask;

            UIntType value_;

            constexpr FloatingPoint( ) noexcept
                : value_( std::bit_cast<UIntType>( static_cast<ValueType>( 0.0 ) ) )
            {
            }

            constexpr explicit FloatingPoint( ValueType value ) noexcept
                : value_( std::bit_cast<UIntType>( value ) )
            {
            }

            constexpr explicit FloatingPoint( UIntType value, bool ) noexcept
                : value_( value )
            {
            }

            constexpr explicit FloatingPoint( UIntType fraction, Int32 exponent, bool sign ) noexcept
                : value_( ( fraction& FractionMask ) |
                    ( ( static_cast<UIntType>( exponent ) << FractionWidth ) & ExponentMask ) |
                    ( sign ? SignMask : 0 ) )
            {
            }


            constexpr FloatingPoint& operator = ( ValueType value ) noexcept
            {
                value_ = std::bit_cast<UIntType>( value );
                return *this;
            }

            constexpr bool Sign( ) const noexcept
            {
                return value_ & SignMask;
            }
            constexpr void SetSign( bool value = true ) noexcept
            {
                if ( value )
                {
                    value_ |= SignMask;
                }
                else
                {
                    value_ &= ~SignMask;
                }
            }

            constexpr Int32 Exponent( ) const noexcept
            {
                return static_cast<Int32>( ( value_ & ExponentMask ) >> FractionWidth ) - ExponentBias;
            }
        private:
            constexpr void SetExponent( UIntType value ) noexcept
            {
                value_ = ( value << FractionWidth ) & ExponentMask;
            }
        public:
            constexpr UIntType Fraction( ) const noexcept
            {
                return value_ & FractionMask;
            }
        private:
            constexpr void SetFraction( UIntType value ) noexcept
            {
                value_ = value & FractionMask;
            }
        public:

            // returns true for +/- 0
            constexpr bool IsZero( ) const noexcept
            {
                return ( value_ & ( ExponentMask | FractionMask ) ) == 0;
            }

            // returns true for +/- Inf
            constexpr bool IsInf( ) const noexcept
            {
                return ( value_ & FractionMask ) == 0 && ( ( value_ & ExponentMask ) == MaxExponent );
            }

            // returns true for +/- NaN
            constexpr bool IsNaN( ) const noexcept
            {
                return ( ( value_ & ExponentMask ) == MaxExponent ) && ( ( value_ & FractionMask ) != 0 );
            }

            // returns true for +/- NaN or +/- Inf
            constexpr bool IsInfOrNaN( ) const noexcept
            {
                return ( value_ & ExponentMask ) == MaxExponent;
            }

            static constexpr ValueType MakeNaN( UIntType value ) noexcept
            {
                UIntType result;
                result = MaxExponent | ( value & FractionMask );
                return std::bit_cast<ValueType>( result );
            }

            constexpr ValueType AsFloatingPoint( ) const noexcept
            {
                return std::bit_cast<ValueType>( value_ );
            }

            constexpr UIntType AsUnsigned( ) const noexcept
            {
                return value_;
            }

            static constexpr FloatingPoint Zero( ) noexcept
            {
                return FloatingPoint( );
            }

            static constexpr FloatingPoint NegZero( ) noexcept
            {
                FloatingPoint result;
                result.value_ = SignMask;
                return result;
            }

            static constexpr FloatingPoint Inf( ) noexcept
            {
                FloatingPoint result;
                result.value_ = MaxExponent;
                return result;
            }

            static constexpr FloatingPoint NegInf( ) noexcept
            {
                FloatingPoint result;
                result.value_ = MaxExponent | SignMask;
                return result;
            }

            constexpr ValueType Trunc( ) const noexcept
            {
                if ( !IsInfOrNaN( ) )
                {
                    Int32 exponent = Exponent( );
                    
                    if ( exponent < static_cast<Int32>( FractionWidth ) )
                    {
                        if ( exponent > -1 )
                        {
                            // abs(x) is greater or equal to 1
                            Int32 trimSize = FractionWidth - exponent;

                            UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );
                            return std::bit_cast<ValueType>( result );
                        }
                        else
                        {
                            // abs(x) is less than 1, then return 0.
                            return Sign( ) ? static_cast<ValueType>( -0.0 ) : static_cast<ValueType>( 0.0 );
                        }
                    }
                    else
                    {
                        // already an integer
                        return std::bit_cast<ValueType>( value_ );
                    }
                }
                else
                {
                    // inf or NaN
                    return std::bit_cast<ValueType>( value_ );
                }
            }

        private:
            constexpr ValueType FastTrunc( ) const noexcept
            {
                Int32 exponent = Exponent( );

                if ( exponent < static_cast<Int32>( FractionWidth ) )
                {
                    if ( exponent > -1 )
                    {
                        // abs(x) is greater or equal to 1
                        Int32 trimSize = FractionWidth - exponent;

                        UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );
                        return std::bit_cast<ValueType>( result );
                    }
                    else
                    {
                        // abs(x) is less than 1, then return 0.
                        return Sign( ) ? static_cast<ValueType>( -0.0 ) : static_cast<ValueType>( 0.0 );
                    }
                }
                else
                {
                    // already an integer
                    return std::bit_cast<ValueType>( value_ );
                }
            }
        public:
            constexpr ValueType ModF( ValueType& intPart ) noexcept
            {
                if ( IsInfOrNaN( ) == false )
                {
                    Int32 exponent = Exponent( );

                    if ( exponent < static_cast<Int32>( FractionWidth ) )
                    {
                        if ( exponent > -1 )
                        {
                            // abs(x) is greater or equal to 1
                            Int32 trimSize = FractionWidth - exponent;
                            UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );
                            intPart = std::bit_cast< ValueType >( result );
                            return std::bit_cast< ValueType >( value_ ) - intPart;
                        }
                        else
                        {
                            // abs(x) is less than 1, then return 0.
                            intPart = Sign( ) ? std::bit_cast< ValueType >( NegativeZeroValue ) : std::bit_cast< ValueType >( ZeroValue );
                            
                            return std::bit_cast<ValueType>( value_ );
                        }
                    }
                    else
                    {
                        // already an integer
                        intPart = std::bit_cast<ValueType>( value_ );
                        return Sign( ) ? std::bit_cast<ValueType>( NegativeZeroValue ) : std::bit_cast<ValueType>( ZeroValue );
                    }
                }
                else
                {
                    intPart = std::bit_cast<ValueType>( value_ );
                    if ( IsInf( ) )
                    {
                        return Sign( ) ? std::bit_cast<ValueType>( NegativeZeroValue ) : std::bit_cast<ValueType>( ZeroValue );
                    }
                    else
                    {
                        return intPart;
                    }
                }
            }




            constexpr ValueType Ceil( ) const noexcept
            {
                if ( IsInfOrNaN( ) || IsZero( ) )
                {
                    return std::bit_cast<ValueType>( value_ );
                }

                Int32 exponent = Exponent( );

                // is this already an integer?
                if ( exponent >= static_cast<Int32>( FractionWidth ) )
                {
                    return std::bit_cast<ValueType>( value_ );
                }

                // If abs(x) is less than 1
                if ( exponent <= -1 )
                {
                    return Sign( ) ? ValueType( -0.0 ) : ValueType( 1.0 );
                }

                Int32 trimSize = FractionWidth - exponent;
                UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );

                // If this is already an integer, return it.
                if ( result == value_ )
                {
                    return std::bit_cast<ValueType>( value_ );
                }
                // If negative, the ceil operation is equivalent to the trunc operation.
                return Sign( ) ? std::bit_cast<ValueType>( result ) : std::bit_cast<ValueType>( result ) + static_cast<ValueType>( 1.0 );
            }

            constexpr ValueType Floor( ) const noexcept
            {
                if ( Sign( ) )
                {
                    FloatingPoint tmp( value_ & ( ExponentMask | FractionMask ), true );
                    return -tmp.Ceil( );
                }
                else
                {
                    return Trunc( );
                }
            }


            constexpr ValueType Round( ) const noexcept
            {
                // If infinity NaN or zero, return it.
                if ( IsInfOrNaN( ) || IsZero( ) )
                {
                    return std::bit_cast<ValueType>( value_ );
                }

                int exponent = Exponent( );

                // If the exponent is greater than the most negative 
                // exponent, then this is already an integer.
                if ( exponent >= static_cast<int>( FractionWidth ) )
                {
                    return std::bit_cast<ValueType>( value_ );
                }

                if ( exponent == -1 )
                {
                    bool isNegative = Sign( );
                    // Absolute value is greater than equal to 0.5 but less than 1.
                    if ( isNegative )
                    {
                        return static_cast<ValueType>( -1.0 );
                    }
                    else
                    {
                        return static_cast<ValueType>( 1.0 );
                    }
                }

                if ( exponent <= -2 )
                {
                    bool isNegative = Sign( );
                    // Absolute value is less than 0.5.
                    if ( isNegative )
                    {
                        return static_cast<ValueType>( -0.0 );
                    }
                    else
                    {
                        return static_cast<ValueType>( 0.0 );
                    }
                }

                UInt32 trimSize = FractionWidth - exponent;

                bool middleBitSet = ( value_ & FractionMask ) & ( UIntType( 1 ) << ( trimSize - 1 ) );

                UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );

                // If this is already an integer, return it.
                if ( result == value_ )
                {
                    return std::bit_cast<ValueType>( value_ );
                }

                if ( !middleBitSet )
                {
                    // Franctional part is less than 0.5 so round value is the
                    // same as the trunc value.
                    return std::bit_cast<ValueType>( result );
                }
                else
                {
                    bool isNegative = Sign( );
                    return isNegative ?
                        std::bit_cast<ValueType>( result ) - static_cast<ValueType>( 1.0 ) :
                        std::bit_cast<ValueType>( result ) + static_cast<ValueType>( 1.0 );
                }
            }
        };
#pragma pack(pop)
        static_assert( sizeof( FloatingPoint<float> ) == sizeof( float ) );
        static_assert( sizeof( FloatingPoint<double> ) == sizeof( double ) );


        // Stores the normalized form of a floating point value.
        // It does not handle the bits patterns for Zero, infinity and NaNs.
        template <typename T>
        class NormalizedFloat
        {
        public:
            using ValueType = std::remove_cvref_t<T>;
            using FloatingPoint = Internal::FloatingPoint<ValueType>;
            using UIntType = typename FloatingPoint::UIntType;

            static constexpr UIntType ExponentMask = FloatingPoint::ExponentMask;
            static constexpr Int32 ExponentWidth = FloatingPoint::ExponentWidth;
            static constexpr Int32 ExponentBias = FloatingPoint::ExponentBias;
            static constexpr Int32 FractionWidth = FloatingPoint::FractionWidth;
            static constexpr UIntType FractionMask = FloatingPoint::FractionMask;
            static constexpr UIntType SignMask = FloatingPoint::SignMask;

            // Max exponent has the form 0xFF...E. So here we must use -2 and not -1.
            static constexpr int MaxExponentValue = ( 1 << ExponentWidth ) - 2;
            static constexpr UIntType One = ( UIntType( 1 ) << FractionWidth );
        private:
            // Unbiased exponent value.
            Int32 exponent_;
            UIntType fraction_;
            bool sign_;


            constexpr unsigned NormalizationShift( UIntType fraction ) noexcept
            {
                unsigned shift = 0;
                while ( ( One & fraction ) == 0 && ( shift < FractionWidth ) )
                {
                    fraction <<= 1;
                    shift++;
                }
                return shift;
            }
        public:

            constexpr NormalizedFloat( Int32 exponent, UIntType fraction, bool sign ) noexcept
                : exponent_( exponent ), fraction_( fraction ), sign_( sign )
            {
                if ( fraction_ < One )
                {
                    auto normalizationShift = NormalizationShift( fraction_ );
                    fraction_ <<= normalizationShift;
                    exponent_ -= normalizationShift;
                }
            }

            constexpr explicit NormalizedFloat( FloatingPoint floatingPoint ) noexcept
                : exponent_( 0 ), fraction_( 0 ), sign_( floatingPoint.Sign( ) )
            {
                if ( floatingPoint.IsInfOrNaN( ) == false && floatingPoint.IsZero( ) == false )
                {
                    if ( ( floatingPoint.value_ & ExponentMask ) == 0 )
                    {
                        // Normalize subnormal numbers.
                        fraction_ = floatingPoint.Fraction( );
                        auto normalizationShift = NormalizationShift( fraction_ );
                        fraction_ <<= normalizationShift;
                        exponent_ = 1 - ExponentBias - normalizationShift;
                    }
                    else
                    {
                        exponent_ = floatingPoint.Exponent( );
                        fraction_ = floatingPoint.Fraction( );
                    }
                }
            }

            constexpr explicit NormalizedFloat( ValueType val ) noexcept
                : NormalizedFloat( FloatingPoint( val ) )
            {
            }

            constexpr void Assign( Int32 exponent, UIntType fraction, bool sign )
            {
                exponent_ = exponent;
                fraction_ = fraction;
                sign_ = sign;
                if ( fraction_ < One )
                {
                    auto normalizationShift = NormalizationShift( fraction_ );
                    fraction_ <<= normalizationShift;
                    exponent_ -= normalizationShift;
                }
            }


            constexpr Int32 Exponent( ) const noexcept
            {
                return exponent_;
            }
            constexpr void SetExponent( Int32 exponent ) noexcept
            {
                exponent_ = exponent;
            }

            constexpr UIntType Fraction( ) const noexcept
            {
                return fraction_;
            }

            constexpr bool Sign( ) const noexcept
            {
                return sign_;
            }


            constexpr int Compare( const NormalizedFloat& other ) const noexcept
            {
                if ( ( sign_ != other.sign_ ) || ( exponent_ > other.exponent_ ) )
                {
                    return sign_ ? -1 : 1;
                }
                else if ( exponent_ == other.exponent_ )
                {
                    if ( fraction_ > other.fraction_ )
                    {
                        return sign_ ? -1 : 1;
                    }
                    else if ( fraction_ == other.fraction_ )
                    {
                        return 0;
                    }
                    else
                    {
                        return sign_ ? 1 : -1;
                    }
                }
                else
                {
                    return sign_ ? 1 : -1;
                }
            }

            // Returns a new normalized floating point number which is equal in value
            // to this number multiplied by 2^e. That is:
            //     new = this *  2^e
            constexpr NormalizedFloat Mul2( int exp ) const noexcept
            {
                NormalizedFloat result = *this;
                result.exponent_ += exp;
                return result;
            }

            constexpr ValueType AsFloatingPoint( ) const noexcept
            {
                int biasedExponent = exponent_ + ExponentBias;

                if ( biasedExponent > MaxExponentValue )
                {
                    return sign_ ? std::bit_cast<ValueType>( FloatingPoint::NegativeInfinityValue ) : std::bit_cast<ValueType>( FloatingPoint::InfinityValue );
                }

                constexpr int subnormalExponent = ExponentBias + 1;
                if ( exponent_ < subnormalExponent )
                {
                    unsigned shift = subnormalExponent - exponent_;
                    // Since exponent > subnormalExponent, shift will allways be greater than zero.
                    if ( shift <= FractionWidth + 1 )
                    {
                        // Generate a subnormal number. Rounding to nearest and round halfway cases to even.
                        const UIntType shiftOutMask = ( UIntType( 1 ) << shift ) - 1;
                        const UIntType shiftOutValue = fraction_ & shiftOutMask;
                        const UIntType halfwayValue = UIntType( 1 ) << ( shift - 1 );
                        Int32 exponent = 0;
                        UIntType fraction = fraction_ >> shift;
                        if ( shiftOutValue > halfwayValue )
                        {
                            fraction += 1;
                        }
                        else if ( shiftOutValue == halfwayValue )
                        {
                            // Round to even.
                            if ( fraction & 0x1 )
                            {
                                fraction += 1;
                            }
                        }

                        // Adding 1 to fraction can lead to overflow. This will only happen when
                        // fraction_ is all ones (0b111..11). For this case, the overflow is carried into the exponent.
                        if ( fraction == One )
                        {
                            exponent = 1;
                        }
                        FloatingPoint result( fraction, exponent, Sign( ) );
                        return result.AsFloatingPoint( );
                    }
                }

                FloatingPoint result( fraction_, exponent_ - 1 + ExponentBias, Sign( ) );
                return result.AsFloatingPoint( );
            }

        };



        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr bool IsInfImpl( T val ) noexcept
        {
            using FloatType = std::remove_cvref_t<T>;
            using UnsignedType = MakeUnsigned<FloatType>;
            constexpr UnsignedType fractionMask = FractionMask<FloatType>;
            constexpr UnsignedType exponentMask = ExponentMask<FloatType>;

            constexpr UnsignedType MaxExponent = FloatingPoint<FloatType>::MaxExponent;
            UnsignedType value = std::bit_cast<UnsignedType>( val );
            return ( value & ( fractionMask | exponentMask ) ) == MaxExponent;
        }

        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr std::remove_cvref_t<T> AbsImpl( T val ) noexcept
        {
            using FloatType = std::remove_cvref_t<T>;
            using UnsignedType = MakeUnsigned<FloatType>;

            constexpr UnsignedType FractionMask = FloatingPoint<FloatType>::FractionMask;
            constexpr UnsignedType ExponentMask = FloatingPoint<FloatType>::ExponentMask;
            constexpr UnsignedType MaxExponent = FloatingPoint<FloatType>::MaxExponent;
            constexpr UnsignedType SignMask = FloatingPoint<FloatType>::SignMask;

            UnsignedType bits = std::bit_cast<UnsignedType>( val );
            // Test for neither NaN nor +/- infinity
            if ( ( bits & ExponentMask ) != MaxExponent ) [[likely]]
            {
                bits &= ~SignMask;
            }
            else
            {
                // NaN or Infinity
                if ( ( bits & FractionMask ) == 0 )
                {
                    // Infinity
                    bits &= ~SignMask;
                }
            }
            return std::bit_cast<FloatType>( bits );
        }

        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr bool SignBitImpl( T val ) noexcept
        {
            using FloatType = std::remove_cvref_t<T>;
            using UnsignedType = MakeUnsigned<FloatType>;
            constexpr UnsignedType SignMask = FloatingPoint<FloatType>::SignMask;

            UnsignedType value = std::bit_cast<UnsignedType>( val );
            return value & SignMask;
        }

        /// <summary>
        /// Get significand and exponent of val
        /// </summary>
        /// <typeparam name="T">floating point type</typeparam>
        /// <param name="val">Value to be decomposed.</param>
        /// <param name="exp">Reference to an int where the value of the exponent is stored.</param>
        /// <returns>The binary significand of val.</returns>
        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr std::remove_cvref_t<T> FRExpImpl( T val, int& exp ) noexcept
        {
            using ValueType = std::remove_cvref_t<T>;
            using FPType = FloatingPoint<ValueType>;
            using NormalizedType = NormalizedFloat<ValueType>;

            FPType fp( val );

            if ( !fp.IsInfOrNaN( ) )
            {
                if ( !fp.IsZero( ) )
                {
                    NormalizedType normalized( fp );
                    exp = normalized.Exponent( ) + 1;
                    normalized.SetExponent( 0 );
                    return normalized.AsFloatingPoint( );
                }
                else
                {
                    exp = 0;
                    return val;
                }
            }
            else
            {
                exp = 0xFFFFFFFF;
                return val;
            }
        }

        /// <summary>
        /// Breaks val into an integral and a fractional part.
        /// </summary>
        /// <typeparam name="T">floating point type</typeparam>
        /// <param name="val">Floating point value to break into parts.</param>
        /// <param name="intpart">
        /// Reference to an object, of the same type as val, where the 
        /// integral part is stored with the same sign as val</param>
        template<typename ValueT>
            requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
        inline constexpr std::remove_cvref_t<ValueT> ModFImpl( ValueT val, ValueT& intPart ) noexcept
        {
            using FloatType = std::remove_cvref_t<ValueT>;
            using FloatingPointType = FloatingPoint<FloatType>;
            FloatingPointType value( val );
            return value.ModF( intPart );
        }


        /// <summary>
        /// Returns a value with the magnitude of magnitudeVal and the sign of signVal.
        /// </summary>
        /// <typeparam name="T">floating point type</typeparam>
        /// <param name="magnitudeVal">
        /// Value with the magnitude of the resulting value.
        /// </param>
        /// <param name="sourceVal">
        /// Value with the sign of the resulting value.
        /// </param>
        /// <returns>
        /// The value with the magnitude of magnitudeVal and the sign of signVal.
        /// </returns>
        template<typename T>
            requires IsFloatingPoint<T>
        inline constexpr std::remove_cvref_t<T> CopySignImpl( T magnitudeVal, T signVal ) noexcept
        {
            using ValueType = std::remove_cvref_t<T>;
            using FPType = FloatingPoint<ValueType>;

            FPType fpMagnitude( magnitudeVal );
            FPType fpSign( signVal );
            fpMagnitude.SetSign( fpSign.Sign( ) );
            return fpMagnitude.AsFloatingPoint( );
        }


        


        
       /*
        * ====================================================
        * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
        *
        * Developed at SunSoft, a Sun Microsystems, Inc. business.
        * Permission to use, copy, modify, and distribute this
        * software is freely granted, provided that this notice
        * is preserved.
        * ====================================================
        */

        template<bool doublePrecision>
        inline constexpr int RemPIo2Core( double* x, double* y, int e0, int nx )
        {
            constexpr int32_t ipio2[] = 
            {
                0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62,
                0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A,
                0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
                0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41,
                0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8,
                0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
                0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5,
                0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08,
                0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
                0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880,
                0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B
            };
            constexpr double PIo2[] = 
            {
                1.57079625129699707031e+00,
                7.54978941586159635335e-08,
                5.39030252995776476554e-15,
                3.28200341580791294123e-22,
                1.27065575308067607349e-29,
                1.22933308981111328932e-36,
                2.73370053816464559624e-44,
                2.16741683877804819444e-51,
            };

            
            constexpr double zero = 0.0;
            constexpr double one = 1.0;
            constexpr double two24 = 1.67772160000000000000e+07;
            constexpr double twon24 = 5.96046447753906250000e-08;

            // initialize jk
            Int32 jk = doublePrecision?4:3;
            Int32 jp = jk;

            // determine jx,jv,q0, note that 3>q0 
            Int32 jx = nx - 1;
            Int32 jv = ( e0 - 3 ) / 24; if ( jv < 0 ) jv = 0;
            Int32 q0 = e0 - 24 * ( jv + 1 );

            // set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] 
            Int32 j = jv - jx; 
            Int32 m = jx + jk;
            double f[20];
            for ( Int32 i = 0; i <= m; i++, j++ )
            {
                f[i] = ( j < 0 ) ? zero : (double)ipio2[j];
            }

            double q[20];
            // compute q[0],q[1],...q[jk] 
            for ( Int32 i = 0; i <= jk; i++ )
            {
                double fw = 0.0;
                for ( j = 0; j <= jx; j++ )
                {
                    fw += x[j] * f[jx + i - j];
                }
                q[i] = fw;
            }

            Int32 jz = jk;

            Int32 iq[20];
            Int32 ih;
            Int32 n = 0;
            double z;

            bool notDone;
            do 
            {
                notDone = false;
                // distill q[] into iq[] reversingly 
                z = q[jz];
                for ( Int32 i = 0, j = jz; j > 0; i++, j-- )
                {
                    double fw = (double)( (int32_t)( twon24 * z ) );
                    iq[i] = (int32_t)( z - two24 * fw );
                    z = q[j - 1] + fw;
                }

                // compute n 

                // actual value of z 
                z = ScaleByN( z, q0 );
                // trim off integer >= 8 
                z -= 8.0 * Floor( z * 0.125 );
                Int32 n = (int32_t)z;
                z -= (double)n;
                ih = 0;
                if ( q0 > 0 )
                {	
                    // need iq[jz-1] to determine n 
                    Int32 i = ( iq[jz - 1] >> ( 24 - q0 ) ); 
                    n += i;
                    iq[jz - 1] -= i << ( 24 - q0 );
                    ih = iq[jz - 1] >> ( 23 - q0 );
                }
                else if ( q0 == 0 )
                {
                    ih = iq[jz - 1] >> 23;
                }
                else if ( z >= 0.5 )
                {
                    ih = 2;
                }

                if ( ih > 0 )
                {	
                    // q > 0.5 
                    n += 1; 
                    Int32 carry = 0;
                    for ( Int32 i = 0; i < jz; i++ )
                    {	
                        // compute 1-q 
                        j = iq[i];
                        if ( carry == 0 )
                        {
                            if ( j != 0 )
                            {
                                carry = 1; 
                                iq[i] = 0x1000000 - j;
                            }
                        }
                        else
                        {
                            iq[i] = 0xffffff - j;
                        }
                    }
                    if ( q0 > 0 )
                    {	
                        // rare case: chance is 1 in 12 
                        switch ( q0 )
                        {
                            case 1:
                                iq[jz - 1] &= 0x7fffff; 
                                break;
                            case 2:
                                iq[jz - 1] &= 0x3fffff; 
                                break;
                        }
                    }
                    if ( ih == 2 )
                    {
                        z = one - z;
                        if ( carry != 0 ) 
                            z -= ScaleByN( one, q0 );
                    }
                }

                // check if recomputation is needed 
                if ( z == zero )
                {
                    j = 0;
                    for ( Int32 i = jz - 1; i >= jk; i-- )
                    {
                        j |= iq[i];
                    }
                    if ( j == 0 )
                    { 
                        // need recomputation 
                        // k = no. of terms needed 
                        Int32 k = 1;
                        for (; iq[jk - k] == 0; k++ )
                        { 
                            // Do nothing ...
                        }

                        for ( Int32 i = jz + 1; i <= jz + k; i++ )
                        {
                            // add q[jz+1] to q[jz+k] 
                            f[jx + i] = (double)ipio2[jv + i];
                            double fw = 0.0;
                            for ( j = 0; j <= jx; j++ )
                            {
                                fw += x[j] * f[jx + i - j];
                            }
                            q[i] = fw;
                        }
                        jz += k;
                        notDone = true;
                    }
                }
            } while ( notDone );

            // chop off zero terms 
            if ( z == 0.0 )
            {
                jz -= 1; 
                q0 -= 24;
                while ( iq[jz] == 0 ) 
                { 
                    jz--; 
                    q0 -= 24; 
                }
            }
            else
            { 
                // break z into 24-bit if necessary 
                z = ScaleByN( z, -q0 );
                if ( z >= two24 )
                {
                    double fw = (double)( (int32_t)( twon24 * z ) );
                    iq[jz] = (int32_t)( z - two24 * fw );
                    jz += 1; q0 += 24;
                    iq[jz] = (int32_t)fw;
                }
                else iq[jz] = (int32_t)z;
            }

            // convert integer "bit" chunk to floating-point value 
            double fw = ScaleByN( one, q0 );
            for ( Int32 i = jz; i >= 0; i-- )
            {
                q[i] = fw * (double)iq[i]; 
                fw *= twon24;
            }

            // compute PIo2[0,...,jp]*q[jz,...,0] 
            double fq[20];
            for ( Int32 i = jz; i >= 0; i-- )
            {
                fw = 0.0;
                for ( Int32 k = 0; k <= jp && k <= jz - i; k++ )
                {
                    fw += PIo2[k] * q[i + k];
                }
                fq[jz - i] = fw;
            }

            // compress fq[] into y[] 
            fw = 0.0;
            if constexpr ( doublePrecision )
            {
                for ( Int32 i = jz; i >= 0; i-- )
                {
                    fw += fq[i];
                }

                y[0] = ( ih == 0 ) ? fw : -fw;
                fw = fq[0] - fw;
                for ( Int32 i = 1; i <= jz; i++ )
                {
                    fw += fq[i];
                }
                y[1] = ( ih == 0 ) ? fw : -fw;
            }
            else
            {
                for ( Int32 i = jz; i >= 0; i-- )
                {
                    fw += fq[i];
                }
                y[0] = ( ih == 0 ) ? fw : -fw;
            }

            return n & 7;
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         *
         * Optimized by Bruce D. Evans.
         */

        inline constexpr int RemPIo2Medium( Int32 ix, double x, double* y ) noexcept
        {
            constexpr double invpio2 = 6.36619772367581382433e-01;
            constexpr double pio2_1 = 1.57079632673412561417e+00;
            constexpr double pio2_1t = 6.07710050650619224932e-11;
            constexpr double pio2_2 = 6.07710050630396597660e-11;
            constexpr double pio2_2t = 2.02226624879595063154e-21;
            constexpr double pio2_3 = 2.02226624871116645580e-21;
            constexpr double pio2_3t = 8.47842766036889956997e-32;

            // Use a specialized rint() to get fn.  Assume round-to-nearest. 
            double fn = x * invpio2 + 0x1.8p52;
            fn = fn - 0x1.8p52;
            Int32 n = (int32_t)fn;

            double r = x - fn * pio2_1;
            // 1st round good to 85 bit 
            double w = fn * pio2_1t;


            Int32 j = ix >> 20;
            y[0] = r - w;
            UInt32 high = GetHigh32Bits<UInt32>( y[0] );
            Int32 i = j - ( ( high >> 20 ) & 0x7ff );
            if ( i > 16 )
            {
                // 2nd iteration needed, good to 118 
                double t = r;
                w = fn * pio2_2;
                r = t - w;
                w = fn * pio2_2t - ( ( t - r ) - w );
                y[0] = r - w;
                high = GetHigh32Bits<UInt32>( y[0] );
                i = j - ( ( high >> 20 ) & 0x7ff );
                if ( i > 49 )
                {
                    // 3rd iteration need, 151 bits acc 
                    // will cover all possible cases 
                    t = r;
                    w = fn * pio2_3;
                    r = t - w;
                    w = fn * pio2_3t - ( ( t - r ) - w );
                    y[0] = r - w;
                }
            }

            y[1] = ( r - y[0] ) - w;
            return n;
        }


        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         *
         * Optimized by Bruce D. Evans.
         */
        inline constexpr int RemPIo2( double x, double* y ) noexcept
        {
            constexpr double zero = 0.00000000000000000000e+00;
            constexpr double two24 = 1.67772160000000000000e+07;
            constexpr double invpio2 = 6.36619772367581382433e-01;
            constexpr double pio2_1 = 1.57079632673412561417e+00;
            constexpr double pio2_1t = 6.07710050650619224932e-11;
            constexpr double pio2_2 = 6.07710050630396597660e-11;
            constexpr double pio2_2t = 2.02226624879595063154e-21;
            constexpr double pio2_3 = 2.02226624871116645580e-21;
            constexpr double pio2_3t = 8.47842766036889956997e-32;

            double z;
            double tx[3]; 
            double ty[2];
            Int32 e0, i, n;
            UInt32 low;
            // high word of x 
            Int32 hx = GetLow32Bits<Int32>( x );

            Int32 ix = hx & 0x7fffffff;
#if 0 // This *must* be handled by caller. 
            if ( ix <= 0x3fe921fb )   
            {
                // |x| ~<= pi/4 , no need for reduction 
                y[0] = x; 
                y[1] = 0; 
                return 0;
            }
#endif
            if ( ix <= 0x400f6a7a )
            {		
                // |x| ~<= 5pi/4 
                if ( ( ix & 0xfffff ) == 0x921fb )
                {
                    // |x| ~= pi/2 or 2pi/2 
                    // cancellation -- use medium case 
                    return RemPIo2Medium( ix, x, y );
                }
                if ( ix <= 0x4002d97c )
                {	
                    // |x| ~<= 3pi/4 
                    if ( hx > 0 )
                    {
                        // one round good to 85 bits 
                        z = x - pio2_1;	
                        y[0] = z - pio2_1t;
                        y[1] = ( z - y[0] ) - pio2_1t;
                        return 1;
                    }
                    else
                    {
                        z = x + pio2_1;
                        y[0] = z + pio2_1t;
                        y[1] = ( z - y[0] ) + pio2_1t;
                        return -1;
                    }
                }
                else
                {
                    if ( hx > 0 )
                    {
                        z = x - 2 * pio2_1;
                        y[0] = z - 2 * pio2_1t;
                        y[1] = ( z - y[0] ) - 2 * pio2_1t;
                        return 2;
                    }
                    else
                    {
                        z = x + 2 * pio2_1;
                        y[0] = z + 2 * pio2_1t;
                        y[1] = ( z - y[0] ) + 2 * pio2_1t;
                        return -2;
                    }
                }
            }
            if ( ix <= 0x401c463b )
            {		
                // |x| ~<= 9pi/4 
                if ( ix <= 0x4015fdbc )
                {	
                    // |x| ~<= 7pi/4 
                    if ( ix == 0x4012d97c )
                    {
                        // |x| ~= 3pi/2 
                        return RemPIo2Medium( ix, x, y );
                    }
                    if ( hx > 0 )
                    {
                        z = x - 3 * pio2_1;
                        y[0] = z - 3 * pio2_1t;
                        y[1] = ( z - y[0] ) - 3 * pio2_1t;
                        return 3;
                    }
                    else
                    {
                        z = x + 3 * pio2_1;
                        y[0] = z + 3 * pio2_1t;
                        y[1] = ( z - y[0] ) + 3 * pio2_1t;
                        return -3;
                    }
                }
                else
                {
                    if ( ix == 0x401921fb )
                    {
                        // |x| ~= 4pi/2 
                        return RemPIo2Medium( ix, x, y );
                    }
                    if ( hx > 0 )
                    {
                        z = x - 4 * pio2_1;
                        y[0] = z - 4 * pio2_1t;
                        y[1] = ( z - y[0] ) - 4 * pio2_1t;
                        return 4;
                    }
                    else
                    {
                        z = x + 4 * pio2_1;
                        y[0] = z + 4 * pio2_1t;
                        y[1] = ( z - y[0] ) + 4 * pio2_1t;
                        return -4;
                    }
                }
            }
            if ( ix < 0x413921fb )
            {	
                // |x| ~< 2^20*(pi/2), medium size 
                return RemPIo2Medium( ix, x, y );
            }

            // all other (large) arguments
            if ( ix >= 0x7ff00000 )
            {		
                // x is inf or NaN 
                y[0] = y[1] = x - x; 
                return 0;
            }
            // set z = scalbn(|x|,ilogb(x)-23) 

            low = GetLow32Bits<Int32>( x );
            
            // e0 = ilogb(z)-23; 
            e0 = ( ix >> 20 ) - 1046;	

            z = From32BitsTo64Bits<double>( ix - ( (int32_t)( e0 << 20 ) ), low );
            for ( i = 0; i < 2; i++ )
            {
                tx[i] = (double)( (int32_t)( z ) );
                z = ( z - tx[i] ) * two24;
            }
            tx[2] = z;
            Int32 nx = 3;
            while ( tx[nx - 1] == zero )
            {
                // skip zero term 
                nx--;	
            }
            n = RemPIo2Core<true>( tx, ty, e0, nx );
            if ( hx < 0 ) 
            { 
                y[0] = -ty[0]; 
                y[1] = -ty[1]; 
                return -n; 
            }
            y[0] = ty[0]; 
            y[1] = ty[1]; 
            return n;
        }

        /* e_rem_pio2f.c -- float version of e_rem_pio2.c
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         * Debugged and optimized by Bruce D. Evans.
         */
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        inline constexpr int RemPIo2( float x, double* y ) noexcept
        {
            // 53 bits of 2/pi
            constexpr double invpio2 = 6.36619772367581382433e-01;
            // first  33 bit of pi/2
            constexpr double pio2_1 = 1.57079631090164184570e+00;
            // pi/2 - pio2_1
            constexpr double pio2_1t = 1.58932547735281966916e-08;

            double w, r, fn;
            double tx[1], ty[1];
            Int32 n;

            Int32 hx = std::bit_cast<Int32>( x );
            Int32 ix = hx & 0x7fffffff;
            // 33+53 bit pi is good enough for medium size 
            if ( ix < 0x4dc90fdb )
            {		
                // |x| ~< 2^28*(pi/2), medium size
                fn = x * invpio2 + 0x1.8p52;
                fn = fn - 0x1.8p52;
                n = (int32_t)fn;
                r = x - fn * pio2_1;
                w = fn * pio2_1t;
                *y = r - w;
                return n;
            }
            // all other (large) arguments
            if ( ix >= 0x7f800000 )
            {		
                // x is inf or NaN 
                *y = x - x; 
                return 0;
            }
            // set z = scalbn(|x|,ilogb(|x|)-23) 

            // e0 = ilogb(|x|)-23; 
            Int32 e0 = ( ix >> 23 ) - 150;
            float z = std::bit_cast<float>(ix - ( (int32_t)( e0 << 23 ) ) );
            tx[0] = z;
            n = RemPIo2Core<false>( tx, ty, e0, 1 );
            if ( hx < 0 ) 
            { 
                *y = -ty[0]; 
                return -n; 
            }
            *y = ty[0]; 
            return n;

        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr double SinCore( double x, double y, int iy ) noexcept
        {
            constexpr double half = 5.00000000000000000000e-01;
            constexpr double S1 = -1.66666666666666324348e-01;
            constexpr double S2 = 8.33333333332248946124e-03;
            constexpr double S3 = -1.98412698298579493134e-04;
            constexpr double S4 = 2.75573137070700676789e-06;
            constexpr double S5 = -2.50507602534068634195e-08;
            constexpr double S6 = 1.58969099521155010221e-10;

            double z = x * x;
            double w = z * z;
            double r = S2 + z * ( S3 + z * S4 ) + z * w * ( S5 + z * S6 );
            double v = z * x;
            if ( iy == 0 )
            {
                return x + v * ( S1 + z * r );
            }
            else
            {
                return x - ( ( z * ( half * y - v * r ) - y ) - v * S1 );
            }
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr double SinCore( double x ) noexcept
        {
            constexpr double S1 = -1.66666666666666324348e-01;
            constexpr double S2 = 8.33333333332248946124e-03;
            constexpr double S3 = -1.98412698298579493134e-04;
            constexpr double S4 = 2.75573137070700676789e-06;
            constexpr double S5 = -2.50507602534068634195e-08;
            constexpr double S6 = 1.58969099521155010221e-10;

            double z = x * x;
            double w = z * z;
            double r = S2 + z * ( S3 + z * S4 ) + z * w * ( S5 + z * S6 );
            double v = z * x;
            return x + v * ( S1 + z * r );
        }

        /* k_sinf.c -- float version of k_sin.c
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         * Optimized by Bruce D. Evans.
         */
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        inline constexpr float SinCoreF( double x ) noexcept
        {
            constexpr double S1 = -0x15555554cbac77.0p-55;
            constexpr double S2 = 0x111110896efbb2.0p-59;
            constexpr double S3 = -0x1a00f9e2cae774.0p-65;
            constexpr double S4 = 0x16cd878c3b46a7.0p-71;

            double z = x * x;
            double w = z * z;
            double r = S3 + z * S4;
            double s = z * x;
            return static_cast<float>(( x + s * ( S1 + z * S2 ) ) + s * w * r);
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr double CosCore( double x, double y ) noexcept
        {
            constexpr double one = 1.00000000000000000000e+00;
            constexpr double C1 = 4.16666666666666019037e-02;
            constexpr double C2 = -1.38888888888741095749e-03;
            constexpr double C3 = 2.48015872894767294178e-05;
            constexpr double C4 = -2.75573143513906633035e-07;
            constexpr double C5 = 2.08757232129817482790e-09;
            constexpr double C6 = -1.13596475577881948265e-11; 

            double z = x * x;
            double w = z * z;
            double r = z * ( C1 + z * ( C2 + z * C3 ) ) + w * w * ( C4 + z * ( C5 + z * C6 ) );
            double hz = 0.5 * z;
            w = one - hz;
            return w + ( ( ( one - w ) - hz ) + ( z * r - x * y ) );
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr double CosCore( double x ) noexcept
        {
            constexpr double one = 1.00000000000000000000e+00;
            constexpr double C1 = 4.16666666666666019037e-02;
            constexpr double C2 = -1.38888888888741095749e-03;
            constexpr double C3 = 2.48015872894767294178e-05;
            constexpr double C4 = -2.75573143513906633035e-07;
            constexpr double C5 = 2.08757232129817482790e-09;
            constexpr double C6 = -1.13596475577881948265e-11;

            double z = x * x;
            double w = z * z;
            double r = z * ( C1 + z * ( C2 + z * C3 ) ) + w * w * ( C4 + z * ( C5 + z * C6 ) );
            double hz = 0.5 * z;
            w = one - hz;
            return w + ( ( ( one - w ) - hz ) + ( z * r ) );
        }


        /* k_cosf.c -- float version of k_cos.c
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         * Debugged and optimized by Bruce D. Evans.
         */

         /*
          * ====================================================
          * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
          *
          * Developed at SunPro, a Sun Microsystems, Inc. business.
          * Permission to use, copy, modify, and distribute this
          * software is freely granted, provided that this notice
          * is preserved.
          * ====================================================
          */
        inline constexpr float CosCoreF( double x ) noexcept
        {
            constexpr double one = 1.0;
            constexpr double C0 = -0x1ffffffd0c5e81.0p-54;
            constexpr double C1 = 0x155553e1053a42.0p-57;
            constexpr double C2 = -0x16c087e80f1e27.0p-62;
            constexpr double C3 = 0x199342e0ee5069.0p-68;

            double z = x * x;
            double w = z * z;
            double r = C2 + z * C3;
            return static_cast<float>( ( ( one + z * C0 ) + w * C1 ) + ( w * z ) * r );
        }


        /*
         * ====================================================
         * Copyright 2004 Sun Microsystems, Inc.  All Rights Reserved.
         *
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr double TanCore( double x, double y, int iy )
        {
            constexpr double T0 = 3.33333333333334091986e-01;
            constexpr double T1 = 1.33333333333201242699e-01;
            constexpr double T2 = 5.39682539762260521377e-02;
            constexpr double T3 = 2.18694882948595424599e-02;
            constexpr double T4 = 8.86323982359930005737e-03;
            constexpr double T5 = 3.59207910759131235356e-03;
            constexpr double T6 = 1.45620945432529025516e-03;
            constexpr double T7 = 5.88041240820264096874e-04;
            constexpr double T8 = 2.46463134818469906812e-04;
            constexpr double T9 = 7.81794442939557092300e-05;
            constexpr double T10 = 7.14072491382608190305e-05;
            constexpr double T11 = -1.85586374855275456654e-05;
            constexpr double T12 = 2.59073051863633712884e-05;

            constexpr double one = 1.00000000000000000000e+00;
            constexpr double pio4 = 7.85398163397448278999e-01;
            constexpr double pio4lo = 3.06161699786838301793e-17;


            double z, w;

            // high word of |x| 
            auto hx = GetHigh32Bits<Int32>( x );
            auto ix = hx & 0x7fffffff;

            if ( ix >= 0x3FE59428 )
            {	
                // |x| >= 0.6744 
                if ( hx < 0 )
                {
                    x = -x;
                    y = -y;
                }
                z = pio4 - x;
                w = pio4lo - y;
                x = z + w;
                y = 0.0;
            }
            z = x * x;
            w = z * z;
            
            // Break x^5*(T[1]+x^2*T[2]+...) into
            // x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +  x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))

            double r = T1 + w * ( T3 + w * ( T5 + w * ( T7 + w * ( T9 + w * T11 ) ) ) );
            double v = z * ( T2 + w * ( T4 + w * ( T6 + w * ( T8 + w * ( T10 + w * T12 ) ) ) ) );
            double s = z * x;
            r = y + z * ( s * ( r + v ) + y );
            
            r += T0 * s;
            w = x + r;
            if ( ix >= 0x3FE59428 )
            {
                v = (double)iy;
                return (double)( 1 - ( ( hx >> 30 ) & 2 ) ) * ( v - 2.0 * ( x - ( w * w / ( w + v ) - r ) ) );
            }
            else if ( iy == 1 )
            {
                return w;
            }
            else
            {
                // compute -1.0 / (x+r) accurately 
                double a, t;
                z = w;
                z = SetLow32Bits( z, 0 );

                // z+v = r+x 
                v = r - ( z - x );	

                // a = -1.0/w 
                t = a = -1.0 / w;
                t = SetLow32Bits( t, 0 );
                s = 1.0 + t * z;
                return t + a * ( s + t * v );
            }
        }

        inline constexpr double TanCore( double x )
        {
            constexpr double T0 = 3.33333333333334091986e-01;
            constexpr double T1 = 1.33333333333201242699e-01;
            constexpr double T2 = 5.39682539762260521377e-02;
            constexpr double T3 = 2.18694882948595424599e-02;
            constexpr double T4 = 8.86323982359930005737e-03;
            constexpr double T5 = 3.59207910759131235356e-03;
            constexpr double T6 = 1.45620945432529025516e-03;
            constexpr double T7 = 5.88041240820264096874e-04;
            constexpr double T8 = 2.46463134818469906812e-04;
            constexpr double T9 = 7.81794442939557092300e-05;
            constexpr double T10 = 7.14072491382608190305e-05;
            constexpr double T11 = -1.85586374855275456654e-05;
            constexpr double T12 = 2.59073051863633712884e-05;

            constexpr double one = 1.00000000000000000000e+00;
            constexpr double pio4 = 7.85398163397448278999e-01;
            constexpr double pio4lo = 3.06161699786838301793e-17;


            double z, w;

            // high word of |x| 
            auto hx = GetHigh32Bits<Int32>( x );
            auto ix = hx & 0x7fffffff;

            if ( ix >= 0x3FE59428 )
            {	
                // |x| >= 0.6744 
                if ( hx < 0 )
                {
                    x = -x;
                }
                z = pio4 - x;
                w = pio4lo;
                x = z + w;
            }
            z = x * x;
            w = z * z;

            // Break x^5*(T[1]+x^2*T[2]+...) into
            // x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +  x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))

            double r = T1 + w * ( T3 + w * ( T5 + w * ( T7 + w * ( T9 + w * T11 ) ) ) );
            double v = z * ( T2 + w * ( T4 + w * ( T6 + w * ( T8 + w * ( T10 + w * T12 ) ) ) ) );
            double s = z * x;
            r = z * ( s * ( r + v ) );
            r += T0 * s;
            w = x + r;
            if ( ix >= 0x3FE59428 )
            {
                return (double)( 1 - ( ( hx >> 30 ) & 2 ) ) * ( 1.0 - 2.0 * ( x - ( w * w / ( w + 1.0 ) - r ) ) );
            }
            else
            {
                return w;
            }
        }


        /* k_tanf.c -- float version of k_tan.c
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         * Optimized by Bruce D. Evans.
         */
        /*
         * ====================================================
         * Copyright 2004 Sun Microsystems, Inc.  All Rights Reserved.
         *
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        template<bool inverse>
        inline constexpr float TanCoreF( double x )
        {
            constexpr double T0 = 0x15554d3418c99f.0p-54;
            constexpr double T1 = 0x1112fd38999f72.0p-55;
            constexpr double T2 = 0x1b54c91d865afe.0p-57;
            constexpr double T3 = 0x191df3908c33ce.0p-58;
            constexpr double T4 = 0x185dadfcecf44e.0p-61;
            constexpr double T5 = 0x1362b9bf971bcd.0p-59;

            double z = x * x;
            double r = T4 + z * T5;
            double t = T2 + z * T3;


            double w = z * z;
            double s = z * x;
            double u = T0 + z * T1;
            r = ( x + s * u ) + ( s * w ) * ( t + w * r );
            if constexpr ( inverse == false )
            {
                return static_cast<float>( r );
            }
            else
            {
                return static_cast<float>( -1.0 / r );
            }
        }
        inline constexpr float TanCoreF( double x )
        {
            constexpr double T0 = 0x15554d3418c99f.0p-54;
            constexpr double T1 = 0x1112fd38999f72.0p-55;
            constexpr double T2 = 0x1b54c91d865afe.0p-57;
            constexpr double T3 = 0x191df3908c33ce.0p-58;
            constexpr double T4 = 0x185dadfcecf44e.0p-61;
            constexpr double T5 = 0x1362b9bf971bcd.0p-59;

            double z = x * x;
            double r = T4 + z * T5;
            double t = T2 + z * T3;
            double w = z * z;
            double s = z * x;
            double u = T0 + z * T1;
            r = ( x + s * u ) + ( s * w ) * ( t + w * r );
            return static_cast<float>( r );
        }


        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        
        inline constexpr double SinImpl( double x ) noexcept
        {
            // pi/4 
            constexpr double PIo4 = M_PI_4;
            double ax = std::bit_cast<double>( std::bit_cast<UInt64>( x ) & 0x7FFFFFFFFFFFFFFFULL );

            if( ax <= PIo4 )
            {
                // |x| < 2**-26 
                if ( ax < 0x1.0p-26 )
                {
                    return x;
                }
                // generate simplified inexact 
                return SinCore( x );
            }
            else if ( std::bit_cast<UInt64>(ax) >= 0x7ff0000000000000ULL )
            {
                // sin(Inf or NaN) is NaN 
                return x - x;
            }
            else
            {
                // argument reduction needed 
                double y[2];
                Int32 n = RemPIo2( x, y );
                switch ( n & 3 )
                {
                    case 0:
                        return  SinCore( y[0], y[1], 1 );
                    case 1:
                        return  CosCore( y[0], y[1] );
                    case 2:
                        return -SinCore( y[0], y[1], 1 );
                    default:
                        return -CosCore( y[0], y[1] );
                }
            }
        }

        /* s_sinf.c -- float version of s_sin.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         * Optimized by Bruce D. Evans.
         */
         /*
          * ====================================================
          * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
          *
          * Developed at SunPro, a Sun Microsystems, Inc. business.
          * Permission to use, copy, modify, and distribute this
          * software is freely granted, provided that this notice
          * is preserved.
          * ====================================================
          */
        inline constexpr float SinImpl( float x ) noexcept
        {
            constexpr double s1pio2 = 1 * M_PI_2;
            constexpr double s2pio2 = 2 * M_PI_2;
            constexpr double s3pio2 = 3 * M_PI_2;
            constexpr double s4pio2 = 4 * M_PI_2;

            auto hx = std::bit_cast<UInt32>( x );
            auto ix = hx & 0x7fffffff;

            if ( ix <= 0x3f490fda )
            {
                // |x| ~<= pi/4 
                if ( ix < 0x39800000 )
                {
                    // |x| < 2**-12 
                    if ( ( (int)x ) == 0 )
                    { 
                        // x with inexact if x != 0 
                        return x;	
                    }
                }
                return SinCoreF( x );
            }
            if ( ix <= 0x407b53d1 )
            {		
                // |x| ~<= 5*pi/4 
                if ( ix <= 0x4016cbe3 )
                {	
                    // |x| ~<= 3pi/4 
                    if ( hx > 0 )
                        return CosCoreF( x - s1pio2 );
                    else
                        return -CosCoreF( x + s1pio2 );
                }
                else
                    return SinCoreF( ( hx > 0 ? s2pio2 : -s2pio2 ) - x );
            }
            if ( ix <= 0x40e231d5 )
            {
                // |x| ~<= 9*pi/4 
                if ( ix <= 0x40afeddf )
                {	
                    // |x| ~<= 7*pi/4 
                    if ( hx > 0 )
                        return -CosCoreF( x - s3pio2 );
                    else
                        return CosCoreF( x + s3pio2 );
                }
                else
                    return SinCoreF( x + ( hx > 0 ? -s4pio2 : s4pio2 ) );
            }
            else if ( ix >= 0x7f800000 )
            {
                // sin(Inf or NaN) is NaN 
                return x - x;
            }
            else
            {
                // general argument reduction needed 
                double y;
                auto n = RemPIo2( x, &y );
                switch ( n & 3 )
                {
                    case 0: 
                        return  SinCoreF( y );
                    case 1: 
                        return  CosCoreF( y );
                    case 2: 
                        return  SinCoreF( -y );
                    default:
                        return -CosCoreF( y );
                }
            }
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr double ASinImpl( double x ) noexcept
        {
            constexpr double one = 1.00000000000000000000e+00;
            constexpr double huge = 1.000e+300;
            constexpr double pio2_hi = 1.57079632679489655800e+00;
            constexpr double pio2_lo = 6.12323399573676603587e-17;
            constexpr double pio4_hi = 7.85398163397448278999e-01;
            // coefficient for R(x^2) 
            constexpr double pS0 = 1.66666666666666657415e-01;
            constexpr double pS1 = -3.25565818622400915405e-01;
            constexpr double pS2 = 2.01212532134862925881e-01;
            constexpr double pS3 = -4.00555345006794114027e-02;
            constexpr double pS4 = 7.91534994289814532176e-04;
            constexpr double pS5 = 3.47933107596021167570e-05;
            constexpr double qS1 = -2.40339491173441421878e+00;
            constexpr double qS2 = 2.02094576023350569471e+00;
            constexpr double qS3 = -6.88283971605453293030e-01;
            constexpr double qS4 = 7.70381505559019352791e-02;

            double t = 0.0, w, p, q, c, r, s;
            
            Int32 hx = GetHigh32Bits<Int32>( x );
            Int32 ix = hx & 0x7fffffff;
            if ( ix >= 0x3ff00000 )
            {
                // |x|>= 1 
                UInt32 lx = GetLow32Bits<UInt32>( x );
                if ( ( ( ix - 0x3ff00000 ) | lx ) == 0 )
                {
                    // asin(1)=+-pi/2 with inexact 
                    return x * pio2_hi + x * pio2_lo;
                }
                // asin(|x|>1) is NaN 
                return ( x - x ) / ( x - x );
            }
            else if ( ix < 0x3fe00000 )
            {	
                // |x|<0.5 
                if ( ix < 0x3e500000 )
                {		
                    // if |x| < 2**-26 
                    if ( huge + x > one )
                    {
                        // return x with inexact if x!=0
                        return x;
                    }
                }
                t = x * x;
                p = t * ( pS0 + t * ( pS1 + t * ( pS2 + t * ( pS3 + t * ( pS4 + t * pS5 ) ) ) ) );
                q = one + t * ( qS1 + t * ( qS2 + t * ( qS3 + t * qS4 ) ) );
                w = p / q;
                return x + x * w;
            }
            // 1> |x|>= 0.5 
            w = one - Abs( x );
            t = w * 0.5;
            p = t * ( pS0 + t * ( pS1 + t * ( pS2 + t * ( pS3 + t * ( pS4 + t * pS5 ) ) ) ) );
            q = one + t * ( qS1 + t * ( qS2 + t * ( qS3 + t * qS4 ) ) );
            s = Sqrt( t );
            if ( ix >= 0x3FEF3333 )
            { 	
                // if |x| > 0.975 
                w = p / q;
                t = pio2_hi - ( 2.0 * ( s + s * w ) - pio2_lo );
            }
            else
            {
                w = s;
                w = SetLow32Bits( w, 0 );
                c = ( t - w * w ) / ( s + w );
                r = p / q;
                p = 2.0 * s * r - ( pio2_lo - 2.0 * c );
                q = pio4_hi - 2.0 * w;
                t = pio4_hi - ( p - q );
            }
            if ( hx > 0 ) 
                return t; 
            else 
                return -t;
        }


        inline constexpr float ASinImpl( float x ) noexcept
        {
            constexpr float one = 1.0000000000e+00f;
            constexpr float huge = 1.000e+30f;
            // coefficient for R(x^2) 
            constexpr float pS0 = 1.6666586697e-01f;
            constexpr float pS1 = -4.2743422091e-02f;
            constexpr float pS2 = -8.6563630030e-03f;
            constexpr float qS1 = -7.0662963390e-01f;

            constexpr float pio2 = 1.570796326794896558e+00f;

            float s;
            float t, w, p, q;
            Int32 hx = std::bit_cast<Int32>( x );
            Int32 ix = hx & 0x7fffffff;
            if ( ix >= 0x3f800000 )
            {
                // |x| >= 1 

                // |x| == 1 
                if ( ix == 0x3f800000 )
                {
                    // asin(+-1) = +-pi/2 with inexact 
                    return x * pio2;
                }
                // asin(|x|>1) is NaN 
                return ( x - x ) / ( x - x );
            }
            else if ( ix < 0x3f000000 )
            {	
                // |x|<0.5 
                if ( ix < 0x39800000 )
                {	
                    // |x| < 2**-12 
                    if ( huge + x > one )
                    {
                        // return x with inexact if x!=0
                        return x;
                    }
                }
                t = x * x;
                p = t * ( pS0 + t * ( pS1 + t * pS2 ) );
                q = one + t * qS1;
                w = p / q;
                return x + x * w;
            }
            // 1> |x|>= 0.5 
            w = one - Abs( x );
            t = w * (float)0.5;
            p = t * ( pS0 + t * ( pS1 + t * pS2 ) );
            q = one + t * qS1;
            s = Sqrt( t );
            w = p / q;
            t = pio2 - 2.0f * ( s + s * w );
            if ( hx > 0 ) return t; else return -t;
        }


        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr double CosImpl( double x ) noexcept
        {
            auto ix = GetHigh32Bits<Int32>( x );

            // |x| ~< pi/4 
            ix &= 0x7fffffff;
            if ( ix <= 0x3fe921fb )
            {
                // if x < 2**-27 * sqrt(2) 
                if ( ix < 0x3e46a09e )
                {
                    if ( ( (int)x ) == 0 )
                    {
                        return 1.0;
                    }
                }
                return CosCore( x );
            }
            else if ( ix >= 0x7ff00000 )
            {
                // cos(Inf or NaN) is NaN 
                return x - x;
            }
            else
            {
                // argument reduction needed 
                double y[2];
                auto n = RemPIo2( x, y );
                switch ( n & 3 )
                {
                    case 0: 
                        return  CosCore( y[0], y[1] );
                    case 1: 
                        return -SinCore( y[0], y[1], 1 );
                    case 2: 
                        return -CosCore( y[0], y[1] );
                    default:
                        return SinCore( y[0], y[1], 1 );
                }
            }
        }

        /* s_cosf.c -- float version of s_cos.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         * Optimized by Bruce D. Evans.
         */

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        inline constexpr float CosImpl( float x ) noexcept
        {
            constexpr double c1pio2 = 1 * M_PI_2;
            constexpr double c2pio2 = 2 * M_PI_2;
            constexpr double c3pio2 = 3 * M_PI_2;
            constexpr double c4pio2 = 4 * M_PI_2;

            auto hx = std::bit_cast<Int32>( x );
            auto ix = hx & 0x7fffffff;

            if ( ix <= 0x3f490fda )
            {		
                // |x| ~<= pi/4
                // |x| < 2**-12 
                if ( ix < 0x39800000 )
                {
                    if ( ( (int)x ) == 0 )
                    {
                        return 1.0;	
                    }
                }
                return CosCoreF( x );
            }
            if ( ix <= 0x407b53d1 )
            {		
                // |x| ~<= 5*pi/4 
                if ( ix <= 0x4016cbe3 )
                {	
                    // |x|  ~> 3*pi/4 
                    if ( hx > 0 )
                        return SinCoreF( c1pio2 - x );
                    else
                        return SinCoreF( x + c1pio2 );
                }
                else
                    return -CosCoreF( x + ( hx > 0 ? -c2pio2 : c2pio2 ) );
            }
            if ( ix <= 0x40e231d5 )
            {		
                // |x| ~<= 9*pi/4 
                if ( ix <= 0x40afeddf )
                {	
                    // |x|  ~> 7*pi/4 
                    if ( hx > 0 )
                        return SinCoreF( x - c3pio2 );
                    else
                        return SinCoreF( -c3pio2 - x );
                }
                else
                    return CosCoreF( x + ( hx > 0 ? -c4pio2 : c4pio2 ) );
            }
            else if ( ix >= 0x7f800000 ) 
            { 
                // cos(Inf or NaN) is NaN 
                return x - x;
            }
            else
            {
                // general argument reduction needed 
                double y;
                auto n = RemPIo2( x, &y );
                switch ( n & 3 )
                {
                    case 0: 
                        return SinCoreF( y );
                    case 1: 
                        return SinCoreF( -y );
                    case 2: 
                        return -SinCoreF( y );
                    default:
                        return SinCoreF( y );
                }
            }
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        inline constexpr double ACosImpl( double x ) noexcept
        {
            constexpr double one = 1.00000000000000000000e+00;
            constexpr double pi = 3.14159265358979311600e+00;
            constexpr double pio2_hi = 1.57079632679489655800e+00;
            
            constexpr double pio2_lo = 6.12323399573676603587e-17;
            
            constexpr double pS0 = 1.66666666666666657415e-01;
            constexpr double pS1 = -3.25565818622400915405e-01;
            constexpr double pS2 = 2.01212532134862925881e-01;
            constexpr double pS3 = -4.00555345006794114027e-02;
            constexpr double pS4 = 7.91534994289814532176e-04;
            constexpr double pS5 = 3.47933107596021167570e-05;
            constexpr double qS1 = -2.40339491173441421878e+00;
            constexpr double qS2 = 2.02094576023350569471e+00;
            constexpr double qS3 = -6.88283971605453293030e-01;
            constexpr double qS4 = 7.70381505559019352791e-02;

            double z, p, q, r, w, s, c, df;
            Int32 hx = GetHigh32Bits<Int32>( x );
            Int32 ix = hx & 0x7fffffff;
            if ( ix >= 0x3ff00000 )
            {	
                // |x| >= 1 
                UInt32 lx = GetLow32Bits<UInt32>( x );
                if ( ( ( ix - 0x3ff00000 ) | lx ) == 0 )
                {	
                    // |x|==1
                    if ( hx > 0 )
                    {
                        // acos(1) = 0  
                        return 0.0;
                    }
                    else
                    {
                        // acos(-1)= pi 
                        return pi + 2.0 * pio2_lo;
                    }
                }
                // acos(|x|>1) is NaN 
                return  ( x - x ) / ( x - x );
            }
            if ( ix < 0x3fe00000 )
            {	
                // |x| < 0.5 
                if ( ix <= 0x3c600000 )
                {
                    // if|x|<2**-57
                    return pio2_hi + pio2_lo;
                }
                z = x * x;
                p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z * ( pS4 + z * pS5 ) ) ) ) );
                q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
                r = p / q;
                return pio2_hi - ( x - ( pio2_lo - x * r ) );
            }
            else  if ( hx < 0 )
            {		
                // x < -0.5 
                z = ( one + x ) * 0.5;
                p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z * ( pS4 + z * pS5 ) ) ) ) );
                q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
                s = Sqrt( z );
                r = p / q;
                w = r * s - pio2_lo;
                return pi - 2.0 * ( s + w );
            }
            else
            {			
                // x > 0.5 
                z = ( one - x ) * 0.5;
                s = Sqrt( z );
                df = std::bit_cast<double>( std::bit_cast<UInt64>( s ) & 0xFFFFFFFF00000000 );
                
                c = ( z - df * df ) / ( s + df );
                p = z * ( pS0 + z * ( pS1 + z * ( pS2 + z * ( pS3 + z * ( pS4 + z * pS5 ) ) ) ) );
                q = one + z * ( qS1 + z * ( qS2 + z * ( qS3 + z * qS4 ) ) );
                r = p / q;
                w = r * s + c;
                return 2.0 * ( df + w );
            }
        }


        /* e_acosf.c -- float version of e_acos.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         */

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        inline constexpr float ACosImpl( float x ) noexcept
        {
            
            constexpr float one = 1.0000000000e+00f;
            constexpr float pi = 3.1415925026e+00f;
            constexpr float pio2_hi = 1.5707962513e+00f;
            
            constexpr float pio2_lo = 7.5497894159e-08f;
            
            constexpr float pS0 = 1.6666586697e-01f;
            constexpr float pS1 = -4.2743422091e-02f;
            constexpr float pS2 = -8.6563630030e-03f;
            constexpr float qS1 = -7.0662963390e-01f;


            float z, p, q, r, w, s, c, df;
            Int32 hx = std::bit_cast<Int32>( x );
            Int32 ix = hx & 0x7fffffff;
            if ( ix >= 0x3f800000 )
            {		
                // |x| >= 1 
                if ( ix == 0x3f800000 )
                {	
                    // |x| == 1 
                    if ( hx > 0 )
                    {
                        // acos(1) = 0 
                        return 0.0;	
                    }
                    else
                    {
                        // acos(-1)= pi 
                        return pi + (float)2.0 * pio2_lo;
                    }
                }
                // acos(|x|>1) is NaN 
                return ( x - x ) / ( x - x );
            }
            if ( ix < 0x3f000000 )
            {	
                // |x| < 0.5 
                if ( ix <= 0x32800000 )
                {
                    // if|x|<2**-26
                    return pio2_hi + pio2_lo;
                }
                z = x * x;
                p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
                q = one + z * qS1;
                r = p / q;
                return pio2_hi - ( x - ( pio2_lo - x * r ) );
            }
            else  if ( hx < 0 )
            {		
                // x < -0.5 
                z = ( one + x ) * 0.5f;
                p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
                q = one + z * qS1;
                s = Sqrt( z );
                r = p / q;
                w = r * s - pio2_lo;
                return pi - 2.0f * ( s + w );
            }
            else
            {			
                // x > 0.5 
                int32_t idf;
                z = ( one - x ) * (float)0.5;
                s = Sqrt( z );
                df = s;
                
                idf = std::bit_cast<Int32>( df );
                df = std::bit_cast<float>( idf & 0xfffff000 );
                c = ( z - df * df ) / ( s + df );
                p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
                q = one + z * qS1;
                r = p / q;
                w = r * s + c;
                return 2.0f * ( df + w );
            }
        }


        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        
        inline constexpr double TanImpl( double x ) noexcept
        {
            // High word of x. 
            auto ix = GetHigh32Bits<Int32>( x );

            // |x| ~< pi/4 
            ix &= 0x7fffffff;
            if ( ix <= 0x3fe921fb )
            {
                // x < 2**-27 
                if ( ix < 0x3e400000 )
                { 
                    if ( (int)x == 0 ) 
                    { 
                        return x;
                    }
                }
                return TanCore( x );
            }
            else if ( ix >= 0x7ff00000 )
            {
                // tan(Inf or NaN) is NaN 
                return x - x; // NaN 
            }
            else
            {
                // argument reduction needed 
                double y[2];
                auto n = RemPIo2( x, y );
                return TanCore( y[0], y[1], 1 - ( ( n & 1 ) << 1 ) ); //  1 -- n even -1 -- n odd 
            }
        }

        inline constexpr float TanImpl( float x ) noexcept
        {
            
            constexpr double t1pio2 = 1 * M_PI_2;
            constexpr double t2pio2 = 2 * M_PI_2;
            constexpr double t3pio2 = 3 * M_PI_2;
            constexpr double t4pio2 = 4 * M_PI_2;

            auto hx = std::bit_cast<Int32>( x );
            
            Int32 ix = hx & 0x7fffffff;

            if ( ix <= 0x3f490fda )
            {
                // |x| ~<= pi/4 
                if ( ix < 0x39800000 )
                {
                    // |x| < 2**-12 
                    if ( ( (int)x ) == 0 )
                    {
                        // x with inexact if x != 0 
                        return x;
                    }
                }
                return TanCoreF( x );
            }
            if ( ix <= 0x407b53d1 )
            {		
                // |x| ~<= 5*pi/4 
                if ( ix <= 0x4016cbe3 )
                {
                    // |x| ~<= 3pi/4 
                    return TanCoreF<true>( x + ( hx > 0 ? -t1pio2 : t1pio2 ) );
                }
                else
                {
                    return TanCoreF( x + ( hx > 0 ? -t2pio2 : t2pio2 ) );
                }
            }
            if ( ix <= 0x40e231d5 )
            {		
                // |x| ~<= 9*pi/4 
                if ( ix <= 0x40afeddf )
                {
                    // |x| ~<= 7*pi/4 
                    return TanCoreF<true>( x + ( hx > 0 ? -t3pio2 : t3pio2 ) );
                }
                else
                {
                    return TanCoreF( x + ( hx > 0 ? -t4pio2 : t4pio2 ) );
                }
            }
            else if ( ix >= 0x7f800000 )
            {
                // tan(Inf or NaN) is NaN 
                return x - x;
            }
            else
            {
                double y;
                // general argument reduction needed 
                auto n = RemPIo2( x, &y );
                // integer parameter: 1 -- n even; -1 -- n odd 
                if ( ( 1 - ( ( n & 1 ) << 1 ) ) == 1 )
                {
                    return TanCoreF( y );
                }
                else
                {
                    return TanCoreF<true>( y );
                }
            }
        }

        inline constexpr double ATanImpl( double x ) noexcept
        {
            constexpr double atanhi0 = 4.63647609000806093515e-01;
            constexpr double atanhi1 = 7.85398163397448278999e-01;
            constexpr double atanhi2 = 9.82793723247329054082e-01;
            constexpr double atanhi3 = 1.57079632679489655800e+00;
            

            constexpr double atanlo0 = 2.26987774529616870924e-17;
            constexpr double atanlo1 = 3.06161699786838301793e-17;
            constexpr double atanlo2 = 1.39033110312309984516e-17;
            constexpr double atanlo3 = 6.12323399573676603587e-17;

            
            constexpr double aT0 = 3.33333333333329318027e-01;
            constexpr double aT1 = -1.99999999998764832476e-01;
            constexpr double aT2 = 1.42857142725034663711e-01;
            constexpr double aT3 = -1.11111104054623557880e-01;
            constexpr double aT4 = 9.09088713343650656196e-02;
            constexpr double aT5 = -7.69187620504482999495e-02;
            constexpr double aT6 = 6.66107313738753120669e-02;
            constexpr double aT7 = -5.83357013379057348645e-02;
            constexpr double aT8 = 4.97687799461593236017e-02;
            constexpr double aT9 = -3.65315727442169155270e-02;
            constexpr double aT10 = 1.62858201153657823623e-02;
            
            constexpr double one = 1.0;
            constexpr double huge = 1.0e300;

            double w, s1, s2, z;

            Int32 hx = GetHigh32Bits<Int32>( x );
            Int32 ix = hx & 0x7fffffff;
            if ( ix >= 0x44100000 )
            {	
                // if |x| >= 2^66 
                UInt32 low = GetLow32Bits<UInt32>( x );
                 
                if ( ix > 0x7ff00000 || ( ix == 0x7ff00000 && ( low != 0 ) ) )
                {
                    // NaN 
                    return x + x;
                }
                if ( hx > 0 )
                {
                    return  atanhi3 + atanlo3;
                }
                else
                {
                    return -atanhi3 - atanlo3;
                }
            } 
            if ( ix < 0x3fdc0000 )
            {	
                // |x| < 0.4375 
                if ( ix < 0x3e400000 )
                {	
                    // |x| < 2^-27 
                    if ( huge + x > one )
                    {
                        // raise inexact 
                        return x;
                    }
                }

                // end of argument reduction 
                z = x * x;
                w = z * z;
                // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                s1 = z * ( aT0 + w * ( aT2 + w * ( aT4 + w * ( aT6 + w * ( aT8 + w * aT10 ) ) ) ) );
                s2 = w * ( aT1 + w * ( aT3 + w * ( aT5 + w * ( aT7 + w * aT9 ) ) ) );

                return x - x * ( s1 + s2 );
            }
            else
            {
                x = Abs( x );
                if ( ix < 0x3ff30000 )
                {		
                    // |x| < 1.1875 
                    if ( ix < 0x3fe60000 )
                    {	
                        // 7/16 <=|x|<11/16 
                        x = ( 2.0 * x - one ) / ( 2.0 + x );

                        // end of argument reduction 
                        z = x * x;
                        w = z * z;
                        // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                        s1 = z * ( aT0 + w * ( aT2 + w * ( aT4 + w * ( aT6 + w * ( aT8 + w * aT10 ) ) ) ) );
                        s2 = w * ( aT1 + w * ( aT3 + w * ( aT5 + w * ( aT7 + w * aT9 ) ) ) );

                        z = atanhi0 - ( ( x * ( s1 + s2 ) - atanlo0 ) - x );
                    }
                    else
                    {	
                        // 11/16<=|x|< 19/16 
                        x = ( x - one ) / ( x + one );

                        // end of argument reduction 
                        z = x * x;
                        w = z * z;
                        // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                        s1 = z * ( aT0 + w * ( aT2 + w * ( aT4 + w * ( aT6 + w * ( aT8 + w * aT10 ) ) ) ) );
                        s2 = w * ( aT1 + w * ( aT3 + w * ( aT5 + w * ( aT7 + w * aT9 ) ) ) );

                        z = atanhi1 - ( ( x * ( s1 + s2 ) - atanlo1 ) - x );

                    }
                }
                else
                {
                    if ( ix < 0x40038000 )
                    {	
                        // |x| < 2.4375 
                        x = ( x - 1.5 ) / ( one + 1.5 * x );

                        // end of argument reduction 
                        z = x * x;
                        w = z * z;
                        // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                        s1 = z * ( aT0 + w * ( aT2 + w * ( aT4 + w * ( aT6 + w * ( aT8 + w * aT10 ) ) ) ) );
                        s2 = w * ( aT1 + w * ( aT3 + w * ( aT5 + w * ( aT7 + w * aT9 ) ) ) );

                        z = atanhi2 - ( ( x * ( s1 + s2 ) - atanlo2 ) - x );
                    }
                    else
                    {	
                        // 2.4375 <= |x| < 2^66 
                        x = -1.0 / x;

                        // end of argument reduction 
                        z = x * x;
                        w = z * z;
                        // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                        s1 = z * ( aT0 + w * ( aT2 + w * ( aT4 + w * ( aT6 + w * ( aT8 + w * aT10 ) ) ) ) );
                        s2 = w * ( aT1 + w * ( aT3 + w * ( aT5 + w * ( aT7 + w * aT9 ) ) ) );

                        z = atanhi3 - ( ( x * ( s1 + s2 ) - atanlo3 ) - x );

                    }
                }

                return ( hx < 0 ) ? -z : z;

            }
            
        }

        inline constexpr float ATanImpl( float x ) noexcept
        {
            constexpr float atanhi0 = 4.6364760399e-01f;
            constexpr float atanhi1 = 7.8539812565e-01f;
            constexpr float atanhi2 = 9.8279368877e-01f;
            constexpr float atanhi3 = 1.5707962513e+00f;

            constexpr float atanlo0 = 5.0121582440e-09f;
            constexpr float atanlo1 = 3.7748947079e-08f;
            constexpr float atanlo2 = 3.4473217170e-08f;
            constexpr float atanlo3 = 7.5497894159e-08f;

            
            constexpr float aT0 = 3.3333328366e-01f;
            constexpr float aT1 = -1.9999158382e-01f;
            constexpr float aT2 = 1.4253635705e-01f;
            constexpr float aT3 = -1.0648017377e-01f;
            constexpr float aT4 = 6.1687607318e-02f;

            constexpr float one = 1.0f;
            constexpr float huge = 1.0e30f;


            float w, s1, s2, z;

            Int32 hx = std::bit_cast<Int32>( x );
            Int32 ix = hx & 0x7fffffff;
            if ( ix >= 0x4c800000 )
            {	
                // if |x| >= 2**26 
                if ( ix > 0x7f800000 )
                {
                    // NaN 
                    return x + x;
                }
                if ( hx > 0 )
                {
                    return atanhi3 + atanlo3;
                }
                else
                {
                    return -atanhi3 - atanlo3;
                }
            } 
            if ( ix < 0x3ee00000 )
            {	
                // |x| < 0.4375 
                if ( ix < 0x39800000 )
                {	
                    // |x| < 2**-12 
                    if ( huge + x > one )
                    {
                        // raise inexact 
                        return x;
                    }
                }

                // end of argument reduction 
                z = x * x;
                w = z * z;
                // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                s1 = z * ( aT0 + w * ( aT2 + w * aT4 ) );
                s2 = w * ( aT1 + w * aT3 );
                return x - x * ( s1 + s2 );
            }
            else
            {
                x = Abs( x );
                if ( ix < 0x3f980000 )
                {
                    // |x| < 1.1875 
                    if ( ix < 0x3f300000 )
                    {	
                        // 7/16 <=|x|<11/16 
                        x = ( 2.0f * x - one ) / ( 2.0f + x );
                        // end of argument reduction 
                        z = x * x;
                        w = z * z;
                        // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                        s1 = z * ( aT0 + w * ( aT2 + w * aT4 ) );
                        s2 = w * ( aT1 + w * aT3 );

                        z = atanhi0 - ( ( x * ( s1 + s2 ) - atanlo0 ) - x );
                    }
                    else
                    {			
                        // 11/16<=|x|< 19/16 
                        x = ( x - one ) / ( x + one );
                        // end of argument reduction 
                        z = x * x;
                        w = z * z;
                        // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                        s1 = z * ( aT0 + w * ( aT2 + w * aT4 ) );
                        s2 = w * ( aT1 + w * aT3 );

                        z = atanhi1 - ( ( x * ( s1 + s2 ) - atanlo1 ) - x );
                    }
                }
                else
                {
                    if ( ix < 0x401c0000 )
                    {	
                        // |x| < 2.4375 
                        x = ( x - 1.5f ) / ( one + 1.5f * x );
                        // end of argument reduction 
                        z = x * x;
                        w = z * z;
                        // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                        s1 = z * ( aT0 + w * ( aT2 + w * aT4 ) );
                        s2 = w * ( aT1 + w * aT3 );

                        z = atanhi2 - ( ( x * ( s1 + s2 ) - atanlo2 ) - x );
                    }
                    else
                    {			
                        // 2.4375 <= |x| < 2**26 
                        x = -1.0f / x;
                        // end of argument reduction 
                        z = x * x;
                        w = z * z;
                        // break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly 
                        s1 = z * ( aT0 + w * ( aT2 + w * aT4 ) );
                        s2 = w * ( aT1 + w * aT3 );

                        z = atanhi3 - ( ( x * ( s1 + s2 ) - atanlo3 ) - x );
                    }
                }
                return ( hx < 0 ) ? -z : z;
            }
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         *
         */
        inline constexpr double ATan2Impl( double y, double x ) noexcept
        {
            constexpr double tiny = 1.0e-300;
            
            constexpr double zero = 0.0;
            constexpr double pi_o_4 = 7.8539816339744827900E-01;
            constexpr double pi_o_2 = 1.5707963267948965580E+00;
            constexpr double pi = 3.1415926535897931160E+00;
            constexpr double pi_lo = 1.2246467991473531772E-16;

            Int32 hx = GetHigh32Bits<Int32>( x );
            UInt32 lx = GetLow32Bits<UInt32>( x );
            Int32 ix = hx & 0x7fffffff;

            Int32 hy = GetHigh32Bits<Int32>( y );
            UInt32 ly = GetLow32Bits<UInt32>( y );
            Int32 iy = hy & 0x7fffffff;

            // Are x or y NaN ?
            if ( ( ( ix | ( ( lx | -static_cast<Int32>(lx) ) >> 31 ) ) > 0x7ff00000 ) || ( ( iy | ( ( ly | -static_cast<Int32>( ly ) ) >> 31 ) ) > 0x7ff00000 ) )
            {
                return x + y;
            }
            if ( hx == 0x3ff00000 && lx == 0 )
            {
                // x=1.0 
                return ATan( y );
            }
            // 2*sign(x)+sign(y) 
            Int32 m = ( ( hy >> 31 ) & 1 ) | ( ( hx >> 30 ) & 2 );

            // If y = 0 
            if ( ( iy | ly ) == 0 )
            {
                switch ( m )
                {
                    case 0:
                    case 1: 
                        // atan(+-0,+anything)=+-0 
                        return y; 	
                    case 2: 
                        // atan(+0,-anything) = pi 
                        return  pi + tiny;
                    case 3: 
                        // atan(-0,-anything) =-pi 
                        return -pi - tiny;
                }
            }
            // when x = 0 
            if ( ( ix | lx ) == 0 )
            {
                return ( hy < 0 ) ? -pi_o_2 - tiny : pi_o_2 + tiny;
            }

            // when x is INF 
            if ( ix == 0x7ff00000 )
            {
                if ( iy == 0x7ff00000 )
                {
                    switch ( m )
                    {
                        case 0: 
                            return  pi_o_4 + tiny;/* atan(+INF,+INF) */
                        case 1: 
                            return -pi_o_4 - tiny;/* atan(-INF,+INF) */
                        case 2: 
                            return  3.0 * pi_o_4 + tiny;/*atan(+INF,-INF)*/
                        case 3: 
                            return -3.0 * pi_o_4 - tiny;/*atan(-INF,-INF)*/
                    }
                }
                else
                {
                    switch ( m )
                    {
                        case 0: 
                            return  zero;	/* atan(+...,+INF) */
                        case 1: 
                            return -zero;	/* atan(-...,+INF) */
                        case 2: 
                            return  pi + tiny;	/* atan(+...,-INF) */
                        case 3: 
                            return -pi - tiny;	/* atan(-...,-INF) */
                    }
                }
            }
            // when y is INF 
            if ( iy == 0x7ff00000 )
            {
                return ( hy < 0 ) ? -pi_o_2 - tiny : pi_o_2 + tiny;
            }

            // compute y/x 
            Int32 k = ( iy - ix ) >> 20;
            double z;
            if ( k > 60 )
            {		 	
                // |y/x| >  2**60 
                z = pi_o_2 + 0.5 * pi_lo;
                m &= 1;
            }
            else if ( hx < 0 && k < -60 )
            {
                // 0 > |y|/x > -2**-60 
                z = 0.0;
            }
            else
            {
                // safe to do y/x 
                z = ATan( Abs( y / x ) );
            }
            switch ( m )
            {
                case 0: 
                    // atan(+,+) 
                    return z;
                case 1: 
                    // atan(-,+) 
                    return -z;	
                case 2: 
                    // atan(+,-) 
                    return  pi - ( z - pi_lo );
                default: 
                    // case 3: atan(-,-) 
                    return  ( z - pi_lo ) - pi;
            }
        }

        /* e_atan2f.c -- float version of e_atan2.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         */

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        inline constexpr float ATan2Impl( float y, float x ) noexcept
        {
            constexpr float tiny = 1.0e-30f;
            constexpr float zero = 0.0f;
            constexpr float pi_o_4 = 7.8539818525e-01f;
            constexpr float pi_o_2 = 1.5707963705e+00f;
            constexpr float pi = 3.1415927410e+00f;
            constexpr float pi_lo = -8.7422776573e-08f;

            auto hx = std::bit_cast<Int32>( x );
            Int32 ix = hx & 0x7fffffff;
            auto hy = std::bit_cast<Int32>( y );
            Int32 iy = hy & 0x7fffffff;
            // Are x or y NaN?
            if ( ( ix > 0x7f800000 ) || ( iy > 0x7f800000 ) )
            {
                return x + y;
            }
            if ( hx == 0x3f800000 )
            {
                // x=1.0 
                return ATan( y );
            }
            // 2*sign(x)+sign(y) 
            Int32 m = ( ( hy >> 31 ) & 1 ) | ( ( hx >> 30 ) & 2 );

            // when y = 0 
            if ( iy == 0 )
            {
                switch ( m )
                {
                    case 0:
                    case 1: 
                        // atan(+-0,+anything)=+-0 
                        return y;
                    case 2: 
                        // atan(+0,-anything) = pi 
                        return  pi + tiny;
                    case 3: 
                        // atan(-0,-anything) =-pi 
                        return -pi - tiny;
                }
            }
            // when x = 0 
            if ( ix == 0 )
            {
                return ( hy < 0 ) ? -pi_o_2 - tiny : pi_o_2 + tiny;
            }

            // when x is INF 
            if ( ix == 0x7f800000 )
            {
                if ( iy == 0x7f800000 )
                {
                    switch ( m )
                    {
                        case 0: 
                            // atan(+INF,+INF) 
                            return  pi_o_4 + tiny;
                        case 1: 
                            // atan(-INF,+INF) 
                            return -pi_o_4 - tiny;
                        case 2: 
                            // atan(+INF,-INF)
                            return  (float)3.0 * pi_o_4 + tiny;
                        case 3: 
                            // atan(-INF,-INF)
                            return (float)-3.0 * pi_o_4 - tiny;
                    }
                }
                else
                {
                    switch ( m )
                    {
                        case 0: 
                            // atan(+...,+INF) 
                            return  zero;
                        case 1: 
                            // atan(-...,+INF) 
                            return -zero;
                        case 2: 
                            // atan(+...,-INF) 
                            return  pi + tiny;
                        case 3: 
                            // atan(-...,-INF) 
                            return -pi - tiny;
                    }
                }
            }
            // when y is INF 
            if ( iy == 0x7f800000 )
            {
                return ( hy < 0 ) ? -pi_o_2 - tiny : pi_o_2 + tiny;
            }

            // compute y/x 
            Int32 k = ( iy - ix ) >> 23;
            float z;
            if ( k > 26 )
            {			
                // |y/x| >  2**26 
                z = pi_o_2 + 0.5f * pi_lo;
                m &= 1;
            }
            else if ( k < -26 && hx < 0 )
            {
                // 0 > |y|/x > -2**-26 
                z = 0.0;
            }
            else
            {
                // safe to do y/x 
                z = ATan( Abs( y / x ) );
            }
            switch ( m )
            {
                case 0: 
                    // atan(+,+)
                    return z;	
                case 1: 
                    //  atan(-,+) 
                    return -z;
                case 2: 
                    // atan(+,-) 
                    return  pi - ( z - pi_lo );
                default: 
                    // case 3: atan(-,-) 
                    return  ( z - pi_lo ) - pi;
            }
        }

        template<typename T>
            requires IsFloatingPoint<T>
        constexpr T LerpImpl( T a, T b, T t ) noexcept
        {
            if ( ( a <= 0 && b >= 0 ) || ( a >= 0 && b <= 0 ) )
            {
                return t * b + ( 1 - t ) * a;
            }
            if ( t == 1 )
            {
                return b;
            }
            T x = a + t * ( b - a );
            if ( ( t > 1 ) == ( b > a ) )
            {
                return b < x ? x : b;
            }
            else
            {
                return x < b ? x : b;
            }
        }

    }

    /// <summary>
    /// <para>
    /// Return the largest floating point number y of the same type 
    /// as x such that y < x. If no such y exists, e.g. if x is -Inf or NaN, then return x.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and performs 1839.04 % better
    /// than <c>std::nextafter( x, -std::numeric_limits&lt;double&gt;::infinity( ) )</c>
    /// for double precision floating point values, and similarly 370.61 % better for
    /// single precision floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The largest floating point number y of the same type 
    /// as x such that y < x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextDown( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        using FloatingPointType = Math::Internal::FloatingPoint<FloatType>;
        using UIntType = FloatingPointType::UIntType;
        constexpr UIntType SignMask = FloatingPointType::SignMask;
        constexpr UIntType FractionMask = FloatingPointType::FractionMask;
        constexpr UIntType ExponentMask = FloatingPointType::ExponentMask;
        constexpr UIntType ExponentAndFractionMask = ExponentMask | FractionMask;
        constexpr UIntType MinusEpsilon = std::bit_cast<UIntType>( -std::numeric_limits<FloatType>::epsilon( ) );
        constexpr UIntType Highest = std::bit_cast<UIntType>( std::numeric_limits<FloatType>::max( ) );

        UIntType bits = std::bit_cast<UIntType>( x );

        
        if ( bits & SignMask )
        {
            if ( ( bits & ExponentMask ) < ExponentMask )
            {
                bits += 1;
            }
        }
        else
        {
            if ( ( bits & ExponentMask ) < ExponentMask )
            {
                if ( bits & ExponentAndFractionMask )
                {
                    bits -= 1;
                }
                else
                {
                    // 0
                    bits = SignMask + 1;
                }
            }
            else
            {
                // inf or NaN
                if ( ( bits & FractionMask ) == 0 )
                {
                    // Inf
                    bits = Highest;
                }
            }
        }
        return std::bit_cast<FloatType>( bits );
    }

    /// <summary>
    /// <para>
    /// Return the smallest floating point number y of the same 
    /// type as x such that x < y. If no such y exists, e.g. if x is 
    /// Inf or NaN, then return x.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and performs 2783.78 % better
    /// than <c>std::nextafter( x, std::numeric_limits&lt;double&gt;::infinity( ) )</c>
    /// for double precision floating point values, and similarly 586.95 % better for
    /// single precision floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The smallest floating point number y of the same 
    /// type as x such that x < y.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextUp( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        using FloatingPointType = Math::Internal::FloatingPoint<FloatType>;
        using UIntType = FloatingPointType::UIntType;
        constexpr UIntType SignMask = FloatingPointType::SignMask;
        constexpr UIntType FractionMask = FloatingPointType::FractionMask;
        constexpr UIntType ExponentMask = FloatingPointType::ExponentMask;
        constexpr UIntType ExponentAndFractionMask = ExponentMask | FractionMask;
        constexpr UIntType Epsilon = std::bit_cast<UIntType>( std::numeric_limits<FloatType>::epsilon( ) );
        constexpr UIntType Lowest = std::bit_cast<UIntType>( std::numeric_limits<FloatType>::lowest( ) );

        UIntType bits = std::bit_cast<UIntType>( x );
        if ( bits & SignMask )
        {
            if ( ( bits & ExponentMask ) < ExponentMask )
            {
                if ( bits & ExponentAndFractionMask )
                {
                    bits -= 1;
                }
                else
                {
                    // -0
                    bits = 1;
                }
            }
            else
            {
                // -inf or NaN
                if ( (bits & FractionMask) == 0 )
                {
                    // -Inf
                    bits = Lowest;
                }
            }
        }
        else
        {
            if ( ( bits & ExponentMask ) < ExponentMask )
            {
                bits += 1;
            }
        }
        return std::bit_cast<FloatType>( bits );
    }

    /// <summary>
    /// IsNaN for integer types, always returns false.
    /// </summary>
    /// <typeparam name="T">
    /// Any integer type
    /// </typeparam>
    /// <param name="val">
    /// Integer value.
    /// </param>
    /// <returns>
    /// false
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsNaN( T val ) noexcept 
    { 
        return false;
    }

    /// <summary>
    /// <para>
    /// Determines if the given floating point number, val, 
    /// is a not-a-number (NaN) value.
    /// </para>
    /// <para>
    /// Runtime performance is equivalent to std::isnan,
    /// but this implementation can be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// true if val is a not-a-number (NaN) value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsNaN( T val ) noexcept
    {
        return Internal::IsNaNImpl<T>( val );
    }

    /// <summary>
    /// Integers cannot represent infinite, so this function
    /// always returns false.
    /// </summary>
    /// <typeparam name="T">
    /// Any integer type.
    /// </typeparam>
    /// <param name="val">
    /// An integer value.
    /// </param>
    /// <returns>
    /// false
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsInf( T val ) noexcept 
    { 
        return false;
    }
    /// <summary>
    /// <para>
    /// Determines if the given floating point number val 
    /// is positive or negative infinity. 
    /// </para>
    /// <para>
    /// Runtime performance is equivalent to std::isinf,
    /// but this implementation can be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// true if val has an infinite value, otherwise false.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsInf( T val ) noexcept
    {
        return Internal::IsInfImpl<std::remove_cvref_t<T>>( val );
    }

    /// <summary>
    /// <para>
    /// Computes the absolute value of a signed integer number. The behavior 
    /// is undefined if the result cannot be represented by the return type.
    /// </para>
    /// <para>
    /// In 2's complement systems, the absolute value of the most-negative value 
    /// is out of range, e.g. for 32-bit 2's complement type int, INT_MIN is -2147483648, 
    /// but the would-be result 2147483648 is greater than INT_MAX, which is 2147483647.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// Any signed integer type.
    /// </typeparam>
    /// <param name="val">
    /// A signed integer value.
    /// </param>
    /// <returns>
    /// The absolute value of val.
    /// </returns>
    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept 
    { 
        if ( std::is_constant_evaluated( ) )
        {
            return val >= 0 ? val : -val;
        }
        else
        {
            return std::abs( val );
        }
    }
    static_assert( Abs( -1 ) == 1 );

    /// <summary>
    /// The absolute value of any unsigned integer
    /// is the same as its value.
    /// </summary>
    /// <typeparam name="T">
    /// Any unsigned integer type.
    /// </typeparam>
    /// <param name="val">
    /// An unsigned integer value.
    /// </param>
    /// <returns>
    /// val without any modification.
    /// </returns>
    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept
    {
        return val;
    }

    /// <summary>
    /// <para>
    /// Computes the absolute value of a floating point value.
    /// </para>
    /// <para>
    /// Runtime performance is equivalent to std::fabs and std::fabsf
    /// since those functions are used unless the function is 
    /// constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The absolute value of val.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T> 
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Internal::AbsImpl( val );
        }
        else
        {
            using FloatT = std::remove_cvref_t<T>;
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return std::fabsf( val );
            }
            else
            {
                return std::fabs( val );
            }
        }
    }
    static_assert( Abs( -1.0 ) == 1.0 );

    /// <summary>
    /// Determines if the given signed integer value is negative.
    /// </summary>
    /// <typeparam name="T">
    /// Any signed integer type.
    /// </typeparam>
    /// <param name="val">
    /// A signed integer value.
    /// </param>
    /// <returns>
    /// returns true if the value is signed, otherwise false.
    /// </returns>
    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept 
    { 
        using IntT = std::remove_cvref_t<T>;
        using UIntT = std::make_unsigned_t<IntT>;
        static constexpr size_t ByteCount = sizeof( IntT );
        static constexpr size_t ShiftCount = ( ( ByteCount - 1 ) * 8 ) + 7;
        static constexpr UIntT UnsignedSignMask = static_cast< UIntT >( 1 ) << ShiftCount;
        static constexpr IntT SignMask = std::bit_cast< IntT >( UnsignedSignMask );
        return (val & SignMask) != 0;
    }

    /// <summary>
    /// An Implementation of SignBit for unsigned integers
    /// that always returns false.
    /// </summary>
    /// <typeparam name="T">
    /// Any unsigned integer type.
    /// </typeparam>
    /// <param name="val">
    /// An unsigned integer value.
    /// </param>
    /// <returns>
    /// false
    /// </returns>
    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept
    {
        return false;
    }

    /// <summary>
    /// <para>
    /// Determines if the given floating point number is negative.
    /// </para>
    /// <para>
    /// Currently this implementation is 70 % faster than std::signbit,
    /// and it can also be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// true if val is less than 0.0.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool SignBit( T val ) noexcept
    {
        return Internal::SignBitImpl( val );
    }

    /// <summary>
    /// <para>
    /// Decomposes the given floating point value val into a normalized 
    /// fraction and an integral power of two.
    /// </para>
    /// <para>
    /// Currently this implementation is more than 6 times faster 
    /// than std::frexp.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// <para>
    /// A std::pair&lt;&gt;> with the normalized fraction
    /// stored in first and the exponent stored in second.
    /// </para>
    /// <para>
    /// If val is zero, both first and second are set to zero.
    /// </para>
    /// <para>
    /// If val is not zero, and no errors occur, the function returns a value,
    /// x, in the range( -1; -0.5], [ 0.5; 1 ) in first and stores an integer value in 
    /// second such that result.first*2^( result.second ) = val.
    /// </para>
    /// <para>
    /// If the value to be stored in result.second is outside the range of int, the behavior is unspecified.
    /// </para>
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::pair<std::remove_cvref_t<T>,int> FRExp( T val ) noexcept
    { 
        std::pair<std::remove_cvref_t<T>, int> result;
        result.first = Internal::FRExpImpl<std::remove_cvref_t<T>>( val, result.second );
        return result;
    }

    /// <summary>
    /// <para>
    /// Decomposes the given floating point value val into a normalized 
    /// fraction and an integral power of two.
    /// </para>
    /// <para>
    /// Currently this implementation is more than 6 times faster 
    /// than std::frexp.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <param name="exp">
    /// A pointer to an integer value to store the exponent to.
    /// </param>
    /// <returns>
    /// <para>
    /// If val is zero, returns zero and stores zero in *exp.
    /// </para>
    /// <para>
    /// If val is not zero, and no errors occur, the function returns a value,
    /// x, in the range( -1; -0.5], [ 0.5; 1 ) and stores an integer value in 
    /// *exp such that x*2^( *exp ) = val.
    /// </para>
    /// <para>
    /// If the value to be stored in *exp is outside the range of int, the behavior is unspecified.
    /// </para>
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int* exp ) noexcept
    { 
        return Internal::FRExpImpl<std::remove_cvref_t<T>>( val, *exp );
    }
    /// <summary>
    /// <para>
    /// Decomposes the given floating point value val into a normalized 
    /// fraction and an integral power of two.
    /// </para>
    /// <para>
    /// Currently this implementation is more than 6 times faster 
    /// than std::frexp.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <param name="exp">
    /// A reference to an integer value to store the exponent to.
    /// </param>
    /// <returns>
    /// <para>
    /// If val is zero, returns zero and stores zero in exp.
    /// </para>
    /// <para>
    /// If val is not zero, and no errors occur, the function returns a value,
    /// x, in the range( -1; -0.5], [ 0.5; 1 ) and stores an integer value in 
    /// exp such that x*2^( exp ) = val.
    /// </para>
    /// <para>
    /// If the value to be stored in exp is outside the range of int, the behavior is unspecified.
    /// </para>
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int& exp ) noexcept
    { 
        return Internal::FRExpImpl<std::remove_cvref_t<T>>( val, exp );
    }

    /// <summary>
    /// <para>
    /// Decomposes floating-point value val into its integral and 
    /// fractional parts, each with the same type and sign as val.
    /// </para>
    /// <para>
    /// Currently 37 % faster than std::modf for double precision
    /// floating point values, and 27 % faster for single precision
    /// floating point values.
    /// </para>
    /// <para>
    /// This implementation can also be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="ValueT">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// A std::pair&lt;ValueT,ValueT&gt; where first holds the integral part 
    /// of the result and second holds the fractional part.
    /// </returns>
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>> 
    constexpr inline std::pair<std::remove_cvref_t<ValueT>, std::remove_cvref_t<ValueT>> ModF( ValueT val ) noexcept
    {
        std::pair<std::remove_cvref_t<ValueT>, std::remove_cvref_t<ValueT>> result;
        result.second = Internal::ModFImpl( val, result.first );
        return result;
    }
    /// <summary>
    /// <para>
    /// Decomposes floating-point value val into its integral and 
    /// fractional parts, each with the same type and sign as val.
    /// </para>
    /// <para>
    /// Currently 37 % faster than std::modf for double precision
    /// floating point values, and 27 % faster for single precision
    /// floating point values.
    /// </para>
    /// <para>
    /// This implementation can also be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="ValueT">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <param name="integerPart">
    /// A pointer to a variable of the ValueT floating point type
    /// that receives the integral part of val.
    /// </param>
    /// <returns>
    /// The fractional part of val.
    /// </returns>
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT* integerPart ) noexcept
    {
        return Internal::ModFImpl( val, *integerPart );
    }
    
    /// <summary>
    /// <para>
    /// Decomposes floating-point value val into its integral and 
    /// fractional parts, each with the same type and sign as val.
    /// </para>
    /// <para>
    /// Currently 37 % faster than std::modf for double precision
    /// floating point values, and 27 % faster for single precision
    /// floating point values.
    /// </para>
    /// <para>
    /// This implementation can also be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="ValueT">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <param name="integerPart">
    /// A reference to a variable of the ValueT floating point type
    /// that receives the integral part of val.
    /// </param>
    /// <returns>
    /// The fractional part of val.
    /// </returns>
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT& integerPart ) noexcept
    {
        return Internal::ModFImpl( val, integerPart );
    }



#ifdef HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP
    /// <summary>
    /// Returns the smaller of the given values.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="first">
    /// The first floating point value.
    /// </param>
    /// <param name="second">
    /// The second floating point value.
    /// </param>
    /// <returns>
    /// Returns the smaller of <c>first</c> and <c>second</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            return std::min( first, second );
        }
        else
        {
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                FloatT result;
                _mm_store_ss( &result, _mm_min_ss( _mm_set_ss( first ), _mm_set_ss( second ) ) );
                return result;
            }
            else
            {
                FloatT result;
                _mm_store_sd( &result, _mm_min_sd( _mm_set_sd( first ), _mm_set_sd( second ) ) );
                return result;
            }
        }
    }
    /// <summary>
    /// Returns the smaller of the given values.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="first">
    /// The first integer value.
    /// </param>
    /// <param name="second">
    /// The second integer value.
    /// </param>
    /// <returns>
    /// Returns the smaller of <c>first</c> and <c>second</c>.
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept
    {
        return std::min( first, second );
    }
#else
    template<typename T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept
    {
        return std::min( first, second );
    }
#endif

#ifdef HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP
    /// <summary>
    /// Returns the larger of the given values.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="first">
    /// The first floating point value.
    /// </param>
    /// <param name="second">
    /// The second floating point value.
    /// </param>
    /// <returns>
    /// Returns the larger of <c>first</c> and <c>second</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            return std::max( first, second );
        }
        else
        {
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                FloatT result;
                _mm_store_ss( &result, _mm_max_ss( _mm_set_ss( first ), _mm_set_ss( second ) ) );
                return result;
            }
            else
            {
                FloatT result;
                _mm_store_sd( &result, _mm_max_sd( _mm_set_sd( first ), _mm_set_sd( second ) ) );
                return result;
            }
        }
    }
    /// <summary>
    /// Returns the larger of the given values.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="first">
    /// The first integer value.
    /// </param>
    /// <param name="second">
    /// The second integer value.
    /// </param>
    /// <returns>
    /// Returns the larger of <c>first</c> and <c>second</c>.
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept
    {
        return std::max( first, second );
    }
#else
    template<typename T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept
    {
        return std::max( first, second );
    }
#endif

    /// <summary>
    /// <para>
    /// Computes the nearest integer not greater in magnitude than value.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, for double precision 
    /// floating point values this function is close to 8 times faster than
    /// std::trunc, For single precision floating point values this function
    /// is 6 % faster than std::trunc.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// A floating point value with the nearest integer not 
    /// greater in magnitude than value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T value ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;

        if ( std::is_constant_evaluated( ) )
        {
            Internal::FloatingPoint<FloatT> tmp( value );
            return tmp.Trunc( );
        }
        else
        {
#ifdef HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC ) );
                return result;
            }
#else
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __truncf( value );
            }
            else
            {
                return __trunc( value );
            }
#endif
        }
    }

    /// <summary>
    /// Just returns value.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// An integer value.
    /// </param>
    /// <returns>
    /// value
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T value ) noexcept
    {
        return value;
    }


    /// <summary>
    /// <para>
    /// Computes the largest integer value not greater than value.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, this function is 15 % faster than
    /// std::floor for both single and double precision floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The largest integer value not greater than value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            Internal::FloatingPoint<FloatT> tmp( value );
            return tmp.Floor( );
        }
        else
        {
#ifdef HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC ) );
                return result;
            }
            /*
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_floor_pd( _mm_set_sd( value ) ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_floor_ps( _mm_set_ss( value ) ) );
                return result;
            }
            */
#else
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __floorf( value );
            }
            else
            {
                return __floor( value );
            }

#endif
        }
    }

    /// <summary>
    /// Just returns value.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// An integer value.
    /// </param>
    /// <returns>
    /// value
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept
    {
        return value;
    }


    /// <summary>
    /// <para>
    /// Computes the smallest integer value not less than value.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, this function is 15 % faster than
    /// std::ceil for both single and double precision floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The smallest integer value not less than value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            Internal::FloatingPoint<FloatT> tmp( value );
            return tmp.Ceil( );
        }
        else
        {
#ifdef HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC ) );
                return result;
            }
            /*
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_ceil_pd( _mm_set_sd( value ) ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_ceil_ps( _mm_set_ss( value ) ) );
                return result;
            }
            */
#else
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __ceilf( value );
            }
            else
            {
                return __ceil( value );
            }
#endif
        }
    }

    /// <summary>
    /// Just returns value.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// An integer value.
    /// </param>
    /// <returns>
    /// value
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept
    {
        return value;
    }


    
#ifdef HCCLIB_IMPLEMENTS_ROUND 
    /// <summary>
    /// <para>
    /// Computes the nearest integer to value, in floating-point format, 
    /// rounding halfway cases away from zero.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, for double precision 
    /// floating point values this function is more then 11 times faster than
    /// std::round, For single precision floating point values this function
    /// is 40 % faster than std::round.
    /// <para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The nearest integer to value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            Internal::FloatingPoint<FloatT> tmp( value );
            return tmp.Round( );
        }
        else
        {
#ifdef HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC ) );
                return result;
            }
#else
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __roundf( value );
            }
            else
            {
                return __round( value );
            }
#endif
        }
    }

    /// <summary>
    /// Just returns value.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// An integer value.
    /// </param>
    /// <returns>
    /// value
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept
    {
        return value;
    }
#else
    template<typename T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept
    {
        return std::round( value );
    }
#endif
    /// <summary>
    /// Clamp
    /// </summary>
#ifdef HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP
    /// <summary>
    /// <para>
    /// If the value is within [minimumValue, maximumValue], the function 
    /// returns value, otherwise returns the nearest boundary.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, this function is 7 % faster than
    /// std::clamp for both single and double precision floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// The value to clamp.
    /// </param>
    /// <param name="minimumValue">
    /// The lower boundary.
    /// </param>
    /// <param name="maximumValue">
    /// The upper boundary.
    /// </param>
    /// <returns>
    /// The value within [minimumValue, maximumValue], or the nearest boundary.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Clamp( T value, T minimumValue, T maximumValue ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            const FloatT tmp = value < minimumValue ? minimumValue : value;
            return tmp > maximumValue ? maximumValue : tmp;
        }
        else
        {
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                FloatT result;
                _mm_store_ss( &result, _mm_min_ss( _mm_max_ss( _mm_set_ss( value ), _mm_set_ss( minimumValue ) ), _mm_set_ss( maximumValue ) ) );
                return result;
            }
            else
            {
                FloatT result;
                _mm_store_sd( &result, _mm_min_sd( _mm_max_sd( _mm_set_sd( value ), _mm_set_sd( minimumValue ) ), _mm_set_sd( maximumValue ) ) );
                return result;
            }
        }
    }

    /// <summary>
    /// If the value is within [minimumValue, maximumValue], the function 
    /// returns value, otherwise returns the nearest boundary.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// The value to clamp.
    /// </param>
    /// <param name="minimumValue">
    /// The lower boundary.
    /// </param>
    /// <param name="maximumValue">
    /// The upper boundary.
    /// </param>
    /// <returns>
    /// The value within [minimumValue, maximumValue], or the nearest boundary.
    /// </returns>
    template<typename T>
        requires ( IsInteger<T> )
    constexpr inline std::remove_cvref_t<T> Clamp( T value, T minimumValue, T maximumValue ) noexcept
    {
        using IntT = std::remove_cvref_t<T>;
        const IntT tmp = value < minimumValue ? minimumValue : value;
        return tmp > maximumValue ? maximumValue : tmp;
    }
#else
    template<typename T>
    constexpr inline std::remove_cvref_t<T> Clamp( T value, T minimumValue, T maximumValue )
    {
        return std::clamp( value, minimumValue, maximumValue );
    }
#endif

    /// <summary>
    /// <para>
    /// Computes the linear interpolation between a and b, if the 
    /// parameter t is inside [​0​, 1), the linear extrapolation otherwise, 
    /// i.e. the result of a + t * ( b - a ) with accounting 
    /// for floating point calculation imprecision.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and
    /// improves runtime performance by 33 %.
    /// </para>
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <typeparam name="U"></typeparam>
    /// <param name="a">An arithmetic type.</param>
    /// <param name="b">An arithmetic type.</param>
    /// <param name="t">An arithmetic type.</param>
    /// <returns>
    /// The interpolated or extrapolated result. 
    /// </returns>
    template<typename T, typename U>
        requires ( ( IsInteger<T> || IsFloatingPoint<T> ) && ( IsInteger<U> || IsFloatingPoint<U> ) )
    constexpr inline std::conditional_t<IsFloatingPoint<T>, T, std::conditional_t<IsFloatingPoint<U>, U, T>> Lerp( T a, T b, U t ) noexcept
    {
        return Internal::LerpImpl( a, b, t );
    }

    /// <summary>
    /// <para>
    /// Composes a floating point value with the magnitude 
    /// of <c>magnitude</c> and the sign of <c>signValue</c>.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and
    /// improves runtime performance for double precision 
    /// floating point values by 490 %, and by 1.82 % for single 
    /// precision floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="magnitude">
    /// A floating point value.
    /// </param>
    /// <param name="signValue">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// A floating point value with the magnitude 
    /// of <c>magnitude</c> and the sign of <c>signValue</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> CopySign( T magnitude, T signValue ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        return Math::Internal::CopySignImpl<FloatT>( magnitude, signValue );
    }
    /// <summary>
    /// <para>
    /// Multiplies a double precision floating point value 
    /// <c>x</c> multplied by <c>FLT_RADIX</c> raised to power <c>n</c>.
    /// </para>
    /// <para>
    /// FLT_RADIX is the radix used by the representation 
    /// of the floating point types.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and
    /// improves runtime performance by 421 %.
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value. 
    /// </param>
    /// <param name="n">
    /// An integer.
    /// </param>
    /// <returns>
    /// <c>x</c> multiplied by <c>FLT_RADIX</c> raised to power <c>n</c>
    /// </returns>
    inline constexpr double ScaleByN( double x, int n ) noexcept
    {
        constexpr double two54 = 1.80143985094819840000e+16;
        constexpr double twom54 = 5.55111512312578270212e-17;
        constexpr double huge = 1.0e+300;
        constexpr double tiny = 1.0e-300;

        Int32 hx = static_cast<Int32>( std::bit_cast<Int64>( x ) >> 32 );
        Int32 lx = static_cast<Int32>( std::bit_cast<Int64>( x ) );

        // extract exponent 
        int32_t k = ( hx & 0x7ff00000 ) >> 20;
        if ( k == 0 )
        {
            // 0 or subnormal x 
            if ( ( lx | ( hx & 0x7fffffff ) ) == 0 )
            {
                // +-0 
                return x;
            }
            x *= two54;
            hx = GetHigh32Bits<Int32>( x );
            k = ( ( hx & 0x7ff00000 ) >> 20 ) - 54;
            if ( n < -50000 )
            {
                // underflow
                return tiny * x;
            }
        }
        if ( k == 0x7ff )
        {
            // NaN or Inf 
            return x + x;
        }
        k = k + n;
        if ( k > 0x7fe )
        {
            // overflow  
            return huge * CopySign( huge, x );
        }
        if ( k > 0 )
        {
            // normal result 
            x = SetHigh32Bits<Int32>( x, ( hx & 0x800fffff ) | ( k << 20 ) );
            return x;
        }
        if ( k <= -54 )
        {
            // in case integer overflow in n+k 
            if ( n > 50000 )
            {
                // overflow
                return huge * CopySign( huge, x );
            }
            else
            {
                // underflow
                return tiny * CopySign( tiny, x );
            }
        }
        k += 54;
        // subnormal result 
        x = SetHigh32Bits<Int32>( x, ( hx & 0x800fffff ) | ( k << 20 ) );
        return x * twom54;
    }
    /// <summary>
    /// <para>
    /// Multiplies a double precision floating point value 
    /// <c>x</c> multplied by <c>FLT_RADIX</c> raised to power <c>n</c>.
    /// </para>
    /// <para>
    /// FLT_RADIX is the radix used by the representation 
    /// of the floating point types.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and
    /// improves runtime performance by 467 %.
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value. 
    /// </param>
    /// <param name="n">
    /// An integer.
    /// </param>
    /// <returns>
    /// <c>x</c> multplied by <c>FLT_RADIX</c> raised to power <c>n</c>
    /// </returns>
    inline constexpr float ScaleByN( float x, int n ) noexcept
    {
        constexpr float two25 = 3.355443200e+07f;
        constexpr float twom25 = 2.9802322388e-08f;
        constexpr float huge = 1.0e+30f;
        constexpr float tiny = 1.0e-30f;

        Int32 ix = std::bit_cast<Int32>( x );

        // extract exponent 
        Int32 k = ( ix & 0x7f800000 ) >> 23;
        if ( k == 0 )
        {
            // 0 or subnormal x 
            if ( ( ix & 0x7fffffff ) == 0 )
            {
                // +-0 
                return x; 
            }
            x *= two25;
            ix = std::bit_cast<Int32>( x );
            k = ( ( ix & 0x7f800000 ) >> 23 ) - 25;
            if ( n < -50000 )
            {
                // underflow
                return tiny * x;
            }
        }
        if ( k == 0xff )
        {
            // NaN or Inf 
            return x + x;
        }
        k = k + n;
        if ( k > 0xfe )
        {
            // overflow  
            return huge * CopySign( huge, x ); 
        }
        if ( k > 0 )
        {
            // normal result 
            return std::bit_cast<float>( ( ix & 0x807fffff ) | ( k << 23 ) );
        }
        if ( k <= -25 )
        {
            if ( n > 50000 )
            {
                // in case integer overflow in n+k: overflow  
                return huge * copysignf( huge, x );
            }
            else
            {
                // underflow
                return tiny * copysignf( tiny, x );	
            }
        }
        // subnormal result 
        k += 25;
        x = std::bit_cast<float>( ( ix & 0x807fffff ) | ( k << 23 ) );
        return x * twom25;
    }


    /// <summary>
    /// <para>
    /// Computes the double precision floating point remainder of the division operation <c>x / y</c>.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and
    /// improves runtime performance by 13.38 %.
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value. 
    /// </param>
    /// <param name="y">
    /// A double precision floating point value. 
    /// </param>
    /// <returns>
    /// The double precision floating point remainder of the division operation <c>x / y</c>.
    /// </returns>
    inline constexpr double FMod( double x, double y ) noexcept
    {
        UInt64 uxi = std::bit_cast<UInt64>( x );
        int ex = uxi >> 52 & 0x7ff;
        int sx = uxi >> 63;

        UInt64 uyi = std::bit_cast<UInt64>( y );
        int ey = uyi >> 52 & 0x7ff;

        uint64_t i;

        if ( uyi << 1 == 0 || IsNaN( y ) || ex == 0x7ff )
        {
            return ( x * y ) / ( x * y );
        }
        if ( uxi << 1 <= uyi << 1 )
        {
            if ( uxi << 1 == uyi << 1 )
            {
                return 0 * x;
            }
            return x;
        }

        // normalize x and y 
        if ( !ex )
        {
            for ( i = uxi << 12; i >> 63 == 0; ex--, i <<= 1 );
            uxi <<= -ex + 1;
        }
        else
        {
            uxi &= static_cast<UInt64>(-1) >> 12;
            uxi |= 1ULL << 52;
        }
        if ( !ey )
        {
            for ( i = uyi << 12; i >> 63 == 0; ey--, i <<= 1 )
            {
                ;
            }
            uyi <<= -ey + 1;
        }
        else
        {
            uyi &= static_cast<UInt64>( -1 ) >> 12;
            uyi |= 1ULL << 52;
        }

        // x mod y 
        for ( ; ex > ey; ex-- )
        {
            i = uxi - uyi;
            if ( i >> 63 == 0 )
            {
                if ( i == 0 )
                    return 0 * x;
                uxi = i;
            }
            uxi <<= 1;
        }
        i = uxi - uyi;
        if ( i >> 63 == 0 )
        {
            if ( i == 0 )
                return 0 * x;
            uxi = i;
        }
        for ( ; uxi >> 52 == 0; uxi <<= 1, ex-- )
        {
            ;
        }

        // scale result 
        if ( ex > 0 )
        {
            uxi -= 1ULL << 52;
            uxi |= (uint64_t)ex << 52;
        }
        else
        {
            uxi >>= -ex + 1;
        }
        uxi |= (uint64_t)sx << 63;

        return std::bit_cast<double>( uxi );
    }


    /* e_fmodf.c -- float version of e_fmod.c.
     * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
     */

    /*
     * ====================================================
     * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
     *
     * Developed at SunPro, a Sun Microsystems, Inc. business.
     * Permission to use, copy, modify, and distribute this
     * software is freely granted, provided that this notice
     * is preserved.
     * ====================================================
     */

     /// <summary>
     /// <para>
     /// Computes the single precision floating point remainder of the division operation <c>x / y</c>.
     /// </para>
     /// <para>
     /// This implementation can be constexpr evaluated, and
     /// improves runtime performance by 89.59 %.
     /// </para>
     /// </summary>
     /// <param name="x">
     /// A single precision floating point value. 
     /// </param>
     /// <param name="y">
     /// A single precision floating point value. 
     /// </param>
     /// <returns>
     /// The single precision floating point remainder of the division operation <c>x / y</c>.
     /// </returns>
    inline constexpr float FMod( float x, float y ) noexcept
    {
        constexpr float one = 1.0; 
        constexpr float Zero[] = { 0.0, -0.0 };

        Int32 n, hx, hy, hz, ix, iy, sx, i;

        hx = std::bit_cast<Int32>( x );
        hy = std::bit_cast<Int32>( y );
        // sign of x 
        sx = hx & 0x80000000;
        // |x| 
        hx ^= sx;
        // |y| 
        hy &= 0x7fffffff;

        // purge off exception values 
        if ( hy == 0 || ( hx >= 0x7f800000 ) || // y=0,or x not finite 
            ( hy > 0x7f800000 ) ) // or y is NaN 
        {
            return ( x * y ) / ( x * y );
        }
        if ( hx < hy )
        {
            // |x|<|y| return x 
            return x;
        }
        if ( hx == hy )
        {
            // |x|=|y| return x*0
            return Zero[static_cast<UInt32>(sx) >> 31];
        }

        // determine ix = ilogb(x) 
        if ( hx < 0x00800000 )
        {	
            // subnormal x 
            for ( ix = -126, i = ( hx << 8 ); i > 0; i <<= 1 )
            {
                ix -= 1;
            }
        }
        else
        {
            ix = ( hx >> 23 ) - 127;
        }

        // determine iy = ilogb(y) 
        if ( hy < 0x00800000 )
        {	
            // subnormal y 
            for ( iy = -126, i = ( hy << 8 ); i >= 0; i <<= 1 )
            {
                iy -= 1;
            }
        }
        else
        {
            iy = ( hy >> 23 ) - 127;
        }

        // set up {hx,lx}, {hy,ly} and align y to x 
        if ( ix >= -126 )
        {
            hx = 0x00800000 | ( 0x007fffff & hx );
        }
        else
        {
            // subnormal x, shift x to normal 
            n = -126 - ix;
            hx = hx << n;
        }
        if ( iy >= -126 )
        {
            hy = 0x00800000 | ( 0x007fffff & hy );
        }
        else
        {
            // subnormal y, shift y to normal 
            n = -126 - iy;
            hy = hy << n;
        }

        // fix point fmod 
        n = ix - iy;
        while ( n-- )
        {
            hz = hx - hy;
            if ( hz < 0 ) 
            { 
                hx = hx + hx; 
            }
            else
            {
                if ( hz == 0 )
                {
                    // return sign(x)*0 
                    return Zero[static_cast<UInt32>( sx ) >> 31];
                }
                hx = hz + hz;
            }
        }
        hz = hx - hy;
        if ( hz >= 0 ) 
        { 
            hx = hz; 
        }

        // convert back to floating value and restore the sign 
        if ( hx == 0 )
        {
            // return sign(x)*0 
            return Zero[static_cast<UInt32>( sx ) >> 31];
        }
        while ( hx < 0x00800000 )
        {
            // normalize x 
            hx = hx + hx;
            iy -= 1;
        }
        if ( iy >= -126 )
        {
            // normalize output 
            hx = ( ( hx - 0x00800000 ) | ( ( iy + 127 ) << 23 ) );
            x = std::bit_cast<float>( hx | sx );
        }
        else
        {
            // subnormal output 
            n = -126 - iy;
            hx >>= n;
            x = std::bit_cast<float>( hx | sx );
            // create necessary signal 
            x *= one;
        }
        // exact output 
        return x;
    }


    namespace Internal
    {
        /*
         * ====================================================
         * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
         *
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        // *
        inline constexpr double ExpImpl( double x ) noexcept
        {
            constexpr double one = 1.0;
            constexpr double halF[2] = { 0.5,-0.5 };
            constexpr double huge = 1.0e+300;
            constexpr double o_threshold = 7.09782712893383973096e+02;
            constexpr double u_threshold = -7.45133219101941108420e+02;
            constexpr double ln2HI[2] = { 6.93147180369123816490e-01, -6.93147180369123816490e-01 };
            constexpr double ln2LO[2] = { 1.90821492927058770002e-10,  -1.90821492927058770002e-10, };
            constexpr double invln2 = 1.44269504088896338700e+00;
            constexpr double P1 = 1.66666666666666019037e-01;
            constexpr double P2 = -2.77777777770155933842e-03;
            constexpr double P3 = 6.61375632143793436117e-05;
            constexpr double P4 = -1.65339022054652515390e-06;
            constexpr double P5 = 4.13813679705723846039e-08;

            constexpr double twom1000 = 9.33263618503218878990e-302;

            double y, hi = 0.0, lo = 0.0, c, t, twopk;
            int32_t k = 0, xsb;
            Int64 ax = std::bit_cast<Int64>( x );
            Int32 hx = static_cast<Int32>( ax >> 32 );

            // sign bit of x 
            xsb = ( hx >> 31 ) & 1;
            // high word of |x| 
            hx &= 0x7fffffff;

            // filter out non-finite argument 
            if ( hx >= 0x40862E42 )
            {
                // if |x|>=709.78... 
                if ( hx >= 0x7ff00000 )
                {
                    UInt32 lx = static_cast<UInt32>( ax );
                    if ( ( ( hx & 0xfffff ) | lx ) != 0 )
                    {
                        // NaN 
                        return x + x;
                    }
                    else
                    {
                        // exp(+-inf)={inf,0} 
                        return ( xsb == 0 ) ? x : 0.0;
                    }
                }
                else
                {
                    if ( x > o_threshold )
                    {
                        // overflow
                        volatile double val = huge;
                        return val * val;
                    }
                    else if ( x < u_threshold )
                    {
                        // underflow 
                        volatile double val = twom1000;
                        return val * val;
                    }
                }
            }

            // this implementation gives 2.7182818284590455 for exp(1.0),
            // which is well within the allowable error. however,
            // 2.718281828459045 is closer to the true value so we prefer that
            // answer, given that 1.0 is such an important argument value. 

            /*
            if ( x == 1.0 )
            {
                return 2.718281828459045235360;
            }
            */

            // argument reduction 
            if ( hx > 0x3fd62e42 )
            {
                // if  |x| > 0.5 ln2 
                if ( hx < 0x3FF0A2B2 )
                {
                    // and |x| < 1.5 ln2 
                    hi = x - ln2HI[xsb];
                    lo = ln2LO[xsb];
                    k = 1 - xsb - xsb;
                }
                else
                {
                    k = static_cast<Int32>( invln2 * x + halF[xsb] );
                    t = k;
                    // t*ln2HI is exact here 
                    hi = x - t * ln2HI[0];
                    lo = t * ln2LO[0];
                }
                x = hi - lo;
            }
            else if ( hx < 0x3e300000 )
            {
                // when |x|<2**-28 
                if ( huge + x > one )
                {
                    // trigger inexact 
                    return one + x;
                }
            }
            else k = 0;

            // x is now in primary range 
            t = x * x;
            if ( k >= -1021 )
            {
                twopk = From32BitsTo64Bits<double>( 0x3ff00000 + ( k << 20 ), 0 );
            }
            else
            {
                twopk = From32BitsTo64Bits<double>( 0x3ff00000 + ( ( k + 1000 ) << 20 ), 0 );
            }
            c = x - t * ( P1 + t * ( P2 + t * ( P3 + t * ( P4 + t * P5 ) ) ) );
            if ( k == 0 )
            {
                return one - ( ( x * c ) / ( c - 2.0 ) - x );
            }
            else
            {
                y = one - ( ( lo - ( x * c ) / ( 2.0 - c ) ) - hi );
            }
            if ( k >= -1021 )
            {
                if ( k == 1024 )
                {
                    return y * 2.0 * 0x1p1023;
                }
                return y * twopk;
            }
            else
            {
                return y * twopk * twom1000;
            }
        }

        /* e_expf.c -- float version of e_exp.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         */

         /*
          * ====================================================
          * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
          *
          * Developed at SunPro, a Sun Microsystems, Inc. business.
          * Permission to use, copy, modify, and distribute this
          * software is freely granted, provided that this notice
          * is preserved.
          * ====================================================
          */

        inline constexpr float ExpImpl( float x ) noexcept
        {

            constexpr float one = 1.0f;
            constexpr float halF[2] = { 0.5f,-0.5f };
            constexpr float huge = 1.0e+30f;
            constexpr float o_threshold = 8.8721679688e+01f;
            constexpr float u_threshold = -1.0397208405e+02f;
            constexpr float ln2HI[2] = { 6.9314575195e-01f, -6.9314575195e-01f };
            constexpr float ln2LO[2] = { 1.4286067653e-06f, -1.4286067653e-06f };
            constexpr float invln2 = 1.4426950216e+00f;

            // Domain [-0.34568, 0.34568], range ~[-4.278e-9, 4.447e-9]:
            // |x*(exp(x)+1)/(exp(x)-1) - p(x)| < 2**-27.74

            constexpr float P1 = 1.6666625440e-1f;
            constexpr float P2 = -2.7667332906e-3f;

            constexpr float twom100 = 7.8886090522e-31f;

            float y, hi = 0.0, lo = 0.0, c, t, twopk;
            Int32 k = 0, xsb;
            UInt32 hx = std::bit_cast<UInt32>( x );

            // sign bit of x 
            xsb = ( hx >> 31 ) & 1;
            // high word of |x| 
            hx &= 0x7fffffff;

            // filter out non-finite argument 
            if ( hx >= 0x42b17218 )
            {
                // if |x|>=88.721... 
                if ( hx > 0x7f800000 )
                {
                    // NaN 
                    return x + x;
                }
                if ( hx == 0x7f800000 )
                {
                    // exp(+-inf)={inf,0} 
                    return ( xsb == 0 ) ? x : 0.0f;
                }
                if ( x > o_threshold )
                {
                    // overflow 
#pragma warning(push)
#pragma warning(disable:4056)
                    return huge * huge;
#pragma warning(pop)
                }
                if ( x < u_threshold )
                {
                    // underflow 
                    return twom100 * twom100;
                }
            }

            // argument reduction 
            if ( hx > 0x3eb17218 )
            {
                // if  |x| > 0.5 ln2 
                if ( hx < 0x3F851592 )
                {
                    // and |x| < 1.5 ln2 
                    hi = x - ln2HI[xsb];
                    lo = ln2LO[xsb];
                    k = 1 - xsb - xsb;
                }
                else
                {
                    k = static_cast<Int32>( invln2 * x + halF[xsb] );
                    t = static_cast<float>( k );
                    // t*ln2HI is exact here 
                    hi = x - t * ln2HI[0];
                    lo = t * ln2LO[0];
                }
                x = hi - lo;
            }
            else if ( hx < 0x39000000 )
            {
                // when |x|<2**-14 
                if ( huge + x > one )
                {
                    // trigger inexact 
                    return one + x;
                }
            }
            else k = 0;

            // x is now in primary range 
            t = x * x;
            if ( k >= -125 )
            {
                twopk = std::bit_cast<float>( 0x3f800000 + ( k << 23 ) );
            }
            else
            {
                twopk = std::bit_cast<float>( 0x3f800000 + ( ( k + 100 ) << 23 ) );
            }
            c = x - t * ( P1 + t * P2 );
            if ( k == 0 )
            {
                return one - ( ( x * c ) / ( c - (float)2.0 ) - x );
            }
            else
            {
                y = one - ( ( lo - ( x * c ) / ( (float)2.0 - c ) ) - hi );
            }
            if ( k >= -125 )
            {
                if ( k == 128 )
                {
                    return y * 2.0F * 0x1p127F;
                }
                return y * twopk;
            }
            else
            {
                return y * twopk * twom100;
            }
        }
    }

    /// <summary>
    /// <para>
    /// Computes <c>e</c>, <c>2.7182818</c>, raised to the given power <c>x</c>.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and calls the
    /// standard implementation at runtime.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// <c>e</c> raised to the given power <c>x</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Exp( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::ExpImpl( x );
        }
        else
        {
            return std::exp( x );
        }
    }


    namespace Internal
    {
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        constexpr inline double HypotImpl( double x, double y ) noexcept
        {
            double a, b; //, t1, t2, y1, y2, w;
            
            auto aa = std::bit_cast<Int64>( x );
            auto ab = std::bit_cast<Int64>( y );

            Int32 ha = static_cast<Int32>( aa >> 32 );
            ha &= 0x7fffffff;
            Int32 hb = static_cast<Int32>( ab >> 32 );
            hb &= 0x7fffffff;
            if ( hb > ha ) 
            { 
                a = y; 
                b = x; 
                std::swap( ha, hb );
                std::swap( aa, ab );
            }
            else 
            { 
                a = x; 
                b = y; 
            }
            a = Abs( a );
            b = Abs( b );
            if ( ( ha - hb ) > 0x3c00000 ) 
            { 
                // x/y > 2**60 
                return a + b; 
            } 
            Int32 k = 0;
            if ( ha > 0x5f300000 )
            {	
                // a>2**500 
                if ( ha >= 0x7ff00000 )
                {	
                    // Inf or NaN 
                    
                    // Use original arg order iff result is NaN; quieten sNaNs. 
                    auto w = Abs( x + 0.0 ) - Abs( y + 0.0 );
                    UInt32 low = static_cast<UInt32>( aa );
                    if ( ( ( ha & 0xfffff ) | low ) == 0 )
                    {
                        w = a;
                    }
                    low = static_cast<UInt32>( ab );
                    if ( ( ( hb ^ 0x7ff00000 ) | low ) == 0 )
                    {
                        w = b;
                    }
                    return w;
                }
                // scale a and b by 2**-600 
                ha -= 0x25800000; 
                hb -= 0x25800000;	
                k += 600;

                aa = ( static_cast<Int64>( ha ) << 32 ) | ( aa & 0x00000000FFFFFFFFLL );
                a = std::bit_cast<double>( aa );

                ab = ( static_cast<Int64>( hb ) << 32 ) | ( ab & 0x00000000FFFFFFFFLL );
                b = std::bit_cast<double>( ab );
            }
            if ( hb < 0x20b00000 )
            {	
                // b < 2**-500 
                if ( hb <= 0x000fffff )
                {	
                    // subnormal b or 0 
                    UInt32 low = static_cast<UInt32>( ab );
                    if ( ( hb | low ) == 0 )
                    {
                        return a;
                    }
                    // t1=2^1022 
                    double t1 = std::bit_cast<double>( 0x7fd0000000000000 );
                    b *= t1;
                    a *= t1;
                    k -= 1022;
                }
                else
                {	
                    // scale a and b by 2^600 
                    // a *= 2^600 
                    ha += 0x25800000;
                    // b *= 2^600 
                    hb += 0x25800000;
                    k -= 600;

                    aa = ( static_cast<Int64>( ha ) << 32 ) | ( aa & 0x00000000FFFFFFFFLL );
                    a = std::bit_cast<double>( aa );

                    ab = ( static_cast<Int64>( hb ) << 32 ) | ( ab & 0x00000000FFFFFFFFLL );
                    b = std::bit_cast<double>( ab );
                }
            }
            // medium size a and b 
            double w = a - b;
            if ( w > b )
            {
                double t1 = std::bit_cast<double>( static_cast<Int64>( ha ) << 32 );
                double t2 = a - t1;
                w = Sqrt( t1 * t1 - ( b * ( -b ) - t2 * ( a + t1 ) ) );
            }
            else
            {
                a = a + a;
                double y1 = std::bit_cast<double>( static_cast<Int64>( hb ) << 32 );
                double y2 = b - y1;
                double t1 = std::bit_cast<double>( static_cast<Int64>( ha + 0x00100000 ) << 32 );
                double t2 = a - t1;
                w = Sqrt( t1 * y1 - ( w * ( -w ) - ( t1 * y2 + t2 * b ) ) );
            }
            if ( k != 0 )
            {
                constexpr UInt32 high = static_cast<UInt32>( std::bit_cast<Int64>(1.0) >> 32 );
                double t1 = std::bit_cast<double>( static_cast<Int64>( high + ( k << 20 ) ) << 32 );
                return t1 * w;
            }
            else
            {
                return w;
            }
        }

        /* e_hypotf.c -- float version of e_hypot.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         */

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        constexpr inline float HypotImpl( float x, float y ) noexcept
        {
            float a, b; // , t1, t2, y1, y2, w;
            

            Int32 ha = std::bit_cast<Int32>( x );
            ha &= 0x7fffffff;
            Int32 hb = std::bit_cast<Int32>( y );
            hb &= 0x7fffffff;
            if ( hb > ha ) 
            { 
                a = y; 
                b = x;
                std::swap( ha, hb );
            }
            else 
            { 
                a = x; 
                b = y; 
            }
            a = Abs( a );
            b = Abs( b );
            if ( ( ha - hb ) > 0xf000000 ) 
            { 
                // x/y > 2**30 
                return a + b; 
            } 
            Int32 k = 0;
            if ( ha > 0x58800000 )
            {	/* a>2**50 */
                if ( ha >= 0x7f800000 )
                {	
                    // Inf or NaN 
                    // Use original arg order iff result is NaN; quieten sNaNs. 
                    auto w = Abs( x + 0.0F ) - Abs( y + 0.0F );
                    if ( ha == 0x7f800000 )
                    {
                        w = a;
                    }
                    if ( hb == 0x7f800000 )
                    {
                        w = b;
                    }
                    return w;
                }
                // scale a and b by 2**-68 
                ha -= 0x22000000; 
                hb -= 0x22000000;	
                k += 68;
                a = std::bit_cast<float>( ha );
                b = std::bit_cast<float>( hb );
            }
            if ( hb < 0x26800000 )
            {	
                // b < 2**-50 
                if ( hb <= 0x007fffff )
                {	
                    // subnormal b or 0 
                    if ( hb == 0 )
                    {
                        return a;
                    }
                    constexpr float t1 = std::bit_cast<float>( 0x7e800000 );
                    b *= t1;
                    a *= t1;
                    k -= 126;
                }
                else
                {	
                    // scale a and b by 2^68 

                    // a *= 2^68 
                    ha += 0x22000000;
                    // b *= 2^68 
                    hb += 0x22000000;
                    k -= 68;
                    a = std::bit_cast<float>( ha );
                    b = std::bit_cast<float>( hb );
                }
            }
            // medium size a and b 
            float w = a - b;
            if ( w > b )
            {
                float t1 = std::bit_cast<float>( ha & 0xfffff000 );
                float t2 = a - t1;
                w = Sqrt( t1 * t1 - ( b * ( -b ) - t2 * ( a + t1 ) ) );
            }
            else
            {
                a = a + a;
                float y1 = std::bit_cast<float>( hb & 0xfffff000 );
                float y2 = b - y1;
                float t1 = std::bit_cast<float>( ( ha + 0x00800000 ) & 0xfffff000 );
                float t2 = a - t1;
                w = Sqrt( t1 * y1 - ( w * ( -w ) - ( t1 * y2 + t2 * b ) ) );
            }
            if ( k != 0 )
            {
                float t1 = std::bit_cast<float>( 0x3f800000 + ( k << 23 ) );
                return t1 * w;
            }
            else
            {
                return w;
            }
        }
    }

    /// <summary>
    /// <para>
    /// Computes the square root of the sum of the squares of x and y, 
    /// without undue overflow or underflow at intermediate stages of 
    /// the computation.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and calls the
    /// standard implementation at runtime.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <param name="y">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The square root of the sum of the squares of x and y.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Hypot( T x, T y ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::HypotImpl( x, y );
        }
        else
        {
            return std::hypot( x, y );
        }
    }


    namespace Internal
    {
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        constexpr inline double LogImpl( double x ) noexcept
        {
            constexpr double ln2_hi = 6.93147180369123816490e-01;
            constexpr double ln2_lo = 1.90821492927058770002e-10;
            constexpr double two54 = 1.80143985094819840000e+16;
            constexpr double Lg1 = 6.666666666666735130e-01;
            constexpr double Lg2 = 3.999999999940941908e-01;
            constexpr double Lg3 = 2.857142874366239149e-01;
            constexpr double Lg4 = 2.222219843214978396e-01;
            constexpr double Lg5 = 1.818357216161805012e-01;
            constexpr double Lg6 = 1.531383769920937332e-01;
            constexpr double Lg7 = 1.479819860511658591e-01; 
            constexpr double zero = 0.0;

            double hfsq, f, s, z, R, w, t1, t2, dk;
            int32_t k, i, j;

            Int64 ax = std::bit_cast<Int64> ( x );
            Int32 hx = static_cast<Int32>( ax >> 32 );
            UInt32 lx = static_cast<UInt32>( ax );

            k = 0;
            if ( hx < 0x00100000 )
            {
                // x < 2**-1022  
                if ( ( ( hx & 0x7fffffff ) | lx ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two54 / zero;
                    return -std::numeric_limits<double>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<double>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 54; 
                x *= two54; 
                ax = std::bit_cast<Int64> ( x );
                hx = static_cast<Int32>( ax >> 32 );
            }
            if ( hx >= 0x7ff00000 )
            {
                return x + x;
            }
            k += ( hx >> 20 ) - 1023;
            hx &= 0x000fffff;
            i = ( hx + 0x95f64 ) & 0x100000;
            // normalize x or x/2 
            ax = (static_cast<Int64>( hx | ( i ^ 0x3ff00000 ) ) << 32) | (ax & 0x00000000FFFFFFFF);
            x = std::bit_cast<double>( ax );
            
            k += ( i >> 20 );
            f = x - 1.0;
            if ( ( 0x000fffff & ( 2 + hx ) ) < 3 )
            {	
                // -2**-20 <= f < 2**-20 
                if ( f == zero )
                {
                    if ( k == 0 )
                    {
                        return zero;
                    }
                    else
                    {
                        dk = static_cast<double>(k);
                        return dk * ln2_hi + dk * ln2_lo;
                    }
                }
                R = f * f * ( 0.5 - 0.33333333333333333 * f );
                if ( k == 0 )
                {
                    return f - R;
                }
                else
                {
                    dk = static_cast<double>( k );
                    return dk * ln2_hi - ( ( R - dk * ln2_lo ) - f );
                }
            }
            s = f / ( 2.0 + f );
            dk = static_cast<double>( k );
            z = s * s;
            i = hx - 0x6147a;
            w = z * z;
            j = 0x6b851 - hx;
            t1 = w * ( Lg2 + w * ( Lg4 + w * Lg6 ) );
            t2 = z * ( Lg1 + w * ( Lg3 + w * ( Lg5 + w * Lg7 ) ) );
            i |= j;
            R = t2 + t1;
            if ( i > 0 )
            {
                hfsq = 0.5 * f * f;
                if ( k == 0 ) 
                    return f - ( hfsq - s * ( hfsq + R ) ); 
                else
                    return dk * ln2_hi - ( ( hfsq - ( s * ( hfsq + R ) + dk * ln2_lo ) ) - f );
            }
            else
            {
                if ( k == 0 ) 
                    return f - s * ( f - R ); 
                else
                    return dk * ln2_hi - ( ( s * ( f - R ) - dk * ln2_lo ) - f );
            }
        }


        /* e_logf.c -- float version of e_log.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
         */

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        constexpr inline float LogImpl( float x ) noexcept
        {
            constexpr float ln2_hi = 6.9313812256e-01f;
            constexpr float ln2_lo = 9.0580006145e-06f;
            constexpr float two25 = 3.355443200e+07f;
                /* |(log(1+s)-log(1-s))/s - Lg(s)| < 2**-34.24 (~[-4.95e-11, 4.97e-11]). */
            constexpr float Lg1 = 0xaaaaaa.0p-24f;
            constexpr float Lg2 = 0xccce13.0p-25f;
            constexpr float Lg3 = 0x91e9ee.0p-25f;
            constexpr float Lg4 = 0xf89e26.0p-26f;

            constexpr float zero = 0.0f;

            float hfsq, f, s, z, R, w, t1, t2, dk;
            //int32_t k, ix, i, j;

            Int32 ix = std::bit_cast<Int32>( x );

            Int32 k = 0;
            if ( ix < 0x00800000 )
            {
                // x < 2**-126  
                if ( ( ix & 0x7fffffff ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two25 / zero;
                    return -std::numeric_limits<float>::infinity( );
                }
                if ( ix < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<float>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 25; 
                x *= two25; 
                ix = std::bit_cast<Int32>( x );
            }
            if ( ix >= 0x7f800000 )
            {
                return x + x;
            }
            k += ( ix >> 23 ) - 127;
            ix &= 0x007fffff;
            Int32 i = ( ix + ( 0x95f64 << 3 ) ) & 0x800000;

            // normalize x or x/2 
            x = std::bit_cast<float>( ix | ( i ^ 0x3f800000 ) );
            
            k += ( i >> 23 );
            f = x - 1.0f;
            if ( ( 0x007fffff & ( 0x8000 + ix ) ) < 0xc000 )
            {	
                // -2**-9 <= f < 2**-9 
                if ( f == zero )
                {
                    if ( k == 0 )
                    {
                        return zero;
                    }
                    else
                    {
                        dk = static_cast<float>( k );
                        return dk * ln2_hi + dk * ln2_lo;
                    }
                }
                R = f * f * ( 0.5f - (float)0.33333333333333333 * f );
                if ( k == 0 ) return f - R; else
                {
                    dk = static_cast<float>( k );
                    return dk * ln2_hi - ( ( R - dk * ln2_lo ) - f );
                }
            }
            s = f / ( 2.0f + f );
            dk = static_cast<float>( k );
            z = s * s;
            i = ix - ( 0x6147a << 3 );
            w = z * z;
            Int32 j = ( 0x6b851 << 3 ) - ix;
            t1 = w * ( Lg2 + w * Lg4 );
            t2 = z * ( Lg1 + w * Lg3 );
            i |= j;
            R = t2 + t1;
            if ( i > 0 )
            {
                hfsq = 0.5f * f * f;
                if ( k == 0 ) 
                    return f - ( hfsq - s * ( hfsq + R ) ); 
                else
                    return dk * ln2_hi - ( ( hfsq - ( s * ( hfsq + R ) + dk * ln2_lo ) ) - f );
            }
            else
            {
                if ( k == 0 ) 
                    return f - s * ( f - R ); 
                else
                    return dk * ln2_hi - ( ( s * ( f - R ) - dk * ln2_lo ) - f );
            }
        }
    }
    /// <summary>
    /// <para>
    /// Computes the natural, base e, logarithm of <c>x</c>.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and calls the
    /// standard implementation at runtime.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The natural, base e, logarithm of <c>x</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::LogImpl( x );
        }
        else
        {
            return std::log( x );
        }
    }

    namespace Internal
    {
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        constexpr inline double Log1pCore( double f ) noexcept
        {
            constexpr double Lg1 = 6.666666666666735130e-01;
            constexpr double Lg2 = 3.999999999940941908e-01;
            constexpr double Lg3 = 2.857142874366239149e-01;
            constexpr double Lg4 = 2.222219843214978396e-01;
            constexpr double Lg5 = 1.818357216161805012e-01;
            constexpr double Lg6 = 1.531383769920937332e-01;
            constexpr double Lg7 = 1.479819860511658591e-01;

            double hfsq, s, z, R, w, t1, t2;

            s = f / ( 2.0 + f );
            z = s * s;
            w = z * z;
            t1 = w * ( Lg2 + w * ( Lg4 + w * Lg6 ) );
            t2 = z * ( Lg1 + w * ( Lg3 + w * ( Lg5 + w * Lg7 ) ) );
            R = t2 + t1;
            hfsq = 0.5 * f * f;
            return s * ( hfsq + R );
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        constexpr inline float Log1pCore( float f ) noexcept
        {
            // |(log(1+s)-log(1-s))/s - Lg(s)| < 2**-34.24 (~[-4.95e-11, 4.97e-11]). 
            constexpr float Lg1 = 0xaaaaaa.0p-24f;
            constexpr float Lg2 = 0xccce13.0p-25f;
            constexpr float Lg3 = 0x91e9ee.0p-25f;
            constexpr float Lg4 = 0xf89e26.0p-26f;

            float hfsq, s, z, R, w, t1, t2;

            s = f / ( 2.0f + f );
            z = s * s;
            w = z * z;
            t1 = w * ( Lg2 + w * Lg4 );
            t2 = z * ( Lg1 + w * Lg3 );
            R = t2 + t1;
            hfsq = 0.5f * f * f;
            return s * ( hfsq + R );
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        constexpr inline double Log2Impl( double x ) noexcept
        {
            constexpr double two54 = 1.80143985094819840000e+16;
            constexpr double ivln2hi = 1.44269504072144627571e+00;
            constexpr double ivln2lo = 1.67517131648865118353e-10;
            constexpr double zero = 0.0;

            double f, hfsq, hi, lo, r, val_hi, val_lo, w, y;

            Int64 ax = std::bit_cast<Int64>( x );
            Int32 hx = static_cast<Int32>( ax >> 32 );
            UInt32 lx = static_cast<UInt32>( ax );

            Int32 k = 0;
            if ( hx < 0x00100000 )
            {			
                // x < 2**-1022  
                if ( ( ( hx & 0x7fffffff ) | lx ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two54 / zero;
                    return -std::numeric_limits<double>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<double>::quiet_NaN( );
                }
                k -= 54; 
                // subnormal number, scale up x 
                x *= two54; 
                ax = std::bit_cast<Int64>( x );
                hx = static_cast<Int32>( ax >> 32 );
            }
            if ( hx >= 0x7ff00000 )
            {
                return x + x;
            }
            if ( hx == 0x3ff00000 && lx == 0 )
            {
                // log(1) = +0 
                return zero;
            }
            k += ( hx >> 20 ) - 1023;
            hx &= 0x000fffff;
            Int32 i = ( hx + 0x95f64 ) & 0x100000;
            // normalize x or x/2 
            ax = (static_cast<Int64>( hx | ( i ^ 0x3ff00000 ) ) << 32) | ( ax & 0x00000000FFFFFFFF);
            x = std::bit_cast<double>( ax );
            k += ( i >> 20 );
            y = static_cast<double>( k );
            f = x - 1.0;
            hfsq = 0.5 * f * f;
            r = Log1pCore( f );

            
            hi = std::bit_cast<double>( std::bit_cast<Int64>( f - hfsq ) & 0xFFFFFFFF00000000 );
            
            lo = ( f - hi ) - hfsq + r;
            val_hi = hi * ivln2hi;
            val_lo = ( lo + hi ) * ivln2lo + lo * ivln2hi;

            // spadd(val_hi, val_lo, y), except for not using double_t: 
            w = y + val_hi;
            val_lo += ( y - w ) + val_hi;
            val_hi = w;

            return val_lo + val_hi;
        }

        constexpr inline float Log2Impl( float x ) noexcept
        {
            constexpr float two25 = 3.3554432000e+07f;
            constexpr float ivln2hi = 1.4428710938e+00f;
            constexpr float ivln2lo = -1.7605285393e-04f;
            constexpr float zero = 0.0;

            float f, hfsq, hi, lo, r, y;
            
            Int32 hx = std::bit_cast<Int32>( x );

            Int32 k = 0;
            if ( hx < 0x00800000 )
            {			
                // x < 2**-126  
                if ( ( hx & 0x7fffffff ) == 0 )
                {
                    // log(+-0)=-inf 
                    // return -two25 / zero;
                    return -std::numeric_limits<float>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<float>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 25; 
                x *= two25; 
                hx = std::bit_cast<Int32>( x );
            }
            if ( hx >= 0x7f800000 )
            {
                return x + x;
            }
            if ( hx == 0x3f800000 )
            {
                // log(1) = +0 
                return zero;
            }
            k += ( hx >> 23 ) - 127;
            hx &= 0x007fffff;
            Int32 i = ( hx + ( 0x4afb0d ) ) & 0x800000;
            // normalize x or x/2 
            x = std::bit_cast<float>( hx | ( i ^ 0x3f800000 ) );
            k += ( i >> 23 );
            y = static_cast<float>( k );
            f = x - 1.0f;
            hfsq = 0.5f * f * f;
            r = Log1pCore( f );

            hi = f - hfsq;
            hx = std::bit_cast<Int32>( hi );
            hi = std::bit_cast<float>( hx & 0xfffff000 );
            lo = ( f - hi ) - hfsq + r;
            return ( lo + hi ) * ivln2lo + lo * ivln2hi + hi * ivln2hi + y;
        }
    }


    /// <summary>
    /// <para>
    /// Computes the binary, base-2, logarithm of x.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and
    /// at runtime performs 251% better than std::log2 for single precision floating
    /// point values, and uses std::log2 for double precision floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The binary, base-2, logarithm of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log2( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::Log2Impl( x );
        }
        else
        {
            using FloatT = std::remove_cvref_t<T>;
            if constexpr ( std::is_same_v<FloatT, double> )
            {
                return std::log2( x );
            }
            else
            {
                return Math::Internal::Log2Impl( x );
            }
        }
        
    }

    namespace Internal
    {
        constexpr inline double Log10Impl( double x ) noexcept
        {
            constexpr double two54 = 1.80143985094819840000e+16;
            constexpr double ivln10hi = 4.34294481878168880939e-01;
            constexpr double ivln10lo = 2.50829467116452752298e-11;
            constexpr double log10_2hi = 3.01029995663611771306e-01;
            constexpr double log10_2lo = 3.69423907715893078616e-13;

            constexpr double zero = 0.0;

            double f, hfsq, hi, lo, r, val_hi, val_lo, w, y, y2;
            
            Int64 ax = std::bit_cast<Int64>( x );
            Int32 hx = static_cast<Int32>( ax >> 32 );
            UInt32 lx = static_cast<UInt32>( ax );
            

            Int32 k = 0;
            if ( hx < 0x00100000 )
            {
                // x < 2**-1022  
                if ( ( ( hx & 0x7fffffff ) | lx ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two54 / zero;
                    return -std::numeric_limits<double>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<double>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 54; 
                x *= two54; 
                ax = std::bit_cast<Int64>( x );
                hx = static_cast<Int32>( ax >> 32 );
            }
            if ( hx >= 0x7ff00000 )
            {
                return x + x;
            }
            if ( hx == 0x3ff00000 && lx == 0 )
            {
                // log(1) = +0 
                return zero;
            }
            k += ( hx >> 20 ) - 1023;
            hx &= 0x000fffff;
            Int32 i = ( hx + 0x95f64 ) & 0x100000;
            // normalize x or x/2 
            ax = ( static_cast<Int64>( hx | ( i ^ 0x3ff00000 ) ) << 32 ) | ( ax & 0x00000000FFFFFFFF );
            x = std::bit_cast<double>( ax );
            
            k += ( i >> 20 );
            y = static_cast<double>( k );
            f = x - 1.0;
            hfsq = 0.5 * f * f;
            r = Log1pCore( f );
            
            hi = std::bit_cast<double>( std::bit_cast<Int64>( f - hfsq ) & 0xFFFFFFFF00000000 );
            
            lo = ( f - hi ) - hfsq + r;
            val_hi = hi * ivln10hi;
            y2 = y * log10_2hi;
            val_lo = y * log10_2lo + ( lo + hi ) * ivln10lo + lo * ivln10hi;

            /*
             * Extra precision in for adding y*log10_2hi is not strictly needed
             * since there is no very large cancellation near x = sqrt(2) or
             * x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
             * with some parallelism and it reduces the error for many args.
             */
            w = y2 + val_hi;
            val_lo += ( y2 - w ) + val_hi;
            val_hi = w;

            return val_lo + val_hi;
        }

        constexpr inline float Log10Impl( float x ) noexcept
        {
            constexpr float two25 = 3.3554432000e+07f;
            constexpr float ivln10hi = 4.3432617188e-01f;
            constexpr float ivln10lo = -3.1689971365e-05f;
            constexpr float log10_2hi = 3.0102920532e-01f;
            constexpr float log10_2lo = 7.9034151668e-07f;

            constexpr float zero = 0.0;

            float f, hfsq, hi, lo, r, y;
            

            Int32 hx = std::bit_cast<Int32>( x );

            Int32 k = 0;
            if ( hx < 0x00800000 )
            {
                // x < 2**-126  
                if ( ( hx & 0x7fffffff ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two25 / zero;
                    return -std::numeric_limits<float>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<float>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 25; x *= two25; 
                hx = std::bit_cast<Int32>( x );
                
            }
            if ( hx >= 0x7f800000 )
            {
                return x + x;
            }
            if ( hx == 0x3f800000 )
            {
                // log(1) = +0 
                return zero;
            }
            k += ( hx >> 23 ) - 127;
            hx &= 0x007fffff;
            Int32 i = ( hx + ( 0x4afb0d ) ) & 0x800000;

            // normalize x or x/2 
            x = std::bit_cast<float>( hx | ( i ^ 0x3f800000 ) );
            

            k += ( i >> 23 );
            y = static_cast<float>( k );
            f = x - 1.0f;
            hfsq = 0.5f * f * f;
            r = Log1pCore( f );

            hi = f - hfsq;
            hx = std::bit_cast<Int32>( hi );
            hi = std::bit_cast<float>( hx & 0xfffff000 );
            lo = ( f - hi ) - hfsq + r;
            return y * log10_2lo + ( lo + hi ) * ivln10lo + lo * ivln10hi + hi * ivln10hi + y * log10_2hi;
        }
    }

    /// <summary>
    /// <para>
    /// Computes the common, base 10, logarithm of x.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated,
    /// but at runtime calls std::log10f for single precision
    /// floating point values and std::log10 for double precision
    /// floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The common, base 10, logarithm of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log10( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::Log10Impl( x );
        }
        else
        {
            using FloatT = std::remove_cvref_t<T>;
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return std::log10f( x );
            }
            else
            {
                return std::log10( x );
            }
        }
    }


    /// <summary>
    /// <para>
    /// Computes the sine of x given in radians.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and 
    /// performs 14.38 % better than std::sin for single precision
    /// floating point values. Calls std::sin double precision
    /// floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The sine of x given in radians.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Sin( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::SinImpl( x );
        }
        else
        {
            if constexpr ( std::is_same_v<std::remove_cvref_t<T>, float> )
            {
                return Math::Internal::SinImpl( x );
            }
            else
            {
                //return Math::Internal::SinImpl( x );
                return std::sin( x );
            }
        }
        
    }

    /// <summary>
    /// <para>
    /// Computes the principal value of the arc sine of x.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and
    /// at runtime performs 59.78 % better than std::asin
    /// for double precision floating point values, and
    /// 109.87 % better than std::asin for single floating 
    /// point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The principal value of the arc sine of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ASin( T x ) noexcept
    {
        return Math::Internal::ASinImpl( x );
    }

    /// <summary>
    /// <para>
    /// Computes the cosine of x given in radians.
    /// </para>
    /// <para>
    /// This implementation can be constexpr evaluated, and 
    /// performs 14.93 % better than std::cos for single precision
    /// floating point values. Calls std::cos double precision
    /// floating point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The cosine of x given in radians.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Cos( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::CosImpl( x );
        }
        else
        {
            if constexpr ( std::is_same_v<std::remove_cvref_t<T>, float> )
            {
                return Math::Internal::CosImpl( x );
            }
            else
            {
                return std::cos( x );
            }
        }
    }

    /// <summary>
    /// <para>
    /// Computes the principal value of the arc cosine of x.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and
    /// at runtime performs 90.89 % better than std::acos
    /// for double precision floating point values, and
    /// 107.69 % better than std::acos for single floating 
    /// point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The principal value of the arc cosine of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ACos( T x ) noexcept
    {
        return Math::Internal::ACosImpl( x );
    }


    /// <summary>
    /// <para>
    /// Computes the tangent of x given in radians.
    /// </para>
    /// This implementation can be constexpr evaluated,
    /// and at runtime calls std::tan.
    /// <para>
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The tangent of x given in radians.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Tan( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::TanImpl( x );
        }
        else
        {
            return std::tan( x );
        }
    }

    /// <summary>
    /// <para>
    /// Computes the principal value of the arc tangent of x.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and
    /// at runtime performs 6.56 % better than std::atan
    /// for double precision floating point values, and
    /// 78.08 % better than std::atan for single floating 
    /// point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The principal value of the arc tangent of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x ) noexcept
    {
        return Math::Internal::ATanImpl( x );
    }

    /// <summary>
    /// <para>
    /// Computes the arc tangent of x / y using the signs of arguments 
    /// to determine the correct quadrant.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and
    /// at runtime performs 44.03 % better than std::atan2
    /// for double precision floating point values, and
    /// 36.17 % better than std::atan2 for single floating 
    /// point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <param name="y">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The arc tangent of x / y using the signs of arguments to 
    /// determine the correct quadrant.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x, T y ) noexcept
    {
        return Math::Internal::ATan2Impl( x, y );
    }
    /// <summary>
    /// <para>
    /// Computes the arc tangent of x / y using the signs of arguments 
    /// to determine the correct quadrant.
    /// </para>
    /// <para>
    /// This function can be constexpr evaluated, and
    /// at runtime performs 44.03 % better than std::atan2
    /// for double precision floating point values, and
    /// 36.17 % better than std::atan2 for single floating 
    /// point values.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <param name="y">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The arc tangent of x / y using the signs of arguments to 
    /// determine the correct quadrant.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan2( T x, T y ) noexcept
    {
        return Math::Internal::ATan2Impl( x, y );
    }

    /// <summary>
    /// Simultaneously compute the sine and cosine of x, where x is in radians, 
    /// returning the sine in the variable referenced by sinResult, and the 
    /// cosine in the variable referenced by cosResult.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <param name="sinResult"></param>
    /// <param name="cosResult"></param>
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr void SinCos( T x, T& sinResult, T& cosResult ) noexcept
    {
        sinResult = Sin( x );
        cosResult = Cos( x );
    }



}

#endif
