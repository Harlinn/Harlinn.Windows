# SyslanguagesReader

Overview

`SyslanguagesReader` wraps `sys.syslanguages` (legacy) and exposes language and locale settings supported by the server.

Reader SQL

```
SELECT
  s24.[Langid],
  s24.[Dateformat],
  s24.[Datefirst],
  s24.[Upgrade],
  s24.[Name],
  s24.[Alias],
  s24.[Months],
  s24.[Shortmonths],
  s24.[Days],
  s24.[Lcid],
  s24.[Msglangid]
FROM
  [sys].[syslanguages] s24
```

Columns and interpretation

- `Langid` (smallint): Language id used in SQL Server.
- `Dateformat` (string): Date format string used by the language (e.g., `mdy`, `dmy`).
- `Datefirst` (byte): First day of the week for the language (1 = Monday, etc.).
- `Upgrade` (int?): Probably/guesswork: internal upgrade or versioning flag for the language.
- `Name` (string): Language name.
- `Alias` (string): Language alias used historically.
- `Months` (string?): Comma-separated month names for the locale.
- `Shortmonths` (string?): Comma-separated abbreviated month names.
- `Days` (string?): Comma-separated day names.
- `Lcid` (int): Windows locale identifier (LCID) for the language.
- `Msglangid` (smallint): Message language id used for system messages.

How to interpret

- Use `Langid` to set session language and to map message or format settings.
- `Dateformat` and `Datefirst` affect parsing and formatting of dates for sessions that use the language.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyslanguagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyslanguagesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Lang:{r.Name} Id:{r.Langid} DateFormat:{r.Dateformat} DateFirst:{r.Datefirst}");
```

See also:

- [sys.syslanguages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-syslanguages)
