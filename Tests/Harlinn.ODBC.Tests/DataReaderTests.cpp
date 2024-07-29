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

BOOST_FIXTURE_TEST_SUITE( DataReaderTests, LocalFixture )

// --run_test=DataReaderTests/DateReaderGetBooleanTest1
BOOST_AUTO_TEST_CASE( DateReaderGetBooleanTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, BitValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if( found )
    {
        auto boolval = reader->GetBoolean( 2 );
        BOOST_CHECK( boolval );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableBooleanTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableBooleanTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, BitValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableBoolval = reader->GetNullableBoolean( 2 );
        BOOST_CHECK( nullableBoolval.has_value( ) );
        BOOST_CHECK( nullableBoolval.value( ) );
    }
}


// --run_test=DataReaderTests/DateReaderGetSByteTest1
BOOST_AUTO_TEST_CASE( DateReaderGetSByteTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, TinyIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetSByte( 2 );
        BOOST_CHECK( value == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableSByteTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableSByteTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, TinyIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableSByte( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1 );
    }
}


// --run_test=DataReaderTests/DateReaderGetByteTest1
BOOST_AUTO_TEST_CASE( DateReaderGetByteTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, TinyIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetByte( 2 );
        BOOST_CHECK( value == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableByteTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableByteTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, TinyIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableByte( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1 );
    }
}


// --run_test=DataReaderTests/DateReaderGetInt16Test1
BOOST_AUTO_TEST_CASE( DateReaderGetInt16Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, SmallIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetInt16( 2 );
        BOOST_CHECK( value == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableInt16Test1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableInt16Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, SmallIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableInt16( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetUInt16Test1
BOOST_AUTO_TEST_CASE( DateReaderGetUInt16Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, SmallIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetUInt16( 2 );
        BOOST_CHECK( value == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableUInt16Test1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableUInt16Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, SmallIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableUInt16( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetInt32Test1
BOOST_AUTO_TEST_CASE( DateReaderGetInt32Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, IntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetInt32( 2 );
        BOOST_CHECK( value == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableInt32Test1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableInt32Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, IntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableInt32( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetUInt32Test1
BOOST_AUTO_TEST_CASE( DateReaderGetUInt32Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, IntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetUInt32( 2 );
        BOOST_CHECK( value == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableUInt32Test1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableUInt32Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, IntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableUInt32( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetInt64Test1
BOOST_AUTO_TEST_CASE( DateReaderGetInt64Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, BigIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetInt64( 2 );
        BOOST_CHECK( value == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableInt64Test1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableInt64Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, BigIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableInt64( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetUInt64Test1
BOOST_AUTO_TEST_CASE( DateReaderGetUInt64Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, BigIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetUInt64( 2 );
        BOOST_CHECK( value == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableUInt64Test1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableUInt64Test1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, BigIntValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableUInt64( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetDecimalTest1
BOOST_AUTO_TEST_CASE( DateReaderGetDecimalTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DecimalValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetDecimal( 2 );
        BOOST_CHECK( value.val[0] == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableDecimalTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableDecimalTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DecimalValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableDecimal( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ).val[ 0 ] == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNumericTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNumericTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, NumericValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetNumeric( 2 );
        BOOST_CHECK( value.val[ 0 ] == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableNumericTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableNumericTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, NumericValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableNumeric( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ).val[ 0 ] == 1 );
    }
}

// --run_test=DataReaderTests/DateReaderGetSingleTest1
BOOST_AUTO_TEST_CASE( DateReaderGetSingleTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, RealValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetSingle( 2 );
        BOOST_CHECK( value == 1.f );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableSingleTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableSingleTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, RealValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableSingle( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1.0f );
    }
}

// --run_test=DataReaderTests/DateReaderGetDoubleTest1
BOOST_AUTO_TEST_CASE( DateReaderGetDoubleTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, FloatValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetDouble( 2 );
        BOOST_CHECK( value == 1.0 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableDoubleTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableDoubleTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, FloatValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableDouble( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1.0 );
    }
}

// --run_test=DataReaderTests/DateReaderGetCurrencyTest1
BOOST_AUTO_TEST_CASE( DateReaderGetCurrencyTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetCurrency( 2 );
        BOOST_CHECK( value == 1.0 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableCurrencyTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableCurrencyTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, SmallMoneyValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableCurrency( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1.0 );
    }
}

// --run_test=DataReaderTests/DateReaderGetCurrencyTest2
BOOST_AUTO_TEST_CASE( DateReaderGetCurrencyTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, MoneyValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetCurrency( 2 );
        BOOST_CHECK( value == 1.0 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableCurrencyTest2
BOOST_AUTO_TEST_CASE( DateReaderGetNullableCurrencyTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, MoneyValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableCurrency( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == 1.0 );
    }
}


// --run_test=DataReaderTests/DateReaderGetDateTimeTest1
BOOST_AUTO_TEST_CASE( DateReaderGetDateTimeTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DateValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        DateTime expected( 2024, 2, 25 );
        auto value = reader->GetDateTime( 2 );
        BOOST_CHECK( value == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableDateTimeTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableDateTimeTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DateValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        DateTime expected( 2024, 2, 25 );
        auto nullableValue = reader->GetNullableDateTime( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetDateTimeTest2
BOOST_AUTO_TEST_CASE( DateReaderGetDateTimeTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DateTimeValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        DateTime expected( 2024, 2, 25, 12, 01, 01, 555 );
        auto value = reader->GetDateTime( 2 );
        auto diff = ( value - expected ).TotalSeconds( );
        BOOST_CHECK( diff < 0.01 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableDateTimeTest2
BOOST_AUTO_TEST_CASE( DateReaderGetNullableDateTimeTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DateTimeValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        DateTime expected( 2024, 2, 25, 12, 01, 01, 555 );
        auto nullableValue = reader->GetNullableDateTime( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        auto diff = ( nullableValue.value( ) - expected ).TotalSeconds( );
        BOOST_CHECK( diff < 0.01 );
    }
}

// --run_test=DataReaderTests/DateReaderGetDateTimeTest3
BOOST_AUTO_TEST_CASE( DateReaderGetDateTimeTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DateTime2Value FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        DateTime expected( 2011, 8, 15, 14, 23, 44, 500 );
        auto value = reader->GetDateTime( 2 );
        auto diff = ( value - expected ).TotalSeconds( );
        BOOST_CHECK( value == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableDateTimeTest3
BOOST_AUTO_TEST_CASE( DateReaderGetNullableDateTimeTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DateTime2Value FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        DateTime expected( 2011, 8, 15, 14, 23, 44, 500 );
        auto nullableValue = reader->GetNullableDateTime( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetDateTimeTest4
BOOST_AUTO_TEST_CASE( DateReaderGetDateTimeTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        DateTime expected( 2010, 12, 31, 23, 59, 0 );
        auto value = reader->GetDateTime( 2 );
        auto diff = ( value - expected ).TotalSeconds( );
        BOOST_CHECK( value == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableDateTimeTest4
BOOST_AUTO_TEST_CASE( DateReaderGetNullableDateTimeTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, SmallDateTimeValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        DateTime expected( 2010, 12, 31, 23, 59, 0 );
        auto nullableValue = reader->GetNullableDateTime( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == expected );
    }
}


// --run_test=DataReaderTests/DateReaderGetTimestampOffsetTest1
BOOST_AUTO_TEST_CASE( DateReaderGetTimestampOffsetTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetTimestampOffset( 2 );
        BOOST_CHECK( value.year == 2011 );
        BOOST_CHECK( value.month == 8 );
        BOOST_CHECK( value.day == 15 );
        BOOST_CHECK( value.hour == 14 );
        BOOST_CHECK( value.minute == 30 );
        BOOST_CHECK( value.second == 0 );
        BOOST_CHECK( value.fraction == 500000000 );
        BOOST_CHECK( value.timezoneHour == 12 );
        BOOST_CHECK( value.timezoneMinute == 30 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableTimestampOffsetTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableTimestampOffsetTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, DateTimeOffsetValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableTimestampOffset( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );

        BOOST_CHECK( nullableValue.value( ).year == 2011 );
        BOOST_CHECK( nullableValue.value( ).month == 8 );
        BOOST_CHECK( nullableValue.value( ).day == 15 );
        BOOST_CHECK( nullableValue.value( ).hour == 14 );
        BOOST_CHECK( nullableValue.value( ).minute == 30 );
        BOOST_CHECK( nullableValue.value( ).second == 0 );
        BOOST_CHECK( nullableValue.value( ).fraction == 500000000 );
        BOOST_CHECK( nullableValue.value( ).timezoneHour == 12 );
        BOOST_CHECK( nullableValue.value( ).timezoneMinute == 30 );
    }
}

// --run_test=DataReaderTests/DateReaderGetTimeTest1
BOOST_AUTO_TEST_CASE( DateReaderGetTimeTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, TimeValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetTime( 2 );
        BOOST_CHECK( value.hour == 23 );
        BOOST_CHECK( value.minute == 59 );
        BOOST_CHECK( value.second == 59 );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableTimeTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableTimeTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, TimeValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableTime( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );

        BOOST_CHECK( nullableValue.value().hour == 23 );
        BOOST_CHECK( nullableValue.value().minute == 59 );
        BOOST_CHECK( nullableValue.value().second == 59 );
    }
}


// --run_test=DataReaderTests/DateReaderGetBinaryTest1
BOOST_AUTO_TEST_CASE( DateReaderGetBinaryTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, BinaryValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetBinary( 2 );
        BOOST_CHECK( value[ 0 ] == 0x0F );
        BOOST_CHECK( value[ 1 ] == 0x0F );
        BOOST_CHECK( value[ 2 ] == 0x0F );
        BOOST_CHECK( value[ 3 ] == 0x0F );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableBinaryTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableBinaryTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, BinaryValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableBinary( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( )[ 0 ] == 0x0F );
        BOOST_CHECK( nullableValue.value( )[ 1 ] == 0x0F );
        BOOST_CHECK( nullableValue.value( )[ 2 ] == 0x0F );
        BOOST_CHECK( nullableValue.value()[ 3 ] == 0x0F );
    }
}



// --run_test=DataReaderTests/DateReaderGetBinaryTest2
BOOST_AUTO_TEST_CASE( DateReaderGetBinaryTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto value = reader->GetBinary( 2 );
        BOOST_CHECK( value[ 0 ] == 0x0F );
        BOOST_CHECK( value[ 1 ] == 0xFF );
        BOOST_CHECK( value[ 2 ] == 0xFF );
        BOOST_CHECK( value[ 3 ] == 0xFF );
        BOOST_CHECK( value[ 4 ] == 0x0F );
        BOOST_CHECK( value[ 5 ] == 0xFF );
        BOOST_CHECK( value[ 6 ] == 0xFF );
        BOOST_CHECK( value[ 7 ] == 0xFF );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableBinaryTest2
BOOST_AUTO_TEST_CASE( DateReaderGetNullableBinaryTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, VarBinaryValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        auto nullableValue = reader->GetNullableBinary( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( )[ 0 ] == 0x0F );
        BOOST_CHECK( nullableValue.value( )[ 1 ] == 0xFF );
        BOOST_CHECK( nullableValue.value( )[ 2 ] == 0xFF );
        BOOST_CHECK( nullableValue.value( )[ 3 ] == 0xFF );
        BOOST_CHECK( nullableValue.value( )[ 4 ] == 0x0F );
        BOOST_CHECK( nullableValue.value( )[ 5 ] == 0xFF );
        BOOST_CHECK( nullableValue.value( )[ 6 ] == 0xFF );
        BOOST_CHECK( nullableValue.value()[ 7 ] == 0xFF );
    }
}


// --run_test=DataReaderTests/DateReaderGetWideStringTest1
BOOST_AUTO_TEST_CASE( DateReaderGetWideStringTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, CharValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"abcd" );
        auto value = reader->GetWideString( 2 );
        BOOST_CHECK( value == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableWideStringTest1
BOOST_AUTO_TEST_CASE( DateReaderGetNullableWideStringTest1 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, CharValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"abcd" );
        auto nullableValue = reader->GetNullableWideString( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value() == expected );
    }
}


// --run_test=DataReaderTests/DateReaderGetWideStringTest2
BOOST_AUTO_TEST_CASE( DateReaderGetWideStringTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, VarCharValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"abcdef" );
        auto value = reader->GetWideString( 2 );
        BOOST_CHECK( value == expected );
    }
}


// --run_test=DataReaderTests/DateReaderGetNullableWideStringTest2
BOOST_AUTO_TEST_CASE( DateReaderGetNullableWideStringTest2 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, VarCharValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"abcdef" );
        auto nullableValue = reader->GetNullableWideString( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == expected );
    }
}



// --run_test=DataReaderTests/DateReaderGetWideStringTest3
BOOST_AUTO_TEST_CASE( DateReaderGetWideStringTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, NCharValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"abcd" );
        auto value = reader->GetWideString( 2 );
        BOOST_CHECK( value == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableWideStringTest3
BOOST_AUTO_TEST_CASE( DateReaderGetNullableWideStringTest3 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, NCharValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"abcd" );
        auto nullableValue = reader->GetNullableWideString( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == expected );
    }
}


// --run_test=DataReaderTests/DateReaderGetWideStringTest4
BOOST_AUTO_TEST_CASE( DateReaderGetWideStringTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, NVarCharValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"abcdef" );
        auto value = reader->GetWideString( 2 );
        BOOST_CHECK( value == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableWideStringTest4
BOOST_AUTO_TEST_CASE( DateReaderGetNullableWideStringTest4 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, NVarCharValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"abcdef" );
        auto nullableValue = reader->GetNullableWideString( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetWideStringTest5
BOOST_AUTO_TEST_CASE( DateReaderGetWideStringTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, TextValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"Text" );
        auto value = reader->GetWideString( 2 );
        BOOST_CHECK( value == expected );
    }
}

// --run_test=DataReaderTests/DateReaderGetNullableWideStringTest5
BOOST_AUTO_TEST_CASE( DateReaderGetNullableWideStringTest5 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, TextValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"Text" );
        auto nullableValue = reader->GetNullableWideString( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == expected );
    }
}



// --run_test=DataReaderTests/DateReaderGetWideStringTest6
BOOST_AUTO_TEST_CASE( DateReaderGetWideStringTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, NTextValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"NText" );
        auto value = reader->GetWideString( 2 );
        BOOST_CHECK( value == expected );
    }
}


// --run_test=DataReaderTests/DateReaderGetNullableWideStringTest6
BOOST_AUTO_TEST_CASE( DateReaderGetNullableWideStringTest6 )
{
    ODBC::Environment environment = ODBC::Environment::Create( );
    auto connection = environment.Connect( DataSource );
    auto rc = connection.SetCurrentCatalog( DatabaseName );
    auto currentCatalog = connection.CurrentCatalog( );
    bool areEqual = currentCatalog == DatabaseName;
    BOOST_CHECK( areEqual );

    auto statement = connection.CreateStatement( );
    auto reader = statement.ExecuteReader( L"SELECT Id, NTextValue FROM TestTable1" );
    auto found = reader->Read( );
    BOOST_CHECK( found );
    if ( found )
    {
        WideString expected( L"NText" );
        auto nullableValue = reader->GetNullableWideString( 2 );
        BOOST_CHECK( nullableValue.has_value( ) );
        BOOST_CHECK( nullableValue.value( ) == expected );
    }
}





BOOST_AUTO_TEST_SUITE_END( )