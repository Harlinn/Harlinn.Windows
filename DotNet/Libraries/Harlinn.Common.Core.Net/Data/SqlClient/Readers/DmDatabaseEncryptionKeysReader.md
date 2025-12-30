# DmDatabaseEncryptionKeysReader — reference

Overview

`DmDatabaseEncryptionKeysReader` wraps `sys.dm_database_encryption_keys` and exposes Transparent Data Encryption (TDE) key and scan state information.

Reader SQL

```
SELECT
  ddek.[database_id],
  ddek.[encryption_state],
  ddek.[create_date],
  ddek.[regenerate_date],
  ddek.[modify_date],
  ddek.[set_date],
  ddek.[opened_date],
  ddek.[key_algorithm],
  ddek.[key_length],
  ddek.[encryptor_thumbprint],
  ddek.[encryptor_type],
  ddek.[percent_complete],
  ddek.[encryption_state_desc],
  ddek.[encryption_scan_state],
  ddek.[encryption_scan_state_desc],
  ddek.[encryption_scan_modify_date]
FROM
  [sys].[dm_database_encryption_keys] ddek
```

Selected columns (property mapping and brief meaning)

- `database_id` ? `DatabaseId` (int?)
  - Database id the encryption key belongs to.

- `encryption_state` ? `EncryptionState` (int?)
  - Numeric encryption state (ENCRYPTION_ENABLED, etc.).

- `create_date` ? `CreateDate` (DateTime?)
  - When the key was created.

- `regenerate_date` ? `RegenerateDate` (DateTime?)
  - When the key was regenerated.

- `modify_date` ? `ModifyDate` (DateTime?)
  - When key metadata modified.

- `set_date` ? `SetDate` (DateTime?)
  - When this key was set as the database encryption key.

- `opened_date` ? `OpenedDate` (DateTime?)
  - When the key was opened for use.

- `key_algorithm` ? `KeyAlgorithm` (string?)
  - Algorithm name used by the key.

- `key_length` ? `KeyLength` (int?)
  - Key length in bits.

- `encryptor_thumbprint` ? `EncryptorThumbprint` (byte[]?)
  - Thumbprint of encryptor certificate or key provider.

- `encryptor_type` ? `EncryptorType` (string?)
  - Type of encryptor (certificate, provider, etc.).

- `percent_complete` ? `PercentComplete` (float?)
  - Percent complete for ongoing encryption or scan operations.

- `encryption_state_desc` ? `EncryptionStateDesc` (string?)
  - Textual description of encryption state.

- `encryption_scan_state` ? `EncryptionScanState` (int?)
  - Numeric code for encryption scan state.

- `encryption_scan_state_desc` ? `EncryptionScanStateDesc` (string?)
  - Text description for scan state.

- `encryption_scan_modify_date` ? `EncryptionScanModifyDate` (DateTime?)
  - When scan state last changed.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmDatabaseEncryptionKeysDataType` objects.
