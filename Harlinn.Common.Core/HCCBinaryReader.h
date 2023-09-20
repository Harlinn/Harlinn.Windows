#pragma once
#ifndef __HCCBINARYREADER_H__
#define __HCCBINARYREADER_H__

#include <HCCLib.h>
#include <HCCIOBase.h>
#include <HCCGuid.h>
#include <HCCCurrency.h>
#include <HCCString.h>
#include <HCCException.h>
#include <HCCArray.h>
#include <HCCVector.h>
#include <HCCLogging.h>


namespace Harlinn::Common::Core::IO
{



    template<typename Derived, bool networkByteOrder, bool use7BitEncodedSize>
    class BinaryReaderBase
    {
        static constexpr long long TicksMask = 0x3FFFFFFFFFFFFFFF;
    public:
        static constexpr bool NetworkByteOrder = networkByteOrder;
        static constexpr bool Use7BitEncodedSize = use7BitEncodedSize;
        using PersistedSizeType = UInt32;
    protected:

        constexpr int Read7BitEncodedInt( )
        {
            // Read out an Int32 7 bits at a time.  The high bit
            // of the byte when on means to continue reading more bytes. 
            int count = 0;
            int shift = 0;
            Byte b;
            do
            {
                // Check for a corrupted stream.  Read a max of 5 bytes.
                // In a future version, add a DataFormatException. 
                if ( shift == 5 * 7 )  // 5 bytes max per Int32, shift += 7 
                {
                    throw Exception( "Bad 7-Bit Int32 format" );
                }
                // ReadByte handles end of stream cases for us.
                b = Read<Byte>( );
                count |= ( b & 0x7F ) << shift;
                shift += 7;
            } while ( ( b & 0x80 ) != 0 );
            return count;
        }

    public:
        constexpr UInt64 Read7BitEncoded( )
        {
            UInt64 resultValue = 0;
            Byte byteValue = Read<Byte>( );
            resultValue = byteValue & 0x7F;
            if ( byteValue & 0x80 )
            {
                byteValue = Read<Byte>( );
                resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 7;
                if ( byteValue & 0x80 )
                {
                    byteValue = Read<Byte>( );
                    resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 14;
                    if ( byteValue & 0x80 )
                    {
                        byteValue = Read<Byte>( );
                        resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 21;
                        if ( byteValue & 0x80 )
                        {
                            byteValue = Read<Byte>( );
                            resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 28;
                            if ( byteValue & 0x80 )
                            {
                                byteValue = Read<Byte>( );
                                resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 35;
                                if ( byteValue & 0x80 )
                                {
                                    byteValue = Read<Byte>( );
                                    resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 42;
                                    if ( byteValue & 0x80 )
                                    {
                                        byteValue = Read<Byte>( );
                                        resultValue |= static_cast<UInt64>( byteValue & 0x7F ) << 49;
                                        if ( byteValue & 0x80 )
                                        {
                                            byteValue = Read<Byte>( );
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

        template<typename T>
            requires ( IsBasicType<T> && sizeof( std::remove_cvref_t<T> ) > 1 )
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
        template<typename T>
            requires ( IsBasicType<T> && sizeof( std::remove_cvref_t<T> ) > 1 )
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


        template<typename T>
            requires ( IsStdBasicString<T> || IsBasicString<T> )
        void Read( T& result )
        {
            using ValueType = typename T::value_type;
            // Length of the string in T::value_type
            int byteLength = Read7BitEncodedInt( );
            if ( byteLength < 0 )
            {
                throw new IO::IOException( "Invalid string length" );
            }

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

        template<typename T>
            requires ( IsStdBasicString<T> || IsBasicString<T> )
        std::remove_cvref_t<T> Read( )
        {
            using ValueType = typename T::value_type;
            using Type = std::remove_cvref_t<T>;
            // Length of the string in T::value_type
            int byteLength = Read7BitEncodedInt( );
            if ( byteLength < 0 )
            {
                throw new IO::IOException( "Invalid string length" );
            }
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

        template<typename T>
            requires (( IsStdVector<T> && IsBasicType<typename T::value_type> && IsNotBoolean<typename T::value_type> ) ||
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

                if constexpr ( NetworkByteOrder )
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

                if constexpr ( NetworkByteOrder )
                {
                    ValueType* data = result.data( );
                    for ( size_t i = 0; i < count; ++i )
                    {
                        data[i] = ByteSwap( data[i] );
                    }
                }
            }
        }


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

                if constexpr ( NetworkByteOrder )
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

    template< IO::StreamReader StreamT, bool networkByteOrder = false, bool use7BitEncodedSize = true >
    class BinaryReader : public BinaryReaderBase<BinaryReader<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>
    {
    public:
        using Base = BinaryReaderBase<BinaryReader<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>;
        using StreamType = StreamT;
    protected:
        StreamType& inStream_;
    public:
        BinaryReader( StreamType& stream )
            : inStream_( stream )
        {
        }

        StreamType& BaseStream( )
        {
            return inStream_;
        }
        using Base::Read;
        long long Read( void* buffer, size_t bufferSize )
        {
            return inStream_.Read( buffer, bufferSize );
        }
    };


}


#endif
