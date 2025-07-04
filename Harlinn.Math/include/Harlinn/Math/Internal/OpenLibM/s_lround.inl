/*-
 * Copyright (c) 2005 David Schultz <das@FreeBSD.ORG>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "cdefs-compat.h"

#include <limits.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
#ifndef type
	//__FBSDID("$FreeBSD: src/lib/msun/src/s_lround.c,v 1.2 2005/04/08 00:52:16 das Exp $");
#define type		double
#define	roundit		round
#define dtype		long
#define	DTYPE_MIN	LONG_MIN
#define	DTYPE_MAX	LONG_MAX
#define	fn		lround
#endif

/*
 * If type has more precision than dtype, the endpoints dtype_(min|max) are
 * of the form xxx.5; they are "out of range" because lround() rounds away
 * from 0.  On the other hand, if type has less precision than dtype, then
 * all values that are out of range are integral, so we might as well assume
 * that everything is in range.  At compile time, INRANGE(x) should reduce to
 * two floating-point comparisons in the former case, or TRUE otherwise.
 */

	
	namespace _CONCAT( fn, _internal )
	{
		constexpr type dtype_min = DTYPE_MIN - static_cast< type >( 0.5 );
		constexpr type dtype_max = DTYPE_MAX + static_cast< type >( 0.5 );
	}
#define	INRANGE(x)	(dtype_max - DTYPE_MAX != static_cast< type >( 0.5 ) || \
			 ((x) > dtype_min && (x) < dtype_max))

	constexpr inline dtype
		fn( type x )
	{
		using namespace _CONCAT( fn, _internal );
		if ( std::is_constant_evaluated( ) )
		{
			return static_cast< dtype >( roundit( x ) );
		}
		else
		{
			if ( INRANGE( x ) )
			{
				x = roundit( x );
				return ( ( dtype )x );
			}
			else
			{
				feraiseexcept( FE_INVALID );
				return ( DTYPE_MAX );
			}
		}
	}

#undef INRANGE
#undef type
#undef roundit
#undef dtype
#undef DTYPE_MIN
#undef DTYPE_MAX
#undef fn
}

