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
/* s_tanhf.c -- float version of s_tanh.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_tanhf.c,v 1.9 2008/02/22 02:30:36 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace tanhf_internal
	{
		constexpr float one = 1.0f, two = 2.0f, tiny = 1.0e-30f, huge = 1.0e30f;
	}
	constexpr inline float
		tanhf( float x )
	{
		using namespace tanhf_internal;
		float t, z;
		int32_t jx, ix;

		GET_FLOAT_WORD( jx, x );
		ix = jx & 0x7fffffff;

		/* x is INF or NaN */
		if ( ix >= 0x7f800000 )
		{
			if ( jx >= 0 )
			{
				/* tanh(+-inf)=+-1 */
				return one / x + one;
			}
			else
			{
				/* tanh(NaN) = NaN */
				return std::numeric_limits<float>::quiet_NaN( );
				//return one / x - one;
			}
		}

		/* |x| < 9 */
		if ( ix < 0x41100000 )
		{		/* |x|<9 */
			if ( ix < 0x39800000 )
			{	/* |x|<2**-12 */
				if ( huge + x > one ) return x; /* tanh(tiny) = tiny with inexact */
			}
			if ( ix >= 0x3f800000 )
			{	/* |x|>=1  */
				t = expm1f( two * fabsf( x ) );
				z = one - two / ( t + two );
			}
			else
			{
				t = expm1f( -two * fabsf( x ) );
				z = -t / ( t + two );
			}
			/* |x| >= 9, return +-1 */
		}
		else
		{
			z = one - tiny;		/* raise inexact flag */
		}
		return ( jx >= 0 ) ? z : -z;
	}
}