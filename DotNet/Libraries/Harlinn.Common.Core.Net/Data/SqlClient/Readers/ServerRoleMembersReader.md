# ServerRoleMembersReader

Overview

`ServerRoleMembersReader` wraps `sys.server_role_members` and exposes membership relationships between server roles and principals.

Reader SQL

```
SELECT
  srm.[role_principal_id],
  srm.[member_principal_id]
FROM
  [sys].[server_role_members] srm
```

Columns and interpretation

- `role_principal_id` (int): Principal id of the role.
- `member_principal_id` (int): Principal id of the member; use these ids to join to `sys.server_principals` to get names.

How to interpret

- Each row indicates that `member_principal_id` is a member of the role identified by `role_principal_id`. Use to build role membership graphs.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerRoleMembersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerRoleMembersReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"RoleId:{r.RolePrincipalId} MemberId:{r.MemberPrincipalId}");
```

See also:

- [sys.server_role_members](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-role-members)
