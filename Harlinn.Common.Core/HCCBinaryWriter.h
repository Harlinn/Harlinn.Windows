#pragma once
#ifndef __HCCBINARYWRITER_H__
#define __HCCBINARYWRITER_H__

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
    class BinaryWriterBase
    {
        static constexpr long long TicksMask = 0x3FFFFFFFFFFFFFFF;
    public:
        static constexpr bool NetworkByteOrder = networkByteOrder;
        static constexpr bool Use7BitEncodedSize = use7BitEncodedSize;
        using PersistedSizeType = UInt32;
    public:
        constexpr void Write7BitEncoded( UInt64 value )
        {
            Byte dest = value & 0x7F;
            if ( value > 127 )
            {
                dest |= 0x80;
                Write( dest );
                value >>= 7;
                dest = value & 0x7F;
                if ( value > 127 )
                {
                    dest |= 0x80;
                    Write( dest );
                    value >>= 7;
                    dest = value & 0x7F;
                    if ( value > 127 )
                    {
                        dest |= 0x80;
                        Write( dest );
                        value >>= 7;
                        dest = value & 0x7F;

                        if ( value > 127 )
                        {
                            dest |= 0x80;
                            Write( dest );
                            value >>= 7;
                            dest = value & 0x7F;

                            if ( value > 127 )
                            {
                                dest |= 0x80;
                                Write( dest );
                                value >>= 7;
                                dest = value & 0x7F;

                                if ( value > 127 )
                                {
                                    dest |= 0x80;
                                    Write( dest );
                                    value >>= 7;
                                    dest = value & 0x7F;

                                    if ( value > 127 )
                                    {
                                        dest |= 0x80;
                                        Write( dest );
                                        value >>= 7;
                                        dest = value & 0x7F;

                                        if ( value > 127 )
                                        {
                                            dest |= 0x80;
                                            Write( dest );
                                            value >>= 7;
                                            dest = value & 0xFF;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Write( dest );
        }

    protected:
        // Write out an int 7 bits at a time.  The high bit of the byte,
        // when on, tells reader to continue reading more bytes. 
        void Write7BitEncodedInt( int value )
        {
            // support negative numbers
            uint v = (uint)value;
            while ( v >= 0x80 )
            {
                Write( (Byte)( v | 0x80 ) );
                v >>= 7;
            }
            Write( (Byte)v );
        }

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

        template<typename T>
            requires ( IsStdBasicString<T> || IsStdBasicStringView<T> || IsBasicString<T> || IsBasicStringView<T> )
        void Write( const T& value )
        {
            using ValueType = typename T::value_type;
            size_t count = value.length( );
            int len = static_cast<int>( count )*sizeof( ValueType );
            Write7BitEncodedInt( len );
            if ( len )
            {
                if constexpr ( NetworkByteOrder && sizeof( ValueType ) > 1 )
                {
                    WriteInNetworkByteOrder( value.data( ), value.size( ) );
                }
                else
                {
                    static_cast<Derived&>( *this ).Write( reinterpret_cast<const Byte*>( value.data( ) ), size_t( len ) * sizeof( ValueType ) );
                }
            }
        }


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

        template<typename T>
            requires IsBoolean<T>
        constexpr void Write( const T value )
        {
            Byte buffer = (Byte)( value ? 1 : 0 );
            static_cast<Derived&>( *this ).Write( &buffer, 1 );
        }

        template<typename T>
            requires (( IsBasicType<T> && sizeof( std::remove_cvref_t<T> ) == 1 ) && IsNotBoolean<T> && (std::is_enum_v<std::remove_cvref_t<T>> == false) )
        constexpr void Write( const T value )
        {
            static_cast<Derived&>( *this ).Write( &value, 1 );
        }

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

        template<typename T>
            requires std::is_enum_v<std::remove_cvref_t<T>>
        void Write(const T value)
        {
            Write(static_cast<std::underlying_type_t<T>>(value));
        }


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

        template<typename T>
            requires ( IsStdVector<T> && IsBoolean<typename T::value_type> )
        void Write( const T& values )
        {
            WriteSize( values.size( ) );
            for ( auto value : values )
            {
                Byte buffer = (Byte)( value ? 1 : 0 );
                static_cast<Derived&>( *this ).Write( &buffer, 1 );
            }
        }

        template<typename T>
            requires (( IsStdVector<T> && IsBasicType<typename T::value_type> && IsNotBoolean<typename T::value_type> ) || 
                ( IsBasicType<typename T::value_type> && ( IsArrayContainer<T> || IsCoreVector<T> || IsStdSpan<T> ) ) )
        void Write( const T& values )
        {
            auto count = static_cast<size_t>( values.size( ) );
            WriteSize( count );
            if constexpr ( NetworkByteOrder )
            {
                WriteInNetworkByteOrder( values.data( ), count );
            }
            else
            {
                static_cast<Derived&>( *this ).Write( values.data(), count * sizeof( T::value_type ) );
            }
        }

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


    template<IO::StreamWriter StreamT, bool networkByteOrder = false, bool use7BitEncodedSize = true>
    class BinaryWriter : public BinaryWriterBase<BinaryWriter<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>
    {
    public:
        using Base = BinaryWriterBase<BinaryWriter<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>;
        using StreamType = StreamT;
    protected:
        StreamType& outStream_;
    public:
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

        using Base::Write;
        void Write( const void* data, size_t dataSize )
        {
            outStream_.Write( data, dataSize );
        }

    };

}

#endif