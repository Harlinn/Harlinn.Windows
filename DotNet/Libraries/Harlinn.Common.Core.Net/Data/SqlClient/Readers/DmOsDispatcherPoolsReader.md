# DmOsDispatcherPoolsReader — reference

Overview

`DmOsDispatcherPoolsReader` wraps `sys.dm_os_dispatcher_pools` and lists dispatcher pools used internally by SQL Server's scheduling/worker system including counts and queue lengths.

Reader SQL

```
SELECT
  dodp.[dispatcher_pool_address],
  dodp.[Type],
  dodp.[Name],
  dodp.[dispatcher_count],
  dodp.[dispatcher_ideal_count],
  dodp.[dispatcher_timeout_ms],
  dodp.[dispatcher_waiting_count],
  dodp.[queue_length]
FROM
  [sys].[dm_os_dispatcher_pools] dodp
```

Columns and interpretation

- `dispatcher_pool_address` ? binary address identifying the dispatcher pool.
- `Type` ? type of dispatcher pool (string).
- `Name` ? pool name.
- `dispatcher_count` ? current number of dispatchers in the pool.
- `dispatcher_ideal_count` ? ideal count of dispatchers for the pool.
- `dispatcher_timeout_ms` ? dispatcher timeout in milliseconds.
- `dispatcher_waiting_count` ? number of dispatchers waiting.
- `queue_length` ? length of the work queue for the pool.

How to interpret

- Use `dispatcher_count` vs `dispatcher_ideal_count` and `queue_length` to identify pools that are under-provisioned or overloaded.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsDispatcherPoolsReader.Sql;
using var rdr = cmd.ExecuteReader();
var p = new DmOsDispatcherPoolsReader(rdr, ownsReader:false);
while (p.Read())
{
    Console.WriteLine($"Pool:{p.Name} Type:{p.Type} Count:{p.DispatcherCount}/{p.DispatcherIdealCount} Queue:{p.QueueLength}");
}
```

See also:

- [sys.dm_os_dispatcher_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-dispatcher-pools)
