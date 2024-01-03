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

#include <HOCI.h>
#include <HCCXml.h>
#include <HCCIO.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <OCITestFixture.h>

using namespace Harlinn::Common;
using namespace Harlinn::OCI;
using namespace Harlinn;

BOOST_FIXTURE_TEST_SUITE( EnvironmentTests, LocalFixture )

// --run_test=EnvironmentTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    OCI::Environment environment;
    BOOST_CHECK( environment.Handle( ) == nullptr );
}

// --run_test=EnvironmentTests/ConstructorTest2
BOOST_AUTO_TEST_CASE( ConstructorTest2 )
{
    OCI::EnvironmentOptions options;
    OCI::Environment environment( options );
    BOOST_CHECK( environment.Handle( ) != nullptr );
}



BOOST_AUTO_TEST_SUITE_END( )