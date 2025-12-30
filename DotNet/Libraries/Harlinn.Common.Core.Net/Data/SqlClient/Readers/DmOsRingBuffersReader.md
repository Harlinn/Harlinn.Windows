# DmOsRingBuffersReader — reference

Overview

`DmOsRingBuffersReader` wraps `sys.dm_os_ring_buffers` and exposes diagnostics ring buffers that contain internal SQL Server events and telemetry records.

Reader SQL

```
SELECT
  dorb.[ring_buffer_address],
  dorb.[ring_buffer_type],
  dorb.[Timestamp],
  dorb.[Record]
FROM
  [sys].[dm_os_ring_buffers] dorb
```

Columns and interpretation

- `ring_buffer_address` ? binary address identifier for the ring buffer.
- `ring_buffer_type` ? type of ring buffer (e.g., scheduler_ring_buffer).
- `Timestamp` ? timestamp value associated with the record (ticks or epoch depending on DMV semantics).
- `Record` ? textual or XML payload for the ring buffer event.

How to interpret

- Useful for reading internal events like deadlock chains, scheduler events and other OS-level telemetry emitted as ring buffer records.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsRingBuffersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsRingBuffersReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Type:{r.RingBufferType} Time:{r.Timestamp} Record:{r.Record}");
}
```

See also:

- [sys.dm_os_ring_buffers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-ring-buffers)
