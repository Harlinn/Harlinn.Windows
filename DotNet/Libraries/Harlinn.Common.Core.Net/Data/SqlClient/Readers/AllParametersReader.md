# AllParametersReader — reference

Overview

`AllParametersReader` wraps [`sys.all_parameters`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-all-parameters-transact-sql) and exposes metadata about procedure/function parameters visible to the current principal.

Reader SQL

```
SELECT
  ap.[object_id],
  ap.[Name],
  ap.[parameter_id],
  ap.[system_type_id],
  ap.[user_type_id],
  ap.[max_length],
  ap.[Precision],
  ap.[Scale],
  ap.[is_output],
  ap.[is_cursor_ref],
  ap.[has_default_value],
  ap.[is_xml_document],
  ap.[default_value],
  ap.[xml_collection_id],
  ap.[is_readonly],
  ap.[is_nullable],
  ap.[encryption_type],
  ap.[encryption_type_desc],
  ap.[encryption_algorithm_name],
  ap.[column_encryption_key_id],
  ap.[column_encryption_key_database_name]
FROM
  [sys].[all_parameters] ap
```

Selected columns (property mapping and brief meaning)

- `object_id` ? property: `ObjectId` (int)
  - Parent object (procedure/function) id.

- `Name` ? property: `Name` (string?)
  - Parameter name.

- `parameter_id` ? property: `ParameterId` (int)
  - Ordinal position of parameter.

- `system_type_id` / `user_type_id` ? properties: `SystemTypeId` (byte), `UserTypeId` (int)
  - Type ids indicating CLR/SQL type and user-defined type mapping.

- `max_length`, `Precision`, `Scale` ? properties: `MaxLength` (short), `Precision` (byte), `Scale` (byte)
  - Parameter sizing and numeric precision/scale.

- `is_output` ? property: `IsOutput` (bool)
  - Indicates output parameter.

- `is_cursor_ref` ? property: `IsCursorRef` (bool)
  - Cursor-ref parameter flag.

- `has_default_value` ? property: `HasDefaultValue` (bool)
  - Whether a default value exists.

- `is_xml_document` ? property: `IsXmlDocument` (bool)
  - XML document type flag.

- `default_value` ? property: `DefaultValue` (object?)
  - Default value expression (provider type may vary).

- `xml_collection_id` ? property: `XmlCollectionId` (int)
  - Xml schema collection id for typed xml parameters.

- `is_readonly` ? property: `IsReadonly` (bool)
  - Read-only parameter flag (table-valued parameter readonly).

- `is_nullable` ? property: `IsNullable` (bool?)
  - Nullable metadata.

- `encryption_*` / `column_encryption_key_*` ? properties: `EncryptionType` (int?), `EncryptionTypeDesc` (string?), `EncryptionAlgorithmName` (string?), `ColumnEncryptionKeyId` (int?), `ColumnEncryptionKeyDatabaseName` (string?)
  - Always Encrypted metadata for the parameter.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AllParametersDataType` objects.

---
