#include "pch.h"

using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Xml;
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

BOOST_FIXTURE_TEST_SUITE( XmlTests, LocalFixture )

const wchar_t* XmlDoc1 = L"<?xml version=\"1.0\"?>"
L"<weather xmlns=\"x-schema:weatherSchema.xml\">"
L"  <date>2020-01-31</date>"
L"  <degrees>-7.5</degrees>"
L"</weather>";


// --run_test=XmlTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    Dom::Document document;
    BOOST_CHECK( document == false );
}


// --run_test=XmlTests/CreateTest1
BOOST_AUTO_TEST_CASE( CreateTest1 )
{
    Dom::Document document = Dom::Document::Create();
    BOOST_CHECK( document != false );
    document.SetAsync( false );
    document.SetValidateOnParse( false );
    document.SetResolveExternals( false );
    document.SetPreserveWhiteSpace( true );
}

// --run_test=XmlTests/ConstructorTest2
BOOST_AUTO_TEST_CASE( ConstructorTest2 )
{
    Dom::Document document( XmlDoc1 );
    BOOST_CHECK( document != false );
}

// --run_test=XmlTests/DocumentElementTest1
BOOST_AUTO_TEST_CASE( DocumentElementTest1 )
{
    Dom::Document document( XmlDoc1 );
    BOOST_CHECK( document != false );

    auto documentElement = document.DocumentElement( );
    BOOST_CHECK( documentElement != false );
}

// --run_test=XmlTests/AttributesTest1
BOOST_AUTO_TEST_CASE( AttributesTest1 )
{
    Dom::Document document( XmlDoc1 );
    BOOST_CHECK( document != false );

    auto documentElement = document.DocumentElement( );
    BOOST_CHECK( documentElement != false );
    auto attributes = documentElement.Attributes( );
    BOOST_CHECK( attributes != false );
    BOOST_CHECK( attributes.size( ) == 1 );
    size_t count = 0;
    for ( auto& node : attributes )
    {
        count++;
    }
    BOOST_CHECK( count == 1);

    auto attribute = documentElement.Attribute( L"xmlns" );
    
    auto attributeValue = attribute.As<WideString>( );
    BOOST_CHECK( attributeValue == L"x-schema:weatherSchema.xml" );



}

// --run_test=XmlTests/ChildNodesTest1
BOOST_AUTO_TEST_CASE( ChildNodesTest1 )
{
    Dom::Document document( XmlDoc1 );
    BOOST_CHECK( document != false );

    auto documentElement = document.DocumentElement( );
    BOOST_CHECK( documentElement != false );
    auto children = documentElement.ChildNodes( );
    BOOST_CHECK( children.size( ) == 2 );
    size_t count = 0;
    for ( auto& node : children )
    {
        count++;
    }
    BOOST_CHECK( count == 2 );
}

// --run_test=XmlTests/LoadTest1
BOOST_AUTO_TEST_CASE( LoadTest1 )
{
    Dom::Document document = Dom::Document::Create( );
    BOOST_CHECK( document != false );
    document.SetAsync( false );
    document.SetValidateOnParse( false );
    document.SetResolveExternals( false );
    document.SetPreserveWhiteSpace( true );

    

    auto success = document.Load( L"EseOptionsTests.xml" );
    BOOST_CHECK( success );


    auto documentElement = document.DocumentElement( );
    auto list = documentElement.ElementsByTagName( L"StorageEngine" );
    BOOST_CHECK( list.size( ) > 0 );
    if ( list.size( ) )
    {
        auto element = list[0];

        auto name = element.Read<WideString>( L"Name" );
        BOOST_CHECK( name.size( ) > 0 );
        auto createPathIfNotExist = element.Read<bool>( L"CreatePathIfNotExist" );
        BOOST_CHECK( createPathIfNotExist );
        auto exceptionAction = element.Read<Ese::ExceptionAction>( L"ExceptionAction" );
        BOOST_CHECK( exceptionAction == Ese::ExceptionAction::None );

    }


}






BOOST_AUTO_TEST_SUITE_END( )