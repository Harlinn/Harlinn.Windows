# IdentityColumnsReader — reference

Overview

`IdentityColumnsReader` wraps `sys.identity_columns` and returns metadata for identity columns (auto-incrementing columns), including seed, increment and last value.

Reader SQL

```
SELECT c.[object_id]
    ,c.[name]
    ,c.[column_id]
    ,c.[system_type_id]
    ,c.[user_type_id]
    ,c.[max_length]
    ,c.[precision]
    ,c.[scale]
    ,c.[collation_name]
    ,c.[is_nullable]
    ,c.[is_ansi_padded]
    ,c.[is_rowguidcol]
    ,c.[is_identity]
    ,c.[is_computed]
    ,c.[is_filestream]
    ,c.[is_replicated]
    ,c.[is_non_sql_subscribed]
    ,c.[is_merge_published]
    ,c.[is_dts_replicated]
    ,c.[is_xml_document]
    ,c.[xml_collection_id]
    ,c.[default_object_id]
    ,c.[rule_object_id]
    ,c.[is_sparse]
    ,c.[is_column_set]
    ,c.[generated_always_type]
    ,c.[generated_always_type_desc]
    ,c.[encryption_type]
    ,c.[encryption_type_desc]
    ,c.[encryption_algorithm_name]
    ,c.[column_encryption_key_id]
    ,c.[column_encryption_key_database_name]
    ,c.[is_hidden]
    ,c.[is_masked]
    ,c.[graph_type]
    ,c.[graph_type_desc]
    ,c.[seed_value]
    ,c.[increment_value]
    ,c.[last_value]
    ,c.[is_not_for_replication]
    ,t.[name] AS [type_name]
FROM [sys].[identity_columns] c
INNER JOIN sys.types t ON c.user_type_id = t.user_type_id
```

Columns and interpretation

- `object_id`, `name`, `column_id` — identifies the column.
- Type metadata: `system_type_id`, `user_type_id`, `max_length`, `precision`, `scale`, `collation_name`.
- Flags: `is_nullable`, `is_ansi_padded`, `is_rowguidcol`, `is_identity`, `is_computed`, `is_filestream`, replication flags, `is_xml_document`, `is_sparse`, `is_column_set`.
- `generated_always_type` / `generated_always_type_desc` — if the column is generated always (persisted/generated) and description.
- Always Encrypted columns metadata: `encryption_type`, `encryption_type_desc`, `encryption_algorithm_name`, `column_encryption_key_id`, `column_encryption_key_database_name`.
- Identity-specific: `seed_value` — starting value for identity; `increment_value` — step value; `last_value` — last generated value (nullable if none); `is_not_for_replication` — whether identity is not used for replication.
- `type_name` — base type name.

How to interpret

- Use `seed_value` and `increment_value` to understand identity generation; `last_value` shows current sequence progress. Flags indicate persistence, encryption and replication behavior.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = IdentityColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new IdentityColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    var c = r.GetIdentityColumn();
    Console.WriteLine($"{c.Name} (obj:{c.ObjectId}) seed:{c.SeedValue} inc:{c.IncrementValue} last:{c.LastValue}");
}
```

See also:

- [sys.identity_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-identity-columns)
