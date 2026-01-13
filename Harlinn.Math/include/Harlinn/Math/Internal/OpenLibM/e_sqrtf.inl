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
/* e_sqrtf.c -- float version of e_sqrt.c.
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

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace sqrtf_internal
	{
		constexpr float	one = 1.0f, tiny = 1.0e-30f;
	}

	constexpr inline float
		__ieee754_sqrtf( float x )
	{
		using namespace sqrtf_internal;
		float z;
		int32_t sign = ( int )0x80000000;
		int32_t ix, s, q, m, t, i;
		uint32_t r;

		GET_FLOAT_WORD( ix, x );

		/* take care of Inf and NaN */
		if ( ( ix & 0x7f800000 ) == 0x7f800000 )
		{
			// sqrt(NaN)=NaN, sqrt(+inf)=+inf sqrt(-inf)=sNaN 

			return x * x + x;
		}
		/* take care of zero */
		if ( ix <= 0 )
		{
			if ( ( ix & ( ~sign ) ) == 0 ) return x;/* sqrt(+-0) = +-0 */
			else if ( ix < 0 )
			{
				return std::numeric_limits<float>::quiet_NaN( );
				//return ( x - x ) / ( x - x );		/* sqrt(-ve) = sNaN */
			}
		}
		/* normalize x */
		m = ( ix >> 23 );
		if ( m == 0 )
		{				/* subnormal x */
			for ( i = 0; ( ix & 0x00800000 ) == 0; i++ ) ix <<= 1;
			m -= i - 1;
		}
		m -= 127;	/* unbias exponent */
		ix = ( ix & 0x007fffff ) | 0x00800000;
		if ( m & 1 )	/* odd m, double x to make it even */
			ix += ix;
		m >>= 1;	/* m = [m/2] */

		/* generate sqrt(x) bit by bit */
		ix += ix;
		q = s = 0;		/* q = sqrt(x) */
		r = 0x01000000;		/* r = moving bit from right to left */

		while ( r != 0 )
		{
			t = s + r;
			if ( t <= ix )
			{
				s = t + r;
				ix -= t;
				q += r;
			}
			ix += ix;
			r >>= 1;
		}

		/* use floating add to find out rounding direction */
		if ( ix != 0 )
		{
			z = one - tiny; /* trigger inexact flag */
			if ( z >= one )
			{
				z = one + tiny;
				if ( z > one )
					q += 2;
				else
					q += ( q & 1 );
			}
		}
		ix = ( q >> 1 ) + 0x3f000000;
		ix += std::bit_cast<int32_t>( std::bit_cast<uint32_t>(m) << 23 );
		SET_FLOAT_WORD( z, ix );
		return z;
	}
}