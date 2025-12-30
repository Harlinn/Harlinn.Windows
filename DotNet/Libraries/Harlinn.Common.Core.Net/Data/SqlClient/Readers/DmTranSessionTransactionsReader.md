# DmTranSessionTransactionsReader — reference

Overview

`DmTranSessionTransactionsReader` wraps `sys.dm_tran_session_transactions` and provides mapping between sessions and the transactions they have open, including descriptors and enlistment counts.

Reader SQL

```
SELECT
  dtst.[session_id],
  dtst.[transaction_id],
  dtst.[transaction_descriptor],
  dtst.[enlist_count],
  dtst.[is_user_transaction],
  dtst.[is_local],
  dtst.[is_enlisted],
  dtst.[is_bound],
  dtst.[open_transaction_count]
FROM
  [sys].[dm_tran_session_transactions] dtst
```

Columns and interpretation

- `session_id` — session id (SPID) owning the transaction.
- `transaction_id` — transaction id for the transaction.
- `transaction_descriptor` — binary descriptor of the transaction.
- `enlist_count` — number of enlistments for the session in the transaction.
- `is_user_transaction` — flag indicating whether it's a user transaction.
- `is_local` — flag indicating if the transaction is local.
- `is_enlisted` — flag indicating whether enlisted in DTC.
- `is_bound` — flag indicating whether the transaction is bound to the session.
- `open_transaction_count` — number of open transactions for the session.

How to interpret

- Useful to correlate sessions to their transactions and to examine descriptor details for troubleshooting enlistment and distributed transaction issues.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranSessionTransactionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranSessionTransactionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Session:{r.SessionId} Tx:{r.TransactionId} EnlistCount:{r.EnlistCount} IsEnlisted:{r.IsEnlisted} OpenTx:{r.OpenTransactionCount}");
}
```

See also:

- [sys.dm_tran_session_transactions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-session-transactions)
