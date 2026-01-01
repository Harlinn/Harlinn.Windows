# SysusersReader

Overview

`SysusersReader` wraps the legacy `sys.sysusers` view and exposes database user principals and related metadata.

Reader SQL

```
SELECT
  s30.[Uid],
  s30.[Status],
  s30.[Name],
  s30.[Sid],
  s30.[Roles],
  s30.[Createdate],
  s30.[Updatedate],
  s30.[Altuid],
  s30.[Password],
  s30.[Gid],
  s30.[Environ],
  s30.[Hasdbaccess],
  s30.[Islogin],
  s30.[Isntname],
  s30.[Isntgroup],
  s30.[Isntuser],
  s30.[Issqluser],
  s30.[Isaliased],
  s30.[Issqlrole],
  s30.[Isapprole]
FROM
  [sys].[sysusers] s30
```

Columns and interpretation

- `Uid` (smallint?): User id within the database.
- `Status` (smallint?): Status flags for the user.
- `Name` (string): User name.
- `Sid` (binary?): Security identifier for the user mapping.
- `Roles` (binary?): Encoded roles membership.
- `Createdate` (datetime): Creation date of the user principal.
- `Updatedate` (datetime): Last update date.
- `Altuid` (smallint?): Alternate uid if used.
- `Password` (binary?): Password hash or stored credential (legacy storage).
- `Gid` (smallint?): Group id (legacy).
- `Environ` (string?): Environment string.
- `Hasdbaccess` (int?): Whether the user has database access.
- `Islogin`/`Isntname`/`Isntgroup`/`Isntuser`/`Issqluser`/`Isaliased`/`Issqlrole`/`Isapprole` (int?): Various flags indicating mapping to logins, Windows groups/users, roles, and application roles.

How to interpret

- Prefer `sys.database_principals` and `sys.database_role_members` for modern security metadata.
- Flags are legacy integer fields; non-zero usually indicates true.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysusersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysusersReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"User:{r.Name} Uid:{r.Uid} Created:{r.Createdate} HasDbAccess:{r.Hasdbaccess}");
```

See also:

- [sys.sysusers](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysusers)
- Prefer [sys.database_principals](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-database-principals) in modern databases.
