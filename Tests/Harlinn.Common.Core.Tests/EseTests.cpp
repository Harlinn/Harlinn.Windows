#include "pch.h"

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
            instance = Ese::Instance( "TestInstance" );
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
    Ese::Instance instance( "TestInstance" );
    BOOST_TEST( instance.IsValid() );
}

// --run_test=EseTests/InstanceMoveConstructorTest
BOOST_AUTO_TEST_CASE( InstanceMoveConstructorTest )
{
    Ese::Instance instance1( "TestInstance" );
    BOOST_TEST( instance1.IsValid() );
    Ese::Instance instance2 = std::move( instance1 );
    BOOST_TEST( instance1.IsValid() == false );
    BOOST_TEST( instance2.IsValid() );

}


// --run_test=EseTests/InstanceInitializationTest
BOOST_AUTO_TEST_CASE( InstanceInitializationTest )
{
    Ese::Instance instance( "TestInstance" );
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
        table1.Update( );
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
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, false );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, ValueToInsert );
        table1.Update( );
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
    auto DoInsert = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetColumn( columnId, FirstValueToInsert );
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
        table1.Update( );
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
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
        table1.Update( );
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
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
        table1.Update( );
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
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
        table1.Update( );
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
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
        table1.Update( );
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
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
        table1.Update( );
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
        table1.Update( );
    };

    auto DoInsertNull = [&table1, columnId]( )
    {
        table1.Insert( );
        table1.SetNull( columnId );
        table1.Update( );
    };

    auto DoReplace = [&table1, columnId, SecondValueToInsert]( )
    {
        table1.Replace( );
        table1.SetColumn( columnId, SecondValueToInsert );
        table1.Update( );
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
    Guid Sensor;
    DateTime Timestamp;
    Int64 Flags = 0;
    Double Value = 0.0;
};


class SensorEngine : public Engine
{
public:
    using Base = Engine;
    static WideString SensorValueTableName;
    static WideString SensorValueIndexName;
    static WideString SensorColumnName;
    static WideString TimestampColumnName;
    static WideString FlagsColumnName;
    static WideString ValueColumnName;
    JET_COLUMNID SensorColumnId;
    JET_COLUMNID TimestampColumnId;
    JET_COLUMNID FlagsColumnId;
    JET_COLUMNID ValueColumnId;
    Ese::Table SensorValues;

    SensorEngine( bool createDatabase = true )
        : Base( createDatabase )
    {
    }

    void CreateSensorValueTable( )
    {
        session.BeginTransaction( );
        SensorValues = database.CreateTable( SensorValueTableName );

        SensorColumnId = SensorValues.AddGuid( SensorColumnName );
        TimestampColumnId = SensorValues.AddDateTime( TimestampColumnName );
        FlagsColumnId = SensorValues.AddUInt64( FlagsColumnName );
        ValueColumnId = SensorValues.AddDouble( ValueColumnName );
        SensorValues.CreateIndex( SensorValueIndexName, Ese::IndexFlags::Primary, L"+S\0+T\0", 6 );

        session.CommitTransaction( );
    }

    void OpenSensorValueTable( )
    {
        SensorValues = database.OpenTable( SensorValueTableName );

        SensorColumnId = SensorValues.GetColumnId( SensorColumnName );
        TimestampColumnId = SensorValues.GetColumnId( TimestampColumnName );
        FlagsColumnId = SensorValues.GetColumnId( FlagsColumnName );
        ValueColumnId = SensorValues.GetColumnId( ValueColumnName );

        SensorValues.SetCurrentIndex( SensorValueIndexName );
    }

    void Insert( const SensorValue& value )
    {
        SensorValues.Insert( );
        SensorValues.SetColumn( SensorColumnId, value.Sensor );
        SensorValues.SetColumn( TimestampColumnId, value.Timestamp );
        SensorValues.SetColumn( FlagsColumnId, value.Flags );
        SensorValues.SetColumn( ValueColumnId, value.Value );
        SensorValues.Update( );
    }

    size_t Insert( size_t sensorCount, const DateTime& start, const DateTime& end, const TimeSpan& step, double valueOffset = 0.0 )
    {
        if ( sensorCount > 10000 )
        {
            sensorCount = 10000;
        }
        DateTime current = start;
        SensorValue sensorValue;
        size_t count = 0;
        while ( current < end )
        {
            sensorValue.Timestamp = current;
            sensorValue.Value = static_cast<double>( count + 1 ) + valueOffset;
            for ( size_t i = 0; i < sensorCount; i++ )
            {
                sensorValue.Sensor = Test::Ids[i];
                Insert( sensorValue );
            }
            current += step;
            count++;
        }
        return count;
    }

    void Update( const SensorValue& value )
    {
        if ( MoveTo( value.Sensor, value.Timestamp ) )
        {
            SensorValues.Replace( );
            SensorValues.SetColumn( FlagsColumnId, value.Flags );
            SensorValues.SetColumn( ValueColumnId, value.Value );
            SensorValues.Update( );
        }
    }


    size_t Update( size_t sensorCount, const DateTime& start, const DateTime& end, const TimeSpan& step, double valueOffset = 0.0 )
    {
        if ( sensorCount > 10000 )
        {
            sensorCount = 10000;
        }
        DateTime current = start;
        SensorValue sensorValue;
        size_t count = 0;
        while ( current < end )
        {
            sensorValue.Timestamp = current;
            sensorValue.Value = static_cast<double>( count + 1 ) + valueOffset;
            for ( size_t i = 0; i < sensorCount; i++ )
            {
                sensorValue.Sensor = Test::Ids[i];
                Update( sensorValue );
            }
            current += step;
            count++;
        }
        return count;
    }



    Guid Sensor( ) const
    {
        Guid result;
        SensorValues.Read( SensorColumnId, result );
        return result;
    }
    DateTime Timestamp( ) const
    {
        DateTime result;
        SensorValues.Read( TimestampColumnId, result );
        return result;
    }
    double Value( ) const
    {
        double result;
        SensorValues.Read( ValueColumnId, result );
        return result;
    }

    bool MoveTo( const Guid& sensorId ) const
    {
        SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
        auto rc = SensorValues.Seek( Ese::SeekFlags::GreaterOrEqual );
        return rc >= Ese::Result::Success;
    }

    bool Filter( const Guid& sensorId ) const
    {
        SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
        auto rc = SensorValues.Seek( Ese::SeekFlags::GreaterOrEqual );
        if ( rc >= Ese::Result::Success )
        {
            SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
            SensorValues.MakeKey( DateTime::MaxValue() );
            SensorValues.SetIndexRange( Ese::IndexRengeFlags::UpperLimit );
            return true;
        }
        else
        {
            return false;
        }
    }


    bool MoveTo( const Guid& sensorId, const DateTime& timestamp ) const
    {
        SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
        SensorValues.MakeKey( timestamp );
        auto rc = SensorValues.Seek( Ese::SeekFlags::LessOrEqual );
        return rc >= Ese::Result::Success;
    }

    bool MoveToLast( const Guid& sensorId ) const
    {
        SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
        SensorValues.MakeKey( DateTime::MaxValue() );

        auto rc = SensorValues.Seek( Ese::SeekFlags::LessOrEqual );
        return rc >= Ese::Result::Success;
    }


    bool ReverseFilter( const Guid& sensorId ) const
    {
        SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
        SensorValues.MakeKey( DateTime::MaxValue( ) );

        auto rc = SensorValues.Seek( Ese::SeekFlags::LessOrEqual );

        if ( rc >= Ese::Result::Success )
        {
            SensorValues.MakeKey( sensorId, Ese::KeyFlags::NewKey );
            SensorValues.SetIndexRange( );
            return true;
        }
        else
        {
            return false;
        }
    }


};

WideString SensorEngine::SensorValueTableName = L"SV";
WideString SensorEngine::SensorValueIndexName = L"ISV";
WideString SensorEngine::SensorColumnName = L"S";
WideString SensorEngine::TimestampColumnName = L"T";
WideString SensorEngine::FlagsColumnName = L"F";
WideString SensorEngine::ValueColumnName = L"V";


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
    auto count = engine.Insert( 3, start, end, step );
    BOOST_TEST( count > 0 );

    auto moveResult = sensorValues.MoveFirst( );
    BOOST_TEST( moveResult );
    auto firstSensor = engine.Sensor();

    moveResult = sensorValues.MoveFirst( );
    BOOST_TEST( moveResult );
    auto secondSensor = engine.Sensor( );
    
    moveResult = sensorValues.MoveFirst( );
    BOOST_TEST( moveResult );
    auto thirdSensor = engine.Sensor( );
    auto fourthSensor = Test::Ids[3];

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


    success = engine.MoveTo( thirdSensor, start + TimeSpan::FromHours( 12.5 ) );
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

    count = engine.Update( 2, start, end, step, 1.0 );

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