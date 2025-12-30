# DmServerMemoryDumpsReader — reference

Overview

`DmServerMemoryDumpsReader` wraps `sys.dm_server_memory_dumps` and lists server-generated memory dump files with timestamps and sizes.

Reader SQL

```
SELECT
  dsmd.[Filename],
  dsmd.[creation_time],
  dsmd.[size_in_bytes]
FROM
  [sys].[dm_server_memory_dumps] dsmd
```

Columns and interpretation

- `Filename` — path and name of the memory dump file.
- `creation_time` — timestamp when the dump was created.
- `size_in_bytes` — file size in bytes (nullable if unknown).

How to interpret

- Use this DMV to enumerate crash or manual memory dumps produced by SQL Server for debugging; combine with debugging tools to analyze.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmServerMemoryDumpsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmServerMemoryDumpsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Dump:{r.Filename} Time:{r.CreationTime} Size:{r.SizeInBytes}");
}
```

See also:

- [sys.dm_server_memory_dumps](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-server-memory-dumps)
