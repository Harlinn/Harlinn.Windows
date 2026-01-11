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
#include <cwctype>
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
            //! \unnamed{struct:1}
            Byte Low;
            //! \unnamed{struct:2}
            Byte High;
        };
        UInt16 Value;
    };

    union Bits32
    {
        struct
        {
            //! \unnamed{struct:1}
            Bits16 Low;
            //! \unnamed{struct:2}
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
            //! \unnamed{struct:1}
            Bits32 Low;
            //! \unnamed{struct:2}
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
                        *index = static_cast<unsigned long>(i);
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

    /// <summary>
    /// Determines whether two memory regions overlap in address space.
    /// </summary>
    /// <param name="first">
    /// The starting address of the first memory region.
    /// </param>
    /// <param name="firstSize">
    /// The size, in bytes, of the first memory region.
    /// </param>
    /// <param name="second">
    /// The starting address of the second memory region.
    /// </param>
    /// <param name="secondSize">
    /// The size, in bytes, of the second memory region.
    /// </param>
    /// <returns>
    /// <para>
    /// Returns <c>true</c> if the memory regions overlap; otherwise, <c>false</c>.
    /// </para>
    /// </returns>
    /// <remarks>
    /// <para>
    /// This function performs a strict overlap test using half-open intervals
    /// defined as [begin, end), where <c>end = begin + size</c>. The regions
    /// overlap if either region's start address falls strictly within the other
    /// region's range.
    /// </para>
    /// <para>
    /// Use this function to decide between copy strategies that require non-overlapping
    /// buffers (e.g., <c>memcpy</c> or <see cref="MemCopy(char*, const char*, size_t)"/>)
    /// and those that safely handle overlap (e.g., <c>memmove</c> or
    /// <see cref="MemMove(char*, const char*, size_t)"/>).
    /// </para>
    /// <list type="bullet">
    ///   <item>
    ///     <description>
    ///     The comparison is performed using byte-wise pointer arithmetic via
    ///     <c>reinterpret_cast&lt;const char*&gt;</c> to avoid type aliasing issues.
    ///     </description>
    ///   </item>
    ///   <item>
    ///     <description>
    ///     Zero-length regions never overlap and will return <c>false</c>.
    ///     </description>
    ///   </item>
    /// </list>
    /// </remarks>
    /// <example>
    /// <code>
    /// char buffer[64]{};
    /// char* a = buffer;
    /// char* b = buffer + 16;
    /// bool overlaps = Harlinn::Common::Overlaps(a, 32, b, 32); // returns true
    /// </code>
    /// </example>
    /// <seealso cref="MemCopy(char*, const char*, size_t)"/>
    /// <seealso cref="MemMove(char*, const char*, size_t)"/>
    inline bool Overlaps( const void* first, size_t firstSize, const void* second, size_t secondSize ) noexcept
    {
        if( first < second )
        {
            return ( reinterpret_cast< const char* >( first ) + firstSize ) > reinterpret_cast< const char* >( second );
        }
        else
        {
            return ( reinterpret_cast<const char*>( second ) + secondSize ) > reinterpret_cast<const char*>( first );
        }
	}

    /// <summary>
    /// Copies a specified number of bytes from a source buffer to a destination buffer using a non-overlapping copy.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer that receives the copied bytes. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="source">
    /// Pointer to the source buffer to copy from. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="length">
    /// The number of bytes to copy. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// <para>
    /// This function wraps <c>memcpy</c> and is intended for non-overlapping memory regions only.
    /// In debug builds, it asserts if the memory regions overlap according to
    /// <see cref="Overlaps(const void*, size_t, const void*, size_t)"/>. In release builds,
    /// providing overlapping regions results in undefined behavior.
    /// </para>
    /// <para>
    /// If there is any possibility that the regions overlap, use
    /// <see cref="MemMove(char*, const char*, size_t)"/> instead.
    /// </para>
    /// <list type="bullet">
    ///   <item>
    ///     <description>Preconditions: <c>dest != nullptr</c> and <c>source != nullptr</c> when <paramref name="length"/> &gt; 0.</description>
    ///   </item>
    ///   <item>
    ///     <description>Buffers must be distinct and non-overlapping for the specified <paramref name="length"/>.</description>
    ///   </item>
    ///   <item>
    ///     <description>Zero-length copies are treated as no-ops.</description>
    ///   </item>
    /// </list>
    /// </remarks>
    /// <example>
    /// <code>
    /// char src[16]{ 'H','a','r','l','i','n','n',0 };
    /// char dst[16]{};
    /// // Ensure non-overlapping regions or use MemMove
    /// if ( !Harlinn::Common::Overlaps( dst, sizeof( dst ), src, sizeof( src ) ) )
    /// {
    ///     Harlinn::Common::MemCopy( dst, src, 8 );
    /// }
    /// </code>
    /// </example>
    /// <seealso cref="MemMove(char*, const char*, size_t)"/>
    /// <seealso cref="MemCopyOrZero(char*, const char*, size_t)"/>
    /// <seealso cref="Overlaps(const void*, size_t, const void*, size_t)"/>
    inline void MemCopy( char* dest, const char* source, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
            if ( !source )
            {
                assert( false && "source is null" );
            }
            if ( Overlaps( dest, length, source, length ) )
            {
                assert( false && "source and dest memory regions overlap" );
			}
#endif
            memcpy( dest, source, length );
        }
    }
    
    /// <summary>
    /// Copies a specified number of bytes from a source buffer to a destination buffer 
    /// if <paramref name="source"/> is non-null, otherwise fills the destination buffer 
    /// with zeros. Uses a non-overlapping copy when a source is provided.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer that receives the copied bytes or zeroes. 
    /// Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="source">
    /// Pointer to the source buffer to copy from. If null, the function zero-fills the 
    /// destination buffer.
    /// </param>
    /// <param name="length">
    /// The number of bytes to copy or zero-fill. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// <para>
    /// When <paramref name="source"/> is not null, this function wraps <c>memcpy</c> and is 
    /// intended for non-overlapping memory regions only. In debug builds, it asserts if the 
    /// memory regions overlap according to <see cref="Overlaps(const void*, size_t, const void*, size_t)"/>. 
    /// In release builds, providing overlapping regions results in undefined behavior.
    /// </para>
    /// <para>
    /// If there is any possibility that the regions overlap, use
    /// <see cref="MemMoveOrZero(char*, const char*, size_t)"/> instead.
    /// </para>
    /// <list type="bullet">
    ///   <item>
    ///     <description>Preconditions: <c>dest != nullptr</c> when <paramref name="length"/> &gt; 0.</description>
    ///   </item>
    ///   <item>
    ///     <description>If <paramref name="source"/> is null, the destination is filled with zeros.</description>
    ///   </item>
    ///   <item>
    ///     <description>Zero-length operations are treated as no-ops.</description>
    ///   </item>
    /// </list>
    /// </remarks>
    /// <example>
    /// <code>
    /// char buffer[32];
    /// const char* maybeSrc = nullptr;
    /// Harlinn::Common::MemCopyOrZero(buffer, maybeSrc, sizeof(buffer)); // zero-fills buffer
    /// </code>
    /// </example>
    /// <seealso cref="Overlaps(const void*, size_t, const void*, size_t)"/>
    /// <seealso cref="MemMoveOrZero(char*, const char*, size_t)"/>
    inline void MemCopyOrZero( char* dest, const char* source, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
#endif
            if ( source )
            {
#ifdef _DEBUG
                if ( Overlaps( dest, length, source, length ) )
                {
                    assert( false && "source and dest memory regions overlap" );
                }
#endif
                memcpy( dest, source, length );
            }
            else
            {
                memset( dest, 0, length );
            }
        }
    }

    /// <summary>
    /// Copies a specified number of wide characters from a source buffer to a destination 
    /// buffer using a non-overlapping copy.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer that receives the copied wide characters. Must be 
    /// non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="source">
    /// Pointer to the source buffer to copy from. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="length">
    /// The number of wide characters to copy. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// <para>
    /// This function wraps <c>wmemcpy</c> and is intended for non-overlapping memory regions only.
    /// In debug builds, it asserts if the memory regions overlap according to
    /// <see cref="Overlaps(const void*, size_t, const void*, size_t)"/>. In release builds,
    /// providing overlapping regions results in undefined behavior.
    /// </para>
    /// <para>
    /// If there is any possibility that the regions overlap, use
    /// <see cref="MemMove(wchar_t*, const wchar_t*, size_t)"/> instead.
    /// </para>
    /// <list type="bullet">
    ///   <item>
    ///     <description>Preconditions: <c>dest != nullptr</c> and <c>source != nullptr</c> when <paramref name="length"/> &gt; 0.</description>
    ///   </item>
    ///   <item>
    ///     <description>Buffers must be distinct and non-overlapping for the specified <paramref name="length"/>.</description>
    ///   </item>
    ///   <item>
    ///     <description>Zero-length copies are treated as no-ops.</description>
    ///   </item>
    /// </list>
    /// </remarks>
    /// <seealso cref="Overlaps(const void*, size_t, const void*, size_t)"/>
    /// <seealso cref="MemMove(wchar_t*, const wchar_t*, size_t)"/>
    inline void MemCopy( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
            if ( !source )
            {
                assert( false && "source is null" );
            }
            if ( Overlaps( dest, length * sizeof( wchar_t ), source, length * sizeof( wchar_t ) ) )
            {
                assert( false && "source and dest memory regions overlap" );
			}
#endif
            wmemcpy( dest, source, length );
        }
    }

    /// <summary>
    /// Copies a specified number of wide characters from a source buffer to a destination buffer 
    /// if <paramref name="source"/> is non-null, otherwise fills the destination buffer with zeros. 
    /// Uses a non-overlapping copy when a source is provided.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer that receives the copied wide characters or zeroes. 
    /// Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="source">
    /// Pointer to the source buffer to copy from. If null, the function zero-fills the destination buffer.
    /// </param>
    /// <param name="length">
    /// The number of wide characters to copy or zero-fill. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// <para>
    /// When <paramref name="source"/> is not null, this function wraps <c>wmemcpy</c> and is intended 
    /// for non-overlapping memory regions only. In debug builds, it asserts if the memory regions 
    /// overlap according to <see cref="Overlaps(const void*, size_t, const void*, size_t)"/>. 
    /// In release builds, providing overlapping regions results in undefined behavior.
    /// </para>
    /// <para>
    /// If there is any possibility that the regions overlap, use
    /// <see cref="MemMoveOrZero(wchar_t*, const wchar_t*, size_t)"/> instead.
    /// </para>
    /// <list type="bullet">
    ///   <item>
    ///     <description>Preconditions: <c>dest != nullptr</c> when <paramref name="length"/> &gt; 0.</description>
    ///   </item>
    ///   <item>
    ///     <description>If <paramref name="source"/> is null, the destination is filled with zeros.</description>
    ///   </item>
    ///   <item>
    ///     <description>Zero-length operations are treated as no-ops.</description>
    ///   </item>
    /// </list>
    /// </remarks>
    /// <seealso cref="Overlaps(const void*, size_t, const void*, size_t)"/>
    /// <seealso cref="MemMoveOrZero(wchar_t*, const wchar_t*, size_t)"/>
    inline void MemCopyOrZero( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
#endif
            if ( source )
            {
#ifdef _DEBUG
                if ( Overlaps( dest, length * sizeof( wchar_t ), source, length * sizeof( wchar_t ) ) )
                {
                    assert( false && "source and dest memory regions overlap" );
                }
#endif
                wmemcpy( dest, source, length );
            }
            else
            {
                wmemset( dest, 0, length );
            }
        }
    }


    /// <summary>
    /// Copies a specified number of bytes from a source buffer to a destination buffer,
    /// correctly handling overlapping memory regions.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer that receives the copied bytes. Must be non-null 
    /// if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="source">
    /// Pointer to the source buffer to copy from. Must be non-null if <paramref name="length"/> 
    /// is greater than zero.
    /// </param>
    /// <param name="length">
    /// The number of bytes to copy. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// <para>
    /// This function wraps <c>memmove</c> and is safe for overlapping source and destination ranges.
    /// </para>
    /// <list type="bullet">
    ///   <item>
    ///     <description>Preconditions: <c>dest != nullptr</c> and <c>source != nullptr</c> when <paramref name="length"/> &gt; 0.</description>
    ///   </item>
    ///   <item>
    ///     <description>Zero-length copies are treated as no-ops.</description>
    ///   </item>
    /// </list>
    /// </remarks>
    /// <seealso cref="MemCopy(char*, const char*, size_t)"/>
    inline void MemMove( char* dest, const char* source, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
            if ( !source )
            {
                assert( false && "source is null" );
            }
#endif
            memmove( dest, source, length );
        }
    }

    /// <summary>
    /// Copies a specified number of bytes from a source buffer to a destination buffer if <paramref name="source"/> is non-null
    /// using overlap-safe semantics, otherwise fills the destination buffer with zeros.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer that receives the copied bytes or zeroes. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="source">
    /// Pointer to the source buffer to copy from. If null, the function zero-fills the destination buffer.
    /// </param>
    /// <param name="length">
    /// The number of bytes to copy or zero-fill. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// <para>
    /// This function wraps <c>memmove</c> when <paramref name="source"/> is non-null and is safe for overlapping memory regions.
    /// If <paramref name="source"/> is null, the destination is filled with zeros.
    /// </para>
    /// </remarks>
    /// <seealso cref="MemCopyOrZero(char*, const char*, size_t)"/>
    inline void MemMoveOrZero( char* dest, const char* source, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
#endif
            if ( source )
            {
                memmove( dest, source, length );
            }
            else
            {
                memset( dest, 0, length );
            }
        }
    }

    /// <summary>
    /// Copies a specified number of wide characters from a source buffer to a destination buffer,
    /// correctly handling overlapping memory regions.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer that receives the copied wide characters. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="source">
    /// Pointer to the source buffer to copy from. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="length">
    /// The number of wide characters to copy. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// <para>
    /// This function wraps <c>wmemmove</c> and is safe for overlapping source and destination ranges.
    /// </para>
    /// </remarks>
    /// <seealso cref="MemCopy(wchar_t*, const wchar_t*, size_t)"/>
    inline void MemMove( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
            if ( !source )
            {
                assert( false && "source is null" );
            }
#endif
            wmemmove( dest, source, length );
        }
    }
    /// <summary>
    /// Copies a specified number of wide characters from a source buffer to a destination buffer if <paramref name="source"/> is non-null
    /// using overlap-safe semantics, otherwise fills the destination buffer with zeros.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer that receives the copied wide characters or zeroes. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="source">
    /// Pointer to the source buffer to copy from. If null, the function zero-fills the destination buffer.
    /// </param>
    /// <param name="length">
    /// The number of wide characters to copy or zero-fill. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// <para>
    /// This function wraps <c>wmemmove</c> when <paramref name="source"/> is non-null and is safe for overlapping memory regions.
    /// If <paramref name="source"/> is null, the destination is filled with zeros.
    /// </para>
    /// </remarks>
    /// <seealso cref="MemCopyOrZero(wchar_t*, const wchar_t*, size_t)"/>
    inline void MemMoveOrZero( wchar_t* dest, const wchar_t* source, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
#endif
            if ( source )
            {
                wmemmove( dest, source, length );
            }
            else
            {
                wmemset( dest, 0, length );
            }
        }
    }

    /// <summary>
    /// Fills a buffer with a specified byte value.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer to fill. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="value">
    /// The byte value to write.
    /// </param>
    /// <param name="length">
    /// The number of bytes to write. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// This function wraps <c>memset</c>.
    /// </remarks>
    inline void MemSet( char* dest, char value, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
#endif
            memset( dest, value, length );
        }
    }
    /// <summary>
    /// Fills a buffer with a specified wide character value.
    /// </summary>
    /// <param name="dest">
    /// Pointer to the destination buffer to fill. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="value">
    /// The wide character value to write.
    /// </param>
    /// <param name="length">
    /// The number of wide characters to write. When zero, the function performs no work.
    /// </param>
    /// <remarks>
    /// This function wraps <c>wmemset</c>.
    /// </remarks>
    inline void MemSet( wchar_t* dest, wchar_t value, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !dest )
            {
                assert( false && "dest is null" );
            }
#endif
            wmemset( dest, value, length );
        }
    }


    /// <summary>
    /// Compares two byte sequences lexicographically.
    /// </summary>
    /// <param name="first">
    /// Pointer to the first buffer to compare. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="second">
    /// Pointer to the second buffer to compare. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="length">
    /// The number of bytes to compare. When zero, the function returns 0.
    /// </param>
    /// <returns>
    /// A negative value if <paramref name="first"/> is less than <paramref name="second"/>,
    /// zero if they are equal, or a positive value if <paramref name="first"/> is greater than <paramref name="second"/>.
    /// </returns>
    /// <remarks>
    /// This function wraps <c>memcmp</c>.
    /// </remarks>
    [[nodiscard]] inline int MemCmp( const char* first, const char* second, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !first )
            {
                assert( false && "first is null" );
            }
            if ( !second )
            {
                assert( false && "second is null" );
            }
#endif
            return memcmp( first, second, length );
        }
		return 0;
    }

    /// <summary>
    /// Compares two byte sequences in a case-insensitive manner.
    /// </summary>
    /// <param name="first">Pointer to the first buffer to compare. Must be non-null when <paramref name="length"/> &gt; 0.</param>
    /// <param name="second">Pointer to the second buffer to compare. Must be non-null when <paramref name="length"/> &gt; 0.</param>
    /// <param name="length">The number of bytes to compare. When zero, the function returns 0.</param>
    /// <returns>
    /// A negative value if <paramref name="first"/> is less than <paramref name="second"/>,
    /// zero if they are equal, or a positive value if <paramref name="first"/> is greater than <paramref name="second"/>.
    /// </returns>
    /// <remarks>
    /// This wrapper calls the platform-specific `_memicmp` implementation for runtime comparisons.
    /// In debug builds the function asserts that pointers are non-null when <paramref name="length"/> &gt; 0.
    /// Zero-length comparisons are treated as equal and return 0.
    /// </remarks>
    [[nodiscard]] inline int MemICmp( const char* first, const char* second, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !first )
            {
                assert( false && "first is null" );
            }
            if ( !second )
            {
                assert( false && "second is null" );
            }
#endif
            return _memicmp( first, second, length );
        }
        return 0;
    }


    /// <summary>
    /// Compares two wide character sequences lexicographically.
    /// </summary>
    /// <param name="first">
    /// Pointer to the first buffer to compare. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="second">
    /// Pointer to the second buffer to compare. Must be non-null if <paramref name="length"/> is greater than zero.
    /// </param>
    /// <param name="length">
    /// The number of wide characters to compare. When zero, the function returns 0.
    /// </param>
    /// <returns>
    /// A negative value if <paramref name="first"/> is less than <paramref name="second"/>,
    /// zero if they are equal, or a positive value if <paramref name="first"/> is greater than <paramref name="second"/>.
    /// </returns>
    /// <remarks>
    /// This function wraps <c>wmemcmp</c>.
    /// </remarks>
    [[nodiscard]] inline int MemCmp( const wchar_t* first, const wchar_t* second, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !first )
            {
                assert( false && "first is null" );
            }
            if ( !second )
            {
                assert( false && "second is null" );
            }
#endif
            return wmemcmp( first, second, length );
        }
		return 0;
    }

    /// <summary>
    /// Case-insensitive comparison of two wide character sequences.
    /// </summary>
    /// <param name="first">Pointer to the first wide character buffer. Must be non-null when <paramref name="second"/> is non-null and <paramref name="length"/> &gt; 0.</param>
    /// <param name="second">Pointer to the second wide character buffer. Must be non-null when <paramref name="first"/> is non-null and <paramref name="length"/> &gt; 0.</param>
    /// <param name="length">The number of wide characters to compare. When zero, the function returns 0.</param>
    /// <returns>
    /// A negative value if <paramref name="first"/> is less than <paramref name="second"/>,
    /// zero if they are equal, or a positive value if <paramref name="first"/> is greater than <paramref name="second"/>.
    /// </returns>
    /// <remarks>
    /// This helper performs a locale-independent, case-insensitive comparison by upper-casing each character
    /// using `std::towupper` and comparing the results. It is used by the wide-character overload of `MemICmp`.
    /// The function does not perform null-termination checks beyond the provided <paramref name="length"/>.
    /// </remarks>
    [[nodiscard]] inline int _wmemicmp( const wchar_t* first, const wchar_t* second, size_t length ) noexcept
    {
        if ( length == 0 )
        {
            return 0;
        }

#ifdef _DEBUG
        if ( !first )
        {
            assert( false && "first is null" );
        }
        if ( !second )
        {
            assert( false && "second is null" );
        }
#endif

        for ( size_t i = 0; i < length; ++i )
        {
            // Use std::towupper which takes/returns wint_t; cast to avoid narrowing.
            wchar_t a = static_cast<wchar_t>( std::towupper( static_cast<wint_t>( first[ i ] ) ) );
            wchar_t b = static_cast<wchar_t>( std::towupper( static_cast<wint_t>( second[ i ] ) ) );
            if ( a < b ) return -1;
            if ( a > b ) return 1;
        }
        return 0;
    }

    /// <summary>
    /// Compares two wide character sequences in a case-insensitive manner.
    /// </summary>
    /// <param name="first">Pointer to the first buffer to compare. Must be non-null when <paramref name="length"/> &gt; 0.</param>
    /// <param name="second">Pointer to the second buffer to compare. Must be non-null when <paramref name="length"/> &gt; 0.</param>
    /// <param name="length">The number of wide characters to compare. When zero, the function returns 0.</param>
    /// <returns>
    /// A negative value if <paramref name="first"/> is less than <paramref name="second"/>,
    /// zero if they are equal, or a positive value if <paramref name="first"/> is greater than <paramref name="second"/>.
    /// </returns>
    /// <remarks>
    /// This function delegates to the internal `_wmemicmp` implementation for runtime comparisons.
    /// In debug builds the function asserts that pointers are non-null when <paramref name="length"/> &gt; 0.
    /// Zero-length comparisons are treated as equal and return 0.
    /// </remarks>
    [[nodiscard]] inline int MemICmp( const wchar_t* first, const wchar_t* second, size_t length ) noexcept
    {
        if ( length )
        {
#ifdef _DEBUG
            if ( !first )
            {
                assert( false && "first is null" );
            }
            if ( !second )
            {
                assert( false && "second is null" );
            }
#endif
            return _wmemicmp( first, second, length );
        }
        return 0;
    }


    /// <summary>
    /// Scans a byte buffer for the first occurrence of the specified byte value.
    /// </summary>
    /// <param name="buffer">
    /// Pointer to the buffer to scan. Must be non-null if <paramref name="bufferSize"/> is greater than zero.
    /// </param>
    /// <param name="value">
    /// The byte value to search for, converted to <c>unsigned char</c> for comparison.
    /// </param>
    /// <param name="bufferSize">
    /// The number of bytes to examine. When zero, the function returns <c>nullptr</c>.
    /// </param>
    /// <returns>
    /// A pointer to the first occurrence of <paramref name="value"/> within the specified range, or <c>nullptr</c> if not found.
    /// </returns>
    /// <remarks>
    /// This function wraps <c>memchr</c>.
    /// </remarks>
    [[nodiscard]] inline char* MemChr( char* buffer, int value, size_t bufferSize ) noexcept
    {
        if ( bufferSize )
        {
#ifdef _DEBUG
            if ( !buffer )
            {
                assert( false && "buffer is null" );
            }
#endif
            return (char*)memchr( buffer, value, bufferSize );
        }
		return nullptr;
    }

    /// <summary>
    /// Scans a byte buffer for the first occurrence of the specified byte value.
    /// </summary>
    /// <param name="buffer">
    /// Pointer to the buffer to scan. Must be non-null if <paramref name="bufferSize"/> is greater than zero.
    /// </param>
    /// <param name="value">
    /// The byte value to search for, converted to <c>unsigned char</c> for comparison.
    /// </param>
    /// <param name="bufferSize">
    /// The number of bytes to examine. When zero, the function returns <c>nullptr</c>.
    /// </param>
    /// <returns>
    /// A pointer to the first occurrence of <paramref name="value"/> within the specified range, or <c>nullptr</c> if not found.
    /// </returns>
    /// <remarks>
    /// This function wraps <c>memchr</c>.
    /// </remarks>
    [[nodiscard]] inline const char* MemChr( const char* buffer, int value, size_t bufferSize ) noexcept
    {
        if ( bufferSize )
        {
#ifdef _DEBUG
            if ( !buffer )
            {
                assert( false && "buffer is null" );
            }
#endif
            return (const char*)memchr( buffer, value, bufferSize );
        }
		return nullptr;
    }

    /// <summary>
    /// Scans a wide character buffer for the first occurrence of the specified wide character value.
    /// </summary>
    /// <param name="buffer">
    /// Pointer to the buffer to scan. Must be non-null if <paramref name="bufferSize"/> is greater than zero.
    /// </param>
    /// <param name="value">
    /// The wide character value to search for.
    /// </param>
    /// <param name="bufferSize">
    /// The number of wide characters to examine. When zero, the function returns <c>nullptr</c>.
    /// </param>
    /// <returns>
    /// A pointer to the first occurrence of <paramref name="value"/> within the specified range, or <c>nullptr</c> if not found.
    /// </returns>
    /// <remarks>
    /// This function wraps <c>wmemchr</c>.
    /// </remarks>
    [[nodiscard]] inline wchar_t* MemChr( wchar_t* buffer, int value, size_t bufferSize ) noexcept
    {
        if ( bufferSize )
        {
#ifdef _DEBUG
            if ( !buffer )
            {
                assert( false && "buffer is null" );
            }
#endif
            return (wchar_t*)wmemchr( buffer, value, bufferSize );
        }
		return nullptr;
    }

    /// <summary>
    /// Scans a wide character buffer for the first occurrence of the specified wide character value.
    /// </summary>
    /// <param name="buffer">
    /// Pointer to the buffer to scan. Must be non-null if <paramref name="bufferSize"/> is greater than zero.
    /// </param>
    /// <param name="value">
    /// The wide character value to search for.
    /// </param>
    /// <param name="bufferSize">
    /// The number of wide characters to examine. When zero, the function returns <c>nullptr</c>.
    /// </param>
    /// <returns>
    /// A pointer to the first occurrence of <paramref name="value"/> within the specified range, or <c>nullptr</c> if not found.
    /// </returns>
    /// <remarks>
    /// This function wraps <c>wmemchr</c>.
    /// </remarks>
    [[nodiscard]] inline const wchar_t* MemChr( const wchar_t* buffer, int value, size_t bufferSize ) noexcept
    {
        if ( bufferSize )
        {
#ifdef _DEBUG
            if ( !buffer )
            {
                assert( false && "buffer is null" );
            }
#endif
            return (const wchar_t*)wmemchr( buffer, value, bufferSize );
		}
		return nullptr;
    }



    /// <summary>
    /// Gets the number of elements in a fixed-size array.
    /// </summary>
    /// <typeparam name="T">
    /// The array element type. Must not be <c>char</c> or <c>wchar_t</c>.
    /// </typeparam>
    /// <typeparam name="N">
    /// The compile-time known array length.
    /// </typeparam>
    /// <param name="array">
    /// Reference to the array.
    /// </param>
    /// <returns>
    /// The number of elements in <paramref name="array"/>.
    /// </returns>
    template<typename T, size_t N>
        requires ( std::is_same_v<char, std::remove_cv_t<T>> == false && std::is_same_v<wchar_t, std::remove_cv_t<T>> == false )
    [[nodiscard]] inline constexpr size_t LengthOf( T( &array )[ N ] ) noexcept
    {
        return N;
    }

    /// <summary>
    /// Gets the number of elements in a container exposing a <c>size()</c> member function.
    /// </summary>
    /// <typeparam name="T">
    /// The container type providing a <c>size()</c> member returning a value convertible to <c>size_t</c>.
    /// </typeparam>
    /// <param name="container">
    /// The container instance.
    /// </param>
    /// <returns>
    /// The result of <c>container.size()</c>.
    /// </returns>
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

    /// <summary>
    /// Computes the length of a null-terminated string for character types supported by this overload.
    /// </summary>
    /// <typeparam name="T">
    /// The character type. Must be <c>char</c> or <c>wchar_t</c>.
    /// </typeparam>
    /// <param name="str">
    /// Pointer to a null-terminated string. If null or the first character is the null terminator, zero is returned.
    /// </param>
    /// <returns>
    /// The number of characters excluding the null terminator; returns 0 for null or empty strings.
    /// </returns>
    /// <remarks>
    /// <para>
    /// This calls into implementation-specific overloads that use <c>std::string_view</c>/<c>std::wstring_view</c> in constant-evaluated contexts,
    /// and <c>strlen</c>/<c>wcslen</c> at runtime.
    /// </para>
    /// </remarks>
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