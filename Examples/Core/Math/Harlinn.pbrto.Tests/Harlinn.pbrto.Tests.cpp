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

#include <HCCApplication.h>
#include <pbrto/NewPbrt.h>
#include <pbrto/NewOptions.h>

#define BOOST_TEST_MODULE Harlinn.Common.Core.Tests
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


int main( int argc, char* argv[ ], char* envp[ ] )
{
    auto application = std::make_shared<Harlinn::Common::Core::Application>( );
    application->Start( );

    pbrto::PBRTOptions opt;
    opt.quiet = true;
    pbrto::InitPBRT( opt );

    auto result = boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
    pbrto::CleanupPBRT( );
    application->Stop( );
    return result;
}

