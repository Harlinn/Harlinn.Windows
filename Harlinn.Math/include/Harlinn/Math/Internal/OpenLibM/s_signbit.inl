/*-
 * Copyright (c) 2003 Mike Barcroft <mike@FreeBSD.org>
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
 *
 * $FreeBSD: src/lib/msun/src/s_signbit.c,v 1.1 2004/07/19 08:16:10 das Exp $
 */

#include "openlibm_math.h"

#include "fpmath.h"
#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	constexpr inline int
		__signbit( double d )
	{
		/*
		union IEEEd2bits u;

		u.d = d;
		return ( u.bits.sign );
		*/
		return static_cast<int>(( std::bit_cast< uint64_t >( d ) & 0x8000'0000'0000'0000ULL ) >> 63);
	}

	constexpr inline int
		__signbitf( float f )
	{
		/*
		union IEEEf2bits u;

		u.f = f;
		return ( u.bits.sign );
		*/
		return static_cast< int >( ( std::bit_cast< uint32_t >( f ) & 0x8000'0000UL ) >> 31 );
	}

#ifdef OLM_LONG_DOUBLE
	/*
	OLM_DLLEXPORT int
		__signbitl( long double e )
	{
		union IEEEl2bits u;

		u.e = e;
		return ( u.bits.sign );
	}
	*/
#endif
}