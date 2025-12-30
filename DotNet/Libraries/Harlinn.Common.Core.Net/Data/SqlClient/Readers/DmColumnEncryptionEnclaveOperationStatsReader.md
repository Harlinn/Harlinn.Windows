# DmColumnEncryptionEnclaveOperationStatsReader — reference

Overview

`DmColumnEncryptionEnclaveOperationStatsReader` wraps `sys.dm_column_encryption_enclave_operation_stats` and exposes aggregated counts of enclave operations by type.

Reader SQL

```
SELECT
  dceeos.[operation_type],
  dceeos.[total_operation_count]
FROM
  [sys].[dm_column_encryption_enclave_operation_stats] dceeos
```

Selected columns (property mapping and brief meaning)

- `operation_type` ? `OperationType` (string?)
  - Name/type of the enclave operation (for example, key retrieval, encryption/decryption operations).

- `total_operation_count` ? `TotalOperationCount` (long?)
  - Total number of operations of the given type performed since the counter was started.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmColumnEncryptionEnclaveOperationStatsDataType` objects.
