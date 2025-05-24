/* e_asinf.c -- float version of e_asin.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_asinf.c,v 1.13 2008/08/08 00:21:27 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Common::Core::Math::Internal::OpenLibM
{
	namespace asinf_internal
	{
		constexpr float
			one = 1.0000000000e+00f, /* 0x3F800000 */
			huge = 1.000e+30f,
			/* coefficient for R(x^2) */
			pS0 = 1.6666586697e-01f,
			pS1 = -4.2743422091e-02f,
			pS2 = -8.6563630030e-03f,
			qS1 = -7.0662963390e-01f;

		constexpr double
			pio2 = 1.570796326794896558e+00;
		constexpr float
			pio2f = 1.570796326794896558e+00f;
	}

	

	constexpr inline float
		__ieee754_asinf( float x )
	{
		using namespace asinf_internal;
		double s;
		float t, w, p, q;
		int32_t hx, ix;
		GET_FLOAT_WORD( hx, x );
		ix = hx & 0x7fffffff;
		if ( ix >= 0x3f800000 )
		{		/* |x| >= 1 */
			if ( ix == 0x3f800000 )		/* |x| == 1 */
			{
				return x * pio2f;		/* asin(+-1) = +-pi/2 with inexact */
			}
			return ( x - x ) / ( x - x );		/* asin(|x|>1) is NaN */
		}
		else if ( ix < 0x3f000000 )
		{	/* |x|<0.5 */
			if ( ix < 0x39800000 )
			{		/* |x| < 2**-12 */
				if ( huge + x > one ) return x;/* return x with inexact if x!=0*/
			}
			t = x * x;
			p = t * ( pS0 + t * ( pS1 + t * pS2 ) );
			q = one + t * qS1;
			w = p / q;
			return x + x * w;
		}
		/* 1> |x|>= 0.5 */
		w = one - FastAbs( x );
		t = w * ( float )0.5;
		p = t * ( pS0 + t * ( pS1 + t * pS2 ) );
		q = one + t * qS1;
		s = sqrt( t );
		w = p / q;
		t = static_cast<float>(pio2 - 2.0 * ( s + s * w ));
		if ( hx > 0 ) return t; else return -t;
	}

	constexpr inline float
		FastASin( float x )
	{
		using namespace asinf_internal;
		float s;
		float t, w, p, q;
		//int32_t hx, ix;
		//int32_t hx;
		//GET_FLOAT_WORD( hx, x );
		Int32 hx = std::bit_cast< Int32 >( x );
		Int32 ix = hx & 0x7fffffff;
		if ( ix >= 0x3f800000 )
		{		/* |x| >= 1 */
			if ( ix == 0x3f800000 )		/* |x| == 1 */
			{
				return x * pio2f;		/* asin(+-1) = +-pi/2 with inexact */
			}
			return std::numeric_limits<float>::quiet_NaN( );
			//return ( x - x ) / ( x - x );		/* asin(|x|>1) is NaN */
		}
		else if ( ix < 0x3f000000 )
		{	/* |x|<0.5 */
			if ( ix < 0x39800000 )
			{		/* |x| < 2**-12 */
				if ( huge + x > one ) return x;/* return x with inexact if x!=0*/
			}
			t = x * x;
			p = t * ( pS0 + t * ( pS1 + t * pS2 ) );
			q = one + t * qS1;
			w = p / q;
			return x + x * w;
		}
		/* 1> |x|>= 0.5 */
		//w = one - fabsf( x );
		w = one - FastAbs( x );
		t = w * 0.5f;
		p = t * ( pS0 + t * ( pS1 + t * pS2 ) );
		q = one + t * qS1;
		//s = sqrtf( t );
		s = Sqrt( t );
		w = p / q;
		t = static_cast< float >( pio2f - 2.0f * ( s + s * w ) );
		if ( hx > 0 ) return t; else return -t;
	}
}