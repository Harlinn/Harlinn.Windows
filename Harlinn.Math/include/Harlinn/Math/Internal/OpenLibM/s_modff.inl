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
/* s_modff.c -- float version of s_modf.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_modff.c,v 1.9 2008/02/22 02:30:35 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace modff_internal
	{
		constexpr float one = 1.0f;
	}

	constexpr inline float
		modff( float x, float* iptr )
	{
		using namespace modff_internal;
		int32_t i0, j0;
		uint32_t i;
		GET_FLOAT_WORD( i0, x );
		j0 = ( ( i0 >> 23 ) & 0xff ) - 0x7f;	/* exponent of x */
		if ( j0 < 23 )
		{			/* integer part in x */
			if ( j0 < 0 )
			{			/* |x|<1 */
				SET_FLOAT_WORD( *iptr, i0 & 0x80000000 );	/* *iptr = +-0 */
				return x;
			}
			else
			{
				i = ( 0x007fffff ) >> j0;
				if ( ( i0 & i ) == 0 )
				{			/* x is integral */
					uint32_t ix;
					*iptr = x;
					GET_FLOAT_WORD( ix, x );
					SET_FLOAT_WORD( x, ix & 0x80000000 );	/* return +-0 */
					return x;
				}
				else
				{
					SET_FLOAT_WORD( *iptr, i0 & ( ~i ) );
					return x - *iptr;
				}
			}
		}
		else
		{			/* no fraction part */
			uint32_t ix;
			*iptr = x * one;
			if ( x != x )			/* NaN */
				return x;
			GET_FLOAT_WORD( ix, x );
			SET_FLOAT_WORD( x, ix & 0x80000000 );	/* return +-0 */
			return x;
		}
	}
}