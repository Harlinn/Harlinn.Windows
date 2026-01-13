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

#include "cdefs-compat.h"
//__FBSDID("$FreeBSD: src/lib/msun/src/e_rem_pio2f.c,v 1.32 2009/06/03 08:16:34 ed Exp $");

/* __ieee754_rem_pio2f(x,y)
 *
 * return the remainder of x rem pi/2 in *y
 * use double precision for everything except passing x
 * use __kernel_rem_pio2() for large x
 */

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace __ieee754_rem_pio2f_internal
	{
		/*
		 * invpio2:  53 bits of 2/pi
		 * pio2_1:   first  33 bit of pi/2
		 * pio2_1t:  pi/2 - pio2_1
		 */

		constexpr double
			invpio2 = 6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
			pio2_1 = 1.57079631090164184570e+00, /* 0x3FF921FB, 0x50000000 */
			pio2_1t = 1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */
	}
	constexpr inline int
		__ieee754_rem_pio2f( float x, double* y )
	{
		using namespace __ieee754_rem_pio2f_internal;
		double w, r, fn;
		double tx[ 1 ], ty[ 1 ];
		float z;
		int32_t e0, n, ix, hx;

		GET_FLOAT_WORD( hx, x );
		ix = hx & 0x7fffffff;
		/* 33+53 bit pi is good enough for medium size */
		if ( ix < 0x4dc90fdb )
		{		/* |x| ~< 2^28*(pi/2), medium size */
/* Use a specialized rint() to get fn.  Assume round-to-nearest. */
			STRICT_ASSIGN( double, fn, x * invpio2 + 0x1.8p52 );
			fn = fn - 0x1.8p52;
#ifdef HAVE_EFFICIENT_IRINT
			n = irint( fn );
#else
			n = ( int32_t )fn;
#endif
			r = x - fn * pio2_1;
			w = fn * pio2_1t;
			*y = r - w;
			return n;
		}
		/*
		 * all other (large) arguments
		 */
		if ( ix >= 0x7f800000 )
		{		/* x is inf or NaN */
			*y = x - x; return 0;
		}
		/* set z = scalbn(|x|,ilogb(|x|)-23) */
		e0 = ( ix >> 23 ) - 150;		/* e0 = ilogb(|x|)-23; */
		SET_FLOAT_WORD( z, ix - ( ( int32_t )( e0 << 23 ) ) );
		tx[ 0 ] = z;
		n = __kernel_rem_pio2( tx, ty, e0, 1, 0 );
		if ( hx < 0 ) { *y = -ty[ 0 ]; return -n; }
		*y = ty[ 0 ]; return n;
	}
}