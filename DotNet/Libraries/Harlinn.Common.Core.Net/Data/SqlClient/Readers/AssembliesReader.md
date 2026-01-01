# AssembliesReader — reference

Overview

`AssembliesReader` wraps [`sys.assemblies`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-assemblies-transact-sql) and exposes metadata about CLR assemblies registered in the database instance.

Reader SQL

```
SELECT
  a0.[Name],
  a0.[principal_id],
  a0.[assembly_id],
  a0.[clr_name],
  a0.[permission_set],
  a0.[permission_set_desc],
  a0.[is_visible],
  a0.[create_date],
  a0.[modify_date],
  a0.[is_user_defined]
FROM
  [sys].[assemblies] a0
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - Assembly name.

- `principal_id` ? property: `PrincipalId` (int?)
  - Owner principal id of the assembly.

- `assembly_id` ? property: `AssemblyId` (int)
  - Unique identifier for the assembly.

- `clr_name` ? property: `ClrName` (string?)
  - CLR manifest name (full assembly name as registered).

- `permission_set` ? property: `PermissionSet` (byte?)
  - Numeric code for permission set (e.g., SAFE, EXTERNAL_ACCESS, UNSAFE).

- `permission_set_desc` ? property: `PermissionSetDesc` (string?)
  - Textual description of the permission set.

- `is_visible` ? property: `IsVisible` (bool)
  - Visibility flag (whether assembly is visible to user code).

- `create_date` ? property: `CreateDate` (DateTime)
  - Creation timestamp.

- `modify_date` ? property: `ModifyDate` (DateTime)
  - Last modification timestamp.

- `is_user_defined` ? property: `IsUserDefined` (bool?)
  - Indicates whether the assembly is user-defined (not system-supplied).

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AssembliesDataType` objects.
