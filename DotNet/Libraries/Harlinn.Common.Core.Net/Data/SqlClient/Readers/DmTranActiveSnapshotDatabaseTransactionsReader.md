# DmTranActiveSnapshotDatabaseTransactionsReader — reference

Overview

`DmTranActiveSnapshotDatabaseTransactionsReader` wraps `sys.dm_tran_active_snapshot_database_transactions` and returns information about active snapshot transactions per database used by versioning.

Reader SQL

```
SELECT
  dtasdt.[transaction_id],
  dtasdt.[transaction_sequence_num],
  dtasdt.[commit_sequence_num],
  dtasdt.[session_id],
  dtasdt.[is_snapshot],
  dtasdt.[first_snapshot_sequence_num],
  dtasdt.[max_version_chain_traversed],
  dtasdt.[average_version_chain_traversed],
  dtasdt.[elapsed_time_seconds]
FROM
  [sys].[dm_tran_active_snapshot_database_transactions] dtasdt
```

Columns and interpretation

- `transaction_id` — transaction identifier.
- `transaction_sequence_num` — sequence number assigned to the transaction.
- `commit_sequence_num` — commit sequence number for the transaction (if committed).
- `session_id` — session associated with the transaction.
- `is_snapshot` — flag indicating whether this transaction uses snapshot isolation.
- `first_snapshot_sequence_num` — the first snapshot sequence number associated with the transaction.
- `max_version_chain_traversed`, `average_version_chain_traversed` — metrics showing how many versioned rows/chains were traversed while reading versioned data.
- `elapsed_time_seconds` — elapsed lifetime of the transaction in seconds.

How to interpret

- Use `max_version_chain_traversed` and `average_version_chain_traversed` to identify transactions that may cause long version chain scans and retention of versioned rows.
- `elapsed_time_seconds` helps identify long-running snapshot transactions that can block version cleanup.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranActiveSnapshotDatabaseTransactionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranActiveSnapshotDatabaseTransactionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Tx:{r.TransactionId} Session:{r.SessionId} Snapshot:{r.IsSnapshot} ElapsedSec:{r.ElapsedTimeSeconds} MaxChain:{r.MaxVersionChainTraversed}");
}
```

See also:

- [sys.dm_tran_active_snapshot_database_transactions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-active-snapshot-database-transactions)
