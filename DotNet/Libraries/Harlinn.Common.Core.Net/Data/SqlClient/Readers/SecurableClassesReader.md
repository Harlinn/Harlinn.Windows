# SecurableClassesReader

Overview

`SecurableClassesReader` wraps `sys.securable_classes` and exposes mapping between securable class numeric codes and their textual descriptions.

Reader SQL

```
SELECT
  sc.[class_desc],
  sc.[Class]
FROM
  [sys].[securable_classes] sc
```

Columns and interpretation

- `class_desc` (string?): Textual description of the class (e.g., 'OBJECT_OR_COLUMN').
- `Class` (int?): Numeric code used in catalog views to indicate the securable class (used in `class` columns such as in `sys.extended_properties`).

How to interpret

- Use the numeric `Class` code to determine what object type a related `major_id`/`minor_id` pair in other views references.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SecurableClassesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SecurableClassesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Class:{r.Class} Desc:{r.ClassDesc}");
```

See also:

- [sys.securable_classes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-securable-classes)

