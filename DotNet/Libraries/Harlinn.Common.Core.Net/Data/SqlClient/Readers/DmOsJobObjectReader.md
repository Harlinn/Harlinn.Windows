# DmOsJobObjectReader — reference

Overview

`DmOsJobObjectReader` wraps `sys.dm_os_job_object` and returns resource management settings and runtime statistics of the Windows Job Object used by SQL Server to constrain resources such as CPU and memory.

Reader SQL

```
SELECT
  dojo.[cpu_rate],
  dojo.[cpu_affinity_mask],
  dojo.[cpu_affinity_group],
  dojo.[memory_limit_mb],
  dojo.[process_memory_limit_mb],
  dojo.[workingset_limit_mb],
  dojo.[non_sos_mem_gap_mb],
  dojo.[low_mem_signal_threshold_mb],
  dojo.[total_user_time],
  dojo.[total_kernel_time],
  dojo.[write_operation_count],
  dojo.[read_operation_count],
  dojo.[peak_process_memory_used_mb],
  dojo.[peak_job_memory_used_mb],
  dojo.[process_physical_affinity]
FROM
  [sys].[dm_os_job_object] dojo
```

Columns and interpretation

- `cpu_rate` ? CPU rate limit applied to the job (percentage or weight depending on settings).
- `cpu_affinity_mask` ? CPU affinity mask assigned for processes in the job.
- `cpu_affinity_group` ? affinity group id.
- `memory_limit_mb` ? memory limit for the job in MB.
- `process_memory_limit_mb` ? per-process memory limit in MB.
- `workingset_limit_mb` ? working set memory limit in MB.
- `non_sos_mem_gap_mb` ? gap reserved for non-SOS memory in MB.
- `low_mem_signal_threshold_mb` ? threshold for low memory signals in MB.
- `total_user_time` / `total_kernel_time` ? cumulative CPU times.
- `write_operation_count` / `read_operation_count` ? I/O operation counts.
- `peak_process_memory_used_mb` / `peak_job_memory_used_mb` ? peak memory usage metrics.
- `process_physical_affinity` ? string describing physical CPU affinity.

How to interpret

- Use to monitor and tune job-level resource constraints. Compare usage counters against limits to find throttling.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsJobObjectReader.Sql;
using var rdr = cmd.ExecuteReader();
var j = new DmOsJobObjectReader(rdr, ownsReader:false);
if (j.Read())
{
    Console.WriteLine($"CPU rate:{j.CpuRate} MemLimitMB:{j.MemoryLimitMb} PeakJobMB:{j.PeakJobMemoryUsedMb} Affinity:{j.ProcessPhysicalAffinity}");
}
```

See also:

- [sys.dm_os_job_object](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-job-object)
