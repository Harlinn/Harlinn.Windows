//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//

#include <cstdio>
#include <string>
#include <vector>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
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
    auto result = rocksDBDataDirectory + "ColumnFamiliesExampleData";
    return std::string( result.data( ), result.size( ) );
}



std::string kDBPath = GetRocksDBExampleDataDirectory( );


int main( )
{
    // open DB
    Options options;
    options.create_if_missing = true;
    DB* db;
    Status s = DB::Open( options, kDBPath, &db );
    assert( s.ok( ) );

    // create column family
    ColumnFamilyHandle* cf;
    s = db->CreateColumnFamily( ColumnFamilyOptions( ), "new_cf", &cf );
    assert( s.ok( ) );

    // close DB
    s = db->DestroyColumnFamilyHandle( cf );
    assert( s.ok( ) );
    delete db;

    // open DB with two column families
    std::vector<ColumnFamilyDescriptor> column_families;
    // have to open default column family
    column_families.push_back( ColumnFamilyDescriptor(
        kDefaultColumnFamilyName, ColumnFamilyOptions( ) ) );
    // open the new one, too
    column_families.push_back( ColumnFamilyDescriptor(
        "new_cf", ColumnFamilyOptions( ) ) );
    std::vector<ColumnFamilyHandle*> handles;
    s = DB::Open( DBOptions( ), kDBPath, column_families, &handles, &db );
    assert( s.ok( ) );

    // put and get from non-default column family
    s = db->Put( WriteOptions( ), handles[1], Slice( "key" ), Slice( "value" ) );
    assert( s.ok( ) );
    std::string value;
    s = db->Get( ReadOptions( ), handles[1], Slice( "key" ), &value );
    assert( s.ok( ) );

    // atomic write
    WriteBatch batch;
    batch.Put( handles[0], Slice( "key2" ), Slice( "value2" ) );
    batch.Put( handles[1], Slice( "key3" ), Slice( "value3" ) );
    batch.Delete( handles[0], Slice( "key" ) );
    s = db->Write( WriteOptions( ), &batch );
    assert( s.ok( ) );

    // drop column family
    s = db->DropColumnFamily( handles[1] );
    assert( s.ok( ) );

    // close db
    for ( auto handle : handles )
    {
        s = db->DestroyColumnFamilyHandle( handle );
        assert( s.ok( ) );
    }
    delete db;

    return 0;
}
