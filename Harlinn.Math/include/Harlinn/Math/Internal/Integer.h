#pragma once
#ifndef HARLINN_MATH_INTERNAL_INTEGER_H_
#define HARLINN_MATH_INTERNAL_INTEGER_H_

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

#include <type_traits>

namespace Harlinn::Math::Internal
{
    /// <summary>
    /// Represents the sign of a signed arithmetic type
    /// </summary>
    class Sign
    {
        bool isSigned_;
    public:
        constexpr explicit Sign( bool isNegative )
            : isSigned_( isNegative )
        {
        }

        constexpr bool IsSigned( ) const { return isSigned_; }
        constexpr bool IsPositive( ) const { return isSigned_ == false; }
        constexpr bool IsNegative( ) const { return isSigned_; }

        friend constexpr bool operator==( Sign first, Sign second )
        {
            return first.isSigned_ == second.isSigned_;
        }

        friend constexpr bool operator!=( Sign first, Sign second )
        {
            return first.isSigned_ != second.isSigned_;
        }

        static const Sign Negative;
        static const Sign Positive;

    };

    inline constexpr Sign Sign::Negative = Sign( true );
    inline constexpr Sign Sign::Positive = Sign( false );

    /// <summary>
    /// A typed wrapper for integral types.
    /// </summary>
    /// <typeparam name="T">
    /// An integral type.
    /// </typeparam>
    template<typename T>
        requires std::is_integral_v<T>
    class Integer
    {
    public:
        using value_type = T;
    protected:
        value_type value_ = 0;
    public:
        constexpr Integer( ) noexcept = default;
        constexpr explicit Integer( value_type value ) noexcept
            : value_( value )
        {
        }

        constexpr Integer( const Integer& value ) noexcept = default;

        constexpr Integer& operator = ( value_type value ) noexcept
        {
            value_ = value;
            return *this;
        }

        static constexpr bool IsSigned = std::is_signed_v<value_type>;
        static constexpr bool IsUnsigned = std::is_unsigned_v<value_type>;

        constexpr Integer& operator=( const Integer& value ) noexcept = default;

        constexpr explicit operator value_type( ) const noexcept
        {
            return value_;
        }

        constexpr value_type Value( ) const noexcept
        {
            return value_;
        }

        constexpr void Assign( value_type value )
        {
            value_ = value;
        }


        constexpr auto operator<=>( const Integer& other ) const noexcept = default;

        constexpr Integer& operator++( ) noexcept
        {
            ++value_;
            return *this;
        }

        constexpr Integer operator++( int ) noexcept
        {
            Integer result = *this;
            ++value_;
            return result;
        }

        constexpr Integer& operator--( ) noexcept
        {
            --value_;
            return *this;
        }

        constexpr Integer operator--( int ) noexcept
        {
            Integer result = *this;
            --value_;
            return result;
        }


        constexpr Integer operator - ( ) noexcept
        {
            return Integer( -value_ );
        }

        constexpr Integer& operator += ( const Integer& other ) noexcept
        {
            value_ += other.value_;
            return *this;
        }

        constexpr Integer& operator -= ( const Integer& other ) noexcept
        {
            value_ -= other.value_;
            return *this;
        }

        constexpr Integer& operator *= ( const Integer& other ) noexcept
        {
            value_ *= other.value_;
            return *this;
        }

        constexpr Integer& operator /= ( const Integer& other )
        {
            value_ /= other.value_;
            return *this;
        }

        constexpr Integer& operator &= ( const Integer& other )
        {
            value_ &= other.value_;
            return *this;
        }

        constexpr Integer& operator |= ( const Integer& other )
        {
            value_ |= other.value_;
            return *this;
        }

        constexpr Integer& operator ^= ( const Integer& other )
        {
            value_ ^= other.value_;
            return *this;
        }

        constexpr Integer& operator >>= ( int shift )
        {
            value_ >>= shift;
            return *this;
        }

        constexpr Integer& operator <<= ( int shift )
        {
            value_ <<= shift;
            return *this;
        }



        friend constexpr Integer operator+( const Integer& first, const Integer& second ) noexcept
        {
            return Integer( first.value_ + second.value_ );
        }

        friend constexpr Integer operator-( const Integer& first, const Integer& second ) noexcept
        {
            return Integer( first.value_ - second.value_ );
        }

        friend constexpr Integer operator*( const Integer& first, const Integer& second ) noexcept
        {
            return Integer( first.value_ * second.value_ );
        }

        friend constexpr Integer operator/( const Integer& first, const Integer& second )
        {
            return Integer( first.value_ / second.value_ );
        }

        friend constexpr Integer operator&( const Integer& first, const Integer& second )
        {
            return Integer( first.value_ & second.value_ );
        }

        friend constexpr Integer operator|( const Integer& first, const Integer& second )
        {
            return Integer( first.value_ | second.value_ );
        }
        friend constexpr Integer operator^( const Integer& first, const Integer& second )
        {
            return Integer( first.value_ ^ second.value_ );
        }

        friend constexpr Integer operator>>( const Integer& value, int shift )
        {
            return Integer( value.value_ >> shift );
        }

        friend constexpr Integer operator<<( const Integer& value, int shift )
        {
            return Integer( value.value_ << shift );
        }


    };
}

#endif
