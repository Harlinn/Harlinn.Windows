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

#include "pch.h"

using namespace Harlinn::Common::Core;

namespace
{
    AnsiString GetDatabaseDir( )
    {
        AnsiString TestDataRoot = Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
        auto directoryPath = IO::Path::Combine( TestDataRoot, "\\LMDB" );

        if ( IO::Directory::Exist( directoryPath ) == false )
        {
            IO::Directory::Create( directoryPath );
        }
        return directoryPath;
    }

    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( LMDBTests, LocalFixture )

// --run_test=LMDBTests/EnvironmentConstructorTest1
BOOST_AUTO_TEST_CASE( EnvironmentConstructorTest1 )
{
    auto DatabaseDir = GetDatabaseDir( );
    LMDB::Environment environment( DatabaseDir );
    BOOST_CHECK( environment.Value( ) != nullptr);
}

// --run_test=LMDBTests/EnvironmentConstructorTest2
BOOST_AUTO_TEST_CASE( EnvironmentConstructorTest2 )
{
    constexpr size_t MaxNumberOfNamedDatabases = 4;
    auto DatabaseDir = GetDatabaseDir( );
    LMDB::Environment environment( DatabaseDir, LMDB::Environment::DefaultMemoryMapSize, MaxNumberOfNamedDatabases );
    BOOST_CHECK( environment.Value( ) != nullptr );
}



// --run_test=LMDBTests/IntegerKeyTest1
BOOST_AUTO_TEST_CASE( IntegerKeyTest1 )
{
    constexpr char DatabaseName[] = "IntKeyTest";
    constexpr size_t MaxNumberOfRecords = 1000;
    constexpr size_t MaxNumberOfNamedDatabases = 4;
    auto DatabaseDir = GetDatabaseDir( );
    LMDB::Environment environment( DatabaseDir, LMDB::Environment::DefaultMemoryMapSize, MaxNumberOfNamedDatabases );
    BOOST_CHECK( environment.Value( ) != nullptr );

    auto transaction = environment.BeginTransaction( );
    BOOST_CHECK( transaction.Value( ) != nullptr );
    auto database = transaction.OpenDatabase( DatabaseName, LMDB::DatabaseFlags::IntegerKey );
    if ( !database )
    {
        database = transaction.OpenDatabase( DatabaseName, LMDB::DatabaseFlags::IntegerKey | LMDB::DatabaseFlags::Create );
    }
    BOOST_CHECK( database.Value( ) != 0 );
    transaction.Truncate( database );
    size_t sumWritten = 0;
    auto cursor = transaction.OpenCursor<size_t, size_t>( database );
    for ( size_t i = 0; i < MaxNumberOfRecords; ++i )
    {
        auto value = i + 1;
        sumWritten += value;
        cursor.Write( value, value );
    }
    size_t sumRead = 0;
    auto success = cursor.MoveFirst( );
    BOOST_CHECK( success );
    do
    {
        sumRead += cursor.Value( );
    } while ( cursor.MoveNext() );
    BOOST_CHECK( sumWritten == sumRead );

    sumRead = 0;
    success = cursor.MoveLast( );
    BOOST_CHECK( success );
    do
    {
        sumRead += cursor.Value( );
    } while ( cursor.MovePrevious( ) );
    BOOST_CHECK( sumWritten == sumRead );

    sumRead = 0;
    for ( size_t i = 0; i < MaxNumberOfRecords; ++i )
    {
        auto key = i + 1;
        success = cursor.Search( key );
        BOOST_CHECK( success );
        sumRead += cursor.Value( );
    }
    BOOST_CHECK( sumWritten == sumRead );

}

// --run_test=LMDBTests/GuidKeyTest1
BOOST_AUTO_TEST_CASE( GuidKeyTest1 )
{
    constexpr char DatabaseName[] = "GuidKeyTest";
    constexpr size_t MaxNumberOfRecords = 1000;
    constexpr size_t MaxNumberOfNamedDatabases = 4;
    auto DatabaseDir = GetDatabaseDir( );
    LMDB::Environment environment( DatabaseDir, LMDB::Environment::DefaultMemoryMapSize, MaxNumberOfNamedDatabases );
    BOOST_CHECK( environment.Value( ) != nullptr );

    auto transaction = environment.BeginTransaction( );
    BOOST_CHECK( transaction.Value( ) != nullptr );
    auto database = transaction.OpenDatabase( DatabaseName, LMDB::DatabaseFlags::IntegerKey );
    if ( !database )
    {
        database = transaction.OpenDatabase( DatabaseName, LMDB::DatabaseFlags::IntegerKey | LMDB::DatabaseFlags::Create );
    }
    BOOST_CHECK( database.Value( ) != 0 );
    transaction.SetCompare( database, []( const MDB_val* first, const MDB_val* second )
    {
        Guid& f = *(Guid*)first->mv_data;
        Guid& s = *(Guid*)second->mv_data;
        return f.CompareTo( s );
    } );
    transaction.Truncate( database );
    size_t sumWritten = 0;
    auto cursor = transaction.OpenCursor<Guid, size_t>( database );
    for ( size_t i = 0; i < MaxNumberOfRecords; ++i )
    {
        Guid key = Test::Ids[i];
        auto value = i + 1;
        sumWritten += value;
        cursor.Write( key, value );
    }
    size_t sumRead = 0;
    auto success = cursor.MoveFirst( );
    BOOST_CHECK( success );
    do
    {
        sumRead += cursor.Value( );
    } while ( cursor.MoveNext( ) );
    BOOST_CHECK( sumWritten == sumRead );

    sumRead = 0;
    success = cursor.MoveLast( );
    BOOST_CHECK( success );
    do
    {
        sumRead += cursor.Value( );
    } while ( cursor.MovePrevious( ) );
    BOOST_CHECK( sumWritten == sumRead );

    sumRead = 0;
    for ( size_t i = 0; i < MaxNumberOfRecords; ++i )
    {
        Guid key = Test::Ids[i];
        success = cursor.Search( key );
        BOOST_CHECK( success );
        sumRead += cursor.Value( );
    }
    BOOST_CHECK( sumWritten == sumRead );

}


// --run_test=LMDBTests/DupSortedIntegerKeyTest1
BOOST_AUTO_TEST_CASE( DupSortedIntegerKeyTest1 )
{
    constexpr char DatabaseName[] = "DupIntKeyTest";
    constexpr size_t MaxNumberOfKeys = 1000;
    constexpr size_t NumberOfValuesPerKey = 10;
    constexpr size_t MaxNumberOfNamedDatabases = 4;
    auto DatabaseDir = GetDatabaseDir( );
    LMDB::Environment environment( DatabaseDir, LMDB::Environment::DefaultMemoryMapSize, MaxNumberOfNamedDatabases );
    BOOST_CHECK( environment.Value( ) != nullptr );

    auto transaction = environment.BeginTransaction( );
    BOOST_CHECK( transaction.Value( ) != nullptr );
    auto database = transaction.OpenDatabase( DatabaseName, LMDB::DatabaseFlags::IntegerKey | LMDB::DatabaseFlags::DupSort | LMDB::DatabaseFlags::IntegerDup );
    if ( !database )
    {
        database = transaction.OpenDatabase( DatabaseName, LMDB::DatabaseFlags::IntegerKey | LMDB::DatabaseFlags::DupSort | LMDB::DatabaseFlags::IntegerDup | LMDB::DatabaseFlags::Create );
    }
    BOOST_CHECK( database.Value( ) != 0 );
    transaction.Truncate( database );
    size_t sumWritten = 0;
    auto cursor = transaction.OpenCursor<size_t, size_t>( database );
    for ( size_t i = 0; i < MaxNumberOfKeys; ++i )
    {
        auto key = i + 1;
        for ( size_t j = 0; j < NumberOfValuesPerKey; ++j )
        {
            auto value = j + 1;
            sumWritten += value;
            cursor.Write( key, value,LMDB::WriteFlags::None );
        }
    }
    size_t sumRead = 0;
    auto success = cursor.MoveFirst( );
    BOOST_CHECK( success );
    do
    {
        do
        {
            sumRead += cursor.Value( );
        } while ( cursor.MoveNextDup( ) );
    } while ( cursor.MoveNextNoDup( ) );
    BOOST_CHECK( sumWritten == sumRead );

    sumRead = 0;
    success = cursor.MoveLast( );
    BOOST_CHECK( success );
    do
    {
        success = cursor.MoveLastDup( );
        BOOST_CHECK( success );
        do
        {
            sumRead += cursor.Value( );
        } while ( cursor.MovePreviousDup( ) );
    } while ( cursor.MovePreviousNoDup( ) );
    BOOST_CHECK( sumWritten == sumRead );

    sumRead = 0;
    for ( size_t i = 0; i < MaxNumberOfKeys; ++i )
    {
        auto key = i + 1;
        success = cursor.Search( key );
        BOOST_CHECK( success );
        do
        {
            sumRead += cursor.Value( );
        } while ( cursor.MoveNextDup( ) );
    }
    BOOST_CHECK( sumWritten == sumRead );

}







// --run_test=LMDBTests/ReadWriteTest1
BOOST_AUTO_TEST_CASE( ReadWriteTest1 )
{
    auto DatabaseDir = GetDatabaseDir( );

    LMDB::Environment environment( DatabaseDir );
    auto transaction = environment.BeginTransaction( );
    auto database = transaction.OpenDatabase( );
    BOOST_CHECK( database.Value( ) != 0 );
    transaction.Truncate( database );


    transaction.Write( database, 1, 1, LMDB::WriteFlags::NoOverwrite );
    transaction.Write( database, 2, 2, LMDB::WriteFlags::NoOverwrite );
    transaction.Write( database, 3, 3, LMDB::WriteFlags::NoOverwrite );


    transaction.Commit( );

    transaction = environment.BeginTransaction(  );
    auto cursor = transaction.OpenCursor( database );

    if ( cursor.MoveTo( 1 ) )
    {
        const auto& current = cursor.Value<int>( );
        BOOST_CHECK( current == 1 );
        cursor.Write( 2 );
    }
    if ( cursor.MoveTo( 2 ) )
    {
        const auto& current = cursor.Value<int>( );
        BOOST_CHECK( current == 2 );
        cursor.Write( 4 );
    }
    if ( cursor.MoveTo( 3 ) )
    {
        const auto& current = cursor.Value<int>( );
        BOOST_CHECK( current == 3 );
        cursor.Write( 6 );
    }
    cursor.Close( );
    transaction.Commit( );

    transaction = environment.BeginTransaction( LMDB::TransactionFlags::ReadOnly );

    cursor = transaction.OpenCursor( database );
    while ( cursor.MoveNext( ) )
    {
        auto& lmdbKey = cursor.Key( );
        auto& lmdbValue = cursor.Value( );
        int key = *(int*)lmdbKey.mv_data;
        int value = *(int*)lmdbValue.mv_data;
        BOOST_CHECK( value == ( 2 * key ) );
    }

    cursor.Close( );
    transaction.Close( );

    environment.CloseDatabase( database );
    environment.Close( );

}




BOOST_AUTO_TEST_SUITE_END( )

