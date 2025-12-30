# DmOsVirtualAddressDumpReader — reference

Overview

`DmOsVirtualAddressDumpReader` wraps `sys.dm_os_virtual_address_dump` and exposes virtual memory region information for the SQL Server process.

Reader SQL

```
SELECT
  dovad.[region_base_address],
  dovad.[region_allocation_base_address],
  dovad.[region_allocation_protection],
  dovad.[region_size_in_bytes],
  dovad.[region_state],
  dovad.[region_current_protection],
  dovad.[region_type]
FROM
  [sys].[dm_os_virtual_address_dump] dovad
```

Columns and interpretation

- `region_base_address` — base address of the memory region.
- `region_allocation_base_address` — base address of the allocation containing the region.
- `region_allocation_protection` — protection flags at allocation time (e.g., PAGE_READWRITE) as binary or encoded value.
- `region_size_in_bytes` — size of the region in bytes.
- `region_state` — state flags for the region (committed, reserved, free) as binary or encoded value.
- `region_current_protection` — current protection flags for the region.
- `region_type` — type of the memory region (private, mapped, image) as binary or encoded value.

How to interpret

- Use to inspect address space layout and memory protection of SQL Server process segments.
- `region_allocation_protection` and `region_current_protection` indicate whether memory is readable, writable or executable.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsVirtualAddressDumpReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsVirtualAddressDumpReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Base:{BitConverter.ToString(r.RegionBaseAddress)} AllocBase:{BitConverter.ToString(r.RegionAllocationBaseAddress)} Size:{r.RegionSizeInBytes}");
}
```

See also:

- [sys.dm_os_virtual_address_dump](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-virtual-address-dump)
