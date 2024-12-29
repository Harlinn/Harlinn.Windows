#pragma once
#ifndef HARLINN_COMMON_CORE_INTERNAL_MATH_TRIGONOMETRY_H_
#define HARLINN_COMMON_CORE_INTERNAL_MATH_TRIGONOMETRY_H_
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

#include <HCCMathForward.h>

namespace Harlinn::Common::Core::Math::Internal
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
    template<bool doublePrecision>
    inline constexpr int RemPIo2Core( double* x, double* y, int e0, int nx )
    {
        constexpr int32_t ipio2[ ] =
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
        constexpr double PIo2[ ] =
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
        Int32 jk = doublePrecision ? 4 : 3;
        Int32 jp = jk;

        // determine jx,jv,q0, note that 3>q0 
        Int32 jx = nx - 1;
        Int32 jv = ( e0 - 3 ) / 24; if ( jv < 0 ) jv = 0;
        Int32 q0 = e0 - 24 * ( jv + 1 );

        // set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] 
        Int32 j = jv - jx;
        Int32 m = jx + jk;
        double f[ 20 ];
        for ( Int32 i = 0; i <= m; i++, j++ )
        {
            f[ i ] = ( j < 0 ) ? zero : ( double )ipio2[ j ];
        }

        double q[ 20 ];
        // compute q[0],q[1],...q[jk] 
        for ( Int32 i = 0; i <= jk; i++ )
        {
            double fw = 0.0;
            for ( j = 0; j <= jx; j++ )
            {
                fw += x[ j ] * f[ jx + i - j ];
            }
            q[ i ] = fw;
        }

        Int32 jz = jk;

        Int32 iq[ 20 ];
        Int32 ih;
        Int32 n = 0;
        double z;

        bool notDone;
        do
        {
            notDone = false;
            // distill q[] into iq[] reversingly 
            z = q[ jz ];
            for ( Int32 i = 0, j = jz; j > 0; i++, j-- )
            {
                double fw = ( double )( ( int32_t )( twon24 * z ) );
                iq[ i ] = ( int32_t )( z - two24 * fw );
                z = q[ j - 1 ] + fw;
            }

            // compute n 

            // actual value of z 
            z = ScaleByN( z, q0 );
            // trim off integer >= 8 
            z -= 8.0 * Floor( z * 0.125 );
            Int32 n = ( int32_t )z;
            z -= ( double )n;
            ih = 0;
            if ( q0 > 0 )
            {
                // need iq[jz-1] to determine n 
                Int32 i = ( iq[ jz - 1 ] >> ( 24 - q0 ) );
                n += i;
                iq[ jz - 1 ] -= i << ( 24 - q0 );
                ih = iq[ jz - 1 ] >> ( 23 - q0 );
            }
            else if ( q0 == 0 )
            {
                ih = iq[ jz - 1 ] >> 23;
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
                    j = iq[ i ];
                    if ( carry == 0 )
                    {
                        if ( j != 0 )
                        {
                            carry = 1;
                            iq[ i ] = 0x1000000 - j;
                        }
                    }
                    else
                    {
                        iq[ i ] = 0xffffff - j;
                    }
                }
                if ( q0 > 0 )
                {
                    // rare case: chance is 1 in 12 
                    switch ( q0 )
                    {
                        case 1:
                            iq[ jz - 1 ] &= 0x7fffff;
                            break;
                        case 2:
                            iq[ jz - 1 ] &= 0x3fffff;
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
                    j |= iq[ i ];
                }
                if ( j == 0 )
                {
                    // need recomputation 
                    // k = no. of terms needed 
                    Int32 k = 1;
                    for ( ; iq[ jk - k ] == 0; k++ )
                    {
                        // Do nothing ...
                    }

                    for ( Int32 i = jz + 1; i <= jz + k; i++ )
                    {
                        // add q[jz+1] to q[jz+k] 
                        f[ jx + i ] = ( double )ipio2[ jv + i ];
                        double fw = 0.0;
                        for ( j = 0; j <= jx; j++ )
                        {
                            fw += x[ j ] * f[ jx + i - j ];
                        }
                        q[ i ] = fw;
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
            while ( iq[ jz ] == 0 )
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
                double fw = ( double )( ( int32_t )( twon24 * z ) );
                iq[ jz ] = ( int32_t )( z - two24 * fw );
                jz += 1; q0 += 24;
                iq[ jz ] = ( int32_t )fw;
            }
            else iq[ jz ] = ( int32_t )z;
        }

        // convert integer "bit" chunk to floating-point value 
        double fw = ScaleByN( one, q0 );
        for ( Int32 i = jz; i >= 0; i-- )
        {
            q[ i ] = fw * ( double )iq[ i ];
            fw *= twon24;
        }

        // compute PIo2[0,...,jp]*q[jz,...,0] 
        double fq[ 20 ];
        for ( Int32 i = jz; i >= 0; i-- )
        {
            fw = 0.0;
            for ( Int32 k = 0; k <= jp && k <= jz - i; k++ )
            {
                fw += PIo2[ k ] * q[ i + k ];
            }
            fq[ jz - i ] = fw;
        }

        // compress fq[] into y[] 
        fw = 0.0;
        if constexpr ( doublePrecision )
        {
            for ( Int32 i = jz; i >= 0; i-- )
            {
                fw += fq[ i ];
            }

            y[ 0 ] = ( ih == 0 ) ? fw : -fw;
            fw = fq[ 0 ] - fw;
            for ( Int32 i = 1; i <= jz; i++ )
            {
                fw += fq[ i ];
            }
            y[ 1 ] = ( ih == 0 ) ? fw : -fw;
        }
        else
        {
            for ( Int32 i = jz; i >= 0; i-- )
            {
                fw += fq[ i ];
            }
            y[ 0 ] = ( ih == 0 ) ? fw : -fw;
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
        Int32 n = ( int32_t )fn;

        double r = x - fn * pio2_1;
        // 1st round good to 85 bit 
        double w = fn * pio2_1t;


        Int32 j = ix >> 20;
        y[ 0 ] = r - w;
        UInt32 high = GetHigh32Bits<UInt32>( y[ 0 ] );
        Int32 i = j - ( ( high >> 20 ) & 0x7ff );
        if ( i > 16 )
        {
            // 2nd iteration needed, good to 118 
            double t = r;
            w = fn * pio2_2;
            r = t - w;
            w = fn * pio2_2t - ( ( t - r ) - w );
            y[ 0 ] = r - w;
            high = GetHigh32Bits<UInt32>( y[ 0 ] );
            i = j - ( ( high >> 20 ) & 0x7ff );
            if ( i > 49 )
            {
                // 3rd iteration need, 151 bits acc 
                // will cover all possible cases 
                t = r;
                w = fn * pio2_3;
                r = t - w;
                w = fn * pio2_3t - ( ( t - r ) - w );
                y[ 0 ] = r - w;
            }
        }

        y[ 1 ] = ( r - y[ 0 ] ) - w;
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
        double tx[ 3 ];
        double ty[ 2 ];
        Int32 e0, i, n;
        UInt32 low;
        // high word of x 
        Int32 hx = GetHigh32Bits<Int32>( x );

        UInt32 ix = std::bit_cast< UInt32 >( hx ) & 0x7fffffffU;

        if ( ix <= 0x3fe921fbU )
        {
            // |x| ~<= pi/4 , no need for reduction 
            y[ 0 ] = x;
            y[ 1 ] = 0;
            return 0;
        }

        if ( ix <= 0x400f6a7aU )
        {
            // |x| ~<= 5pi/4 
            if ( ( ix & 0xfffffU ) == 0x921fbU )
            {
                // |x| ~= pi/2 or 2pi/2 
                // cancellation -- use medium case 
                return RemPIo2Medium( ix, x, y );
            }
            if ( ix <= 0x4002d97cU )
            {
                // |x| ~<= 3pi/4 
                if ( hx > 0 )
                {
                    // one round good to 85 bits 
                    z = x - pio2_1;
                    y[ 0 ] = z - pio2_1t;
                    y[ 1 ] = ( z - y[ 0 ] ) - pio2_1t;
                    return 1;
                }
                else
                {
                    z = x + pio2_1;
                    y[ 0 ] = z + pio2_1t;
                    y[ 1 ] = ( z - y[ 0 ] ) + pio2_1t;
                    return -1;
                }
            }
            else
            {
                if ( hx > 0 )
                {
                    z = x - 2 * pio2_1;
                    y[ 0 ] = z - 2 * pio2_1t;
                    y[ 1 ] = ( z - y[ 0 ] ) - 2 * pio2_1t;
                    return 2;
                }
                else
                {
                    z = x + 2 * pio2_1;
                    y[ 0 ] = z + 2 * pio2_1t;
                    y[ 1 ] = ( z - y[ 0 ] ) + 2 * pio2_1t;
                    return -2;
                }
            }
        }
        if ( ix <= 0x401c463bU )
        {
            // |x| ~<= 9pi/4 
            if ( ix <= 0x4015fdbcU )
            {
                // |x| ~<= 7pi/4 
                if ( ix == 0x4012d97cU )
                {
                    // |x| ~= 3pi/2 
                    return RemPIo2Medium( ix, x, y );
                }
                if ( hx > 0 )
                {
                    z = x - 3 * pio2_1;
                    y[ 0 ] = z - 3 * pio2_1t;
                    y[ 1 ] = ( z - y[ 0 ] ) - 3 * pio2_1t;
                    return 3;
                }
                else
                {
                    z = x + 3 * pio2_1;
                    y[ 0 ] = z + 3 * pio2_1t;
                    y[ 1 ] = ( z - y[ 0 ] ) + 3 * pio2_1t;
                    return -3;
                }
            }
            else
            {
                if ( ix == 0x401921fbU )
                {
                    // |x| ~= 4pi/2 
                    return RemPIo2Medium( ix, x, y );
                }
                if ( hx > 0 )
                {
                    z = x - 4 * pio2_1;
                    y[ 0 ] = z - 4 * pio2_1t;
                    y[ 1 ] = ( z - y[ 0 ] ) - 4 * pio2_1t;
                    return 4;
                }
                else
                {
                    z = x + 4 * pio2_1;
                    y[ 0 ] = z + 4 * pio2_1t;
                    y[ 1 ] = ( z - y[ 0 ] ) + 4 * pio2_1t;
                    return -4;
                }
            }
        }
        if ( ix < 0x413921fbU )
        {
            // |x| ~< 2^20*(pi/2), medium size 
            return RemPIo2Medium( ix, x, y );
        }

        // all other (large) arguments
        if ( ix >= 0x7ff00000U )
        {
            // x is inf or NaN 
            y[ 0 ] = y[ 1 ] = x - x;
            return 0;
        }
        // set z = scalbn(|x|,ilogb(x)-23) 

        low = GetLow32Bits<Int32>( x );

        // e0 = ilogb(z)-23; 
        e0 = ( ix >> 20 ) - 1046;

        z = From32BitsTo64Bits<double>( std::bit_cast< Int32 >( ix ) - ( std::bit_cast< Int32 >( e0 << 20 ) ), low );
        for ( i = 0; i < 2; i++ )
        {
            tx[ i ] = ( double )( ( int32_t )( z ) );
            z = ( z - tx[ i ] ) * two24;
        }
        tx[ 2 ] = z;
        Int32 nx = 3;
        while ( tx[ nx - 1 ] == zero )
        {
            // skip zero term 
            nx--;
        }
        n = RemPIo2Core<true>( tx, ty, e0, nx );
        if ( hx < 0 )
        {
            y[ 0 ] = -ty[ 0 ];
            y[ 1 ] = -ty[ 1 ];
            return -n;
        }
        y[ 0 ] = ty[ 0 ];
        y[ 1 ] = ty[ 1 ];
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
        double tx[ 1 ], ty[ 1 ];
        Int32 n;

        Int32 hx = std::bit_cast< Int32 >( x );
        UInt32 ix = std::bit_cast< UInt32 >( hx ) & 0x7fffffffU;
        // 33+53 bit pi is good enough for medium size 
        if ( ix < 0x4dc90fdbU )
        {
            // |x| ~< 2^28*(pi/2), medium size
            fn = x * invpio2 + 0x1.8p52;
            fn = fn - 0x1.8p52;
            n = ( int32_t )fn;
            r = x - fn * pio2_1;
            w = fn * pio2_1t;
            *y = r - w;
            return n;
        }
        // all other (large) arguments
        if ( ix >= 0x7f800000U )
        {
            // x is inf or NaN 
            *y = x - x;
            return 0;
        }
        // set z = scalbn(|x|,ilogb(|x|)-23) 

        // e0 = ilogb(|x|)-23; 
        Int32 e0 = ( ix >> 23 ) - 150;
        float z = std::bit_cast< float >( std::bit_cast< Int32 >( ix ) - ( std::bit_cast< Int32 >( e0 << 23 ) ) );
        tx[ 0 ] = z;
        n = RemPIo2Core<false>( tx, ty, e0, 1 );
        if ( hx < 0 )
        {
            *y = -ty[ 0 ];
            return -n;
        }
        *y = ty[ 0 ];
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
        return static_cast< float >( ( x + s * ( S1 + z * S2 ) ) + s * w * r );
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
        return static_cast< float >( ( ( one + z * C0 ) + w * C1 ) + ( w * z ) * r );
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
            v = ( double )iy;
            return ( double )( 1 - ( ( hx >> 30 ) & 2 ) ) * ( v - 2.0 * ( x - ( w * w / ( w + v ) - r ) ) );
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
            return ( double )( 1 - ( ( hx >> 30 ) & 2 ) ) * ( 1.0 - 2.0 * ( x - ( w * w / ( w + 1.0 ) - r ) ) );
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
            return static_cast< float >( r );
        }
        else
        {
            return static_cast< float >( -1.0 / r );
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
        return static_cast< float >( r );
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

     /// <summary>
     /// constexpr implementation if sin.
     /// <para>
     /// This function has been tested with all valid 
     /// single precision floating point values, as double precision 
     /// point values, between -((2*pi)+epsilon) and ((2*pi)+epsilon), and
     /// 2400646 out of 2173837238 values generated a different 
     /// result than <c>std::sin</c>. The maximum deviation
     /// from <c>std::sin</c> was 1.11022e-16 for the value
     /// -5.75955.
     /// </para>
     /// </summary>
     /// <param name="x">
     /// An angle in radians to calculate the sine for.
     /// </param>
     /// <returns>
     /// The sine of the input value.
     /// </returns>
    inline constexpr double SinImpl( double x ) noexcept
    {
        // pi/4 
        constexpr double PIo4 = M_PI_4;
        double ax = std::bit_cast< double >( std::bit_cast< UInt64 >( x ) & 0x7FFFFFFFFFFFFFFFULL );

        if ( ax <= PIo4 )
        {
            // |x| < 2**-26 
            if ( ax < 0x1.0p-26 )
            {
                return x;
            }
            // generate simplified inexact 
            return SinCore( x );
        }
        else if ( std::bit_cast< UInt64 >( ax ) >= 0x7ff0000000000000ULL )
        {
            // sin(Inf or NaN) is NaN 
            return x - x;
        }
        else
        {
            // argument reduction needed 
            double y[ 2 ];
            Int32 n = RemPIo2( x, y );
            switch ( n & 3 )
            {
                case 0:
                    return  SinCore( y[ 0 ], y[ 1 ], 1 );
                case 1:
                    return  CosCore( y[ 0 ], y[ 1 ] );
                case 2:
                    return -SinCore( y[ 0 ], y[ 1 ], 1 );
                default:
                    return -CosCore( y[ 0 ], y[ 1 ] );
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

      /// <summary>
      /// constexpr implementation if sin.
      /// <para>
      /// This function has been tested with all valid 
      /// single precision floating point values between 
      /// -((2*pi)+epsilon) and ((2*pi)+epsilon), and
      /// 131312 out of 2173837238 values generated a different 
      /// result than <c>std::sin</c>. The maximum deviation
      /// from <c>std::sin</c> was 5.96046e-08 for the value
      /// -5.75846.
      /// </para>
      /// </summary>
      /// <param name="x">
      /// An angle in radians to calculate the sine for.
      /// </param>
      /// <returns>
      /// The sine of the input value.
      /// </returns>
    inline constexpr float SinImpl( float x ) noexcept
    {
        constexpr double s1pio2 = 1 * M_PI_2;
        constexpr double s2pio2 = 2 * M_PI_2;
        constexpr double s3pio2 = 3 * M_PI_2;
        constexpr double s4pio2 = 4 * M_PI_2;

        auto hx = std::bit_cast< Int32 >( x );
        UInt32 ix = std::bit_cast< UInt32 >( hx ) & 0x7fffffffU;

        if ( ix <= 0x3f490fdaU )
        {
            // |x| ~<= pi/4 
            if ( ix < 0x39800000U )
            {
                // |x| < 2**-12 
                if ( ( ( int )x ) == 0 )
                {
                    // x with inexact if x != 0 
                    return x;
                }
            }
            return SinCoreF( x );
        }
        if ( ix <= 0x407b53d1U )
        {
            // |x| ~<= 5*pi/4 
            if ( ix <= 0x4016cbe3U )
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
        if ( ix <= 0x40e231d5U )
        {
            // |x| ~<= 9*pi/4 
            if ( ix <= 0x40afeddfU )
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
        else if ( ix >= 0x7f800000U )
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
        Int32 hx = std::bit_cast< Int32 >( x );
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
        t = w * ( float )0.5;
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

     /// <summary>
     /// constexpr implementation if cos.
     /// <para>
     /// This function has been tested with all valid 
     /// single precision floating point values between 
     /// -((2*pi)+epsilon) and ((2*pi)+epsilon), and
     /// 2499716 out of 2173837238 values generated a different 
     /// result than <c>std::sin</c>. The maximum deviation
     /// from <c>std::sin</c> was 1.11022e-16 for the value
     /// -6.177.
     /// </para>
     /// </summary>
     /// <param name="x">
     /// An angle in radians to calculate the cosine for.
     /// </param>
     /// <returns>
     /// The cosine of the input value.
     /// </returns>
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
                if ( ( ( int )x ) == 0 )
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
            double y[ 2 ];
            auto n = RemPIo2( x, y );
            switch ( n & 3 )
            {
                case 0:
                    return  CosCore( y[ 0 ], y[ 1 ] );
                case 1:
                    return -SinCore( y[ 0 ], y[ 1 ], 1 );
                case 2:
                    return -CosCore( y[ 0 ], y[ 1 ] );
                default:
                    return SinCore( y[ 0 ], y[ 1 ], 1 );
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

      /// <summary>
      /// constexpr implementation if cos.
      /// <para>
      /// This function has been tested with all valid 
      /// single precision floating point values between 
      /// -((2*pi)+epsilon) and ((2*pi)+epsilon), and
      /// 166488 out of 2173837238 values generated a different 
      /// result than <c>std::sin</c>. The maximum deviation
      /// from <c>std::sin</c> was 5.96046e-08 for the value
      /// -6.24929.
      /// </para>
      /// </summary>
      /// <param name="x">
      /// An angle in radians to calculate the cosine for.
      /// </param>
      /// <returns>
      /// The cosine of the input value.
      /// </returns>
    inline constexpr float CosImpl( float x ) noexcept
    {
        constexpr double c1pio2 = 1 * M_PI_2;
        constexpr double c2pio2 = 2 * M_PI_2;
        constexpr double c3pio2 = 3 * M_PI_2;
        constexpr double c4pio2 = 4 * M_PI_2;

        auto hx = std::bit_cast< Int32 >( x );
        auto ix = hx & 0x7fffffff;

        if ( ix <= 0x3f490fda )
        {
            // |x| ~<= pi/4
            // |x| < 2**-12 
            if ( ix < 0x39800000 )
            {
                if ( ( ( int )x ) == 0 )
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
            df = std::bit_cast< double >( std::bit_cast< UInt64 >( s ) & 0xFFFFFFFF00000000 );

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
        Int32 hx = std::bit_cast< Int32 >( x );
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
                    return pi + ( float )2.0 * pio2_lo;
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
            z = ( one - x ) * ( float )0.5;
            s = Sqrt( z );
            df = s;

            idf = std::bit_cast< Int32 >( df );
            df = std::bit_cast< float >( idf & 0xfffff000 );
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
                if ( ( int )x == 0 )
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
            double y[ 2 ];
            auto n = RemPIo2( x, y );
            return TanCore( y[ 0 ], y[ 1 ], 1 - ( ( n & 1 ) << 1 ) ); //  1 -- n even -1 -- n odd 
        }
    }

    inline constexpr float TanImpl( float x ) noexcept
    {

        constexpr double t1pio2 = 1 * M_PI_2;
        constexpr double t2pio2 = 2 * M_PI_2;
        constexpr double t3pio2 = 3 * M_PI_2;
        constexpr double t4pio2 = 4 * M_PI_2;

        auto hx = std::bit_cast< Int32 >( x );

        Int32 ix = hx & 0x7fffffff;

        if ( ix <= 0x3f490fda )
        {
            // |x| ~<= pi/4 
            if ( ix < 0x39800000 )
            {
                // |x| < 2**-12 
                if ( ( ( int )x ) == 0 )
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

        Int32 hx = std::bit_cast< Int32 >( x );
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
        if ( ( ( ix | ( ( lx | -static_cast< Int32 >( lx ) ) >> 31 ) ) > 0x7ff00000 ) || ( ( iy | ( ( ly | -static_cast< Int32 >( ly ) ) >> 31 ) ) > 0x7ff00000 ) )
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

        auto hx = std::bit_cast< Int32 >( x );
        Int32 ix = hx & 0x7fffffff;
        auto hy = std::bit_cast< Int32 >( y );
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
                        return  ( float )3.0 * pi_o_4 + tiny;
                    case 3:
                        // atan(-INF,-INF)
                        return ( float )-3.0 * pi_o_4 - tiny;
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


}

#endif