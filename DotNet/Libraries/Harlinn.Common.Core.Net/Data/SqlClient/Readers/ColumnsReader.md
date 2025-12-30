# ColumnsReader — reference

Overview

`ColumnsReader` wraps `sys.columns` (joined to `sys.types`) and exposes metadata for columns defined on objects visible to the current principal.

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
    ,t.[name] AS [type_name]
FROM [sys].[columns] c
INNER JOIN sys.types t ON c.user_type_id = t.user_type_id
```

Selected columns (method mapping and brief meaning)

- `object_id` ? `GetObjectId()` (int): Parent object id.
- `name` ? `GetName()` (string): Column name.
- `column_id` ? `GetColumnId()` (int): Column ordinal.
- `system_type_id` ? `GetSystemTypeId()` (byte): Internal type id.
- `user_type_id` ? `GetUserTypeId()` (int): User type id referencing `sys.types`.
- `max_length` ? `GetMaxLength()` (short): Max storage length in bytes.
- `precision` ? `GetPrecision()` (byte): Numeric precision.
- `scale` ? `GetScale()` (byte): Numeric scale.
- `collation_name` ? `GetCollationName()` (string?): Collation for char columns.
- `is_nullable` ? `GetIsNullable()` (bool): NULL allowance.
- `is_ansi_padded` ? `GetIsAnsiPadded()` (bool): ANSI padding flag.
- `is_rowguidcol` ? `GetIsRowguidcol()` (bool): ROWGUIDCOL flag.
- `is_identity` ? `GetIsIdentity()` (bool): Identity flag.
- `is_computed` ? `GetIsComputed()` (bool): Computed column flag.
- `is_filestream` ? `GetIsFilestream()` (bool): FILESTREAM usage.
- `is_replicated` ? `GetIsReplicated()` (bool): Replication flag.
- `is_non_sql_subscribed` ? `GetIsNonSqlSubscribed()` (bool): Replication subscription flag.
- `is_merge_published` ? `GetIsMergePublished()` (bool): Merge publication flag.
- `is_dts_replicated` ? `GetIsDtsReplicated()` (bool): DTS replication flag.
- `is_xml_document` ? `GetIsXmlDocument()` (bool): XML document type flag.
- `xml_collection_id` ? `GetXmlCollectionId()` (int): Xml collection id.
- `default_object_id` ? `GetDefaultObjectId()` (int): Default constraint object id.
- `rule_object_id` ? `GetRuleObjectId()` (int): Legacy rule object id.
- `is_sparse` ? `GetIsSparse()` (bool): SPARSE flag.
- `is_column_set` ? `GetIsColumnSet()` (bool): Column set flag.
- `generated_always_type` ? `GetGeneratedAlwaysType()` (byte): Generated-always type code.
- `generated_always_type_desc` ? `GetGeneratedAlwaysTypeDesc()` (string): Description of generated-always behavior.
- `encryption_*` / `column_encryption_key_*` ? encryption metadata methods.
- `is_hidden` ? `GetIsHidden()` (bool): Hidden column flag.
- `is_masked` ? `GetIsMasked()` (bool): Dynamic data masking flag.
- `graph_type` / `graph_type_desc` ? graph metadata.
- `type_name` ? `GetTypeName()` (string): Resolved SQL type name from `sys.types`.

Helpers

- `GetColumn()` converts the current row to a `Types.Column` object.
- `GetColumns()` iterates and returns a list of `Types.Column` objects.
