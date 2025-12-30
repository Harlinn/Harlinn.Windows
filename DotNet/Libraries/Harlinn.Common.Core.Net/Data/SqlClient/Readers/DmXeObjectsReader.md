# DmXeObjectsReader — reference

Overview

`DmXeObjectsReader` wraps `sys.dm_xe_objects` and returns metadata about Extended Events objects (events, actions, targets), including capabilities and type information.

Reader SQL

```
SELECT
  dxo.[Name],
  dxo.[object_type],
  dxo.[package_guid],
  dxo.[Description],
  dxo.[Capabilities],
  dxo.[capabilities_desc],
  dxo.[type_name],
  dxo.[type_package_guid],
  dxo.[type_size]
FROM
  [sys].[dm_xe_objects] dxo
```

Columns and interpretation

- `Name` — object name.
- `object_type` — object type (EVENT, ACTION, TARGET etc.).
- `package_guid` — GUID of the package providing the object.
- `Description` — textual description of the object.
- `Capabilities` / `capabilities_desc` — numeric capabilities and textual description.
- `type_name` / `type_package_guid` / `type_size` — type information for the object payload.

How to interpret

- Use to enumerate available event types, actions, and targets and to determine how to interpret event payloads and configure sessions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXeObjectsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXeObjectsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Object:{r.Name} Type:{r.ObjectType} Desc:{r.Description} Package:{r.PackageGuid}");
}
```

See also:

- [sys.dm_xe_objects](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xe-objects)
