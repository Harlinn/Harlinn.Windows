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

BOOST_FIXTURE_TEST_SUITE( EnvironmentTests, LocalFixture )

// --run_test=EnvironmentTests/EnvironmentInstanceTest1
BOOST_AUTO_TEST_CASE( EnvironmentInstanceTest1 )
{
    auto root = Config::Root::Instance( );
    auto environment = root->Environment( );
    BOOST_CHECK( environment != nullptr );
}

// --run_test=EnvironmentTests/EnvironmentValuesTest1
BOOST_AUTO_TEST_CASE( EnvironmentValuesTest1 )
{
    auto root = Config::Root::Instance( );
    auto environment = root->Environment( );
    auto& values1 = environment->Items( );
    BOOST_CHECK( values1.size( ) > 0 );

    auto pathIt = values1.find( L"path" );
    BOOST_CHECK( pathIt != values1.end( ) );
    auto& path = pathIt->second;
    auto pathValue = path->Value( );
    BOOST_CHECK( pathValue.size() > 0 );

    auto valueIt = values1.find( L"DUMMY42" );
    BOOST_CHECK( valueIt == values1.end( ) );

    environment->Write( L"DUMMY42", L"42" );
    auto& values2 = environment->Items( );
    valueIt = values2.find( L"DUMMY42" );
    BOOST_CHECK( valueIt != values2.end( ) );

    auto& value = valueIt->second;
    bool valueSetResult = value->SetValue( L"43" );
    BOOST_CHECK( valueSetResult );

    auto s = value->Value( );
    BOOST_CHECK( s == L"43" );

    auto value2 = environment->Read( L"DUMMY32" );
    BOOST_CHECK( value2 == nullptr );

    auto deleteResult1 = environment->Delete( L"DUMMY42" );
    BOOST_CHECK( deleteResult1 );
    auto value3 = environment->Read( L"DUMMY42" );
    BOOST_CHECK( value3 == nullptr );


    auto deleteResult2 = environment->Delete( L"DUMMY32" );
    BOOST_CHECK( deleteResult2 == false );


}



BOOST_AUTO_TEST_SUITE_END( )