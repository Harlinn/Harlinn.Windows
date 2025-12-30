# DmOsProcessMemoryReader — reference

Overview

`DmOsProcessMemoryReader` wraps `sys.dm_os_process_memory` and returns memory usage statistics for the SQL Server process including physical memory in use, virtual address space usage and low-memory indicators.

Reader SQL

```
SELECT
  dopm.[physical_memory_in_use_kb],
  dopm.[large_page_allocations_kb],
  dopm.[locked_page_allocations_kb],
  dopm.[total_virtual_address_space_kb],
  dopm.[virtual_address_space_reserved_kb],
  dopm.[virtual_address_space_committed_kb],
  dopm.[virtual_address_space_available_kb],
  dopm.[page_fault_count],
  dopm.[memory_utilization_percentage],
  dopm.[available_commit_limit_kb],
  dopm.[process_physical_memory_low],
  dopm.[process_virtual_memory_low]
FROM
  [sys].[dm_os_process_memory] dopm
```

Columns and interpretation

- `physical_memory_in_use_kb` ? physical memory used by the process in KB.
- `large_page_allocations_kb` ? large page allocations in KB.
- `locked_page_allocations_kb` ? locked page allocations in KB.
- `total_virtual_address_space_kb` ? total VA space in KB.
- `virtual_address_space_reserved_kb` ? reserved VA in KB.
- `virtual_address_space_committed_kb` ? committed VA in KB.
- `virtual_address_space_available_kb` ? VA available in KB.
- `page_fault_count` ? number of page faults observed.
- `memory_utilization_percentage` ? percentage of memory utilization.
- `available_commit_limit_kb` ? available commit limit in KB.
- `process_physical_memory_low` / `process_virtual_memory_low` ? boolean low-memory indicators.

How to interpret

- Use these metrics to assess process memory pressure, fragmentation and whether the OS or process is signaling low memory.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsProcessMemoryReader.Sql;
using var rdr = cmd.ExecuteReader();
var m = new DmOsProcessMemoryReader(rdr, ownsReader:false);
if (m.Read())
{
    Console.WriteLine($"PhysKB:{m.PhysicalMemoryInUseKb} VACommittedKB:{m.VirtualAddressSpaceCommittedKb} PageFaults:{m.PageFaultCount} MemUtil%:{m.MemoryUtilizationPercentage}");
}
```

See also:

- [sys.dm_os_process_memory](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-process-memory)
