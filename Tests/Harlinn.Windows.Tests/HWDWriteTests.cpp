#include <HWDWrite.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace Harlinn::Common::Core;
using namespace Harlinn::Windows;
using namespace Harlinn::Windows::Graphics;


namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( HWDWriteTests, LocalFixture )


// --run_test=HWDWriteTests/FactoryCTorTest1
BOOST_AUTO_TEST_CASE( FactoryCTorTest1 )
{
    using namespace Harlinn::Windows::Graphics::DirectWrite;
    Factory factory(FactoryType::Shared);

    auto ptr = factory.GetInterfacePointer<IDWriteFactory>( );

    BOOST_CHECK( ptr != nullptr );

}

// --run_test=HWDWriteTests/SystemFontCollectionIteratorTest1
BOOST_AUTO_TEST_CASE( SystemFontCollectionIteratorTest1 )
{
    using namespace Harlinn::Windows::Graphics::DirectWrite;
    Factory factory( FactoryType::Shared );

    auto systemFontCollection = factory.GetSystemFontCollection( );

    for ( auto& fontFamily : systemFontCollection )
    {
        auto familyName = fontFamily.GetFamilyNames( ).GetString( 0 );
        PrintLn( L"Font Family: {}", familyName );
        //BOOST_TEST_MESSAGE( "Font Family: " << familyName );
    } 
    

}





BOOST_AUTO_TEST_SUITE_END( )