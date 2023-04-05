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