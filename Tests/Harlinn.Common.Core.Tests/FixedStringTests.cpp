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
#include <HCCFixedString.h>

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

BOOST_FIXTURE_TEST_SUITE( FixedStringTests, LocalFixture )

// --run_test=FixedStringTests/BasicCompiletimeTest1
BOOST_AUTO_TEST_CASE( BasicCompiletimeTest1 )
{
    using FixedString = FixedWideZString<UInt16, 128>;
    static_assert( FixedString::ArraySize == 129 );
    constexpr size_t alignment = std::alignment_of_v<FixedString>;
    static_assert( alignment == 1 );
    constexpr size_t sizeofFixedString = sizeof( FixedString );
    constexpr size_t expectedSizeofFixedString = sizeof( UInt16 ) + ( ( 128 + 1 ) * sizeof( wchar_t ) );
    static_assert( sizeofFixedString == expectedSizeofFixedString );
}
// --run_test=FixedStringTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    using FixedString = FixedWideZString<UInt16, 128>;
    FixedString str;
    BOOST_CHECK( str.length() == 0 );
}

// --run_test=FixedStringTests/ConstructorTest2
BOOST_AUTO_TEST_CASE( ConstructorTest2 )
{
    using FixedString = FixedWideZString<UInt16, 128>;
    FixedString str1(L"");
    constexpr bool val1 = IsSpecializationOf<std::string_view, std::basic_string_view>;
    constexpr bool val2 = IsSpecializationOf<std::string, std::basic_string>;

    BOOST_CHECK( str1.length( ) == 0 );
    FixedString str2( L"2" );
    BOOST_CHECK( str2.length( ) == 1 );
    FixedString str3( str2 );
    BOOST_CHECK( str3.length( ) == 1 );
}




BOOST_AUTO_TEST_SUITE_END( )