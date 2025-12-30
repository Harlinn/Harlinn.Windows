# MaskedColumnsReader — reference

Overview

`MaskedColumnsReader` wraps `sys.masked_columns` and returns column metadata for columns that use dynamic data masking, including masking functions and related type information.

Reader SQL

```
SELECT mc.[object_id]
      ,mc.[name]
      ,mc.[column_id]
      ,mc.[system_type_id]
      ,mc.[user_type_id]
      ,mc.[max_length]
      ,mc.[precision]
      ,mc.[scale]
      ,mc.[collation_name]
      ,mc.[is_nullable]
      ,mc.[is_ansi_padded]
      ,mc.[is_rowguidcol]
      ,mc.[is_identity]
      ,mc.[is_filestream]
      ,mc.[is_replicated]
      ,mc.[is_non_sql_subscribed]
      ,mc.[is_merge_published]
      ,mc.[is_dts_replicated]
      ,mc.[is_xml_document]
      ,mc.[xml_collection_id]
      ,mc.[default_object_id]
      ,mc.[rule_object_id]
      ,mc.[definition]
      ,mc.[uses_database_collation]
      ,mc.[is_persisted]
      ,mc.[is_computed]
      ,mc.[is_sparse]
      ,mc.[is_column_set]
      ,mc.[generated_always_type]
      ,mc.[generated_always_type_desc]
      ,mc.[encryption_type]
      ,mc.[encryption_type_desc]
      ,mc.[encryption_algorithm_name]
      ,mc.[column_encryption_key_id]
      ,mc.[column_encryption_key_database_name]
      ,mc.[is_hidden]
      ,mc.[is_masked]
      ,mc.[masking_function]
      ,mc.[graph_type]
      ,mc.[graph_type_desc]
FROM [sys].[masked_columns] mc
```

Columns and interpretation

- Column identity and type metadata: `object_id`, `name`, `column_id`, `system_type_id`, `user_type_id`, `max_length`, `precision`, `scale`, `collation_name`.
- Flags: `is_nullable`, `is_ansi_padded`, `is_rowguidcol`, `is_identity`, `is_filestream`, replication flags, `is_xml_document`.
- Schema/definition metadata: `default_object_id`, `rule_object_id`, `definition` (computed expression), `uses_database_collation`, `is_persisted`, `is_computed`.
- Masking: `is_masked` — whether dynamic data masking is applied; `masking_function` — masking function name and parameters.
- Always Encrypted metadata: same fields as other readers (`encryption_type`, `encryption_algorithm_name`, `column_encryption_key_id`, ...).
- Graph metadata: `graph_type`, `graph_type_desc`.

How to interpret

- `masking_function` contains the defined masking function (e.g., `default()`, `email()`) and indicates how data is masked at query time for non-privileged users.
- Encryption and masking can coexist; use flags to determine effective data protection settings.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = MaskedColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new MaskedColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    var m = r.GetMaskedColumn();
    Console.WriteLine($"{m.Name} Obj:{m.ObjectId} Masked:{m.IsMasked} MaskFn:{m.MaskingFunction}");
}
```

See also:

- [sys.masked_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-masked-columns)
