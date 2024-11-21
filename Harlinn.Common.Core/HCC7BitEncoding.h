#pragma once
#ifndef __HCC7BITENCODING_H__
#define __HCC7BITENCODING_H__
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

namespace Harlinn::Common::Core
{
    constexpr UInt64 MaxOneByteValue =   0x7FULL;
    constexpr UInt64 MaxTwoByteValue =   0x3FFFULL;
    constexpr UInt64 MaxThreeByteValue = 0x1FFFFFULL;
    constexpr UInt64 MaxFourByteValue =  0xFFFFFFFULL;
    constexpr UInt64 MaxFiveByteValue =  0x7FFFFFFFFULL;
    constexpr UInt64 MaxSixByteValue =   0x3FFFFFFFFFFULL;
    constexpr UInt64 MaxSevenByteValue = 0x1FFFFFFFFFFFFULL;
    constexpr UInt64 MaxEightByteValue = 0xFFFFFFFFFFFFFFULL;
    constexpr UInt64 MaxNineByteValue  = 0xFFFFFFFFFFFFFFFFULL;

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 64-bit unsigned integer.
    /// </summary>
    /// <param name="value">
    /// The 64-bit unsigned integer.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    inline constexpr size_t SizeOf7BitEncodedValue( UInt64 value ) noexcept
    {
        if ( value > MaxOneByteValue )
        {
            if ( value > MaxTwoByteValue )
            {
                if ( value > MaxThreeByteValue )
                {
                    if ( value > MaxFourByteValue )
                    {
                        if ( value > MaxFiveByteValue )
                        {
                            if ( value > MaxSixByteValue )
                            {
                                if ( value > MaxSevenByteValue )
                                {
                                    if ( value > MaxEightByteValue )
                                    {
                                        return 9;
                                    }
                                    else
                                    {
                                        return 8;
                                    }
                                }
                                else
                                {
                                    return 7;
                                }
                            }
                            else
                            {
                                return 6;
                            }
                        }
                        else
                        {
                            return 5;
                        }
                    }
                    else
                    {
                        return 4;
                    }
                }
                else
                {
                    return 3;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 64-bit signed integer.
    /// </summary>
    /// <param name="value">
    /// The 64-bit signed integer.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t SizeOf7BitEncodedValue( Int64 value ) noexcept
    {
        return SizeOf7BitEncodedValue( ( std::bit_cast<UInt64>( value ) << 1 ) | ( std::bit_cast< UInt64 >( value ) >> 63) );
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 32-bit unsigned integer.
    /// </summary>
    /// <param name="value">
    /// The 32-bit unsigned integer.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    inline constexpr size_t SizeOf7BitEncodedValue( UInt32 value ) noexcept
    {
        if ( value > MaxOneByteValue )
        {
            if ( value > MaxTwoByteValue )
            {
                if ( value > MaxThreeByteValue )
                {
                    if ( value > MaxFourByteValue )
                    {
                        
                        return 5;
                    }
                    else
                    {
                        return 4;
                    }
                }
                else
                {
                    return 3;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 32-bit signed integer.
    /// </summary>
    /// <param name="value">
    /// The 32-bit signed integer.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t SizeOf7BitEncodedValue( Int32 value ) noexcept
    {
        return SizeOf7BitEncodedValue( ( std::bit_cast< UInt32 >( value ) << 1 ) | ( std::bit_cast< UInt32 >( value ) >> 31 ) );
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 16-bit unsigned integer.
    /// </summary>
    /// <param name="value">
    /// The 16-bit unsigned integer.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    inline constexpr size_t SizeOf7BitEncodedValue( UInt16 value ) noexcept
    {
        if ( value > MaxOneByteValue )
        {
            if ( value > MaxTwoByteValue )
            {
                return 3;
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 16-bit signed integer.
    /// </summary>
    /// <param name="value">
    /// The 16-bit signed integer.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t SizeOf7BitEncodedValue( Int16 value ) noexcept
    {
        return SizeOf7BitEncodedValue( ( std::bit_cast< UInt16 >( value ) << 1 ) | ( std::bit_cast< UInt16 >( value ) >> 15 ) );
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 16-bit wchar_t.
    /// </summary>
    /// <param name="value">
    /// The 16-bit wchar_t.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t SizeOf7BitEncodedValue( wchar_t value ) noexcept
    {
        return SizeOf7BitEncodedValue( std::bit_cast<UInt16>( value ) );
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 8-bit unsigned integer.
    /// </summary>
    /// <param name="value">
    /// The 8-bit unsigned integer.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    inline constexpr size_t SizeOf7BitEncodedValue( Byte value ) noexcept
    {
        if ( value > MaxOneByteValue )
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 8-bit signed integer.
    /// </summary>
    /// <param name="value">
    /// The 8-bit signed integer.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to ensure compatibility with the encodings for the
    /// wider signed integer types.
    /// </remarks>
    inline constexpr size_t SizeOf7BitEncodedValue( SByte value ) noexcept
    {
        return SizeOf7BitEncodedValue( ( std::bit_cast< Byte >( value ) << 1 ) | ( std::bit_cast< Byte >( value ) >> 7 ) );
    }

    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 8-bit char.
    /// </summary>
    /// <param name="value">
    /// The 8-bit char.
    /// </param>
    /// <returns>
    /// Number of bytes required to store value as a 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to ensure compatibility with the encodings for the
    /// wider signed integer types.
    /// </remarks>
    inline constexpr size_t SizeOf7BitEncodedValue( char value ) noexcept
    {
        return SizeOf7BitEncodedValue( std::bit_cast<Byte>( value ) );
    }



    /// <summary>
    /// Calculates the size, in bytes, required to store a 7-bit 
    /// encoded 64-bit unsigned integer.
    /// </summary>
    /// <typeparam name="N">
    /// The 64-bit unsigned integer.
    /// </typeparam>
    template<UInt64 N>
    inline constexpr size_t SizeOf7BitEncoded_v = SizeOf7BitEncodedValue( N );

    /// <summary>
    /// Encodes a 64-bit unsigned integer as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 64-bit unsigned integer value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    inline constexpr size_t Write7BitEncodedValue( UInt64 value, Byte* dest ) noexcept
    {
        // Loop manually unrolled for performance:
        dest[0] = value & 0x7F;
        if ( value > 127 )
        {
            dest[0] |= 0x80;
            value >>= 7;
            dest[1] = value & 0x7F;
            if ( value > 127 )
            {
                dest[1] |= 0x80;
                value >>= 7;
                dest[2] = value & 0x7F;

                if ( value > 127 )
                {
                    dest[2] |= 0x80;
                    value >>= 7;
                    dest[3] = value & 0x7F;

                    if ( value > 127 )
                    {
                        dest[3] |= 0x80;
                        value >>= 7;
                        dest[4] = value & 0x7F;

                        if ( value > 127 )
                        {
                            dest[4] |= 0x80;
                            value >>= 7;
                            dest[5] = value & 0x7F;

                            if ( value > 127 )
                            {
                                dest[5] |= 0x80;
                                value >>= 7;
                                dest[6] = value & 0x7F;

                                if ( value > 127 )
                                {
                                    dest[6] |= 0x80;
                                    value >>= 7;
                                    dest[7] = value & 0x7F;

                                    if ( value > 127 )
                                    {
                                        dest[7] |= 0x80;
                                        value >>= 7;
                                        dest[8] = value & 0xFF;
                                        return 9;
                                    }
                                    else
                                    {
                                        return 8;
                                    }
                                }
                                else
                                {
                                    return 7;
                                }
                            }
                            else
                            {
                                return 6;
                            }
                        }
                        else
                        {
                            return 5;
                        }
                    }
                    else
                    {
                        return 4;
                    }
                }
                else
                {
                    return 3;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Encodes a 64-bit signed integer as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 64-bit signed integer value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t Write7BitEncodedValue( Int64 value, Byte* dest ) noexcept
    {
        return Write7BitEncodedValue( ( std::bit_cast< UInt64 >( value ) << 1 ) | ( std::bit_cast< UInt64 >( value ) >> 63 ), dest );
    }

    /// <summary>
    /// Encodes a 32-bit unsigned integer as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 32-bit unsigned integer value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    inline constexpr size_t Write7BitEncodedValue( UInt32 value, Byte* dest ) noexcept
    {
        // Loop manually unrolled for performance:
        dest[0] = value & 0x7F;
        if ( value > 127 )
        {
            dest[0] |= 0x80;
            value >>= 7;
            dest[1] = value & 0x7F;
            if ( value > 127 )
            {
                dest[1] |= 0x80;
                value >>= 7;
                dest[2] = value & 0x7F;

                if ( value > 127 )
                {
                    dest[2] |= 0x80;
                    value >>= 7;
                    dest[3] = value & 0x7F;

                    if ( value > 127 )
                    {
                        dest[3] |= 0x80;
                        value >>= 7;
                        dest[4] = value & 0x7F;
                        
                        return 5;
                        
                    }
                    else
                    {
                        return 4;
                    }
                }
                else
                {
                    return 3;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Encodes a 32-bit signed integer as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 32-bit signed integer value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t Write7BitEncodedValue( Int32 value, Byte* dest ) noexcept
    {
        return Write7BitEncodedValue( ( std::bit_cast< UInt32 >( value ) << 1 ) | ( std::bit_cast< UInt32 >( value ) >> 31 ), dest );
    }

    /// <summary>
    /// Encodes a 16-bit unsigned integer as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 16-bit unsigned integer value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    inline constexpr size_t Write7BitEncodedValue( UInt16 value, Byte* dest ) noexcept
    {
        dest[0] = value & 0x7F;
        if ( value > 127 )
        {
            dest[0] |= 0x80;
            value >>= 7;
            dest[1] = value & 0x7F;
            if ( value > 127 )
            {
                dest[1] |= 0x80;
                value >>= 7;
                dest[2] = value & 0x7F;

                return 3;
                
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Encodes a 16-bit signed integer as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 16-bit signed integer value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t Write7BitEncodedValue( Int16 value, Byte* dest ) noexcept
    {
        return Write7BitEncodedValue( ( std::bit_cast< UInt16 >( value ) << 1 ) | ( std::bit_cast< UInt16 >( value ) >> 15 ), dest );
    }
    /// <summary>
    /// Encodes a 16-bit wchar_t as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 16-bit wchar_t value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    inline constexpr size_t Write7BitEncodedValue( wchar_t value, Byte* dest ) noexcept
    {
        return Write7BitEncodedValue( std::bit_cast<UInt16>( value ), dest );
    }

    /// <summary>
    /// Encodes a 8-bit unsigned integer as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 8-bit unsigned integer value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    inline constexpr size_t Write7BitEncodedValue( Byte value, Byte* dest ) noexcept
    {
        dest[0] = value & 0x7F;
        if ( value > 127 )
        {
            dest[0] |= 0x80;
            value >>= 7;
            dest[1] = value & 0x7F;

            return 2;
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Encodes a 8-bit signed integer as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 8-bit signed integer value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to ensure compatibility with the encodings for the
    /// wider signed integer types.
    /// </remarks>
    inline constexpr size_t Write7BitEncodedValue( SByte value, Byte* dest ) noexcept
    {
        return Write7BitEncodedValue( ( std::bit_cast< Byte >( value ) << 1 ) | ( std::bit_cast< Byte >( value ) >> 7 ), dest );
    }
    /// <summary>
    /// Encodes a 8-bit char as a 7-bit encoded value.
    /// </summary>
    /// <param name="value">
    /// The 8-bit char value.
    /// </param>
    /// <param name="dest">
    /// <para>
    /// The a pointer to the buffer receiving the 7-bit encoded number.
    /// </para>
    /// <para>
    /// The size of the buffer must be greater or equal to the value
    /// returned by SizeOf7BitEncodedValue for the value.
    /// </para>
    /// </param>
    /// <returns>
    /// Number of bytes written to the destination buffer.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to ensure compatibility with the encodings for the
    /// wider signed integer types.
    /// </remarks>
    inline constexpr size_t Write7BitEncodedValue( char value, Byte* dest ) noexcept
    {
        return Write7BitEncodedValue( ( std::bit_cast< Byte >( value ) << 1 ) | ( std::bit_cast< Byte >( value ) >> 7 ), dest );
    }

    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 64-bit unsigned integer
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 64-bit unsigned integer that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, UInt64& resultValue ) noexcept
    {
        Byte byteValue = buffer[offset];
        resultValue = byteValue & 0x7F;
        if ( byteValue & 0x80 )
        {
            byteValue = buffer[offset + 1];
            resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 7;
            if ( byteValue & 0x80 )
            {
                byteValue = buffer[offset + 2];
                resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 14;
                if ( byteValue & 0x80 )
                {
                    byteValue = buffer[offset + 3];
                    resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 21;
                    if ( byteValue & 0x80 )
                    {
                        byteValue = buffer[offset + 4];
                        resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 28;
                        if ( byteValue & 0x80 )
                        {
                            byteValue = buffer[offset + 5];
                            resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 35;
                            if ( byteValue & 0x80 )
                            {
                                byteValue = buffer[offset + 6];
                                resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 42;
                                if ( byteValue & 0x80 )
                                {
                                    byteValue = buffer[offset + 7];
                                    resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 49;
                                    if ( byteValue & 0x80 )
                                    {
                                        byteValue = buffer[offset + 8];
                                        resultValue |= static_cast<UInt64>( byteValue ) << 56;
                                        return 9;
                                    }
                                    else
                                    {
                                        return 8;
                                    }
                                }
                                else
                                {
                                    return 7;
                                }
                            }
                            else
                            {
                                return 6;
                            }
                        }
                        else
                        {
                            return 5;
                        }
                    }
                    else
                    {
                        return 4;
                    }
                }
                else
                {
                    return 3;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 64-bit signed integer
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 64-bit signed integer that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, Int64& resultValue ) noexcept
    {
        UInt64 resVal = 0;
        auto result = Read7BitEncodedValue( buffer, offset, resVal );
        resultValue = std::bit_cast< Int64 >( ( resVal >> 1 ) | ( resVal << 63 ) );
        return result;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 64-bit unsigned integer.
    /// </returns>
    template<typename Reader>
        requires requires( Reader r, Byte& b)
        { 
            { r.Read( b ) };
        }
    inline constexpr UInt64 Read7BitEncodedUInt64( Reader& reader) noexcept
    {
        UInt64 resultValue = 0;
        Byte byteValue = 0;
        reader.Read( byteValue );
        resultValue = byteValue & 0x7F;
        if ( byteValue & 0x80 )
        {
            reader.Read( byteValue );
            resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 7;
            if ( byteValue & 0x80 )
            {
                reader.Read( byteValue );
                resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 14;
                if ( byteValue & 0x80 )
                {
                    reader.Read( byteValue );
                    resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 21;
                    if ( byteValue & 0x80 )
                    {
                        reader.Read( byteValue );
                        resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 28;
                        if ( byteValue & 0x80 )
                        {
                            reader.Read( byteValue );
                            resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 35;
                            if ( byteValue & 0x80 )
                            {
                                reader.Read( byteValue );
                                resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 42;
                                if ( byteValue & 0x80 )
                                {
                                    reader.Read( byteValue );
                                    resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 49;
                                    if ( byteValue & 0x80 )
                                    {
                                        reader.Read( byteValue );
                                        resultValue |= static_cast<UInt64>( byteValue ) << 56;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return resultValue;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 64-bit signed integer.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr Int64 Read7BitEncodedInt64( Reader& reader ) noexcept
    {
        UInt64 resVal = Read7BitEncodedUInt64( reader );
        Int64 resultValue = std::bit_cast< Int64 >( ( resVal >> 1 ) | ( resVal << 63 ) );
        return resultValue;
    }

    
    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 32-bit unsigned integer
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 32-bit unsigned integer that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, UInt32& resultValue ) noexcept
    {
        Byte byteValue = buffer[offset];
        resultValue = byteValue & 0x7F;
        if ( byteValue & 0x80 )
        {
            byteValue = buffer[offset + 1];
            resultValue |= static_cast<UInt32>( byteValue & 0x7F ) << 7;
            if ( byteValue & 0x80 )
            {
                byteValue = buffer[offset + 2];
                resultValue |= static_cast<UInt32>( byteValue & 0x7F ) << 14;
                if ( byteValue & 0x80 )
                {
                    byteValue = buffer[offset + 3];
                    resultValue |= static_cast<UInt32>( byteValue & 0x7F ) << 21;
                    if ( byteValue & 0x80 )
                    {
                        byteValue = buffer[offset + 4];
                        resultValue |= static_cast<UInt32>( byteValue & 0x7F ) << 28;
                        return 5;
                        
                    }
                    else
                    {
                        return 4;
                    }
                }
                else
                {
                    return 3;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 32-bit signed integer
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 32-bit signed integer that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, Int32& resultValue ) noexcept
    {
        UInt32 resVal = 0;
        auto result = Read7BitEncodedValue( buffer, offset, resVal );
        resultValue = std::bit_cast< Int32 >( ( resVal >> 1 ) | ( resVal << 31 ) );
        return result;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 32-bit unsigned integer.
    /// </returns>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr UInt32 Read7BitEncodedUInt32( Reader& reader ) noexcept
    {
        UInt32 resultValue = 0;
        Byte byteValue = 0;
        reader.Read( byteValue );
        resultValue = byteValue & 0x7F;
        if ( byteValue & 0x80 )
        {
            reader.Read( byteValue );
            resultValue |= static_cast< UInt32 >( byteValue & 0x7F ) << 7;
            if ( byteValue & 0x80 )
            {
                reader.Read( byteValue );
                resultValue |= static_cast< UInt32 >( byteValue & 0x7F ) << 14;
                if ( byteValue & 0x80 )
                {
                    reader.Read( byteValue );
                    resultValue |= static_cast< UInt32 >( byteValue & 0x7F ) << 21;
                    if ( byteValue & 0x80 )
                    {
                        reader.Read( byteValue );
                        resultValue |= static_cast< UInt32 >( byteValue & 0x7F ) << 28;
                    }
                }
            }
        }
        return resultValue;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 32-bit signed integer.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr Int32 Read7BitEncodedInt32( Reader& reader ) noexcept
    {
        UInt32 resVal = Read7BitEncodedUInt32( reader );
        Int32 resultValue = std::bit_cast< Int32 >( ( resVal >> 1 ) | ( resVal << 31 ) );
        return resultValue;
    }

    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 16-bit unsigned integer
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 16-bit unsigned integer that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, UInt16& resultValue ) noexcept
    {
        Byte byteValue = buffer[offset];
        resultValue = byteValue & 0x7F;
        if ( byteValue & 0x80 )
        {
            byteValue = buffer[offset + 1];
            resultValue |= static_cast<UInt16>( byteValue & 0x7F ) << 7;
            if ( byteValue & 0x80 )
            {
                byteValue = buffer[offset + 2];
                resultValue |= static_cast<UInt16>( byteValue & 0x7F ) << 14;
                return 3;
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
    }

    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 16-bit signed integer
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 16-bit signed integer that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, Int16& resultValue ) noexcept
    {
        UInt16 resVal = 0;
        auto result = Read7BitEncodedValue( buffer, offset, resVal );
        resultValue = std::bit_cast< Int16 >( static_cast<UInt16>(( resVal >> 1 ) | ( resVal << 15 )) );
        return result;
    }

    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 16-bit wchar_t
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 16-bit wchar_t that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, wchar_t& resultValue ) noexcept
    {
        UInt16 resVal = 0;
        auto result = Read7BitEncodedValue( buffer, offset, resVal );
        resultValue = static_cast<wchar_t>( resVal );
        return result;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 16-bit unsigned integer.
    /// </returns>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr UInt16 Read7BitEncodedUInt16( Reader& reader ) noexcept
    {
        UInt16 resultValue = 0;
        Byte byteValue = 0;
        reader.Read( byteValue );
        resultValue = byteValue & 0x7F;
        if ( byteValue & 0x80 )
        {
            reader.Read( byteValue );
            resultValue |= static_cast< UInt16 >( byteValue & 0x7F ) << 7;
            if ( byteValue & 0x80 )
            {
                reader.Read( byteValue );
                resultValue |= static_cast< UInt16 >( byteValue & 0x7F ) << 14;
            }
        }
        return resultValue;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 16-bit signed integer.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to minimize the size of the 7-bit encoding.
    /// </remarks>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr Int16 Read7BitEncodedInt16( Reader& reader ) noexcept
    {
        UInt16 resVal = Read7BitEncodedUInt16( reader );
        Int16 resultValue = std::bit_cast< Int16 >( ( resVal >> 1 ) | ( resVal << 15 ) );
        return resultValue;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 16-bit wchar_t.
    /// </returns>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr wchar_t Read7BitEncodedWChar( Reader& reader ) noexcept
    {
        return std::bit_cast< wchar_t >( Read7BitEncodedUInt16( reader ) );
    }


    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 8-bit unsigned integer
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 8-bit unsigned integer that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, Byte& resultValue ) noexcept
    {
        Byte byteValue = buffer[offset];
        resultValue = byteValue & 0x7F;
        if ( byteValue & 0x80 )
        {
            byteValue = buffer[offset + 1];
            resultValue |= static_cast<Byte>( byteValue & 0x7F ) << 7;
            return 2;
        }
        else
        {
            return 1;
        }
    }
    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 8-bit signed integer
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 8-bit signed integer that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to ensure compatibility with the encodings for the
    /// wider signed integer types.
    /// </remarks>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, SByte& resultValue ) noexcept
    {
        Byte resVal = 0;
        auto result = Read7BitEncodedValue( buffer, offset, resVal );
        resultValue = std::bit_cast< SByte >( static_cast<Byte>(( resVal >> 1 ) | ( resVal << 7 )) );
        return result;
    }

    /// <summary>
    /// Reads a 7-bit encoded numer, located at offset in the buffer, 
    /// decodes in and places the result into the 8-bit char
    /// referenced by resultValue.
    /// </summary>
    /// <param name="buffer">
    /// A pointer to the buffer containing the 7-bit encoded number.
    /// </param>
    /// <param name="offset">
    /// The offset into buffer of the start of the 7-bit encoded number.
    /// </param>
    /// <param name="resultValue">
    /// A reference to the 8-bit char that receives the
    /// value of the 7-bit encoded number.
    /// </param>
    /// <returns>
    /// Number of bytes read to decode the 7-bit encoded number.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to ensure compatibility with the encodings for the
    /// wider signed integer types.
    /// </remarks>
    inline constexpr size_t Read7BitEncodedValue( const Byte* buffer, size_t offset, char& resultValue ) noexcept
    {
        Byte resVal = 0;
        auto result = Read7BitEncodedValue( buffer, offset, resVal );
        resultValue = std::bit_cast< char >( static_cast< Byte >( ( resVal >> 1 ) | ( resVal << 7 ) ) );
        return result;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 8-bit unsigned integer.
    /// </returns>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr Byte Read7BitEncodedByte( Reader& reader ) noexcept
    {
        Byte resultValue = 0;
        Byte byteValue = 0;
        reader.Read( byteValue );
        resultValue = byteValue & 0x7F;
        if ( byteValue & 0x80 )
        {
            reader.Read( byteValue );
            resultValue |= static_cast< Byte >( byteValue & 0x7F ) << 7;
        }
        return resultValue;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 8-bit signed integer.
    /// </returns>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr SByte Read7BitEncodedSByte( Reader& reader ) noexcept
    {
        Byte resVal = Read7BitEncodedByte( reader );
        SByte resultValue = std::bit_cast< SByte >( ( resVal >> 1 ) | ( resVal << 7 ) );
        return resultValue;
    }

    /// <summary>
    /// Decodes a 7-bit encoded numer by reading
    /// one byte at the time from the Reader object referenced by reader.
    /// </summary>
    /// <typeparam name="Reader">
    /// A type that reads one byte at the time from the
    /// underlying source and places the result in
    /// the referenced argument.
    /// </typeparam>
    /// <param name="reader">
    /// The reader object.
    /// </param>
    /// <returns>
    /// The decoded 8-bit char.
    /// </returns>
    /// <remarks>
    /// The sign bit is rotated to the least significant bit,
    /// and the remaining bits are shifted one bit to the right
    /// to ensure compatibility with the encodings for the
    /// wider signed integer types.
    /// </remarks>
    template<typename Reader>
        requires requires( Reader r, Byte& b )
        {
            { r.Read( b ) };
        }
    inline constexpr char Read7BitEncodedChar( Reader& reader ) noexcept
    {
        Byte resVal = Read7BitEncodedByte( reader );
        SByte resultValue = std::bit_cast< SByte >( ( resVal >> 1 ) | ( resVal << 7 ) );
        return resultValue;
    }



}

#endif
