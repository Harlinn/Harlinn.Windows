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

BOOST_FIXTURE_TEST_SUITE( StatementTests, LocalFixture )

// --run_test=StatementTests/ColumnIsAutoIncrementTest1
BOOST_AUTO_TEST_CASE( ColumnIsAutoIncrementTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    bool columnIsAutoIncrement = statement.ColumnIsAutoIncrement( 1 );
    BOOST_CHECK( columnIsAutoIncrement == false );

}

// --run_test=StatementTests/ColumnIsAutoIncrementTest2
BOOST_AUTO_TEST_CASE( ColumnIsAutoIncrementTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, LastName, FirstName, MiddleName FROM Persons" );
    BOOST_CHECK( rc == Result::Success );
    bool columnIsAutoIncrement = statement.ColumnIsAutoIncrement( 1 );
    BOOST_CHECK( columnIsAutoIncrement == true );

}

// --run_test=StatementTests/ColumnBaseNameTest1
BOOST_AUTO_TEST_CASE( ColumnBaseNameTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, LastName, FirstName, MiddleName FROM Persons FOR BROWSE" );
    BOOST_CHECK( rc == Result::Success );
    auto baseName = statement.ColumnBaseName( 1 );
    BOOST_CHECK( baseName == L"Id" );
}


// --run_test=StatementTests/ColumnBaseTableNameTest1
BOOST_AUTO_TEST_CASE( ColumnBaseTableNameTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, LastName, FirstName, MiddleName FROM Persons FOR BROWSE" );
    BOOST_CHECK( rc == Result::Success );
    auto baseName = statement.ColumnBaseTableName( 1 );
    BOOST_CHECK( baseName == L"Persons" );
}

// --run_test=StatementTests/ColumnIsCaseSensitiveTest1
BOOST_AUTO_TEST_CASE( ColumnIsCaseSensitiveTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, LastName, FirstName, MiddleName FROM Persons" );
    BOOST_CHECK( rc == Result::Success );
    auto columnIsCaseSensitive = statement.ColumnIsCaseSensitive( 2 );
    BOOST_CHECK( columnIsCaseSensitive == false );
}

// --run_test=StatementTests/ColumnCatalogNameTest1
BOOST_AUTO_TEST_CASE( ColumnCatalogNameTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, LastName, FirstName, MiddleName FROM Persons FOR BROWSE" );
    BOOST_CHECK( rc == Result::Success );
    auto columnCatalogName = statement.ColumnCatalogName( 1 );
    BOOST_CHECK( columnCatalogName == DatabaseName );
}

// --run_test=StatementTests/ColumnConciseTypeTest1
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 1 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::BigInt );
}

// --run_test=StatementTests/ColumnConciseTypeTest2
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Bit );
}

// --run_test=StatementTests/ColumnConciseTypeTest3
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TinyIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::TinyInt );
}

// --run_test=StatementTests/ColumnConciseTypeTest4
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::SmallInt );
}

// --run_test=StatementTests/ColumnConciseTypeTest5
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, IntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Integer );
}

// --run_test=StatementTests/ColumnConciseTypeTest6
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BigIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::BigInt );
}

// --run_test=StatementTests/ColumnConciseTypeTest7
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Decimal );
}

// --run_test=StatementTests/ColumnConciseTypeTest8
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NumericValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Numeric );
}

// --run_test=StatementTests/ColumnConciseTypeTest9
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RealValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Real );
}

// --run_test=StatementTests/ColumnConciseTypeTest10
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Float );
}

// --run_test=StatementTests/ColumnConciseTypeTest11
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest11 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Decimal );
}

// --run_test=StatementTests/ColumnConciseTypeTest12
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest12 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Decimal );
}

// --run_test=StatementTests/ColumnConciseTypeTest13
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest13 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Date );
}

// --run_test=StatementTests/ColumnConciseTypeTest14
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest14 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::TimeStamp );
}

// --run_test=StatementTests/ColumnConciseTypeTest15
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest15 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTime2Value FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::TimeStamp );
}

// --run_test=StatementTests/ColumnConciseTypeTest16
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest16 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::TimeStampOffset );
}

// --run_test=StatementTests/ColumnConciseTypeTest17
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest17 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::TimeStamp );
}

// --run_test=StatementTests/ColumnConciseTypeTest18
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest18 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Time2 );
}


// --run_test=StatementTests/ColumnConciseTypeTest19
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest19 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, UniqueidentifierValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Guid );
}

// --run_test=StatementTests/ColumnConciseTypeTest20
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest20 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RowVersionValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Binary );
}

// --run_test=StatementTests/ColumnConciseTypeTest21
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest21 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Binary );
}

// --run_test=StatementTests/ColumnConciseTypeTest22
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest22 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::VarBinary );
}

// --run_test=StatementTests/ColumnConciseTypeTest23
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest23 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, CharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::Char );
}

// --run_test=StatementTests/ColumnConciseTypeTest24
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest24 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::VarChar );
}

// --run_test=StatementTests/ColumnConciseTypeTest25
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest25 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::WChar );
}

// --run_test=StatementTests/ColumnConciseTypeTest26
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest26 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NVarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::WVarChar );
}

// --run_test=StatementTests/ColumnConciseTypeTest27
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest27 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::LongVarChar );
}

// --run_test=StatementTests/ColumnConciseTypeTest28
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest28 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NTextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::WLongVarChar );
}

// --run_test=StatementTests/ColumnConciseTypeTest29
BOOST_AUTO_TEST_CASE( ColumnConciseTypeTest29 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, ImageValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnConciseType = statement.ColumnConciseType( 2 );
    BOOST_CHECK( columnConciseType == ODBC::SqlType::LongVarBinary );
}









BOOST_AUTO_TEST_SUITE_END( )