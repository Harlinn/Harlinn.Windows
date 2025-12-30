# ForeignKeyReader — reference

Overview

`ForeignKeyReader` wraps `sys.foreign_keys` and returns metadata about foreign key constraints, including referential actions, related tables and schema names.

Reader SQL

```
SELECT fk.[name]
    ,fk.[object_id]
    ,fk.[principal_id]
    ,fk.[schema_id]
    ,fk.[parent_object_id]
    ,fk.[type]
    ,fk.[type_desc]
    ,fk.[create_date]
    ,fk.[modify_date]
    ,fk.[is_ms_shipped]
    ,fk.[is_published]
    ,fk.[is_schema_published]
    ,fk.[referenced_object_id]
    ,fk.[key_index_id]
    ,fk.[is_disabled]
    ,fk.[is_not_for_replication]
    ,fk.[is_not_trusted]
    ,fk.[delete_referential_action]
    ,fk.[delete_referential_action_desc]
    ,fk.[update_referential_action]
    ,fk.[update_referential_action_desc]
    ,fk.[is_system_named]
    , t.[name] AS [table_name]
    , s.[name] AS [schema_name]
    , rt.[name] AS [referenced_table_name]
    , rs.[name] AS [referenced_schema_name]
FROM [sys].[foreign_keys] fk
INNER JOIN sys.tables t ON fk.[parent_object_id] = t.object_id
INNER JOIN sys.schemas s ON t.schema_id = s.schema_id
INNER JOIN sys.tables rt ON fk.referenced_object_id = rt.object_id
INNER JOIN sys.schemas rs ON rt.schema_id = rs.schema_id
```

Columns and interpretation

- `name` — foreign key constraint name.
- `object_id` — object id of the foreign key constraint.
- `principal_id` — principal id owning the constraint (nullable).
- `schema_id` — schema id of the parent table.
- `parent_object_id` — object id of the parent table that has the foreign key.
- `type` / `type_desc` — type code and description.
- `create_date` / `modify_date` — timestamps for creation and modification.
- `is_ms_shipped`, `is_published`, `is_schema_published` — metadata flags.
- `referenced_object_id` — object id of the referenced table.
- `key_index_id` — index id used for the key.
- `is_disabled` — whether the foreign key is disabled.
- `is_not_for_replication` — whether foreign key enforcement is disabled for replication.
- `is_not_trusted` — whether the constraint is not trusted by the optimizer.
- `delete_referential_action` / `delete_referential_action_desc` — referential action for delete (NO_ACTION, CASCADE, SET_NULL, etc.).
- `update_referential_action` / `update_referential_action_desc` — referential action for update.
- `is_system_named` — whether system assigned the name.
- `table_name` / `schema_name` — parent table and schema names.
- `referenced_table_name` / `referenced_schema_name` — referenced table and schema names.

How to interpret

- `delete_referential_action_desc` and `update_referential_action_desc` indicate the behavior when referenced rows are deleted/updated.
- `is_not_trusted` means the constraint is disabled for query optimization assumptions; it may require validation.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ForeignKeyReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ForeignKeyReader(rdr, ownsReader:false);
while (r.Read())
{
    var fk = r.GetForeignKey();
    Console.WriteLine($"FK:{fk.Name} Table:{fk.SchemaName}.{fk.TableName} -> {fk.ReferencedSchemaName}.{fk.ReferencedTableName} DeleteAction:{fk.DeleteReferentialActionDesc}");
}
```

See also:

- [sys.foreign_keys](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-foreign-keys)
