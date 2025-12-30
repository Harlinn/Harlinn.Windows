# NumberedProcedureParametersReader — reference

Overview

`NumberedProcedureParametersReader` wraps `sys.numbered_procedure_parameters` and returns parameters for procedures that are numbered (legacy or internal representations), including type and direction.

Reader SQL

```
SELECT
  npp.[object_id],
  npp.[procedure_number],
  npp.[Name],
  npp.[parameter_id],
  npp.[system_type_id],
  npp.[user_type_id],
  npp.[max_length],
  npp.[Precision],
  npp.[Scale],
  npp.[is_output],
  npp.[is_cursor_ref]
FROM
  [sys].[numbered_procedure_parameters] npp
```

Columns and interpretation

- `object_id` — object id of the procedure.
- `procedure_number` — internal procedure number (smallint) for numbered procedures.
- `Name` — parameter name (nullable for unnamed parameters).
- `parameter_id` — ordinal id of the parameter.
- `system_type_id`, `user_type_id`, `max_length`, `Precision`, `Scale` — type metadata.
- `is_output` — whether the parameter is an output parameter.
- `is_cursor_ref` — whether the parameter is a cursor reference.

How to interpret

- Use to inspect older or internal numbered procedures; combine with `sys.objects` to map object ids to names.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = NumberedProcedureParametersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new NumberedProcedureParametersReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} ProcNo:{r.ProcedureNumber} Param:{r.Name} Id:{r.ParameterId} Out:{r.IsOutput}");
}
```

See also:

- [sys.numbered_procedure_parameters](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-numbered-procedure-parameters)
