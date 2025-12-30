# SchemaObjectsReader

Overview

`SchemaObjectsReader` wraps `sys.objects` (selected columns) and exposes general information about schema-scoped objects (tables, views, procedures, etc.).

Reader SQL

```
SELECT [name]
    ,[object_id]
    ,[principal_id]
    ,[schema_id]
    ,[parent_object_id]
    ,[type]
    ,[type_desc]
    ,[create_date]
    ,[modify_date]
    ,[is_ms_shipped]
    ,[is_published]
    ,[is_schema_published]
FROM [sys].[objects]
```

Columns and interpretation

- `name` (string): Name of the object.
- `object_id` (int): Object identifier within the database.
- `principal_id` (int?): Owner principal id for the object.
- `schema_id` (int): Schema id owning the object.
- `parent_object_id` (int): For columns like constraints or triggers, the parent object id; for most objects 0.
- `type` (string): Short object type code (e.g., 'U' = user table, 'V' = view).
- `type_desc` (string): Descriptive type text (e.g., 'USER_TABLE').
- `create_date` (DateTime): Creation timestamp.
- `modify_date` (DateTime): Last modification timestamp.
- `is_ms_shipped` (bool): Whether object is shipped by Microsoft.
- `is_published` (bool): Whether object is published for replication.
- `is_schema_published` (bool): Whether object is schema published.

How to interpret

- Join `schema_id` to `sys.schemas` to get schema names.
- Use `type` and `type_desc` to filter objects like tables or stored procedures.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SchemaObjectsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SchemaObjectsReader(rdr, ownsReader:false);
while (r.Read())
{
    var o = r.GetSchemaObject();
    Console.WriteLine($"{o.Name} ({o.TypeDesc}) id={o.ObjectId}");
}
```

See also:

- [sys.objects](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-objects)

