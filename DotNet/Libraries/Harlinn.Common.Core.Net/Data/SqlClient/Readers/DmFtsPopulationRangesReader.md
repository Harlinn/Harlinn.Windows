# DmFtsPopulationRangesReader — reference

Overview

`DmFtsPopulationRangesReader` wraps `sys.dm_fts_population_ranges` and provides information about ranges being processed during full-text index population including processed row counts and errors.

Reader SQL

```
SELECT
  dfpr.[memory_address],
  dfpr.[parent_memory_address],
  dfpr.[is_retry],
  dfpr.[session_id],
  dfpr.[processed_row_count],
  dfpr.[error_count]
FROM
  [sys].[dm_fts_population_ranges] dfpr
```

Columns and interpretation

- `memory_address` / `parent_memory_address` ? internal memory tokens for the range and parent.
- `is_retry` ? whether this range is being retried.
- `session_id` ? session handling the range.
- `processed_row_count` ? number of rows processed for the range.
- `error_count` ? number of errors encountered processing the range.

How to interpret

- Use `processed_row_count` and `error_count` to track progress and problems for individual population ranges.
- `is_retry` flags ranges that previously failed.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFtsPopulationRangesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmFtsPopulationRangesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Range {BitConverter.ToString(r.MemoryAddress)} Parent:{BitConverter.ToString(r.ParentMemoryAddress)} Sess:{r.SessionId} Rows:{r.ProcessedRowCount} Errors:{r.ErrorCount}");
}
```

See also:

- [sys.dm_fts_population_ranges](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-fts-population-ranges)
