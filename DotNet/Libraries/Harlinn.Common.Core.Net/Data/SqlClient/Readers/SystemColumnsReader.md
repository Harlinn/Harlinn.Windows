# SystemColumnsReader

Overview

`SystemColumnsReader` wraps `sys.system_columns` and provides detailed metadata about columns for system objects. It also joins to `sys.types` to provide the type name.

Reader SQL

```
SELECT ssc.[object_id]
    ,ssc.[name]
    ,ssc.[column_id]
    ,ssc.[system_type_id]
    ,ssc.[user_type_id]
    ,ssc.[max_length]
    ,ssc.[precision]
    ,ssc.[scale]
    ,ssc.[collation_name]
    ,ssc.[is_nullable]
    ,ssc.[is_ansi_padded]
    ,ssc.[is_rowguidcol]
    ,ssc.[is_identity]
    ,ssc.[is_computed]
    ,ssc.[is_filestream]
    ,ssc.[is_replicated]
    ,ssc.[is_non_sql_subscribed]
    ,ssc.[is_merge_published]
    ,ssc.[is_dts_replicated]
    ,ssc.[is_xml_document]
    ,ssc.[xml_collection_id]
    ,ssc.[default_object_id]
    ,ssc.[rule_object_id]
    ,ssc.[is_sparse]
    ,ssc.[is_column_set]
    ,ssc.[generated_always_type]
    ,ssc.[generated_always_type_desc]
    ,ssc.[encryption_type]
    ,ssc.[encryption_type_desc]
    ,ssc.[encryption_algorithm_name]
    ,ssc.[column_encryption_key_id]
    ,ssc.[column_encryption_key_database_name]
    ,ssc.[is_hidden]
    ,ssc.[is_masked]
    ,ssc.[graph_type]
    ,ssc.[graph_type_desc]
    ,t.[name] AS TypeName
FROM [sys].[system_columns] ssc
INNER JOIN sys.types t ON ssc.user_type_id = t.user_type_id
```

Columns and interpretation

- `object_id` (int): Object id that owns the column.
- `name` (string): Column name.
- `column_id` (int): Column id within the object.
- `system_type_id` (tinyint): Internal system type id.
- `user_type_id` (int): Database-wide user type id for the column type.
- `max_length` (smallint): Maximum byte length of the column.
- `precision` (tinyint): Precision for numeric types.
- `scale` (tinyint): Scale for numeric types.
- `collation_name` (string?): Collation name for character types.
- `is_nullable` (bit): Whether the column allows NULL.
- `is_ansi_padded` (bit): ANSI padding behavior.
- `is_rowguidcol` (bit): Whether the column is ROWGUIDCOL.
- `is_identity` (bit): Whether the column is identity.
- `is_computed` (bit): Whether the column is computed.
- `is_filestream` (bit): Whether the column is FILESTREAM.
- `is_replicated` (bit): Whether the column is replicated.
- `is_non_sql_subscribed` (bit): Non-SQL subscription flag.
- `is_merge_published` (bit): Merge publication flag.
- `is_dts_replicated` (bit): DTS replication flag.
- `is_xml_document` (bit): Whether the column is an XML document type.
- `xml_collection_id` (int): XML collection id if XML typed.
- `default_object_id` (int): Object id of default constraint object.
- `rule_object_id` (int): Object id of rule object.
- `is_sparse` (bit): Whether the column is SPARSE.
- `is_column_set` (bit): Whether the column is a column set for sparse columns.
- `generated_always_type` (tinyint): Generated always type code.
- `generated_always_type_desc` (string): Description of generated always type.
- `encryption_type` (int?): Always Encrypted type code.
- `encryption_type_desc` (string?): Description of encryption type.
- `encryption_algorithm_name` (string?): Algorithm name used for encryption.
- `column_encryption_key_id` (int?): Column encryption key id.
- `column_encryption_key_database_name` (string?): Database name of column encryption key.
- `is_hidden` (bit): Whether the column is hidden (e.g., internal or system-hidden column).
- `is_masked` (bit): Whether the column has a masking policy applied.
- `graph_type` (int?): Graph type code for graph tables.
- `graph_type_desc` (string?): Graph type description.
- `TypeName` (string): Human-readable type name joined from `sys.types`.

How to interpret

- Use `object_id` and `column_id` to join to `sys.objects` and `sys.columns` for object and column mapping.
- `max_length`, `precision`, and `scale` describe storage characteristics; for character data `max_length` is in bytes.
- Encryption and masking fields relate to Always Encrypted and Dynamic Data Masking features.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemColumnsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Obj:{r.GetObjectId()} Col:{r.GetName()} Id:{r.GetColumnId()} Type:{r.GetTypeName()} Nullable:{r.GetIsNullable()}");
```

See also:

- [sys.system_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-columns)
- [sys.types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-types)
