# DmTranCurrentSnapshotReader — reference

Overview

`DmTranCurrentSnapshotReader` wraps `sys.dm_tran_current_snapshot` and returns the current transaction sequence number for the database snapshot used by the session.

Reader SQL

```
SELECT
  dtcs.[transaction_sequence_num]
FROM
  [sys].[dm_tran_current_snapshot] dtcs
```

Columns and interpretation

- `transaction_sequence_num` — the current transaction sequence number for the active snapshot. This value identifies the sequence number assigned to the snapshot and can be used to correlate versioning activity and retention of versions.

How to interpret

- A null or absent value indicates the session is not using a snapshot. For snapshot isolation or read-committed snapshot, this value represents the snapshot point.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranCurrentSnapshotReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranCurrentSnapshotReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"CurrentSnapshotSequence:{r.TransactionSequenceNum}");
}
```

See also:

- [sys.dm_tran_current_snapshot](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-current-snapshot)
