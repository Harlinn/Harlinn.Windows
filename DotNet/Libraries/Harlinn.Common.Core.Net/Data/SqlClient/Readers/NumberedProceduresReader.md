# NumberedProceduresReader — reference

Overview

`NumberedProceduresReader` wraps `sys.numbered_procedures` and returns entries for numbered procedures, including their internal definitions.

Reader SQL

```
SELECT
  np.[object_id],
  np.[procedure_number],
  np.[Definition]
FROM
  [sys].[numbered_procedures] np
```

Columns and interpretation

- `object_id` — object id of the object containing the numbered procedure.
- `procedure_number` — numeric identifier of the numbered procedure (nullable).
- `Definition` — textual definition (T-SQL) of the numbered procedure (nullable).

How to interpret

- Numbered procedures are legacy/internal; `definition` gives the body and may be null for certain system objects.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = NumberedProceduresReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new NumberedProceduresReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} ProcNo:{r.ProcedureNumber} DefLen:{(r.Definition?.Length ?? 0)}");
}
```

See also:

- [sys.numbered_procedures](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-numbered-procedures)
