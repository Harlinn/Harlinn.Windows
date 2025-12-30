# DmDbXtpObjectStatsReader — reference

Overview

`DmDbXtpObjectStatsReader` wraps `sys.dm_db_xtp_object_stats` and reports DML attempt counters and conflict metrics for memory-optimized objects.

Reader SQL

```
SELECT
  ddxos.[object_id],
  ddxos.[xtp_object_id],
  ddxos.[row_insert_attempts],
  ddxos.[row_update_attempts],
  ddxos.[row_delete_attempts],
  ddxos.[write_conflicts],
  ddxos.[unique_constraint_violations],
  ddxos.[object_address]
FROM
  [sys].[dm_db_xtp_object_stats] ddxos
```

Columns (how to interpret)

- `row_insert_attempts`, `row_update_attempts`, `row_delete_attempts` ? total attempts of respective DML operations. Useful to measure write workload.

- `write_conflicts` ? number of write conflicts encountered; indicates concurrency conflicts under optimistic concurrency model.

- `unique_constraint_violations` ? count of violations of unique constraints detected during operations.

- `object_address` ? internal address token for the object; used for deep diagnostics.

Interpretation

- High write_conflicts relative to attempt counts suggests contention and may justify retry logic tuning, partitioning, or schema changes.
- Unique constraint violations indicate application logic issues or data anomalies.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpObjectStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var s = new DmDbXtpObjectStatsReader(reader, ownsReader: false);
while (s.Read())
{
    Console.WriteLine($"Obj {s.ObjectId} Inserts:{s.RowInsertAttempts} Updates:{s.RowUpdateAttempts} Deletes:{s.RowDeleteAttempts}");
    Console.WriteLine($" Conflicts: {s.WriteConflicts} UniqueViolations: {s.UniqueConstraintViolations}");
}
```

See also:

- [sys.dm_db_xtp_object_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-object-stats)
