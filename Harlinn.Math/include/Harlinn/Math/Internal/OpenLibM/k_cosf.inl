/* k_cosf.c -- float version of k_cos.c
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 * Debugged and optimized by Bruce D. Evans.
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

#ifndef INLINE_KERNEL_COSDF
#include "cdefs-compat.h"
//__FBSDID("$FreeBSD: src/lib/msun/src/k_cosf.c,v 1.18 2009/06/03 08:16:34 ed Exp $");
#endif

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace __kernel_cosdf_internal
	{
		/* |cos(x) - c(x)| < 2**-34.1 (~[-5.37e-11, 5.295e-11]). */
		constexpr double
			one = 1.0,
			C0 = -0x1ffffffd0c5e81.0p-54,	/* -0.499999997251031003120 */
			C1 = 0x155553e1053a42.0p-57,	/*  0.0416666233237390631894 */
			C2 = -0x16c087e80f1e27.0p-62,	/* -0.00138867637746099294692 */
			C3 = 0x199342e0ee5069.0p-68;	/*  0.0000243904487962774090654 */
	}

#ifndef INLINE_KERNEL_COSDF
	//extern
#endif
		//__inline float
	constexpr inline float
		__kernel_cosdf( double x )
	{
		using namespace __kernel_cosdf_internal;
		double r, w, z;

		/* Try to optimize for parallel evaluation as in k_tanf.c. */
		z = x * x;
		w = z * z;
		r = C2 + z * C3;
		return static_cast<float>(( ( one + z * C0 ) + w * C1 ) + ( w * z ) * r);
	}
}