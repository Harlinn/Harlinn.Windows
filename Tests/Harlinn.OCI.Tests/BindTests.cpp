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

#include <HOCI.h>
#include <HCCXml.h>
#include <HCCIO.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <OCITestFixture.h>

using namespace Harlinn::Common;
using namespace Harlinn::OCI;

BOOST_FIXTURE_TEST_SUITE( BindTests, LocalFixture )

// --run_test=BindTests/ExecuteTest1
BOOST_AUTO_TEST_CASE( ExecuteTest1 )
{

}

BOOST_AUTO_TEST_SUITE_END( )