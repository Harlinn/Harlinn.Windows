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
/* @(#)s_logb.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_logb.c,v 1.12 2008/02/08 01:22:13 bde Exp $");

/*
 * double logb(x)
 * IEEE 754 logb. Included to pass IEEE test suite. Not recommend.
 * Use ilogb instead.
 */

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace logb_internal
	{
		constexpr double
			two54 = 1.80143985094819840000e+16;	/* 43500000 00000000 */
	}

	constexpr inline double
		logb( double x )
	{
		using namespace logb_internal;
		int32_t lx, ix;
		EXTRACT_WORDS( ix, lx, x );
		ix &= 0x7fffffff;			/* high |x| */
		if ( ( ix | lx ) == 0 ) return -1.0 / fabs( x );
		if ( ix >= 0x7ff00000 ) return x * x;
		if ( ix < 0x00100000 )
		{
			x *= two54;		 /* convert subnormal x to normal */
			GET_HIGH_WORD( ix, x );
			ix &= 0x7fffffff;
			return ( double )( ( ix >> 20 ) - 1023 - 54 );
		}
		else
			return ( double )( ( ix >> 20 ) - 1023 );
	}

}
