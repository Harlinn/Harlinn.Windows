/*
   Copyright 2024 Espen Harlinn

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

#include <HODBC.h>
#include <HCCXml.h>
#include <HCCIO.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <ODBCTestFixture.h>

using namespace Harlinn::Common;
using namespace Harlinn::ODBC;
using namespace Harlinn;

BOOST_FIXTURE_TEST_SUITE( EnvironmentTests, LocalFixture )

// --run_test=EnvironmentTests/ConstructorTest1
BOOST_AUTO_TEST_CASE( ConstructorTest1 )
{
    ODBC::Environment environment;
    BOOST_CHECK( environment.Handle( ) == ODBC::Environment::InvalidHandle );
}

// --run_test=EnvironmentTests/ConstructorTest2
BOOST_AUTO_TEST_CASE( ConstructorTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    BOOST_CHECK( environment.Handle( ) != ODBC::Environment::InvalidHandle );
}

// --run_test=EnvironmentTests/DriversTest1
BOOST_AUTO_TEST_CASE( DriversTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    BOOST_CHECK( environment.Handle( ) != ODBC::Environment::InvalidHandle );

    auto drivers = environment.Drivers( Fetch::First );
    BOOST_CHECK( drivers.size( ) > 0 );
}

// --run_test=EnvironmentTests/DataSourcesTest1
BOOST_AUTO_TEST_CASE( DataSourcesTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    BOOST_CHECK( environment.Handle( ) != ODBC::Environment::InvalidHandle );

    auto dataSources = environment.DataSources( Fetch::First );
    BOOST_CHECK( dataSources.size( ) > 0 );
}

// --run_test=EnvironmentTests/ConnectToDataSourceTest1
BOOST_AUTO_TEST_CASE( ConnectToDataSourceTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    BOOST_CHECK( environment.Handle( ) != ODBC::Environment::InvalidHandle );

    auto connection = environment.Connect( DataSource );
    BOOST_CHECK( connection.Handle( ) != ODBC::Connection::InvalidHandle );

}

// --run_test=EnvironmentTests/ConnectionGetFunctionsTest1
BOOST_AUTO_TEST_CASE( ConnectionGetFunctionsTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    BOOST_CHECK( environment.Handle( ) != ODBC::Environment::InvalidHandle );

    auto connection = environment.Connect( DataSource );
    BOOST_CHECK( connection.Handle( ) != ODBC::Connection::InvalidHandle );

    SQLUSMALLINT supportedFunctions[SQL_API_ODBC3_ALL_FUNCTIONS_SIZE];
    connection.GetFunctions( SQL_API_ODBC3_ALL_FUNCTIONS, supportedFunctions );

    bool SQLTablesSupported = SQL_FUNC_EXISTS( supportedFunctions, SQL_API_SQLTABLES );
    BOOST_CHECK( SQLTablesSupported );

}


// --run_test=EnvironmentTests/SetCurrentCatalogTest1
BOOST_AUTO_TEST_CASE( SetCurrentCatalogTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    BOOST_CHECK( environment.Handle( ) != ODBC::Environment::InvalidHandle );

    auto connection = environment.Connect( DataSource );
    BOOST_CHECK( connection.Handle( ) != ODBC::Connection::InvalidHandle );

    auto rc = connection.SetCurrentCatalog( DatabaseName );
    BOOST_CHECK( rc >= Result::Success );

    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );
}


class DateReaderTest1DateReader : public DataReader
{
    Int64 id_ = 0;
    ODBC::TimeStamp ts_;
    Int32 flags_ = 0;
    Double value_ = 0.0;
public:
    static constexpr SQLUSMALLINT ID_ID = 1;
    static constexpr SQLUSMALLINT TS_ID = 2;
    static constexpr SQLUSMALLINT FLAGS_ID = 3;
    static constexpr SQLUSMALLINT VALUE_ID = 4;

    using Base = DataReader;

    DateReaderTest1DateReader(const Statement* statement)
        : Base( statement )
    {
        Bind( ID_ID, &id_, nullptr );
        Bind( TS_ID, &ts_, nullptr );
        Bind( FLAGS_ID, &flags_, nullptr );
        Bind( VALUE_ID, &value_, nullptr );
    }

    constexpr Int64 Id( ) const noexcept
    {
        return id_;
    }
    constexpr const ODBC::TimeStamp& Timestamp( ) const noexcept
    {
        return ts_;
    }
    constexpr Int32 Flags( ) const noexcept
    {
        return flags_;
    }
    constexpr Double Value( ) const noexcept
    {
        return value_;
    }

};


// --run_test=EnvironmentTests/DateReaderTest1
BOOST_AUTO_TEST_CASE( DateReaderTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader<DateReaderTest1DateReader>( L"select Id, Ts, Flags, val from TimeseriesValue1" );

    while ( reader->Read( ) )
    {
    }

}

// --run_test=EnvironmentTests/DateReaderTest2
BOOST_AUTO_TEST_CASE( DateReaderTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    Int64 id = 2;
    Int64 idIndicator = 0;
    statement.BindParameter( 1, ParameterDirection::Input, &id );
    auto reader = statement.ExecuteReader<DateReaderTest1DateReader>( L"select Id, Ts, Flags, val from TimeseriesValue1 where Id = ?" );

    while ( reader->Read( ) )
    {

    }

}









BOOST_AUTO_TEST_SUITE_END( )