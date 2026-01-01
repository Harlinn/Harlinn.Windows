# SystemObjectsReader

Overview

`SystemObjectsReader` wraps `sys.system_objects` and exposes metadata about system objects (views, procedures, functions, etc.).

Reader SQL

```
SELECT
  so.[Name],
  so.[object_id],
  so.[principal_id],
  so.[schema_id],
  so.[parent_object_id],
  so.[Type],
  so.[type_desc],
  so.[create_date],
  so.[modify_date],
  so.[is_ms_shipped],
  so.[is_published],
  so.[is_schema_published]
FROM
  [sys].[system_objects] so
```

Columns and interpretation

- `Name` (string): Object name.
- `object_id` (int): Object id.
- `principal_id` (int?): Principal id (owner) for the object.
- `schema_id` (int): Schema id of the object.
- `parent_object_id` (int?): Parent object id, if applicable.
- `Type` (string): Object type code.
- `type_desc` (string?): Object type description.
- `create_date` (datetime): Creation date.
- `modify_date` (datetime): Last modification date.
- `is_ms_shipped` (bit?): Whether the object is shipped by Microsoft.
- `is_published` (bit?): Publication flag.
- `is_schema_published` (bit?): Schema publication flag.

How to interpret

- Use `object_id` and `schema_id` to join with `sys.schemas` and `sys.objects` for additional context.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemObjectsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemObjectsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.Name} Id:{r.ObjectId} Type:{r.Type} Created:{r.CreateDate}");
```

See also:

- [sys.system_objects](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-objects)
