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
#define BOOST_TEST_MODULE Harlinn.Julia.Tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <HJulia.h>

int main( int argc, char* argv[], char* envp[] )
{
    auto application = std::make_shared<Harlinn::Common::Core::Application>( );
    application->Start( );
    Harlinn::Julia::Init( );
    auto result = boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
    Harlinn::Julia::Finalize( 0 );
    application->Stop( );
    return result;
}
