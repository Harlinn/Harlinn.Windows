# ServerPrincipalCredentialsReader

Overview

`ServerPrincipalCredentialsReader` wraps `sys.server_principal_credentials` and exposes mappings between server principals and credentials.

Reader SQL

```
SELECT
  spc.[principal_id],
  spc.[credential_id]
FROM
  [sys].[server_principal_credentials] spc
```

Columns and interpretation

- `principal_id` (int): Principal id of the server principal (maps to `sys.server_principals`).
- `credential_id` (int): Identifier of the credential linked to the principal (maps to `sys.credentials`).

How to interpret

- These rows indicate which credentials are associated with server principals for authentication to external resources.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerPrincipalCredentialsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerPrincipalCredentialsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Principal:{r.PrincipalId} Credential:{r.CredentialId}");
```

See also:

- [sys.server_principal_credentials](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-principal-credentials)

