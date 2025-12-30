# DmTranCommitTableReader — reference

Overview

`DmTranCommitTableReader` wraps `sys.dm_tran_commit_table` and returns recent commit table entries, including commit timestamps and sequence numbers used internally by the transaction manager.

Reader SQL

```
SELECT
  dtct.[commit_ts],
  dtct.[xdes_id],
  dtct.[commit_lbn],
  dtct.[commit_csn],
  dtct.[commit_time]
FROM
  [sys].[dm_tran_commit_table] dtct
```

Columns and interpretation

- `commit_ts` — commit timestamp (internal format, nullable).
- `xdes_id` — transaction descriptor id.
- `commit_lbn` — commit log block number.
- `commit_csn` — commit sequence number.
- `commit_time` — commit time as datetime.

How to interpret

- Use to inspect recent commits and correlate commit ordering and timing for troubleshooting transaction behavior.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranCommitTableReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranCommitTableReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"CommitTime:{r.CommitTime} CommitLBN:{r.CommitLbn} CSN:{r.CommitCsn} Xdes:{r.XdesId}");
}
```

See also:

- [sys.dm_tran_commit_table](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-commit-table)
