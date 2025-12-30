# DmTranGlobalTransactionsLogReader — reference

Overview

`DmTranGlobalTransactionsLogReader` wraps `sys.dm_tran_global_transactions_log` and returns log entries related to global transactions including prepare LSNs and commit timestamps.

Reader SQL

```
SELECT
  dtgtl.[transaction_id],
  dtgtl.[time_utc],
  dtgtl.[Dropped],
  dtgtl.[resource_manager_id],
  dtgtl.[resource_manager_prepare_lsn],
  dtgtl.[resource_manager_ack_received],
  dtgtl.[commit_timestamp]
FROM
  [sys].[dm_tran_global_transactions_log] dtgtl
```

Columns and interpretation

- `transaction_id` — GUID of the global transaction.
- `time_utc` — UTC timestamp of the log entry.
- `Dropped` — flag indicating if the log entry was dropped.
- `resource_manager_id` — GUID of the resource manager.
- `resource_manager_prepare_lsn` — prepare LSN for the resource manager (string nullable).
- `resource_manager_ack_received` — flag indicating whether ack has been received from resource manager.
- `commit_timestamp` — commit timestamp (long) associated with the log entry.

How to interpret

- Useful to track global transaction progress across prepare and commit phases and resource manager acknowledgements.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranGlobalTransactionsLogReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranGlobalTransactionsLogReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Tx:{r.TransactionId} TimeUTC:{r.TimeUtc} Dropped:{r.Dropped} RM:{r.ResourceManagerId} CommitTS:{r.CommitTimestamp}");
}
```

See also:

- [sys.dm_tran_global_transactions_log](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-global-transactions-log)
