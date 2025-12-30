# ServerPermissionsReader

Overview

`ServerPermissionsReader` wraps `sys.server_permissions` and exposes server-level permission grants and their metadata.

Reader SQL

```
SELECT
  sp2.[Class],
  sp2.[class_desc],
  sp2.[major_id],
  sp2.[minor_id],
  sp2.[grantee_principal_id],
  sp2.[grantor_principal_id],
  sp2.[Type],
  sp2.[permission_name],
  sp2.[State],
  sp2.[state_desc]
FROM
  [sys].[server_permissions] sp2
```

Columns and interpretation

- `Class` (byte): Securable class code the permission applies to.
- `class_desc` (string?): Description of the class.
- `major_id` (int): Major id referencing the object the permission applies to.
- `minor_id` (int): Minor id, often used for sub-object references.
- `grantee_principal_id` (int): Principal id receiving the permission.
- `grantor_principal_id` (int): Principal id who granted the permission.
- `Type` (string): Permission type code.
- `permission_name` (string?): Name of the permission (e.g., CONNECT SQL).
- `State` (string): State code for the permission (e.g., GRANT, DENY).
- `state_desc` (string?): Description of the state.

How to interpret

- Use `grantee_principal_id` to map to principals in `sys.server_principals`.
- `Class` and `major_id` determine the target object; for server-wide permissions `major_id` may be 0.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerPermissionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerPermissionsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Grantee:{r.GranteePrincipalId} Permission:{r.PermissionName} State:{r.State}");
```

See also:

- [sys.server_permissions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-permissions)

