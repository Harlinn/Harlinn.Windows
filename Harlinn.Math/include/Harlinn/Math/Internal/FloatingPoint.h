#pragma once
#ifndef HARLINN_MATH_INTERNAL_FLOATINGPOINT_H_
#define HARLINN_MATH_INTERNAL_FLOATINGPOINT_H_

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

#include "Integer.h"
#include <Harlinn/Common/Utils.h>

namespace Harlinn::Math
{
    using namespace Harlinn::Common;
}

namespace Harlinn::Math::Internal
{
    
    template <FloatingPointType T>
    struct FractionWidth;

    template <>
    struct FractionWidth<float>
    {
        static constexpr UInt32 value = 23;
    };
    template <>
    struct FractionWidth<double>
    {
        static constexpr UInt32 value = 52;
    };


    template <FloatingPointType T>
    struct ExponentWidth;
    template <>
    struct ExponentWidth<float>
    {
        static constexpr UInt32 value = 8;
    };
    template <>
    struct ExponentWidth<double>
    {
        static constexpr UInt32 value = 11;
    };

    template <FloatingPointType T>
    struct ExponentBias;
    template <>
    struct ExponentBias<float>
    {
        static constexpr UInt32 value = _FBIAS;
    };
    template <>
    struct ExponentBias<double>
    {
        static constexpr UInt32 value = _DBIAS;
    };

    template <FloatingPointType T>
    struct InfinityUnsignedValue;
    template <>
    struct InfinityUnsignedValue<float>
    {
        static constexpr UInt32 value = 0X7F800000UL;
    };
    template <>
    struct InfinityUnsignedValue<double>
    {
        static constexpr UInt64 value = 0x7FF0000000000000ULL;
    };

    template <FloatingPointType T>
    struct NegativeInfinityUnsignedValue;
    template <>
    struct NegativeInfinityUnsignedValue<float>
    {
        static constexpr UInt32 value = 0xFF800000UL;
    };
    template <>
    struct NegativeInfinityUnsignedValue<double>
    {
        static constexpr UInt64 value = 0xFFF0000000000000ULL;
    };
    template <FloatingPointType T>
    struct QuietNaNUnsignedValue;
    template <>
    struct QuietNaNUnsignedValue<float>
    {
        static constexpr UInt32 value = 0XFFC00001UL;
    };
    template <>
    struct QuietNaNUnsignedValue<double>
    {
        static constexpr UInt64 value = 0x7FF0000000000001ULL;
    };


    template <FloatingPointType T>
    struct StorageType;
    template <>
    struct StorageType<float>
    {
        using type = UInt32;
    };
    template <>
    struct StorageType<double>
    {
        using type = UInt64;
    };

    template <typename T>
        requires( sizeof( T ) > sizeof( void* ) )
    inline constexpr T MultiplyAdd( const T& x, const T& y, const T& z )
    {
        if ( std::is_constant_evaluated( ) )
        {
            return x * y + z;
        }
        else
        {
            return std::fma( x, y, z );
        }
    }

    template <typename T>
        requires ( sizeof( T ) <= sizeof( void* ) )
    inline constexpr T MultiplyAdd( T x, T y, T z )
    {
        if ( std::is_constant_evaluated( ) )
        {
            return x * y + z;
        }
        else
        {
            return std::fma( x, y, z );
        }
    }

    template <typename T>
        requires ( sizeof( T ) > sizeof( void* ) )
    inline constexpr T PolyEval( const T&, const T& a0 )
    {
        return a0;
    }

    template <typename T>
        requires ( sizeof( T ) <= sizeof( void* ) )
    inline constexpr T PolyEval( T, T a0 )
    {
        return a0;
    }

    template <typename T, typename... Ts>
        requires ( sizeof( T ) > sizeof( void* ) )
    inline constexpr T PolyEval( const T& x, const T& a0, const Ts &...a )
    {
        return MultiplyAdd( x, PolyEval( x, a... ), a0 );
    }

    template <typename T, typename... Ts>
        requires ( sizeof( T ) <= sizeof( void* ) )
    inline constexpr T PolyEval( T x, T a0, Ts... a )
    {
        return MultiplyAdd( x, PolyEval( x, a... ), a0 );
    }

    /// <summary>
    /// Holds the value of the exponent part of a floating point value.
    /// </summary>
    /// <typeparam name="T">
    /// Floating point type
    /// </typeparam>
    template<typename T>
    class Exponent : public Integer<Int32>
    {
    public:
        using FloatType = T;
        using Base = Integer<Int32>;
        static constexpr Int32 Bias = static_cast< Int32 >( Internal::ExponentBias<FloatType>::value );

        using Base::Base;

        static constexpr Exponent SubNormal( ) noexcept
        {
            return Exponent( -Bias );
        }
        static constexpr Exponent Min( )
        {
            return Exponent( 1 - Bias );
        }
        static constexpr Exponent Zero( )
        {
            return Exponent( 0 );
        }
        static constexpr Exponent Max( )
        {
            return Exponent( Bias );
        }
        static constexpr Exponent Inf( )
        {
            return Exponent( Bias + 1 );
        }
    };

    /// <summary>
    /// Holds the value of the biased exponent part of a floating point value.
    /// </summary>
    /// <typeparam name="T">
    /// Floating point type
    /// </typeparam>
    template<typename T>
    class BiasedExponent : public Integer<Int32>
    {
    public:
        using FloatType = T;
        using Base = Integer<Int32>;
        static constexpr Int32 Bias = static_cast< Int32 >( Internal::ExponentBias<FloatType>::value );

        using Base::Base;

        constexpr BiasedExponent( Exponent<FloatType> exp ) noexcept
            : Base( static_cast< Int32 >( exp ) + Bias )
        {
        }

        // Cast operator to get convert from BiasedExponent to Exponent.
        constexpr operator Exponent<FloatType>( ) const noexcept
        {
            return Exponent<FloatType>( Base::value_ - Bias );
        }

        constexpr BiasedExponent& operator++( ) noexcept
        {
            assert( *this != BiasedExponent( Exponent::inf( ) ) );
            ++Base::value_;
            return *this;
        }

        constexpr BiasedExponent operator++( int ) noexcept
        {
            assert( *this != BiasedExponent( Exponent::inf( ) ) );
            BiasedExponent result = *this;
            ++Base::value_;
            return result;
        }

        constexpr BiasedExponent& operator--( ) noexcept
        {
            assert( *this != BiasedExponent( Exponent::subnormal( ) ) );
            --Base::value_;
            return *this;
        }

        constexpr BiasedExponent operator--( int ) noexcept
        {
            assert( *this != BiasedExponent( Exponent::subnormal( ) ) );
            BiasedExponent result = *this;
            --Base::value_;
            return result;
        }
    };

    /// <summary>
    /// Holds the value of the significand part of a floating point value.
    /// </summary>
    /// <typeparam name="T">
    /// Floating point type
    /// </typeparam>
    template<typename T>
    class Significand : public Integer<typename Internal::StorageType<T>::type>
    {
    public:
        using Base = Integer<typename Internal::StorageType<T>::type>;
        using FloatType = T;
        using StorageType = typename Internal::StorageType<T>::type;
        using Base::Base;

        static constexpr StorageType BitMask = FractionMask<FloatType, StorageType>;
        static constexpr Int32 BitWidth = static_cast< Int32 >( Internal::FractionWidth<FloatType>::value );

        static constexpr Significand Zero( )
        {
            return Significand( static_cast< StorageType >( 0 ) );
        }
        static constexpr Significand LSB( )
        {
            return Significand( static_cast< StorageType >( 1 ) );
        }
        static constexpr Significand MSB( )
        {
            return Significand( static_cast< StorageType >( 1 ) << ( BitWidth - 1 ) );
        }
        static constexpr Significand Mask( )
        {
            return Significand( BitMask );
        }

    };


    /// <summary>
    /// A template for encoding and decoding 
    /// floating point values.
    /// </summary>
    /// <typeparam name="T">
    /// Floating point type
    /// </typeparam>
    template<typename T>
    struct FloatingPoint
    {
        using value_type = std::remove_cvref_t<T>;
        using ValueType = value_type;

        using ExponentType = Internal::Exponent<ValueType>;
        using BiasedExponentType = Internal::BiasedExponent<ValueType>;
        using SignificandType = Internal::Significand<ValueType>;

        using StorageType = typename Internal::StorageType<value_type>::type;

        using UIntType = MakeUnsigned<ValueType>;
        using IntType = std::make_signed_t<UIntType>;

        static constexpr Int32 SignWidth = 1;
        static constexpr Int32 FractionWidth = static_cast< Int32 >( Internal::FractionWidth<ValueType>::value );
        static constexpr Int32 SignificandWidth = FractionWidth;
        static constexpr Int32 ExponentWidth = static_cast< Int32 >( Internal::ExponentWidth<ValueType>::value );
        static constexpr Int32 TotalWidth = SignWidth + ExponentWidth + FractionWidth;
        static constexpr Int32 StorageWidth = sizeof( StorageType ) * CHAR_BIT;

        static constexpr Int32 ExponentBias = ( 1 << ( ExponentWidth - 1 ) ) - 1;

        static constexpr Int32 MaxExponentValue = ( 1 << ExponentWidth ) - 1;

        static constexpr StorageType MaxExponent = static_cast< UIntType >( MaxExponentValue ) << FractionWidth;

        static constexpr StorageType FractionMask = FractionMask<ValueType, UIntType>;
        static constexpr StorageType SignificandMask = FractionMask;
        static constexpr StorageType ExponentMask = ExponentMask<ValueType, UIntType>;
        static constexpr StorageType ExponentFractionMask = FractionMask | ExponentMask;
        static constexpr StorageType SignMask = ~( FractionMask | ExponentMask );
        static constexpr StorageType ExponentSignMask = ExponentMask | SignMask;

        static constexpr StorageType InfinityValue = Internal::InfinityUnsignedValue<ValueType>::value;
        static constexpr StorageType NegativeInfinityValue = Internal::NegativeInfinityUnsignedValue<ValueType>::value;
        static constexpr StorageType QuietNaNValue = Internal::QuietNaNUnsignedValue<ValueType>::value;
        static constexpr StorageType ZeroValue = static_cast< UIntType >( 0 );
        static constexpr StorageType NegativeZeroValue = SignMask;

        StorageType value_;

        constexpr FloatingPoint( ) noexcept
            : value_( std::bit_cast< StorageType >( static_cast< ValueType >( 0.0 ) ) )
        {
        }

        constexpr explicit FloatingPoint( ValueType value ) noexcept
            : value_( std::bit_cast< StorageType >( value ) )
        {
        }

        constexpr explicit FloatingPoint( StorageType value ) noexcept
            : value_( value )
        {
        }

        constexpr explicit FloatingPoint( StorageType fraction, Int32 exponent, bool sign ) noexcept
            : value_( ( fraction& FractionMask ) |
                ( ( static_cast< UIntType >( exponent ) << FractionWidth ) & ExponentMask ) |
                ( sign ? SignMask : 0 ) )
        {
        }

        /// Merges bits from 'first' and 'second' values according to 'mask'.
        /// Use 'first' bits when corresponding 'mask' bits are clear and 'second' bits when
        /// corresponding bits are set.
        static constexpr StorageType MaskedMerge( StorageType first, StorageType second, StorageType mask )
        {
            // https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
            return first ^ ( ( first ^ second ) & mask );
        }




        static constexpr StorageType Encode( BiasedExponent<value_type> exp )
        {
            return ( static_cast< StorageType >( exp.Value( ) ) << SignificandWidth ) & ExponentMask;
        }

        static constexpr StorageType Encode( Significand<value_type> value )
        {
            return static_cast< StorageType >( value.Value( ) ) & SignificandMask;
        }

        static constexpr StorageType Encode( BiasedExponent<value_type> exp, Significand<value_type> sig )
        {
            return Encode( exp ) | Encode( sig );
        }

        static constexpr StorageType Encode( Sign sign, BiasedExponent<value_type> exp, Significand<value_type> sig )
        {
            if ( sign.IsNegative( ) )
            {
                return SignMask | Encode( exp, sig );
            }
            return Encode( exp, sig );
        }

        static constexpr FloatingPoint CreateValue( Internal::Sign sign, StorageType biasedExp, StorageType mantissa )
        {
            return FloatingPoint( Encode( sign, BiasedExponentType( static_cast< uint32_t >( biasedExp ) ), SignificandType( mantissa ) ) );
        }

        // The function converts integer number and unbiased exponent to proper
        // float T type:
        //   Result = number * 2^(ep+1 - exponent_bias)
        // Be careful!
        //   1) "ep" is the raw exponent value.
        //   2) The function adds +1 to ep for seamless normalized to denormalized
        //      transition.
        //   3) The function does not check exponent high limit.
        //   4) "number" zero value is not processed correctly.
        //   5) Number is unsigned, so the result can be only positive.
        static constexpr FloatingPoint MakeValue( StorageType number, int ep )
        {
            FloatingPoint result( 0 );
            int lz = FractionWidth + 1 - ( StorageWidth - std::countl_zero( number ) );

            number <<= lz;
            ep -= lz;


            if ( ep >= 0 ) [[likely]]
            {
                // Implicit number bit will be removed by mask
                result.SetSignificand( number );
                result.setBiasedExponent( static_cast< StorageType >( ep + 1 ) );
            }
            else
            {
                result.SetSignificand( number >> -ep );
            }
            return result;
        }


        constexpr FloatingPoint& operator = ( ValueType value ) noexcept
        {
            value_ = std::bit_cast< UIntType >( value );
            return *this;
        }

        constexpr Internal::Sign Sign( ) const noexcept
        {
            return Internal::Sign( value_ & SignMask );
        }
        constexpr bool Signed( ) const noexcept
        {
            return value_ & SignMask;
        }
        constexpr void SetSign( bool value = true ) noexcept
        {
            if ( value )
            {
                value_ |= SignMask;
            }
            else
            {
                value_ &= ~SignMask;
            }
        }
        constexpr void SetSign( Internal::Sign sign ) noexcept
        {
            SetSign( sign.IsSigned( ) );
        }


        constexpr Int32 ExponentValue( ) const noexcept
        {
            return static_cast< Int32 >( ( value_ & ExponentMask ) >> FractionWidth ) - ExponentBias;
        }

        constexpr Internal::Exponent<value_type> Exponent( ) const noexcept
        {
            return Internal::Exponent( ExponentValue( ) );
        }

        constexpr void SetExponent( Int32 value ) noexcept
        {
            value_ = ( static_cast< StorageType >( std::bit_cast< UInt32 >( value ) ) << FractionWidth ) & ExponentMask;
        }
        constexpr void SetExponent( Internal::Exponent<value_type> value ) noexcept
        {
            value_ = ( static_cast< StorageType >( std::bit_cast< UInt32 >( value.Value( ) ) ) << FractionWidth ) & ExponentMask;
        }


        constexpr Internal::BiasedExponent<value_type> BiasedExponent( ) const
        {
            return BiasedExponent( static_cast< uint32_t >( ExponentValue( ) >> SignificandWidth ) );
        }
        constexpr void SetBiasedExponent( Internal::BiasedExponent<value_type> biased )
        {
            value_ = MaskedMerge( value_, Encode( biased ), ExponentMask );
        }


        constexpr StorageType FractionValue( ) const noexcept
        {
            return value_ & FractionMask;
        }
        constexpr StorageType SignificandValue( ) const noexcept
        {
            return value_ & FractionMask;
        }
        constexpr StorageType MantissaValue( ) const noexcept
        {
            return value_ & FractionMask;
        }
        constexpr Internal::Significand<value_type> Fraction( ) const noexcept
        {
            return Internal::Significand<value_type>( value_ & FractionMask );
        }
        constexpr Internal::Significand<value_type> Significand( ) const noexcept
        {
            return Internal::Significand<value_type>( value_ & FractionMask );
        }
        constexpr Internal::Significand<value_type> Mantissa( ) const noexcept
        {
            return Internal::Significand<value_type>( value_ & FractionMask );
        }


        constexpr void SetFraction( StorageType value ) noexcept
        {
            value_ = value & FractionMask;
        }
        constexpr void SetFraction( Internal::Significand<value_type> value ) noexcept
        {
            value_ = value.value( ) & FractionMask;
        }
        constexpr void SetSignificand( StorageType value ) noexcept
        {
            value_ = value & FractionMask;
        }
        constexpr void SetSignificand( Internal::Significand<value_type> value ) noexcept
        {
            value_ = value.value( ) & FractionMask;
        }
        constexpr void SetMantissa( StorageType value ) noexcept
        {
            value_ = value & FractionMask;
        }
        constexpr void SetMantissa( Internal::Significand<value_type> value ) noexcept
        {
            value_ = value.value( ) & FractionMask;
        }


        constexpr StorageType ExponentFractionValue( ) const noexcept
        {
            return value_ & ExponentFractionMask;
        }
        constexpr StorageType ExponentSignificandValue( ) const noexcept
        {
            return value_ & ExponentFractionMask;
        }

        // returns true for +/- 0
        constexpr bool IsZero( ) const noexcept
        {
            return ( value_ & ( ExponentMask | FractionMask ) ) == 0;
        }

        // returns true for +/- NaN
        constexpr bool IsNaN( ) const noexcept
        {
            return ( ( value_ & ExponentMask ) == MaxExponent ) && ( ( value_ & FractionMask ) != 0 );
        }

        constexpr bool IsQuietNaN( ) const
        {
            return ExponentSignificandValue( ) >= Encode( ExponentType::Inf( ), SignificandType::MSB( ) );
        }

        constexpr bool IsSignalingNaN( ) const
        {
            return IsNaN( ) && IsQuietNaN( ) == false;
        }
        constexpr bool IsInf( ) const
        {
            return ExponentSignificandValue( ) == Encode( ExponentType::Inf( ), SignificandType::Zero( ) );
        }
        constexpr bool IsFinite( ) const
        {
            return ExponentValue( ) != Encode( ExponentType::Inf( ) );
        }
        constexpr bool IsSubNormal( ) const
        {
            return ExponentValue( ) == Encode( ExponentType::SubNormal( ) );
        }
        constexpr bool IsNormal( ) const
        {
            return IsFinite( ) && IsSubNormal( ) == false;
        }
        constexpr FloatingPoint NextTowardInf( ) const
        {
            if ( IsFinite( ) )
            {
                return FloatingPoint( value_ + static_cast< StorageType >( 1 ) );
            }
            return FloatingPoint( value_ );
        }

        // returns true for +/- NaN or +/- Inf
        constexpr bool IsInfOrNaN( ) const noexcept
        {
            return ( value_ & ExponentMask ) == MaxExponent;
        }

        constexpr ValueType AsFloatingPoint( ) const noexcept
        {
            return std::bit_cast< ValueType >( value_ );
        }

        constexpr UIntType AsUnsigned( ) const noexcept
        {
            return value_;
        }

        static constexpr FloatingPoint Zero( Internal::Sign sign = Internal::Sign::Positive ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::SubNormal( ), SignificandType::Zero( ) ) );
        }

        static constexpr FloatingPoint One( Internal::Sign sign = Internal::Sign::Positive ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::Zero( ), SignificandType::Zero( ) ) );
        }

        static constexpr FloatingPoint MinSubNormal( Internal::Sign sign = Internal::Sign::Positive ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::SubNormal( ), SignificandType::LSB( ) ) );
        }
        static constexpr FloatingPoint MaxSubNormal( Internal::Sign sign = Internal::Sign::Positive ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::SubNormal( ), SignificandType::Mask( ) ) );
        }
        static constexpr FloatingPoint MinNormal( Internal::Sign sign = Internal::Sign::Positive ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::Min( ), SignificandType::Zero( ) ) );
        }
        static constexpr FloatingPoint MaxNormal( Internal::Sign sign = Internal::Sign::Positive ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::Max( ), SignificandType::Mask( ) ) );
        }

        static constexpr FloatingPoint Inf( Internal::Sign sign = Internal::Sign::Positive ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::Inf( ), SignificandType::zero( ) ) );
        }
        static constexpr FloatingPoint SignalingNaN( Internal::Sign sign = Internal::Sign::Positive, StorageType v = 0 ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::Inf( ), ( v ? SignificandType( v ) : ( SignificandType::MSB( ) >> 1 ) ) ) );
        }
        static constexpr FloatingPoint QuietNaN( Internal::Sign sign = Internal::Sign::Positive, StorageType v = 0 ) noexcept
        {
            return FloatingPoint( Encode( sign, ExponentType::Inf( ), SignificandType::MSB( ) | SignificandType( v ) ) );
        }


        constexpr StorageType ExtractExplicitMantissa( ) const
        {
            if ( IsSubNormal( ) )
            {
                return SignificandValue( );
            }
            return ( StorageType( 1 ) << SignificandWidth ) | SignificandValue( );
        }

        // If the number is subnormal, the exponent is treated as if it were the
        // minimum exponent for a normal number. This is to keep continuity between
        // the normal and subnormal ranges, but it causes problems for functions where
        // values are calculated from the exponent, since just subtracting the bias
        // will give a slightly incorrect result. Additionally, zero has an exponent
        // of zero, and that should actually be treated as zero.
        constexpr int ExtractExplicitExponent( ) const
        {
            ExponentType exponent( BiasedExponent( ) );
            if ( IsZero( ) )
            {
                exponent = ExponentType::zero( );
            }
            if ( exponent == ExponentType::SubNormal( ) )
            {
                exponent = ExponentType::Min( );
            }
            return static_cast< Int32 >( exponent );
        }


        constexpr ValueType Abs( ) const noexcept
        {
            return std::bit_cast< ValueType >( value_ & ExponentFractionMask );
        }

        static constexpr ValueType Abs( ValueType value )
        {
            FloatingPoint fp( value );
            return fp.Abs( );
        }

        constexpr FloatingPoint Min( FloatingPoint other ) const noexcept
        {
            if ( IsNaN( ) )
            {
                return other;
            }
            if ( other.IsNaN( ) )
            {
                return FloatingPoint( value_ );
            }
            if ( Signed( ) != other.Signed( ) )
            {
                return Signed( ) ? FloatingPoint( value_ ) : other;
            }
            return std::bit_cast< value_type >( value_ ) < std::bit_cast< value_type >( other ) ? FloatingPoint( value_ ) : other;
        }
        constexpr ValueType Min( ValueType other ) const noexcept
        {
            FloatingPoint fp( other );
            std::bit_cast< ValueType >( Min( fp ) );
        }

        static constexpr ValueType Min( ValueType first, ValueType second ) noexcept
        {
            FloatingPoint fpFirst( first );
            FloatingPoint fpSecond( second );
            return fpFirst.Min( second );
        }

        constexpr FloatingPoint Max( FloatingPoint other ) const noexcept
        {
            if ( IsNaN( ) )
            {
                return other;
            }
            if ( other.IsNaN( ) )
            {
                return FloatingPoint( value_ );
            }
            if ( Signed( ) != other.Signed( ) )
            {
                return Signed( ) ? other : FloatingPoint( value_ );
            }
            return std::bit_cast< value_type >( value_ ) > std::bit_cast< value_type >( other ) ? FloatingPoint( value_ ) : other;
        }
        constexpr ValueType Max( ValueType other ) const noexcept
        {
            FloatingPoint fp( other );
            std::bit_cast< ValueType >( Max( fp ) );
        }

        static constexpr ValueType Max( ValueType first, ValueType second ) noexcept
        {
            FloatingPoint fpFirst( first );
            FloatingPoint fpSecond( second );
            return fpFirst.Max( second );
        }





        constexpr ValueType Trunc( ) const noexcept
        {
            if ( !IsInfOrNaN( ) ) [[likely]]
            {
                Int32 exponent = ExponentValue( );

                if ( exponent < FractionWidth )
                {
                    if ( exponent > -1 )
                    {
                        // abs(x) is greater or equal to 1
                        Int32 trimSize = FractionWidth - exponent;

                        UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );
                        return std::bit_cast< ValueType >( result );
                    }
                    else
                    {
                        // abs(x) is less than 1, then return 0.
                        return Signed( ) ? static_cast< ValueType >( -0.0 ) : static_cast< ValueType >( 0.0 );
                    }
                }
                else
                {
                    // already an integer
                    return std::bit_cast< ValueType >( value_ );
                }
            }
            else
            {
                // inf or NaN
                return std::bit_cast< ValueType >( value_ );
            }
        }

        static constexpr ValueType Trunc( ValueType value )
        {
            FloatingPoint<ValueType> fp( value );
            return fp.Trunc( );
        }

        constexpr ValueType Ceil( ) const noexcept
        {
            if ( IsInfOrNaN( ) || IsZero( ) )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            Int32 exponent = ExponentValue( );

            // is this already an integer?
            if ( exponent >= static_cast< Int32 >( FractionWidth ) )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            // If abs(x) is less than 1
            if ( exponent <= -1 )
            {
                return Signed( ) ? ValueType( -0.0 ) : ValueType( 1.0 );
            }

            Int32 trimSize = FractionWidth - exponent;
            UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );

            // If this is already an integer, return it.
            if ( result == value_ )
            {
                return std::bit_cast< ValueType >( value_ );
            }
            // If negative, the ceil operation is equivalent to the trunc operation.
            return Signed( ) ? std::bit_cast< ValueType >( result ) : std::bit_cast< ValueType >( result ) + static_cast< ValueType >( 1.0 );
        }

        static constexpr ValueType Ceil( ValueType value )
        {
            FloatingPoint<ValueType> fp( value );
            return fp.Ceil( );
        }

        constexpr ValueType Floor( ) const noexcept
        {
            if ( Signed( ) )
            {
                FloatingPoint tmp( value_ & ( ExponentMask | FractionMask ) );
                return -tmp.Ceil( );
            }
            else
            {
                return Trunc( );
            }
        }

        static constexpr ValueType Floor( ValueType value )
        {
            FloatingPoint<ValueType> fp( value );
            return fp.Floor( );
        }

        constexpr ValueType Round( ) const noexcept
        {
            // If infinity NaN or zero, return it.
            if ( IsInfOrNaN( ) || IsZero( ) )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            int exponent = ExponentValue( );

            // If the exponent is greater than the most negative 
            // exponent, then this is already an integer.
            if ( exponent >= FractionWidth )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            if ( exponent == -1 )
            {
                bool isNegative = Signed( );
                // Absolute value is greater than equal to 0.5 but less than 1.
                if ( isNegative )
                {
                    return static_cast< ValueType >( -1.0 );
                }
                else
                {
                    return static_cast< ValueType >( 1.0 );
                }
            }

            if ( exponent <= -2 )
            {
                bool isNegative = Signed( );
                // Absolute value is less than 0.5.
                if ( isNegative )
                {
                    return static_cast< ValueType >( -0.0 );
                }
                else
                {
                    return static_cast< ValueType >( 0.0 );
                }
            }

            UInt32 trimSize = FractionWidth - exponent;

            bool middleBitSet = ( value_ & FractionMask ) & ( UIntType( 1 ) << ( trimSize - 1 ) );

            UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );

            // If this is already an integer, return it.
            if ( result == value_ )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            if ( !middleBitSet )
            {
                // Franctional part is less than 0.5 so round value is the
                // same as the trunc value.
                return std::bit_cast< ValueType >( result );
            }
            else
            {
                bool isNegative = Signed( );
                return isNegative ?
                    std::bit_cast< ValueType >( result ) - static_cast< ValueType >( 1.0 ) :
                    std::bit_cast< ValueType >( result ) + static_cast< ValueType >( 1.0 );
            }
        }

        static constexpr ValueType Round( ValueType value )
        {
            FloatingPoint<ValueType> fp( value );
            return fp.Round( );
        }

        constexpr ValueType ModF( ValueType& intPart ) noexcept
        {
            if ( IsInfOrNaN( ) == false )
            {
                Int32 exponent = ExponentValue( );

                if ( exponent < static_cast< Int32 >( FractionWidth ) )
                {
                    if ( exponent > -1 )
                    {
                        // abs(x) is greater or equal to 1
                        Int32 trimSize = FractionWidth - exponent;
                        UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );
                        intPart = std::bit_cast< ValueType >( result );
                        return std::bit_cast< ValueType >( value_ ) - intPart;
                    }
                    else
                    {
                        // abs(x) is less than 1, then return 0.
                        intPart = Signed( ) ? std::bit_cast< ValueType >( NegativeZeroValue ) : std::bit_cast< ValueType >( ZeroValue );

                        return std::bit_cast< ValueType >( value_ );
                    }
                }
                else
                {
                    // already an integer
                    intPart = std::bit_cast< ValueType >( value_ );
                    return Signed( ) ? std::bit_cast< ValueType >( NegativeZeroValue ) : std::bit_cast< ValueType >( ZeroValue );
                }
            }
            else
            {
                intPart = std::bit_cast< ValueType >( value_ );
                if ( IsInf( ) )
                {
                    return Signed( ) ? std::bit_cast< ValueType >( NegativeZeroValue ) : std::bit_cast< ValueType >( ZeroValue );
                }
                else
                {
                    return intPart;
                }
            }
        }


        constexpr static ValueType ModF( ValueType value, ValueType& intPart ) noexcept
        {
            FloatingPoint fp( value );
            return fp.ModF( intPart );
        }
    };

    static_assert( sizeof( FloatingPoint<float> ) == sizeof( float ) );
    static_assert( sizeof( FloatingPoint<double> ) == sizeof( double ) );


    // Stores the normalized form of a floating point value.
    // It does not handle the bits patterns for Zero, infinity and NaNs.
    template <typename T>
    class NormalizedFloat
    {
    public:
        using ValueType = std::remove_cvref_t<T>;
        using FloatingPoint = FloatingPoint<ValueType>;
        using UIntType = typename FloatingPoint::UIntType;

        static constexpr UIntType ExponentMask = FloatingPoint::ExponentMask;
        static constexpr Int32 ExponentWidth = FloatingPoint::ExponentWidth;
        static constexpr Int32 ExponentBias = FloatingPoint::ExponentBias;
        static constexpr Int32 FractionWidth = FloatingPoint::FractionWidth;
        static constexpr UIntType FractionMask = FloatingPoint::FractionMask;
        static constexpr UIntType SignMask = FloatingPoint::SignMask;

        // Max exponent has the form 0xFF...E. So here we must use -2 and not -1.
        static constexpr int MaxExponentValue = ( 1 << ExponentWidth ) - 2;
        static constexpr UIntType One = ( UIntType( 1 ) << FractionWidth );
    private:
        // Unbiased exponent value.
        Int32 exponent_;
        UIntType fraction_;
        bool sign_;


        constexpr unsigned NormalizationShift( UIntType fraction ) noexcept
        {
            unsigned shift = 0;
            while ( ( One & fraction ) == 0 && ( shift < FractionWidth ) )
            {
                fraction <<= 1;
                shift++;
            }
            return shift;
        }
    public:

        constexpr NormalizedFloat( Int32 exponent, UIntType fraction, bool sign ) noexcept
            : exponent_( exponent ), fraction_( fraction ), sign_( sign )
        {
            if ( fraction_ < One )
            {
                auto normalizationShift = NormalizationShift( fraction_ );
                fraction_ <<= normalizationShift;
                exponent_ -= normalizationShift;
            }
        }

        constexpr explicit NormalizedFloat( FloatingPoint floatingPoint ) noexcept
            : exponent_( 0 ), fraction_( 0 ), sign_( floatingPoint.Signed( ) )
        {
            if ( floatingPoint.IsInfOrNaN( ) == false && floatingPoint.IsZero( ) == false )
            {
                if ( ( floatingPoint.value_ & ExponentMask ) == 0 )
                {
                    // Normalize subnormal numbers.
                    fraction_ = floatingPoint.FractionValue( );
                    auto normalizationShift = NormalizationShift( fraction_ );
                    fraction_ <<= normalizationShift;
                    exponent_ = 1 - ExponentBias - normalizationShift;
                }
                else
                {
                    exponent_ = floatingPoint.ExponentValue( );
                    fraction_ = floatingPoint.FractionValue( );
                }
            }
        }

        constexpr explicit NormalizedFloat( ValueType val ) noexcept
            : NormalizedFloat( FloatingPoint( val ) )
        {
        }

        constexpr void Assign( Int32 exponent, UIntType fraction, bool sign )
        {
            exponent_ = exponent;
            fraction_ = fraction;
            sign_ = sign;
            if ( fraction_ < One )
            {
                auto normalizationShift = NormalizationShift( fraction_ );
                fraction_ <<= normalizationShift;
                exponent_ -= normalizationShift;
            }
        }


        constexpr Int32 Exponent( ) const noexcept
        {
            return exponent_;
        }
        constexpr void SetExponent( Int32 exponent ) noexcept
        {
            exponent_ = exponent;
        }

        constexpr UIntType Fraction( ) const noexcept
        {
            return fraction_;
        }

        constexpr bool Sign( ) const noexcept
        {
            return sign_;
        }


        constexpr int Compare( const NormalizedFloat& other ) const noexcept
        {
            if ( ( sign_ != other.sign_ ) || ( exponent_ > other.exponent_ ) )
            {
                return sign_ ? -1 : 1;
            }
            else if ( exponent_ == other.exponent_ )
            {
                if ( fraction_ > other.fraction_ )
                {
                    return sign_ ? -1 : 1;
                }
                else if ( fraction_ == other.fraction_ )
                {
                    return 0;
                }
                else
                {
                    return sign_ ? 1 : -1;
                }
            }
            else
            {
                return sign_ ? 1 : -1;
            }
        }

        // Returns a new normalized floating point number which is equal in value
        // to this number multiplied by 2^e. That is:
        //     new = this *  2^e
        constexpr NormalizedFloat Mul2( int exp ) const noexcept
        {
            NormalizedFloat result = *this;
            result.exponent_ += exp;
            return result;
        }

        constexpr ValueType AsFloatingPoint( ) const noexcept
        {
            int biasedExponent = exponent_ + ExponentBias;

            if ( biasedExponent > MaxExponentValue )
            {
                return sign_ ? std::bit_cast< ValueType >( FloatingPoint::NegativeInfinityValue ) : std::bit_cast< ValueType >( FloatingPoint::InfinityValue );
            }

            constexpr int subnormalExponent = ExponentBias + 1;
            if ( exponent_ < subnormalExponent )
            {
                unsigned shift = subnormalExponent - exponent_;
                // Since exponent > subnormalExponent, shift will allways be greater than zero.
                if ( shift <= FractionWidth + 1 )
                {
                    // Generate a subnormal number. Rounding to nearest and round halfway cases to even.
                    const UIntType shiftOutMask = ( UIntType( 1 ) << shift ) - 1;
                    const UIntType shiftOutValue = fraction_ & shiftOutMask;
                    const UIntType halfwayValue = UIntType( 1 ) << ( shift - 1 );
                    Int32 exponent = 0;
                    UIntType fraction = fraction_ >> shift;
                    if ( shiftOutValue > halfwayValue )
                    {
                        fraction += 1;
                    }
                    else if ( shiftOutValue == halfwayValue )
                    {
                        // Round to even.
                        if ( fraction & 0x1 )
                        {
                            fraction += 1;
                        }
                    }

                    // Adding 1 to fraction can lead to overflow. This will only happen when
                    // fraction_ is all ones (0b111..11). For this case, the overflow is carried into the exponent.
                    if ( fraction == One )
                    {
                        exponent = 1;
                    }
                    FloatingPoint result( fraction, exponent, Sign( ) );
                    return result.AsFloatingPoint( );
                }
            }

            FloatingPoint result( fraction_, exponent_ - 1 + ExponentBias, Sign( ) );
            return result.AsFloatingPoint( );
        }

    };

}

#endif
