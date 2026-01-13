/*
   Copyright 2024-2026 Espen Harlinn

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

BOOST_FIXTURE_TEST_SUITE( EnvironmentTests, LocalFixture )

// --run_test=EnvironmentTests/EnvironmentVariableTest1
BOOST_AUTO_TEST_CASE( EnvironmentVariableTest1 )
{
    auto value = Environment::EnvironmentVariable( L"Path" );
    auto size = value.size( );
    BOOST_CHECK( size > 0 );
}

// --run_test=EnvironmentTests/EnvironmentStringsTest1
BOOST_AUTO_TEST_CASE( EnvironmentStringsTest1 )
{
    Environment::EnvironmentStrings environmentStrings;
    auto data = environmentStrings.data( );
    BOOST_CHECK( data != nullptr );
}

// --run_test=EnvironmentTests/EnvironmentStringsSizeTest1
BOOST_AUTO_TEST_CASE( EnvironmentStringsSizeTest1 )
{
    Environment::EnvironmentStrings environmentStrings;
    auto size = environmentStrings.size( );
    BOOST_CHECK( size > 0 );
}

// --run_test=EnvironmentTests/EnvironmentStringsAtTest1
BOOST_AUTO_TEST_CASE( EnvironmentStringsAtTest1 )
{
    Environment::EnvironmentStrings environmentStrings;
    auto size = environmentStrings.size( );
    for ( size_t i = 0; i < size; ++i )
    {
        auto entry = environmentStrings.at( i );
        BOOST_CHECK( entry != nullptr );
    }
}

// --run_test=EnvironmentTests/IsServiceTest1
BOOST_AUTO_TEST_CASE( IsServiceTest1 )
{
    auto value = Environment::IsService( );
    BOOST_CHECK( value == false );
}

// --run_test=EnvironmentTests/ProcessEntriesTest1
BOOST_AUTO_TEST_CASE( ProcessEntriesTest1 )
{
    Environment::ProcessEntries processEntries;
    auto value = processEntries.size();
    BOOST_CHECK( value > 0 );
}

// --run_test=EnvironmentTests/WhereTest1
BOOST_AUTO_TEST_CASE( WhereTest1 )
{
    auto result = Environment::Where(L"cmd.exe");
    
    BOOST_CHECK( result.size() > 0 );
}

// --run_test=EnvironmentTests/WhereTest2
BOOST_AUTO_TEST_CASE( WhereTest2 )
{
    auto result = Environment::Where( L"cmd654987321.exe" );

    BOOST_CHECK( result.size( ) == 0 );
}

// --run_test=EnvironmentTests/WhereTest3
BOOST_AUTO_TEST_CASE( WhereTest3 )
{
    auto path = Environment::EnvironmentVariable( L"path" );
    auto result = Environment::Where( path, L"cmd.exe" );

    BOOST_CHECK( result.size( ) > 0 );
}

// --run_test=EnvironmentTests/WhereTest4
BOOST_AUTO_TEST_CASE( WhereTest4 )
{
    auto path = Environment::EnvironmentVariable( L"path" );
    auto result = Environment::Where( path, L"cmd654987321.exe" );

    BOOST_CHECK( result.size( ) == 0 );
}

// --run_test=EnvironmentTests/WhereTest5
BOOST_AUTO_TEST_CASE( WhereTest5 )
{
    auto result = Environment::Where( "cmd.exe" );

    BOOST_CHECK( result.size( ) > 0 );
}

// --run_test=EnvironmentTests/WhereTest6
BOOST_AUTO_TEST_CASE( WhereTest6 )
{
    auto result = Environment::Where( "cmd654987321.exe" );

    BOOST_CHECK( result.size( ) == 0 );
}

// --run_test=EnvironmentTests/WhereTest7
BOOST_AUTO_TEST_CASE( WhereTest7 )
{
    auto path = Environment::EnvironmentVariable( "path" );
    auto result = Environment::Where( path, "cmd.exe" );

    BOOST_CHECK( result.size( ) > 0 );
}

// --run_test=EnvironmentTests/WhereTest8
BOOST_AUTO_TEST_CASE( WhereTest8 )
{
    auto path = Environment::EnvironmentVariable( "path" );
    auto result = Environment::Where( path, "cmd654987321.exe" );

    BOOST_CHECK( result.size( ) == 0 );
}

// --run_test=EnvironmentTests/GetDomainOrWorkgroupNameTest
BOOST_AUTO_TEST_CASE( GetDomainOrWorkgroupNameTest )
{
    auto domainOrComputerName = Environment::Computer::GetDomainOrWorkgroupName( );
    BOOST_CHECK( domainOrComputerName.size( ) > 0 );
}

// --run_test=EnvironmentTests/UsersTest
BOOST_AUTO_TEST_CASE( UsersTest )
{
    Environment::Users users;
    BOOST_CHECK( users.size( ) > 0 );
}

// --run_test=EnvironmentTests/IsComputerDomainJoinedTest
BOOST_AUTO_TEST_CASE( IsComputerDomainJoinedTest )
{
    BOOST_CHECK_NO_THROW( Environment::IsComputerDomainJoined( ) );
}

// --run_test=EnvironmentTests/GroupsTest
BOOST_AUTO_TEST_CASE( GroupsTest )
{
    Environment::Groups groups;
    BOOST_CHECK( groups.size( ) > 0 );
}







BOOST_AUTO_TEST_SUITE_END( )