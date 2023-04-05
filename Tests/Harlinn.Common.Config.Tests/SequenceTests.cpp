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

BOOST_FIXTURE_TEST_SUITE( SequenceTests, LocalFixture )

// --run_test=SequenceTests/ElementsInstanceTest1
BOOST_AUTO_TEST_CASE( ElementsInstanceTest1 )
{
    auto root = Config::Root::Instance( );
    auto elements = root->Elements( );
    BOOST_CHECK( elements != nullptr );
}

// --run_test=SequenceTests/AddSequenceTest1
BOOST_AUTO_TEST_CASE( AddSequenceTest1 )
{
    auto root = Config::Root::Instance( );
    auto elements = root->Elements( );
    BOOST_CHECK( elements != nullptr );

    auto element = elements->AddElement( L"Element" );
    BOOST_CHECK( element != nullptr );

    auto sequence1 = element->AddSequence( L"Test" );
    BOOST_CHECK( sequence1 != nullptr );

    auto sequence2 = element->Find( L"Test" );
    BOOST_CHECK( sequence1 == sequence2 );

    auto sequence3 = element->Find<Config::Sequence>( L"Test" );
    BOOST_CHECK( sequence1 == sequence3 );
}

// --run_test=SequenceTests/BooleanValueTest1
BOOST_AUTO_TEST_CASE( BooleanValueTest1 )
{
    using NodeType = Config::BooleanValue;
    constexpr Config::NodeType expectedType = Config::NodeType::Boolean;
    using ValueType = NodeType::ValueType;
    ValueType expectedValue = true;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t notificationId, void* data )
    {
        switch ( notificationId )
        {
            case NodeType::ValueChangedNotificationId:
            {
                if ( sender->Type( ) == expectedType )
                {
                    nodeData.Node = static_cast<NodeType*>( sender );
                    nodeData.Type = sender->Type( );
                    nodeData.Value = *reinterpret_cast<ValueType*>( data );
                }
            }
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"TestElement" );
    auto testSequence = testElement->AddElement( L"TestSequence" );
    auto value1 = testSequence->AddBoolean( L"Value" );
    auto value2 = testSequence->Find( L"Value" );
    auto value3 = testSequence->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}



BOOST_AUTO_TEST_SUITE_END( )
