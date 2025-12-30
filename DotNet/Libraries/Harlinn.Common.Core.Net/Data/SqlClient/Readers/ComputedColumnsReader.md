# ComputedColumnsReader — reference

Overview

`ComputedColumnsReader` wraps `sys.computed_columns` (joined to `sys.types`) and exposes metadata about computed columns defined on tables and views.

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
    ,c.[definition]
    ,c.[uses_database_collation]
    ,c.[is_persisted]
    ,t.[name] AS [type_name]
FROM [sys].[computed_columns] c
INNER JOIN sys.types t ON c.user_type_id = t.user_type_id
```

Selected columns (method mapping and brief meaning)

- `object_id` ? `GetObjectId()` (int): Parent object id.
- `name` ? `GetName()` (string): Computed column name.
- `column_id` ? `GetColumnId()` (int): Column id.
- `system_type_id` / `user_type_id` ? type ids.
- `max_length`, `precision`, `scale` ? sizing.
- `collation_name` ? collation for character results.
- `is_nullable`, `is_ansi_padded`, `is_rowguidcol`, `is_identity`, `is_computed` ? flags.
- `definition` ? `GetDefinition()` (string): T-SQL expression defining the computed column.
- `uses_database_collation` ? `GetUsesDatabaseCollation()` (bool): Collation usage flag.
- `is_persisted` ? `GetIsPersisted()` (bool): Whether computed column is persisted.
- encryption and graph metadata included as in `sys.columns`.

Helpers

- `GetComputedColumn()` returns a `Types.ComputedColumn` instance for the current row.
- `GetComputedColumns()` reads all rows and returns a list.
