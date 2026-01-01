# SystypesReader

Overview

`SystypesReader` wraps the legacy `sys.systypes` view and exposes type definitions and attributes used in older SQL Server versions.

Reader SQL

```
SELECT
  s31.[Name],
  s31.[Xtype],
  s31.[Status],
  s31.[Xusertype],
  s31.[Length],
  s31.[Xprec],
  s31.[Xscale],
  s31.[Tdefault],
  s31.[Domain],
  s31.[Uid],
  s31.[Reserved],
  s31.[Collationid],
  s31.[Usertype],
  s31.[Variable],
  s31.[Allownulls],
  s31.[Type],
  s31.[Printfmt],
  s31.[Prec],
  s31.[Scale],
  s31.[Collation]
FROM
  [sys].[systypes] s31
```

Columns and interpretation

- `Name` (string): Type name.
- `Xtype` (tinyint): Internal type code.
- `Status` (tinyint?): Status flags for the type.
- `Xusertype` (smallint?): Internal user type id.
- `Length` (smallint): Default length in bytes.
- `Xprec` (tinyint): Precision (legacy column).
- `Xscale` (tinyint): Scale (legacy column).
- `Tdefault` (int): Default type id reference.
- `Domain` (int): Domain id reference.
- `Uid` (smallint?): Owner user id.
- `Reserved` (smallint?): Reserved flag.
- `Collationid` (int?): Collation id if applicable.
- `Usertype` (smallint?): User type id.
- `Variable` (bit): Whether the type is variable-length.
- `Allownulls` (bit?): Whether the type allows NULL.
- `Type` (tinyint): Another type code used by the engine.
- `Printfmt` (string?): Print format for the type.
- `Prec` (smallint?): Precision.
- `Scale` (tinyint?): Scale.
- `Collation` (string?): Collation name.

How to interpret

- `sys.systypes` is legacy; prefer `sys.types` for modern databases.
- Use type codes and user type ids to map to type usage in `sys.columns` and parameter definitions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystypesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystypesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Type:{r.Name} Length:{r.Length} Variable:{r.Variable} Collation:{r.Collation}");
```

See also:

- [sys.systypes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-systypes)
- Prefer [sys.types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-types) for modern usage.
