# DmOsStacksReader — reference

Overview

`DmOsStacksReader` wraps `sys.dm_os_stacks` and returns individual stack frames for kernel or worker stacks exposed by the server.

Reader SQL

```
SELECT
  dos1.[stack_address],
  dos1.[frame_index],
  dos1.[frame_address]
FROM
  [sys].[dm_os_stacks] dos1
```

Columns and interpretation

- `stack_address` — binary address identifying the stack instance.
- `frame_index` — index of the frame within the stack; lower values are closer to the stack base or top depending on platform.
- `frame_address` — binary address of the specific frame (instruction pointer) on the stack.

How to interpret

- Use frames together with debugging tools or symbol information to identify call stacks for threads/workers.
- Multiple rows with the same `stack_address` represent sequential frames for the same stack.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsStacksReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsStacksReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Stack:{BitConverter.ToString(r.StackAddress)} FrameIdx:{r.FrameIndex} FrameAddr:{BitConverter.ToString(r.FrameAddress)}");
}
```

See also:

- [sys.dm_os_stacks](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-stacks)
