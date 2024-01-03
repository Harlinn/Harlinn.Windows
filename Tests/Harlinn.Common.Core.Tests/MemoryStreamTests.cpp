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

BOOST_FIXTURE_TEST_SUITE( MemoryStreamTests, LocalFixture )

// --run_test=MemoryStreamTests/WriteTest1
BOOST_AUTO_TEST_CASE( WriteTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::MemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto size = memoryStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );
    Byte* buffer = memoryStream.Buffer( );
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

// --run_test=MemoryStreamTests/SetPositionTest1
BOOST_AUTO_TEST_CASE( SetPositionTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };

    IO::MemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    memoryStream.SetPosition( 0 );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == 0 );

}

// --run_test=MemoryStreamTests/SeekTest1
BOOST_AUTO_TEST_CASE( SeekTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::MemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    memoryStream.SetPosition( 0 );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == 0 );

    memoryStream.Seek( 0, IO::SeekOrigin::EndOfFile );
    position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );
}

// --run_test=MemoryStreamTests/SeekTest2
BOOST_AUTO_TEST_CASE( SeekTest2 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::MemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );

    memoryStream.Seek( -1, IO::SeekOrigin::CurrentPosition );
    position = memoryStream.Position( );
    BOOST_CHECK( position == (expectedSize - 1) );
    memoryStream.Seek( -1, IO::SeekOrigin::CurrentPosition );
    position = memoryStream.Position( );
    BOOST_CHECK( position == ( expectedSize - 2 ) );
}

// --run_test=MemoryStreamTests/SeekTest3
BOOST_AUTO_TEST_CASE( SeekTest3 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::MemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );

    memoryStream.Seek( 1, IO::SeekOrigin::StartOfFile );
    position = memoryStream.Position( );
    BOOST_CHECK( position == 1 );
}

// --run_test=MemoryStreamTests/SeekTest4
BOOST_AUTO_TEST_CASE( SeekTest4 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    std::array<Byte, 4> array4{ 4,4,4,4 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::MemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );

    memoryStream.Seek( 11, IO::SeekOrigin::StartOfFile );
    position = memoryStream.Position( );
    BOOST_CHECK( position == 11 );
    auto size = memoryStream.Size( );
    BOOST_CHECK( size == 11 );
    memoryStream.Write( array4.data( ), array4.size( ) );
    size = memoryStream.Size( );
    BOOST_CHECK( size == 15 );


}



// --run_test=MemoryStreamTests/CapacityTest1
BOOST_AUTO_TEST_CASE( CapacityTest1 )
{
    constexpr size_t expectedCapacity = 1024 * 1024;
    IO::MemoryStream memoryStream;
    memoryStream.SetCapacity( expectedCapacity );
    auto capacity = memoryStream.Capacity( );
    BOOST_CHECK( capacity == expectedCapacity );
    auto size = memoryStream.Size( );
    BOOST_CHECK( size == 0 );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == 0 );

}

// --run_test=MemoryStreamTests/SizeTest1
BOOST_AUTO_TEST_CASE( SizeTest1 )
{
    constexpr size_t expectedSize = 1024 * 1024;
    IO::MemoryStream memoryStream;
    memoryStream.SetSize( expectedSize );
    auto size = memoryStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto capacity = memoryStream.Capacity( );
    BOOST_CHECK( capacity >= size );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == 0 );
}

// --run_test=MemoryStreamTests/CanReadTest1
BOOST_AUTO_TEST_CASE( CanReadTest1 )
{
    IO::MemoryStream memoryStream;
    auto value = memoryStream.CanRead( );
    BOOST_CHECK( value );
}

// --run_test=MemoryStreamTests/CanWriteTest1
BOOST_AUTO_TEST_CASE( CanWriteTest1 )
{
    IO::MemoryStream memoryStream;
    auto value = memoryStream.CanWrite( );
    BOOST_CHECK( value );
}

// --run_test=MemoryStreamTests/CanSeekTest1
BOOST_AUTO_TEST_CASE( CanSeekTest1 )
{
    IO::MemoryStream memoryStream;
    auto value = memoryStream.CanSeek( );
    BOOST_CHECK( value );
}


// --run_test=MemoryStreamTests/CanTimeoutTest1
BOOST_AUTO_TEST_CASE( CanTimeoutTest1 )
{
    IO::MemoryStream memoryStream;
    auto value = memoryStream.CanTimeout( );
    BOOST_CHECK( value == false );
}

// --run_test=MemoryStreamTests/ReadTest1
BOOST_AUTO_TEST_CASE( ReadTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    std::array<Byte, 3> array1r{ 0,0,0 };
    std::array<Byte, 3> array2r{ 0,0,0 };
    std::array<Byte, 3> array3r{ 0,0,0 };


    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::MemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto size = memoryStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );
    memoryStream.SetPosition( 0 );
    position = memoryStream.Position( );
    BOOST_CHECK( position == 0 );
    memoryStream.Read( array1r.data( ), array1r.size( ) );
    memoryStream.Read( array2r.data( ), array2r.size( ) );
    memoryStream.Read( array3r.data( ), array3r.size( ) );
    BOOST_CHECK( array1r == array1 );
    BOOST_CHECK( array2r == array2 );
    BOOST_CHECK( array3r == array3 );

    
}



BOOST_AUTO_TEST_SUITE_END( )

