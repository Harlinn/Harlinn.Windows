#pragma once
#ifndef HCCFLOATINGPOINT_H_
#define HCCFLOATINGPOINT_H_
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
    template <typename T>
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


    template <typename T>
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

    template <typename T>
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

    template <typename T>
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

    template <typename T>
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
    template <typename T>
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


    template<typename T>
    struct FloatingPoint
    {
        using ValueType = std::remove_cvref_t<T>;
        using UIntType = MakeUnsigned<ValueType>;
        using IntType = std::make_signed_t<UIntType>;

        static constexpr Int32 FractionWidth = static_cast< Int32 >( FractionWidth<ValueType>::value );
        static constexpr Int32 ExponentWidth = static_cast< Int32 >( ExponentWidth<ValueType>::value );

        static constexpr Int32 ExponentBias = ( 1 << ( ExponentWidth - 1 ) ) - 1;

        static constexpr Int32 MaxExponentValue = ( 1 << ExponentWidth ) - 1;

        static constexpr UIntType MaxExponent = static_cast< UIntType >( MaxExponentValue ) << FractionWidth;

        static constexpr UIntType MinSubnormal = UIntType( 1 );
        static constexpr UIntType MaxSubnormal = ( UIntType( 1 ) << FractionWidth ) - 1;
        static constexpr UIntType MinNormal = ( UIntType( 1 ) << FractionWidth );
        static constexpr UIntType MaxNormal = ( ( UIntType( MaxExponentValue ) - 1 ) << FractionWidth ) | MaxSubnormal;

        static constexpr UIntType FractionMask = FractionMask<ValueType, UIntType>;
        static constexpr UIntType ExponentMask = ExponentMask<ValueType, UIntType>;
        static constexpr UIntType SignMask = ~( FractionMask | ExponentMask );

        static constexpr UIntType InfinityValue = InfinityUnsignedValue<ValueType>::value;
        static constexpr UIntType NegativeInfinityValue = NegativeInfinityUnsignedValue<ValueType>::value;
        static constexpr UIntType QuietNaNValue = QuietNaNUnsignedValue<ValueType>::value;
        static constexpr UIntType ZeroValue = static_cast< UIntType >( 0 );
        static constexpr UIntType NegativeZeroValue = SignMask;

        UIntType value_;

        constexpr FloatingPoint( ) noexcept
            : value_( std::bit_cast< UIntType >( static_cast< ValueType >( 0.0 ) ) )
        {
        }

        constexpr explicit FloatingPoint( ValueType value ) noexcept
            : value_( std::bit_cast< UIntType >( value ) )
        {
        }

        constexpr explicit FloatingPoint( UIntType value, bool ) noexcept
            : value_( value )
        {
        }

        constexpr explicit FloatingPoint( UIntType fraction, Int32 exponent, bool sign ) noexcept
            : value_( ( fraction& FractionMask ) |
                ( ( static_cast< UIntType >( exponent ) << FractionWidth ) & ExponentMask ) |
                ( sign ? SignMask : 0 ) )
        {
        }


        constexpr FloatingPoint& operator = ( ValueType value ) noexcept
        {
            value_ = std::bit_cast< UIntType >( value );
            return *this;
        }

        constexpr bool Sign( ) const noexcept
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

        constexpr Int32 Exponent( ) const noexcept
        {
            return static_cast< Int32 >( ( value_ & ExponentMask ) >> FractionWidth ) - ExponentBias;
        }
    private:
        constexpr void SetExponent( UIntType value ) noexcept
        {
            value_ = ( value << FractionWidth ) & ExponentMask;
        }
    public:
        constexpr UIntType Fraction( ) const noexcept
        {
            return value_ & FractionMask;
        }
    private:
        constexpr void SetFraction( UIntType value ) noexcept
        {
            value_ = value & FractionMask;
        }
    public:

        // returns true for +/- 0
        constexpr bool IsZero( ) const noexcept
        {
            return ( value_ & ( ExponentMask | FractionMask ) ) == 0;
        }

        // returns true for +/- Inf
        constexpr bool IsInf( ) const noexcept
        {
            return ( value_ & FractionMask ) == 0 && ( ( value_ & ExponentMask ) == MaxExponent );
        }

        // returns true for +/- NaN
        constexpr bool IsNaN( ) const noexcept
        {
            return ( ( value_ & ExponentMask ) == MaxExponent ) && ( ( value_ & FractionMask ) != 0 );
        }

        // returns true for +/- NaN or +/- Inf
        constexpr bool IsInfOrNaN( ) const noexcept
        {
            return ( value_ & ExponentMask ) == MaxExponent;
        }

        static constexpr ValueType MakeNaN( UIntType value ) noexcept
        {
            UIntType result;
            result = MaxExponent | ( value & FractionMask );
            return std::bit_cast< ValueType >( result );
        }

        constexpr ValueType AsFloatingPoint( ) const noexcept
        {
            return std::bit_cast< ValueType >( value_ );
        }

        constexpr UIntType AsUnsigned( ) const noexcept
        {
            return value_;
        }

        static constexpr FloatingPoint Zero( ) noexcept
        {
            return FloatingPoint( );
        }

        static constexpr FloatingPoint NegZero( ) noexcept
        {
            FloatingPoint result;
            result.value_ = SignMask;
            return result;
        }

        static constexpr FloatingPoint Inf( ) noexcept
        {
            FloatingPoint result;
            result.value_ = MaxExponent;
            return result;
        }

        static constexpr FloatingPoint NegInf( ) noexcept
        {
            FloatingPoint result;
            result.value_ = MaxExponent | SignMask;
            return result;
        }

        constexpr ValueType Trunc( ) const noexcept
        {
            if ( !IsInfOrNaN( ) )
            {
                Int32 exponent = Exponent( );

                if ( exponent < static_cast< Int32 >( FractionWidth ) )
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
                        return Sign( ) ? static_cast< ValueType >( -0.0 ) : static_cast< ValueType >( 0.0 );
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

    private:
        constexpr ValueType FastTrunc( ) const noexcept
        {
            Int32 exponent = Exponent( );

            if ( exponent < static_cast< Int32 >( FractionWidth ) )
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
                    return Sign( ) ? static_cast< ValueType >( -0.0 ) : static_cast< ValueType >( 0.0 );
                }
            }
            else
            {
                // already an integer
                return std::bit_cast< ValueType >( value_ );
            }
        }
    public:
        constexpr ValueType ModF( ValueType& intPart ) noexcept
        {
            if ( IsInfOrNaN( ) == false )
            {
                Int32 exponent = Exponent( );

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
                        intPart = Sign( ) ? std::bit_cast< ValueType >( NegativeZeroValue ) : std::bit_cast< ValueType >( ZeroValue );

                        return std::bit_cast< ValueType >( value_ );
                    }
                }
                else
                {
                    // already an integer
                    intPart = std::bit_cast< ValueType >( value_ );
                    return Sign( ) ? std::bit_cast< ValueType >( NegativeZeroValue ) : std::bit_cast< ValueType >( ZeroValue );
                }
            }
            else
            {
                intPart = std::bit_cast< ValueType >( value_ );
                if ( IsInf( ) )
                {
                    return Sign( ) ? std::bit_cast< ValueType >( NegativeZeroValue ) : std::bit_cast< ValueType >( ZeroValue );
                }
                else
                {
                    return intPart;
                }
            }
        }




        constexpr ValueType Ceil( ) const noexcept
        {
            if ( IsInfOrNaN( ) || IsZero( ) )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            Int32 exponent = Exponent( );

            // is this already an integer?
            if ( exponent >= static_cast< Int32 >( FractionWidth ) )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            // If abs(x) is less than 1
            if ( exponent <= -1 )
            {
                return Sign( ) ? ValueType( -0.0 ) : ValueType( 1.0 );
            }

            Int32 trimSize = FractionWidth - exponent;
            UIntType result = ( value_ & ( SignMask | ExponentMask ) ) | ( ( ( value_ & FractionMask ) >> trimSize ) << trimSize );

            // If this is already an integer, return it.
            if ( result == value_ )
            {
                return std::bit_cast< ValueType >( value_ );
            }
            // If negative, the ceil operation is equivalent to the trunc operation.
            return Sign( ) ? std::bit_cast< ValueType >( result ) : std::bit_cast< ValueType >( result ) + static_cast< ValueType >( 1.0 );
        }

        constexpr ValueType Floor( ) const noexcept
        {
            if ( Sign( ) )
            {
                FloatingPoint tmp( value_ & ( ExponentMask | FractionMask ), true );
                return -tmp.Ceil( );
            }
            else
            {
                return Trunc( );
            }
        }


        constexpr ValueType Round( ) const noexcept
        {
            // If infinity NaN or zero, return it.
            if ( IsInfOrNaN( ) || IsZero( ) )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            int exponent = Exponent( );

            // If the exponent is greater than the most negative 
            // exponent, then this is already an integer.
            if ( exponent >= static_cast< int >( FractionWidth ) )
            {
                return std::bit_cast< ValueType >( value_ );
            }

            if ( exponent == -1 )
            {
                bool isNegative = Sign( );
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
                bool isNegative = Sign( );
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
                bool isNegative = Sign( );
                return isNegative ?
                    std::bit_cast< ValueType >( result ) - static_cast< ValueType >( 1.0 ) :
                    std::bit_cast< ValueType >( result ) + static_cast< ValueType >( 1.0 );
            }
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
            : exponent_( 0 ), fraction_( 0 ), sign_( floatingPoint.Sign( ) )
        {
            if ( floatingPoint.IsInfOrNaN( ) == false && floatingPoint.IsZero( ) == false )
            {
                if ( ( floatingPoint.value_ & ExponentMask ) == 0 )
                {
                    // Normalize subnormal numbers.
                    fraction_ = floatingPoint.Fraction( );
                    auto normalizationShift = NormalizationShift( fraction_ );
                    fraction_ <<= normalizationShift;
                    exponent_ = 1 - ExponentBias - normalizationShift;
                }
                else
                {
                    exponent_ = floatingPoint.Exponent( );
                    fraction_ = floatingPoint.Fraction( );
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
