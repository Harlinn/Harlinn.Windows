# SysoledbusersReader

Overview

`SysoledbusersReader` wraps `sys.sysoledbusers` (legacy) and exposes information about linked remote login mappings for OLE DB remote servers in older SQL Server versions.

Reader SQL

```
SELECT
  s11.[Rmtsrvid],
  s11.[Rmtloginame],
  s11.[Rmtpassword],
  s11.[Loginsid],
  s11.[Status],
  s11.[Changedate]
FROM
  [sys].[sysoledbusers] s11
```

Columns and interpretation

- `Rmtsrvid` (smallint?): Remote server id associated with the mapping.
- `Rmtloginame` (string?): Remote login name used on the remote server.
- `Rmtpassword` (string?): Remote login password (legacy storage; may be encrypted or null).
- `Loginsid` (binary?): Local login SID mapped to the remote login.
- `Status` (smallint?): Status flags for the mapping.
- `Changedate` (datetime): Date/time when the mapping was last changed.

How to interpret

- These rows represent mappings between local logins and remote logins used by linked server/OLE DB remote access.
- Prefer using modern linked server metadata views such as `sys.servers` and `sys.linked_logins` for current systems.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysoledbusersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysoledbusersReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"RemoteServerId:{r.Rmtsrvid} RemoteLogin:{r.Rmtloginame} LocalSid:{BitConverter.ToString(r.Loginsid ?? Array.Empty<byte>())}");
```

See also:

- [sys.sysoledbusers](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysoledbusers)
