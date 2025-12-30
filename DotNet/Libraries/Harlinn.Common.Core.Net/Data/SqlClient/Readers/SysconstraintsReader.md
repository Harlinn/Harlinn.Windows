# SysconstraintsReader

Overview

`SysconstraintsReader` wraps `sys.sysconstraints` and exposes legacy constraint metadata for tables.

Reader SQL

```
SELECT
  s38.[Constid],
  s38.[Id],
  s38.[Colid],
  s38.[Spare1],
  s38.[Status],
  s38.[Actions],
  s38.[Error]
FROM
  [sys].[sysconstraints] s38
```

Columns and interpretation

- `Constid` (int): Constraint id.
- `Id` (int): Table id the constraint applies to.
- `Colid` (short?): Column id within the table if the constraint is column-specific.
- `Spare1` (byte?): Reserved/unused field.
- `Status` (int?): Status flags describing the constraint.
- `Actions` (int?): Action flags describing what to do when constraint violated.
- `Error` (int?): Error number to raise when constraint violated.

How to interpret

- This legacy view stores constraint definitions; prefer `sys.check_constraints`, `sys.key_constraints`, and `sys.default_constraints` for modern metadata. Use `Constid` to correlate to object definitions in older metadata systems.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysconstraintsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysconstraintsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Constraint:{r.Constid} Table:{r.Id} Col:{r.Colid} Status:{r.Status}");
```

See also:

- sys.sysconstraints (legacy)
- [sys.check_constraints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-check-constraints) (modern)
