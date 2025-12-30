# DatabasePermissionsReader — reference

Overview

`DatabasePermissionsReader` wraps `sys.database_permissions` and exposes permission grants, denies and revokes at the database scope.

Reader SQL

```
SELECT
  dp.[Class],
  dp.[class_desc],
  dp.[major_id],
  dp.[minor_id],
  dp.[grantee_principal_id],
  dp.[grantor_principal_id],
  dp.[Type],
  dp.[permission_name],
  dp.[State],
  dp.[state_desc]
FROM
  [sys].[database_permissions] dp
```

Selected columns (property mapping and brief meaning)

- `Class` ? `Class` (byte): Object class code the permission applies to.
- `class_desc` ? `ClassDesc` (string?): Description of the class.
- `major_id` / `minor_id` ? object identifiers narrowing permission scope (e.g., object_id, column_id).
- `grantee_principal_id` ? `GranteePrincipalId` (int): Principal receiving the permission.
- `grantor_principal_id` ? `GrantorPrincipalId` (int): Principal that granted the permission.
- `Type` ? `Type` (string): Permission type code.
- `permission_name` ? `PermissionName` (string?): Human-friendly permission name.
- `State` ? `State` (string): State code (GRANT/DENY/REVOKE).
- `state_desc` ? `StateDesc` (string?): Description of the state.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabasePermissionsDataType` objects.
