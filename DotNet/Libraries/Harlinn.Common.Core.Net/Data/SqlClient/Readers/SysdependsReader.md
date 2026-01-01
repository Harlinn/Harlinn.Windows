# SysdependsReader

Overview

`SysdependsReader` wraps `sys.sysdepends` (legacy) and exposes dependency relationships between database objects.

Reader SQL

```
SELECT
  s40.[Id],
  s40.[Depid],
  s40.[Number],
  s40.[Depnumber],
  s40.[Status],
  s40.[Deptype],
  s40.[Depdbid],
  s40.[Depsiteid],
  s40.[Selall],
  s40.[Resultobj],
  s40.[Readobj]
FROM
  [sys].[sysdepends] s40
```

Columns and interpretation

- `Id` (int): Object id of the dependent object (the object that has the dependency).
- `Depid` (int): Object id of the referenced object (the dependency target).
- `Number` (smallint?): Probably/guesswork: column or ordinal number within the object for the dependent reference.
- `Depnumber` (smallint?): Probably/guesswork: column or ordinal number within the referenced object.
- `Status` (smallint?): Probably/guesswork: status flags describing the dependency relationship (internal use).
- `Deptype` (tinyint): Dependency type code (internal categorization of dependency: object, column, etc.).
- `Depdbid` (smallint?): Probably/guesswork: database id of the referenced object when cross-database dependencies exist.
- `Depsiteid` (smallint?): Probably/guesswork: site id for distributed or remote dependencies.
- `Selall` (bit): Indicates whether the dependency is on SELECT * (select all columns) affecting dependency resolution.
- `Resultobj` (bit): Indicates this dependency is on the result of a computed object (internal meaning).
- `Readobj` (bit): Indicates a read dependency (object is read by the dependent object).

How to interpret

- Use `Id` and `Depid` to discover which objects depend on which other objects.
- Join to `sys.objects` (or `sys.sysobjects`) using object id to resolve human-readable object names.
- The `Selall`, `Resultobj`, and `Readobj` flags describe the nature of the dependency; treat them as boolean indicators.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysdependsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysdependsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.Id} DependsOn:{r.Depid} Type:{r.Deptype} SelAll:{r.Selall}");
```

See also:

- [sys.sysdepends](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysdepends)
