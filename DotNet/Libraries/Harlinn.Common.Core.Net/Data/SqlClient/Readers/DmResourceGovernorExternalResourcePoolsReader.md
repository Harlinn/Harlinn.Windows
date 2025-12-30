# DmResourceGovernorExternalResourcePoolsReader — reference

Overview

`DmResourceGovernorExternalResourcePoolsReader` wraps `sys.dm_resource_governor_external_resource_pools` and returns statistics and configuration for external resource pools managed by Resource Governor.

Reader SQL

```
SELECT
  drgerp.[external_pool_id],
  drgerp.[Name],
  drgerp.[pool_version],
  drgerp.[max_cpu_percent],
  drgerp.[max_processes],
  drgerp.[max_memory_percent],
  drgerp.[statistics_start_time],
  drgerp.[peak_memory_kb],
  drgerp.[write_io_count],
  drgerp.[read_io_count],
  drgerp.[total_cpu_kernel_ms],
  drgerp.[total_cpu_user_ms],
  drgerp.[active_processes_count]
FROM
  [sys].[dm_resource_governor_external_resource_pools] drgerp
```

Columns and interpretation

- `external_pool_id` — identifier of the external pool.
- `Name` — pool name.
- `pool_version` — version or generation counter for the pool configuration.
- `max_cpu_percent` — configured maximum CPU percent allowed.
- `max_processes` — configured maximum processes in the pool.
- `max_memory_percent` — configured memory percent limit for the pool.
- `statistics_start_time` — timestamp when statistics collection started.
- `peak_memory_kb` — peak memory usage observed for the pool in KB.
- `write_io_count` / `read_io_count` — counts of I/O operations.
- `total_cpu_kernel_ms` / `total_cpu_user_ms` — cumulative CPU time used by pool, in milliseconds.
- `active_processes_count` — number of active processes currently in the pool.

How to interpret

- Use CPU/memory/I/O counters to see pool resource usage and detect overruns or contention.
- `pool_version` helps track configuration changes.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmResourceGovernorExternalResourcePoolsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmResourceGovernorExternalResourcePoolsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Pool:{r.ExternalPoolId} Name:{r.Name} CPU%:{r.MaxCpuPercent} MemKB:{r.PeakMemoryKb} ActiveProcs:{r.ActiveProcessesCount}");
}
```

See also:

- [sys.dm_resource_governor_external_resource_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-resource-governor-external-resource-pools)
