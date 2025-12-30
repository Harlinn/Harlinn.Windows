# DmTranGlobalRecoveryTransactionsReader — reference

Overview

`DmTranGlobalRecoveryTransactionsReader` wraps `sys.dm_tran_global_recovery_transactions` and returns information about global transactions that are being recovered, including their UOW and transaction manager details.

Reader SQL

```
SELECT
  dtgrt.[database_id],
  dtgrt.[transaction_uow],
  dtgrt.[transaction_manager_dbid],
  dtgrt.[transaction_manager_rmid],
  dtgrt.[transaction_manager_server_name],
  dtgrt.[transaction_manager_database_name]
FROM
  [sys].[dm_tran_global_recovery_transactions] dtgrt
```

Columns and interpretation

- `database_id` — database id associated with the global transaction.
- `transaction_uow` — GUID unit-of-work identifying the global transaction.
- `transaction_manager_dbid` — database id of the transaction manager.
- `transaction_manager_rmid` — RMID (resource manager id) GUID for the manager.
- `transaction_manager_server_name` — server name hosting the transaction manager (nullable).
- `transaction_manager_database_name` — database name hosting the transaction manager (nullable).

How to interpret

- Useful when diagnosing distributed transaction recovery and mapping global transactions to their managers.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranGlobalRecoveryTransactionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranGlobalRecoveryTransactionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DatabaseId} UOW:{r.TransactionUow} TMServer:{r.TransactionManagerServerName} TMDB:{r.TransactionManagerDatabaseName}");
}
```

See also:

- [sys.dm_tran_global_recovery_transactions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-global-recovery-transactions)
