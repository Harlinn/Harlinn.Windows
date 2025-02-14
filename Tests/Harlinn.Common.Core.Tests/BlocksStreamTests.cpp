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
#include "pch.h"

using namespace Harlinn::Common::Core;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( BlocksStreamTests, LocalFixture )

// --run_test=BlocksStreamTests/WriteTest1
BOOST_AUTO_TEST_CASE( WriteTest1 )
{
    
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::Blocks::Stream blocksStream;
    blocksStream.Write( array1.data( ), array1.size( ) );
    blocksStream.Write( array2.data( ), array2.size( ) );
    blocksStream.Write( array3.data( ), array3.size( ) );
    auto size = blocksStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto position = blocksStream.Position( );
    BOOST_CHECK( position == expectedSize );

    auto& blocks = blocksStream.Blocks( );
    auto blockCount = blocks.size( );
    BOOST_CHECK( blockCount == 1 );
    auto* block = blocks.Head( );

    Byte* buffer = block->data( );
    BOOST_CHECK( buffer[0] == array1[0] );
    BOOST_CHECK( buffer[1] == array1[1] );
    BOOST_CHECK( buffer[2] == array1[2] );
    BOOST_CHECK( buffer[3] == array2[0] );
    BOOST_CHECK( buffer[4] == array2[1] );
    BOOST_CHECK( buffer[5] == array2[2] );
    BOOST_CHECK( buffer[6] == array3[0] );
    BOOST_CHECK( buffer[7] == array3[1] );
    BOOST_CHECK( buffer[8] == array3[2] );
}

// --run_test=BlocksStreamTests/SetPositionTest1
BOOST_AUTO_TEST_CASE( SetPositionTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };

    IO::Blocks::Stream blocksStream;
    blocksStream.Write( array1.data( ), array1.size( ) );
    blocksStream.Write( array2.data( ), array2.size( ) );
    blocksStream.Write( array3.data( ), array3.size( ) );
    blocksStream.SetPosition( 0 );
    auto position = blocksStream.Position( );
    BOOST_CHECK( position == 0 );

}

// --run_test=BlocksStreamTests/SeekTest1
BOOST_AUTO_TEST_CASE( SeekTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::Blocks::Stream blocksStream;
    blocksStream.Write( array1.data( ), array1.size( ) );
    blocksStream.Write( array2.data( ), array2.size( ) );
    blocksStream.Write( array3.data( ), array3.size( ) );
    blocksStream.SetPosition( 0 );
    auto position = blocksStream.Position( );
    BOOST_CHECK( position == 0 );

    blocksStream.Seek( 0, IO::SeekOrigin::EndOfFile );
    position = blocksStream.Position( );
    BOOST_CHECK( position == expectedSize );
}

// --run_test=BlocksStreamTests/SeekTest2
BOOST_AUTO_TEST_CASE( SeekTest2 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::Blocks::Stream blocksStream;
    blocksStream.Write( array1.data( ), array1.size( ) );
    blocksStream.Write( array2.data( ), array2.size( ) );
    blocksStream.Write( array3.data( ), array3.size( ) );
    auto position = blocksStream.Position( );
    BOOST_CHECK( position == expectedSize );

    blocksStream.Seek( -1, IO::SeekOrigin::CurrentPosition );
    position = blocksStream.Position( );
    BOOST_CHECK( position == ( expectedSize - 1 ) );
    blocksStream.Seek( -1, IO::SeekOrigin::CurrentPosition );
    position = blocksStream.Position( );
    BOOST_CHECK( position == ( expectedSize - 2 ) );
}

// --run_test=BlocksStreamTests/SeekTest3
BOOST_AUTO_TEST_CASE( SeekTest3 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::Blocks::Stream blocksStream;
    blocksStream.Write( array1.data( ), array1.size( ) );
    blocksStream.Write( array2.data( ), array2.size( ) );
    blocksStream.Write( array3.data( ), array3.size( ) );
    auto position = blocksStream.Position( );
    BOOST_CHECK( position == expectedSize );

    blocksStream.Seek( 1, IO::SeekOrigin::StartOfFile );
    position = blocksStream.Position( );
    BOOST_CHECK( position == 1 );
}

// --run_test=BlocksStreamTests/SeekTest4
BOOST_AUTO_TEST_CASE( SeekTest4 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    std::array<Byte, 4> array4{ 4,4,4,4 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::Blocks::Stream blocksStream;
    blocksStream.Write( array1.data( ), array1.size( ) );
    blocksStream.Write( array2.data( ), array2.size( ) );
    blocksStream.Write( array3.data( ), array3.size( ) );
    auto position = blocksStream.Position( );
    BOOST_CHECK( position == expectedSize );

    blocksStream.Seek( 11, IO::SeekOrigin::StartOfFile );
    position = blocksStream.Position( );
    BOOST_CHECK( position == 11 );
    auto size = blocksStream.Size( );
    BOOST_CHECK( size == 11 );
    blocksStream.Write( array4.data( ), array4.size( ) );
    size = blocksStream.Size( );
    BOOST_CHECK( size == 15 );


}

// --run_test=BlocksStreamTests/SizeTest1
BOOST_AUTO_TEST_CASE( SizeTest1 )
{
    constexpr size_t expectedSize = 1024 * 1024;
    IO::Blocks::Stream blocksStream;
    blocksStream.SetSize( expectedSize );
    auto size = blocksStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto position = blocksStream.Position( );
    BOOST_CHECK( position == 0 );
}

// --run_test=BlocksStreamTests/CanReadTest1
BOOST_AUTO_TEST_CASE( CanReadTest1 )
{
    IO::Blocks::Stream blocksStream;
    auto value = blocksStream.CanRead( );
    BOOST_CHECK( value );
}

// --run_test=BlocksStreamTests/CanWriteTest1
BOOST_AUTO_TEST_CASE( CanWriteTest1 )
{
    IO::Blocks::Stream blocksStream;
    auto value = blocksStream.CanWrite( );
    BOOST_CHECK( value );
}

// --run_test=BlocksStreamTests/CanSeekTest1
BOOST_AUTO_TEST_CASE( CanSeekTest1 )
{
    IO::Blocks::Stream blocksStream;
    auto value = blocksStream.CanSeek( );
    BOOST_CHECK( value );
}


// --run_test=BlocksStreamTests/CanTimeoutTest1
BOOST_AUTO_TEST_CASE( CanTimeoutTest1 )
{
    IO::Blocks::Stream blocksStream;
    auto value = blocksStream.CanTimeout( );
    BOOST_CHECK( value == false );
}

// --run_test=BlocksStreamTests/ReadTest1
BOOST_AUTO_TEST_CASE( ReadTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    std::array<Byte, 3> array1r{ 0,0,0 };
    std::array<Byte, 3> array2r{ 0,0,0 };
    std::array<Byte, 3> array3r{ 0,0,0 };


    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::Blocks::Stream blocksStream;
    blocksStream.Write( array1.data( ), array1.size( ) );
    blocksStream.Write( array2.data( ), array2.size( ) );
    blocksStream.Write( array3.data( ), array3.size( ) );
    auto size = blocksStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto position = blocksStream.Position( );
    BOOST_CHECK( position == expectedSize );
    blocksStream.SetPosition( 0 );
    position = blocksStream.Position( );
    BOOST_CHECK( position == 0 );
    blocksStream.Read( array1r.data( ), array1r.size( ) );
    blocksStream.Read( array2r.data( ), array2r.size( ) );
    blocksStream.Read( array3r.data( ), array3r.size( ) );
    BOOST_CHECK( array1r == array1 );
    BOOST_CHECK( array2r == array2 );
    BOOST_CHECK( array3r == array3 );
}


// --run_test=BlocksStreamTests/WriteTest2
BOOST_AUTO_TEST_CASE( WriteTest2 )
{
    constexpr size_t BlockDataSize = IO::Blocks::Stream::BlockDataSize;
    constexpr size_t InitialSize = 1024*1024*24;

    std::vector<Byte> vector1( InitialSize, static_cast<Byte>( 1 ) );
    std::vector<Byte> vector2( InitialSize, static_cast<Byte>( 2 ) );

    IO::Blocks::Stream blocksStream;
    std::array<size_t, 5> writeSizes{1,2,3,4,5};
    size_t i = 0;
    while ( i < InitialSize )
    {
        auto* data = vector1.data( );
        auto remaining = InitialSize - i;
        auto writeSize = std::min( writeSizes[i % writeSizes.size( )], remaining );
        blocksStream.Write( &data[i], writeSize );
        i += writeSize;
    }

    auto size = blocksStream.Size( );
    BOOST_CHECK( size == InitialSize );
    blocksStream.SetPosition( 0 );
    blocksStream.Read( vector2.data( ), InitialSize );
    BOOST_CHECK( vector1 == vector2 );
}

// --run_test=BlocksStreamTests/WriteTest3
BOOST_AUTO_TEST_CASE( WriteTest3 )
{
    constexpr size_t BlockDataSize = IO::Blocks::Stream::BlockDataSize;
    constexpr size_t InitialSize = 1024 * 1024 * 24;

    std::vector<Byte> vector1( InitialSize, static_cast<Byte>( 1 ) );
    std::vector<Byte> vector2( InitialSize, static_cast<Byte>( 2 ) );
    std::vector<Byte> vector3( InitialSize, static_cast<Byte>( 1 ) );
    std::vector<Byte> vector4( InitialSize, static_cast<Byte>( 4 ) );

    IO::Blocks::Stream blocksStream;
    std::array<size_t, 5> writeSizes{ 1,2,3,4,5 };
    size_t i = 0;
    while ( i < InitialSize )
    {
        auto* data = vector1.data( );
        auto remaining = InitialSize - i;
        auto writeSize = std::min( writeSizes[i % writeSizes.size( )], remaining );
        blocksStream.Write( &data[i], writeSize );
        i += writeSize;
    }

    auto size = blocksStream.Size( );
    BOOST_CHECK( size == InitialSize );
    i = 0;
    while ( i < InitialSize )
    {
        auto* data2 = vector2.data( );
        auto* data3 = vector3.data( );
        auto remaining = InitialSize - i;
        auto writeSize = writeSizes[i % writeSizes.size( )];
        auto numberofBytesToWrite = std::min( writeSize, remaining );
        if ( writeSize < 4 )
        {
            blocksStream.SetPosition( static_cast<Int64>(i) );
            blocksStream.Write( &data2[i], numberofBytesToWrite );
            memcpy( &data3[i], &data2[i], numberofBytesToWrite );
        }
        i += numberofBytesToWrite;
    }

    size = blocksStream.Size( );
    BOOST_CHECK( size == InitialSize );
    blocksStream.SetPosition( 0 );
    blocksStream.Read( vector4.data( ), InitialSize );
    for ( i = 0; i < InitialSize; ++i )
    {
        auto value3 = vector3[i];
        auto value4 = vector4[i];
        if ( value3 != value4 )
        {
            auto remaining = InitialSize - i;
            auto blockOffset = i % BlockDataSize;
            printf( "Difference located at %zu of %zu - remaining %zu, segment size: %zu, segment offset: %zu ,vector3[i]: %d, vector4[i]: %d\n",i, InitialSize, remaining, BlockDataSize, blockOffset,value3, value4 );
            break;
        }
    }

    BOOST_CHECK( vector3 == vector4 );
}


// --run_test=BlocksStreamTests/BoolTest1
BOOST_AUTO_TEST_CASE( BoolTest1 )
{
    constexpr bool value1 = false;
    constexpr bool value2 = true;
    std::optional<bool> optional1;
    std::optional<bool> optional2 = value1;
    std::optional<bool> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<bool>( );
    auto v2 = reader.Read<bool>( );
    auto v3 = reader.Read<std::optional<bool>>( );
    auto v4 = reader.Read<std::optional<bool>>( );
    auto v5 = reader.Read<std::optional<bool>>( );
    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/SByteTest1
BOOST_AUTO_TEST_CASE( SByteTest1 )
{
    constexpr SByte value1 = 10;
    constexpr SByte value2 = 100;
    std::optional<SByte> optional1;
    std::optional<SByte> optional2 = value1;
    std::optional<SByte> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<SByte>( );
    auto v2 = reader.Read<SByte>( );
    auto v3 = reader.Read<std::optional<SByte>>( );
    auto v4 = reader.Read<std::optional<SByte>>( );
    auto v5 = reader.Read<std::optional<SByte>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/ByteTest1
BOOST_AUTO_TEST_CASE( ByteTest1 )
{
    constexpr Byte value1 = 10;
    constexpr Byte value2 = 100;
    std::optional<Byte> optional1;
    std::optional<Byte> optional2 = value1;
    std::optional<Byte> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<Byte>( );
    auto v2 = reader.Read<Byte>( );
    auto v3 = reader.Read<std::optional<Byte>>( );
    auto v4 = reader.Read<std::optional<Byte>>( );
    auto v5 = reader.Read<std::optional<Byte>>( );
    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/Int16Test1
BOOST_AUTO_TEST_CASE( Int16Test1 )
{
    constexpr Int16 value1 = 10;
    constexpr Int16 value2 = 100;
    std::optional<Int16> optional1;
    std::optional<Int16> optional2 = value1;
    std::optional<Int16> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<Int16>( );
    auto v2 = reader.Read<Int16>( );
    auto v3 = reader.Read<std::optional<Int16>>( );
    auto v4 = reader.Read<std::optional<Int16>>( );
    auto v5 = reader.Read<std::optional<Int16>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/UInt16Test1
BOOST_AUTO_TEST_CASE( UInt16Test1 )
{
    constexpr UInt16 value1 = 10;
    constexpr UInt16 value2 = 100;
    std::optional<UInt16> optional1;
    std::optional<UInt16> optional2 = value1;
    std::optional<UInt16> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<UInt16>( );
    auto v2 = reader.Read<UInt16>( );
    auto v3 = reader.Read<std::optional<UInt16>>( );
    auto v4 = reader.Read<std::optional<UInt16>>( );
    auto v5 = reader.Read<std::optional<UInt16>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/Int32Test1
BOOST_AUTO_TEST_CASE( Int32Test1 )
{
    constexpr Int32 value1 = 10;
    constexpr Int32 value2 = 100;
    std::optional<Int32> optional1;
    std::optional<Int32> optional2 = value1;
    std::optional<Int32> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<Int32>( );
    auto v2 = reader.Read<Int32>( );
    auto v3 = reader.Read<std::optional<Int32>>( );
    auto v4 = reader.Read<std::optional<Int32>>( );
    auto v5 = reader.Read<std::optional<Int32>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/UInt32Test1
BOOST_AUTO_TEST_CASE( UInt32Test1 )
{
    constexpr UInt32 value1 = 10;
    constexpr UInt32 value2 = 100;
    std::optional<UInt32> optional1;
    std::optional<UInt32> optional2 = value1;
    std::optional<UInt32> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<UInt32>( );
    auto v2 = reader.Read<UInt32>( );
    auto v3 = reader.Read<std::optional<UInt32>>( );
    auto v4 = reader.Read<std::optional<UInt32>>( );
    auto v5 = reader.Read<std::optional<UInt32>>( );
    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/Int64Test1
BOOST_AUTO_TEST_CASE( Int64Test1 )
{
    constexpr Int64 value1 = 10;
    constexpr Int64 value2 = 100;
    std::optional<Int64> optional1;
    std::optional<Int64> optional2 = value1;
    std::optional<Int64> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<Int64>( );
    auto v2 = reader.Read<Int64>( );
    auto v3 = reader.Read<std::optional<Int64>>( );
    auto v4 = reader.Read<std::optional<Int64>>( );
    auto v5 = reader.Read<std::optional<Int64>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/UInt64Test1
BOOST_AUTO_TEST_CASE( UInt64Test1 )
{
    constexpr UInt64 value1 = 10;
    constexpr UInt64 value2 = 100;
    std::optional<UInt64> optional1;
    std::optional<UInt64> optional2 = value1;
    std::optional<UInt64> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<UInt64>( );
    auto v2 = reader.Read<UInt64>( );
    auto v3 = reader.Read<std::optional<UInt64>>( );
    auto v4 = reader.Read<std::optional<UInt64>>( );
    auto v5 = reader.Read<std::optional<UInt64>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}


// --run_test=BlocksStreamTests/SingleTest1
BOOST_AUTO_TEST_CASE( SingleTest1 )
{
    constexpr float value1 = 10;
    constexpr float value2 = 100;
    std::optional<float> optional1;
    std::optional<float> optional2 = value1;
    std::optional<float> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<float>( );
    auto v2 = reader.Read<float>( );
    auto v3 = reader.Read<std::optional<float>>( );
    auto v4 = reader.Read<std::optional<float>>( );
    auto v5 = reader.Read<std::optional<float>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}


// --run_test=BlocksStreamTests/DoubleTest1
BOOST_AUTO_TEST_CASE( DoubleTest1 )
{
    constexpr Double value1 = 10;
    constexpr Double value2 = 100;
    std::optional<Double> optional1;
    std::optional<Double> optional2 = value1;
    std::optional<Double> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<Double>( );
    auto v2 = reader.Read<Double>( );
    auto v3 = reader.Read<std::optional<Double>>( );
    auto v4 = reader.Read<std::optional<Double>>( );
    auto v5 = reader.Read<std::optional<Double>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/DateTimeTest1
BOOST_AUTO_TEST_CASE( DateTimeTest1 )
{
    DateTime value1( 2020, 1, 10 );
    DateTime value2( 2020, 1, 20 );
    std::optional<DateTime> optional1;
    std::optional<DateTime> optional2 = value1;
    std::optional<DateTime> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<DateTime>( );
    auto v2 = reader.Read<DateTime>( );
    auto v3 = reader.Read<std::optional<DateTime>>( );
    auto v4 = reader.Read<std::optional<DateTime>>( );
    auto v5 = reader.Read<std::optional<DateTime>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/TimeSpanTest1
BOOST_AUTO_TEST_CASE( TimeSpanTest1 )
{
    TimeSpan value1( 2000LL );
    TimeSpan value2( 3000LL );
    std::optional<TimeSpan> optional1;
    std::optional<TimeSpan> optional2 = value1;
    std::optional<TimeSpan> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<TimeSpan>( );
    auto v2 = reader.Read<TimeSpan>( );
    auto v3 = reader.Read<std::optional<TimeSpan>>( );
    auto v4 = reader.Read<std::optional<TimeSpan>>( );
    auto v5 = reader.Read<std::optional<TimeSpan>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/GuidTest1
BOOST_AUTO_TEST_CASE( GuidTest1 )
{
    Guid value1( L"{A69ED24E-E20D-4A5A-93AF-828ED3D46119}" );
    Guid value2( L"{4C42B1DB-9209-4EA3-8700-C438789FB47F}" );
    std::optional<Guid> optional1;
    std::optional<Guid> optional2 = value1;
    std::optional<Guid> optional3 = value2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    writer.Write( optional1 );
    writer.Write( optional2 );
    writer.Write( optional3 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<Guid>( );
    auto v2 = reader.Read<Guid>( );
    auto v3 = reader.Read<std::optional<Guid>>( );
    auto v4 = reader.Read<std::optional<Guid>>( );
    auto v5 = reader.Read<std::optional<Guid>>( );

    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
    BOOST_CHECK( v3.has_value( ) == false );
    BOOST_CHECK( v4.has_value( ) );
    BOOST_CHECK( v4.value( ) == value1 );
    BOOST_CHECK( v5.has_value( ) );
    BOOST_CHECK( v5.value( ) == value2 );
}

// --run_test=BlocksStreamTests/StringTest1
BOOST_AUTO_TEST_CASE( StringTest1 )
{
    AnsiString value1( "s1" );
    AnsiString value2( "s2" );

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( value1 );
    writer.Write( value2 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    auto v1 = reader.Read<AnsiString>( );
    auto v2 = reader.Read<AnsiString>( );
    BOOST_CHECK( value1 == v1 );
    BOOST_CHECK( value2 == v2 );
}


// --run_test=BlocksStreamTests/BoolTest2
BOOST_AUTO_TEST_CASE( BoolTest2 )
{
    std::vector<bool> values1{ true,false };
    std::vector<bool> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == true );
    BOOST_CHECK( values2[1] == false );
}

// --run_test=BlocksStreamTests/BoolTest3
BOOST_AUTO_TEST_CASE( BoolTest3 )
{
    std::vector<bool> values1;
    std::vector<bool> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}


// --run_test=BlocksStreamTests/SByteTest2
BOOST_AUTO_TEST_CASE( SByteTest2 )
{
    std::vector<SByte> values1{ 10,20 };
    std::vector<SByte> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/SByteTest3
BOOST_AUTO_TEST_CASE( SByteTest3 )
{
    std::vector<SByte> values1;
    std::vector<SByte> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/ByteTest2
BOOST_AUTO_TEST_CASE( ByteTest2 )
{
    std::vector<Byte> values1{ 10,20 };
    std::vector<Byte> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/ByteTest3
BOOST_AUTO_TEST_CASE( ByteTest3 )
{
    std::vector<Byte> values1;
    std::vector<Byte> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/Int16Test2
BOOST_AUTO_TEST_CASE( Int16Test2 )
{
    std::vector<Int16> values1{ 10,20 };
    std::vector<Int16> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/Int16Test3
BOOST_AUTO_TEST_CASE( Int16Test3 )
{
    std::vector<Int16> values1;
    std::vector<Int16> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/UInt16Test2
BOOST_AUTO_TEST_CASE( UInt16Test2 )
{
    std::vector<UInt16> values1{ 10,20 };
    std::vector<UInt16> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/UInt16Test3
BOOST_AUTO_TEST_CASE( UInt16Test3 )
{
    std::vector<UInt16> values1;
    std::vector<UInt16> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/Int32Test2
BOOST_AUTO_TEST_CASE( Int32Test2 )
{
    std::vector<Int32> values1{ 10,20 };
    std::vector<Int32> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/Int32Test3
BOOST_AUTO_TEST_CASE( Int32Test3 )
{
    std::vector<Int32> values1;
    std::vector<Int32> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/UInt32Test2
BOOST_AUTO_TEST_CASE( UInt32Test2 )
{
    std::vector<UInt32> values1{ 10,20 };
    std::vector<UInt32> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/UInt32Test3
BOOST_AUTO_TEST_CASE( UInt32Test3 )
{
    std::vector<UInt32> values1;
    std::vector<UInt32> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/Int64Test2
BOOST_AUTO_TEST_CASE( Int64Test2 )
{
    std::vector<Int64> values1{ 10,20 };
    std::vector<Int64> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/Int64Test3
BOOST_AUTO_TEST_CASE( Int64Test3 )
{
    std::vector<Int64> values1;
    std::vector<Int64> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/SByteTest2
BOOST_AUTO_TEST_CASE( UInt64Test2 )
{
    std::vector<UInt64> values1{ 10,20 };
    std::vector<UInt64> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/UInt64Test3
BOOST_AUTO_TEST_CASE( UInt64Test3 )
{
    std::vector<UInt64> values1;
    std::vector<UInt64> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/SingleTest2
BOOST_AUTO_TEST_CASE( SingleTest2 )
{
    std::vector<float> values1{ 10,20 };
    std::vector<float> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/SingleTest3
BOOST_AUTO_TEST_CASE( SingleTest3 )
{
    std::vector<float> values1;
    std::vector<float> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/DoubleTest2
BOOST_AUTO_TEST_CASE( DoubleTest2 )
{
    std::vector<Double> values1{ 10,20 };
    std::vector<Double> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == 10 );
    BOOST_CHECK( values2[1] == 20 );
}

// --run_test=BlocksStreamTests/DoubleTest3
BOOST_AUTO_TEST_CASE( DoubleTest3 )
{
    std::vector<Double> values1;
    std::vector<Double> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/DateTimeTest2
BOOST_AUTO_TEST_CASE( DateTimeTest2 )
{
    std::vector<DateTime> values1{ DateTime( 10LL ),DateTime( 20LL ) };
    std::vector<DateTime> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0].Ticks( ) == 10 );
    BOOST_CHECK( values2[1].Ticks( ) == 20 );
}

// --run_test=BlocksStreamTests/DateTimeTest3
BOOST_AUTO_TEST_CASE( DateTimeTest3 )
{
    std::vector<DateTime> values1;
    std::vector<DateTime> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

// --run_test=BlocksStreamTests/TimeSpanTest2
BOOST_AUTO_TEST_CASE( TimeSpanTest2 )
{
    std::vector<TimeSpan> values1{ TimeSpan( 10LL ),TimeSpan( 20LL ) };
    std::vector<TimeSpan> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0].Ticks( ) == 10 );
    BOOST_CHECK( values2[1].Ticks( ) == 20 );
}

// --run_test=BlocksStreamTests/TimeSpanTest3
BOOST_AUTO_TEST_CASE( TimeSpanTest3 )
{
    std::vector<TimeSpan> values1;
    std::vector<TimeSpan> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}



// --run_test=BlocksStreamTests/GuidTest2
BOOST_AUTO_TEST_CASE( GuidTest2 )
{
    std::vector<Guid> values1{ Guid( L"{67C4E44A-D623-4264-84F8-E7EA902FA441}" ),Guid( L"{5263FE0A-BE9E-4D90-A864-235A64C7171D}" ) };
    std::vector<Guid> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 2 );
    BOOST_CHECK( values2[0] == values1[0] );
    BOOST_CHECK( values2[1] == values1[1] );
}

// --run_test=BlocksStreamTests/GuidTest3
BOOST_AUTO_TEST_CASE( GuidTest3 )
{
    std::vector<Guid> values1;
    std::vector<Guid> values2;

    IO::Blocks::Stream stream;
    IO::BinaryWriter writer( stream );
    writer.Write( values1 );
    stream.SetPosition( 0 );
    IO::BinaryReader reader( stream );

    reader.Read( values2 );
    BOOST_CHECK( values2.size( ) == 0 );
}

BOOST_AUTO_TEST_SUITE_END( )