#pragma once
#ifndef HCCMATHFORWARD_H_
#define HCCMATHFORWARD_H_
/*
   Copyright 2024-2025 Espen Harlinn

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

#include "HCCLib.h"

namespace Harlinn::Common::Core::Math
{
    template<typename T>
    concept FloatingPointType = std::is_floating_point_v<T>;

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
    constexpr inline std::decay_t<T> FMod( T x, T y ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Exp( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ExpM1( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Hypot( T x, T y ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Hypot( T x, T y, T z ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log1P( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log2( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log10( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Pow( T x, T y ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Sin( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ASin( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Cos( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ACos( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Tan( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T y, T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan2( T y, T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr void SinCos( T x, T& sinResult, T& cosResult ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr void SinCos( T x, T* sinResult, T* cosResult ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> J0( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> J1( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> JN( int n, T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Y0( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Y1( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> YN( int n, T x ) noexcept;



    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> CopySign( T magnitude, T signValue ) noexcept;


    template<IntegerType T>
    constexpr inline bool IsNaN( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool IsNaN( T val ) noexcept;
    template<ArithmeticType T, ArithmeticType ... Args>
    constexpr inline bool IsNaN( T val, Args&& ... args ) noexcept;

    template<IntegerType T>
    constexpr inline bool IsInf( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool IsInf( T val ) noexcept;
    template<ArithmeticType T, ArithmeticType ... Args>
    constexpr inline bool IsInf( T val, Args&& ... args ) noexcept;

    template<IntegerType T>
    constexpr inline bool IsFinite( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool IsFinite( T val ) noexcept;
    template<ArithmeticType T, ArithmeticType ... Args>
    constexpr inline bool IsFinite( T val, Args&& ... args ) noexcept;

    template<IntegerType T>
    constexpr inline bool IsNormal( T val ) noexcept;
    template<FloatingPointType T>
    constexpr inline bool IsNormal( T val ) noexcept;
    template<ArithmeticType T, ArithmeticType ... Args>
    constexpr inline bool IsNormal( T val, Args&& ... args ) noexcept;


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

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept;

    template<typename T1, typename T2, typename T3>
        requires IsArithmetic<T1>&& IsArithmetic<T2>&& IsArithmetic<T3>
    constexpr inline T1 Clamp( T1 value, T2 minimumValue, T3 maximumValue );


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan2( T x, T y ) noexcept;

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
    constexpr inline std::decay_t<T> Remainder( T x, T y ) noexcept;

    template<FloatingPointType T>
    constexpr inline std::decay_t<T> RemQuo( T x, T y, int* quo ) noexcept;




}

#endif