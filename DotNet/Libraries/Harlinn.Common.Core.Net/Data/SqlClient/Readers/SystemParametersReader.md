# SystemParametersReader

Overview

`SystemParametersReader` wraps `sys.system_parameters` and exposes metadata about parameters for system objects such as stored procedures and functions.

Reader SQL

```
SELECT
  sp1.[object_id],
  sp1.[Name],
  sp1.[parameter_id],
  sp1.[system_type_id],
  sp1.[user_type_id],
  sp1.[max_length],
  sp1.[Precision],
  sp1.[Scale],
  sp1.[is_output],
  sp1.[is_cursor_ref],
  sp1.[has_default_value],
  sp1.[is_xml_document],
  sp1.[default_value],
  sp1.[xml_collection_id],
  sp1.[is_readonly],
  sp1.[is_nullable],
  sp1.[encryption_type],
  sp1.[encryption_type_desc],
  sp1.[encryption_algorithm_name],
  sp1.[column_encryption_key_id],
  sp1.[column_encryption_key_database_name]
FROM
  [sys].[system_parameters] sp1
```

Columns and interpretation

- `object_id` (int): Object id the parameter belongs to.
- `Name` (string?): Parameter name.
- `parameter_id` (int): Id/position of the parameter within the object.
- `system_type_id` (tinyint): System type id.
- `user_type_id` (int): User type id.
- `max_length` (smallint): Maximum byte length.
- `Precision` (tinyint): Precision for numeric types.
- `Scale` (tinyint): Scale for numeric types.
- `is_output` (bit): Whether the parameter is an output parameter.
- `is_cursor_ref` (bit): Whether the parameter is a cursor reference.
- `has_default_value` (bit): Whether a default value is defined.
- `is_xml_document` (bit): Whether the parameter is an XML document type.
- `default_value` (sql_variant/object?): Default value if present.
- `xml_collection_id` (int): XML collection id if XML typed.
- `is_readonly` (bit): Whether the parameter is readonly (table-valued parameters may be readonly).
- `is_nullable` (bit?): Nullable indicator.
- `encryption_type`/`encryption_type_desc`/`encryption_algorithm_name`/`column_encryption_key_id`/`column_encryption_key_database_name`: Columns related to Always Encrypted metadata.

How to interpret

- Use `object_id` and `parameter_id` to map parameters to their parent objects and to preserve parameter order for calls.
- Default values may be returned as a typed value; handle as object/sql_variant.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemParametersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemParametersReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.ObjectId} Param:{r.Name} Id:{r.ParameterId} IsOutput:{r.IsOutput} TypeId:{r.SystemTypeId}");
```

See also:

- [sys.system_parameters](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-parameters)
