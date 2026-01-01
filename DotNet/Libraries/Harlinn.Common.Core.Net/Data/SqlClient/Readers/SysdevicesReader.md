# SysdevicesReader

Overview

`SysdevicesReader` wraps `sys.sysdevices` (legacy) and exposes information about physical devices defined in the server (used by older SQL Server features like tape devices and device-based files).

Reader SQL

```
SELECT
  s15.[Name],
  s15.[Size],
  s15.[Low],
  s15.[High],
  s15.[Status],
  s15.[Cntrltype],
  s15.[Phyname]
FROM
  [sys].[sysdevices] s15
```

Columns and interpretation

- `Name` (string): Logical device name.
- `Size` (int?): Device size in pages or another unit used by the server.
- `Low` (int?): Probably/guesswork: low-water mark or starting extent for allocations on the device.
- `High` (int?): Probably/guesswork: high-water mark or ending extent for allocations on the device.
- `Status` (smallint?): Status flags describing the device state.
- `Cntrltype` (smallint?): Control type code indicating device physical type (e.g., disk, tape).
- `Phyname` (string?): Physical device path or name.

How to interpret

- These fields are primarily useful when working with legacy device-oriented storage or investigating older systems.
- Prefer modern file and filegroup metadata (`sys.master_files`, `sys.database_files`, `sys.filegroups`) for current SQL Server versions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysdevicesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysdevicesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Device:{r.Name} Physical:{r.Phyname} Size:{r.Size} Status:{r.Status}");
```

See also:

- [sys.sysdevices](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysdevices)
