#pragma once
#ifndef HARLINN_COMMON_CORE_INTERNAL_MATH_SQRT_INL_
#define HARLINN_COMMON_CORE_INTERNAL_MATH_SQRT_INL_
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
    inline constexpr double SqrtImpl( double x )
    {
        constexpr double one = 1.0;
        constexpr double tiny = 1.0e-300;
        constexpr Int32 sign = 0x80000000;
        double z;

        Int32 s0, q, m, t, i;
        UInt32 r, t1, s1, q1;

        Int64 ax = std::bit_cast< Int64 >( x );
        Int32 ix0 = static_cast< Int32 >( ax >> 32 );
        UInt32 ix1 = static_cast< UInt32 >( ax );

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
                if ( q1 == ( UInt32 )0xffffffff )
                {
                    q1 = 0;
                    q += 1;
                }
                else if ( z > one )
                {
                    if ( q1 == ( UInt32 )0xfffffffe )
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
        z = std::bit_cast< double >( ( static_cast< UInt64 >( ix0 ) << 32 ) + static_cast< UInt64 >( ix1 ) );
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
        constexpr Int32 sign = ( int )0x80000000;

        float z;
        Int32 ix, s, q, m, t, i;
        UInt32 r;

        ix = std::bit_cast< Int32 >( x );

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
        z = std::bit_cast< float >( ix );
        return z;
    }
}
#endif
