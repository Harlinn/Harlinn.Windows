# SysmessagesReader

Overview

`SysmessagesReader` wraps `sys.sysmessages` (legacy) and exposes server message catalog entries (error messages and their metadata) for the server.

Reader SQL

```
SELECT
  s12.[Error],
  s12.[Severity],
  s12.[Dlevel],
  s12.[Description],
  s12.[Msglangid]
FROM
  [sys].[sysmessages] s12
```

Columns and interpretation

- `Error` (int): Error message number.
- `Severity` (tinyint?): Severity level for the message.
- `Dlevel` (smallint?): Probably/guesswork: detail level or diagnostic level.
- `Description` (string?): Text description of the message.
- `Msglangid` (smallint): Message language id indicating the language of the `Description` text.

How to interpret

- Use `Error` and `Msglangid` to find the correct message text for a given language.
- `Severity` indicates seriousness of the message; higher numbers typically indicate more severe conditions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysmessagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysmessagesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Error:{r.Error} Severity:{r.Severity} Lang:{r.Msglangid} Desc:{r.Description}");
```

See also:

- [sys.sysmessages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysmessages)
