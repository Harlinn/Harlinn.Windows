/* e_atanhf.c -- float version of e_atanh.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_atanhf.c,v 1.7 2008/02/22 02:30:34 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace atanhf_internal
	{
		constexpr float one = 1.0, huge = 1e30f;

		constexpr float zero = 0.0f;
	}

	constexpr inline float
		__ieee754_atanhf( float x )
	{
		using namespace atanhf_internal;
		float t;
		int32_t hx, ix;
		GET_FLOAT_WORD( hx, x );
		ix = hx & 0x7fffffff;
		if ( ix > 0x3f800000 )
		{
			/* |x|>1 */
			return std::numeric_limits<float>::quiet_NaN( );
			//return ( x - x ) / ( x - x );
		}
		if ( ix == 0x3f800000 )
		{
			return CopySign( std::numeric_limits<float>::infinity( ), x );
			//return x / zero;
		}
		if ( ix<0x31800000 && ( huge + x ) > 0.0f ) return x;	/* x<2**-28 */
		SET_FLOAT_WORD( x, ix );
		if ( ix < 0x3f000000 )
		{		/* x < 0.5 */
			t = x + x;
			t = ( float )0.5 * Log1P( t + t * x / ( one - x ) );
		}
		else
			t = ( float )0.5 * Log1P( ( x + x ) / ( one - x ) );
		if ( hx >= 0 ) return t; else return -t;
	}
}