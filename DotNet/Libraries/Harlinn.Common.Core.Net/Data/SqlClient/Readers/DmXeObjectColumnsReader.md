# DmXeObjectColumnsReader — reference

Overview

`DmXeObjectColumnsReader` wraps `sys.dm_xe_object_columns` and exposes column definitions for Extended Events objects, including types, capabilities and descriptions.

Reader SQL

```
SELECT
  dxoc.[Name],
  dxoc.[column_id],
  dxoc.[object_name],
  dxoc.[object_package_guid],
  dxoc.[type_name],
  dxoc.[type_package_guid],
  dxoc.[column_type],
  dxoc.[column_value],
  dxoc.[Capabilities],
  dxoc.[capabilities_desc],
  dxoc.[Description]
FROM
  [sys].[dm_xe_object_columns] dxoc
```

Columns and interpretation

- `Name` — column name.
- `column_id` — numeric id of the column.
- `object_name` — name of the object owning the column.
- `object_package_guid` — GUID of the package containing the object.
- `type_name` — name of the type used by the column.
- `type_package_guid` — GUID for the type's package.
- `column_type` — textual classification of the column type (e.g., xml, int, string).
- `column_value` — default or sample value (nullable string).
- `Capabilities` — numeric capabilities bitmask.
- `capabilities_desc` — textual description of capabilities.
- `Description` — textual description of the column.

How to interpret

- Useful for tooling or display logic to determine how to parse and present event columns based on type and capabilities.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXeObjectColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXeObjectColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Object:{r.ObjectName} Column:{r.Name} Type:{r.TypeName} Desc:{r.Description}");
}
```

See also:

- [sys.dm_xe_object_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xe-object-columns)
