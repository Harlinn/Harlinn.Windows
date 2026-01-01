# TableTypesReader

Overview

`TableTypesReader` wraps `sys.table_types` and exposes user-defined table type metadata.

Reader SQL

```
SELECT st.[name]
    ,stt.[system_type_id]
    ,stt.[user_type_id]
    ,stt.[schema_id]
    ,stt.[principal_id]
    ,stt.[max_length]
    ,stt.[precision]
    ,stt.[scale]
    ,stt.[collation_name]
    ,stt.[is_nullable]
    ,stt.[is_user_defined]
    ,stt.[is_assembly_type]
    ,stt.[default_object_id]
    ,stt.[rule_object_id]
    ,stt.[is_table_type]
    ,stt.[type_table_object_id]
    ,stt.[is_memory_optimized]
FROM [sys].[table_types] stt
```

Columns and interpretation

- `name` (string): Type name.
- `system_type_id` (tinyint): System type id.
- `user_type_id` (int): User type id.
- `schema_id` (int): Schema id of the type.
- `principal_id` (int?): Principal id (owner).
- `max_length` (smallint): Maximum length in bytes.
- `precision` (tinyint): Precision for numeric types.
- `scale` (tinyint): Scale for numeric types.
- `collation_name` (string?): Collation name.
- `is_nullable` (bit): Whether type allows NULL values.
- `is_user_defined` (bit): Whether type is user-defined.
- `is_assembly_type` (bit): Whether type is CLR assembly type.
- `default_object_id` (int): Default object id.
- `rule_object_id` (int): Rule object id.
- `is_table_type` (bit): Whether the type is a table type.
- `type_table_object_id` (int): Object id of the type table if applicable.
- `is_memory_optimized` (bit): Whether table type is memory-optimized.

How to interpret

- Table types are used for table-valued parameters and table variables. Memory-optimized indicator applies to memory-optimized table types.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TableTypesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TableTypesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Type:{r.GetName()} SystemTypeId:{r.GetSystemTypeId()} UserTypeId:{r.GetUserTypeId()} MemoryOptimized:{r.GetIsMemoryOptimized()}");
```

See also:

- [sys.table_types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-table-types)
