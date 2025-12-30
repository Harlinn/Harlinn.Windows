# DmXtpTransactionRecentRowsReader — reference

Overview

`DmXtpTransactionRecentRowsReader` wraps `sys.dm_xtp_transaction_recent_rows` and returns recent row images for active In-Memory OLTP (XTP) transactions, showing before/after images and timestamps.

Reader SQL

```
SELECT
  dxtrr.[node_id],
  dxtrr.[xtp_transaction_id],
  dxtrr.[row_address],
  dxtrr.[table_address],
  dxtrr.[before_begin],
  dxtrr.[before_end],
  dxtrr.[before_links],
  dxtrr.[before_time],
  dxtrr.[after_begin],
  dxtrr.[after_end],
  dxtrr.[after_links],
  dxtrr.[after_time],
  dxtrr.[Outcome]
FROM
  [sys].[dm_xtp_transaction_recent_rows] dxtrr
```

Columns and interpretation

- `node_id` — node id in an availability group or internal node identifier.
- `xtp_transaction_id` — In-Memory OLTP transaction id.
- `row_address` — binary pointer to the row image before/after.
- `table_address` — binary pointer to the table (rowset) structure.
- `before_begin`, `before_end`, `before_links`, `before_time` — metrics and timestamps for the 'before' image of the row; exact encoding is internal.
- `after_begin`, `after_end`, `after_links`, `after_time` — metrics and timestamps for the 'after' image.
- `Outcome` — binary field encoding the outcome/status of the recent row operation.

How to interpret

- This DMV is low-level and intended for debugging In-Memory OLTP transaction behavior; the binary pointers and time fields are internal representations.
- Use `xtp_transaction_id` to correlate with transaction statistics in `sys.dm_xtp_transaction_stats`.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXtpTransactionRecentRowsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXtpTransactionRecentRowsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Node:{r.NodeId} Tx:{r.XtpTransactionId} TableAddr:{BitConverter.ToString(r.TableAddress)} OutcomeLen:{r.Outcome.Length}");
}
```

See also:

- [sys.dm_xtp_transaction_recent_rows](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xtp-transaction-recent-rows)
