
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
/* @(#)e_remainder.c 1.3 95/01/18 */
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

#include "cdefs-compat.h"
//__FBSDID("$FreeBSD: src/lib/msun/src/e_remainder.c,v 1.12 2008/03/30 20:47:42 das Exp $");

/* __ieee754_remainder(x,p)
 * Return :                  
 * 	returns  x REM p  =  x - [x/p]*p as if in infinite 
 * 	precise arithmetic, where [x/p] is the (infinite bit) 
 *	integer nearest x/p (in half way case choose the even one).
 * Method : 
 *	Based on fmod() return x-[x/p]chopped*p exactlp.
 */

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace remainder_internal
	{
		constexpr double zero = 0.0;
	}

	constexpr inline double
		__ieee754_remainder( double x, double p )
	{
		using namespace remainder_internal;
		int32_t hx, hp;
		uint32_t sx, lx, lp;
		double p_half;

		EXTRACT_WORDS( hx, lx, x );
		EXTRACT_WORDS( hp, lp, p );
		sx = hx & 0x80000000;
		hp &= 0x7fffffff;
		hx &= 0x7fffffff;

		/* purge off exception values */
		if ( ( hp | lp ) == 0 )
		{
			/* p = 0 */
			return std::numeric_limits<double>::quiet_NaN( );
			//return ( x * p ) / ( x * p );
		}
		if ( ( hx >= 0x7ff00000 ) ||			/* x not finite */
			( ( hp >= 0x7ff00000 ) &&			/* p is NaN */
				( ( ( hp - 0x7ff00000 ) | lp ) != 0 ) ) )
			return ( ( long double )x * p ) / ( ( long double )x * p );


		if ( hp <= 0x7fdfffff ) x = __ieee754_fmod( x, p + p );	/* now x < 2p */
		if ( ( ( hx - hp ) | ( lx - lp ) ) == 0 ) return 0. * x;
		x = fabs( x );
		p = fabs( p );
		if ( hp < 0x00200000 )
		{
			if ( x + x > p )
			{
				x -= p;
				if ( x + x >= p ) x -= p;
			}
		}
		else
		{
			p_half = 0.5 * p;
			if ( x > p_half )
			{
				x -= p;
				if ( x >= p_half ) x -= p;
			}
		}
		GET_HIGH_WORD( hx, x );
		if ( ( hx & 0x7fffffff ) == 0 ) hx = 0;
		SET_HIGH_WORD( x, hx ^ sx );
		return x;
	}

}
