# DmOsBufferDescriptorsReader — reference

Overview

`DmOsBufferDescriptorsReader` wraps `sys.dm_os_buffer_descriptors` and returns buffer pool descriptors showing per-page metadata such as the database/file/page location, allocation and I/O status.

Reader SQL

```
SELECT
  dobd.[database_id],
  dobd.[file_id],
  dobd.[page_id],
  dobd.[page_level],
  dobd.[allocation_unit_id],
  dobd.[page_type],
  dobd.[row_count],
  dobd.[free_space_in_bytes],
  dobd.[is_modified],
  dobd.[numa_node],
  dobd.[read_microsec],
  dobd.[is_in_bpool_extension],
  dobd.[error_code],
  dobd.[op_history]
FROM
  [sys].[dm_os_buffer_descriptors] dobd
```

Columns and interpretation

- `database_id` ? database id owning the page.
- `file_id` ? file id within the database.
- `page_id` ? page id (page number within file).
- `page_level` ? page level (index leaf level etc.).
- `allocation_unit_id` ? allocation unit id for mapping to object/partition.
- `page_type` ? string describing the page type (Data, IAM, PFS, GAM, etc.).
- `row_count` ? number of rows stored on the page (if applicable).
- `free_space_in_bytes` ? free bytes remaining on the page.
- `is_modified` ? whether page has been modified in buffer (dirty).
- `numa_node` ? NUMA node where the buffer resides.
- `read_microsec` ? time in microseconds since last read (or read latency metric).
- `is_in_bpool_extension` ? whether this page resides in a buffer pool extension store.
- `error_code` ? any error associated with the page/buffer.
- `op_history` ? binary operation history metadata.

How to interpret

- Use to diagnose buffer pool residency, dirty pages, and distribution across NUMA nodes.
- `is_in_bpool_extension` shows whether the page was held in buffer pool extension (e.g., SSD-backed cache).
- `page_type` and `allocation_unit_id` help map buffers to objects and index structures.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsBufferDescriptorsReader.Sql;
using var rdr = cmd.ExecuteReader();
var b = new DmOsBufferDescriptorsReader(rdr, ownsReader:false);
while (b.Read())
{
    Console.WriteLine($"DB:{b.DatabaseId} File:{b.FileId} Page:{b.PageId} Type:{b.PageType} Dirty:{b.IsModified} FreeBytes:{b.FreeSpaceInBytes} NUMA:{b.NumaNode}");
}
```

See also:

- [sys.dm_os_buffer_descriptors](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-buffer-descriptors)
