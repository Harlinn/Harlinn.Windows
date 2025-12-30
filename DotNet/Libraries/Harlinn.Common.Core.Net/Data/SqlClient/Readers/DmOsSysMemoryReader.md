# DmOsSysMemoryReader — reference

Overview

`DmOsSysMemoryReader` wraps `sys.dm_os_sys_memory` and returns system memory state including totals, available amounts and kernel pool sizes.

Reader SQL

```
SELECT
  dosm.[total_physical_memory_kb],
  dosm.[available_physical_memory_kb],
  dosm.[total_page_file_kb],
  dosm.[available_page_file_kb],
  dosm.[system_cache_kb],
  dosm.[kernel_paged_pool_kb],
  dosm.[kernel_nonpaged_pool_kb],
  dosm.[system_high_memory_signal_state],
  dosm.[system_low_memory_signal_state],
  dosm.[system_memory_state_desc]
FROM
  [sys].[dm_os_sys_memory] dosm
```

Columns and interpretation

- `total_physical_memory_kb` — total physical RAM in kilobytes.
- `available_physical_memory_kb` — currently available physical RAM in kilobytes.
- `total_page_file_kb` — total configured page file size in kilobytes.
- `available_page_file_kb` — currently available page file space in kilobytes.
- `system_cache_kb` — memory used by the system cache in kilobytes.
- `kernel_paged_pool_kb` — size of the kernel paged pool in kilobytes.
- `kernel_nonpaged_pool_kb` — size of the kernel nonpaged pool in kilobytes.
- `system_high_memory_signal_state` — boolean indicator if system reached high memory signaling state.
- `system_low_memory_signal_state` — boolean indicator if system reached low memory signaling state.
- `system_memory_state_desc` — textual description of current system memory state.

How to interpret

- Low `available_physical_memory_kb` combined with active low-memory signals indicates memory pressure.
- `kernel_*_pool_kb` growth can indicate kernel-level resource usage; leaks may show as sustained increase.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsSysMemoryReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsSysMemoryReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"AvailMB:{r.AvailablePhysicalMemoryKb/1024} TotalMB:{r.TotalPhysicalMemoryKb/1024} PageFileMB:{r.TotalPageFileKb/1024} State:{r.SystemMemoryStateDesc}");
}
```

See also:

- [sys.dm_os_sys_memory](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-sys-memory)
