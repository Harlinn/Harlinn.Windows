#include <HCCApplication.h>
#define BOOST_TEST_MODULE Harlinn.OCI.Tests
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

int main( int argc, char* argv[], char* envp[] )
{
    Harlinn::Common::Core::Application application;
    application.Start( );
    auto result = boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
    application.Stop( );
    return result;
}

