/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#pragma once
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
//__FBSDID("$FreeBSD: src/lib/msun/src/k_logf.h,v 1.3 2011/10/15 05:23:28 das Exp $");

/*
 * Float version of k_log.h.  See the latter for most comments.
 */

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace k_log1pf_internal
	{
		constexpr float
			/* |(log(1+s)-log(1-s))/s - Lg(s)| < 2**-34.24 (~[-4.95e-11, 4.97e-11]). */
			Lg1 = 0xaaaaaa.0p-24f,	/* 0.66666662693 */
			Lg2 = 0xccce13.0p-25f,	/* 0.40000972152 */
			Lg3 = 0x91e9ee.0p-25f,	/* 0.28498786688 */
			Lg4 = 0xf89e26.0p-26f;	/* 0.24279078841 */
	}
	constexpr inline float
		k_log1pf( float f )
	{
		using namespace k_log1pf_internal;
		float hfsq, s, z, R, w, t1, t2;

		s = f / ( ( float )2.0 + f );
		z = s * s;
		w = z * z;
		t1 = w * ( Lg2 + w * Lg4 );
		t2 = z * ( Lg1 + w * Lg3 );
		R = t2 + t1;
		hfsq = ( float )0.5 * f * f;
		return s * ( hfsq + R );
	}
}