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
/* s_asinhf.c -- float version of s_asinh.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_asinhf.c,v 1.9 2008/02/22 02:30:35 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{

	namespace asinhf_internal
	{
		constexpr float
			one = 1.0000000000e+00f, /* 0x3F800000 */
			ln2 = 6.9314718246e-01f, /* 0x3f317218 */
			huge = 1.0000000000e+30f;
	}
	constexpr inline float
		asinhf( float x )
	{
		using namespace asinhf_internal;
		float t, w;
		int32_t hx, ix;
		GET_FLOAT_WORD( hx, x );
		ix = hx & 0x7fffffff;
		if ( ix >= 0x7f800000 ) return x + x;	/* x is inf or NaN */
		if ( ix < 0x31800000 )
		{	/* |x|<2**-28 */
			if ( huge + x > one ) return x;	/* return x inexact except 0 */
		}
		if ( ix > 0x4d800000 )
		{	/* |x| > 2**28 */
			w = Log( Abs( x ) ) + ln2;
		}
		else if ( ix > 0x40000000 )
		{	/* 2**28 > |x| > 2.0 */
			t = Abs( x );
			w = Log( ( float )2.0 * t + one / ( Sqrt( x * x + one ) + t ) );
		}
		else
		{		/* 2.0 > |x| > 2**-28 */
			t = x * x;
			w = Log1P( Abs( x ) + t / ( one + Sqrt( one + t ) ) );
		}
		if ( hx > 0 ) return w; else return -w;
	}
}