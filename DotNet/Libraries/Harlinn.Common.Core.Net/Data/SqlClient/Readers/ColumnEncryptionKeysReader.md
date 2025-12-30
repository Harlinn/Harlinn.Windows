# ColumnEncryptionKeysReader — reference

Overview

`ColumnEncryptionKeysReader` wraps `sys.column_encryption_keys` and exposes metadata for Column Encryption Keys used by Always Encrypted feature.

Reader SQL

```
SELECT
  cek.[Name],
  cek.[column_encryption_key_id],
  cek.[create_date],
  cek.[modify_date]
FROM
  [sys].[column_encryption_keys] cek
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - Name of the column encryption key.

- `column_encryption_key_id` ? property: `ColumnEncryptionKeyId` (int)
  - Identifier for the column encryption key.

- `create_date` ? property: `CreateDate` (DateTime)
  - Creation timestamp.

- `modify_date` ? property: `ModifyDate` (DateTime)
  - Last modification timestamp.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ColumnEncryptionKeysDataType` objects.
