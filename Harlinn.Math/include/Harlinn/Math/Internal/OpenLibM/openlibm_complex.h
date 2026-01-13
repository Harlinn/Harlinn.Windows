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
/*	$OpenBSD: complex.h,v 1.5 2014/03/16 18:38:30 guenther Exp $	*/
/*
 * Copyright (c) 2008 Martynas Venckus <martynas@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifdef OPENLIBM_USE_HOST_COMPLEX_H
#include <complex.h>
#else /* !OPENLIBM_USE_HOST_COMPLEX_H */

#ifndef OPENLIBM_COMPLEX_H
#define	OPENLIBM_COMPLEX_H

namespace Harlinn::Math::Internal::OpenLibM
{
	//#define complex _Complex

	//#define _Complex_I 1.0fi
	//#define I _Complex_I

	/*
	 * Macros that can be used to construct complex values.
	 *
	 * The C99 standard intends x+I*y to be used for this, but x+I*y is
	 * currently unusable in general since gcc introduces many overflow,
	 * underflow, sign and efficiency bugs by rewriting I*y as
	 * (0.0+I)*(y+0.0*I) and laboriously computing the full complex product.
	 * In particular, I*Inf is corrupted to NaN+I*Inf, and I*-0 is corrupted
	 * to -0.0+I*0.0.
	 *
	 * In C11, a CMPLX(x,y) macro was added to circumvent this limitation,
	 * and gcc 4.7 added a __builtin_complex feature to simplify implementation
	 * of CMPLX in libc, so we can take advantage of these features if they
	 * are available. Clang simply allows complex values to be constructed
	 * using a compound literal.
	 *
	 * If __builtin_complex is not available, resort to using inline
	 * functions instead. These can unfortunately not be used to construct
	 * compile-time constants.
	 *
	 * C99 specifies that complex numbers have the same representation as
	 * an array of two elements, where the first element is the real part
	 * and the second element is the imaginary part.
	 */

#ifdef __clang__
#  define CMPLXF(x, y) ((float complex){x, y})
#  define CMPLX(x, y) ((double complex){x, y})
#  define CMPLXL(x, y) ((long double complex){x, y})
#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) && !defined(__INTEL_COMPILER)
#  define CMPLXF(x,y) __builtin_complex ((float) (x), (float) (y))
#  define CMPLX(x,y) __builtin_complex ((double) (x), (double) (y))
#  define CMPLXL(x,y) __builtin_complex ((long double) (x), (long double) (y))
#else
	constexpr inline std::complex<float>
		CMPLXF( float x, float y )
	{
		return std::complex<float>( x, y );
		//union {
		//	float a[2];
		//	float complex f;
		//} z = {{ x, y }};
		//
		//return (z.f);
	}

	constexpr inline std::complex<double>
		CMPLX( double x, double y )
	{
		return std::complex<double>( x, y );
		//union {
		//	double a[2];
		//	double complex f;
		//} z = {{ x, y }};
		//
		//return (z.f);
	}

	constexpr inline std::complex<long double>
		CMPLXL( long double x, long double y )
	{
		return std::complex<long double>( x, y );
		//union {
		//	long double a[2];
		//	long double complex f;
		//} z = {{ x, y }};
		//
		//return (z.f);
	}
#endif

	/*
	 * Double versions of C99 functions
	 */
	 //double complex cacos(double complex);
	 //double complex casin(double complex);
	 //double complex catan(double complex);
	 //double complex ccos(double complex);
	 //double complex csin(double complex);
	 //double complex ctan(double complex);
	 //double complex cacosh(double complex);
	 //double complex casinh(double complex);
	 //double complex catanh(double complex);
	 //double complex ccosh(double complex);
	 //double complex csinh(double complex);
	 //double complex ctanh(double complex);
	 //double complex cexp(double complex);
	 //double complex clog(double complex);
	 //double cabs(double complex);
	 //double complex cpow(double complex, double complex);
	 //double complex csqrt(double complex);
	 //double carg(double complex);
	 //double cimag(double complex);
	 //double complex conj(double complex);
	 //double complex cproj(double complex);
	 //double creal(double complex);

	constexpr inline std::complex<double> cacos( std::complex<double> );
	constexpr inline std::complex<double> casin( std::complex<double> );
	constexpr inline std::complex<double> catan( std::complex<double> );
	constexpr inline std::complex<double> ccos( std::complex<double> );
	constexpr inline std::complex<double> csin( std::complex<double> );
	constexpr inline std::complex<double> ctan( std::complex<double> );
	constexpr inline std::complex<double> cacosh( std::complex<double> );
	constexpr inline std::complex<double> casinh( std::complex<double> );
	constexpr inline std::complex<double> catanh( std::complex<double> );
	constexpr inline std::complex<double> ccosh( std::complex<double> );
	constexpr inline std::complex<double> csinh( std::complex<double> );
	constexpr inline std::complex<double> ctanh( std::complex<double> );
	constexpr inline std::complex<double> cexp( std::complex<double> );
	constexpr inline std::complex<double> clog( std::complex<double> );
	constexpr inline double cabs( std::complex<double> );
	constexpr inline std::complex<double> cpow( std::complex<double>, std::complex<double> );
	constexpr inline std::complex<double> csqrt( std::complex<double> );
	constexpr inline double carg( std::complex<double> );
	constexpr inline double cimag( std::complex<double> );
	constexpr inline std::complex<double> conj( std::complex<double> );
	constexpr inline std::complex<double> cproj( std::complex<double> );
	constexpr inline double creal( std::complex<double> );

	/*
	 * Float versions of C99 functions
	 */
	 //float complex cacosf(float complex);
	 //float complex casinf(float complex);
	 //float complex catanf(float complex);
	 //float complex ccosf(float complex);
	 //float complex csinf(float complex);
	 //float complex ctanf(float complex);
	 //float complex cacoshf(float complex);
	 //float complex casinhf(float complex);
	 //float complex catanhf(float complex);
	 //float complex ccoshf(float complex);
	 //float complex csinhf(float complex);
	 //float complex ctanhf(float complex);
	 //float complex cexpf(float complex);
	 //float complex clogf(float complex);
	 //float cabsf(float complex);
	 //float complex cpowf(float complex, float complex);
	 //float complex csqrtf(float complex);
	 //float cargf(float complex);
	 //float cimagf(float complex);
	 //float complex conjf(float complex);
	 //float complex cprojf(float complex);
	 //float crealf(float complex);

	constexpr inline std::complex<float> cacosf( std::complex<float> );
	constexpr inline std::complex<float> casinf( std::complex<float> );
	constexpr inline std::complex<float> catanf( std::complex<float> );
	constexpr inline std::complex<float> ccosf( std::complex<float> );
	constexpr inline std::complex<float> csinf( std::complex<float> );
	constexpr inline std::complex<float> ctanf( std::complex<float> );
	constexpr inline std::complex<float> cacoshf( std::complex<float> );
	constexpr inline std::complex<float> casinhf( std::complex<float> );
	constexpr inline std::complex<float> catanhf( std::complex<float> );
	constexpr inline std::complex<float> ccoshf( std::complex<float> );
	constexpr inline std::complex<float> csinhf( std::complex<float> );
	constexpr inline std::complex<float> ctanhf( std::complex<float> );
	constexpr inline std::complex<float> cexpf( std::complex<float> );
	constexpr inline std::complex<float> clogf( std::complex<float> );
	constexpr inline float cabsf( std::complex<float> );
	constexpr inline std::complex<float> cpowf( std::complex<float>, std::complex<float> );
	constexpr inline std::complex<float> csqrtf( std::complex<float> );
	constexpr inline float cargf( std::complex<float> );
	constexpr inline float cimagf( std::complex<float> );
	constexpr inline std::complex<float> conjf( std::complex<float> );
	constexpr inline std::complex<float> cprojf( std::complex<float> );
	constexpr inline float crealf( std::complex<float> );

	/*
	 * Long double versions of C99 functions
	 */
	 // long double complex cacosl(long double complex);
	 // long double complex casinl(long double complex);
	 // long double complex catanl(long double complex);
	 // long double complex ccosl(long double complex);
	 // long double complex csinl(long double complex);
	 // long double complex ctanl(long double complex);
	 // long double complex cacoshl(long double complex);
	 // long double complex casinhl(long double complex);
	 // long double complex catanhl(long double complex);
	 // long double complex ccoshl(long double complex);
	 // long double complex csinhl(long double complex);
	 // long double complex ctanhl(long double complex);
	 // long double complex cexpl(long double complex);
	 // long double complex clogl(long double complex);
	 // long double cabsl(long double complex);
	 // long double complex cpowl(long double complex,
	 // 	long double complex);
	 // long double complex csqrtl(long double complex);
	 // long double cargl(long double complex);
	 // long double cimagl(long double complex);
	 // long double complex conjl(long double complex);
	 // long double complex cprojl(long double complex);
	 // long double creall(long double complex);

	constexpr inline std::complex<long double> cacosl( std::complex<long double> );
	constexpr inline std::complex<long double> casinl( std::complex<long double> );
	constexpr inline std::complex<long double> catanl( std::complex<long double> );
	constexpr inline std::complex<long double> ccosl( std::complex<long double> );
	constexpr inline std::complex<long double> csinl( std::complex<long double> );
	constexpr inline std::complex<long double> ctanl( std::complex<long double> );
	constexpr inline std::complex<long double> cacoshl( std::complex<long double> );
	constexpr inline std::complex<long double> casinhl( std::complex<long double> );
	constexpr inline std::complex<long double> catanhl( std::complex<long double> );
	constexpr inline std::complex<long double> ccoshl( std::complex<long double> );
	constexpr inline std::complex<long double> csinhl( std::complex<long double> );
	constexpr inline std::complex<long double> ctanhl( std::complex<long double> );
	constexpr inline std::complex<long double> cexpl( std::complex<long double> );
	constexpr inline std::complex<long double> clogl( std::complex<long double> );
	constexpr inline long double cabsl( std::complex<long double> );
	constexpr inline std::complex<long double> cpowl( std::complex<long double>,
		std::complex<long double> );
	constexpr inline std::complex<long double> csqrtl( std::complex<long double> );
	constexpr inline long double cargl( std::complex<long double> );
	constexpr inline long double cimagl( std::complex<long double> );
	constexpr inline std::complex<long double> conjl( std::complex<long double> );
	constexpr inline std::complex<long double> cprojl( std::complex<long double> );
	constexpr inline long double creall( std::complex<long double> );

}
#endif /* !OPENLIBM_COMPLEX_H */

#endif /* OPENLIBM_USE_HOST_COMPLEX_H */
