# DmHadrNameIdMapReader — reference

Overview

`DmHadrNameIdMapReader` wraps `sys.dm_hadr_name_id_map` and provides mappings between textual names and GUID identifiers used in the HADR subsystem.

Reader SQL

```
SELECT
  dhnim.[Name],
  dhnim.[Id]
FROM
  [sys].[dm_hadr_name_id_map] dhnim
```

Columns and interpretation

- `Name` ? textual name for an HADR entity (AG, replica, etc.).
- `Id` ? GUID identifier corresponding to the name.

How to interpret

- Use this mapping to find GUIDs for entities when querying other HADR DMVs that require GUID identifiers.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrNameIdMapReader.Sql;
using var rdr = cmd.ExecuteReader();
var m = new DmHadrNameIdMapReader(rdr, ownsReader:false);
while (m.Read())
{
    Console.WriteLine($"Name:{m.Name} Id:{m.Id}");
}
```

See also:

- [sys.dm_hadr_name_id_map](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-name-id-map)
