# ExtendedProceduresReader — reference

Overview

`ExtendedProceduresReader` wraps `sys.extended_procedures` and returns metadata about extended stored procedures (legacy feature) including DLL names implementing the procedures.

Reader SQL

```
SELECT
  ep0.[Name],
  ep0.[object_id],
  ep0.[principal_id],
  ep0.[schema_id],
  ep0.[parent_object_id],
  ep0.[Type],
  ep0.[type_desc],
  ep0.[create_date],
  ep0.[modify_date],
  ep0.[is_ms_shipped],
  ep0.[is_published],
  ep0.[is_schema_published],
  ep0.[dll_name]
FROM
  [sys].[extended_procedures] ep0
```

Columns and interpretation

- `Name` — extended procedure name.
- `object_id` — object id for the extended procedure.
- `principal_id` — owning principal id (nullable).
- `schema_id` — schema id.
- `parent_object_id` — parent object id.
- `Type` / `type_desc` — type code and description.
- `create_date` / `modify_date` — creation and modification timestamps.
- `is_ms_shipped`, `is_published`, `is_schema_published` — flags indicating origin and publication.
- `dll_name` — DLL implementing the extended procedure (nullable).

How to interpret

- Extended procedures are legacy; `dll_name` reveals the native DLL used. Exercise caution when relying on extended procedures in modern systems.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExtendedProceduresReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExtendedProceduresReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Proc:{r.Name} ObjectId:{r.ObjectId} DLL:{r.DllName}");
}
```

See also:

- [sys.extended_procedures](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-extended-procedures)
