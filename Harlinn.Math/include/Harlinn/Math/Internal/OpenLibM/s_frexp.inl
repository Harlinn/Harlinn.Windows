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
/* @(#)s_frexp.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_frexp.c,v 1.11 2008/02/22 02:30:35 das Exp $");

/*
 * for non-zero x
 *	x = frexp(arg,&exp);
 * return a double fp quantity x such that 0.5 <= |x| <1.0
 * and the corresponding binary exponent "exp". That is
 *	arg = x*2^exp.
 * If arg is inf, 0.0, or NaN, then frexp(arg,&exp) returns arg
 * with *exp=0.
 */

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"
namespace Harlinn::Math::Internal::OpenLibM
{
	namespace frexp_internal
	{
		constexpr double
			two54 = 1.80143985094819840000e+16; /* 0x43500000, 0x00000000 */
	}

	constexpr inline double
		frexp( double x, int* eptr )
	{
		using namespace frexp_internal;
		int32_t hx, ix, lx;
		EXTRACT_WORDS( hx, lx, x );
		ix = 0x7fffffff & hx;
		*eptr = 0;
		if ( ix >= 0x7ff00000 || ( ( ix | lx ) == 0 ) ) return x;	/* 0,inf,nan */
		if ( ix < 0x00100000 )
		{		/* subnormal */
			x *= two54;
			GET_HIGH_WORD( hx, x );
			ix = hx & 0x7fffffff;
			*eptr = -54;
		}
		*eptr += ( ix >> 20 ) - 1022;
		hx = ( hx & 0x800fffff ) | 0x3fe00000;
		SET_HIGH_WORD( x, hx );
		return x;
	}

}
