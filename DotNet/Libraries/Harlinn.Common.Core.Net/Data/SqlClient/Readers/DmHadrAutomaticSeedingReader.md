# DmHadrAutomaticSeedingReader — reference

Overview

`DmHadrAutomaticSeedingReader` wraps `sys.dm_hadr_automatic_seeding` and provides details about automatic seeding operations for availability groups including operation ids, states, errors and attempt counts.

Reader SQL

```
SELECT
  dhas.[start_time],
  dhas.[completion_time],
  dhas.[ag_id],
  dhas.[ag_db_id],
  dhas.[ag_remote_replica_id],
  dhas.[operation_id],
  dhas.[is_source],
  dhas.[current_state],
  dhas.[performed_seeding],
  dhas.[failure_state],
  dhas.[failure_state_desc],
  dhas.[error_code],
  dhas.[number_of_attempts]
FROM
  [sys].[dm_hadr_automatic_seeding] dhas
```

Columns and interpretation

- `start_time` / `completion_time` ? timestamps for the seeding operation.
- `ag_id`, `ag_db_id`, `ag_remote_replica_id` ? AG and replica identifiers.
- `operation_id` ? unique operation identifier (GUID).
- `is_source` ? whether this row represents the source of seeding.
- `current_state` / `performed_seeding` ? current state and whether seeding was performed.
- `failure_state` / `failure_state_desc` / `error_code` ? failure details if any.
- `number_of_attempts` ? retry attempts count.

How to interpret

- Use `current_state` and `failure_state` to diagnose failed or stuck automatic seeding operations.
- `number_of_attempts` and `error_code` help triage persistent failures.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrAutomaticSeedingReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmHadrAutomaticSeedingReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Op:{s.OperationId} AGDB:{s.AgDbId} Source:{s.IsSource} State:{s.CurrentState} Attempts:{s.NumberOfAttempts} Error:{s.ErrorCode} Desc:{s.FailureStateDesc}");
}
```

See also:

- [sys.dm_hadr_automatic_seeding](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-automatic-seeding)
