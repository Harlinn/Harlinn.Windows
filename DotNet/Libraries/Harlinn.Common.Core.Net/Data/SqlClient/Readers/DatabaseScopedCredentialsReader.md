# DatabaseScopedCredentialsReader — reference

Overview

`DatabaseScopedCredentialsReader` wraps `sys.database_scoped_credentials` and exposes database-scoped credential metadata.

Reader SQL

```
SELECT
  dsc0.[Name],
  dsc0.[principal_id],
  dsc0.[credential_id],
  dsc0.[credential_identity],
  dsc0.[create_date],
  dsc0.[modify_date],
  dsc0.[target_type],
  dsc0.[target_id]
FROM
  [sys].[database_scoped_credentials] dsc0
```

Selected columns (property mapping and brief meaning)

- `Name` ? `Name` (string): Credential name local to the database.
- `principal_id` ? `PrincipalId` (int): Principal which owns the credential.
- `credential_id` ? `CredentialId` (int): Identifier referencing the server-level credential (if applicable).
- `credential_identity` ? `CredentialIdentity` (string?): Identity value for the credential (for example a username).
- `create_date` ? `CreateDate` (DateTime): Creation timestamp.
- `modify_date` ? `ModifyDate` (DateTime): Last modification timestamp.
- `target_type` ? `TargetType` (string?): Target type classification for the credential (if any).
- `target_id` ? `TargetId` (int?): Target object identifier if the credential targets a specific object.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseScopedCredentialsDataType` objects.
