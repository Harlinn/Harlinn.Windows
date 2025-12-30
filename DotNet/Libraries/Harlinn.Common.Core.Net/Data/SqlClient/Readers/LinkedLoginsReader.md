# LinkedLoginsReader — reference

Overview

`LinkedLoginsReader` wraps `sys.linked_logins` and returns mappings between local principals and remote logins for linked servers.

Reader SQL

```
SELECT
  ll.[server_id],
  ll.[local_principal_id],
  ll.[uses_self_credential],
  ll.[remote_name],
  ll.[modify_date]
FROM
  [sys].[linked_logins] ll
```

Columns and interpretation

- `server_id` — id of the linked server.
- `local_principal_id` — principal id in the local server to which the remote login is mapped (nullable).
- `uses_self_credential` — whether the link uses the caller's credentials.
- `remote_name` — name of the remote login.
- `modify_date` — last modification date of the mapping.

How to interpret

- Use to audit linked server mappings and understand which local principals map to remote logins.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = LinkedLoginsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new LinkedLoginsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Server:{r.ServerId} LocalPrincipal:{r.LocalPrincipalId} Remote:{r.RemoteName} SelfCred:{r.UsesSelfCredential}");
}
```

See also:

- [sys.linked_logins](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-linked-logins)
