# SysaltfilesReader

Overview

`SysaltfilesReader` wraps `sys.sysaltfiles` and exposes legacy file and device information (primarily for backward compatibility with older SQL Server versions).

Reader SQL

```
SELECT
  s26.[Fileid],
  s26.[Groupid],
  s26.[Size],
  s26.[Maxsize],
  s26.[Growth],
  s26.[Status],
  s26.[Perf],
  s26.[Dbid],
  s26.[Name],
  s26.[Filename]
FROM
  [sys].[sysaltfiles] s26
```

Columns and interpretation

- `Fileid` (short?): File id within the system.
- `Groupid` (short?): Filegroup id.
- `Size`, `Maxsize`, `Growth` (int): Size metrics (pages or units depending on legacy semantics).
- `Status` (int?): Status flags for the file.
- `Perf` (int?): Performance flags.
- `Dbid` (short?): Database id.
- `Name` (string): Logical file name.
- `Filename` (string?): Physical filename path.

How to interpret

- This view is legacy; modern catalogs use `sys.database_files`. Use `Filename` and `Name` to map file-level storage.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysaltfilesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysaltfilesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"File:{r.Name} Path:{r.Filename} Size:{r.Size}");
```

See also:

- [sys.sysaltfiles](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysaltfiles) (legacy)
