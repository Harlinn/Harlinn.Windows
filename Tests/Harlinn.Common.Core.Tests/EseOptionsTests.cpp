#include "pch.h"
#include "HCCEseOptions.h"
using namespace Harlinn::Common::Core;

// EseOptionsTests.cpp
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        {
            CoInitializeEx( nullptr, COINIT_MULTITHREADED );
        }
        ~LocalFixture( )
        {
            CoUninitialize( );
        }
    };
}

BOOST_FIXTURE_TEST_SUITE( EseOptionsTests, LocalFixture )

// --run_test=EseOptionsTests/LoadOptionsTest
BOOST_AUTO_TEST_CASE( LoadOptionsTest )
{
    auto options = Ese::Options::LoadFromFile( L"EseOptionsTests.xml" );
    bool loaded = options != nullptr;
    BOOST_TEST( loaded );
}


BOOST_AUTO_TEST_SUITE_END( )