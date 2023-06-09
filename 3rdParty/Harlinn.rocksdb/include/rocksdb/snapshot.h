//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#pragma once

#include "rocksdb/types.h"

namespace ROCKSDB_NAMESPACE {

class DB;

// Abstract handle to particular state of a DB.
// A Snapshot is an immutable object and can therefore be safely
// accessed from multiple threads without any external synchronization.
//
// To Create a Snapshot, call DB::GetSnapshot().
// To Destroy a Snapshot, call DB::ReleaseSnapshot(snapshot).
class Snapshot {
 public:
  // returns Snapshot's sequence number
  virtual SequenceNumber GetSequenceNumber() const = 0;

 protected:
  ROCKSDB_LIBRARY_API virtual ~Snapshot();
};

// Simple RAII wrapper class for Snapshot.
// Constructing this object will create a snapshot.  Destructing will
// release the snapshot.
class ManagedSnapshot {
 public:
  ROCKSDB_LIBRARY_API explicit ManagedSnapshot(DB* db);

  // Instead of creating a snapshot, take ownership of the input snapshot.
  ROCKSDB_LIBRARY_API ManagedSnapshot(DB* db, const Snapshot* _snapshot);

  ROCKSDB_LIBRARY_API ~ManagedSnapshot();

  ROCKSDB_LIBRARY_API const Snapshot* snapshot();

 private:
  DB* db_;
  const Snapshot* snapshot_;
};

}  // namespace ROCKSDB_NAMESPACE
