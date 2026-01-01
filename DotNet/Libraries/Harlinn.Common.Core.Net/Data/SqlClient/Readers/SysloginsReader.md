# SysloginsReader

Overview

`SysloginsReader` wraps `sys.syslogins` (legacy) and exposes login-level information for server logins in older SQL Server versions.

Reader SQL

```
SELECT
  s13.[Sid],
  s13.[Status],
  s13.[Createdate],
  s13.[Updatedate],
  s13.[Accdate],
  s13.[Totcpu],
  s13.[Totio],
  s13.[Spacelimit],
  s13.[Timelimit],
  s13.[Resultlimit],
  s13.[Name],
  s13.[Dbname],
  s13.[Password],
  s13.[Language],
  s13.[Denylogin],
  s13.[Hasaccess],
  s13.[Isntname],
  s13.[Isntgroup],
  s13.[Isntuser],
  s13.[Sysadmin],
  s13.[Securityadmin],
  s13.[Serveradmin],
  s13.[Setupadmin],
  s13.[Processadmin],
  s13.[Diskadmin],
  s13.[Dbcreator],
  s13.[Bulkadmin],
  s13.[Loginname]
FROM
  [sys].[syslogins] s13
```

Columns and interpretation

- `Sid` (binary?): Security identifier for the login.
- `Status` (smallint?): Status flags for the login account (internal bitmask).
- `Createdate` (datetime): Login creation date.
- `Updatedate` (datetime): Login last update date.
- `Accdate` (datetime): Last access date for the login.
- `Totcpu` (int?): Total CPU used by the login (legacy cumulative metric).
- `Totio` (int?): Total IO used by the login (legacy cumulative metric).
- `Spacelimit` (int?): Space limit for the login (legacy quota fields).
- `Timelimit` (int?): Time limit for the login (legacy field).
- `Resultlimit` (int?): Result limits for the login (legacy resource governor fields).
- `Name` (string): Login name.
- `Dbname` (string?): Default database name for the login.
- `Password` (string?): Password hash or password field (legacy storage; may be null).
- `Language` (string?): Default language for the login.
- `Denylogin` (int?): Flag indicating login is denied.
- `Hasaccess` (int?): Flag indicating login has access.
- `Isntname` (int?): Probably/guesswork: internal flag about NT name mapping.
- `Isntgroup` (int?): Probably/guesswork: internal flag indicating Windows group mapping.
- `Isntuser` (int?): Probably/guesswork: internal flag indicating Windows user mapping.
- `Sysadmin` (int?): Flag indicating membership in sysadmin role.
- `Securityadmin` (int?): Flag indicating membership in securityadmin role.
- `Serveradmin` (int?): Flag indicating membership in serveradmin role.
- `Setupadmin` (int?): Flag indicating membership in setupadmin role.
- `Processadmin` (int?): Flag indicating membership in processadmin role.
- `Diskadmin` (int?): Flag indicating membership in diskadmin role.
- `Dbcreator` (int?): Flag indicating membership in dbcreator role.
- `Bulkadmin` (int?): Flag indicating membership in bulkadmin role.
- `Loginname` (string): Windows or SQL login name (display name).

How to interpret

- Prefer modern views like `sys.server_principals` and `sys.sql_logins` for current SQL Server versions; `sys.syslogins` is legacy.
- Role flags are represented as numeric flags; non-zero indicates membership/true.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysloginsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysloginsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Login:{r.Name} SID:{BitConverter.ToString(r.Sid ?? Array.Empty<byte>())} Created:{r.Createdate} LastAccess:{r.Accdate}");
```

See also:

- [sys.syslogins](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-syslogins)
