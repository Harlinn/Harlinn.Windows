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

BOOST_FIXTURE_TEST_SUITE( ElementTests, LocalFixture )

// --run_test=ElementTests/ElementsInstanceTest1
BOOST_AUTO_TEST_CASE( ElementsInstanceTest1 )
{
    auto root = Config::Root::Instance( );
    auto elements = root->Elements( );
    BOOST_CHECK( elements != nullptr );
}

// --run_test=ElementTests/AddGroupTest1
BOOST_AUTO_TEST_CASE( AddGroupTest1 )
{
    auto root = Config::Root::Instance( );
    auto elements = root->Elements( );
    BOOST_CHECK( elements != nullptr );

    auto element1 = elements->AddElement( L"Test" );
    BOOST_CHECK( element1 != nullptr );
    auto element1a = elements->Find( L"Test" );
    BOOST_CHECK( element1a != nullptr );
    BOOST_CHECK( element1a == element1 );
}

// --run_test=ElementTests/BooleanValueTest1
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
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddBoolean( L"Value" );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );
    
    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get() );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/CharValueTest1
BOOST_AUTO_TEST_CASE( CharValueTest1 )
{
    using NodeType = Config::CharValue;
    constexpr Config::NodeType expectedType = Config::NodeType::Char;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 'A';
    ValueType expectedValue = 'B';

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddChar( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/SByteValueTest1
BOOST_AUTO_TEST_CASE( SByteValueTest1 )
{
    using NodeType = Config::SByteValue;
    constexpr Config::NodeType expectedType = Config::NodeType::SByte;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 'A';
    ValueType expectedValue = 'B';

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddSByte( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/ByteValueTest1
BOOST_AUTO_TEST_CASE( ByteValueTest1 )
{
    using NodeType = Config::ByteValue;
    constexpr Config::NodeType expectedType = Config::NodeType::Byte;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 'A';
    ValueType expectedValue = 'B';

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddByte( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/Int16ValueTest1
BOOST_AUTO_TEST_CASE( WCharValueTest1 )
{
    using NodeType = Config::WCharValue;
    constexpr Config::NodeType expectedType = Config::NodeType::WChar;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = L'A';
    ValueType expectedValue = L'B';

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddWChar( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}


// --run_test=ElementTests/Int16ValueTest1
BOOST_AUTO_TEST_CASE( Int16ValueTest1 )
{
    using NodeType = Config::Int16Value;
    constexpr Config::NodeType expectedType = Config::NodeType::Int16;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 100;
    ValueType expectedValue = 200;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddInt16( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/UInt16ValueTest1
BOOST_AUTO_TEST_CASE( UInt16ValueTest1 )
{
    using NodeType = Config::UInt16Value;
    constexpr Config::NodeType expectedType = Config::NodeType::UInt16;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 100;
    ValueType expectedValue = 200;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddUInt16( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/Int32ValueTest1
BOOST_AUTO_TEST_CASE( Int32ValueTest1 )
{
    using NodeType = Config::Int32Value;
    constexpr Config::NodeType expectedType = Config::NodeType::Int32;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 100;
    ValueType expectedValue = 200;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddInt32( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/UInt32ValueTest1
BOOST_AUTO_TEST_CASE( UInt32ValueTest1 )
{
    using NodeType = Config::UInt32Value;
    constexpr Config::NodeType expectedType = Config::NodeType::UInt32;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 100;
    ValueType expectedValue = 200;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddUInt32( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/Int64ValueTest1
BOOST_AUTO_TEST_CASE( Int64ValueTest1 )
{
    using NodeType = Config::Int64Value;
    constexpr Config::NodeType expectedType = Config::NodeType::Int64;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 100;
    ValueType expectedValue = 200;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddInt64( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/UInt64ValueTest1
BOOST_AUTO_TEST_CASE( UInt64ValueTest1 )
{
    using NodeType = Config::UInt64Value;
    constexpr Config::NodeType expectedType = Config::NodeType::UInt64;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 100;
    ValueType expectedValue = 200;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddUInt64( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/SingleValueTest1
BOOST_AUTO_TEST_CASE( SingleValueTest1 )
{
    using NodeType = Config::SingleValue;
    constexpr Config::NodeType expectedType = Config::NodeType::Single;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 1;
    ValueType expectedValue = 2;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddSingle( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}

// --run_test=ElementTests/DoubleValueTest1
BOOST_AUTO_TEST_CASE( DoubleValueTest1 )
{
    using NodeType = Config::DoubleValue;
    constexpr Config::NodeType expectedType = Config::NodeType::Double;
    using ValueType = NodeType::ValueType;
    ValueType initialValue = 1;
    ValueType expectedValue = 2;

    struct NodeData
    {
        Config::NodeType Type;
        ValueType Value;
        NodeType* Node;
    };
    NodeData nodeData{};

    auto root = Config::Root::Instance( );
    root->OnNotification.connect( [&nodeData]( Config::Node* sender, uint64_t key, void* data )
    {
        if ( sender->Type( ) == expectedType && key == NodeType::ValueChangedNotificationId )
        {
            nodeData.Node = static_cast<NodeType*>( sender );
            nodeData.Type = sender->Type( );
            nodeData.Value = *reinterpret_cast<ValueType*>( data );
        }
    } );

    auto elements = root->Elements( );
    auto testElement = elements->AddElement( L"Test" );
    auto value1 = testElement->AddDouble( L"Value", initialValue );
    auto value2 = testElement->Find( L"Value" );
    auto value3 = testElement->Find<NodeType>( L"Value" );

    value3->SetValue( expectedValue );

    BOOST_CHECK( nodeData.Type == expectedType );
    BOOST_CHECK( nodeData.Value == expectedValue );
    BOOST_CHECK( nodeData.Node == value1.get( ) );
    BOOST_CHECK( value1 == value2 );
    BOOST_CHECK( value1 == value3 );
}


BOOST_AUTO_TEST_SUITE_END( )