# SqlDependenciesReader

Overview

`SqlDependenciesReader` wraps `sys.sql_dependencies` and exposes dependency relationships discovered from SQL modules.

Reader SQL

```
SELECT
  sd.[Class],
  sd.[class_desc],
  sd.[object_id],
  sd.[column_id],
  sd.[referenced_major_id],
  sd.[referenced_minor_id],
  sd.[is_selected],
  sd.[is_updated],
  sd.[is_select_all]
FROM
  [sys].[sql_dependencies] sd
```

Columns and interpretation

- `Class` (byte): Securable class code for the referencing object.
- `class_desc` (string?): Description of the class.
- `object_id` (int): Object id of the referencing object (e.g., stored procedure).
- `column_id` (int): Column id within the object if applicable.
- `referenced_major_id`, `referenced_minor_id` (int): Object and column ids of the referenced object/column.
- `is_selected` (bool): True if the dependency includes a SELECT on the referenced object/column.
- `is_updated` (bool): True if the dependency includes DML that updates the referenced object/column.
- `is_select_all` (bool): True if a SELECT * dependency was detected.

How to interpret

- Use these rows to determine which database objects are referenced by SQL modules. `is_select_all` signals possible schema-binding concerns when columns change.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SqlDependenciesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SqlDependenciesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Object:{r.ObjectId} References:{r.ReferencedMajorId}.{r.ReferencedMinorId} Selected:{r.IsSelected} Updated:{r.IsUpdated}");
```

See also:

- [sys.sql_dependencies](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sql-dependencies)
