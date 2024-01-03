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


#include <HCCLoggerLMDBSinkStorage.h>


using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::Logging::Sinks::Storage;

namespace
{
    AnsiString GetDatabaseDir( )
    {
        AnsiString TestDataRoot = Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
        auto directoryPath = IO::Path::Combine( TestDataRoot, "\\LogStorageTest" );

        if ( IO::Directory::Exist( directoryPath ) == false )
        {
            IO::Directory::Create( directoryPath );
        }
        return directoryPath;
    }

    void RemoveDatabaseFiles( const AnsiString& directoryPath )
    {
        AnsiString datafile = directoryPath + "\\data.mdb";
        AnsiString lockfile = directoryPath + "\\lock.mdb";
        if ( IO::File::Exist( datafile ) )
        {
            IO::File::Delete( datafile );
        }
        if ( IO::File::Exist( lockfile ) )
        {
            IO::File::Delete( lockfile );
        }
    }

    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };

    template<typename SessionRefT>
    bool InitializeLogSite( SessionRefT& session, int line, const char* file, const char* function )
    {
        const char* fmt = "{}";
        Int32 arg1 = 0;

        bool isFixedSize = Harlinn::Common::Core::Persistent::IsFixedSize( arg1 );
        size_t fixedSize = isFixedSize ? Harlinn::Common::Core::Persistent::BufferSize( arg1 ) : 0;
        auto argDescriptor = Harlinn::Common::Core::Persistent::Descriptor( arg1 );
        Harlinn::Common::Core::Logging::LogSite logSite( Harlinn::Common::Core::Logging::Level::Error, fmt, reinterpret_cast<const Byte*>( &argDescriptor ), sizeof( argDescriptor ), isFixedSize, fixedSize, line, 0, file, function );

        return session->InitializeLogSite( &logSite );
    }

    


    template<typename SessionRefT>
    size_t InitializeLogSite( SessionRefT& session, size_t count )
    {
        size_t result = 0;
        for ( size_t i = 0; i < count; i++ )
        {
            auto file = std::format( "file{}.cpp", i + 1 );
            auto function = std::format( "void func{}( )", i + 1 );
            if ( InitializeLogSite( session, 10, file.c_str( ), function.c_str( ) ) )
            {
                result++;
            }
        }
        return result;
    }


}

BOOST_FIXTURE_TEST_SUITE( LoggerLMDBSinkStorageTests, LocalFixture )

// --run_test=LoggerLMDBSinkStorageTests/LogDatabaseConstructorTest1
BOOST_AUTO_TEST_CASE( LogDatabaseConstructorTest1 )
{
    auto DatabaseDir = GetDatabaseDir( );
    RemoveDatabaseFiles( DatabaseDir );
    LogDatabaseOptions options( DatabaseDir );
    LogDatabase logDatabase( options );
    auto session = logDatabase.CreateSession( );
    BOOST_CHECK( session != nullptr );
}

// --run_test=LoggerLMDBSinkStorageTests/InsertLogSiteTest1
BOOST_AUTO_TEST_CASE( InsertLogSiteTest1 )
{
    constexpr size_t LogSiteCount = 1000;
    auto DatabaseDir = GetDatabaseDir( );
    RemoveDatabaseFiles( DatabaseDir );
    LogDatabaseOptions options( DatabaseDir );
    LogDatabase logDatabase( options );
    auto session = logDatabase.CreateSession( );
    BOOST_CHECK( session != nullptr );

    auto insertCount1 = InitializeLogSite( session, LogSiteCount );
    BOOST_CHECK( insertCount1 == LogSiteCount );
    auto insertCount2 = InitializeLogSite( session, LogSiteCount );
    BOOST_CHECK( insertCount2 == 0 );

    auto logsiteTable = session->GetLogSiteTable( );

    size_t minId = MaxUInt64;
    size_t maxId = 0;
    size_t count = 0;
    logsiteTable->MoveFirst( );
    do
    {
        Logging::Types::LogSiteData logSite;
        logsiteTable->Read( logSite );
        auto id = logSite.Id( );
        if ( id < minId )
        {
            minId = id;
        }
        if ( id > maxId )
        {
            maxId = id;
        }
        count++;

    } while ( logsiteTable->MoveNext( ) );
    BOOST_CHECK( minId == 1 );
    BOOST_CHECK( count == LogSiteCount );
    BOOST_CHECK( maxId == LogSiteCount );
}

// --run_test=LoggerLMDBSinkStorageTests/InsertBackendComputerInfoTest1
BOOST_AUTO_TEST_CASE( InsertBackendComputerInfoTest1 )
{
    auto DatabaseDir = GetDatabaseDir( );
    RemoveDatabaseFiles( DatabaseDir );
    LogDatabaseOptions options( DatabaseDir );
    LogDatabase logDatabase( options );
    auto session = logDatabase.CreateSession( );
    BOOST_CHECK( session != nullptr );

    auto machineId = Environment::MachineGuid( );

    auto table = session->GetLogComputerTable( );
    auto found = table->Find( machineId );
    BOOST_CHECK( found == false );

    auto backendComputerInfo = Logging::Types::GetComputerInfo( );
    bool inserted1 = table->Insert( &backendComputerInfo );
    BOOST_CHECK( inserted1 == true );
    bool inserted2 = table->Insert( &backendComputerInfo );
    BOOST_CHECK( inserted2 == false );
}

// --run_test=LoggerLMDBSinkStorageTests/InsertBackendUserInfoTest1
BOOST_AUTO_TEST_CASE( InsertBackendUserInfoTest1 )
{
    auto DatabaseDir = GetDatabaseDir( );
    RemoveDatabaseFiles( DatabaseDir );
    LogDatabaseOptions options( DatabaseDir );
    LogDatabase logDatabase( options );
    auto session = logDatabase.CreateSession( );
    BOOST_CHECK( session != nullptr );

    auto table = session->GetLogUserTable( );

    auto backendUserInfo1 = Logging::Types::GetUserInfo( );
    bool inserted1 = table->Insert( &backendUserInfo1 );
    BOOST_CHECK( inserted1 == true );
    auto backendUserInfo2 = Logging::Types::GetUserInfo( );
    bool inserted2 = table->Insert( &backendUserInfo2 );
    BOOST_CHECK( inserted2 == false );
}






BOOST_AUTO_TEST_SUITE_END( )
