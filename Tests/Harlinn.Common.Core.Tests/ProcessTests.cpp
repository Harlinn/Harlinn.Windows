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
