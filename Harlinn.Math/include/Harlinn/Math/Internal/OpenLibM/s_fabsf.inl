/* s_fabsf.c -- float version of s_fabs.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_fabsf.c,v 1.8 2008/02/22 02:30:35 das Exp $");

/*
 * fabsf(x) returns the absolute value of x.
 */

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	constexpr inline float
		fabsf( float x )
	{
		//uint32_t ix;
		//GET_FLOAT_WORD( ix, x );
		//SET_FLOAT_WORD( x, ix & 0x7fffffff );
		//return x;
		return std::bit_cast< float >( std::bit_cast< UInt32 >( x ) & 0x7fffffff );
	}
}