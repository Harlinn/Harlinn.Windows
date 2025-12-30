# LoginTokenReader — reference

Overview

`LoginTokenReader` wraps `sys.login_token` and returns the token entries representing the security context for the current connection or session.

Reader SQL

```
SELECT
  lt.[principal_id],
  lt.[Sid],
  lt.[Name],
  lt.[Type],
  lt.[Usage]
FROM
  [sys].[login_token] lt
```

Columns and interpretation

- `principal_id` — database principal id (nullable) if the token maps to a principal.
- `Sid` — binary SID for the token entry (nullable).
- `Name` — name associated with the token (login, role, etc.).
- `Type` — token type (e.g., SQL user, WINDOWS GROUP, etc.).
- `Usage` — how the token is used (e.g., AUTHENTICATION, IMPERSONATION).

How to interpret

- `sys.login_token` is session-specific and shows the effective security tokens; useful for debugging permission/impersonation issues.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = LoginTokenReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new LoginTokenReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Principal:{r.PrincipalId} Name:{r.Name} Type:{r.Type} Usage:{r.Usage}");
}
```

See also:

- [sys.login_token](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-login-token)
