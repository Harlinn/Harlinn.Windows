# AllColumnsReader — reference

Overview

`AllColumnsReader` wraps a query on [`sys.all_columns`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-all-columns-transact-sql) (joined to [`sys.types`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-types-transact-sql)) and exposes column metadata for every column in the database (tables, views, etc.). The reader provides typed properties for each selected column and convenience methods to convert rows to domain objects.

Reader SQL

```
SELECT
  ac.[object_id],
  ac.[Name],
  ac.[column_id],
  ac.[system_type_id],
  ac.[user_type_id],
  ac.[max_length],
  ac.[Precision],
  ac.[Scale],
  ac.[collation_name],
  ac.[is_nullable],
  ac.[is_ansi_padded],
  ac.[is_rowguidcol],
  ac.[is_identity],
  ac.[is_computed],
  ac.[is_filestream],
  ac.[is_replicated],
  ac.[is_non_sql_subscribed],
  ac.[is_merge_published],
  ac.[is_dts_replicated],
  ac.[is_xml_document],
  ac.[xml_collection_id],
  ac.[default_object_id],
  ac.[rule_object_id],
  ac.[is_sparse],
  ac.[is_column_set],
  ac.[generated_always_type],
  ac.[generated_always_type_desc],
  ac.[encryption_type],
  ac.[encryption_type_desc],
  ac.[encryption_algorithm_name],
  ac.[column_encryption_key_id],
  ac.[column_encryption_key_database_name],
  ac.[is_hidden],
  ac.[is_masked],
  ac.[graph_type],
  ac.[graph_type_desc],
  t.[name] AS [type_name]
FROM
  [sys].[all_columns] ac
INNER JOIN sys.types t ON ac.user_type_id = t.user_type_id
```

Notes on source views

- Primary view: `sys.all_columns` — describes all column metadata for objects the current user can see.
- Joined view: `sys.types` — resolves `user_type_id` to human-readable `type_name`.

Selected columns (property mapping and brief meaning)

- `object_id` ? property: `ObjectId` (int)
  - ID of the parent object (table or view).

- `Name` ? property: `Name` (string?)
  - Column name.

- `column_id` ? property: `ColumnId` (int)
  - Column ordinal within the object.

- `system_type_id` ? property: `SystemTypeId` (byte)
  - Internal SQL Server system type id.

- `user_type_id` ? property: `UserTypeId` (int)
  - User type id referencing `sys.types`.

- `max_length` ? property: `MaxLength` (short)
  - Maximum storage size (bytes).

- `Precision` ? property: `Precision` (byte)
  - Numeric precision for decimal / numeric types.

- `Scale` ? property: `Scale` (byte)
  - Numeric scale for decimal / numeric types.

- `collation_name` ? property: `CollationName` (string?)
  - Collation name for character columns (nullable).

- `is_nullable` ? property: `IsNullable` (bool?)
  - Whether the column allows NULL values.

- `is_ansi_padded` ? property: `IsAnsiPadded` (bool)
  - ANSI_PADDING behavior for the column.

- `is_rowguidcol` ? property: `IsRowguidcol` (bool)
  - Indicates ROWGUIDCOL property.

- `is_identity` ? property: `IsIdentity` (bool)
  - Indicates identity column.

- `is_computed` ? property: `IsComputed` (bool)
  - Indicates computed column.

- `is_filestream` ? property: `IsFilestream` (bool)
  - Uses FILESTREAM storage.

- `is_replicated` ? property: `IsReplicated` (bool?)
  - Replication metadata flag.

- `is_non_sql_subscribed` ? property: `IsNonSqlSubscribed` (bool?)
  - Replication subscription metadata.

- `is_merge_published` ? property: `IsMergePublished` (bool?)
  - Replication metadata for merge publication.

- `is_dts_replicated` ? property: `IsDtsReplicated` (bool?)
  - DTS replication flag (legacy).

- `is_xml_document` ? property: `IsXmlDocument` (bool)
  - Indicates XML DOCUMENT_TYPE columns.

- `xml_collection_id` ? property: `XmlCollectionId` (int)
  - XML collection id for typed XML columns.

- `default_object_id` ? property: `DefaultObjectId` (int)
  - Object id of the default constraint, if any.

- `rule_object_id` ? property: `RuleObjectId` (int)
  - Legacy rule object id.

- `is_sparse` ? property: `IsSparse` (bool?)
  - Indicates SPARSE column.

- `is_column_set` ? property: `IsColumnSet` (bool?)
  - Indicates column set for sparse columns.

- `generated_always_type` ? property: `GeneratedAlwaysType` (byte?)
  - Generated-always metadata (if present).

- `generated_always_type_desc` ? property: `GeneratedAlwaysTypeDesc` (string?)
  - Description of generated-always behavior.

- `encryption_type` ? property: `EncryptionType` (int?)
  - Always Encrypted column encryption type id.

- `encryption_type_desc` ? property: `EncryptionTypeDesc` (string?)
  - Description of encryption type.

- `encryption_algorithm_name` ? property: `EncryptionAlgorithmName` (string?)
  - Encryption algorithm name when column is encrypted.

- `column_encryption_key_id` ? property: `ColumnEncryptionKeyId` (int?)
  - Column encryption key id used for Always Encrypted.

- `column_encryption_key_database_name` ? property: `ColumnEncryptionKeyDatabaseName` (string?)
  - Database name where encryption key is stored.

- `is_hidden` ? property: `IsHidden` (bool?)
  - Hidden column flag (internal/hidden columns).

- `is_masked` ? property: `IsMasked` (bool)
  - Dynamic data masking flag.

- `graph_type` ? property: `GraphType` (int?)
  - Graph table metadata (node/edge type code).

- `graph_type_desc` ? property: `GraphTypeDesc` (string?)
  - Description of graph type.

- `type_name` ? property: `TypeName` (string)
  - Resolved type name from `sys.types` (human-readable SQL type name).

Usage

Open the reader with a `SqlDataReader` and iterate; properties map to the columns above. Use `ToDataObject()` / `ToList()` to get typed domain objects defined in `Types` namespace.

