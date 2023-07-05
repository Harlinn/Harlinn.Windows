#pragma once
#ifndef __HCCARRAY_H__
#define __HCCARRAY_H__

#include <HCCLib.h>
#include <HCCDateTime.h>
#include <HCCGuid.h>
#include <HCCCurrency.h>
#include <HCC7BitEncoding.h>
#include <HCCIterator.h>

#pragma pack(push,1)
namespace Harlinn::Common::Core
{
    
    template<typename T, size_t N>
    class ArrayEx : public std::array<T, N>
    {
    public:
        using Base = std::array<T, N>;

        using Base::value_type;
        using Base::size_type;
        using Base::difference_type;
        using Base::pointer;
        using Base::const_pointer;
        using Base::reference;
        using Base::const_reference;

        using Base::iterator;
        using Base::const_iterator;

        using Base::reverse_iterator;
        using Base::const_reverse_iterator;

        using Base::size;
        using Base::begin;
        using Base::end;

        template<size_t N2>
        constexpr Array<T, N + N2> operator + ( const std::array<T, N2>& other ) const noexcept
        {
            Array<T, N + N2> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            std::copy( other.begin( ), other.end( ), result.begin( )+size() );
            return result;
        }
    };



    namespace Internal
    {
        template <class FirstT, class... RestT>
        struct EnforceSame
        {
            static_assert( std::conjunction_v<std::is_same<FirstT, RestT>...>,"All array elements must be of the same type." );
            using type = FirstT;
        };
    }

    template <class FirstT, class... RestT>
    ArrayEx( FirstT, RestT... ) ->ArrayEx<typename Internal::EnforceSame<FirstT, RestT...>::type, 1 + sizeof...( RestT )>;


    template<typename T, size_t N>
    class Array
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        using iterator = Internal::PointerIterator<Array<T,N>>;
        using const_iterator = Internal::ConstPointerIterator<Array<T, N>>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        T data_[N];

        [[nodiscard]] constexpr iterator begin( ) noexcept
        {
            return iterator( &data_[ 0 ] );
        }

        [[nodiscard]] constexpr const_iterator begin( ) const noexcept
        {
            const_iterator result( &data_[ 0 ] );
            return result;
        }

        [[nodiscard]] constexpr iterator end( ) noexcept
        {
            return iterator( &data_[ N ] );
        }

        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            const_iterator result( &data_[ N ] );
            return result;
        }

        [[nodiscard]] constexpr bool operator==( const Array& other ) const noexcept
        {
            return std::equal( begin( ), end( ), other.begin( ) );
        }



        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            return N;
        }

        [[nodiscard]] constexpr size_type max_size( ) const noexcept
        {
            return N;
        }

        [[nodiscard]] constexpr bool empty( ) const noexcept
        {
            return false;
        }

        [[nodiscard]] constexpr reference at( size_type offset )
        {
            return data_[offset];
        }

        [[nodiscard]] constexpr const_reference at( size_type offset ) const
        {
            return data_[offset];
        }

        [[nodiscard]] constexpr reference operator[]( size_type offset ) noexcept
        {
            return data_[offset];
        }

        [[nodiscard]] constexpr const_reference operator[]( size_type offset ) const noexcept
        {
            return data_[offset];
        }


        [[nodiscard]] reference front( ) noexcept
        {
            return data_[0];
        }

        [[nodiscard]] const_reference front( ) const noexcept
        {
            return data_[0];
        }

        [[nodiscard]] reference back( ) noexcept
        {
            return data_[N - 1];
        }

        [[nodiscard]] const_reference back( ) const noexcept
        {
            return data_[N-1];
        }


        [[nodiscard]] constexpr pointer data( ) noexcept
        {
            return data_;
        }

        [[nodiscard]] constexpr const_pointer data( ) const noexcept
        {
            return data_;
        }

        template<size_t N2>
        constexpr Array<T, N + N2> operator + ( const std::array<T, N2>& other ) const noexcept
        {
            Array<T, N + N2> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            std::copy( other.begin( ), other.end( ), result.begin( ) + size( ) );
            return result;
        }
        template<size_t N2>
        constexpr Array<T, N + N2> operator + ( const Array<T, N2>& other ) const noexcept
        {
            Array<T, N + N2> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            std::copy( other.begin( ), other.end( ), result.begin( ) + size( ) );
            return result;
        }


    };

    template<typename T>
    class Array<T, 0>
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        using iterator = Internal::PointerIterator<Array<T, 0>>;
        using const_iterator = Internal::ConstPointerIterator<Array<T, 0>>;

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;


        T data_[1];

        [[nodiscard]] constexpr iterator begin( ) noexcept
        {
            return iterator( &data_[0] );
        }

        [[nodiscard]] constexpr const_iterator begin( ) const noexcept
        {
            return const_iterator( &data_[ 0 ] );
        }

        [[nodiscard]] constexpr iterator end( ) noexcept
        {
            return iterator( &data_[ 0 ] );
        }

        [[nodiscard]] constexpr const_iterator end( ) const noexcept
        {
            return const_iterator( &data_[ 0 ] );
        }

        [[nodiscard]] constexpr bool operator==( const Array& other ) const noexcept
        {
            return std::equal( begin( ), end( ), other.begin( ) );
        }

        [[nodiscard]] constexpr size_type size( ) const noexcept
        {
            return 0;
        }

        [[nodiscard]] constexpr size_type max_size( ) const noexcept
        {
            return 0;
        }

        [[nodiscard]] constexpr bool empty( ) const noexcept
        {
            return true;
        }

        [[nodiscard]] constexpr reference at( size_type offset )
        {
            return data_[offset];
        }

        [[nodiscard]] constexpr const_reference at( size_type offset ) const
        {
            return data_[offset];
        }

        [[nodiscard]] constexpr reference operator[]( size_type offset ) noexcept
        {
            return data_[offset];
        }

        [[nodiscard]] constexpr const_reference operator[]( size_type offset ) const noexcept
        {
            return data_[offset];
        }

        [[nodiscard]] reference front( ) noexcept
        {
            return data_[0];
        }

        [[nodiscard]] const_reference front( ) const noexcept
        {
            return data_[0];
        }

        [[nodiscard]] reference back( ) noexcept
        {
            return data_[0];
        }

        [[nodiscard]] const_reference back( ) const noexcept
        {
            return data_[0];
        }

        [[nodiscard]] constexpr pointer data( ) noexcept
        {
            return nullptr;
        }

        [[nodiscard]] constexpr const_pointer data( ) const noexcept
        {
            return nullptr;
        }

        template<size_t N2>
        constexpr Array<T, N2> operator + ( const std::array<T, N2>& other ) const noexcept
        {
            Array<T, N2> result{};
            std::copy( other.begin( ), other.end( ), result.begin( ) );
            return result;
        }
        template<size_t N2>
        constexpr Array<T, N2> operator + ( const Array<T, N2>& other ) const noexcept
        {
            return other;
        }

    };

    template <class FirstT, class... RestT>
    Array( FirstT, RestT... )->Array<typename Internal::EnforceSame<FirstT, RestT...>::type, 1 + sizeof...( RestT )>;


    namespace Internal
    {

        template <std::size_t index, typename Arg, typename... Args>
        struct ByteOffsetOf
        {
            static constexpr size_t value = ( std::is_same_v< std::remove_cvref_t<Arg>, bool> ? 1 : sizeof( std::remove_cvref_t<Arg> ) ) + ByteOffsetOf<index - 1, Args...>::value;
        };
        template <typename Arg, typename... Args>
        struct ByteOffsetOf<0, Arg, Args...>
        {
            static constexpr size_t value = 0;
        };

        template<std::size_t index, typename ...Args>
        constexpr size_t ByteOffsetOf_v = ByteOffsetOf<index, Args...>::value;

        template <typename Arg, typename... Args>
        struct _ByteSizeOf
        {
            static constexpr size_t value = (std::is_same_v< std::remove_cvref_t<Arg>,bool>? 1 : sizeof( std::remove_cvref_t<Arg> ) ) + _ByteSizeOf<Args...>::value;
        };
        template <typename Arg>
        struct _ByteSizeOf<Arg>
        {
            static constexpr size_t value = ( std::is_same_v< std::remove_cvref_t<Arg>, bool> ? 1 : sizeof( std::remove_cvref_t<Arg> ) );
        };


        template<typename ...Args>
        constexpr size_t _ByteSizeOf_v = _ByteSizeOf<Args...>::value;
    }






    template<size_t N>
    class ByteArray : public ArrayEx<Byte, N>
    {
    public:
        using Base = ArrayEx<Byte, N>;

        using value_type = Base::value_type;
        using size_type = Base::size_type;
        using difference_type = Base::difference_type;
        using pointer = Base::pointer;
        using const_pointer = Base::const_pointer;
        using reference = Base::reference;
        using const_reference = Base::const_reference;

        using iterator = Base::iterator;
        using const_iterator = Base::const_iterator;

        using reverse_iterator = Base::reverse_iterator;
        using const_reverse_iterator = Base::const_reverse_iterator;

        using Base::size;
        using Base::begin;
        using Base::end;
        using Base::data;
        using Base::front;
        using Base::back;

        constexpr ByteArray( ) noexcept
            : Base{}
        {
        }

        template<typename Arg, typename ...Args>
        constexpr ByteArray( Arg&& arg, Args&& ... args ) noexcept
            : Base{}
        { 
            Write(0, std::forward<Arg>( arg ), std::forward<Args>( args )... );

        }

        constexpr explicit ByteArray( char value ) noexcept
            : Base{ static_cast<Byte>( value ) }
        {

        }

        constexpr explicit ByteArray( SByte value ) noexcept
            : Base{ static_cast<Byte>( value ) }
        {

        }
        constexpr explicit ByteArray( Byte value ) noexcept
            : Base{ value }
        {

        }

        constexpr explicit ByteArray( Int16 value ) noexcept
            : Base{ static_cast<Byte>( value ), static_cast<Byte>( value >> 8 ) }
        {

        }
        constexpr explicit ByteArray( UInt16 value ) noexcept
            : Base{ static_cast<Byte>( value ), static_cast<Byte>( value >> 8 ) }
        {

        }

        constexpr explicit ByteArray( wchar_t value ) noexcept
            : Base{ static_cast<Byte>( value ), static_cast<Byte>( value >> 8 ) }
        {

        }

        constexpr explicit ByteArray( Int32 value ) noexcept
            : Base{ static_cast<Byte>( value ), static_cast<Byte>( value >> 8 ), static_cast<Byte>( value >> 16 ), static_cast<Byte>( value >> 24 ) }
        {

        }
        constexpr explicit ByteArray( UInt32 value ) noexcept
            : Base{ static_cast<Byte>( value ), static_cast<Byte>( value >> 8 ), static_cast<Byte>( value >> 16 ), static_cast<Byte>( value >> 24 ) }
        {

        }

        constexpr explicit ByteArray( Int64 value ) noexcept
            : Base{ static_cast<Byte>( value ), static_cast<Byte>( value >> 8 ), static_cast<Byte>( value >> 16 ), static_cast<Byte>( value >> 24 ),
                static_cast<Byte>( value >> 32 ), static_cast<Byte>( value >> 40 ), static_cast<Byte>( value >> 48 ), static_cast<Byte>( value >> 56 ) }
        {

        }
        constexpr explicit ByteArray( UInt64 value ) noexcept
            : Base{ static_cast<Byte>( value ), static_cast<Byte>( value >> 8 ), static_cast<Byte>( value >> 16 ), static_cast<Byte>( value >> 24 ),
                static_cast<Byte>( value >> 32 ), static_cast<Byte>( value >> 40 ), static_cast<Byte>( value >> 48 ), static_cast<Byte>( value >> 56 ) }
        {

        }

        constexpr explicit ByteArray( float value ) noexcept
            : ByteArray( std::bit_cast<UInt32>( value ) )
        { 
        }
        constexpr explicit ByteArray( double value ) noexcept
            : ByteArray( std::bit_cast<UInt64>( value ) )
        {
        }

        constexpr explicit ByteArray( TimeSpan value ) noexcept
            : ByteArray( std::bit_cast<Int64>( value ) )
        {
        }

        constexpr explicit ByteArray( DateTime value ) noexcept
            : ByteArray( std::bit_cast<Int64>( value ) )
        {
        }

        constexpr explicit ByteArray( Currency value ) noexcept
            : ByteArray( std::bit_cast<Int64>( value ) )
        {
        }

        
        template<typename T1, size_t N1>
        constexpr explicit ByteArray( std::array<T1,N1> value ) noexcept
            : Base{}
        {
            size_t offset = 0;
            constexpr auto count = value.size( );
            for ( size_t i = 0; i < count; ++i )
            {
                offset = Write( offset, value[i] );
            }
        }


        constexpr explicit ByteArray( GUID value ) noexcept
            : Base{}
        {
            *( data( ) ) = static_cast<Byte>( value.Data1 );
            *( data( ) + 1 ) = static_cast<Byte>( value.Data1 >> 8 );
            *( data( ) + 2 ) = static_cast<Byte>( value.Data1 >> 16 );
            *( data( ) + 3 ) = static_cast<Byte>( value.Data1 >> 24 );
            *( data( ) + 4 ) = static_cast<Byte>( value.Data2 );
            *( data( ) + 5 ) = static_cast<Byte>( value.Data2 >> 8 );
            *( data( ) + 6 ) = static_cast<Byte>( value.Data3 );
            *( data( ) + 7 ) = static_cast<Byte>( value.Data3 >> 8 );
            *( data( ) + 8 ) = static_cast<Byte>( value.Data4[0] );
            *( data( ) + 9 ) = static_cast<Byte>( value.Data4[1] );
            *( data( ) + 10 ) = static_cast<Byte>( value.Data4[2] );
            *( data( ) + 11 ) = static_cast<Byte>( value.Data4[3] );
            *( data( ) + 12 ) = static_cast<Byte>( value.Data4[4] );
            *( data( ) + 13 ) = static_cast<Byte>( value.Data4[5] );
            *( data( ) + 14 ) = static_cast<Byte>( value.Data4[6] );
            *( data( ) + 15 ) = static_cast<Byte>( value.Data4[7] );
        }
        constexpr explicit ByteArray( Guid value ) noexcept
            : Base{}
        {
            const GUID& val = value;
            *( data( ) ) = static_cast<Byte>( val.Data1 );
            *( data( ) + 1 ) = static_cast<Byte>( val.Data1 >> 8 );
            *( data( ) + 2 ) = static_cast<Byte>( val.Data1 >> 16 );
            *( data( ) + 3 ) = static_cast<Byte>( val.Data1 >> 24 );
            *( data( ) + 4 ) = static_cast<Byte>( val.Data2 );
            *( data( ) + 5 ) = static_cast<Byte>( val.Data2 >> 8 );
            *( data( ) + 6 ) = static_cast<Byte>( val.Data3 );
            *( data( ) + 7 ) = static_cast<Byte>( val.Data3 >> 8 );
            *( data( ) + 8 ) = static_cast<Byte>( val.Data4[0] );
            *( data( ) + 9 ) = static_cast<Byte>( val.Data4[1] );
            *( data( ) + 10 ) = static_cast<Byte>( val.Data4[2] );
            *( data( ) + 11 ) = static_cast<Byte>( val.Data4[3] );
            *( data( ) + 12 ) = static_cast<Byte>( val.Data4[4] );
            *( data( ) + 13 ) = static_cast<Byte>( val.Data4[5] );
            *( data( ) + 14 ) = static_cast<Byte>( val.Data4[6] );
            *( data( ) + 15 ) = static_cast<Byte>( val.Data4[7] );
        }

        template<typename E>
            requires std::is_enum_v<E>
        constexpr explicit ByteArray( E value ) noexcept
            : ByteArray( std::bit_cast< std::underlying_type_t<E> >( value ) )
        {
        }

        [[nodiscard]] constexpr bool operator==( const ByteArray& other ) const noexcept
        {
            return std::equal( begin( ), end( ), other.begin( ) );
        }


        template<size_t N2>
        constexpr ByteArray<N + N2> operator + ( const std::array<Byte, N2>& other ) const noexcept
        {
            ByteArray<N + N2> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            std::copy( other.begin( ), other.end( ), result.begin( ) + size( ) );
            return result;
        }

        template<size_t N2>
        constexpr ByteArray<N + N2> operator + ( const Array<Byte, N2>& other ) const noexcept
        {
            ByteArray<N + N2> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            std::copy( other.begin( ), other.end( ), result.begin( ) + size( ) );
            return result;
        }


        constexpr ByteArray<N + 1> operator + ( bool value ) const noexcept
        {
            ByteArray<N + 1> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value? 1:0 );
            return result;
        }

        constexpr ByteArray<N + 1> operator + ( char value ) const noexcept
        {
            ByteArray<N + 1> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            return result;
        }

        constexpr ByteArray<N + 1> operator + ( SByte value ) const noexcept
        {
            ByteArray<N + 1> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            return result;
        }

        constexpr ByteArray<N + 1> operator + ( Byte value ) const noexcept
        {
            ByteArray<N + 1> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = value;
            return result;
        }

        constexpr ByteArray<N + 2> operator + ( Int16 value ) const noexcept
        {
            ByteArray<N + 2> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            result[size( ) + 1] = static_cast<Byte>( value >> 8 );
            return result;
        }
        constexpr ByteArray<N + 2> operator + ( UInt16 value ) const noexcept
        {
            ByteArray<N + 2> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            result[size( ) + 1] = static_cast<Byte>( value >> 8 );
            return result;
        }

        constexpr ByteArray<N + 2> operator + ( wchar_t value ) const noexcept
        {
            ByteArray<N + 2> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            result[size( ) + 1] = static_cast<Byte>( value >> 8 );
            return result;
        }


        constexpr ByteArray<N + 4> operator + ( Int32 value ) const noexcept
        {
            ByteArray<N + 4> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            result[size( ) + 1] = static_cast<Byte>( value >> 8 );
            result[size( ) + 2] = static_cast<Byte>( value >> 16 );
            result[size( ) + 3] = static_cast<Byte>( value >> 24 );
            return result;
        }
        constexpr ByteArray<N + 4> operator + ( UInt32 value ) const noexcept
        {
            ByteArray<N + 4> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            result[size( ) + 1] = static_cast<Byte>( value >> 8 );
            result[size( ) + 2] = static_cast<Byte>( value >> 16 );
            result[size( ) + 3] = static_cast<Byte>( value >> 24 );
            return result;
        }
        constexpr ByteArray<N + 8> operator + ( Int64 value ) const noexcept
        {
            ByteArray<N + 8> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            result[size( ) + 1] = static_cast<Byte>( value >> 8 );
            result[size( ) + 2] = static_cast<Byte>( value >> 16 );
            result[size( ) + 3] = static_cast<Byte>( value >> 24 );
            result[size( ) + 4] = static_cast<Byte>( value >> 32 );
            result[size( ) + 5] = static_cast<Byte>( value >> 40 );
            result[size( ) + 6] = static_cast<Byte>( value >> 48 );
            result[size( ) + 7] = static_cast<Byte>( value >> 56 );
            return result;
        }
        constexpr ByteArray<N + 8> operator + ( UInt64 value ) const noexcept
        {
            ByteArray<N + 8> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            result[size( )] = static_cast<Byte>( value );
            result[size( ) + 1] = static_cast<Byte>( value >> 8 );
            result[size( ) + 2] = static_cast<Byte>( value >> 16 );
            result[size( ) + 3] = static_cast<Byte>( value >> 24 );
            result[size( ) + 4] = static_cast<Byte>( value >> 32 );
            result[size( ) + 5] = static_cast<Byte>( value >> 40 );
            result[size( ) + 6] = static_cast<Byte>( value >> 48 );
            result[size( ) + 7] = static_cast<Byte>( value >> 56 );
            return result;
        }
        
        constexpr ByteArray<N + 4> operator + ( float value ) const noexcept
        {
            ByteArray<N + 4> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            auto val = std::bit_cast<UInt32>( value );
            result[size( )] = static_cast<Byte>( val );
            result[size( ) + 1] = static_cast<Byte>( val >> 8 );
            result[size( ) + 2] = static_cast<Byte>( val >> 16 );
            result[size( ) + 3] = static_cast<Byte>( val >> 24 );
            return result;
        }

        constexpr ByteArray<N + 8> operator + ( double value ) const noexcept
        {
            ByteArray<N + 8> result{};
            std::copy( begin( ), end( ), result.begin( ) );

            auto val = std::bit_cast<UInt64>( value );
            result[size( )] = static_cast<Byte>( val );
            result[size( ) + 1] = static_cast<Byte>( val >> 8 );
            result[size( ) + 2] = static_cast<Byte>( val >> 16 );
            result[size( ) + 3] = static_cast<Byte>( val >> 24 );
            result[size( ) + 4] = static_cast<Byte>( val >> 32 );
            result[size( ) + 5] = static_cast<Byte>( val >> 40 );
            result[size( ) + 6] = static_cast<Byte>( val >> 48 );
            result[size( ) + 7] = static_cast<Byte>( val >> 56 );
            return result;
        }

        constexpr ByteArray<N + 8> operator + ( TimeSpan value ) const noexcept
        {
            ByteArray<N + 8> result{};
            std::copy( begin( ), end( ), result.begin( ) );

            Int64 val = value.Ticks( );
            result[size( )] = static_cast<Byte>( val );
            result[size( ) + 1] = static_cast<Byte>( val >> 8 );
            result[size( ) + 2] = static_cast<Byte>( val >> 16 );
            result[size( ) + 3] = static_cast<Byte>( val >> 24 );
            result[size( ) + 4] = static_cast<Byte>( val >> 32 );
            result[size( ) + 5] = static_cast<Byte>( val >> 40 );
            result[size( ) + 6] = static_cast<Byte>( val >> 48 );
            result[size( ) + 7] = static_cast<Byte>( val >> 56 );
            return result;
        }

        constexpr ByteArray<N + 8> operator + ( DateTime value ) const noexcept
        {
            ByteArray<N + 8> result{};
            std::copy( begin( ), end( ), result.begin( ) );

            Int64 val = value.Ticks( );
            result[size( )] = static_cast<Byte>( val );
            result[size( ) + 1] = static_cast<Byte>( val >> 8 );
            result[size( ) + 2] = static_cast<Byte>( val >> 16 );
            result[size( ) + 3] = static_cast<Byte>( val >> 24 );
            result[size( ) + 4] = static_cast<Byte>( val >> 32 );
            result[size( ) + 5] = static_cast<Byte>( val >> 40 );
            result[size( ) + 6] = static_cast<Byte>( val >> 48 );
            result[size( ) + 7] = static_cast<Byte>( val >> 56 );
            return result;
        }

        constexpr ByteArray<N + 8> operator + ( Currency value ) const noexcept
        {
            ByteArray<N + 8> result{};
            std::copy( begin( ), end( ), result.begin( ) );

            Int64 val = std::bit_cast<Int64>( value );
            result[size( )] = static_cast<Byte>( val );
            result[size( ) + 1] = static_cast<Byte>( val >> 8 );
            result[size( ) + 2] = static_cast<Byte>( val >> 16 );
            result[size( ) + 3] = static_cast<Byte>( val >> 24 );
            result[size( ) + 4] = static_cast<Byte>( val >> 32 );
            result[size( ) + 5] = static_cast<Byte>( val >> 40 );
            result[size( ) + 6] = static_cast<Byte>( val >> 48 );
            result[size( ) + 7] = static_cast<Byte>( val >> 56 );
            return result;
        }

        constexpr ByteArray<N + 16> operator + ( GUID value ) const noexcept
        {
            ByteArray<N + 16> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            
            result[size( )] = static_cast<Byte>( value.Data1 );
            result[size( ) + 1] = static_cast<Byte>( value.Data1 >> 8 );
            result[size( ) + 2] = static_cast<Byte>( value.Data1 >> 16 );
            result[size( ) + 3] = static_cast<Byte>( value.Data1 >> 24 );
            result[size( ) + 4] = static_cast<Byte>( value.Data2 );
            result[size( ) + 5] = static_cast<Byte>( value.Data2 >> 8 );
            result[size( ) + 6] = static_cast<Byte>( value.Data3 );
            result[size( ) + 7] = static_cast<Byte>( value.Data3 >> 8 );
            result[size( ) + 8] = static_cast<Byte>( value.Data4[0] );
            result[size( ) + 9] = static_cast<Byte>( value.Data4[1] );
            result[size( ) + 10] = static_cast<Byte>( value.Data4[2] );
            result[size( ) + 11] = static_cast<Byte>( value.Data4[3] );
            result[size( ) + 12] = static_cast<Byte>( value.Data4[4] );
            result[size( ) + 13] = static_cast<Byte>( value.Data4[5] );
            result[size( ) + 14] = static_cast<Byte>( value.Data4[6] );
            result[size( ) + 15] = static_cast<Byte>( value.Data4[7] );

            return result;
        }

        constexpr ByteArray<N + 16> operator + ( Guid value ) const noexcept
        {
            ByteArray<N + 16> result{};
            std::copy( begin( ), end( ), result.begin( ) );

            const GUID& val = value;

            result[size( )] = static_cast<Byte>( val.Data1 );
            result[size( ) + 1] = static_cast<Byte>( val.Data1 >> 8 );
            result[size( ) + 2] = static_cast<Byte>( val.Data1 >> 16 );
            result[size( ) + 3] = static_cast<Byte>( val.Data1 >> 24 );
            result[size( ) + 4] = static_cast<Byte>( val.Data2 );
            result[size( ) + 5] = static_cast<Byte>( val.Data2 >> 8 );
            result[size( ) + 6] = static_cast<Byte>( val.Data3 );
            result[size( ) + 7] = static_cast<Byte>( val.Data3 >> 8 );
            result[size( ) + 8] = static_cast<Byte>( val.Data4[0] );
            result[size( ) + 9] = static_cast<Byte>( val.Data4[1] );
            result[size( ) + 10] = static_cast<Byte>( val.Data4[2] );
            result[size( ) + 11] = static_cast<Byte>( val.Data4[3] );
            result[size( ) + 12] = static_cast<Byte>( val.Data4[4] );
            result[size( ) + 13] = static_cast<Byte>( val.Data4[5] );
            result[size( ) + 14] = static_cast<Byte>( val.Data4[6] );
            result[size( ) + 15] = static_cast<Byte>( val.Data4[7] );

            return result;
        }

        template<typename E>
            requires std::is_enum_v<E>
        constexpr ByteArray<N + sizeof( std::underlying_type_t<E> )> operator + ( E value ) const noexcept
        {
            ByteArray<N + sizeof( std::underlying_type_t<E> )> result{};
            std::copy( begin( ), end( ), result.begin( ) );
            if constexpr ( sizeof( std::underlying_type_t<E> ) == 1 )
            {
                result[size( )] = static_cast<Byte>( value );
            }
            else if constexpr ( sizeof( std::underlying_type_t<E> ) == 2 )
            {
                result[size( )] = static_cast<Byte>( static_cast<UInt32>( value ) );
                result[size( ) + 1] = static_cast<Byte>( static_cast<UInt32>( value ) >> 8 );
            }
            else if constexpr ( sizeof( std::underlying_type_t<E> ) == 4 )
            {
                result[size( )] = static_cast<Byte>( static_cast<UInt32>( value ) );
                result[size( ) + 1] = static_cast<Byte>( static_cast<UInt32>( value ) >> 8 );
                result[size( ) + 2] = static_cast<Byte>( static_cast<UInt32>( value ) >> 16 );
                result[size( ) + 3] = static_cast<Byte>( static_cast<UInt32>( value ) >> 24 );
            }
            else 
            {
                result[size( )] = static_cast<Byte>( static_cast<UInt64>( value ) );
                result[size( ) + 1] = static_cast<Byte>( static_cast<UInt64>( value ) >> 8 );
                result[size( ) + 2] = static_cast<Byte>( static_cast<UInt64>( value ) >> 16 );
                result[size( ) + 3] = static_cast<Byte>( static_cast<UInt64>( value ) >> 24 );
                result[size( ) + 4] = static_cast<Byte>( static_cast<UInt64>( value ) >> 32 );
                result[size( ) + 5] = static_cast<Byte>( static_cast<UInt64>( value ) >> 40 );
                result[size( ) + 6] = static_cast<Byte>( static_cast<UInt64>( value ) >> 48 );
                result[size( ) + 7] = static_cast<Byte>( static_cast<UInt64>( value ) >> 56 );
            }
            return result;
        }


        template<typename T>
        constexpr T Read( const_iterator it ) const noexcept;
        template<typename T>
        constexpr T Read( size_type offset ) const noexcept;


        constexpr const_iterator Read( const_iterator it, bool& value ) const noexcept
        {
            value = ( *it ) ? true : false;
            return it + 1;
        }

        template<>
        constexpr bool Read<bool>( const_iterator it ) const noexcept
        {
            auto result = ( *it ) ? true : false;
            return result;
        }
        template<>
        constexpr bool Read<bool>( size_type offset ) const noexcept
        {
            auto result = ( * ( data() + offset ) ) ? true : false;
            return result;
        }


        constexpr const_iterator Read( const_iterator it, char& value ) const noexcept
        {
            value = static_cast<char>( *it );
            return it + 1;
        }
        template<>
        constexpr char Read<char>( const_iterator it ) const noexcept
        {
            auto result = static_cast<char>( *it );
            return result;
        }
        template<>
        constexpr char Read<char>( size_type offset ) const noexcept
        {
            auto result = static_cast<char>( *( data( ) + offset ) );
            return result;
        }


        constexpr const_iterator Read( const_iterator it, SByte& value ) const noexcept
        {
            value = static_cast<SByte>( *it );
            return it + 1;
        }
        template<>
        constexpr SByte Read<SByte>( const_iterator it ) const noexcept
        {
            auto result = static_cast<SByte>( *it );
            return result;
        }
        template<>
        constexpr SByte Read<SByte>( size_type offset ) const noexcept
        {
            auto result = static_cast<SByte>( *( data( ) + offset ) );
            return result;
        }

        constexpr const_iterator Read( const_iterator it, Byte& value ) const noexcept
        {
            value = *it;
            return it + 1;
        }
        template<>
        constexpr Byte Read<Byte>( const_iterator it ) const noexcept
        {
            auto result = static_cast<Byte>( *it );
            return result;
        }
        template<>
        constexpr Byte Read<Byte>( size_type offset ) const noexcept
        {
            auto result = static_cast<Byte>( *( data( ) + offset ) );
            return result;
        }

        constexpr const_iterator Read( const_iterator it, Int16& value ) const noexcept
        {
            value = static_cast<Int16>( *it ) 
                | ( static_cast<Int16>( *(it + 1) ) << 8 );
            return it + 2;
        }
        template<>
        constexpr Int16 Read<Int16>( const_iterator it ) const noexcept
        {
            auto result = static_cast<Int16>( static_cast<Byte>(*it) ) 
                | (static_cast<Int16>( static_cast<Byte>( *( it + 1 ) ) ) << 8);
            return result;
        }
        template<>
        constexpr Int16 Read<Int16>( size_type offset ) const noexcept
        {
            auto result = static_cast<Int16>( *( data( ) + offset ) ) 
                | (static_cast<Int16>( *( data( ) + offset + 1 ) ) << 8);
            return result;
        }


        constexpr const_iterator Read( const_iterator it, UInt16& value ) const noexcept
        {
            value = static_cast<UInt16>( *it ) 
                | (static_cast<UInt16>( *( it + 1 ) ) << 8);
            return it + 2;
        }
        template<>
        constexpr UInt16 Read<UInt16>( const_iterator it ) const noexcept
        {
            auto result = static_cast<UInt16>( *it ) 
                | ( static_cast<UInt16>( *( it + 1 ) ) << 8 );
            return result;
        }

        template<>
        constexpr UInt16 Read<UInt16>( size_type offset ) const noexcept
        {
            auto result = static_cast<UInt16>( *( data( ) + offset ) ) 
                | (static_cast<UInt16>( *( data( ) + offset + 1 ) ) << 8);
            return result;
        }

        constexpr const_iterator Read( const_iterator it, wchar_t& value ) const noexcept
        {
            value = static_cast<wchar_t>( *it )
                | ( static_cast<wchar_t>( *( it + 1 ) ) << 8 );
            return it + 2;
        }
        template<>
        constexpr wchar_t Read<wchar_t>( const_iterator it ) const noexcept
        {
            auto result = static_cast<wchar_t>( *it )
                | ( static_cast<wchar_t>( *( it + 1 ) ) << 8 );
            return result;
        }

        template<>
        constexpr wchar_t Read<wchar_t>( size_type offset ) const noexcept
        {
            auto result = static_cast<wchar_t>( *( data( ) + offset ) )
                | ( static_cast<wchar_t>( *( data( ) + offset + 1 ) ) << 8 );
            return result;
        }


        constexpr const_iterator Read( const_iterator it, Int32& value ) const noexcept
        {
            value = static_cast<Int32>( *it )
                | ( static_cast<Int32>( *( it + 1 ) ) << 8 )
                | ( static_cast<Int32>( *( it + 2 ) ) << 16 )
                | ( static_cast<Int32>( *( it + 3 ) ) << 24 );
            return it + 4;
        }
        template<>
        constexpr Int32 Read<Int32>( const_iterator it ) const noexcept
        {
            auto result = static_cast<Int32>( static_cast<Byte>( *it ) )
                | ( static_cast<Int32>( static_cast<Byte>( *( it + 1 ) ) ) << 8 )
                | ( static_cast<Int32>( static_cast<Byte>( *( it + 2 ) ) ) << 16 )
                | ( static_cast<Int32>( static_cast<Byte>( *( it + 3 ) ) ) << 24 );
            return result;
        }
        template<>
        constexpr Int32 Read<Int32>( size_type offset ) const noexcept
        {
            auto result = static_cast<Int32>( *( data( ) + offset ) )
                | ( static_cast<Int32>( *( data( ) + offset + 1 ) ) << 8 )
                | ( static_cast<Int32>( *( data( ) + offset + 2 ) ) << 16 )
                | ( static_cast<Int32>( *( data( ) + offset + 3 ) ) << 24 );
            return result;
        }

        constexpr const_iterator Read( const_iterator it, UInt32& value ) const noexcept
        {
            value = static_cast<UInt32>( *it )
                | ( static_cast<UInt32>( *( it + 1 ) ) << 8 )
                | ( static_cast<UInt32>( *( it + 2 ) ) << 16 )
                | ( static_cast<UInt32>( *( it + 3 ) ) << 24 );
            return it + 4;
        }
        template<>
        constexpr UInt32 Read<UInt32>( const_iterator it ) const noexcept
        {
            auto result = static_cast<UInt32>( static_cast<Byte>( *it ) )
                | ( static_cast<UInt32>( static_cast<Byte>( *( it + 1 ) ) ) << 8 )
                | ( static_cast<UInt32>( static_cast<Byte>( *( it + 2 ) ) ) << 16 )
                | ( static_cast<UInt32>( static_cast<Byte>( *( it + 3 ) ) ) << 24 );
            return result;
        }
        template<>
        constexpr UInt32 Read<UInt32>( size_type offset ) const noexcept
        {
            auto result = static_cast<UInt32>( *( data( ) + offset ) )
                | ( static_cast<UInt32>( *( data( ) + offset + 1 ) ) << 8 )
                | ( static_cast<UInt32>( *( data( ) + offset + 2 ) ) << 16 )
                | ( static_cast<UInt32>( *( data( ) + offset + 3 ) ) << 24 );
            return result;
        }

        constexpr const_iterator Read( const_iterator it, Int64& value ) const noexcept
        {
            value = static_cast<Int64>( *it )
                | ( static_cast<Int64>( *( it + 1 ) ) << 8 )
                | ( static_cast<Int64>( *( it + 2 ) ) << 16 )
                | ( static_cast<Int64>( *( it + 3 ) ) << 24 )
                | ( static_cast<Int64>( *( it + 4 ) ) << 32 )
                | ( static_cast<Int64>( *( it + 5 ) ) << 40 )
                | ( static_cast<Int64>( *( it + 6 ) ) << 48 )
                | ( static_cast<Int64>( *( it + 7 ) ) << 56 );
            return it + 8;
        }
        template<>
        constexpr Int64 Read<Int64>( const_iterator it ) const noexcept
        {
            auto result = static_cast<Int64>( static_cast<Byte>( *it ) )
                | ( static_cast<Int64>( static_cast<Byte>( *( it + 1 ) ) ) << 8 )
                | ( static_cast<Int64>( static_cast<Byte>( *( it + 2 ) ) ) << 16 )
                | ( static_cast<Int64>( static_cast<Byte>( *( it + 3 ) ) ) << 24 )
                | ( static_cast<Int64>( static_cast<Byte>( *( it + 4 ) ) ) << 32 )
                | ( static_cast<Int64>( static_cast<Byte>( *( it + 5 ) ) ) << 40 )
                | ( static_cast<Int64>( static_cast<Byte>( *( it + 6 ) ) ) << 48 )
                | ( static_cast<Int64>( static_cast<Byte>( *( it + 7 ) ) ) << 56 );
            return result;
        }
        template<>
        constexpr Int64 Read<Int64>( size_type offset ) const noexcept
        {
            auto result = static_cast<Int64>( *( data( ) + offset ) )
                | ( static_cast<Int64>( *( data( ) + offset + 1 ) ) << 8 )
                | ( static_cast<Int64>( *( data( ) + offset + 2 ) ) << 16 )
                | ( static_cast<Int64>( *( data( ) + offset + 3 ) ) << 24 )
                | ( static_cast<Int64>( *( data( ) + offset + 4 ) ) << 32 )
                | ( static_cast<Int64>( *( data( ) + offset + 5 ) ) << 40 )
                | ( static_cast<Int64>( *( data( ) + offset + 6 ) ) << 48 )
                | ( static_cast<Int64>( *( data( ) + offset + 7 ) ) << 56 );
            return result;
        }

        constexpr const_iterator Read( const_iterator it, UInt64& value ) const noexcept
        {
            value = static_cast<UInt64>( *it )
                | ( static_cast<UInt64>( *( it + 1 ) ) << 8 )
                | ( static_cast<UInt64>( *( it + 2 ) ) << 16 )
                | ( static_cast<UInt64>( *( it + 3 ) ) << 24 )
                | ( static_cast<UInt64>( *( it + 4 ) ) << 32 )
                | ( static_cast<UInt64>( *( it + 5 ) ) << 40 )
                | ( static_cast<UInt64>( *( it + 6 ) ) << 48 )
                | ( static_cast<UInt64>( *( it + 7 ) ) << 56 );
            return it + 8;
        }
        template<>
        constexpr UInt64 Read<UInt64>( const_iterator it ) const noexcept
        {
            auto result = static_cast<UInt64>( static_cast<Byte>( *it ) )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 1 ) ) ) << 8 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 2 ) ) ) << 16 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 3 ) ) ) << 24 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 4 ) ) ) << 32 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 5 ) ) ) << 40 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 6 ) ) ) << 48 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 7 ) ) ) << 56 );
            return result;
        }
        template<>
        constexpr UInt64 Read<UInt64>( size_type offset ) const noexcept
        {
            auto result = static_cast<UInt64>( *( data( ) + offset ) )
                | ( static_cast<UInt64>( *( data( ) + offset + 1 ) ) << 8 )
                | ( static_cast<UInt64>( *( data( ) + offset + 2 ) ) << 16 )
                | ( static_cast<UInt64>( *( data( ) + offset + 3 ) ) << 24 )
                | ( static_cast<UInt64>( *( data( ) + offset + 4 ) ) << 32 )
                | ( static_cast<UInt64>( *( data( ) + offset + 5 ) ) << 40 )
                | ( static_cast<UInt64>( *( data( ) + offset + 6 ) ) << 48 )
                | ( static_cast<UInt64>( *( data( ) + offset + 7 ) ) << 56 );
            return result;
        }


        constexpr const_iterator Read( const_iterator it, float& value ) const noexcept
        {
            value = std::bit_cast<float>( static_cast<UInt32>( *it )
                | ( static_cast<UInt32>( *( it + 1 ) ) << 8 )
                | ( static_cast<UInt32>( *( it + 2 ) ) << 16 )
                | ( static_cast<UInt32>( *( it + 3 ) ) << 24 ) );
            return it + 4;
        }
        template<>
        constexpr float Read<float>( const_iterator it ) const noexcept
        {
            auto result = std::bit_cast<float>( static_cast<UInt32>( static_cast<Byte>( *it ) )
                | ( static_cast<UInt32>( static_cast<Byte>( *( it + 1 ) ) ) << 8 )
                | ( static_cast<UInt32>( static_cast<Byte>( *( it + 2 ) ) ) << 16 )
                | ( static_cast<UInt32>( static_cast<Byte>( *( it + 3 ) ) ) << 24 ) );
            return result;
        }
        template<>
        constexpr float Read<float>( size_type offset ) const noexcept
        {
            auto result = std::bit_cast<float>( static_cast<UInt32>( *( data( ) + offset ) )
                | ( static_cast<UInt32>( *( data( ) + offset + 1 ) ) << 8 )
                | ( static_cast<UInt32>( *( data( ) + offset + 2 ) ) << 16 )
                | ( static_cast<UInt32>( *( data( ) + offset + 3 ) ) << 24 ) );
            return result;
        }

        constexpr const_iterator Read( const_iterator it, double& value ) const noexcept
        {
            value = std::bit_cast<double>( static_cast<UInt64>( *it )
                | ( static_cast<UInt64>( *( it + 1 ) ) << 8 )
                | ( static_cast<UInt64>( *( it + 2 ) ) << 16 )
                | ( static_cast<UInt64>( *( it + 3 ) ) << 24 )
                | ( static_cast<UInt64>( *( it + 4 ) ) << 32 )
                | ( static_cast<UInt64>( *( it + 5 ) ) << 40 )
                | ( static_cast<UInt64>( *( it + 6 ) ) << 48 )
                | ( static_cast<UInt64>( *( it + 7 ) ) << 56 ) );
            return it + 8;
        }
        template<>
        constexpr double Read<double>( const_iterator it ) const noexcept
        {
            auto result = std::bit_cast<double>( static_cast<UInt64>( static_cast<Byte>( *it ) )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 1 ) ) ) << 8 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 2 ) ) ) << 16 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 3 ) ) ) << 24 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 4 ) ) ) << 32 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 5 ) ) ) << 40 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 6 ) ) ) << 48 )
                | ( static_cast<UInt64>( static_cast<Byte>( *( it + 7 ) ) ) << 56 ) );
            return result;
        }
        template<>
        constexpr double Read<double>( size_type offset ) const noexcept
        {
            auto result = std::bit_cast<double>( static_cast<UInt64>( *( data( ) + offset ) )
                | ( static_cast<UInt64>( *( data( ) + offset + 1 ) ) << 8 )
                | ( static_cast<UInt64>( *( data( ) + offset + 2 ) ) << 16 )
                | ( static_cast<UInt64>( *( data( ) + offset + 3 ) ) << 24 )
                | ( static_cast<UInt64>( *( data( ) + offset + 4 ) ) << 32 )
                | ( static_cast<UInt64>( *( data( ) + offset + 5 ) ) << 40 )
                | ( static_cast<UInt64>( *( data( ) + offset + 6 ) ) << 48 )
                | ( static_cast<UInt64>( *( data( ) + offset + 7 ) ) << 56 ) );
            return result;
        }

        constexpr const_iterator Read( const_iterator it, TimeSpan& value ) const noexcept
        {
            Int64 val = 0;
            auto result = Read( it, val );
            value = TimeSpan( val );
            return result;
        }
        template<>
        constexpr TimeSpan Read<TimeSpan>( const_iterator it ) const noexcept
        {
            auto result = Read<Int64>( it );
            return TimeSpan( result );
        }
        template<>
        constexpr TimeSpan Read<TimeSpan>( size_type offset ) const noexcept
        {
            auto result = Read<Int64>( offset );
            return TimeSpan( result );
        }


        constexpr const_iterator Read( const_iterator it, DateTime& value ) const noexcept
        {
            Int64 val = 0;
            auto result = Read( it, val );
            value = DateTime( val );
            return result;
        }
        template<>
        constexpr DateTime Read<DateTime>( const_iterator it ) const noexcept
        {
            auto result = Read<Int64>( it );
            return DateTime( result );
        }
        template<>
        constexpr DateTime Read<DateTime>( size_type offset ) const noexcept
        {
            auto result = Read<Int64>( offset );
            return DateTime( result );
        }

        constexpr const_iterator Read( const_iterator it, Currency& value ) const noexcept
        {
            Int64 val = 0;
            auto result = Read( it, val );
            value = std::bit_cast<Currency>( val );
            return result;
        }
        template<>
        constexpr Currency Read<Currency>( const_iterator it ) const noexcept
        {
            auto result = Read<Int64>( it );
            return std::bit_cast<Currency>( result );
        }
        template<>
        constexpr Currency Read<Currency>( size_type offset ) const noexcept
        {
            auto result = Read<Int64>( offset );
            return std::bit_cast<Currency>( result );
        }

        constexpr const_iterator Read( const_iterator it, GUID& value ) const noexcept
        {
            value.Data1 = static_cast<unsigned long>( static_cast<Byte>( *it ) )
                | ( static_cast<unsigned long>( static_cast<Byte>( *( it + 1 ) ) ) << 8 )
                | ( static_cast<unsigned long>( static_cast<Byte>( *( it + 2 ) ) ) << 16 )
                | ( static_cast<unsigned long>( static_cast<Byte>( *( it + 3 ) ) ) << 24 );
            value.Data2 = static_cast<UInt16>( static_cast<UInt16>( static_cast<Byte>( *( it + 4 ) ) )
                | ( static_cast<UInt16>( static_cast<Byte>( *( it + 5 ) ) ) << 8 ) );
            value.Data3 = static_cast<UInt16>( static_cast<UInt16>( static_cast<Byte>( *( it + 6 ) ) )
                | ( static_cast<UInt16>( static_cast<Byte>( *( it + 7 ) ) ) << 8 ) );
            value.Data4[0] = static_cast<Byte>( *( it + 8 ) );
            value.Data4[1] = static_cast<Byte>( *( it + 9 ) );
            value.Data4[2] = static_cast<Byte>( *( it + 10 ) );
            value.Data4[3] = static_cast<Byte>( *( it + 11 ) );
            value.Data4[4] = static_cast<Byte>( *( it + 12 ) );
            value.Data4[5] = static_cast<Byte>( *( it + 13 ) );
            value.Data4[6] = static_cast<Byte>( *( it + 14 ) );
            value.Data4[7] = static_cast<Byte>( *( it + 15 ) );


            return it + 16;
        }

        template<>
        constexpr GUID Read<GUID>( const_iterator it ) const noexcept
        {
            GUID result{ static_cast<unsigned long>( static_cast<Byte>( *it ) )
                    | ( static_cast<unsigned long>( static_cast<Byte>( *( it + 1 ) ) ) << 8 )
                    | ( static_cast<unsigned long>( static_cast<Byte>( *( it + 2 ) ) ) << 16 )
                    | ( static_cast<unsigned long>( static_cast<Byte>( *( it + 3 ) ) ) << 24 ),
                static_cast<UInt16>( static_cast<UInt16>( static_cast<Byte>( *( it + 4 ) ) )
                    | ( static_cast<UInt16>( static_cast<Byte>( *( it + 5 ) ) ) << 8 ) ),
                static_cast<UInt16>( static_cast<UInt16>( static_cast<Byte>( *( it + 6 ) ) )
                    | ( static_cast<UInt16>( static_cast<Byte>( *( it + 7 ) ) ) << 8 ) ),
                static_cast<Byte>( *( it + 8 ) ),
                static_cast<Byte>( *( it + 9 ) ),
                static_cast<Byte>( *( it + 10 ) ),
                static_cast<Byte>( *( it + 11 ) ),
                static_cast<Byte>( *( it + 12 ) ),
                static_cast<Byte>( *( it + 13 ) ),
                static_cast<Byte>( *( it + 14 ) ),
                static_cast<Byte>( *( it + 15 ) ) };
            return result;
        }

        template<>
        constexpr GUID Read<GUID>( size_type offset ) const noexcept
        {
            const auto* ptr = data( ) + offset;
            GUID result{ static_cast<unsigned long>( static_cast<Byte>( *ptr ) )
                    | ( static_cast<unsigned long>( static_cast<Byte>( *( ptr + 1 ) ) ) << 8 )
                    | ( static_cast<unsigned long>( static_cast<Byte>( *( ptr + 2 ) ) ) << 16 )
                    | ( static_cast<unsigned long>( static_cast<Byte>( *( ptr + 3 ) ) ) << 24 ),
                static_cast<UInt16>( static_cast<UInt16>( static_cast<Byte>( *( ptr + 4 ) ) )
                    | ( static_cast<UInt16>( static_cast<Byte>( *( ptr + 5 ) ) ) << 8 ) ),
                static_cast<UInt16>( static_cast<UInt16>( static_cast<Byte>( *( ptr + 6 ) ) )
                    | ( static_cast<UInt16>( static_cast<Byte>( *( ptr + 7 ) ) ) << 8 ) ),
                static_cast<Byte>( *( ptr + 8 ) ),
                static_cast<Byte>( *( ptr + 9 ) ),
                static_cast<Byte>( *( ptr + 10 ) ),
                static_cast<Byte>( *( ptr + 11 ) ),
                static_cast<Byte>( *( ptr + 12 ) ),
                static_cast<Byte>( *( ptr + 13 ) ),
                static_cast<Byte>( *( ptr + 14 ) ),
                static_cast<Byte>( *( ptr + 15 ) ) };
            return result;
        }

        constexpr const_iterator Read( const_iterator it, Guid& value ) const noexcept
        {
            GUID& guid = value;
            return Read( it, guid );
        }
        template<>
        constexpr Guid Read<Guid>( const_iterator it ) const noexcept
        {
            return Read<GUID>( it );
        }
        template<>
        constexpr Guid Read<Guid>( size_type offset ) const noexcept
        {
            return Read<GUID>( offset );
        }

        template<typename E>
            requires std::is_enum_v<E>
        constexpr const_iterator Read( const_iterator it, E& value ) const noexcept
        {
            std::underlying_type_t<E> val{};
            auto result = Read( it, val );
            value = static_cast<E>( val );
            return result;
        }

        template<typename E>
            requires std::is_enum_v<E>
        constexpr E Read( const_iterator it ) const noexcept
        {
            return static_cast<E>( Read<std::underlying_type_t<E>>( it ) );
        }
        template<typename E>
            requires std::is_enum_v<E>
        constexpr E Read( size_type offset ) const noexcept
        {
            return static_cast<E>( Read<std::underlying_type_t<E>>( offset ) );
        }



        template<size_t N>
        constexpr ByteArray<N> Read( size_type offset ) const noexcept
        {
            ByteArray<N> result;
            std::copy( begin( ) + offset, begin( ) + offset + N, result.begin( ) );
            return result;
        }

        
        constexpr const_iterator Read7BitEncoded( const_iterator it, UInt64& result ) const noexcept
        {
            auto offset = std::distance( begin( ), it );
            auto encodedSize = Read7BitEncodedValue( data( ), offset, result );
            return begin( ) + offset + encodedSize;
        }

        constexpr size_type Read7BitEncoded( size_type offset, UInt64& result ) const noexcept
        {
            auto encodedSize = Read7BitEncodedValue( data( ), offset, result );
            return offset + encodedSize;
        }
        constexpr UInt64 Read7BitEncoded( const_iterator it ) const noexcept
        {
            UInt64 result = 0;
            auto offset = std::distance( begin( ), it );
            Read7BitEncodedValue( data( ), offset, result );
            return result;
        }
        constexpr UInt64 Read7BitEncoded( size_type offset ) const noexcept
        {
            UInt64 result = 0;
            Read7BitEncodedValue( data( ), offset, result );
            return result;
        }


        constexpr size_type Write( size_type byteOffset, bool value ) noexcept
        {
            *( data( ) + byteOffset ) = value?1:0;
            return byteOffset + 1;
        }

        constexpr size_type Write( size_type byteOffset, char value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            return byteOffset + 1;
        }

        constexpr size_type Write( size_type byteOffset, SByte value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>(value);
            return byteOffset + 1;
        }
        constexpr size_type Write( size_type byteOffset, Byte value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            return byteOffset + 1;
        }

        constexpr size_type Write( size_type byteOffset, Int16 value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( value >> 8 );
            return byteOffset + 2;
        }
        constexpr size_type Write( size_type byteOffset, UInt16 value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( value >> 8 );
            return byteOffset + 2;
        }

        constexpr size_type Write( size_type byteOffset, wchar_t value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( value >> 8 );
            return byteOffset + 2;
        }

        constexpr size_type Write( size_type byteOffset, Int32 value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( value >> 8 );
            *( data( ) + byteOffset + 2 ) = static_cast<Byte>( value >> 16 );
            *( data( ) + byteOffset + 3 ) = static_cast<Byte>( value >> 24 );
            return byteOffset + 4;
        }
        constexpr size_type Write( size_type byteOffset, UInt32 value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( value >> 8 );
            *( data( ) + byteOffset + 2 ) = static_cast<Byte>( value >> 16 );
            *( data( ) + byteOffset + 3 ) = static_cast<Byte>( value >> 24 );
            return byteOffset + 4;
        }

        constexpr size_type Write( size_type byteOffset, long value ) noexcept
        {
            return Write( byteOffset, static_cast<Int32>(value) );
        }
        constexpr size_type Write( size_type byteOffset, unsigned long value ) noexcept
        {
            return Write( byteOffset, static_cast<UInt32>( value ) );
        }

        constexpr size_type Write( size_type byteOffset, Int64 value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( value >> 8 );
            *( data( ) + byteOffset + 2 ) = static_cast<Byte>( value >> 16 );
            *( data( ) + byteOffset + 3 ) = static_cast<Byte>( value >> 24 );
            *( data( ) + byteOffset + 4 ) = static_cast<Byte>( value >> 32 );
            *( data( ) + byteOffset + 5 ) = static_cast<Byte>( value >> 40 );
            *( data( ) + byteOffset + 6 ) = static_cast<Byte>( value >> 48 );
            *( data( ) + byteOffset + 7 ) = static_cast<Byte>( value >> 56 );
            return byteOffset + 8;
        }

        constexpr size_type Write( size_type byteOffset, UInt64 value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( value >> 8 );
            *( data( ) + byteOffset + 2 ) = static_cast<Byte>( value >> 16 );
            *( data( ) + byteOffset + 3 ) = static_cast<Byte>( value >> 24 );
            *( data( ) + byteOffset + 4 ) = static_cast<Byte>( value >> 32 );
            *( data( ) + byteOffset + 5 ) = static_cast<Byte>( value >> 40 );
            *( data( ) + byteOffset + 6 ) = static_cast<Byte>( value >> 48 );
            *( data( ) + byteOffset + 7 ) = static_cast<Byte>( value >> 56 );
            return byteOffset + 8;
        }
        constexpr size_type Write( size_type byteOffset, float value ) noexcept
        {
            return Write( byteOffset, std::bit_cast<UInt32>( value ) );
        }
        constexpr size_type Write( size_type byteOffset, double value ) noexcept
        {
            return Write( byteOffset, std::bit_cast<UInt64>( value ) );
        }
        constexpr size_type Write( size_type byteOffset, TimeSpan value ) noexcept
        {
            return Write( byteOffset, std::bit_cast<UInt64>( value ) );
        }
        constexpr size_type Write( size_type byteOffset, DateTime value ) noexcept
        {
            return Write( byteOffset, std::bit_cast<UInt64>( value ) );
        }
        constexpr size_type Write( size_type byteOffset, Currency value ) noexcept
        {
            return Write( byteOffset, std::bit_cast<UInt64>( value ) );
        }

        constexpr size_type Write( size_type byteOffset, GUID value ) noexcept
        {
            *( data( ) + byteOffset ) = static_cast<Byte>( value.Data1 );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( value.Data1 >> 8 );
            *( data( ) + byteOffset + 2 ) = static_cast<Byte>( value.Data1 >> 16 );
            *( data( ) + byteOffset + 3 ) = static_cast<Byte>( value.Data1 >> 24 );
            *( data( ) + byteOffset + 4 ) = static_cast<Byte>( value.Data2 );
            *( data( ) + byteOffset + 5 ) = static_cast<Byte>( value.Data2 >> 8 );
            *( data( ) + byteOffset + 6 ) = static_cast<Byte>( value.Data3 );
            *( data( ) + byteOffset + 7 ) = static_cast<Byte>( value.Data3 >> 8 );
            *( data( ) + byteOffset + 8 ) = static_cast<Byte>( value.Data4[0] );
            *( data( ) + byteOffset + 9 ) = static_cast<Byte>( value.Data4[1] );
            *( data( ) + byteOffset + 10 ) = static_cast<Byte>( value.Data4[2] );
            *( data( ) + byteOffset + 11 ) = static_cast<Byte>( value.Data4[3] );
            *( data( ) + byteOffset + 12 ) = static_cast<Byte>( value.Data4[4] );
            *( data( ) + byteOffset + 13 ) = static_cast<Byte>( value.Data4[5] );
            *( data( ) + byteOffset + 14 ) = static_cast<Byte>( value.Data4[6] );
            *( data( ) + byteOffset + 15 ) = static_cast<Byte>( value.Data4[7] );
            return byteOffset + 16;
        }
        constexpr size_type Write( size_type byteOffset, Guid value ) noexcept
        {
            const GUID& val = value;
            *( data( ) + byteOffset ) = static_cast<Byte>( val.Data1 );
            *( data( ) + byteOffset + 1 ) = static_cast<Byte>( val.Data1 >> 8 );
            *( data( ) + byteOffset + 2 ) = static_cast<Byte>( val.Data1 >> 16 );
            *( data( ) + byteOffset + 3 ) = static_cast<Byte>( val.Data1 >> 24 );
            *( data( ) + byteOffset + 4 ) = static_cast<Byte>( val.Data2 );
            *( data( ) + byteOffset + 5 ) = static_cast<Byte>( val.Data2 >> 8 );
            *( data( ) + byteOffset + 6 ) = static_cast<Byte>( val.Data3 );
            *( data( ) + byteOffset + 7 ) = static_cast<Byte>( val.Data3 >> 8 );
            *( data( ) + byteOffset + 8 ) = static_cast<Byte>( val.Data4[0] );
            *( data( ) + byteOffset + 9 ) = static_cast<Byte>( val.Data4[1] );
            *( data( ) + byteOffset + 10 ) = static_cast<Byte>( val.Data4[2] );
            *( data( ) + byteOffset + 11 ) = static_cast<Byte>( val.Data4[3] );
            *( data( ) + byteOffset + 12 ) = static_cast<Byte>( val.Data4[4] );
            *( data( ) + byteOffset + 13 ) = static_cast<Byte>( val.Data4[5] );
            *( data( ) + byteOffset + 14 ) = static_cast<Byte>( val.Data4[6] );
            *( data( ) + byteOffset + 15 ) = static_cast<Byte>( val.Data4[7] );
            return byteOffset + 16;
        }

        template<typename E>
            requires std::is_enum_v<E>
        constexpr size_type Write( size_type byteOffset, E value ) noexcept
        {
            return Write( byteOffset, static_cast<std::underlying_type_t<E>>( value ) );
        }

        template<typename T, size_t N>
        constexpr size_type Write( size_type byteOffset, T (&array)[N] ) noexcept
        {
            auto result = byteOffset;
            for ( size_t i = 0; i < N; ++i )
            {
                result = Write( result, array[i] );
            }
            return result;
        }
        template<typename T, size_t N>
        constexpr size_type Write( size_type byteOffset, const std::array<T,N>& array ) noexcept
        {
            auto result = byteOffset;
            for ( size_t i = 0; i < N; ++i )
            {
                result = Write( result, array[i] );
            }
            return result;
        }




        template<typename Arg, typename ...Args>
        constexpr size_type Write( size_type byteOffset, Arg&& arg, Args&& ... args ) noexcept
        {
            auto offset = Write( byteOffset, std::forward<Arg>( arg ) );
            auto result = Write( offset, std::forward<Args>( args )... );
            return result;
        }

        constexpr size_type Write7BitEncoded( size_type byteOffset, UInt64 value ) noexcept
        {
            auto encodedSize = Write7BitEncodedValue( value, data( ) + byteOffset );
            return byteOffset + encodedSize;
        }

        constexpr size_type Write7BitEncoded_( size_type byteOffset, UInt64 value ) noexcept
        {
            return Core::Write7BitEncodedValue( value, data( ) + byteOffset );
        }

    };

    



    template <typename ...Args>
    ByteArray( Args... )->ByteArray< Internal::_ByteSizeOf_v<Args...> >;

    template<size_t N>
    inline constexpr ByteArray<N> Write7BitEncodedValue( UInt64 value ) noexcept
    {
        ByteArray<N> result;
        Write7BitEncodedValue( value, result.data( ) );
        return result;
    }


    template<size_t N>
    inline constexpr UInt64 Read7BitEncodedValue( const ByteArray<N>& byteArray ) noexcept
    {
        UInt64 result = 0;
        Read7BitEncodedValue( byteArray.data( ), 0, result );
        return result;
    }

    template<UInt64 N>
    struct SevenBitEncode
    {
        static constexpr size_t Size = SizeOf7BitEncoded_v<N>;
        using type = ByteArray<Size>;
    private:
        static constexpr type Encode( )
        {
            type v;
            v.Write7BitEncoded( 0, N );
            return v;
        }
    public:
        static constexpr type value = Encode( );

    };


    template<typename T>
    struct SevenBitDecode
    {
        static constexpr UInt64 value = Read7BitEncodedValue( T::value );
    };

    template<size_t N, bool networkByteOrder = false, bool use7BitEncodedSize = true>
    class ArrayReader
    {
    public:
        using Data = ByteArray<N>;
        static constexpr bool NetworkByteOrder = networkByteOrder;
        static constexpr bool Use7BitEncodedSize = use7BitEncodedSize;
        using PersistedSizeType = UInt32;
    private:
        size_t offset_ = 0;
        const Data* data_ = nullptr;
    public:
        constexpr ArrayReader( const Data* data ) noexcept
            : data_( data )
        { }

        size_t ReadSize( )
        {
            if constexpr ( Use7BitEncodedSize )
            {
                size_t size = Read7BitEncoded( );
                return size;
            }
            else
            {
                auto size = static_cast<size_t>( Read<UInt32>( ) );
                return size;
            }
        }

        template<typename T>
            requires IsInteger<T>
        constexpr std::remove_cvref_t<T> Read7BitEncoded( ) noexcept
        {
            using IntType = std::remove_cvref_t<T>;
            IntType result = 0;
            size_t encodedSize = Core::Read7BitEncodedValue( data_->data( ), offset_, result );
            offset_ += encodedSize;
            return result;
        }

        template<typename T>
            requires IsBasicType<T>
        constexpr std::remove_cvref_t<T> Read( ) noexcept
        { 
            using Type = std::remove_cvref_t<T>;
            Type result = data_->Read<Type>( offset_ );
            offset_ += sizeof( T );
            return result;
        }

        template<typename T>
            requires IsBasicType<T>
        constexpr void Read( T& value ) noexcept
        { 
            using Type = std::remove_cvref_t<T>;
            value = data_->Read<Type>( offset_ );
            offset_ += sizeof( T );
        }

        template<>
        constexpr void Read( long& value ) noexcept
        { 
            value = data_->Read<Int32>( offset_ );
            offset_ += sizeof( Int32 );
        }
        template<>
        constexpr void Read( unsigned long& value ) noexcept
        {
            value = data_->Read<UInt32>( offset_ );
            offset_ += sizeof( UInt32 );
        }


    };


    template<size_t N, bool networkByteOrder = false, bool use7BitEncodedSize = true>
    class ArrayWriter
    {
    public:
        using Data = ByteArray<N>;
        static constexpr bool NetworkByteOrder = networkByteOrder;
        static constexpr bool Use7BitEncodedSize = use7BitEncodedSize;
        using PersistedSizeType = UInt32;
    private:
        size_t offset_ = 0;
        Data* data_ = nullptr;
    public:
        constexpr ArrayWriter( Data* data ) noexcept
            : data_( data )
        {
        }

        void WriteSize( size_t size )
        {
            if constexpr ( Use7BitEncodedSize )
            {
                Write7BitEncoded( size );
            }
            else if constexpr ( NetworkByteOrder )
            {
                UInt32 sz = ByteSwap( static_cast<UInt32>( size ) );
                offset_ = data_->Write( offset_, sz );
            }
            else
            {
                UInt32 sz = static_cast<UInt32>( size );
                offset_ = data_->Write( offset_, sz );
            }
        }

        template<typename T>
        void Write7BitEncoded( UInt64 value )
        {
            offset_ = data_->Write7BitEncoded( offset_, value );
        }


        template<typename T>
        void Write( const T& value )
        {
            offset_ = data_->Write( offset_, value );
        }
    };



}
#pragma pack(pop)

#endif
