/* @(#)s_tanh.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_tanh.c,v 1.9 2008/02/22 02:30:36 das Exp $");

/* Tanh(x)
 * Return the Hyperbolic Tangent of x
 *
 * Method :
 *				       x    -x
 *				      e  - e
 *	0. tanh(x) is defined to be -----------
 *				       x    -x
 *				      e  + e
 *	1. reduce x to non-negative by tanh(-x) = -tanh(x).
 *	2.  0      <= x <  2**-28 : tanh(x) := x with inexact if x != 0
 *					        -t
 *	    2**-28 <= x <  1      : tanh(x) := -----; t = expm1(-2x)
 *					       t + 2
 *						     2
 *	    1      <= x <  22     : tanh(x) := 1 - -----; t = expm1(2x)
 *						   t + 2
 *	    22     <= x <= INF    : tanh(x) := 1.
 *
 * Special cases:
 *	tanh(NaN) is NaN;
 *	only tanh(0)=0 is exact for finite argument.
 */

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace tanh_internal
	{
		constexpr double one = 1.0, two = 2.0, tiny = 1.0e-300, huge = 1.0e300;
	}

	constexpr inline double
		tanh( double x )
	{
		using namespace tanh_internal;
		double t, z;
		int32_t jx, ix;

		GET_HIGH_WORD( jx, x );
		ix = jx & 0x7fffffff;

		/* x is INF or NaN */
		if ( ix >= 0x7ff00000 )
		{
			if ( jx >= 0 )
			{
				/* tanh(+-inf)=+-1 */
				return one / x + one;
			}
			else
			{
				/* tanh(NaN) = NaN */
				return std::numeric_limits<double>::quiet_NaN( );
				//return one / x - one;
			}
		}

		/* |x| < 22 */
		if ( ix < 0x40360000 )
		{		/* |x|<22 */
			if ( ix < 0x3e300000 )
			{	/* |x|<2**-28 */
				if ( huge + x > one ) return x; /* tanh(tiny) = tiny with inexact */
			}
			if ( ix >= 0x3ff00000 )
			{	/* |x|>=1  */
				t = expm1( two * fabs( x ) );
				z = one - two / ( t + two );
			}
			else
			{
				t = expm1( -two * fabs( x ) );
				z = -t / ( t + two );
			}
			/* |x| >= 22, return +-1 */
		}
		else
		{
			z = one - tiny;		/* raise inexact flag */
		}
		return ( jx >= 0 ) ? z : -z;
	}

}
