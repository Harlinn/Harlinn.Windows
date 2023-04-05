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

BOOST_FIXTURE_TEST_SUITE( ProcessTests, LocalFixture )

// --run_test=ProcessTests/ProcessCmdDirTest1
BOOST_AUTO_TEST_CASE( ProcessCmdDirTest1 )
{
    ProcessOptions processOptions( L"C:\\Windows\\System32\\cmd.exe", L"/c time /t" );
    Process process( processOptions );
    process.Wait( );
    auto exitcode = process.ExitCode( );
    BOOST_CHECK( exitcode == 0 );

}
BOOST_AUTO_TEST_SUITE_END( )
