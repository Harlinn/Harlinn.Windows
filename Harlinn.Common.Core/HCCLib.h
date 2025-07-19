#pragma once
#ifndef __HCCLIB_H__
#define __HCCLIB_H__
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

#include <HCCDef.h>
#include <HCCTraits.h>


#include <Harlinn/Common/Utils.h>


#define HCCLIB_IMPLEMENTS_ROUND 1
#define HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP 1
#define HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC 1



namespace Harlinn::Common::Core
{
    using Harlinn::Common::ByteSwap;


    template<typename T>
    inline constexpr bool IsGUID = std::is_same_v<std::remove_cv_t<T>, GUID>;

    /// <summary>
    /// Swaps the bytes of the Data1, Data2 and Data3 fields
    /// of a Guid or GUID, while leaving Data4 as it is. 
    /// </summary>
    /// <typeparam name="T">Guid or GUID</typeparam>
    /// <param name="guid">A GUID type.</param>
    /// <returns>
    /// The GUID type with the bytes swapped.
    /// </returns>
    template<typename T>
        requires IsGUID<T>
    inline constexpr T ByteSwap( const T& guid ) noexcept
    {
        return GUID{ ByteSwap( guid.Data1 ), ByteSwap( guid.Data2 ), ByteSwap( guid.Data3 ), { guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] } };
    }


    [[nodiscard]] inline char ToUpper( char c ) noexcept
    {
#pragma warning(push)
#pragma warning(disable:4302)
        return ( char )CharUpperA( ( ( LPSTR )( c ) ) );
#pragma warning(pop)
    }
    [[nodiscard]] inline wchar_t ToUpper( wchar_t c ) noexcept
    {
#pragma warning(push)
#pragma warning(disable:4302)
        return ( wchar_t )CharUpperW( ( ( LPWSTR )( c ) ) );
#pragma warning(pop)
    }
    [[nodiscard]] inline char ToLower( char c ) noexcept
    {
#pragma warning(push)
#pragma warning(disable:4302)
        return ( char )CharLowerA( ( ( LPSTR )( c ) ) );
#pragma warning(pop)
    }
    [[nodiscard]] inline wchar_t ToLower( wchar_t c ) noexcept
    {
#pragma warning(push)
#pragma warning(disable:4302)
        return ( wchar_t )CharLowerW( ( ( LPWSTR )( c ) ) );
#pragma warning(pop)
    }

    inline void ToUpper( char* s )
    {
        CharUpperA( s );
    }

    inline void ToUpper( wchar_t* s )
    {
        CharUpperW( s );
    }

    inline void ToLower( char* s )
    {
        CharLowerA( s );
    }

    inline void ToLower( wchar_t* s )
    {
        CharLowerW( s );
    }

    inline void ToUpper( char* s, size_t size )
    {
        CharUpperBuffA( s, static_cast< DWORD >( size ) );
    }

    inline void ToUpper( wchar_t* s, size_t size )
    {
        CharUpperBuffW( s, static_cast< DWORD >( size ) );
    }

    inline void ToLower( char* s, size_t size )
    {
        CharLowerBuffA( s, static_cast< DWORD >( size ) );
    }

    inline void ToLower( wchar_t* s, size_t size )
    {
        CharLowerBuffW( s, static_cast< DWORD >( size ) );
    }


    [[nodiscard]] inline char* MemIChr( char* buffer, int value, size_t bufferSize ) noexcept
    {
        auto lowerValue = ToLower( static_cast< char >( value ) );
        auto ptr = buffer;
        auto endPtr = buffer + bufferSize;
        while ( ptr < endPtr )
        {
            if ( ToLower( static_cast< char >( *ptr ) ) == lowerValue )
            {
                return ptr;
            }
            ptr++;
        }
        return nullptr;
    }
    [[nodiscard]] inline const char* MemIChr( const char* buffer, int value, size_t bufferSize ) noexcept
    {
        auto lowerValue = ToLower( static_cast< char >( value ) );
        auto ptr = buffer;
        auto endPtr = buffer + bufferSize;
        while ( ptr < endPtr )
        {
            if ( ToLower( static_cast< char >( *ptr ) ) == lowerValue )
            {
                return ptr;
            }
            ptr++;
        }
        return nullptr;
    }
    [[nodiscard]] inline wchar_t* MemIChr( wchar_t* buffer, int value, size_t bufferSize ) noexcept
    {
        auto lowerValue = ToLower( static_cast< wchar_t >( value ) );
        auto ptr = buffer;
        auto endPtr = buffer + bufferSize;
        while ( ptr < endPtr )
        {
            if ( ToLower( static_cast< wchar_t >( *ptr ) ) == lowerValue )
            {
                return ptr;
            }
            ptr++;
        }
        return nullptr;
    }
    [[nodiscard]] inline const wchar_t* MemIChr( const wchar_t* buffer, int value, size_t bufferSize ) noexcept
    {
        auto lowerValue = ToLower( static_cast< wchar_t >( value ) );
        auto ptr = buffer;
        auto endPtr = buffer + bufferSize;
        while ( ptr < endPtr )
        {
            if ( ToLower( static_cast< wchar_t >( *ptr ) ) == lowerValue )
            {
                return ptr;
            }
            ptr++;
        }
        return nullptr;
    }





    template<typename T1, typename T2>
        requires ((std::is_same_v<Guid, std::remove_cvref_t<T1>> || std::is_same_v<GUID, std::remove_cvref_t<T1>> ) &&
                ( std::is_same_v<Guid, std::remove_cvref_t<T2>> || std::is_same_v<GUID, std::remove_cvref_t<T2>> ) )
    constexpr inline int Compare( const T1& v1, const T2& v2 ) noexcept
    {
        return reinterpret_cast<const Guid&>(v1).CompareTo( reinterpret_cast< const Guid& >( v2 ) );
    }


    template<typename FirstT, typename SecondT >
        requires requires( FirstT f, SecondT s )
        { 
            { Compare( f, s ) } ->std::convertible_to<int>;
        }
    inline int Compare( const FirstT* first, size_t firstLength, const SecondT* second, size_t secondLength )
    {
        auto compareSize = std::min( firstLength, secondLength );
        for ( size_t i = 0; i < compareSize; i++ )
        {
            auto result = Compare(first[i], second[i] );
            if ( result )
            {
                return result;
            }
        }
        if ( firstLength == secondLength )
        {
            return 0;
        }
        else if ( firstLength < secondLength )
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    template<typename FirstT, typename SecondT, typename ConversionFunc >
        requires requires( FirstT f, SecondT s, ConversionFunc func )
        {
            { Compare( f, s ) } ->std::convertible_to<int>;
            { func(s) } ->std::convertible_to<FirstT>;
        }
    inline int Compare( const FirstT* first, size_t firstLength, const SecondT* second, size_t secondLength, ConversionFunc converter )
    {
        auto compareSize = std::min( firstLength, secondLength );
        for ( size_t i = 0; i < compareSize; i++ )
        {
            auto result = Compare( first[ i ], converter( second[ i ] ) );
            if ( result )
            {
                return result;
            }
        }
        if ( firstLength == secondLength )
        {
            return 0;
        }
        else if ( firstLength < secondLength )
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    template<typename FirstT, typename SecondT, typename CompareFunc >
        requires requires( FirstT f, SecondT s, CompareFunc func )
    {
        { func( f, s ) } ->std::convertible_to<int>;
    }
    inline int CompareEx( const FirstT* first, size_t firstLength, const SecondT* second, size_t secondLength, CompareFunc compare )
    {
        auto compareSize = std::min( firstLength, secondLength );
        for ( size_t i = 0; i < compareSize; i++ )
        {
            auto result = compare( first[ i ], second[ i ] );
            if ( result )
            {
                return result;
            }
        }
        if ( firstLength == secondLength )
        {
            return 0;
        }
        else if ( firstLength < secondLength )
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }





    template<SimpleSpanLike T1, SimpleSpanLike T2, typename ConversionFunc >
    inline int Compare( const T1& first, const T2& second, ConversionFunc converter )
    {
        return Compare( first.data( ), first.size( ), second.data( ), second.size( ), converter );
    }

    template<SimpleSpanLike T1, SimpleSpanLike T2 >
        requires (std::is_same_v< typename T1::value_type, typename T2::value_type > && ( IsBasicString<T1> == false ) )
    inline int Compare( const T1& first, const T2& second )
    {
        return Compare( first.data( ), first.size( ), second.data( ), second.size( ) );
    }


    class XXH64Hasher
    {
    public:
        using HashType = XXH64_hash_t;
        using StateType = XXH64_state_t;
        using CanonicalType = XXH64_canonical_t;
        using ErrorCode = XXH_errorcode;
    private:
        StateType state_{};
    public:
        XXH64Hasher( HashType seed = 0)
        {
            Reset( seed );
        }

        XXH64Hasher( const XXH64Hasher& other ) = delete;
        XXH64Hasher( XXH64Hasher&& other ) = delete;

        ~XXH64Hasher( )
        {
        }

        XXH64Hasher& operator =( const XXH64Hasher& other ) = delete;
        XXH64Hasher& operator =( XXH64Hasher&& other ) = delete;

        ErrorCode Reset( HashType seed = 0 )
        {
            return XXH64_reset( &state_, seed );
        }

        HashType Digest( )
        {
            return XXH64_digest( &state_ );
        }

        void Update( const void* input, size_t length )
        {
            XXH64_update( &state_, input, length );
        }

        template<typename T>
            requires std::is_same_v<T,bool>
                void Add( T value )
        {
                
            Byte v = value ? 1 : 0;
            Update( &v, 1 );
        }
        template<typename T>
            requires (std::is_integral_v<T> && ( std::is_same_v<T, bool> == false ) ) || std::is_floating_point_v<T>
        void Add( T value )
        {
            Update( &value, sizeof(T) );
        }
        template<typename T>
            requires std::is_same_v<DateTime, std::remove_cvref_t<T>> ||
                std::is_same_v<TimeSpan, std::remove_cvref_t<T>> ||
                std::is_same_v<Currency, std::remove_cvref_t<T>> ||
                std::is_same_v<Guid, std::remove_cvref_t<T>>
        void Add( T value )
        {
            Update( &value, sizeof( std::remove_cvref_t<T> ) );
        }


        void Add( const Byte* value, size_t size )
        {
            if ( size )
            {
                Update( value, size );
            }
        }

        template<typename T>
            requires std::is_same_v<char,T> || std::is_same_v<wchar_t, T>
        void Add( const T* value, size_t size )
        {
            if ( size )
            {
                Update( value, size * sizeof( T ) );
            }
        }

        template<SimpleStringLike StringT>
        void Add( const StringT& str )
        {
            auto size = str.size( );
            if ( size )
            {
                Add( static_cast< const Byte* >( str.c_str( ) ), size * sizeof( typename StringT::value_type ) );
            }
        }

        template<typename T>
        void Add( const std::basic_string_view<T>& str )
        {
            auto size = str.size( );
            if ( size )
            {
                Add( reinterpret_cast< const Byte* >( str.data( ) ), size * sizeof( T ) );
            }
        }
        


        template<typename T>
            requires std::is_same_v<char,T> || std::is_same_v<wchar_t, T>
        void Add( const T* value )
        {
            if ( value )
            {
                auto size = LengthOf( value );
                Update( value, size * sizeof( T ) );
            }
        }

    };


    template<typename CharType>
    bool HexToBinary( CharType c, Byte& result )
    {
        if ( c >= static_cast<CharType>( '0' ) && c <= static_cast<CharType>( '9' ) )
        {
            result = static_cast<Byte>( c ) - static_cast<Byte>( '0' );
            return true;
        }
        else if ( c >= static_cast<CharType>( 'a' ) && c <= static_cast<CharType>( 'f' ) )
        {
            result = (static_cast<Byte>( c ) - static_cast<Byte>( 'a' )) + 10;
            return true;
        }
        else if ( c >= static_cast<CharType>( 'A' ) && c <= static_cast<CharType>( 'F' ) )
        {
            result = ( static_cast<Byte>( c ) - static_cast<Byte>( 'A' ) ) + 10;
            return true;
        }
        else
        {
            return false;
        }

    }
    
    template<typename CharType>
    inline bool HexToBinary( const CharType* text, size_t textLength, std::vector<Byte>& result )
    {
        if ( ( textLength % 2 ) == 0 )
        {
            const CharType* textEnd = text + textLength;
            size_t binaryLength = textLength / 2;
            result.clear( );
            result.resize( binaryLength );
            size_t i = 0;
            while ( text < textEnd )
            {
                Byte msn;
                if ( HexToBinary( *text, msn ) )
                {
                    text++;
                    Byte lsn;
                    if ( HexToBinary( *text, lsn ) )
                    {
                        text++;
                        result[i] = ( msn << 4 ) | lsn;
                        i++;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    /// <summary>
    /// Extracts a plain pointer from a smart pointer
    /// </summary>
    template <typename PointerT>
    inline constexpr [[nodiscard]] auto UnwrapPointer( const PointerT& pointer ) noexcept
    { 
        return std::addressof( *pointer );
    }
    /// <summary>
    /// Extracts a plain pointer from a smart pointer
    /// </summary>
    template <typename PointerT>
    inline constexpr [[nodiscard]] auto UnwrapPointer( PointerT& pointer ) noexcept
    {
        return std::addressof( *pointer );
    }

    /// <summary>
    /// ensure no conversion for regular pointers
    /// </summary>
    template <typename T>
    inline constexpr [[nodiscard]] T* UnwrapPointer( T* pointer ) noexcept
    { 
        return pointer;
    }


    template <typename PointerT, std::enable_if_t<!std::is_pointer_v<PointerT>, int> = 0>
    inline constexpr [[nodiscard]] PointerT WrapPointer( typename std::pointer_traits<PointerT>::element_type* pointer ) noexcept
    {
        return std::pointer_traits<PointerT>::pointer_to( *pointer );
    }

    /// <summary>
    /// ensure no conversion for regular pointers
    /// </summary>
    template <typename PointerT, std::enable_if_t<std::is_pointer_v<PointerT>, int> = 0>
    inline constexpr [[nodiscard]] PointerT WrapPointer( PointerT pointer ) noexcept
    {
        return pointer;
    }


    namespace Atomic
    {
        template<typename T>
            requires std::is_same_v<T,SByte> || std::is_same_v<T, Byte> || std::is_same_v<T, char>
        inline T Increment( volatile T* value )
        {
            char previousValue;
            do
            {
                previousValue = std::bit_cast<char>(*value);
            } while ( _InterlockedCompareExchange8( reinterpret_cast<volatile char*>(value), previousValue + 1, previousValue ) != previousValue );
            return std::bit_cast< T >( previousValue + 1 );
        }
        template<typename T>
            requires std::is_same_v<T, SByte> || std::is_same_v<T, Byte> || std::is_same_v<T, char>
        inline T Decrement( volatile T* value )
        {
            char previousValue;
            do
            {
                previousValue = std::bit_cast< char >( *value );
            } while ( _InterlockedCompareExchange8( reinterpret_cast< volatile char* >( value ), previousValue - 1, previousValue ) != previousValue );
            return std::bit_cast<T>( previousValue - 1 );
        }

        template<typename T>
            requires std::is_same_v<T, Int16> || std::is_same_v<T, UInt16>
        inline T Increment( volatile T* value )
        {
            return std::bit_cast< T >( _InterlockedIncrement16( reinterpret_cast< volatile short* >( value ) ) );
        }
        template<typename T>
            requires std::is_same_v<T, Int16> || std::is_same_v<T, UInt16>
        inline T Decrement( volatile T* value )
        {
            return std::bit_cast< T >( _InterlockedDecrement16( reinterpret_cast< volatile short* >( value ) ) );
        }

        template<typename T>
            requires std::is_same_v<T, Int32> || std::is_same_v<T, UInt32> || std::is_same_v<T, long> || std::is_same_v<T, unsigned long>
        inline T Increment( volatile T* value )
        {
            return std::bit_cast< T >( _InterlockedIncrement( reinterpret_cast< volatile unsigned int* >( value ) ) );
        }
        template<typename T>
            requires std::is_same_v<T, Int32> || std::is_same_v<T, UInt32> || std::is_same_v<T, long> || std::is_same_v<T, unsigned long>
        inline T Decrement( volatile T* value )
        {
            return std::bit_cast< T >( _InterlockedDecrement( reinterpret_cast< volatile unsigned int* >( value ) ) );
        }

        template<typename T>
            requires std::is_same_v<T, Int64> || std::is_same_v<T, UInt64> 
        inline T Increment( volatile T* value )
        {
            return std::bit_cast< T >( _InterlockedIncrement64( reinterpret_cast< volatile short* >( value ) ) );
        }
        template<typename T>
            requires std::is_same_v<T, Int64> || std::is_same_v<T, UInt64>
        inline T Decrement( volatile T* value )
        {
            return std::bit_cast< T >( _InterlockedDecrement64( reinterpret_cast< volatile short* >( value ) ) );
        }

        template<typename T>
            requires std::is_same_v<T, SByte> || std::is_same_v<T, Byte> || std::is_same_v<T, char>
        inline T Load( const volatile T* value )
        {
            return std::bit_cast< T >( __iso_volatile_load8( reinterpret_cast< const volatile __int8* >( value ) ) );
        }
        template<typename T>
            requires std::is_same_v<T, SByte> || std::is_same_v<T, Byte> || std::is_same_v<T, char>
        void Store( volatile T* location, T value )
        {
            __iso_volatile_store8( reinterpret_cast< volatile __int8* >( location ), std::bit_cast<__int8>( value ) );
        }

        template<typename T>
            requires std::is_same_v<T, Int16> || std::is_same_v<T, UInt16>
        inline T Load( const volatile T* value )
        {
            return std::bit_cast< T >( __iso_volatile_load16( reinterpret_cast< const volatile __int16* >( value ) ) );
        }
        template<typename T>
            requires std::is_same_v<T, Int16> || std::is_same_v<T, UInt16>
        void Store( volatile T* location, T value )
        {
            __iso_volatile_store16( reinterpret_cast< volatile __int16* >( location ), std::bit_cast< __int16 >( value ) );
        }

        template<typename T>
            requires std::is_same_v<T, Int32> || std::is_same_v<T, UInt32> || std::is_same_v<T, long> || std::is_same_v<T, unsigned long>
        inline T Load( const volatile T* value )
        {
            return std::bit_cast< T >( __iso_volatile_load32( reinterpret_cast< const volatile __int32* >( value ) ) );
        }
        template<typename T>
            requires std::is_same_v<T, Int32> || std::is_same_v<T, UInt32> || std::is_same_v<T, long> || std::is_same_v<T, unsigned long>
        void Store( volatile T* location, T value )
        {
            __iso_volatile_store32( reinterpret_cast< volatile __int32* >( location ), std::bit_cast< __int32 >( value ) );
        }

        template<typename T>
            requires std::is_same_v<T, Int64> || std::is_same_v<T, UInt64>
        inline T Load( const volatile T* value )
        {
            return std::bit_cast< T >( __iso_volatile_load64( reinterpret_cast< const volatile __int64* >( value ) ) );
        }
        template<typename T>
            requires std::is_same_v<T, Int64> || std::is_same_v<T, UInt64>
        void Store( volatile T* location, T value )
        {
            __iso_volatile_store64( reinterpret_cast< volatile __int64* >( location ), std::bit_cast< __int64 >( value ) );
        }
    }


    template<typename T>
        requires std::is_integral_v<T>
    class AtomicReferenceCount
    {
    public:
        using value_type = T;
    private:
        value_type referenceCount_{ static_cast< value_type >( 0 ) };
    public:
        constexpr AtomicReferenceCount( ) = default;
            
        explicit constexpr AtomicReferenceCount( value_type initialValue )
            : referenceCount_( initialValue )
        {}

        /// <summary>
        /// Increments the reference count by 1.
        /// </summary>
        /// <returns>Returns the resulting incremented value.</returns>
        value_type Increment( ) 
        { 
            return Atomic::Increment( &referenceCount_ );
        }

        /// <summary>
        /// Decrements the reference count by 1. 
        /// </summary>
        /// <returns>Returns the resulting decremented value.</returns>
        value_type Decrement( )
        {
            return Atomic::Decrement( &referenceCount_ );
        }

        /// <summary>
        /// Tests if the reference count is 1. By convention the calling thread owns 
        /// the reference, and no other thread should alter the state of the
        /// reference counted object.
        /// </summary>
        /// <returns>true if the reference count is 1, otherwise false.</returns>
        bool IsOne( ) const 
        { 
            return Atomic::Load( &referenceCount_ ) == 1;
        }

        /// <summary>
        /// Tests if the reference count is zero. By convention any
        /// object with a reference count of 0 will be destroyed.
        /// </summary>
        /// <returns>true if the reference count is 0, otherwise false.</returns>
        bool IsZero( ) const
        {
            return Atomic::Load( &referenceCount_ ) == 0;
        }
    };


    class ReferenceCounted
    {
        mutable UInt32 referenceCount_ = 1;
    public:
        constexpr ReferenceCounted( ) = default;
            
        ReferenceCounted( const ReferenceCounted& ) = delete;
        ReferenceCounted& operator=( const ReferenceCounted& ) = delete;

        bool HasOneRef( ) const { return referenceCount_ == 1; }
        bool HasAtLeastOneRef( ) const { return referenceCount_ >= 1; }

        virtual ~ReferenceCounted( ) = default;

        UInt32 AddRef( ) const
        {
            return ++referenceCount_;
        }

        /// <summary>
        /// Returns zero if the object was destroyed.
        /// </summary>
        /// <returns>zero if the object was destroyed.</returns>
        UInt32 Release( ) const
        {
            auto result = --referenceCount_;
            if ( result == 0 )
            {
                delete this;
            }
            return result;
        }
    };
    static_assert( SimpleComLike<ReferenceCounted> );

    class ReferenceCountedThreadSafe
    {
        mutable AtomicReferenceCount<UInt32> referenceCount_{1};
    public:
        explicit constexpr ReferenceCountedThreadSafe( ) = default;
        ReferenceCountedThreadSafe( const ReferenceCountedThreadSafe& ) = delete;
        ReferenceCountedThreadSafe& operator=( const ReferenceCountedThreadSafe& ) = delete;

        bool HasOneRef( ) const
        {
            return referenceCount_.IsOne( );
        }
        bool HasAtLeastOneRef( ) const
        {
            return referenceCount_.IsZero() == false;
        }
        
        virtual ~ReferenceCountedThreadSafe( ) = default;

        UInt32 AddRef( ) const
        {
            return referenceCount_.Increment( );
        }

        /// <summary>
        /// Returns zero if the object was destroyed.
        /// </summary>
        /// <returns>zero if the object was destroyed.</returns>
        UInt32 Release( ) const
        { 
            auto result = referenceCount_.Decrement( );
            if ( result == 0 )
            {
                delete this;
            }
            return result;
        }
    };
    static_assert( SimpleComLike<ReferenceCountedThreadSafe> );
    

    template<typename T>
    class ReferenceCountedData : public ReferenceCountedThreadSafe
    {
    public:
        using Base = ReferenceCountedThreadSafe;
        using value_type = T;
    private:
        value_type data_;
    public:
        template<typename... Args >
            requires std::is_constructible_v< value_type, Args...>
        ReferenceCountedData( Args&& ... args )
            : data_( std::forward<Args>( args )... )
        {
        }

        const value_type& Data( ) const
        {
            return data_;
        }
        value_type& Data( )
        {
            return data_;
        }

        void Assign( const value_type& data )
        {
            data_ = data;
        }
        void Assign( value_type&& data )
        {
            data_ = std::move(data);
        }

    };
    

    template<typename ValueT>
    class ReferenceCountedPtr
    {
        template<typename U>
        friend class ReferenceCountedPtr;
    public:
        using ValueType = ValueT;
        using value_type = ValueT;
    private:
        ValueType* pointer_ = nullptr;
    public:
        constexpr ReferenceCountedPtr( ) noexcept = default;

        explicit ReferenceCountedPtr( ValueType* pointer, bool addRef = false ) noexcept
            : pointer_( pointer )
        {
            if ( addRef && ( pointer_ != nullptr ) )
            {
                pointer_->AddRef( );
            }
        }

        ReferenceCountedPtr( const ReferenceCountedPtr& other ) noexcept
            : pointer_( other.pointer_ )
        {
            if ( pointer_ )
            {
                pointer_->AddRef( );
            }
        }

        ReferenceCountedPtr( ReferenceCountedPtr&& other ) noexcept
            : pointer_( other.pointer_ )
        {
            if ( pointer_ )
            {
                other.pointer_ = nullptr;
            }
        }

        template<SimpleComLike U>
            requires ( std::is_base_of_v<ValueType, U> && std::is_same_v<ValueType, U> == false)
        ReferenceCountedPtr( const ReferenceCountedPtr<U>& other ) noexcept
            : pointer_( other.pointer_ )
        {
            if ( pointer_ )
            {
                pointer_->AddRef( );
            }
        }

        template<SimpleComLike U>
            requires ( std::is_base_of_v<ValueType, U>&& std::is_same_v<ValueType, U> == false )
        ReferenceCountedPtr( ReferenceCountedPtr<U>&& other ) noexcept
            : pointer_( other.pointer_ )
        {
            if ( pointer_ )
            {
                other.pointer_ = nullptr;
            }
        }

        ~ReferenceCountedPtr( ) noexcept
        {
            ValueType* tmp = pointer_;
            pointer_ = nullptr;
            if ( tmp )
            {
                tmp->Release( );
            }
        }

        constexpr operator bool( ) const noexcept
        {
            return pointer_ != nullptr;
        }

        template<SimpleComLike U>
            requires (std::is_base_of_v<ValueType, U> && std::is_same_v<ValueType, U> == false)
        ReferenceCountedPtr& operator = ( const ReferenceCountedPtr<U>& other ) 
        {
            if ( pointer_ != other.pointer_ )
            {
                if ( pointer_ )
                {
                    pointer_->Release( );
                }
                pointer_ = other.pointer_;
                if ( pointer_ )
                {
                    pointer_->AddRef( );
                }
            }
            return *this;
        }
        
        ReferenceCountedPtr& operator = ( const ReferenceCountedPtr& other )
        {
            if ( pointer_ != other.pointer_ )
            {
                if ( pointer_ )
                {
                    pointer_->Release( );
                }
                pointer_ = other.pointer_;
                if ( pointer_ )
                {
                    pointer_->AddRef( );
                }
            }
            return *this;
        }
        

        ReferenceCountedPtr& operator = ( ReferenceCountedPtr&& other ) noexcept
        {
            std::swap( pointer_, other.pointer_ );
            return *this;
        }

        void swap( ReferenceCountedPtr& other ) noexcept
        {
            std::swap( pointer_, other.pointer_ );
        }

        friend void swap( ReferenceCountedPtr& first, ReferenceCountedPtr& second ) noexcept
        {
            first.swap( second );
        }

        void ResetPtr( ValueType* other = nullptr, bool addRef = false ) noexcept
        {
            if ( pointer_ != other )
            {
                if ( pointer_ )
                {
                    pointer_->Release( );
                }
                pointer_ = other;
                if ( addRef && ( pointer_ != nullptr ) )
                {
                    pointer_->AddRef( );
                }
            }
        }

        ReferenceCountedPtr& operator = ( nullptr_t )
        {
            if ( pointer_ )
            {
                auto tmp = pointer_;
                pointer_ = nullptr;
                tmp->Release( );
            }
            return *this;
        }

        ValueType* Detach( )
        {
            auto tmp = pointer_;
            pointer_ = nullptr;
            return tmp;
        }

        ValueType* get( ) const
        {
            return pointer_;
        }


        constexpr bool operator == ( const ReferenceCountedPtr& other ) const noexcept
        {
            return pointer_ == other.pointer_;
        }
        constexpr bool operator != ( const ReferenceCountedPtr& other ) const noexcept
        {
            return pointer_ != other.pointer_;
        }

        constexpr bool operator == ( const ValueType* other ) const noexcept
        {
            return pointer_ == other;
        }
        constexpr bool operator != ( const ValueType* other ) const noexcept
        {
            return pointer_ != other;
        }

        ValueType* operator -> ( ) const noexcept
        {
            return ( ValueType* )pointer_;
        }
        std::add_lvalue_reference_t<ValueType> operator* ( ) const noexcept
        {
            return *pointer_;
        }
    };

    template<SimpleComLike T, typename... Args>
    inline ReferenceCountedPtr<T> MakeReferenceCounted( Args&& ... args )
    {
        T* obj = new T( std::forward<Args>( args )... );
        ReferenceCountedPtr<T> result( obj );
        return result;
    }

    template<SimpleComLike T>
    inline ReferenceCountedPtr<T> WrapReferenceCounted( T* ptr, bool addRef = false )
    {
        ReferenceCountedPtr<T> result( ptr, addRef );
        return result;
    }
}

namespace std
{

    template<Harlinn::Common::SimpleComLike ValueT>
    inline void swap( Harlinn::Common::Core::ReferenceCountedPtr<ValueT>& first, Harlinn::Common::Core::ReferenceCountedPtr<ValueT>& second ) noexcept
    {
        first.swap( second );
    }
}

#endif

