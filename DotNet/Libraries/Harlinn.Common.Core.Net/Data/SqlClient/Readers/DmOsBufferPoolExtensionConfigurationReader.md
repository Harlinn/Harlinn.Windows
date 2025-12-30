# DmOsBufferPoolExtensionConfigurationReader — reference

Overview

`DmOsBufferPoolExtensionConfigurationReader` wraps `sys.dm_os_buffer_pool_extension_configuration` and returns configuration and status information for the buffer pool extension (BPE), a feature that allows SQL Server to extend the buffer pool to SSD storage.

Reader SQL

```
SELECT
  dobpec.[Path],
  dobpec.[file_id],
  dobpec.[State],
  dobpec.[state_description],
  dobpec.[current_size_in_kb]
FROM
  [sys].[dm_os_buffer_pool_extension_configuration] dobpec
```

Columns and interpretation

- `Path` ? `Path` (string?)
  - Path to the buffer pool extension file or location.

- `file_id` ? `FileId` (int?)
  - File id associated with the buffer pool extension file.

- `State` / `state_description` ? `State` (int?), `StateDescription` (string)
  - Numeric and textual state of the buffer pool extension (enabled, disabled, initializing, failed, etc.).

- `current_size_in_kb` ? `CurrentSizeInKb` (long?)
  - Current configured size of the buffer pool extension in kilobytes.

How to interpret

- Use `State` and `StateDescription` to determine whether the buffer pool extension is active and healthy.
- `CurrentSizeInKb` indicates how much extension capacity is configured and used.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsBufferPoolExtensionConfigurationReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsBufferPoolExtensionConfigurationReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Path:{r.Path} FileId:{r.FileId} State:{r.StateDescription} SizeKB:{r.CurrentSizeInKb}");
}
```

See also:

- [sys.dm_os_buffer_pool_extension_configuration](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-buffer-pool-extension-configuration)
