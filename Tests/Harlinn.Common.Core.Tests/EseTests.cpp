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

#include "pch.h"

using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;

namespace
{
    WideString TestDataRoot = Environment::EnvironmentVariable( L"HCC_TEST_DATA_ROOT" );

    WideString DatabaseDir = IO::Path::Combine<WideString>( TestDataRoot, L"\\ESE\\Test" );
    WideString DatabasePath = DatabaseDir + L"\\Database.edb";
    WideString DatabaseSystemPath = DatabaseDir + L"\\System\\";
    WideString DatabaseLogfilePath = DatabaseDir + L"\\Log\\";


    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    class Engine
    {
    public:
        Ese::Instance instance;
        Ese::Session session;
        Ese::Database database;

        Engine( bool createNewDatabase = true )
        {
            instance = Ese::Instance( L"TestInstance" );
            instance.SetCreatePathIfNotExist( );
            instance.SetExceptionAction( Ese::ExceptionAction::None );
            instance.SetSystemPath( DatabaseSystemPath );
            instance.SetLogFilePath( DatabaseLogfilePath );

            session = instance.BeginSession( );
            if ( createNewDatabase )
            {
                database = session.CreateDatabase( DatabasePath, Ese::CreateDatabaseFlags::OverwriteExisting );
            }
            else
            {
                session.AttachDatabase( DatabasePath );
                database = session.OpenDatabase( DatabasePath );
            }
        }
    };
}

BOOST_FIXTURE_TEST_SUITE( EseTests, LocalFixture )

// --run_test=EseTests/StaticAssertsTest
BOOST_AUTO_TEST_CASE( StaticAssertsTest )
{
    // This test passes by compiling
    static_assert( std::is_nothrow_default_constructible_v<Ese::Table>, "Table must be default constructible" );
    static_assert( std::is_move_constructible_v<Ese::Table>, "Table must be move constructible" );
    static_assert( std::is_move_assignable_v<Ese::Table>, "Table must be move assignable" );
    static_assert( !std::is_copy_constructible_v<Ese::Table>, "Table must not be copy constructible" );
    static_assert( !std::is_copy_assignable_v<Ese::Table>, "Table must be copy assignable" );

    static_assert( std::is_nothrow_default_constructible_v<Ese::Database>, "Database must be default constructible" );
    static_assert( std::is_move_constructible_v<Ese::Database>, "Database must be move constructible" );
    static_assert( std::is_move_assignable_v<Ese::Database>, "Database must be move assignable" );
    static_assert( !std::is_copy_constructible_v<Ese::Database>, "Database must not be copy constructible" );
    static_assert( !std::is_copy_assignable_v<Ese::Database>, "Database must be copy assignable" );

    static_assert( std::is_nothrow_default_constructible_v<Ese::Session>, "Session must be default constructible" );
    static_assert( std::is_move_constructible_v<Ese::Session>, "Session must be move constructible" );
    static_assert( std::is_move_assignable_v<Ese::Session>, "Session must be move assignable" );
    static_assert( !std::is_copy_constructible_v<Ese::Session>, "Session must not be copy constructible" );
    static_assert( !std::is_copy_assignable_v<Ese::Session>, "Session must be copy assignable" );

    static_assert( std::is_nothrow_default_constructible_v<Ese::Instance>, "Instance must be default constructible" );
    static_assert( std::is_move_constructible_v<Ese::Instance>, "Instance must be move constructible" );
    static_assert( std::is_move_assignable_v<Ese::Instance>, "Instance must be move assignable" );
    static_assert( !std::is_copy_constructible_v<Ese::Instance>, "Instance must not be copy constructible" );
    static_assert( !std::is_copy_assignable_v<Ese::Instance>, "Instance must be copy assignable" );


}




// --run_test=EseTests/InstanceConstructorTest
BOOST_AUTO_TEST_CASE( InstanceConstructorTest )
{
    Ese::Instance instance( L"TestInstance" );
    BOOST_TEST( instance.IsValid() );
}

// --run_test=EseTests/InstanceMoveConstructorTest
BOOST_AUTO_TEST_CASE( InstanceMoveConstructorTest )
{
    Ese::Instance instance1( L"TestInstance" );
    BOOST_TEST( instance1.IsValid() );
    Ese::Instance instance2 = std::move( instance1 );
    BOOST_TEST( instance1.IsValid() == false );
    BOOST_TEST( instance2.IsValid() );

}


// --run_test=EseTests/InstanceInitializationTest
BOOST_AUTO_TEST_CASE( InstanceInitializationTest )
{
    Ese::Instance instance( L"TestInstance" );
    BOOST_TEST( instance.IsValid() );
    instance.SetCreatePathIfNotExist( );
    instance.SetExceptionAction( Ese::ExceptionAction::None );
    instance.SetCircularLog( true );
    instance.SetSystemPath( DatabaseSystemPath );
    instance.SetLogFilePath( DatabaseLogfilePath );

    auto session = instance.BeginSession( );
    BOOST_TEST( session.IsValid() );
    auto database = session.CreateDatabase( DatabasePath, Ese::CreateDatabaseFlags::OverwriteExisting );
    BOOST_TEST( database.IsValid() );

}

// --run_test=EseTests/CreateTableTest1
BOOST_AUTO_TEST_CASE( CreateTableTest1 )
{
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
}

// --run_test=EseTests/CreateTableWithBooleanColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithBooleanColumnTest1 )
{
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddBoolean( "fieldName" );
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, true );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert() );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<bool>( columnId );
    BOOST_TEST( value1.has_value() );
    BOOST_TEST( value1.value_or( false ) );
    auto value2 = false;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 );
}

// --run_test=EseTests/CreateTableWithBooleanColumnTest2
BOOST_AUTO_TEST_CASE( CreateTableWithBooleanColumnTest2 )
{
    // Initialize the Extensible Storage Engine
    Ese::Instance instance( L"TestInstance" );
    // Set the path to the directory that will contain the checkpoint file for the instance 
    instance.SetSystemPath( DatabaseSystemPath );
    // Set the path to the directory that will contain the transaction log files for the instance 
    instance.SetLogFilePath( DatabaseLogfilePath );

    // Create the session
    auto session = instance.BeginSession( );
    // Create or open the database overwriting any existing data
    auto database = session.CreateDatabase( DatabasePath, Ese::CreateDatabaseFlags::OverwriteExisting );
    // Create a table
    auto table1 = database.CreateTable( "table1" );
    // Add a column
    auto columnId = table1.AddBoolean( "fieldName" );
    auto DoInsert = [ &table1, columnId ]( )
        {
            // Insert a new row
            table1.Insert( );
            // Assign a value to the column
            table1.SetColumn( columnId, true );
            // Write the data to the table
            table1.Store( );
        };
    // Inser two rows of data
    DoInsert( );
    DoInsert( );
    
    // Move the table cursor to the first row
    if ( table1.MoveFirst( ) )
    {
        // Retrieve the column value as a std::optional<bool>
        auto value1 = table1.As<bool>( columnId );
        // Move the table cursor to the next row
        if ( table1.MoveNext( ) )
        {
            auto value2 = false;
            // Retrieve the column value by passing a reference
            // to the variable that will be assigned the column
            // value 
            auto columnNotNull = table1.Read( columnId, value2 );
            // Verify that the data is as expected
            assert( columnNotNull == value1.has_value( ) == true );
            assert( value2 == value1.value( ) == true );
            // Verify that there are no more rows
            assert( table1.MoveNext( ) == false );
        }
    }
}

// --run_test=EseTests/CreateTableWithNullableBooleanColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableBooleanColumnTest1 )
{
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddBoolean( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, true );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, false );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<bool>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( false ) );
    auto value2 = false;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == false );
}


// --run_test=EseTests/CreateTableWithSByteColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithSByteColumnTest1 )
{
    using ValueType = char;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddSByte( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    char value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableSByteColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableSByteColumnTest1 )
{
    using ValueType = char;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddSByte( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    char value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

// --run_test=EseTests/CreateTableWithByteColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithByteColumnTest1 )
{
    using ValueType = Byte;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddByte( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableByteColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableByteColumnTest1 )
{
    using ValueType = Byte;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddByte( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}


// --run_test=EseTests/CreateTableWithInt16ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithInt16ColumnTest1 )
{
    using ValueType = Int16;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddInt16( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableInt16ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableInt16ColumnTest1 )
{
    using ValueType = Int16;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddInt16( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}


// --run_test=EseTests/CreateTableWithUInt16ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithUInt16ColumnTest1 )
{
    using ValueType = UInt16;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddUInt16( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableUInt16ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableUInt16ColumnTest1 )
{
    using ValueType = UInt16;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddUInt16( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

// --run_test=EseTests/CreateTableWithInt32ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithInt32ColumnTest1 )
{
    using ValueType = Int32;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddInt32( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableInt32ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableInt32ColumnTest1 )
{
    using ValueType = Int32;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddInt32( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}


// --run_test=EseTests/CreateTableWithUInt32ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithUInt32ColumnTest1 )
{
    using ValueType = UInt32;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddUInt32( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableUInt32ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableUInt32ColumnTest1 )
{
    using ValueType = UInt32;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddUInt32( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

// --run_test=EseTests/CreateTableWithInt64ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithInt64ColumnTest1 )
{
    using ValueType = Int64;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddInt64( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableInt64ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableInt64ColumnTest1 )
{
    using ValueType = Int64;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddInt64( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}


// --run_test=EseTests/CreateTableWithUInt64ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithUInt64ColumnTest1 )
{
    using ValueType = UInt64;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddUInt64( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableUInt64ColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableUInt64ColumnTest1 )
{
    using ValueType = UInt64;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddUInt64( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

// --run_test=EseTests/CreateTableWithSingleColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithSingleColumnTest1 )
{
    using ValueType = float;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddSingle( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableSingleColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableSingleColumnTest1 )
{
    using ValueType = float;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddSingle( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

// --run_test=EseTests/CreateTableWithDoubleColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithDoubleColumnTest1 )
{
    using ValueType = Double;
    constexpr ValueType ValueToInsert = 1;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddDouble( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableDoubleColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableDoubleColumnTest1 )
{
    using ValueType = Double;
    constexpr ValueType FirstValueToInsert = 1;
    constexpr ValueType SecondValueToInsert = 2;
    constexpr ValueType InitialValue = 0;
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddDouble( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert ]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert ]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

// --run_test=EseTests/CreateTableWithCurrencyColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithCurrencyColumnTest1 )
{
    using ValueType = Currency;
    constexpr ValueType ValueToInsert = Currency( 1 );
    constexpr ValueType InitialValue = Currency( 0 );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddCurrency( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableCurrencyColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableCurrencyColumnTest1 )
{
    using ValueType = Currency;
    constexpr ValueType FirstValueToInsert = Currency( 1 );
    constexpr ValueType SecondValueToInsert = Currency( 2 );
    constexpr ValueType InitialValue = Currency( 0 );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddCurrency( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}



// --run_test=EseTests/CreateTableWithTimeSpanColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithTimeSpanColumnTest1 )
{
    using ValueType = TimeSpan;
    constexpr ValueType ValueToInsert = TimeSpan( 1 );
    constexpr ValueType InitialValue = TimeSpan( 0 );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddTimeSpan( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableTimeSpanColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableTimeSpanColumnTest1 )
{
    using ValueType = TimeSpan;
    constexpr ValueType FirstValueToInsert = TimeSpan( 1 );
    constexpr ValueType SecondValueToInsert = TimeSpan( 2 );
    constexpr ValueType InitialValue = TimeSpan( 0 );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddTimeSpan( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}


// --run_test=EseTests/CreateTableWithDateTimeColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithDateTimeColumnTest1 )
{
    using ValueType = DateTime;
    ValueType ValueToInsert( 2020, 2, 1 );
    ValueType InitialValue( 2020, 1, 1 );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddDateTime( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableDateTimeColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableDateTimeColumnTest1 )
{
    using ValueType = DateTime;
    ValueType FirstValueToInsert( 2020, 2, 1 );
    ValueType SecondValueToInsert( 2020, 3, 1 );
    ValueType InitialValue( 2020, 1, 1 );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddDateTime( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

// --run_test=EseTests/CreateTableWithGuidColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithGuidColumnTest1 )
{
    using ValueType = Guid;
    ValueType ValueToInsert( L"{6FFE553E-0511-4FDA-9EAC-739C4D1A8842}" );
    ValueType InitialValue( L"{40E85BE1-9056-482A-9C7E-E416990B1373}" );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddGuid( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableGuidColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableGuidColumnTest1 )
{
    using ValueType = Guid;
    ValueType FirstValueToInsert( L"{C0119F86-22B4-4229-81C1-2B1E1CBB1FEE}" );
    ValueType SecondValueToInsert( L"{2BDA7975-FF66-433D-980D-B23E32C45353}" );
    ValueType InitialValue( L"{4E0BFC59-09FA-469A-9F4D-A886087D4870}" );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddGuid( "fieldName", Ese::ColumnFlags::Fixed );
    auto DoInsert = [&table1, columnId, FirstValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

// --run_test=EseTests/CreateTableWithTextColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithTextColumnTest1 )
{
    using ValueType = AnsiString;
    ValueType ValueToInsert( "Text to store" );
    ValueType InitialValue( "Not stored" );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddText( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<AnsiString>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableTextColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableTextColumnTest1 )
{
    using ValueType = AnsiString;
    ValueType FirstValueToInsert( "Text to store" );;
    ValueType SecondValueToInsert( "Second Text to store" );;
    ValueType InitialValue( "Not stored" );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddText( "fieldName", 127, 1200, Ese::ColumnFlags::None );
    auto DoInsert = [&table1, columnId, FirstValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}


// --run_test=EseTests/CreateTableWithBinaryColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithBinaryColumnTest1 )
{
    using ValueType = std::vector<Byte>;
    ValueType ValueToInsert( { 'B','I','N','A','R','Y', '\x20', 'T', 'O', '\x20', 'S', 'T', 'O', 'R', 'E' } );
    ValueType InitialValue( {'N','O','T','\x20','S','T','O','R', 'E', 'D'} );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddBinary( "fieldName" );
    auto DoInsert = [&table1, columnId, ValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Store( );
    };

    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == ValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == ValueToInsert );
}

// --run_test=EseTests/CreateTableWithNullableBinaryColumnTest1
BOOST_AUTO_TEST_CASE( CreateTableWithNullableBinaryColumnTest1 )
{
    using ValueType = std::vector<Byte>;
    ValueType FirstValueToInsert( { 'B','I','N','A','R','Y', '\x20', 'T', 'O', '\x20', 'S', 'T', 'O', 'R', 'E' } );
    ValueType SecondValueToInsert( { 'S','E','C','O','N','D','\x20','B','I','N','A','R','Y', '\x20', 'T', 'O', '\x20', 'S', 'T', 'O', 'R', 'E' } );
    ValueType InitialValue( { 'N','O','T','\x20','S','T','O','R', 'E', 'D' } );
    Engine engine;
    auto& database = engine.database;
    auto table1 = database.CreateTable( "table1" );
    BOOST_TEST( table1.IsValid( ) );
    auto columnId = table1.AddBinary( "fieldName", 255, Ese::ColumnFlags::None );
    auto DoInsert = [&table1, columnId, FirstValueToInsert]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Store( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Store( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Store( );
    };


    BOOST_REQUIRE_NO_THROW( DoInsert( ) );
    bool moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    auto value1 = table1.As<ValueType>( columnId );
    BOOST_TEST( value1.has_value( ) );
    BOOST_TEST( value1.value_or( InitialValue ) == FirstValueToInsert );
    ValueType value2 = InitialValue;
    auto notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == FirstValueToInsert );

    BOOST_REQUIRE_NO_THROW( DoInsertNull( ) );
    moveResult = table1.MoveFirst( );
    BOOST_TEST( moveResult );
    moveResult = table1.MoveNext( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull == false );

    BOOST_REQUIRE_NO_THROW( DoReplace( ) );
    moveResult = table1.MoveLast( );
    BOOST_TEST( moveResult );
    notNull = table1.Read( columnId, value2 );
    BOOST_TEST( notNull );
    BOOST_TEST( value2 == SecondValueToInsert );
}

struct SensorValue
{
    boost::uuids::uuid Sensor;
    std::chrono::system_clock::time_point Timestamp;
    int64_t Flags = 0;
    double Value = 0.0;
};


class SensorEngine : public Engine
{
public:
    using Base = Engine;
    static constexpr char SensorValueTableName[] = "SV";
    static constexpr char SensorValueIndexName[] = "ISV";
    static constexpr char SensorColumnName[] = "S";
    static constexpr char TimestampColumnName[] = "T";
    static constexpr char FlagsColumnName[] = "F";
    static constexpr char ValueColumnName[] = "V";

    JET_COLUMNID SensorColumnId = 0;
    JET_COLUMNID TimestampColumnId = 0;
    JET_COLUMNID FlagsColumnId = 0;
    JET_COLUMNID ValueColumnId = 0;
    Ese::Table SensorValues;

    SensorEngine( bool createDatabase = true )
        : Base( createDatabase )
    {
    }

    void CreateSensorValueTable( )
    {
        auto transaction = session.StartTransaction( );
        SensorValues = database.CreateTable( SensorValueTableName );

        SensorColumnId = SensorValues.AddGuid( SensorColumnName );
        TimestampColumnId = SensorValues.AddDateTime( TimestampColumnName );
        FlagsColumnId = SensorValues.AddUInt64( FlagsColumnName );
        ValueColumnId = SensorValues.AddDouble( ValueColumnName );
        SensorValues.CreateIndex( SensorValueIndexName, Ese::IndexFlags::Primary, "+S\0+T\0", 7 );

        transaction.Commit( );
    }

    void OpenSensorValueTable( )
    {
        SensorValues = database.OpenTable( SensorValueTableName );

        SensorColumnId = SensorValues.GetColumnId( SensorColumnName );
        TimestampColumnId = SensorValues.GetColumnId( TimestampColumnName );
        FlagsColumnId = SensorValues.GetColumnId( FlagsColumnName );
        ValueColumnId = SensorValues.GetColumnId( ValueColumnName );
    }

    void Insert( const SensorValue& value )
    {
        SensorValues.Insert( );
        SensorValues.SetColumn( SensorColumnId, value.Sensor );
        SensorValues.SetColumn( TimestampColumnId, value.Timestamp );
        SensorValues.SetColumn( FlagsColumnId, value.Flags );
        SensorValues.SetColumn( ValueColumnId, value.Value );
        SensorValues.Store( );
    }

    size_t Insert( size_t sensorCount, const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end, const std::chrono::system_clock::duration& step, double valueOffset = 0.0 )
    {
        if ( sensorCount > 10000 )
        {
            sensorCount = 10000;
        }
        std::chrono::system_clock::time_point current = start;
        SensorValue sensorValue;
        size_t count = 0;
        while ( current < end )
        {
            sensorValue.Timestamp = current;
            sensorValue.Value = static_cast<double>( count + 1 ) + valueOffset;
            for ( size_t i = 0; i < sensorCount; i++ )
            {
                sensorValue.Sensor = reinterpret_cast<const boost::uuids::uuid&>(Test::Ids[i]);
                Insert( sensorValue );
            }
            current += step;
            count++;
        }
        return count;
    }

    void Store( const SensorValue& value )
    {
        if ( MoveTo( value.Sensor, value.Timestamp ) )
        {
            SensorValues.Replace( );
            SensorValues.SetColumn( FlagsColumnId, value.Flags );
            SensorValues.SetColumn( ValueColumnId, value.Value );
            SensorValues.Store( );
        }
    }


    size_t Store( size_t sensorCount, const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end, const std::chrono::system_clock::duration& step, double valueOffset = 0.0 )
    {
        if ( sensorCount > 10000 )
        {
            sensorCount = 10000;
        }
        std::chrono::system_clock::time_point current = start;
        SensorValue sensorValue;
        size_t count = 0;
        while ( current < end )
        {
            sensorValue.Timestamp = current;
            sensorValue.Value = static_cast<double>( count + 1 ) + valueOffset;
            for ( size_t i = 0; i < sensorCount; i++ )
            {
                sensorValue.Sensor = reinterpret_cast< const boost::uuids::uuid& >( Test::Ids[ i ] );
                Store( sensorValue );
            }
            current += step;
            count++;
        }
        return count;
    }

    void Delete( const SensorValue& value )
    {
        if ( MoveTo( value.Sensor, value.Timestamp ) )
        {
            SensorValues.Delete( );
        }
    }



    boost::uuids::uuid Sensor( ) const
    {
        boost::uuids::uuid result;
        SensorValues.Read( SensorColumnId, result );
        return result;
    }
    std::chrono::system_clock::time_point Timestamp( ) const
    {
        std::chrono::system_clock::time_point result;
        SensorValues.Read( TimestampColumnId, result );
        return result;
    }
    int64_t Flags( ) const
    {
        int64_t result;
        SensorValues.Read( FlagsColumnId, result );
        return result;
    }

    double Value( ) const
    {
        double result;
        SensorValues.Read( ValueColumnId, result );
        return result;
    }

    SensorValue Retrieve( )
    {
        SensorValue result{ Sensor( ), Timestamp( ), Flags( ), Value( ) };
        return result;
    }



    bool MoveTo( const boost::uuids::uuid& sensorId ) const
    {
        SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey | Ese::KeyFlags::FullColumnStartLimit );
        auto rc = SensorValues.Seek( Ese::SeekFlags::GreaterOrEqual );
        return rc >= Ese::Result::Success;
    }

    bool MoveTo( const boost::uuids::uuid& sensorId, const std::chrono::system_clock::time_point& timestamp ) const
    {
        SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
        SensorValues.MakeKey( timestamp );
        auto rc = SensorValues.Seek( Ese::SeekFlags::LessOrEqual );
        return rc >= Ese::Result::Success;
    }

    bool MoveToLast( const boost::uuids::uuid& sensorId ) const
    {
        //SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
        //SensorValues.MakeKey( DateTime::MaxValue( ) );
        SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey | Ese::KeyFlags::FullColumnEndLimit );

        auto rc = SensorValues.Seek( Ese::SeekFlags::LessOrEqual );
        return rc >= Ese::Result::Success;
    }

    bool Filter( const boost::uuids::uuid& sensorId ) const
    {
        auto success = MoveTo( sensorId );
        if ( success )
        {
            SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey | Ese::KeyFlags::FullColumnEndLimit );
            SensorValues.SetIndexRange( Ese::IndexRangeFlags::Inclusive | Ese::IndexRangeFlags::UpperLimit );
            return true;
        }
        else
        {
            return false;
        }
    }



    bool ReverseFilter( const boost::uuids::uuid& sensorId ) const
    {
        auto success = MoveToLast( sensorId );
        if ( success )
        {
            SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey | Ese::KeyFlags::FullColumnStartLimit );
            SensorValues.SetIndexRange( Ese::IndexRangeFlags::Inclusive);
            return true;
        }
        else
        {
            return false;
        }
    }


};



// --run_test=EseTests/CreateSensorValueTableTest1
BOOST_AUTO_TEST_CASE( CreateSensorValueTableTest1 )
{
    SensorEngine engine;
    auto& database = engine.database;
    engine.CreateSensorValueTable( );
    BOOST_TEST( engine.SensorValues.IsValid( ) );
}

// --run_test=EseTests/InsertSearchAndUpdateSensorValueTableTest1
BOOST_AUTO_TEST_CASE( InsertSearchAndUpdateSensorValueTableTest1 )
{
    SensorEngine engine;
    auto& database = engine.database;
    engine.CreateSensorValueTable( );
    BOOST_TEST( engine.SensorValues.IsValid( ) );
    auto& sensorValues = engine.SensorValues;

    DateTime start( 2020, 1, 1 );
    DateTime end( 2020, 1, 2 );
    TimeSpan step = TimeSpan::FromHours( 1 );
    auto count = engine.Insert( 3, start.ToTimePoint(), end.ToTimePoint( ), step.ToDuration() );
    BOOST_TEST( count > 0 );

    auto firstSensor = reinterpret_cast< const boost::uuids::uuid& >( Test::Ids[ 0 ] );
    auto secondSensor = reinterpret_cast< const boost::uuids::uuid& >( Test::Ids[ 1 ] );
    auto thirdSensor = reinterpret_cast< const boost::uuids::uuid& >( Test::Ids[ 2 ] );
    auto fourthSensor = reinterpret_cast< const boost::uuids::uuid& >( Test::Ids[ 3 ] );

    auto success = sensorValues.MoveFirst( );
    BOOST_CHECK( success );
    if ( success )
    {
        size_t rowCount = 0;
        double sum = 0.0;
        do
        {
            sum += engine.Value( );
            rowCount++;
        } while ( sensorValues.MoveNext( ) );
        BOOST_CHECK( rowCount == 72 );
        BOOST_CHECK( sum == 900 );
    }


    success = engine.MoveTo( firstSensor );
    BOOST_CHECK( success );
    if ( success )
    {
        size_t rowCount = 0;
        double sum = 0.0;
        do
        {
            auto sensorId = engine.Sensor( );
            if ( sensorId != firstSensor )
            {
                break;
            }
            sum += engine.Value( );
            rowCount++;
        } while ( sensorValues.MoveNext( ) );
        BOOST_CHECK( rowCount == 24 );
        BOOST_CHECK( sum == 300 );
    }

    success = engine.Filter( secondSensor );
    BOOST_CHECK( success );
    if ( success )
    {
        size_t rowCount = 0;
        double sum = 0.0;
        do
        {
            sum += engine.Value( );
            rowCount++;
        } while ( sensorValues.MoveNext( ) );
        BOOST_CHECK( rowCount == 24 );
        BOOST_CHECK( sum == 300 );
    }


    success = engine.MoveTo( thirdSensor, start.ToTimePoint( ) + TimeSpan::FromHours( 12.5 ).ToDuration() );
    BOOST_CHECK( success );
    if ( success )
    {
        size_t rowCount = 0;
        double sum = 0.0;
        do
        {
            auto sensorId = engine.Sensor( );
            if ( sensorId != thirdSensor )
            {
                break;
            }
            sum += engine.Value( );
            rowCount++;
        } while ( sensorValues.MoveNext( ) );
        BOOST_CHECK( rowCount == 12 );
        BOOST_CHECK( sum == 222 );
    }

    count = engine.Store( 2, start.ToTimePoint(), end.ToTimePoint(), step.ToDuration(), 1.0 );

    success = engine.MoveToLast( secondSensor );
    BOOST_CHECK( success );
    if ( success )
    {
        size_t rowCount = 0;
        double sum = 0.0;
        do
        {
            auto sensorId = engine.Sensor( );
            if ( sensorId != secondSensor )
            {
                break;
            }
            sum += engine.Value( );
            rowCount++;
        } while ( sensorValues.MovePrevious( ) );
        BOOST_CHECK( rowCount == 24 );
        BOOST_CHECK( sum == 324 );
    }

    success = engine.ReverseFilter( secondSensor );
    BOOST_CHECK( success );
    if ( success )
    {
        size_t rowCount = 0;
        double sum = 0.0;
        do
        {
            sum += engine.Value( );
            rowCount++;
        } while ( sensorValues.MovePrevious( ) );
        BOOST_CHECK( rowCount == 24 );
        BOOST_CHECK( sum == 324 );
    }

    success = sensorValues.MoveFirst( );
    BOOST_CHECK( success );
    if ( success )
    {
        size_t rowCount = 0;
        double sum = 0.0;
        do
        {
            sum += engine.Value( );
            rowCount++;
        } while ( sensorValues.MoveNext( ) );
        BOOST_CHECK( rowCount == 72 );
        BOOST_CHECK( sum == 948 );
    }


}


BOOST_AUTO_TEST_SUITE_END( )