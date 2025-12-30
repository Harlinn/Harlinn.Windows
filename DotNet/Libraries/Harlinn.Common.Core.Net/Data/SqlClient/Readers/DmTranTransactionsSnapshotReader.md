# DmTranTransactionsSnapshotReader — reference

Overview

`DmTranTransactionsSnapshotReader` wraps `sys.dm_tran_transactions_snapshot` and returns mapping between transactions and snapshot identifiers/sequence numbers used for versioning.

Reader SQL

```
SELECT
  dtts.[transaction_sequence_num],
  dtts.[snapshot_id],
  dtts.[snapshot_sequence_num]
FROM
  [sys].[dm_tran_transactions_snapshot] dtts
```

Columns and interpretation

- `transaction_sequence_num` — sequence number of the transaction.
- `snapshot_id` — snapshot identifier (integer) associated with the transaction.
- `snapshot_sequence_num` — sequence number of the snapshot.

How to interpret

- Use to correlate transactions with snapshot ids and sequence numbers to understand which snapshots are retaining versions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranTransactionsSnapshotReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranTransactionsSnapshotReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"TxSeq:{r.TransactionSequenceNum} SnapshotId:{r.SnapshotId} SnapshotSeq:{r.SnapshotSequenceNum}");
}
```

See also:

- [sys.dm_tran_transactions_snapshot](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-transactions-snapshot)
