# DmTranCurrentTransactionReader — reference

Overview

`DmTranCurrentTransactionReader` wraps `sys.dm_tran_current_transaction` and returns details about the current transaction on the session, including sequence numbers and snapshot information.

Reader SQL

```
SELECT
  dtct0.[transaction_id],
  dtct0.[transaction_sequence_num],
  dtct0.[transaction_is_snapshot],
  dtct0.[first_snapshot_sequence_num],
  dtct0.[last_transaction_sequence_num],
  dtct0.[first_useful_sequence_num]
FROM
  [sys].[dm_tran_current_transaction] dtct0
```

Columns and interpretation

- `transaction_id` — transaction identifier for the current transaction.
- `transaction_sequence_num` — sequence number assigned to the transaction.
- `transaction_is_snapshot` — flag indicating whether the current transaction is a snapshot transaction.
- `first_snapshot_sequence_num` — sequence number for the first snapshot associated with the transaction (if applicable).
- `last_transaction_sequence_num` — sequence number of the last transaction in the context.
- `first_useful_sequence_num` — first useful sequence number for version cleanup; helps determine which versions are still needed.

How to interpret

- Useful for session-level inspection to determine whether the current transaction uses snapshot isolation and to correlate with version store entries.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranCurrentTransactionReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranCurrentTransactionReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"TxId:{r.TransactionId} Seq:{r.TransactionSequenceNum} IsSnapshot:{r.TransactionIsSnapshot} FirstUsefulSeq:{r.FirstUsefulSequenceNum}");
}
```

See also:

- [sys.dm_tran_current_transaction](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-current-transaction)
