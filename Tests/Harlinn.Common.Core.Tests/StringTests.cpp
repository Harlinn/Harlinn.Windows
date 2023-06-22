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
