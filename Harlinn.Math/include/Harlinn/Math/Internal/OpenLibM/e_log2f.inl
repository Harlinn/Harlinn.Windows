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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_log2f.c,v 1.5 2011/10/15 05:23:28 das Exp $");

/*
 * Float version of e_log2.c.  See the latter for most comments.
 */

#include "openlibm_math.h"

#include "math_private.h"
#include "k_logf.h"


namespace Harlinn::Math::Internal::OpenLibM
{
	// VBS
#define float_t float

	namespace log2f_internal
	{
		constexpr float
			two25 = 3.3554432000e+07f, /* 0x4c000000 */
			ivln2hi = 1.4428710938e+00f, /* 0x3fb8b000 */
			ivln2lo = -1.7605285393e-04f; /* 0xb9389ad4 */

		constexpr float zero = 0.0f;
	}

	constexpr inline float
		__ieee754_log2f( float x )
	{
		using namespace log2f_internal;
		float f, hfsq, hi, lo, r, y;
		int32_t i, k, hx;

		GET_FLOAT_WORD( hx, x );

		k = 0;
		if ( hx < 0x00800000 )
		{			/* x < 2**-126  */
			if ( ( hx & 0x7fffffff ) == 0 )
			{
				return -std::numeric_limits<float>::infinity( );
				//return -two25 / zero;		/* log(+-0)=-inf */
			}
			if ( hx < 0 )
			{
				return std::numeric_limits<float>::quiet_NaN( );
				//return ( x - x ) / zero;	/* log(-#) = NaN */
			}
			k -= 25; x *= two25; /* subnormal number, scale up x */
			GET_FLOAT_WORD( hx, x );
		}
		if ( hx >= 0x7f800000 ) return x + x;
		if ( hx == 0x3f800000 )
			return 0.f;			/* log(1) = +0 */
		k += ( hx >> 23 ) - 127;
		hx &= 0x007fffff;
		i = ( hx + ( 0x4afb0d ) ) & 0x800000;
		SET_FLOAT_WORD( x, hx | ( i ^ 0x3f800000 ) );	/* normalize x or x/2 */
		k += ( i >> 23 );
		y = ( float )k;
		f = x - ( float )1.0;
		hfsq = ( float )0.5 * f * f;
		r = k_log1pf( f );

		/*
		 * We no longer need to avoid falling into the multi-precision
		 * calculations due to compiler bugs breaking Dekker's theorem.
		 * Keep avoiding this as an optimization.  See e_log2.c for more
		 * details (some details are here only because the optimization
		 * is not yet available in double precision).
		 *
		 * Another compiler bug turned up.  With gcc on i386,
		 * (ivln2lo + ivln2hi) would be evaluated in float precision
		 * despite runtime evaluations using double precision.  So we
		 * must cast one of its terms to float_t.  This makes the whole
		 * expression have type float_t, so return is forced to waste
		 * time clobbering its extra precision.
		 */
		if ( sizeof( float_t ) > sizeof( float ) )
			return ( r - hfsq + f ) * ( ( float_t )ivln2lo + ivln2hi ) + y;

		hi = f - hfsq;
		GET_FLOAT_WORD( hx, hi );
		SET_FLOAT_WORD( hi, hx & 0xfffff000 );
		lo = ( f - hi ) - hfsq + r;
		return ( lo + hi ) * ivln2lo + lo * ivln2hi + hi * ivln2hi + y;
	}
}