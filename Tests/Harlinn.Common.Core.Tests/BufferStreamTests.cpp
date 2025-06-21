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

using namespace Harlinn::Common;
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

BOOST_FIXTURE_TEST_SUITE( BufferStreamTests, LocalFixture )

// --run_test=BufferStreamTests/WriteTest1
BOOST_AUTO_TEST_CASE( WriteTest1 )
{
    std::array<Byte, 9> buffer;
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedPosition = array1.size( ) + array2.size( ) + array3.size( );

    IO::BufferStream bufferStream( buffer.data(), buffer.size());
    bufferStream.Write( array1.data( ), array1.size( ) );
    bufferStream.Write( array2.data( ), array2.size( ) );
    bufferStream.Write( array3.data( ), array3.size( ) );

    auto position = bufferStream.Position( );
    BOOST_CHECK( position == expectedPosition );
    
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

// --run_test=BufferStreamTests/SetPositionTest1
BOOST_AUTO_TEST_CASE( SetPositionTest1 )
{
    std::array<Byte, 9> buffer;
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };

    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    bufferStream.Write( array1.data( ), array1.size( ) );
    bufferStream.Write( array2.data( ), array2.size( ) );
    bufferStream.Write( array3.data( ), array3.size( ) );
    bufferStream.SetPosition( 0 );
    auto position = bufferStream.Position( );
    BOOST_CHECK( position == 0 );
}

// --run_test=BufferStreamTests/SeekTest1
BOOST_AUTO_TEST_CASE( SeekTest1 )
{
    std::array<Byte, 9> buffer;
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    bufferStream.Write( array1.data( ), array1.size( ) );
    bufferStream.Write( array2.data( ), array2.size( ) );
    bufferStream.Write( array3.data( ), array3.size( ) );
    bufferStream.SetPosition( 0 );
    auto position = bufferStream.Position( );
    BOOST_CHECK( position == 0 );

    bufferStream.Seek( 0, IO::SeekOrigin::EndOfFile );
    position = bufferStream.Position( );
    BOOST_CHECK( position == expectedSize );
}

// --run_test=BufferStreamTests/SeekTest2
BOOST_AUTO_TEST_CASE( SeekTest2 )
{
    std::array<Byte, 9> buffer;
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    bufferStream.Write( array1.data( ), array1.size( ) );
    bufferStream.Write( array2.data( ), array2.size( ) );
    bufferStream.Write( array3.data( ), array3.size( ) );
    auto position = bufferStream.Position( );
    BOOST_CHECK( position == expectedSize );

    bufferStream.Seek( -1, IO::SeekOrigin::CurrentPosition );
    position = bufferStream.Position( );
    BOOST_CHECK( position == ( expectedSize - 1 ) );
    bufferStream.Seek( -1, IO::SeekOrigin::CurrentPosition );
    position = bufferStream.Position( );
    BOOST_CHECK( position == ( expectedSize - 2 ) );
}

// --run_test=BufferStreamTests/SeekTest3
BOOST_AUTO_TEST_CASE( SeekTest3 )
{
    std::array<Byte, 9> buffer;
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    bufferStream.Write( array1.data( ), array1.size( ) );
    bufferStream.Write( array2.data( ), array2.size( ) );
    bufferStream.Write( array3.data( ), array3.size( ) );
    auto position = bufferStream.Position( );
    BOOST_CHECK( position == expectedSize );

    bufferStream.Seek( 1, IO::SeekOrigin::StartOfFile );
    position = bufferStream.Position( );
    BOOST_CHECK( position == 1 );
}

// --run_test=BufferStreamTests/CanReadTest1
BOOST_AUTO_TEST_CASE( CanReadTest1 )
{
    std::array<Byte, 9> buffer;
    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    auto value = bufferStream.CanRead( );
    BOOST_CHECK( value );
}

// --run_test=BufferStreamTests/CanWriteTest1
BOOST_AUTO_TEST_CASE( CanWriteTest1 )
{
    std::array<Byte, 9> buffer;
    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    auto value = bufferStream.CanWrite( );
    BOOST_CHECK( value );
}

// --run_test=BufferStreamTests/CanSeekTest1
BOOST_AUTO_TEST_CASE( CanSeekTest1 )
{
    std::array<Byte, 9> buffer;
    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    auto value = bufferStream.CanSeek( );
    BOOST_CHECK( value );
}


// --run_test=BufferStreamTests/CanTimeoutTest1
BOOST_AUTO_TEST_CASE( CanTimeoutTest1 )
{
    std::array<Byte, 9> buffer;
    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    auto value = bufferStream.CanTimeout( );
    BOOST_CHECK( value == false );
}

// --run_test=BufferStreamTests/ReadTest1
BOOST_AUTO_TEST_CASE( ReadTest1 )
{
    std::array<Byte, 9> buffer;
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    std::array<Byte, 3> array1r{ 0,0,0 };
    std::array<Byte, 3> array2r{ 0,0,0 };
    std::array<Byte, 3> array3r{ 0,0,0 };


    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::BufferStream bufferStream( buffer.data( ), buffer.size( ) );
    bufferStream.Write( array1.data( ), array1.size( ) );
    bufferStream.Write( array2.data( ), array2.size( ) );
    bufferStream.Write( array3.data( ), array3.size( ) );
    auto size = bufferStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto position = bufferStream.Position( );
    BOOST_CHECK( position == expectedSize );
    bufferStream.SetPosition( 0 );
    position = bufferStream.Position( );
    BOOST_CHECK( position == 0 );
    bufferStream.Read( array1r.data( ), array1r.size( ) );
    bufferStream.Read( array2r.data( ), array2r.size( ) );
    bufferStream.Read( array3r.data( ), array3r.size( ) );
    BOOST_CHECK( array1r == array1 );
    BOOST_CHECK( array2r == array2 );
    BOOST_CHECK( array3r == array3 );


}




BOOST_AUTO_TEST_SUITE_END( )