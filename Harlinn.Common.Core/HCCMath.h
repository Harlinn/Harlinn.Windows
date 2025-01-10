#pragma once
#ifndef __HCCMATH_H__
#define __HCCMATH_H__
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

#include "HCCSIMD.h"
#include "HCCMathForward.h"
#include "HCCFloatingPoint.h"
#include "Internal/Math/sqrt.h"
#include "Internal/Math/trigonometry.h"

#include "Internal/Math/constexpr_math.h"

namespace Harlinn::Common::Core::Math
{
    template<typename ArthmeticT>
    struct Constants : public std::false_type
    { };

    template<>
    struct Constants<float> : public std::true_type
    {
        using ValueType = float;
        static constexpr ValueType ShadowEpsilon = static_cast< ValueType >( 0.0001 );

        static constexpr ValueType MinusOne = -1.f;
        static constexpr ValueType MinusZero = -0.f;
        static constexpr ValueType Zero = 0.f;
        static constexpr ValueType One = 1.f;
        static constexpr ValueType Two = 2.f;
        static constexpr ValueType Three = 3.f;
        
        static constexpr ValueType Pi = static_cast< ValueType >( 3.14159265358979323846 );
        static constexpr ValueType NegativePi = -Pi;
        static constexpr ValueType PiTimes2 = static_cast< ValueType >( 2. * M_PI );
        static constexpr ValueType InvPi = static_cast< ValueType >( 0.31830988618379067154 );
        static constexpr ValueType Inv2Pi = static_cast< ValueType >( 0.15915494309189533577 );
        static constexpr ValueType Inv4Pi = static_cast< ValueType >( 0.07957747154594766788 );
        static constexpr ValueType PiOver2 = static_cast< ValueType >( 1.57079632679489661923 );
        static constexpr ValueType PiOver4 = static_cast< ValueType >( 0.78539816339744830961 );
        static constexpr ValueType Sqrt2 = static_cast< ValueType >( 1.41421356237309504880 );
        static constexpr ValueType Infinity = std::numeric_limits<ValueType >::infinity( );

        static constexpr ValueType MachineEpsilon = std::numeric_limits<ValueType>::epsilon( ) * 0.5f;
        
        static constexpr ValueType OneMinusEpsilon = 0x1.fffffep-1f;


    };
    template<>
    struct Constants<double> : public std::true_type
    {
        using ValueType = double;
        static constexpr ValueType ShadowEpsilon = static_cast< ValueType >( 0.0001 );

        static constexpr ValueType MinusOne = -1.;
        static constexpr ValueType MinusZero = -0.;
        static constexpr ValueType Zero = 0.;
        static constexpr ValueType One = 1.;
        static constexpr ValueType Two = 2.;
        static constexpr ValueType Three = 3.;
        static constexpr ValueType Pi = 3.14159265358979323846;
        static constexpr ValueType NegativePi = -Pi;
        static constexpr ValueType PiTimes2 = 2. * M_PI;
        static constexpr ValueType InvPi = 0.31830988618379067154;
        static constexpr ValueType Inv2Pi = 0.15915494309189533577;
        static constexpr ValueType Inv4Pi = 0.07957747154594766788;
        static constexpr ValueType PiOver2 = 1.57079632679489661923;
        static constexpr ValueType PiOver4 = 0.78539816339744830961;
        static constexpr ValueType Sqrt2 = 1.41421356237309504880;
                                                                   
        static constexpr ValueType Infinity = std::numeric_limits<ValueType>::infinity( );

        static constexpr ValueType MachineEpsilon = std::numeric_limits<ValueType>::epsilon( ) * 0.5;
        static constexpr double OneMinusEpsilon = 0x1.fffffffffffffp-1;

    };



    /// <summary>
    /// Tests whether two double precision floating
    /// point values holds the same value. This function
    /// returns true if both hold the same NaN value.
    /// </summary>
    /// <param name="first">
    /// A double precision floating point value.
    /// </param>
    /// <param name="second">
    /// A double precision floating point value.
    /// </param>
    /// <returns>
    /// true if both arguments are binary equivalent, otherwise false.
    /// </returns>
    constexpr inline bool IsSameValue( double first, double second ) noexcept
    {
        return std::bit_cast<Int64>( first ) == std::bit_cast<Int64>( second );
    }
    /// <summary>
    /// Tests whether two single precision floating
    /// point values holds the same value. This function
    /// returns true if both hold the same NaN value.
    /// </summary>
    /// <param name="first">
    /// A single precision floating point value.
    /// </param>
    /// <param name="second">
    /// A single precision floating point value.
    /// </param>
    /// <returns>
    /// true if both arguments are binary equivalent, otherwise false.
    /// </returns>
    constexpr inline bool IsSameValue( float x, float y ) noexcept
    {
        return std::bit_cast<Int32>( x ) == std::bit_cast<Int32>( y );
    }

    
    /// <summary>
    /// Tests if a double precision floating value is zero.
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value.
    /// </param>
    /// <returns>
    /// true if the argument is zero, otherwise false.
    /// </returns>
    constexpr inline bool IsZero( double x ) noexcept
    {
        return ( std::bit_cast<Int64>( x ) & 0x7FFFFFFFFFFFFFFF ) == 0;
    }
    /// <summary>
    /// Tests if a double precision floating value is zero.
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value.
    /// </param>
    /// <returns>
    /// true if the argument is zero, otherwise false.
    /// </returns>
    constexpr inline bool IsZero( float x ) noexcept
    {
        return ( std::bit_cast<Int32>( x ) & 0x7FFFFFFF ) == 0;
    }


    /// <summary>
    /// <para>
    /// Returns the sign of a value for a bool or an unsigned integer type.
    /// </para>
    /// <para>
    /// This function treats bool as an unsigned integer.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// bool or an unsigned integer type.
    /// </typeparam>
    /// <param name="val">
    /// The value to test.
    /// </param>
    /// <returns>
    /// <para>
    /// If invoked with a bool this function returns true if the value is not false, otherwise false.
    /// </para>
    /// <para>
    /// If invoked with an unsigned integer type this function returns 1 if the value is greater than 0, otherwise 0.
    /// </para>
    /// </returns>
    template< typename T>
        requires IsUnsignedInteger<std::remove_cvref_t<T>> || IsBoolean<std::remove_cvref_t<T>>
    constexpr inline T signum( T val ) noexcept
    {
        constexpr T zero = static_cast<T>( 0 );
        return static_cast<T>( val > zero ? 1 : 0 );
    }

    /// <summary>
    /// Returns the sign of a value for a signed integer type.
    /// </summary>
    /// <typeparam name="T">
    /// Any signed integer type.
    /// </typeparam>
    /// <param name="val">
    /// The value to test.
    /// </param>
    /// <returns>
    /// Returns:
    /// <list type="bullet">
    /// <item>-1 if val is less than zero.</item>
    /// <item>0 if val is equal to zero.</item>
    /// <item>1 if val is greater than zero.</item>
    /// </list>
    /// </returns>
    template< typename T>
        requires IsSignedInteger<std::remove_cvref_t<T>>
    constexpr inline T signum( T val ) noexcept
    {
        constexpr T zero = static_cast< T >( 0 );
        constexpr T one = static_cast< T >( 1 );
        constexpr T minusOne = static_cast< T >( -1 );
        return val > zero ? one : ( val < zero ? minusOne : zero );
    }

    /// <summary>
    /// Returns the sign of a value for a floating point type.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// The value to test.
    /// </param>
    /// <returns>
    /// Returns:
    /// <list type="bullet">
    /// <item>-1.0 if val is less than zero.</item>
    /// <item>0.0 if val is equal to zero.</item>
    /// <item>1.0 if val is greater than zero.</item>
    /// </list>
    /// </returns>
    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    constexpr inline T signum( T val ) noexcept
    {
        constexpr T zero = static_cast<T>( 0 );
        constexpr T one = static_cast<T>( 1 );
        constexpr T minusOne = static_cast<T>( -1 );
        if constexpr ( sizeof( std::remove_cvref_t<T> ) == 4 )
        {
            UInt32 bits = std::bit_cast<UInt32, T>( val );
            return bits & 0x7FFFFFFF ? bits & 0x80000000 ? minusOne : one : zero;
        }
        else
        {
            UInt64 bits = std::bit_cast<UInt64, T>( val );
            return bits & 0x7FFFFFFFFFFFFFFF ? bits & 0x8000000000000000 ? minusOne : one : zero;
        }
    }

    

    /// <summary>
    /// Converts an angle in degrees into the corresponding
    /// angle in radians.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="angleInDegrees">
    /// The angle in degrees.
    /// </param>
    /// <returns>
    /// The angle in radians.
    /// </returns>
    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    constexpr inline std::remove_cvref_t<T> Deg2Rad( T angleInDegrees ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        constexpr FloatT factor = static_cast<FloatT>( M_PI_4/45.0 );
        return angleInDegrees * factor;
    }
    /// <summary>
    /// Converts an angle in radians into the corresponding
    /// angle in degrees.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="angleInRadians">
    /// The angle in radians.
    /// </param>
    /// <returns>
    /// The angle in degrees.
    /// </returns>
    template< typename T>
        requires IsFloatingPoint<std::remove_cvref_t<T>>
    constexpr inline std::remove_cvref_t<T> Rad2Deg( T angleInRadians ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        constexpr FloatT factor = static_cast<FloatT>( 45.0/M_PI_4 );
        return angleInRadians * factor;
    }

    /// <summary>
    /// <para>
    /// Returns the next representable value of x in the direction of y. If x equals to y, y is returned.
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value.
    /// </param>
    /// <param name="y">
    /// A double precision floating point value.
    /// </param>
    /// <returns>
    /// The next representable value of x in the direction of y. is returned. If x equals y, then y is returned
    /// </returns>
    inline constexpr double NextAfter( double x, double y ) noexcept
    {
        double t;

        Int32 hx = GetHigh32Bits<Int32>( x );
        UInt32 lx = GetLow32Bits<UInt32>( x );

        Int32 hy = GetHigh32Bits<Int32>( y );
        UInt32 ly = GetLow32Bits<UInt32>( y );

        // |x| 
        Int32 ix = hx & 0x7fffffff;
        // |y| 
        Int32 iy = hy & 0x7fffffff;

        // Are x or y NaN?
        if ( ( ( ix >= 0x7ff00000 ) && ( ( ix - 0x7ff00000 ) | lx ) != 0 ) || ( ( iy >= 0x7ff00000 ) && ( ( iy - 0x7ff00000 ) | ly ) != 0 ) )
        {
            return x + y;
        }
        if ( x == y )
        {
            // x=y, return y 
            return y;
        }
        if ( ( ix | lx ) == 0 )
        {			
            // x == 0 
            // return +-minsubnormal 
            x = From32BitsTo64Bits<double>( hy & 0x80000000, 1 );
            t = x * x;
            if ( t == x )
            {
                return t;
            }
            else
            {
                // raise underflow flag 
                return x;
            }
        }
        if ( hx >= 0 )
        {	
            // x > 0 
            if ( hx > hy || ( ( hx == hy ) && ( lx > ly ) ) )
            {	
                // x > y, x -= ulp 
                if ( lx == 0 )
                {
                    hx -= 1;
                }
                lx -= 1;
            }
            else
            {
                // x < y, x += ulp 
                lx += 1;
                if ( lx == 0 )
                {
                    hx += 1;
                }
            }
        }
        else
        {
            // x < 0 
            if ( hy >= 0 || hx > hy || ( ( hx == hy ) && ( lx > ly ) ) )
            {
                // x < y, x -= ulp 
                if ( lx == 0 )
                {
                    hx -= 1;
                }
                lx -= 1;
            }
            else
            {
                // x > y, x += ulp 
                lx += 1;
                if ( lx == 0 )
                {
                    hx += 1;
                }
            }
        }
        hy = hx & 0x7ff00000;
        if ( hy >= 0x7ff00000 )
        {
            // overflow  
            return x + x;
        }
        if ( hy < 0x00100000 )
        {
            // underflow 
            t = x * x;
            if ( t != x )
            {
                // raise underflow flag 
                y = From32BitsTo64Bits<double>( hx, lx );
                return y;
            }
        }
        x = From32BitsTo64Bits<double>( hx, lx );
        return x;
    }

    /// <summary>
    /// <para>
    /// Returns the next representable value of x in the direction of y. If x equals to y, y is returned.
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A single precision floating point value.
    /// </param>
    /// <param name="y">
    /// A single precision floating point value.
    /// </param>
    /// <returns>
    /// The next representable value of x in the direction of y. is returned. If x equals y, then y is returned
    /// </returns>
    inline constexpr float NextAfter( float x, float y ) noexcept
    {
        volatile float t;
        int32_t hx, hy, ix, iy;

        hx = std::bit_cast<Int32>( x );
        hy = std::bit_cast<Int32>( y );
        // |x| 
        ix = hx & 0x7fffffff;
        // |y| 
        iy = hy & 0x7fffffff;

        // Are x or y NaN?
        if ( ( ix > 0x7f800000 ) || ( iy > 0x7f800000 ) )
        {
            return x + y;
        }
        if ( x == y )
        {
            // x=y, return y 
            return y;
        }
        if ( ix == 0 )
        {
            // x == 0 
            // return +-minsubnormal 
            x = std::bit_cast<float>( ( hy & 0x80000000 ) | 1 );
            t = x * x;
            if ( t == x )
            {
                return t;
            }
            else
            {
                // raise underflow flag 
                return x;
            }
        }
        if ( hx >= 0 )
        {
            // x > 0 
            if ( hx > hy )
            {
                // x > y, x -= ulp 
                hx -= 1;
            }
            else
            {
                // x < y, x += ulp 
                hx += 1;
            }
        }
        else
        {
            // x < 0 
            if ( hy >= 0 || hx > hy )
            {
                // x < y, x -= ulp 
                hx -= 1;
            }
            else
            {
                // x > y, x += ulp 
                hx += 1;
            }
        }
        hy = hx & 0x7f800000;
        if ( hy >= 0x7f800000 )
        {
            // overflow  
            return x + x;
        }
        if ( hy < 0x00800000 )
        {
            // underflow 
            t = x * x;
            if ( t != x )
            {
                // raise underflow flag 
                y = std::bit_cast<float>( hx );
                return y;
            }
        }
        x = std::bit_cast<float>( hx );
        return x;
    }


    /// <summary>
    /// <para>
    /// Computes the square root of x.  
    /// </para>
    /// <para>
    /// The runtime performance of this implementation
    /// is equivalent to the runtime performance of std::sqrt.
    /// </para>
    /// <para>
    /// Unlike std::sqrt this implementation can be constexpr 
    /// evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point value.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// Returns the square root of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Sqrt( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::SqrtImpl( x );
        }
        else
        {
            using FloatType = std::remove_cvref_t<T>;
            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_sqrt_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_sqrt_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }
    static_assert( Sqrt(2.0) > 0.0 );


    namespace Internal
    {
        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr bool IsNaNImpl( T val ) noexcept
        {
            using FloatType = std::remove_cvref_t<T>;
            using UnsignedType = MakeUnsigned<FloatType>;
            constexpr UnsignedType fractionMask = FractionMask<FloatType>;
            constexpr UnsignedType exponentMask = ExponentMask<FloatType>;

            UnsignedType value = std::bit_cast<UnsignedType>( val );

            if ( ( value & exponentMask ) != exponentMask )
            {
                return false;
            }
            else
            {
                return value & fractionMask ? true : false;
            }
        }



        



        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr bool IsInfImpl( T val ) noexcept
        {
            using FloatType = std::remove_cvref_t<T>;
            using UnsignedType = MakeUnsigned<FloatType>;
            constexpr UnsignedType fractionMask = FractionMask<FloatType>;
            constexpr UnsignedType exponentMask = ExponentMask<FloatType>;

            constexpr UnsignedType MaxExponent = FloatingPoint<FloatType>::MaxExponent;
            UnsignedType value = std::bit_cast<UnsignedType>( val );
            return ( value & ( fractionMask | exponentMask ) ) == MaxExponent;
        }

        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr std::remove_cvref_t<T> AbsImpl( T val ) noexcept
        {
            using FloatType = std::remove_cvref_t<T>;
            using UnsignedType = MakeUnsigned<FloatType>;

            constexpr UnsignedType FractionMask = FloatingPoint<FloatType>::FractionMask;
            constexpr UnsignedType ExponentMask = FloatingPoint<FloatType>::ExponentMask;
            constexpr UnsignedType MaxExponent = FloatingPoint<FloatType>::MaxExponent;
            constexpr UnsignedType SignMask = FloatingPoint<FloatType>::SignMask;

            UnsignedType bits = std::bit_cast<UnsignedType>( val );
            // Test for neither NaN nor +/- infinity
            if ( ( bits & ExponentMask ) != MaxExponent ) [[likely]]
            {
                bits &= ~SignMask;
            }
            else
            {
                // NaN or Infinity
                if ( ( bits & FractionMask ) == 0 )
                {
                    // Infinity
                    bits &= ~SignMask;
                }
            }
            return std::bit_cast<FloatType>( bits );
        }

        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr bool SignBitImpl( T val ) noexcept
        {
            using FloatType = std::remove_cvref_t<T>;
            using UnsignedType = MakeUnsigned<FloatType>;
            constexpr UnsignedType SignMask = FloatingPoint<FloatType>::SignMask;

            UnsignedType value = std::bit_cast<UnsignedType>( val );
            return value & SignMask;
        }

        /// <summary>
        /// Get significand and exponent of val
        /// </summary>
        /// <typeparam name="T">floating point type</typeparam>
        /// <param name="val">Value to be decomposed.</param>
        /// <param name="exp">Reference to an int where the value of the exponent is stored.</param>
        /// <returns>The binary significand of val.</returns>
        template<typename T>
            requires IsFloatingPoint<std::remove_cvref_t<T>>
        inline constexpr std::remove_cvref_t<T> FRExpImpl( T val, int& exp ) noexcept
        {
            using ValueType = std::remove_cvref_t<T>;
            using FPType = FloatingPoint<ValueType>;
            using NormalizedType = NormalizedFloat<ValueType>;

            FPType fp( val );

            if ( !fp.IsInfOrNaN( ) )
            {
                if ( !fp.IsZero( ) )
                {
                    NormalizedType normalized( fp );
                    exp = normalized.Exponent( ) + 1;
                    normalized.SetExponent( 0 );
                    return normalized.AsFloatingPoint( );
                }
                else
                {
                    exp = 0;
                    return val;
                }
            }
            else
            {
                exp = 0xFFFFFFFF;
                return val;
            }
        }

        /// <summary>
        /// Breaks val into an integral and a fractional part.
        /// </summary>
        /// <typeparam name="T">floating point type</typeparam>
        /// <param name="val">Floating point value to break into parts.</param>
        /// <param name="intpart">
        /// Reference to an object, of the same type as val, where the 
        /// integral part is stored with the same sign as val</param>
        template<typename ValueT>
            requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
        inline constexpr std::remove_cvref_t<ValueT> ModFImpl( ValueT val, ValueT& intPart ) noexcept
        {
            using FloatType = std::remove_cvref_t<ValueT>;
            using FloatingPointType = FloatingPoint<FloatType>;
            FloatingPointType value( val );
            return value.ModF( intPart );
        }


        /// <summary>
        /// Returns a value with the magnitude of magnitudeVal and the sign of signVal.
        /// </summary>
        /// <typeparam name="T">floating point type</typeparam>
        /// <param name="magnitudeVal">
        /// Value with the magnitude of the resulting value.
        /// </param>
        /// <param name="sourceVal">
        /// Value with the sign of the resulting value.
        /// </param>
        /// <returns>
        /// The value with the magnitude of magnitudeVal and the sign of signVal.
        /// </returns>
        template<typename T>
            requires IsFloatingPoint<T>
        inline constexpr std::remove_cvref_t<T> CopySignImpl( T magnitudeVal, T signVal ) noexcept
        {
            using ValueType = std::remove_cvref_t<T>;
            using FPType = FloatingPoint<ValueType>;

            FPType fpMagnitude( magnitudeVal );
            FPType fpSign( signVal );
            fpMagnitude.SetSign( fpSign.Sign( ) );
            return fpMagnitude.AsFloatingPoint( );
        }



        template<typename T>
            requires IsFloatingPoint<T>
        constexpr T LerpImpl( T a, T b, T t ) noexcept
        {
            if ( ( a <= 0 && b >= 0 ) || ( a >= 0 && b <= 0 ) )
            {
                return t * b + ( 1 - t ) * a;
            }
            else if ( t == 1 )
            {
                return b;
            }
            T x = a + t * ( b - a );
            if ( ( t > 1 ) == ( b > a ) )
            {
                return b < x ? x : b;
            }
            else
            {
                return x < b ? x : b;
            }
        }

    }

    /// <summary>
    /// <para>
    /// Return the largest floating point number y of the same type 
    /// as x such that y < x. If no such y exists, e.g. if x is -Inf or NaN, then return x.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The largest floating point number y of the same type 
    /// as x such that y < x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextDown( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        using FloatingPointType = Math::FloatingPoint<FloatType>;
        using UIntType = FloatingPointType::UIntType;
        constexpr UIntType SignMask = FloatingPointType::SignMask;
        constexpr UIntType FractionMask = FloatingPointType::FractionMask;
        constexpr UIntType ExponentMask = FloatingPointType::ExponentMask;
        constexpr UIntType ExponentAndFractionMask = ExponentMask | FractionMask;
        constexpr UIntType MinusEpsilon = std::bit_cast<UIntType>( -std::numeric_limits<FloatType>::epsilon( ) );
        constexpr UIntType Highest = std::bit_cast<UIntType>( std::numeric_limits<FloatType>::max( ) );

        UIntType bits = std::bit_cast<UIntType>( x );

        
        if ( bits & SignMask )
        {
            if ( ( bits & ExponentMask ) < ExponentMask )
            {
                bits += 1;
            }
        }
        else
        {
            if ( ( bits & ExponentMask ) < ExponentMask )
            {
                if ( bits & ExponentAndFractionMask )
                {
                    bits -= 1;
                }
                else
                {
                    // 0
                    bits = SignMask + 1;
                }
            }
            else
            {
                // inf or NaN
                if ( ( bits & FractionMask ) == 0 )
                {
                    // Inf
                    bits = Highest;
                }
            }
        }
        return std::bit_cast<FloatType>( bits );
    }

    /// <summary>
    /// <para>
    /// Return the smallest floating point number y of the same 
    /// type as x such that x < y. If no such y exists, e.g. if x is 
    /// Inf or NaN, then return x.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The smallest floating point number y of the same 
    /// type as x such that x < y.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr std::remove_cvref_t<T> NextUp( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        using FloatingPointType = Math::FloatingPoint<FloatType>;
        using UIntType = FloatingPointType::UIntType;
        constexpr UIntType SignMask = FloatingPointType::SignMask;
        constexpr UIntType FractionMask = FloatingPointType::FractionMask;
        constexpr UIntType ExponentMask = FloatingPointType::ExponentMask;
        constexpr UIntType ExponentAndFractionMask = ExponentMask | FractionMask;
        constexpr UIntType Epsilon = std::bit_cast<UIntType>( std::numeric_limits<FloatType>::epsilon( ) );
        constexpr UIntType Lowest = std::bit_cast<UIntType>( std::numeric_limits<FloatType>::lowest( ) );

        UIntType bits = std::bit_cast<UIntType>( x );
        if ( bits & SignMask )
        {
            if ( ( bits & ExponentMask ) < ExponentMask )
            {
                if ( bits & ExponentAndFractionMask )
                {
                    bits -= 1;
                }
                else
                {
                    // -0
                    bits = 1;
                }
            }
            else
            {
                // -inf or NaN
                if ( (bits & FractionMask) == 0 )
                {
                    // -Inf
                    bits = Lowest;
                }
            }
        }
        else
        {
            if ( ( bits & ExponentMask ) < ExponentMask )
            {
                bits += 1;
            }
        }
        return std::bit_cast<FloatType>( bits );
    }

    /// <summary>
    /// IsNaN for integer types, always returns false.
    /// </summary>
    /// <typeparam name="T">
    /// Any integer type
    /// </typeparam>
    /// <param name="val">
    /// Integer value.
    /// </param>
    /// <returns>
    /// false
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsNaN( T val ) noexcept
    { 
        return false;
    }

    /// <summary>
    /// <para>
    /// Determines if the given floating point number, val, 
    /// is a not-a-number (NaN) value.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// true if val is a not-a-number (NaN) value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsNaN( T val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Internal::IsNaNImpl<T>( val );
        }
        else
        {
            return std::isnan( val );
        }
    }

    /// <summary>
    /// Integers cannot represent infinite, so this function
    /// always returns false.
    /// </summary>
    /// <typeparam name="T">
    /// Any integer type.
    /// </typeparam>
    /// <param name="val">
    /// An integer value.
    /// </param>
    /// <returns>
    /// false
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsInf( T val ) noexcept
    { 
        return false;
    }
    /// <summary>
    /// <para>
    /// Determines if the given floating point number val 
    /// is positive or negative infinity. 
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// true if val has an infinite value, otherwise false.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsInf( T val ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            return Internal::IsInfImpl<FloatT>( val );
        }
        else
        {
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return Internal::IsInfImpl<FloatT>( val );
            }
            else
            {
                return std::isinf( val );
            }
        }
    }

    /// <summary>
    /// <para>
    /// Computes the absolute value of a signed integer number. The behavior 
    /// is undefined if the result cannot be represented by the return type.
    /// </para>
    /// <para>
    /// In 2's complement systems, the absolute value of the most-negative value 
    /// is out of range, e.g. for 32-bit 2's complement type int, INT_MIN is -2147483648, 
    /// but the would-be result 2147483648 is greater than INT_MAX, which is 2147483647.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// Any signed integer type.
    /// </typeparam>
    /// <param name="val">
    /// A signed integer value.
    /// </param>
    /// <returns>
    /// The absolute value of val.
    /// </returns>
    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept
    { 
        if ( std::is_constant_evaluated( ) )
        {
            return val >= 0 ? val : -val;
        }
        else
        {
            return std::abs( val );
        }
    }
    static_assert( Abs( -1 ) == 1 );

    /// <summary>
    /// The absolute value of any unsigned integer
    /// is the same as its value.
    /// </summary>
    /// <typeparam name="T">
    /// Any unsigned integer type.
    /// </typeparam>
    /// <param name="val">
    /// An unsigned integer value.
    /// </param>
    /// <returns>
    /// val without any modification.
    /// </returns>
    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept
    {
        return val;
    }

    /// <summary>
    /// <para>
    /// Computes the absolute value of a floating point value.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The absolute value of val.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T> 
    constexpr inline std::remove_cvref_t<T> Abs( T val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Internal::AbsImpl( val );
        }
        else
        {
            using FloatT = std::remove_cvref_t<T>;
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return std::fabsf( val );
            }
            else
            {
                return std::fabs( val );
            }
        }
    }
    static_assert( Abs( -1.0 ) == 1.0 );

    /// <summary>
    /// Determines if the given signed integer value is negative.
    /// </summary>
    /// <typeparam name="T">
    /// Any signed integer type.
    /// </typeparam>
    /// <param name="val">
    /// A signed integer value.
    /// </param>
    /// <returns>
    /// returns true if the value is signed, otherwise false.
    /// </returns>
    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept
    { 
        using IntT = std::remove_cvref_t<T>;
        using UIntT = std::make_unsigned_t<IntT>;
        constexpr size_t ByteCount = sizeof( IntT );
        constexpr size_t ShiftCount = ( ( ByteCount - 1 ) * 8 ) + 7;
        constexpr UIntT UnsignedSignMask = static_cast< UIntT >( 1 ) << ShiftCount;
        constexpr IntT SignMask = std::bit_cast< IntT >( UnsignedSignMask );
        return (val & SignMask) != 0;
    }

    /// <summary>
    /// An Implementation of SignBit for unsigned integers
    /// that always returns false.
    /// </summary>
    /// <typeparam name="T">
    /// Any unsigned integer type.
    /// </typeparam>
    /// <param name="val">
    /// An unsigned integer value.
    /// </param>
    /// <returns>
    /// false
    /// </returns>
    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline bool SignBit( T val ) noexcept
    {
        return false;
    }

    /// <summary>
    /// <para>
    /// Determines if the given floating point number is negative.
    /// </para>
    /// <para>
    /// Currently this implementation is 70 % faster than std::signbit,
    /// and it can also be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// true if val is less than 0.0.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool SignBit( T val ) noexcept
    {
        return Internal::SignBitImpl( val );
    }

    /// <summary>
    /// <para>
    /// Decomposes the given floating point value val into a normalized 
    /// fraction and an integral power of two.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// <para>
    /// A std::pair&lt;&gt;> with the normalized fraction
    /// stored in first and the exponent stored in second.
    /// </para>
    /// <para>
    /// If val is zero, both first and second are set to zero.
    /// </para>
    /// <para>
    /// If val is not zero, and no errors occur, the function returns a value,
    /// x, in the range( -1; -0.5], [ 0.5; 1 ) in first and stores an integer value in 
    /// second such that result.first*2^( result.second ) = val.
    /// </para>
    /// <para>
    /// If the value to be stored in result.second is outside the range of int, the behavior is unspecified.
    /// </para>
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::pair<std::remove_cvref_t<T>,int> FRExp( T val ) noexcept
    { 
        std::pair<std::remove_cvref_t<T>, int> result;
        result.first = Internal::FRExpImpl<std::remove_cvref_t<T>>( val, result.second );
        return result;
    }

    /// <summary>
    /// <para>
    /// Decomposes the given floating point value val into a normalized 
    /// fraction and an integral power of two.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <param name="exp">
    /// A pointer to an integer value to store the exponent to.
    /// </param>
    /// <returns>
    /// <para>
    /// If val is zero, returns zero and stores zero in *exp.
    /// </para>
    /// <para>
    /// If val is not zero, and no errors occur, the function returns a value,
    /// x, in the range( -1; -0.5], [ 0.5; 1 ) and stores an integer value in 
    /// *exp such that x*2^( *exp ) = val.
    /// </para>
    /// <para>
    /// If the value to be stored in *exp is outside the range of int, the behavior is unspecified.
    /// </para>
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int* exp ) noexcept
    { 
        return Internal::FRExpImpl<std::remove_cvref_t<T>>( val, *exp );
    }
    /// <summary>
    /// <para>
    /// Decomposes the given floating point value val into a normalized 
    /// fraction and an integral power of two.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <param name="exp">
    /// A reference to an integer value to store the exponent to.
    /// </param>
    /// <returns>
    /// <para>
    /// If val is zero, returns zero and stores zero in exp.
    /// </para>
    /// <para>
    /// If val is not zero, and no errors occur, the function returns a value,
    /// x, in the range( -1; -0.5], [ 0.5; 1 ) and stores an integer value in 
    /// exp such that x*2^( exp ) = val.
    /// </para>
    /// <para>
    /// If the value to be stored in exp is outside the range of int, the behavior is unspecified.
    /// </para>
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FRExp( T val, int& exp ) noexcept
    { 
        return Internal::FRExpImpl<std::remove_cvref_t<T>>( val, exp );
    }

    /// <summary>
    /// <para>
    /// Decomposes floating-point value val into its integral and 
    /// fractional parts, each with the same type and sign as val.
    /// </para>
    /// <para>
    /// This implementation can also be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="ValueT">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// A std::pair&lt;ValueT,ValueT&gt; where first holds the integral part 
    /// of the result and second holds the fractional part.
    /// </returns>
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>> 
    constexpr inline std::pair<std::remove_cvref_t<ValueT>, std::remove_cvref_t<ValueT>> ModF( ValueT val ) noexcept
    {
        std::pair<std::remove_cvref_t<ValueT>, std::remove_cvref_t<ValueT>> result;
        result.second = Internal::ModFImpl( val, result.first );
        return result;
    }
    /// <summary>
    /// <para>
    /// Decomposes floating-point value val into its integral and 
    /// fractional parts, each with the same type and sign as val.
    /// </para>
    /// <para>
    /// This implementation can also be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="ValueT">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <param name="integerPart">
    /// A pointer to a variable of the ValueT floating point type
    /// that receives the integral part of val.
    /// </param>
    /// <returns>
    /// The fractional part of val.
    /// </returns>
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT* integerPart ) noexcept
    {
        return Internal::ModFImpl( val, *integerPart );
    }
    
    /// <summary>
    /// <para>
    /// Decomposes floating-point value val into its integral and 
    /// fractional parts, each with the same type and sign as val.
    /// </para>
    /// <para>
    /// This implementation can also be constexpr evaluated.
    /// </para>
    /// </summary>
    /// <typeparam name="ValueT">
    /// A floating point type.
    /// </typeparam>
    /// <param name="val">
    /// A floating point value.
    /// </param>
    /// <param name="integerPart">
    /// A reference to a variable of the ValueT floating point type
    /// that receives the integral part of val.
    /// </param>
    /// <returns>
    /// The fractional part of val.
    /// </returns>
    template<typename ValueT>
        requires IsFloatingPoint<std::remove_cvref_t<ValueT>>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT& integerPart ) noexcept
    {
        return Internal::ModFImpl( val, integerPart );
    }


#ifdef HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP
    /// <summary>
    /// Returns the smaller of the given values.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="first">
    /// The first floating point value.
    /// </param>
    /// <param name="second">
    /// The second floating point value.
    /// </param>
    /// <returns>
    /// Returns the smaller of <c>first</c> and <c>second</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            return std::min( first, second );
        }
        else
        {
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                FloatT result;
                _mm_store_ss( &result, _mm_min_ss( _mm_set_ss( first ), _mm_set_ss( second ) ) );
                return result;
            }
            else
            {
                return std::min( first, second );
                /*
                FloatT result;
                _mm_store_sd( &result, _mm_min_sd( _mm_set_sd( first ), _mm_set_sd( second ) ) );
                return result;
                */
            }
        }
    }
    /// <summary>
    /// Returns the smaller of the given values.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="first">
    /// The first integer value.
    /// </param>
    /// <param name="second">
    /// The second integer value.
    /// </param>
    /// <returns>
    /// Returns the smaller of <c>first</c> and <c>second</c>.
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept
    {
        return std::min( first, second );
    }
#else
    template<typename T>
    constexpr inline std::remove_cvref_t<T> Min( T first, T second ) noexcept
    {
        return std::min( first, second );
    }
#endif
    template<typename T, typename ...Args>
        requires IsFloatingPoint<T> || IsInteger<T>
    constexpr inline T Min( T first, T second, Args... remaining ) noexcept
    {
        return Min( Min( first, second ), remaining... );
    }


#ifdef HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP
    /// <summary>
    /// Returns the larger of the given values.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="first">
    /// The first floating point value.
    /// </param>
    /// <param name="second">
    /// The second floating point value.
    /// </param>
    /// <returns>
    /// Returns the larger of <c>first</c> and <c>second</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            return std::max( first, second );
        }
        else
        {
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                FloatT result;
                _mm_store_ss( &result, _mm_max_ss( _mm_set_ss( first ), _mm_set_ss( second ) ) );
                return result;
            }
            else
            {
                return std::max( first, second );
                /*
                FloatT result;
                _mm_store_sd( &result, _mm_max_sd( _mm_set_sd( first ), _mm_set_sd( second ) ) );
                return result;
                */
            }
        }
    }
    /// <summary>
    /// Returns the larger of the given values.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="first">
    /// The first integer value.
    /// </param>
    /// <param name="second">
    /// The second integer value.
    /// </param>
    /// <returns>
    /// Returns the larger of <c>first</c> and <c>second</c>.
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept
    {
        return std::max( first, second );
    }
#else
    template<typename T>
    constexpr inline std::remove_cvref_t<T> Max( T first, T second ) noexcept
    {
        return std::max( first, second );
    }
#endif

    template<typename T, typename ...Args>
        requires IsFloatingPoint<T> || IsInteger<T>
    constexpr inline T Max( T first, T second, Args... remaining ) noexcept
    {
        return Max( Max( first, second ), remaining... );
    }

    /// <summary>
    /// <para>
    /// Computes the nearest integer not greater in magnitude than value.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// A floating point value with the nearest integer not 
    /// greater in magnitude than value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T value ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;

        if ( std::is_constant_evaluated( ) )
        {
            FloatingPoint<FloatT> tmp( value );
            return tmp.Trunc( );
        }
        else
        {
#ifdef HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                return __truncf( value );
                /*
                float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC ) );
                return result;
                */
            }
#else
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __truncf( value );
            }
            else
            {
                return __trunc( value );
            }
#endif
        }
    }

    /// <summary>
    /// Just returns value.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// An integer value.
    /// </param>
    /// <returns>
    /// value
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Trunc( T value ) noexcept
    {
        return value;
    }


    /// <summary>
    /// <para>
    /// Computes the largest integer value not greater than value.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The largest integer value not greater than value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            FloatingPoint<FloatT> tmp( value );
            return tmp.Floor( );
        }
        else
        {
#ifdef HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __floorf( value );
            }
            else
            {
                return __floor( value );
            }
            /*
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC ) );
                return result;
            }
            */
#else
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __floorf( value );
            }
            else
            {
                return __floor( value );
            }

#endif
        }
    }

    /// <summary>
    /// Just returns value.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// An integer value.
    /// </param>
    /// <returns>
    /// value
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Floor( T value ) noexcept
    {
        return value;
    }


    /// <summary>
    /// <para>
    /// Computes the smallest integer value not less than value.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The smallest integer value not less than value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            FloatingPoint<FloatT> tmp( value );
            return tmp.Ceil( );
        }
        else
        {
#ifdef HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __ceilf( value );
            }
            else
            {
                return __ceil( value );
            }
            /*
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC ) );
                return result;
            }
            */
#else
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __ceilf( value );
            }
            else
            {
                return __ceil( value );
            }
#endif
        }
    }

    /// <summary>
    /// Just returns value.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// An integer value.
    /// </param>
    /// <returns>
    /// value
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Ceil( T value ) noexcept
    {
        return value;
    }


    
#ifdef HCCLIB_IMPLEMENTS_ROUND 
    /// <summary>
    /// <para>
    /// Computes the nearest integer to value, in floating-point format, 
    /// rounding halfway cases away from zero.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="value">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The nearest integer to value.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            FloatingPoint<FloatT> tmp( value );
            return tmp.Round( );
        }
        else
        {
#ifdef HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __roundf( value );
            }
            else
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC ) );
                return result;
            }
            /*
            if constexpr ( std::is_same_v<double, T> )
            {
                double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC ) );
                return result;
            }
            */
#else
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __roundf( value );
            }
            else
            {
                return __round( value );
            }
#endif
        }
    }

    /// <summary>
    /// Just returns value.
    /// </summary>
    /// <typeparam name="T">
    /// An integer type.
    /// </typeparam>
    /// <param name="value">
    /// An integer value.
    /// </param>
    /// <returns>
    /// value
    /// </returns>
    template<typename T>
        requires IsInteger<T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept
    {
        return value;
    }
#else
    template<typename T>
    constexpr inline std::remove_cvref_t<T> Round( T value ) noexcept
    {
        return std::round( value );
    }
#endif

#ifdef HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP
    /// <summary>
    /// <para>
    /// If the value is within [minimumValue, maximumValue], the function 
    /// returns value, otherwise returns the nearest boundary.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// Any type that supports the <c>&lt;<c> operator.
    /// </typeparam>
    /// <param name="value">
    /// The value to clamp.
    /// </param>
    /// <param name="minimumValue">
    /// The lower boundary.
    /// </param>
    /// <param name="maximumValue">
    /// The upper boundary.
    /// </param>
    /// <returns>
    /// The value within [minimumValue, maximumValue], or the nearest boundary.
    /// </returns>
    template<typename T>
        requires requires(const T& t1, const T& t2 )
        { 
            { t1 < t2 }->std::convertible_to<bool>;
        }
    constexpr inline const T& Clamp( const T& value, const T& minimumValue, const T& maximumValue )
    {
        if ( value < minimumValue )
        {
            return minimumValue;
        }
        else if ( maximumValue < value )
        {
            return maximumValue;
        }
        else
        {
            return value;
        }
    }

#else
    template<typename T>
    constexpr inline T& Clamp( const T& value, const T& minimumValue, const T& maximumValue )
    {
        return std::clamp( value, minimumValue, maximumValue );
    }
#endif

    /// <summary>
    /// <para>
    /// Computes the linear interpolation between a and b, if the 
    /// parameter t is inside [​0​, 1), the linear extrapolation otherwise, 
    /// i.e. the result of a + t * ( b - a ) with accounting 
    /// for floating point calculation imprecision.
    /// </para>
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <typeparam name="U"></typeparam>
    /// <param name="a">An arithmetic type.</param>
    /// <param name="b">An arithmetic type.</param>
    /// <param name="t">An arithmetic type.</param>
    /// <returns>
    /// The interpolated or extrapolated result. 
    /// </returns>
    template<typename T, typename U>
        requires ( ( IsInteger<T> || IsFloatingPoint<T> ) && ( IsInteger<U> || IsFloatingPoint<U> ) )
    constexpr inline std::conditional_t<IsFloatingPoint<T>, T, std::conditional_t<IsFloatingPoint<U>, U, T>> Lerp( T a, T b, U t ) noexcept
    {
        return Internal::LerpImpl( a, b, t );
    }

    /// <summary>
    /// <para>
    /// Composes a floating point value with the magnitude 
    /// of <c>magnitude</c> and the sign of <c>signValue</c>.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="magnitude">
    /// A floating point value.
    /// </param>
    /// <param name="signValue">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// A floating point value with the magnitude 
    /// of <c>magnitude</c> and the sign of <c>signValue</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> CopySign( T magnitude, T signValue ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        return Math::Internal::CopySignImpl<FloatT>( magnitude, signValue );
    }
    /// <summary>
    /// <para>
    /// Multiplies a double precision floating point value 
    /// <c>x</c> multplied by <c>FLT_RADIX</c> raised to power <c>n</c>.
    /// </para>
    /// <para>
    /// FLT_RADIX is the radix used by the representation 
    /// of the floating point types.
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value. 
    /// </param>
    /// <param name="n">
    /// An integer.
    /// </param>
    /// <returns>
    /// <c>x</c> multiplied by <c>FLT_RADIX</c> raised to power <c>n</c>
    /// </returns>
    inline constexpr double ScaleByN( double x, int n ) noexcept
    {
        constexpr double two54 = 1.80143985094819840000e+16;
        constexpr double twom54 = 5.55111512312578270212e-17;
        constexpr double huge = 1.0e+300;
        constexpr double tiny = 1.0e-300;

        Int32 hx = static_cast<Int32>( std::bit_cast<Int64>( x ) >> 32 );
        Int32 lx = static_cast<Int32>( std::bit_cast<Int64>( x ) );

        // extract exponent 
        int32_t k = ( hx & 0x7ff00000 ) >> 20;
        if ( k == 0 )
        {
            // 0 or subnormal x 
            if ( ( lx | ( hx & 0x7fffffff ) ) == 0 )
            {
                // +-0 
                return x;
            }
            x *= two54;
            hx = GetHigh32Bits<Int32>( x );
            k = ( ( hx & 0x7ff00000 ) >> 20 ) - 54;
            if ( n < -50000 )
            {
                // underflow
                return tiny * x;
            }
        }
        if ( k == 0x7ff )
        {
            // NaN or Inf 
            return x + x;
        }
        k = k + n;
        if ( k > 0x7fe )
        {
            // overflow  
            return huge * CopySign( huge, x );
        }
        if ( k > 0 )
        {
            // normal result 
            x = SetHigh32Bits<Int32>( x, ( hx & 0x800fffff ) | ( k << 20 ) );
            return x;
        }
        if ( k <= -54 )
        {
            // in case integer overflow in n+k 
            if ( n > 50000 )
            {
                // overflow
                return huge * CopySign( huge, x );
            }
            else
            {
                // underflow
                return tiny * CopySign( tiny, x );
            }
        }
        k += 54;
        // subnormal result 
        x = SetHigh32Bits<Int32>( x, ( hx & 0x800fffff ) | ( k << 20 ) );
        return x * twom54;
    }
    /// <summary>
    /// <para>
    /// Multiplies a double precision floating point value 
    /// <c>x</c> multplied by <c>FLT_RADIX</c> raised to power <c>n</c>.
    /// </para>
    /// <para>
    /// FLT_RADIX is the radix used by the representation 
    /// of the floating point types.
    /// </para>
    /// </summary>
    /// <param name="x">
    /// A double precision floating point value. 
    /// </param>
    /// <param name="n">
    /// An integer.
    /// </param>
    /// <returns>
    /// <c>x</c> multplied by <c>FLT_RADIX</c> raised to power <c>n</c>
    /// </returns>
    inline constexpr float ScaleByN( float x, int n ) noexcept
    {
        constexpr float two25 = 3.355443200e+07f;
        constexpr float twom25 = 2.9802322388e-08f;
        constexpr float huge = 1.0e+30f;
        constexpr float tiny = 1.0e-30f;

        Int32 ix = std::bit_cast<Int32>( x );

        // extract exponent 
        Int32 k = ( ix & 0x7f800000 ) >> 23;
        if ( k == 0 )
        {
            // 0 or subnormal x 
            if ( ( ix & 0x7fffffff ) == 0 )
            {
                // +-0 
                return x; 
            }
            x *= two25;
            ix = std::bit_cast<Int32>( x );
            k = ( ( ix & 0x7f800000 ) >> 23 ) - 25;
            if ( n < -50000 )
            {
                // underflow
                return tiny * x;
            }
        }
        if ( k == 0xff )
        {
            // NaN or Inf 
            return x + x;
        }
        k = k + n;
        if ( k > 0xfe )
        {
            // overflow  
            return huge * CopySign( huge, x ); 
        }
        if ( k > 0 )
        {
            // normal result 
            return std::bit_cast<float>( ( ix & 0x807fffff ) | ( k << 23 ) );
        }
        if ( k <= -25 )
        {
            if ( n > 50000 )
            {
                // in case integer overflow in n+k: overflow  
                return huge * copysignf( huge, x );
            }
            else
            {
                // underflow
                return tiny * copysignf( tiny, x );	
            }
        }
        // subnormal result 
        k += 25;
        x = std::bit_cast<float>( ( ix & 0x807fffff ) | ( k << 23 ) );
        return x * twom25;
    }

    namespace Internal
    {
        /// <summary>
        /// <para>
        /// Computes the double precision floating point remainder of the division operation <c>x / y</c>.
        /// </para>
        /// <para>
        /// This implementation can be constexpr evaluated, and
        /// improves runtime performance by 13.38 %.
        /// </para>
        /// </summary>
        /// <param name="x">
        /// A double precision floating point value. 
        /// </param>
        /// <param name="y">
        /// A double precision floating point value. 
        /// </param>
        /// <returns>
        /// The double precision floating point remainder of the division operation <c>x / y</c>.
        /// </returns>
        inline constexpr double FModImpl( double x, double y ) noexcept
        {
            UInt64 uxi = std::bit_cast< UInt64 >( x );
            int ex = uxi >> 52 & 0x7ff;
            int sx = uxi >> 63;

            UInt64 uyi = std::bit_cast< UInt64 >( y );
            int ey = uyi >> 52 & 0x7ff;

            uint64_t i;

            if ( uyi << 1 == 0 || IsNaN( y ) || ex == 0x7ff )
            {
                return ( x * y ) / ( x * y );
            }
            if ( uxi << 1 <= uyi << 1 )
            {
                if ( uxi << 1 == uyi << 1 )
                {
                    return 0 * x;
                }
                return x;
            }

            // normalize x and y 
            if ( !ex )
            {
                for ( i = uxi << 12; i >> 63 == 0; ex--, i <<= 1 );
                uxi <<= -ex + 1;
            }
            else
            {
                uxi &= static_cast< UInt64 >( -1 ) >> 12;
                uxi |= 1ULL << 52;
            }
            if ( !ey )
            {
                for ( i = uyi << 12; i >> 63 == 0; ey--, i <<= 1 )
                {
                    ;
                }
                uyi <<= -ey + 1;
            }
            else
            {
                uyi &= static_cast< UInt64 >( -1 ) >> 12;
                uyi |= 1ULL << 52;
            }

            // x mod y 
            for ( ; ex > ey; ex-- )
            {
                i = uxi - uyi;
                if ( i >> 63 == 0 )
                {
                    if ( i == 0 )
                        return 0 * x;
                    uxi = i;
                }
                uxi <<= 1;
            }
            i = uxi - uyi;
            if ( i >> 63 == 0 )
            {
                if ( i == 0 )
                    return 0 * x;
                uxi = i;
            }
            for ( ; uxi >> 52 == 0; uxi <<= 1, ex-- )
            {
                ;
            }

            // scale result 
            if ( ex > 0 )
            {
                uxi -= 1ULL << 52;
                uxi |= ( uint64_t )ex << 52;
            }
            else
            {
                uxi >>= -ex + 1;
            }
            uxi |= ( uint64_t )sx << 63;

            return std::bit_cast< double >( uxi );
        }


        /* e_fmodf.c -- float version of e_fmod.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
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

          /// <summary>
          /// <para>
          /// Computes the single precision floating point remainder of the division operation <c>x / y</c>.
          /// </para>
          /// <para>
          /// This implementation can be constexpr evaluated, and
          /// improves runtime performance by 89.59 %.
          /// </para>
          /// </summary>
          /// <param name="x">
          /// A single precision floating point value. 
          /// </param>
          /// <param name="y">
          /// A single precision floating point value. 
          /// </param>
          /// <returns>
          /// The single precision floating point remainder of the division operation <c>x / y</c>.
          /// </returns>
        inline constexpr float FModImpl( float x, float y ) noexcept
        {
            constexpr float one = 1.0;
            constexpr float Zero[ ] = { 0.0, -0.0 };

            Int32 n, hx, hy, hz, ix, iy, sx, i;

            hx = std::bit_cast< Int32 >( x );
            hy = std::bit_cast< Int32 >( y );
            // sign of x 
            sx = hx & 0x80000000;
            // |x| 
            hx ^= sx;
            // |y| 
            hy &= 0x7fffffff;

            // purge off exception values 
            if ( hy == 0 || ( hx >= 0x7f800000 ) || // y=0,or x not finite 
                ( hy > 0x7f800000 ) ) // or y is NaN 
            {
                return ( x * y ) / ( x * y );
            }
            if ( hx < hy )
            {
                // |x|<|y| return x 
                return x;
            }
            if ( hx == hy )
            {
                // |x|=|y| return x*0
                return Zero[ static_cast< UInt32 >( sx ) >> 31 ];
            }

            // determine ix = ilogb(x) 
            if ( hx < 0x00800000 )
            {
                // subnormal x 
                for ( ix = -126, i = ( hx << 8 ); i > 0; i <<= 1 )
                {
                    ix -= 1;
                }
            }
            else
            {
                ix = ( hx >> 23 ) - 127;
            }

            // determine iy = ilogb(y) 
            if ( hy < 0x00800000 )
            {
                // subnormal y 
                for ( iy = -126, i = ( hy << 8 ); i >= 0; i <<= 1 )
                {
                    iy -= 1;
                }
            }
            else
            {
                iy = ( hy >> 23 ) - 127;
            }

            // set up {hx,lx}, {hy,ly} and align y to x 
            if ( ix >= -126 )
            {
                hx = 0x00800000 | ( 0x007fffff & hx );
            }
            else
            {
                // subnormal x, shift x to normal 
                n = -126 - ix;
                hx = hx << n;
            }
            if ( iy >= -126 )
            {
                hy = 0x00800000 | ( 0x007fffff & hy );
            }
            else
            {
                // subnormal y, shift y to normal 
                n = -126 - iy;
                hy = hy << n;
            }

            // fix point fmod 
            n = ix - iy;
            while ( n-- )
            {
                hz = hx - hy;
                if ( hz < 0 )
                {
                    hx = hx + hx;
                }
                else
                {
                    if ( hz == 0 )
                    {
                        // return sign(x)*0 
                        return Zero[ static_cast< UInt32 >( sx ) >> 31 ];
                    }
                    hx = hz + hz;
                }
            }
            hz = hx - hy;
            if ( hz >= 0 )
            {
                hx = hz;
            }

            // convert back to floating value and restore the sign 
            if ( hx == 0 )
            {
                // return sign(x)*0 
                return Zero[ static_cast< UInt32 >( sx ) >> 31 ];
            }
            while ( hx < 0x00800000 )
            {
                // normalize x 
                hx = hx + hx;
                iy -= 1;
            }
            if ( iy >= -126 )
            {
                // normalize output 
                hx = ( ( hx - 0x00800000 ) | ( ( iy + 127 ) << 23 ) );
                x = std::bit_cast< float >( hx | sx );
            }
            else
            {
                // subnormal output 
                n = -126 - iy;
                hx >>= n;
                x = std::bit_cast< float >( hx | sx );
                // create necessary signal 
                x *= one;
            }
            // exact output 
            return x;
        }
    }

    /// <summary>
    /// <para>
    /// Computes the point remainder of the division operation <c>x / y</c>.
    /// </para>
    /// </summary>
    /// <typeparam name="FloatT">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value. 
    /// </param>
    /// <param name="y">
    /// A floating point value. 
    /// </param>
    /// <returns>
    /// The floating point remainder of the division operation <c>x / y</c>.
    /// </returns>
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline std::remove_cvref_t<FloatT> FMod( FloatT x, FloatT y ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::FModImpl( x, y );
        }
        else
        {
            return std::fmod( x, y );
        }
    }


    namespace Internal
    {
        /*
         * ====================================================
         * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
         *
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        // *
        inline constexpr double ExpImpl( double x ) noexcept
        {
            constexpr double one = 1.0;
            constexpr double halF[2] = { 0.5,-0.5 };
            constexpr double huge = 1.0e+300;
            constexpr double o_threshold = 7.09782712893383973096e+02;
            constexpr double u_threshold = -7.45133219101941108420e+02;
            constexpr double ln2HI[2] = { 6.93147180369123816490e-01, -6.93147180369123816490e-01 };
            constexpr double ln2LO[2] = { 1.90821492927058770002e-10,  -1.90821492927058770002e-10, };
            constexpr double invln2 = 1.44269504088896338700e+00;
            constexpr double P1 = 1.66666666666666019037e-01;
            constexpr double P2 = -2.77777777770155933842e-03;
            constexpr double P3 = 6.61375632143793436117e-05;
            constexpr double P4 = -1.65339022054652515390e-06;
            constexpr double P5 = 4.13813679705723846039e-08;

            constexpr double twom1000 = 9.33263618503218878990e-302;

            double y, hi = 0.0, lo = 0.0, c, t, twopk;
            int32_t k = 0, xsb;
            Int64 ax = std::bit_cast<Int64>( x );
            Int32 hx = static_cast<Int32>( ax >> 32 );

            // sign bit of x 
            xsb = ( hx >> 31 ) & 1;
            // high word of |x| 
            hx &= 0x7fffffff;

            // filter out non-finite argument 
            if ( hx >= 0x40862E42 )
            {
                // if |x|>=709.78... 
                if ( hx >= 0x7ff00000 )
                {
                    UInt32 lx = static_cast<UInt32>( ax );
                    if ( ( ( hx & 0xfffff ) | lx ) != 0 )
                    {
                        // NaN 
                        return x + x;
                    }
                    else
                    {
                        // exp(+-inf)={inf,0} 
                        return ( xsb == 0 ) ? x : 0.0;
                    }
                }
                else
                {
                    if ( x > o_threshold )
                    {
                        // overflow
                        volatile double val = huge;
                        return val * val;
                    }
                    else if ( x < u_threshold )
                    {
                        // underflow 
                        volatile double val = twom1000;
                        return val * val;
                    }
                }
            }

            // this implementation gives 2.7182818284590455 for exp(1.0),
            // which is well within the allowable error. however,
            // 2.718281828459045 is closer to the true value so we prefer that
            // answer, given that 1.0 is such an important argument value. 

            /*
            if ( x == 1.0 )
            {
                return 2.718281828459045235360;
            }
            */

            // argument reduction 
            if ( hx > 0x3fd62e42 )
            {
                // if  |x| > 0.5 ln2 
                if ( hx < 0x3FF0A2B2 )
                {
                    // and |x| < 1.5 ln2 
                    hi = x - ln2HI[xsb];
                    lo = ln2LO[xsb];
                    k = 1 - xsb - xsb;
                }
                else
                {
                    k = static_cast<Int32>( invln2 * x + halF[xsb] );
                    t = k;
                    // t*ln2HI is exact here 
                    hi = x - t * ln2HI[0];
                    lo = t * ln2LO[0];
                }
                x = hi - lo;
            }
            else if ( hx < 0x3e300000 )
            {
                // when |x|<2**-28 
                if ( huge + x > one )
                {
                    // trigger inexact 
                    return one + x;
                }
            }
            else k = 0;

            // x is now in primary range 
            t = x * x;
            if ( k >= -1021 )
            {
                twopk = From32BitsTo64Bits<double>( 0x3ff00000 + ( k << 20 ), 0 );
            }
            else
            {
                twopk = From32BitsTo64Bits<double>( 0x3ff00000 + ( ( k + 1000 ) << 20 ), 0 );
            }
            c = x - t * ( P1 + t * ( P2 + t * ( P3 + t * ( P4 + t * P5 ) ) ) );
            if ( k == 0 )
            {
                return one - ( ( x * c ) / ( c - 2.0 ) - x );
            }
            else
            {
                y = one - ( ( lo - ( x * c ) / ( 2.0 - c ) ) - hi );
            }
            if ( k >= -1021 )
            {
                if ( k == 1024 )
                {
                    return y * 2.0 * 0x1p1023;
                }
                return y * twopk;
            }
            else
            {
                return y * twopk * twom1000;
            }
        }

        /* e_expf.c -- float version of e_exp.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
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

        inline constexpr float ExpImpl( float x ) noexcept
        {

            constexpr float one = 1.0f;
            constexpr float halF[2] = { 0.5f,-0.5f };
            constexpr float huge = 1.0e+30f;
            constexpr float o_threshold = 8.8721679688e+01f;
            constexpr float u_threshold = -1.0397208405e+02f;
            constexpr float ln2HI[2] = { 6.9314575195e-01f, -6.9314575195e-01f };
            constexpr float ln2LO[2] = { 1.4286067653e-06f, -1.4286067653e-06f };
            constexpr float invln2 = 1.4426950216e+00f;

            // Domain [-0.34568, 0.34568], range ~[-4.278e-9, 4.447e-9]:
            // |x*(exp(x)+1)/(exp(x)-1) - p(x)| < 2**-27.74

            constexpr float P1 = 1.6666625440e-1f;
            constexpr float P2 = -2.7667332906e-3f;

            constexpr float twom100 = 7.8886090522e-31f;

            float y, hi = 0.0, lo = 0.0, c, t, twopk;
            Int32 k = 0, xsb;
            UInt32 hx = std::bit_cast<UInt32>( x );

            // sign bit of x 
            xsb = ( hx >> 31 ) & 1;
            // high word of |x| 
            hx &= 0x7fffffff;

            // filter out non-finite argument 
            if ( hx >= 0x42b17218 )
            {
                // if |x|>=88.721... 
                if ( hx > 0x7f800000 )
                {
                    // NaN 
                    return x + x;
                }
                if ( hx == 0x7f800000 )
                {
                    // exp(+-inf)={inf,0} 
                    return ( xsb == 0 ) ? x : 0.0f;
                }
                if ( x > o_threshold )
                {
                    // overflow 
#pragma warning(push)
#pragma warning(disable:4056)
                    return huge * huge;
#pragma warning(pop)
                }
                if ( x < u_threshold )
                {
                    // underflow 
                    return twom100 * twom100;
                }
            }

            // argument reduction 
            if ( hx > 0x3eb17218 )
            {
                // if  |x| > 0.5 ln2 
                if ( hx < 0x3F851592 )
                {
                    // and |x| < 1.5 ln2 
                    hi = x - ln2HI[xsb];
                    lo = ln2LO[xsb];
                    k = 1 - xsb - xsb;
                }
                else
                {
                    k = static_cast<Int32>( invln2 * x + halF[xsb] );
                    t = static_cast<float>( k );
                    // t*ln2HI is exact here 
                    hi = x - t * ln2HI[0];
                    lo = t * ln2LO[0];
                }
                x = hi - lo;
            }
            else if ( hx < 0x39000000 )
            {
                // when |x|<2**-14 
                if ( huge + x > one )
                {
                    // trigger inexact 
                    return one + x;
                }
            }
            else k = 0;

            // x is now in primary range 
            t = x * x;
            if ( k >= -125 )
            {
                twopk = std::bit_cast<float>( 0x3f800000 + ( k << 23 ) );
            }
            else
            {
                twopk = std::bit_cast<float>( 0x3f800000 + ( ( k + 100 ) << 23 ) );
            }
            c = x - t * ( P1 + t * P2 );
            if ( k == 0 )
            {
                return one - ( ( x * c ) / ( c - (float)2.0 ) - x );
            }
            else
            {
                y = one - ( ( lo - ( x * c ) / ( (float)2.0 - c ) ) - hi );
            }
            if ( k >= -125 )
            {
                if ( k == 128 )
                {
                    return y * 2.0F * 0x1p127F;
                }
                return y * twopk;
            }
            else
            {
                return y * twopk * twom100;
            }
        }
    }

    /// <summary>
    /// <para>
    /// Computes <c>e</c>, <c>2.7182818</c>, raised to the given power <c>x</c>.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// <c>e</c> raised to the given power <c>x</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Exp( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::ExpImpl( x );
        }
        else
        {
            return Math::Internal::ExpImpl( x );
            //return std::exp( x );
        }
    }


    namespace Internal
    {
    }

    /// <summary>
    /// <para>
    /// Computes the square root of the sum of the squares of x and y, 
    /// without undue overflow or underflow at intermediate stages of 
    /// the computation.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <param name="y">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The square root of the sum of the squares of x and y.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Hypot( T x, T y ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Sqrt( x * x + y * y );
        }
        else
        {   
            using FloatT = std::remove_cvref_t<T>;
            using Traits = SIMD::Traits<FloatT,2>;
            
            auto v = Traits::Set( y, x );
            v = Traits::Mul( v, v );
            v = Traits::HSum( v );
            v = Traits::Sqrt( v );
            return Traits::First( v );
        }
    }


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Hypot( T x, T y, T z ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Sqrt( x*x + y*y + z*z );
        }
        else
        {
            using FloatT = std::remove_cvref_t<T>;
            using Traits = SIMD::Traits<FloatT, 3>;

            auto v = Traits::Set( z, y, x );
            v = Traits::Mul( v, v );
            v = Traits::HSum( v );
            v = Traits::Sqrt( v );
            return Traits::First( v );

        }
    }


    namespace Internal
    {
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */

        constexpr inline double LogImpl( double x ) noexcept
        {
            constexpr double ln2_hi = 6.93147180369123816490e-01;
            constexpr double ln2_lo = 1.90821492927058770002e-10;
            constexpr double two54 = 1.80143985094819840000e+16;
            constexpr double Lg1 = 6.666666666666735130e-01;
            constexpr double Lg2 = 3.999999999940941908e-01;
            constexpr double Lg3 = 2.857142874366239149e-01;
            constexpr double Lg4 = 2.222219843214978396e-01;
            constexpr double Lg5 = 1.818357216161805012e-01;
            constexpr double Lg6 = 1.531383769920937332e-01;
            constexpr double Lg7 = 1.479819860511658591e-01; 
            constexpr double zero = 0.0;

            double hfsq, f, s, z, R, w, t1, t2, dk;
            int32_t k, i, j;

            Int64 ax = std::bit_cast<Int64> ( x );
            Int32 hx = static_cast<Int32>( ax >> 32 );
            UInt32 lx = static_cast<UInt32>( ax );

            k = 0;
            if ( hx < 0x00100000 )
            {
                // x < 2**-1022  
                if ( ( ( hx & 0x7fffffff ) | lx ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two54 / zero;
                    return -std::numeric_limits<double>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<double>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 54; 
                x *= two54; 
                ax = std::bit_cast<Int64> ( x );
                hx = static_cast<Int32>( ax >> 32 );
            }
            if ( hx >= 0x7ff00000 )
            {
                return x + x;
            }
            k += ( hx >> 20 ) - 1023;
            hx &= 0x000fffff;
            i = ( hx + 0x95f64 ) & 0x100000;
            // normalize x or x/2 
            ax = (static_cast<Int64>( hx | ( i ^ 0x3ff00000 ) ) << 32) | (ax & 0x00000000FFFFFFFF);
            x = std::bit_cast<double>( ax );
            
            k += ( i >> 20 );
            f = x - 1.0;
            if ( ( 0x000fffff & ( 2 + hx ) ) < 3 )
            {	
                // -2**-20 <= f < 2**-20 
                if ( f == zero )
                {
                    if ( k == 0 )
                    {
                        return zero;
                    }
                    else
                    {
                        dk = static_cast<double>(k);
                        return dk * ln2_hi + dk * ln2_lo;
                    }
                }
                R = f * f * ( 0.5 - 0.33333333333333333 * f );
                if ( k == 0 )
                {
                    return f - R;
                }
                else
                {
                    dk = static_cast<double>( k );
                    return dk * ln2_hi - ( ( R - dk * ln2_lo ) - f );
                }
            }
            s = f / ( 2.0 + f );
            dk = static_cast<double>( k );
            z = s * s;
            i = hx - 0x6147a;
            w = z * z;
            j = 0x6b851 - hx;
            t1 = w * ( Lg2 + w * ( Lg4 + w * Lg6 ) );
            t2 = z * ( Lg1 + w * ( Lg3 + w * ( Lg5 + w * Lg7 ) ) );
            i |= j;
            R = t2 + t1;
            if ( i > 0 )
            {
                hfsq = 0.5 * f * f;
                if ( k == 0 ) 
                    return f - ( hfsq - s * ( hfsq + R ) ); 
                else
                    return dk * ln2_hi - ( ( hfsq - ( s * ( hfsq + R ) + dk * ln2_lo ) ) - f );
            }
            else
            {
                if ( k == 0 ) 
                    return f - s * ( f - R ); 
                else
                    return dk * ln2_hi - ( ( s * ( f - R ) - dk * ln2_lo ) - f );
            }
        }


        /* e_logf.c -- float version of e_log.c.
         * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
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
        constexpr inline float LogImpl( float x ) noexcept
        {
            constexpr float ln2_hi = 6.9313812256e-01f;
            constexpr float ln2_lo = 9.0580006145e-06f;
            constexpr float two25 = 3.355443200e+07f;
                /* |(log(1+s)-log(1-s))/s - Lg(s)| < 2**-34.24 (~[-4.95e-11, 4.97e-11]). */
            constexpr float Lg1 = 0xaaaaaa.0p-24f;
            constexpr float Lg2 = 0xccce13.0p-25f;
            constexpr float Lg3 = 0x91e9ee.0p-25f;
            constexpr float Lg4 = 0xf89e26.0p-26f;

            constexpr float zero = 0.0f;

            float hfsq, f, s, z, R, w, t1, t2, dk;
            //int32_t k, ix, i, j;

            Int32 ix = std::bit_cast<Int32>( x );

            Int32 k = 0;
            if ( ix < 0x00800000 )
            {
                // x < 2**-126  
                if ( ( ix & 0x7fffffff ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two25 / zero;
                    return -std::numeric_limits<float>::infinity( );
                }
                if ( ix < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<float>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 25; 
                x *= two25; 
                ix = std::bit_cast<Int32>( x );
            }
            if ( ix >= 0x7f800000 )
            {
                return x + x;
            }
            k += ( ix >> 23 ) - 127;
            ix &= 0x007fffff;
            Int32 i = ( ix + ( 0x95f64 << 3 ) ) & 0x800000;

            // normalize x or x/2 
            x = std::bit_cast<float>( ix | ( i ^ 0x3f800000 ) );
            
            k += ( i >> 23 );
            f = x - 1.0f;
            if ( ( 0x007fffff & ( 0x8000 + ix ) ) < 0xc000 )
            {	
                // -2**-9 <= f < 2**-9 
                if ( f == zero )
                {
                    if ( k == 0 )
                    {
                        return zero;
                    }
                    else
                    {
                        dk = static_cast<float>( k );
                        return dk * ln2_hi + dk * ln2_lo;
                    }
                }
                R = f * f * ( 0.5f - (float)0.33333333333333333 * f );
                if ( k == 0 ) return f - R; else
                {
                    dk = static_cast<float>( k );
                    return dk * ln2_hi - ( ( R - dk * ln2_lo ) - f );
                }
            }
            s = f / ( 2.0f + f );
            dk = static_cast<float>( k );
            z = s * s;
            i = ix - ( 0x6147a << 3 );
            w = z * z;
            Int32 j = ( 0x6b851 << 3 ) - ix;
            t1 = w * ( Lg2 + w * Lg4 );
            t2 = z * ( Lg1 + w * Lg3 );
            i |= j;
            R = t2 + t1;
            if ( i > 0 )
            {
                hfsq = 0.5f * f * f;
                if ( k == 0 ) 
                    return f - ( hfsq - s * ( hfsq + R ) ); 
                else
                    return dk * ln2_hi - ( ( hfsq - ( s * ( hfsq + R ) + dk * ln2_lo ) ) - f );
            }
            else
            {
                if ( k == 0 ) 
                    return f - s * ( f - R ); 
                else
                    return dk * ln2_hi - ( ( s * ( f - R ) - dk * ln2_lo ) - f );
            }
        }
    }
    /// <summary>
    /// <para>
    /// Computes the natural, base e, logarithm of <c>x</c>.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The natural, base e, logarithm of <c>x</c>.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::LogImpl( x );
        }
        else
        {
            return Math::Internal::LogImpl( x );
            //return std::log( x );
        }
    }

    namespace Internal
    {
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        constexpr inline double Log1pCore( double f ) noexcept
        {
            constexpr double Lg1 = 6.666666666666735130e-01;
            constexpr double Lg2 = 3.999999999940941908e-01;
            constexpr double Lg3 = 2.857142874366239149e-01;
            constexpr double Lg4 = 2.222219843214978396e-01;
            constexpr double Lg5 = 1.818357216161805012e-01;
            constexpr double Lg6 = 1.531383769920937332e-01;
            constexpr double Lg7 = 1.479819860511658591e-01;

            double hfsq, s, z, R, w, t1, t2;

            s = f / ( 2.0 + f );
            z = s * s;
            w = z * z;
            t1 = w * ( Lg2 + w * ( Lg4 + w * Lg6 ) );
            t2 = z * ( Lg1 + w * ( Lg3 + w * ( Lg5 + w * Lg7 ) ) );
            R = t2 + t1;
            hfsq = 0.5 * f * f;
            return s * ( hfsq + R );
        }

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
        constexpr inline float Log1pCore( float f ) noexcept
        {
            // |(log(1+s)-log(1-s))/s - Lg(s)| < 2**-34.24 (~[-4.95e-11, 4.97e-11]). 
            constexpr float Lg1 = 0xaaaaaa.0p-24f;
            constexpr float Lg2 = 0xccce13.0p-25f;
            constexpr float Lg3 = 0x91e9ee.0p-25f;
            constexpr float Lg4 = 0xf89e26.0p-26f;

            float hfsq, s, z, R, w, t1, t2;

            s = f / ( 2.0f + f );
            z = s * s;
            w = z * z;
            t1 = w * ( Lg2 + w * Lg4 );
            t2 = z * ( Lg1 + w * Lg3 );
            R = t2 + t1;
            hfsq = 0.5f * f * f;
            return s * ( hfsq + R );
        }

        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunSoft, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        constexpr inline double Log2Impl( double x ) noexcept
        {
            constexpr double two54 = 1.80143985094819840000e+16;
            constexpr double ivln2hi = 1.44269504072144627571e+00;
            constexpr double ivln2lo = 1.67517131648865118353e-10;
            constexpr double zero = 0.0;

            double f, hfsq, hi, lo, r, val_hi, val_lo, w, y;

            Int64 ax = std::bit_cast<Int64>( x );
            Int32 hx = static_cast<Int32>( ax >> 32 );
            UInt32 lx = static_cast<UInt32>( ax );

            Int32 k = 0;
            if ( hx < 0x00100000 )
            {			
                // x < 2**-1022  
                if ( ( ( hx & 0x7fffffff ) | lx ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two54 / zero;
                    return -std::numeric_limits<double>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<double>::quiet_NaN( );
                }
                k -= 54; 
                // subnormal number, scale up x 
                x *= two54; 
                ax = std::bit_cast<Int64>( x );
                hx = static_cast<Int32>( ax >> 32 );
            }
            if ( hx >= 0x7ff00000 )
            {
                return x + x;
            }
            if ( hx == 0x3ff00000 && lx == 0 )
            {
                // log(1) = +0 
                return zero;
            }
            k += ( hx >> 20 ) - 1023;
            hx &= 0x000fffff;
            Int32 i = ( hx + 0x95f64 ) & 0x100000;
            // normalize x or x/2 
            ax = (static_cast<Int64>( hx | ( i ^ 0x3ff00000 ) ) << 32) | ( ax & 0x00000000FFFFFFFF);
            x = std::bit_cast<double>( ax );
            k += ( i >> 20 );
            y = static_cast<double>( k );
            f = x - 1.0;
            hfsq = 0.5 * f * f;
            r = Log1pCore( f );

            
            hi = std::bit_cast<double>( std::bit_cast<Int64>( f - hfsq ) & 0xFFFFFFFF00000000 );
            
            lo = ( f - hi ) - hfsq + r;
            val_hi = hi * ivln2hi;
            val_lo = ( lo + hi ) * ivln2lo + lo * ivln2hi;

            // spadd(val_hi, val_lo, y), except for not using double_t: 
            w = y + val_hi;
            val_lo += ( y - w ) + val_hi;
            val_hi = w;

            return val_lo + val_hi;
        }

        constexpr inline float Log2Impl( float x ) noexcept
        {
            constexpr float two25 = 3.3554432000e+07f;
            constexpr float ivln2hi = 1.4428710938e+00f;
            constexpr float ivln2lo = -1.7605285393e-04f;
            constexpr float zero = 0.0;

            float f, hfsq, hi, lo, r, y;
            
            Int32 hx = std::bit_cast<Int32>( x );

            Int32 k = 0;
            if ( hx < 0x00800000 )
            {			
                // x < 2**-126  
                if ( ( hx & 0x7fffffff ) == 0 )
                {
                    // log(+-0)=-inf 
                    // return -two25 / zero;
                    return -std::numeric_limits<float>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<float>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 25; 
                x *= two25; 
                hx = std::bit_cast<Int32>( x );
            }
            if ( hx >= 0x7f800000 )
            {
                return x + x;
            }
            if ( hx == 0x3f800000 )
            {
                // log(1) = +0 
                return zero;
            }
            k += ( hx >> 23 ) - 127;
            hx &= 0x007fffff;
            Int32 i = ( hx + ( 0x4afb0d ) ) & 0x800000;
            // normalize x or x/2 
            x = std::bit_cast<float>( hx | ( i ^ 0x3f800000 ) );
            k += ( i >> 23 );
            y = static_cast<float>( k );
            f = x - 1.0f;
            hfsq = 0.5f * f * f;
            r = Log1pCore( f );

            hi = f - hfsq;
            hx = std::bit_cast<Int32>( hi );
            hi = std::bit_cast<float>( hx & 0xfffff000 );
            lo = ( f - hi ) - hfsq + r;
            return ( lo + hi ) * ivln2lo + lo * ivln2hi + hi * ivln2hi + y;
        }
    }


    /// <summary>
    /// <para>
    /// Computes the binary, base-2, logarithm of x.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The binary, base-2, logarithm of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log2( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::Log2Impl( x );
        }
        else
        {
            return Math::Internal::Log2Impl( x );
        }
        
    }

    namespace Internal
    {
        constexpr inline double Log10Impl( double x ) noexcept
        {
            constexpr double two54 = 1.80143985094819840000e+16;
            constexpr double ivln10hi = 4.34294481878168880939e-01;
            constexpr double ivln10lo = 2.50829467116452752298e-11;
            constexpr double log10_2hi = 3.01029995663611771306e-01;
            constexpr double log10_2lo = 3.69423907715893078616e-13;

            constexpr double zero = 0.0;

            double f, hfsq, hi, lo, r, val_hi, val_lo, w, y, y2;
            
            Int64 ax = std::bit_cast<Int64>( x );
            Int32 hx = static_cast<Int32>( ax >> 32 );
            UInt32 lx = static_cast<UInt32>( ax );
            

            Int32 k = 0;
            if ( hx < 0x00100000 )
            {
                // x < 2**-1022  
                if ( ( ( hx & 0x7fffffff ) | lx ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two54 / zero;
                    return -std::numeric_limits<double>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<double>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 54; 
                x *= two54; 
                ax = std::bit_cast<Int64>( x );
                hx = static_cast<Int32>( ax >> 32 );
            }
            if ( hx >= 0x7ff00000 )
            {
                return x + x;
            }
            if ( hx == 0x3ff00000 && lx == 0 )
            {
                // log(1) = +0 
                return zero;
            }
            k += ( hx >> 20 ) - 1023;
            hx &= 0x000fffff;
            Int32 i = ( hx + 0x95f64 ) & 0x100000;
            // normalize x or x/2 
            ax = ( static_cast<Int64>( hx | ( i ^ 0x3ff00000 ) ) << 32 ) | ( ax & 0x00000000FFFFFFFF );
            x = std::bit_cast<double>( ax );
            
            k += ( i >> 20 );
            y = static_cast<double>( k );
            f = x - 1.0;
            hfsq = 0.5 * f * f;
            r = Log1pCore( f );
            
            hi = std::bit_cast<double>( std::bit_cast<Int64>( f - hfsq ) & 0xFFFFFFFF00000000 );
            
            lo = ( f - hi ) - hfsq + r;
            val_hi = hi * ivln10hi;
            y2 = y * log10_2hi;
            val_lo = y * log10_2lo + ( lo + hi ) * ivln10lo + lo * ivln10hi;

            /*
             * Extra precision in for adding y*log10_2hi is not strictly needed
             * since there is no very large cancellation near x = sqrt(2) or
             * x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
             * with some parallelism and it reduces the error for many args.
             */
            w = y2 + val_hi;
            val_lo += ( y2 - w ) + val_hi;
            val_hi = w;

            return val_lo + val_hi;
        }

        constexpr inline float Log10Impl( float x ) noexcept
        {
            constexpr float two25 = 3.3554432000e+07f;
            constexpr float ivln10hi = 4.3432617188e-01f;
            constexpr float ivln10lo = -3.1689971365e-05f;
            constexpr float log10_2hi = 3.0102920532e-01f;
            constexpr float log10_2lo = 7.9034151668e-07f;

            constexpr float zero = 0.0;

            float f, hfsq, hi, lo, r, y;
            

            Int32 hx = std::bit_cast<Int32>( x );

            Int32 k = 0;
            if ( hx < 0x00800000 )
            {
                // x < 2**-126  
                if ( ( hx & 0x7fffffff ) == 0 )
                {
                    // log(+-0)=-inf 
                    //return -two25 / zero;
                    return -std::numeric_limits<float>::infinity( );
                }
                if ( hx < 0 )
                {
                    // log(-#) = NaN 
                    //return ( x - x ) / zero;
                    return std::numeric_limits<float>::quiet_NaN( );
                }
                // subnormal number, scale up x 
                k -= 25; x *= two25; 
                hx = std::bit_cast<Int32>( x );
                
            }
            if ( hx >= 0x7f800000 )
            {
                return x + x;
            }
            if ( hx == 0x3f800000 )
            {
                // log(1) = +0 
                return zero;
            }
            k += ( hx >> 23 ) - 127;
            hx &= 0x007fffff;
            Int32 i = ( hx + ( 0x4afb0d ) ) & 0x800000;

            // normalize x or x/2 
            x = std::bit_cast<float>( hx | ( i ^ 0x3f800000 ) );
            

            k += ( i >> 23 );
            y = static_cast<float>( k );
            f = x - 1.0f;
            hfsq = 0.5f * f * f;
            r = Log1pCore( f );

            hi = f - hfsq;
            hx = std::bit_cast<Int32>( hi );
            hi = std::bit_cast<float>( hx & 0xfffff000 );
            lo = ( f - hi ) - hfsq + r;
            return y * log10_2lo + ( lo + hi ) * ivln10lo + lo * ivln10hi + hi * ivln10hi + y * log10_2hi;
        }
    }

    /// <summary>
    /// <para>
    /// Computes the common, base 10, logarithm of x.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The common, base 10, logarithm of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log10( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::Log10Impl( x );
        }
        else
        {
            return Math::Internal::Log10Impl( x );
            /*
            using FloatT = std::remove_cvref_t<T>;
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return std::log10f( x );
            }
            else
            {
                return std::log10( x );
            }
            */
        }
    }


    /// <summary>
    /// <para>
    /// Computes the sine of x given in radians.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The sine of x given in radians.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Sin( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::SinImpl( x );
        }
        else
        {
            if constexpr ( std::is_same_v<std::remove_cvref_t<T>, float> )
            {
                return Math::Internal::SinImpl( x );
                //return sinf( x );
            }
            else
            {

                //using FloatType = std::remove_cvref_t<T>;
                //FloatType result;
                //_mm_store_sd( &result, _mm_sin_pd( _mm_set_sd( x ) ) );
                //return result;
                //return Math::Internal::SinImpl( x );
                return sin( x );
            }
        }
    }

    /// <summary>
    /// <para>
    /// Computes the principal value of the arc sine of x.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The principal value of the arc sine of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ASin( T x ) noexcept
    {
        return Math::Internal::ASinImpl( x );
    }

    /// <summary>
    /// <para>
    /// Computes the cosine of x given in radians.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The cosine of x given in radians.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Cos( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::CosImpl( x );
        }
        else
        {
            if constexpr ( std::is_same_v<std::remove_cvref_t<T>, float> )
            {
                return Math::Internal::CosImpl( x );
                //return cosf( x );
            }
            else
            {
                //using FloatType = std::remove_cvref_t<T>;
                //FloatType result;
                //_mm_store_sd( &result, _mm_cos_pd( _mm_set_sd( x ) ) );
                //return result;
                return cos( x );
            }
        }
    }

    /// <summary>
    /// <para>
    /// Computes the principal value of the arc cosine of x.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The principal value of the arc cosine of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ACos( T x ) noexcept
    {
        return Math::Internal::ACosImpl( x );
    }


    /// <summary>
    /// <para>
    /// Computes the tangent of x given in radians.
    /// </para>
    /// This implementation can be constexpr evaluated,
    /// and at runtime calls std::tan.
    /// <para>
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The tangent of x given in radians.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Tan( T x ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::TanImpl( x );
        }
        else
        {
            using FloatType = std::remove_cvref_t<T>;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::TanImpl( x );
            }
            else
            {
                return std::tan( x );
            }
            
            /*
            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_tan_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_tan_pd( _mm_set_sd( x ) ) );
            }
            return result;
            */
            //return std::tan( x );
        }
    }

    /// <summary>
    /// <para>
    /// Computes the principal value of the arc tangent of x.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The principal value of the arc tangent of x.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x ) noexcept
    {
        return Math::Internal::ATanImpl( x );
    }

    /// <summary>
    /// <para>
    /// Computes the arc tangent of x / y using the signs of arguments 
    /// to determine the correct quadrant.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <param name="y">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The arc tangent of x / y using the signs of arguments to 
    /// determine the correct quadrant.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T x, T y ) noexcept
    {
        return Math::Internal::ATan2Impl( x, y );
    }
    /// <summary>
    /// <para>
    /// Computes the arc tangent of x / y using the signs of arguments 
    /// to determine the correct quadrant.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <param name="y">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The arc tangent of x / y using the signs of arguments to 
    /// determine the correct quadrant.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan2( T x, T y ) noexcept
    {
        return Math::Internal::ATan2Impl( x, y );
    }

    /// <summary>
    /// Simultaneously compute the sine and cosine of x, where x is in radians, 
    /// returning the sine in the variable referenced by sinResult, and the 
    /// cosine in the variable referenced by cosResult.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <param name="sinResult"></param>
    /// <param name="cosResult"></param>
    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr void SinCos( T x, T& sinResult, T& cosResult ) noexcept
    {
        sinResult = Sin( x );
        cosResult = Cos( x );
    }


    template<typename T>
        requires IsInteger<T>
    inline constexpr T FMA( T a, T b, T c ) noexcept
    {
        return a * b + c;
    }

    template<typename T>
        requires IsFloatingPoint<T>
    inline constexpr T FMA( T a, T b, T c ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            return a * b + c;
        }
        else
        {
            return std::fma( a, b, c );
        }
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SinXOverX( FloatT x )
    {
        if ( 1 - x * x == 1 )
        {
            return 1;
        }
        return Math::Sin( x ) / x;
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr FloatT ExpM1( FloatT x )
    {
        if ( std::is_constant_evaluated( ) )
        {
            FloatT u = Exp( x );
            if ( u == static_cast< FloatT >( 1. ) )
            {
                return x;
            }
            if ( u - static_cast< FloatT >( 1. ) == static_cast< FloatT >( -1. ) )
            {
                return static_cast< FloatT >( -1. );
            }
            return ( u - static_cast< FloatT >( 1. ) ) * x / Log( u );
        }
        else
        {
            using Traits = SIMD::Traits<FloatT, 1>;
            return Traits::First( Traits::ExpM1( Traits::Load( &x ) ) );
        }
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Sinc( FloatT x )
    {
        return SinXOverX( Constants<FloatT>::Pi * x );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT WindowedSinc( FloatT x, FloatT radius, FloatT tau )
    {
        if ( Abs( x ) > radius )
        {
            return 0;
        }
        return Sinc( x ) * Sinc( x / tau );
    }

    template<typename T>
        requires (IsFloatingPoint<T> == false)
    constexpr inline T Mod( T a, T b )
    {
        T result = a - ( a / b ) * b;
        return static_cast<T>( result < 0 ? result + b : result );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Mod( FloatT a, FloatT b )
    {
        return FMod( a, b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Radians( FloatT deg )
    {
        return ( Constants<FloatT>:: Pi / static_cast < FloatT >(180) ) * deg;
    }
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Degrees( FloatT rad )
    {
        return ( static_cast< FloatT >(180) / Constants<FloatT>::Pi ) * rad;
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SmoothStep( FloatT x, FloatT a, FloatT b )
    {
        if ( a == b )
        {
            return x < a ? Constants< FloatT>::Zero : Constants< FloatT>::One;
        }
        FloatT t = Clamp( ( x - a ) / ( b - a ), Constants< FloatT>::Zero, Constants< FloatT>::One );
        return t * t * ( Constants< FloatT>::Three - Constants< FloatT>::Two * t );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SafeSqrt( FloatT x )
    {
        return Sqrt( std::max( Constants< FloatT>::Zero, x ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Sqr( FloatT v )
    {
        return v * v;
    }

    
    namespace Internal
    {
        template<typename FloatT>
        struct FastPowImpl
        {
            template<int n>
            static constexpr inline FloatT Pow( FloatT v )
            {
                if constexpr ( n < 0 )
                {
                    return Constants< FloatT>::One / Pow<-n>( v );
                }
                auto n2 = Pow<n / 2>( v );
                return n2 * n2 * Pow<n & 1>( v );
            }

            template<>
            static constexpr inline FloatT Pow<1>( FloatT v )
            {
                return v;
            }
            template<>
            static constexpr inline FloatT Pow<0>( FloatT v )
            {
                return Constants< FloatT>::One;
            }
        };
    }

    template<int n, typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT FastPow( FloatT v )
    {
        return Internal::FastPowImpl<FloatT>::Pow<n>( v );
    }


    template <typename FloatT, typename C>
    constexpr inline FloatT EvaluatePolynomial( FloatT t, C c )
    {
        return c;
    }

    template <typename FloatT, typename C, typename... Args>
    constexpr inline FloatT EvaluatePolynomial( FloatT t, C c, Args... remaining )
    {
        return FMA( t, EvaluatePolynomial( t, remaining... ), c );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SafeASin( FloatT x )
    {
        return ASin( Clamp( x, Constants< FloatT >::MinusOne, Constants< FloatT >::One ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SafeACos( FloatT x )
    {
        return ACos( Clamp( x, Constants< FloatT >::MinusOne, Constants< FloatT >::One ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT NextFloatUp( FloatT v )
    {   
        return NextUp( v );
        /*
        if ( IsInf( v ) && v > static_cast< FloatT >( 0. ) )
        {
            return v;
        }
        if ( v == static_cast< FloatT >( -0. ) )
        {
            v = static_cast< FloatT >( 0 );
        }
        auto ui = std::bit_cast< MakeUnsigned<FloatT> >( v );
        if ( v >= static_cast< FloatT >( 0 ) )
        {
            ++ui;
        }
        else
        {
            --ui;
        }
        return std::bit_cast<FloatT>( ui );
        */
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr FloatT NextFloatDown( FloatT v )
    {
        return NextDown( v );
        /*
        if ( IsInf( v ) && v < static_cast< FloatT >( 0. ) )
        {
            return v;
        }
        if ( v == static_cast< FloatT >( 0. ) )
        {
            v = static_cast< FloatT >( -0. );
        }
        auto ui = std::bit_cast< MakeUnsigned<FloatT> >( v );
        if ( v > static_cast< FloatT >( 0. ) )
        {
            --ui;
        }
        else
        {
            ++ui;
        }
        return std::bit_cast< FloatT >( ui );
        */
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Gamma( int n )
    {
        return ( static_cast< FloatT >( n ) * Constants<FloatT>::MachineEpsilon ) / ( Constants< FloatT >::One - static_cast< FloatT >( n ) * Constants<FloatT>::MachineEpsilon );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT AddRoundUp( FloatT a, FloatT b )
    {
        return NextFloatUp( a + b );
    }
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT AddRoundDown( FloatT a, FloatT b )
    {
        return NextFloatDown( a + b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SubRoundUp( FloatT a, FloatT b )
    {
        return AddRoundUp( a, -b );
    }
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SubRoundDown( FloatT a, FloatT b )
    {
        return AddRoundDown( a, -b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT MulRoundUp( FloatT a, FloatT b )
    {
        return NextFloatUp( a * b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT MulRoundDown( FloatT a, FloatT b )
    {
        return NextFloatDown( a * b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT DivRoundUp( FloatT a, FloatT b )
    {
        return NextFloatUp( a / b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT DivRoundDown( FloatT a, FloatT b )
    {
        return NextFloatDown( a / b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SqrtRoundUp( FloatT a )
    {
        return NextFloatUp( Sqrt( a ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SqrtRoundDown( FloatT a )
    {
        return std::max<FloatT>( 0, NextFloatDown( Sqrt( a ) ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT FMARoundUp( FloatT a, FloatT b, FloatT c )
    {
        return NextFloatUp( FMA( a, b, c ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT FMARoundDown( FloatT a, FloatT b, FloatT c )
    {
        return NextFloatDown( FMA( a, b, c ) );
    }


    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT FastLog2( FloatT x )
    {
        constexpr FloatT invLog2 = static_cast< FloatT >( 1.442695040888963387004650940071 );
        return Math::Log( x ) * invLog2;
    }

    constexpr inline int Log2Int( float v )
    {
        if ( v < 1.f )
        {
            return -Log2Int( 1.f / v );
        }
        else
        {
            constexpr UInt32 midSignificand = 0b00000000001101010000010011110011;
            return Core::Exponent( v ) + ( ( Core::Significand( v ) >= midSignificand ) ? 1 : 0 );
        }
    }

    constexpr inline int Log2Int( double v )
    {
        if ( v < 1. )
        {
            return -Log2Int( 1. / v );
        }
        else
        {
            constexpr UInt64 midSignificand = 0b110101000001001111001100110011111110011101111001101;
            return Core::Exponent( v ) + ( ( Core::Significand( v ) >= midSignificand ) ? 1 : 0 );
        }
    }

    constexpr inline int Log2Int( UInt32 v )
    {
        unsigned long index = 0;
        if ( IndexOfBitFromMSB( &index, v ) )
        {
            return std::bit_cast<int>( index );
        }
        return 0;
    }
    constexpr inline int Log2Int( Int32 v )
    {
        return Log2Int( std::bit_cast< UInt32 >( v ) );
    }

    constexpr inline int Log2Int( UInt64 v )
    {
        unsigned long index = 0;
        IndexOfBitFromMSB( &index, v );
        return std::bit_cast< int >( index );
    }

    constexpr inline int Log2Int( Int64 v )
    {
        return Log2Int( std::bit_cast< UInt64 >( v ) );
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr inline int Log4Int( T v )
    {
        return Log2Int( v ) / 2;
    }

    // https://stackoverflow.com/a/10792321
    constexpr inline float FastExp( float x )
    {
        // Compute $x'$ such that $\roman{e}^x = 2^{x'}$
        float xp = x * 1.442695041f;

        // Find integer and fractional components of $x'$
        float fxp = Floor( xp ), f = xp - fxp;
        auto i = static_cast<int>( fxp );

        // Evaluate polynomial approximation of $2^f$
        float twoToF = EvaluatePolynomial( f, 1.f, 0.695556856f, 0.226173572f, 0.0781455737f );

        // Scale $2^f$ by $2^i$ and return final result
        int exponent = Core::Exponent( twoToF ) + i;
        if ( exponent < -126 )
        {
            return 0;
        }
        if ( exponent > 127 )
        {
            return Constants<float>::Infinity;
        }
        auto bits = std::bit_cast<UInt32>( twoToF );
        bits &= 0b10000000011111111111111111111111u;
        bits |= ( exponent + 127 ) << 23;
        return std::bit_cast<float>( bits );
    }


    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Gaussian( FloatT x, FloatT mu = 0, FloatT sigma = 1 )
    {
        return static_cast<FloatT>( 1 )/ Sqrt( static_cast< FloatT >( 2 ) * Constants<FloatT>::Pi * sigma * sigma ) *
            FastExp( -Sqr( x - mu ) / ( static_cast< FloatT >( 2 ) * sigma * sigma ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT GaussianIntegral( FloatT x0, FloatT x1, FloatT mu = 0, FloatT sigma = 1 )
    {
        FloatT sigmaRoot2 = sigma * Constants<FloatT>::Sqrt2;
        return static_cast< FloatT >( 0.5 ) * ( std::erf( ( mu - x0 ) / sigmaRoot2 ) - std::erf( ( mu - x1 ) / sigmaRoot2 ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Logistic( FloatT x, FloatT s )
    {
        x = Abs( x );
        return Exp( -x / s ) / ( s * Sqr( 1 + Exp( -x / s ) ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT LogisticCDF( FloatT x, FloatT s )
    {
        return static_cast< FloatT >( 1 ) / ( static_cast< FloatT >( 1 ) + Exp( -x / s ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT TrimmedLogistic( FloatT x, FloatT s, FloatT a, FloatT b )
    {
        return Logistic( x, s ) / ( LogisticCDF( b, s ) - LogisticCDF( a, s ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT ErfInv( FloatT a );
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT I0( FloatT x );
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT LogI0( FloatT x );

    template<typename Predicate>
    constexpr inline size_t FindInterval( size_t sz, const Predicate& pred )
    {
        using ssize_t = std::make_signed_t<size_t>;
        ssize_t size = ( ssize_t )sz - 2, first = 1;
        while ( size > 0 )
        {
            // Evaluate predicate at midpoint and update _first_ and _size_
            size_t half = ( size_t )size >> 1, middle = first + half;
            bool predResult = pred( middle );
            first = predResult ? middle + 1 : first;
            size = predResult ? size - ( half + 1 ) : half;
        }
        return ( size_t )Clamp( ( ssize_t )first - 1, ( ssize_t )0, ( ssize_t )sz - 2 );
    }

    template <typename T>
    constexpr inline bool IsPowerOf4( T v )
    {
        return v == 1 << ( 2 * Log4Int( v ) );
    }

    constexpr inline Int32 RoundUpPow2( Int32 v )
    {
        return NextPowerOfTwo( v );
    }

    constexpr inline Int64 RoundUpPow2( Int64 v )
    {
        return NextPowerOfTwo( v );
    }

    template <typename T>
    constexpr inline T RoundUpPow4( T v )
    {
        return IsPowerOf4( v ) ? v : ( 1 << ( 2 * ( 1 + Log4Int( v ) ) ) );
    }

    template<typename T>
        requires IsFloatingPoint<T>
    class CompensatedSum
    {
    public:
        using value_type = T;
        using ValueType = T;
    private:
        ValueType sum_ = 0;
        ValueType c_ = 0;
    public:
        // CompensatedSum Public Methods
        constexpr CompensatedSum( ) noexcept = default;
        
        constexpr explicit CompensatedSum( ValueType v ) noexcept
            : sum_( v ) 
        {}

        constexpr CompensatedSum& operator=( ValueType v ) noexcept
        {
            sum_ = v;
            c_ = 0;
            return *this;
        }

        constexpr CompensatedSum& operator+=( ValueType v ) noexcept
        {
            ValueType delta = v - c_;
            ValueType newSum = sum_ + delta;
            c_ = ( newSum - sum_ ) - delta;
            sum_ = newSum;
            return *this;
        }

        constexpr explicit operator ValueType( ) const noexcept
        { 
            return sum_; 
        }

        std::string ToString( ) const;

    private:
        
    };

    // CompensatedFloat Definition
    template<typename T>
        requires IsFloatingPoint<T>
    class CompensatedFloat
    {
    public:
        using value_type = T;
        using ValueType = T;

        ValueType v{};
        ValueType err{};
    
    public:
        // CompensatedFloat Public Methods
        constexpr CompensatedFloat( ValueType v, ValueType err = 0 ) noexcept
            : v( v ), err( err ) 
        {}
        constexpr explicit operator float( ) const noexcept
        { 
            return float( v ) + float( err );
        }
        constexpr explicit operator double( ) const noexcept
        { 
            return double( v ) + double( err ); 
        }
        std::string ToString( ) const;
    };

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline CompensatedFloat<FloatT> TwoProd( FloatT a, FloatT b )
    {
        FloatT ab = a * b;
        return { ab, FMA( a, b, -ab ) };
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline CompensatedFloat<FloatT> TwoSum( FloatT a, FloatT b )
    {
        FloatT s = a + b, delta = s - a;
        return { s, ( a - ( s - delta ) ) + ( b - delta ) };
    }

    template <typename Ta, typename Tb, typename Tc, typename Td>
        requires IsFloatingPoint<Ta> && IsFloatingPoint<Tb> && IsFloatingPoint<Tc> && IsFloatingPoint<Td>
    constexpr inline auto DifferenceOfProducts( Ta a, Tb b, Tc c, Td d )
    {
        auto cd = c * d;
        auto differenceOfProducts = FMA( a, b, -cd );
        auto error = FMA( -c, d, cd );
        return differenceOfProducts + error;
    }

    template <typename Ta, typename Tb, typename Tc, typename Td>
        requires IsFloatingPoint<Ta>&& IsFloatingPoint<Tb>&& IsFloatingPoint<Tc>&& IsFloatingPoint<Td>
    constexpr inline auto SumOfProducts( Ta a, Tb b, Tc c, Td d )
    {
        auto cd = c * d;
        auto sumOfProducts = FMA( a, b, cd );
        auto error = FMA( c, d, -cd );
        return sumOfProducts + error;
    }

    namespace Internal
    {
        // InnerProduct Helper Functions
        template<typename FloatT>
            requires IsFloatingPoint<FloatT>
        constexpr CompensatedFloat<FloatT> InnerProduct( FloatT a, FloatT b )
        {
            return TwoProd( a, b );
        }

        // Accurate dot products with FMA: Graillat et al.,
        // https://www-pequan.lip6.fr/~graillat/papers/posterRNC7.pdf
        //
        // Accurate summation, dot product and polynomial evaluation in complex
        // floating point arithmetic, Graillat and Menissier-Morain.
        template <typename FloatT, typename... T>
            requires IsFloatingPoint<FloatT>
        constexpr inline CompensatedFloat<FloatT> InnerProduct( FloatT a, FloatT b, T... terms )
        {
            auto ab = TwoProd( a, b );
            auto tp = InnerProduct( terms... );
            auto sum = TwoSum( ab.v, tp.v );
            return { sum.v, ab.err + ( tp.err + sum.err ) };
        }

    }  

    template <typename FloatT, typename... T>
        requires std::conjunction_v<std::is_arithmetic<T>...>
    constexpr inline FloatT InnerProduct( FloatT term, T... terms )
    {
        auto ip = Internal::InnerProduct( term, terms... );
        return static_cast< FloatT >( ip );
    }

    template <typename FloatT, typename... T>
        requires IsFloatingPoint<FloatT>
    constexpr inline bool Quadratic( FloatT a, FloatT b, FloatT c, FloatT* t0, FloatT* t1 )
    {
        // Handle case of $a=0$ for quadratic solution
        if ( a == static_cast< FloatT >( 0 ) )
        {
            if ( b == static_cast< FloatT >( 0 ) )
            {
                return false;
            }
            *t0 = *t1 = -c / b;
            return true;
        }

        // Find quadratic discriminant
        FloatT discrim = DifferenceOfProducts( b, b, 4 * a, c );
        if ( discrim < 0 )
        {
            return false;
        }
        FloatT rootDiscrim = Sqrt( discrim );

        // Compute quadratic _t_ values
        FloatT q = static_cast< FloatT >( -0.5 ) * ( b + CopySign( rootDiscrim, b ) );
        *t0 = q / a;
        *t1 = c / q;
        if ( *t0 > *t1 )
        {
            std::swap( *t0, *t1 );
        }
        return true;
    }


    template <typename Func, typename FloatT>
    constexpr inline FloatT NewtonBisection( FloatT x0, FloatT x1, Func f, FloatT xEps = static_cast< FloatT >(1e-6), FloatT fEps = static_cast< FloatT >(1e-6) )
    {
        FloatT fx0 = f( x0 ).first, fx1 = f( x1 ).first;
        if ( Abs( fx0 ) < fEps )
        {
            return x0;
        }
        if ( Abs( fx1 ) < fEps )
        {
            return x1;
        }
        bool startIsNegative = fx0 < static_cast< FloatT >( 0 );

        // Set initial midpoint using linear approximation of f
        FloatT xMid = x0 + ( x1 - x0 ) * -fx0 / ( fx1 - fx0 );

        while ( true )
        {
            // Fall back to bisection if _xMid_ is out of bounds
            if ( !( x0 < xMid && xMid < x1 ) )
            {
                xMid = ( x0 + x1 ) / static_cast< FloatT >( 2 );
            }

            // Evaluate function and narrow bracket range _[x0, x1]_
            std::pair<FloatT, FloatT> fxMid = f( xMid );
            
            if ( startIsNegative == ( fxMid.first < static_cast< FloatT >( 0 ) ) )
            {
                x0 = xMid;
            }
            else
            {
                x1 = xMid;
            }

            // Stop the iteration if converged
            if ( ( x1 - x0 ) < xEps || Abs( fxMid.first ) < fEps )
            {
                return xMid;
            }
            // Perform a Newton step
            xMid -= fxMid.first / fxMid.second;
        }
    }

    


    template<typename T>
        requires IsFloatingPoint<T>
    class Interval 
    {
    public:
        using value_type = T;
        //static constexpr Interval Pi{Constants<value_type>::Pi,Constants<value_type>::Pi };
    private:
        value_type lowerBound_ = static_cast< value_type >( 0 );
        value_type upperBound_ = static_cast< value_type >( 0 );
    public:
        constexpr Interval( ) = default;

        constexpr explicit Interval( value_type v )
            : lowerBound_( v ), upperBound_( v )
        {
        }

        constexpr Interval( value_type low, value_type high )
            : lowerBound_( std::min(low, high) ), upperBound_( std::max(low, high ) )
        {
        }
    private:
        constexpr Interval( value_type low, value_type high, bool )
            : lowerBound_( low ), upperBound_( high )
        {
        }
    public:
        constexpr static Interval FromValueAndError( value_type v, value_type err )
        {
            if ( err == static_cast< value_type >( 0 ) )
            {
                return Interval(v);
            }
            else
            {
                return Interval( SubRoundDown( v, err ), AddRoundUp( v, err ) );
            }
        }

        constexpr Interval& operator=( value_type v )
        {
            lowerBound_ = v; 
            upperBound_ = v;
            return *this;
        }

        constexpr value_type UpperBound( ) const { return upperBound_; }
        constexpr value_type LowerBound( ) const { return lowerBound_; }
        constexpr value_type Midpoint( ) const { return ( lowerBound_ + upperBound_ ) / 2; }
        constexpr value_type Width( ) const { return upperBound_ - lowerBound_; }

        constexpr value_type operator[]( size_t i ) const
        {
            return i == 0 ? lowerBound_ : upperBound_;
        }

        constexpr explicit operator value_type( ) const
        {
            return Midpoint( );
        }

        
        constexpr bool Exactly( value_type v ) const
        {
            return lowerBound_ == v && upperBound_ == v;
        }

        constexpr bool operator==( value_type v ) const
        {
            return Exactly( v );
        }

        constexpr Interval operator-( ) const
        {
            return { -upperBound_, -lowerBound_ };
        }

        constexpr Interval operator+( const Interval& i ) const
        {
            return { AddRoundDown( lowerBound_, i.lowerBound_ ), AddRoundUp( upperBound_, i.upperBound_ ) };
        }

        constexpr Interval operator-( const Interval& i ) const
        {
            return { SubRoundDown( lowerBound_, i.upperBound_ ), SubRoundUp( upperBound_, i.lowerBound_ ) };
        }

        constexpr Interval operator*( const Interval& i ) const
        {
            value_type lp[ 4 ] = 
            { 
                MulRoundDown( lowerBound_, i.lowerBound_ ), 
                MulRoundDown( upperBound_, i.lowerBound_ ),
                MulRoundDown( lowerBound_, i.upperBound_ ), 
                MulRoundDown( upperBound_, i.upperBound_ ) 
            };
            value_type hp[ 4 ] = 
            { 
                MulRoundUp( lowerBound_, i.lowerBound_ ), 
                MulRoundUp( upperBound_, i.lowerBound_ ),
                MulRoundUp( lowerBound_, i.upperBound_ ), 
                MulRoundUp( upperBound_, i.upperBound_ ) 
            };
            return { Min( lp[ 0 ], lp[ 1 ], lp[ 2 ], lp[ 3 ] ),
                    Max( hp[ 0 ], hp[ 1 ], hp[ 2 ], hp[ 3 ] ) };


            /*
            return { std::min( {lp[ 0 ], lp[ 1 ], lp[ 2 ], lp[ 3 ]} ),
                    std::max( {hp[ 0 ], hp[ 1 ], hp[ 2 ], hp[ 3 ]} ) };
            */
        }

        constexpr Interval operator/( const Interval& i ) const;

        constexpr bool operator==( const Interval& i ) const
        {
            return lowerBound_ == i.lowerBound_ && upperBound_ == i.upperBound_;
        }

        constexpr bool operator!=( value_type f ) const
        {
            return f < lowerBound_ || f > upperBound_;
        }

        std::string ToString( ) const;

        constexpr Interval& operator+=( Interval i )
        {
            *this = Interval( *this + i );
            return *this;
        }
        constexpr Interval& operator-=( Interval i )
        {
            *this = Interval( *this - i );
            return *this;
        }
        constexpr Interval& operator*=( Interval i )
        {
            *this = Interval( *this * i );
            return *this;
        }
        constexpr Interval& operator/=( Interval i )
        {
            *this = Interval( *this / i );
            return *this;
        }
        constexpr Interval& operator+=( value_type f ) { return *this += Interval( f ); }
        constexpr Interval& operator-=( value_type f ) { return *this -= Interval( f ); }
        constexpr Interval& operator*=( value_type f )
        {
            if ( f > static_cast< value_type >( 0 ) )
            {
                *this = Interval( MulRoundDown( f, lowerBound_ ), MulRoundUp( f, upperBound_ ) );
            }
            else
            {
                *this = Interval( MulRoundDown( f, upperBound_ ), MulRoundUp( f, lowerBound_ ) );
            }
            return *this;
        }
        constexpr Interval& operator/=( value_type f )
        {
            if ( f > static_cast< value_type >( 0 ) )
            {
                *this = Interval( DivRoundDown( lowerBound_, f ), DivRoundUp( upperBound_, f ) );
            }
            else
            {
                *this = Interval( DivRoundDown( upperBound_, f ), DivRoundUp( lowerBound_, f ) );
            }
            return *this;
        }


    };

    // Interval Inline Functions
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline bool InRange( FloatT value, const Interval<FloatT>& interval )
    {
        return value >= interval.LowerBound( ) && value <= interval.UpperBound( );
    }
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline bool InRange( const Interval<FloatT>& first, const Interval<FloatT>& second )
    {
        return first.LowerBound( ) <= second.UpperBound( ) && first.UpperBound( ) >= second.LowerBound( );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline Interval<FloatT> Interval<FloatT>::operator/( const Interval<FloatT>& interval ) const
    {
        if ( InRange( static_cast< FloatT >( 0 ), interval ) )
        {
            // The interval we're dividing by straddles zero, so just
            // return an interval of everything.
            return Interval<FloatT>( -std::numeric_limits<FloatT>::infinity(), std::numeric_limits<FloatT>::infinity( ) );
        }
        FloatT lowQuot[ 4 ] = { DivRoundDown( lowerBound_, interval.lowerBound_ ), DivRoundDown( upperBound_, interval.lowerBound_ ),
                            DivRoundDown( lowerBound_, interval.upperBound_ ), DivRoundDown( upperBound_, interval.upperBound_ ) };
        FloatT highQuot[ 4 ] = { DivRoundUp( lowerBound_, interval.lowerBound_ ), DivRoundUp( upperBound_, interval.lowerBound_ ),
                             DivRoundUp( lowerBound_, interval.upperBound_ ), DivRoundUp( upperBound_, interval.upperBound_ ) };
        return { Min( lowQuot[ 0 ], lowQuot[ 1 ], lowQuot[ 2 ], lowQuot[ 3 ] ),
                Max( highQuot[ 0 ], highQuot[ 1 ], highQuot[ 2 ], highQuot[ 3 ] ) };
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline Interval<FloatT> Sqr( const Interval<FloatT>& interval )
    {
        FloatT alow = Abs( interval.LowerBound( ) ); 
        FloatT ahigh = Abs( interval.UpperBound( ) );
        if ( alow > ahigh )
        {
            std::swap( alow, ahigh );
        }
        if ( InRange( static_cast< FloatT >( 0 ), interval ) )
        {
            return Interval<FloatT>( static_cast< FloatT >( 0 ), MulRoundUp( ahigh, ahigh ) );
        }
        return Interval<FloatT>( MulRoundDown( alow, alow ), MulRoundUp( ahigh, ahigh ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> MulPow2( FloatT s, const Interval<FloatT>& i );
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> MulPow2( const Interval<FloatT>& i, FloatT s );

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> operator+( FloatT f, const Interval<FloatT>& i )
    {
        return Interval<FloatT>( f ) + i;
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> operator-( FloatT f, const Interval<FloatT>& i )
    {
        return Interval<FloatT>( f ) - i;
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> operator*( FloatT f, const Interval<FloatT>& i )
    {
        if ( f > static_cast< FloatT >( 0 ) )
        {
            return Interval<FloatT>( MulRoundDown( f, i.LowerBound( ) ), MulRoundUp( f, i.UpperBound( ) ) );
        }
        else
        {
            return Interval<FloatT>( MulRoundDown( f, i.UpperBound( ) ), MulRoundUp( f, i.LowerBound( ) ) );
        }
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> operator/( FloatT f, const Interval<FloatT>& i )
    {
        if ( InRange( static_cast< FloatT >( 0 ), i ) )
        {
            // The interval we're dividing by straddles zero, so just
            // return an interval of everything.
            return Interval<FloatT>( -std::numeric_limits<FloatT>::infinity( ), std::numeric_limits<FloatT>::infinity( ) );
        }

        if ( f > static_cast< FloatT >( 0 ) )
        {
            return Interval( DivRoundDown( f, i.UpperBound( ) ), DivRoundUp( f, i.LowerBound( ) ) );
        }
        else
        {
            return Interval( DivRoundDown( f, i.LowerBound( ) ), DivRoundUp( f, i.UpperBound( ) ) );
        }
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> operator+( const Interval<FloatT>& i, FloatT f )
    {
        return i + Interval( f );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> operator-( const Interval<FloatT>& i, FloatT f )
    {
        return i - Interval( f );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> operator*( const Interval<FloatT>& i, FloatT f )
    {
        if ( f > static_cast< FloatT >( 0 ) )
            return Interval( MulRoundDown( f, i.LowerBound( ) ), MulRoundUp( f, i.UpperBound( ) ) );
        else
            return Interval( MulRoundDown( f, i.UpperBound( ) ), MulRoundUp( f, i.LowerBound( ) ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> operator/( const Interval<FloatT>& i, FloatT f )
    {
        if ( f == static_cast< FloatT >( 0 ) )
        {
            return Interval( -std::numeric_limits<FloatT>::infinity( ), std::numeric_limits<FloatT>::infinity( ) );
        }

        if ( f > static_cast< FloatT >( 0 ) )
        {
            return Interval( DivRoundDown( i.LowerBound( ), f ), DivRoundUp( i.UpperBound( ), f ) );
        }
        else
        {
            return Interval( DivRoundDown( i.UpperBound( ), f ), DivRoundUp( i.LowerBound( ), f ) );
        }
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline FloatT Floor( const Interval<FloatT>& i )
    {
        return Floor( i.LowerBound( ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline FloatT Ceil( const Interval<FloatT>& i )
    {
        return Ceil( i.UpperBound( ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline FloatT floor( const Interval<FloatT>& i )
    {
        return Floor( i );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline FloatT ceil( const Interval<FloatT>& i )
    {
        return Ceil( i );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline FloatT Min( const Interval<FloatT>& a, const Interval<FloatT>& b )
    {
        return std::min( a.LowerBound( ), b.LowerBound( ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline FloatT Max( const Interval<FloatT>& a, const Interval<FloatT>& b )
    {
        return std::max( a.UpperBound( ), b.UpperBound( ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline FloatT min( const Interval<FloatT>& a, const Interval<FloatT>& b )
    {
        return Min( a, b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline FloatT max( const Interval<FloatT>& a, const Interval<FloatT>& b )
    {
        return Max( a, b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> Sqrt( const Interval<FloatT>& i )
    {
        return { SqrtRoundDown( i.LowerBound( ) ), SqrtRoundUp( i.UpperBound( ) ) };
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> sqrt( const Interval<FloatT>& i )
    {
        return Sqrt( i );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> FMA( const Interval<FloatT>& a, const Interval<FloatT>& b, const Interval<FloatT>& c )
    {
        FloatT low = Min( FMARoundDown( a.LowerBound( ), b.LowerBound( ), c.LowerBound( ) ),
                              FMARoundDown( a.UpperBound( ), b.LowerBound( ), c.LowerBound( ) ),
                              FMARoundDown( a.LowerBound( ), b.UpperBound( ), c.LowerBound( ) ),
                              FMARoundDown( a.UpperBound( ), b.UpperBound( ), c.LowerBound( ) ) );
        FloatT high = Max( FMARoundUp( a.LowerBound( ), b.LowerBound( ), c.UpperBound( ) ),
                               FMARoundUp( a.UpperBound( ), b.LowerBound( ), c.UpperBound( ) ),
                               FMARoundUp( a.LowerBound( ), b.UpperBound( ), c.UpperBound( ) ),
                               FMARoundUp( a.UpperBound( ), b.UpperBound( ), c.UpperBound( ) ) );
        return Interval<FloatT>( low, high );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> DifferenceOfProducts( const Interval<FloatT>& a, const Interval<FloatT>& b, const Interval<FloatT>& c, const Interval<FloatT>& d )
    {
        FloatT ab[ 4 ] = 
        { 
            a.LowerBound( ) * b.LowerBound( ), 
            a.UpperBound( ) * b.LowerBound( ),
            a.LowerBound( ) * b.UpperBound( ), 
            a.UpperBound( ) * b.UpperBound( ) 
        };
        FloatT abLow = Min( ab[ 0 ], ab[ 1 ], ab[ 2 ], ab[ 3 ] );
        FloatT abHigh = Max( ab[ 0 ], ab[ 1 ], ab[ 2 ], ab[ 3 ] );
        int abLowIndex = abLow == ab[ 0 ] ? 0 : ( abLow == ab[ 1 ] ? 1 : ( abLow == ab[ 2 ] ? 2 : 3 ) );
        int abHighIndex =
            abHigh == ab[ 0 ] ? 0 : ( abHigh == ab[ 1 ] ? 1 : ( abHigh == ab[ 2 ] ? 2 : 3 ) );

        FloatT cd[ 4 ] = 
        { 
            c.LowerBound( ) * d.LowerBound( ), 
            c.UpperBound( ) * d.LowerBound( ),
            c.LowerBound( ) * d.UpperBound( ), 
            c.UpperBound( ) * d.UpperBound( ) 
        };
        FloatT cdLow = Min( cd[ 0 ], cd[ 1 ], cd[ 2 ], cd[ 3 ] );
        FloatT cdHigh = Max( cd[ 0 ], cd[ 1 ], cd[ 2 ], cd[ 3 ] );
        int cdLowIndex = cdLow == cd[ 0 ] ? 0 : ( cdLow == cd[ 1 ] ? 1 : ( cdLow == cd[ 2 ] ? 2 : 3 ) );
        int cdHighIndex = cdHigh == cd[ 0 ] ? 0 : ( cdHigh == cd[ 1 ] ? 1 : ( cdHigh == cd[ 2 ] ? 2 : 3 ) );

        // Invert cd Indices since it's subtracted...
        FloatT low = DifferenceOfProducts( a[ abLowIndex & 1 ], b[ abLowIndex >> 1 ], c[ cdHighIndex & 1 ], d[ cdHighIndex >> 1 ] );
        FloatT high = DifferenceOfProducts( a[ abHighIndex & 1 ], b[ abHighIndex >> 1 ], c[ cdLowIndex & 1 ], d[ cdLowIndex >> 1 ] );
        

        return { NextFloatDown( NextFloatDown( low ) ), NextFloatUp( NextFloatUp( high ) ) };
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> SumOfProducts( const Interval<FloatT>& a, const Interval<FloatT>& b, const Interval<FloatT>& c, const Interval<FloatT>& d )
    {
        return DifferenceOfProducts( a, b, -c, d );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> MulPow2( FloatT s, const Interval<FloatT>& i )
    {
        return MulPow2( i, s );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> MulPow2( const Interval<FloatT>& i, FloatT s )
    {
        FloatT as = std::abs( s );

        // Multiplication by powers of 2 is exaact
        return Interval<FloatT>( std::min( i.LowerBound( ) * s, i.UpperBound( ) * s ),
            std::max( i.LowerBound( ) * s, i.UpperBound( ) * s ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> Abs( const Interval<FloatT>& i )
    {
        if ( i.LowerBound( ) >= static_cast< FloatT >( 0 ) )
        {
            // The entire interval is greater than zero, so we're all set.
            return i;
        }
        else if ( i.UpperBound( ) <= static_cast< FloatT >( 0 ) )
        {
            // The entire interval is less than zero.
            return Interval( -i.UpperBound( ), -i.LowerBound( ) );
        }
        else
        {
            // The interval straddles zero.
            return Interval( static_cast< FloatT >( 0 ), std::max( -i.LowerBound( ), i.UpperBound( ) ) );
        }
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> abs( const Interval<FloatT>& i )
    {
        return Abs( i );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> ACos( const Interval<FloatT>& i )
    {
        FloatT low = ACos( std::min<FloatT>( static_cast< FloatT >( 1 ), i.UpperBound( ) ) );
        FloatT high = ACos( std::max<FloatT>( static_cast< FloatT >( -1 ), i.LowerBound( ) ) );

        return Interval<FloatT>( std::max<FloatT>( static_cast< FloatT >( 0 ), NextFloatDown( low ) ), NextFloatUp( high ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> Sin( const Interval<FloatT>& i )
    {
        FloatT low = Math::Sin( std::max<FloatT>( static_cast< FloatT >( 0 ), i.LowerBound( ) ) );
        FloatT high = Math::Sin( i.UpperBound( ) );

        if ( low > high )
        {
            std::swap( low, high );
        }
        low = std::max<FloatT>( static_cast< FloatT >( -1 ), NextFloatDown( low ) );
        high = std::min<FloatT>( static_cast< FloatT >( 1 ), NextFloatUp( high ) );
        if ( InRange( Constants<FloatT>::PiOver2, i ) )
        {
            high = static_cast< FloatT >( 1 );
        }
        if ( InRange( ( static_cast< FloatT >( 3. ) / static_cast< FloatT >( 2. ) ) * Constants<FloatT>::Pi, i ) )
        {
            low = static_cast< FloatT >( -1 );
        }
        return Interval( low, high );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> Cos( const Interval<FloatT>& i )
    {
        FloatT low = std::cos( std::max<FloatT>( static_cast< FloatT >( 0 ), i.LowerBound( ) ) );
        FloatT high = Cos( i.UpperBound( ) );
        if ( low > high )
        {
            std::swap( low, high );
        }
        low = std::max<FloatT>( static_cast< FloatT >( -1 ), NextFloatDown( low ) );
        high = std::min<FloatT>( static_cast< FloatT >( 1 ), NextFloatUp( high ) );
        if ( InRange( Constants<FloatT>::Pi, i ) )
        {
            low = static_cast< FloatT >( -1 );
        }

        return Interval( low, high );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline bool Quadratic( const Interval<FloatT>& a, const Interval<FloatT>& b, const Interval<FloatT>& c, Interval<FloatT>* t0, Interval<FloatT>* t1 )
    {
        // Find quadratic discriminant
        auto discrim = DifferenceOfProducts( b, b, MulPow2( static_cast< FloatT >( 4 ), a ), c );
        if ( discrim.LowerBound( ) < static_cast< FloatT >( 0 ) )
        {
            return false;
        }
        Interval<FloatT> floatRootDiscrim = Sqrt( discrim );

        // Compute quadratic _t_ values
        Interval<FloatT> q;
        if ( ( FloatT )b < static_cast< FloatT >( 0 ) )
        {
            q = MulPow2( static_cast< FloatT >( -.5 ), b - floatRootDiscrim );
        }
        else
        {
            q = MulPow2( static_cast< FloatT >( -.5 ), b + floatRootDiscrim );
        }
        *t0 = q / a;
        *t1 = c / q;
        if ( t0->LowerBound( ) > t1->LowerBound( ) )
        {
            std::swap( *t0, *t1 );
        }
        return true;
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> SumSquares( const Interval<FloatT>& i )
    {
        return Sqr( i );
    }

    template <typename FloatT, typename... Args>
        requires IsFloatingPoint<FloatT>
    inline Interval<FloatT> SumSquares( const Interval<FloatT>& i, Args... args )
    {
        Interval ss = FMA( i, i, SumSquares( args... ) );
        return Interval( std::max<FloatT>( 0, ss.LowerBound( ) ), ss.UpperBound( ) );
    }


}

#endif
