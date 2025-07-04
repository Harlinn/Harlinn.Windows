/* @(#)s_nextafter.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_nextafter.c,v 1.12 2008/02/22 02:30:35 das Exp $");

/* IEEE functions
 *	nextafter(x,y)
 *	return the next machine floating-point number of x in the
 *	direction toward y.
 *   Special cases:
 */

#include <float.h>
#include "openlibm_math.h"

#include "math_private.h"
namespace Harlinn::Math::Internal::OpenLibM
{
	constexpr inline double
		nextafter( double x, double y )
	{
		double t;
		int32_t hx, hy, ix, iy;
		uint32_t lx, ly;

		EXTRACT_WORDS( hx, lx, x );
		EXTRACT_WORDS( hy, ly, y );
		ix = hx & 0x7fffffff;		/* |x| */
		iy = hy & 0x7fffffff;		/* |y| */

		if ( ( ( ix >= 0x7ff00000 ) && ( ( ix - 0x7ff00000 ) | lx ) != 0 ) ||   /* x is nan */
			( ( iy >= 0x7ff00000 ) && ( ( iy - 0x7ff00000 ) | ly ) != 0 ) )     /* y is nan */
			return x + y;
		if ( x == y ) return y;		/* x=y, return y */
		if ( ( ix | lx ) == 0 )
		{	
			/* x == 0 */

			return CopySign( std::numeric_limits<double>::denorm_min( ), y );

			/*
			INSERT_WORDS( x, hy & 0x80000000, 1 );	// return +-minsubnormal 
			t = x * x;
			if ( t == x ) 
				return t; 
			else 
				return x;	// raise underflow flag 
			*/
		}
		if ( hx >= 0 )
		{				/* x > 0 */
			if ( hx > hy || ( ( hx == hy ) && ( lx > ly ) ) )
			{	/* x > y, x -= ulp */
				if ( lx == 0 ) hx -= 1;
				lx -= 1;
			}
			else
			{				/* x < y, x += ulp */
				lx += 1;
				if ( lx == 0 ) hx += 1;
			}
		}
		else
		{				/* x < 0 */
			if ( hy >= 0 || hx > hy || ( ( hx == hy ) && ( lx > ly ) ) )
			{/* x < y, x -= ulp */
				if ( lx == 0 ) hx -= 1;
				lx -= 1;
			}
			else
			{				/* x > y, x += ulp */
				lx += 1;
				if ( lx == 0 ) hx += 1;
			}
		}
		hy = hx & 0x7ff00000;
		if ( hy >= 0x7ff00000 )
		{
			/* overflow  */
			return CopySign( std::numeric_limits<double>::infinity( ), y );
			//return x + x;	
		}
		/*
		if ( hy < 0x00100000 )
		{		
			// underflow 
			t = x * x;
			if ( t != x )
			{
				// raise underflow flag 
				INSERT_WORDS( y, hx, lx );
				return y;
			}
		}
		*/
		INSERT_WORDS( x, hx, lx );
		return x;
	}

}
