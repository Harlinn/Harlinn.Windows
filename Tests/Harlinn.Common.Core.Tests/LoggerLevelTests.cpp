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