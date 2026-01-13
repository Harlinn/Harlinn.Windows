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

#include "HCCHtmlNamedCharacters.h"

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


BOOST_FIXTURE_TEST_SUITE( HtmlNamedCharactersTests, LocalFixture )

// --run_test=HtmlNamedCharactersTests/SortedTest
BOOST_AUTO_TEST_CASE( SortedTest )
{
    auto charactersByName = Html::CharactersByName( );
    auto charactersByNameCount = charactersByName.size( );
    for ( size_t i = 1; i < charactersByNameCount; i++ )
    {
        const auto& previous = charactersByName[ i - 1 ];
        const auto& current = charactersByName[ i ];
        if ( previous.Name >= current.Name )
        {
            BOOST_CHECK( false );
        }
    }
    
    auto charactersByValue = Html::CharactersByValue( );
    auto charactersByValueCount = charactersByValue.size( );
    for ( size_t i = 1; i < charactersByValueCount; i++ )
    {
        const auto& previous = charactersByValue[ i - 1 ];
        const auto& current = charactersByValue[ i ];
        if ( previous.Value >= current.Value )
        {
            BOOST_CHECK( false );
        }
    }
}

// --run_test=HtmlNamedCharactersTests/EncodeTest
BOOST_AUTO_TEST_CASE( EncodeTest )
{
    WideString expected( L"&amp;Smith &lt;&amp;&gt; Jones" );
    WideString str( L"&Smith <&> Jones" );
    auto encodedStr = Html::Encode<WideString>( str );
    bool asExpected = encodedStr == expected;
    BOOST_CHECK( asExpected );
}

// --run_test=HtmlNamedCharactersTests/DecodeTest
BOOST_AUTO_TEST_CASE( DecodeTest )
{
    WideString expected( L"&Smith <&> Jones" );
    WideString str( L"&amp;Smith &lt;&amp;&gt; Jones" );
    
    auto decodedStr = Html::Decode<WideString>( str );
    bool asExpected = decodedStr == expected;
    BOOST_CHECK( asExpected );
}


BOOST_AUTO_TEST_SUITE_END( )