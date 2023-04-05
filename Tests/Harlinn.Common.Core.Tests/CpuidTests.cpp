#include <intrin.h>
#include <boost/test/unit_test.hpp>


namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( CpuidTests, LocalFixture )

// --run_test=CpuidTests/Int64ByRefOrValueTest
BOOST_AUTO_TEST_CASE( Int64ByRefOrValueTest )
{
    __cpuidex
}

BOOST_AUTO_TEST_SUITE_END( )