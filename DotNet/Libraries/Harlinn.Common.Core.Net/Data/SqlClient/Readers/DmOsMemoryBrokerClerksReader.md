# DmOsMemoryBrokerClerksReader — reference

Overview

`DmOsMemoryBrokerClerksReader` wraps `sys.dm_os_memory_broker_clerks` and returns memory usage and simulated benefit metrics for memory clerk categories managed by the memory broker.

Reader SQL

```
SELECT
  dombc.[clerk_name],
  dombc.[total_kb],
  dombc.[simulated_kb],
  dombc.[simulation_benefit],
  dombc.[internal_benefit],
  dombc.[external_benefit],
  dombc.[value_of_memory],
  dombc.[periodic_freed_kb],
  dombc.[internal_freed_kb]
FROM
  [sys].[dm_os_memory_broker_clerks] dombc
```

Columns and interpretation

- `clerk_name` ? memory clerk category name.
- `total_kb` ? total kilobytes currently held by this clerk.
- `simulated_kb` ? kilobytes that would be freed under simulated memory pressure.
- `simulation_benefit` ? metric indicating benefit (score) from freeing simulated memory.
- `internal_benefit` / `external_benefit` ? benefit breakdown for internal vs external consumers.
- `value_of_memory` ? numeric value representing importance of memory held by this clerk.
- `periodic_freed_kb` ? KB freed periodically by the clerk.
- `internal_freed_kb` ? KB freed internally by the clerk.

How to interpret

- Use to determine which memory clerks hold significant memory and which would yield the greatest benefit if trimmed under memory pressure.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsMemoryBrokerClerksReader.Sql;
using var rdr = cmd.ExecuteReader();
var c = new DmOsMemoryBrokerClerksReader(rdr, ownsReader:false);
while (c.Read())
{
    Console.WriteLine($"Clerk:{c.ClerkName} TotalKB:{c.TotalKb} SimKB:{c.SimulatedKb} Value:{c.ValueOfMemory}");
}
```

See also:

- [sys.dm_os_memory_broker_clerks](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-memory-broker-clerks)
