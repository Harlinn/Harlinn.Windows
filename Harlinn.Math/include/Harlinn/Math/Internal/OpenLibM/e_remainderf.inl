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
/* e_remainderf.c -- float version of e_remainder.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_remainderf.c,v 1.8 2008/02/12 17:11:36 bde Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace remainderf_internal
	{
		constexpr float zero = 0.0f;
	}


	constexpr inline float
		__ieee754_remainderf( float x, float p )
	{
		using namespace remainderf_internal;
		int32_t hx, hp;
		uint32_t sx;
		float p_half;

		GET_FLOAT_WORD( hx, x );
		GET_FLOAT_WORD( hp, p );
		sx = hx & 0x80000000;
		hp &= 0x7fffffff;
		hx &= 0x7fffffff;

		/* purge off exception values */
		if ( hp == 0 )
		{
			/* p = 0 */
			return std::numeric_limits<float>::quiet_NaN( );
			//return ( x * p ) / ( x * p );
		}
		if ( ( hx >= 0x7f800000 ) ||			/* x not finite */
			( ( hp > 0x7f800000 ) ) )			/* p is NaN */
			return static_cast<float>(( ( long double )x * p ) / ( ( long double )x * p ));


		if ( hp <= 0x7effffff ) x = __ieee754_fmodf( x, p + p );	/* now x < 2p */
		if ( ( hx - hp ) == 0 ) return 0.f * x;
		x = FastAbs( x );
		p = FastAbs( p );
		if ( hp < 0x01000000 )
		{
			if ( x + x > p )
			{
				x -= p;
				if ( x + x >= p ) x -= p;
			}
		}
		else
		{
			p_half = ( float )0.5 * p;
			if ( x > p_half )
			{
				x -= p;
				if ( x >= p_half ) x -= p;
			}
		}
		GET_FLOAT_WORD( hx, x );
		if ( ( hx & 0x7fffffff ) == 0 ) hx = 0;
		SET_FLOAT_WORD( x, hx ^ sx );
		return x;
	}
}