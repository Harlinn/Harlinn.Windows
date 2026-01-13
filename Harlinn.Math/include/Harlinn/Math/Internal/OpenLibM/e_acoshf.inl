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
/* e_acoshf.c -- float version of e_acosh.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_acoshf.c,v 1.8 2008/02/22 02:30:34 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace acoshf_internal
	{
		constexpr float
			one = 1.0f,
			ln2 = 6.9314718246e-01f;  /* 0x3f317218 */
	}

	constexpr inline float
		__ieee754_acoshf( float x )
	{
		using namespace acoshf_internal;
		float t;
		int32_t hx;
		GET_FLOAT_WORD( hx, x );
		if ( hx < 0x3f800000 )
		{	
			/* x < 1 */
			return std::numeric_limits<float>::quiet_NaN( );
			//return ( x - x ) / ( x - x );
		}
		else if ( hx >= 0x4d800000 )
		{	/* x > 2**28 */
			if ( hx >= 0x7f800000 )
			{	/* x is inf of NaN */
				return x + x;
			}
			else
				return Log( x ) + ln2;	/* acosh(huge)=log(2x) */
		}
		else if ( hx == 0x3f800000 )
		{
			return 0.0;			/* acosh(1) = 0 */
		}
		else if ( hx > 0x40000000 )
		{	/* 2**28 > x > 2 */
			t = x * x;
			return Log( ( float )2.0 * x - one / ( x + Sqrt( t - one ) ) );
		}
		else
		{			/* 1<x<2 */
			t = x - one;
			return Log1P( t + Sqrt( ( float )2.0 * t + t * t ) );
		}
	}
}