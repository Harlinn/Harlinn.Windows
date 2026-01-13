#pragma once
#ifndef HARLINN_MATH_MATHFORWARD_H_
#define HARLINN_MATH_MATHFORWARD_H_

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

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif

#include <Harlinn/Common/Utils.h>

#include <cmath>
#include <cfenv>
#include <complex>

#include <emmintrin.h>


namespace Harlinn::Math
{
    using namespace Harlinn::Common;

    template<FloatingPointType T>
    constexpr inline bool IsSameValue( T first, T second ) noexcept;
    template<IntegerType T>
    constexpr inline bool IsSameValue( T first, T second ) noexcept;

    template<FloatingPointType T>
    constexpr inline bool IsZero( T x ) noexcept;

    template<IntegerType T>
    constexpr inline bool IsZero( T x ) noexcept;

    template<UnsignedIntegerOrBooleanType T>
    constexpr inline T signum( T val ) noexcept;

    template<SignedIntegerType T>
    constexpr inline T signum( T val ) noexcept;

    template< FloatingPointType T>
    constexpr inline T signum( T val ) noexcept;

    inline constexpr double ScaleBN( double x, int n ) noexcept;
    inline constexpr float ScaleBN( float x, int n ) noexcept;

    template<FloatingPointType T>
    constexpr inline T FMod( T x, T y ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Exp( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Exp2( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Exp10( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ExpM1( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Hypot( T x, T y ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Hypot( T x, T y, T z ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Log( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Log1P( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Log2( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Log10( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Pow( T x, T y ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Sin( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ASin( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Cos( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ACos( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Tan( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ATan( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ATan( T y, T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ATan2( T y, T x ) noexcept;

    template<FloatingPointType T>
    inline constexpr void SinCos( T x, T& sinResult, T& cosResult ) noexcept;

    template<FloatingPointType T>
    inline constexpr void SinCos( T x, T* sinResult, T* cosResult ) noexcept;

    template<FloatingPointType T>
    constexpr inline T SinH( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ASinH( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T CosH( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ACosH( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T TanH( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ATanH( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T J0( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T J1( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T JN( int n, T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Y0( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Y1( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T YN( int n, T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Erf( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ErfC( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T TGamma( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T LGamma( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T CopySign( T magnitude, T signValue ) noexcept;


    template<IntegerType T>
    constexpr inline bool IsNaN( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool IsNaN( T val ) noexcept;
    template<ArithmeticType T, ArithmeticType ... Args>
    constexpr inline bool IsNaN( T val, Args ... args ) noexcept;

    template<IntegerType T>
    constexpr inline bool IsInf( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool IsInf( T val ) noexcept;
    template<ArithmeticType T, ArithmeticType ... Args>
    constexpr inline bool IsInf( T val, Args ... args ) noexcept;

    template<IntegerType T>
    constexpr inline bool IsFinite( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool IsFinite( T val ) noexcept;
    template<ArithmeticType T, ArithmeticType ... Args>
    constexpr inline bool IsFinite( T val, Args ... args ) noexcept;

    template<IntegerType T>
    constexpr inline bool IsNormal( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool IsNormal( T val ) noexcept;
    template<ArithmeticType T, ArithmeticType ... Args>
    constexpr inline bool IsNormal( T val, Args ... args ) noexcept;


    template<SignedIntegerType T>
    constexpr inline T Abs( T val ) noexcept;
    template<UnsignedIntegerType T>
    constexpr inline T Abs( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline T Abs( T val ) noexcept;

    template<SignedIntegerType T>
    constexpr inline T FastAbs( T val ) noexcept;
    template<UnsignedIntegerType T>
    constexpr inline T FastAbs( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline T FastAbs( T val ) noexcept;

    template<SignedIntegerType T>
    constexpr inline bool SignBit( T val ) noexcept;
    template<UnsignedIntegerType T>
    constexpr inline bool SignBit( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool SignBit( T val ) noexcept;


    template<FloatingPointType T>
    constexpr inline std::pair<T, int> FRExp( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline T FRExp( T val, int* exp ) noexcept;
    template<FloatingPointType T>
    constexpr inline T FRExp( T val, int& exp ) noexcept;

    template<FloatingPointType T>
    constexpr inline std::pair<T, T> ModF( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline T ModF( T val, T* integerPart ) noexcept;
    template<FloatingPointType T>
    constexpr inline T ModF( T val, T& integerPart ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Min( T first, T second ) noexcept;
    template<IntegerType T>
    constexpr inline T Min( T first, T second ) noexcept;
    template<FloatingPointType T, FloatingPointType ...Args>
    constexpr inline T Min( T first, T second, Args... remaining ) noexcept;
    template<IntegerType T, IntegerType ...Args>
    constexpr inline T Min( T first, T second, Args... remaining ) noexcept;


    template<FloatingPointType T>
    constexpr inline T Max( T first, T second ) noexcept;
    template<IntegerType T>
    constexpr inline T Max( T first, T second ) noexcept;
    template<FloatingPointType T, FloatingPointType ...Args>
    constexpr inline T Max( T first, T second, Args... remaining ) noexcept;
    template<IntegerType T, IntegerType ...Args>
    constexpr inline T Max( T first, T second, Args... remaining ) noexcept;


    template<FloatingPointType T>
    constexpr inline T Trunc( T value ) noexcept;
    template<IntegerType T>
    constexpr inline T Trunc( T value ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Floor( T value ) noexcept;
    template<IntegerType T>
    constexpr inline T Floor( T value ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Ceil( T value ) noexcept;
    template<IntegerType T>
    constexpr inline T Ceil( T value ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Round( T value ) noexcept;
    template<IntegerType T>
    constexpr inline T Round( T value ) noexcept;

    template<ArithmeticType T1, ArithmeticType T2, ArithmeticType T3>
    constexpr inline T1 Clamp( T1 value, T2 minimumValue, T3 maximumValue ) noexcept;

    template<ArithmeticType T, ArithmeticType U>
    constexpr inline auto Lerp( T a, T b, U t ) noexcept;

    template<FloatingPointType T>
    inline constexpr T NextDown( T x ) noexcept;
    template<FloatingPointType T>
    inline constexpr T NextUp( T x ) noexcept;

    template< FloatingPointType T>
    constexpr inline T Deg2Rad( T angleInDegrees ) noexcept;

    template< FloatingPointType T>
    constexpr inline T Rad2Deg( T angleInRadians ) noexcept;

    inline constexpr double NextAfter( double x, double y ) noexcept;
    inline constexpr float NextAfter( float x, float y ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Sqrt( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T ReciprocalSqrt( T x ) noexcept;

    template<FloatingPointType T>
    constexpr inline T Cbrt( T x ) noexcept;


    template<FloatingPointType T>
    constexpr inline T Remainder( T x, T y ) noexcept;

    template<FloatingPointType T>
    constexpr inline T RemQuo( T x, T y, int* quo ) noexcept;

    template<FloatingPointType T>
    constexpr inline T FDim( T x, T y ) noexcept;

    template<IntegerType T>
    inline constexpr T FMA( T a, T b, T c ) noexcept;

    template<FloatingPointType T>
    inline constexpr T FMA( T a, T b, T c ) noexcept;
}


#endif
