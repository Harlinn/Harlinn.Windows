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
#include "HCCLoggerLevel.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Logging;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( LoggerLevelTests, LocalFixture )

// --run_test=LoggerLevelTests/LevelOStreamOperatorTest1A
BOOST_AUTO_TEST_CASE( LevelOStreamOperatorTest1A )
{
    using StringType = AnsiString;
    Level level = Level::All & ~Level::System;
    std::string expectedResult = "Verbose|Trace|Debug|Info|Notice|Warning|Error|Exception|Critical|Alert|Emergency";

    std::ostringstream dest;

    dest << level;

    auto result = dest.str( );

    bool equal = expectedResult == result;

    BOOST_TEST( equal );
}


BOOST_AUTO_TEST_SUITE_END( )