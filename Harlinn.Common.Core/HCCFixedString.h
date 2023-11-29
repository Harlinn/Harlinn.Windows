#pragma once
#ifndef HCCFIXEDSTRING_H_
#define HCCFIXEDSTRING_H_

#include <HCCLib.h>

namespace Harlinn::Common::Core
{
#pragma pack(push,1)
    template <typename SizeT, typename CharT, size_t maxSize, bool zeroTerminated >
    class BasicFixedString
    {
    public:
        using SizeType = SizeT;
        using CharType = CharT;
        static constexpr size_t MaxSize = maxSize;
        static constexpr bool ZeroTerminated = zeroTerminated;
        static constexpr size_t ArraySize = maxSize + ( ZeroTerminated ? 1 : 0 );
        using ArrayType = std::array<CharType, ArraySize>;
        using ViewType = std::basic_string_view<CharType>;
        using SpanType = std::span<CharType>;

        using iterator = typename ArrayType::iterator;
        using const_iterator = typename ArrayType::const_iterator;
    private:
        SizeType size_;
        ArrayType data_;
    public:
        constexpr BasicFixedString( ) noexcept
            : size_( 0 ), data_{}
        {
        }

        constexpr BasicFixedString( const CharType* str, size_t strLength )
            : size_( static_cast< SizeType >( strLength ) ), data_{}
        {
            std::copy( str, str + strLength, data_.begin( ) );
        }

        BasicFixedString( const CharType* str )
            : BasicFixedString( str, LengthOf( str ) )
        {
        }

        template<typename T>
            requires ( IsSpecializationOf<T, std::basic_string>&& std::is_same_v<typename T::value_type, CharType> )
        BasicFixedString( const T& str )
            : BasicFixedString( str.c_str( ), str.length( ) )
        {
        }

        template<typename T>
            requires ( IsSpecializationOf<T, std::basic_string_view>&& std::is_same_v<typename T::value_type, CharType> )
        BasicFixedString( const T& str )
            : BasicFixedString( str.data( ), str.length( ) )
        {
        }

        constexpr BasicFixedString( size_t count, CharType val )
            : size_( static_cast< SizeType >( count ) ), data_{}
        {
            std::fill( data_.begin( ), data_.begin( ) + count, val );
        }

        constexpr const CharType* c_str( ) const noexcept
        {
            return data_.data( );
        }
        constexpr const CharType* data( ) const noexcept
        {
            return data_.data( );
        }
        constexpr CharType* data( ) noexcept
        {
            return data_.data( );
        }

        constexpr size_t length( ) const noexcept
        {
            return static_cast< size_t >( size_ );
        }

        constexpr iterator begin( ) noexcept
        {
            data_.begin( );
        }
        constexpr iterator end( ) noexcept
        {
            data_.begin( ) + length( );
        }
        constexpr const_iterator begin( ) const noexcept
        {
            data_.begin( );
        }
        constexpr const_iterator end( ) const noexcept
        {
            data_.begin( ) + length( );
        }

        constexpr CharType& operator[]( size_t index ) const noexcept
        {
            return data_[ index ];
        }
        constexpr CharType& operator[]( size_t index ) noexcept
        {
            return data_[ index ];
        }
        constexpr CharType& at( size_t index ) const noexcept
        {
            return data_[ index ];
        }
        constexpr CharType& at( size_t index ) noexcept
        {
            return data_[ index ];
        }

        constexpr CharType& front( ) const noexcept
        {
            return data_[ 0 ];
        }
        constexpr CharType& front( ) noexcept
        {
            return data_[ 0 ];
        }
        constexpr CharType& back( ) const noexcept
        {
            return data_[ size_ - 1 ];
        }
        constexpr CharType& back( ) noexcept
        {
            return data_[ size_ - 1 ];
        }

        template<typename T>
            requires ( IsSpecializationOf<T, std::basic_string>&& std::is_same_v<typename T::value_type, CharType> )
        BasicFixedString& operator = ( const T& other )
        {
            std::copy( other.begin( ), other.end( ), data_.data( ) );
            size_ = other.length( );
            data_[ size_ ] = static_cast< CharType >( 0 );
            return *this;
        }

        template<typename T>
            requires ( IsSpecializationOf<T, std::basic_string_view>&& std::is_same_v<typename T::value_type, CharType> )
        BasicFixedString& operator = ( const T& other )
        {
            std::copy( other.begin( ), other.end( ), data_.data( ) );
            size_ = other.length( );
            data_[ size_ ] = static_cast< CharType >( 0 );
            return *this;
        }

        BasicFixedString& operator = ( const CharType* str )
        {
            size_t len = LengthOf( str );
            std::copy( str, str + len, data_.data( ) );
            size_ = len;
            data_[ size_ ] = static_cast< CharType >( 0 );
            return *this;
        }


        constexpr const ViewType View( ) const noexcept
        {
            return ViewType( data_.data( ), size_ );
        }
        constexpr ViewType View( ) noexcept
        {
            return ViewType( data_.data( ), size_ );
        }
        constexpr const SpanType Span( ) const noexcept
        {
            return SpanType( data_.data( ), size_ );
        }
        constexpr SpanType Span( ) noexcept
        {
            return SpanType( data_.data( ), size_ );
        }

        size_t Hash( ) const noexcept
        {
            if ( size_ )
            {
                return XXH3_64bits( data_.data( ), size_ * sizeof( CharType ) );
            }
            else
            {
                return 0;
            }
        }
    };

#pragma pack(pop)
    template <typename SizeT, size_t maxSize>
    using FixedWideString = BasicFixedString<SizeT, wchar_t, maxSize, false>;


    template <typename SizeT, size_t maxSize>
    using FixedString = BasicFixedString<SizeT, char, maxSize, false>;
    template <typename SizeT, size_t maxSize>
    using FixedWideZString = BasicFixedString<SizeT, wchar_t, maxSize, true>;
    template <typename SizeT, size_t maxSize>
    using FixedZString = BasicFixedString<SizeT, char, maxSize, true>;
}

#endif
