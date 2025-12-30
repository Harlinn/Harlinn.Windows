# ColumnEncryptionKeyValuesReader — reference

Overview

`ColumnEncryptionKeyValuesReader` wraps `sys.column_encryption_key_values` and exposes encrypted key values and algorithm names for column encryption keys.

Reader SQL

```
SELECT
  cekv.[column_encryption_key_id],
  cekv.[column_master_key_id],
  cekv.[encrypted_value],
  cekv.[encryption_algorithm_name]
FROM
  [sys].[column_encryption_key_values] cekv
```

Selected columns (property mapping and brief meaning)

- `column_encryption_key_id` ? property: `ColumnEncryptionKeyId` (int)
  - Identifier of the column encryption key these values belong to.

- `column_master_key_id` ? property: `ColumnMasterKeyId` (int)
  - Identifier of the column master key used to encrypt the CEK value.

- `encrypted_value` ? property: `EncryptedValue` (byte[]?)
  - Encrypted key value blob.

- `encryption_algorithm_name` ? property: `EncryptionAlgorithmName` (string?)
  - The encryption algorithm name used to encrypt the CEK value.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ColumnEncryptionKeyValuesDataType` objects.
