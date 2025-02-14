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
        LocalFixture( )
        {
            CoInitializeEx( nullptr, COINIT_MULTITHREADED );
        }
        ~LocalFixture( )
        {
            CoUninitialize( );
        }
    };
}

BOOST_FIXTURE_TEST_SUITE( IStreamMemoryStreamTests, LocalFixture )

// --run_test=IStreamMemoryStreamTests/WriteTest1
BOOST_AUTO_TEST_CASE( WriteTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::IStreamMemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto size = memoryStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );
}

// --run_test=IStreamMemoryStreamTests/SetPositionTest1
BOOST_AUTO_TEST_CASE( SetPositionTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };

    IO::IStreamMemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    memoryStream.SetPosition( 0 );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == 0 );

}

// --run_test=IStreamMemoryStreamTests/SeekTest1
BOOST_AUTO_TEST_CASE( SeekTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::IStreamMemoryStream memoryStream;
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

// --run_test=IStreamMemoryStreamTests/SeekTest2
BOOST_AUTO_TEST_CASE( SeekTest2 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::IStreamMemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );

    memoryStream.Seek( -1, IO::SeekOrigin::CurrentPosition );
    position = memoryStream.Position( );
    BOOST_CHECK( position == ( expectedSize - 1 ) );
    memoryStream.Seek( -1, IO::SeekOrigin::CurrentPosition );
    position = memoryStream.Position( );
    BOOST_CHECK( position == ( expectedSize - 2 ) );
}

// --run_test=IStreamMemoryStreamTests/SeekTest3
BOOST_AUTO_TEST_CASE( SeekTest3 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::IStreamMemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );

    memoryStream.Seek( 1, IO::SeekOrigin::StartOfFile );
    position = memoryStream.Position( );
    BOOST_CHECK( position == 1 );
}

// --run_test=IStreamMemoryStreamTests/SeekTest4
BOOST_AUTO_TEST_CASE( SeekTest4 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    std::array<Byte, 4> array4{ 4,4,4,4 };
    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::IStreamMemoryStream memoryStream;
    memoryStream.Write( array1.data( ), array1.size( ) );
    memoryStream.Write( array2.data( ), array2.size( ) );
    memoryStream.Write( array3.data( ), array3.size( ) );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == expectedSize );

    memoryStream.Seek( 11, IO::SeekOrigin::StartOfFile );
    position = memoryStream.Position( );
    BOOST_CHECK( position == 11 );
    auto size = memoryStream.Size( );
    // Setting the position does not change the size
    BOOST_CHECK( size == 9 );
    memoryStream.Write( array4.data( ), array4.size( ) );
    size = memoryStream.Size( );
    BOOST_CHECK( size == 15 );


}

// --run_test=IStreamMemoryStreamTests/SizeTest1
BOOST_AUTO_TEST_CASE( SizeTest1 )
{
    constexpr size_t expectedSize = 1024 * 1024;
    IO::IStreamMemoryStream memoryStream;
    memoryStream.SetSize( expectedSize );
    auto size = memoryStream.Size( );
    BOOST_CHECK( size == expectedSize );
    auto position = memoryStream.Position( );
    BOOST_CHECK( position == 0 );
}

// --run_test=IStreamMemoryStreamTests/CanReadTest1
BOOST_AUTO_TEST_CASE( CanReadTest1 )
{
    IO::IStreamMemoryStream memoryStream;
    auto value = memoryStream.CanRead( );
    BOOST_CHECK( value );
}

// --run_test=IStreamMemoryStreamTests/CanWriteTest1
BOOST_AUTO_TEST_CASE( CanWriteTest1 )
{
    IO::IStreamMemoryStream memoryStream;
    auto value = memoryStream.CanWrite( );
    BOOST_CHECK( value );
}

// --run_test=IStreamMemoryStreamTests/CanSeekTest1
BOOST_AUTO_TEST_CASE( CanSeekTest1 )
{
    IO::IStreamMemoryStream memoryStream;
    auto value = memoryStream.CanSeek( );
    BOOST_CHECK( value );
}


// --run_test=IStreamMemoryStreamTests/CanTimeoutTest1
BOOST_AUTO_TEST_CASE( CanTimeoutTest1 )
{
    IO::IStreamMemoryStream memoryStream;
    auto value = memoryStream.CanTimeout( );
    BOOST_CHECK( value == false );
}

// --run_test=IStreamMemoryStreamTests/ReadTest1
BOOST_AUTO_TEST_CASE( ReadTest1 )
{
    std::array<Byte, 3> array1{ 1,1,1 };
    std::array<Byte, 3> array2{ 2,2,2 };
    std::array<Byte, 3> array3{ 3,3,3 };
    std::array<Byte, 3> array1r{ 0,0,0 };
    std::array<Byte, 3> array2r{ 0,0,0 };
    std::array<Byte, 3> array3r{ 0,0,0 };


    auto expectedSize = array1.size( ) + array2.size( ) + array3.size( );

    IO::IStreamMemoryStream memoryStream;
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
