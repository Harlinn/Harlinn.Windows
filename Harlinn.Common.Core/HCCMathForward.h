#pragma once
#ifndef HCCMATHFORWARD_H_
#define HCCMATHFORWARD_H_
/*
   Copyright 2024 Espen Harlinn

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

    constexpr inline bool IsSameValue( double first, double second ) noexcept;
    constexpr inline bool IsSameValue( float x, float y ) noexcept;
    constexpr inline bool IsZero( double x ) noexcept;
    constexpr inline bool IsZero( float x ) noexcept;

    template< typename T>
        requires IsUnsignedInteger<std::remove_cvref_t<T>> || IsBoolean<std::remove_cvref_t<T>>
    constexpr inline T signum( T val ) noexcept;

    template< typename T>
        requires IsSignedInteger<std::remove_cvref_t<T>>
    constexpr inline T signum( T val ) noexcept;

    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    constexpr inline T signum( T val ) noexcept;

    inline constexpr double ScaleByN( double x, int n ) noexcept;
    inline constexpr float ScaleByN( float x, int n ) noexcept;
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline constexpr std::remove_cvref_t<FloatT> FMod( FloatT x, FloatT y ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Exp( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> CopySign( T magnitude, T signValue ) noexcept;


    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsNaN( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsNaN( T val ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsInf( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsInf( T val ) noexcept;

    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;
    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept;

    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept;
    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool SignBit( T val ) noexcept;


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::pair<double, int> FRExp( T val ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int* exp ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int& exp ) noexcept;

    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::pair<std::remove_cvref_t<ValueT>, std::remove_cvref_t<ValueT>> ModF( ValueT val ) noexcept;
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT* integerPart ) noexcept;
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT& integerPart ) noexcept;

    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept;
    template<typename T, typename ...Args>
        requires IsFloatingPoint<T> || IsInteger<T>
    constexpr inline T Min( T first, T second, Args... remaining ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept;

    template<typename T, typename ...Args>
        requires IsFloatingPoint<T> || IsInteger<T>
    constexpr inline T Max( T first, T second, Args... remaining ) noexcept;


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T value ) noexcept;
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T value ) noexcept;

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

    template<typename T>
        requires requires( const T& t1, const T& t2 )
        {
            { t1 < t2 }->std::convertible_to<bool>;
        }
    constexpr inline const T& Clamp( const T& value, const T& minimumValue, const T& maximumValue );


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextDown( T x ) noexcept;
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextUp( T x ) noexcept;

    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    constexpr inline std::remove_cvref_t<T> Deg2Rad( T angleInDegrees ) noexcept;

    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    constexpr inline std::remove_cvref_t<T> Rad2Deg( T angleInRadians ) noexcept;

    inline constexpr double NextAfter( double x, double y ) noexcept;
    inline constexpr float NextAfter( float x, float y ) noexcept;

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Sqrt( T x ) noexcept;







}

#endif