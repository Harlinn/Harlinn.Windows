# DatabasePrincipalsReader — reference

Overview

`DatabasePrincipalsReader` wraps `sys.database_principals` and exposes database-level principal (user/role) metadata.

Reader SQL

```
SELECT
  dp0.[Name],
  dp0.[principal_id],
  dp0.[Type],
  dp0.[type_desc],
  dp0.[default_schema_name],
  dp0.[create_date],
  dp0.[modify_date],
  dp0.[owning_principal_id],
  dp0.[Sid],
  dp0.[is_fixed_role],
  dp0.[authentication_type],
  dp0.[authentication_type_desc],
  dp0.[default_language_name],
  dp0.[default_language_lcid],
  dp0.[allow_encrypted_value_modifications]
FROM
  [sys].[database_principals] dp0
```

Selected columns (property mapping and brief meaning)

- `Name` ? `Name` (string): Principal name.
- `principal_id` ? `PrincipalId` (int): Principal identifier.
- `Type` / `type_desc` ? type code and description (SQL user, Windows user, role etc.).
- `default_schema_name` ? `DefaultSchemaName` (string?): Default schema for the principal.
- `create_date` / `modify_date` ? creation and modification timestamps.
- `owning_principal_id` ? `OwningPrincipalId` (int?): Owner principal id for this principal.
- `Sid` ? `Sid` (byte[]?): Binary SID for Windows principals.
- `is_fixed_role` ? `IsFixedRole` (bool): Whether principal is a fixed database role.
- `authentication_type` / `authentication_type_desc` ? authentication type code and description.
- `default_language_name` / `default_language_lcid` ? default language settings.
- `allow_encrypted_value_modifications` ? `AllowEncryptedValueModifications` (bool): Flag whether principal can modify encrypted values.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabasePrincipalsDataType` objects.
