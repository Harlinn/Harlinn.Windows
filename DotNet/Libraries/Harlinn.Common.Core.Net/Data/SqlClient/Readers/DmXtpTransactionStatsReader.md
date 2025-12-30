# DmXtpTransactionStatsReader — reference

Overview

`DmXtpTransactionStatsReader` wraps `sys.dm_xtp_transaction_stats` and returns aggregated transaction statistics for In-Memory OLTP (XTP), such as counts of aborts, validation failures, row operations and scan statistics.

Reader SQL

```
SELECT
  dxts.[total_count],
  dxts.[read_only_count],
  dxts.[total_aborts],
  dxts.[system_aborts],
  dxts.[validation_failures],
  dxts.[dependencies_taken],
  dxts.[dependencies_failed],
  dxts.[savepoint_create],
  dxts.[savepoint_rollbacks],
  dxts.[savepoint_refreshes],
  dxts.[log_bytes_written],
  dxts.[log_IO_count],
  dxts.[phantom_scans_started],
  dxts.[phantom_scans_retries],
  dxts.[phantom_rows_touched],
  dxts.[phantom_rows_expiring],
  dxts.[phantom_rows_expired],
  dxts.[phantom_rows_expired_removed],
  dxts.[scans_started],
  dxts.[scans_retried],
  dxts.[rows_returned],
  dxts.[rows_touched],
  dxts.[rows_expiring],
  dxts.[rows_expired],
  dxts.[rows_expired_removed],
  dxts.[row_insert_attempts],
  dxts.[row_update_attempts],
  dxts.[row_delete_attempts],
  dxts.[write_conflicts],
  dxts.[unique_constraint_violations],
  dxts.[drop_table_memory_attempts],
  dxts.[drop_table_memory_failures]
FROM
  [sys].[dm_xtp_transaction_stats] dxts
```

Columns and interpretation

- `total_count` — total number of XTP transactions.
- `read_only_count` — number of read-only transactions.
- `total_aborts` — total aborts observed.
- `system_aborts` — system-initiated aborts count.
- `validation_failures` — count of validation failures.
- `dependencies_taken` / `dependencies_failed` — counts of dependency checks taken/failing.
- `savepoint_create`, `savepoint_rollbacks`, `savepoint_refreshes` — counts of savepoint operations.
- `log_bytes_written`, `log_IO_count` — logging volume counters.
- `phantom_scans_started`, `phantom_scans_retries`, `phantom_rows_*` — phantom detection and expiration statistics.
- `scans_started`, `scans_retried`, `rows_returned`, `rows_touched`, `rows_expiring`, `rows_expired`, `rows_expired_removed` — scan and row lifecycle counters.
- `row_insert_attempts`, `row_update_attempts`, `row_delete_attempts` — counts of DML attempts.
- `write_conflicts`, `unique_constraint_violations` — conflict and constraint failure counts.
- `drop_table_memory_attempts`, `drop_table_memory_failures` — counts relating to memory reclamation during DROP TABLE.

How to interpret

- Use these counters to assess transaction workload characteristics and failure modes. High `validation_failures` or `write_conflicts` indicates concurrency contention.
- `log_bytes_written` and `log_IO_count` indicate IO pressure from XTP transactions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXtpTransactionStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXtpTransactionStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"TotalTx:{r.TotalCount} Aborts:{r.TotalAborts} ValidationFailures:{r.ValidationFailures} WriteConflicts:{r.WriteConflicts}");
}
```

See also:

- [sys.dm_xtp_transaction_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xtp-transaction-stats)
