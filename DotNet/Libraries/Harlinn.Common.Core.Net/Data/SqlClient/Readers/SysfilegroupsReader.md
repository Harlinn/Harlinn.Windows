# SysfilegroupsReader

Overview

`SysfilegroupsReader` wraps `sys.sysfilegroups` (legacy) and exposes information about filegroups defined in the database.

Reader SQL

```
SELECT
  s28.[Groupid],
  s28.[Allocpolicy],
  s28.[Status],
  s28.[Groupname]
FROM
  [sys].[sysfilegroups] s28
```

Columns and interpretation

- `Groupid` (smallint?): Identifier of the filegroup.
- `Allocpolicy` (smallint?): Allocation policy code for the filegroup (internal representation).
- `Status` (int?): Status bitmask for the filegroup (internal flags such as read-only, offline etc.).
- `Groupname` (string): Name of the filegroup.

How to interpret

- `Groupid` uniquely identifies the filegroup within the database and can be used to join to file-level metadata.
- `Allocpolicy` explains how allocations are distributed across files in the group; use modern `sys.data_spaces` and `sys.filegroups` documentation for meaning.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysfilegroupsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysfilegroupsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Group:{r.Groupname} Id:{r.Groupid} Policy:{r.Allocpolicy} Status:{r.Status}");
```

See also:

- [sys.sysfilegroups](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysfilegroups)
