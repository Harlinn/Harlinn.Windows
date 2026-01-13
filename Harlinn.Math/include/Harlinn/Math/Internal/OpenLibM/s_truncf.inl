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
/* @(#)s_floor.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_truncf.c,v 1.1 2004/06/20 09:25:43 das Exp $");

/*
 * truncf(x)
 * Return x rounded toward 0 to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to truncf(x).
 */

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace truncf_internal
	{
		constexpr float huge = 1.0e30F;
	}

	constexpr inline float
		truncf( float x )
	{
		using namespace truncf_internal;
		int32_t i0, j0;
		uint32_t i;
		GET_FLOAT_WORD( i0, x );
		j0 = ( ( i0 >> 23 ) & 0xff ) - 0x7f;
		if ( j0 < 23 )
		{
			if ( j0 < 0 )
			{ 	/* raise inexact if x != 0 */
				if ( huge + x > 0.0F )		/* |x|<1, so return 0*sign(x) */
					i0 &= 0x80000000;
			}
			else
			{
				i = ( 0x007fffff ) >> j0;
				if ( ( i0 & i ) == 0 ) return x; /* x is integral */
				if ( huge + x > 0.0F )		/* raise inexact flag */
					i0 &= ( ~i );
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