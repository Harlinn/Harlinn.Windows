/* e_acosf.c -- float version of e_acos.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_acosf.c,v 1.11 2008/08/03 17:39:54 das Exp $");

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace acosf_internal
	{
		constexpr float
			one = 1.0000000000e+00f, /* 0x3F800000 */
			pi = 3.1415925026e+00f, /* 0x40490fda */
			pio2_hi = 1.5707962513e+00f; /* 0x3fc90fda */
		constexpr float
			pio2_lo = 7.5497894159e-08f; /* 0x33a22168 */
		constexpr float
			pS0 = 1.6666586697e-01f,
			pS1 = -4.2743422091e-02f,
			pS2 = -8.6563630030e-03f,
			qS1 = -7.0662963390e-01f;
	}

	constexpr inline float
		__ieee754_acosf( float x )
	{
		using namespace acosf_internal;
		float z, p, q, r, w, s, c, df;
		int32_t hx, ix;
		GET_FLOAT_WORD( hx, x );
		ix = hx & 0x7fffffff;
		if ( ix >= 0x3f800000 )
		{		/* |x| >= 1 */
			if ( ix == 0x3f800000 )
			{	/* |x| == 1 */
				if ( hx > 0 ) return 0.0;	/* acos(1) = 0 */
				else return pi + ( float )2.0 * pio2_lo;	/* acos(-1)= pi */
			}
			return ( x - x ) / ( x - x );		/* acos(|x|>1) is NaN */
		}
		if ( ix < 0x3f000000 )
		{	/* |x| < 0.5 */
			if ( ix <= 0x32800000 ) return pio2_hi + pio2_lo;/*if|x|<2**-26*/
			z = x * x;
			p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
			q = one + z * qS1;
			r = p / q;
			return pio2_hi - ( x - ( pio2_lo - x * r ) );
		}
		else  if ( hx < 0 )
		{		/* x < -0.5 */
			z = ( one + x ) * ( float )0.5;
			p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
			q = one + z * qS1;
			s = sqrtf( z );
			r = p / q;
			w = r * s - pio2_lo;
			return pi - ( float )2.0 * ( s + w );
		}
		else
		{			/* x > 0.5 */
			int32_t idf;
			z = ( one - x ) * ( float )0.5;
			s = sqrtf( z );
			df = s;
			GET_FLOAT_WORD( idf, df );
			SET_FLOAT_WORD( df, idf & 0xfffff000 );
			c = ( z - df * df ) / ( s + df );
			p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
			q = one + z * qS1;
			r = p / q;
			w = r * s + c;
			return ( float )2.0 * ( df + w );
		}
	}

	constexpr inline float
		FastACos( float x )
	{
		using namespace acosf_internal;
		float z, p, q, r, w, s, c, df;
		int32_t hx, ix;
		//GET_FLOAT_WORD( hx, x );
		hx = std::bit_cast< int32_t >( x );
		ix = hx & 0x7fffffff;
		if ( ix >= 0x3f800000 )
		{		/* |x| >= 1 */
			if ( ix == 0x3f800000 )
			{	/* |x| == 1 */
				if ( hx > 0 ) return 0.0;	/* acos(1) = 0 */
				else return pi + 2.0f * pio2_lo;	/* acos(-1)= pi */
			}
			/* acos(|x|>1) is NaN */
			return std::numeric_limits<float>::quiet_NaN( );
			//return ( x - x ) / ( x - x );
		}
		if ( ix < 0x3f000000 )
		{	/* |x| < 0.5 */
			if ( ix <= 0x32800000 ) return pio2_hi + pio2_lo;/*if|x|<2**-26*/
			z = x * x;
			p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
			q = one + z * qS1;
			r = p / q;
			return pio2_hi - ( x - ( pio2_lo - x * r ) );
		}
		else  if ( hx < 0 )
		{		/* x < -0.5 */
			z = ( one + x ) * 0.5f;
			p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
			q = one + z * qS1;
			s = Sqrt( z );
			r = p / q;
			w = r * s - pio2_lo;
			return pi - 2.0f * ( s + w );
		}
		else
		{			/* x > 0.5 */
			//int32_t idf;
			z = ( one - x ) * 0.5f;
			s = Sqrt( z );
			df = s;
			//GET_FLOAT_WORD( idf, df );
			//SET_FLOAT_WORD( df, idf & 0xfffff000 );
			df = std::bit_cast< float >( std::bit_cast< int32_t >( df ) & 0xfffff000 );
			c = ( z - df * df ) / ( s + df );
			p = z * ( pS0 + z * ( pS1 + z * pS2 ) );
			q = one + z * qS1;
			r = p / q;
			w = r * s + c;
			return 2.0f * ( df + w );
		}
	}
}