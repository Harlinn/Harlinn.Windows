# DatabaseCredentialsReader — reference

Overview

`DatabaseCredentialsReader` wraps `sys.database_credentials` and exposes database-scoped credentials.

Reader SQL

```
SELECT
  dc.[Name],
  dc.[principal_id],
  dc.[credential_id],
  dc.[credential_identity],
  dc.[create_date],
  dc.[modify_date],
  dc.[target_type],
  dc.[target_id]
FROM
  [sys].[database_credentials] dc
```

Selected columns (property mapping and brief meaning)

- `Name` ? `Name` (string): Credential name within database.
- `principal_id` ? `PrincipalId` (int): Principal id owning the credential.
- `credential_id` ? `CredentialId` (int): Identifier referencing server-level credential.
- `credential_identity` ? `CredentialIdentity` (string?): Identity used by the credential.
- `create_date` / `modify_date` ? creation and modification timestamps.
- `target_type` ? `TargetType` (string?): Target type for the credential.
- `target_id` ? `TargetId` (int?): Target id if scoped.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseCredentialsDataType` objects.
