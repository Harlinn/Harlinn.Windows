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

#include <HODBC.h>
#include <HCCXml.h>
#include <HCCIO.h>
#include <HCCGenerators.h>

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

// --run_test=StatementTests/ColumnCountTest1
BOOST_AUTO_TEST_CASE( ColumnCountTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnCount = statement.ColumnCount( );
    BOOST_CHECK( columnCount == 2 );
}


// --run_test=StatementTests/ColumnDisplaySizeTest1
BOOST_AUTO_TEST_CASE( ColumnDisplaySizeTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnDisplaySize = statement.ColumnDisplaySize( 2 );
    BOOST_CHECK( columnDisplaySize == 1 );
}

// --run_test=StatementTests/ColumnHasFixedPrecisionAndScaleTest1
BOOST_AUTO_TEST_CASE( ColumnHasFixedPrecisionAndScaleTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnHasFixedPrecisionAndScale = statement.ColumnHasFixedPrecisionAndScale( 2 );
    BOOST_CHECK( columnHasFixedPrecisionAndScale );
}

// --run_test=StatementTests/ColumnHasFixedPrecisionAndScaleTest2
BOOST_AUTO_TEST_CASE( ColumnHasFixedPrecisionAndScaleTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnHasFixedPrecisionAndScale = statement.ColumnHasFixedPrecisionAndScale( 2 );
    BOOST_CHECK( columnHasFixedPrecisionAndScale );
}

// --run_test=StatementTests/ColumnHasFixedPrecisionAndScaleTest3
BOOST_AUTO_TEST_CASE( ColumnHasFixedPrecisionAndScaleTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnHasFixedPrecisionAndScale = statement.ColumnHasFixedPrecisionAndScale( 2 );
    BOOST_CHECK( columnHasFixedPrecisionAndScale == false );
}

// --run_test=StatementTests/ColumnHasFixedPrecisionAndScaleTest4
BOOST_AUTO_TEST_CASE( ColumnHasFixedPrecisionAndScaleTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NumericValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnHasFixedPrecisionAndScale = statement.ColumnHasFixedPrecisionAndScale( 2 );
    BOOST_CHECK( columnHasFixedPrecisionAndScale == false );
}

// --run_test=StatementTests/ColumnHasFixedPrecisionAndScaleTest5
BOOST_AUTO_TEST_CASE( ColumnHasFixedPrecisionAndScaleTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RealValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnHasFixedPrecisionAndScale = statement.ColumnHasFixedPrecisionAndScale( 2 );
    BOOST_CHECK( columnHasFixedPrecisionAndScale == false );
}

// --run_test=StatementTests/ColumnHasFixedPrecisionAndScaleTest6
BOOST_AUTO_TEST_CASE( ColumnHasFixedPrecisionAndScaleTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnHasFixedPrecisionAndScale = statement.ColumnHasFixedPrecisionAndScale( 2 );
    BOOST_CHECK( columnHasFixedPrecisionAndScale == false );
}

// --run_test=StatementTests/ColumnLabelTest1
BOOST_AUTO_TEST_CASE( ColumnLabelTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLabel = statement.ColumnLabel( 2 );
    BOOST_CHECK( columnLabel == L"BitValue" );
}

// --run_test=StatementTests/ColumnLengthTest1
BOOST_AUTO_TEST_CASE( ColumnLengthTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 1 );
}

// --run_test=StatementTests/ColumnLengthTest2
BOOST_AUTO_TEST_CASE( ColumnLengthTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TinyIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 3 );
}

// --run_test=StatementTests/ColumnLengthTest3
BOOST_AUTO_TEST_CASE( ColumnLengthTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 5 );
}

// --run_test=StatementTests/ColumnLengthTest4
BOOST_AUTO_TEST_CASE( ColumnLengthTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, IntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 10 );
}

// --run_test=StatementTests/ColumnLengthTest5
BOOST_AUTO_TEST_CASE( ColumnLengthTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BigIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 19 );
}

// --run_test=StatementTests/ColumnLengthTest6
BOOST_AUTO_TEST_CASE( ColumnLengthTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 38 );
}

// --run_test=StatementTests/ColumnLengthTest7
BOOST_AUTO_TEST_CASE( ColumnLengthTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NumericValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 18 );
}

// --run_test=StatementTests/ColumnLengthTest8
BOOST_AUTO_TEST_CASE( ColumnLengthTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RealValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 24 );
}

// --run_test=StatementTests/ColumnLengthTest9
BOOST_AUTO_TEST_CASE( ColumnLengthTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 53 );
    
}

// --run_test=StatementTests/ColumnLengthTest10
BOOST_AUTO_TEST_CASE( ColumnLengthTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 10 );
}

// --run_test=StatementTests/ColumnLengthTest11
BOOST_AUTO_TEST_CASE( ColumnLengthTest11 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 19 );
}

// --run_test=StatementTests/ColumnLengthTest12
BOOST_AUTO_TEST_CASE( ColumnLengthTest12 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 10 );
}

// --run_test=StatementTests/ColumnLengthTest13
BOOST_AUTO_TEST_CASE( ColumnLengthTest13 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 23 );
}

// --run_test=StatementTests/ColumnLengthTest14
BOOST_AUTO_TEST_CASE( ColumnLengthTest14 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTime2Value FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 27 );
}

// --run_test=StatementTests/ColumnLengthTest15
BOOST_AUTO_TEST_CASE( ColumnLengthTest15 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 34 );
}

// --run_test=StatementTests/ColumnLengthTest16
BOOST_AUTO_TEST_CASE( ColumnLengthTest16 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 16 );
}

// --run_test=StatementTests/ColumnLengthTest17
BOOST_AUTO_TEST_CASE( ColumnLengthTest17 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 16 );
}

// --run_test=StatementTests/ColumnLengthTest18
BOOST_AUTO_TEST_CASE( ColumnLengthTest18 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, UniqueidentifierValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 36 );
}

// --run_test=StatementTests/ColumnLengthTest19
BOOST_AUTO_TEST_CASE( ColumnLengthTest19 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RowVersionValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 8 );
}

// --run_test=StatementTests/ColumnLengthTest20
BOOST_AUTO_TEST_CASE( ColumnLengthTest20 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 4 );
}

// --run_test=StatementTests/ColumnLengthTest21
BOOST_AUTO_TEST_CASE( ColumnLengthTest21 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 0 );
}

// --run_test=StatementTests/ColumnLengthTest22
BOOST_AUTO_TEST_CASE( ColumnLengthTest22 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, CharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 4 );
}

// --run_test=StatementTests/ColumnLengthTest23
BOOST_AUTO_TEST_CASE( ColumnLengthTest23 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 0 );
}

// --run_test=StatementTests/ColumnLengthTest24
BOOST_AUTO_TEST_CASE( ColumnLengthTest24 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 4 );
}

// --run_test=StatementTests/ColumnLengthTest25
BOOST_AUTO_TEST_CASE( ColumnLengthTest25 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NVarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 0 );
}

// --run_test=StatementTests/ColumnLengthTest26
BOOST_AUTO_TEST_CASE( ColumnLengthTest26 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 2147483647 );
}

// --run_test=StatementTests/ColumnLengthTest27
BOOST_AUTO_TEST_CASE( ColumnLengthTest27 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NTextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 1073741823 );
}

// --run_test=StatementTests/ColumnLengthTest28
BOOST_AUTO_TEST_CASE( ColumnLengthTest28 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, ImageValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLength = statement.ColumnLength( 2 );
    BOOST_CHECK( columnLength == 2147483647 );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest1
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest1
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest2
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RowVersionValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"0x" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest2
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RowVersionValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest3
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"$" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest3
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest4
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"0x" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest4
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest5
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"0x" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest5
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"" );
}


// --run_test=StatementTests/ColumnLiteralPrefixTest6
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"N'" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest6
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"'" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest7
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NVarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"N'" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest7
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NVarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"'" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest8
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NTextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"N'" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest8
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NTextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"'" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest9
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, ImageValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"0x" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest9
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, ImageValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest10
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, CharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"'" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest10
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, CharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"'" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest11
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest11 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"'" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest11
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest11 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"'" );
}

// --run_test=StatementTests/ColumnLiteralPrefixTest12
BOOST_AUTO_TEST_CASE( ColumnLiteralPrefixTest12 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralPrefix = statement.ColumnLiteralPrefix( 2 );
    BOOST_CHECK( columnLiteralPrefix == L"'" );
}

// --run_test=StatementTests/ColumnLiteralSuffixTest12
BOOST_AUTO_TEST_CASE( ColumnLiteralSuffixTest12 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLiteralSuffix = statement.ColumnLiteralSuffix( 2 );
    BOOST_CHECK( columnLiteralSuffix == L"'" );
}

// --run_test=StatementTests/ColumnLocalTypeNameTest1
BOOST_AUTO_TEST_CASE( ColumnLocalTypeNameTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLocalTypeName = statement.ColumnLocalTypeName( 2 );
    BOOST_CHECK( columnLocalTypeName == L"bit" );
}

// --run_test=StatementTests/ColumnLocalTypeNameTest2
BOOST_AUTO_TEST_CASE( ColumnLocalTypeNameTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TinyIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnLocalTypeName = statement.ColumnLocalTypeName( 2 );
    BOOST_CHECK( columnLocalTypeName == L"tinyint" );
}

// --run_test=StatementTests/ColumnNameTest1
BOOST_AUTO_TEST_CASE( ColumnNameTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnName = statement.ColumnName( 2 );
    BOOST_CHECK( columnName == L"BitValue" );
}

// --run_test=StatementTests/ColumnIsNullableTest1
BOOST_AUTO_TEST_CASE( ColumnIsNullableTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnIsNullable = statement.ColumnIsNullable( 2 );
    BOOST_CHECK( columnIsNullable.has_value( ) == true );
    BOOST_CHECK( columnIsNullable.value() == true );
}

// --run_test=StatementTests/ColumnNumericPrecisionRadixTest1
BOOST_AUTO_TEST_CASE( ColumnNumericPrecisionRadixTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnNumericPrecisionRadix = statement.ColumnNumericPrecisionRadix( 2 );
    BOOST_CHECK( columnNumericPrecisionRadix == 2 );
}

// --run_test=StatementTests/ColumnNumericPrecisionRadixTest2
BOOST_AUTO_TEST_CASE( ColumnNumericPrecisionRadixTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnNumericPrecisionRadix = statement.ColumnNumericPrecisionRadix( 2 );
    BOOST_CHECK( columnNumericPrecisionRadix == 10 );
}

// --run_test=StatementTests/ColumnNumericPrecisionRadixTest3
BOOST_AUTO_TEST_CASE( ColumnNumericPrecisionRadixTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnNumericPrecisionRadix = statement.ColumnNumericPrecisionRadix( 2 );
    BOOST_CHECK( columnNumericPrecisionRadix == 10 );
}

// --run_test=StatementTests/ColumnNumericPrecisionRadixTest4
BOOST_AUTO_TEST_CASE( ColumnNumericPrecisionRadixTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnNumericPrecisionRadix = statement.ColumnNumericPrecisionRadix( 2 );
    BOOST_CHECK( columnNumericPrecisionRadix == 10 );
}

// --run_test=StatementTests/ColumnNumericPrecisionRadixTest5
BOOST_AUTO_TEST_CASE( ColumnNumericPrecisionRadixTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTime2Value FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnNumericPrecisionRadix = statement.ColumnNumericPrecisionRadix( 2 );
    BOOST_CHECK( columnNumericPrecisionRadix == 0 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest1
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 1 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest2
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TinyIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 1 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest3
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 2 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest4
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, IntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 4 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest5
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BigIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 8 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest6
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 40 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest7
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NumericValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 20 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest8
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RealValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( float ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest9
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( double ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest10
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 12 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest11
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest11 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 21 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest12
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest12 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( ODBC::Date ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest13
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest13 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( ODBC::TimeStamp ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest14
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest14 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTime2Value FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( ODBC::TimeStamp ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest15
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest15 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( ODBC::TimeStampOffset ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest16
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest16 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( ODBC::TimeStamp ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest17
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest17 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( ODBC::Time2 ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest18
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest18 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, UniqueidentifierValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == sizeof( Guid ) );
}

// --run_test=StatementTests/ColumnBinaryLengthTest19
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest19 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RowVersionValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 8 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest20
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest20 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 4 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest21
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest21 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 0 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest22
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest22 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, CharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 4 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest23
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest23 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 0 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest24
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest24 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 8 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest25
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest25 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NVarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 0 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest26
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest26 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 2147483647 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest27
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest27 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NTextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 2147483646 );
}

// --run_test=StatementTests/ColumnBinaryLengthTest28
BOOST_AUTO_TEST_CASE( ColumnBinaryLengthTest28 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, ImageValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnBinaryLength = statement.ColumnBinaryLength( 2 );
    BOOST_CHECK( columnBinaryLength == 2147483647 );
}

// --run_test=StatementTests/ColumnPrecisionTest1
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 1 );
}

// --run_test=StatementTests/ColumnPrecisionTest2
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TinyIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 3 );
}

// --run_test=StatementTests/ColumnPrecisionTest3
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 5 );
}

// --run_test=StatementTests/ColumnPrecisionTest4
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, IntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 10 );
}

// --run_test=StatementTests/ColumnPrecisionTest5
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BigIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 19 );
}

// --run_test=StatementTests/ColumnPrecisionTest6
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 38 );
}

// --run_test=StatementTests/ColumnPrecisionTest7
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NumericValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 18 );
}

// --run_test=StatementTests/ColumnPrecisionTest8
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RealValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    // 24-bit precision
    BOOST_CHECK( columnPrecision == 24 );
}

// --run_test=StatementTests/ColumnPrecisionTest9
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    // 53-bit precision
    BOOST_CHECK( columnPrecision == 53 );
}

// --run_test=StatementTests/ColumnPrecisionTest10
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 10 );
}

// --run_test=StatementTests/ColumnPrecisionTest11
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest11 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 19 );
}

// --run_test=StatementTests/ColumnPrecisionTest12
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest12 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 0 );
}

// --run_test=StatementTests/ColumnPrecisionTest13
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest13 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 3 );
}

// --run_test=StatementTests/ColumnPrecisionTest14
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest14 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTime2Value FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 7 );
}

// --run_test=StatementTests/ColumnPrecisionTest15
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest15 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 7 );
}

// --run_test=StatementTests/ColumnPrecisionTest16
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest16 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 0 );
}

// --run_test=StatementTests/ColumnPrecisionTest17
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest17 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 7 );
}

// --run_test=StatementTests/ColumnPrecisionTest18
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest18 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, UniqueidentifierValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 36 );
}

// --run_test=StatementTests/ColumnPrecisionTest19
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest19 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RowVersionValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 8 );
}

// --run_test=StatementTests/ColumnPrecisionTest20
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest20 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 4 );
}

// --run_test=StatementTests/ColumnPrecisionTest21
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest21 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 0 );
}


// --run_test=StatementTests/ColumnPrecisionTest22
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest22 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, CharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 4 );
}

// --run_test=StatementTests/ColumnPrecisionTest23
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest23 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 0 );
}

// --run_test=StatementTests/ColumnPrecisionTest24
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest24 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 4 );
}

// --run_test=StatementTests/ColumnPrecisionTest25
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest25 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NVarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 0 );
}

// --run_test=StatementTests/ColumnPrecisionTest26
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest26 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 2147483647 );
}

// --run_test=StatementTests/ColumnPrecisionTest27
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest27 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NTextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 1073741823 );
}

// --run_test=StatementTests/ColumnPrecisionTest28
BOOST_AUTO_TEST_CASE( ColumnPrecisionTest28 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, ImageValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnPrecision = statement.ColumnPrecision( 2 );
    BOOST_CHECK( columnPrecision == 2147483647 );
}

// --run_test=StatementTests/ColumnScaleTest1
BOOST_AUTO_TEST_CASE( ColumnScaleTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 4 );
}

// --run_test=StatementTests/ColumnScaleTest2
BOOST_AUTO_TEST_CASE( ColumnScaleTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NumericValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 6 );
}

// --run_test=StatementTests/ColumnScaleTest3
BOOST_AUTO_TEST_CASE( ColumnScaleTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 4 );
}

// --run_test=StatementTests/ColumnScaleTest4
BOOST_AUTO_TEST_CASE( ColumnScaleTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 4 );
}


// --run_test=StatementTests/ColumnScaleTest5
BOOST_AUTO_TEST_CASE( ColumnScaleTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 3 );
}


// --run_test=StatementTests/ColumnScaleTest6
BOOST_AUTO_TEST_CASE( ColumnScaleTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTime2Value FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 7 );
}

// --run_test=StatementTests/ColumnScaleTest7
BOOST_AUTO_TEST_CASE( ColumnScaleTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 7 );
}

// --run_test=StatementTests/ColumnScaleTest8
BOOST_AUTO_TEST_CASE( ColumnScaleTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 0 );
}


// --run_test=StatementTests/ColumnScaleTest9
BOOST_AUTO_TEST_CASE( ColumnScaleTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 7 );
}


// --run_test=StatementTests/ColumnScaleTest10
BOOST_AUTO_TEST_CASE( ColumnScaleTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnScale = statement.ColumnScale( 2 );
    BOOST_CHECK( columnScale == 0 );
}

// --run_test=StatementTests/ColumnSchemaNameTest1
BOOST_AUTO_TEST_CASE( ColumnSchemaNameTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1 FOR BROWSE" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSchemaName = statement.ColumnSchemaName( 2 );
    BOOST_CHECK( columnSchemaName.IsEmpty() );
}


// --run_test=StatementTests/ColumnSchemaNameTest2
BOOST_AUTO_TEST_CASE( ColumnSchemaNameTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestSchema.TestTable3 FOR BROWSE" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSchemaName = statement.ColumnSchemaName( 2 );
    BOOST_CHECK( columnSchemaName == L"TestSchema" );
}


// --run_test=StatementTests/ColumnSearchPredicatesTest1
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest2
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TinyIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest3
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest4
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, IntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest5
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BigIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest6
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}


// --run_test=StatementTests/ColumnSearchPredicatesTest7
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NumericValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest8
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RealValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest9
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest10
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest11
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest11 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest12
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest12 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest13
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest13 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest14
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest14 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTime2Value FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest15
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest15 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest16
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest16 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest17
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest17 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest18
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest18 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, UniqueidentifierValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest19
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest19 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RowVersionValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest20
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest20 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest21
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest21 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::AllExceptLike );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest22
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest22 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, CharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest23
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest23 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}


// --run_test=StatementTests/ColumnSearchPredicatesTest24
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest24 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest25
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest25 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NVarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::Searchable );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest26
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest26 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::LikeOnly );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest27
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest27 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NTextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::LikeOnly );
}

// --run_test=StatementTests/ColumnSearchPredicatesTest28
BOOST_AUTO_TEST_CASE( ColumnSearchPredicatesTest28 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, ImageValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnSearchPredicates = statement.ColumnSearchPredicates( 2 );
    BOOST_CHECK( columnSearchPredicates == SearchPredicates::None );
}

// --run_test=StatementTests/ColumnTableNameTest1
BOOST_AUTO_TEST_CASE( ColumnTableNameTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1 FOR BROWSE" );
    BOOST_CHECK( rc == Result::Success );
    auto columnTableName = statement.ColumnTableName( 2 );
    BOOST_CHECK( columnTableName == L"TestTable1" );
}

// --run_test=StatementTests/ColumnTypeTest1
BOOST_AUTO_TEST_CASE( ColumnTypeTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Bit );
}

// --run_test=StatementTests/ColumnTypeTest2
BOOST_AUTO_TEST_CASE( ColumnTypeTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TinyIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::TinyInt );
}

// --run_test=StatementTests/ColumnTypeTest3
BOOST_AUTO_TEST_CASE( ColumnTypeTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::SmallInt );
}

// --run_test=StatementTests/ColumnTypeTest4
BOOST_AUTO_TEST_CASE( ColumnTypeTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, IntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Integer );
}

// --run_test=StatementTests/ColumnTypeTest5
BOOST_AUTO_TEST_CASE( ColumnTypeTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BigIntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::BigInt );
}

// --run_test=StatementTests/ColumnTypeTest6
BOOST_AUTO_TEST_CASE( ColumnTypeTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DecimalValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Decimal );
}

// --run_test=StatementTests/ColumnTypeTest7
BOOST_AUTO_TEST_CASE( ColumnTypeTest7 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NumericValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Numeric );
}

// --run_test=StatementTests/ColumnTypeTest8
BOOST_AUTO_TEST_CASE( ColumnTypeTest8 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RealValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Real );
}

// --run_test=StatementTests/ColumnTypeTest9
BOOST_AUTO_TEST_CASE( ColumnTypeTest9 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, FloatValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Float );
}

// --run_test=StatementTests/ColumnTypeTest10
BOOST_AUTO_TEST_CASE( ColumnTypeTest10 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Decimal );
}

// --run_test=StatementTests/ColumnTypeTest11
BOOST_AUTO_TEST_CASE( ColumnTypeTest11 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, MoneyValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Decimal );
}

// --run_test=StatementTests/ColumnTypeTest12
BOOST_AUTO_TEST_CASE( ColumnTypeTest12 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Date );
}

// --run_test=StatementTests/ColumnTypeTest13
BOOST_AUTO_TEST_CASE( ColumnTypeTest13 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::DateTime );
}

// --run_test=StatementTests/ColumnTypeTest14
BOOST_AUTO_TEST_CASE( ColumnTypeTest14 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTime2Value FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::DateTime );
}

// --run_test=StatementTests/ColumnTypeTest15
BOOST_AUTO_TEST_CASE( ColumnTypeTest15 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::TimeStampOffset );
}

// --run_test=StatementTests/ColumnTypeTest16
BOOST_AUTO_TEST_CASE( ColumnTypeTest16 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::DateTime );
}

// --run_test=StatementTests/ColumnTypeTest17
BOOST_AUTO_TEST_CASE( ColumnTypeTest17 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TimeValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Time2 );
}

// --run_test=StatementTests/ColumnTypeTest18
BOOST_AUTO_TEST_CASE( ColumnTypeTest18 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, UniqueidentifierValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Guid );
}

// --run_test=StatementTests/ColumnTypeTest19
BOOST_AUTO_TEST_CASE( ColumnTypeTest19 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, RowVersionValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Binary );
}

// --run_test=StatementTests/ColumnTypeTest20
BOOST_AUTO_TEST_CASE( ColumnTypeTest20 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Binary );
}

// --run_test=StatementTests/ColumnTypeTest21
BOOST_AUTO_TEST_CASE( ColumnTypeTest21 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::VarBinary );
}

// --run_test=StatementTests/ColumnTypeTest22
BOOST_AUTO_TEST_CASE( ColumnTypeTest22 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, CharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::Char );
}

// --run_test=StatementTests/ColumnTypeTest23
BOOST_AUTO_TEST_CASE( ColumnTypeTest23 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, VarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::VarChar );
}

// --run_test=StatementTests/ColumnTypeTest24
BOOST_AUTO_TEST_CASE( ColumnTypeTest24 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::WChar );
}

// --run_test=StatementTests/ColumnTypeTest25
BOOST_AUTO_TEST_CASE( ColumnTypeTest25 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NVarCharValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::WVarChar );
}

// --run_test=StatementTests/ColumnTypeTest26
BOOST_AUTO_TEST_CASE( ColumnTypeTest26 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, TextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::LongVarChar );
}

// --run_test=StatementTests/ColumnTypeTest27
BOOST_AUTO_TEST_CASE( ColumnTypeTest27 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, NTextValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::WLongVarChar );
}

// --run_test=StatementTests/ColumnTypeTest28
BOOST_AUTO_TEST_CASE( ColumnTypeTest28 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, ImageValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnType = statement.ColumnType( 2 );
    BOOST_CHECK( columnType == SqlType::LongVarBinary );
}

// --run_test=StatementTests/ColumnTypeNameTest1
BOOST_AUTO_TEST_CASE( ColumnTypeNameTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnTypeName = statement.ColumnTypeName( 2 );
    BOOST_CHECK( columnTypeName == L"bit" );
}

// --run_test=StatementTests/ColumnIsUnnamedTest1
BOOST_AUTO_TEST_CASE( ColumnIsUnnamedTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnIsUnnamed = statement.ColumnIsUnnamed( 2 );
    BOOST_CHECK( columnIsUnnamed == false );
}

// --run_test=StatementTests/ColumnIsUnsignedTest1
BOOST_AUTO_TEST_CASE( ColumnIsUnsignedTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, IntValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnIsUnsigned = statement.ColumnIsUnsigned( 2 );
    BOOST_CHECK( columnIsUnsigned == false );
}


// --run_test=StatementTests/ColumnIsUpdatableTest1
BOOST_AUTO_TEST_CASE( ColumnIsUpdatableTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"SELECT Id, BitValue FROM TestTable1" );
    BOOST_CHECK( rc == Result::Success );
    auto columnIsUpdatable = statement.ColumnIsUpdatable( 2 );
    BOOST_CHECK( columnIsUpdatable.has_value() == false );
}


// --run_test=StatementTests/NumParamsTest1
BOOST_AUTO_TEST_CASE( NumParamsTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );


    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"{? = call TestFunction1(?,?)}" );
    BOOST_CHECK( rc == Result::Success );
    auto numParams = statement.NumParams( );
    BOOST_CHECK( numParams == 3 );
}

// --run_test=StatementTests/BindInt32ParameterTest1
BOOST_AUTO_TEST_CASE( BindInt32ParameterTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );


    auto statement = connection.CreateStatement( );
    rc = statement.Prepare( L"{? = call TestFunction1(?,?)}" );
    BOOST_CHECK( rc == Result::Success );

    int result = 0;
    int a = 1;
    int b = 2;

    statement.BindInt32Parameter( 1, &result, nullptr, ODBC::ParameterDirection::Output );
    statement.BindInt32Parameter( 2, &a );
    statement.BindInt32Parameter( 3, &b );
    statement.Execute( );
    BOOST_CHECK( result == 3 );

}

// --run_test=StatementTests/VarCharTest1
BOOST_AUTO_TEST_CASE( VarCharTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto deleteStatement = connection.CreateStatement( );
    deleteStatement.ExecDirect( L"DELETE FROM TestSchema.TestTable4" );


    auto insertStatement = connection.CreateStatement( );
    rc = insertStatement.Prepare( L"INSERT INTO TestSchema.TestTable4 VALUES(?,?)" );
    BOOST_CHECK( rc == Result::Success );
    Int64 id = 1;
    auto text = Generators::Generate<AnsiString>( 1'000'000ULL, "abcdefghijklmnopqrstuvwxyz1234567890" );
    
    insertStatement.BindInt64Parameter( 1, &id );
    insertStatement.BindVarCharParameter( 2, text );
    insertStatement.Execute( );

    auto selectStatement = connection.CreateStatement( );
    auto reader = selectStatement.ExecuteReader( L"SELECT Id, [Value] FROM TestSchema.TestTable4" );
    reader->Read( );
    auto retrievedId = reader->GetInt64( 1 );
    auto retrievedValue = reader->GetAnsiString( 2 );
    bool equal = retrievedValue == text;
    BOOST_CHECK( equal );

}


// --run_test=StatementTests/NVarCharTest1
BOOST_AUTO_TEST_CASE( NVarCharTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto deleteStatement = connection.CreateStatement( );
    deleteStatement.ExecDirect( L"DELETE FROM TestSchema.TestTable5" );


    auto insertStatement = connection.CreateStatement( );
    rc = insertStatement.Prepare( L"INSERT INTO TestSchema.TestTable5 VALUES(?,?)" );
    BOOST_CHECK( rc == Result::Success );
    Int64 id = 1;
    auto text = Generators::Generate<WideString>( 1'000'000ULL, L"abcdefghijklmnopqrstuvwxyz1234567890" );
    
    insertStatement.BindInt64Parameter( 1, &id );
    insertStatement.BindNVarCharParameter( 2, text );
    insertStatement.Execute( );

    auto selectStatement = connection.CreateStatement( );
    auto reader = selectStatement.ExecuteReader( L"SELECT Id, [Value] FROM TestSchema.TestTable5" );
    reader->Read( );
    auto retrievedId = reader->GetInt64( 1 );
    auto retrievedValue = reader->GetWideString( 2 );
    bool equal = retrievedValue == text;
    BOOST_CHECK( equal );

}

// --run_test=StatementTests/VarBinaryTest1
BOOST_AUTO_TEST_CASE( VarBinaryTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );

    auto deleteStatement = connection.CreateStatement( );
    deleteStatement.ExecDirect( L"DELETE FROM TestSchema.TestTable6" );


    auto insertStatement = connection.CreateStatement( );
    rc = insertStatement.Prepare( L"INSERT INTO TestSchema.TestTable6 VALUES(?,?)" );
    BOOST_CHECK( rc == Result::Success );
    Int64 id = 1;
    auto text = Generators::Generate<std::vector<Byte>>( 1'000'000ULL, "abcdefghijklmnopqrstuvwxyz1234567890" );
    
    insertStatement.BindInt64Parameter( 1, &id );
    insertStatement.BindVarBinaryParameter( 2, text );
    insertStatement.Execute( );

    auto selectStatement = connection.CreateStatement( );
    auto reader = selectStatement.ExecuteReader( L"SELECT Id, [Value] FROM TestSchema.TestTable6" );
    reader->Read( );
    auto retrievedId = reader->GetInt64( 1 );
    auto retrievedValue = reader->GetBinary( 2 );
    bool equal = retrievedValue == text;
    BOOST_CHECK( equal );

}




BOOST_AUTO_TEST_SUITE_END( )