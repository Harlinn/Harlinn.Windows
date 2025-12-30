# DmDbXtpHashIndexStatsReader — reference

Overview

`DmDbXtpHashIndexStatsReader` wraps `sys.dm_db_xtp_hash_index_stats` and reports statistics for memory-optimized hash indexes. Use these to evaluate hash bucket distribution and chain lengths which affect lookup performance.

Reader SQL

```
SELECT
  ddxhis.[object_id],
  ddxhis.[xtp_object_id],
  ddxhis.[index_id],
  ddxhis.[total_bucket_count],
  ddxhis.[empty_bucket_count],
  ddxhis.[avg_chain_length],
  ddxhis.[max_chain_length]
FROM
  [sys].[dm_db_xtp_hash_index_stats] ddxhis
```

Columns (how to interpret)

- `object_id` ? `ObjectId` (int)
  - Table object id owning the hash index.

- `xtp_object_id` ? `XtpObjectId` (int)
  - Internal XTP object id for the memory-optimized object.

- `index_id` ? `IndexId` (int)
  - Index id within the object.

- `total_bucket_count` ? `TotalBucketCount` (long)
  - Number of hash buckets configured for the index. Larger bucket counts reduce average chain length but increase memory usage.

- `empty_bucket_count` ? `EmptyBucketCount` (long?)
  - Buckets with no entries; proportion of empty vs total indicates load factor.

- `avg_chain_length` ? `AvgChainLength` (long)
  - Average length of chains (entries per bucket). Lower is better for hash performance.

- `max_chain_length` ? `MaxChainLength` (long)
  - Maximum chain length observed. High values indicate heavy collision and potential performance issues.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpHashIndexStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var s = new DmDbXtpHashIndexStatsReader(reader, ownsReader: false);
while (s.Read())
{
    Console.WriteLine($"Object {s.ObjectId} Index {s.IndexId} Buckets: {s.TotalBucketCount} Empty: {s.EmptyBucketCount}");
    Console.WriteLine($" AvgChain: {s.AvgChainLength} MaxChain: {s.MaxChainLength}");
}
```

See also:

- [sys.dm_db_xtp_hash_index_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-hash-index-stats)
