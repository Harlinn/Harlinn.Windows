# FiletableSystemDefinedObjectsReader — reference

Overview

`FiletableSystemDefinedObjectsReader` wraps `sys.filetable_system_defined_objects` and returns mappings between filetable system-defined objects and their parent objects.

Reader SQL

```
SELECT
  fsdo.[object_id],
  fsdo.[parent_object_id]
FROM
  [sys].[filetable_system_defined_objects] fsdo
```

Columns and interpretation

- `object_id` — object id of the system-defined object associated with the filetable (for example, internal stream or path tables used by the filetable feature).
- `parent_object_id` — parent object id (the filetable object id) to which the system-defined object belongs.

How to interpret

- Use when enumerating filetable-related system artifacts; `parent_object_id` helps correlate system objects to the user-facing filetable.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FiletableSystemDefinedObjectsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FiletableSystemDefinedObjectsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"SystemObj:{r.ObjectId} Parent:{r.ParentObjectId}");
}
```

See also:

- [sys.filetable_system_defined_objects](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-filetable-system-defined-objects)
