# SysloginsReader

Reads rows from the `sys.syslogins` compatibility view. This view exposes server-level login accounts and metadata.

Columns:

- `Sid` (binary?, nullable)
  - Description: Security identifier for the login.
  - Interpretation: Use to map to Windows or SQL principal.
- `Status` (short?, nullable)
  - Description: Login status flags.
  - Interpretation: Encoded status bits (enabled/disabled, policy state, etc.).
- `Createdate` (DateTime)
  - Description: Date the login was created.
  - Interpretation: Creation timestamp.
- `Updatedate` (DateTime)
  - Description: Date the login was last updated.
  - Interpretation: Last modification timestamp.
- `Accdate` (DateTime)
  - Description: Probably/guesswork: last access date.
  - Interpretation: When the login last authenticated or accessed.
- `Totcpu` (int?, nullable)
  - Description: Total CPU time consumed by this login.
  - Interpretation: Aggregate CPU usage metric.
- `Totio` (int?, nullable)
  - Description: Total IO used by this login.
  - Interpretation: Aggregate IO metric.
- `Spacelimit` (int?, nullable)
  - Description: Probably/guesswork: disk space limit for login-owned objects.
  - Interpretation: Limits used in older SQL Server versions.
- `Timelimit` (int?, nullable)
  - Description: Probably/guesswork: CPU time limit or session time limit.
  - Interpretation: Internal or policy-driven limit.
- `Resultlimit` (int?, nullable)
  - Description: Probably/guesswork: maximum result set rows or limits.
  - Interpretation: Internal legacy value.
- `Name` (string)
  - Description: Login display name.
  - Interpretation: Name of the login as defined in SQL Server.
- `Dbname` (string?, nullable)
  - Description: Default database name for the login.
  - Interpretation: Database used on login by default.
- `Password` (string?, nullable)
  - Description: Probably/guesswork: hashed password or historic password field.
  - Interpretation: Do not rely on this for current authentication methods; may be NULL/hashed.
- `Language` (string?, nullable)
  - Description: Default language for the login.
  - Interpretation: Language alias or name.
- `Denylogin` (int?, nullable)
  - Description: Probably/guesswork: flag indicating if login is denied.
  - Interpretation: Non-zero indicates DENY.
- `Hasaccess` (int?, nullable)
  - Description: Probably/guesswork: whether the login has access to the server/database.
  - Interpretation: Non-zero indicates access present.
- `Isntname`, `Isntgroup`, `Isntuser` (int?, nullable)
  - Description: Probably/guesswork: flags indicating whether the login is a Windows NT name, group, or user.
  - Interpretation: Non-zero indicates true.
- Server role flags: `Sysadmin`, `Securityadmin`, `Serveradmin`, `Setupadmin`, `Processadmin`, `Diskadmin`, `Dbcreator`, `Bulkadmin` (int?, nullable)
  - Description: Role membership flags for common server roles.
  - Interpretation: Non-zero indicates membership.
- `Loginname` (string)
  - Description: Login name used to authenticate.
  - Interpretation: User-friendly login name.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysloginsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysloginsReader(reader);
while (r.Read())
{
    Console.WriteLine($"login={r.Loginname} name={r.Name} created={r.Createdate} disabled={(r.Status.HasValue && r.Status.Value==0)}");
}
```

See also:
- [sys.syslogins](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-syslogins-transact-sql)
