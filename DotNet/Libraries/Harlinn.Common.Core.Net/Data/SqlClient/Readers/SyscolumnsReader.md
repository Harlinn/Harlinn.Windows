# SyscolumnsReader

Overview

`SyscolumnsReader` wraps the legacy `sys.syscolumns` view and exposes column metadata for older compatibility scenarios.

Reader SQL

```
SELECT
  s42.[Name],
  s42.[Id],
  s42.[Xtype],
  s42.[Typestat],
  s42.[Xusertype],
  s42.[Length],
  s42.[Xprec],
  s42.[Xscale],
  s42.[Colid],
  s42.[Xoffset],
  s42.[Bitpos],
  s42.[Reserved],
  s42.[Colstat],
  s42.[Cdefault],
  s42.[Domain],
  s42.[Number],
  s42.[Colorder],
  s42.[Autoval],
  s42.[Offset],
  s42.[Collationid],
  s42.[Language],
  s42.[Status],
  s42.[Type],
  s42.[Usertype],
  s42.[Printfmt],
  s42.[Prec],
  s42.[Scale],
  s42.[Iscomputed],
  s42.[Isoutparam],
  s42.[Isnullable],
  s42.[Collation],
  s42.[Tdscollation]
FROM
  [sys].[syscolumns] s42
```

Columns and interpretation

Many columns are legacy internal representations; common useful fields:

- `Name` (string?): Column name.
- `Id` (int): Table id that owns the column.
- `Colid` (short?): Column id within the table.
- `Length` (short): Storage length.
- `Prec`/`Scale` (short/int?): Precision and scale for numeric types.
- `Iscomputed`/`Isnullable` (int?): Flags indicating computed or nullable columns.
- `Collation` (string?): Collation name if applicable.
- `Tdscollation` (binary?): TDS collation bytes.

Other fields such as `Xtype`, `Xusertype`, `Typestat`, `Xoffset`, `Autoval` are internal legacy encodings and should be interpreted with caution.

How to interpret

- For modern development prefer `sys.columns`, `sys.types`, and `sys.default_constraints`. Use `Id` and `Colid` to join to other legacy sys tables.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscolumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscolumnsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"TableId:{r.Id} Column:{r.Name} Colid:{r.Colid} Length:{r.Length} Nullable:{r.Isnullable}");
```

See also:

- sys.syscolumns (legacy)
- [sys.columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-columns) (modern replacement)
