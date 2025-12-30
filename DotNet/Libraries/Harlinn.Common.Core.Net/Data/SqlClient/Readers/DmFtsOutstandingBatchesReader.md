# DmFtsOutstandingBatchesReader — reference

Overview

`DmFtsOutstandingBatchesReader` wraps `sys.dm_fts_outstanding_batches` and returns information about outstanding full-text indexing batches including retry hints, failure counts and timestamps.

Reader SQL

```
SELECT
  dfob.[database_id],
  dfob.[catalog_id],
  dfob.[table_id],
  dfob.[batch_id],
  dfob.[memory_address],
  dfob.[crawl_memory_address],
  dfob.[memregion_memory_address],
  dfob.[hr_batch],
  dfob.[is_retry_batch],
  dfob.[retry_hints],
  dfob.[retry_hints_description],
  dfob.[doc_failed],
  dfob.[batch_timestamp]
FROM
  [sys].[dm_fts_outstanding_batches] dfob
```

Columns and interpretation

- `database_id`, `catalog_id`, `table_id`, `batch_id` ? identifiers for the batch.
- `memory_address`, `crawl_memory_address`, `memregion_memory_address` ? internal memory tokens.
- `hr_batch` ? human-readable batch id or internal flag.
- `is_retry_batch` ? whether this batch is a retry.
- `retry_hints` / `retry_hints_description` ? numeric hint and textual description for retry reason.
- `doc_failed` ? number of documents in the batch that failed.
- `batch_timestamp` ? timestamp token for the batch.

How to interpret

- `is_retry_batch` and `retry_hints` indicate batches requiring special handling; `doc_failed` surfaces batch-level failures.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFtsOutstandingBatchesReader.Sql;
using var rdr = cmd.ExecuteReader();
var b = new DmFtsOutstandingBatchesReader(rdr, ownsReader:false);
while (b.Read())
{
    Console.WriteLine($"Batch:{b.BatchId} Table:{b.TableId} Retry:{b.IsRetryBatch} FailedDocs:{b.DocFailed} RetryHints:{b.RetryHintsDescription}");
}
```

See also:

- [sys.dm_fts_outstanding_batches](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-fts-outstanding-batches)
