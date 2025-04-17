/* e_coshf.c -- float version of e_cosh.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_coshf.c,v 1.9 2011/10/21 06:28:47 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"
namespace Harlinn::Common::Core::Math::Internal::OpenLibM
{
	namespace coshf_internal
	{
		constexpr float one = 1.0f, half = 0.5f, huge = 1.0e30f;
	}

	constexpr inline float
		__ieee754_coshf( float x )
	{
		using namespace coshf_internal;
		float t, w;
		int32_t ix;

		GET_FLOAT_WORD( ix, x );
		ix &= 0x7fffffff;

		/* x is INF or NaN */
		if ( ix >= 0x7f800000 ) return x * x;

		/* |x| in [0,0.5*ln2], return 1+expm1(|x|)^2/(2*exp(|x|)) */
		if ( ix < 0x3eb17218 )
		{
			t = ExpM1( FastAbs( x ) );
			w = one + t;
			if ( ix < 0x39800000 ) return one;	/* cosh(tiny) = 1 */
			return one + ( t * t ) / ( w + w );
		}

		/* |x| in [0.5*ln2,9], return (exp(|x|)+1/exp(|x|))/2; */
		if ( ix < 0x41100000 )
		{
			t = Exp( FastAbs( x ) );
			return half * t + half / t;
		}

		/* |x| in [9, log(maxfloat)] return half*exp(|x|) */
		if ( ix < 0x42b17217 )  return half * Exp( FastAbs( x ) );

		/* |x| in [log(maxfloat), overflowthresold] */
		if ( ix <= 0x42b2d4fc )
			return __ldexp_expf( FastAbs( x ), -1 );

		/* |x| > overflowthresold, cosh(x) overflow */
#pragma warning( push )
#pragma warning( disable : 4056 )
		return huge * huge;
#pragma warning( pop )
	}
}