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

BOOST_FIXTURE_TEST_SUITE( SecurityPackageTests, LocalFixture )
// --run_test=SecurityPackageTests/SecurityPackageConstructorTest1
BOOST_AUTO_TEST_CASE( SecurityPackageConstructorTest1 )
{
    SecurityPackages securityPackages;

    BOOST_CHECK( securityPackages.size( ) > 0 );
}
BOOST_AUTO_TEST_SUITE_END( )
