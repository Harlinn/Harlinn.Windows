/* @(#)s_asinh.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_asinh.c,v 1.9 2008/02/22 02:30:35 das Exp $");

/* asinh(x)
 * Method :
 *	Based on
 *		asinh(x) = sign(x) * log [ |x| + sqrt(x*x+1) ]
 *	we have
 *	asinh(x) := x  if  1+x*x=1,
 *		 := sign(x)*(log(x)+ln2)) for large |x|, else
 *		 := sign(x)*log(2|x|+1/(|x|+sqrt(x*x+1))) if|x|>2, else
 *		 := sign(x)*log1p(|x| + x^2/(1 + sqrt(1+x^2)))
 */

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace asinh_internal
	{
		constexpr double
			one = 1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
			ln2 = 6.93147180559945286227e-01, /* 0x3FE62E42, 0xFEFA39EF */
			huge = 1.00000000000000000000e+300;
	}
	constexpr inline double
		asinh( double x )
	{
		using namespace asinh_internal;
		double t, w;
		int32_t hx, ix;
		GET_HIGH_WORD( hx, x );
		ix = hx & 0x7fffffff;
		if ( ix >= 0x7ff00000 ) return x + x;	/* x is inf or NaN */
		if ( ix < 0x3e300000 )
		{	/* |x|<2**-28 */
			if ( huge + x > one ) return x;	/* return x inexact except 0 */
		}
		if ( ix > 0x41b00000 )
		{	/* |x| > 2**28 */
			w = Log( Abs( x ) ) + ln2;
		}
		else if ( ix > 0x40000000 )
		{	/* 2**28 > |x| > 2.0 */
			t = Abs( x );
			w = Log( 2.0 * t + one / ( Sqrt( x * x + one ) + t ) );
		}
		else
		{		/* 2.0 > |x| > 2**-28 */
			t = x * x;
			w = Log1P( Abs( x ) + t / ( one + Sqrt( one + t ) ) );
		}
		if ( hx > 0 ) return w; else return -w;
	}

}
