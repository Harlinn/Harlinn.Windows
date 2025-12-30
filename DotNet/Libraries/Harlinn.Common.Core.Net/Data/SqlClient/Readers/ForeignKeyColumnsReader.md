# ForeignKeyColumnsReader — reference

Overview

`ForeignKeyColumnsReader` wraps `sys.foreign_key_columns` and returns mapping between foreign key constraint columns and the parent/referenced column ids, including column names joined from `sys.columns`.

Reader SQL

```
SELECT fkc.[constraint_object_id]
    ,fkc.[constraint_column_id]
    ,fkc.[parent_object_id]
    ,fkc.[parent_column_id]
    ,fkc.[referenced_object_id]
    ,fkc.[referenced_column_id]
    ,  c.[name] AS [column_name]
    , cr.[name] AS [referenced_column_name]
FROM [sys].[foreign_key_columns] fkc
INNER JOIN sys.columns c ON fkc.parent_object_id = c.object_id AND fkc.parent_column_id = c.column_id
INNER JOIN sys.columns cr ON fkc.referenced_object_id = cr.object_id AND fkc.referenced_column_id = cr.column_id
```

Columns and interpretation

- `constraint_object_id` — object id of the foreign key constraint.
- `constraint_column_id` — ordinal position of the column within the constraint.
- `parent_object_id` — object id of the parent table (the table that contains the foreign key).
- `parent_column_id` — column id in the parent table participating in the foreign key.
- `referenced_object_id` — object id of the referenced (primary/unique key) table.
- `referenced_column_id` — column id in the referenced table that the foreign key points to.
- `column_name` — name of the parent table column (joined from `sys.columns`).
- `referenced_column_name` — name of the referenced table column.

How to interpret

- Use the constraint and column ids to reconstruct the complete foreign key mapping. `column_name` and `referenced_column_name` provide human-readable labels.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ForeignKeyColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ForeignKeyColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    var fk = r.GetForeignKeyColumn();
    Console.WriteLine($"Constraint:{fk.ConstraintObjectId} ColOrdinal:{fk.ConstraintColumnId} Table:{fk.ParentObjectId}.{fk.ColumnName} -> Ref:{fk.ReferencedObjectId}.{fk.ReferencedColumnName}");
}
```

See also:

- [sys.foreign_key_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-foreign-key-columns)
