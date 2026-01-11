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
        LocalFixture( ) { }
        ~LocalFixture( ) { }
    };

    // Helper to verify null termination at [size] for AnsiString / WideString
    template<typename TString>
    void VerifyNullTerminated( const TString& s )
    {
        // When size is zero, c_str must still be valid and point to an empty string.
        // Verify terminator at size().
        const auto* p = s.c_str( );
        // Guard against null
        BOOST_REQUIRE( p != nullptr );
        // Verify terminator
        BOOST_TEST( p[ s.size( ) ] == static_cast<typename TString::value_type>( 0 ) );
    }
}

BOOST_FIXTURE_TEST_SUITE( StringTests, LocalFixture )



// --run_test=StringTests/BufferHeaderSizeTest1
BOOST_AUTO_TEST_CASE( BufferHeaderSizeTest1 )
{
    constexpr size_t WideStringBufferHeaderSize = WideString::BufferHeaderSize;
    constexpr size_t AnsiStringBufferHeaderSize = AnsiString::BufferHeaderSize;
    bool equal = WideStringBufferHeaderSize == AnsiStringBufferHeaderSize;
    BOOST_TEST( equal );

}

BOOST_AUTO_TEST_CASE( Ctor_FromStdString )
{
    const std::string src = "hello world"; 
    BasicString<char> s( src ); 
    BOOST_CHECK_EQUAL( s.size( ), src.size( ) ); 
    BOOST_CHECK_EQUAL( std::string( s.c_str( ), s.size( ) ), src ); 
    BOOST_CHECK( s.IsUnique( ) ); 
    BOOST_CHECK( s.StartsWith( 'h' ) ); 
    BOOST_CHECK( s.EndsWith( 'd' ) ); 
    BOOST_CHECK( s == src ); 
    BOOST_CHECK_EQUAL( BasicString<char>::Compare( s, src.c_str( ) ), 0 );
}

BOOST_AUTO_TEST_CASE( Ctor_FromStdVectorChar )
{
    std::vector<char> buf{ 'A','B','C','D' }; 
    BasicString<char> s( buf ); 
    BOOST_CHECK_EQUAL( s.size( ), buf.size( ) ); 
    BOOST_CHECK_EQUAL( std::string( s.c_str( ), s.size( ) ), std::string( buf.data( ), buf.size( ) ) ); 
    // Modify original buffer; BasicString should remain unchanged 
    buf[0] = 'Z'; 
    BOOST_CHECK_EQUAL(std::string(s.c_str(), s.size()), "ABCD"); 
    BOOST_CHECK(s.EndsWith('D')); 
    BOOST_CHECK(s.StartsWith('A')); 
}
BOOST_AUTO_TEST_CASE( Ctor_FromStdSpanConstChar )
{
    const char raw[ ] = "span-based"; 
    std::span<const char> sp( raw, 10 ); // "span-based" length 10 excluding terminator 
    BasicString<char> s(sp); 
    BOOST_CHECK_EQUAL(s.size(), sp.size()); 
    BOOST_CHECK_EQUAL(std::string(s.c_str(), s.size()), std::string(sp.data(), sp.size())); 
    BOOST_CHECK_EQUAL(s.IndexOf('b'), 5); BOOST_CHECK(s.IStartsWith("SPAN")); // case-insensitive start 
    BOOST_CHECK(s.IEndsWith("BASED"));  // case-insensitive end 
}

BOOST_AUTO_TEST_CASE( Ctor_FromStdSpanChar_EmbeddedNull )
{ 
    // Buffer with embedded null; span provides explicit length 
    std::vector<char> buf{'a','\0','b','c'}; 
    std::span<char> sp(buf.data(), buf.size()); 
    BasicString<char> s(sp); 
    BOOST_CHECK_EQUAL(s.size(), 4u); // Construct stdstring with explicit size to include embedded null 
    std::string as(s.data(), s.size()); 
    BOOST_CHECK_EQUAL(as.size(), 4u); 
    BOOST_CHECK(as[0] == 'a' && as[1] == '\0' && as[2] == 'b' && as[3] == 'c'); // Verify comparisons with string_view of explicit length 
    std::string_view sv(buf.data(), buf.size()); 
    BOOST_CHECK(s == sv); 
}
BOOST_AUTO_TEST_CASE( Ctor_FromEmptyContainers )
{
    const std::string emptyStr; 
    BasicString<char> s1( emptyStr ); 
    BOOST_CHECK_EQUAL( s1.size( ), 0u ); 
    BOOST_CHECK( s1.empty( ) ); 
    BOOST_CHECK( s1.c_str( ) != nullptr );
    std::vector<char> emptyVec;
    BasicString<char> s2( emptyVec );
    BOOST_CHECK_EQUAL( s2.size( ), 0u );
    BOOST_CHECK( s2.empty( ) );
}
            
BOOST_AUTO_TEST_CASE( Ctor_FromStdWString )
{
    const std::wstring src = L"wide hello"; 
    BasicString<wchar_t> s( src ); 
    BOOST_CHECK_EQUAL( s.size( ), src.size( ) ); 
    BOOST_CHECK( std::wstring( s.c_str( ), s.size( ) ) == src ); 
    BOOST_CHECK( s.IsUnique( ) ); 
    BOOST_CHECK( s.StartsWith( L'w' ) ); 
    BOOST_CHECK( s.EndsWith( L'o' ) ); 
    BOOST_CHECK( s == src ); 
    BOOST_CHECK_EQUAL( BasicString<wchar_t>::Compare( s, src.c_str( ) ), 0 );
}

BOOST_AUTO_TEST_CASE( Ctor_FromStdVectorWChar )
{
    std::vector<wchar_t> buf{ L'X',L'Y',L'Z' }; 
    BasicString<wchar_t> s( buf ); 
    BOOST_CHECK_EQUAL( s.size( ), buf.size( ) ); 
    BOOST_CHECK( std::wstring( s.c_str( ), s.size( ) ) == std::wstring( buf.data( ), buf.size( ) ) ); // Modify original vector and ensure string content stable buf[1] = L'Q'; 
    BOOST_CHECK(std::wstring(s.c_str(), s.size()) == L"XYZ"); 
    BOOST_CHECK(s.EndsWith(L'Z')); 
    BOOST_CHECK(s.StartsWith(L'X')); 
}
BOOST_AUTO_TEST_CASE( Ctor_FromStdSpanConstWChar )
{
    const wchar_t raw[ ] = L"SpanWide"; 
    std::span<const wchar_t> sp( raw, 8 ); // explicit length without relying on terminator 
    BasicString<wchar_t> s(sp); 
    BOOST_CHECK_EQUAL(s.size(), sp.size()); 
    BOOST_CHECK(std::wstring(s.c_str(), s.size()) == std::wstring(sp.data(), sp.size())); 
    BOOST_CHECK_EQUAL(s.IndexOf(L'W'), 4u); 
    BOOST_CHECK(s.IStartsWith(L"SPAN")); // case-insensitive start 
    BOOST_CHECK(s.IEndsWith(L"WIDE"));   // case-insensitive end 
}

BOOST_AUTO_TEST_CASE( Ctor_FromEmptyWideContainers )
{
    const std::wstring emptyWStr; 
    BasicString<wchar_t> s1( emptyWStr ); 
    BOOST_CHECK_EQUAL( s1.size( ), 0u ); 
    BOOST_CHECK( s1.empty( ) );
    std::vector<wchar_t> emptyVec;
    BasicString<wchar_t> s2( emptyVec );
    BOOST_CHECK_EQUAL( s2.size( ), 0u );
    BOOST_CHECK( s2.empty( ) );
}


// Verifies concatenation of two non-empty buffers for AnsiString.
BOOST_AUTO_TEST_CASE( Concatenate_Two_Ansi_Buffers )
{
    // Arrange
    const char* s1 = "Hello";
    const char* s2 = "World";
    const size_t n1 = 5;
    const size_t n2 = 5;

    // Act
    AnsiString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == n1 + n2 );
    BOOST_TEST( result == "HelloWorld" );
    VerifyNullTerminated( result );
}

// Verifies concatenation of two non-empty buffers for WideString.
BOOST_AUTO_TEST_CASE( Concatenate_Two_Wide_Buffers )
{
    // Arrange
    const wchar_t* s1 = L"Hello";
    const wchar_t* s2 = L"Wide";
    const size_t n1 = 5;
    const size_t n2 = 4;

    // Act
    WideString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == n1 + n2 );
	auto equal = result == L"HelloWide";
    BOOST_TEST( equal );
    VerifyNullTerminated( result );
}

// Verifies concatenation when the first part is empty (n1 == 0) for AnsiString.
BOOST_AUTO_TEST_CASE( Concatenate_FirstEmpty_Ansi )
{
    // Arrange
    const char* s1 = nullptr;
    const char* s2 = "Tail";
    const size_t n1 = 0;
    const size_t n2 = 4;

    // Act
    AnsiString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == n2 );
    BOOST_TEST( result == "Tail" );
    VerifyNullTerminated( result );
}

// Verifies concatenation when the second part is empty (n2 == 0) for AnsiString.
BOOST_AUTO_TEST_CASE( Concatenate_SecondEmpty_Ansi )
{
    // Arrange
    const char* s1 = "Head";
    const char* s2 = nullptr;
    const size_t n1 = 4;
    const size_t n2 = 0;

    // Act
    AnsiString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == n1 );
    BOOST_TEST( result == "Head" );
    VerifyNullTerminated( result );
}

// Verifies concatenation when both parts are empty for AnsiString.
BOOST_AUTO_TEST_CASE( Concatenate_BothEmpty_Ansi )
{
    // Arrange
    const char* s1 = nullptr;
    const char* s2 = nullptr;
    const size_t n1 = 0;
    const size_t n2 = 0;

    // Act
    AnsiString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == 0u );
    BOOST_TEST( result.empty( ) );
    VerifyNullTerminated( result );
}

// Verifies concatenation when the first part is empty (n1 == 0) for WideString.
BOOST_AUTO_TEST_CASE( Concatenate_FirstEmpty_Wide )
{
    // Arrange
    const wchar_t* s1 = nullptr;
    const wchar_t* s2 = L"Tail";
    const size_t n1 = 0;
    const size_t n2 = 4;

    // Act
    WideString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == n2 );
	auto equal = result == L"Tail";
    BOOST_TEST( equal );
    VerifyNullTerminated( result );
}

// Verifies concatenation when the second part is empty (n2 == 0) for WideString.
BOOST_AUTO_TEST_CASE( Concatenate_SecondEmpty_Wide )
{
    // Arrange
    const wchar_t* s1 = L"Head";
    const wchar_t* s2 = nullptr;
    const size_t n1 = 4;
    const size_t n2 = 0;

    // Act
    WideString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == n1 );
	auto equal = result == L"Head";
    BOOST_TEST( equal );
    VerifyNullTerminated( result );
}

// Verifies concatenation when both parts are empty for WideString.
BOOST_AUTO_TEST_CASE( Concatenate_BothEmpty_Wide )
{
    // Arrange
    const wchar_t* s1 = nullptr;
    const wchar_t* s2 = nullptr;
    const size_t n1 = 0;
    const size_t n2 = 0;

    // Act
    WideString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == 0u );
    BOOST_TEST( result.empty( ) );
    VerifyNullTerminated( result );
}

// Verifies that partial buffer lengths are respected (substring concatenation) for AnsiString.
BOOST_AUTO_TEST_CASE( Concatenate_PartialLengths_Ansi )
{
    // Arrange
    const char* s1 = "Hello..";
    const char* s2 = "World!!";
    const size_t n1 = 5;  // "Hello"
    const size_t n2 = 5;  // "World"

    // Act
    AnsiString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == n1 + n2 );
    BOOST_TEST( result == "HelloWorld" );
    VerifyNullTerminated( result );
}

// Verifies that partial buffer lengths are respected (substring concatenation) for WideString.
BOOST_AUTO_TEST_CASE( Concatenate_PartialLengths_Wide )
{
    // Arrange
    const wchar_t* s1 = L"Data123";
    const wchar_t* s2 = L"XYZ789";
    const size_t n1 = 4;  // L"Data"
    const size_t n2 = 3;  // L"XYZ"

    // Act
    WideString result( s1, n1, s2, n2 );

    // Assert
    BOOST_TEST( result.size( ) == n1 + n2 );
	auto equal = result == L"DataXYZ";
    BOOST_TEST( equal );
    VerifyNullTerminated( result );
}

// Ansi: repeat + tail -> concatenation 
BOOST_AUTO_TEST_CASE(Ansi_RepeatAndTail_Concatenates) 
{ 
    // Arrange 
    BasicString<char> s('*', 5, "ABC", 3); 
    const std::string expected = "*****ABC";
    // Act
    const size_t sz = s.size( );
    const char* cstr = s.c_str( );

    // Assert size
    bool sizeOk = ( sz == expected.size( ) );
    BOOST_TEST( sizeOk );

    // Assert content equality
    bool contentOk = ( s == std::string_view( expected ) );
    BOOST_TEST( contentOk );

    // Assert null terminator
    bool terminatorOk = ( cstr[ sz ] == '\0' );
    BOOST_TEST( terminatorOk );
}
// Ansi: repeat only (tail empty) 
BOOST_AUTO_TEST_CASE(Ansi_RepeatOnly_BuildsRepeatedString) 
{ 
    // Arrange 
    BasicString<char> s('Q', 4, "", 0); 
    const std::string expected = "QQQQ";
    // Act
    const size_t sz = s.size( );
    const char* cstr = s.c_str( );

    // Assert size
    bool sizeOk = ( sz == expected.size( ) );
    BOOST_TEST( sizeOk );

    // Assert content equality
    bool contentOk = ( s == std::string_view( expected ) );
    BOOST_TEST( contentOk );

    // Assert null terminator
    bool terminatorOk = ( cstr[ sz ] == '\0' );
    BOOST_TEST( terminatorOk );
}
// Ansi: tail only (repeat count zero) 
BOOST_AUTO_TEST_CASE(Ansi_TailOnly_BuildsTail) 
{ 
    // Arrange 
    BasicString<char> s('Z', 0, "ABC", 3); 
    const std::string expected = "ABC";
    // Act
    const size_t sz = s.size( );
    const char* cstr = s.c_str( );

    // Assert size
    bool sizeOk = ( sz == expected.size( ) );
    BOOST_TEST( sizeOk );

    // Assert content equality
    bool contentOk = ( s == std::string_view( expected ) );
    BOOST_TEST( contentOk );

    // Assert null terminator
    bool terminatorOk = ( cstr[ sz ] == '\0' );
    BOOST_TEST( terminatorOk );
}
// Ansi: empty when both repeat count and tail length are zero 
BOOST_AUTO_TEST_CASE(Ansi_Empty_WhenBothZero) 
{ 
    // Arrange 
    BasicString<char> s('X', 0, "", 0);
    // Act
    const bool isEmpty = s.empty( );

    // Assert empty
    bool emptyOk = isEmpty;
    BOOST_TEST( emptyOk );

    // Assert size is zero
    bool sizeOk = ( s.size( ) == 0 );
    BOOST_TEST( sizeOk );
}
// Wide: repeat + tail -> concatenation 
BOOST_AUTO_TEST_CASE(Wide_RepeatAndTail_Concatenates) 
{ 
    // Arrange 
    BasicString<wchar_t> s(L'*', 3, L"XYZ", 3); 
    const std::wstring expected = L"***XYZ";
    // Act
    const size_t sz = s.size( );
    const wchar_t* cstr = s.c_str( );

    // Assert size
    bool sizeOk = ( sz == expected.size( ) );
    BOOST_TEST( sizeOk );

    // Assert content equality
    bool contentOk = ( s == std::wstring_view( expected ) );
    BOOST_TEST( contentOk );

    // Assert null terminator
    bool terminatorOk = ( cstr[ sz ] == L'\0' );
    BOOST_TEST( terminatorOk );
}
// Wide: repeat only (tail empty) 
BOOST_AUTO_TEST_CASE(Wide_RepeatOnly_BuildsRepeatedString) 
{ 
    // Arrange 
    BasicString<wchar_t> s(L'Q', 2, L"", 0); 
    const std::wstring expected = L"QQ";
    // Act
    const size_t sz = s.size( );
    const wchar_t* cstr = s.c_str( );

    // Assert size
    bool sizeOk = ( sz == expected.size( ) );
    BOOST_TEST( sizeOk );

    // Assert content equality
    bool contentOk = ( s == std::wstring_view( expected ) );
    BOOST_TEST( contentOk );

    // Assert null terminator
    bool terminatorOk = ( cstr[ sz ] == L'\0' );
    BOOST_TEST( terminatorOk );
}
// Wide: tail only (repeat count zero) 
BOOST_AUTO_TEST_CASE(Wide_TailOnly_BuildsTail) 
{ 
    // Arrange 
    BasicString<wchar_t> s(L'Z', 0, L"AB", 2); 
    const std::wstring expected = L"AB";
    // Act
    const size_t sz = s.size( );
    const wchar_t* cstr = s.c_str( );

    // Assert size
    bool sizeOk = ( sz == expected.size( ) );
    BOOST_TEST( sizeOk );

    // Assert content equality
    bool contentOk = ( s == std::wstring_view( expected ) );
    BOOST_TEST( contentOk );

    // Assert null terminator
    bool terminatorOk = ( cstr[ sz ] == L'\0' );
    BOOST_TEST( terminatorOk );
}
// Wide: empty when both repeat count and tail length are zero 
BOOST_AUTO_TEST_CASE(Wide_Empty_WhenBothZero) 
{ 
    // Arrange 
    BasicString<wchar_t> s(L'X', 0, L"", 0);
    // Act
    const bool isEmpty = s.empty( );

    // Assert empty
    bool emptyOk = isEmpty;
    BOOST_TEST( emptyOk );

    // Assert size is zero
    bool sizeOk = ( s.size( ) == 0 );
    BOOST_TEST( sizeOk );
}

// Test: char - value repeated then appended C-string
BOOST_AUTO_TEST_CASE( TestChar_ValueCountAndString2 )
{
    // Arrange
    BasicString<char> s( '*', 3, "abc", 3 );

    // Assert length
    bool lenOk = ( s.length( ) == 6 );
    BOOST_TEST( lenOk );

    // Assert content
    std::string actual( s.c_str( ), s.size( ) );
    bool contentOk = ( actual == std::string( "***abc" ) );
    BOOST_TEST( contentOk );
}

// Test: char - only repeated value (string2 empty)
BOOST_AUTO_TEST_CASE( TestChar_OnlyCount )
{
    // Arrange
    BasicString<char> s( '$', 4, "", 0 );

    // Assert length
    bool lenOk = ( s.length( ) == 4 );
    BOOST_TEST( lenOk );

    // Assert content
    std::string actual( s.c_str( ), s.size( ) );
    bool contentOk = ( actual == std::string( "$$$$" ) );
    BOOST_TEST( contentOk );
}

// Test: char - only string2 (count zero)
BOOST_AUTO_TEST_CASE( TestChar_OnlyString2 )
{
    // Arrange
    BasicString<char> s( 'x', 0, "hello", 5 );

    // Assert length
    bool lenOk = ( s.length( ) == 5 );
    BOOST_TEST( lenOk );

    // Assert content
    std::string actual( s.c_str( ), s.size( ) );
    bool contentOk = ( actual == std::string( "hello" ) );
    BOOST_TEST( contentOk );
}

// Test: char - both zero -> empty
BOOST_AUTO_TEST_CASE( TestChar_BothZeroEmpty )
{
    // Arrange
    BasicString<char> s( 'a', 0, nullptr, 0 );

    // Assert length
    bool lenOk = ( s.length( ) == 0 );
    BOOST_TEST( lenOk );

    // Assert content is empty
    bool contentOk = ( s.empty( ) );
    BOOST_TEST( contentOk );
}

// Wide character (wchar_t) counterparts

// Test: wchar_t - value repeated then appended wide C-string
BOOST_AUTO_TEST_CASE( TestWide_ValueCountAndString2 )
{
    // Arrange
    BasicString<wchar_t> s( L'*', 3, L"abc", 3 );

    // Assert length
    bool lenOk = ( s.length( ) == 6 );
    BOOST_TEST( lenOk );

    // Assert content
    std::wstring actual( s.c_str( ), s.size( ) );
    bool contentOk = ( actual == std::wstring( L"***abc" ) );
    BOOST_TEST( contentOk );
}

// Test: wchar_t - only repeated value (string2 empty)
BOOST_AUTO_TEST_CASE( TestWide_OnlyCount )
{
    // Arrange
    BasicString<wchar_t> s( L'$', 4, L"", 0 );

    // Assert length
    bool lenOk = ( s.length( ) == 4 );
    BOOST_TEST( lenOk );

    // Assert content
    std::wstring actual( s.c_str( ), s.size( ) );
    bool contentOk = ( actual == std::wstring( L"$$$$" ) );
    BOOST_TEST( contentOk );
}

// Test: wchar_t - only string2 (count zero)
BOOST_AUTO_TEST_CASE( TestWide_OnlyString2 )
{
    // Arrange
    BasicString<wchar_t> s( L'x', 0, L"hello", 5 );

    // Assert length
    bool lenOk = ( s.length( ) == 5 );
    BOOST_TEST( lenOk );

    // Assert content
    std::wstring actual( s.c_str( ), s.size( ) );
    bool contentOk = ( actual == std::wstring( L"hello" ) );
    BOOST_TEST( contentOk );
}

// Test: wchar_t - both zero -> empty
BOOST_AUTO_TEST_CASE( TestWide_BothZeroEmpty )
{
    // Arrange
    BasicString<wchar_t> s( L'a', 0, nullptr, 0 );

    // Assert length
    bool lenOk = ( s.length( ) == 0 );
    BOOST_TEST( lenOk );

    // Assert content is empty
    bool contentOk = ( s.empty( ) );
    BOOST_TEST( contentOk );
}

/// Test constructing an ANSI BasicString from a prefix and repeated character suffix.
BOOST_AUTO_TEST_CASE( TestPrefixAndRepeatedChar_Ansi )
{
    // Arrange: prefix, prefix length, repeat character and count
    const char* prefix = "HelloWorld";
    std::size_t size1 = 5;
    char value = '*';
    std::size_t count = 3;

    // Act: construct the BasicString using the (string1, size1, value, count) constructor
    BasicString<char> s( prefix, size1, value, count );

    // Build expected std::string for verification
    std::string expectedPrefix( prefix, size1 );
    std::string expectedSuffix( count, value );
    std::string expected = expectedPrefix + expectedSuffix;

    // Build actual std::string from constructed BasicString
    std::string actual( s.data( ), s.size( ) );

    // Assert: use a bool variable as argument to BOOST_TEST
    bool areEqual = ( actual == expected );
    BOOST_TEST( areEqual );
}

/// Test constructing an ANSI BasicString when prefix length is zero (only repeated chars).
BOOST_AUTO_TEST_CASE( TestPrefixAndRepeatedChar_EmptyPrefix )
{
    // Arrange: prefix present but size1 is zero, repeat character and count
    const char* prefix = "ignored";
    std::size_t size1 = 0;
    char value = '#';
    std::size_t count = 4;

    // Act: construct the BasicString
    BasicString<char> s( prefix, size1, value, count );

    // Build expected std::string with only repeated characters
    std::string expected( count, value );

    // Build actual std::string from constructed BasicString
    std::string actual( s.data( ), s.size( ) );

    // Assert equality via a bool variable
    bool areEqual = ( actual == expected );
    BOOST_TEST( areEqual );
}

/// Test constructing a wide BasicString from a wide prefix and a repeated wide character.
BOOST_AUTO_TEST_CASE( TestPrefixAndRepeatedChar_Wide )
{
    // Arrange: wide prefix, prefix length, repeat wide char and count
    const wchar_t* prefix = L"WideHello";
    std::size_t size1 = 4;
    wchar_t value = L'?';
    std::size_t count = 2;

    // Act: construct the BasicString<wchar_t>
    BasicString<wchar_t> ws( prefix, size1, value, count );

    // Build expected std::wstring
    std::wstring expectedPrefix( prefix, size1 );
    std::wstring expectedSuffix( count, value );
    std::wstring expected = expectedPrefix + expectedSuffix;

    // Build actual std::wstring from constructed BasicString<wchar_t>
    std::wstring actual( ws.data( ), ws.size( ) );

    // Assert equality via a bool variable
    bool areEqual = ( actual == expected );
    BOOST_TEST( areEqual );
}

// Test constructing BasicString<char> from two std::string_view values.
BOOST_AUTO_TEST_CASE( Concatenate_StringView_StringView )
{
    // Prepare input parts as string_view.
    std::string_view part1 = "Hello ";
    std::string_view part2 = "World";

    // Construct BasicString<char> from two string_view spans.
    BasicString<char> result( part1, part2 );

    // Verify resulting length equals sum of part lengths.
    bool lengthIsCorrect = ( result.size( ) == ( part1.size( ) + part2.size( ) ) );
    BOOST_TEST( lengthIsCorrect );

    // Verify content equals expected concatenation.
    std::string expected = std::string( part1 ) + std::string( part2 );
    bool contentMatches = ( std::string( result.data( ), result.size( ) ) == expected );
    BOOST_TEST( contentMatches );
}

// Test constructing BasicString<char> from std::string and std::string_view.
BOOST_AUTO_TEST_CASE( Concatenate_String_StringView )
{
    // Prepare input parts: std::string and std::string_view.
    std::string s1 = "Foo";
    std::string_view s2 = "Bar";

    // Construct BasicString<char> from mixed contiguous containers.
    BasicString<char> result( s1, s2 );

    // Verify resulting length equals sum of part lengths.
    bool lengthIsCorrect = ( result.length( ) == ( s1.size( ) + s2.size( ) ) );
    BOOST_TEST( lengthIsCorrect );

    // Verify content equals expected concatenation.
    std::string expected = s1 + std::string( s2 );
    bool contentMatches = ( std::string( result.data( ), result.size( ) ) == expected );
    BOOST_TEST( contentMatches );
}

// Test constructing BasicString<wchar_t> from std::wstring and std::wstring_view.
BOOST_AUTO_TEST_CASE( Concatenate_WideString_WideStringView )
{
    // Prepare wide input parts.
    std::wstring ws1 = L"Wide";
    std::wstring_view ws2 = L"Concat";

    // Construct BasicString<wchar_t> from wide contiguous containers.
    BasicString<wchar_t> result( ws1, ws2 );

    // Verify resulting length equals sum of part lengths.
    bool lengthIsCorrect = ( result.Length( ) == ( ws1.size( ) + ws2.size( ) ) );
    BOOST_TEST( lengthIsCorrect );

    // Verify content equals expected wide concatenation.
    std::wstring expected = ws1 + std::wstring( ws2 );
    bool contentMatches = ( std::wstring( result.data( ), result.size( ) ) == expected );
    BOOST_TEST( contentMatches );
}

// Test constructing BasicString with empty spans in various combinations.
BOOST_AUTO_TEST_CASE( Concatenate_EmptySpans )
{
    // Case 1: first empty, second non-empty.
    std::string_view empty = "";
    std::string_view nonEmpty = "NonEmpty";

    // Construct BasicString from (empty, nonEmpty).
    BasicString<char> result1( empty, nonEmpty );

    // Verify length and content for case 1.
    bool length1Correct = ( result1.size( ) == nonEmpty.size( ) );
    BOOST_TEST( length1Correct );
    bool content1Matches = ( std::string( result1.data( ), result1.size( ) ) == std::string( nonEmpty ) );
    BOOST_TEST( content1Matches );

    // Case 2: first non-empty, second empty.
    BasicString<char> result2( nonEmpty, empty );

    // Verify length and content for case 2.
    bool length2Correct = ( result2.size( ) == nonEmpty.size( ) );
    BOOST_TEST( length2Correct );
    bool content2Matches = ( std::string( result2.data( ), result2.size( ) ) == std::string( nonEmpty ) );
    BOOST_TEST( content2Matches );

    // Case 3: both empty.
    BasicString<char> result3( empty, empty );

    // Verify length and content for case 3.
    bool length3Correct = ( result3.size( ) == 0 );
    BOOST_TEST( length3Correct );
    bool content3Matches = ( result3.data( ) == nullptr || std::string( result3.data( ), result3.size( ) ).empty( ) );
    BOOST_TEST( content3Matches );
}

BOOST_AUTO_TEST_CASE( Test_Concatenate_StringView_And_CString_Length )
{
    std::string_view prefix = "Hello";
    const char* suffix = " World";
    BasicString<char> result( prefix, suffix, static_cast<BasicString<char>::size_type>( 6 ) );

    BasicString<char> expected( "Hello World" );
    bool eq = ( result == expected );
    BOOST_TEST( eq );
}

BOOST_AUTO_TEST_CASE( Test_EmptySpan_With_CString )
{
    std::string_view prefix = "";
    const char* suffix = "OnlySuffix";
    BasicString<char> result( prefix, suffix, static_cast<BasicString<char>::size_type>( std::strlen( suffix ) ) );

    BasicString<char> expected( suffix );
    bool eq = ( result == expected );
    BOOST_TEST( eq );
}

BOOST_AUTO_TEST_CASE( Test_Span_With_EmptyCString )
{
    std::string_view prefix = "OnlyPrefix";
    const char* suffix = "";
    BasicString<char> result( prefix, suffix, static_cast<BasicString<char>::size_type>( 0 ) );

    BasicString<char> expected( prefix.data( ), prefix.size( ) );
    bool eq = ( result == expected );
    BOOST_TEST( eq );
}

BOOST_AUTO_TEST_CASE( Test_Wide_Concatenate_WStringView_And_CWideString_Length )
{
    std::wstring_view prefix = L"WideHello";
    const wchar_t* suffix = L" WideWorld";
    BasicString<wchar_t> result( prefix, suffix, static_cast<BasicString<wchar_t>::size_type>( 10 ) );

    BasicString<wchar_t> expected( L"WideHello WideWorld", static_cast<BasicString<wchar_t>::size_type>( 19 ) );
    bool eq = ( result == expected );
    BOOST_TEST( eq );
}

BOOST_AUTO_TEST_CASE( Test_Wide_EmptySpan_With_CWideString )
{
    std::wstring_view prefix = L"";
    const wchar_t* suffix = L"WideOnlySuffix";
    BasicString<wchar_t> result( prefix, suffix, static_cast<BasicString<wchar_t>::size_type>( std::wcslen( suffix ) ) );

    BasicString<wchar_t> expected( suffix );
    bool eq = ( result == expected );
    BOOST_TEST( eq );
}

BOOST_AUTO_TEST_CASE( Test_Wide_Span_With_EmptyCWideString )
{
    std::wstring_view prefix = L"WideOnlyPrefix";
    const wchar_t* suffix = L"";
    BasicString<wchar_t> result( prefix, suffix, static_cast<BasicString<wchar_t>::size_type>( 0 ) );

    BasicString<wchar_t> expected( prefix.data( ), prefix.size( ) );
    bool eq = ( result == expected );
    BOOST_TEST( eq );
}

BOOST_AUTO_TEST_CASE( ConstructFromPointerAndStringView )
{
    const char* prefix = "Hello";
    std::string_view suffix = "llo";
    // prefix length 2 -> "He" + "llo" => "Hello"
    BasicString<char> s( prefix, 2, suffix );
    BasicString<char> expected( "Hello" );
    bool equals = ( s == expected );
    BOOST_TEST( equals );
}

BOOST_AUTO_TEST_CASE( ConstructFromPointerAndStdString )
{
    const char* prefix = "Good";
    std::string suffix = std::string( "bye" );
    // "Good" (size 4) + "bye" => "Goodbye"
    BasicString<char> s( prefix, 4, suffix );
    BasicString<char> expected( "Goodbye" );
    bool equals = ( s == expected );
    BOOST_TEST( equals );
}

BOOST_AUTO_TEST_CASE( ConstructFromPointerAndVectorChar )
{
    const char* prefix = "Start";
    std::vector<char> suffix = { 'S', 't', 'o', 'p' }; // "Stop"
    // prefix length 3 -> "Sta" + "Stop" => "StaStop"
    BasicString<char> s( prefix, 3, suffix );
    BasicString<char> expected( "StaStop" );
    bool equals = ( s == expected );
    BOOST_TEST( equals );
}

BOOST_AUTO_TEST_CASE( ConstructWithNullPrefixAndSpan )
{
    // nullptr allowed when size is zero
    const char* prefix = nullptr;
    std::string_view suffix = "world";
    BasicString<char> s( prefix, 0, suffix );
    BasicString<char> expected( "world" );
    bool equals = ( s == expected );
    BOOST_TEST( equals );
}

BOOST_AUTO_TEST_CASE( ConstructWideStringFromPointerAndWStringView )
{
    const wchar_t* prefix = L"Wide";
    std::wstring_view suffix = L"Hello";
    // prefix size 4 + suffix => "WideHello"
    BasicString<wchar_t> s( prefix, 4, suffix );
    BasicString<wchar_t> expected( L"WideHello", 9 );
    bool equals = ( s == expected );
    BOOST_TEST( equals );
}

/// Test constructing BasicString<char> from a std::string_view with a prepended character value.
BOOST_AUTO_TEST_CASE( TestConstructFromStringView_Char )
{
    // Arrange
    std::string_view sv( "hello" );
    // Act
    BasicString<char> s( '*', sv );
    // Assert
    bool sizeOk = ( s.size( ) == 6 );
    BOOST_TEST( sizeOk );
    bool firstCharOk = ( s[ 0 ] == '*' );
    BOOST_TEST( firstCharOk );
    std::string result( s.data( ), s.size( ) );
    bool contentOk = ( result == std::string( "*hello" ) );
    BOOST_TEST( contentOk );
}

/// Test constructing BasicString<wchar_t> from a std::wstring_view with a prepended wide character.
BOOST_AUTO_TEST_CASE( TestConstructFromStringView_WideChar )
{
    // Arrange
    std::wstring_view wsv( L"Wide" );
    // Act
    BasicString<wchar_t> ws( L'X', wsv );
    // Assert
    bool sizeOk = ( ws.size( ) == 5 );
    BOOST_TEST( sizeOk );
    bool firstCharOk = ( ws[ 0 ] == L'X' );
    BOOST_TEST( firstCharOk );
    std::wstring wresult( ws.data( ), ws.size( ) );
    bool contentOk = ( wresult == std::wstring( L"XWide" ) );
    BOOST_TEST( contentOk );
}

/// Test constructing BasicString<char> from a std::vector<char> and from an empty span.
BOOST_AUTO_TEST_CASE( TestConstructFromVector_Char_AndEmptySpan )
{
    // Arrange
    std::vector<char> vec = { 'a', 'b' };
    std::vector<char> emptyVec;
    // Act
    BasicString<char> s1( '#', vec );
    BasicString<char> s2( '#', emptyVec );
    // Assert s1
    bool sizeOk1 = ( s1.size( ) == 3 );
    BOOST_TEST( sizeOk1 );
    std::string result1( s1.data( ), s1.size( ) );
    bool contentOk1 = ( result1 == std::string( "#ab" ) );
    BOOST_TEST( contentOk1 );
    // Assert s2
    bool sizeOk2 = ( s2.size( ) == 1 );
    BOOST_TEST( sizeOk2 );
    std::string result2( s2.data( ), s2.size( ) );
    bool contentOk2 = ( result2 == std::string( "#" ) );
    BOOST_TEST( contentOk2 );
}

//
// Construct BasicString<char> from std::string_view span with a leading repeated char value.
// Expected result: repeated value characters followed by span content.
//
BOOST_AUTO_TEST_CASE( BasicString_ConstructFromSpanWithLeadingValue )
{
    // Arrange
    std::string_view span = "world";
    char value = '*';
    BasicString<char>::size_type count = 3;

    // Act
    BasicString<char> s( value, count, span );

    // Expected
    std::string expected = std::string( static_cast<size_t>( count ), value ) + std::string( span );

    // Assert - size
    bool sizeOk = ( s.size( ) == expected.size( ) );
    BOOST_TEST( sizeOk );

    // Assert - content
    bool contentOk = std::string( s.c_str( ), s.size( ) ) == expected;
    BOOST_TEST( contentOk );

    // Assert - StartsWith
    bool startsOk = s.StartsWith( value );
    BOOST_TEST( startsOk );

    // Assert - EndsWith (C-string)
    bool endsOk = s.EndsWith( expected.c_str( ) );
    BOOST_TEST( endsOk );

    // Assert - operator== with C-string
    bool eqOk = ( s == expected.c_str( ) );
    BOOST_TEST( eqOk );
}

//
// Construct BasicString<wchar_t> from std::wstring_view span with a leading repeated wchar_t value.
// Expected result: repeated value characters followed by span content.
//
BOOST_AUTO_TEST_CASE( BasicStringW_ConstructFromSpanWithLeadingValue )
{
    // Arrange
    std::wstring_view span = L"世界";
    wchar_t value = L'#';
    BasicString<wchar_t>::size_type count = 2;

    // Act
    BasicString<wchar_t> s( value, count, span );

    // Expected
    std::wstring expected( static_cast<size_t>( count ), value );
    expected += std::wstring( span );

    // Assert - size
    bool sizeOk = ( s.size( ) == expected.size( ) );
    BOOST_TEST( sizeOk );

    // Assert - content
    bool contentOk = std::wstring( s.c_str( ), s.size( ) ) == expected;
    BOOST_TEST( contentOk );

    // Assert - StartsWith
    bool startsOk = s.StartsWith( value );
    BOOST_TEST( startsOk );

    // Assert - EndsWith (wide C-string)
    bool endsOk = s.EndsWith( expected.c_str( ) );
    BOOST_TEST( endsOk );

    // Assert - operator== with wide C-string
    bool eqOk = ( s == expected.c_str( ) );
    BOOST_TEST( eqOk );
}

//
// Empty span and non-zero count should produce string consisting only of repeated value characters.
//
BOOST_AUTO_TEST_CASE( BasicString_ConstructEmptySpanLeadingValueOnly )
{
    // Arrange
    std::string_view span = "";
    char value = 'X';
    BasicString<char>::size_type count = 5;

    // Act
    BasicString<char> s( value, count, span );

    // Expected
    std::string expected( static_cast<size_t>( count ), value );

    // Assert - content
    bool contentOk = std::string( s.c_str( ), s.size( ) ) == expected;
    BOOST_TEST( contentOk );

    // Assert - size
    bool sizeOk = ( s.size( ) == expected.size( ) );
    BOOST_TEST( sizeOk );
}

//
// Non-empty span and count == 0 should produce string equal to the span.
//
BOOST_AUTO_TEST_CASE( BasicString_ConstructSpanNoLeadingValue )
{
    // Arrange
    std::string_view span = "hello";
    char value = '*';
    BasicString<char>::size_type count = 0;

    // Act
    BasicString<char> s( value, count, span );

    // Expected
    std::string expected( span );

    // Assert - content equals span
    bool contentOk = std::string( s.c_str( ), s.size( ) ) == expected;
    BOOST_TEST( contentOk );

    // Assert - equality with C-string
    bool eqOk = ( s == expected.c_str( ) );
    BOOST_TEST( eqOk );
}

/// Test constructing Ansi BasicString from a std::string_view span, then appending repeated char value
BOOST_AUTO_TEST_CASE( ConstructFromSpanAndAppendValue_Ansi )
{
    // Arrange
    std::string_view span = "Hello";
    char value = '*';
    std::size_t count = 3;

    // Act
    BasicString<char> s( span, value, count );
    BasicString<char> expected( "Hello***" );

    // Assert
    bool equal = ( s == expected );
    BOOST_TEST( equal );
}

/// Test constructing Wide BasicString from a std::wstring_view span, then appending repeated wchar_t value
BOOST_AUTO_TEST_CASE( ConstructFromSpanAndAppendValue_Wide )
{
    // Arrange
    std::wstring_view span = L"Hi";
    wchar_t value = L'!';
    std::size_t count = 2;

    // Act
    BasicString<wchar_t> s( span, value, count );
    BasicString<wchar_t> expected( L"Hi!!" );

    // Assert
    bool equal = ( s == expected );
    BOOST_TEST( equal );
}

/// Test that count == 0 results in the original span content (no appended characters)
BOOST_AUTO_TEST_CASE( ConstructFromSpanAndAppendValue_CountZero )
{
    // Arrange
    std::string_view span = "Base";
    char value = '-';
    std::size_t count = 0;

    // Act
    BasicString<char> s( span, value, count );
    BasicString<char> expected( "Base" );

    // Assert
    bool equal = ( s == expected );
    BOOST_TEST( equal );
}

/// Test empty span with positive count produces repeated value characters
BOOST_AUTO_TEST_CASE( ConstructFromEmptySpanAndCountPositive )
{
    // Arrange
    std::string_view span = "";
    char value = 'X';
    std::size_t count = 5;

    // Act
    BasicString<char> s( span, value, count );
    BasicString<char> expected( "XXXXX" );

    // Assert
    bool equal = ( s == expected );
    BOOST_TEST( equal );
}

BOOST_AUTO_TEST_CASE( ConstructFromStringView_AppendsValueAtEnd_Ansi )
{
    std::string_view span = "world";
    BasicString<char> s( span, '!' );

    BasicString<char> expected( "world!", 6 );

    bool result = ( s == expected );
    BOOST_TEST( result );

    bool resultLen = ( s.Length( ) == expected.Length( ) );
    BOOST_TEST( resultLen );
}

BOOST_AUTO_TEST_CASE( ConstructFromEmptyStringView_CreatesSingleChar_Ansi )
{
    std::string_view span = "";
    BasicString<char> s( span, 'A' );

    BasicString<char> expected( "A", 1 );

    bool result = ( s == expected );
    BOOST_TEST( result );

    bool resultLen = ( s.Length( ) == 1 );
    BOOST_TEST( resultLen );
}

BOOST_AUTO_TEST_CASE( ConstructFromWStringView_AppendsValueAtEnd_Wide )
{
    std::wstring_view span = L"wide";
    BasicString<wchar_t> s( span, L'X' );

    BasicString<wchar_t> expected( L"wideX", 5 );

    bool result = ( s == expected );
    BOOST_TEST( result );

    bool resultLen = ( s.Length( ) == expected.Length( ) );
    BOOST_TEST( resultLen );
}

BOOST_AUTO_TEST_CASE( ConstructFromSingleCharSpan_AppendsValue_Ansi )
{
    std::string_view span = "a";
    BasicString<char> s( span, 'z' );

    BasicString<char> expected( "az", 2 );

    bool result = ( s == expected );
    BOOST_TEST( result );

    bool resultLen = ( s.Length( ) == 2 );
    BOOST_TEST( resultLen );
}

// Test that concatenating three non-empty ANSI parts produces the expected result.
BOOST_AUTO_TEST_CASE( ThreePartConcat_Ansi_NonEmpty )
{
    // Arrange
    const char* p1 = "Hello";
    size_t s1 = 5;
    const char* p2 = " ";
    size_t s2 = 1;
    const char* p3 = "World";
    size_t s3 = 5;

    // Act
    BasicString<char> result( p1, s1, p2, s2, p3, s3 );
    std::string actual( result.data( ), result.size( ) );
    std::string expected = "Hello World";

    // Assert
    bool equal = ( actual == expected );
    BOOST_TEST( equal );

    bool equalSize = ( result.size( ) == expected.size( ) );
    BOOST_TEST( equalSize );
}

// Test that constructor handles nullptr parts when size is zero and empty parts.
BOOST_AUTO_TEST_CASE( ThreePartConcat_Ansi_EmptyPartsAndNullPtrs )
{
    // Arrange
    const char* p1 = nullptr;
    size_t s1 = 0;
    const char* p2 = "Middle";
    size_t s2 = 6; // "Middle" length
    const char* p3 = nullptr;
    size_t s3 = 0;

    // Act
    BasicString<char> result( p1, s1, p2, s2, p3, s3 );
    std::string actual( result.data( ), result.size( ) );
    std::string expected = "Middle";

    // Assert
    bool equal = ( actual == expected );
    BOOST_TEST( equal );

    bool equalSize = ( result.size( ) == expected.size( ) );
    BOOST_TEST( equalSize );
}

// Test that constructor preserves embedded null characters when explicit sizes are provided.
BOOST_AUTO_TEST_CASE( ThreePartConcat_Ansi_EmbeddedNulls )
{
    // Arrange
    char part1[ ] = { 'a', 'b', '\0', 'c' }; // length 4
    size_t s1 = 4;
    char part2[ ] = { '-', '\0' }; // length 2 (includes embedded null)
    size_t s2 = 2;
    char part3[ ] = { 'X', 'Y' }; // length 2
    size_t s3 = 2;

    // Act
    BasicString<char> result( part1, s1, part2, s2, part3, s3 );
    std::string actual( result.data( ), result.size( ) );

    // Build expected string with explicit sizes (to include embedded nulls)
    std::string expected;
    expected.append( part1, s1 );
    expected.append( part2, s2 );
    expected.append( part3, s3 );

    // Assert
    bool equal = ( actual == expected );
    BOOST_TEST( equal );

    bool equalSize = ( result.size( ) == expected.size( ) );
    BOOST_TEST( equalSize );
}

// --- Wide-character (wchar_t) tests ---

// Test that concatenating three non-empty wide parts produces the expected result.
BOOST_AUTO_TEST_CASE( ThreePartConcat_Wide_NonEmpty )
{
    // Arrange
    const wchar_t* p1 = L"Hello";
    size_t s1 = 5;
    const wchar_t* p2 = L" ";
    size_t s2 = 1;
    const wchar_t* p3 = L"World";
    size_t s3 = 5;

    // Act
    BasicString<wchar_t> result( p1, s1, p2, s2, p3, s3 );
    std::wstring actual( result.data( ), result.size( ) );
    std::wstring expected = L"Hello World";

    // Assert
    bool equal = ( actual == expected );
    BOOST_TEST( equal );

    bool equalSize = ( result.size( ) == expected.size( ) );
    BOOST_TEST( equalSize );
}

// Test that constructor handles nullptr parts when size is zero and empty wide parts.
BOOST_AUTO_TEST_CASE( ThreePartConcat_Wide_EmptyPartsAndNullPtrs )
{
    // Arrange
    const wchar_t* p1 = nullptr;
    size_t s1 = 0;
    const wchar_t* p2 = L"Middle";
    size_t s2 = 6; // "Middle" length
    const wchar_t* p3 = nullptr;
    size_t s3 = 0;

    // Act
    BasicString<wchar_t> result( p1, s1, p2, s2, p3, s3 );
    std::wstring actual( result.data( ), result.size( ) );
    std::wstring expected = L"Middle";

    // Assert
    bool equal = ( actual == expected );
    BOOST_TEST( equal );

    bool equalSize = ( result.size( ) == expected.size( ) );
    BOOST_TEST( equalSize );
}

// Test that constructor preserves embedded null wide characters when explicit sizes are provided.
BOOST_AUTO_TEST_CASE( ThreePartConcat_Wide_EmbeddedNulls )
{
    // Arrange
    wchar_t part1[ ] = { L'a', L'b', L'\0', L'c' }; // length 4
    size_t s1 = 4;
    wchar_t part2[ ] = { L'-', L'\0' }; // length 2 (includes embedded null)
    size_t s2 = 2;
    wchar_t part3[ ] = { L'X', L'Y' }; // length 2
    size_t s3 = 2;

    // Act
    BasicString<wchar_t> result( part1, s1, part2, s2, part3, s3 );
    std::wstring actual( result.data( ), result.size( ) );

    // Build expected wstring with explicit sizes (to include embedded nulls)
    std::wstring expected;
    expected.append( part1, s1 );
    expected.append( part2, s2 );
    expected.append( part3, s3 );

    // Assert
    bool equal = ( actual == expected );
    BOOST_TEST( equal );

    bool equalSize = ( result.size( ) == expected.size( ) );
    BOOST_TEST( equalSize );
}

/// <summary>
/// Verify that the constructor BasicString(CharType value, size_type count, const CharType* string2, size_type size2, const CharType* string3, size_type size3)
/// correctly produces the concatenation: repeated value (count times) + string2 (size2 chars) + string3 (size3 chars).
/// </summary>
BOOST_AUTO_TEST_CASE( Constructor_ValueCountAndTwoStrings )
{
    // Arrange
    BasicString<char> s( '*', 5, "hello", 5, "world", 5 );
    std::string expected = std::string( 5, '*' ) + "hello" + "world";
    bool cond = ( s.size( ) == expected.size( ) ) && ( std::string( s.c_str( ), s.size( ) ) == expected );

    // Assert
    BOOST_TEST( cond );
}

/// <summary>
/// Same test as above but for wide characters (wchar_t).
/// Ensures wide-character overload produces expected wide string.
/// </summary>
BOOST_AUTO_TEST_CASE( Constructor_WideChar_ValueCountAndTwoStrings )
{
    // Arrange
    BasicString<wchar_t> ws( L'A', 3, L"abc", 3, L"def", 3 );
    std::wstring expected = std::wstring( 3, L'A' ) + L"abc" + L"def";
    bool cond = ( ws.size( ) == expected.size( ) ) && ( std::wstring( ws.c_str( ), ws.size( ) ) == expected );

    // Assert
    BOOST_TEST( cond );
}

/// <summary>
/// Construct with all zero lengths results in an empty BasicString.
/// Verifies empty() and that c_str() yields an empty zero-terminated string.
/// </summary>
BOOST_AUTO_TEST_CASE( Constructor_ZeroCountsProducesEmpty )
{
    // Arrange
    BasicString<char> empty( 'x', 0, nullptr, 0, nullptr, 0 );

    // Act / Assert
    bool condEmpty = empty.empty( );
    BOOST_TEST( condEmpty );

    bool condCStrEmpty = ( empty.c_str( ) != nullptr ) ? ( empty.c_str( )[ 0 ] == '\0' ) : true;
    BOOST_TEST( condCStrEmpty );
}

/// <summary>
/// Construct where the middle segment is empty but last segment is present.
/// Verifies concatenation when one input segment has length zero.
/// </summary>
BOOST_AUTO_TEST_CASE( Constructor_PartialEmptyMiddle )
{
    // Arrange
    BasicString<char> s( 'z', 2, "", 0, "end", 3 );
    std::string expected = std::string( 2, 'z' ) + "end";
    bool cond = ( s.size( ) == expected.size( ) ) && ( std::string( s.c_str( ), s.size( ) ) == expected );

    // Assert
    BOOST_TEST( cond );
}

BOOST_AUTO_TEST_CASE( Construct_WithPrefixValueSuffix_Ansi )
{
    // Arrange / Act
    BasicString<char> s( "pre", 3, '*', 5, "post", 4 );

    // Assert
    bool equalsExpected = ( s == "pre*****post" );
    BOOST_TEST( equalsExpected );

    bool sizeIsCorrect = ( s.size( ) == ( 3 + 5 + 4 ) );
    BOOST_TEST( sizeIsCorrect );
}

BOOST_AUTO_TEST_CASE( Construct_WithPrefixValueSuffix_Wide )
{
    // Arrange / Act
    BasicString<wchar_t> s( L"pre", 3, L'*', 5, L"post", 4 );

    // Assert
    bool equalsExpected = ( s == L"pre*****post" );
    BOOST_TEST( equalsExpected );

    bool sizeIsCorrect = ( s.size( ) == ( 3 + 5 + 4 ) );
    BOOST_TEST( sizeIsCorrect );
}

BOOST_AUTO_TEST_CASE( Construct_OnlyRepeatedValue )
{
    // Arrange / Act
    BasicString<char> s( nullptr, 0, '#', 7, nullptr, 0 );

    // Assert
    bool equalsExpected = ( s == "#######" );
    BOOST_TEST( equalsExpected );

    bool sizeIsCorrect = ( s.size( ) == 7 );
    BOOST_TEST( sizeIsCorrect );
}

BOOST_AUTO_TEST_CASE( Construct_AllZero_YieldsEmpty )
{
    // Arrange / Act
    BasicString<char> s( nullptr, 0, 'x', 0, nullptr, 0 );

    // Assert
    bool isEmpty = ( s.size( ) == 0 );
    BOOST_TEST( isEmpty );

    bool equalsEmptyLiteral = ( s == "" );
    BOOST_TEST( equalsEmptyLiteral );
}

BOOST_AUTO_TEST_CASE( Construct_String1_String2_ValueAtEnd )
{
    // string1 + string2 + value repeated
    BasicString<char> s( "Hello", 5, "World", 5, '*', 3 );
    bool equalsExpected = ( s == "HelloWorld***" );
    BOOST_TEST( equalsExpected );

    bool sizeOk = ( s.size( ) == 13 );
    BOOST_TEST( sizeOk );
}

BOOST_AUTO_TEST_CASE( Construct_BothNull_OnlyValueRepeated )
{
    // both string1 and string2 null with count > 0 -> repeated value
    BasicString<char> s( nullptr, 0, nullptr, 0, 'A', 4 );
    bool equalsExpected = ( s == "AAAA" );
    BOOST_TEST( equalsExpected );

    bool sizeOk = ( s.size( ) == 4 );
    BOOST_TEST( sizeOk );
}

BOOST_AUTO_TEST_CASE( Construct_CountZero_ConcatOnly )
{
    // count == 0 -> only concatenation of string1 and string2
    BasicString<char> s( "abc", 3, "def", 3, 'Z', 0 );
    bool equalsExpected = ( s == "abcdef" );
    BOOST_TEST( equalsExpected );

    bool sizeOk = ( s.size( ) == 6 );
    BOOST_TEST( sizeOk );
}

BOOST_AUTO_TEST_CASE( Construct_EmptyFirstString_SecondPlusValues )
{
    // string1 empty (nullptr,size0) -> result is string2 + repeated value
    BasicString<char> s( nullptr, 0, "xyz", 3, '-', 2 );
    bool equalsExpected = ( s == "xyz--" );
    BOOST_TEST( equalsExpected );

    bool sizeOk = ( s.size( ) == 5 );
    BOOST_TEST( sizeOk );
}

BOOST_AUTO_TEST_CASE( Construct_WideChar_Variant )
{
    // wide-char variant
    BasicString<wchar_t> s( L"pre", 3, L"post", 4, L'X', 2 );
    bool equalsExpected = ( s == L"prepostXX" );
    BOOST_TEST( equalsExpected );

    bool sizeOk = ( s.size( ) == 9 );
    BOOST_TEST( sizeOk );
}

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
    equal = string2.cdata( ) == string1.cdata( );
    BOOST_TEST( equal );
}

// --run_test=StringTests/ConstructorTest9A
BOOST_AUTO_TEST_CASE( ConstructorTest9A )
{
    AnsiString string1( "123" );
    AnsiString string2( string1 );
    bool equal = string2 == "123";
    BOOST_TEST( equal );
    equal = string2.cdata( ) == string1.cdata( );
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


// --run_test=StringTests/StringEqualTest1W
BOOST_AUTO_TEST_CASE( StringEqualTest1W )
{
    WideString first;
    WideString second;
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest2W
BOOST_AUTO_TEST_CASE( StringEqualTest2W )
{
    WideString first( L"1" );
    WideString second;
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest3W
BOOST_AUTO_TEST_CASE( StringEqualTest3W )
{
    WideString first;
    WideString second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest4W
BOOST_AUTO_TEST_CASE( StringEqualTest4W )
{
    WideString first( L"12" );
    WideString second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest5W
BOOST_AUTO_TEST_CASE( StringEqualTest5W )
{
    WideString first( L"1" );
    WideString second( L"12" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest6W
BOOST_AUTO_TEST_CASE( StringEqualTest6W )
{
    WideString first( L"123" );
    WideString second( L"123" );
    bool equal = first == second;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringEqualTest7W
BOOST_AUTO_TEST_CASE( StringEqualTest7W )
{
    WideString first;
    const wchar_t* second = nullptr;
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest8W
BOOST_AUTO_TEST_CASE( StringEqualTest8W )
{
    WideString first( L"1" );
    const wchar_t* second = nullptr;
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest9W
BOOST_AUTO_TEST_CASE( StringEqualTest9W )
{
    WideString first;
    const wchar_t* second = L"1";
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest10W
BOOST_AUTO_TEST_CASE( StringEqualTest10W )
{
    WideString first( L"12" );
    const wchar_t* second = L"1";
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest11W
BOOST_AUTO_TEST_CASE( StringEqualTest11W )
{
    WideString first( L"1" );
    const wchar_t* second = L"12";
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest12W
BOOST_AUTO_TEST_CASE( StringEqualTest12W )
{
    WideString first( L"123" );
    const wchar_t* second = L"123";
    bool equal = first == second;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringEqualTest13W
BOOST_AUTO_TEST_CASE( StringEqualTest13W )
{
    const wchar_t* first = nullptr;
    WideString second;
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest14W
BOOST_AUTO_TEST_CASE( StringEqualTest14W )
{
    const wchar_t* first = L"1";
    WideString second;
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest15W
BOOST_AUTO_TEST_CASE( StringEqualTest15W )
{
    const wchar_t* first = nullptr;
    WideString second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest16W
BOOST_AUTO_TEST_CASE( StringEqualTest16W )
{
    const wchar_t* first = L"12";
    WideString second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest17W
BOOST_AUTO_TEST_CASE( StringEqualTest17W )
{
    const wchar_t* first = L"1";
    WideString second( L"12" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest18W
BOOST_AUTO_TEST_CASE( StringEqualTest18W )
{
    const wchar_t* first = L"123";
    WideString second( L"123" );
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest19W
BOOST_AUTO_TEST_CASE( StringEqualTest19W )
{
    std::wstring first;
    WideString second;
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest20W
BOOST_AUTO_TEST_CASE( StringEqualTest20W )
{
    std::wstring first( L"1" );
    WideString second;
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest21W
BOOST_AUTO_TEST_CASE( StringEqualTest21W )
{
    std::wstring first;
    WideString second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest22W
BOOST_AUTO_TEST_CASE( StringEqualTest22W )
{
    std::wstring first( L"12" );
    WideString second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest23W
BOOST_AUTO_TEST_CASE( StringEqualTest23W )
{
    std::wstring first( L"1" );
    WideString second( L"12" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest24W
BOOST_AUTO_TEST_CASE( StringEqualTest24W )
{
    std::wstring first( L"123" );
    WideString second( L"123" );
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest25W
BOOST_AUTO_TEST_CASE( StringEqualTest25W )
{
    WideString first;
    std::wstring second;
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest26W
BOOST_AUTO_TEST_CASE( StringEqualTest26W )
{
    WideString first( L"1" );
    std::wstring second;
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest27W
BOOST_AUTO_TEST_CASE( StringEqualTest27W )
{
    WideString first;
    std::wstring second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest28W
BOOST_AUTO_TEST_CASE( StringEqualTest28W )
{
    WideString first( L"12" );
    std::wstring second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest29W
BOOST_AUTO_TEST_CASE( StringEqualTest29W )
{
    WideString first( L"1" );
    std::wstring second( L"12" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest30W
BOOST_AUTO_TEST_CASE( StringEqualTest30W )
{
    WideString first( L"123" );
    std::wstring second( L"123" );
    bool equal = first == second;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringEqualTest31W
BOOST_AUTO_TEST_CASE( StringEqualTest31W )
{
    std::wstring_view first;
    WideString second;
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest32W
BOOST_AUTO_TEST_CASE( StringEqualTest32W )
{
    std::wstring_view first( L"1" );
    WideString second;
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest33W
BOOST_AUTO_TEST_CASE( StringEqualTest33W )
{
    std::wstring_view first;
    WideString second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest34W
BOOST_AUTO_TEST_CASE( StringEqualTest34W )
{
    std::wstring_view first( L"12" );
    WideString second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest35W
BOOST_AUTO_TEST_CASE( StringEqualTest35W )
{
    std::wstring_view first( L"1" );
    WideString second( L"12" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest36W
BOOST_AUTO_TEST_CASE( StringEqualTest36W )
{
    std::wstring_view first( L"123" );
    WideString second( L"123" );
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest37W
BOOST_AUTO_TEST_CASE( StringEqualTest37W )
{
    WideString first;
    std::wstring_view second;
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringEqualTest38W
BOOST_AUTO_TEST_CASE( StringEqualTest38W )
{
    WideString first( L"1" );
    std::wstring_view second;
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest39W
BOOST_AUTO_TEST_CASE( StringEqualTest39W )
{
    WideString first;
    std::wstring_view second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest40W
BOOST_AUTO_TEST_CASE( StringEqualTest40W )
{
    WideString first( L"12" );
    std::wstring_view second( L"1" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest41W
BOOST_AUTO_TEST_CASE( StringEqualTest41W )
{
    WideString first( L"1" );
    std::wstring_view second( L"12" );
    bool equal = first == second;
    BOOST_TEST( equal == false );
}

// --run_test=StringTests/StringEqualTest42W
BOOST_AUTO_TEST_CASE( StringEqualTest42W )
{
    WideString first( L"123" );
    std::wstring_view second( L"123" );
    bool equal = first == second;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringNotEqualTest1W
BOOST_AUTO_TEST_CASE( StringNotEqualTest1W )
{
    WideString first;
    WideString second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest2W
BOOST_AUTO_TEST_CASE( StringNotEqualTest2W )
{
    WideString first( L"1" );
    WideString second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest3W
BOOST_AUTO_TEST_CASE( StringNotEqualTest3W )
{
    WideString first;
    WideString second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest4W
BOOST_AUTO_TEST_CASE( StringNotEqualTest4W )
{
    WideString first( L"12" );
    WideString second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest5W
BOOST_AUTO_TEST_CASE( StringNotEqualTest5W )
{
    WideString first( L"1" );
    WideString second( L"12" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest6W
BOOST_AUTO_TEST_CASE( StringNotEqualTest6W )
{
    WideString first( L"123" );
    WideString second( L"123" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}


// --run_test=StringTests/StringNotEqualTest7W
BOOST_AUTO_TEST_CASE( StringNotEqualTest7W )
{
    WideString first;
    const wchar_t* second = nullptr;
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest8W
BOOST_AUTO_TEST_CASE( StringNotEqualTest8W )
{
    WideString first( L"1" );
    const wchar_t* second = nullptr;
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest9W
BOOST_AUTO_TEST_CASE( StringNotEqualTest9W )
{
    WideString first;
    const wchar_t* second = L"1";
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest10W
BOOST_AUTO_TEST_CASE( StringNotEqualTest10W )
{
    WideString first( L"12" );
    const wchar_t* second = L"1";
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest11W
BOOST_AUTO_TEST_CASE( StringNotEqualTest11W )
{
    WideString first( L"1" );
    const wchar_t* second = L"12";
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest12W
BOOST_AUTO_TEST_CASE( StringNotEqualTest12W )
{
    WideString first( L"123" );
    const wchar_t* second = L"123";
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}


// --run_test=StringTests/StringNotEqualTest13W
BOOST_AUTO_TEST_CASE( StringNotEqualTest13W )
{
    const wchar_t* first = nullptr;
    WideString second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest14W
BOOST_AUTO_TEST_CASE( StringNotEqualTest14W )
{
    const wchar_t* first = L"1";
    WideString second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest15W
BOOST_AUTO_TEST_CASE( StringNotEqualTest15W )
{
    const wchar_t* first = nullptr;
    WideString second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest16W
BOOST_AUTO_TEST_CASE( StringNotEqualTest16W )
{
    const wchar_t* first = L"12";
    WideString second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest17W
BOOST_AUTO_TEST_CASE( StringNotEqualTest17W )
{
    const wchar_t* first = L"1";
    WideString second( L"12" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest18W
BOOST_AUTO_TEST_CASE( StringNotEqualTest18W )
{
    const wchar_t* first = L"123";
    WideString second( L"123" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest19W
BOOST_AUTO_TEST_CASE( StringNotEqualTest19W )
{
    std::wstring first;
    WideString second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest20W
BOOST_AUTO_TEST_CASE( StringNotEqualTest20W )
{
    std::wstring first( L"1" );
    WideString second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest21W
BOOST_AUTO_TEST_CASE( StringNotEqualTest21W )
{
    std::wstring first;
    WideString second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest22W
BOOST_AUTO_TEST_CASE( StringNotEqualTest22W )
{
    std::wstring first( L"12" );
    WideString second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest23W
BOOST_AUTO_TEST_CASE( StringNotEqualTest23W )
{
    std::wstring first( L"1" );
    WideString second( L"12" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest24W
BOOST_AUTO_TEST_CASE( StringNotEqualTest24W )
{
    std::wstring first( L"123" );
    WideString second( L"123" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest25W
BOOST_AUTO_TEST_CASE( StringNotEqualTest25W )
{
    WideString first;
    std::wstring second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest26W
BOOST_AUTO_TEST_CASE( StringNotEqualTest26W )
{
    WideString first( L"1" );
    std::wstring second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest27W
BOOST_AUTO_TEST_CASE( StringNotEqualTest27W )
{
    WideString first;
    std::wstring second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest28W
BOOST_AUTO_TEST_CASE( StringNotEqualTest28W )
{
    WideString first( L"12" );
    std::wstring second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest29W
BOOST_AUTO_TEST_CASE( StringNotEqualTest29W )
{
    WideString first( L"1" );
    std::wstring second( L"12" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest30W
BOOST_AUTO_TEST_CASE( StringNotEqualTest30W )
{
    WideString first( L"123" );
    std::wstring second( L"123" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}


// --run_test=StringTests/StringNotEqualTest31W
BOOST_AUTO_TEST_CASE( StringNotEqualTest31W )
{
    std::wstring_view first;
    WideString second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest32W
BOOST_AUTO_TEST_CASE( StringNotEqualTest32W )
{
    std::wstring_view first( L"1" );
    WideString second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest33W
BOOST_AUTO_TEST_CASE( StringNotEqualTest33W )
{
    std::wstring_view first;
    WideString second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest34W
BOOST_AUTO_TEST_CASE( StringNotEqualTest34W )
{
    std::wstring_view first( L"12" );
    WideString second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest35W
BOOST_AUTO_TEST_CASE( StringNotEqualTest35W )
{
    std::wstring_view first( L"1" );
    WideString second( L"12" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest36W
BOOST_AUTO_TEST_CASE( StringNotEqualTest36W )
{
    std::wstring_view first( L"123" );
    WideString second( L"123" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest37W
BOOST_AUTO_TEST_CASE( StringNotEqualTest37W )
{
    WideString first;
    std::wstring_view second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}

// --run_test=StringTests/StringNotEqualTest38W
BOOST_AUTO_TEST_CASE( StringNotEqualTest38W )
{
    WideString first( L"1" );
    std::wstring_view second;
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest39W
BOOST_AUTO_TEST_CASE( StringNotEqualTest39W )
{
    WideString first;
    std::wstring_view second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest40W
BOOST_AUTO_TEST_CASE( StringNotEqualTest40W )
{
    WideString first( L"12" );
    std::wstring_view second( L"1" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest41W
BOOST_AUTO_TEST_CASE( StringNotEqualTest41W )
{
    WideString first( L"1" );
    std::wstring_view second( L"12" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual );
}

// --run_test=StringTests/StringNotEqualTest42W
BOOST_AUTO_TEST_CASE( StringNotEqualTest42W )
{
    WideString first( L"123" );
    std::wstring_view second( L"123" );
    bool notEqual = first != second;
    BOOST_TEST( notEqual == false );
}


// --run_test=StringTests/StringLessOrEqualTest1W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest1W )
{
    WideString first;
    WideString second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest2W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest2W )
{
    WideString first( L"1" );
    WideString second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest3W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest3W )
{
    WideString first;
    WideString second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest4W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest4W )
{
    WideString first( L"12" );
    WideString second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest5W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest5W )
{
    WideString first( L"1" );
    WideString second( L"12" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest6W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest6W )
{
    WideString first( L"123" );
    WideString second( L"123" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}


// --run_test=StringTests/StringLessOrEqualTest7W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest7W )
{
    const wchar_t* first = nullptr;
    WideString second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest8W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest8W )
{
    const wchar_t* first = L"1";
    WideString second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest9W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest9W )
{
    const wchar_t* first = nullptr;
    WideString second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest10W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest10W )
{
    const wchar_t* first = L"12";
    WideString second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest11W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest11W )
{
    const wchar_t* first = L"1";
    WideString second( L"12" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest12W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest12W )
{
    const wchar_t* first = L"123";
    WideString second( L"123" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest13W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest13W )
{
    WideString first;
    const wchar_t* second = nullptr;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest14W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest14W )
{
    WideString first( L"1" );
    const wchar_t* second = nullptr;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest15W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest15W )
{
    WideString first;
    const wchar_t* second = L"1";
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest16W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest16W )
{
    WideString first( L"12" );
    const wchar_t* second = L"1";
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest17W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest17W )
{
    WideString first( L"1" );
    const wchar_t* second = L"12";
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest18W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest18W )
{
    WideString first( L"123" );
    const wchar_t* second = L"123";
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}


// --run_test=StringTests/StringLessOrEqualTest19W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest19W )
{
    std::wstring first;
    WideString second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest20W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest20W )
{
    std::wstring first( L"1" );
    WideString second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest21W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest21W )
{
    std::wstring first;
    WideString second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest22W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest22W )
{
    std::wstring first( L"12" );
    WideString second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest23W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest23W )
{
    std::wstring first( L"1" );
    WideString second( L"12" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest24W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest24W )
{
    std::wstring first( L"123" );
    WideString second( L"123" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest25W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest25W )
{
    WideString first;
    std::wstring second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest26W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest26W )
{
    WideString first( L"1" );
    std::wstring second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest27W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest27W )
{
    WideString first;
    std::wstring second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest28W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest28W )
{
    WideString first( L"12" );
    std::wstring second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest29W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest29W )
{
    WideString first( L"1" );
    std::wstring second( L"12" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest30W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest30W )
{
    WideString first( L"123" );
    std::wstring second( L"123" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest31W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest31W )
{
    std::wstring_view first;
    WideString second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest32W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest32W )
{
    std::wstring_view first( L"1" );
    WideString second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest33W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest33W )
{
    std::wstring_view first;
    WideString second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest34W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest34W )
{
    std::wstring_view first( L"12" );
    WideString second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest35W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest35W )
{
    std::wstring_view first( L"1" );
    WideString second( L"12" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest36W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest36W )
{
    std::wstring_view first( L"123" );
    WideString second( L"123" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest37W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest37W )
{
    WideString first;
    std::wstring_view second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest38W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest38W )
{
    WideString first( L"1" );
    std::wstring_view second;
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest39W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest39W )
{
    WideString first;
    std::wstring_view second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest40W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest40W )
{
    WideString first( L"12" );
    std::wstring_view second( L"1" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual == false );
}

// --run_test=StringTests/StringLessOrEqualTest41W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest41W )
{
    WideString first( L"1" );
    std::wstring_view second( L"12" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessOrEqualTest42W
BOOST_AUTO_TEST_CASE( StringLessOrEqualTest42W )
{
    WideString first( L"123" );
    std::wstring_view second( L"123" );
    bool lessOrEqual = first <= second;
    BOOST_TEST( lessOrEqual );
}

// --run_test=StringTests/StringLessTest1W
BOOST_AUTO_TEST_CASE( StringLessTest1W )
{
    WideString first;
    WideString second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest2W
BOOST_AUTO_TEST_CASE( StringLessTest2W )
{
    WideString first( L"1" );
    WideString second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest3W
BOOST_AUTO_TEST_CASE( StringLessTest3W )
{
    WideString first;
    WideString second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest4W
BOOST_AUTO_TEST_CASE( StringLessTest4W )
{
    WideString first( L"12" );
    WideString second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest5W
BOOST_AUTO_TEST_CASE( StringLessTest5W )
{
    WideString first( L"1" );
    WideString second( L"12" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest6W
BOOST_AUTO_TEST_CASE( StringLessTest6W )
{
    WideString first( L"123" );
    WideString second( L"123" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}


// --run_test=StringTests/StringLessTest7W
BOOST_AUTO_TEST_CASE( StringLessTest7W )
{
    const wchar_t* first = nullptr;
    WideString second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest8W
BOOST_AUTO_TEST_CASE( StringLessTest8W )
{
    const wchar_t* first = L"1";
    WideString second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest9W
BOOST_AUTO_TEST_CASE( StringLessTest9W )
{
    const wchar_t* first = nullptr;
    WideString second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest10W
BOOST_AUTO_TEST_CASE( StringLessTest10W )
{
    const wchar_t* first = L"12";
    WideString second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest11W
BOOST_AUTO_TEST_CASE( StringLessTest11W )
{
    const wchar_t* first = L"1";
    WideString second( L"12" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest12W
BOOST_AUTO_TEST_CASE( StringLessTest12W )
{
    const wchar_t* first = L"123";
    WideString second( L"123" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest13W
BOOST_AUTO_TEST_CASE( StringLessTest13W )
{
    WideString first;
    const wchar_t* second = nullptr;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest14W
BOOST_AUTO_TEST_CASE( StringLessTest14W )
{
    WideString first( L"1" );
    const wchar_t* second = nullptr;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest15W
BOOST_AUTO_TEST_CASE( StringLessTest15W )
{
    WideString first;
    const wchar_t* second = L"1";
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest16W
BOOST_AUTO_TEST_CASE( StringLessTest16W )
{
    WideString first( L"12" );
    const wchar_t* second = L"1";
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest17W
BOOST_AUTO_TEST_CASE( StringLessTest17W )
{
    WideString first( L"1" );
    const wchar_t* second = L"12";
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest18W
BOOST_AUTO_TEST_CASE( StringLessTest18W )
{
    WideString first( L"123" );
    const wchar_t* second = L"123";
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}


// --run_test=StringTests/StringLessTest19W
BOOST_AUTO_TEST_CASE( StringLessTest19W )
{
    std::wstring first;
    WideString second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest20W
BOOST_AUTO_TEST_CASE( StringLessTest20W )
{
    std::wstring first( L"1" );
    WideString second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest21W
BOOST_AUTO_TEST_CASE( StringLessTest21W )
{
    std::wstring first;
    WideString second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest22W
BOOST_AUTO_TEST_CASE( StringLessTest22W )
{
    std::wstring first( L"12" );
    WideString second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest23W
BOOST_AUTO_TEST_CASE( StringLessTest23W )
{
    std::wstring first( L"1" );
    WideString second( L"12" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest24W
BOOST_AUTO_TEST_CASE( StringLessTest24W )
{
    std::wstring first( L"123" );
    WideString second( L"123" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest25W
BOOST_AUTO_TEST_CASE( StringLessTest25W )
{
    WideString first;
    std::wstring second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest26W
BOOST_AUTO_TEST_CASE( StringLessTest26W )
{
    WideString first( L"1" );
    std::wstring second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest27W
BOOST_AUTO_TEST_CASE( StringLessTest27W )
{
    WideString first;
    std::wstring second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest28W
BOOST_AUTO_TEST_CASE( StringLessTest28W )
{
    WideString first( L"12" );
    std::wstring second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest29W
BOOST_AUTO_TEST_CASE( StringLessTest29W )
{
    WideString first( L"1" );
    std::wstring second( L"12" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest30W
BOOST_AUTO_TEST_CASE( StringLessTest30W )
{
    WideString first( L"123" );
    std::wstring second( L"123" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest31W
BOOST_AUTO_TEST_CASE( StringLessTest31W )
{
    std::wstring_view first;
    WideString second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest32W
BOOST_AUTO_TEST_CASE( StringLessTest32W )
{
    std::wstring_view first( L"1" );
    WideString second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest33W
BOOST_AUTO_TEST_CASE( StringLessTest33W )
{
    std::wstring_view first;
    WideString second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest34W
BOOST_AUTO_TEST_CASE( StringLessTest34W )
{
    std::wstring_view first( L"12" );
    WideString second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest35W
BOOST_AUTO_TEST_CASE( StringLessTest35W )
{
    std::wstring_view first( L"1" );
    WideString second( L"12" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest36W
BOOST_AUTO_TEST_CASE( StringLessTest36W )
{
    std::wstring_view first( L"123" );
    WideString second( L"123" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest37W
BOOST_AUTO_TEST_CASE( StringLessTest37W )
{
    WideString first;
    std::wstring_view second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest38W
BOOST_AUTO_TEST_CASE( StringLessTest38W )
{
    WideString first( L"1" );
    std::wstring_view second;
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest39W
BOOST_AUTO_TEST_CASE( StringLessTest39W )
{
    WideString first;
    std::wstring_view second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest40W
BOOST_AUTO_TEST_CASE( StringLessTest40W )
{
    WideString first( L"12" );
    std::wstring_view second( L"1" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringLessTest41W
BOOST_AUTO_TEST_CASE( StringLessTest41W )
{
    WideString first( L"1" );
    std::wstring_view second( L"12" );
    bool isLess = first < second;
    BOOST_TEST( isLess );
}

// --run_test=StringTests/StringLessTest42W
BOOST_AUTO_TEST_CASE( StringLessTest42W )
{
    WideString first( L"123" );
    std::wstring_view second( L"123" );
    bool isLess = first < second;
    BOOST_TEST( isLess == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest1W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest1W )
{
    WideString first;
    WideString second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest2W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest2W )
{
    WideString first( L"1" );
    WideString second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest3W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest3W )
{
    WideString first;
    WideString second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest4W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest4W )
{
    WideString first( L"12" );
    WideString second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest5W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest5W )
{
    WideString first( L"1" );
    WideString second( L"12" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest6W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest6W )
{
    WideString first( L"123" );
    WideString second( L"123" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}


// --run_test=StringTests/StringGreaterOrEqualTest7W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest7W )
{
    const wchar_t* first = nullptr;
    WideString second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest8W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest8W )
{
    const wchar_t* first = L"1";
    WideString second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest9W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest9W )
{
    const wchar_t* first = nullptr;
    WideString second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest10W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest10W )
{
    const wchar_t* first = L"12";
    WideString second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest11W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest11W )
{
    const wchar_t* first = L"1";
    WideString second( L"12" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest12W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest12W )
{
    const wchar_t* first = L"123";
    WideString second( L"123" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest13W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest13W )
{
    WideString first;
    const wchar_t* second = nullptr;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest14W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest14W )
{
    WideString first( L"1" );
    const wchar_t* second = nullptr;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual  );
}

// --run_test=StringTests/StringGreaterOrEqualTest15W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest15W )
{
    WideString first;
    const wchar_t* second = L"1";
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest16W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest16W )
{
    WideString first( L"12" );
    const wchar_t* second = L"1";
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest17W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest17W )
{
    WideString first( L"1" );
    const wchar_t* second = L"12";
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest18W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest18W )
{
    WideString first( L"123" );
    const wchar_t* second = L"123";
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}


// --run_test=StringTests/StringGreaterOrEqualTest19W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest19W )
{
    std::wstring first;
    WideString second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest20W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest20W )
{
    std::wstring first( L"1" );
    WideString second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest21W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest21W )
{
    std::wstring first;
    WideString second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest22W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest22W )
{
    std::wstring first( L"12" );
    WideString second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest23W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest23W )
{
    std::wstring first( L"1" );
    WideString second( L"12" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest24W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest24W )
{
    std::wstring first( L"123" );
    WideString second( L"123" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest25W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest25W )
{
    WideString first;
    std::wstring second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest26W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest26W )
{
    WideString first( L"1" );
    std::wstring second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest27W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest27W )
{
    WideString first;
    std::wstring second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest28W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest28W )
{
    WideString first( L"12" );
    std::wstring second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest29W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest29W )
{
    WideString first( L"1" );
    std::wstring second( L"12" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest30W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest30W )
{
    WideString first( L"123" );
    std::wstring second( L"123" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest31W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest31W )
{
    std::wstring_view first;
    WideString second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest32W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest32W )
{
    std::wstring_view first( L"1" );
    WideString second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest33W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest33W )
{
    std::wstring_view first;
    WideString second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest34W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest34W )
{
    std::wstring_view first( L"12" );
    WideString second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest35W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest35W )
{
    std::wstring_view first( L"1" );
    WideString second( L"12" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest36W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest36W )
{
    std::wstring_view first( L"123" );
    WideString second( L"123" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest37W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest37W )
{
    WideString first;
    std::wstring_view second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest38W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest38W )
{
    WideString first( L"1" );
    std::wstring_view second;
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest39W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest39W )
{
    WideString first;
    std::wstring_view second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest40W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest40W )
{
    WideString first( L"12" );
    std::wstring_view second( L"1" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterOrEqualTest41W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest41W )
{
    WideString first( L"1" );
    std::wstring_view second( L"12" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual == false );
}

// --run_test=StringTests/StringGreaterOrEqualTest42W
BOOST_AUTO_TEST_CASE( StringGreaterOrEqualTest42W )
{
    WideString first( L"123" );
    std::wstring_view second( L"123" );
    bool greaterOrEqual = first >= second;
    BOOST_TEST( greaterOrEqual );
}

// --run_test=StringTests/StringGreaterTest1W
BOOST_AUTO_TEST_CASE( StringGreaterTest1W )
{
    WideString first;
    WideString second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest2W
BOOST_AUTO_TEST_CASE( StringGreaterTest2W )
{
    WideString first( L"1" );
    WideString second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest3W
BOOST_AUTO_TEST_CASE( StringGreaterTest3W )
{
    WideString first;
    WideString second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest4W
BOOST_AUTO_TEST_CASE( StringGreaterTest4W )
{
    WideString first( L"12" );
    WideString second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest5W
BOOST_AUTO_TEST_CASE( StringGreaterTest5W )
{
    WideString first( L"1" );
    WideString second( L"12" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest6W
BOOST_AUTO_TEST_CASE( StringGreaterTest6W )
{
    WideString first( L"123" );
    WideString second( L"123" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}


// --run_test=StringTests/StringGreaterTest7W
BOOST_AUTO_TEST_CASE( StringGreaterTest7W )
{
    const wchar_t* first = nullptr;
    WideString second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest8W
BOOST_AUTO_TEST_CASE( StringGreaterTest8W )
{
    const wchar_t* first = L"1";
    WideString second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest9W
BOOST_AUTO_TEST_CASE( StringGreaterTest9W )
{
    const wchar_t* first = nullptr;
    WideString second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest10W
BOOST_AUTO_TEST_CASE( StringGreaterTest10W )
{
    const wchar_t* first = L"12";
    WideString second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest11W
BOOST_AUTO_TEST_CASE( StringGreaterTest11W )
{
    const wchar_t* first = L"1";
    WideString second( L"12" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest12W
BOOST_AUTO_TEST_CASE( StringGreaterTest12W )
{
    const wchar_t* first = L"123";
    WideString second( L"123" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest13W
BOOST_AUTO_TEST_CASE( StringGreaterTest13W )
{
    WideString first;
    const wchar_t* second = nullptr;
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest14W
BOOST_AUTO_TEST_CASE( StringGreaterTest14W )
{
    WideString first( L"1" );
    const wchar_t* second = nullptr;
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest15W
BOOST_AUTO_TEST_CASE( StringGreaterTest15W )
{
    WideString first;
    const wchar_t* second = L"1";
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest16W
BOOST_AUTO_TEST_CASE( StringGreaterTest16W )
{
    WideString first( L"12" );
    const wchar_t* second = L"1";
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest17W
BOOST_AUTO_TEST_CASE( StringGreaterTest17W )
{
    WideString first( L"1" );
    const wchar_t* second = L"12";
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest18W
BOOST_AUTO_TEST_CASE( StringGreaterTest18W )
{
    WideString first( L"123" );
    const wchar_t* second = L"123";
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}


// --run_test=StringTests/StringGreaterTest19W
BOOST_AUTO_TEST_CASE( StringGreaterTest19W )
{
    std::wstring first;
    WideString second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest20W
BOOST_AUTO_TEST_CASE( StringGreaterTest20W )
{
    std::wstring first( L"1" );
    WideString second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest21W
BOOST_AUTO_TEST_CASE( StringGreaterTest21W )
{
    std::wstring first;
    WideString second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest22W
BOOST_AUTO_TEST_CASE( StringGreaterTest22W )
{
    std::wstring first( L"12" );
    WideString second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest23W
BOOST_AUTO_TEST_CASE( StringGreaterTest23W )
{
    std::wstring first( L"1" );
    WideString second( L"12" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest24W
BOOST_AUTO_TEST_CASE( StringGreaterTest24W )
{
    std::wstring first( L"123" );
    WideString second( L"123" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest25W
BOOST_AUTO_TEST_CASE( StringGreaterTest25W )
{
    WideString first;
    std::wstring second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest26W
BOOST_AUTO_TEST_CASE( StringGreaterTest26W )
{
    WideString first( L"1" );
    std::wstring second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest27W
BOOST_AUTO_TEST_CASE( StringGreaterTest27W )
{
    WideString first;
    std::wstring second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest28W
BOOST_AUTO_TEST_CASE( StringGreaterTest28W )
{
    WideString first( L"12" );
    std::wstring second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest29W
BOOST_AUTO_TEST_CASE( StringGreaterTest29W )
{
    WideString first( L"1" );
    std::wstring second( L"12" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest30W
BOOST_AUTO_TEST_CASE( StringGreaterTest30W )
{
    WideString first( L"123" );
    std::wstring second( L"123" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest31W
BOOST_AUTO_TEST_CASE( StringGreaterTest31W )
{
    std::wstring_view first;
    WideString second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest32W
BOOST_AUTO_TEST_CASE( StringGreaterTest32W )
{
    std::wstring_view first( L"1" );
    WideString second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest33W
BOOST_AUTO_TEST_CASE( StringGreaterTest33W )
{
    std::wstring_view first;
    WideString second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest34W
BOOST_AUTO_TEST_CASE( StringGreaterTest34W )
{
    std::wstring_view first( L"12" );
    WideString second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest35W
BOOST_AUTO_TEST_CASE( StringGreaterTest35W )
{
    std::wstring_view first( L"1" );
    WideString second( L"12" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest36W
BOOST_AUTO_TEST_CASE( StringGreaterTest36W )
{
    std::wstring_view first( L"123" );
    WideString second( L"123" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest37W
BOOST_AUTO_TEST_CASE( StringGreaterTest37W )
{
    WideString first;
    std::wstring_view second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest38W
BOOST_AUTO_TEST_CASE( StringGreaterTest38W )
{
    WideString first( L"1" );
    std::wstring_view second;
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest39W
BOOST_AUTO_TEST_CASE( StringGreaterTest39W )
{
    WideString first;
    std::wstring_view second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest40W
BOOST_AUTO_TEST_CASE( StringGreaterTest40W )
{
    WideString first( L"12" );
    std::wstring_view second( L"1" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater );
}

// --run_test=StringTests/StringGreaterTest41W
BOOST_AUTO_TEST_CASE( StringGreaterTest41W )
{
    WideString first( L"1" );
    std::wstring_view second( L"12" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
}

// --run_test=StringTests/StringGreaterTest42W
BOOST_AUTO_TEST_CASE( StringGreaterTest42W )
{
    WideString first( L"123" );
    std::wstring_view second( L"123" );
    bool isGreater = first > second;
    BOOST_TEST( isGreater == false );
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


// --run_test=StringTests/StringReplaceTest1W
BOOST_AUTO_TEST_CASE( StringReplaceTest1W )
{
    WideString expectedStr( L"4123" );
    WideString str( L"123" );
    str.Replace( 0, 0, L"4", 1 );
    
    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest2W
BOOST_AUTO_TEST_CASE( StringReplaceTest2W )
{
    WideString expectedStr( L"1423" );
    WideString str( L"123" );
    str.Replace( 1, 0, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest3W
BOOST_AUTO_TEST_CASE( StringReplaceTest3W )
{
    WideString expectedStr( L"1243" );
    WideString str( L"123" );
    str.Replace( 2, 0, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest4W
BOOST_AUTO_TEST_CASE( StringReplaceTest4W )
{
    WideString expectedStr( L"1234" );
    WideString str( L"123" );
    str.Replace( 3, 0, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest5W
BOOST_AUTO_TEST_CASE( StringReplaceTest5W )
{
    WideString expectedStr( L"123 4" );
    WideString str( L"123" );
    str.Replace( 4, 0, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}


// --run_test=StringTests/StringReplaceTest6W
BOOST_AUTO_TEST_CASE( StringReplaceTest6W )
{
    WideString expectedStr1( L"4123" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 0, 0, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest7W
BOOST_AUTO_TEST_CASE( StringReplaceTest7W )
{
    WideString expectedStr1( L"1423" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 1, 0, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest8W
BOOST_AUTO_TEST_CASE( StringReplaceTest8W )
{
    WideString expectedStr1( L"1243" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 2, 0, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest9W
BOOST_AUTO_TEST_CASE( StringReplaceTest9W )
{
    WideString expectedStr1( L"1234" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 3, 0, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest10W
BOOST_AUTO_TEST_CASE( StringReplaceTest10W )
{
    WideString expectedStr1( L"123 4" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 4, 0, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest11W
BOOST_AUTO_TEST_CASE( StringReplaceTest11W )
{
    WideString expectedStr( L"423" );
    WideString str( L"123" );
    str.Replace( 0, 1, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}


// --run_test=StringTests/StringReplaceTest12W
BOOST_AUTO_TEST_CASE( StringReplaceTest12W )
{
    WideString expectedStr( L"143" );
    WideString str( L"123" );
    str.Replace( 1, 1, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest13W
BOOST_AUTO_TEST_CASE( StringReplaceTest13W )
{
    WideString expectedStr( L"124" );
    WideString str( L"123" );
    str.Replace( 2, 1, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest14W
BOOST_AUTO_TEST_CASE( StringReplaceTest14W )
{
    WideString expectedStr( L"1234" );
    WideString str( L"123" );
    str.Replace( 3, 1, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest15W
BOOST_AUTO_TEST_CASE( StringReplaceTest15W )
{
    WideString expectedStr( L"123 4" );
    WideString str( L"123" );
    str.Replace( 4, 1, L"4", 1 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest16W
BOOST_AUTO_TEST_CASE( StringReplaceTest16W )
{
    WideString expectedStr1( L"423" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 0, 1, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest17W
BOOST_AUTO_TEST_CASE( StringReplaceTest17W )
{
    WideString expectedStr1( L"143" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 1, 1, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest18W
BOOST_AUTO_TEST_CASE( StringReplaceTest18W )
{
    WideString expectedStr1( L"124" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 2, 1, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest19W
BOOST_AUTO_TEST_CASE( StringReplaceTest19W )
{
    WideString expectedStr1( L"1234" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 3, 1, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest20W
BOOST_AUTO_TEST_CASE( StringReplaceTest20W )
{
    WideString expectedStr1( L"123 4" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 4, 1, L"4", 1 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );
    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest21W
BOOST_AUTO_TEST_CASE( StringReplaceTest21W )
{
    WideString expectedStr( L"4523" );
    WideString str( L"123" );
    str.Replace( 0, 1, L"45", 2 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest22W
BOOST_AUTO_TEST_CASE( StringReplaceTest22W )
{
    WideString expectedStr( L"1453" );
    WideString str( L"123" );
    str.Replace( 1, 1, L"45", 2 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest23W
BOOST_AUTO_TEST_CASE( StringReplaceTest23W )
{
    WideString expectedStr( L"1245" );
    WideString str( L"123" );
    str.Replace( 2, 1, L"45", 2 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest24W
BOOST_AUTO_TEST_CASE( StringReplaceTest24W )
{
    WideString expectedStr( L"12345" );
    WideString str( L"123" );
    str.Replace( 3, 1, L"45", 2 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest25W
BOOST_AUTO_TEST_CASE( StringReplaceTest25W )
{
    WideString expectedStr( L"123 45" );
    WideString str( L"123" );
    str.Replace( 4, 1, L"45", 2 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest26W
BOOST_AUTO_TEST_CASE( StringReplaceTest26W )
{
    WideString expectedStr1( L"4523" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 0, 1, L"45", 2 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest27W
BOOST_AUTO_TEST_CASE( StringReplaceTest27W )
{
    WideString expectedStr1( L"1453" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 1, 1, L"45", 2 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest28W
BOOST_AUTO_TEST_CASE( StringReplaceTest28W )
{
    WideString expectedStr1( L"1245" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 2, 1, L"45", 2 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest29W
BOOST_AUTO_TEST_CASE( StringReplaceTest29W )
{
    WideString expectedStr1( L"12345" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 3, 1, L"45", 2 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest30W
BOOST_AUTO_TEST_CASE( StringReplaceTest30W )
{
    WideString expectedStr1( L"123 45" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 4, 1, L"45", 2 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest31W
BOOST_AUTO_TEST_CASE( StringReplaceTest31W )
{
    WideString expectedStr( L"23" );
    WideString str( L"123" );
    str.Replace( 0, 1, L"", 0 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest32W
BOOST_AUTO_TEST_CASE( StringReplaceTest32W )
{
    WideString expectedStr( L"13" );
    WideString str( L"123" );
    str.Replace( 1, 1, L"", 0 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest33W
BOOST_AUTO_TEST_CASE( StringReplaceTest33W )
{
    WideString expectedStr( L"12" );
    WideString str( L"123" );
    str.Replace( 2, 1, L"", 0 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest34W
BOOST_AUTO_TEST_CASE( StringReplaceTest34W )
{
    WideString expectedStr( L"123" );
    WideString str( L"123" );
    str.Replace( 3, 1, L"", 0 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}


// --run_test=StringTests/StringReplaceTest35W
BOOST_AUTO_TEST_CASE( StringReplaceTest35W )
{
    WideString expectedStr( L"123" );
    WideString str( L"123" );
    str.Replace( 4, 1, L"", 0 );

    bool equal = expectedStr == str;

    BOOST_TEST( equal );
}


// --run_test=StringTests/StringReplaceTest36W
BOOST_AUTO_TEST_CASE( StringReplaceTest36W )
{
    WideString expectedStr1( L"23" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 0, 1, L"", 0 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest37W
BOOST_AUTO_TEST_CASE( StringReplaceTest37W )
{
    WideString expectedStr1( L"13" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 1, 1, L"", 0 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest38W
BOOST_AUTO_TEST_CASE( StringReplaceTest38W )
{
    WideString expectedStr1( L"12" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 2, 1, L"", 0 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest39W
BOOST_AUTO_TEST_CASE( StringReplaceTest39W )
{
    WideString expectedStr1( L"123" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 3, 1, L"", 0 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringReplaceTest40W
BOOST_AUTO_TEST_CASE( StringReplaceTest40W )
{
    WideString expectedStr1( L"123" );
    WideString expectedStr2( L"123" );
    WideString str1( L"123" );
    WideString str2 = str1;
    str1.Replace( 4, 1, L"", 0 );

    bool equal = expectedStr1 == str1;
    BOOST_TEST( equal );

    equal = expectedStr2 == str2;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfTest1A
BOOST_AUTO_TEST_CASE( StringIndexOfTest1A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    StringType::value_type lookFor{ 'B' };
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest1W
BOOST_AUTO_TEST_CASE( StringIndexOfTest1W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    StringType::value_type lookFor{ L'B' };
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest2A
BOOST_AUTO_TEST_CASE( StringIndexOfTest2A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    StringType lookFor{ "BC" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest2W
BOOST_AUTO_TEST_CASE( StringIndexOfTest2W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    StringType lookFor{ L"BC" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest3A
BOOST_AUTO_TEST_CASE( StringIndexOfTest3A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    std::string_view lookFor{ "BC" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest3W
BOOST_AUTO_TEST_CASE( StringIndexOfTest3W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF" };
    std::wstring_view lookFor{ L"BC" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest4A
BOOST_AUTO_TEST_CASE( StringIndexOfTest4A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    std::string lookFor{ "BC" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest4W
BOOST_AUTO_TEST_CASE( StringIndexOfTest4W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    std::wstring lookFor{ L"BC" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest5A
BOOST_AUTO_TEST_CASE( StringIndexOfTest5A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    const StringType::value_type* lookFor{ "BC" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest5W
BOOST_AUTO_TEST_CASE( StringIndexOfTest5W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    const StringType::value_type* lookFor{ L"BC" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfTest6A
BOOST_AUTO_TEST_CASE( StringIndexOfTest6A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    StringType::value_type lookFor{ 'B' };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 8;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest6W
BOOST_AUTO_TEST_CASE( StringIndexOfTest6W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    StringType::value_type lookFor{ L'B' };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 8;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest7A
BOOST_AUTO_TEST_CASE( StringIndexOfTest7A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    StringType lookFor{ "BC" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest7W
BOOST_AUTO_TEST_CASE( StringIndexOfTest7W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    StringType lookFor{ L"BC" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest8A
BOOST_AUTO_TEST_CASE( StringIndexOfTest8A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    std::string_view lookFor{ "BC" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest8W
BOOST_AUTO_TEST_CASE( StringIndexOfTest8W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    std::wstring_view lookFor{ L"BC" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest9A
BOOST_AUTO_TEST_CASE( StringIndexOfTest9A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    std::string lookFor{ "BC" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest9W
BOOST_AUTO_TEST_CASE( StringIndexOfTest9W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    std::wstring lookFor{ L"BC" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest10A
BOOST_AUTO_TEST_CASE( StringIndexOfTest10A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    const StringType::value_type* lookFor{ "BC" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfTest10W
BOOST_AUTO_TEST_CASE( StringIndexOfTest10W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    const StringType::value_type* lookFor{ L"BC" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfTest1A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest1A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    StringType::value_type lookFor{ 'b' };
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest1W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest1W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    StringType::value_type lookFor{ L'b' };
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest2A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest2A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    StringType lookFor{ "bc" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest2W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest2W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    StringType lookFor{ L"bc" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest3A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest3A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    std::string_view lookFor{ "bc" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest3W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest3W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    std::wstring_view lookFor{ L"bc" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest4A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest4A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    std::string lookFor{ "bc" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest4W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest4W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    std::wstring lookFor{ L"bc" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest5A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest5A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCDDEEFF" };
    const StringType::value_type* lookFor{ "bc" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest5W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest5W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCDDEEFF" };
    const StringType::value_type* lookFor{ L"bc" };
    StringType::size_type expectedIndex = 3;

    auto index = text.IIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfTest6A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest6A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    StringType::value_type lookFor{ 'b' };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 8;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest6W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest6W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    StringType::value_type lookFor{ L'b' };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 8;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest7A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest7A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    StringType lookFor{ "bc" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest7W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest7W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    StringType lookFor{ L"bc" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest8A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest8A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    std::string_view lookFor{ "bc" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest8W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest8W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    std::wstring_view lookFor{ L"bc" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest9A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest9A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    std::string lookFor{ "bc" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest9W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest9W )
{
    using StringType = WideString;
    StringType text{ L"AABBCCAABBCC" };
    std::wstring lookFor{ L"bc" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest10A
BOOST_AUTO_TEST_CASE( StringIIndexOfTest10A )
{
    using StringType = AnsiString;
    StringType text{ "AABBCCAABBCC" };
    const StringType::value_type* lookFor{ "bc" };
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfTest10W
BOOST_AUTO_TEST_CASE( StringIIndexOfTest10W )
{
    using StringType = WideString;
    StringType text{L"AABBCCAABBCC"};
    const StringType::value_type* lookFor{L"bc"};
    StringType::size_type startAtIndex = 6;
    StringType::size_type expectedIndex = 9;

    auto index = text.IIndexOf( lookFor, startAtIndex );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest1A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest1A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    StringType lookFor{"BC"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest1W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest1W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    StringType lookFor{L"BC"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest2A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest2A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"BC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest2W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest2W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"BC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest3A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest3A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest3W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest3W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest4A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest4A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{"BC"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest4W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest4W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{L"BC"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest5A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest5A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"BC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest5W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest5W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"BC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest6A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest6A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest6W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest6W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest7A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest7A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor{"BC"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest7W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest7W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor{L"BC"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest8A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest8A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"BC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest8W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest8W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"BC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest9A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest9A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest9W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest9W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}



// --run_test=StringTests/StringIndexOfAnyOfTest10A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest10A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor{"BC"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest10W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest10W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor{L"BC"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest11A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest11A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"BC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest11W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest11W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"BC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyOfTest12A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest12A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyOfTest12W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyOfTest12W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest1A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest1A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    StringType lookFor{"bc"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest1W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest1W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    StringType lookFor{L"bc"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest2A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest2A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"bc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest2W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest2W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"bc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest3A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest3A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest3W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest3W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest4A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest4A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{"bc"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest4W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest4W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{L"bc"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest5A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest5A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"bc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest5W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest5W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"bc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest6A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest6A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest6W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest6W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest7A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest7A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor{"bc"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest7W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest7W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor{L"bc"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest8A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest8A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"bc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest8W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest8W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"bc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest9A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest9A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest9W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest9W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}



// --run_test=StringTests/StringIIndexOfAnyOfTest10A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest10A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor{"bc"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest10W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest10W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor{L"bc"};
    StringType::size_type expectedIndex = 2;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest11A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest11A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"bc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest11W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest11W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"bc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyOfTest12A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest12A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyOfTest12W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyOfTest12W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest1A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest1A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    StringType lookFor{"AB"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyButTest1W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest1W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    StringType lookFor{L"AB"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest2A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest2A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest2W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest2W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest3A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest3A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    StringType lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest3W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest3W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    StringType lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyButTest4A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest4A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor{"AB"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyButTest4W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest4W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor{L"AB"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest5A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest5A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest5W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest5W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest6A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest6A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest6W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest6W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyButTest7A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest7A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor{"AB"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyButTest7W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest7W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor{L"AB"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest8A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest8A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest8W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest8W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest9A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest9A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest9W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest9W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyButTest10A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest10A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{"AB"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIndexOfAnyButTest10W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest10W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{L"AB"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest11A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest11A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest11W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest11W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest12A
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest12A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = 0;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIndexOfAnyButTest12W
BOOST_AUTO_TEST_CASE( StringIndexOfAnyButTest12W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = 0;

    auto index = text.IndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest1A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest1A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    StringType lookFor{"ab"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyButTest1W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest1W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    StringType lookFor{L"ab"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest2A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest2A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest2W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest2W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest3A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest3A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    StringType lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest3W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest3W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    StringType lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyButTest4A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest4A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor{"ab"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyButTest4W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest4W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor{L"ab"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest5A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest5A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest5W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest5W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest6A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest6A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest6W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest6W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyButTest7A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest7A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor{"ab"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyButTest7W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest7W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor{L"ab"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest8A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest8A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest8W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest8W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest9A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest9A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest9W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest9W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 0;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyButTest10A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest10A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{"ab"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIIndexOfAnyButTest10W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest10W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{L"ab"};
    StringType::size_type expectedIndex = 4;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest11A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest11A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest11W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest11W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest12A
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest12A )
{
    using StringType = AnsiString;
    StringType text{"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = 0;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringIIndexOfAnyButTest12W
BOOST_AUTO_TEST_CASE( StringIIndexOfAnyButTest12W )
{
    using StringType = WideString;
    StringType text{L"AABBCCDDEEFF"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = 0;

    auto index = text.IIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest1A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest1A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor{"AB"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest1W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest1W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor{L"AB"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest2A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest2A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor{"AABBAABB"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest2W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest2W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor{L"AABBAABB"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest3A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest3A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor{"AABBAABBC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest3W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest3W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor{L"AABBAABBC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest4A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest4A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor{"AC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest4W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest4W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor{L"AC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest5A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest5A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest5W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest5W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest6A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest6A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest6W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest6W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest7A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest7A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest7W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest7W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest8A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest8A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{"AB"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest8W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest8W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{L"AB"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest9A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest9A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{"AABBAABB"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest9W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest9W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{L"AABBAABB"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest10A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest10A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{"AABBAABBC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest10W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest10W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{L"AABBAABBC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest11A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest11A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{"AC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest11W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest11W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{L"AC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest12A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest12A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest12W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest12W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest13A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest13A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest13W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest13W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest14A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest14A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest14W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest14W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest15A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest15A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{"AB"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest15W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest15W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{L"AB"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest16A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest16A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{"AABBAABB"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest16W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest16W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{L"AABBAABB"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest17A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest17A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{"AABBAABBC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest17W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest17W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{L"AABBAABBC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest18A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest18A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{"AC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest18W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest18W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{L"AC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest19A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest19A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest19W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest19W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest20A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest20A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest20W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest20W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest21A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest21A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest21W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest21W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest22A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest22A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{"AB"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest22W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest22W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{L"AB"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest23A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest23A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{"AABBAABB"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest23W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest23W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{L"AABBAABB"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest24A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest24A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{"AABBAABBC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest24W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest24W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{L"AABBAABBC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest25A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest25A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{"AC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest25W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest25W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{L"AC"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest26A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest26A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest26W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest26W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest27A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest27A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest27W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest27W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"AB"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfTest28A
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest28A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfTest28W
BOOST_AUTO_TEST_CASE( StringLastIndexOfTest28W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

/////////////////////////////////////////////////////////////
// --run_test=StringTests/StringILastIndexOfTest1A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest1A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor{"ab"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest1W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest1W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor{L"ab"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest2A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest2A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor{"aabbaabb"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest2W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest2W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor{L"aabbaabb"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest3A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest3A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor{"aabbaabbc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest3W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest3W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor{L"aabbaabbc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest4A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest4A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor{"ac"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest4W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest4W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor{L"ac"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest5A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest5A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest5W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest5W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest6A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest6A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest6W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest6W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest7A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest7A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest7W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest7W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest8A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest8A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{"ab"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest8W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest8W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{L"ab"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest9A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest9A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{"aabbaabb"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest9W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest9W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{L"aabbaabb"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest10A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest10A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{"aabbaabbc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest10W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest10W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{L"aabbaabbc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest11A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest11A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{"ac"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest11W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest11W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor{L"ac"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest12A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest12A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest12W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest12W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest13A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest13A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest13W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest13W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest14A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest14A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest14W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest14W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest15A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest15A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{"ab"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest15W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest15W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{L"ab"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest16A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest16A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{"aabbaabb"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest16W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest16W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{L"aabbaabb"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest17A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest17A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{"aabbaabbc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest17W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest17W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{L"aabbaabbc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest18A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest18A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{"ac"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest18W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest18W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor{L"ac"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest19A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest19A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest19W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest19W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest20A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest20A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest20W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest20W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest21A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest21A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest21W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest21W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest22A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest22A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{"ab"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest22W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest22W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{L"ab"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest23A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest23A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{"aabbaabb"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest23W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest23W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{L"aabbaabb"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest24A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest24A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{"aabbaabbc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest24W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest24W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{L"aabbaabbc"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest25A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest25A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{"ac"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest25W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest25W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{L"ac"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest26A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest26A )
{
    using StringType = AnsiString;
    StringType text{"AABBAABB"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest26W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest26W )
{
    using StringType = WideString;
    StringType text{L"AABBAABB"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest27A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest27A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest27W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest27W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"ab"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfTest28A
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest28A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfTest28W
BOOST_AUTO_TEST_CASE( StringILastIndexOfTest28W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest1A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest1A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest1W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest1W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest2A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest2A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest2W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest2W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest3A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest3A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest3W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest3W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest4A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest4A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest4W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest4W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest5A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest5A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest5W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest5W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest6A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest6A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest6W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest6W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest7A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest7A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest7W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest7W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest8A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest8A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest8W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest8W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest9A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest9A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest9W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest9W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest10A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest10A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest10W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest10W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest11A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest11A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest11W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest11W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest12A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest12A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest12W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest12W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest13A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest13A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest13W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest13W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest14A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest14A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest14W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest14W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest15A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest15A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest15W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest15W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest16A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest16A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest16W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest16W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest17A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest17A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest17W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest17W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest18A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest18A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest18W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest18W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest19A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest19A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest19W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest19W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest20A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest20A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest20W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest20W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest21A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest21A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest21W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest21W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest22A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest22A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest22W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest22W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest23A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest23A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest23W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest23W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyOfTest24A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest24A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyOfTest24W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyOfTest24W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest1A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest1A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest1W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest1W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest2A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest2A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest2W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest2W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest3A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest3A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest3W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest3W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest4A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest4A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest4W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest4W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest5A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest5A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest5W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest5W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest6A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest6A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest6W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest6W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest7A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest7A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest7W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest7W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest8A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest8A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest8W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest8W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest9A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest9A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest9W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest9W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest10A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest10A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest10W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest10W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest11A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest11A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest11W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest11W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest12A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest12A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest12W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest12W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest13A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest13A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest13W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest13W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest14A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest14A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest14W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest14W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest15A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest15A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest15W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest15W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest16A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest16A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest16W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest16W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest17A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest17A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest17W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest17W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest18A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest18A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest18W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest18W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest19A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest19A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest19W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest19W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"9876"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest20A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest20A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest20W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest20W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest21A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest21A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest21W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest21W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"0987"};
    StringType::size_type expectedIndex = 0;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest22A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest22A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest22W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest22W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"0987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest23A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest23A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest23W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest23W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyOfTest24A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest24A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyOfTest24W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyOfTest24W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyOf( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest1A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest1A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest1W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest1W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest2A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest2A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest2W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest2W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest3A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest3A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest3W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest3W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest4A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest4A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest4W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest4W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest5A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest5A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest5W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest5W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest6A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest6A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest6W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest6W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest7A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest7A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest7W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest7W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest8A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest8A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest8W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest8W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest9A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest9A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest9W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest9W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest10A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest10A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest10W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest10W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest11A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest11A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest11W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest11W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest12A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest12A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest12W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest12W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest13A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest13A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest13W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest13W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest14A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest14A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest14W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest14W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest15A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest15A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest15W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest15W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest16A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest16A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest16W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest16W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest17A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest17A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest17W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest17W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest18A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest18A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest18W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest18W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest19A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest19A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest19W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest19W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest20A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest20A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest20W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest20W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest21A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest21A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest21W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest21W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest22A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest22A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest22W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest22W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = 6;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest23A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest23A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest23W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest23W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringLastIndexOfAnyButTest24A
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest24A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringLastIndexOfAnyButTest24W
BOOST_AUTO_TEST_CASE( StringLastIndexOfAnyButTest24W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.LastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest1A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest1A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest1W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest1W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest2A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest2A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest2W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest2W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest3A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest3A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor{"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest3W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest3W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor{L"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest4A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest4A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    StringType lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest4W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest4W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    StringType lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest5A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest5A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest5W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest5W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest6A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest6A )
{
    using StringType = AnsiString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest6W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest6W )
{
    using StringType = WideString;
    StringType text;
    StringType lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest7A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest7A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest7W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest7W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest8A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest8A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest8W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest8W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest9A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest9A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest9W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest9W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest10A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest10A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest10W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest10W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest11A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest11A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest11W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest11W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest12A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest12A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest12W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest12W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest13A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest13A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest13W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest13W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest14A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest14A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest14W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest14W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest15A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest15A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest15W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest15W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest16A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest16A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest16W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest16W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest17A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest17A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest17W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest17W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest18A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest18A )
{
    using StringType = AnsiString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest18W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest18W )
{
    using StringType = WideString;
    StringType text;
    std::basic_string_view<StringType::value_type> lookFor;
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest19A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest19A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest19W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest19W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"9876"};
    StringType::size_type expectedIndex = 5;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest20A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest20A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest20W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest20W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"0123456"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest21A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest21A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest21W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest21W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{L"987"};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest22A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest22A )
{
    using StringType = AnsiString;
    StringType text{"0123456"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest22W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest22W )
{
    using StringType = WideString;
    StringType text{L"0123456"};
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = 6;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest23A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest23A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest23W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest23W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{L"987"};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringILastIndexOfAnyButTest24A
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest24A )
{
    using StringType = AnsiString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}

// --run_test=StringTests/StringILastIndexOfAnyButTest24W
BOOST_AUTO_TEST_CASE( StringILastIndexOfAnyButTest24W )
{
    using StringType = WideString;
    StringType text;
    const StringType::value_type* lookFor{nullptr};
    StringType::size_type expectedIndex = StringType::npos;

    auto index = text.ILastIndexOfAnyBut( lookFor );

    bool equal = expectedIndex == index;
    BOOST_TEST( equal );
}


// --run_test=StringTests/StringOStreamOperatorTest1A
BOOST_AUTO_TEST_CASE( StringOStreamOperatorTest1A )
{
    using StringType = AnsiString;
    StringType text{"The Text"};
    
    std::ostringstream dest;

    dest << text;

    auto result = dest.str( );

    bool equal = text == result;


    BOOST_TEST( equal );
}

// --run_test=StringTests/StringOStreamOperatorTest1W
BOOST_AUTO_TEST_CASE( StringOStreamOperatorTest1W )
{
    using StringType = WideString;
    StringType text{L"The Text"};

    std::wostringstream dest;

    dest << text;

    auto result = dest.str( );

    bool equal = text == result;


    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIStreamOperatorTest1A
BOOST_AUTO_TEST_CASE( StringIStreamOperatorTest1A )
{
    using StringType = AnsiString;
    StringType text{"The Text"};

    std::istringstream source( text.c_str() );

    StringType result;

    source >> result;

    bool equal = result == "The";


    BOOST_TEST( equal );
}


// --run_test=StringTests/StringIStreamOperatorTest1W
BOOST_AUTO_TEST_CASE( StringIStreamOperatorTest1w )
{
    using StringType = WideString;
    StringType text{L"The Text"};

    std::wistringstream source( text.c_str( ) );

    StringType result;

    source >> result;

    bool equal = result == L"The";


    BOOST_TEST( equal );
}

// --run_test=StringTests/SplitTest1A
BOOST_AUTO_TEST_CASE( SplitTest1A )
{
    AnsiString source{ "Debug | Info | Error" };
    AnsiStringView sourceView = source;
    
    auto result1 = source.Split<std::string_view>( '|', true );

    auto count = result1.size( );

    bool equal = count == 3;
    BOOST_TEST( equal );

    auto result2 = sourceView.Split( '|', false );

    count = result2.size( );

    equal = count == 3;
    BOOST_TEST( equal );

}

// --run_test=StringTests/SplitTest1W
BOOST_AUTO_TEST_CASE( SplitTest1W )
{
    WideString source{ L"Debug | Info | Error" };
    WideStringView sourceView = source;
    auto result1 = source.Split<std::wstring_view>( L'|', true );

    auto count = result1.size( );

    bool equal = count == 3;
    BOOST_TEST( equal );

    auto result2 = sourceView.Split( '|', false );

    count = result2.size( );

    equal = count == 3;
    BOOST_TEST( equal );

}

// --run_test=StringTests/SplitTest2A
BOOST_AUTO_TEST_CASE( SplitTest2A )
{
    AnsiString source{ "," };
    AnsiStringView sourceView = source;
    
    auto result1 = source.Split<std::string_view>( ',', true );

    auto count = result1.size( );

    bool equal = count == 0;
    BOOST_TEST( equal );

    auto result2 = sourceView.Split( ',', false );

    count = result2.size( );

    equal = count == 2;
    BOOST_TEST( equal );
}


// --run_test=StringTests/SplitTest3A
BOOST_AUTO_TEST_CASE( SplitTest3A )
{
    AnsiString source { "" };
    AnsiStringView sourceView = source;
    
    auto result1 = source.Split<std::string_view>( ',', true );

    auto count = result1.size( );

    bool equal = count == 0;
    BOOST_TEST( equal );

    auto result2 = sourceView.Split( '|', false );

    count = result2.size( );

    equal = count == 1;
    BOOST_TEST( equal );
}


// --run_test=StringTests/SplitTest4A
BOOST_AUTO_TEST_CASE( SplitTest4A )
{
    AnsiString source { "0" };
    AnsiStringView sourceView = source;
    
    auto result1 = source.Split<std::string_view>( ',', true );

    auto count = result1.size( );

    bool equal = count == 1;
    BOOST_TEST( equal );

    auto result2 = sourceView.Split( '|', false );

    count = result2.size( );

    equal = count == 1;
    BOOST_TEST( equal );
}

// --run_test=StringTests/JoinTest1A
BOOST_AUTO_TEST_CASE( JoinTest1A )
{
	std::vector<int> values{ 1, 2, 3, 4, 5 };
	auto result = AnsiString::Join( ",", values );
	bool equal = result == "1,2,3,4,5";
	BOOST_TEST( equal );
}

// --run_test=StringTests/JoinTest1W
BOOST_AUTO_TEST_CASE( JoinTest1W )
{
    std::vector<int> values{ 1, 2, 3, 4, 5 };
    auto result = WideString::Join( L", ", values );
    bool equal = result == L"1, 2, 3, 4, 5";
    BOOST_TEST( equal );
}

// --run_test=StringTests/JoinTest2A
BOOST_AUTO_TEST_CASE( JoinTest2A )
{
    std::vector<const char*> values{ "100", "2", "3", "4", "0x5" };
    auto result = AnsiString::Join( ",", values );
    bool equal = result == "100,2,3,4,0x5";
    BOOST_TEST( equal );
}



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
    WideString str1{ L" a " };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L" a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest1b
BOOST_AUTO_TEST_CASE( TrimTrailingTest1b )
{
    AnsiString str1{ " a " };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == " a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest1c
BOOST_AUTO_TEST_CASE( TrimTrailingTest1c )
{
    std::wstring_view str1{ L" a " };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L" a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest1d
BOOST_AUTO_TEST_CASE( TrimTrailingTest1d )
{
    std::string_view str1{ " a " };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == " a";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/TrimTrailingTest2a
BOOST_AUTO_TEST_CASE( TrimTrailingTest2a )
{
    WideString str1{ L" " };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest2b
BOOST_AUTO_TEST_CASE( TrimTrailingTest2b )
{
    AnsiString str1{ " " };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest2c
BOOST_AUTO_TEST_CASE( TrimTrailingTest2c )
{
    std::wstring_view str1{ L" " };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest2d
BOOST_AUTO_TEST_CASE( TrimTrailingTest2d )
{
    std::string_view str1{ " " };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest3a
BOOST_AUTO_TEST_CASE( TrimTrailingTest3a )
{
    WideString str1 { L"" };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest3b
BOOST_AUTO_TEST_CASE( TrimTrailingTest3b )
{
    AnsiString str1{ "" };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest3c
BOOST_AUTO_TEST_CASE( TrimTrailingTest3c )
{
    std::wstring_view str1{ L"" };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTrailingTest3d
BOOST_AUTO_TEST_CASE( TrimTrailingTest3d )
{
    std::string_view str1{ "" };
    auto str2 = TrimTrailing( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}



// --run_test=StringTests/TrimLeadingTest1a
BOOST_AUTO_TEST_CASE( TrimLeadingTest1a )
{
    WideString str1{ L" a " };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"a ";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest1b
BOOST_AUTO_TEST_CASE( TrimLeadingTest1b )
{
    AnsiString str1{ " a " };
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
    WideString str1{ L" " };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest2b
BOOST_AUTO_TEST_CASE( TrimLeadingTest2b )
{
    AnsiString str1{ " " };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest2c
BOOST_AUTO_TEST_CASE( TrimLeadingTest2c )
{
    std::wstring_view str1{ L" " };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest2d
BOOST_AUTO_TEST_CASE( TrimLeadingTest2d )
{
    std::string_view str1{ " " };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/TrimLeadingTest3a
BOOST_AUTO_TEST_CASE( TrimLeadingTest3a )
{
    WideString str1{ L"" };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest3b
BOOST_AUTO_TEST_CASE( TrimLeadingTest3b )
{
    AnsiString str1{ "" };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimLeadingTest3c
BOOST_AUTO_TEST_CASE( TrimLeadingTest3c )
{
    std::wstring_view str1{ L"" };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/TrimLeadingTest3d
BOOST_AUTO_TEST_CASE( TrimLeadingTest3d )
{
    std::string_view str1{ "" };
    auto str2 = TrimLeading( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}


// --run_test=StringTests/TrimTest1a
BOOST_AUTO_TEST_CASE( TrimTest1a )
{
    WideString str1{ L" a " };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest1b
BOOST_AUTO_TEST_CASE( TrimTest1b )
{
    AnsiString str1{ " a " };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest1c
BOOST_AUTO_TEST_CASE( TrimTest1c )
{
    std::wstring_view str1{ L" a " };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest1d
BOOST_AUTO_TEST_CASE( TrimTest1d )
{
    std::string_view str1{ " a " };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "a";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest2a
BOOST_AUTO_TEST_CASE( TrimTest2a )
{
    WideString str1{ L" " };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest2b
BOOST_AUTO_TEST_CASE( TrimTest2b )
{
    AnsiString str1{ " " };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest2c
BOOST_AUTO_TEST_CASE( TrimTest2c )
{
    std::wstring_view str1{ L" " };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest2d
BOOST_AUTO_TEST_CASE( TrimTest2d )
{
    std::string_view str1{ " " };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest3a
BOOST_AUTO_TEST_CASE( TrimTest3a )
{
    WideString str1{ L"" };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest3b
BOOST_AUTO_TEST_CASE( TrimTest3b )
{
    AnsiString str1{ "" };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == "";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest3c
BOOST_AUTO_TEST_CASE( TrimTest3c )
{
    std::wstring_view str1{ L"" };
    auto str2 = Trim( str1 );
    bool areEqual = str2 == L"";
    BOOST_TEST( areEqual );
}

// --run_test=StringTests/TrimTest3d
BOOST_AUTO_TEST_CASE( TrimTest3d )
{
    std::string_view str1{ "" };
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

// --run_test=StringTests/ParseBooleanTest1A
BOOST_AUTO_TEST_CASE( ParseBooleanTest1A )
{
    AnsiString TrueStr{ "True" };
    AnsiString FalseStr{ "False" };
    bool value = Parse<bool>( TrueStr );
    bool equal = value == true;
    BOOST_TEST( equal );
    value = Parse<bool>( FalseStr );
    equal = value == false;
    BOOST_TEST( equal );
}

// --run_test=StringTests/InsertTest1
BOOST_AUTO_TEST_CASE( InsertTest1 )
{
    WideString s;
    s.Insert( 0ULL, 1ULL, L'H' );
    auto equal = s == L"H";
    BOOST_TEST( equal );
}

// --run_test=StringTests/InsertTest2
BOOST_AUTO_TEST_CASE( InsertTest2 )
{
    WideString s;
    s.Insert( 2ULL, 1ULL, L'H' );
    auto equal = s == L"  H";
    BOOST_TEST( equal );
}

// --run_test=StringTests/InsertTest3
BOOST_AUTO_TEST_CASE( InsertTest3 )
{
    WideString s1(L"AC" );
    WideString s2( L"B" );
    s1.Insert( 1ULL, s2 );
    auto equal = s1 == L"ABC";
    BOOST_TEST( equal );
}

// --run_test=StringTests/InsertTest4
BOOST_AUTO_TEST_CASE( InsertTest4 )
{
    WideString s1( L"AC" );
    std::wstring s2( L"B" );
    s1.Insert( 1ULL, s2 );
    auto equal = s1 == L"ABC";
    BOOST_TEST( equal );
}

// --run_test=StringTests/InsertTest5
BOOST_AUTO_TEST_CASE( InsertTest5 )
{
    WideString s1( L"AC" );
    std::wstring_view s2( L"B" );
    s1.Insert( 1ULL, s2 );
    auto equal = s1 == L"ABC";
    BOOST_TEST( equal );
}

// --run_test=StringTests/InsertTest6
BOOST_AUTO_TEST_CASE( InsertTest6 )
{
    WideString s1( L"AC" );
    std::wstring_view s2( L"B" );
    WideString s3 = s1;
    s1.Insert( 1ULL, s2 );
    auto equal = s1 == L"ABC";
    BOOST_TEST( equal );
    equal = s3 == L"AC";
    BOOST_TEST( equal );
}


BOOST_AUTO_TEST_SUITE_END( )
