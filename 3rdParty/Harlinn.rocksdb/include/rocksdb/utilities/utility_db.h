// Copyright (c) Facebook, Inc. and its affiliates. All Rights Reserved.
// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#pragma once
#ifndef ROCKSDB_LITE
#include <string>
#include <vector>

#include "rocksdb/db.h"
#include "rocksdb/utilities/db_ttl.h"
#include "rocksdb/utilities/stackable_db.h"

namespace ROCKSDB_NAMESPACE {

// Please don't use this class. It's deprecated
class UtilityDB {
 public:
  // This function is here only for backwards compatibility. Please use the
  // functions defined in DBWithTTl (rocksdb/utilities/db_ttl.h)
  // (deprecated)
#if defined(__GNUC__) || defined(__clang__)
  __attribute__((deprecated))
#elif _WIN32
  __declspec(deprecated)
#endif
  ROCKSDB_LIBRARY_API static Status
  OpenTtlDB(const Options& options, const std::string& name,
            StackableDB** dbptr, int32_t ttl = 0, bool read_only = false);
};

}  // namespace ROCKSDB_NAMESPACE
#endif  // ROCKSDB_LITE
