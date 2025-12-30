# ParametersReader — reference

Overview

`ParametersReader` wraps `sys.parameters` and returns metadata about parameters for stored procedures, functions and other programmable objects.

Reader SQL

```
SELECT par.[object_id]
      ,par.[name]
      ,par.[parameter_id]
      ,par.[system_type_id]
      ,par.[user_type_id]
      ,par.[max_length]
      ,par.[precision]
      ,par.[scale]
      ,par.[is_output]
      ,par.[is_cursor_ref]
      ,par.[has_default_value]
      ,par.[is_xml_document]
      ,par.[default_value]
      ,par.[xml_collection_id]
      ,par.[is_readonly]
      ,par.[is_nullable]
      ,par.[encryption_type]
      ,par.[encryption_type_desc]
      ,par.[encryption_algorithm_name]
      ,par.[column_encryption_key_id]
      ,par.[column_encryption_key_database_name]
      ,t.[name] AS [type_name]
  FROM [sys].[parameters] par
  LEFT JOIN sys.types t ON par.user_type_id = t.user_type_id
```

Columns and interpretation

- `object_id` — object id of the parent object (procedure/function).
- `name` — parameter name.
- `parameter_id` — ordinal id of the parameter.
- Type metadata: `system_type_id`, `user_type_id`, `max_length`, `precision`, `scale`, `type_name`.
- `is_output` — whether parameter is output parameter.
- `is_cursor_ref` — whether parameter is a cursor reference.
- `has_default_value` / `default_value` — default value and whether one exists.
- `is_xml_document` / `xml_collection_id` — xml-document flag and associated xml collection id for validation.
- `is_readonly` — readonly flag for table-valued parameters.
- `is_nullable` — whether parameter accepts NULL.
- Encryption fields: `encryption_type`, `encryption_type_desc`, `encryption_algorithm_name`, `column_encryption_key_id`, `column_encryption_key_database_name` — Always Encrypted metadata.

How to interpret

- Use to inspect signatures of programmable objects. `is_readonly` applies to TVPs; xml collection id links to validation schemas.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ParametersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ParametersReader(rdr, ownsReader:false);
while (r.Read())
{
    var p = r.GetParameter();
    Console.WriteLine($"Obj:{p.ObjectId} Param:{p.Name} Id:{p.ParameterId} Type:{p.TypeName} Out:{p.IsOutput}");
}
```

See also:

- [sys.parameters](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-parameters)
