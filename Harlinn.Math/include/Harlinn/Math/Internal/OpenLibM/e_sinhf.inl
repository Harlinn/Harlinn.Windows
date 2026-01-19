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
/* e_sinhf.c -- float version of e_sinh.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_sinhf.c,v 1.10 2011/10/21 06:28:47 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace sinhf_internal
	{
		constexpr float one = 1.0f, shuge = 1.0e37f;
	}

	constexpr inline float
		__ieee754_sinhf( float x )
	{
		using namespace sinhf_internal;
		float t, h;
		int32_t ix, jx;

		GET_FLOAT_WORD( jx, x );
		ix = jx & 0x7fffffff;

		/* x is INF or NaN */
		if ( ix >= 0x7f800000 ) return x + x;

		h = 0.5;
		if ( jx < 0 ) h = -h;
		/* |x| in [0,9], return sign(x)*0.5*(E+E/(E+1))) */
		if ( ix < 0x41100000 )
		{		/* |x|<9 */
			if ( ix < 0x39800000 ) 		/* |x|<2**-12 */
				if ( shuge + x > one ) return x;/* sinh(tiny) = tiny with inexact */
			t = ExpM1( FastAbs( x ) );
			if ( ix < 0x3f800000 ) return h * ( ( float )2.0 * t - t * t / ( t + one ) );
			return h * ( t + t / ( t + one ) );
		}

		/* |x| in [9, logf(maxfloat)] return 0.5*exp(|x|) */
		if ( ix < 0x42b17217 )  return h * Exp( FastAbs( x ) );

		/* |x| in [logf(maxfloat), overflowthresold] */
		if ( ix <= 0x42b2d4fc )
			return h * 2.0F * __ldexp_expf( FastAbs( x ), -1 );

		/* |x| > overflowthresold, sinh(x) overflow */
		return x * shuge;
	}
}