/* e_j1f.c -- float version of e_j1.c.
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

#include <assert.h>
#include "cdefs-compat.h"
#include "openlibm_math.h"
#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace j1f_internal
	{
		constexpr inline float ponef( float ); 
		constexpr inline float qonef( float );

		constexpr float
			huge = 1e30f,
			one = 1.0f,
			invsqrtpi = 5.6418961287e-01f, /* 0x3f106ebb */
			tpi = 6.3661974669e-01f, /* 0x3f22f983 */
			/* R0/S0 on [0,2] */
			r00 = -6.2500000000e-02f, /* 0xbd800000 */
			r01 = 1.4070566976e-03f, /* 0x3ab86cfd */
			r02 = -1.5995563444e-05f, /* 0xb7862e36 */
			r03 = 4.9672799207e-08f, /* 0x335557d2 */
			s01 = 1.9153760746e-02f, /* 0x3c9ce859 */
			s02 = 1.8594678841e-04f, /* 0x3942fab6 */
			s03 = 1.1771846857e-06f, /* 0x359dffc2 */
			s04 = 5.0463624390e-09f, /* 0x31ad6446 */
			s05 = 1.2354227016e-11f; /* 0x2d59567e */

		constexpr float zero = 0.0f;
	}

	constexpr inline float
		__ieee754_j1f( float x )
	{
		using namespace j1f_internal;
		float z, s, c, ss, cc, r, u, v, y;
		int32_t hx, ix;

		GET_FLOAT_WORD( hx, x );
		ix = hx & 0x7fffffff;
		if ( ix >= 0x7f800000 ) return one / x;
		y = Abs( x );
		if ( ix >= 0x40000000 )
		{	/* |x| >= 2.0 */
			SinCos( y, &s, &c );
			//s = sinf( y );
			//c = cosf( y );
			ss = -s - c;
			cc = s - c;
			if ( ix < 0x7f000000 )
			{  /* make sure y+y not overflow */
				z = Cos( y + y );
				if ( ( s * c ) > zero ) cc = z / ss;
				else 	    ss = z / cc;
			}
			/*
			 * j1(x) = 1/sqrt(pi) * (P(1,x)*cc - Q(1,x)*ss) / sqrt(x)
			 * y1(x) = 1/sqrt(pi) * (P(1,x)*ss + Q(1,x)*cc) / sqrt(x)
			 */
			if ( ix > 0x58000000 ) z = ( invsqrtpi * cc ) / Sqrt( y ); /* |x|>2**49 */
			else
			{
				u = ponef( y ); v = qonef( y );
				z = invsqrtpi * ( u * cc - v * ss ) / Sqrt( y );
			}
			if ( hx < 0 ) return -z;
			else  	 return  z;
		}
		if ( ix < 0x39000000 )
		{	/* |x|<2**-13 */
			if ( huge + x > one ) return ( float )0.5 * x;/* inexact if x!=0 necessary */
		}
		z = x * x;
		r = z * ( r00 + z * ( r01 + z * ( r02 + z * r03 ) ) );
		s = one + z * ( s01 + z * ( s02 + z * ( s03 + z * ( s04 + z * s05 ) ) ) );
		r *= x;
		return( x * ( float )0.5 + r / s );
	}

	namespace j1f_internal
	{
		constexpr float U0[ 5 ] = {
		 -1.9605709612e-01f, /* 0xbe48c331 */
		  5.0443872809e-02f, /* 0x3d4e9e3c */
		 -1.9125689287e-03f, /* 0xbafaaf2a */
		  2.3525259166e-05f, /* 0x37c5581c */
		 -9.1909917899e-08f, /* 0xb3c56003 */
		};
		constexpr float V0[ 5 ] = {
		  1.9916731864e-02f, /* 0x3ca3286a */
		  2.0255257550e-04f, /* 0x3954644b */
		  1.3560879779e-06f, /* 0x35b602d4 */
		  6.2274145840e-09f, /* 0x31d5f8eb */
		  1.6655924903e-11f, /* 0x2d9281cf */
		};
	}

	constexpr inline float
		__ieee754_y1f( float x )
	{
		using namespace j1f_internal;
		float z, s, c, ss, cc, u, v;
		int32_t hx, ix;

		GET_FLOAT_WORD( hx, x );
		ix = 0x7fffffff & hx;
		/* if Y1(NaN) is NaN, Y1(-inf) is NaN, Y1(inf) is 0 */
		if ( ix >= 0x7f800000 ) return  one / ( x + x * x );
		if ( ix == 0 )
		{
			return -std::numeric_limits<float>::infinity( );
			//return -one / zero;
		}
		if ( hx < 0 )
		{
			return std::numeric_limits<float>::quiet_NaN( );
			//return zero / zero;
		}
		if ( ix >= 0x40000000 )
		{  /* |x| >= 2.0 */
			SinCos( x, &s, &c );
			//s = sinf( x );
			//c = cosf( x );
			ss = -s - c;
			cc = s - c;
			if ( ix < 0x7f000000 )
			{  /* make sure x+x not overflow */
				z = Cos( x + x );
				if ( ( s * c ) > zero ) cc = z / ss;
				else            ss = z / cc;
			}
			/* y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x0)+q1(x)*cos(x0))
			 * where x0 = x-3pi/4
			 *      Better formula:
			 *              cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
			 *                      =  1/sqrt(2) * (sin(x) - cos(x))
			 *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
			 *                      = -1/sqrt(2) * (cos(x) + sin(x))
			 * To avoid cancellation, use
			 *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
			 * to compute the worse one.
			 */
			if ( ix > 0x58000000 ) z = ( invsqrtpi * ss ) / Sqrt( x ); /* |x|>2**49 */
			else
			{
				u = ponef( x ); v = qonef( x );
				z = invsqrtpi * ( u * ss + v * cc ) / Sqrt( x );
			}
			return z;
		}
		if ( ix <= 0x33000000 )
		{    /* x < 2**-25 */
			return( -tpi / x );
		}
		z = x * x;
		u = U0[ 0 ] + z * ( U0[ 1 ] + z * ( U0[ 2 ] + z * ( U0[ 3 ] + z * U0[ 4 ] ) ) );
		v = one + z * ( V0[ 0 ] + z * ( V0[ 1 ] + z * ( V0[ 2 ] + z * ( V0[ 3 ] + z * V0[ 4 ] ) ) ) );
		return( x * ( u / v ) + tpi * ( __ieee754_j1f( x ) * __ieee754_logf( x ) - one / x ) );
	}

	namespace j1f_internal
	{

		/* For x >= 8, the asymptotic expansions of pone is
		 *	1 + 15/128 s^2 - 4725/2^15 s^4 - ...,	where s = 1/x.
		 * We approximate pone by
		 * 	pone(x) = 1 + (R/S)
		 * where  R = pr0 + pr1*s^2 + pr2*s^4 + ... + pr5*s^10
		 * 	  S = 1 + ps0*s^2 + ... + ps4*s^10
		 * and
		 *	| pone(x)-1-R/S | <= 2  ** ( -60.06)
		 */

		constexpr float pr8[ 6 ] = { /* for x in [inf, 8]=1/[0,0.125] */
		  0.0000000000e+00f, /* 0x00000000 */
		  1.1718750000e-01f, /* 0x3df00000 */
		  1.3239480972e+01f, /* 0x4153d4ea */
		  4.1205184937e+02f, /* 0x43ce06a3 */
		  3.8747453613e+03f, /* 0x45722bed */
		  7.9144794922e+03f, /* 0x45f753d6 */
		};
		constexpr float ps8[ 5 ] = {
		  1.1420736694e+02f, /* 0x42e46a2c */
		  3.6509309082e+03f, /* 0x45642ee5 */
		  3.6956207031e+04f, /* 0x47105c35 */
		  9.7602796875e+04f, /* 0x47bea166 */
		  3.0804271484e+04f, /* 0x46f0a88b */
		};

		constexpr float pr5[ 6 ] = { /* for x in [8,4.5454]=1/[0.125,0.22001] */
		  1.3199052094e-11f, /* 0x2d68333f */
		  1.1718749255e-01f, /* 0x3defffff */
		  6.8027510643e+00f, /* 0x40d9b023 */
		  1.0830818176e+02f, /* 0x42d89dca */
		  5.1763616943e+02f, /* 0x440168b7 */
		  5.2871520996e+02f, /* 0x44042dc6 */
		};
		constexpr float ps5[ 5 ] = {
		  5.9280597687e+01f, /* 0x426d1f55 */
		  9.9140142822e+02f, /* 0x4477d9b1 */
		  5.3532670898e+03f, /* 0x45a74a23 */
		  7.8446904297e+03f, /* 0x45f52586 */
		  1.5040468750e+03f, /* 0x44bc0180 */
		};

		constexpr float pr3[ 6 ] = {
		  3.0250391081e-09f, /* 0x314fe10d */
		  1.1718686670e-01f, /* 0x3defffab */
		  3.9329774380e+00f, /* 0x407bb5e7 */
		  3.5119403839e+01f, /* 0x420c7a45 */
		  9.1055007935e+01f, /* 0x42b61c2a */
		  4.8559066772e+01f, /* 0x42423c7c */
		};
		constexpr float ps3[ 5 ] = {
		  3.4791309357e+01f, /* 0x420b2a4d */
		  3.3676245117e+02f, /* 0x43a86198 */
		  1.0468714600e+03f, /* 0x4482dbe3 */
		  8.9081134033e+02f, /* 0x445eb3ed */
		  1.0378793335e+02f, /* 0x42cf936c */
		};

		constexpr float pr2[ 6 ] = {/* for x in [2.8570,2]=1/[0.3499,0.5] */
		  1.0771083225e-07f, /* 0x33e74ea8 */
		  1.1717621982e-01f, /* 0x3deffa16 */
		  2.3685150146e+00f, /* 0x401795c0 */
		  1.2242610931e+01f, /* 0x4143e1bc */
		  1.7693971634e+01f, /* 0x418d8d41 */
		  5.0735230446e+00f, /* 0x40a25a4d */
		};
		constexpr float ps2[ 5 ] = {
		  2.1436485291e+01f, /* 0x41ab7dec */
		  1.2529022980e+02f, /* 0x42fa9499 */
		  2.3227647400e+02f, /* 0x436846c7 */
		  1.1767937469e+02f, /* 0x42eb5bd7 */
		  8.3646392822e+00f, /* 0x4105d590 */
		};

		constexpr inline float ponef( float x )
		{
			const float* p, * q;
			float z, r, s;
			int32_t ix;
			GET_FLOAT_WORD( ix, x );
			ix &= 0x7fffffff;
			if ( ix >= 0x41000000 ) { p = pr8; q = ps8; }
			else if ( ix >= 0x409173eb ) { p = pr5; q = ps5; }
			else if ( ix >= 0x4036d917 ) { p = pr3; q = ps3; }
			else { p = pr2; q = ps2; }	/* ix>=0x40000000 */
			z = one / ( x * x );
			r = p[ 0 ] + z * ( p[ 1 ] + z * ( p[ 2 ] + z * ( p[ 3 ] + z * ( p[ 4 ] + z * p[ 5 ] ) ) ) );
			s = one + z * ( q[ 0 ] + z * ( q[ 1 ] + z * ( q[ 2 ] + z * ( q[ 3 ] + z * q[ 4 ] ) ) ) );
			return one + r / s;
		}


		/* For x >= 8, the asymptotic expansions of qone is
		 *	3/8 s - 105/1024 s^3 - ..., where s = 1/x.
		 * We approximate pone by
		 * 	qone(x) = s*(0.375 + (R/S))
		 * where  R = qr1*s^2 + qr2*s^4 + ... + qr5*s^10
		 * 	  S = 1 + qs1*s^2 + ... + qs6*s^12
		 * and
		 *	| qone(x)/s -0.375-R/S | <= 2  ** ( -61.13)
		 */

		constexpr float qr8[ 6 ] = { /* for x in [inf, 8]=1/[0,0.125] */
		  0.0000000000e+00f, /* 0x00000000 */
		 -1.0253906250e-01f, /* 0xbdd20000 */
		 -1.6271753311e+01f, /* 0xc1822c8d */
		 -7.5960174561e+02f, /* 0xc43de683 */
		 -1.1849806641e+04f, /* 0xc639273a */
		 -4.8438511719e+04f, /* 0xc73d3683 */
		};
		constexpr float qs8[ 6 ] = {
		  1.6139537048e+02f, /* 0x43216537 */
		  7.8253862305e+03f, /* 0x45f48b17 */
		  1.3387534375e+05f, /* 0x4802bcd6 */
		  7.1965775000e+05f, /* 0x492fb29c */
		  6.6660125000e+05f, /* 0x4922be94 */
		 -2.9449025000e+05f, /* 0xc88fcb48 */
		};

		constexpr float qr5[ 6 ] = { /* for x in [8,4.5454]=1/[0.125,0.22001] */
		 -2.0897993405e-11f, /* 0xadb7d219 */
		 -1.0253904760e-01f, /* 0xbdd1fffe */
		 -8.0564479828e+00f, /* 0xc100e736 */
		 -1.8366960144e+02f, /* 0xc337ab6b */
		 -1.3731937256e+03f, /* 0xc4aba633 */
		 -2.6124443359e+03f, /* 0xc523471c */
		};
		constexpr float qs5[ 6 ] = {
		  8.1276550293e+01f, /* 0x42a28d98 */
		  1.9917987061e+03f, /* 0x44f8f98f */
		  1.7468484375e+04f, /* 0x468878f8 */
		  4.9851425781e+04f, /* 0x4742bb6d */
		  2.7948074219e+04f, /* 0x46da5826 */
		 -4.7191835938e+03f, /* 0xc5937978 */
		};

		constexpr float qr3[ 6 ] = {
		 -5.0783124372e-09f, /* 0xb1ae7d4f */
		 -1.0253783315e-01f, /* 0xbdd1ff5b */
		 -4.6101160049e+00f, /* 0xc0938612 */
		 -5.7847221375e+01f, /* 0xc267638e */
		 -2.2824453735e+02f, /* 0xc3643e9a */
		 -2.1921012878e+02f, /* 0xc35b35cb */
		};
		constexpr float qs3[ 6 ] = {
		  4.7665153503e+01f, /* 0x423ea91e */
		  6.7386511230e+02f, /* 0x4428775e */
		  3.3801528320e+03f, /* 0x45534272 */
		  5.5477290039e+03f, /* 0x45ad5dd5 */
		  1.9031191406e+03f, /* 0x44ede3d0 */
		 -1.3520118713e+02f, /* 0xc3073381 */
		};

		constexpr float qr2[ 6 ] = {/* for x in [2.8570,2]=1/[0.3499,0.5] */
		 -1.7838172539e-07f, /* 0xb43f8932 */
		 -1.0251704603e-01f, /* 0xbdd1f475 */
		 -2.7522056103e+00f, /* 0xc0302423 */
		 -1.9663616180e+01f, /* 0xc19d4f16 */
		 -4.2325313568e+01f, /* 0xc2294d1f */
		 -2.1371921539e+01f, /* 0xc1aaf9b2 */
		};
		constexpr float qs2[ 6 ] = {
		  2.9533363342e+01f, /* 0x41ec4454 */
		  2.5298155212e+02f, /* 0x437cfb47 */
		  7.5750280762e+02f, /* 0x443d602e */
		  7.3939318848e+02f, /* 0x4438d92a */
		  1.5594900513e+02f, /* 0x431bf2f2 */
		 -4.9594988823e+00f, /* 0xc09eb437 */
		};

		constexpr inline float qonef( float x )
		{
			const float* p, * q;
			float  s, r, z;
			int32_t ix;
			GET_FLOAT_WORD( ix, x );
			ix &= 0x7fffffff;
			if ( ix >= 0x41000000 ) { p = qr8; q = qs8; }
			else if ( ix >= 0x409173eb ) { p = qr5; q = qs5; }
			else if ( ix >= 0x4036d917 ) { p = qr3; q = qs3; }
			else { p = qr2; q = qs2; }	/* ix>=0x40000000 */
			z = one / ( x * x );
			r = p[ 0 ] + z * ( p[ 1 ] + z * ( p[ 2 ] + z * ( p[ 3 ] + z * ( p[ 4 ] + z * p[ 5 ] ) ) ) );
			s = one + z * ( q[ 0 ] + z * ( q[ 1 ] + z * ( q[ 2 ] + z * ( q[ 3 ] + z * ( q[ 4 ] + z * q[ 5 ] ) ) ) ) );
			return ( ( float ).375 + r / s ) / x;
		}
	}
}