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

BOOST_FIXTURE_TEST_SUITE( FlagsTests, LocalFixture )

// --run_test=FlagsTests/EseColumnTypeToWideStringTest
BOOST_AUTO_TEST_CASE( EseColumnTypeToWideStringTest )
{
    WideString expected( L"DateTime" );
    auto str1 = ToWideString( Ese::ColumnType::DateTime );
    auto str2 = Format(L"{}", Ese::ColumnType::DateTime );
    bool equals = str1 == expected;
    BOOST_CHECK( equals );
    equals = str2 == expected;
    BOOST_CHECK( equals );
}

// --run_test=FlagsTests/TryParseEseColumnTypeTest
BOOST_AUTO_TEST_CASE( TryParseEseColumnTypeTest )
{
    WideString str( L" DateTime " );
    auto expected = Ese::ColumnType::DateTime;
    Ese::ColumnType value{};
    auto succeeded = TryParse( str, value );
    BOOST_CHECK( succeeded );
    bool equals = value == expected;
    BOOST_CHECK( equals );
}

// --run_test=FlagsTests/EseColumnFlagsToWideStringTest
BOOST_AUTO_TEST_CASE( EseColumnFlagsToWideStringTest )
{
    WideString expected( L"Fixed|NotNULL" );
    auto str1 = ToWideString( Ese::ColumnFlags::Fixed | Ese::ColumnFlags::NotNULL );
    auto str2 = Format( L"{}", Ese::ColumnFlags::Fixed | Ese::ColumnFlags::NotNULL );
    bool equals = str1 == expected;
    BOOST_CHECK( equals );
    equals = str2 == expected;
    BOOST_CHECK( equals );
}

// --run_test=FlagsTests/TryParseEseColumnFlagsTest
BOOST_AUTO_TEST_CASE( TryParseEseColumnFlagsTest )
{
    WideString str( L" NotNULL | Fixed ");
    auto expected = Ese::ColumnFlags::Fixed | Ese::ColumnFlags::NotNULL;
    Ese::ColumnFlags value{};
    auto succeeded = TryParse( str, value );
    BOOST_CHECK( succeeded );
    bool equals = value == expected;
    BOOST_CHECK( equals );
}




BOOST_AUTO_TEST_SUITE_END( )