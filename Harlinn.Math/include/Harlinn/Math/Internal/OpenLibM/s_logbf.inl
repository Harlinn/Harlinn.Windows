/* s_logbf.c -- float version of s_logb.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_logbf.c,v 1.9 2008/02/22 02:30:35 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace logbf_internal
	{
		constexpr float
			two25 = 3.355443200e+07;		/* 0x4c000000 */
	}

	constexpr inline float
		logbf( float x )
	{
		using namespace logbf_internal;
		int32_t ix;
		GET_FLOAT_WORD( ix, x );
		ix &= 0x7fffffff;			/* high |x| */
		if ( ix == 0 ) return ( float )-1.0 / fabsf( x );
		if ( ix >= 0x7f800000 ) return x * x;
		if ( ix < 0x00800000 )
		{
			x *= two25;		 /* convert subnormal x to normal */
			GET_FLOAT_WORD( ix, x );
			ix &= 0x7fffffff;
			return ( float )( ( ix >> 23 ) - 127 - 25 );
		}
		else
			return ( float )( ( ix >> 23 ) - 127 );
	}
}