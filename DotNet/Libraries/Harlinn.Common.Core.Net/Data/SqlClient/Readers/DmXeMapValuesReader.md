# DmXeMapValuesReader — reference

Overview

`DmXeMapValuesReader` wraps `sys.dm_xe_map_values` and returns mapping values for Eventing (Extended Events) map objects used to translate numeric keys to human readable strings.

Reader SQL

```
SELECT
  dxmv.[Name],
  dxmv.[object_package_guid],
  dxmv.[map_key],
  dxmv.[map_value]
FROM
  [sys].[dm_xe_map_values] dxmv
```

Columns and interpretation

- `Name` — name of the map.
- `object_package_guid` — GUID of the package containing the object.
- `map_key` — numeric key value used in the map.
- `map_value` — textual value corresponding to the key.

How to interpret

- Use this DMV to decode numeric map keys in event payloads into readable strings for diagnostics and reporting.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXeMapValuesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXeMapValuesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Map:{r.Name} Key:{r.MapKey} Value:{r.MapValue} Package:{r.ObjectPackageGuid}");
}
```

See also:

- [sys.dm_xe_map_values](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xe-map-values)
