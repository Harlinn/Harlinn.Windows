// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#pragma once

#include <string>

#include "rocksdb/customizable.h"
#include "rocksdb/table.h"

namespace ROCKSDB_NAMESPACE {

class Slice;
class BlockBuilder;
struct ConfigOptions;
struct Options;

// FlushBlockPolicy provides a configurable way to determine when to flush a
// block in the block based tables,
class FlushBlockPolicy {
 public:
  // Keep track of the key/value sequences and return the boolean value to
  // determine if table builder should flush current data block.
  virtual bool Update(const Slice& key, const Slice& value) = 0;

  virtual ~FlushBlockPolicy() {}
};

class FlushBlockPolicyFactory : public Customizable {
 public:
  static const char* Type() { return "FlushBlockPolicyFactory"; }

  // Creates a FlushBlockPolicyFactory based on the input value.
  // By default, this method can create EveryKey or BySize PolicyFactory,
  // which take now config_options.
  ROCKSDB_LIBRARY_API static Status CreateFromString(
      const ConfigOptions& config_options, const std::string& value,
      std::shared_ptr<FlushBlockPolicyFactory>* result);

  // Return a new block flush policy that flushes data blocks by data size.
  // FlushBlockPolicy may need to access the metadata of the data block
  // builder to determine when to flush the blocks.
  //
  // Callers must delete the result after any database that is using the
  // result has been closed.
  virtual FlushBlockPolicy* NewFlushBlockPolicy(
      const BlockBasedTableOptions& table_options,
      const BlockBuilder& data_block_builder) const = 0;

  virtual ~FlushBlockPolicyFactory() {}
};

class FlushBlockBySizePolicyFactory : public FlushBlockPolicyFactory {
 public:
  FlushBlockBySizePolicyFactory();

  static const char* kClassName() { return "FlushBlockBySizePolicyFactory"; }
  const char* Name() const override { return kClassName(); }

  ROCKSDB_LIBRARY_API FlushBlockPolicy* NewFlushBlockPolicy(
      const BlockBasedTableOptions& table_options,
      const BlockBuilder& data_block_builder) const override;

  ROCKSDB_LIBRARY_API static FlushBlockPolicy* NewFlushBlockPolicy(
      const uint64_t size, const int deviation,
      const BlockBuilder& data_block_builder);
};

}  // namespace ROCKSDB_NAMESPACE
