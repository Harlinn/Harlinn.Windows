# DmDbXtpCheckpointInternalsReader — reference

Overview

`DmDbXtpCheckpointInternalsReader` wraps the dynamic management view `sys.dm_db_xtp_checkpoint_internals` and exposes internal checkpoint housekeeping values for In-Memory OLTP (XTP). These values are useful when diagnosing checkpoint progress, synchronization and recovery readiness for memory-optimized data.

Reader SQL

```
SELECT
  ddxci.[checkpoint_id],
  ddxci.[checkpoint_timestamp],
  ddxci.[last_segment_lsn],
  ddxci.[recovery_lsn],
  ddxci.[is_synchronized]
FROM
  [sys].[dm_db_xtp_checkpoint_internals] ddxci
```

Columns (how to interpret)

- `checkpoint_id` ? `CheckpointId` (long)
  - Monotonically increasing identifier for the checkpoint. Use to correlate checkpoint lifecycle events; higher = more recent.

- `checkpoint_timestamp` ? `CheckpointTimestamp` (long?)
  - Probably/guesswork: internal timestamp or ticks when the checkpoint was created. Not a SQL Server DATETIME; treat as opaque unless converted using product-specific tools.

- `last_segment_lsn` ? `LastSegmentLsn` (decimal?)
  - The LSN (log sequence number) of the last segment processed by the checkpoint subsystem. Compare with other LSNs to determine how far checkpointing has progressed in the transaction log.

- `recovery_lsn` ? `RecoveryLsn` (decimal?)
  - LSN used as a recovery point candidate. If database recovery requires replay, this LSN is the candidate for recovery processing.

- `is_synchronized` ? `IsSynchronized` (bool?)
  - Whether checkpoint components are synchronized (true) or not (false). A value of false may indicate in-progress work or stalls.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpCheckpointInternalsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbXtpCheckpointInternalsReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"CheckpointId: {r.CheckpointId}");
    Console.WriteLine($" CheckpointTimestamp (opaque): {r.CheckpointTimestamp}");
    Console.WriteLine($" LastSegmentLSN: {r.LastSegmentLsn}");
    Console.WriteLine($" RecoveryLSN: {r.RecoveryLsn}");
    Console.WriteLine($" IsSynchronized: {r.IsSynchronized}");
}
```

See also:

- [sys.dm_db_xtp_checkpoint_internals](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-checkpoint-internals)