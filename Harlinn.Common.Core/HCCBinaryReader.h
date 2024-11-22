#pragma once
#ifndef __HCCBINARYREADER_H__
#define __HCCBINARYREADER_H__
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
    /// This template is used to implement deserialization
    /// of binary data using a Read function implemented by the 
    /// derived class with the following signature:
    /// </para>
    /// <code>
    /// long long Read( void* buffer, size_t bufferSize );
    /// </code>
    /// </summary>
    /// <typeparam name="Derived">
    /// The type of the derived class.
    /// </typeparam>
    /// <typeparam name="networkByteOrder">
    /// If true the template will convert data from network byte order 
    /// to little endian format, otherwise false.
    /// </typeparam>
    /// <typeparam name="use7BitEncodedSize">
    /// If true size information is expected to be 7-bit encoded, otherwise false.
    /// </typeparam>
    /// <remarks>
    /// This class supports reading of the following types from the underlying stream:
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
    /// <item>std::string</item>
    /// <item>std::wstring</item>
    /// <item>AnsiString</item>
    /// <item>WideString</item>
    /// <item>Binary</item>
    /// <item>enum types</item>
    /// <item>std::optional&lt;T&gt; containing any of the above. </item>
    /// </list>
    /// The template can also read length prefixed data from the underlying stream 
    /// into std::vector, std::array and c-style arrays, where the value type
    /// is any of the above.
    /// </remarks>
    template<typename Derived, bool networkByteOrder, bool use7BitEncodedSize>
    class BinaryReaderBase
    {
        static constexpr long long TicksMask = 0x3FFFFFFFFFFFFFFF;
    public:
        static constexpr bool NetworkByteOrder = networkByteOrder;
        static constexpr bool Use7BitEncodedSize = use7BitEncodedSize;
        using PersistedSizeType = UInt32;
    public:
        /// <summary>
        /// Reads and decodes a 7-bit encoded unsigned 64-bit integer.
        /// </summary>
        /// <returns>
        /// The decoded unsigned 64-bit integer.
        /// </returns>
        constexpr UInt64 Read7BitEncoded( )
        {
            return Read7BitEncodedUInt64( *this );
        }

        /// <summary>
        /// Reads size information from the underlying stream. This is usually
        /// the count of elements that comes next in the stream.
        /// </summary>
        /// <returns>
        /// The size retrieved from the stream.
        /// </returns>
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

        /// <summary>
        /// Reads a boolean value from the stream. 
        /// </summary>
        /// <typeparam name="T">
        /// Must be bool.
        /// </typeparam>
        /// <returns>The boolean value.</returns>
        template<typename T>
            requires IsBoolean<T>
        T Read( )
        {
            Byte v;
            auto bytesRead = static_cast<Derived&>( *this ).Read( &v, 1 );
            if ( bytesRead == 0 )
            {
                HCC_THROW( IO::EndOfStreamException );
            }
            return v ? true : false;
        }
        /// <summary>
        /// Reads a boolean value from the stream and writes it to the 
        /// bool variable referenced by the value parameter. 
        /// </summary>
        /// <typeparam name="T">
        /// Must be bool.
        /// </typeparam>
        /// <param name="value">
        /// A reference to the variable that will receive the value read 
        /// by the function.
        /// </param>
        template<typename T>
            requires IsBoolean<T>
        void Read( T& value )
        {
            Byte v;
            auto bytesRead = static_cast<Derived&>( *this ).Read( &v, 1 );
            if ( bytesRead == 0 )
            {
                HCC_THROW( IO::EndOfStreamException );
            }
            value = v ? true : false;
        }

        /// <summary>
        /// Reads a non-boolean byte sized value from the stream and writes
        /// it to the byte sized variable referenced by the value parameter. 
        /// </summary>
        /// <typeparam name="T">
        /// Must be char, SByte, Byte or a byte sized enum.
        /// </typeparam>
        /// <param name="value">
        /// A reference to the variable that will receive the value read 
        /// by the function.
        /// </param>
        template<typename T>
            requires ( ( IsBasicType<T> && sizeof( std::remove_cvref_t<T> ) == 1 ) && IsNotBoolean<T> )
        constexpr void Read( T& value )
        {
            auto bytesRead = static_cast<Derived&>( *this ).Read( &value, 1 );
            if ( bytesRead == 0 )
            {
                HCC_THROW( IO::EndOfStreamException );
            }
        }

        /// <summary>
        /// Reads a non-boolean byte sized value from the stream
        /// and returns the value.
        /// </summary>
        /// <typeparam name="T">
        /// Must be char, SByte, Byte or a byte sized enum.
        /// </typeparam>
        /// <returns>The value read from the stream.</returns>
        template<typename T>
            requires ( ( IsBasicType<T> && sizeof( std::remove_cvref_t<T> ) == 1 ) && IsNotBoolean<T> )
        constexpr std::remove_cvref_t<T> Read( )
        {
            std::remove_cvref_t<T> value;
            auto bytesRead = static_cast<Derived&>( *this ).Read( &value, 1 );
            if ( bytesRead == 0 )
            {
                HCC_THROW( IO::EndOfStreamException );
            }
            return value;
        }

        /// <summary>
        /// Reads a value with size greater than 1 from the stream and writes
        /// it to the variable referenced by the value parameter. 
        /// </summary>
        /// <typeparam name="T">
        /// Must be wchar_t, Int16, UInt16, Int32, long, UInt32, unsigned long, 
        /// Int64, UInt64, float, double, TimeSpan, DateTime, Currency, Guid or 
        /// an enum with a size greater than 1.
        /// </typeparam>
        /// <param name="value">
        /// A reference to the variable that will receive the value read 
        /// by the function.
        /// </param>
        template<typename T>
            requires ( (IsBasicType<T> || std::is_enum_v<T> ) && sizeof( std::remove_cvref_t<T> ) > 1 )
        constexpr void Read( T& value )
        {
            using Type = std::remove_cvref_t<T>;
            if constexpr ( std::is_enum_v<Type> )
            {
                std::underlying_type_t<Type> v = 0;
                Read( v );
                value = static_cast<Type>( v );
            }
            else if constexpr ( NetworkByteOrder )
            {
                
                Type val;
                auto bytesRead = static_cast<Derived&>( *this ).Read( &val, sizeof( Type ) );
                if ( bytesRead < sizeof( Type ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }
                value = ByteSwap( val );
            }
            else
            {
                auto bytesRead = static_cast<Derived&>( *this ).Read( &value, sizeof( Type ) );
                if ( bytesRead < sizeof( Type ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }
            }
        }
        /// <summary>
        /// Reads a value with size greater than 1 from the stream
        /// and returns the value.
        /// </summary>
        /// <typeparam name="T">
        /// Must be wchar_t, Int16, UInt16, Int32, long, UInt32, unsigned long, 
        /// Int64, UInt64, float, double, TimeSpan, DateTime, Currency, Guid or 
        /// an enum with a size greater than 1.
        /// </typeparam>
        /// <returns>The value read from the stream.</returns>
        template<typename T>
            requires ( (IsBasicType<T> || std::is_enum_v<T>) && sizeof( std::remove_cvref_t<T> ) > 1 )
        constexpr std::remove_cvref_t<T> Read( )
        {
            using Type = std::remove_cvref_t<T>;
            Type value;
            if constexpr ( std::is_enum_v<Type> )
            {
                return static_cast<Type>( Read<std::underlying_type_t<Type>>( ) );
            }
            else if constexpr ( NetworkByteOrder )
            {
                
                Type val;
                auto bytesRead = static_cast<Derived&>( *this ).Read( &val, sizeof( Type ) );
                if ( bytesRead < sizeof( Type ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }
                value = ByteSwap( val );
            }
            else
            {
                auto bytesRead = static_cast<Derived&>( *this ).Read( &value, sizeof( Type ) );
                if ( bytesRead < sizeof( Type ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }
            }
            return value;
        }

        /// <summary>
        /// Reads a std::optional from the stream and places the result
        /// in the variable referenced by the argument.
        /// </summary>
        /// <typeparam name="T">
        /// One of the basic data types. 
        /// </typeparam>
        /// <param name="value">
        /// A reference to the variable that will receive the value read from the stream.
        /// </param>
        template<typename T>
            requires IsStdOptional<T>
        void Read( T& value )
        {
            auto hasValue = Read<bool>( );
            if ( hasValue )
            {
                value = Read<typename T::value_type>( );
            }
            else
            {
                value.reset( );
            }
        }
        /// <summary>
        /// Reads a std::optional from the stream and returns the result.
        /// </summary>
        /// <typeparam name="T">
        /// One of the basic data types. 
        /// </typeparam>
        /// <returns>
        /// The result.
        /// </returns>
        template<typename T>
            requires IsStdOptional<T>
        std::remove_cvref_t<T> Read( )
        {
            auto hasValue = Read<bool>( );
            if ( hasValue )
            {
                return Read<typename T::value_type>( );
            }
            else
            {
                return std::remove_cvref_t<T>( );
            }
        }


        /// <summary>
        /// Reads a string from the stream and places the result
        /// in the value referenced by the argument.
        /// </summary>
        /// <typeparam name="T">
        /// A string type that satisfies the StringLike concept.
        /// </typeparam>
        /// <param name="result">
        /// A reference to the variable that will receive the result.
        /// </param>
        template<StringLike T>
        void Read( T& result )
        {
            using ValueType = typename T::value_type;
            // Length of the string bytes
            auto byteLength = Read7BitEncoded( );

            if ( byteLength != 0 )
            {
                size_t stringLength = static_cast< size_t >( byteLength ) / sizeof( ValueType );
                result.resize( stringLength );
                if constexpr ( IsBasicString<T> )
                {
                    result.EnsureUnique( );
                }
                auto bytesRead = static_cast<Derived&>( *this ).Read( result.data( ), static_cast<size_t>(byteLength) );
                if ( bytesRead < static_cast<long long>( byteLength ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }
                if constexpr ( NetworkByteOrder && sizeof( typename T::value_type ) > 1 )
                {
                    auto ptr = result.data( );
                    auto endPtr = ptr + stringLength;
                    while ( ptr < endPtr )
                    {
                        *ptr = ByteSwap( *ptr );
                        ++ptr;
                    }
                }
            }
            else
            {
                result.clear( );
            }
        }

        /// <summary>
        /// Reads a string from the stream and returns the result.
        /// </summary>
        /// <typeparam name="T">
        /// A string type that satisfies the StringLike concept.
        /// </typeparam>
        /// <returns>
        /// The result.
        /// </returns>
        template<StringLike T>
        std::remove_cvref_t<T> Read( )
        {
            using ValueType = typename T::value_type;
            using Type = std::remove_cvref_t<T>;
            // Length of the string in bytes
            auto byteLength = Read7BitEncoded( );
            Type result;
            if ( byteLength != 0 )
            {
                size_t stringLength = static_cast< size_t >( byteLength ) / sizeof( ValueType );
                result.resize( stringLength );
                auto bytesRead = static_cast<Derived&>( *this ).Read( result.data( ), static_cast< size_t >( byteLength ) );
                if ( bytesRead < static_cast<long long>( byteLength ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }
                if constexpr ( NetworkByteOrder && sizeof( typename T::value_type ) > 1 )
                {
                    auto ptr = result.data( );
                    auto endPtr = ptr + stringLength;
                    while ( ptr < endPtr )
                    {
                        *ptr = ByteSwap( *ptr );
                        ++ptr;
                    }
                }
            }
            return result;
        }

        /// <summary>
        /// Reads a sequence of bytes representing boolean values from the stream and places the result
        /// in the value referenced by the argument.
        /// </summary>
        /// <typeparam name="T">
        /// must be std::vector<bool>
        /// </typeparam>
        /// <param name="result">
        /// A reference to the variable that will receive the result.
        /// </param>
        template<typename T>
            requires ( IsStdVector<T>&& IsBoolean<typename T::value_type> )
        void Read( T& result )
        {
            auto count = ReadSize( );

            if ( count != 0 )
            {
                result.reserve( count );
                for ( size_t i = 0; i < count; ++i )
                {
                    auto value = Read<bool>( );
                    result.emplace_back( value );
                }
            }
            else
            {
                result.clear( );
            }
        }

        /// <summary>
        /// Reads a sequence of elements representing non-boolean values from the stream and places the result
        /// in the value referenced by the argument.
        /// </summary>
        /// <typeparam name="T">
        /// std::vector or Core::Vector where the value type is one of the basic data types except for bool. 
        /// </typeparam>
        /// <param name="result">
        /// A reference to the variable that will receive the result.
        /// </param>
        template<typename T>
            requires (( (IsStdVector<T> || std::is_same_v<T,Binary> ) && IsBasicType<typename T::value_type> && IsNotBoolean<typename T::value_type> ) ||
                ( IsCoreVector<T> && IsBasicType<typename T::value_type> ) )
        void Read( T& result )
        {
            using ValueType = typename T::value_type;
            auto count = ReadSize( );

            if ( count != 0 )
            {
                result.resize( static_cast<T::size_type>( count ) );
                auto numberOfBytesToRead = static_cast<size_t>( count ) * sizeof( ValueType );
                auto bytesRead = static_cast<Derived&>( *this ).Read( result.data( ), numberOfBytesToRead );
                if ( bytesRead < static_cast<long long>( numberOfBytesToRead ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }

                if constexpr ( NetworkByteOrder && sizeof( ValueType ) > 1 )
                {
                    ValueType* data = result.data( );
                    for ( size_t i = 0; i < count; ++i )
                    {
                        data[i] = ByteSwap( data[i] );
                    }
                }
            }
            else
            {
                result.clear( );
            }
        }

        /// <summary>
        /// Reads a sequence of elements representing values from the stream and places the result
        /// in the value referenced by the argument.
        /// </summary>
        /// <typeparam name="T">
        /// std::array where the value type is one of the basic data types. 
        /// </typeparam>
        /// <param name="result">
        /// A reference to the variable that will receive the result.
        /// </param>
        template<typename T>
            requires ( IsBasicType<typename T::value_type> && IsArrayContainer<T> )
        void Read( T& result )
        {
            using ValueType = typename T::value_type;
            auto count = ReadSize( );
            if ( count != result.size( ) )
            {
                HCC_THROW(ArgumentException, L"Unexpected array size", L"result" );
            }

            if ( count != 0 )
            {
                auto numberOfBytesToRead = static_cast<size_t>( count ) * sizeof( ValueType );
                auto bytesRead = static_cast<Derived&>( *this ).Read( result.data( ), numberOfBytesToRead );
                if ( bytesRead < static_cast<long long>( numberOfBytesToRead ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }

                if constexpr ( NetworkByteOrder && sizeof( ValueType ) > 1 )
                {
                    ValueType* data = result.data( );
                    for ( size_t i = 0; i < count; ++i )
                    {
                        data[i] = ByteSwap( data[i] );
                    }
                }
            }
        }

        /// <summary>
        /// Reads a sequence of elements representing values from the stream and places the result
        /// in the value referenced by the argument.
        /// </summary>
        /// <typeparam name="T">
        /// a c-style array type where the element type is one of the basic data types. 
        /// </typeparam>
        /// <param name="result">
        /// A reference to the variable that will receive the result.
        /// </param>
        template<typename T, size_t N>
            requires IsBasicType<T>
        void Read( T ( &result )[N] )
        {
            constexpr auto arraySize = N;
            using ValueType = T;
            auto count = ReadSize( );
            if ( count != arraySize )
            {
                HCC_THROW(ArgumentException, L"Unexpected array size", L"result" );
            }

            if ( arraySize != 0 )
            {
                constexpr auto numberOfBytesToRead = static_cast<size_t>( arraySize ) * sizeof( ValueType );
                auto bytesRead = static_cast<Derived&>( *this ).Read( result, numberOfBytesToRead );
                if ( bytesRead < static_cast<long long>( numberOfBytesToRead ) )
                {
                    HCC_THROW( IO::EndOfStreamException );
                }

                if constexpr ( NetworkByteOrder && sizeof( ValueType ) > 1 )
                {
                    for ( size_t i = 0; i < arraySize; ++i )
                    {
                        result[i] = ByteSwap( result[i] );
                    }
                }
            }
        }

    };


    template<typename StreamT, size_t BufferSizeValue, bool networkByteOrder = false, bool use7BitEncodedSize = true>
    class BufferedBinaryReader : public BinaryReaderBase<BufferedBinaryReader<StreamT, BufferSizeValue, networkByteOrder, use7BitEncodedSize >, networkByteOrder, use7BitEncodedSize >
    {
    public:
        using Base = BinaryReaderBase<BufferedBinaryReader<StreamT, BufferSizeValue, networkByteOrder, use7BitEncodedSize >, networkByteOrder, use7BitEncodedSize >;
        using StreamType = StreamT;
        static constexpr size_t BufferSize = BufferSizeValue;
    protected:
        Byte buffer_[BufferSize];
        size_t bufferPosition_;
        size_t bytesInBuffer_;
        StreamType& inStream_;
    public:
        BufferedBinaryReader( StreamType& stream )
            : inStream_( stream ), bufferPosition_( 0 ), bytesInBuffer_(0)
        {
        }

        StreamType& BaseStream( )
        {
            return inStream_;
        }
        using Base::Read;
        long long Read( void* buffer, size_t bufferSize )
        {
            size_t remainingInBuffer = bytesInBuffer_ - bufferPosition_;
            if ( bufferSize <= remainingInBuffer )
            {
                memcpy( buffer, &buffer_[bufferPosition_], bufferSize );
                bufferPosition_ += bufferSize;
                return static_cast<long long>( bufferSize );
            }
            Byte* ptr = (Byte*)buffer;
            size_t bytesRead = 0;
            if ( remainingInBuffer )
            {
                memcpy( ptr, &buffer_[bufferPosition_], remainingInBuffer );
                ptr += remainingInBuffer;
                bufferSize -= remainingInBuffer;
                bytesRead = remainingInBuffer;
                bufferPosition_ = 0; 
                bytesInBuffer_ = 0;
            }
            if ( bufferSize > BufferSize)
            {
                bytesRead += static_cast<size_t>(inStream_.Read( ptr, bufferSize ));
            }
            else
            {
                bytesInBuffer_ = static_cast<size_t>( inStream_.Receive( buffer_, BufferSize ,bufferSize ) );
                memcpy( buffer, buffer_, bufferSize );
                bufferPosition_ = bufferSize;
                bytesRead += bufferSize;
            }
            return static_cast<long long>( bytesRead );
        }
    };

    /// <summary>
    /// This template is used to implement deserialization
    /// of binary data from stream objects that satisfies the
    /// IO::StreamReader concept.
    /// </summary>
    /// <typeparam name="StreamT">
    /// A type that satisfies the IO::StreamReader concept.
    /// </typeparam>
    /// <typeparam name="networkByteOrder">
    /// If true the template will convert data from network byte order 
    /// to little endian format, otherwise false.
    /// </typeparam>
    /// <typeparam name="use7BitEncodedSize">
    /// If true size information is expected to be 7-bit encoded, otherwise false.
    /// </typeparam>
    template< IO::StreamReader StreamT, bool networkByteOrder = false, bool use7BitEncodedSize = true >
    class BinaryReader : public BinaryReaderBase<BinaryReader<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>
    {
    public:
        using Base = BinaryReaderBase<BinaryReader<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>;
        using StreamType = StreamT;
    protected:
        StreamType& inStream_;
    public:
        /// <summary>
        /// Constructs a BinaryReader for the stream.
        /// </summary>
        /// <param name="stream">
        /// The input stream.
        /// </param>
        BinaryReader( StreamType& stream )
            : inStream_( stream )
        {
        }

        /// <summary>
        /// Provides access to the underlying stream.
        /// </summary>
        /// <returns>
        /// </returns>
        StreamType& BaseStream( )
        {
            return inStream_;
        }
        /// <summary>
        /// Avoids hiding the various Read implementations implemented 
        /// in the base template class.
        /// </summary>
        using Base::Read;

        /// <summary>
        /// Reads data from the underlying stream.
        /// </summary>
        /// <param name="buffer">
        /// A pointer to the buffer that will receive the data. The size 
        /// of the buffer must be greater or equal to the value passed in 
        /// the bufferSize argument.
        /// </param>
        /// <param name="bufferSize">
        /// The number bytes to read from the stream.
        /// </param>
        /// <returns>
        /// The number of bytes placed in the buffer by this function.
        /// </returns>
        long long Read( void* buffer, size_t bufferSize )
        {
            return inStream_.Read( buffer, bufferSize );
        }
    };


}


#endif
