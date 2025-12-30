# DmOsSysInfoReader — reference

Overview

`DmOsSysInfoReader` wraps `sys.dm_os_sys_info` and returns general system and SQL Server runtime metrics such as CPU ticks, memory sizes, scheduler counts and startup time.

Reader SQL

```
SELECT
  dosi.[cpu_ticks],
  dosi.[ms_ticks],
  dosi.[cpu_count],
  dosi.[hyperthread_ratio],
  dosi.[physical_memory_kb],
  dosi.[virtual_memory_kb],
  dosi.[committed_kb],
  dosi.[committed_target_kb],
  dosi.[visible_target_kb],
  dosi.[stack_size_in_bytes],
  dosi.[os_quantum],
  dosi.[os_error_mode],
  dosi.[os_priority_class],
  dosi.[max_workers_count],
  dosi.[scheduler_count],
  dosi.[scheduler_total_count],
  dosi.[deadlock_monitor_serial_number],
  dosi.[sqlserver_start_time_ms_ticks],
  dosi.[sqlserver_start_time],
  dosi.[affinity_type],
  dosi.[affinity_type_desc],
  dosi.[process_kernel_time_ms],
  dosi.[process_user_time_ms],
  dosi.[time_source],
  dosi.[time_source_desc],
  dosi.[virtual_machine_type],
  dosi.[virtual_machine_type_desc],
  dosi.[softnuma_configuration],
  dosi.[softnuma_configuration_desc],
  dosi.[process_physical_affinity],
  dosi.[sql_memory_model],
  dosi.[sql_memory_model_desc],
  dosi.[socket_count],
  dosi.[cores_per_socket],
  dosi.[numa_node_count],
  dosi.[container_type],
  dosi.[container_type_desc]
FROM
  [sys].[dm_os_sys_info] dosi
```

Columns and interpretation

- `cpu_ticks` — high-resolution CPU tick counter value used for time calculations.
- `ms_ticks` — millisecond tick counter value.
- `cpu_count` — number of logical CPUs reported by the OS.
- `hyperthread_ratio` — hyper-threading ratio (logical per physical core multiplier).
- `physical_memory_kb` — total physical memory available to the OS in kilobytes.
- `virtual_memory_kb` — total virtual memory available in kilobytes.
- `committed_kb` — current committed memory for the SQL Server process in kilobytes.
- `committed_target_kb` — target committed memory goal in kilobytes.
- `visible_target_kb` — memory visible to SQL Server (MAX_MEMORY or container limit) in kilobytes.
- `stack_size_in_bytes` — size of thread stacks in bytes.
- `os_quantum` — OS scheduling quantum value.
- `os_error_mode` — OS error mode configuration value.
- `os_priority_class` — process priority class as reported by the OS.
- `max_workers_count` — maximum number of workers SQL Server can create.
- `scheduler_count` — number of schedulers visible to SQL Server.
- `scheduler_total_count` — total number of scheduler objects.
- `deadlock_monitor_serial_number` — serial number for the deadlock monitor (incrementing counter).
- `sqlserver_start_time_ms_ticks` — server start time in ms ticks.
- `sqlserver_start_time` — server start time as a datetime.
- `affinity_type` — numeric code for CPU affinity configuration.
- `affinity_type_desc` — textual description of affinity configuration.
- `process_kernel_time_ms` — kernel mode CPU time used by the SQL Server process in milliseconds.
- `process_user_time_ms` — user mode CPU time used by the SQL Server process in milliseconds.
- `time_source` — numeric code for the time source used by the server.
- `time_source_desc` — textual description of time source.
- `virtual_machine_type` — numeric code indicating VM type.
- `virtual_machine_type_desc` — textual description of VM type.
- `softnuma_configuration` — numeric code for soft-NUMA configuration.
- `softnuma_configuration_desc` — textual description of soft-NUMA.
- `process_physical_affinity` — textual mask describing physical core affinity for the process.
- `sql_memory_model` — numeric code for SQL memory model (e.g., locked pages, dynamic).
- `sql_memory_model_desc` — textual description of SQL memory model.
- `socket_count` — number of CPU sockets detected.
- `cores_per_socket` — number of cores per socket.
- `numa_node_count` — number of NUMA nodes detected.
- `container_type` — numeric code describing containerization (if any).
- `container_type_desc` — textual description of container type.

How to interpret

- Use `cpu_count`, `socket_count`, `cores_per_socket` and `numa_node_count` to understand server topology.
- Compare `committed_kb`, `committed_target_kb` and `visible_target_kb` to evaluate memory pressure and configuration.
- `sqlserver_start_time` and ms tick values help correlate uptime and performance counters.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsSysInfoReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsSysInfoReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"CPUs:{r.CpuCount} Sockets:{r.SocketCount} Cores/Socket:{r.CoresPerSocket} NUMA:{r.NumaNodeCount} PhysicalMemMB:{r.PhysicalMemoryKb/1024}");
}
```

See also:

- [sys.dm_os_sys_info](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-sys-info)
