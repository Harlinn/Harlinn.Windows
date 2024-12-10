#pragma once
#ifndef __HCCLIB_H__
#define __HCCLIB_H__
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

#include <HCCDef.h>
#include <HCCTraits.h>
#include <HCCConcepts.h>

#define HCCLIB_IMPLEMENTS_ROUND 1
#define HCCLIB_IMPLEMENTS_MIN_MAX_CLAMP 1
#define HCCLIB_IMPLEMENTS_FLOOR_CEIL_TRUNC 1

namespace Harlinn::Common::Core::Logging
{
    /// <summary>
    /// Fully declared in HCCLoggerImpl.h
    /// </summary>
    class ThreadLogger;

    /// <summary>
    /// Passed to ThreadLogger::Flush,
    /// either directly or indirectly through
    /// CurrentThread::FlushLogger
    /// </summary>
    enum class FlushType
    {
        /// <summary>
        /// Normal flush operation
        /// </summary>
        Normal,
        /// <summary>
        /// Flush was called while the LogManager checks 
        /// each ThreadLogger for uncommitted data.
        /// </summary>
        Poll,
        /// <summary>
        /// Flush was called because the LogManager
        /// detected that the thread has exited.
        /// 
        /// In this case the Buffer will have its Final flag set.
        /// </summary>
        Final
    };
}


namespace Harlinn::Common::Core
{
#pragma pack(push,1)
    struct Bits8
    {
        Byte Value;
    };
    union Bits16
    {
        struct
        {
            Byte Low;
            Byte High;
        };
        UInt16 Value;
    };

    union Bits32
    {
        struct
        {
            Bits16 Low;
            Bits16 High;
        };
        UInt32 Value;
        Int32 Int32Value;
        Single SingleValue;
    };

    union Bits64
    {
        struct
        {
            Bits32 Low;
            Bits32 High;
        };
        UInt64 Value;
        Int64 Int64Value;
        Double DoubleValue;
    };

#pragma pack(pop)


    namespace Internal
    {
        template<typename T, std::size_t... N>
        inline constexpr T ByteSwapImpl( T value, std::index_sequence<N...> )
        {
            return ( ( ( ( value >> ( N * CHAR_BIT ) ) & (T)(unsigned char)( -1 ) )  << ( ( sizeof( T ) - 1 - N ) * CHAR_BIT ) ) | ... );
        };
    }
    template<typename T>
        requires IsInteger<std::remove_cvref_t<T>>
    inline constexpr T ByteSwap( T value )
    {
        if ( std::is_constant_evaluated( ) )
        {
            return std::bit_cast<T>( Internal::ByteSwapImpl(std::bit_cast<std::make_unsigned_t<T>>( value ),  std::make_index_sequence<sizeof( T )>( ) ) );
        }
        else
        {
            if constexpr ( sizeof( std::remove_cvref_t<T> ) == 1 )
            {
                return value;
            }
            else if constexpr ( sizeof( std::remove_cvref_t<T> ) == 2 )
            {
                return std::bit_cast<std::remove_cvref_t<T>>( 
                    _byteswap_ushort( std::bit_cast<UInt16>( value ) ) );
            }
            else if constexpr ( sizeof( std::remove_cvref_t<T> ) == 4 )
            {
                return std::bit_cast<std::remove_cvref_t<T>>( 
                    _byteswap_ulong( std::bit_cast<UInt32>( value ) ) );
            }
            else
            {
                return std::bit_cast<std::remove_cvref_t<T>>(
                    _byteswap_uint64( std::bit_cast<UInt64>( value ) ));
            }
        }
    }

    
    template<size_t N>
    struct BitMask
    {
        static_assert( N <= 64 && N > 0, "Unsupported bit-mask width" );
        using type = std::conditional_t
            <
            N <= 8, Byte,
            std::conditional_t
                <
                N <= 16, UInt16,
                std::conditional_t
                    <
                    N <= 32, UInt32,
                    UInt64
                    >    
                >
            >;
        static constexpr type value = (( static_cast<type>( 1 ) << ( N - 1 ) ) - 1) ^ ( static_cast<type>( 1 ) << ( N - 1 ) );
    };

    template<size_t N>
    inline constexpr auto BitMask_v = BitMask<N>::value;
    template<size_t N>
    using BitMask_t = typename BitMask<N>::type;

    /// <summary>
    /// Reverses the order of the bits of a byte.
    /// </summary>
    inline constexpr Byte ReverseBits( Byte b ) noexcept
    {
        /*
         * From: https://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64BitsDiv
         */
        b = static_cast<Byte>( ( static_cast<UInt64>(b) * 0x0202020202ULL & 0x010884422010ULL ) % 1023 );
        return b;
    }

    inline constexpr SByte ReverseBits( SByte b ) noexcept
    {
        return std::bit_cast<SByte>( ReverseBits( std::bit_cast<Byte>(b) ) );
    }
    inline constexpr char ReverseBits( char b ) noexcept
    {
        return std::bit_cast<char>( ReverseBits( std::bit_cast<Byte>( b ) ) );
    }

    inline constexpr UInt16 ReverseBits( UInt16 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt16 hi = static_cast<UInt16>( ReverseBits( static_cast<Byte>( val & 0x00FF ) ) )<< 8;
            UInt16 lo = static_cast<UInt16>( ReverseBits( static_cast<Byte>( val >> 8 ) ) );
            UInt16 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast<Byte*>( &val );
            UInt16 result;
            Byte* resultPtr = reinterpret_cast<Byte*>( &result );

            resultPtr[0] = ReverseBits( srcPtr[1] );
            resultPtr[1] = ReverseBits( srcPtr[0] );
            return result;
        }
    }
    inline constexpr Int16 ReverseBits( Int16 val ) noexcept
    {
        return std::bit_cast<Int16>( ReverseBits( std::bit_cast<UInt16>( val ) ) );
    }
    inline constexpr wchar_t ReverseBits( wchar_t val ) noexcept
    {
        return std::bit_cast<wchar_t>( ReverseBits( std::bit_cast<UInt16>( val ) ) );
    }


    inline constexpr UInt32 ReverseBits( UInt32 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt32 hi = static_cast<UInt32>( ReverseBits( static_cast<UInt16>( val & 0xFFFF ) ) ) << 16;
            UInt32 lo = static_cast<UInt32>( ReverseBits( static_cast<UInt16>( val >> 16 ) ) );
            UInt32 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast<Byte*>( &val );
            UInt32 result;
            Byte* resultPtr = reinterpret_cast<Byte*>( &result );

            resultPtr[0] = ReverseBits( srcPtr[3] );
            resultPtr[1] = ReverseBits( srcPtr[2] );
            resultPtr[2] = ReverseBits( srcPtr[1] );
            resultPtr[3] = ReverseBits( srcPtr[0] );
            return result;
        }
    }
    inline constexpr Int32 ReverseBits( Int32 val ) noexcept
    {
        return std::bit_cast<Int32>( ReverseBits( std::bit_cast<UInt32>( val ) ) );
    }
    inline constexpr long ReverseBits( long val ) noexcept
    {
        return std::bit_cast<long>( ReverseBits( std::bit_cast<UInt32>( val ) ) );
    }
    inline constexpr unsigned long ReverseBits( unsigned long val ) noexcept
    {
        return std::bit_cast<unsigned long>( ReverseBits( std::bit_cast<UInt32>( val ) ) );
    }


    inline constexpr UInt64 ReverseBits( UInt64 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt64 hi = static_cast<UInt64>( ReverseBits( static_cast<UInt32>( val & 0xFFFFFFFF ) ) ) << 32;
            UInt64 lo = static_cast<UInt64>( ReverseBits( static_cast<UInt32>( val >> 32 ) ) );
            UInt64 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast<Byte*>( &val );
            UInt64 result;
            Byte* resultPtr = reinterpret_cast<Byte*>( &result );

            resultPtr[0] = ReverseBits( srcPtr[7] );
            resultPtr[1] = ReverseBits( srcPtr[6] );
            resultPtr[2] = ReverseBits( srcPtr[5] );
            resultPtr[3] = ReverseBits( srcPtr[4] );
            resultPtr[4] = ReverseBits( srcPtr[3] );
            resultPtr[5] = ReverseBits( srcPtr[2] );
            resultPtr[6] = ReverseBits( srcPtr[1] );
            resultPtr[7] = ReverseBits( srcPtr[0] );
            return result;
        }
    }
    inline constexpr Int64 ReverseBits( Int64 val ) noexcept
    {
        return std::bit_cast<Int64>( ReverseBits( std::bit_cast<UInt64>( val ) ) );
    }
    inline constexpr Single ReverseBits( Single val ) noexcept
    {
        return std::bit_cast<Single>( ReverseBits( std::bit_cast<UInt32>( val ) ) );
    }
    inline constexpr Double ReverseBits( Double val ) noexcept
    {
        return std::bit_cast<Double>( ReverseBits( std::bit_cast<UInt64>( val ) ) );
    }

    template<typename T>
        requires std::is_integral_v<T>
    constexpr bool IndexOfBitFromMSB( unsigned long* index, T bits )
    {
        using UIntType = std::make_unsigned_t<T>;
        auto value = std::bit_cast< UIntType >( bits );
        if ( std::is_constant_evaluated( ) )
        {
            auto maskSize = ( ( sizeof( bits ) - 1 ) * 8 ) + 7;
            for ( int i = static_cast<int>( maskSize ); i >= 0; i-- )
            {
                if ( value & ( static_cast< UIntType >( 1 ) << i ) )
                {
                    if ( index )
                    {
                        *index = i;
                    }
                    return true;
                }
            }
            return false;
        }
        else
        {
            auto bitsSize = sizeof( bits );
            if ( bitsSize > 4 )
            {
                return _BitScanReverse64( index, bits ) != 0;
            }
            else
            {
                return _BitScanReverse( index, bits ) != 0;
            }
        }
    }

    

    /// <summary>
    /// Creates a bit-mask
    /// </summary>
    /// <param name="bitIndex">
    /// The number of bits to set.
    /// The value of numberOfBitsToSet must be in the range [1,64]
    /// </param>
    /// <returns>The generated bit-mask</returns>
    inline constexpr UInt64 CreateBitMask64( unsigned numberOfBitsToSet ) noexcept
    {
#ifdef _DEBUG
        if ( !std::is_constant_evaluated( ) )
        {
            assert( numberOfBitsToSet <= 64 && numberOfBitsToSet > 0 && "The value of numberOfBitsToSet must be in the range [1,64]" );
        }
#endif
        UInt64 mostSignificantBit = 1ULL << (numberOfBitsToSet - 1);
        if ( std::is_constant_evaluated( ) )
        {
            return ( mostSignificantBit - 1 ) ^ mostSignificantBit;
        }
        else
        {
            return _blsmsk_u64( mostSignificantBit );
        }
    }
    
    /// <summary>
    /// Creates a bit-mask with all the bits -
    /// up to, and including, the bit at bitIndex
    /// - set.
    /// </summary>
    /// <param name="bitIndex">
    /// The number of bits to set.
    /// The value of numberOfBitsToSet must be in the range [1,32]
    /// </param>
    /// <returns>The generated bit-mask</returns>
    inline constexpr UInt32 CreateBitMask32( unsigned numberOfBitsToSet ) noexcept
    {
#ifdef _DEBUG
        if ( !std::is_constant_evaluated( ) )
        {
            assert( numberOfBitsToSet <= 32 && numberOfBitsToSet > 0 && "The value of numberOfBitsToSet must be in the range [1,32]" );
        }
#endif
        UInt32 mostSignificantBit = 1ULL << ( numberOfBitsToSet - 1 );
        if ( std::is_constant_evaluated( ) )
        {
            return ( mostSignificantBit - 1 ) ^ mostSignificantBit;
        }
        else
        {
            return _blsmsk_u32( mostSignificantBit );
        }
    }

    /// <summary>
    /// Extracts contiguous bits from value
    /// </summary>
    /// <param name="value"></param>
    /// <param name="start">
    /// 0 based index of the least significant bit to extract.
    /// </param>
    /// <param name="len">
    /// Number of bits to extract,
    /// </param>
    /// <returns>
    /// the extracted bits, with the first extracted bit at
    /// position 0, the least significant bit in the
    /// returned value.
    /// </returns>
    inline constexpr UInt64 ExtractBits64( UInt64 value, UInt32 start, UInt32 len ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt64 mask = len ? CreateBitMask64( len ) : 0;
            return ( value >> start ) & mask;
        }
        else
        {
            return _bextr_u64( value, start, len );
        }
    }
    /// <summary>
    /// Extracts contiguous bits from value
    /// </summary>
    /// <param name="value"></param>
    /// <param name="start">
    /// 0 based index of the least significant bit to extract.
    /// </param>
    /// <param name="len">
    /// Number of bits to extract,
    /// </param>
    /// <returns>
    /// the extracted bits, with the first extracted bit at
    /// position 0, the least significant bit in the
    /// returned value.
    /// </returns>
    inline constexpr UInt32 ExtractBits32( UInt32 value, UInt32 start, UInt32 len ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt32 mask = len ? CreateBitMask32( len ) : 0;
            return ( value >> start ) & mask;
        }
        else
        {
            return _bextr_u32(value, start, len );
        }
    }

    
    template<size_t N>
    inline const void* AlignTo( const void* address )
    {
        return reinterpret_cast<const void*>(( reinterpret_cast<size_t>(address) + N ) & ~static_cast<size_t>( N ));
    }
    template<size_t N>
    inline void* AlignTo( void* address )
    {
        return reinterpret_cast<void*>( ( reinterpret_cast<size_t>( address ) + N ) & ~static_cast<size_t>( N ) );
    }
    template<size_t N>
    inline size_t AlignedPaddingFor( const void* address )
    {
        return (( reinterpret_cast<size_t>( address ) + N ) & ~static_cast<size_t>( N )) - reinterpret_cast<size_t>( address );
    }



    template<typename T>
    inline constexpr bool IsGUID = std::is_same_v<std::remove_cv_t<T>, GUID>;

    template<typename T>
        requires IsGUID<T>
    inline constexpr T ByteSwap( const T& guid ) noexcept
    {
        return GUID{ ByteSwap( guid.Data1 ), ByteSwap( guid.Data2 ), ByteSwap( guid.Data3 ), { guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] } };
    }


    template<typename T>
        requires (IsFloatingPoint<std::remove_cvref_t<T>> || std::is_enum_v<std::remove_cvref_t<T>> )
    inline constexpr T ByteSwap( const T value ) noexcept
    {
        using Type = std::remove_cvref_t<T>;
        using UIntType = MakeUnsigned<Type>;
        std::bit_cast<Type>( ByteSwap( std::bit_cast<UIntType>( value ) ) );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
        {
            { std::bit_cast<UInt64>( t2 ) }->std::convertible_to<UInt64>;
        }
    inline constexpr T1 GetHigh32Bits( T2 val ) noexcept
    {
        auto value = std::bit_cast<UInt64>( val );
        return static_cast<T1>( value >> 32 );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
        {
            { std::bit_cast<UInt64>( t2 ) }->std::convertible_to<UInt64>;
        }
    inline constexpr T2 SetHigh32Bits( T2 x, T1 value ) noexcept
    {
        return std::bit_cast<T2>( (std::bit_cast<UInt64>( x ) & 0x00000000FFFFFFFFULL) + (static_cast<UInt64>(std::bit_cast<UInt32>( value )) << 32) );
    }

    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
        {
            { std::bit_cast<UInt64>( t2 ) }->std::convertible_to<UInt64>;
        }
    inline constexpr T1 GetLow32Bits( T2 val ) noexcept
    {
        auto value = std::bit_cast<UInt64>( val );
        return static_cast<T1>( value );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
        {
            { std::bit_cast<UInt64>( t2 ) }->std::convertible_to<UInt64>;
        }
    inline constexpr T2 SetLow32Bits( T2 x, T1 value ) noexcept
    {
        return std::bit_cast<T2>( ( std::bit_cast<UInt64>( x ) & 0xFFFFFFFF00000000ULL ) + static_cast<UInt64>( std::bit_cast<UInt32>( value ) ) );
    }

    template<typename T1, typename T2, typename T3>
        requires ( sizeof( T1 ) == 8 ) && ( std::is_same_v<Int32, T2> || std::is_same_v<UInt32, T2> ) && ( std::is_same_v<Int32, T3> || std::is_same_v<UInt32, T3> ) && requires( UInt64 v1 )
        {
            { std::bit_cast<T1>( v1 ) }->std::same_as<T1>;
        }
    inline constexpr T1 From32BitsTo64Bits( T2 high32Bits, T3 low32Bits ) noexcept
    {
        return std::bit_cast<T1>(  (static_cast<UInt64>( high32Bits ) << 32) + static_cast<UInt64>( low32Bits ) );
    }

    constexpr inline int Exponent( double value ) noexcept
    {
        return static_cast<int>( std::bit_cast<Int64>( std::bit_cast<UInt64>( value ) >> 52 ) - 1023 );
    }
    constexpr inline int Exponent( float v ) noexcept
    {
        return std::bit_cast< Int32 >( std::bit_cast< UInt32 >( v ) >> 23 ) - 127;
    }


    constexpr inline UInt64 Significand( double value ) noexcept
    {
        return std::bit_cast< UInt64 >( value ) & ( ( 1ULL << 52 ) - 1 );
    }

    constexpr inline int Significand( float v ) noexcept
    {
        return std::bit_cast< UInt32 >( v ) & ( ( 1 << 23 ) - 1 );
    }


    constexpr inline UInt64 SignBit( double value )
    {
        return std::bit_cast< UInt64 >( value ) & 0x8000000000000000;
    }

    constexpr uint32_t SignBit( float v )
    {
        return std::bit_cast< UInt32 >( v ) & 0x80000000;
    }


    constexpr inline double FlipSign( double a, double b )
    {
        return std::bit_cast<double>( std::bit_cast< UInt64 >( a ) ^ SignBit( b ) );
    }
    constexpr inline float FlipSign( float a, float b )
    {
        return std::bit_cast< float >( std::bit_cast< UInt32 >( a ) ^ SignBit( b ) );
    }








    inline void MemCopy( char* dest, const char* source, size_t length ) noexcept
    {
        memcpy( dest, source, length );
    }
    inline void MemCopy( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
    {
        wmemcpy( dest, source, length );
    }

    inline void MemMove( char* dest, const char* source, size_t length ) noexcept
    {
        memmove( dest, source, length );
    }
    inline void MemMove( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
    {
        wmemmove( dest, source, length );
    }

    inline void MemSet( char* dest, char value, size_t length ) noexcept
    {
        memset( dest, value, length );
    }
    inline void MemSet( wchar_t* dest, wchar_t value, size_t length ) noexcept
    {
        wmemset( dest, value, length );
    }


    [[nodiscard]] inline int MemCmp( const char* first, const char* second, size_t length )
    {
        return memcmp( first, second, length );
    }

    [[nodiscard]] inline int MemCmp( const wchar_t* first, const wchar_t* second, size_t length )
    {
        return wmemcmp( first, second, length );
    }

    [[nodiscard]] inline char* MemChr( char* buffer, int value, size_t bufferSize ) noexcept
    {
        return ( char* )memchr( buffer, value, bufferSize );
    }
    [[nodiscard]] inline const char* MemChr( const char* buffer, int value, size_t bufferSize ) noexcept
    {
        return ( const char* )memchr( buffer, value, bufferSize );
    }
    [[nodiscard]] inline wchar_t* MemChr( wchar_t* buffer, int value, size_t bufferSize ) noexcept
    {
        return ( wchar_t* )wmemchr( buffer, value, bufferSize );
    }
    [[nodiscard]] inline const wchar_t* MemChr( const wchar_t* buffer, int value, size_t bufferSize ) noexcept
    {
        return ( const wchar_t* )wmemchr( buffer, value, bufferSize );
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





    template<typename T, size_t N>
        requires ( std::is_same_v<char,std::remove_cv_t<T>> == false && std::is_same_v<wchar_t, std::remove_cv_t<T>> == false )
    [[nodiscard]] inline constexpr size_t LengthOf( T ( &array )[N] ) noexcept
    {
        return N;
    }

    template<typename T>
        requires requires( T container )
        {
            { container.size( ) } -> std::convertible_to<size_t>;
        }
    [[nodiscard]] inline constexpr size_t LengthOf( const T& container ) noexcept
    {
        return container.size( );
    }

    namespace Internal
    {
        [[nodiscard]] inline constexpr size_t LengthOf( const char* s ) noexcept
        {
            if ( std::is_constant_evaluated( ) )
            {
                return s && s[0] ? std::string_view( s ).size( ) : 0;
            }
            else
            {
                return s && s[0] ? strlen( s ) : 0;
            }
        }
        [[nodiscard]] inline constexpr size_t LengthOf( const wchar_t* s ) noexcept
        {
            if ( std::is_constant_evaluated( ) )
            {
                return s && s[0] ? std::wstring_view( s ).size( ) : 0;
            }
            else
            {
                return s && s[0] ? wcslen( s ) : 0;
            }
        }
    }

    template<typename T>
        requires std::is_same_v<T,char> || std::is_same_v<T, wchar_t>
    [[nodiscard]] inline constexpr size_t LengthOf( const T* str ) noexcept
    {
        return Core::Internal::LengthOf( str );
    }

    inline constexpr int Compare( nullptr_t s1, nullptr_t s2 ) noexcept
    {
        return 0;
    }

    inline constexpr int Compare( nullptr_t s1, const char* s2 ) noexcept
    {
        return s2 && s2[0]?-1:0;
    }

    inline constexpr int Compare( const char* s1, nullptr_t s2 ) noexcept
    {
        return s1 && s1[0]?1:0;
    }

    inline constexpr int Compare( const char* s1, const char* s2 ) noexcept
    {   
        if ( std::is_constant_evaluated() )
        {
            if ( s1 && s1[0] )
            {
                if ( s2 && s2[0] )
                {
                    return std::string_view( s1 ).compare( s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[0] )
            {
                return -1;
            }
            return 0;
        }
        else
        {
            if ( s1 && s1[0] )
            {
                if ( s2 && s2[0] )
                {
                    return strcmp( s1, s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[0] )
            {
                return -1;
            }
            return 0;
        }
    }

    inline constexpr int Compare( nullptr_t s1, const wchar_t* s2 ) noexcept
    {
        return s2 && s2[0] ? -1 : 0;
    }

    inline constexpr int Compare( const wchar_t* s1, nullptr_t s2 ) noexcept
    {
        return s1 && s1[0] ? 1 : 0;
    }

    inline constexpr int Compare( const wchar_t* s1, const wchar_t* s2 ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            if ( s1 && s1[0] )
            {
                if ( s2 && s2[0] )
                {
                    return std::wstring_view( s1 ).compare( s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[0] )
            {
                return -1;
            }
            return 0;
        }
        else
        {
            if ( s1 && s1[0] )
            {
                if ( s2 && s2[0] )
                {
                    return wcscmp( s1, s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[0] )
            {
                return -1;
            }
            return 0;
        }
    }

    template<typename T>
        requires std::is_integral_v<T> || std::is_floating_point_v<T> 
    constexpr inline int Compare( T v1, T v2 ) noexcept
    {
        return v1 > v2 ? 1 : v1 < v2 ? -1 : 0;
    }


    template<typename T>
        requires std::is_same_v<DateTime, std::remove_cvref_t<T>> || 
            std::is_same_v<TimeSpan, std::remove_cvref_t<T>> || 
            std::is_same_v<Currency, std::remove_cvref_t<T>>
    constexpr inline int Compare( T v1, T v2 ) noexcept
    {
        return v1.CompareTo( v2 );
    }


    template<typename T1, typename T2>
        requires ((std::is_same_v<Guid, std::remove_cvref_t<T1>> || std::is_same_v<GUID, std::remove_cvref_t<T1>> ) &&
                ( std::is_same_v<Guid, std::remove_cvref_t<T2>> || std::is_same_v<GUID, std::remove_cvref_t<T2>> ) )
    constexpr inline int Compare( const T1& v1, const T2& v2 ) noexcept
    {
        return reinterpret_cast<const Guid&>(v1).CompareTo( reinterpret_cast< const Guid& >( v2 ) );
    }


    template<typename T1, typename T2 >
        requires requires( const T1& t1, const T2& t2 )
        {
            { t1.compare( t2 ) } ->std::convertible_to<int>;
        }
    inline int Compare( const T1& v1, const T2& v2 ) noexcept
    {
        return v1.compare( v2 );
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



    template<typename T>
        requires std::is_floating_point_v<T>
    constexpr bool AreNearlyEqual( T a, T b, T smallNumber = static_cast<T>( 0.0001 ) ) noexcept
    {
        if ( a <= b )
        {
            return ( b - a ) <= smallNumber;
        }
        else
        {
            return ( a - b ) <= smallNumber;
        }
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
            Add( str.c_str( ), str.size( ) );
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

        template<typename T>
            requires IsSpecializationOf<T, std::basic_string_view>
        void Add( const T& str )
        { 
            Add( str.data(), str.size() );
        }
    };


    // Bit manipulation
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsPowerOfTwo( T v ) noexcept
    {
        return v != 0 && ( v & ( v - 1 ) ) == 0;
    }
    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsPowerOf2( T v ) noexcept
    {
        return IsPowerOfTwo( v );
    }

    template<typename T>
        requires std::is_enum_v<std::remove_cvref_t<T>>
    constexpr inline bool IsPowerOfTwo( T v ) noexcept
    {
        auto val = std::bit_cast<std::underlying_type_t<std::remove_cvref_t<T>>>( v );
        return val != 0 && ( val & ( val - 1 ) ) == 0;
    }
    template<typename T>
        requires std::is_enum_v<std::remove_cvref_t<T>>
    constexpr inline bool IsPowerOf2( T v ) noexcept
    {
        return IsPowerOfTwo( v );
    }

    
    constexpr inline Byte NextPowerOfTwo( Byte v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v++;
        return v;
    }
    constexpr inline SByte NextPowerOfTwo( SByte v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v++;
        return v;
    }


    constexpr inline Int16 NextPowerOfTwo( Int16 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v++;
        return v;
    }
    constexpr inline UInt16 NextPowerOfTwo( UInt16 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v++;
        return v;
    }
    

    constexpr inline Int32 NextPowerOfTwo( Int32 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }
    constexpr inline UInt32 NextPowerOfTwo( UInt32 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }

    constexpr inline Int64 NextPowerOfTwo( Int64 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v |= v >> 32;
        v++;
        return v;
    }
    constexpr inline UInt64 NextPowerOfTwo( UInt64 v ) noexcept
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v |= v >> 32;
        v++;
        return v;
    }

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
            return Atomic::Increment( &referenceCount_ );
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
        /// <returns>true if the reference count is 1, otherwise false.</returns>
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
        ReferenceCountedPtr<T> result( ptr );
        return result;
    }

    template<typename T>
    class MallocaDeleter
    {
    public:
        MallocaDeleter( ) = default;
        void operator()( T* p ) const
        {
            _freea( p );
        };
    };



    
}

namespace std
{
    template<Harlinn::Common::Core::SimpleComLike ValueT>
    inline void swap( Harlinn::Common::Core::ReferenceCountedPtr<ValueT>& first, Harlinn::Common::Core::ReferenceCountedPtr<ValueT>& second ) noexcept
    {
        first.swap( second );
    }
}

#endif

