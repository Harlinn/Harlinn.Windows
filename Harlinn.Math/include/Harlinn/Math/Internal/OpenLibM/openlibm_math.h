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
 * from: @(#)fdlibm.h 5.1 93/09/24
 * $FreeBSD: src/lib/msun/src/openlibm.h,v 1.82 2011/11/12 19:55:48 theraven Exp $
 */

#ifdef OPENLIBM_USE_HOST_MATH_H
#include <math.h>
#else /* !OPENLIBM_USE_HOST_MATH_H */

#include "openlibm_defs.h"

#ifndef OPENLIBM_MATH_H
#define	OPENLIBM_MATH_H

#if (defined(_WIN32) || defined (_MSC_VER)) && !defined(__WIN32__)
    #define __WIN32__
#endif

#if !defined(__arm__) && !defined(__wasm__)
#define OLM_LONG_DOUBLE
#endif

#ifndef __pure2
#define __pure2
#endif

namespace Harlinn::Math::Internal::OpenLibM
{ 

/*
 * ANSI/POSIX
 */
extern const union __infinity_un {
	unsigned char	__uc[8];
	double		__ud;
} __infinity;

extern const union __nan_un {
	unsigned char	__uc[sizeof(float)];
	float		__uf;
} __nan;

/* VBS
#if __GNUC_PREREQ__(3, 3) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 800)
#define	__MATH_BUILTIN_CONSTANTS
#endif

#if __GNUC_PREREQ__(3, 0) && !defined(__INTEL_COMPILER)
#define	__MATH_BUILTIN_RELOPS
#endif
*/

//VBS begin
#define __MATH_BUILTIN_CONSTANTS
//#define	__MATH_BUILTIN_RELOPS
#ifndef __ISO_C_VISIBLE
#define __ISO_C_VISIBLE 1999
#endif
//VBS end

#ifndef HUGE_VAL
#ifdef __MATH_BUILTIN_CONSTANTS
#define	HUGE_VAL	__builtin_huge_val()
#else
#define	HUGE_VAL	(__infinity.__ud)
#endif
#endif

#if __ISO_C_VISIBLE >= 1999
#ifndef FP_ILOGB0
#define	FP_ILOGB0	(-INT_MAX)
#endif
#ifndef FP_ILOGBNAN
#define	FP_ILOGBNAN	INT_MAX
#endif

#ifdef __MATH_BUILTIN_CONSTANTS
#ifndef HUGE_VALF
#define	HUGE_VALF	__builtin_huge_valf()
#endif
#ifndef HUGE_VALL
#define	HUGE_VALL	__builtin_huge_vall()
#endif
#ifndef INFINITY
#define	INFINITY	HUGE_VALF /*__builtin_inff()*/
#endif
#ifndef NAN
#define	NAN		__builtin_nanf("")
#endif
#else
#define	HUGE_VALF	(float)HUGE_VAL
#define	HUGE_VALL	(long double)HUGE_VAL
#define	INFINITY	HUGE_VALF
#define	NAN		(__nan.__uf)
#endif /* __MATH_BUILTIN_CONSTANTS */

#define	MATH_ERRNO	1
#define	MATH_ERREXCEPT	2
#ifndef math_errhandling
#define	math_errhandling	MATH_ERREXCEPT
#endif

#define	FP_FAST_FMAF	1
#if defined( __ia64__ ) || defined( _M_X64 )
#define	FP_FAST_FMA	1
#define	FP_FAST_FMAL	1
#endif

/* Symbolic constants to classify floating point numbers. */

#ifndef FP_INFINITE
#define	FP_INFINITE	0x01
#endif
#ifndef FP_NAN
#define	FP_NAN		0x02
#endif

#ifndef _MSC_VER
#define	FP_NORMAL	0x04
#define	FP_SUBNORMAL	0x08
#define	FP_ZERO		0x10
#else
constexpr int FP_NORMAL_ = 0x04;
constexpr int FP_SUBNORMAL_ = 0x08;
constexpr int FP_ZERO_ = 0x10;
#endif
/*
#define	fpclassify(x) \
    ((sizeof (x) == sizeof (float)) ? __fpclassifyf(x) \
    : (sizeof (x) == sizeof (double)) ? __fpclassifyd(x) \
    : __fpclassifyl(x))
*/

constexpr inline int	__fpclassifyd( double ) __pure2;
constexpr inline int	__fpclassifyf( float ) __pure2;
constexpr inline int	__fpclassifyl( long double v ) __pure2
{
    return __fpclassifyd( v );
}
constexpr inline int	__isfinitef( float ) __pure2;
constexpr inline int	__isfinite( double ) __pure2;
constexpr inline int	__isfinitel( long double v ) __pure2
{
    return __isfinite( v );
}
constexpr inline int	( isinf )( double ) __pure2;
constexpr inline int	__isinff( float ) __pure2;
constexpr inline int	__isinfl( long double v ) __pure2
{
    return isinf( v );
}
constexpr inline int	( isnan )( double ) __pure2;
constexpr inline int	__isnanf( float ) __pure2;
constexpr inline int	__isnanl( long double v ) __pure2
{
    return isnan( v );
}
constexpr inline int	__isnormalf( float ) __pure2;
constexpr inline int	__isnormal( double ) __pure2;
constexpr inline int	__isnormall( long double v ) __pure2
{
    return __isnormal( v );
}
constexpr inline int	__signbit( double ) __pure2;
constexpr inline int	__signbitf( float ) __pure2;
constexpr inline int	__signbitl( long double v ) __pure2
{
    return __signbit( v );
}





constexpr inline auto fpclassify( float x ) noexcept
{
    return __fpclassifyf( x );
}

constexpr inline auto fpclassify( double x ) noexcept
{
    return __fpclassifyd( x );
}

constexpr inline int isfinite( float x ) noexcept
{
    return __isfinitef( x );
}

constexpr inline int isfinite( double x ) noexcept
{
    return __isfinite( x );
}

constexpr inline int isinf( float x )
{
    return __isinff( x );
}

constexpr inline int isnan( float x ) noexcept
{
    return __isnanf( x );
}


constexpr inline int isnormal( float x ) noexcept
{
    return __isnormalf( x );
}

constexpr inline int isnormal( double x ) noexcept
{
    return __isnormal( x );
}

constexpr inline int signbit( float x ) noexcept
{
    return __signbitf( x );
}

constexpr inline int signbit( double x ) noexcept
{
    return __signbit( x );
}

template<typename T>
    requires std::is_floating_point_v<T>
constexpr inline bool isunordered( T x, T y )
{
    return isnan( x ) || isnan( y );
}

template<typename T>
    requires std::is_floating_point_v<T>
constexpr inline bool isordered( T x, T y )
{
    return isunordered( x, y ) == false;
}

template<typename T>
    requires std::is_floating_point_v<T>
constexpr inline bool isgreater( T x, T y )
{
    return isordered( x, y ) && x > y;
}

template<typename T>
    requires std::is_floating_point_v<T>
constexpr inline bool isgreaterequal( T x, T y )
{
    return isordered( x, y ) && x >= y;
}

template<typename T>
    requires std::is_floating_point_v<T>
constexpr inline bool isless( T x, T y )
{
    return isordered( x, y ) && x < y;
}

template<typename T>
    requires std::is_floating_point_v<T>
constexpr inline bool islessequal( T x, T y )
{
    return isordered( x, y ) && x <= y;
}

template<typename T>
    requires std::is_floating_point_v<T>
constexpr inline bool islessgreater( T x, T y )
{
    return isordered( x, y ) && ( x > y || y > x );
}



/*
#define	isfinite(x)					\
    ((sizeof (x) == sizeof (float)) ? __isfinitef(x)	\
    : (sizeof (x) == sizeof (double)) ? __isfinite(x)	\
    : __isfinitel(x))
#define	isinf(x)					\
    ((sizeof (x) == sizeof (float)) ? __isinff(x)	\
    : (sizeof (x) == sizeof (double)) ? isinf(x)	\
    : __isinfl(x))
#define	isnan(x)					\
    ((sizeof (x) == sizeof (float)) ? __isnanf(x)	\
    : (sizeof (x) == sizeof (double)) ? isnan(x)	\
    : __isnanl(x))
#define	isnormal(x)					\
    ((sizeof (x) == sizeof (float)) ? __isnormalf(x)	\
    : (sizeof (x) == sizeof (double)) ? __isnormal(x)	\
    : __isnormall(x))
*/

/*
#ifdef __MATH_BUILTIN_RELOPS
#define	isgreater(x, y)		__builtin_isgreater((x), (y))
#define	isgreaterequal(x, y)	__builtin_isgreaterequal((x), (y))
#define	isless(x, y)		__builtin_isless((x), (y))
#define	islessequal(x, y)	__builtin_islessequal((x), (y))
#define	islessgreater(x, y)	__builtin_islessgreater((x), (y))
#define	isunordered(x, y)	__builtin_isunordered((x), (y))
#else
#define	isgreater(x, y)		(!isunordered((x), (y)) && (x) > (y))
#define	isgreaterequal(x, y)	(!isunordered((x), (y)) && (x) >= (y))
#define	isless(x, y)		(!isunordered((x), (y)) && (x) < (y))
#define	islessequal(x, y)	(!isunordered((x), (y)) && (x) <= (y))
#define	islessgreater(x, y)	(!isunordered((x), (y)) && \
					((x) > (y) || (y) > (x)))
#define	isunordered(x, y)	(isnan(x) || isnan(y))
#endif */ /* __MATH_BUILTIN_RELOPS */

/*
#define	signbit(x)					\
    ((sizeof (x) == sizeof (float)) ? __signbitf(x)	\
    : (sizeof (x) == sizeof (double)) ? __signbit(x)	\
    : __signbitl(x))
*/
//VBS
//typedef	__double_t	double_t;
//typedef	__float_t	float_t;
#endif /* __ISO_C_VISIBLE >= 1999 */

/*
 * XOPEN/SVID
 */
#if __BSD_VISIBLE || __XSI_VISIBLE
#define	M_E		2.7182818284590452354	/* e */
#define	M_LOG2E		1.4426950408889634074	/* log 2e */
#define	M_LOG10E	0.43429448190325182765	/* log 10e */
#define	M_LN2		0.69314718055994530942	/* log e2 */
#define	M_LN10		2.30258509299404568402	/* log e10 */
#define	M_PI		3.14159265358979323846	/* pi */
#define	M_PI_2		1.57079632679489661923	/* pi/2 */
#define	M_PI_4		0.78539816339744830962	/* pi/4 */
#define	M_1_PI		0.31830988618379067154	/* 1/pi */
#define	M_2_PI		0.63661977236758134308	/* 2/pi */
#define	M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define	M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define	M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */

#define	MAXFLOAT	((float)3.40282346638528860e+38)

#ifndef OPENLIBM_ONLY_THREAD_SAFE
constexpr inline extern int signgam;
#endif
#endif /* __BSD_VISIBLE || __XSI_VISIBLE */

#if __BSD_VISIBLE
#if 0
/* Old value from 4.4BSD-Lite openlibm.h; this is probably better. */
#define	HUGE		HUGE_VAL
#else
#define	HUGE		MAXFLOAT
#endif
#endif /* __BSD_VISIBLE */

/*
 * Most of these functions depend on the rounding mode and have the side
 * effect of raising floating-point exceptions, so they are not declared
 * as __pure2.  In C99, FENV_ACCESS affects the purity of these functions.
 */

//#if defined(__cplusplus)
//extern "C" {
//#endif
    /* Symbol present when OpenLibm is used. */
    int isopenlibm( void );

    /*
     * ANSI/POSIX
     */

    constexpr inline double	acos( double );
    constexpr inline double	asin( double );
    constexpr inline double	atan( double );
    constexpr inline double	atan2( double, double );
    constexpr inline double	cos( double );
    constexpr inline double	sin( double );
    constexpr inline double	tan( double );

    constexpr inline double	cosh( double );
    constexpr inline double	sinh( double );
    constexpr inline double	tanh( double );

    constexpr inline double	exp( double );
    constexpr inline double	frexp( double, int* );	/* fundamentally !__pure2 */
    constexpr inline double	ldexp( double, int );
    constexpr inline double	log( double );
    constexpr inline double	log10( double );
    constexpr inline double	modf( double, double* );	/* fundamentally !__pure2 */

    constexpr inline double	pow( double, double );
    constexpr inline double	sqrt( double );

    constexpr inline double	ceil( double );
    constexpr inline double	fabs( double ) __pure2;
    constexpr inline double	floor( double );
    constexpr inline double	fmod( double, double );

    /*
     * These functions are not in C90.
     */
#if __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 || __XSI_VISIBLE
    constexpr inline double	acosh( double );
    constexpr inline double	asinh( double );
    constexpr inline double	atanh( double );
    constexpr inline double	cbrt( double );
    constexpr inline double	erf( double );
    constexpr inline double	erfc( double );
    constexpr inline double	exp2( double );
    constexpr inline double	expm1( double );
    constexpr inline double	fma( double, double, double );
    constexpr inline double	hypot( double, double );
    constexpr inline int	ilogb( double ) __pure2;
    constexpr inline double	lgamma( double );
    constexpr inline long long llrint( double );
    constexpr inline long long llround( double );
    constexpr inline double	log1p( double );
    constexpr inline double	log2( double );
    constexpr inline double	logb( double );
    constexpr inline long	lrint( double );
    constexpr inline long	lround( double );
    inline double	nan( const char* ) __pure2;
    constexpr inline double	nextafter( double, double );
    constexpr inline double	remainder( double, double );
    constexpr inline double	remquo( double, double, int* );
    constexpr inline double	rint( double );
#endif /* __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 || __XSI_VISIBLE */

//#if __BSD_VISIBLE || __XSI_VISIBLE
    constexpr inline double	j0( double );
    constexpr inline double	j1( double );
    constexpr inline double	jn( int, double );
    constexpr inline double	y0( double );
    constexpr inline double	y1( double );
    constexpr inline double	yn( int, double );
//#endif /* __BSD_VISIBLE || __XSI_VISIBLE */

#if __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999
    constexpr inline double	copysign( double, double ) __pure2;
    constexpr inline double	fdim( double, double );
    constexpr inline double	fmax( double, double ) __pure2;
    constexpr inline double	fmin( double, double ) __pure2;
    constexpr inline double	nearbyint( double );
    constexpr inline double	round( double );
    constexpr inline double	scalbln( double, long );
    constexpr inline double	scalbn( double, int );
    constexpr inline double	tgamma( double );
    constexpr inline double	trunc( double );
#endif

    /*
     * BSD math library entry points
     */
//#if __BSD_VISIBLE
    constexpr inline int	isinff( float ) __pure2;
    constexpr inline int	isnanf( float ) __pure2;

    /*
     * Reentrant version of lgamma; passes signgam back by reference as the
     * second argument; user must allocate space for signgam.
     */
    constexpr inline double	lgamma_r( double, int* );

    /*
     * Single sine/cosine function.
     */
    constexpr inline void	sincos( double, double*, double* );
//#endif /* __BSD_VISIBLE */

    /* float versions of ANSI/POSIX functions */
#if __ISO_C_VISIBLE >= 1999
    constexpr inline float	acosf( float );
    constexpr inline float	asinf( float );
    constexpr inline float	atanf( float );
    constexpr inline float	atan2f( float, float );
    constexpr inline float	cosf( float );
    constexpr inline float	sinf( float );
    constexpr inline float	tanf( float );

    constexpr inline float	coshf( float );
    constexpr inline float	sinhf( float );
    constexpr inline float	tanhf( float );

    constexpr inline float	exp2f( float );
    constexpr inline float	expf( float );
    constexpr inline float	expm1f( float );
    constexpr inline float	frexpf( float, int* );	/* fundamentally !__pure2 */
    constexpr inline int	ilogbf( float ) __pure2;
    constexpr inline float	ldexpf( float, int );
    constexpr inline float	log10f( float );
    constexpr inline float	log1pf( float );
    constexpr inline float	log2f( float );
    constexpr inline float	logf( float );
    constexpr inline float	modff( float, float* );	/* fundamentally !__pure2 */

    constexpr inline float	powf( float, float );
    constexpr inline float	sqrtf( float );

    constexpr inline float	ceilf( float );
    constexpr inline float	fabsf( float ) __pure2;
    constexpr inline float	floorf( float );
    constexpr inline float	fmodf( float, float );
    constexpr inline float	roundf( float );

    constexpr inline float	erff( float );
    constexpr inline float	erfcf( float );
    constexpr inline float	hypotf( float, float );
    constexpr inline float	lgammaf( float );
    constexpr inline float	tgammaf( float );

    constexpr inline float	acoshf( float );
    constexpr inline float	asinhf( float );
    constexpr inline float	atanhf( float );
    constexpr inline float	cbrtf( float );
    constexpr inline float	logbf( float );
    constexpr inline float	copysignf( float, float ) __pure2;
    constexpr inline long long llrintf( float );
    constexpr inline long long llroundf( float );
    constexpr inline long	lrintf( float );
    constexpr inline long	lroundf( float );
    inline float	nanf( const char* ) __pure2;
    constexpr inline float	nearbyintf( float );
    constexpr inline float	nextafterf( float, float );
    constexpr inline float	remainderf( float, float );
    constexpr inline float	remquof( float, float, int* );
    constexpr inline float	rintf( float );
    constexpr inline float	scalblnf( float, long );
    constexpr inline float	scalbnf( float, int );
    constexpr inline float	truncf( float );

    constexpr inline float	fdimf( float, float );
    constexpr inline float	fmaf( float, float, float );
    constexpr inline float	fmaxf( float, float ) __pure2;
    constexpr inline float	fminf( float, float ) __pure2;
#endif

    /*
     * float versions of BSD math library entry points
     */
//#if __BSD_VISIBLE
    constexpr inline float	dremf( float, float );
    constexpr inline float	j0f( float );
    constexpr inline float	j1f( float );
    constexpr inline float	jnf( int, float );
    constexpr inline float	y0f( float );
    constexpr inline float	y1f( float );
    constexpr inline float	ynf( int, float );

    /*
     * Float versions of reentrant version of lgamma; passes signgam back by
     * reference as the second argument; user must allocate space for signgam.
     */
    constexpr inline float	lgammaf_r( float, int* );

    /*
     * Single sine/cosine function.
     */
    constexpr inline void	sincosf( float, float*, float* );
//#endif	/* __BSD_VISIBLE */

    /*
     * long double versions of ISO/POSIX math functions
     */

#ifdef HAS_REAL_LONG_DOUBLE


#if __ISO_C_VISIBLE >= 1999
    constexpr inline long double	acoshl( long double );
    constexpr inline long double	acosl( long double );
    constexpr inline long double	asinhl( long double );
    constexpr inline long double	asinl( long double );
    constexpr inline long double	atan2l( long double, long double );
    constexpr inline long double	atanhl( long double );
    constexpr inline long double	atanl( long double );
    constexpr inline long double	cbrtl( long double );
    constexpr inline long double	ceill( long double );
    constexpr inline long double	copysignl( long double, long double ) __pure2;
    constexpr inline long double	coshl( long double );
    constexpr inline long double	cosl( long double );
    constexpr inline long double	erfcl( long double );
    constexpr inline long double	erfl( long double );
    constexpr inline long double	exp2l( long double );
    constexpr inline long double	expl( long double );
    constexpr inline long double	expm1l( long double );
    constexpr inline long double	fabsl( long double ) __pure2;
    constexpr inline long double	fdiml( long double, long double );
    constexpr inline long double	floorl( long double );
    constexpr inline long double	fmal( long double, long double, long double );
    constexpr inline long double	fmaxl( long double, long double ) __pure2;
    constexpr inline long double	fminl( long double, long double ) __pure2;
    constexpr inline long double	fmodl( long double, long double );
    constexpr inline long double	frexpl( long double value, int* ); /* fundamentally !__pure2 */
    constexpr inline long double	hypotl( long double, long double );
    constexpr inline int		ilogbl( long double ) __pure2;
    constexpr inline long double	ldexpl( long double, int );
    constexpr inline long double	lgammal( long double );
    constexpr inline long long	llrintl( long double );
    constexpr inline long long	llroundl( long double );
    constexpr inline long double	log10l( long double );
    constexpr inline long double	log1pl( long double );
    constexpr inline long double	log2l( long double );
    constexpr inline long double	logbl( long double );
    constexpr inline long double	logl( long double );
    constexpr inline long		lrintl( long double );
    constexpr inline long		lroundl( long double );
    constexpr inline long double	modfl( long double, long double* ); /* fundamentally !__pure2 */
    constexpr inline long double	nanl( const char* ) __pure2;
    constexpr inline long double	nearbyintl( long double );
    constexpr inline long double	nextafterl( long double, long double );
    constexpr inline double		nexttoward( double, long double );
    constexpr inline float		nexttowardf( float, long double );
    constexpr inline long double	nexttowardl( long double, long double );
    constexpr inline long double	powl( long double, long double );
    constexpr inline long double	remainderl( long double, long double );
    constexpr inline long double	remquol( long double, long double, int* );
    constexpr inline long double	rintl( long double );
    constexpr inline long double	roundl( long double );
    constexpr inline long double	scalblnl( long double, long );
    constexpr inline long double	scalbnl( long double, int );
    constexpr inline long double	sinhl( long double );
    constexpr inline long double	sinl( long double );
    constexpr inline long double	sqrtl( long double );
    constexpr inline long double	tanhl( long double );
    constexpr inline long double	tanl( long double );
    constexpr inline long double	tgammal( long double );
    constexpr inline long double	truncl( long double );
#endif /* __ISO_C_VISIBLE >= 1999 */

#else /*!HAS_REAL_LONG_DOUBLE*/
    constexpr inline long double acoshl( long double value )
    {
        return acosh( value );
    }
    constexpr inline long double	acosl( long double value )
    {
        return acos( value );
    }

    constexpr inline long double	asinhl( long double value )
    {
        return asinh( value );
    }
    constexpr inline long double	asinl( long double value )
    {
        return asin( value );
    }
    constexpr inline long double	atan2l( long double x, long double y )
    {
        return atan2( x, y );
    }
    constexpr inline long double	atanhl( long double value )
    {
        return atanh( value );
    }
    constexpr inline long double	atanl( long double value )
    {
        return atan( value );
    }
    constexpr inline long double	cbrtl( long double value )
    {
        return cbrt( value );
    }
    constexpr inline long double	ceill( long double value )
    {
        return ceil( value );
    }
    constexpr inline long double	copysignl( long double x, long double y) __pure2
    {
        return copysign( x, y );
    }
    constexpr inline long double	coshl( long double value )
    {
        return cosh( value );
    }
    constexpr inline long double	cosl( long double value )
    {
        return cos( value );
    }
    constexpr inline long double	erfcl( long double value )
    {
        return erfc( value );
    }
    constexpr inline long double	erfl( long double value )
    {
        return erf( value );
    }
    constexpr inline long double	exp2l( long double value )
    {
        return exp2( value );
    }
    constexpr inline long double	expl( long double value )
    {
        return exp( value );
    }
    constexpr inline long double	expm1l( long double value )
    {
        return expm1( value );
    }
    constexpr inline long double	fabsl( long double value ) __pure2
    {
        return fabs( value );
    }
    constexpr inline long double	fdiml( long double x, long double y )
    {
        return fdim( x, y );
    }
    constexpr inline long double	floorl( long double value )
    {
        return floor( value );
    }
    constexpr inline long double	fmal( long double a, long double b, long double c )
    {
        return fma( a, b, c );
    }
    constexpr inline long double	fmaxl( long double a, long double b ) __pure2
    {
        return fmax( a, b );
    }
    constexpr inline long double	fminl( long double a, long double b ) __pure2
    {
        return fmin( a, b );
    }
    constexpr inline long double	fmodl( long double x, long double y )
    {
        return fmod( x, y );
    }
    constexpr inline long double	frexpl( long double value, int* exp ) /* fundamentally !__pure2 */
    {
        return frexp( value, exp );
    }
    constexpr inline long double	hypotl( long double x, long double y )
    {
        return hypot( x, y );
    }
    constexpr inline int		ilogbl( long double value ) __pure2
    {
        return ilogb( value );
    }
    constexpr inline long double	ldexpl( long double arg, int exp )
    {
        return ldexp( arg, exp );
    }
    constexpr inline long double	lgammal( long double value )
    {
        return lgamma( value );
    }
    constexpr inline long long	llrintl( long double value )
    {
        return llrint( value );
    }
    constexpr inline long long	llroundl( long double value )
    {
        return llround( value );
    }
    constexpr inline long double	log10l( long double value )
    {
        return log10( value );
    }
    constexpr inline long double	log1pl( long double value )
    {
        return log1p( value );
    }
    constexpr inline long double	log2l( long double value )
    {
        return log2( value );
    }
    constexpr inline long double	logbl( long double value )
    {
        return logb( value );
    }
    constexpr inline long double	logl( long double value )
    {
        return log( value );
    }
    constexpr inline long		lrintl( long double value )
    {
        return lrint( value );
    }
    constexpr inline long		lroundl( long double value )
    {
        return lround( value );
    }
    constexpr inline long double	modfl( long double x, long double* iptr ) /* fundamentally !__pure2 */
    {
        return modf( x, reinterpret_cast<double*>( iptr ) );
    }
    inline long double	nanl( const char* s ) __pure2
    {
        return nan( s );
    }
    constexpr inline long double	nearbyintl( long double value )
    {
        return nearbyint( value );
    }
    constexpr inline long double	nextafterl( long double from, long double to )
    {
        return nextafter( from, to );
    }
    constexpr inline double		nexttoward( double from, long double to );
    constexpr inline float		nexttowardf( float from, long double to );
    
    constexpr inline long double	nexttowardl( long double from, long double to )
    {
        return nexttoward( from, to );
    }
    constexpr inline long double	powl( long double base, long double exponent )
    {
        return pow( base, exponent );
    }
    constexpr inline long double	remainderl( long double x, long double y )
    {
        return remainder( x, y );
    }
    constexpr inline long double	remquol( long double x, long double y, int* quo )
    {
        return remquo( x, y, quo );
    }
    constexpr inline long double	rintl( long double value )
    {
        return rint( value );
    }
    constexpr inline long double	roundl( long double value )
    {
        return round( value );
    }
    constexpr inline long double	scalblnl( long double arg, long exp )
    {
        return scalbln( arg, exp );
    }
    constexpr inline long double	scalbnl( long double arg, int exp )
    {
        return scalbn( arg, exp );
    }
    constexpr inline long double	sinhl( long double value )
    {
        return sinh( value );
    }
    constexpr inline long double	sinl( long double value )
    {
        return sin( value );
    }
    constexpr inline long double	sqrtl( long double value )
    {
        return sqrt( value );
    }
    constexpr inline long double	tanhl( long double value )
    {
        return tanh( value );
    }
    constexpr inline long double	tanl( long double value )
    {
        return tan( value );
    }
    
    constexpr inline long double	tgammal( long double value )
    {
        return tgamma( value );
    }
    
    constexpr inline long double	truncl( long double value )
    {
        return trunc( value );
    }
#endif /*HAS_REAL_LONG_DOUBLE*/


    /* Reentrant version of lgammal. */
//#if __BSD_VISIBLE
    constexpr inline long double	lgammal_r( long double x, int* signgamp )
    {
        return lgamma_r( x, signgamp );
    }

    /*
     * Single sine/cosine function.
     */
    constexpr inline void	sincosl( long double x, long double* sine, long double* cosine );
//#endif	/* __BSD_VISIBLE */

}

//#if defined(__cplusplus)
//}
//#endif
#endif /* !OPENLIBM_MATH_H */

#endif /* OPENLIBM_USE_HOST_MATH_H */
