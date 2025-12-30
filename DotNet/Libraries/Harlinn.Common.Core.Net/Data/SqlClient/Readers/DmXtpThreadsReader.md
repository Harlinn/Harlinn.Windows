# DmXtpThreadsReader — reference

Overview

`DmXtpThreadsReader` wraps `sys.dm_xtp_threads` and returns information about XTP worker threads, including retired row and transaction counts processed by each thread.

Reader SQL

```
SELECT
  dxt.[thread_address],
  dxt.[thread_type],
  dxt.[thread_type_desc],
  dxt.[retired_row_count],
  dxt.[retired_transaction_count]
FROM
  [sys].[dm_xtp_threads] dxt
```

Columns and interpretation

- `thread_address` — binary pointer identifying the thread control block.
- `thread_type` — numeric code for the thread type.
- `thread_type_desc` — textual description of the thread type.
- `retired_row_count` — number of rows retired (processed and cleaned up) by the thread.
- `retired_transaction_count` — number of transactions retired by the thread.

How to interpret

- Use retired counts to understand per-thread throughput and whether certain threads are doing disproportionate work.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXtpThreadsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXtpThreadsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Thread:{BitConverter.ToString(r.ThreadAddress)} Type:{r.ThreadTypeDesc} RowsRetired:{r.RetiredRowCount} TxRetired:{r.RetiredTransactionCount}");
}
```

See also:

- [sys.dm_xtp_threads](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xtp-threads)
