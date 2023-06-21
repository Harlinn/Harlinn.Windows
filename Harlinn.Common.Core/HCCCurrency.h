#pragma once
#ifndef __HCCCURRENCY_H__
#define __HCCCURRENCY_H__

#include <HCCLib.h>

namespace Harlinn::Common::Core
{
    /// <summary>
    /// Currency are stored as 64-bit integer, scaled by 10,000 to 
    /// give a fixed-point number with 15 digits to the left of the 
    /// decimal point and 4 digits to the right.
    /// 
    /// This representation provides a range of 
    /// -922,337,203,685,477.5808 to 922,337,203,685,477.5807.
    /// 
    /// The Currency type is useful for calculations involving money and 
    /// for fixed-point calculations in which accuracy is important.
    /// </summary>
    class Currency
    {
    public:
        using value_type = Int64;
        static constexpr value_type Scale = 10000;
    private:
        value_type value_;

        constexpr explicit Currency( value_type value, bool ) noexcept
            : value_( value )
        {
        }
    public:
        constexpr Currency( ) noexcept
            : value_( 0 )
        {
        }

        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        constexpr Currency( T value ) noexcept
            : value_( value * Scale )
        {
        }
        constexpr explicit Currency( CY value ) noexcept
            : value_( value.int64 )
        {
        }

        constexpr value_type Value( ) const noexcept
        {
            return value_;
        }

        constexpr Currency& operator++( ) noexcept
        {
            value_ += Scale;
            return *this;
        }

        constexpr Currency operator++( int ) noexcept
        {
            Currency result( value_, false );
            value_ += Scale;
            return result;
        }

        constexpr Currency& operator--( ) noexcept
        {
            value_ -= Scale;
            return *this;
        }

        constexpr Currency operator--( int ) noexcept
        {
            Currency result( value_, false );
            value_ -= Scale;
            return result;
        }

        constexpr Currency& operator = ( const CY value ) noexcept
        {
            value_ = value.int64;
            return *this;
        }

        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        constexpr Currency& operator = ( const T value ) noexcept
        {
            value_ = static_cast<value_type>( value * Scale );
            return *this;
        }

        template<typename T>
            requires (std::is_arithmetic_v<T> && std::is_nothrow_convertible_v<T, value_type>)
        constexpr Currency& operator += ( const T value ) noexcept
        {
            value_ = static_cast<value_type>( value_ + (value * Scale) );
            return *this;
        }
        constexpr Currency& operator += ( const Currency& other ) noexcept
        {
            value_ += other.value_;
            return *this;
        }
        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        constexpr Currency operator + ( const T value ) const noexcept
        {
            return Currency( static_cast<value_type>( value_ + (value * Scale) ), false);
        }
        constexpr Currency operator + ( const Currency& other ) const noexcept
        {
            return Currency( value_ + other.value_, false );
        }
        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        friend constexpr Currency operator + ( const T first, const Currency& second ) noexcept
        {
            return Currency( static_cast<value_type>( (first * Scale) + second.value_ ) , false);
        }

        template<typename T>
            requires (std::is_arithmetic_v<T> && std::is_nothrow_convertible_v<T, value_type>)
        constexpr Currency& operator -= ( const T value ) noexcept
        {
            value_ = static_cast<value_type>( value_ - (value * Scale) );
            return *this;
        }
        constexpr Currency& operator -= ( const Currency& other ) noexcept
        {
            value_ -= other.value_;
            return *this;
        }
        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        constexpr Currency operator - ( const T value ) const noexcept
        {
            return Currency( static_cast<value_type>( value_ - (value * Scale) ), false);
        }
        constexpr Currency operator - ( const Currency& other ) const noexcept
        {
            return Currency( value_ - other.value_, false );
        }
        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        friend constexpr Currency operator - ( const T first, const Currency& second ) noexcept
        {
            return Currency( static_cast<value_type>( (first * Scale) - second.value_ ) , false);
        }

        template<typename T>
            requires (std::is_arithmetic_v<T> && std::is_nothrow_convertible_v<T, value_type>)
        constexpr Currency& operator *= ( const T value ) noexcept
        {
            value_ = static_cast<value_type>( value_ * value );
            return *this;
        }
        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        constexpr Currency operator * ( const T value ) const noexcept
        {
            return Currency( static_cast<value_type>( value_ * value ), false);
        }
        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        friend constexpr Currency operator * ( const T first, const Currency& second ) noexcept
        {
            return Currency( static_cast<value_type>( first * second.value_ ) , false);
        }

        template<typename T>
            requires (std::is_arithmetic_v<T> && std::is_nothrow_convertible_v<T, value_type>)
        constexpr Currency& operator /= ( const T value ) noexcept
        {
            value_ = static_cast<value_type>( value_ / value );
            return *this;
        }
        template<typename T>
            requires ( std::is_arithmetic_v<T>&& std::is_nothrow_convertible_v<T, value_type> )
        constexpr Currency operator / ( const T value ) const noexcept
        {
            return Currency( static_cast<value_type>( value_ / value ), false);
        }


        explicit constexpr operator bool( ) const noexcept
        {
            return value_ != 0;
        }

        constexpr bool operator == ( const Currency& other ) const noexcept
        {
            return value_ == other.value_;
        }
        constexpr bool operator != ( const Currency& other ) const noexcept
        {
            return value_ != other.value_;
        }
        constexpr bool operator <  ( const Currency& other ) const noexcept
        {
            return value_ < other.value_;
        }
        constexpr bool operator <= ( const Currency& other ) const noexcept
        {
            return value_ <= other.value_;
        }
        constexpr bool operator >  ( const Currency& other ) const noexcept
        {
            return value_ > other.value_;
        }
        constexpr bool operator >= ( const Currency& other ) const noexcept
        {
            return value_ >= other.value_;
        }

        constexpr int CompareTo( const Currency& other ) const noexcept
        {
            if ( value_ > other.value_ )
            {
                return 1;
            }
            if ( value_ < other.value_ )
            {
                return -1;
            }
            return 0;
        }


        friend std::ostream& operator << ( std::ostream& stream, const Currency& currency )
        {
            stream << currency.Value();
            return stream;
        }

        template<typename T>
        constexpr T As( ) const noexcept
        {
            return static_cast<T>( value_ / Scale );
        }

        template<>
        constexpr CY As<CY>( ) const noexcept
        {
            return CY{ .int64 = value_ };
        }


        HCC_EXPORT WideString ToWideString( ) const;
        HCC_EXPORT std::string ToAnsiString( ) const;

        template<>
        HCC_EXPORT WideString As<WideString>( ) const;
        template<>
        HCC_EXPORT std::string As<std::string>( ) const;

        HCC_EXPORT static bool TryParse( const wchar_t* text, Currency& result );
        HCC_EXPORT static bool TryParse( const char* text, Currency& result );
        HCC_EXPORT static Currency Parse( const wchar_t* text );
        HCC_EXPORT static Currency Parse( const char* text );
    };

    template<typename T>
    inline constexpr bool IsCurrency = std::is_same_v<std::remove_cv_t<T>, Currency>;

    template<typename T>
        requires IsCurrency<T>
    inline constexpr T ByteSwap( const T value ) noexcept
    {
        return std::bit_cast<Currency>( ByteSwap( std::bit_cast<UInt64>( value ) ) );
    }

}

#endif
