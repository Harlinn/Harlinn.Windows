# DmTranGlobalTransactionsReader — reference

Overview

`DmTranGlobalTransactionsReader` wraps `sys.dm_tran_global_transactions` and returns global transaction information for distributed transactions, including phases timing and diagnostic status.

Reader SQL

```
SELECT
  dtgt.[transaction_id],
  dtgt.[database_id],
  dtgt.[transaction_state],
  dtgt.[resource_manager_id],
  dtgt.[resource_manager_server],
  dtgt.[resource_manager_database],
  dtgt.[resource_manager_dbid],
  dtgt.[resource_manager_state],
  dtgt.[resource_prepare_lsn],
  dtgt.[resource_phase_1_time],
  dtgt.[resource_phase_2_time],
  dtgt.[transaction_phase_1_time],
  dtgt.[transaction_phase_2_time],
  dtgt.[transaction_total_time],
  dtgt.[transaction_diag_status],
  dtgt.[resource_manager_diag_status],
  dtgt.[max_csn]
FROM
  [sys].[dm_tran_global_transactions] dtgt
```

Columns and interpretation

- `transaction_id` — GUID of the global transaction.
- `database_id` — database id associated with the transaction.
- `transaction_state` — numeric transaction state.
- `resource_manager_id` — GUID of the resource manager.
- `resource_manager_server`, `resource_manager_database` — server and database of the resource manager (nullable).
- `resource_manager_dbid` — database id of the resource manager.
- `resource_manager_state` — numeric state for the resource manager involvement.
- `resource_prepare_lsn` — LSN where resource manager prepared (nullable string).
- `resource_phase_1_time`, `resource_phase_2_time` — timing metrics for resource phases (likely milliseconds).
- `transaction_phase_1_time`, `transaction_phase_2_time`, `transaction_total_time` — timing metrics for transaction phases and total duration.
- `transaction_diag_status`, `resource_manager_diag_status` — diagnostic status codes.
- `max_csn` — maximum commit sequence number observed for the transaction.

How to interpret

- Timing fields help detect slow prepare/commit phases. Diagnostic status fields indicate error or special conditions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranGlobalTransactionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranGlobalTransactionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Tx:{r.TransactionId} DB:{r.DatabaseId} RM:{r.ResourceManagerId} PrepareLSN:{r.ResourcePrepareLsn} TotalTime:{r.TransactionTotalTime}");
}
```

See also:

- [sys.dm_tran_global_transactions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-global-transactions)
