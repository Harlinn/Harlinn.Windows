# ColumnMasterKeysReader — reference

Overview

`ColumnMasterKeysReader` wraps `sys.column_master_keys` and exposes metadata for Column Master Keys used by Always Encrypted and enclave computations.

Reader SQL

```
SELECT
  cmk.[Name],
  cmk.[column_master_key_id],
  cmk.[create_date],
  cmk.[modify_date],
  cmk.[key_store_provider_name],
  cmk.[key_path],
  cmk.[allow_enclave_computations],
  cmk.[Signature]
FROM
  [sys].[column_master_keys] cmk
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - Name of the column master key.

- `column_master_key_id` ? property: `ColumnMasterKeyId` (int)
  - Identifier for the column master key.

- `create_date` ? property: `CreateDate` (DateTime)
  - Creation timestamp.

- `modify_date` ? property: `ModifyDate` (DateTime)
  - Last modification timestamp.

- `key_store_provider_name` ? property: `KeyStoreProviderName` (string?)
  - Name of the key store provider (e.g., a provider for external key stores).

- `key_path` ? property: `KeyPath` (string?)
  - Provider-specific path or identifier to locate the master key.

- `allow_enclave_computations` ? property: `AllowEnclaveComputations` (int)
  - Indicator whether enclave computations are allowed for this master key.

- `Signature` ? property: `Signature` (byte[]?)
  - Optional signature blob associated with the master key registration.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ColumnMasterKeysDataType` objects.
