# SysreferencesReader

Overview

`SysreferencesReader` wraps the legacy `sys.sysreferences` view and exposes foreign key constraint definitions and column mappings.

Reader SQL

```
SELECT
  s32.[Constid],
  s32.[Fkeyid],
  s32.[Rkeyid],
  s32.[Rkeyindid],
  s32.[Keycnt],
  s32.[Forkeys],
  s32.[Refkeys],
  s32.[Fkeydbid],
  s32.[Rkeydbid],
  s32.[Fkey1],
  ... up to Fkey16 and Rkey16
FROM
  [sys].[sysreferences] s32
```

Columns and interpretation

- `Constid` (int): Constraint id for the foreign key.
- `Fkeyid` (int): Object id of the referencing (child) table.
- `Rkeyid` (int?): Object id of the referenced (parent) table.
- `Rkeyindid` (smallint?): Index id on the referenced table used by the foreign key.
- `Keycnt` (smallint?): Number of key columns in the foreign key.
- `Forkeys` (binary?): Encoded list or bitmask of referencing key columns.
- `Refkeys` (binary?): Encoded list or bitmask of referenced key columns.
- `Fkeydbid` (smallint?): Database id of the referencing table when cross-database.
- `Rkeydbid` (smallint?): Database id of the referenced table when cross-database.
- `Fkey1..Fkey16` (smallint?): Column ids in the referencing table for each key position (up to 16 columns supported).
- `Rkey1..Rkey16` (smallint?): Column ids in the referenced table for each key position.

How to interpret

- Use `Fkeyid` and `Rkeyid` to join to `sys.objects` to get table names.
- Use `FkeyN` and `RkeyN` to map corresponding column ids; join to `sys.columns` to get column names.
- `Keycnt` indicates how many of the `Fkey`/`Rkey` columns are valid.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysreferencesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysreferencesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Constraint:{r.Constid} ChildObj:{r.Fkeyid} ParentObj:{r.Rkeyid} KeyCount:{r.Keycnt}");
```

See also:

- [sys.sysreferences](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysreferences)
