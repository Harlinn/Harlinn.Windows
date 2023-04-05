#include <HCCApplication.h>

#define BOOST_TEST_MODULE Harlinn.Common.Core.Tests
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


int main( int argc, char* argv[], char* envp[] )
{
    Harlinn::Common::Core::ApplicationOptions options;
    options.Load( );
    Harlinn::Common::Core::Application application( options );
    application.Start( );
    auto result = boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
    application.Stop( );
    return result;
}

