# DmDbXtpTransactionsReader — reference

Overview

`DmDbXtpTransactionsReader` wraps `sys.dm_db_xtp_transactions` and exposes detailed information about memory-optimized (XTP) transactions, including TSN ranges, state, resource usage, commit dependencies and dependent addresses used for internal tracking.

Reader SQL

```
SELECT
  ddxt.[node_id],
  ddxt.[xtp_transaction_id],
  ddxt.[transaction_id],
  ddxt.[session_id],
  ddxt.[begin_tsn],
  ddxt.[end_tsn],
  ddxt.[State],
  ddxt.[state_desc],
  ddxt.[Result],
  ddxt.[result_desc],
  ddxt.[xtp_parent_transaction_node_id],
  ddxt.[xtp_parent_transaction_id],
  ddxt.[last_error],
  ddxt.[is_speculative],
  ddxt.[is_prepared],
  ddxt.[is_delayed_durability],
  ddxt.[memory_address],
  ddxt.[database_address],
  ddxt.[thread_id],
  ddxt.[read_set_row_count],
  ddxt.[write_set_row_count],
  ddxt.[scan_set_count],
  ddxt.[savepoint_garbage_count],
  ddxt.[log_bytes_required],
  ddxt.[count_of_allocations],
  ddxt.[allocated_bytes],
  ddxt.[reserved_bytes],
  ddxt.[commit_dependency_count],
  ddxt.[commit_dependency_total_attempt_count],
  ddxt.[scan_area],
  ddxt.[scan_area_desc],
  ddxt.[scan_location],
  ddxt.[dependent_1_address],
  ...
  ddxt.[dependent_8_address]
FROM
  [sys].[dm_db_xtp_transactions] ddxt
```

Columns (how to interpret)

- `node_id` ? NUMA/node id where transaction is executing.

- `xtp_transaction_id` ? internal XTP transaction identifier.

- `transaction_id` ? transaction id visible to SQL Server engine.

- `session_id` ? session SPID associated with transaction.

- `begin_tsn` / `end_tsn` ? transaction sequence number range (TSNs) assigned for the transaction's lifetime.

- `State` / `state_desc` ? numeric and textual state (active, committing, committed, aborting, aborted) to understand progress.

- `Result` / `result_desc` ? numeric and textual result code (success, conflict, timeout, abort reason).

- `xtp_parent_transaction_node_id` / `xtp_parent_transaction_id` ? parent transaction references for nested or distributed transactions.

- `last_error` ? last error code recorded for transaction attempts.

- `is_speculative`, `is_prepared`, `is_delayed_durability` ? flags indicating transaction properties.

- `memory_address` / `database_address` ? internal addresses for transaction control block and database context; use for deep diagnostics.

- `thread_id` ? worker thread id servicing the transaction.

- `read_set_row_count` / `write_set_row_count` / `scan_set_count` ? resource usage counts indicating how many rows were read, written or scanned by the transaction; useful to estimate working set.

- `savepoint_garbage_count` ? number of obsolete savepoints pending cleanup.

- `log_bytes_required` ? estimate of log bytes required for commit; useful for log planning.

- `count_of_allocations` / `allocated_bytes` / `reserved_bytes` ? memory allocation counts and byte sizes used by transaction.

- `commit_dependency_count` / `commit_dependency_total_attempt_count` ? counts indicating number of commit dependencies and attempts; high values might indicate complex commit coordination.

- `scan_area` / `scan_area_desc` / `scan_location` ? scan area codes and description showing what kind of scan the transaction performed and where.

- `dependent_n_address` ? addresses of up to 8 dependent objects/resources tracked for commit dependency resolution.

Interpretation

- Monitor transactions with large read_set/write_set counts and high allocated/reserved bytes for potential resource pressure.
- Look at `state_desc` and `result_desc` to identify blocked/failed transactions.
- `log_bytes_required` helps determine whether delayed durability is impacting log usage.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpTransactionsReader.Sql;
using var reader = cmd.ExecuteReader();
var t = new DmDbXtpTransactionsReader(reader, ownsReader: false);
while (t.Read())
{
    Console.WriteLine($"XTP Tx {t.XtpTransactionId} TxId {t.TransactionId} Sess {t.SessionId} State: {t.StateDesc}");
    Console.WriteLine($" TSN range: {t.BeginTsn}-{t.EndTsn} Read/Write rows: {t.ReadSetRowCount}/{t.WriteSetRowCount}");
    Console.WriteLine($" Allocated bytes: {t.AllocatedBytes} Reserved: {t.ReservedBytes} Log bytes required: {t.LogBytesRequired}");
}
```

See also:

- [sys.dm_db_xtp_transactions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-xtp-transactions)
