# DmFtsIndexPopulationReader — reference

Overview

`DmFtsIndexPopulationReader` wraps `sys.dm_fts_index_population` and provides status and progress for full-text index population operations, including counts of ranges and workers.

Reader SQL

```
SELECT
  dfip.[database_id],
  dfip.[catalog_id],
  dfip.[table_id],
  dfip.[memory_address],
  dfip.[population_type],
  dfip.[population_type_description],
  dfip.[is_clustered_index_scan],
  dfip.[range_count],
  dfip.[completed_range_count],
  dfip.[outstanding_batch_count],
  dfip.[Status],
  dfip.[status_description],
  dfip.[completion_type],
  dfip.[completion_type_description],
  dfip.[worker_count],
  dfip.[queued_population_type],
  dfip.[queued_population_type_description],
  dfip.[start_time],
  dfip.[incremental_timestamp]
FROM
  [sys].[dm_fts_index_population] dfip
```

Columns and interpretation

- `database_id`, `catalog_id`, `table_id` ? identifiers for the index population target.
- `memory_address` ? internal memory token.
- `population_type` / `population_type_description` ? type of population (auto/manual/full/incremental).
- `is_clustered_index_scan` ? whether a clustered index scan is used.
- `range_count`, `completed_range_count` ? total and completed range counts for population.
- `outstanding_batch_count` ? number of outstanding batches still to process.
- `Status` / `status_description` ? numeric and textual status for the population process.
- `completion_type` / `completion_type_description` ? completion type and its description.
- `worker_count` ? number of worker threads assigned.
- `queued_population_type` and description indicate queued type if any.
- `start_time` ? start time of population.
- `incremental_timestamp` ? timestamp token for incremental population.

How to interpret

- Monitor `completed_range_count` vs `range_count` and `outstanding_batch_count` to observe progress.
- `Status` and `StatusDescription` show current activity state and potential errors.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFtsIndexPopulationReader.Sql;
using var rdr = cmd.ExecuteReader();
var p = new DmFtsIndexPopulationReader(rdr, ownsReader:false);
while (p.Read())
{
    Console.WriteLine($"Catalog:{p.CatalogId} Table:{p.TableId} Status:{p.StatusDescription} Ranges:{p.CompletedRangeCount}/{p.RangeCount} Workers:{p.WorkerCount}");
}
```

See also:

- [sys.dm_fts_index_population](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-fts-index-population)
