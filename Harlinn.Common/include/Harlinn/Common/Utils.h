#pragma once
#ifndef HARLINN_COMMON_UTILS_H_
#define HARLINN_COMMON_UTILS_H_

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

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif

#include <bit>
#include <cassert>
#include <limits>
#include <cmath>
#include <string_view>
#include "Concepts.h"

namespace Harlinn::Common
{
    template<typename T>
    inline constexpr bool IsNotBoolean = std::is_same_v<std::remove_cvref_t<T>, bool> == false;
    template<typename T>
    inline constexpr bool IsBoolean = std::is_same_v<std::remove_cvref_t<T>, bool>;
    template<typename T>
    inline constexpr bool IsInteger = std::is_integral_v<std::remove_cvref_t<T>> && IsBoolean<T> == false;

    template<typename T>
    inline constexpr bool IsSignedInteger = IsInteger<std::remove_cvref_t<T>> && std::is_signed_v<std::remove_cvref_t<T>>;

    template<typename T>
    inline constexpr bool IsUnsignedInteger = IsInteger<T> && std::is_unsigned_v<std::remove_cvref_t<T>>;

    template<typename T>
    inline constexpr bool IsFloatingPoint = std::is_floating_point_v<std::remove_cvref_t<T>>;

    template<typename T>
    inline constexpr bool IsArithmetic = IsInteger<T> || IsFloatingPoint<T>;

    namespace Internal
    {
        template <size_t>
        struct MakeUnsignedHelper;

        template <>
        struct MakeUnsignedHelper<1>
        {
            using Type = Byte;
        };

        template <>
        struct MakeUnsignedHelper<2>
        {
            using Type = UInt16;
        };

        template <>
        struct MakeUnsignedHelper<4>
        {
            using Type = UInt32;
        };

        template <>
        struct MakeUnsignedHelper<8>
        {
            using Type = UInt64;
        };
    }


    template<typename T>
    using MakeUnsigned = typename Internal::MakeUnsignedHelper< sizeof( T ) >::Type;

    template<typename T, typename U = MakeUnsigned< std::remove_cvref_t<T> > >
    inline constexpr U FractionMask = std::numeric_limits<std::remove_cvref_t<T>>::max( );

    template<typename T, typename U = MakeUnsigned< std::remove_cvref_t<T> > >
    inline constexpr U ExponentMask = 0;

    template<>
    inline constexpr UInt32 FractionMask<float, UInt32> = std::bit_cast< UInt32 >( 0b00000000011111111111111111111111 );
    template<>
    inline constexpr UInt32 ExponentMask<float, UInt32> = std::bit_cast< UInt32 >( 0b01111111100000000000000000000000 );

    template<>
    inline constexpr UInt64 FractionMask<double, UInt64> = std::bit_cast< UInt64 >( 0b0000000000001111111111111111111111111111111111111111111111111111 );
    template<>
    inline constexpr UInt64 ExponentMask<double, UInt64> = std::bit_cast< UInt64 >( 0b0111111111110000000000000000000000000000000000000000000000000000 );



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
            return ( ( ( ( value >> ( N * CHAR_BIT ) ) & ( T )( unsigned char )( -1 ) ) << ( ( sizeof( T ) - 1 - N ) * CHAR_BIT ) ) | ... );
        };
    }
    /// <summary>
    /// Reverses the order of bytes in an integer.
    /// </summary>
    /// <typeparam name="T">
    /// An integral type, normally deduced from the argument.
    /// </typeparam>
    /// <param name="value">
    /// An integral value.
    /// </param>
    /// <returns>
    /// An integral value calculated by reversing the order of the bytes from the argument.
    /// </returns>
    template<IntegerType T>
    inline constexpr T ByteSwap( T value )
    {
        if ( std::is_constant_evaluated( ) )
        {
            return std::bit_cast< T >( Internal::ByteSwapImpl( std::bit_cast< std::make_unsigned_t<T> >( value ), std::make_index_sequence<sizeof( T )>( ) ) );
        }
        else
        {
            if constexpr ( sizeof( std::remove_cvref_t<T> ) == 1 )
            {
                return value;
            }
            else if constexpr ( sizeof( std::remove_cvref_t<T> ) == 2 )
            {
                return std::bit_cast< std::remove_cvref_t<T> >(
                    _byteswap_ushort( std::bit_cast< UInt16 >( value ) ) );
            }
            else if constexpr ( sizeof( std::remove_cvref_t<T> ) == 4 )
            {
                return std::bit_cast< std::remove_cvref_t<T> >(
                    _byteswap_ulong( std::bit_cast< UInt32 >( value ) ) );
            }
            else
            {
                return std::bit_cast< std::remove_cvref_t<T> >(
                    _byteswap_uint64( std::bit_cast< UInt64 >( value ) ) );
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
        static constexpr type value = ( ( static_cast< type >( 1 ) << ( N - 1 ) ) - 1 ) ^ ( static_cast< type >( 1 ) << ( N - 1 ) );
    };

    template<size_t N>
    inline constexpr auto BitMask_v = BitMask<N>::value;
    template<size_t N>
    using BitMask_t = typename BitMask<N>::type;

    /// <summary>
    /// Creates a bitmask with the <c>N</c> right-most bits set to 1, and all other bits
    /// set to 0.
    /// </summary>
    /// <typeparam name="T">
    /// An unsigned integral type.
    /// </typeparam>
    /// <typeparam name="N">
    /// The number if rightmost bits to set.
    /// </typeparam>
    /// <returns>
    /// The bitmask.
    /// </returns>
    template <UnsignedIntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskTrailingOnes( )
    {
        return BitMask_v<N>;
    }

    template <SignedIntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskTrailingOnes( )
    {
        return std::bit_cast< T >( static_cast< std::make_unsigned_t<T> >( BitMask_v<N> ) );
    }


    /// <summary>
    /// Creates a bitmask with the <c>N</c> left-most bits set to 1, and all other bits
    /// set to 0.
    /// </summary>
    /// <typeparam name="T">
    /// An unsigned integral type.
    /// </typeparam>
    /// <typeparam name="N">
    /// The number if rightmost bits to set.
    /// </typeparam>
    /// <returns>
    /// The bitmask.
    /// </returns>
    template <UnsignedIntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskLeadingOnes( )
    {
        return ~BitMask_v<( CHAR_BIT * sizeof( T ) ) - N>;
    }

    template <SignedIntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskLeadingOnes( )
    {
        return std::bit_cast< T >( static_cast< std::make_unsigned_t<T> >( ~BitMask_v<( CHAR_BIT * sizeof( T ) ) - N> ) );
    }

    /// <summary>
    /// Creates a bitmask with the <c>N</c> right-most bits set to 0, and all other bits
    /// set to 1.
    /// </summary>
    /// <typeparam name="T">
    /// An unsigned integral type.
    /// </typeparam>
    /// <typeparam name="N">
    /// The number if rightmost bits to clear.
    /// </typeparam>
    /// <returns>
    /// The bitmask.
    /// </returns>
    template <UnsignedIntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskTrailingZeros( )
    {
        return ~BitMask_v<N>;
    }

    template <SignedIntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskTrailingZeros( )
    {
        return std::bit_cast< T >( static_cast< std::make_unsigned_t<T> >( ~BitMask_v<N> ) );
    }

    /// <summary>
    /// Creates a bitmask with the <c>N</c> left-most bits set to 0, and all other bits
    /// set to 1.
    /// </summary>
    /// <typeparam name="T">
    /// An unsigned integral type.
    /// </typeparam>
    /// <typeparam name="N">
    /// The number if rightmost bits to clear.
    /// </typeparam>
    /// <returns>
    /// The bitmask.
    /// </returns>
    template <UnsignedIntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskLeadingZeros( )
    {
        return BitMask_v<( CHAR_BIT * sizeof( T ) ) - N>;
    }

    template <SignedIntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskLeadingZeros( )
    {
        return std::bit_cast< T >( BitMask_v<( CHAR_BIT * sizeof( T ) ) - N> );
    }


    /// <summary>
    /// Reverses the order of the bits of a byte.
    /// </summary>
    inline constexpr Byte ReverseBits( Byte b ) noexcept
    {
        /*
         * From: https://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64BitsDiv
         */
        b = static_cast< Byte >( ( static_cast< UInt64 >( b ) * 0x0202020202ULL & 0x010884422010ULL ) % 1023 );
        return b;
    }

    /// <summary>
    /// Reverses the order of the bits of a SByte.
    /// </summary>
    inline constexpr SByte ReverseBits( SByte b ) noexcept
    {
        return std::bit_cast< SByte >( ReverseBits( std::bit_cast< Byte >( b ) ) );
    }
    /// <summary>
    /// Reverses the order of the bits of a char.
    /// </summary>
    inline constexpr char ReverseBits( char b ) noexcept
    {
        return std::bit_cast< char >( ReverseBits( std::bit_cast< Byte >( b ) ) );
    }

    /// <summary>
    /// Reverses the order of the bits of an UInt16.
    /// </summary>
    inline constexpr UInt16 ReverseBits( UInt16 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt16 hi = static_cast< UInt16 >( ReverseBits( static_cast< Byte >( val & 0x00FF ) ) ) << 8;
            UInt16 lo = static_cast< UInt16 >( ReverseBits( static_cast< Byte >( val >> 8 ) ) );
            UInt16 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast< Byte* >( &val );
            UInt16 result;
            Byte* resultPtr = reinterpret_cast< Byte* >( &result );

            resultPtr[ 0 ] = ReverseBits( srcPtr[ 1 ] );
            resultPtr[ 1 ] = ReverseBits( srcPtr[ 0 ] );
            return result;
        }
    }
    /// <summary>
    /// Reverses the order of the bits of an Int16.
    /// </summary>
    inline constexpr Int16 ReverseBits( Int16 val ) noexcept
    {
        return std::bit_cast< Int16 >( ReverseBits( std::bit_cast< UInt16 >( val ) ) );
    }
    inline constexpr wchar_t ReverseBits( wchar_t val ) noexcept
    {
        return std::bit_cast< wchar_t >( ReverseBits( std::bit_cast< UInt16 >( val ) ) );
    }


    /// <summary>
    /// Reverses the order of the bits of an UInt32.
    /// </summary>
    inline constexpr UInt32 ReverseBits( UInt32 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt32 hi = static_cast< UInt32 >( ReverseBits( static_cast< UInt16 >( val & 0xFFFF ) ) ) << 16;
            UInt32 lo = static_cast< UInt32 >( ReverseBits( static_cast< UInt16 >( val >> 16 ) ) );
            UInt32 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast< Byte* >( &val );
            UInt32 result;
            Byte* resultPtr = reinterpret_cast< Byte* >( &result );

            resultPtr[ 0 ] = ReverseBits( srcPtr[ 3 ] );
            resultPtr[ 1 ] = ReverseBits( srcPtr[ 2 ] );
            resultPtr[ 2 ] = ReverseBits( srcPtr[ 1 ] );
            resultPtr[ 3 ] = ReverseBits( srcPtr[ 0 ] );
            return result;
        }
    }
    /// <summary>
    /// Reverses the order of the bits of an Int32.
    /// </summary>
    inline constexpr Int32 ReverseBits( Int32 val ) noexcept
    {
        return std::bit_cast< Int32 >( ReverseBits( std::bit_cast< UInt32 >( val ) ) );
    }
    /// <summary>
    /// Reverses the order of the bits of a long.
    /// </summary>
    inline constexpr long ReverseBits( long val ) noexcept
    {
        return std::bit_cast< long >( ReverseBits( std::bit_cast< UInt32 >( val ) ) );
    }
    /// <summary>
    /// Reverses the order of the bits of an unsigned long.
    /// </summary>
    inline constexpr unsigned long ReverseBits( unsigned long val ) noexcept
    {
        return std::bit_cast< unsigned long >( ReverseBits( std::bit_cast< UInt32 >( val ) ) );
    }

    /// <summary>
    /// Reverses the order of the bits of an UInt64.
    /// </summary>
    inline constexpr UInt64 ReverseBits( UInt64 val ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            UInt64 hi = static_cast< UInt64 >( ReverseBits( static_cast< UInt32 >( val & 0xFFFFFFFF ) ) ) << 32;
            UInt64 lo = static_cast< UInt64 >( ReverseBits( static_cast< UInt32 >( val >> 32 ) ) );
            UInt64 result = lo | hi;
            return result;
        }
        else
        {
            Byte* srcPtr = reinterpret_cast< Byte* >( &val );
            UInt64 result;
            Byte* resultPtr = reinterpret_cast< Byte* >( &result );

            resultPtr[ 0 ] = ReverseBits( srcPtr[ 7 ] );
            resultPtr[ 1 ] = ReverseBits( srcPtr[ 6 ] );
            resultPtr[ 2 ] = ReverseBits( srcPtr[ 5 ] );
            resultPtr[ 3 ] = ReverseBits( srcPtr[ 4 ] );
            resultPtr[ 4 ] = ReverseBits( srcPtr[ 3 ] );
            resultPtr[ 5 ] = ReverseBits( srcPtr[ 2 ] );
            resultPtr[ 6 ] = ReverseBits( srcPtr[ 1 ] );
            resultPtr[ 7 ] = ReverseBits( srcPtr[ 0 ] );
            return result;
        }
    }

    /// <summary>
    /// Reverses the order of the bits of an Int64.
    /// </summary>
    inline constexpr Int64 ReverseBits( Int64 val ) noexcept
    {
        return std::bit_cast< Int64 >( ReverseBits( std::bit_cast< UInt64 >( val ) ) );
    }
    /// <summary>
    /// Reverses the order of the bits of a float.
    /// </summary>
    inline constexpr Single ReverseBits( float val ) noexcept
    {
        return std::bit_cast< Single >( ReverseBits( std::bit_cast< UInt32 >( val ) ) );
    }
    /// <summary>
    /// Reverses the order of the bits of a double.
    /// </summary>
    inline constexpr Double ReverseBits( double val ) noexcept
    {
        return std::bit_cast< Double >( ReverseBits( std::bit_cast< UInt64 >( val ) ) );
    }

    /// <summary>
    /// Search the mask data from least significant bit (LSB) to the most significant bit (MSB) for a set bit (1).
    /// </summary>
    /// <param name="index">
    /// Pointer to a value that will receive the zero based index of the
    /// of the bit, if found.
    /// </param>
    /// <param name="bits">
    /// The value to search.
    /// </param>
    /// <returns>
    /// Returns true if a set bit was found and the value pointed to by index is valid.
    /// </returns>
    template<IntegerType T>
    constexpr bool IndexOfBitFromLSB( unsigned long* index, T bits )
    {
        if ( std::is_constant_evaluated( ) )
        {
            using UIntType = std::make_unsigned_t<T>;
            auto value = std::bit_cast< UIntType >( bits );
            auto maskSize = ( ( sizeof( bits ) - 1 ) * 8 ) + 7;
            for ( UIntType i = 0; i < maskSize; i++ )
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
            constexpr auto bitsSize = sizeof( bits );

            if constexpr ( bitsSize > 4 )
            {
                auto value = std::bit_cast< UInt64 >( bits );
                return _BitScanForward64( index, value ) != 0;
            }
            else
            {
                using UIntType = std::make_unsigned_t<T>;
                auto value = std::bit_cast< UIntType >( bits );
                return _BitScanForward( index, value ) != 0;
            }
        }
    }

    /// <summary>
    /// Search the mask data from least significant bit (LSB) to the most significant bit (MSB) for a set bit (1).
    /// </summary>
    /// <param name="bits">
    /// The value to search.
    /// </param>
    /// <returns>
    /// An std::optional with an assigned value if a set bit was found.
    /// </returns>
    template<IntegerType T>
    constexpr std::optional<unsigned long> IndexOfBitFromLSB( T bits )
    {
        unsigned long index{};
        if ( IndexOfBitFromLSB( &index, bits ) )
        {
            return index;
        }
        return {};
    }

    /// <summary>
    /// Search the mask data from most significant bit (MSB) to least significant bit (LSB) for a set bit (1).
    /// </summary>
    /// <param name="index">
    /// Pointer to a value that will receive the zero based index of the
    /// of the bit, if found.
    /// </param>
    /// <param name="bits">
    /// The value to search.
    /// </param>
    /// <returns>
    /// Returns true if a set bit was found and the value pointed to by index is valid.
    /// </returns>
    template<IntegerType T>
    constexpr bool IndexOfBitFromMSB( unsigned long* index, T bits )
    {
        using UIntType = std::make_unsigned_t<T>;

        if ( std::is_constant_evaluated( ) )
        {
            auto value = std::bit_cast< UIntType >( bits );
            auto maskSize = ( ( sizeof( bits ) - 1 ) * 8 ) + 7;
            for ( int i = static_cast< int >( maskSize ); i >= 0; i-- )
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
            constexpr auto bitsSize = sizeof( bits );

            if constexpr ( bitsSize > 4 )
            {
                auto value = std::bit_cast< UInt64 >( bits );
                return _BitScanReverse64( index, value ) != 0;
            }
            else
            {
                using UIntType = std::make_unsigned_t<T>;
                auto value = std::bit_cast< UIntType >( bits );
                return _BitScanReverse( index, value ) != 0;
            }
        }
    }

    /// <summary>
    /// Search the mask data from most significant bit (MSB) to least significant bit (LSB) for a set bit (1).
    /// </summary>
    /// <param name="bits">
    /// The value to search.
    /// </param>
    /// <returns>
    /// An std::optional with an assigned value if a set bit was found.
    /// </returns>
    template<IntegerType T>
    constexpr std::optional<unsigned long> IndexOfBitFromMSB( T bits )
    {
        unsigned long index{};
        if ( IndexOfBitFromMSB( &index, bits ) )
        {
            return index;
        }
        return {};
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
        UInt64 mostSignificantBit = 1ULL << ( numberOfBitsToSet - 1 );
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
            return _bextr_u32( value, start, len );
        }
    }


    /// <summary>
    /// Calculates the address that is aligned on an <c>N</c> byte boundary
    /// greater, or equal, to <c>address</c>. 
    /// </summary>
    /// <typeparam name="N">
    /// The requested alignment.
    /// </typeparam>
    /// <param name="address">
    /// The address to calculate the alignment for. 
    /// </param>
    /// <returns>
    /// The aligned address.
    /// </returns>
    template<size_t N>
    inline const void* AlignTo( const void* address )
    {
        return reinterpret_cast< const void* >( ( reinterpret_cast< size_t >( address ) + N ) & ~static_cast< size_t >( N ) );
    }

    /// <summary>
    /// Calculates the address that is aligned on an <c>N</c> byte boundary
    /// greater, or equal, to <c>address</c>. 
    /// </summary>
    /// <typeparam name="N">
    /// The requested alignment.
    /// </typeparam>
    /// <param name="address">
    /// The address to calculate the alignment for. 
    /// </param>
    /// <returns>
    /// The aligned address.
    /// </returns>
    template<size_t N>
    inline void* AlignTo( void* address )
    {
        return reinterpret_cast< void* >( ( reinterpret_cast< size_t >( address ) + N ) & ~static_cast< size_t >( N ) );
    }

    /// <summary>
    /// Calculates the number of bytes between the argument <c>address</c> 
    /// and an address that is aligned on an <c>N</c> byte boundary
    /// greater, or equal, to <c>address</c>. 
    /// </summary>
    /// <typeparam name="N"></typeparam>
    /// <param name="address"></param>
    /// <returns></returns>
    template<size_t N>
    inline size_t AlignedPaddingFor( const void* address )
    {
        return ( ( reinterpret_cast< size_t >( address ) + N ) & ~static_cast< size_t >( N ) ) - reinterpret_cast< size_t >( address );
    }

    /// <summary>
    /// Reverses the bytes of a floating point value, or an enum.
    /// </summary>
    /// <typeparam name="T">
    /// A floating point type, or an enum type.
    /// </typeparam>
    /// <param name="value">
    /// The value.
    /// </param>
    /// <returns>
    /// The result.
    /// </returns>
    template<typename T>
        requires ( IsFloatingPoint<std::remove_cvref_t<T>> || std::is_enum_v<std::remove_cvref_t<T>> )
    inline constexpr T ByteSwap( const T value ) noexcept
    {
        using Type = std::remove_cvref_t<T>;
        using UIntType = MakeUnsigned<Type>;
        std::bit_cast< Type >( ByteSwap( std::bit_cast< UIntType >( value ) ) );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
    {
        { std::bit_cast< UInt64 >( t2 ) }->std::convertible_to<UInt64>;
    }
    inline constexpr T1 GetHigh32Bits( T2 val ) noexcept
    {
        auto value = std::bit_cast< UInt64 >( val );
        return std::bit_cast< T1 >( static_cast< UInt32 >( value >> 32 ) );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
    {
        { std::bit_cast< UInt64 >( t2 ) }->std::convertible_to<UInt64>;
    }
    inline constexpr T2 SetHigh32Bits( T2 x, T1 value ) noexcept
    {
        return std::bit_cast< T2 >( ( std::bit_cast< UInt64 >( x ) & 0x00000000FFFFFFFFULL ) + ( static_cast< UInt64 >( std::bit_cast< UInt32 >( value ) ) << 32 ) );
    }

    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
    {
        { std::bit_cast< UInt64 >( t2 ) }->std::convertible_to<UInt64>;
    }
    inline constexpr T1 GetLow32Bits( T2 val ) noexcept
    {
        auto value = std::bit_cast< UInt64 >( val );
        return std::bit_cast< T1 >( static_cast< UInt32 >( value ) );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 ) && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> ) && requires( T2 t2 )
    {
        { std::bit_cast< UInt64 >( t2 ) }->std::convertible_to<UInt64>;
    }
    inline constexpr T2 SetLow32Bits( T2 x, T1 value ) noexcept
    {
        return std::bit_cast< T2 >( ( std::bit_cast< UInt64 >( x ) & 0xFFFFFFFF00000000ULL ) + static_cast< UInt64 >( std::bit_cast< UInt32 >( value ) ) );
    }

    template<typename T1, typename T2, typename T3>
        requires ( sizeof( T1 ) == 8 ) && ( std::is_same_v<Int32, T2> || std::is_same_v<UInt32, T2> ) && ( std::is_same_v<Int32, T3> || std::is_same_v<UInt32, T3> ) && requires( UInt64 v1 )
    {
        { std::bit_cast< T1 >( v1 ) }->std::same_as<T1>;
    }
    inline constexpr T1 From32BitsTo64Bits( T2 high32Bits, T3 low32Bits ) noexcept
    {
        return std::bit_cast< T1 >( ( static_cast< UInt64 >( high32Bits ) << 32 ) + static_cast< UInt64 >( low32Bits ) );
    }

    constexpr inline int Exponent( double value ) noexcept
    {
        return static_cast< int >( std::bit_cast< Int64 >( std::bit_cast< UInt64 >( value ) >> 52 ) - 1023 );
    }
    constexpr inline int Exponent( float v ) noexcept
    {
        return std::bit_cast< Int32 >( std::bit_cast< UInt32 >( v ) >> 23 ) - 127;
    }


    constexpr inline UInt64 Significand( double value ) noexcept
    {
        return std::bit_cast< UInt64 >( value ) & ( ( 1ULL << 52 ) - 1 );
    }

    constexpr inline UInt32 Significand( float v ) noexcept
    {
        return std::bit_cast< UInt32 >( v ) & ( ( 1 << 23 ) - 1 );
    }


    constexpr inline UInt64 FastSignBit( double value )
    {
        return std::bit_cast< UInt64 >( value ) & 0x8000000000000000;
    }

    constexpr UInt32 FastSignBit( float v )
    {
        return std::bit_cast< UInt32 >( v ) & 0x80000000;
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



    template<typename T, size_t N>
        requires ( std::is_same_v<char, std::remove_cv_t<T>> == false && std::is_same_v<wchar_t, std::remove_cv_t<T>> == false )
    [[nodiscard]] inline constexpr size_t LengthOf( T( &array )[ N ] ) noexcept
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
                return s && s[ 0 ] ? std::string_view( s ).size( ) : 0;
            }
            else
            {
                return s && s[ 0 ] ? strlen( s ) : 0;
            }
        }
        [[nodiscard]] inline constexpr size_t LengthOf( const wchar_t* s ) noexcept
        {
            if ( std::is_constant_evaluated( ) )
            {
                return s && s[ 0 ] ? std::wstring_view( s ).size( ) : 0;
            }
            else
            {
                return s && s[ 0 ] ? wcslen( s ) : 0;
            }
        }
    }

    template<typename T>
        requires std::is_same_v<T, char> || std::is_same_v<T, wchar_t>
    [[nodiscard]] inline constexpr size_t LengthOf( const T* str ) noexcept
    {
        return Common::Internal::LengthOf( str );
    }

    inline constexpr int Compare( nullptr_t s1, nullptr_t s2 ) noexcept
    {
        return 0;
    }

    inline constexpr int Compare( nullptr_t s1, const char* s2 ) noexcept
    {
        return s2 && s2[ 0 ] ? -1 : 0;
    }

    inline constexpr int Compare( const char* s1, nullptr_t s2 ) noexcept
    {
        return s1 && s1[ 0 ] ? 1 : 0;
    }

    inline constexpr int Compare( const char* s1, const char* s2 ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            if ( s1 && s1[ 0 ] )
            {
                if ( s2 && s2[ 0 ] )
                {
                    return std::string_view( s1 ).compare( s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[ 0 ] )
            {
                return -1;
            }
            return 0;
        }
        else
        {
            if ( s1 && s1[ 0 ] )
            {
                if ( s2 && s2[ 0 ] )
                {
                    return strcmp( s1, s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[ 0 ] )
            {
                return -1;
            }
            return 0;
        }
    }

    inline constexpr int Compare( nullptr_t s1, const wchar_t* s2 ) noexcept
    {
        return s2 && s2[ 0 ] ? -1 : 0;
    }

    inline constexpr int Compare( const wchar_t* s1, nullptr_t s2 ) noexcept
    {
        return s1 && s1[ 0 ] ? 1 : 0;
    }

    inline constexpr int Compare( const wchar_t* s1, const wchar_t* s2 ) noexcept
    {
        if ( std::is_constant_evaluated( ) )
        {
            if ( s1 && s1[ 0 ] )
            {
                if ( s2 && s2[ 0 ] )
                {
                    return std::wstring_view( s1 ).compare( s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[ 0 ] )
            {
                return -1;
            }
            return 0;
        }
        else
        {
            if ( s1 && s1[ 0 ] )
            {
                if ( s2 && s2[ 0 ] )
                {
                    return wcscmp( s1, s2 );
                }
                else
                {
                    return 1;
                }
            }
            else if ( s2 && s2[ 0 ] )
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
        requires requires ( const T& t1, const T& t2 )
        {
            { t1.CompareTo( t2 ) } ->std::convertible_to<int>;
        }
    constexpr inline int Compare( T first, T second ) noexcept
    {
        return first.CompareTo( second );
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

    





    template<typename T>
        requires std::is_floating_point_v<T>
    constexpr bool AreNearlyEqual( T a, T b, T smallNumber = static_cast< T >( 0.0001 ) ) noexcept
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
        auto val = std::bit_cast< std::underlying_type_t<std::remove_cvref_t<T>> >( v );
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

    namespace Internal
    {
        template <typename Fn>
        struct FinallyImpl : public Fn
        {
            FinallyImpl( Fn&& Func )
                : Fn( std::forward<Fn>( Func ) )
            {
            }
            FinallyImpl( const FinallyImpl& ) = delete;
            FinallyImpl( FinallyImpl&& ) = delete;
            ~FinallyImpl( )
            {
                this->operator()( );
            }
        };
    }

    template <typename Fn>
    inline Internal::FinallyImpl<Fn> Finally( Fn&& Func )
    {
        return { std::forward<Fn>( Func ) };
    }

}

#endif