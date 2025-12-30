# DmTranAbortedTransactionsReader — reference

Overview

`DmTranAbortedTransactionsReader` wraps `sys.dm_tran_aborted_transactions` and returns details about transactions that were aborted including LSNs and nesting information.

Reader SQL

```
SELECT
  dtat.[transaction_id],
  dtat.[database_id],
  dtat.[begin_xact_lsn],
  dtat.[end_xact_lsn],
  dtat.[begin_time],
  dtat.[nest_aborted]
FROM
  [sys].[dm_tran_aborted_transactions] dtat
```

Columns and interpretation

- `transaction_id` — transaction identifier.
- `database_id` — database id where the transaction ran.
- `begin_xact_lsn` / `end_xact_lsn` — LSNs marking the transaction begin and end.
- `begin_time` — when the transaction began.
- `nest_aborted` — boolean indicating if nested transactions were also aborted.

How to interpret

- Useful for diagnosing aborted transactions and their scope; LSNs can correlate with log records.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranAbortedTransactionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranAbortedTransactionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Tx:{r.TransactionId} DB:{r.DatabaseId} BeginLSN:{r.BeginXactLsn} BeginTime:{r.BeginTime} NestedAborted:{r.NestAborted}");
}
```

See also:

- [sys.dm_tran_aborted_transactions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-aborted-transactions)
