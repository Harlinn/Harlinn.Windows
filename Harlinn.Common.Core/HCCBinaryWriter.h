#pragma once
#ifndef __HCCBINARYWRITER_H__
#define __HCCBINARYWRITER_H__
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

#include <HCCLib.h>
#include <HCCIOBase.h>
#include <HCCGuid.h>
#include <HCCCurrency.h>
#include <HCCString.h>
#include <HCCBinary.h>
#include <HCCException.h>
#include <HCCArray.h>
#include <HCCVector.h>
#include <HCCLogging.h>
#include <HCC7BitEncoding.h>

namespace Harlinn::Common::Core::IO
{
    /// <summary>
    /// <para>
    /// This template is used to implement serialization
    /// of binary data using a Write function implemented by the 
    /// derived class with the following signature:
    /// </para>
    /// <code>
    /// void Write( const void* data, size_t dataSize );
    /// </code>
    /// </summary>
    /// <typeparam name="Derived">
    /// The type of the derived class.
    /// </typeparam>
    /// <typeparam name="networkByteOrder">
    /// If true the template will convert data to network byte order 
    /// from little endian format, otherwise false.
    /// </typeparam>
    /// <typeparam name="use7BitEncodedSize">
    /// If true size information will written as 7-bit encoded unsigned numbers, otherwise false.
    /// </typeparam>
    /// <remarks>
    /// This class supports writing the following types from the underlying stream:
    /// <list type="bullet">
    /// <item>bool</item>
    /// <item>char</item>
    /// <item>SByte</item>
    /// <item>Byte</item>
    /// <item>wchar_t</item>
    /// <item>Int16</item>
    /// <item>UInt16</item>
    /// <item>Int32</item>
    /// <item>long</item>
    /// <item>UInt32</item>
    /// <item>unsigned long</item>
    /// <item>Int64</item>
    /// <item>UInt64</item>
    /// <item>float</item>
    /// <item>double</item>
    /// <item>TimeSpan</item>
    /// <item>DateTime</item>
    /// <item>Currency</item>
    /// <item>Guid</item>
    /// <item>std::string, std::string_view, AnsiString, std::wstring, WideString or anything else that satisfies the SimpleSpanLike concept with a value type of char or wchar_t.</item>
    /// <item>zero terminated c strings of char or wchar_t.
    /// <item>Binary</item>
    /// <item>enum types</item>
    /// <item>std::optional&lt;T&gt; containing any of the above. </item>
    /// </list>
    /// The template can also write length prefixed data to the underlying stream 
    /// from std::vector, std::array and c-style arrays, where the value type
    /// is any of the above.
    /// </remarks>
    template<typename Derived, bool networkByteOrder, bool use7BitEncodedSize>
    class BinaryWriterBase
    {
        static constexpr long long TicksMask = 0x3FFFFFFFFFFFFFFF;
    public:
        static constexpr bool NetworkByteOrder = networkByteOrder;
        static constexpr bool Use7BitEncodedSize = use7BitEncodedSize;
        using PersistedSizeType = UInt32;
    public:
        /// <summary>
        /// Writes the unsigned 64-bit value to the stream as a 7-bit encoded number.
        /// </summary>
        /// <param name="value">
        /// </param>
        constexpr void Write7BitEncoded( UInt64 value )
        {
            std::array<Byte, 9> buffer;
            auto size = Write7BitEncodedValue( value, buffer.data( ) );
            static_cast< Derived& >( *this ).Write( buffer.data( ), size );
        }

    protected:
        /// <summary>
        /// Writes values to the underlying stream in network byte order.
        /// </summary>
        /// <typeparam name="T">
        /// The type of the data to write
        /// </typeparam>
        /// <param name="data">
        /// A pointer to a buffer containing the elements to write to the stream.
        /// </param>
        /// <param name="dataSize">
        /// The number of elements to write to the stream.
        /// </param>
        template<typename T>
        void WriteInNetworkByteOrder( const T* data, size_t dataSize )
        {
            using ValueType = std::remove_cvref_t<T>;
            if constexpr ( sizeof( ValueType ) > 1 )
            {
                using DestType = ValueType;
                constexpr size_t BufferSize = 128;
                std::array<DestType, BufferSize> buffer;
                size_t numberOfFullWrites = dataSize / BufferSize;
                size_t remainingElements = dataSize % BufferSize;
                const ValueType* source = data;
                for ( size_t i = 0; i < numberOfFullWrites; ++i )
                {
                    for ( size_t j = 0; j < BufferSize; ++j )
                    {
                        buffer[j] = ByteSwap( source[j] );
                    }
                    static_cast<Derived&>( *this ).Write( reinterpret_cast<const Byte*>( buffer.data( ) ), BufferSize * sizeof( DestType ) );
                    source += BufferSize;
                }
                for ( size_t j = 0; j < remainingElements; ++j )
                {
                    buffer[j] = ByteSwap( source[j] );
                }
                static_cast<Derived&>( *this ).Write( reinterpret_cast<const Byte*>( buffer.data( ) ), remainingElements * sizeof( DestType ) );

            }
            else
            {
                static_cast<Derived&>( *this ).Write( reinterpret_cast<const Byte*>( data ), size_t( dataSize ) );
            }
        }
    public:

        /// <summary>
        /// <para>
        /// Writes a span of characters to a stream.
        /// </para>
        /// <para>
        /// First the length of the span, in bytes, is written to the stream as a 7-bit encoded number.
        /// Followed by the characters of the argument span.
        /// </para>
        /// </summary>
        /// <typeparam name="T">
        /// std::string, std::string_view, AnsiString, std::wstring, WideString or anything else that satisfies the SimpleSpanLike concept with a value type of char or wchar_t.
        /// </typeparam>
        /// <param name="value">
        /// The span of characters to write to the stream.
        /// </param>
        template<typename SpanT>
            requires SimpleStringLike<SpanT> || IsStdBasicStringView<SpanT> || IsBasicStringView<SpanT>
        void Write( const SpanT& value )
        {
            using ValueType = typename SpanT::value_type;
            size_t count = value.size( );
            auto len = count *sizeof( ValueType );
            Write7BitEncoded( len );
            if ( len )
            {
                if constexpr ( NetworkByteOrder && sizeof( ValueType ) > 1 )
                {
                    WriteInNetworkByteOrder( value.data( ), value.size( ) );
                }
                else
                {
                    static_cast<Derived&>( *this ).Write( reinterpret_cast<const Byte*>( value.data( ) ), size_t( len ) );
                }
            }
        }
        /// <summary>
        /// Writes a zero teminated string of characters to the stream as a span of characters.
        /// </summary>
        /// <typeparam name="T">
        /// The character type of the string, either char or wchar_t.
        /// </typeparam>
        /// <param name="str">
        /// The zero terminated string.
        /// </param>
        template<typename T>
            requires ( std::is_same_v<char,T> || std::is_same_v<wchar_t, T> )
        void Write( const T* str )
        {
            std::basic_string_view stringView( str );
            Write( stringView );
        }

        /// <summary>
        /// Writes size information to the stream.
        /// </summary>
        /// <param name="size"></param>
        void WriteSize( size_t size )
        {
            if constexpr ( Use7BitEncodedSize )
            {
                Write7BitEncoded( size );
            }
            else if constexpr ( NetworkByteOrder )
            {
                UInt32 sz = ByteSwap( static_cast<UInt32>( size ) );
                static_cast<Derived&>( *this ).Write( &sz, sizeof( UInt32 ) );
            }
            else
            {
                UInt32 sz = static_cast<UInt32>( size );
                static_cast<Derived&>( *this ).Write( &sz, sizeof( UInt32 ) );
            }
        }

        /// <summary>
        /// Writes a boolean value to the stream.
        /// </summary>
        /// <typeparam name="T">
        /// Must be bool.
        /// </typeparam>
        /// <param name="value">
        /// The value to write to the stream.
        /// </param>
        template<typename T>
            requires IsBoolean<T>
        constexpr void Write( const T value )
        {
            Byte buffer = (Byte)( value ? 1 : 0 );
            static_cast<Derived&>( *this ).Write( &buffer, 1 );
        }

        /// <summary>
        /// Writes a byte sized value to the stream.
        /// </summary>
        /// <typeparam name="T">
        /// Must be char, SByte or Byte..
        /// </typeparam>
        /// <param name="value">
        /// The value to write to the stream.
        /// </param>
        template<typename T>
            requires (( IsBasicType<T> && sizeof( std::remove_cvref_t<T> ) == 1 ) && IsNotBoolean<T> && (std::is_enum_v<std::remove_cvref_t<T>> == false) )
        constexpr void Write( const T value )
        {
            static_cast<Derived&>( *this ).Write( &value, 1 );
        }

        /// <summary>
        /// Writes a value with a size larger than 1 byte to the stream.
        /// </summary>
        /// <typeparam name="T">
        /// Must be wchar_t, Int16, UInt16, Int32, long, UInt32, unsigned long, 
        /// Int64, UInt64, float, double, TimeSpan, DateTime, Currency, Guid or 
        /// an enum with a size greater than 1.
        /// </typeparam>
        /// <param name="value">
        /// The value to write to the stream.
        /// </param>
        template<typename T>
            requires ( IsBasicType<T> && sizeof( std::remove_cvref_t<T> ) > 1 && (std::is_enum_v<std::remove_cvref_t<T>> == false))
        constexpr void Write( const T value )
        {
            if constexpr ( NetworkByteOrder )
            {
                auto val = ByteSwap( value );
                static_cast<Derived&>( *this ).Write( &val, sizeof( std::remove_cvref_t<T> ) );
            }
            else
            {
                static_cast<Derived&>( *this ).Write( &value, sizeof( std::remove_cvref_t<T> ) );
            }
        }

        /// <summary>
        /// Writes an enum value to a stream.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="value">
        /// The enum value.
        /// </param>
        template<typename T>
            requires std::is_enum_v<std::remove_cvref_t<T>>
        void Write(const T value)
        {
            Write(static_cast<std::underlying_type_t<T>>(value));
        }


        /// <summary>
        /// Writes an optional to a stream.
        /// </summary>
        /// <typeparam name="T">
        /// One of the basic data types. 
        /// </typeparam>
        /// <param name="value">
        /// A const reference to a std::optional for one of the basic types.
        /// </param>
        template<typename T>
            requires IsStdOptional<T>
        void Write( const T& value )
        {
            bool hasValue = value.has_value( );
            Write( hasValue );
            if ( hasValue )
            {
                Write( value.value( ) );
            }
        }

        /// <summary>
        /// Writes a std::vector&lt;bool&gt; or another container that matches 
        /// the SimpleSpanLike concept with a value type of bool to a stream.
        /// </summary>
        /// <typeparam name="T">
        /// Must be std::vector&lt;bool&gt; or another container that matches 
        /// the SimpleSpanLike concept with a value type of bool
        /// </typeparam>
        /// <param name="values"></param>
        template<typename T>
            requires IsBoolean<typename T::value_type> && requires ( const T& t)
            { 
                { t.size( ) }->std::same_as<typename T::size_type>;
                { t.begin( ) }->std::same_as<typename T::const_iterator>;
                { t.end( ) }->std::same_as<typename T::const_iterator>;
            }
        void Write( const T& values )
        {
            WriteSize( values.size( ) );
            for ( auto value : values )
            {
                Byte buffer = (Byte)( value ? 1 : 0 );
                static_cast<Derived&>( *this ).Write( &buffer, 1 );
            }
        }

        /// <summary>
        /// Writes a container that satisfies the SimpleSpanLike concept, but not 
        /// the SimpleStringLike concept or IsStdBasicStringView<T> and IsBasicStringView<T>; to a stream if the value type is not bool.
        /// </summary>
        /// <typeparam name="T">
        /// A container that satisfies the SimpleSpanLike concept, but not 
        /// the SimpleStringLike concept or IsStdBasicStringView<T> and IsBasicStringView<T>.
        /// The value type of the container cannot be bool.
        /// </typeparam>
        /// <param name="values"></param>
        template<SimpleSpanLike T>
            requires IsBasicType<typename T::value_type> && 
                        IsNotBoolean<typename T::value_type> && ( SimpleStringLike<T> == false && IsStdBasicStringView<T> == false && IsBasicStringView<T> == false )
        void Write( const T& values )
        {
            using ValueType = typename T::value_type;
            auto count = static_cast<size_t>( values.size( ) );
            WriteSize( count );
            if constexpr ( NetworkByteOrder && sizeof( ValueType ) > 1 )
            {
                WriteInNetworkByteOrder( values.data( ), count );
            }
            else
            {
                static_cast<Derived&>( *this ).Write( values.data(), count * sizeof( T::value_type ) );
            }
        }

        /// <summary>
        /// Writes a c-style array of any of the basic types to a stream.
        /// </summary>
        /// <typeparam name="T">
        /// The array element type.
        /// </typeparam>
        /// <typeparam name="N">
        /// The number of elements in the array.
        /// </typeparam>
        /// <param name="values">
        /// A reference to a c-style array. 
        /// </param>
        template<typename T, size_t N>
            requires IsBasicType<T> 
        void Write( const T (&values)[N] )
        {
            constexpr auto count = N; 
            using ValueType = std::remove_cvref_t<T>;
            WriteSize( count );
            if constexpr ( NetworkByteOrder )
            {
                WriteInNetworkByteOrder( values, count );
            }
            else
            {
                static_cast<Derived&>( *this ).Write( values, count * sizeof( ValueType ) );
            }
        }






    };


    template<IO::StreamWriter StreamWriterT, size_t BufferSizeValue, bool networkByteOrder = false, bool use7BitEncodedSize = true >
    class BufferedBinaryWriter : public BinaryWriterBase< BufferedBinaryWriter<StreamWriterT, BufferSizeValue, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize >
    {
    public:
        using Base = BinaryWriterBase< BufferedBinaryWriter<StreamWriterT, BufferSizeValue, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize >;

        static constexpr size_t BufferSize = BufferSizeValue;
    private:
        Byte buffer_[BufferSize];
        size_t bufferPosition_;
        StreamWriterT& outStream_;
    public:
        BufferedBinaryWriter( StreamWriterT& output )
            : outStream_( output ), bufferPosition_( 0 )
        {
        }

        ~BufferedBinaryWriter( )
        {
            Flush( );
        }

        using Base::Write;
        void Write( const void* data, size_t dataSize )
        {
            if ( dataSize <= BufferSize - bufferPosition_ )
            {
                memcpy( &buffer_[bufferPosition_], data, dataSize );
                bufferPosition_ += dataSize;
            }
            else
            {
                Byte* ptr = (Byte*)data;
                if ( bufferPosition_ < BufferSize )
                {
                    size_t remaining = BufferSize - bufferPosition_;
                    memcpy( &buffer_[bufferPosition_], ptr, remaining );
                    ptr += remaining;
                    dataSize -= remaining;
                    bufferPosition_ = BufferSize;
                }
                WriteToStream( buffer_, bufferPosition_ );
                bufferPosition_ = 0;
                if ( dataSize > BufferSize )
                {
                    WriteToStream( ptr, dataSize );
                }
                else
                {
                    memcpy( buffer_, ptr, dataSize );
                    bufferPosition_ = dataSize;
                }
            }
        }

        void Flush( )
        {
            if ( bufferPosition_ )
            {
                WriteToStream( buffer_, bufferPosition_ );
                bufferPosition_ = 0;
            }
        }

    private:
        void WriteToStream( const void* data, size_t dataSize )
        {
            outStream_.Write( data, dataSize );
        }
    };

    /// <summary>
    /// This template is used to implement serialization
    /// of binary data to stream objects that satisfies the
    /// IO::StreamWriter concept.
    /// </summary>
    /// <typeparam name="StreamT">
    /// A type that satisfies the IO::StreamWriter concept.
    /// </typeparam>
    /// <typeparam name="networkByteOrder">
    /// If true the template will convert data to network byte order 
    /// from little endian format, otherwise false.
    /// </typeparam>
    /// <typeparam name="use7BitEncodedSize">
    /// If true size information will written as 7-bit encoded unsigned numbers, otherwise false.
    /// </typeparam>
    template<IO::StreamWriter StreamT, bool networkByteOrder = false, bool use7BitEncodedSize = true>
    class BinaryWriter : public BinaryWriterBase<BinaryWriter<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>
    {
    public:
        using Base = BinaryWriterBase<BinaryWriter<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>;
        using StreamType = StreamT;
    protected:
        StreamType& outStream_;
    public:
        /// <summary>
        /// Constructs a BinaryWriter for the output stream.
        /// </summary>
        /// <param name="output">
        /// The output stream.
        /// </param>
        BinaryWriter( StreamType& output )
            : outStream_( output )
        {
        }


        /// <summary>
        /// Returns the stream associated with the writer. 
        /// </summary>
        /// <returns>the stream associated with the writer</returns>
        StreamType& BaseStream( )
        {
            return outStream_;
        }
        /// <summary>
        /// Avoids hiding the Write functions implemented by the base class.
        /// </summary>
        using Base::Write;
        /// <summary>
        /// Writes data to the underlying stream.
        /// </summary>
        /// <param name="data">
        /// A pointer to the data to write. The size of this buffer must be 
        /// greater of equal to the dataSize parameter.
        /// </param>
        /// <param name="dataSize">
        /// The number of bytes to write to the underlying stream.
        /// </param>
        void Write( const void* data, size_t dataSize )
        {
            outStream_.Write( data, dataSize );
        }

    };

}

#endif