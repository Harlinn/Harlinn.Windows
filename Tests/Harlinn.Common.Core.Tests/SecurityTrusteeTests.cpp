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