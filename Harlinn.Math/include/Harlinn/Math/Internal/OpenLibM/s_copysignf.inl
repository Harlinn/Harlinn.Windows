/* s_copysignf.c -- float version of s_copysign.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_copysignf.c,v 1.10 2008/02/22 02:30:35 das Exp $");

/*
 * copysignf(float x, float y)
 * copysignf(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 */

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{

	constexpr inline float
		copysignf( float x, float y )
	{
		uint32_t ix, iy;
		GET_FLOAT_WORD( ix, x );
		GET_FLOAT_WORD( iy, y );
		SET_FLOAT_WORD( x, ( ix & 0x7fffffff ) | ( iy & 0x80000000 ) );
		return x;
	}

}