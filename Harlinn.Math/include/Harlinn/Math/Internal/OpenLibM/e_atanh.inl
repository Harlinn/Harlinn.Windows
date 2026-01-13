
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
/* @(#)e_atanh.c 1.3 95/01/18 */
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

#include "cdefs-compat.h"
//__FBSDID("$FreeBSD: src/lib/msun/src/e_atanh.c,v 1.8 2008/02/22 02:30:34 das Exp $");

/* __ieee754_atanh(x)
 * Method :
 *    1.Reduced x to positive by atanh(-x) = -atanh(x)
 *    2.For x>=0.5
 *                  1              2x                          x
 *	atanh(x) = --- * log(1 + -------) = 0.5 * log1p(2 * --------)
 *                  2             1 - x                      1 - x
 *	
 * 	For x<0.5
 *	atanh(x) = 0.5*log1p(2x+2x*x/(1-x))
 *
 * Special cases:
 *	atanh(x) is NaN if |x| > 1 with signal;
 *	atanh(NaN) is that NaN with no signal;
 *	atanh(+-1) is +-INF with signal.
 *
 */

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace atanh_internal
	{
		constexpr double one = 1.0, huge = 1e300;
		constexpr double zero = 0.0;
	}

	constexpr inline double
		__ieee754_atanh( double x )
	{
		using namespace atanh_internal;
		double t;
		int32_t hx, ix;
		uint32_t lx;
		EXTRACT_WORDS( hx, lx, x );
		ix = hx & 0x7fffffff;
		if ( ( ix | ( ( lx | ( Negate( lx ) ) ) >> 31 ) ) > 0x3ff00000 )
		{
			/* |x|>1 */
			return std::numeric_limits<double>::quiet_NaN( );
			//return ( x - x ) / ( x - x );
		}
		if ( ix == 0x3ff00000 )
		{
			return CopySign( std::numeric_limits<double>::infinity( ), x );
			//return x / zero;
		}
		if ( ix<0x3e300000 && ( huge + x ) > 0.0 ) return x;	/* x<2**-28 */
		SET_HIGH_WORD( x, ix );
		if ( ix < 0x3fe00000 )
		{		/* x < 0.5 */
			t = x + x;
			t = 0.5 * Log1P( t + t * x / ( one - x ) );
		}
		else
			t = 0.5 * Log1P( ( x + x ) / ( one - x ) );
		if ( hx >= 0 ) return t; else return -t;
	}

}
