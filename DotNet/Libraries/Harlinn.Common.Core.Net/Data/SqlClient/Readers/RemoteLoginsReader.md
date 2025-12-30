# RemoteLoginsReader

Overview

`RemoteLoginsReader` wraps `sys.remote_logins` and exposes mappings between remote server logins and local principals.

Reader SQL

```
SELECT
  rl.[server_id],
  rl.[remote_name],
  rl.[local_principal_id],
  rl.[modify_date]
FROM
  [sys].[remote_logins] rl
```

Columns and interpretation

- `server_id` (int): Identifier of the remote server (links to `sys.servers`).
- `remote_name` (string?): Name of the login on the remote server.
- `local_principal_id` (int?): Local principal id mapped to the remote login (may be NULL).
- `modify_date` (DateTime): Last modified timestamp for the mapping.

How to interpret

- Remote logins are part of linked server security mappings. `local_principal_id` may be NULL meaning mapping applies to all users.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = RemoteLoginsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new RemoteLoginsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Server:{r.ServerId} Remote:{r.RemoteName} LocalPrincipal:{r.LocalPrincipalId}");
}
```

See also:

- [sys.remote_logins](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-remote-logins)

