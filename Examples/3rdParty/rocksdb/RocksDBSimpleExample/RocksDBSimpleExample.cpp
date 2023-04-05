#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "rocksdb/c.h"
#include <HCCEnvironment.h>
#include <HCCIO.h>

namespace hcc = Harlinn::Common::Core;


std::string  GetRootDataDirectory( )
{
    auto result = hcc::Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
    if ( !result.ends_with( "\\" ) && !result.ends_with( "/" ) )
    {
        result += '\\';
    }
    return result;
}

std::string  GetRocksDBDataDirectory( )
{
    auto dataDir = GetRootDataDirectory( );
    auto rocksDBDataDirectory = dataDir + "RocksDB";
    hcc::IO::Directory::Create( rocksDBDataDirectory );
    rocksDBDataDirectory += '\\';
    return rocksDBDataDirectory;
}

std::string  GetRocksDBExampleDataDirectory( )
{
    auto rocksDBDataDirectory = GetRocksDBDataDirectory( );
    auto result = rocksDBDataDirectory + "SimpleExampleData";
    return result;
}

std::string  GetRocksDBExampleBackupDirectory( )
{
    auto rocksDBDataDirectory = GetRocksDBDataDirectory( );
    auto result = rocksDBDataDirectory + "SimpleExampleBackup";
    return result;
}


int main( int argc, char** argv )
{
    auto DBPath = GetRocksDBExampleDataDirectory( );
    auto DBBackupPath = GetRocksDBExampleBackupDirectory( );


    rocksdb_t* db;
    rocksdb_backup_engine_t* be;
    rocksdb_options_t* options = rocksdb_options_create( );
    // Optimize RocksDB. This is the easiest way to
    // get RocksDB to perform well.
#if defined(OS_WIN)
    SYSTEM_INFO system_info;
    GetSystemInfo( &system_info );
    long cpus = system_info.dwNumberOfProcessors;
#else
    long cpus = sysconf( _SC_NPROCESSORS_ONLN );
#endif
    // Set # of online cores
    rocksdb_options_increase_parallelism( options, (int)( cpus ) );
    rocksdb_options_optimize_level_style_compaction( options, 0 );
    // create the DB if it's not already present
    rocksdb_options_set_create_if_missing( options, 1 );

    // open DB
    char* err = NULL;
    db = rocksdb_open( options, DBPath.c_str(), &err );
    assert( !err );

    // open Backup Engine that we will use for backing up our database
    be = rocksdb_backup_engine_open( options, DBBackupPath.c_str( ), &err );
    assert( !err );

    // Put key-value
    rocksdb_writeoptions_t* writeoptions = rocksdb_writeoptions_create( );
    const char key[] = "key";
    const char* value = "value";
    rocksdb_put( db, writeoptions, key, strlen( key ), value, strlen( value ) + 1,
        &err );
    assert( !err );
    // Get value
    rocksdb_readoptions_t* readoptions = rocksdb_readoptions_create( );
    size_t len;
    char* returned_value =
        rocksdb_get( db, readoptions, key, strlen( key ), &len, &err );
    assert( !err );
    assert( strcmp( returned_value, "value" ) == 0 );
    free( returned_value );

    // create new backup in a directory specified by DBBackupPath
    rocksdb_backup_engine_create_new_backup( be, db, &err );
    assert( !err );

    rocksdb_close( db );

    // If something is wrong, you might want to restore data from last backup
    rocksdb_restore_options_t* restore_options = rocksdb_restore_options_create( );
    rocksdb_backup_engine_restore_db_from_latest_backup( be, DBPath.c_str( ), DBPath.c_str( ), restore_options, &err );
    assert( !err );
    rocksdb_restore_options_destroy( restore_options );

    db = rocksdb_open( options, DBPath.c_str( ), &err );
    assert( !err );

    // cleanup
    rocksdb_writeoptions_destroy( writeoptions );
    rocksdb_readoptions_destroy( readoptions );
    rocksdb_options_destroy( options );
    rocksdb_backup_engine_close( be );
    rocksdb_close( db );

    return 0;
}
