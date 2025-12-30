# DmOsHostsReader — reference

Overview

`DmOsHostsReader` wraps `sys.dm_os_hosts` and returns information about hosts recognized by SQL Server's OS layer including task counts, I/O statistics and default memory clerk address.

Reader SQL

```
SELECT
  doh.[host_address],
  doh.[Type],
  doh.[Name],
  doh.[enqueued_tasks_count],
  doh.[active_tasks_count],
  doh.[completed_ios_count],
  doh.[completed_ios_in_bytes],
  doh.[active_ios_count],
  doh.[default_memory_clerk_address]
FROM
  [sys].[dm_os_hosts] doh
```

Columns and interpretation

- `host_address` ? binary address identifying the host.
- `Type` ? host type description (e.g., worker host, scheduler host).
- `Name` ? host name.
- `enqueued_tasks_count` ? number of tasks enqueued for the host.
- `active_tasks_count` ? number of tasks currently active.
- `completed_ios_count` ? total completed I/O operations.
- `completed_ios_in_bytes` ? bytes processed by completed I/O.
- `active_ios_count` ? number of active I/O operations.
- `default_memory_clerk_address` ? address of the default memory clerk for the host.

How to interpret

- Useful to monitor host-level task and I/O activity and to find hosts with high I/O usage or many queued tasks.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsHostsReader.Sql;
using var rdr = cmd.ExecuteReader();
var h = new DmOsHostsReader(rdr, ownsReader:false);
while (h.Read())
{
    Console.WriteLine($"Host:{h.Name} Type:{h.Type} Enqueued:{h.EnqueuedTasksCount} ActiveTasks:{h.ActiveTasksCount} ActiveIOs:{h.ActiveIosCount}");
}
```

See also:

- [sys.dm_os_hosts](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-hosts)
