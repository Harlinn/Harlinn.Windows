# CredentialsReader — reference

Overview

`CredentialsReader` wraps `sys.credentials` and exposes server-level credentials used for authentication to external resources.

Reader SQL

```
SELECT
  c1.[credential_id],
  c1.[Name],
  c1.[credential_identity],
  c1.[create_date],
  c1.[modify_date],
  c1.[target_type],
  c1.[target_id]
FROM
  [sys].[credentials] c1
```

Selected columns (property mapping and brief meaning)

- `credential_id` ? property: `CredentialId` (int)
  - Identifier for the credential.

- `Name` ? property: `Name` (string)
  - Credential name.

- `credential_identity` ? property: `CredentialIdentity` (string?)
  - Identity string used by the credential (e.g., username).

- `create_date` / `modify_date` ? creation and modification timestamps.

- `target_type` ? property: `TargetType` (string?)
  - Type of object the credential targets (if applicable).

- `target_id` ? property: `TargetId` (int?)
  - Target object id if the credential is scoped.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.CredentialsDataType` objects.
