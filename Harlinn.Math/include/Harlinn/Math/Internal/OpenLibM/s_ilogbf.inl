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
/* s_ilogbf.c -- float version of s_ilogb.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_ilogbf.c,v 1.8 2008/02/22 02:30:35 das Exp $");

#include <limits.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	constexpr inline int
		ilogbf( float x )
	{
		int32_t hx, ix;

		GET_FLOAT_WORD( hx, x );
		hx &= 0x7fffffff;
		if ( hx < 0x00800000 )
		{
			if ( hx == 0 )
				return FP_ILOGB0;
			else			/* subnormal x */
				for ( ix = -126, hx <<= 8; hx > 0; hx <<= 1 ) ix -= 1;
			return ix;
		}
		else if ( hx < 0x7f800000 ) return ( hx >> 23 ) - 127;
		else if ( hx > 0x7f800000 ) return FP_ILOGBNAN;
		else return INT_MAX;
	}
}