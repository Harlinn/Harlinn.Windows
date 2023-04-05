#include <hccfg/hccfg_node.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common;

namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) 
        {
            Config::Root::Reset( );
        }
    };
}

BOOST_FIXTURE_TEST_SUITE( RootTests, LocalFixture )

// --run_test=RootTests/RootInstanceTest1
BOOST_AUTO_TEST_CASE( RootInstanceTest1 )
{
    auto root = Config::Root::Instance( );
    BOOST_CHECK( root != nullptr );
}

BOOST_AUTO_TEST_SUITE_END( )