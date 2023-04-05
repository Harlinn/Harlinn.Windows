// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#pragma once

#include "rocksdb/db.h"
#include "rocksdb/status.h"

namespace ROCKSDB_NAMESPACE {
namespace experimental {

// Supported only for Leveled compaction
ROCKSDB_LIBRARY_API Status SuggestCompactRange(DB* db, ColumnFamilyHandle* column_family,
                           const Slice* begin, const Slice* end);
ROCKSDB_LIBRARY_API Status SuggestCompactRange(DB* db, const Slice* begin, const Slice* end);

// Move all L0 files to target_level skipping compaction.
// This operation succeeds only if the files in L0 have disjoint ranges; this
// is guaranteed to happen, for instance, if keys are inserted in sorted
// order. Furthermore, all levels between 1 and target_level must be empty.
// If any of the above condition is violated, InvalidArgument will be
// returned.
ROCKSDB_LIBRARY_API Status PromoteL0(DB* db, ColumnFamilyHandle* column_family,
                 int target_level = 1);

}  // namespace experimental
}  // namespace ROCKSDB_NAMESPACE
