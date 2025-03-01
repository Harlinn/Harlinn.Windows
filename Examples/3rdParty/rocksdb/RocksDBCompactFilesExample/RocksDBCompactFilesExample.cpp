//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//

#include <mutex>
#include <string>
#include "rocksdb/db.h"
#include "rocksdb/env.h"
#include "rocksdb/options.h"

#include <HCCEnvironment.h>
#include <HCCIO.h>

namespace hcc = Harlinn::Common::Core;

using namespace ROCKSDB_NAMESPACE;


hcc::AnsiString GetRootDataDirectory( )
{
    auto result = hcc::Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
    if ( !result.ends_with( "\\" ) && !result.ends_with( "/" ) )
    {
        result += '\\';
    }
    return result;
}

hcc::AnsiString GetRocksDBDataDirectory( )
{
    auto dataDir = GetRootDataDirectory( );
    auto rocksDBDataDirectory = dataDir + "RocksDB";
    hcc::IO::Directory::Create( rocksDBDataDirectory );
    rocksDBDataDirectory += '\\';
    return rocksDBDataDirectory;
}

std::string GetRocksDBExampleDataDirectory( )
{
    auto rocksDBDataDirectory = GetRocksDBDataDirectory( );
    auto result = rocksDBDataDirectory + "CompactFilesExampleData";
    return std::string( result.data( ), result.size( ) );
}


std::string kDBPath = GetRocksDBExampleDataDirectory( );


struct CompactionTask;

// This is an example interface of external-compaction algorithm.
// Compaction algorithm can be implemented outside the core-RocksDB
// code by using the pluggable compaction APIs that RocksDb provides.
class Compactor : public EventListener
{
public:
    // Picks and returns a compaction task given the specified DB
    // and column family.  It is the caller's responsibility to
    // destroy the returned CompactionTask.  Returns "nullptr"
    // if it cannot find a proper compaction task.
    virtual CompactionTask* PickCompaction(
        DB* db, const std::string& cf_name ) = 0;

    // Schedule and run the specified compaction task in background.
    virtual void ScheduleCompaction( CompactionTask* task ) = 0;
};

// Example structure that describes a compaction task.
struct CompactionTask
{
    CompactionTask(
        DB* _db, Compactor* _compactor,
        const std::string& _column_family_name,
        const std::vector<std::string>& _input_file_names,
        const int _output_level,
        const CompactionOptions& _compact_options,
        bool _retry_on_fail )
        : db( _db ),
        compactor( _compactor ),
        column_family_name( _column_family_name ),
        input_file_names( _input_file_names ),
        output_level( _output_level ),
        compact_options( _compact_options ),
        retry_on_fail( _retry_on_fail )
    {
    }
    DB* db;
    Compactor* compactor;
    const std::string& column_family_name;
    std::vector<std::string> input_file_names;
    int output_level;
    CompactionOptions compact_options;
    bool retry_on_fail;
};

// A simple compaction algorithm that always compacts everything
// to the highest level whenever possible.
class FullCompactor : public Compactor
{
public:
    explicit FullCompactor( const Options options ) : options_( options )
    {
        compact_options_.compression = options_.compression;
        compact_options_.output_file_size_limit =
            options_.target_file_size_base;
    }

    // When flush happens, it determines whether to trigger compaction. If
    // triggered_writes_stop is true, it will also set the retry flag of
    // compaction-task to true.
    void OnFlushCompleted(
        DB* db, const FlushJobInfo& info ) override
    {
        CompactionTask* task = PickCompaction( db, info.cf_name );
        if ( task != nullptr )
        {
            if ( info.triggered_writes_stop )
            {
                task->retry_on_fail = true;
            }
            // Schedule compaction in a different thread.
            ScheduleCompaction( task );
        }
    }

    // Always pick a compaction which includes all files whenever possible.
    CompactionTask* PickCompaction(
        DB* db, const std::string& cf_name ) override
    {
        ColumnFamilyMetaData cf_meta;
        db->GetColumnFamilyMetaData( &cf_meta );

        std::vector<std::string> input_file_names;
        for ( auto level : cf_meta.levels )
        {
            for ( auto file : level.files )
            {
                if ( file.being_compacted )
                {
                    return nullptr;
                }
                input_file_names.push_back( file.name );
            }
        }
        return new CompactionTask(
            db, this, cf_name, input_file_names,
            options_.num_levels - 1, compact_options_, false );
    }

    // Schedule the specified compaction task in background.
    void ScheduleCompaction( CompactionTask* task ) override
    {
        options_.env->Schedule( &FullCompactor::CompactFiles, task );
    }

    static void CompactFiles( void* arg )
    {
        std::unique_ptr<CompactionTask> task(
            reinterpret_cast<CompactionTask*>( arg ) );
        assert( task );
        assert( task->db );
        Status s = task->db->CompactFiles(
            task->compact_options,
            task->input_file_names,
            task->output_level );
        printf( "CompactFiles() finished with status %s\n", s.ToString( ).c_str( ) );
        if ( !s.ok( ) && !s.IsIOError( ) && task->retry_on_fail )
        {
            // If a compaction task with its retry_on_fail=true failed,
            // try to schedule another compaction in case the reason
            // is not an IO error.
            CompactionTask* new_task = task->compactor->PickCompaction(
                task->db, task->column_family_name );
            task->compactor->ScheduleCompaction( new_task );
        }
    }

private:
    Options options_;
    CompactionOptions compact_options_;
};

int main( )
{
    Options options;
    options.create_if_missing = true;
    // Disable RocksDB background compaction.
    options.compaction_style = kCompactionStyleNone;
    // Small slowdown and stop trigger for experimental purpose.
    options.level0_slowdown_writes_trigger = 3;
    options.level0_stop_writes_trigger = 5;
    options.IncreaseParallelism( 5 );
    options.listeners.emplace_back( new FullCompactor( options ) );

    DB* db = nullptr;
    DestroyDB( kDBPath, options );
    Status s = DB::Open( options, kDBPath, &db );
    assert( s.ok( ) );
    assert( db );

    // if background compaction is not working, write will stall
    // because of options.level0_stop_writes_trigger
    for ( int i = 1000; i < 99999; ++i )
    {
        db->Put( WriteOptions( ), std::to_string( i ),
            std::string( 500, 'a' + ( i % 26 ) ) );
    }

    // verify the values are still there
    std::string value;
    for ( int i = 1000; i < 99999; ++i )
    {
        db->Get( ReadOptions( ), std::to_string( i ),
            &value );
        assert( value == std::string( 500, 'a' + ( i % 26 ) ) );
    }

    // close the db.
    delete db;

    return 0;
}
