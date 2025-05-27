#pragma once
#ifndef __HCCMATH_H__
#define __HCCMATH_H__
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

#include "HCCSIMD.h"
#include "HCCMathForward.h"
#include "HCCFloatingPoint.h"

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

        static constexpr ValueType E = static_cast< ValueType >( M_E );
        static constexpr ValueType E2 = static_cast< ValueType >( M_E * M_E );
        static constexpr ValueType E3 = static_cast< ValueType >( M_E * M_E * M_E );

        static constexpr ValueType Infinity = std::numeric_limits<ValueType >::infinity( );
        static constexpr ValueType NegativeInfinity = -std::numeric_limits<ValueType >::infinity( );
        static constexpr ValueType NaN = std::numeric_limits<ValueType >::quiet_NaN( );
        static constexpr ValueType NegativeNaN = -std::numeric_limits<ValueType >::quiet_NaN( );

        static constexpr ValueType sNaN = std::numeric_limits<ValueType >::quiet_NaN( );
        static constexpr ValueType sNegativeNaN = -std::numeric_limits<ValueType >::signaling_NaN( );

        static constexpr ValueType MachineEpsilon = std::numeric_limits<ValueType>::epsilon( ) * 0.5f;
        
        static constexpr ValueType OneMinusEpsilon = 0x1.fffffep-1f;

        static constexpr ValueType Max = std::numeric_limits<ValueType>::max( );
        static constexpr ValueType Min = std::numeric_limits<ValueType>::min( );

        static constexpr ValueType DenormalMin = std::numeric_limits<ValueType>::denorm_min( );

        static constexpr ValueType Lowest = std::numeric_limits<ValueType>::lowest( );



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
        
        static constexpr ValueType E = M_E;
        static constexpr ValueType E2 = M_E * M_E;
        static constexpr ValueType E3 = M_E * M_E * M_E;

        static constexpr ValueType Infinity = std::numeric_limits<ValueType>::infinity( );
        static constexpr ValueType NegativeInfinity = -std::numeric_limits<ValueType >::infinity( );
        static constexpr ValueType NaN = std::numeric_limits<ValueType >::quiet_NaN( );
        static constexpr ValueType NegativeNaN = -std::numeric_limits<ValueType >::quiet_NaN( );

        static constexpr ValueType sNaN = std::numeric_limits<ValueType >::quiet_NaN( );
        static constexpr ValueType sNegativeNaN = -std::numeric_limits<ValueType >::signaling_NaN( );

        static constexpr ValueType MachineEpsilon = std::numeric_limits<ValueType>::epsilon( ) * 0.5;
        static constexpr double OneMinusEpsilon = 0x1.fffffffffffffp-1;

        static constexpr ValueType Max = std::numeric_limits<ValueType>::max( );
        static constexpr ValueType Min = std::numeric_limits<ValueType>::min( );

        static constexpr ValueType DenormalMin = std::numeric_limits<ValueType>::denorm_min( );

        static constexpr ValueType Lowest = std::numeric_limits<ValueType>::lowest( );

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

    constexpr inline bool IsSameValue( Int32 x, Int32 y ) noexcept
    {
        return x == y;
    }
    constexpr inline bool IsSameValue( UInt32 x, UInt32 y ) noexcept
    {
        return x == y;
    }
    constexpr inline bool IsSameValue( Int64 x, Int64 y ) noexcept
    {
        return x == y;
    }
    constexpr inline bool IsSameValue( UInt64 x, UInt64 y ) noexcept
    {
        return x == y;
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

    constexpr inline bool IsZero( Int32 x ) noexcept
    {
        return x == 0L;
    }
    constexpr inline bool IsZero( UInt32 x ) noexcept
    {
        return x == 0UL;
    }
    constexpr inline bool IsZero( Int64 x ) noexcept
    {
        return x == 0LL;
    }
    constexpr inline bool IsZero( UInt64 x ) noexcept
    {
        return x == 0ULL;
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
        constexpr FloatT factor = static_cast<FloatT>( M_PI/180.0 );
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
        constexpr FloatT factor = static_cast<FloatT>( 180.0/M_PI );
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
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::OpenLibM::nextafter( x, y );
        }
        else
        {
            return std::nextafter( x, y );
        }
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
        //float t;
        

        int32_t hx = std::bit_cast<Int32>( x );
        int32_t hy = std::bit_cast<Int32>( y );
        // |x| 
        int32_t ix = hx & 0x7fffffff;
        // |y| 
        int32_t iy = hy & 0x7fffffff;

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
            float t = x * x;
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
            return CopySign( std::numeric_limits<float>::infinity( ), y );
            //return x + x;
        }
        if ( hy < 0x00800000 )
        {
            // underflow 
            float t = x * x;
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
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::sqrtf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::sqrt( x );
            }
        }
        else
        {
            
            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return sqrtf( x );
                //_mm_store_ss( &result, _mm_sqrt_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_sqrt_pd( _mm_set_sd( x ) ) );
                
            }
            return result;
        }
    }
    static_assert( Sqrt(2.0) > 0.0 );

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ReciprocalSqrt( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            constexpr FloatType one = static_cast< FloatType >( 1. );
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                if ( x == 0.f )
                {
                    return CopySign( std::numeric_limits<float>::infinity( ), x );
                }
                return one / Math::Internal::OpenLibM::sqrtf( x );
            }
            else
            {
                if ( x == 0. )
                {
                    return CopySign( std::numeric_limits<double>::infinity( ), x );
                }
                return one / Math::Internal::OpenLibM::sqrt( x );
            }
        }
        else
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                FloatType result;
                _mm_store_ss( &result, _mm_rsqrt_ps( _mm_set_ss( x ) ) );
                return result;
            }
            else
            {
                constexpr FloatType one = static_cast< FloatType >( 1. );
                return one / Sqrt( x );
                
            }
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Cbrt( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::cbrtf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::cbrt( x );
            }
        }
        else
        {

            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_cbrt_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_cbrt_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }
    static_assert( Cbrt( 2.0 ) > 0.0 );

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
            constexpr T zero = static_cast< T >( 0.0 );
            constexpr T one = static_cast< T >( 1.0 );
            if ( ( a <= zero && b >= zero ) || ( a >= zero && b <= zero ) )
            {
                return t * b + ( one - t ) * a;
            }
            else if ( t == one )
            {
                return b;
            }
            T x = a + t * ( b - a );
            if ( ( t > one ) == ( b > a ) )
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
    /// Determines if any of the given integral or floating point values 
    /// is a not-a-number (NaN) value.
    /// </summary>
    /// <typeparam name="T">
    /// Integral or floating point type.
    /// </typeparam>
    /// <typeparam name="...Args">
    /// Integral or floating point types.
    /// </typeparam>
    /// <param name="val">
    /// Integral or floating point value.
    /// </param>
    /// <param name="...args">
    /// Integral or floating point value.
    /// </param>
    /// <returns>
    /// <c>true</c> if any of the given integral or floating point values 
    /// is a not-a-number (NaN) value, otherwise <c>false</c>.
    /// </returns>
    template<typename T, typename ... Args>
        requires IsArithmetic<T> && (IsArithmetic<Args> && ...)
    constexpr inline bool IsNaN( T val, Args&& ... args ) noexcept
    {
        if ( IsNaN( val ) )
        {
            return true;
        }
        return IsNaN( args ... );
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
    /// Determines if any of the given integral or floating point numbers
    /// is positive or negative infinity. 
    /// </summary>
    /// <typeparam name="T">
    /// Integral or floating point type.
    /// </typeparam>
    /// <typeparam name="...Args">
    /// Integral or floating point types.
    /// </typeparam>
    /// <param name="val">
    /// Integral or floating point value.
    /// </param>
    /// <param name="...args">
    /// Integral or floating point value.
    /// </param>
    /// <returns>
    /// <c>true</c> if any of the given integral or floating point numbers
    /// is positive or negative infinity, otherwise <c>false</c>. 
    /// </returns>
    template<typename T, typename ... Args>
        requires IsArithmetic<T> && ( IsArithmetic<Args> && ... )
    constexpr inline bool IsInf( T val, Args&& ... args ) noexcept
    {
        if ( IsInf( val ) )
        {
            return true;
        }
        return IsInf( args ... );
    }

    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsFinite( T val ) noexcept
    {
        return true;
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline bool IsFinite( T val ) noexcept
    {
        return Internal::OpenLibM::isfinite( val );
    }

    template<typename T, typename ... Args>
        requires IsArithmetic<T> && ( IsArithmetic<Args> && ... )
    constexpr inline bool IsFinite( Args&& ... args ) noexcept
    {
        return (IsFinite( args ) && ...);
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
                return Internal::OpenLibM::fabs( val );
            }
        }
    }
    static_assert( Abs( -1.0 ) == 1.0 );


    template<typename T>
        requires IsUnsignedInteger<T>
    constexpr inline std::remove_cvref_t<T> FastAbs( T val ) noexcept
    {
        return val;
    }

    template<typename T>
        requires IsSignedInteger<T>
    constexpr inline std::remove_cvref_t<T> FastAbs( T val ) noexcept
    {
        using IntT = std::remove_cvref_t<T>;
        
        if constexpr ( sizeof( IntT ) == 1 )
        {
            return std::bit_cast< IntT >( std::bit_cast< UInt8 >( val ) & static_cast< UInt8 >(0x7FU) );
        }
        else if constexpr ( sizeof( IntT ) == 2 )
        {
            return std::bit_cast< IntT >( std::bit_cast< UInt16 >( val ) & static_cast< UInt16 >( 0x7FFFU ) );
        }
        else if constexpr ( sizeof( IntT ) == 4 )
        {
            return std::bit_cast< IntT >( std::bit_cast< UInt32 >( val ) & 0x7FFFFFFFUL );
        }
        else
        {
            return std::bit_cast< IntT >( std::bit_cast< UInt64 >( val ) & 0x7FFFFFFFFFFFFFFFULL );
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FastAbs( T val ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return std::bit_cast< float >( std::bit_cast< UInt32 >( val ) & 0x7FFFFFFFUL );
        }
        else
        {
            return std::bit_cast< double >( std::bit_cast< UInt64 >( val ) & 0x7FFFFFFFFFFFFFFFULL );
        }
    }


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
        using FloatT = std::remove_cvref_t<T>;

        std::pair<FloatT, int> result;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            result.first = Internal::OpenLibM::frexpf( val, &result.second );
        }
        else
        {
            result.first = Internal::OpenLibM::frexp( val, &result.second );
        }
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
        using FloatT = std::remove_cvref_t<T>;

        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Internal::OpenLibM::frexpf( val, exp );
        }
        else
        {
            return Internal::OpenLibM::frexp( val, exp );
        }
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
        using FloatT = std::remove_cvref_t<T>;

        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Internal::OpenLibM::frexpf( val, &exp );
        }
        else
        {
            return Internal::OpenLibM::frexp( val, &exp );
        }
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
        requires IsFloatingPoint<ValueT> 
    constexpr inline std::pair<std::remove_cvref_t<ValueT>, std::remove_cvref_t<ValueT>> ModF( ValueT val ) noexcept
    {
        using FloatT = std::remove_cvref_t<ValueT>;
        std::pair<FloatT, FloatT> result;

        if constexpr ( std::is_same_v<FloatT, float> )
        {
            result.second = Internal::OpenLibM::modff( val, &result.first );
        }
        else
        {
            result.second = Internal::OpenLibM::modf( val, &result.first );
        }
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
        requires IsFloatingPoint<ValueT>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT* integerPart ) noexcept
    {
        using FloatT = std::remove_cvref_t<ValueT>;

        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Internal::OpenLibM::modff( val, integerPart );
        }
        else
        {
            return Internal::OpenLibM::modf( val, integerPart );
        }
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
        requires IsFloatingPoint<ValueT>
    constexpr inline std::remove_cvref_t<ValueT> ModF( ValueT val, ValueT& integerPart ) noexcept
    {
        using FloatT = std::remove_cvref_t<ValueT>;

        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Internal::OpenLibM::modff( val, &integerPart );
        }
        else
        {
            return Internal::OpenLibM::modf( val, &integerPart );
        }
    }


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

    template<typename T, typename ...Args>
        requires IsFloatingPoint<T> || IsInteger<T>
    constexpr inline T Min( T first, T second, Args... remaining ) noexcept
    {
        return Min( Min( first, second ), remaining... );
    }



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

    template<typename T, typename ...Args>
        requires IsArithmetic<T>
    constexpr inline T Max( T first, T second, Args... remaining ) noexcept
    {
        return Max( Max( first, second ), remaining... );
    }


    template<SimpleSpanLike T>
        requires IsArithmetic<typename T::value_type>
    constexpr inline typename T::value_type Multiply( const T & values )
    {
        using ValueType = typename T::value_type;
        ValueType result = static_cast< ValueType >( 1 );
        for ( auto v : values )
        {
            result *= v;
        }
        return result;
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
            if constexpr ( std::is_same_v<double, FloatT> )
            {
                alignas( 16 ) double result;
                _mm_store_sd( &result, _mm_round_pd( _mm_set_sd( value ), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC ) );
                return result;
            }
            else
            {
                //return __truncf( value );
                
                alignas(16) float result;
                _mm_store_ss( &result, _mm_round_ps( _mm_set_ss( value ), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC ) );
                return result;
                
            }
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
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __floorf( value );
            }
            else
            {
                return __floor( value );
            }
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
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return __ceilf( value );
            }
            else
            {
                return __ceil( value );
            }
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
    template<typename T1, typename T2, typename T3>
        requires IsArithmetic<T1> && IsArithmetic<T2>&& IsArithmetic<T3>
    constexpr inline T1 Clamp( T1 value, T2 minimumValue, T3 maximumValue )
    {
        if ( value < static_cast< T1 >( minimumValue ) )
        {
            return static_cast<T1>( minimumValue );
        }
        else if ( static_cast< T1 >( maximumValue ) < value )
        {
            return static_cast<T1>( maximumValue );
        }
        else
        {
            return value;
        }
    }

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
        requires IsArithmetic<T> && IsArithmetic<U>
    constexpr inline MakeFloatingPoint<T,U> Lerp( T a, T b, U t ) noexcept
    {
        return ( 1 - t ) * a + t * b;
    }

    template<typename T, typename U>
        requires IsArithmetic<T>&& IsArithmetic<U>
    constexpr inline MakeFloatingPoint<T, U> Lerp2( U t, T a, T b ) noexcept
    {
        //using FloatT = MakeFloatingPoint<T, U>;
        //return Internal::LerpImpl( static_cast< FloatT >( a ), static_cast< FloatT >( b ), static_cast< FloatT >( t ) );
        return ( 1 - t ) * a + t * b;
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
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            return Math::Internal::CopySignImpl<FloatType>( magnitude, signValue );
        }
        else
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Internal::OpenLibM::copysignf( magnitude, signValue );
            }
            else
            {
                return Math::Internal::CopySignImpl<FloatType>( magnitude, signValue );
            }
        }

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
            return CopySign( std::numeric_limits<double>::infinity( ), x );
            //return huge * CopySign( huge, x );
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
            return CopySign( std::numeric_limits<float>::infinity( ),  x );
            //return huge * CopySign( huge, x ); 
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
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return Internal::OpenLibM::fmodf( x, y );
            }
            else
            {
                return Internal::OpenLibM::fmod( x, y );
            }
        }
        else
        {
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return Internal::OpenLibM::fmodf( x, y );
            }
            else
            {
                return std::fmod( x, y );
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
        using FloatType = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatType, float> )
        {
            return Math::Internal::OpenLibM::expf( x );
        }
        else
        {
            return Math::Internal::OpenLibM::exp( x );
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ExpM1( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::expm1f( x );
            }
            else
            {
                return Math::Internal::OpenLibM::expm1( x );
            }
        }
        else
        {
            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_expm1_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_expm1_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Exp2( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::exp2f( x );
            }
            else
            {
                return Math::Internal::OpenLibM::exp2( x );
            }
        }
        else
        {
            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_exp2_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_exp2_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }

    namespace Internal
    {
        constexpr double Exp10Impl( double x ) noexcept
        {
            return Pow( 10.0, x );
        }

        constexpr float Exp10Impl( float x ) noexcept
        {
            return Pow( 10.0f, x );
        }

    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Exp10( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::Exp10Impl( x );
            }
            else
            {
                return Math::Internal::Exp10Impl( x );
            }
        }
        else
        {
            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_exp10_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_exp10_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
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
            return Math::Internal::OpenLibM::FastHypot( x, y );
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
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Internal::OpenLibM::logf( x );
        }
        else
        {
            return Internal::OpenLibM::log( x );
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Log1P( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Internal::OpenLibM::log1pf( x );
        }
        else
        {
            return Internal::OpenLibM::log1p( x );
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
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::log2f( x );
        }
        else
        {
            return Math::Internal::OpenLibM::log2( x );
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
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::log10f( x );
        }
        else
        {
            return Math::Internal::OpenLibM::log10( x );
        }
    }

    /// <summary>
    /// Computes the value of x raised to the power y.
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
    /// x raised to the power y.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Pow( T x, T y ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::powf( x, y );
        }
        else
        {
            return Math::Internal::OpenLibM::pow( x, y );
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
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::sinf( x );
        }
        else
        {
            if ( std::is_constant_evaluated( ) )
            {
                return Math::Internal::OpenLibM::sin( x );
            }
            else
            {
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
        return Math::Internal::OpenLibM::FastASin( x );
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
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::cosf( x );
        }
        else
        {
            if ( std::is_constant_evaluated( ) )
            {
                return Math::Internal::OpenLibM::cos( x );
            }
            else
            {
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
        return Math::Internal::OpenLibM::FastACos( x );
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
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::tanf( x );
        }
        else
        {
            if ( std::is_constant_evaluated( ) )
            {
                return Math::Internal::OpenLibM::tan( x );
            }
            else
            {
                return tan( x );
            }
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
        if ( std::is_constant_evaluated( ) )
        {
            using FloatT = std::remove_cvref_t<T>;
            if constexpr ( std::is_same_v<FloatT, float> )
            {
                return Math::Internal::OpenLibM::atanf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::atan( x );
            }
        }
        else
        {
            return std::atan( x );
        }
    }

    /// <summary>
    /// <para>
    /// arc tangent of y / x using the signs of arguments to determine the correct quadrant.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="y">
    /// A floating point value.
    /// </param>
    /// <param name="c">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The arc tangent of y / x using the signs of arguments to determine the correct quadrant.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan( T y, T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::atan2f( y, x );
        }
        else
        {
            return Math::Internal::OpenLibM::atan2( y, x );
        }
    }
    /// <summary>
    /// <para>
    /// The arc tangent of y / x using the signs of arguments to determine the correct quadrant.
    /// </para>
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type.
    /// </typeparam>
    /// <param name="y">
    /// A floating point value.
    /// </param>
    /// <param name="x">
    /// A floating point value.
    /// </param>
    /// <returns>
    /// The arc tangent of y / x using the signs of arguments to determine the correct quadrant.
    /// </returns>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATan2( T y, T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::atan2f( y, x );
        }
        else
        {
            return Math::Internal::OpenLibM::atan2( y, x );
        }
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
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::sincosf( x, &sinResult, &cosResult );
        }
        else
        {
            return Math::Internal::OpenLibM::sincos( x, &sinResult, &cosResult );
        }
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
    inline constexpr void SinCos( T x, T* sinResult, T* cosResult ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::sincosf( x, sinResult, cosResult );
        }
        else
        {
            return Math::Internal::OpenLibM::sincos( x, sinResult, cosResult );
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> SinH( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::sinhf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::sinh( x );
            }
        }
        else
        {

            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_sinh_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_sinh_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ASinH( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::asinhf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::asinh( x );
            }
        }
        else
        {

            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_asinh_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_asinh_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> CosH( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::coshf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::cosh( x );
            }
        }
        else
        {

            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_cosh_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_cosh_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ACosH( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::acoshf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::acosh( x );
            }
        }
        else
        {

            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_acosh_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_acosh_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> TanH( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::tanhf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::tanh( x );
            }
        }
        else
        {

            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_tanh_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_tanh_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ATanH( T x ) noexcept
    {
        using FloatType = std::remove_cvref_t<T>;
        if ( std::is_constant_evaluated( ) )
        {
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                return Math::Internal::OpenLibM::atanhf( x );
            }
            else
            {
                return Math::Internal::OpenLibM::atanh( x );
            }
        }
        else
        {

            FloatType result;
            if constexpr ( std::is_same_v<FloatType, float> )
            {
                _mm_store_ss( &result, _mm_atanh_ps( _mm_set_ss( x ) ) );
            }
            else
            {
                _mm_store_sd( &result, _mm_atanh_pd( _mm_set_sd( x ) ) );
            }
            return result;
        }
    }






    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> J0( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::j0f( x );
        }
        else
        {
            return Math::Internal::OpenLibM::j0( x );
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> J1( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::j1f( x );
        }
        else
        {
            return Math::Internal::OpenLibM::j1( x );
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> JN(int n, T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::jnf( n, x );
        }
        else
        {
            return Math::Internal::OpenLibM::jn( n, x );
        }
    }


    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Y0( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::y0f( x );
        }
        else
        {
            return Math::Internal::OpenLibM::y0( x );
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Y1( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::y1f( x );
        }
        else
        {
            return Math::Internal::OpenLibM::y1( x );
        }
    }

    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> YN( int n, T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::ynf( n, x );
        }
        else
        {
            return Math::Internal::OpenLibM::yn( n, x );
        }
    }

    /// <summary>
    /// Computes the error function of x
    /// </summary>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Erf( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::erff( x );
        }
        else
        {
            return Math::Internal::OpenLibM::erf( x );
        }
    }

    /// <summary>
    /// Computes the complementary error function of x,
    /// </summary>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> ErfC( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::erfcf( x );
        }
        else
        {
            return Math::Internal::OpenLibM::erfc( x );
        }
    }

    /// <summary>
    /// Computes the gamma function of x.
    /// </summary>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> TGamma( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::tgammaf( x );
        }
        else
        {
            return Math::Internal::OpenLibM::tgamma( x );
        }
    }

    /// <summary>
    /// Computes the natural logarithm of the absolute value of the gamma function of x.
    /// </summary>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> LGamma( T x ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::lgammaf( x );
        }
        else
        {
            return Math::Internal::OpenLibM::lgamma( x );
        }
    }



    /// <summary>
    /// Computes the IEEE remainder of the floating point division operation x / y
    /// </summary>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> Remainder( T x, T y ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::remainderf( x, y );
        }
        else
        {
            return Math::Internal::OpenLibM::remainder( x, y );
        }
    }

    
    /// <summary>
    /// Computes the floating-point remainder of the division operation x / y like Remainder. 
    /// Additionally, the sign and at least the three of the last bits of x / y will be 
    /// stored in quo, sufficient to determine the octant of the result within a period.
    /// </summary>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> RemQuo( T x, T y, int* quo ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::remquof( x, y, quo );
        }
        else
        {
            return Math::Internal::OpenLibM::remquo( x, y, quo );
        }
    }

    /// <summary>
    /// Returns the positive difference between x and y, that is, if x > y, returns x - y, otherwise (i.e. if x <= y) returns +0.
    /// </summary>
    template<typename T>
        requires IsFloatingPoint<T>
    constexpr inline std::remove_cvref_t<T> FDim( T x, T y ) noexcept
    {
        using FloatT = std::remove_cvref_t<T>;
        if constexpr ( std::is_same_v<FloatT, float> )
        {
            return Math::Internal::OpenLibM::fdimf( x, y );
        }
        else
        {
            return Math::Internal::OpenLibM::fdim( x, y );
        }
    }



    /// <summary>
    /// Computes x * y + z as if to infinite precision and rounded only once to fit the result type.
    /// </summary>
    template<typename T>
        requires IsInteger<T>
    inline constexpr T FMA( T a, T b, T c ) noexcept
    {
        return a * b + c;
    }

    /// <summary>
    /// Computes x * y + z as if to infinite precision and rounded only once to fit the result type.
    /// </summary>
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

    /*
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
    */

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

    template<typename T>
        requires IsArithmetic<T> || IsComplex<T>
    constexpr inline T Sqr( T v )
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
        requires IsArithmetic<FloatT>
    constexpr inline FloatT EvaluatePolynomial( FloatT t, C c )
    {
        return c;
    }

    template <typename FloatT, typename C, typename... Args>
        requires IsArithmetic<FloatT>
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
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr FloatT NextFloatDown( FloatT v )
    {
        return NextDown( v );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT Gamma( int n )
    {
        return ( static_cast< FloatT >( n ) * Constants<FloatT>::MachineEpsilon ) / ( Constants< FloatT >::One - static_cast< FloatT >( n ) * Constants<FloatT>::MachineEpsilon );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT AddAdjustUp( FloatT a, FloatT b )
    {
        return NextUp( a + b );
    }
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT AddAdjustDown( FloatT a, FloatT b )
    {
        return NextDown( a + b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SubAdjustUp( FloatT a, FloatT b )
    {
        return AddAdjustUp( a, -b );
    }
    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SubAdjustDown( FloatT a, FloatT b )
    {
        return AddAdjustDown( a, -b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT MulAdjustUp( FloatT a, FloatT b )
    {
        return NextUp( a * b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT MulAdjustDown( FloatT a, FloatT b )
    {
        return NextDown( a * b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT DivAdjustUp( FloatT a, FloatT b )
    {
        return NextUp( a / b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT DivAdjustDown( FloatT a, FloatT b )
    {
        return NextDown( a / b );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SqrtAdjustUp( FloatT a )
    {
        return NextUp( Sqrt( a ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT SqrtAdjustDown( FloatT a )
    {
        return std::max<FloatT>( 0, NextDown( Sqrt( a ) ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT FMAAdjustUp( FloatT a, FloatT b, FloatT c )
    {
        return NextUp( FMA( a, b, c ) );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT FMAAdjustDown( FloatT a, FloatT b, FloatT c )
    {
        return NextDown( FMA( a, b, c ) );
    }


    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    constexpr inline FloatT FastLog2( FloatT x )
    {
        return Log2( x );
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
        //static inline constexpr Interval Pi{Constants<value_type>::Pi,Constants<value_type>::Pi };
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
                return Interval( SubAdjustDown( v, err ), AddAdjustUp( v, err ) );
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
            return { AddAdjustDown( lowerBound_, i.lowerBound_ ), AddAdjustUp( upperBound_, i.upperBound_ ) };
        }

        constexpr Interval operator-( const Interval& i ) const
        {
            return { SubAdjustDown( lowerBound_, i.upperBound_ ), SubAdjustUp( upperBound_, i.lowerBound_ ) };
        }

        constexpr Interval operator*( const Interval& i ) const
        {
            value_type lp[ 4 ] = 
            { 
                MulAdjustDown( lowerBound_, i.lowerBound_ ),
                MulAdjustDown( upperBound_, i.lowerBound_ ),
                MulAdjustDown( lowerBound_, i.upperBound_ ),
                MulAdjustDown( upperBound_, i.upperBound_ )
            };
            value_type hp[ 4 ] = 
            { 
                MulAdjustUp( lowerBound_, i.lowerBound_ ),
                MulAdjustUp( upperBound_, i.lowerBound_ ),
                MulAdjustUp( lowerBound_, i.upperBound_ ),
                MulAdjustUp( upperBound_, i.upperBound_ )
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
                *this = Interval( MulAdjustDown( f, lowerBound_ ), MulAdjustUp( f, upperBound_ ) );
            }
            else
            {
                *this = Interval( MulAdjustDown( f, upperBound_ ), MulAdjustUp( f, lowerBound_ ) );
            }
            return *this;
        }
        constexpr Interval& operator/=( value_type f )
        {
            if ( f > static_cast< value_type >( 0 ) )
            {
                *this = Interval( DivAdjustDown( lowerBound_, f ), DivAdjustUp( upperBound_, f ) );
            }
            else
            {
                *this = Interval( DivAdjustDown( upperBound_, f ), DivAdjustUp( lowerBound_, f ) );
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
        FloatT lowQuot[ 4 ] = { DivAdjustDown( lowerBound_, interval.lowerBound_ ), DivAdjustDown( upperBound_, interval.lowerBound_ ),
                            DivAdjustDown( lowerBound_, interval.upperBound_ ), DivAdjustDown( upperBound_, interval.upperBound_ ) };
        FloatT highQuot[ 4 ] = { DivAdjustUp( lowerBound_, interval.lowerBound_ ), DivAdjustUp( upperBound_, interval.lowerBound_ ),
                             DivAdjustUp( lowerBound_, interval.upperBound_ ), DivAdjustUp( upperBound_, interval.upperBound_ ) };
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
            return Interval<FloatT>( static_cast< FloatT >( 0 ), MulAdjustUp( ahigh, ahigh ) );
        }
        return Interval<FloatT>( MulAdjustDown( alow, alow ), MulAdjustUp( ahigh, ahigh ) );
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
            return Interval<FloatT>( MulAdjustDown( f, i.LowerBound( ) ), MulAdjustUp( f, i.UpperBound( ) ) );
        }
        else
        {
            return Interval<FloatT>( MulAdjustDown( f, i.UpperBound( ) ), MulAdjustUp( f, i.LowerBound( ) ) );
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
            return Interval( DivAdjustDown( f, i.UpperBound( ) ), DivAdjustUp( f, i.LowerBound( ) ) );
        }
        else
        {
            return Interval( DivAdjustDown( f, i.LowerBound( ) ), DivAdjustUp( f, i.UpperBound( ) ) );
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
            return Interval( MulAdjustDown( f, i.LowerBound( ) ), MulAdjustUp( f, i.UpperBound( ) ) );
        else
            return Interval( MulAdjustDown( f, i.UpperBound( ) ), MulAdjustUp( f, i.LowerBound( ) ) );
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
            return Interval( DivAdjustDown( i.LowerBound( ), f ), DivAdjustUp( i.UpperBound( ), f ) );
        }
        else
        {
            return Interval( DivAdjustDown( i.UpperBound( ), f ), DivAdjustUp( i.LowerBound( ), f ) );
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
        return { SqrtAdjustDown( i.LowerBound( ) ), SqrtAdjustUp( i.UpperBound( ) ) };
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
        FloatT low = Min( FMAAdjustDown( a.LowerBound( ), b.LowerBound( ), c.LowerBound( ) ),
                              FMAAdjustDown( a.UpperBound( ), b.LowerBound( ), c.LowerBound( ) ),
                              FMAAdjustDown( a.LowerBound( ), b.UpperBound( ), c.LowerBound( ) ),
                              FMAAdjustDown( a.UpperBound( ), b.UpperBound( ), c.LowerBound( ) ) );
        FloatT high = Max( FMAAdjustUp( a.LowerBound( ), b.LowerBound( ), c.UpperBound( ) ),
                               FMAAdjustUp( a.UpperBound( ), b.LowerBound( ), c.UpperBound( ) ),
                               FMAAdjustUp( a.LowerBound( ), b.UpperBound( ), c.UpperBound( ) ),
                               FMAAdjustUp( a.UpperBound( ), b.UpperBound( ), c.UpperBound( ) ) );
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
        

        return { NextDown( NextDown( low ) ), NextUp( NextUp( high ) ) };
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

        return Interval<FloatT>( std::max<FloatT>( static_cast< FloatT >( 0 ), NextDown( low ) ), NextUp( high ) );
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
        low = std::max<FloatT>( static_cast< FloatT >( -1 ), NextDown( low ) );
        high = std::min<FloatT>( static_cast< FloatT >( 1 ), NextUp( high ) );
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
        FloatT low = Math::Cos( std::max<FloatT>( static_cast< FloatT >( 0 ), i.LowerBound( ) ) );
        FloatT high = Math::Cos( i.UpperBound( ) );
        if ( low > high )
        {
            std::swap( low, high );
        }
        low = std::max<FloatT>( static_cast< FloatT >( -1 ), NextDown( low ) );
        high = std::min<FloatT>( static_cast< FloatT >( 1 ), NextUp( high ) );
        if ( InRange( Constants<FloatT>::Pi, i ) )
        {
            low = static_cast< FloatT >( -1 );
        }

        return Interval( low, high );
    }

    template<typename FloatT>
        requires IsFloatingPoint<FloatT>
    inline void SinCos( const Interval<FloatT>& i, Interval<FloatT>* sine, Interval<FloatT>* cosine )
    {
        FloatT sinLow;
        FloatT cosLow;
        Math::SinCos( std::max<FloatT>( static_cast< FloatT >( 0 ), i.LowerBound( ) ), &sinLow, &cosLow );

        FloatT sinHigh;
        FloatT cosHigh;
        Math::SinCos( i.UpperBound( ), &sinHigh, &cosHigh );

        if ( sinLow > sinHigh )
        {
            std::swap( sinLow, sinHigh );
        }
        if ( cosLow > cosHigh )
        {
            std::swap( cosLow, cosHigh );
        }
        sinLow = std::max<FloatT>( static_cast< FloatT >( -1 ), NextDown( sinLow ) );
        sinHigh = std::min<FloatT>( static_cast< FloatT >( 1 ), NextUp( sinHigh ) );
        cosLow = std::max<FloatT>( static_cast< FloatT >( -1 ), NextDown( cosLow ) );
        cosHigh = std::min<FloatT>( static_cast< FloatT >( 1 ), NextUp( cosHigh ) );

        if ( InRange( Constants<FloatT>::PiOver2, i ) )
        {
            sinHigh = static_cast< FloatT >( 1 );
        }
        if ( InRange( ( static_cast< FloatT >( 3. ) / static_cast< FloatT >( 2. ) ) * Constants<FloatT>::Pi, i ) )
        {
            sinLow = static_cast< FloatT >( -1 );
        }
        if ( InRange( Constants<FloatT>::Pi, i ) )
        {
            cosLow = static_cast< FloatT >( -1 );
        }
        *sine = Interval( sinLow, sinHigh );
        *cosine = Interval( cosLow, cosHigh );
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

    namespace Internal
    {
        constexpr float HalfToFloat( const UInt16 value )
        {
            constexpr UInt32 Magic = 113UL << 23UL;
            constexpr UInt32 ShiftedExp = 0x7c00 << 13;

            const UInt16 h = value;
            UInt32 result = ( h & 0x7fff ) << 13;

            const UInt32 exp = ShiftedExp & result;
            result += ( 127 - 15 ) << 23;

            if ( exp == ShiftedExp )
            {
                result += ( 128 - 16 ) << 23;
            }
            else if ( exp == 0 )
            {
                result += 1 << 23;
                auto f = std::bit_cast< float >( result );
                f -= std::bit_cast< float >( Magic );
                result = std::bit_cast< UInt32 >( f );
            }

            result |= ( h & 0x8000 ) << 16;
            return std::bit_cast< float >( result );
        }

        constexpr UInt16 FloatToHalf( float value )
        {
            constexpr UInt32 FloatInfinity = 255UL << 23UL;
            constexpr UInt32 HalfInfinity = 31UL << 23UL;
            constexpr UInt32 Magic = 15UL << 23UL;
            constexpr UInt32 SignMask = 0x80000000UL;
            constexpr UInt32 RoundMask = ~0xfffUL;

            UInt32 v = std::bit_cast< UInt32 >( value );

            const UInt32 sign = v & SignMask;
            v ^= sign;
            UInt32 h = 0;
            if ( v >= FloatInfinity )
            {
                h = ( v > FloatInfinity ) ? 0x7e00 : 0x7c00;
            }
            else
            {
                v &= RoundMask;
                auto f = std::bit_cast< float >( v );
                f *= std::bit_cast< float >( Magic );
                v = std::bit_cast< UInt32 >( f );
                v -= RoundMask;

                if ( v > HalfInfinity )
                {
                    v = HalfInfinity;
                }
                h = v >> 13;
            }

            h |= sign >> 16;
            return h;
        }
    }

    class Half
    {
    public:
        static constexpr UInt16 ExponentMask = 0b0111110000000000;
        static constexpr UInt16 SignificandMask = 0b1111111111;
        static constexpr UInt16 NegativeZero = 0b1000000000000000;
        static constexpr UInt16 PositiveZero = 0;
        static constexpr UInt16 NegativeInfinity = 0b1111110000000000;
        static constexpr UInt16 PositiveInfinity = 0b0111110000000000;
    private:
        UInt16 value_ = 0;
    public:
        constexpr Half( ) noexcept = default;
        constexpr Half( const Half& other ) noexcept = default;
        constexpr Half& operator=( const Half& other ) noexcept = default;

    private:
        explicit constexpr Half( UInt16 value ) noexcept
            : value_( value )
        { }
    public:

        explicit constexpr Half( float value ) noexcept
            : value_( Internal::FloatToHalf( value ) )
        { }
        explicit constexpr Half( double value ) noexcept
            : Half( static_cast<float>( value ) )
        { }

        static constexpr Half FromBits( UInt16 value ) noexcept
        {
            return Half( value );
        }

        constexpr UInt16 Bits( ) const noexcept
        { 
            return value_; 
        }

        explicit constexpr operator float( ) const noexcept
        {
            return Internal::HalfToFloat( value_ );
        }
        explicit constexpr operator double( ) const noexcept
        { 
            return static_cast< double >( Internal::HalfToFloat( value_ ) );
        }

        constexpr bool operator==( const Half& other ) const noexcept
        {
            if ( value_ == other.value_ )
            {
                return true;
            }
            return ( value_ == NegativeZero && other.value_ == PositiveZero ) || ( value_ == PositiveZero && other.value_ == NegativeZero );
        }
        constexpr bool operator!=( const Half& other ) const noexcept
        { 
            return !( *this == other );
        }

        constexpr Half operator-( ) const noexcept
        { 
            return Half( static_cast<UInt16>( value_ ^ ( 1 << 15 ) ) );
        }

        constexpr int Sign( ) const noexcept
        { 
            return ( value_ >> 15 ) ? -1 : 1;
        }

        constexpr bool IsInf( ) const noexcept
        { 
            return value_ == PositiveInfinity || value_ == NegativeInfinity;
        }

        constexpr bool IsNaN( ) const noexcept
        {
            return ( ( value_ & ExponentMask ) == ExponentMask &&
                ( value_ & SignificandMask ) != 0 );
        }

        
        constexpr Half NextUp( ) const noexcept
        {
            if ( IsInf( ) && Sign( ) == 1 )
            {
                return *this;
            }

            Half up = *this;
            if ( up.value_ == NegativeZero )
            {
                up.value_ = PositiveZero;
            }
            
            if ( up.Sign( ) >= 0 )
            {
                ++up.value_;
            }
            else
            {
                --up.value_;
            }
            return up;
        }

        constexpr Half NextDown( ) const noexcept
        {
            if ( IsInf( ) && Sign( ) == -1 )
            {
                return *this;
            }

            Half down = *this;
            if ( down.value_ == PositiveZero )
            {
                down.value_ = NegativeZero;
            }
            if ( down.Sign( ) >= 0 )
            {
                --down.value_;
            }
            else
            {
                ++down.value_;
            }
            return down;
        }
    };
}


namespace std
{
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Math::Half, CharT>
    {
        formatter<float, CharT> floatFormatter;
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return floatFormatter.parse( ctx );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Half& half, FormatContext& ctx ) const
        {
            float v = static_cast< float >( half );
            return floatFormatter.format( v, ctx );
        }
    };

    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Math::Interval<float>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Interval<float>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}, {}]", value.LowerBound( ), value.UpperBound( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}, {}]", value.LowerBound( ), value.UpperBound( ) );
            }
        }
    };
    template<typename CharT>
    struct formatter<Harlinn::Common::Core::Math::Interval<double>, CharT>
    {
        constexpr auto parse( basic_format_parse_context<CharT>& ctx )
        {
            return ctx.begin( );
        }

        template <typename FormatContext>
        auto format( const Harlinn::Common::Core::Math::Interval<double>& value, FormatContext& ctx ) const
        {
            if constexpr ( is_same_v<CharT, wchar_t> )
            {
                return std::format_to( ctx.out( ), L"[{}, {}]", value.LowerBound( ), value.UpperBound( ) );
            }
            else
            {
                return std::format_to( ctx.out( ), "[{}, {}]", value.LowerBound( ), value.UpperBound( ) );
            }
        }
    };

}

#endif
