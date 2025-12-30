# DmDbXtpNonclusteredIndexStatsReader — reference

Overview

`DmDbXtpNonclusteredIndexStatsReader` wraps `sys.dm_db_xtp_nonclustered_index_stats` and reports page-level and operation counters for nonclustered indexes on memory-optimized tables. Useful for understanding split/merge behavior and page operations.

Reader SQL

```
SELECT
  ddxnis.[object_id],
  ddxnis.[xtp_object_id],
  ddxnis.[index_id],
  ddxnis.[delta_pages],
  ddxnis.[internal_pages],
  ddxnis.[leaf_pages],
  ddxnis.[outstanding_retired_nodes],
  ddxnis.[page_update_count],
  ddxnis.[page_update_retry_count],
  ddxnis.[page_consolidation_count],
  ddxnis.[page_consolidation_retry_count],
  ddxnis.[page_split_count],
  ddxnis.[page_split_retry_count],
  ddxnis.[key_split_count],
  ddxnis.[key_split_retry_count],
  ddxnis.[page_merge_count],
  ddxnis.[page_merge_retry_count],
  ddxnis.[key_merge_count],
  ddxnis.[key_merge_retry_count],
  ddxnis.[uses_key_normalization]
FROM
  [sys].[dm_db_xtp_nonclustered_index_stats] ddxnis
```

Columns (how to interpret)

- `delta_pages`, `internal_pages`, `leaf_pages` ? breakdown of pages by type for the index. Use to estimate index storage composition.

- `outstanding_retired_nodes` ? count of retired nodes pending cleanup; high values may indicate delayed reclamation.

- `page_update_count` / `page_update_retry_count` ? updates and retries; retries indicate contention.

- `page_consolidation_*`, `page_split_*`, `key_split_*`, `page_merge_*`, `key_merge_*` ? counters for structural maintenance operations and their retries. A high number indicates heavy maintenance due to fragmentation or concurrent modifications.

- `uses_key_normalization` ? whether the index uses key normalization; impacts how splits/merges behave.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpNonclusteredIndexStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var s = new DmDbXtpNonclusteredIndexStatsReader(reader, ownsReader: false);
while (s.Read())
{
    Console.WriteLine($"Obj {s.ObjectId} Index {s.IndexId} Pages: delta={s.DeltaPages} internal={s.InternalPages} leaf={s.LeafPages}");
    Console.WriteLine($" Splits: {s.PageSplitCount} (retries {s.PageSplitRetryCount}), Merges: {s.PageMergeCount}");
}
```

See also:

- [sys.dm_db_xtp_nonclustered_index_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-nonclustered-index-stats)
