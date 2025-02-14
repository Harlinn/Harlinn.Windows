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
#include <HCCFormatStringParser.h>

using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Formatting;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    void ParseTest( const char* formatString )
    {
        FormatStringParser formatStringParser( formatString );
        auto isValid = formatStringParser.IsValid( );
        BOOST_CHECK( isValid );
    }

}

BOOST_FIXTURE_TEST_SUITE( FormatStringParserTests, LocalFixture )

// --run_test=FormatStringParserTests/EmptyTest1
BOOST_AUTO_TEST_CASE( EmptyTest1 )
{
    ParseTest( "" );
}

// --run_test=FormatStringParserTests/SimpleTest1
BOOST_AUTO_TEST_CASE( SimpleTest1 )
{
    ParseTest( "{:6}" );
    ParseTest( "{:6}" );
    ParseTest( "{:*<6}" );
    ParseTest( "{:*>6}" );
    ParseTest( "{:*^6}" );
    ParseTest( "{:6d}" );
    ParseTest( "{:6}" );
    ParseTest( "{0:},{0:+},{0:-},{0: }" );
    ParseTest( "{:10f}" );
    ParseTest( "{:{}.{}f}" );
}

// --run_test=FormatStringParserTests/SimpleTest2
BOOST_AUTO_TEST_CASE( SimpleTest2 )
{
    FormatStringParser formatStringParser( "{0:},{0:+},{0:-},{0: }" );
    auto isValid = formatStringParser.IsValid( );
    BOOST_CHECK( isValid );
    auto size = formatStringParser.size( );
    BOOST_CHECK( size == 7 );

    auto& section1 = formatStringParser[ 0 ];
    bool equal1 = section1 == "{0:}";
    BOOST_CHECK( equal1 );

    auto& section2 = formatStringParser[ 1 ];
    bool equal2 = section2 == ",";
    BOOST_CHECK( equal2 );

    auto& section3 = formatStringParser[ 2 ];
    bool equal3 = section3 == "{0:+}";
    BOOST_CHECK( equal3 );

    auto& section4 = formatStringParser[ 3 ];
    bool equal4 = section4 == ",";
    BOOST_CHECK( equal4 );

    auto& section5 = formatStringParser[ 4 ];
    bool equal5 = section5 == "{0:-}";
    BOOST_CHECK( equal5 );

    auto& section6 = formatStringParser[ 5 ];
    bool equal6 = section6 == ",";
    BOOST_CHECK( equal6 );

    auto& section7 = formatStringParser[ 6 ];
    bool equal7 = section7 == "{0: }";
    BOOST_CHECK( equal7 );

}

// --run_test=FormatStringParserTests/SimpleTest3
BOOST_AUTO_TEST_CASE( SimpleTest3 )
{
    FormatStringParser formatStringParser( "{:{}.{}}" );
    auto isValid = formatStringParser.IsValid( );
    BOOST_CHECK( isValid );
    auto size = formatStringParser.size( );
    BOOST_CHECK( size == 1 );

    auto& section1 = formatStringParser[ 0 ];
    bool equal1 = section1 == "{:{}.{}}";
    BOOST_CHECK( equal1 );

}




BOOST_AUTO_TEST_SUITE_END( )