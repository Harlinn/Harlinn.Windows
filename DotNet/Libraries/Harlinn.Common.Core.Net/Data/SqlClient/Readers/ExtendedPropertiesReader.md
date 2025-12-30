# ExtendedPropertiesReader — reference

Overview

`ExtendedPropertiesReader` wraps `sys.extended_properties` and returns user-defined extended properties attached to various schema-scoped objects.

Reader SQL

```
SELECT
  ep.[Class],
  ep.[class_desc],
  ep.[major_id],
  ep.[minor_id],
  ep.[Name],
  ep.[Value]
FROM
  [sys].[extended_properties] ep
```

Columns and interpretation

- `Class` — numeric class code indicating the type of object the property is attached to (e.g., object, column, schema).
- `class_desc` — textual description for the class.
- `major_id` — primary identifier for the object owning the property (for example object_id).
- `minor_id` — secondary identifier (for example column_id) when applicable.
- `Name` — name of the extended property.
- `Value` — value of the extended property; type is SQL `sql_variant` so it may be string, int, etc.

How to interpret

- Extended properties are commonly used to store descriptions and metadata (e.g., MS_Description). `major_id`/`minor_id` map the property to the specific object and sub-object.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExtendedPropertiesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExtendedPropertiesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Class:{r.ClassDesc} Major:{r.MajorId} Minor:{r.MinorId} Name:{r.Name} Value:{r.Value}");
}
```

See also:

- [sys.extended_properties](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-extended-properties)
