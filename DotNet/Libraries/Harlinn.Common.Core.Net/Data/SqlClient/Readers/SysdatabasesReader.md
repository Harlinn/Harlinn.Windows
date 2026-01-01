# SysdatabasesReader

Overview

`SysdatabasesReader` wraps `sys.sysdatabases` (legacy) and exposes basic catalog information about databases in the server instance.

Reader SQL

```
SELECT
  s16.[Name],
  s16.[Dbid],
  s16.[Sid],
  s16.[Mode],
  s16.[Status],
  s16.[Status2],
  s16.[Crdate],
  s16.[Reserved],
  s16.[Category],
  s16.[Cmptlevel],
  s16.[Filename],
  s16.[Version]
FROM
  [sys].[sysdatabases] s16
```

Columns and interpretation

- `Name` (string): Database name.
- `Dbid` (smallint?): Database identifier (database id).
- `Sid` (binary?): Database owner security identifier (owner SID).
- `Mode` (smallint?): Database mode flags (internal). Probably/guesswork: encodes single-user/multi-user and compatibility-related flags.
- `Status` (int?): Status bitmask describing database options and state (internal flags such as offline, read-only, etc.).
- `Status2` (int?): Additional status bits (internal). Probably/guesswork: extended status information introduced later.
- `Crdate` (datetime): Database creation date.
- `Reserved` (datetime?): Probably/guesswork: reservation timestamp or reserved field used by older SQL Server versions.
- `Category` (int?): Probably/guesswork: classification/category code for the database.
- `Cmptlevel` (tinyint): Database compatibility level.
- `Filename` (string?): Primary data file physical filename.
- `Version` (smallint?): Database internal version number.

How to interpret

- Use `Dbid` to join with other legacy metadata views that reference database id.
- `Sid` can be used to map the database owner to a server principal.
- Inspect `Status`/`Status2` bits using SQL Server documentation for the legacy `sysdatabases` view or prefer modern catalog views like `sys.databases` for clearer meaning.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysdatabasesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysdatabasesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Db: {r.Name} Id:{r.Dbid} Created:{r.Crdate} File:{r.Filename} Compat:{r.Cmptlevel}");
```

See also:

- [sys.sysdatabases](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysdatabases)
