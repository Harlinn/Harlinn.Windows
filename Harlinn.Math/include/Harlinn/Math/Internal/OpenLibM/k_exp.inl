/*-
 * Copyright (c) 2011 David Schultz <das@FreeBSD.ORG>
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
//__FBSDID("$FreeBSD: src/lib/msun/src/k_exp.c,v 1.1 2011/10/21 06:27:56 das Exp $");

//#include <openlibm_complex.h>
#include "openlibm_math.h"

#include "math_private.h"

namespace Harlinn::Math::Internal::OpenLibM
{
	namespace __frexp_exp_internal
	{
		constexpr uint32_t k = 1799;		/* constant for reduction */
		constexpr double kln2 = 1246.97177782734161156;	/* k * ln2 */
	}

	/*
	 * Compute exp(x), scaled to avoid spurious overflow.  An exponent is
	 * returned separately in 'expt'.
	 *
	 * Input:  ln(DBL_MAX) <= x < ln(2 * DBL_MAX / DBL_MIN_DENORM) ~= 1454.91
	 * Output: 2**1023 <= y < 2**1024
	 */
	constexpr inline double
		__frexp_exp( double x, int* expt )
	{
		using namespace __frexp_exp_internal;
		double exp_x;
		uint32_t hx;

		/*
		 * We use exp(x) = exp(x - kln2) * 2**k, carefully chosen to
		 * minimize |exp(kln2) - 2**k|.  We also scale the exponent of
		 * exp_x to MAX_EXP so that the result can be multiplied by
		 * a tiny number without losing accuracy due to denormalization.
		 */
		exp_x = exp( x - kln2 );
		GET_HIGH_WORD( hx, exp_x );
		*expt = ( hx >> 20 ) - ( 0x3ff + 1023 ) + k;
		SET_HIGH_WORD( exp_x, ( hx & 0xfffff ) | ( ( 0x3ff + 1023 ) << 20 ) );
		return ( exp_x );
	}

	/*
	 * __ldexp_exp(x, expt) and __ldexp_cexp(x, expt) compute exp(x) * 2**expt.
	 * They are intended for large arguments (real part >= ln(DBL_MAX))
	 * where care is needed to avoid overflow.
	 *
	 * The present implementation is narrowly tailored for our hyperbolic and
	 * exponential functions.  We assume expt is small (0 or -1), and the caller
	 * has filtered out very large x, for which overflow would be inevitable.
	 */

	constexpr inline double
		__ldexp_exp( double x, int expt )
	{
		double exp_x, scale;
		int ex_expt;

		exp_x = __frexp_exp( x, &ex_expt );
		expt += ex_expt;
		INSERT_WORDS( scale, ( 0x3ff + expt ) << 20, 0 );
		return ( exp_x * scale );
	}

	constexpr inline std::complex<double>
		__ldexp_cexp( std::complex<double> z, int expt )
	{
		double x, y, exp_x, scale1, scale2;
		int ex_expt, half_expt;

		x = z.real( ); //creal( z );
		y = z.imag( ); //cimag( z );
		exp_x = __frexp_exp( x, &ex_expt );
		expt += ex_expt;

		/*
		 * Arrange so that scale1 * scale2 == 2**expt.  We use this to
		 * compensate for scalbn being horrendously slow.
		 */
		half_expt = expt / 2;
		INSERT_WORDS( scale1, ( 0x3ff + half_expt ) << 20, 0 );
		half_expt = expt - half_expt;
		INSERT_WORDS( scale2, ( 0x3ff + half_expt ) << 20, 0 );

		return std::complex<double>( cos( y ) * exp_x * scale1 * scale2,
			sin( y ) * exp_x * scale1 * scale2 );

		//return ( CMPLX( cos( y ) * exp_x * scale1 * scale2,
		//	sin( y ) * exp_x * scale1 * scale2 ) );
	}
}