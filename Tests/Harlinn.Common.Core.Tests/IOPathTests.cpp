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

BOOST_FIXTURE_TEST_SUITE( IOPathTests, LocalFixture )

// --run_test=IOPathTests/IsDirectorySeparatorTest1
BOOST_AUTO_TEST_CASE( IsDirectorySeparatorTest1 )
{
    char c1 = '/';
    auto check = IO::Path::IsDirectorySeparator( c1 );
    BOOST_CHECK( check );

    char c2 = '\\';
    check = IO::Path::IsDirectorySeparator( c2 );
    BOOST_CHECK( check );

    wchar_t c3 = L'/';
    check = IO::Path::IsDirectorySeparator( c3 );
    BOOST_CHECK( check );

    wchar_t c4 = L'\\';
    check = IO::Path::IsDirectorySeparator( c4 );
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/IsDirectorySeparatorTest2
BOOST_AUTO_TEST_CASE( IsDirectorySeparatorTest2 )
{
    std::string stdStr1( "/" );
    auto check = IO::Path::IsDirectorySeparator( stdStr1 );
    BOOST_CHECK( check );

    std::string stdStr2( "\\" );
    check = IO::Path::IsDirectorySeparator( stdStr2 );
    BOOST_CHECK( check );

    std::string stdStr3( "" );
    check = IO::Path::IsDirectorySeparator( stdStr3 ) == false;
    BOOST_CHECK( check );

    std::string stdStr4( "a" );
    check = IO::Path::IsDirectorySeparator( stdStr4 ) == false;
    BOOST_CHECK( check );

    
    WideString wStr1( L"/" );
    check = IO::Path::IsDirectorySeparator( wStr1 );
    BOOST_CHECK( check );
    std::span spn( wStr1 );


    WideString wStr2( L"\\" );
    check = IO::Path::IsDirectorySeparator( wStr2 );
    BOOST_CHECK( check );

    WideString wStr3( L"" );
    check = IO::Path::IsDirectorySeparator( wStr3 ) == false;
    BOOST_CHECK( check );

    WideString wStr4( L"a" );
    check = IO::Path::IsDirectorySeparator( wStr4 ) == false;
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/EnsurePathEndsWithDirectorySeparatorTest1
BOOST_AUTO_TEST_CASE( EnsurePathEndsWithDirectorySeparatorTest1 )
{
    std::string str1( "c:" );
    std::string_view sv1 = str1;
    auto result = IO::Path::EnsurePathEndsWithDirectorySeparator( str1 );
    bool check = result == "c:\\";
    BOOST_CHECK( check );
    result = IO::Path::EnsurePathEndsWithDirectorySeparator<std::string>( sv1 );
    check = result == "c:\\";
    BOOST_CHECK( check );

    str1 = "c:/";
    result = IO::Path::EnsurePathEndsWithDirectorySeparator( str1 );
    check = result == "c:/";
    BOOST_CHECK( check );

    str1 = "";
    result = IO::Path::EnsurePathEndsWithDirectorySeparator( str1 );
    check = result == "\\";
    BOOST_CHECK( check );

}

// --run_test=IOPathTests/RemoveTrailingDirectorySeparatorTest1
BOOST_AUTO_TEST_CASE( RemoveTrailingDirectorySeparatorTest1 )
{
    std::string str1( "c:\\" );
    std::string_view sv1 = str1;
    auto result = IO::Path::RemoveTrailingDirectorySeparator( str1 );
    bool check = result == "c:";
    BOOST_CHECK( check );
    result = IO::Path::RemoveTrailingDirectorySeparator<std::string>( sv1 );
    check = result == "c:";
    BOOST_CHECK( check );

    str1 = "c:/";
    result = IO::Path::RemoveTrailingDirectorySeparator( str1 );
    check = result == "c:";
    BOOST_CHECK( check );

    str1 = "\\";
    result = IO::Path::RemoveTrailingDirectorySeparator( str1 );
    check = result == "";
    BOOST_CHECK( check );

}

// --run_test=IOPathTests/CombineTest1
BOOST_AUTO_TEST_CASE( CombineTest1 )
{
    std::string str1( "c:" );
    std::string str2( "folder" );
    auto result = IO::Path::Combine<std::string>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

BOOST_AUTO_TEST_SUITE_END( )