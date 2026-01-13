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
/* s_ceilf.c -- float version of s_ceil.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_ceilf.c,v 1.8 2008/02/22 02:30:35 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace ceilf_internal
	{
		constexpr float huge = 1.0e30f;
	}

	constexpr inline float
		ceilf( float x )
	{
		using namespace ceilf_internal;
		int32_t i0, j0;
		uint32_t i;

		GET_FLOAT_WORD( i0, x );
		j0 = ( ( i0 >> 23 ) & 0xff ) - 0x7f;
		if ( j0 < 23 )
		{
			if ( j0 < 0 )
			{ 	/* raise inexact if x != 0 */
				if ( huge + x > ( float )0.0 )
				{/* return 0*sign(x) if |x|<1 */
					if ( i0 < 0 ) { i0 = 0x80000000; }
					else if ( i0 != 0 ) { i0 = 0x3f800000; }
				}
			}
			else
			{
				i = ( 0x007fffff ) >> j0;
				if ( ( i0 & i ) == 0 ) return x; /* x is integral */
				if ( huge + x > ( float )0.0 )
				{	/* raise inexact flag */
					if ( i0 > 0 ) i0 += ( 0x00800000 ) >> j0;
					i0 &= ( ~i );
				}
			}
		}
		else
		{
			if ( j0 == 0x80 ) return x + x;	/* inf or NaN */
			else return x;		/* x is integral */
		}
		SET_FLOAT_WORD( x, i0 );
		return x;
	}
}