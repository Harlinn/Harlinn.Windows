#include "pch.h"

using namespace Harlinn::Common::Core;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) { }
        ~LocalFixture( ) { }
    };
}

BOOST_FIXTURE_TEST_SUITE( StringTests, LocalFixture )

#ifdef HCC_WITH_BASIC_STRING


// --run_test=StringTests/ConstructorTest1W
BOOST_AUTO_TEST_CASE( ConstructorTest1W )
{
    WideString string;

    BOOST_TEST( string.empty() );
}

// --run_test=StringTests/ConstructorTest1A
BOOST_AUTO_TEST_CASE( ConstructorTest1A )
{
    AnsiString string;
    BOOST_TEST( string.empty( ) );
}

// --run_test=StringTests/ConstructorTest2W
BOOST_AUTO_TEST_CASE( ConstructorTest2W )
{
    WideString string( L"1" );
    bool equal = string == L"1";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest2A
BOOST_AUTO_TEST_CASE( ConstructorTest2A )
{
    AnsiString string( "1" );
    bool equal = string == "1";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest3W
BOOST_AUTO_TEST_CASE( ConstructorTest3W )
{
    WideString string( L"123", 2 );
    bool equal = string == L"12";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest3A
BOOST_AUTO_TEST_CASE( ConstructorTest3A )
{
    AnsiString string( "123", 2 );
    bool equal = string == "12";
    BOOST_TEST( equal );
}


// --run_test=StringTests/ConstructorTest4W
BOOST_AUTO_TEST_CASE( ConstructorTest4W )
{
    WideString string1( L"123" );
    WideString string2( string1.begin() + 1, string1.end() - 1 );
    bool equal = string2 == L"2";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest4A
BOOST_AUTO_TEST_CASE( ConstructorTest4A )
{
    AnsiString string1( "123" );
    AnsiString string2( string1.begin( ) + 1, string1.end( ) - 1 );
    bool equal = string2 == "2";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest5W
BOOST_AUTO_TEST_CASE( ConstructorTest5W )
{
    WideString string1( L"123" );
    WideString string2( string1.data( ) + 1, string1.data( ) + 2 );
    bool equal = string2 == L"2";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest5A
BOOST_AUTO_TEST_CASE( ConstructorTest5A )
{
    AnsiString string1( "123" );
    AnsiString string2( string1.data( ) + 1, string1.data( ) + 2 );
    bool equal = string2 == "2";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest6W
BOOST_AUTO_TEST_CASE( ConstructorTest6W )
{
    std::vector<wchar_t> string1{ '1','2', '3' };
    WideString string2( string1.begin( ) + 1, string1.end( ) - 1 );
    bool equal = string2 == L"2";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest6A
BOOST_AUTO_TEST_CASE( ConstructorTest6A )
{
    std::vector<char> string1{ '1', '2', '3' };
    AnsiString string2( string1.begin( ) + 1, string1.end( ) - 1 );
    bool equal = string2 == "2";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest7W
BOOST_AUTO_TEST_CASE( ConstructorTest7W )
{
    std::vector<wchar_t> vector{ '1', '2', '3' };
    WideStringView string1( vector.data(), vector.size() );
    WideString string2( string1 );
    bool equal = string2 == L"123";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest7A
BOOST_AUTO_TEST_CASE( ConstructorTest7A )
{
    std::vector<char> vector{ '1', '2', '3' };
    AnsiStringView string1( vector.data( ), vector.size( ) );
    AnsiString string2( string1 );
    bool equal = string2 == "123";
    BOOST_TEST( equal );
}


// --run_test=StringTests/ConstructorTest8W
BOOST_AUTO_TEST_CASE( ConstructorTest8W )
{
    WideString string1( 3, L'3' );
    bool equal = string1 == L"333";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest8A
BOOST_AUTO_TEST_CASE( ConstructorTest8A )
{
    AnsiString string1( 3, '3' );
    bool equal = string1 == "333";
    BOOST_TEST( equal );
}


// --run_test=StringTests/ConstructorTest9W
BOOST_AUTO_TEST_CASE( ConstructorTest9W )
{
    WideString string1( L"123" );
    WideString string2( string1 );
    bool equal = string2 == L"123";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest9A
BOOST_AUTO_TEST_CASE( ConstructorTest9A )
{
    AnsiString string1( "123" );
    AnsiString string2( string1 );
    bool equal = string2 == "123";
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest10W
BOOST_AUTO_TEST_CASE( ConstructorTest10W )
{
    WideString string1( L"123" );
    WideString string2( std::move(string1) );
    bool equal = string2 == L"123";
    BOOST_TEST( equal );
    BOOST_TEST( string1.empty() );
}

// --run_test=StringTests/ConstructorTest10A
BOOST_AUTO_TEST_CASE( ConstructorTest10A )
{
    AnsiString string1( "123" );
    AnsiString string2( std::move( string1 ) );
    bool equal = string2 == "123";
    BOOST_TEST( equal );
    BOOST_TEST( string1.empty( ) );
}

// --run_test=StringTests/StringIsUniqueTest1W
BOOST_AUTO_TEST_CASE( StringIsUniqueTest1W )
{
    WideString string1( L"123" );
    BOOST_TEST( string1.IsUnique() );
    WideString string2( string1 );
    BOOST_TEST( string1.IsUnique( ) == false );
    BOOST_TEST( string2.IsUnique( ) == false );
}

// --run_test=StringTests/StringIsUniqueTest1A
BOOST_AUTO_TEST_CASE( StringIsUniqueTest1A )
{
    AnsiString string1( "123" );
    BOOST_TEST( string1.IsUnique( ) );
    AnsiString string2( string1 );
    BOOST_TEST( string1.IsUnique( ) == false );
    BOOST_TEST( string2.IsUnique( ) == false );
}

// --run_test=StringTests/StringCloneTest1W
BOOST_AUTO_TEST_CASE( StringCloneTest1W )
{
    WideString string1( L"123" );
    BOOST_TEST( string1.IsUnique( ) );
    WideString string2( string1.Clone() );
    BOOST_TEST( string1.IsUnique( ) );
    BOOST_TEST( string2.IsUnique( ) );
}

// --run_test=StringTests/StringCloneTest1A
BOOST_AUTO_TEST_CASE( StringCloneTest1A )
{
    AnsiString string1( "123" );
    BOOST_TEST( string1.IsUnique( ) );
    AnsiString string2( string1.Clone( ) );
    BOOST_TEST( string1.IsUnique( ) );
    BOOST_TEST( string2.IsUnique( ) );
}

// --run_test=StringTests/StringEnsureUniqueTest1W
BOOST_AUTO_TEST_CASE( StringEnsureUniqueTest1W )
{
    WideString string1( L"123" );
    BOOST_TEST( string1.IsUnique( ) );
    WideString string2( string1 );
    BOOST_TEST( string1.IsUnique( ) == false );
    BOOST_TEST( string2.IsUnique( ) == false );
    string2.EnsureUnique( );
    BOOST_TEST( string1.IsUnique( ) );
    BOOST_TEST( string2.IsUnique( ) );
}

// --run_test=StringTests/StringEnsureUniqueTest1A
BOOST_AUTO_TEST_CASE( StringEnsureUniqueTest1A )
{
    AnsiString string1( "123" );
    BOOST_TEST( string1.IsUnique( ) );
    AnsiString string2( string1 );
    BOOST_TEST( string1.IsUnique( ) == false );
    BOOST_TEST( string2.IsUnique( ) == false );
    string2.EnsureUnique( );
    BOOST_TEST( string1.IsUnique( ) );
    BOOST_TEST( string2.IsUnique( ) );
}

// --run_test=StringTests/StringFromTest1W
BOOST_AUTO_TEST_CASE( StringFromTest1W )
{
    WideString from( L"123" );
    WideString to = WideString::From( from );
    bool equal = to == from;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest1A
BOOST_AUTO_TEST_CASE( StringFromTest1A )
{
    AnsiString from( "123" );
    AnsiString to = AnsiString::From( from );
    bool equal = to == from;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest2W
BOOST_AUTO_TEST_CASE( StringFromTest2W )
{
    std::wstring from( L"123" );
    WideString to = WideString::From( from );
    bool equal = to == from.c_str();
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest2A
BOOST_AUTO_TEST_CASE( StringFromTest2A )
{
    std::string from( "123" );
    AnsiString to = AnsiString::From( from );
    bool equal = to == from.c_str( );
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest3W
BOOST_AUTO_TEST_CASE( StringFromTest3W )
{
    WideString from( L"123" );
    WideString to = WideString::From( from.c_str() );
    bool equal = to == from;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest3W
BOOST_AUTO_TEST_CASE( StringFromTest3A )
{
    AnsiString from( "123" );
    AnsiString to = AnsiString::From( from.c_str( ) );
    bool equal = to == from;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest4W
BOOST_AUTO_TEST_CASE( StringFromTest4W )
{
    AnsiString from( "123" );
    WideString to = WideString::From( from );
    bool equal = to == ToWideString(from);
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest4A
BOOST_AUTO_TEST_CASE( StringFromTest4A )
{
    WideString from( L"123" );
    AnsiString to = AnsiString::From( from );
    bool equal = to == ToAnsiString( from );
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest5W
BOOST_AUTO_TEST_CASE( StringFromTest5W )
{
    AnsiString from( "123" );
    WideString to = WideString::From( from.c_str( ) );
    bool equal = to == ToWideString( from );
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest5A
BOOST_AUTO_TEST_CASE( StringFromTest5A )
{
    WideString from( L"123" );
    AnsiString to = AnsiString::From( from.c_str( ) );
    bool equal = to == ToAnsiString( from );
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest6W
BOOST_AUTO_TEST_CASE( StringFromTest6W )
{
    std::string from( "123" );
    WideString to = WideString::From( from );
    bool equal = to == ToWideString( from );
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest6A
BOOST_AUTO_TEST_CASE( StringFromTest6A )
{
    std::wstring from( L"123" );
    AnsiString to = AnsiString::From( from );
    bool equal = to == ToAnsiString( from );
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest7W
BOOST_AUTO_TEST_CASE( StringFromTest7W )
{
    std::string from( "123" );
    std::string_view from_view( from );
    WideString to = WideString::From( from_view );
    bool equal = to == ToWideString( from );
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringFromTest7A
BOOST_AUTO_TEST_CASE( StringFromTest7A )
{
    std::wstring from( L"123" );
    std::wstring_view from_view( from );
    AnsiString to = AnsiString::From( from_view );
    bool equal = to == ToAnsiString( from );
    BOOST_TEST( equal );
}






#endif


// --run_test=StringTests/FormatWStringTest
BOOST_AUTO_TEST_CASE( FormatWStringTest )
{
    const wchar_t* arg1 = L"Lorem ipsum dolor sit amet";
    const wchar_t* arg2 = L"consectetur adipiscing elit";
    double arg3 = 1.0;
    auto formatted = Format( L"{} {} {}", arg1, arg2, arg3 );
    BOOST_TEST( formatted.size( ) > 0 );
}

// --run_test=StringTests/FormatStringTest
BOOST_AUTO_TEST_CASE( FormatStringTest )
{
    const char* arg1 = "Lorem ipsum dolor sit amet";
    const char* arg2 = "consectetur adipiscing elit";
    double arg3 = 1.0;
    auto formatted = Format( "{} {} {}", arg1, arg2, arg3 );
    BOOST_TEST( formatted.size( ) > 0 );
}

// --run_test=StringTests/TrimTrailingTest1a
BOOST_AUTO_TEST_CASE( TrimTrailingTest1a )
{
    WideString str1 = L" a ";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L" a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest1b
BOOST_AUTO_TEST_CASE( TrimTrailingTest1b )
{
    AnsiString str1 = " a ";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == " a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest1c
BOOST_AUTO_TEST_CASE( TrimTrailingTest1c )
{
    std::wstring_view str1 = L" a ";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L" a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest1d
BOOST_AUTO_TEST_CASE( TrimTrailingTest1d )
{
    std::string_view str1 = " a ";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == " a";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/TrimTrailingTest2a
BOOST_AUTO_TEST_CASE( TrimTrailingTest2a )
{
    WideString str1 = L" ";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest2b
BOOST_AUTO_TEST_CASE( TrimTrailingTest2b )
{
    AnsiString str1 = " ";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest2c
BOOST_AUTO_TEST_CASE( TrimTrailingTest2c )
{
    std::wstring_view str1 = L" ";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest2d
BOOST_AUTO_TEST_CASE( TrimTrailingTest2d )
{
    std::string_view str1 = " ";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest3a
BOOST_AUTO_TEST_CASE( TrimTrailingTest3a )
{
    WideString str1 = L"";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest3b
BOOST_AUTO_TEST_CASE( TrimTrailingTest3b )
{
    AnsiString str1 = "";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest3c
BOOST_AUTO_TEST_CASE( TrimTrailingTest3c )
{
    std::wstring_view str1 = L"";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest3d
BOOST_AUTO_TEST_CASE( TrimTrailingTest3d )
{
    std::string_view str1 = "";
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}



// --run_test=StringTests/TrimLeadingTest1a
BOOST_AUTO_TEST_CASE( TrimLeadingTest1a )
{
    WideString str1 = L" a ";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"a ";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest1b
BOOST_AUTO_TEST_CASE( TrimLeadingTest1b )
{
    AnsiString str1 = " a ";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "a ";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest1c
BOOST_AUTO_TEST_CASE( TrimLeadingTest1c )
{
    std::wstring_view str1 = L" a ";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"a ";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest1d
BOOST_AUTO_TEST_CASE( TrimLeadingTest1d )
{
    std::string_view str1 = " a ";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "a ";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest2a
BOOST_AUTO_TEST_CASE( TrimLeadingTest2a )
{
    WideString str1 = L" ";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest2b
BOOST_AUTO_TEST_CASE( TrimLeadingTest2b )
{
    AnsiString str1 = " ";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest2c
BOOST_AUTO_TEST_CASE( TrimLeadingTest2c )
{
    std::wstring_view str1 = L" ";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest2d
BOOST_AUTO_TEST_CASE( TrimLeadingTest2d )
{
    std::string_view str1 = " ";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/TrimLeadingTest3a
BOOST_AUTO_TEST_CASE( TrimLeadingTest3a )
{
    WideString str1 = L"";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest3b
BOOST_AUTO_TEST_CASE( TrimLeadingTest3b )
{
    AnsiString str1 = "";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest3c
BOOST_AUTO_TEST_CASE( TrimLeadingTest3c )
{
    std::wstring_view str1 = L"";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/TrimLeadingTest3d
BOOST_AUTO_TEST_CASE( TrimLeadingTest3d )
{
    std::string_view str1 = "";
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/TrimTest1a
BOOST_AUTO_TEST_CASE( TrimTest1a )
{
    WideString str1 = L" a ";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest1b
BOOST_AUTO_TEST_CASE( TrimTest1b )
{
    AnsiString str1 = " a ";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest1c
BOOST_AUTO_TEST_CASE( TrimTest1c )
{
    std::wstring_view str1 = L" a ";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest1d
BOOST_AUTO_TEST_CASE( TrimTest1d )
{
    std::string_view str1 = " a ";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest2a
BOOST_AUTO_TEST_CASE( TrimTest2a )
{
    WideString str1 = L" ";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest2b
BOOST_AUTO_TEST_CASE( TrimTest2b )
{
    AnsiString str1 = " ";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest2c
BOOST_AUTO_TEST_CASE( TrimTest2c )
{
    std::wstring_view str1 = L" ";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest2d
BOOST_AUTO_TEST_CASE( TrimTest2d )
{
    std::string_view str1 = " ";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest3a
BOOST_AUTO_TEST_CASE( TrimTest3a )
{
    WideString str1 = L"";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest3b
BOOST_AUTO_TEST_CASE( TrimTest3b )
{
    AnsiString str1 = "";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest3c
BOOST_AUTO_TEST_CASE( TrimTest3c )
{
    std::wstring_view str1 = L"";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest3d
BOOST_AUTO_TEST_CASE( TrimTest3d )
{
    std::string_view str1 = "";
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/ToAnsiStringTest001d
BOOST_AUTO_TEST_CASE( ToAnsiStringTest001d )
{
    float value = 1.0f;
    std::locale locale;
    auto str = ToAnsiString( value, 6,2, locale );
    bool areEqual = str == "001.00";
    BOOST_TEST( areEqual );
}



BOOST_AUTO_TEST_SUITE_END( )
