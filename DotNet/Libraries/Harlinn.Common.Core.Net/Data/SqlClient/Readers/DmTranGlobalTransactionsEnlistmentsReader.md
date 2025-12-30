# DmTranGlobalTransactionsEnlistmentsReader — reference

Overview

`DmTranGlobalTransactionsEnlistmentsReader` wraps `sys.dm_tran_global_transactions_enlistments` and provides enlistment-level information for global (distributed) transactions such as isolation level, resource manager, and prepare LSN.

Reader SQL

```
SELECT
  dtgte.[transaction_id],
  dtgte.[database_id],
  dtgte.[iso_level],
  dtgte.[can_commit],
  dtgte.[enlistment_state],
  dtgte.[resource_manager_id],
  dtgte.[server_name],
  dtgte.[database_name],
  dtgte.[transaction_manager_server_name],
  dtgte.[transaction_manager_database_name],
  dtgte.[transaction_manager_database_id],
  dtgte.[transaction_manager_rmid],
  dtgte.[prepare_lsn],
  dtgte.[snapshot_timestamp],
  dtgte.[oldest_active_lsn],
  dtgte.[prepare_elapsed_time],
  dtgte.[object_ref_count],
  dtgte.[transaction_timeout],
  dtgte.[diag_status]
FROM
  [sys].[dm_tran_global_transactions_enlistments] dtgte
```

Columns and interpretation

- `transaction_id` — GUID identifying the global transaction.
- `database_id` — database id for the enlistment.
- `iso_level` — isolation level used by the enlistment.
- `can_commit` — flag indicating if the enlistment can commit.
- `enlistment_state` — numeric state value for the enlistment.
- `resource_manager_id` — GUID of the resource manager involved.
- `server_name`, `database_name` — server and database where the enlistment runs (nullable).
- `transaction_manager_server_name`, `transaction_manager_database_name` — transaction manager location information (nullable).
- `transaction_manager_database_id` — manager database id.
- `transaction_manager_rmid` — RMID GUID for the transaction manager.
- `prepare_lsn` — LSN where the resource was prepared (nullable string).
- `snapshot_timestamp` — snapshot timestamp (long) associated with the enlistment.
- `oldest_active_lsn` — oldest active LSN known to the enlistment.
- `prepare_elapsed_time` — elapsed time in prepare state (milliseconds or internal units).
- `object_ref_count` — reference count of objects held by the enlistment.
- `transaction_timeout` — configured timeout for the transaction.
- `diag_status` — diagnostic status flags.

How to interpret

- Use these fields to diagnose distributed transaction enlistment states, resource manager involvement and prepare/commit timing.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranGlobalTransactionsEnlistmentsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranGlobalTransactionsEnlistmentsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Tx:{r.TransactionId} DB:{r.DatabaseId} RM:{r.ResourceManagerId} PrepareLSN:{r.PrepareLsn} SnapshotTS:{r.SnapshotTimestamp}");
}
```

See also:

- [sys.dm_tran_global_transactions_enlistments](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-global-transactions-enlistments)
