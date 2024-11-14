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

// --run_test=IOPathTests/IsDirectorySeparatorTest
BOOST_AUTO_TEST_CASE( IsDirectorySeparatorTest )
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


BOOST_AUTO_TEST_SUITE_END( )