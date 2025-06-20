/* s_rintf.c -- float version of s_rint.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_rintf.c,v 1.12 2008/02/22 02:30:35 das Exp $");

#include <float.h>
#include "openlibm_math.h"
#include <stdint.h>

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace rintf_internal
	{
		constexpr float
			TWO23[ 2 ] = {
			  8.3886080000e+06f, /* 0x4b000000 */
			 -8.3886080000e+06f, /* 0xcb000000 */
		};
	}

	constexpr inline float
		rintf( float x )
	{
		using namespace rintf_internal;
		int32_t i0, j0, sx;
		float w, t;
		GET_FLOAT_WORD( i0, x );
		sx = ( i0 >> 31 ) & 1;
		j0 = ( ( i0 >> 23 ) & 0xff ) - 0x7f;
		if ( j0 < 23 )
		{
			if ( j0 < 0 )
			{
				if ( ( i0 & 0x7fffffff ) == 0 ) return x;
				STRICT_ASSIGN( float, w, TWO23[ sx ] + x );
				t = w - TWO23[ sx ];
				GET_FLOAT_WORD( i0, t );
				SET_FLOAT_WORD( t, ( i0 & 0x7fffffff ) | ( sx << 31 ) );
				return t;
			}
			STRICT_ASSIGN( float, w, TWO23[ sx ] + x );
			return w - TWO23[ sx ];
		}
		if ( j0 == 0x80 ) return x + x;	/* inf or NaN */
		else return x;			/* x is integral */
	}
}