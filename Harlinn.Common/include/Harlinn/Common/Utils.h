#pragma once
#ifndef HARLINN_COMMON_UTILS_H_
#define HARLINN_COMMON_UTILS_H_

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

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif

#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cwctype>
#include <limits>
#include <string_view>

#include "Concepts.h"

namespace Harlinn::Common
{
    /// <summary>
    /// Evaluates to true when the type `T`, after removing cv-qualifiers and references,
    /// is not the boolean type (`bool`).
    /// </summary>
    /// <typeparam name="T">
    /// The type to test. CV-qualifiers and references are ignored.
    /// </typeparam>
    template<typename T>
    inline constexpr bool IsNotBoolean = std::is_same_v<std::remove_cvref_t<T>, bool> == false;

    /// <summary>
    /// Evaluates to true when the type <c>T</c>, after removing cv-qualifiers and references,
    /// is the boolean type (<c>bool</c>).
    /// </summary>
    /// <typeparam name="T">
    /// The type to test. CV-qualifiers and references are ignored.
    /// </typeparam>
    template<typename T>
    inline constexpr bool IsBoolean = std::is_same_v<std::remove_cvref_t<T>, bool>;

    /// <summary>
    /// Evaluates to true when the type <c>T</c>, after removing cv-qualifiers and references,
    /// is an integral type and is not the boolean type (<c>bool</c>).
    /// </summary>
    /// <typeparam name="T">
    /// The type to test. CV-qualifiers and references are ignored. Boolean is excluded.
    /// </typeparam>
    template<typename T>
    inline constexpr bool IsInteger = std::is_integral_v<std::remove_cvref_t<T>> && IsBoolean<T> == false;

    /// <summary>
    /// Evaluates to true when the type <c>T</c>, after removing cv-qualifiers and references,
    /// is a signed integral type (boolean excluded).
    /// </summary>
    /// <typeparam name="T">
    /// The type to test. CV-qualifiers and references are ignored.
    /// </typeparam>
    template<typename T>
    inline constexpr bool IsSignedInteger = IsInteger<T> && std::is_signed_v<std::remove_cvref_t<T>>;

    /// <summary>
    /// Evaluates to true when the type <c>T</c>, after removing cv-qualifiers and references,
    /// is an unsigned integral type (boolean excluded).
    /// </summary>
    /// <typeparam name="T">
    /// The type to test. CV-qualifiers and references are ignored.
    /// </typeparam>
    template<typename T>
    inline constexpr bool IsUnsignedInteger = IsInteger<T> && std::is_unsigned_v<std::remove_cvref_t<T>>;

    /// <summary>
    /// Evaluates to true when the type <c>T</c>, after removing cv-qualifiers and references,
    /// is a floating-point type.
    /// </summary>
    /// <typeparam name="T">The type to test. CV-qualifiers and references are ignored.</typeparam>
    template<typename T>
    inline constexpr bool IsFloatingPoint = std::is_floating_point_v<std::remove_cvref_t<T>>;

    /// <summary>
    /// Evaluates to true when the type <c>T</c> is either an integral type (excluding <c>bool</c>)
    /// or a floating-point type. CV-qualifiers and references are removed before testing.
    /// </summary>
    /// <typeparam name="T">The type to test. CV-qualifiers and references are ignored.</typeparam>
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


    /// <summary>
    /// Maps a type to an unsigned integer type with the same storage size.
    /// </summary>
    /// <typeparam name="T">Source type. CV-qualifiers and references are ignored when determining the size.</typeparam>
    /// <remarks>
    /// This alias uses the `Internal::MakeUnsignedHelper` specializations for sizes 1, 2, 4 and 8
    /// to select the appropriate unsigned integer type (`Byte`, `UInt16`, `UInt32`, `UInt64`).
    /// The resulting type is typically used to manipulate the bit-pattern representation of `T`.
    /// </remarks>
    template<typename T>
    using MakeUnsigned = typename Internal::MakeUnsignedHelper< sizeof( T ) >::Type;

    /// <summary>
    /// Bit mask selecting the fraction (mantissa) bits for the storage type corresponding to <c>T</c>.
    /// </summary>
    /// <typeparam name="T">
    /// The source type whose bit-pattern is being described. CV-qualifiers and references are ignored.
    /// </typeparam>
    /// <typeparam name="U">
    /// Unsigned integer type used to represent the bit-pattern of <c>T</c>. 
    /// Defaults to <c>MakeUnsigned&lt;std::remove_cvref_t&lt;T&gt;&gt;</c>.
    /// </typeparam>
    /// <returns>
    /// The mask value with all fraction/mantissa bits set for type <c>U</c>. 
    /// The primary template defaults to all ones.
    /// </returns>
    /// <remarks>
    /// Primary template yields <c>std::numeric_limits&lt;U&gt;::max()</c>. 
    /// Specializations provide precise IEEE-754 masks for
    /// single- and double-precision floating-point types.
    /// </remarks>
    template<typename T, typename U = MakeUnsigned< std::remove_cvref_t<T> > >
    inline constexpr U FractionMask = std::numeric_limits<U>::max( );

    /// <summary>
    /// Bit mask selecting the exponent bits for the storage type corresponding to <c>T</c>.
    /// </summary>
    /// <typeparam name="T">
    /// The source type whose bit-pattern is being described. CV-qualifiers 
    /// and references are ignored.
    /// </typeparam>
    /// <typeparam name="U">
    /// Unsigned integer type used to represent the bit-pattern of <c>T</c>. 
    /// Defaults to <c>MakeUnsigned&lt;std::remove_cvref_t&lt;T&gt;&gt;</c>.
    /// </typeparam>
    /// <returns>
    /// The mask value with exponent bits set for type <c>U</c>. 
    /// The primary template defaults to zero.
    /// </returns>
    /// <remarks>
    /// Primary template yields zero; specializations provide the 
    /// IEEE-754 exponent masks for float and double.
    /// </remarks>
    template<typename T, typename U = MakeUnsigned< std::remove_cvref_t<T> > >
    inline constexpr U ExponentMask = 0;

    /// <summary>
    /// Fraction (mantissa) mask specialization for IEEE-754 single-precision (<c>float</c>).
    /// </summary>
    /// <typeparam name="float">
    /// The floating-point type being described.
    /// </typeparam>
    /// <typeparam name="UInt32">
    /// The unsigned integer type used to represent the <c>float</c> bit-pattern.
    /// </typeparam>
    /// <returns>
    /// The 32-bit mask selecting the 23 fraction bits of an IEEE-754 single-precision float.
    /// </returns>
    /// <remarks>
    /// The binary literal has the lower 23 bits set (mantissa). 
    /// <c>std::bit_cast</c> is used to ensure the constant is of type <c>UInt32</c>.
    /// </remarks>
    template<>
    inline constexpr UInt32 FractionMask<float, UInt32> = std::bit_cast< UInt32 >( 0b00000000011111111111111111111111 );
    
    /// <summary>
    /// Exponent mask specialization for IEEE-754 single-precision (<c>float</c>).
    /// </summary>
    /// <typeparam name="float">
    /// The floating-point type being described.
    /// </typeparam>
    /// <typeparam name="UInt32">
    /// The unsigned integer type used to represent the <c>float</c> bit-pattern.
    /// </typeparam>
    /// <returns>
    /// The 32-bit mask selecting the 8 exponent bits of an IEEE-754 single-precision float.
    /// </returns>
    /// <remarks>
    /// The binary literal corresponds to the exponent field (8 bits) positioned in the IEEE-754 single-precision layout.
    /// </remarks>
    template<>
    inline constexpr UInt32 ExponentMask<float, UInt32> = std::bit_cast< UInt32 >( 0b01111111100000000000000000000000 );

    /// <summary>
    /// Fraction (mantissa) mask specialization for IEEE-754 double-precision (<c>double</c>).
    /// </summary>
    /// <typeparam name="double">The floating-point type being described.</typeparam>
    /// <typeparam name="UInt64">The unsigned integer type used to represent the <c>double</c> bit-pattern.</typeparam>
    /// <returns>The 64-bit mask selecting the 52 fraction bits of an IEEE-754 double-precision value.</returns>
    /// <remarks>
    /// The binary literal has the lower 52 bits set (mantissa). <c>std::bit_cast</c> ensures the constant is of type <c>UInt64</c>.
    /// </remarks>
    template<>
    inline constexpr UInt64 FractionMask<double, UInt64> = std::bit_cast< UInt64 >( 0b0000000000001111111111111111111111111111111111111111111111111111 );
    
    /// <summary>
    /// Exponent mask specialization for IEEE-754 double-precision (<c>double</c>).
    /// </summary>
    /// <typeparam name="double">The floating-point type being described.</typeparam>
    /// <typeparam name="UInt64">The unsigned integer type used to represent the <c>double</c> bit-pattern.</typeparam>
    /// <returns>The 64-bit mask selecting the 11 exponent bits of an IEEE-754 double-precision value.</returns>
    /// <remarks>
    /// The binary literal corresponds to the exponent field (11 bits) positioned in the IEEE-754 double-precision layout.
    /// </remarks>
    template<>
    inline constexpr UInt64 ExponentMask<double, UInt64> = std::bit_cast< UInt64 >( 0b0111111111110000000000000000000000000000000000000000000000000000 );



#pragma pack(push,1)
    /// <summary>
    /// Represents an 8-bit storage unit exposing the raw byte value.
    /// </summary>
    /// <remarks>
    /// This type is a simple wrapper around a single <c>Byte</c> and is used when explicit 8-bit
    /// access is required (for example bitwise operations or byte-level views).
    /// </remarks>
    struct Bits8
    {
        /// <summary>
        /// The underlying 8-bit value.
        /// </summary>
        Byte Value;
    };

    /// <summary>
    /// Represents a 16-bit storage view that can be accessed as two bytes or as a 16-bit value.
    /// </summary>
    /// <remarks>
    /// The anonymous struct provides low/high byte access. Use <c>Low</c> and <c>High</c> for byte-wise
    /// manipulation and <c>Value</c> to treat the two bytes as a single <c>UInt16</c> value.
    /// The layout relies on the surrounding <c>#pragma pack(push,1)</c> to define packing.
    /// </remarks>
    union Bits16
    {
        struct
        {
            /// <summary>
            /// The low-order byte (least significant byte) of the 16-bit storage.
            /// </summary>
            Byte Low;
            /// <summary>
            /// The high-order byte (most significant byte) of the 16-bit storage.
            /// </summary>
            Byte High;
        };
        /// <summary>
        /// The 16-bit unsigned view of the storage.
        /// </summary>
        UInt16 Value;
    };

    /// <summary>
    /// Represents a 32-bit storage view that can be accessed as two 16-bit halves, a 32-bit unsigned value,
    /// a 32-bit signed integer, or a single-precision floating-point value.
    /// </summary>
    /// <remarks>
    /// Use the <c>Low</c> and <c>High</c> members to access the lower and upper 16-bit halves respectively.
    /// The union provides multiple interpretations of the same 32-bit bit-pattern without changing memory.
    /// </remarks>
    union Bits32
    {
        struct
        {
            /// <summary>
            /// The lower 16-bit half of the 32-bit storage.
            /// </summary>
            Bits16 Low;
            /// <summary>
            /// The upper 16-bit half of the 32-bit storage.
            /// </summary>
            Bits16 High;
        };
        /// <summary>
        /// The 32-bit unsigned integer view of the storage.
        /// </summary>
        UInt32 Value;
        /// <summary>
        /// The 32-bit signed integer view of the storage.
        /// </summary>
        Int32 Int32Value;
        /// <summary>
        /// The 32-bit single-precision floating-point view of the storage.
        /// </summary>
        Single SingleValue;
    };

    /// <summary>
    /// Represents a 64-bit storage view that can be accessed as two 32-bit halves, a 64-bit unsigned value,
    /// a 64-bit signed integer, or a double-precision floating-point value.
    /// </summary>
    /// <remarks>
    /// Use <c>Low</c> and <c>High</c> to manipulate the lower and upper 32-bit halves. The union permits
    /// reinterpretation of the underlying 64-bit bit-pattern as different scalar types without casting.
    /// </remarks>
    union Bits64
    {
        struct
        {
            /// <summary>
            /// The lower 32-bit half of the 64-bit storage.
            /// </summary>
            Bits32 Low;
            /// <summary>
            /// The upper 32-bit half of the 64-bit storage.
            /// </summary>
            Bits32 High;
        };
        /// <summary>
        /// The 64-bit unsigned integer view of the storage.
        /// </summary>
        UInt64 Value;
        /// <summary>
        /// The 64-bit signed integer view of the storage.
        /// </summary>
        Int64 Int64Value;
        /// <summary>
        /// The 64-bit double-precision floating-point view of the storage.
        /// </summary>
        Double DoubleValue;
    };

#pragma pack(pop)


    namespace Internal
    {
        template<typename T>
        inline constexpr T ByteSwapImpl( T value )
        {
            constexpr std::size_t S = sizeof( T );
            using ByteArray = std::array<unsigned char, S>;
            ByteArray bytes = std::bit_cast<ByteArray>( value );

            // Reverse bytes in-place
            for ( std::size_t i = 0; i < S / 2; ++i )
            {
                unsigned char tmp = bytes[ i ];
                bytes[ i ] = bytes[ S - 1 - i ];
                bytes[ S - 1 - i ] = tmp;
            }
            return std::bit_cast<T>( bytes );
        }
    }

    /// <summary>
    /// Reverses the order of bytes in an integral value.
    /// </summary>
    /// <typeparam name="T">
    /// An integral type. CV-qualifiers and references are ignored. The type must satisfy the <c>IntegerType</c> concept.
    /// </typeparam>
    /// <param name="value">
    /// The integral value whose byte order will be reversed.
    /// </param>
    /// <returns>
    /// The value produced by reversing the byte order of <paramref name="value"/>.
    /// </returns>
    /// <remarks>
    /// <para>
    /// In a constant-evaluated context the byte reversal is performed 
    /// using a constexpr algorithm implemented by <c>Internal::ByteSwapImpl</c> 
    /// operating on the unsigned bit-pattern of <typeparamref name="T"/>.
    /// </para>
    /// <para>
    /// At runtime the implementation dispatches to platform-specific intrinsics for performance:
    /// <c>_byteswap_ushort</c>, <c>_byteswap_ulong</c>, and <c>_byteswap_uint64</c> are used for 2-, 4- and 8-byte
    /// storage sizes respectively. For 1-byte types the original value is returned unchanged.
    /// </para>
    /// <para>
    /// The function uses <c>std::bit_cast</c> to safely reinterpret between signed and unsigned representations
    /// without invoking undefined behavior. The caller must ensure <typeparamref name="T"/> models the
    /// <c>IntegerType</c> concept defined in <c>Concepts.h</c>.
    /// </para>
    /// </remarks>
    template<IntegerType T>
    inline constexpr T ByteSwap( T value )
    {
        if ( std::is_constant_evaluated( ) )
        {
            return std::bit_cast< T >( Internal::ByteSwapImpl( std::bit_cast< std::make_unsigned_t<T> >( value ) ) );
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
        std::bit_cast<Type>( ByteSwap( std::bit_cast<UIntType>( value ) ) );
    }


    /// <summary>
    /// Compile-time helper that provides a bit-mask value and a sized integer type for a mask width.
    /// </summary>
    /// <typeparam name="N">The number of bits in the mask. Must be in the range [0,64].</typeparam>
    /// <remarks>
    /// The nested <c>type</c> alias selects the smallest unsigned integer type that can hold <c>N</c> bits:
    /// - <= 8 -> <c>Byte</c>
    /// - <= 16 -> <c>UInt16</c>
    /// - <= 32 -> <c>UInt32</c>
    /// - otherwise -> <c>UInt64</c>.
    /// The static constexpr <c>value</c> contains a mask with the lowest <c>N</c> bits set when <c>N != 0</c>.
    /// </remarks>
    template<size_t N>
    struct BitMask
    {
        static_assert( N <= 64, "Unsupported bit-mask width" );
        
        /// <summary>
        /// Unsigned integer type capable of holding <c>N</c> bits.
        /// </summary>
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

        /// <summary>
        /// The bit-mask value with the lowest <c>N</c> bits set.
        /// </summary>
        /// <remarks>
        /// If <c>N == 0</c> the value is zero. For <c>N &gt; 0</c> the expression computes
        /// a mask with the least-significant <c>N</c> bits set to one.
        /// </remarks>
        static constexpr type value = N ? ( ( static_cast< type >( 1 ) << ( N - 1 ) ) - 1 ) ^ ( static_cast< type >( 1 ) << ( N - 1 ) ) : 0;
    };

    /// <summary>
    /// Variable template convenience that yields <c>BitMask&lt;N&gt;::value</c>.
    /// </summary>
    /// <typeparam name="N">
    /// The number of bits in the mask.
    /// </typeparam>
    template<size_t N>
    inline constexpr auto BitMask_v = BitMask<N>::value;
    
    /// <summary>
    /// Alias for the integer type selected by <c>BitMask&lt;N&gt;</c>.
    /// </summary>
    /// <typeparam name="N">The number of bits the type must be able to represent.</typeparam>
    template<size_t N>
    using BitMask_t = typename BitMask<N>::type;

    /// <summary>
    /// Produces a value of type <c>T</c> with the lowest <c>N</c> bits set to one (trailing ones).
    /// </summary>
    /// <typeparam name="T">An integer type (signed or unsigned). CV-qualifiers and references are ignored.</typeparam>
    /// <typeparam name="N">Number of trailing one bits to set. Must be <= <c>CHAR_BIT * sizeof(T)</c>.</typeparam>
    /// <returns>
    /// A value of type <c>T</c> where the least-significant <c>N</c> bits are ones and all higher bits are zero.
    /// </returns>
    /// <remarks>
    /// The implementation uses <c>BitMask_v&lt;N&gt;</c> for the mask and <c>std::bit_cast</c> to safely convert between
    /// signed and unsigned representations.
    /// </remarks>
    template <IntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskTrailingOnes( )
    {
        return std::bit_cast< T >( static_cast< std::make_unsigned_t<T> >( BitMask_v<N> ) );
    }

    /// <summary>
    /// Produces a value of type <c>T</c> with the highest <c>N</c> bits set to one (leading ones).
    /// </summary>
    /// <typeparam name="T">An integer type (signed or unsigned). CV-qualifiers and references are ignored.</typeparam>
    /// <typeparam name="N">Number of leading one bits to set. Must be <= <c>CHAR_BIT * sizeof(T)</c>.</typeparam>
    /// <returns>
    /// A value of type <c>T</c> where the most-significant <c>N</c> bits are ones and all lower bits are zero.
    /// </returns>
    /// <remarks>
    /// The result is computed by creating a mask for the complementary width and inverting it.
    /// Uses <c>std::bit_cast</c> and unsigned arithmetic to avoid undefined behavior when manipulating signed types.
    /// </remarks>
    template <IntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskLeadingOnes( )
    {
        return std::bit_cast< T >( static_cast< std::make_unsigned_t<T> >( ~BitMask_v<( CHAR_BIT * sizeof( T ) ) - N> ) );
    }


    /// <summary>
    /// Produces a value of type <c>T</c> with the lowest <c>N</c> bits cleared (trailing zeros) and all other bits set.
    /// </summary>
    /// <typeparam name="T">An integer type (signed or unsigned). CV-qualifiers and references are ignored.</typeparam>
    /// <typeparam name="N">Number of trailing zero bits. Must be <= <c>CHAR_BIT * sizeof(T)</c>.</typeparam>
    /// <returns>
    /// A value of type <c>T</c> where the least-significant <c>N</c> bits are zero and all higher bits are one.
    /// </returns>
    /// <remarks>
    /// Implemented as the bitwise complement of <c>BitMask_v&lt;N&gt;</c>, cast back to <c>T</c> via <c>std::bit_cast</c>.
    /// </remarks>
    template <IntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskTrailingZeros( )
    {
        return std::bit_cast< T >( static_cast< std::make_unsigned_t<T> >( ~BitMask_v<N> ) );
    }

    /// <summary>
    /// Produces a value of type <c>T</c> with the highest <c>N</c> bits cleared (leading zeros) and all other bits set.
    /// </summary>
    /// <typeparam name="T">An integer type (signed or unsigned). CV-qualifiers and references are ignored.</typeparam>
    /// <typeparam name="N">Number of leading zero bits. Must be <= <c>CHAR_BIT * sizeof(T)</c>.</typeparam>
    /// <returns>
    /// A value of type <c>T</c> where the most-significant <c>N</c> bits are zero and all lower bits are one.
    /// </returns>
    /// <remarks>
    /// This function uses <c>BitMask_v&lt;(CHAR_BIT * sizeof(T)) - N&gt;</c> to compute the mask for the lower bits,
    /// then casts to <c>T</c> using <c>std::bit_cast</c>.
    /// </remarks>
    template <IntegerType T, size_t N>
        requires ( N <= CHAR_BIT * sizeof( T ) )
    constexpr T MaskLeadingZeros( )
    {
        return std::bit_cast< T >( BitMask_v<( CHAR_BIT * sizeof( T ) ) - N> );
    }


    inline constexpr Byte ReverseBits( Byte b ) noexcept
    {
        /*
         * From: https://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64BitsDiv
         */
        b = static_cast< Byte >( ( static_cast< UInt64 >( b ) * 0x0202020202ULL & 0x010884422010ULL ) % 1023 );
        return b;
    }

    inline constexpr SByte ReverseBits( SByte b ) noexcept
    {
        return std::bit_cast< SByte >( ReverseBits( std::bit_cast< Byte >( b ) ) );
    }
    inline constexpr char ReverseBits( char b ) noexcept
    {
        return std::bit_cast< char >( ReverseBits( std::bit_cast< Byte >( b ) ) );
    }

    /// <summary>
    /// Reverses the order of the bits of an 16-bit unsigned value.
    /// </summary>
    /// <param name="val">
    /// The 16-bit value whose bits will be reversed.
    /// </param>
    /// <returns>
    /// The bit-reversed value.
    /// </returns>
    inline constexpr UInt16 ReverseBits( UInt16 val ) noexcept
    {
        // Extract low and high bytes, reverse each byte and swap
        UInt16 lowByte = static_cast<UInt16>( static_cast<Byte>( val & 0x00FF ) );
        UInt16 highByte = static_cast<UInt16>( static_cast<Byte>( val >> 8 ) );

        UInt16 revLow = static_cast<UInt16>( ReverseBits( static_cast<Byte>( lowByte ) ) );
        UInt16 revHigh = static_cast<UInt16>( ReverseBits( static_cast<Byte>( highByte ) ) );

        return static_cast<UInt16>( ( revLow << 8 ) | revHigh );
    }
    inline constexpr Int16 ReverseBits( Int16 val ) noexcept
    {
        return std::bit_cast< Int16 >( ReverseBits( std::bit_cast< UInt16 >( val ) ) );
    }
    inline constexpr wchar_t ReverseBits( wchar_t val ) noexcept
    {
        return std::bit_cast< wchar_t >( ReverseBits( std::bit_cast< UInt16 >( val ) ) );
    }

    /// <summary>
    /// Reverses the order of the bits of an UInt32 value.
    /// </summary>
    /// <param name="val">The 32-bit value whose bits will be reversed.</param>
    /// <returns>The bit-reversed 32-bit value.</returns>
    inline constexpr UInt32 ReverseBits( UInt32 val ) noexcept
    {
        // Split into 16-bit halves, reverse each half (which in turn reverses bytes and bits)
        UInt32 low = static_cast<UInt32>( static_cast<UInt16>( val & 0xFFFFu ) );
        UInt32 high = static_cast<UInt32>( static_cast<UInt16>( val >> 16 ) );

        UInt32 revLow = static_cast<UInt32>( ReverseBits( static_cast<UInt16>( low ) ) );
        UInt32 revHigh = static_cast<UInt32>( ReverseBits( static_cast<UInt16>( high ) ) );

        return ( revLow << 16 ) | revHigh;
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
        UInt64 low = static_cast<UInt64>( static_cast<UInt32>( val & 0xFFFFFFFFULL ) );
        UInt64 high = static_cast<UInt64>( static_cast<UInt32>( val >> 32 ) );

        UInt64 revLow = static_cast<UInt64>( ReverseBits( static_cast<UInt32>( low ) ) );
        UInt64 revHigh = static_cast<UInt64>( ReverseBits( static_cast<UInt32>( high ) ) );

        return ( revLow << 32 ) | revHigh;
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
    /// <summary>
    /// Search the mask data from least significant bit (LSB) to the most significant bit (MSB) for a set bit (1).
    /// </summary>
    /// <param name="index">Optional pointer that will receive the zero-based index of the found bit. May be null.</param>
    /// <param name="bits">Integer value to search (CV-qualifiers and references are ignored).</param>
    /// <returns>True if a set bit was found; otherwise false. When true and <paramref name="index"/> is non-null the index is written.</returns>
    /// <remarks>
    /// - Uses a constexpr fast-path (`std::countr_zero`) for constant evaluation and platform intrinsics
    ///   (`_BitScanForward` / `_BitScanForward64`) for runtime on MSVC for best performance.
    /// - Operates on the unsigned bit-pattern of `T` via `std::bit_cast` to avoid UB when `T` is signed.
    /// </remarks>
    template<IntegerType T>
    constexpr bool IndexOfBitFromLSB( unsigned long* index, T bits )
    {
        using UIntType = std::make_unsigned_t<T>;
        // Work on the unsigned bit-pattern
        const UIntType valueU = std::bit_cast<UIntType>( bits );

        if ( std::is_constant_evaluated( ) )
        {
            // Constant-eval: use std::countr_zero (constexpr) instead of manual loop.
            if ( valueU == static_cast<UIntType>( 0 ) )
            {
                return false;
            }
            // std::countr_zero is well-defined for unsigned integer types and is constexpr.
            unsigned long idx = static_cast<unsigned long>( std::countr_zero( valueU ) );
            if ( index )
            {
                *index = idx;
            }
            return true;
        }
        else
        {
            // Runtime: dispatch to MSVC intrinsics for performance.
            if constexpr ( sizeof( UIntType ) > 4 )
            {
                // Use 64-bit intrinsic. Cast the value to UInt64 to match intrinsic signature.
                auto v = std::bit_cast<UInt64>( bits );
                return _BitScanForward64( index, v ) != 0;
            }
            else
            {
                // Use 32-bit intrinsic. Ensure the value is passed as unsigned long (DWORD).
                auto v = static_cast<unsigned long>( valueU );
                return _BitScanForward( index, v ) != 0;
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
    /// <param name="index">Optional pointer that will receive the zero-based index of the found bit. May be null.</param>
    /// <param name="bits">Integer value to search (CV-qualifiers and references are ignored).</param>
    /// <returns>True if a set bit was found; otherwise false. When true and <paramref name="index"/> is non-null the index is written.</returns>
    /// <remarks>
    /// - In constant-evaluated contexts uses <c>std::bit_width</c> (constexpr) to compute the index in O(1).
    /// - At runtime dispatches to MSVC intrinsics <c>_BitScanReverse</c>/<c>_BitScanReverse64</c> for maximum performance on Windows/x64.
    /// - Operates on the unsigned bit-pattern of <c>T</c> via <c>std::bit_cast</c> to avoid signed-shift UB.
    /// </remarks>
    template<IntegerType T>
    constexpr bool IndexOfBitFromMSB( unsigned long* index, T bits )
    {
        using UIntType = std::make_unsigned_t<T>;
        const UIntType valueU = std::bit_cast<UIntType>( bits );

        if ( std::is_constant_evaluated( ) )
        {
            if ( valueU == static_cast<UIntType>( 0 ) )
            {
                return false;
            }
            // std::bit_width(valueU) returns floor(log2(valueU)) + 1 for valueU > 0
            unsigned long idx = static_cast<unsigned long>( std::bit_width( valueU ) - 1u );
            if ( index )
            {
                *index = idx;
            }
            return true;
        }
        else
        {
#ifdef _MSC_VER
            if constexpr ( sizeof( UIntType ) > 4 )
            {
                UInt64 v = std::bit_cast<UInt64>( bits );
                unsigned long tmpIndex = 0;
                const auto rc = _BitScanReverse64( &tmpIndex, v );
                if ( rc != 0 )
                {
                    if ( index )
                    {
                        *index = tmpIndex;
                    }
                    return true;
                }
                return false;
            }
            else
            {
                unsigned long v = static_cast<unsigned long>( valueU );
                unsigned long tmpIndex = 0;
                const auto rc = _BitScanReverse( &tmpIndex, v );
                if ( rc != 0 )
                {
                    if ( index )
                    {
                        *index = tmpIndex;
                    }
                    return true;
                }
                return false;
            }
#else
            if ( valueU == static_cast<UIntType>( 0 ) )
            {
                return false;
            }
            unsigned long idx = static_cast<unsigned long>( std::bit_width( valueU ) - 1u );
            if ( index )
            {
                *index = idx;
            }
            return true;
#endif
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
            // Keep the original assertion semantics in debug builds, but function remains well-defined in release.
            assert( numberOfBitsToSet <= 64 && "The value of numberOfBitsToSet must be in the range [0,64]" );
        }
#endif

        // Handle edge cases explicitly to avoid undefined behavior from shifts:
        if ( numberOfBitsToSet == 0 )
        {
            return 0ULL;
        }
        if ( numberOfBitsToSet >= 64 )
        {
            return static_cast<UInt64>( ~static_cast<UInt64>( 0 ) ); // all ones
        }

        // Now 1 <= numberOfBitsToSet <= 63
        if ( std::is_constant_evaluated( ) )
        {
            // Constexpr-friendly arithmetic: (1 << n) - 1
            return ( ( static_cast<UInt64>( 1 ) << numberOfBitsToSet ) - 1ULL );
        }
        else
        {
#ifdef _MSC_VER
            // Runtime: use BLSMSK intrinsic for best performance on MSVC.
            // BLSMSK(msb) produces a mask with all bits <= the provided single set bit set;
            // provide the bit at position (n-1).
            UInt64 msb = static_cast<UInt64>( 1 ) << ( numberOfBitsToSet - 1 );
            return _blsmsk_u64( msb );
#else
            // Portable runtime fallback: same as consteval arithmetic
            return ( ( static_cast<UInt64>( 1 ) << numberOfBitsToSet ) - 1ULL );
#endif
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
            // Preserve developer assertion in debug builds; production still behaves safely for out-of-range inputs.
            assert( numberOfBitsToSet <= 32 && "The value of numberOfBitsToSet must be in the range [0,32]" );
        }
#endif

        // Avoid undefined behaviour: handle 0 and >=32 explicitly
        if ( numberOfBitsToSet == 0 )
        {
            return 0u;
        }
        if ( numberOfBitsToSet >= 32 )
        {
            return static_cast<UInt32>( ~static_cast<UInt32>( 0 ) ); // 0xFFFFFFFFu
        }

        // Now 1 <= numberOfBitsToSet <= 31
        if ( std::is_constant_evaluated( ) )
        {
            // Constexpr-friendly: (1u << n) - 1
            return ( ( static_cast<UInt32>( 1u ) << numberOfBitsToSet ) - 1u );
        }
        else
        {
#ifdef _MSC_VER
            // Runtime: use BLSMSK intrinsic on MSVC for best performance.
            // Provide the single-bit value at position (n-1).
            UInt32 msb = static_cast<UInt32>( 1u ) << ( numberOfBitsToSet - 1 );
            return _blsmsk_u32( msb );
#else
            // Portable runtime fallback
            return ( ( static_cast<UInt32>( 1u ) << numberOfBitsToSet ) - 1u );
#endif
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
        if ( len == 0 || start >= 64 )
        {
            return 0ULL;
        }
        const uint64_t start64 = static_cast<uint64_t>( start );
        const uint64_t len64 = static_cast<uint64_t>( len );
        const uint64_t maxAvailable = 64u - start64;
        const uint64_t effectiveLen = ( len64 > maxAvailable ) ? maxAvailable : len64;

        if ( std::is_constant_evaluated( ) )
        {
            UInt64 mask = CreateBitMask64( static_cast<unsigned>( effectiveLen ) );
            return ( value >> start ) & mask;
        }
        else
        {
#ifdef _MSC_VER
            return _bextr_u64( value, static_cast<unsigned long>( start ), static_cast<unsigned long>( effectiveLen ) );
#else
            UInt64 mask = CreateBitMask64( static_cast<unsigned>( effectiveLen ) );
            return ( value >> start ) & mask;
#endif
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
        if ( len == 0 || start >= 32 )
        {
            return 0u;
        }

        const uint64_t start64 = static_cast<uint64_t>( start );
        const uint64_t len64 = static_cast<uint64_t>( len );
        const uint64_t maxAvailable = 32u - start64;
        const uint64_t effectiveLen64 = ( len64 > maxAvailable ) ? maxAvailable : len64;
        const unsigned effectiveLen = static_cast<unsigned>( effectiveLen64 );

        if ( std::is_constant_evaluated( ) )
        {
            UInt32 mask = CreateBitMask32( effectiveLen );
            return ( value >> start ) & mask;
        }
        else
        {
#ifdef _MSC_VER
            return _bextr_u32( value, static_cast<unsigned long>( start ), static_cast<unsigned long>( effectiveLen ) );
#else
            UInt32 mask = CreateBitMask32( effectiveLen );
            return ( value >> start ) & mask;
#endif
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
    template<size_t N, typename T>
    inline constexpr T* AlignTo( T* address ) noexcept
    {
        static_assert( N > 0, "AlignTo<N>: alignment N must be > 0" );

        constexpr bool IsPow2 = ( N & ( N - 1 ) ) == 0;

        const size_t addr = reinterpret_cast<size_t>( address );

        if constexpr ( IsPow2 )
        {
            // Fast path for power-of-two alignments: (addr + (N-1)) & ~(N-1)
            constexpr size_t mask = static_cast<size_t>( N - 1 );
            const size_t aligned = ( addr + mask ) & ~mask;
            return reinterpret_cast<T*>( aligned );
        }
        else
        {
            // Generic path for arbitrary N: compute remainder and add the minimal delta.
            const size_t rem = addr % static_cast<size_t>( N );
            if ( rem == 0 )
            {
                return address;
            }
            const size_t aligned = addr + ( static_cast<size_t>( N ) - rem );
            return reinterpret_cast<T*>( aligned );
        }
    }


    /// <summary>
    /// Calculates the number of bytes between the argument <c>address</c> 
    /// and an address that is aligned on an <c>N</c> byte boundary
    /// greater, or equal, to <c>address</c>. 
    /// </summary>
    /// <typeparam name="N"></typeparam>
    /// <param name="address"></param>
    /// <returns></returns>
    template<size_t N, typename T>
    inline constexpr size_t AlignedPaddingFor( const T* address ) noexcept
    {
        static_assert( N > 0, "AlignedPaddingFor<N>: alignment N must be > 0" );

        constexpr bool IsPow2 = ( N & ( N - 1 ) ) == 0;

        const size_t addr = reinterpret_cast<size_t>( address );

        if constexpr ( IsPow2 )
        {
            // Use bit operations for power-of-two alignments.
            // Avoids potential unsigned overflow from (addr + mask).
            constexpr size_t mask = static_cast<size_t>( N - 1 );
            const size_t rem = addr & mask;
            return rem ? ( ( mask + 1 ) - rem ) : 0u;
        }
        else
        {
            // Generic alignment: compute remainder via modulo and return delta.
            const size_t rem = addr % static_cast<size_t>( N );
            return rem == 0 ? 0u : ( static_cast<size_t>( N ) - rem );
        }
    }

    


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 )
            && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> )
            && std::is_trivially_copyable_v<std::remove_cvref_t<T2>>
    inline constexpr T1 GetHigh32Bits( T2 val ) noexcept
    {
        UInt64 bits;
        if constexpr ( std::is_integral_v<std::remove_cvref_t<T2>> )
        {
            bits = static_cast< UInt64 >( val );
        }
        else
        {
            bits = std::bit_cast< UInt64 >( val );
        }

        const UInt32 high32 = static_cast< UInt32 >( bits >> 32 );
        return std::bit_cast< T1 >( high32 );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 )
            && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> )
            && std::is_trivially_copyable_v<std::remove_cvref_t<T2>>
    inline constexpr T2 SetHigh32Bits( T2 x, T1 value ) noexcept
    {
        UInt64 bits;
        if constexpr ( std::is_integral_v<std::remove_cvref_t<T2>> )
        {
            bits = static_cast<UInt64>( x );
        }
        else
        {
            bits = std::bit_cast<UInt64>( x );
        }

        const UInt32 high32 = std::bit_cast<UInt32>( value );

        const UInt64 resultBits = ( bits & 0x00000000FFFFFFFFULL ) | ( static_cast<UInt64>( high32 ) << 32 );

        return std::bit_cast<T2>( resultBits );
    }

    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 )
            && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> )
            && std::is_trivially_copyable_v<std::remove_cvref_t<T2>>
    inline constexpr T1 GetLow32Bits( T2 val ) noexcept
    {
        UInt64 bits;
        if constexpr ( std::is_integral_v<std::remove_cvref_t<T2>> )
        {
            bits = static_cast<UInt64>( val );
        }
        else
        {
            bits = std::bit_cast<UInt64>( val );
        }

        const UInt32 low32 = static_cast<UInt32>( bits & 0xFFFFFFFFULL );
        return std::bit_cast<T1>( low32 );
    }


    template<typename T1, typename T2>
        requires ( sizeof( T2 ) == 8 )
            && ( std::is_same_v<Int32, T1> || std::is_same_v<UInt32, T1> )
            && std::is_trivially_copyable_v<std::remove_cvref_t<T2>>
    inline constexpr T2 SetLow32Bits( T2 x, T1 value ) noexcept
    {
        UInt64 bits;
        if constexpr ( std::is_integral_v<std::remove_cvref_t<T2>> )
        {
            // Fast path for integral storage types
            bits = static_cast<UInt64>( x );
        }
        else
        {
            bits = std::bit_cast<UInt64>( x );
        }

        const UInt32 low32 = std::bit_cast<UInt32>( value );

        const UInt64 resultBits = ( bits & 0xFFFFFFFF00000000ULL ) | static_cast<UInt64>( low32 );

        return std::bit_cast<T2>( resultBits );
    }

    template<typename T1, typename T2, typename T3>
        requires ( sizeof(T1) == 8 )
            && ( std::is_same_v<Int32, T2> || std::is_same_v<UInt32, T2> )
            && ( std::is_same_v<Int32, T3> || std::is_same_v<UInt32, T3> )
            && std::is_trivially_copyable_v<std::remove_cvref_t<T1>>
            && std::is_trivially_copyable_v<std::remove_cvref_t<T2>>
            && std::is_trivially_copyable_v<std::remove_cvref_t<T3>>
    inline constexpr T1 From32BitsTo64Bits( T2 high32Bits, T3 low32Bits ) noexcept
    {
        const UInt64 high = static_cast<UInt64>( std::bit_cast<UInt32>( high32Bits ) ) << 32;
        const UInt64 low  = static_cast<UInt64>( std::bit_cast<UInt32>( low32Bits ) );
        const UInt64 combined = high | low;

        return std::bit_cast<T1>( combined );
    }

    constexpr inline bool IsSubnormal( double value ) noexcept
    { 
        const UInt64 bits = std::bit_cast<UInt64>( value );
        return ( ( bits & ExponentMask<double> ) == 0ULL ) && ( ( bits & FractionMask<double> ) != 0ULL );
    }

    constexpr inline int Exponent( double value ) noexcept
    {
        const UInt64 bits = std::bit_cast<UInt64>( value );
        const unsigned expBits = static_cast<unsigned>( ( bits >> 52 ) & 0x7FFu );
        // Normalized numbers: exponent = e - 1023
        // Subnormals / zero : exponent = 1 - 1023  (i.e. -1022)
        return expBits ? ( static_cast<int>( expBits ) - 1023 ) : ( 1 - 1023 );
    }

    constexpr inline bool IsSubnormal( float value ) noexcept
    {
        const UInt32 bits = std::bit_cast<UInt32>( value );
        return ( ( bits & ExponentMask<float> ) == 0u ) && ( ( bits & FractionMask<float> ) != 0u );
    }

    constexpr inline int Exponent( float v ) noexcept
    {
        const UInt32 bits = std::bit_cast<UInt32>( v );
        const unsigned expBits = static_cast<unsigned>( ( bits >> 23 ) & 0xFFu );
        // Normalized numbers: exponent = e - 127
        // Subnormals / zero : exponent = 1 - 127  (i.e. -126)
        return expBits ? ( static_cast<int>( expBits ) - 127 ) : ( 1 - 127 );
    }


    constexpr inline UInt64 Significand( double value ) noexcept
    {
        return std::bit_cast<UInt64>( value ) & FractionMask<double>;
    }

    constexpr inline UInt32 Significand( float v ) noexcept
    {
        return std::bit_cast<UInt32>( v ) & FractionMask<float>;
    }


    constexpr inline UInt64 FastSignBit( double value ) noexcept
    {
        return std::bit_cast<UInt64>( value ) & 0x8000000000000000ULL;
    }

    constexpr inline UInt32 FastSignBit( float v ) noexcept
    {
        return std::bit_cast<UInt32>( v ) & 0x80000000UL;
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

    template<typename CharT>
        requires ( std::is_same_v< std::remove_cvref_t<CharT>, char > ||
            std::is_same_v< std::remove_cvref_t<CharT>, wchar_t > )
    inline constexpr int Compare( nullptr_t s1, const CharT* s2 ) noexcept
    {
#ifdef _DEBUG
        assert( s1 == nullptr );
#endif
        return ( s2 && s2[ 0 ] ) ? -1 : 0;
    }

    template<typename CharT>
        requires ( std::is_same_v< std::remove_cvref_t<CharT>, char > ||
            std::is_same_v< std::remove_cvref_t<CharT>, wchar_t > )
    inline constexpr int Compare( const CharT* s1, nullptr_t s2 ) noexcept
    {
#ifdef _DEBUG
        assert( s2 == nullptr );
#endif
        return s1 && s1[ 0 ] ? 1 : 0;
    }

    template<typename CharT>
        requires ( std::is_same_v< std::remove_cvref_t<CharT>, char > ||
            std::is_same_v< std::remove_cvref_t<CharT>, wchar_t > )
    inline constexpr int Compare( const CharT* s1, const CharT* s2 ) noexcept
    {
        // fast-path: identical pointer -> equal
        if ( s1 == s2 )
        {
            return 0;
        }

        if constexpr ( std::is_same_v< std::remove_cvref_t<CharT>, char > )
        {
            // treat null as empty
            const char* a = s1 ? s1 : "";
            const char* b = s2 ? s2 : "";

            if ( std::is_constant_evaluated( ) )
            {
                const int rc = std::string_view( a ).compare( b );
                return rc > 0 ? 1 : rc < 0 ? -1 : 0;
            }
            else
            {
                const int rc = strcmp( a, b );
                return rc > 0 ? 1 : rc < 0 ? -1 : 0;
            }
        }
        else
        {
            // treat null as empty
            const wchar_t* a = s1 ? s1 : L"";
            const wchar_t* b = s2 ? s2 : L"";

            if ( std::is_constant_evaluated( ) )
            {
                const int rc = std::wstring_view( a ).compare( b );
                return rc > 0 ? 1 : rc < 0 ? -1 : 0;
            }
            else
            {
                const int rc = wcscmp( a, b );
                return rc > 0 ? 1 : rc < 0 ? -1 : 0;
            }
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