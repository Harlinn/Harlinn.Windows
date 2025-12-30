# DatabaseRoleMembersReader — reference

Overview

`DatabaseRoleMembersReader` wraps `sys.database_role_members` and exposes membership relationships between database roles and principals.

Reader SQL

```
SELECT
  drm.[role_principal_id],
  drm.[member_principal_id]
FROM
  [sys].[database_role_members] drm
```

Selected columns (property mapping and brief meaning)

- `role_principal_id` ? `RolePrincipalId` (int): Principal id of the role.
- `member_principal_id` ? `MemberPrincipalId` (int): Principal id of the member.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseRoleMembersDataType` objects.
