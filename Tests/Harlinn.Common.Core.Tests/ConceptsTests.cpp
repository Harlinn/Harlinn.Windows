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

BOOST_FIXTURE_TEST_SUITE( ConceptsTests, LocalFixture )

// --run_test=ConceptsTests/SimpleSpanLikeTest
BOOST_AUTO_TEST_CASE( SimpleSpanLikeTest )
{
    constexpr bool b1 = SimpleSpanLike<std::vector<WideString>>;
    BOOST_CHECK( b1 );
    constexpr bool b2 = SimpleSpanLike<WideString>;
    BOOST_CHECK( b2 );
    constexpr bool b3 = SimpleSpanLike<std::string>;
    BOOST_CHECK( b3 );
    constexpr bool b4 = SimpleSpanLike<std::string_view>;
    BOOST_CHECK( b4 );
    constexpr bool b5 = SimpleSpanLike<std::map<WideString, WideString>> == false;
    BOOST_CHECK( b5 );
    constexpr bool b6 = SimpleSpanLike<std::array<WideString, 5>>;
    BOOST_CHECK( b6 );
    constexpr bool b7 = SimpleSpanLike<std::span<WideString, 5>>;
    BOOST_CHECK( b7 );


}

// --run_test=ConceptsTests/SimpleStringLikeTest
BOOST_AUTO_TEST_CASE( SimpleStringLikeTest )
{
    constexpr bool b1 = SimpleStringLike<std::string>;
    BOOST_CHECK( b1 );
    constexpr bool b2 = SimpleStringLike<AnsiString>;
    BOOST_CHECK( b2 );
    constexpr bool b3 = SimpleStringLike<std::wstring>;
    BOOST_CHECK( b3 );
    constexpr bool b4 = SimpleStringLike<WideString>;
    BOOST_CHECK( b4 );
}

// --run_test=ConceptsTests/SimpleAnsiStringLikeTest
BOOST_AUTO_TEST_CASE( SimpleAnsiStringLikeTest )
{
    constexpr bool b1 = SimpleAnsiStringLike<std::string>;
    BOOST_CHECK( b1 );
    constexpr bool b2 = SimpleAnsiStringLike<AnsiString>;
    BOOST_CHECK( b2 );
    constexpr bool b3 = SimpleAnsiStringLike<std::wstring> == false;
    BOOST_CHECK( b3 );
    constexpr bool b4 = SimpleAnsiStringLike<WideString> == false;
    BOOST_CHECK( b4 );
}

// --run_test=ConceptsTests/SimpleWideStringLikeTest
BOOST_AUTO_TEST_CASE( SimpleWideStringLikeTest )
{
    constexpr bool b1 = SimpleWideStringLike<std::string> == false;
    BOOST_CHECK( b1 );
    constexpr bool b2 = SimpleWideStringLike<AnsiString> == false;
    BOOST_CHECK( b2 );
    constexpr bool b3 = SimpleWideStringLike<std::wstring>;
    BOOST_CHECK( b3 );
    constexpr bool b4 = SimpleWideStringLike<WideString>;
    BOOST_CHECK( b4 );
}

// --run_test=ConceptsTests/StringLikeTest
BOOST_AUTO_TEST_CASE( StringLikeTest )
{
    constexpr bool b1 = StringLike<std::string>;
    BOOST_CHECK( b1 );
    constexpr bool b2 = StringLike<AnsiString>;
    BOOST_CHECK( b2 );
    constexpr bool b3 = StringLike<std::wstring>;
    BOOST_CHECK( b3 );
    constexpr bool b4 = StringLike<WideString>;
    BOOST_CHECK( b4 );
}

// --run_test=ConceptsTests/AnsiStringLikeTest
BOOST_AUTO_TEST_CASE( AnsiStringLikeTest )
{
    constexpr bool b1 = AnsiStringLike<std::string>;
    BOOST_CHECK( b1 );
    constexpr bool b2 = AnsiStringLike<AnsiString>;
    BOOST_CHECK( b2 );
    constexpr bool b3 = AnsiStringLike<std::wstring> == false;
    BOOST_CHECK( b3 );
    constexpr bool b4 = AnsiStringLike<WideString> == false;
    BOOST_CHECK( b4 );
}

// --run_test=ConceptsTests/WideStringLikeTest
BOOST_AUTO_TEST_CASE( WideStringLikeTest )
{
    constexpr bool b1 = WideStringLike<std::string> == false;
    BOOST_CHECK( b1 );
    constexpr bool b2 = WideStringLike<AnsiString> == false;
    BOOST_CHECK( b2 );
    constexpr bool b3 = WideStringLike<std::wstring>;
    BOOST_CHECK( b3 );
    constexpr bool b4 = WideStringLike<WideString>;
    BOOST_CHECK( b4 );
}

// --run_test=ConceptsTests/SimpleCharSpanLikeTest
BOOST_AUTO_TEST_CASE( SimpleCharSpanLikeTest )
{
    constexpr bool b1 = SimpleCharSpanLike<std::string>;
    BOOST_CHECK( b1 );
    constexpr bool b2 = SimpleCharSpanLike<AnsiString>;
    BOOST_CHECK( b2 );
    constexpr bool b3 = SimpleCharSpanLike<std::wstring>;
    BOOST_CHECK( b3 );
    constexpr bool b4 = SimpleCharSpanLike<WideString>;
    BOOST_CHECK( b4 );
    constexpr bool b5 = SimpleCharSpanLike<std::string_view>;
    BOOST_CHECK( b5 );
    constexpr bool b6 = SimpleCharSpanLike<AnsiStringView>;
    BOOST_CHECK( b6 );
    constexpr bool b7 = SimpleCharSpanLike<std::wstring_view>;
    BOOST_CHECK( b7 );
    constexpr bool b8 = SimpleCharSpanLike<WideStringView>;
    BOOST_CHECK( b8 );
    constexpr bool b9 = SimpleCharSpanLike<std::span<char>>;
    BOOST_CHECK( b9 );
    constexpr bool b10 = SimpleCharSpanLike<std::span<wchar_t>>;
    BOOST_CHECK( b10 );

}

// --run_test=ConceptsTests/SimpleAnsiCharSpanLikeTest
BOOST_AUTO_TEST_CASE( SimpleAnsiCharSpanLikeTest )
{
    constexpr bool b1 = SimpleAnsiCharSpanLike<std::string>;
    BOOST_CHECK( b1 );
    constexpr bool b2 = SimpleAnsiCharSpanLike<AnsiString>;
    BOOST_CHECK( b2 );
    constexpr bool b3 = SimpleAnsiCharSpanLike<std::wstring> == false;
    BOOST_CHECK( b3 );
    constexpr bool b4 = SimpleAnsiCharSpanLike<WideString> == false;
    BOOST_CHECK( b4 );
    constexpr bool b5 = SimpleAnsiCharSpanLike<std::string_view>;
    BOOST_CHECK( b5 );
    constexpr bool b6 = SimpleAnsiCharSpanLike<AnsiStringView>;
    BOOST_CHECK( b6 );
    constexpr bool b7 = SimpleAnsiCharSpanLike<std::wstring_view> == false;
    BOOST_CHECK( b7 );
    constexpr bool b8 = SimpleAnsiCharSpanLike<WideStringView> == false;
    BOOST_CHECK( b8 );
    constexpr bool b9 = SimpleAnsiCharSpanLike<std::span<char>>;
    BOOST_CHECK( b9 );
    constexpr bool b10 = SimpleAnsiCharSpanLike<std::span<wchar_t>> == false;
    BOOST_CHECK( b10 );
}

// --run_test=ConceptsTests/SimpleWideCharSpanLikeTest
BOOST_AUTO_TEST_CASE( SimpleWideCharSpanLikeTest )
{
    constexpr bool b1 = SimpleWideCharSpanLike<std::string> == false;
    BOOST_CHECK( b1 );
    constexpr bool b2 = SimpleWideCharSpanLike<AnsiString> == false;
    BOOST_CHECK( b2 );
    constexpr bool b3 = SimpleWideCharSpanLike<std::wstring>;
    BOOST_CHECK( b3 );
    constexpr bool b4 = SimpleWideCharSpanLike<WideString>;
    BOOST_CHECK( b4 );
    constexpr bool b5 = SimpleWideCharSpanLike<std::string_view> == false;
    BOOST_CHECK( b5 );
    constexpr bool b6 = SimpleWideCharSpanLike<AnsiStringView> == false;
    BOOST_CHECK( b6 );
    constexpr bool b7 = SimpleWideCharSpanLike<std::wstring_view>;
    BOOST_CHECK( b7 );
    constexpr bool b8 = SimpleWideCharSpanLike<WideStringView>;
    BOOST_CHECK( b8 );
    constexpr bool b9 = SimpleWideCharSpanLike<std::span<char>> == false;
    BOOST_CHECK( b9 );
    constexpr bool b10 = SimpleWideCharSpanLike<std::span<wchar_t>>;
    BOOST_CHECK( b10 );

}




BOOST_AUTO_TEST_SUITE_END( )