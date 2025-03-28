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

BOOST_FIXTURE_TEST_SUITE( GuidTests, LocalFixture )

// --run_test=GuidTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    Guid guid;
    BOOST_CHECK( guid.empty( ) );
    BOOST_CHECK( guid ? false : true );
}

// --run_test=GuidTests/ConstructorTest2
BOOST_AUTO_TEST_CASE( ConstructorTest2 )
{
    // {8D544315-5A2F-4807-93D5-F66E5D690197}
    static const GUID expectedGuid = { 0x8d544315, 0x5a2f, 0x4807, { 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 } };
    constexpr unsigned char bytes[ ] = { 0x15, 0x43, 0x54, 0x8D, 0x2F, 0x5A, 0x07, 0x48, 0x93, 0xD5, 0xF6, 0x6E, 0x5D, 0x69, 0x01, 0x97 };
    constexpr unsigned long long uint64s[ ] = { 0x48075A2F8D544315, 0x9701695D6EF6D593 };

    Guid guid1( expectedGuid );
    BOOST_CHECK( guid1 == expectedGuid );
    BOOST_CHECK( guid1 ? true : false );

    Guid guid2( uint64s[0], uint64s[ 1 ] );
    BOOST_CHECK( guid2 == expectedGuid );

    Guid guid3( uint64s );
    BOOST_CHECK( guid3 == expectedGuid );

    Guid guid4( bytes );
    BOOST_CHECK( guid4 == expectedGuid );

    Guid guid5( { 0x15, 0x43, 0x54, 0x8D, 0x2F, 0x5A, 0x07, 0x48, 0x93, 0xD5, 0xF6, 0x6E, 0x5D, 0x69, 0x01, 0x97 } );
    BOOST_CHECK( guid5 == expectedGuid );

    Guid guid6( 0x15, 0x43, 0x54, 0x8D, 0x2F, 0x5A, 0x07, 0x48, 0x93, 0xD5, 0xF6, 0x6E, 0x5D, 0x69, 0x01, 0x97);
    BOOST_CHECK( guid6 == expectedGuid );

}

// --run_test=GuidTests/ConstructorTest3
BOOST_AUTO_TEST_CASE( ConstructorTest3 )
{
    // {8D544315-5A2F-4807-93D5-F66E5D690197}
    static const GUID expectedGuid = { 0x8d544315, 0x5a2f, 0x4807, { 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 } };

    Guid guid( L"{8D544315-5A2F-4807-93D5-F66E5D690197}" );
    BOOST_CHECK( guid == expectedGuid );
}

// --run_test=GuidTests/ConstructorTest4
BOOST_AUTO_TEST_CASE( ConstructorTest4 )
{
    // {8D544315-5A2F-4807-93D5-F66E5D690197}
    static const GUID expectedGuid = { 0x8d544315, 0x5a2f, 0x4807, { 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 } };

    Guid guid( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    BOOST_CHECK( guid == expectedGuid );
}

// --run_test=GuidTests/ToStringTest1
BOOST_AUTO_TEST_CASE( ToStringTest1 )
{
    // {8D544315-5A2F-4807-93D5-F66E5D690197}
    static const GUID expectedGuid = { 0x8d544315, 0x5a2f, 0x4807, { 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 } };

    Guid guid( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    BOOST_CHECK( guid == expectedGuid );
    auto str = guid.ToWideString( );
    BOOST_CHECK( str == L"{8D544315-5A2F-4807-93D5-F66E5D690197}" );

}

// --run_test=GuidTests/EqTest1
BOOST_AUTO_TEST_CASE( EqTest1 )
{
    Guid guid1a( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid1b( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid2a( 0xa46d5eb1, 0x7606, 0x4418, 0x90, 0x68, 0xf8, 0x36, 0x98, 0x28, 0xe6, 0xc9 );

    BOOST_CHECK( guid1a == guid1b );
    BOOST_CHECK( (guid1a == guid2a) == false );
}

// --run_test=GuidTests/NotEqTest1
BOOST_AUTO_TEST_CASE( NotEqTest1 )
{
    Guid guid1a( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid1b( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid2a( 0xa46d5eb1, 0x7606, 0x4418, 0x90, 0x68, 0xf8, 0x36, 0x98, 0x28, 0xe6, 0xc9 );

    BOOST_CHECK( guid1a != guid2a );
    BOOST_CHECK( ( guid1a != guid1b ) == false );
}

// --run_test=GuidTests/LtTest1
BOOST_AUTO_TEST_CASE( LtTest1 )
{
    Guid guid1a( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid1b( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid2a( 0xa46d5eb1, 0x7606, 0x4418, 0x90, 0x68, 0xf8, 0x36, 0x98, 0x28, 0xe6, 0xc9 );

    BOOST_CHECK( guid1a < guid2a );
    BOOST_CHECK( ( guid1a < guid1b ) == false );
}

// --run_test=GuidTests/LtEqTest1
BOOST_AUTO_TEST_CASE( LtEqTest1 )
{
    Guid guid1a( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid1b( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid2a( 0xa46d5eb1, 0x7606, 0x4418, 0x90, 0x68, 0xf8, 0x36, 0x98, 0x28, 0xe6, 0xc9 );

    BOOST_CHECK( guid1a < guid2a );
    BOOST_CHECK( guid1a <= guid1b );
}


// --run_test=GuidTests/GtTest1
BOOST_AUTO_TEST_CASE( GtTest1 )
{
    Guid guid1a( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid1b( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid2a( 0xa46d5eb1, 0x7606, 0x4418, 0x90, 0x68, 0xf8, 0x36, 0x98, 0x28, 0xe6, 0xc9 );

    BOOST_CHECK( guid2a > guid1a );
    BOOST_CHECK( ( guid1a > guid1b ) == false );
}

// --run_test=GuidTests/GtEqTest1
BOOST_AUTO_TEST_CASE( GtEqTest1 )
{
    Guid guid1a( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid1b( 0x8d544315, 0x5a2f, 0x4807, 0x93, 0xd5, 0xf6, 0x6e, 0x5d, 0x69, 0x1, 0x97 );
    Guid guid2a( 0xa46d5eb1, 0x7606, 0x4418, 0x90, 0x68, 0xf8, 0x36, 0x98, 0x28, 0xe6, 0xc9 );

    BOOST_CHECK( guid2a >= guid1a );
    BOOST_CHECK( guid1a >= guid1b );
}




BOOST_AUTO_TEST_SUITE_END( )