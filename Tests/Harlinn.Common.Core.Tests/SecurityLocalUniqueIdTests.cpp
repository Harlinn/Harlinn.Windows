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
using namespace Harlinn::Common::Core::Security;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( SecurityLocalUniqueIdTests, LocalFixture )

// --run_test=SecurityLocalUniqueIdTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    LocalUniqueId localUniqueId;
    bool hasValue = !!localUniqueId;
    BOOST_CHECK( hasValue == false );
}

// --run_test=SecurityLocalUniqueIdTests/NewTest1
BOOST_AUTO_TEST_CASE( NewTest1 )
{
    LocalUniqueId localUniqueId = LocalUniqueId::New();
    bool hasValue = !!localUniqueId;
    BOOST_CHECK( hasValue == true );
}

// --run_test=SecurityLocalUniqueIdTests/FromPrivilegeNameTest1
BOOST_AUTO_TEST_CASE( FromPrivilegeNameTest1 )
{
    LocalUniqueId localUniqueId = LocalUniqueId::FromPrivilegeName( SE_SECURITY_NAME );
    bool hasValue = !!localUniqueId;
    BOOST_CHECK( hasValue == true );
}

// --run_test=SecurityLocalUniqueIdTests/QueryPrivilegeNameTest1
BOOST_AUTO_TEST_CASE( QueryPrivilegeNameTest1 )
{
    LocalUniqueId localUniqueId = LocalUniqueId::FromPrivilegeName( SE_SECURITY_NAME );
    bool hasValue = !!localUniqueId;
    BOOST_CHECK( hasValue == true );

    auto privilegeName = localUniqueId.QueryPrivilegeName( );
    BOOST_CHECK( privilegeName == SE_SECURITY_NAME );
}




BOOST_AUTO_TEST_SUITE_END( )