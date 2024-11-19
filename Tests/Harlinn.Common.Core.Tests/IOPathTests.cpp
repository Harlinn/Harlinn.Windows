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
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest2
BOOST_AUTO_TEST_CASE( CombineTest2 )
{
    std::string_view str1( "c:" );
    std::string_view str2( "folder" );
    auto result = IO::Path::Combine<AnsiString>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest3
BOOST_AUTO_TEST_CASE( CombineTest3 )
{
    std::string str1( "c:" );
    std::string_view str2( "folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest4
BOOST_AUTO_TEST_CASE( CombineTest4 )
{
    const char* str1 = "c:";
    std::string_view str2( "folder" );
    auto result = IO::Path::Combine<AnsiString>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest5
BOOST_AUTO_TEST_CASE( CombineTest5 )
{
    std::string_view str1( "c:" );
    const char* str2 = "folder";
    auto result = IO::Path::Combine<AnsiString>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest6
BOOST_AUTO_TEST_CASE( CombineTest6 )
{
    std::string str1( "c:" );
    const char* str2 = "folder";
    auto result = IO::Path::Combine<std::string,char,AnsiString>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest7
BOOST_AUTO_TEST_CASE( CombineTest7 )
{
    std::vector<char> str1( { 'c',':' } );
    boost::container::small_vector<char,12> str2( { 'f','o','l','d','e','r' } );
    auto result = IO::Path::Combine<AnsiString>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest8
BOOST_AUTO_TEST_CASE( CombineTest8 )
{
    const char* str1 = "c:";
    std::string str2( "folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest9
BOOST_AUTO_TEST_CASE( CombineTest9 )
{
    std::string str1 = "c:";
    const char* str2( "folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest10
BOOST_AUTO_TEST_CASE( CombineTest10 )
{
    const char* str1 = "c:";
    const char* str2( "folder" );
    auto result = IO::Path::Combine<std::string>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest11
BOOST_AUTO_TEST_CASE( CombineTest11 )
{
    std::wstring str1( L"c:" );
    std::wstring str2( L"folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest12
BOOST_AUTO_TEST_CASE( CombineTest12 )
{
    std::wstring_view str1( L"c:" );
    std::wstring_view str2( L"folder" );
    auto result = IO::Path::Combine<WideString>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest13
BOOST_AUTO_TEST_CASE( CombineTest13 )
{
    std::wstring str1( L"c:" );
    std::wstring_view str2( L"folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest14
BOOST_AUTO_TEST_CASE( CombineTest14 )
{
    const wchar_t* str1 = L"c:";
    std::wstring_view str2( L"folder" );
    auto result = IO::Path::Combine<WideString>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest15
BOOST_AUTO_TEST_CASE( CombineTest15 )
{
    std::wstring_view str1( L"c:" );
    const wchar_t* str2 = L"folder";
    auto result = IO::Path::Combine<WideString>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest16
BOOST_AUTO_TEST_CASE( CombineTest16 )
{
    std::wstring str1( L"c:" );
    const wchar_t* str2 = L"folder";
    auto result = IO::Path::Combine<std::wstring, wchar_t,WideString>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest17
BOOST_AUTO_TEST_CASE( CombineTest17 )
{
    std::vector<wchar_t> str1( { 'c',':' } );
    boost::container::small_vector<wchar_t, 12> str2( { 'f','o','l','d','e','r' } );
    auto result = IO::Path::Combine<WideString>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest18
BOOST_AUTO_TEST_CASE( CombineTest18 )
{
    const wchar_t* str1 = L"c:";
    std::wstring str2( L"folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest19
BOOST_AUTO_TEST_CASE( CombineTest19 )
{
    std::wstring str1 = L"c:";
    const wchar_t* str2( L"folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest20
BOOST_AUTO_TEST_CASE( CombineTest20 )
{
    const wchar_t* str1 = L"c:";
    const wchar_t* str2( L"folder" );
    auto result = IO::Path::Combine<std::wstring>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest21
BOOST_AUTO_TEST_CASE( CombineTest21 )
{
    AnsiString str1( "c:" );
    AnsiString str2( "folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest22
BOOST_AUTO_TEST_CASE( CombineTest22 )
{
    AnsiStringView str1( "c:" );
    AnsiStringView str2( "folder" );
    auto result = IO::Path::Combine<std::string> ( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest23
BOOST_AUTO_TEST_CASE( CombineTest23 )
{
    AnsiString str1( "c:" );
    AnsiStringView str2( "folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest24
BOOST_AUTO_TEST_CASE( CombineTest24 )
{
    const char* str1 = "c:";
    AnsiStringView str2( "folder" );
    auto result = IO::Path::Combine<std::string>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest25
BOOST_AUTO_TEST_CASE( CombineTest25 )
{
    AnsiStringView str1( "c:" );
    const char* str2 = "folder";
    auto result = IO::Path::Combine<std::string>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest26
BOOST_AUTO_TEST_CASE( CombineTest26 )
{
    AnsiString str1( "c:" );
    const char* str2 = "folder";
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest27
BOOST_AUTO_TEST_CASE( CombineTest27 )
{
    std::vector<char> str1( { 'c',':' } );
    boost::container::small_vector<char, 12> str2( { 'f','o','l','d','e','r' } );
    auto result = IO::Path::Combine<AnsiString>( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest28
BOOST_AUTO_TEST_CASE( CombineTest28 )
{
    const char* str1 = "c:";
    AnsiString str2( "folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest29
BOOST_AUTO_TEST_CASE( CombineTest29 )
{
    AnsiString str1( "c:" );
    const char* str2( "folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == "c:\\folder";
    BOOST_CHECK( check );
}


// --run_test=IOPathTests/CombineTest30
BOOST_AUTO_TEST_CASE( CombineTest30 )
{
    WideString str1( L"c:" );
    WideString str2( L"folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest31
BOOST_AUTO_TEST_CASE( CombineTest31 )
{
    WideStringView str1( L"c:" );
    WideStringView str2( L"folder" );
    auto result = IO::Path::Combine<std::wstring>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest32
BOOST_AUTO_TEST_CASE( CombineTest32 )
{
    WideString str1( L"c:" );
    WideStringView str2( L"folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest33
BOOST_AUTO_TEST_CASE( CombineTest33 )
{
    const wchar_t* str1 = L"c:";
    WideStringView str2( L"folder" );
    auto result = IO::Path::Combine<std::wstring>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest34
BOOST_AUTO_TEST_CASE( CombineTest34 )
{
    WideStringView str1( L"c:" );
    const wchar_t* str2 = L"folder";
    auto result = IO::Path::Combine<std::wstring>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest35
BOOST_AUTO_TEST_CASE( CombineTest35 )
{
    WideString str1( L"c:" );
    const wchar_t* str2 = L"folder";
    auto result = IO::Path::Combine<WideString, wchar_t, std::wstring>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest36
BOOST_AUTO_TEST_CASE( CombineTest36 )
{
    std::vector<wchar_t> str1( { 'c',':' } );
    boost::container::small_vector<wchar_t, 12> str2( { 'f','o','l','d','e','r' } );
    auto result = IO::Path::Combine<std::wstring>( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest37
BOOST_AUTO_TEST_CASE( CombineTest37 )
{
    const wchar_t* str1 = L"c:";
    WideString str2( L"folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/CombineTest38
BOOST_AUTO_TEST_CASE( CombineTest38 )
{
    WideString str1( L"c:" );
    const wchar_t* str2( L"folder" );
    auto result = IO::Path::Combine( str1, str2 );
    bool check = result == L"c:\\folder";
    BOOST_CHECK( check );
}



// --run_test=IOPathTests/ChangeExtensionTest1
BOOST_AUTO_TEST_CASE( ChangeExtensionTest1 )
{
    std::string_view path( "c:\\folder\\file.txt" );
    std::string_view newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension<std::string>( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest2
BOOST_AUTO_TEST_CASE( ChangeExtensionTest2 )
{
    std::string path( "c:\\folder\\file.txt" );
    std::string_view newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest3
BOOST_AUTO_TEST_CASE( ChangeExtensionTest3 )
{
    std::string_view path( "c:\\folder\\file.txt" );
    std::string newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest4
BOOST_AUTO_TEST_CASE( ChangeExtensionTest4 )
{
    std::string path( "c:\\folder\\file.txt" );
    std::string newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest5
BOOST_AUTO_TEST_CASE( ChangeExtensionTest5 )
{
    std::string path( "c:\\folder\\file.txt" );
    const char* newExtension = ".cpp";
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest6
BOOST_AUTO_TEST_CASE( ChangeExtensionTest6 )
{
    const char* path = "c:\\folder\\file.txt";
    std::string newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest7
BOOST_AUTO_TEST_CASE( ChangeExtensionTest7 )
{
    std::string_view path( "c:\\folder\\file.txt" );
    const char* newExtension = ".cpp";
    auto result = IO::Path::ChangeExtension<std::string>( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest8
BOOST_AUTO_TEST_CASE( ChangeExtensionTest8 )
{
    const char* path = "c:\\folder\\file.txt";
    std::string_view newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension<std::string>( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest9
BOOST_AUTO_TEST_CASE( ChangeExtensionTest9 )
{
    const char* path = "c:\\folder\\file.txt";
    const char* newExtension = ".cpp";
    auto result = IO::Path::ChangeExtension<std::string>( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest10
BOOST_AUTO_TEST_CASE( ChangeExtensionTest10 )
{
    std::wstring_view path( L"c:\\folder\\file.txt" );
    std::wstring_view newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension<std::wstring>( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest11
BOOST_AUTO_TEST_CASE( ChangeExtensionTest11 )
{
    std::wstring path( L"c:\\folder\\file.txt" );
    std::wstring_view newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest12
BOOST_AUTO_TEST_CASE( ChangeExtensionTest12 )
{
    std::wstring_view path( L"c:\\folder\\file.txt" );
    std::wstring newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest13
BOOST_AUTO_TEST_CASE( ChangeExtensionTest13 )
{
    std::wstring path( L"c:\\folder\\file.txt" );
    std::wstring newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest14
BOOST_AUTO_TEST_CASE( ChangeExtensionTest14 )
{
    std::wstring path( L"c:\\folder\\file.txt" );
    const wchar_t* newExtension = L".cpp";
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest15
BOOST_AUTO_TEST_CASE( ChangeExtensionTest15 )
{
    const wchar_t* path = L"c:\\folder\\file.txt";
    std::wstring newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest16
BOOST_AUTO_TEST_CASE( ChangeExtensionTest16 )
{
    std::wstring_view path( L"c:\\folder\\file.txt" );
    const wchar_t* newExtension = L".cpp";
    auto result = IO::Path::ChangeExtension<std::wstring>( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest17
BOOST_AUTO_TEST_CASE( ChangeExtensionTest17 )
{
    const wchar_t* path = L"c:\\folder\\file.txt";
    std::wstring_view newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension<std::wstring>( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest18
BOOST_AUTO_TEST_CASE( ChangeExtensionTest18 )
{
    const wchar_t* path = L"c:\\folder\\file.txt";
    const wchar_t* newExtension = L".cpp";
    auto result = IO::Path::ChangeExtension<std::wstring>( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest19
BOOST_AUTO_TEST_CASE( ChangeExtensionTest19 )
{
    AnsiStringView path( "c:\\folder\\file.txt" );
    AnsiStringView newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension<AnsiString>( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest20
BOOST_AUTO_TEST_CASE( ChangeExtensionTest20 )
{
    AnsiString path( "c:\\folder\\file.txt" );
    AnsiStringView newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest21
BOOST_AUTO_TEST_CASE( ChangeExtensionTest21 )
{
    AnsiStringView path( "c:\\folder\\file.txt" );
    AnsiString newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest22
BOOST_AUTO_TEST_CASE( ChangeExtensionTest22 )
{
    AnsiString path( "c:\\folder\\file.txt" );
    AnsiString newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest23
BOOST_AUTO_TEST_CASE( ChangeExtensionTest23 )
{
    AnsiString path( "c:\\folder\\file.txt" );
    const char* newExtension = ".cpp";
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest24
BOOST_AUTO_TEST_CASE( ChangeExtensionTest24 )
{
    const char* path = "c:\\folder\\file.txt";
    AnsiString newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest25
BOOST_AUTO_TEST_CASE( ChangeExtensionTest25 )
{
    AnsiStringView path( "c:\\folder\\file.txt" );
    const char* newExtension = ".cpp";
    auto result = IO::Path::ChangeExtension<AnsiString>( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest26
BOOST_AUTO_TEST_CASE( ChangeExtensionTest26 )
{
    const char* path = "c:\\folder\\file.txt";
    AnsiStringView newExtension( ".cpp" );
    auto result = IO::Path::ChangeExtension<AnsiString>( path, newExtension );
    bool check = result == "c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest27
BOOST_AUTO_TEST_CASE( ChangeExtensionTest27 )
{
    WideStringView path( L"c:\\folder\\file.txt" );
    WideStringView newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension<WideString>( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest28
BOOST_AUTO_TEST_CASE( ChangeExtensionTest28 )
{
    WideString path( L"c:\\folder\\file.txt" );
    WideStringView newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest29
BOOST_AUTO_TEST_CASE( ChangeExtensionTest29 )
{
    WideStringView path( L"c:\\folder\\file.txt" );
    WideString newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest30
BOOST_AUTO_TEST_CASE( ChangeExtensionTest30 )
{
    WideString path( L"c:\\folder\\file.txt" );
    WideString newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest31
BOOST_AUTO_TEST_CASE( ChangeExtensionTest31 )
{
    WideString path( L"c:\\folder\\file.txt" );
    const wchar_t* newExtension = L".cpp";
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest32
BOOST_AUTO_TEST_CASE( ChangeExtensionTest32 )
{
    const wchar_t* path = L"c:\\folder\\file.txt";
    WideString newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest33
BOOST_AUTO_TEST_CASE( ChangeExtensionTest33 )
{
    WideStringView path( L"c:\\folder\\file.txt" );
    const wchar_t* newExtension = L".cpp";
    auto result = IO::Path::ChangeExtension<WideString>( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}

// --run_test=IOPathTests/ChangeExtensionTest34
BOOST_AUTO_TEST_CASE( ChangeExtensionTest34 )
{
    const wchar_t* path = L"c:\\folder\\file.txt";
    WideStringView newExtension( L".cpp" );
    auto result = IO::Path::ChangeExtension<WideString>( path, newExtension );
    bool check = result == L"c:\\folder\\file.cpp";
    BOOST_CHECK( check );
}




BOOST_AUTO_TEST_SUITE_END( )