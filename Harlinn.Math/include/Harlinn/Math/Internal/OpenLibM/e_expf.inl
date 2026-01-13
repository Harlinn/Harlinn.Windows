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

#include "cdefs-compat.h"
//__FBSDID("$FreeBSD: src/lib/msun/src/e_expf.c,v 1.16 2011/10/21 06:26:38 das Exp $");

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace expf_internal
	{
		constexpr float
			one = 1.0f,
			halF[ 2 ] = { 0.5f,-0.5f, },
			huge = 1.0e+30f,
			o_threshold = 8.8721679688e+01f,  /* 0x42b17180 */
			u_threshold = -1.0397208405e+02f,  /* 0xc2cff1b5 */
			ln2HI[ 2 ] = { 6.9314575195e-01f,		/* 0x3f317200 */
					 -6.9314575195e-01f, },	/* 0xbf317200 */
			ln2LO[ 2 ] = { 1.4286067653e-06f,  	/* 0x35bfbe8e */
					 -1.4286067653e-06f, },	/* 0xb5bfbe8e */
			invln2 = 1.4426950216e+00f, 		/* 0x3fb8aa3b */
			/*
			 * Domain [-0.34568, 0.34568], range ~[-4.278e-9, 4.447e-9]:
			 * |x*(exp(x)+1)/(exp(x)-1) - p(x)| < 2**-27.74
			 */
			P1 = 1.6666625440e-1f,		/*  0xaaaa8f.0p-26 */
			P2 = -2.7667332906e-3f;		/* -0xb55215.0p-32 */

		constexpr float twom100 = 7.8886090522e-31f;      /* 2**-100=0x0d800000 */
	}

	

	constexpr inline float
		__ieee754_expf( float x )
	{
		using namespace expf_internal;
		float y, hi = 0.0, lo = 0.0, c, t, twopk;
		int32_t k = 0, xsb;
		uint32_t hx;

		GET_FLOAT_WORD( hx, x );
		xsb = ( hx >> 31 ) & 1;		/* sign bit of x */
		hx &= 0x7fffffff;		/* high word of |x| */

		/* filter out non-finite argument */
		if ( hx >= 0x42b17218 )
		{			/* if |x|>=88.721... */
			if ( hx > 0x7f800000 )
				return x + x;	 		/* NaN */
			if ( hx == 0x7f800000 )
				return ( xsb == 0 ) ? x : 0.0f;		/* exp(+-inf)={inf,0} */
			if ( x > o_threshold )
			{
#pragma warning(push)
#pragma warning(disable:4056)
				return huge * huge; /* overflow */
#pragma warning(pop)
			}
			if ( x < u_threshold ) return twom100 * twom100; /* underflow */
		}

		/* argument reduction */
		if ( hx > 0x3eb17218 )
		{		/* if  |x| > 0.5 ln2 */
			if ( hx < 0x3F851592 )
			{	/* and |x| < 1.5 ln2 */
				hi = x - ln2HI[ xsb ]; lo = ln2LO[ xsb ]; k = 1 - xsb - xsb;
			}
			else
			{
				k = static_cast< int32_t >( invln2 * x + halF[ xsb ] );
				t = static_cast< float >( k );
				hi = x - t * ln2HI[ 0 ];	/* t*ln2HI is exact here */
				lo = t * ln2LO[ 0 ];
			}
			STRICT_ASSIGN( float, x, hi - lo );
		}
		else if ( hx < 0x39000000 )
		{	/* when |x|<2**-14 */
			if ( huge + x > one ) return one + x;/* trigger inexact */
		}
		else k = 0;

		/* x is now in primary range */
		t = x * x;
		if ( k >= -125 )
			SET_FLOAT_WORD( twopk, 0x3f800000U + ( std::bit_cast<uint32_t>( k ) << 23 ) );
		else
			SET_FLOAT_WORD( twopk, 0x3f800000U + ( ( std::bit_cast<uint32_t>( k ) + 100 ) << 23 ) );
		c = x - t * ( P1 + t * P2 );
		if ( k == 0 ) 	return one - ( ( x * c ) / ( c - static_cast< float >( 2.0 ) ) - x );
		else 		y = one - ( ( lo - ( x * c ) / ( static_cast< float >( 2.0 ) - c ) ) - hi );
		if ( k >= -125 )
		{
			if ( k == 128 ) return y * 2.0F * 0x1p127F;
			return y * twopk;
		}
		else
		{
			return y * twopk * twom100;
		}
	}
}