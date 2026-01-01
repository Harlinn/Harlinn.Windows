# UserTokenReader

Overview

`UserTokenReader` wraps `sys.user_token` and exposes token information associated with principals, used for authentication and authorization contexts.

Reader SQL

```
SELECT
  ut.[principal_id],
  ut.[Sid],
  ut.[Name],
  ut.[Type],
  ut.[Usage]
FROM
  [sys].[user_token] ut
```

Columns and interpretation

- `principal_id` (int?): Principal id associated with the token. NULL for tokens not bound to a principal.
- `Sid` (varbinary?): Security identifier (SID) binary for the token.
- `Name` (nvarchar?): Name associated with the token (e.g., login or external provider name).
- `Type` (nvarchar?): Token type (e.g., Windows principal, certificate, asymmetric key).
- `Usage` (nvarchar?): Description of token usage (e.g., authentication, signing).

How to interpret

- `Sid` can be used to map tokens to Windows accounts or principals; interpret using appropriate APIs or catalog joins.
- `Type` and `Usage` describe the nature and purpose of the token; use these fields for auditing and security analysis.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = UserTokenReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new UserTokenReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Principal:{r.PrincipalId} Name:{r.Name} Type:{r.Type} Usage:{r.Usage}");
```

See also:

- [sys.user_token](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-user-token)
