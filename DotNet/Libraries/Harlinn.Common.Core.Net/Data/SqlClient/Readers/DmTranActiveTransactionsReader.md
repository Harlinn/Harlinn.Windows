# DmTranActiveTransactionsReader — reference

Overview

`DmTranActiveTransactionsReader` wraps `sys.dm_tran_active_transactions` and returns information about currently active transactions in the instance, including DTC status and isolation levels.

Reader SQL

```
SELECT
  dtat0.[transaction_id],
  dtat0.[Name],
  dtat0.[transaction_begin_time],
  dtat0.[transaction_type],
  dtat0.[transaction_uow],
  dtat0.[transaction_state],
  dtat0.[transaction_status],
  dtat0.[transaction_status2],
  dtat0.[dtc_state],
  dtat0.[dtc_status],
  dtat0.[dtc_isolation_level],
  dtat0.[filestream_transaction_id]
FROM
  [sys].[dm_tran_active_transactions] dtat0
```

Columns and interpretation

- `transaction_id` — transaction identifier.
- `Name` — transaction name where provided.
- `transaction_begin_time` — when the transaction began.
- `transaction_type` — numeric code representing transaction type (local, distributed, etc.).
- `transaction_uow` — GUID unit-of-work for distributed transactions (nullable).
- `transaction_state` / `transaction_status` / `transaction_status2` — numeric status/state codes for the transaction.
- `dtc_state` / `dtc_status` / `dtc_isolation_level` — DTC-related state, status and isolation level for distributed transactions.
- `filestream_transaction_id` — filestream transaction identifier (binary) when filestream is used.

How to interpret

- Useful for monitoring active transactions and diagnosing hung or long-running transactions.
- DTC fields help diagnose issues with distributed transactions and their coordinator.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranActiveTransactionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranActiveTransactionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Tx:{r.TransactionId} Begin:{r.TransactionBeginTime} Type:{r.TransactionType} State:{r.TransactionState} DTCstate:{r.DtcState}");
}
```

See also:

- [sys.dm_tran_active_transactions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-active-transactions)
