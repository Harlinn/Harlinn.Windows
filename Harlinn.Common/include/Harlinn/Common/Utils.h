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
#include <chrono>
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
        template<typename T>
        struct IsStdChronoDuration : std::false_type {};

        template<typename Rep, typename Period>
        struct IsStdChronoDuration<std::chrono::duration<Rep, Period>> : std::true_type {};
    }

    template<typename T>
    inline constexpr bool IsStdChronoDuration = Internal::IsStdChronoDuration<std::remove_cvref_t<T>>::value;


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

    /*
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
    */

    template<typename T>
        requires IsInteger<T>
    constexpr inline bool IsPowerOfTwo( T v ) noexcept
    {
        using U = std::make_unsigned_t<T>;
        const U u = static_cast< U >( v );
        // Negative signed values become large unsigned values; treat negatives as not power-of-two.
        // The test below correctly yields false for those cases because u != 0 && (u & (u - 1)) == 0
        // will be false for a two's-complement negative when interpreted as unsigned.
        return u != 0u && ( ( u & ( u - 1u ) ) == 0u );
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
        using UT = std::underlying_type_t<std::remove_cvref_t<T>>;
        using U = std::make_unsigned_t<UT>;
        const U u = static_cast< U >( static_cast< UT >( v ) );
        return u != 0u && ( ( u & ( u - 1u ) ) == 0u );
    }
    template<typename T>
        requires std::is_enum_v<std::remove_cvref_t<T>>
    constexpr inline bool IsPowerOf2( T v ) noexcept
    {
        return IsPowerOfTwo( v );
    }

    namespace Internal
    {
        template<typename U>
        constexpr inline U NextPowerOfTwoUnsignedHelper( U v ) noexcept
        {
            static_assert( std::is_unsigned_v<U> );
            if ( v == 0u )
            {
                return U( 1 );
            }

            const unsigned width = static_cast< unsigned >( sizeof( U ) * 8 );
            const U highestPower = U( 1 ) << ( width - 1 );

            if ( v > highestPower )
            {
                // Cannot represent the strictly greater next power-of-two; saturate to highestPower.
                return highestPower;
            }

            U x = v - 1u;
            for ( unsigned shift = 1u; shift < width; shift <<= 1u )
            {
                x |= ( x >> shift );
            }
            return x + 1u;
        }
    }
    

    template<SignedIntegerType T>
    constexpr inline T NextPowerOfTwo( T v ) noexcept
    {
        using U = std::make_unsigned_t<T>;
        if constexpr ( std::is_signed_v<T> )
        {
            if ( v <= 0 )
            {
                return static_cast< T >( 1 );
            }
        }
        const U u = static_cast< U >( v );
        U r = Internal::NextPowerOfTwoUnsignedHelper<U>( u );

        const U maxSigned = static_cast< U >( std::numeric_limits<T>::max( ) );
        if ( r > maxSigned )
        {
            r = maxSigned;
        }
        return static_cast< T >( r );
    }

    template<UnsignedIntegerType T>
    constexpr inline T NextPowerOfTwo( T v ) noexcept
    {
        return Internal::NextPowerOfTwoUnsignedHelper<T>( v );
    }



    /// <summary>
    /// Stateless deleter that releases memory allocated by the C runtime allocator family using <c>free</c>.
    /// </summary>
    /// <typeparam name="T">The pointed-to element type. The deleter accepts a pointer of type <c>T*</c> and forwards it to <c>free</c>.</typeparam>
    /// <remarks>
    /// - Use this deleter with smart pointers (for example `std::unique_ptr<T, FreeDeleter<T>>`) to automatically
    ///   free memory allocated with C allocation functions such as <c>malloc</c>, <c>calloc</c> or <c>realloc</c>.
    /// - The pointer passed to <c>operator()</c> MUST originate from a compatible C allocator. Passing pointers
    ///   allocated by <c>new</c> / <c>new[]</c> results in undefined behavior.
    /// - Per the C standard, calling <c>free</c> with a null pointer is a no-op; the deleter safely accepts <c>nullptr</c>.
    /// - The operation does not throw exceptions.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Allocate with malloc and manage with unique_ptr + FreeDeleter
    /// void* raw = std::malloc( sizeof(int) * 10 );
    /// auto p = std::unique_ptr<int, FreeDeleter<int>>( static_cast<int*>( raw ) );
    /// // memory will be released via free when 'p' is destroyed
    /// </code>
    /// </example>
    template<typename T>
    class FreeDeleter
    {
    public:
        FreeDeleter( ) = default;
        /// <summary>Frees memory previously allocated with a C allocator (for example <c>malloc</c>).</summary>
        /// <param name="p">Pointer to be freed. May be <c>nullptr</c>.</param>
        void operator()( T* p ) const
        {
            free( p );
        };
    };

    /// <summary>
    /// Stateless deleter that releases memory allocated with the Microsoft-specific automatic allocator (<c>_malloca</c>)
    /// by calling the matching <c>_freea</c>.
    /// </summary>
    /// <typeparam name="T">The pointed-to element type. The deleter accepts a pointer of type <c>T*</c> and forwards it to <c>_freea</c>.</typeparam>
    /// <remarks>
    /// - Use this deleter with smart pointers when memory is allocated with the Microsoft CRT helper <c>_malloca</c>.
    /// - Memory allocated with <c>_malloca</c> must be freed with <c>_freea</c>. Passing such memory to <c>free</c>
    ///   (or vice versa) is undefined behavior.
    /// - The pointer passed to <c>operator()</c> may be <c>nullptr</c>; <c>_freea</c> handles that case.
    /// - This deleter is Microsoft-specific; do not use on non-MSVC toolchains without verifying availability.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Allocate with _malloca and manage with unique_ptr + FreeADeleter
    /// auto raw = static_cast<char*>( _malloca( 256 ) );
    /// auto p = std::unique_ptr<char, FreeADeleter<char>>( raw );
    /// // memory will be released via _freea when 'p' is destroyed
    /// </code>
    /// </example>
    template<typename T>
    class FreeADeleter
    {
    public:
        FreeADeleter( ) = default;
        /// <summary>Releases memory previously allocated with <c>_malloca</c>.</summary>
        /// <param name="p">Pointer to be freed. May be <c>nullptr</c>.</param>
        void operator()( T* p ) const
        {
            _freea( p );
        };
    };

    /// <summary>
    /// Stateless deleter that releases memory allocated via COM allocator functions by calling <c>CoTaskMemFree</c>.
    /// </summary>
    /// <typeparam name="T">The pointed-to element type. Typically used with <c>void</c> or POD pointer types returned by COM APIs.</typeparam>
    /// <remarks>
    /// - Use this deleter with smart pointers (for example `std::unique_ptr<T, CoTaskMemFreeDeleter<T>>`) to manage memory
    ///   obtained from COM allocation functions such as <c>CoTaskMemAlloc</c> or functions that document the caller must
    ///   free the returned buffer with <c>CoTaskMemFree</c>.
    /// - Per the Windows API, <c>CoTaskMemFree</c> accepts a null pointer and performs no action. The deleter therefore
    ///   safely accepts <c>nullptr</c>.
    /// - Ensure that the memory passed to this deleter was allocated by a compatible COM allocator (for example <c>CoTaskMemAlloc</c>);
    ///   mismatched allocators may cause heap corruption.
    /// - The operation does not throw exceptions.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Example: receive memory from a COM API that uses CoTaskMemAlloc and manage with unique_ptr
    /// void* raw = nullptr;
    /// // Assume SomeComFunction allocates memory using CoTaskMemAlloc and returns via out parameter:
    /// // HRESULT hr = SomeComFunction(&raw);
    /// // Manage the returned buffer:
    /// auto p = std::unique_ptr<void, CoTaskMemFreeDeleter<void>>( raw );
    /// // memory will be released via CoTaskMemFree when 'p' is destroyed
    /// </code>
    /// </example>
    template<typename T>
    class CoTaskMemFreeDeleter
    {
    public:
        CoTaskMemFreeDeleter( ) = default;
        /// <summary>Frees memory previously allocated by a COM allocator using <c>CoTaskMemFree</c>.</summary>
        /// <param name="p">Pointer to be freed. May be <c>nullptr</c>.</param>
        void operator()( T* p ) const
        {
            CoTaskMemFree( p );
        };
    };

    /// <summary>
    /// Stateless deleter that calls the <c>Release</c> method on a reference-counted object.
    /// </summary>
    /// <typeparam name="T">The object type which must provide a <c>Release()</c> member function (for example COM interface pointers deriving from <c>IUnkown</c>).</typeparam>
    /// <remarks>
    /// - This deleter is intended for use with objects that implement COM-style reference counting where the correct
    ///   way to release a reference is to call the object's <c>Release()</c> method rather than using <c>delete</c>.
    /// - The template requires that <c>T*</c> supports the expression <c>p->Release()</c>.
    /// - The caller is responsible for ensuring the pointer is valid before the deleter is invoked. If a null pointer
    ///   is possible, wrap the pointer or use a guard to avoid calling <c>Release</c> on <c>nullptr</c>.
    /// - The deleter does not call <c>delete</c> and does not take ownership beyond invoking <c>Release</c>.
    /// - The operation does not throw exceptions.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Example with a COM interface pointer:
    /// IUnknown* raw = nullptr;
    /// // ... obtain interface pointer, e.g. CoCreateInstance(...)
    /// // Manage with unique_ptr and ReleaseDeleter:
    /// auto p = std::unique_ptr<IUnknown, ReleaseDeleter<IUnknown>>( raw );
    /// // When 'p' is destroyed, p->Release() is invoked.
    /// </code>
    /// </example>
    template<typename T>
        requires requires ( T* p )
    {
        { p->Release( ) };
    }
    class ReleaseDeleter
    {
    public:
        ReleaseDeleter( ) = default;
        /// <summary>Calls <c>Release()</c> on the provided pointer.</summary>
        /// <param name="p">Pointer to the object whose <c>Release()</c> method will be invoked. Must not be <c>nullptr</c>.</param>
        void operator()( T* p ) const
        {
            p->Release( );
        };
    };

    namespace Internal
    {
        /// <summary>
        /// Internal RAII helper that invokes the provided callable when the guard is destroyed.
        /// </summary>
        /// <typeparam name="Fn">
        /// Type of the callable object. Must be invocable with no arguments.
        /// </typeparam>
        /// <remarks>
        /// - This type is intended for internal use and is returned by the free function <c>Finally</c>.
        /// - The guard stores the callable in the base class subobject and invokes it from the destructor via <c>operator()()</c>.
        /// - The type is non-copyable and non-movable to ensure a single deterministic invocation of the callable.
        /// - Use the <c>Finally</c> factory function to construct instances of this type.
        /// </remarks>
        /// <example>
        /// <code language="cpp">
        /// // Typical usage via the Finally factory:
        /// auto guard = Finally( [&](){ /* cleanup */ } );
        /// // 'cleanup' will be called automatically when 'guard' goes out of scope.
        /// </code>
        /// </example>
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

    /// <summary>
    /// Creates a scope-bound guard that will invoke the supplied callable when the returned guard is destroyed.
    /// </summary>
    /// <typeparam name="Fn">
    /// Type of the callable to store. Must be invocable with no arguments.
    /// </typeparam>
    /// <param name="Func">
    /// Callable to invoke at scope exit; forwarded into the returned guard.
    /// </param>
    /// <returns>
    /// An instance of <c>Internal::FinallyImpl&lt;Fn&gt;</c> that will invoke <paramref name="Func"/> from its destructor.
    /// </returns>
    /// <remarks>
    /// - The returned guard is non-copyable and non-movable to ensure a single invocation of the callable.
    /// - The callable is invoked from the guard's destructor; it MUST NOT throw. Throwing from a destructor invoked during stack
    ///   unwinding will result in <c>std::terminate</c>.
    /// - Use this factory to perform scope-based cleanup (RAII) without writing a custom guard type.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Run cleanup on scope exit:
    /// auto guard = Finally( [&](){
    ///     // cleanup actions here
    /// } );
    /// // cleanup will run when 'guard' is destroyed (end of scope)
    /// </code>
    /// </example>
    template <typename Fn>
        requires std::is_invocable_v<Fn>
    inline Internal::FinallyImpl<Fn> Finally( Fn&& Func )
    {
        return { std::forward<Fn>( Func ) };
    }

    /// <summary>
    /// Determines whether adding two signed integers can be performed without overflowing or underflowing.
    /// </summary>
    /// <typeparam name="T">
    /// Signed integer type (CV-qualifiers and references are ignored).
    /// </typeparam>
    /// <param name="lhs">
    /// Left operand.
    /// </param>
    /// <param name="rhs">
    /// Right operand.
    /// </param>
    /// <returns>
    /// <c>true</c> if the sum <c>lhs + rhs</c> is representable in type <c>T</c>; otherwise <c>false</c>.
    /// </returns>
    /// <remarks>
    /// - The function avoids performing the addition when it might overflow by using division/subtraction-based bounds checks.
    /// - For <c>rhs &gt; 0</c> the check ensures <c>lhs &lt;= Max - rhs</c> to detect positive overflow.
    /// - For <c>rhs &lt;= 0</c> the check ensures <c>lhs &gt;= Min - rhs</c> to detect negative underflow.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    template<SignedIntegerType T>
    constexpr inline bool IsAdditionSafe( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        const T MinValue = std::numeric_limits<T>::min( );
        if ( rhs > 0 )
        {
            // positive rhs: overflow if lhs > MaxValue - rhs
            return lhs <= ( MaxValue - rhs );
        }
        else
        {
            // non-positive rhs (rhs == 0 handled here too): underflow if lhs < MinValue - rhs
            return lhs >= ( MinValue - rhs );
        }
    }

    /// <summary>
    /// Adds two signed integers and clamps the result to the valid range for the type.
    /// </summary>
    /// <typeparam name="T">
    /// Signed integer type.
    /// </typeparam>
    /// <param name="lhs">
    /// Left operand.
    /// </param>
    /// <param name="rhs">
    /// Right operand.
    /// </param>
    /// <returns>
    /// The sum clamped to [std::numeric_limits<T>::min(), std::numeric_limits<T>::max()].
    /// </returns>
    template<SignedIntegerType T>
    constexpr inline T SafeAddition( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        const T MinValue = std::numeric_limits<T>::min( );

        if ( rhs > 0 )
        {
            // Would overflow to > MaxValue
            if ( lhs > ( MaxValue - rhs ) )
            {
                return MaxValue;
            }
        }
        else if ( rhs < 0 )
        {
            // Would underflow to < MinValue
            if ( lhs < ( MinValue - rhs ) )
            {
                return MinValue;
            }
        }
        return static_cast< T >( lhs + rhs );
    }

    /// <summary>
    /// Determines whether adding two unsigned integers can be performed without overflowing the type <c>T</c>.
    /// </summary>
    /// <typeparam name="T">
    /// An unsigned integer type (CV-qualifiers and references are ignored).
    /// </typeparam>
    /// <param name="lhs">
    /// Left operand.
    /// </param>
    /// <param name="rhs">
    /// Right operand.
    /// </param>
    /// <returns>
    /// <c>true</c> when <c>lhs + rhs</c> is representable in type <c>T</c>; otherwise <c>false</c>.
    /// </returns>
    /// <remarks>
    /// - The function avoids performing the addition (which could overflow) and instead compares <c>lhs</c> against
    ///   <c>std::numeric_limits&lt;T&gt;::max() - rhs</c>. For unsigned types the minimum value is zero, so only the
    ///   upper bound needs checking.
    /// - The function is <c>constexpr</c> and <c>noexcept</c> and is suitable for use in constant-evaluated contexts.
    /// - If the function returns <c>false</c>, callers should handle the overflow case (for example by clamping,
    ///   using <c>SafeAddition</c>, or returning an error).
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// UInt32 a = 4000000000u;
    /// UInt32 b = 500000000u;
    /// if ( IsAdditionSafe<UInt32>( a, b ) )
    /// {
    ///     UInt32 sum = static_cast<UInt32>( a + b );
    /// }
    /// else
    /// {
    ///     // handle overflow (e.g. clamp)
    ///     UInt32 sum = std::numeric_limits<UInt32>::max();
    /// }
    /// </code>
    /// </example>
    template<UnsignedIntegerType T>
    constexpr inline bool IsAdditionSafe( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        const T MinValue = std::numeric_limits<T>::min( );
        return lhs <= ( MaxValue - rhs );
    }

    /// <summary>
    /// Adds two unsigned integers and clamps the result to the valid range for the type.
    /// </summary>
    /// <typeparam name="T">
    /// Unsigned integer type.
    /// </typeparam>
    /// <param name="lhs">
    /// Left operand.
    /// </param>
    /// <param name="rhs">
    /// Right operand.
    /// </param>
    /// <returns>
    /// The sum clamped to std::numeric_limits<T>::max().
    /// </returns>
    template<UnsignedIntegerType T>
    constexpr inline T SafeAddition( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        // Overflow if lhs > MaxValue - rhs
        if ( lhs > ( MaxValue - rhs ) )
        {
            return MaxValue;
        }
        return static_cast< T >( lhs + rhs );
    }


    /// <summary>
    /// Determines whether subtracting <paramref name="rhs"/> from <paramref name="lhs"/> can be performed
    /// without overflowing or underflowing the representable range of the signed integer type <typeparamref name="T"/>.
    /// </summary>
    /// <typeparam name="T">
    /// Signed integer type (CV-qualifiers and references are ignored).
    /// </typeparam>
    /// <param name="lhs">
    /// left operand.</param>
    /// <param name="rhs">
    /// right operand.
    /// </param>
    /// <returns>
    /// <c>true</c> when <c>lhs - rhs</c> is representable in type <typeparamref name="T"/>; otherwise <c>false</c>.
    /// </returns>
    /// <remarks>
    /// - The function avoids performing the subtraction when it might overflow by using bound checks against
    ///   <c>std::numeric_limits&lt;T&gt;::min()</c> and <c>std::numeric_limits&lt;T&gt;::max()</c>.
    /// - When <c>rhs &gt; 0</c> it checks for underflow: the operation is safe when
    ///   <c>lhs &gt;= Min + rhs</c>.
    /// - When <c>rhs &lt;= 0</c> the subtraction is equivalent to adding <c>-rhs</c>; it checks for positive overflow:
    ///   the operation is safe when <c>lhs &lt;= Max + rhs</c> (note <c>rhs</c> is non-positive in this branch).
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    template<SignedIntegerType T>
    constexpr inline bool IsSubtractionSafe( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        const T MinValue = std::numeric_limits<T>::min( );

        if ( rhs > 0 )
        {
            // Subtracting a positive rhs can underflow: lhs - rhs < MinValue
            // Safe when lhs >= MinValue + rhs (no underflow).
            return lhs >= ( MinValue + rhs );
        }
        else
        {
            // Subtracting a non-positive rhs is equivalent to adding -rhs (>=0),
            // which can overflow if lhs > MaxValue + rhs (rhs is <= 0 so this is safe to compute).
            return lhs <= ( MaxValue + rhs );
        }
    }

    /// <summary>
    /// Subtracts <paramref name="rhs"/> from <paramref name="lhs"/> and clamps the result to the valid range
    /// for the signed integer type <typeparamref name="T"/>.
    /// </summary>
    /// <typeparam name="T">A signed integer type (CV-qualifiers and references are ignored).</typeparam>
    /// <param name="lhs">The minuend (left operand).</param>
    /// <param name="rhs">The subtrahend (right operand).</param>
    /// <returns>
    /// The value of <c>lhs - rhs</c> if representable in <typeparamref name="T"/>;
    /// otherwise <c>std::numeric_limits&lt;T&gt;::min()</c> for underflow or
    /// <c>std::numeric_limits&lt;T&gt;::max()</c> for overflow.
    /// </returns>
    /// <remarks>
    /// - The implementation performs bounds checks to avoid undefined behaviour from signed integer overflow.
    /// - When <c>rhs &gt; 0</c> the function detects potential underflow and returns <c>MinValue</c> if needed.
    ///   When <c>rhs &lt; 0</c> the subtraction is equivalent to addition of <c>-rhs</c> and the function
    ///   detects potential overflow and returns <c>MaxValue</c> if needed.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>, suitable for constant-evaluated contexts.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Example: clamp on underflow
    /// int32_t a = std::numeric_limits<int32_t>::min() + 5;
    /// int32_t b = 10;
    /// auto r = SafeSubtraction<int32_t>( a, b ); // r == std::numeric_limits<int32_t>::min()
    /// </code>
    /// </example>
    template<SignedIntegerType T>
    constexpr inline T SafeSubtraction( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        const T MinValue = std::numeric_limits<T>::min( );

        if ( rhs > 0 )
        {
            // Subtracting a positive rhs can underflow: lhs - rhs < MinValue
            if ( lhs < ( MinValue + rhs ) )
            {
                return MinValue;
            }
        }
        else if ( rhs < 0 )
        {
            // Subtracting a negative rhs is equivalent to adding -rhs (positive),
            // which can overflow: lhs - rhs > MaxValue  <=>  lhs > MaxValue + rhs  (rhs <= 0)
            if ( lhs > ( MaxValue + rhs ) )
            {
                return MaxValue;
            }
        }

        return static_cast< T >( lhs - rhs );
    }

    /// <summary>
    /// Determines whether subtracting <paramref name="rhs"/> from <paramref name="lhs"/>
    /// can be performed for an unsigned integer type <typeparamref name="T"/> without underflow.
    /// </summary>
    /// <typeparam name="T">An unsigned integer type (CV-qualifiers and references are ignored).</typeparam>
    /// <param name="lhs">The minuend (left operand).</param>
    /// <param name="rhs">The subtrahend (right operand).</param>
    /// <returns>
    /// <c>true</c> when <c>lhs - rhs</c> is representable in type <typeparamref name="T"/> (i.e. no underflow);
    /// otherwise <c>false</c>.
    /// </returns>
    /// <remarks>
    /// - For unsigned integers an underflow occurs when <c>lhs &lt; rhs</c>. This function performs the
    ///   simple bound check <c>lhs &gt;= rhs</c> to determine safety without performing the subtraction.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>, suitable for use in constant-evaluated contexts.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// UInt32 a = 5u;
    /// UInt32 b = 10u;
    /// bool ok = IsSubtractionSafe&lt;UInt32&gt;( a, b ); // ok == false (would underflow)
    /// </code>
    /// </example>
    template<UnsignedIntegerType T>
    constexpr inline bool IsSubtractionSafe( T lhs, T rhs ) noexcept
    {
        // For unsigned integers subtraction underflows when lhs < rhs.
        // It's safe to subtract when lhs >= rhs.
        return lhs >= rhs;
    }

    /// <summary>
    /// Subtracts two unsigned integers and clamps the result to the valid range for the type.
    /// </summary>
    /// <typeparam name="T">Unsigned integer type.</typeparam>
    /// <param name="lhs">Left operand.</param>
    /// <param name="rhs">Right operand.</param>
    /// <returns>The difference clamped to [0, std::numeric_limits<T>::max()].</returns>
    template<UnsignedIntegerType T>
    constexpr inline T SafeSubtraction( T lhs, T rhs ) noexcept
    {
        // For unsigned types an underflow occurs when lhs < rhs.
        // Clamp to zero in that case; otherwise perform the subtraction.
        return ( lhs < rhs ) ? static_cast< T >( 0 ) : static_cast< T >( lhs - rhs );
    }

    /// <summary>
    /// Determines whether the multiplication <c>lhs * rhs</c> can be performed for the signed integer
    /// type <typeparamref name="T"/> without overflowing or underflowing the representable range.
    /// </summary>
    /// <typeparam name="T">Signed integer type (CV-qualifiers and references are ignored).</typeparam>
    /// <param name="lhs">Left operand.</param>
    /// <param name="rhs">Right operand.</param>
    /// <returns>
    /// <c>true</c> when the product <c>lhs * rhs</c> is representable in type <typeparamref name="T"/>; otherwise <c>false</c>.
    /// </returns>
    /// <remarks>
    /// - The function avoids performing the multiplication when it might overflow by using division-based bounds checks.
    /// - Fast-path: if either operand is zero the product is always representable.
    /// - For non-zero operands the implementation compares against <c>std::numeric_limits&lt;T&gt;::max()</c>
    ///   or <c>std::numeric_limits&lt;T&gt;::min()</c> as appropriate to detect overflow/underflow without causing UB.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Safe: fits in int32_t
    /// bool ok1 = IsMultiplicationSafe<int32_t>( 10000, 2000 );
    /// // Unsafe: would overflow int32_t
    /// bool ok2 = IsMultiplicationSafe<int32_t>( std::numeric_limits<int32_t>::max(), 2 );
    /// </code>
    /// </example>
    template<SignedIntegerType T>
    constexpr inline bool IsMultiplicationSafe( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        const T MinValue = std::numeric_limits<T>::min( );

        // Fast-paths
        if ( lhs == 0 || rhs == 0 )
        {
            return true;
        }

        // Both operands non-zero. Use division to check bounds without performing multiplication.
        if ( lhs > 0 )
        {
            if ( rhs > 0 )
            {
                // both positive: lhs <= Max / rhs
                return lhs <= ( MaxValue / rhs );
            }
            else
            {
                // lhs > 0, rhs < 0: rhs >= Min / lhs
                return rhs >= ( MinValue / lhs );
            }
        }
        else // lhs < 0
        {
            if ( rhs > 0 )
            {
                // lhs < 0, rhs > 0: lhs >= Min / rhs
                return lhs >= ( MinValue / rhs );
            }
            else
            {
                // both negative: lhs >= Max / rhs
                // (product is positive; compare using Max)
                return lhs >= ( MaxValue / rhs );
            }
        }
    }

    /// <summary>
    /// Multiplies two signed integers and clamps the result to the valid range for the type.
    /// </summary>
    /// <typeparam name="T">A signed integer type.</typeparam>
    /// <param name="lhs">Left operand.</param>
    /// <param name="rhs">Right operand.</param>
    /// <returns>
    /// The product <c>lhs * rhs</c> if it fits in type <typeparamref name="T"/>; otherwise
    /// returns <c>std::numeric_limits&lt;T&gt;::max()</c> or <c>std::numeric_limits&lt;T&gt;::min()</c>
    /// depending on the sign of the mathematical product.
    /// </returns>
    /// <remarks>
    /// - The implementation avoids performing a multiplication that would overflow by first
    ///   using <see cref="IsMultiplicationSafe"/>. If the multiplication is safe the product
    ///   is performed and returned.
    /// - When the product cannot be represented in <typeparamref name="T"/>, the function
    ///   clamps to the appropriate endpoint (max for positive overflow, min for negative overflow).
    /// - This function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// int32_t a = 100000;
    /// int32_t b = 30000;
    /// int32_t safeProduct = SafeMultiplication<int32_t>(a, b); // clamped to INT32_MAX
    /// </code>
    /// </example>
    template<SignedIntegerType T>
    constexpr inline T SafeMultiplication( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        const T MinValue = std::numeric_limits<T>::min( );

        // Zero fast-path
        if ( lhs == 0 || rhs == 0 )
        {
            return static_cast< T >( 0 );
        }

        // If safe, perform multiplication
        if ( IsMultiplicationSafe( lhs, rhs ) )
        {
            return static_cast< T >( lhs * rhs );
        }

        // Overflow/underflow: determine sign of the mathematical product.
        // Product is positive when operands have same sign.
        const bool productIsPositive = ( ( lhs > 0 ) == ( rhs > 0 ) );
        return productIsPositive ? MaxValue : MinValue;
    }


    /// <summary>
    /// Determines whether the multiplication of two unsigned integers can be performed
    /// without overflowing the representable range for the type <typeparamref name="T"/>.
    /// </summary>
    /// <typeparam name="T">An unsigned integer type.</typeparam>
    /// <param name="lhs">Left operand.</param>
    /// <param name="rhs">Right operand.</param>
    /// <returns>
    /// <c>true</c> if <c>lhs * rhs</c> is representable in type <typeparamref name="T"/>; otherwise <c>false</c>.
    /// </returns>
    /// <remarks>
    /// - The check avoids performing the multiplication directly (which would overflow on success),
    ///   and instead uses the bound check <c>lhs <= max / rhs</c>.
    /// - If either operand is zero the multiplication is safe.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    template<UnsignedIntegerType T>
    constexpr inline bool IsMultiplicationSafe( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );

        // Fast-path: zero product is always safe.
        if ( lhs == static_cast< T >( 0 ) || rhs == static_cast< T >( 0 ) )
        {
            return true;
        }

        // Avoid division by zero; rhs != 0 here.
        return lhs <= ( MaxValue / rhs );
    }


    /// <summary>
    /// Multiplies two unsigned integers and clamps the result to the valid range for the type.
    /// </summary>
    /// <typeparam name="T">An unsigned integer type.</typeparam>
    /// <param name="lhs">Left operand.</param>
    /// <param name="rhs">Right operand.</param>
    /// <returns>
    /// The product <c>lhs * rhs</c> if it fits in type <typeparamref name="T"/>; otherwise
    /// returns <c>std::numeric_limits&lt;T&gt;::max()</c>.
    /// </returns>
    /// <remarks>
    /// - The implementation uses <c>IsMultiplicationSafe</c> to avoid performing a multiplication that would overflow.
    /// - When either operand is zero the result is zero.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// UInt32 a = 100000u;
    /// UInt32 b = 600u;
    /// UInt32 product = SafeMultiplication<UInt32>(a, b); // may be clamped to UINT32_MAX if overflow
    /// </code>
    /// </example>
    template<UnsignedIntegerType T>
    constexpr inline T SafeMultiplication( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );

        // Fast-path: zero product is always safe.
        if ( lhs == static_cast< T >( 0 ) || rhs == static_cast< T >( 0 ) )
        {
            return static_cast< T >( 0 );
        }

        // If safe, perform multiplication (checked above to avoid overflow).
        if ( IsMultiplicationSafe( lhs, rhs ) )
        {
            return static_cast< T >( lhs * rhs );
        }

        // Overflow: clamp to maximum representable unsigned value.
        return MaxValue;
    }

    /// <summary>
    /// Determines whether the division <c>lhs / rhs</c> can be performed for signed integer
    /// type <typeparamref name="T"/> without causing undefined behaviour (division by zero or
    /// signed overflow).
    /// </summary>
    /// <typeparam name="T">Signed integer type.</typeparam>
    /// <param name="lhs">Dividend.</param>
    /// <param name="rhs">Divisor.</param>
    /// <returns>
    /// <c>true</c> when the division is safe to perform (no divide-by-zero and no signed overflow),
    /// otherwise <c>false</c>.
    /// </returns>
    /// <remarks>
    /// - Division by zero is not allowed and returns <c>false</c>.
    /// - The only signed-integer division that can overflow on two's-complement architectures is
    ///   when <c>lhs == std::numeric_limits&lt;T&gt;::min()</c> and <c>rhs == -1</c>. This function
    ///   detects and reports that case as unsafe.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// // Safe
    /// bool ok1 = IsDivisionSafe<int32_t>( 10, 2 ); // true
    /// // Divide by zero
    /// bool ok2 = IsDivisionSafe<int32_t>( 10, 0 ); // false
    /// // Overflow case
    /// bool ok3 = IsDivisionSafe<int32_t>( std::numeric_limits<int32_t>::min(), -1 ); // false
    /// </code>
    /// </example>
    template<SignedIntegerType T>
    constexpr inline bool IsDivisionSafe( T lhs, T rhs ) noexcept
    {
        // Division by zero is always unsafe.
        if ( rhs == static_cast< T >( 0 ) )
        {
            return false;
        }

        // The only signed division that can overflow is MIN / -1.
        // Check and reject that specific case.
        if ( rhs == static_cast< T >( -1 ) && lhs == std::numeric_limits<T>::min( ) )
        {
            return false;
        }

        return true;
    }

    /// <summary>
    /// Divides two signed integers and clamps the result to the valid range for the type.
    /// </summary>
    /// <typeparam name="T">A signed integer type.</typeparam>
    /// <param name="lhs">Dividend.</param>
    /// <param name="rhs">Divisor.</param>
    /// <returns>
    /// The quotient <c>lhs / rhs</c> if it can be performed without undefined behaviour;
    /// otherwise the result is clamped to <c>std::numeric_limits&lt;T&gt;::max()</c> or
    /// <c>std::numeric_limits&lt;T&gt;::min()</c> depending on the mathematical sign of
    /// the result or the operand signs in the case of division by zero.
    /// </returns>
    /// <remarks>
    /// - Division by zero is not permitted; this function returns <c>MaxValue</c> when
    ///   <paramref name="lhs"/> is non-negative and <c>MinValue</c> when <paramref name="lhs"/>
    ///   is negative to provide a well-defined clamped result.
    /// - The only signed integer division that can overflow on two's-complement machines is
    ///   <c>MinValue / -1</c>; this case is detected and clamps to <c>MaxValue</c>.
    /// - For all other inputs the operation performs the normal quotient <c>lhs / rhs</c>.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// int32_t a = 10;
    /// int32_t b = 2;
    /// int32_t r = SafeDivision<int32_t>(a, b); // 5
    /// int32_t z = SafeDivision<int32_t>(a, 0); // INT32_MAX
    /// int32_t ov = SafeDivision<int32_t>(std::numeric_limits<int32_t>::min(), -1); // INT32_MAX (clamped)
    /// </code>
    /// </example>
    template<SignedIntegerType T>
    constexpr inline T SafeDivision( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );
        const T MinValue = std::numeric_limits<T>::min( );

        // Division by zero: clamp based on sign of dividend to give deterministic result.
        if ( rhs == static_cast< T >( 0 ) )
        {
            return ( lhs >= static_cast< T >( 0 ) ) ? MaxValue : MinValue;
        }

        // MIN / -1 is the only signed integer division that can overflow.
        if ( lhs == MinValue && rhs == static_cast< T >( -1 ) )
        {
            return MaxValue;
        }
        return static_cast< T >( lhs / rhs );
    }

    /// <summary>
    /// Determines whether the division <c>lhs / rhs</c> can be performed for an unsigned integer
    /// type <typeparamref name="T"/> without causing undefined behaviour (division by zero).
    /// </summary>
    /// <typeparam name="T">
    /// An unsigned integer type.
    /// </typeparam>
    /// <param name="lhs">
    /// Dividend (unused for safety check but included for symmetry with signed overload).
    /// </param>
    /// <param name="rhs">
    /// Divisor. Division is unsafe when this is zero.
    /// </param>
    /// <returns>
    /// <c>true</c> if <c>rhs</c> is non-zero and the division is therefore safe; otherwise <c>false</c>.
    /// </returns>
    /// <remarks>
    /// - For unsigned integer types there is no overflow from the division operation itself;
    ///   the only undefined behaviour to guard against is division by zero.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    template<UnsignedIntegerType T>
    constexpr inline bool IsDivisionSafe( T lhs, T rhs ) noexcept
    {
        // lhs is intentionally unused 
        ( void )lhs; 
        return rhs != static_cast< T >( 0 );
    }

    /// <summary>
    /// Divides two unsigned integers and clamps the result to the valid range for the type.
    /// </summary>
    /// <typeparam name="T">An unsigned integer type.</typeparam>
    /// <param name="lhs">Dividend.</param>
    /// <param name="rhs">Divisor.</param>
    /// <returns>
    /// The quotient <c>lhs / rhs</c> when <c>rhs != 0</c>. If <c>rhs == 0</c> the function
    /// returns <c>std::numeric_limits&lt;T&gt;::max()</c> to provide a well-defined clamped result
    /// instead of performing a division-by-zero.
    /// </returns>
    /// <remarks>
    /// - Unsigned integer division cannot overflow; the only undefined behaviour to guard against is division by zero.
    /// - The function is <c>constexpr</c> and <c>noexcept</c>.
    /// </remarks>
    /// <example>
    /// <code language="cpp">
    /// UInt32 a = 10u;
    /// UInt32 b = 2u;
    /// UInt32 r = SafeDivision<UInt32>(a, b); // 5
    /// UInt32 z = SafeDivision<UInt32>(a, 0u); // UINT32_MAX (clamped)
    /// </code>
    /// </example>
    template<UnsignedIntegerType T>
    constexpr inline T SafeDivision( T lhs, T rhs ) noexcept
    {
        const T MaxValue = std::numeric_limits<T>::max( );

        // Check for division by zero: return saturated value.
        if ( rhs == static_cast< T >( 0 ) )
        {
            return MaxValue;
        }

        // Normal case:
        return static_cast< T >( lhs / rhs );
    }



}

#endif