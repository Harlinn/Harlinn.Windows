# SysfilesReader

Overview

`SysfilesReader` wraps `sys.sysfiles` (legacy) and exposes information about database files.

Reader SQL

```
SELECT
  s27.[Fileid],
  s27.[Groupid],
  s27.[Size],
  s27.[Maxsize],
  s27.[Growth],
  s27.[Status],
  s27.[Perf],
  s27.[Name],
  s27.[Filename]
FROM
  [sys].[sysfiles] s27
```

Columns and interpretation

- `Fileid` (smallint?): File id within the database.
- `Groupid` (smallint?): Filegroup id this file belongs to.
- `Size` (int): Current file size in pages.
- `Maxsize` (int): Maximum size in pages (-1 or special values may indicate unlimited).
- `Growth` (int): Growth increment in pages or percentage encoded as an int (legacy encoding).
- `Status` (int?): Status bitmask for the file (internal flags such as offline, read-only, auto-grow settings).
- `Perf` (int?): Performance flags or metrics (internal use).
- `Name` (string): Logical file name.
- `Filename` (string?): Physical file path.

How to interpret

- Use `Fileid` and `Groupid` to relate files to filegroups and allocations.
- `Size`, `Maxsize`, and `Growth` are expressed in pages; multiply by the database page size (typically 8 KB) to get bytes.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysfilesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysfilesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"File:{r.Name} Path:{r.Filename} SizePages:{r.Size} Max:{r.Maxsize} Growth:{r.Growth}");
```

See also:

- [sys.sysfiles](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysfiles)
