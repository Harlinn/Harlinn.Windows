# DmReplTranhashReader — reference

Overview

`DmReplTranhashReader` wraps `sys.dm_repl_tranhash` and returns replication transaction hash bucket statistics used for tracking transactions in the replication engine.

Reader SQL

```
SELECT
  drt.[Buckets],
  drt.[hashed_trans],
  drt.[completed_trans],
  drt.[compensated_trans],
  drt.[first_begin_lsn],
  drt.[last_commit_lsn]
FROM
  [sys].[dm_repl_tranhash] drt
```

Columns and interpretation

- `Buckets` — number of buckets in the transaction hash structure.
- `hashed_trans` — number of transactions currently hashed into buckets.
- `completed_trans` — count of transactions marked completed.
- `compensated_trans` — count of compensated transactions (replication compensation logic).
- `first_begin_lsn` — LSN of the earliest transaction begin in the hash (string representation).
- `last_commit_lsn` — LSN of the latest commit in the hash (string representation).

How to interpret

- Use the counts to assess replication transaction backlog or hash table sizing.
- LSN values help determine the timeframe covered by transactions in the hash.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmReplTranhashReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmReplTranhashReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Buckets:{r.Buckets} Hashed:{r.HashedTrans} Completed:{r.CompletedTrans} FirstLSN:{r.FirstBeginLsn} LastLSN:{r.LastCommitLsn}");
}
```

See also:

- [sys.dm_repl_tranhash](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-repl-tranhash)
