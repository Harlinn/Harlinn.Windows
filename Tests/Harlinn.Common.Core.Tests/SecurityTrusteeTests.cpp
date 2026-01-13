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

BOOST_FIXTURE_TEST_SUITE( SecurityTrusteeTests, LocalFixture )

// --run_test=SecurityTrusteeTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    Trustee trustee;
    bool isNotValid = trustee.IsValid( ) == false;
    BOOST_CHECK( isNotValid );
    isNotValid = !trustee;
    BOOST_CHECK( isNotValid );

    isNotValid = trustee == nullptr;
    BOOST_CHECK( isNotValid );

}


// --run_test=SecurityTrusteeTests/ConstructorTest2
BOOST_AUTO_TEST_CASE( ConstructorTest2 )
{
    auto userPrincipal = Environment::UserName( Environment::UserNameFormat::SamCompatible );

    Trustee trustee( userPrincipal.c_str());
    bool isValid = trustee.IsValid( ) == true;
    BOOST_CHECK( isValid );
    isValid = !!trustee;
    BOOST_CHECK( isValid );

    isValid = trustee != nullptr;
    BOOST_CHECK( isValid );

}



BOOST_AUTO_TEST_SUITE_END( )