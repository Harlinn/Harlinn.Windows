# KeyConstraintsReader — reference

Overview

`KeyConstraintsReader` wraps `sys.key_constraints` and returns metadata about key constraints (PRIMARY KEY, UNIQUE) including enforcement and the underlying index.

Reader SQL

```
SELECT kc.[name]
      ,kc.[object_id]
      ,kc.[principal_id]
      ,kc.[schema_id]
      ,kc.[parent_object_id]
      ,kc.[type]
      ,kc.[type_desc]
      ,kc.[create_date]
      ,kc.[modify_date]
      ,kc.[is_ms_shipped]
      ,kc.[is_published]
      ,kc.[is_schema_published]
      ,kc.[unique_index_id]
      ,kc.[is_system_named]
      ,kc.[is_enforced]
      ,so.[name] AS [TableName]
  FROM [sys].[key_constraints] kc
  LEFT JOIN [sys].[objects] so ON (so.[object_id] = kc.[parent_object_id])
```

Columns and interpretation

- `name`, `object_id` — name and id of the constraint object.
- `principal_id`, `schema_id`, `parent_object_id` — owner, schema and parent table id.
- `type` / `type_desc` — constraint type, e.g., PRIMARY_KEY_CONSTRAINT.
- `create_date` / `modify_date` — timestamps.
- `is_ms_shipped`, `is_published`, `is_schema_published` — metadata flags.
- `unique_index_id` — index id used to implement the constraint (nullable).
- `is_system_named` — whether the name was assigned by the system.
- `is_enforced` — whether the constraint is enforced.
- `TableName` — table name joined from `sys.objects`.

How to interpret

- `unique_index_id` links the constraint to an index; if `is_enforced` is false the constraint may be disabled.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = KeyConstraintsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new KeyConstraintsReader(rdr, ownsReader:false);
while (r.Read())
{
    var kc = r.GetKeyConstraint();
    Console.WriteLine($"Constraint:{kc.Name} Table:{kc.TableName} Enforced:{kc.IsEnforced} IndexId:{kc.UniqueIndexId}");
}
```

See also:

- [sys.key_constraints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-key-constraints)
