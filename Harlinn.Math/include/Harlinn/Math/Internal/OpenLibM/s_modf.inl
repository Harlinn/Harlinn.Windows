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
/* @(#)s_modf.c 5.1 93/09/24 */
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

/*
 * modf(double x, double *iptr)
 * return fraction part of x, and return x's integral part in *iptr.
 * Method:
 *	Bit twiddling.
 *
 * Exception:
 *	No exception.
 */

#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace modf_internal
	{
		constexpr double one = 1.0;
	}

	constexpr inline double
		modf( double x, double* iptr )
	{
		using namespace modf_internal;
		int32_t i0, i1, j0;
		uint32_t i;
		EXTRACT_WORDS( i0, i1, x );
		j0 = ( ( i0 >> 20 ) & 0x7ff ) - 0x3ff;	/* exponent of x */
		if ( j0 < 20 )
		{			/* integer part in high x */
			if ( j0 < 0 )
			{			/* |x|<1 */
				INSERT_WORDS( *iptr, i0 & 0x80000000, 0 );	/* *iptr = +-0 */
				return x;
			}
			else
			{
				i = ( 0x000fffff ) >> j0;
				if ( ( ( i0 & i ) | i1 ) == 0 )
				{		/* x is integral */
					uint32_t high;
					*iptr = x;
					GET_HIGH_WORD( high, x );
					INSERT_WORDS( x, high & 0x80000000, 0 );	/* return +-0 */
					return x;
				}
				else
				{
					INSERT_WORDS( *iptr, i0 & ( ~i ), 0 );
					return x - *iptr;
				}
			}
		}
		else if ( j0 > 51 )
		{		/* no fraction part */
			uint32_t high;
			if ( j0 == 0x400 )
			{		/* inf/NaN */
				*iptr = x;
				return 0.0 / x;
			}
			*iptr = x * one;
			GET_HIGH_WORD( high, x );
			INSERT_WORDS( x, high & 0x80000000, 0 );	/* return +-0 */
			return x;
		}
		else
		{			/* fraction part in low x */
			i = ( ( uint32_t )( 0xffffffff ) ) >> ( j0 - 20 );
			if ( ( i1 & i ) == 0 )
			{ 		/* x is integral */
				uint32_t high;
				*iptr = x;
				GET_HIGH_WORD( high, x );
				INSERT_WORDS( x, high & 0x80000000, 0 );	/* return +-0 */
				return x;
			}
			else
			{
				INSERT_WORDS( *iptr, i0, i1 & ( ~i ) );
				return x - *iptr;
			}
		}
	}
}