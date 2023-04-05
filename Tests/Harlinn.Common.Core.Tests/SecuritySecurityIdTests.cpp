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

BOOST_FIXTURE_TEST_SUITE( SecuritySecurityIdTests, LocalFixture )

// --run_test=SecuritySecurityIdTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    SecurityId securityId;
    bool isValid = securityId.IsValid( );
    BOOST_CHECK( isValid == false );

}

// --run_test=SecuritySecurityIdTests/ConstructorTest2
BOOST_AUTO_TEST_CASE( ConstructorTest2 )
{
    auto username = Environment::UserName( Environment::UserNameFormat::SamCompatible );
    
    SecurityIdAndDomain securityIdAndDomain( username.c_str( ) );
    auto& securityId = securityIdAndDomain.SecurityId( );

    bool isValid = securityId.IsValid( );
    BOOST_CHECK( isValid );
}



BOOST_AUTO_TEST_SUITE_END( )