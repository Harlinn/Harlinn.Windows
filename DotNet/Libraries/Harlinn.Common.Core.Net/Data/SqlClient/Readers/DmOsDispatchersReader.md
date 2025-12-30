# DmOsDispatchersReader — reference

Overview

`DmOsDispatchersReader` wraps `sys.dm_os_dispatchers` and returns details about individual dispatchers assigned to tasks/work items including state, wait times and processed item counts.

Reader SQL

```
SELECT
  dod.[dispatcher_pool_address],
  dod.[task_address],
  dod.[State],
  dod.[wait_duration],
  dod.[current_item_duration],
  dod.[items_processed],
  dod.[fade_end_time]
FROM
  [sys].[dm_os_dispatchers] dod
```

Columns and interpretation

- `dispatcher_pool_address` ? binary address for the dispatcher pool that owns the dispatcher.
- `task_address` ? binary address for the task currently executing or assigned.
- `State` ? textual state of the dispatcher (Running, Waiting, Idle, etc.).
- `wait_duration` ? time the dispatcher has been waiting (ticks / microseconds depending on DMV semantics).
- `current_item_duration` ? duration spent on the current item.
- `items_processed` ? number of items the dispatcher has processed.
- `fade_end_time` ? timestamp or time value indicating when dispatcher fade-out ends.

How to interpret

- Monitor `wait_duration` and `items_processed` to detect contention or overloaded dispatchers. High wait with low processed counts may indicate stalls.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsDispatchersReader.Sql;
using var rdr = cmd.ExecuteReader();
var d = new DmOsDispatchersReader(rdr, ownsReader:false);
while (d.Read())
{
    Console.WriteLine($"Pool:{BitConverter.ToString(d.DispatcherPoolAddress)} Task:{BitConverter.ToString(d.TaskAddress)} State:{d.State} Wait:{d.WaitDuration} Items:{d.ItemsProcessed}");
}
```

See also:

- [sys.dm_os_dispatchers](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-dispatchers)
