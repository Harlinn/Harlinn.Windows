# DmOsEnumerateFixedDrivesReader — reference

Overview

`DmOsEnumerateFixedDrivesReader` wraps `sys.dm_os_enumerate_fixed_drives` and lists fixed drives on the OS with free space metrics and drive types.

Reader SQL

```
SELECT
  doefd.[fixed_drive_path],
  doefd.[drive_type],
  doefd.[drive_type_desc],
  doefd.[free_space_in_bytes]
FROM
  [sys].[dm_os_enumerate_fixed_drives] doefd
```

Columns and interpretation

- `fixed_drive_path` ? path/drive letter (string?)
- `drive_type` ? numeric drive type code (int)
- `drive_type_desc` ? textual description of drive type (string?)
- `free_space_in_bytes` ? available free space on the drive in bytes (long)

How to interpret

- Useful to identify local fixed drives and ensure there is sufficient free space for database files, backups, or buffer pool extension files.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsEnumerateFixedDrivesReader.Sql;
using var rdr = cmd.ExecuteReader();
var d = new DmOsEnumerateFixedDrivesReader(rdr, ownsReader:false);
while (d.Read())
{
    Console.WriteLine($"Drive:{d.FixedDrivePath} Type:{d.DriveTypeDesc} FreeBytes:{d.FreeSpaceInBytes}");
}
```

See also:

- [sys.dm_os_enumerate_fixed_drives](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-enumerate-fixed-drives)
