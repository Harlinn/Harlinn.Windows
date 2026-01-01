# SysremoteloginsReader

Overview

`SysremoteloginsReader` wraps the legacy `sys.sysremotelogins` view and exposes mappings for remote logins used with remote servers/linked servers.

Reader SQL

```
SELECT
  s7.[Remoteserverid],
  s7.[Remoteusername],
  s7.[Status],
  s7.[Sid],
  s7.[Changedate]
FROM
  [sys].[sysremotelogins] s7
```

Columns and interpretation

- `Remoteserverid` (smallint?): Remote server identifier.
- `Remoteusername` (string?): Username on the remote server mapped to the local login.
- `Status` (smallint?): Status flags for the mapping (internal bitmask).
- `Sid` (binary?): Local login SID that the mapping applies to.
- `Changedate` (datetime): When the mapping was last changed.

How to interpret

- These mappings show how local logins are mapped to remote accounts; prefer `sys.servers` and `sys.linked_logins` for modern linked server metadata.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysremoteloginsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysremoteloginsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"RemoteServerId:{r.Remoteserverid} RemoteUser:{r.Remoteusername} Changed:{r.Changedate}");
```

See also:

- [sys.sysremotelogins](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysremotelogins)
