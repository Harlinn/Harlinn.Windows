/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#include <hccfg/hccfg_node.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "TestData.h"

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

BOOST_FIXTURE_TEST_SUITE( FindByPathTests, LocalFixture )

// --run_test=FindByPathTests/FindRootTest1
BOOST_AUTO_TEST_CASE( FindRootTest1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto root2 = root->FindByPath( L"/" );
    BOOST_CHECK( root2 != nullptr );
}

// --run_test=FindByPathTests/FindElementsTest1
BOOST_AUTO_TEST_CASE( FindElementsTest1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"Elements" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    auto type = node->Type( );
    BOOST_CHECK( name == L"Elements" );
    BOOST_CHECK( type == Config::NodeType::Elements );
}

// --run_test=FindByPathTests/FindElementsTest2
BOOST_AUTO_TEST_CASE( FindElementsTest2 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"/Elements" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    auto type = node->Type( );
    BOOST_CHECK( name == L"Elements" );
    BOOST_CHECK( type == Config::NodeType::Elements );
}

// --run_test=FindByPathTests/FindEnvironmentTest1
BOOST_AUTO_TEST_CASE( FindEnvironmentTest1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"Environment" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    auto type = node->Type( );
    BOOST_CHECK( name == L"Environment" );
    BOOST_CHECK( type == Config::NodeType::Environment );
}

// --run_test=FindByPathTests/FindEnvironmentTest2
BOOST_AUTO_TEST_CASE( FindEnvironmentTest2 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"/Environment" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    auto type = node->Type( );
    BOOST_CHECK( name == L"Environment" );
    BOOST_CHECK( type == Config::NodeType::Environment );
}

// --run_test=FindByPathTests/FindPathTest1
BOOST_AUTO_TEST_CASE( FindPathTest1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"Environment/path" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    auto type = node->Type( );
    BOOST_CHECK( _wcsicmp(name.c_str(), L"path" ) == 0 );
    BOOST_CHECK( type == Config::NodeType::EnvironmentValue );
}

// --run_test=FindByPathTests/FindPathTest2
BOOST_AUTO_TEST_CASE( FindPathTest2 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"/Environment/path" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    auto type = node->Type( );
    BOOST_CHECK( _wcsicmp( name.c_str( ), L"path" ) == 0 );
    BOOST_CHECK( type == Config::NodeType::EnvironmentValue );
}


// --run_test=FindByPathTests/FindElementsR1Test1
BOOST_AUTO_TEST_CASE( FindElementsR1Test1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"Elements/R1" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    auto type = node->Type( );
    BOOST_CHECK( name == L"R1" );
    BOOST_CHECK( type == Config::NodeType::Element );
}


void CheckElement( const Reference<Config::Node>& elementNode )
{
    auto type = elementNode->Type( );
    BOOST_CHECK( type == Config::NodeType::Element );
    auto booleanNode = elementNode->Find( L"Boolean" );
    BOOST_CHECK( booleanNode->Type() == Config::NodeType::Boolean );
    auto charNode = elementNode->Find( L"Char" );
    BOOST_CHECK( charNode->Type( ) == Config::NodeType::Char );
    auto sbyteNode = elementNode->Find( L"SByte" );
    BOOST_CHECK( sbyteNode->Type( ) == Config::NodeType::SByte );
    auto byteNode = elementNode->Find( L"Byte" );
    BOOST_CHECK( byteNode->Type( ) == Config::NodeType::Byte );
    auto wcharNode = elementNode->Find( L"WChar" );
    BOOST_CHECK( wcharNode->Type( ) == Config::NodeType::WChar );
    auto int16Node = elementNode->Find( L"Int16" );
    BOOST_CHECK( int16Node->Type( ) == Config::NodeType::Int16 );
    auto uint16Node = elementNode->Find( L"UInt16" );
    BOOST_CHECK( uint16Node->Type( ) == Config::NodeType::UInt16 );
    auto int32Node = elementNode->Find( L"Int32" );
    BOOST_CHECK( int32Node->Type( ) == Config::NodeType::Int32 );
    auto uint32Node = elementNode->Find( L"UInt32" );
    BOOST_CHECK( uint32Node->Type( ) == Config::NodeType::UInt32 );
    auto int64Node = elementNode->Find( L"Int64" );
    BOOST_CHECK( int64Node->Type( ) == Config::NodeType::Int64 );
    auto uint64Node = elementNode->Find( L"UInt64" );
    BOOST_CHECK( uint64Node->Type( ) == Config::NodeType::UInt64 );
    auto singleNode = elementNode->Find( L"Single" );
    BOOST_CHECK( singleNode->Type( ) == Config::NodeType::Single );
    auto doubleNode = elementNode->Find( L"Double" );
    BOOST_CHECK( doubleNode->Type( ) == Config::NodeType::Double );
    auto timeSpanNode = elementNode->Find( L"TimeSpan" );
    BOOST_CHECK( timeSpanNode->Type( ) == Config::NodeType::TimeSpan );
    auto dateTimeNode = elementNode->Find( L"DateTime" );
    BOOST_CHECK( dateTimeNode->Type( ) == Config::NodeType::DateTime );
    auto currencyNode = elementNode->Find( L"Currency" );
    BOOST_CHECK( currencyNode->Type( ) == Config::NodeType::Currency );
    auto guidNode = elementNode->Find( L"Guid" );
    BOOST_CHECK( guidNode->Type( ) == Config::NodeType::Guid );
    auto stringNode = elementNode->Find( L"String" );
    BOOST_CHECK( stringNode->Type( ) == Config::NodeType::String );
    auto wideStringNode = elementNode->Find( L"WideString" );
    BOOST_CHECK( wideStringNode->Type( ) == Config::NodeType::WideString );

}

void CheckChildSequence( const Reference<Config::Node>& sequenceNode )
{
    auto type = sequenceNode->Type( );
    BOOST_CHECK( type == Config::NodeType::Sequence );
    Reference<Config::Sequence> sequence( static_cast<Config::Sequence*>(sequenceNode.get()),true);


    auto booleanNode = sequence->at( 0 );
    BOOST_CHECK( booleanNode->Type( ) == Config::NodeType::Boolean );
    auto charNode = sequence->at( 1 );
    BOOST_CHECK( charNode->Type( ) == Config::NodeType::Char );
    auto sbyteNode = sequence->at( 2 );
    BOOST_CHECK( sbyteNode->Type( ) == Config::NodeType::SByte );
    auto byteNode = sequence->at( 3 );
    BOOST_CHECK( byteNode->Type( ) == Config::NodeType::Byte );
    auto wcharNode = sequence->at( 4 );
    BOOST_CHECK( wcharNode->Type( ) == Config::NodeType::WChar );
    auto int16Node = sequence->at( 5 );
    BOOST_CHECK( int16Node->Type( ) == Config::NodeType::Int16 );
    auto uint16Node = sequence->at( 6 );
    BOOST_CHECK( uint16Node->Type( ) == Config::NodeType::UInt16 );
    auto int32Node = sequence->at( 7 );
    BOOST_CHECK( int32Node->Type( ) == Config::NodeType::Int32 );
    auto uint32Node = sequence->at( 8 );
    BOOST_CHECK( uint32Node->Type( ) == Config::NodeType::UInt32 );
    auto int64Node = sequence->at( 9 );
    BOOST_CHECK( int64Node->Type( ) == Config::NodeType::Int64 );
    auto uint64Node = sequence->at( 10 );
    BOOST_CHECK( uint64Node->Type( ) == Config::NodeType::UInt64 );
    auto singleNode = sequence->at( 11 );
    BOOST_CHECK( singleNode->Type( ) == Config::NodeType::Single );
    auto doubleNode = sequence->at( 12 );
    BOOST_CHECK( doubleNode->Type( ) == Config::NodeType::Double );
    auto timeSpanNode = sequence->at( 13 );
    BOOST_CHECK( timeSpanNode->Type( ) == Config::NodeType::TimeSpan );
    auto dateTimeNode = sequence->at( 14 );
    BOOST_CHECK( dateTimeNode->Type( ) == Config::NodeType::DateTime );
    auto currencyNode = sequence->at( 15 );
    BOOST_CHECK( currencyNode->Type( ) == Config::NodeType::Currency );
    auto guidNode = sequence->at( 16 );
    BOOST_CHECK( guidNode->Type( ) == Config::NodeType::Guid );
    auto stringNode = sequence->at( 17 );
    BOOST_CHECK( stringNode->Type( ) == Config::NodeType::String );
    auto wideStringNode = sequence->at( 18 );
    BOOST_CHECK( wideStringNode->Type( ) == Config::NodeType::WideString );
}


// --run_test=FindByPathTests/FindElementsR1ElementTest1
BOOST_AUTO_TEST_CASE( FindElementsR1ElementTest1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"Elements/R1/Element" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    BOOST_CHECK( name == L"Element" );
    CheckElement( node );
}

// --run_test=FindByPathTests/FindElementsR1SequenceTest1
BOOST_AUTO_TEST_CASE( FindElementsR1SequenceTest1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"Elements/R1/Sequence" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    BOOST_CHECK( name == L"Sequence" );
    auto type = node->Type( );
    BOOST_CHECK( type == Config::NodeType::Sequence );
}

// --run_test=FindByPathTests/FindElementsR1Sequence1Test1
BOOST_AUTO_TEST_CASE( FindElementsR1Sequence1Test1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"Elements/R1/Sequence/1" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    BOOST_CHECK( name == L"S1" );
    CheckChildSequence( node );
}

// --run_test=FindByPathTests/FindElementsR1Sequence1P2Test1
BOOST_AUTO_TEST_CASE( FindElementsR1Sequence1P2Test1 )
{
    GenerateTestData( );

    auto root = Config::Root::Instance( );

    auto node = root->FindByPath( L"Elements/R1/Sequence/1/../2" );
    BOOST_CHECK( node != nullptr );
    auto name = node->Name( );
    BOOST_CHECK( name == L"S2" );
    CheckChildSequence( node );
}




BOOST_AUTO_TEST_SUITE_END( )