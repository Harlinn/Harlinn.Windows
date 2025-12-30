# DmPalProcessesReader — reference

Overview

`DmPalProcessesReader` wraps `sys.dm_pal_processes` and provides per-process metrics such as CPU time, memory usage and I/O statistics at the OS level.

Reader SQL

```
SELECT
  dpp.[process_id],
  dpp.[process_name],
  dpp.[processor_time],
  dpp.[user_time],
  dpp.[privileged_time],
  dpp.[virtual_bytes_peak],
  dpp.[virtual_bytes],
  dpp.[working_set_peak],
  dpp.[working_set],
  dpp.[page_file_bytes_peak],
  dpp.[page_file_bytes],
  dpp.[private_bytes],
  dpp.[thread_count],
  dpp.[elapsed_time],
  dpp.[pool_paged_bytes],
  dpp.[handle_count],
  dpp.[io_read_operations],
  dpp.[io_write_operations],
  dpp.[io_read_bytes],
  dpp.[io_write_bytes],
  dpp.[working_set_private]
FROM
  [sys].[dm_pal_processes] dpp
```

Columns and interpretation

- `process_id` — OS process identifier.
- `process_name` — process executable name.
- `processor_time` — total processor time used by the process.
- `user_time` — user-mode CPU time used.
- `privileged_time` — kernel-mode CPU time used.
- `virtual_bytes_peak` — peak virtual memory usage.
- `virtual_bytes` — current virtual memory usage.
- `working_set_peak` — peak working set size.
- `working_set` — current working set size.
- `page_file_bytes_peak` — peak page file usage.
- `page_file_bytes` — current page file usage.
- `private_bytes` — private bytes used by the process.
- `thread_count` — number of threads in the process.
- `elapsed_time` — elapsed runtime for the process.
- `pool_paged_bytes` — paged pool usage.
- `handle_count` — number of handles used by the process.
- `io_read_operations` / `io_write_operations` — count of I/O operations.
- `io_read_bytes` / `io_write_bytes` — bytes read/written by the process.
- `working_set_private` — private portion of the working set.

How to interpret

- Compare memory counters to identify memory-heavy processes.
- I/O counters help identify processes performing heavy disk operations.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmPalProcessesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmPalProcessesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"PID:{r.ProcessId} Name:{r.ProcessName} CPUms:{r.ProcessorTime} MemMB:{r.WorkingSet/1024/1024} IOReadBytes:{r.IoReadBytes}");
}
```

See also:

- [sys.dm_pal_processes](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-pal-processes)
