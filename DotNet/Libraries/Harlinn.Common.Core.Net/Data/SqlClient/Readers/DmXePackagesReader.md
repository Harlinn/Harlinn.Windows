# DmXePackagesReader — reference

Overview

`DmXePackagesReader` wraps `sys.dm_xe_packages` and returns information about Extended Events packages registered in the server.

Reader SQL

```
SELECT
  dxp.[Name],
  dxp.[Guid],
  dxp.[Description],
  dxp.[Capabilities],
  dxp.[capabilities_desc],
  dxp.[module_guid],
  dxp.[module_address]
FROM
  [sys].[dm_xe_packages] dxp
```

Columns and interpretation

- `Name` — package name.
- `Guid` — package GUID.
- `Description` — textual description for the package.
- `Capabilities` / `capabilities_desc` — package capabilities and description.
- `module_guid` — GUID for the module implementing the package.
- `module_address` — internal binary address for the module.

How to interpret

- Use to identify available XE packages and their capabilities when configuring event sessions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXePackagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXePackagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Package:{r.Name} GUID:{r.Guid} Module:{r.ModuleGuid} Desc:{r.Description}");
}
```

See also:

- [sys.dm_xe_packages](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xe-packages)
