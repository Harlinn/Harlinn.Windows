# SysforeignkeysReader

Overview

`SysforeignkeysReader` wraps `sys.sysforeignkeys` (legacy) and exposes foreign key constraint mappings between referencing and referenced tables/columns.

Reader SQL

```
SELECT
  s39.[Constid],
  s39.[Fkeyid],
  s39.[Rkeyid],
  s39.[Fkey],
  s39.[Rkey],
  s39.[Keyno]
FROM
  [sys].[sysforeignkeys] s39
```

Columns and interpretation

- `Constid` (int): Constraint id for the foreign key constraint.
- `Fkeyid` (int): Object id of the foreign key constraint's referencing table (the child table id).
- `Rkeyid` (int): Object id of the referenced table (parent table id).
- `Fkey` (smallint?): Column id in the referencing table (child column id) that participates in the foreign key.
- `Rkey` (smallint?): Column id in the referenced table (parent column id) that participates in the foreign key.
- `Keyno` (smallint?): Ordinal position of the column within a multi-column foreign key.

How to interpret

- Use `Fkeyid` and `Rkeyid` to join to `sys.objects` (or `sys.sysobjects`) to resolve table names.
- The `Fkey` and `Rkey` column ids can be joined to `sys.columns` to get column names.
- `Keyno` indicates the order of columns for composite foreign keys.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysforeignkeysReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysforeignkeysReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Constraint:{r.Constid} ChildObj:{r.Fkeyid} ParentObj:{r.Rkeyid} ChildCol:{r.Fkey} ParentCol:{r.Rkey} Ordinal:{r.Keyno}");
```

See also:

- [sys.sysforeignkeys](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysforeignkeys)
