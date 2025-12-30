# DmHadrPhysicalSeedingStatsReader — reference

Overview

`DmHadrPhysicalSeedingStatsReader` wraps `sys.dm_hadr_physical_seeding_stats` and provides metrics for physical seeding operations including bytes transferred and operation durations.

Reader SQL

```
SELECT
  dhpss.[operation_id],
  dhpss.[ag_id],
  dhpss.[ag_db_id],
  dhpss.[replica_id],
  dhpss.[bytes_transferred],
  dhpss.[bytes_transferred_per_second],
  dhpss.[elapsed_seconds]
FROM
  [sys].[dm_hadr_physical_seeding_stats] dhpss
```

Columns and interpretation

- `operation_id`, `ag_id`, `ag_db_id`, `replica_id` ? identifiers for the seeding operation and AG.
- `bytes_transferred` ? total bytes transferred for the seeding operation.
- `bytes_transferred_per_second` ? transfer throughput.
- `elapsed_seconds` ? elapsed time for the operation in seconds.

How to interpret

- Use transfer rates and elapsed times to assess seeding performance and network throughput.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrPhysicalSeedingStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmHadrPhysicalSeedingStatsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Op:{s.OperationId} AGDB:{s.AgDbId} Bytes:{s.BytesTransferred} Rate:{s.BytesTransferredPerSecond}/s Elapsed:{s.ElapsedSeconds}s");
}
```

See also:

- [sys.dm_hadr_physical_seeding_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-physical-seeding-stats)
