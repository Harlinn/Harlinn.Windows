# DmColumnEncryptionEnclaveReader — reference

Overview

`DmColumnEncryptionEnclaveReader` wraps `sys.dm_column_encryption_enclave` and exposes runtime metrics for the column encryption enclave.

Reader SQL

```
SELECT
  dcee.[current_enclave_session_count],
  dcee.[current_column_encryption_key_count],
  dcee.[current_memory_size_kb],
  dcee.[total_evicted_session_count]
FROM
  [sys].[dm_column_encryption_enclave] dcee
```

Selected columns (property mapping and brief meaning)

- `current_enclave_session_count` ? `CurrentEnclaveSessionCount` (int?)
  - Number of active enclave sessions.

- `current_column_encryption_key_count` ? `CurrentColumnEncryptionKeyCount` (int?)
  - Count of column encryption keys currently loaded in the enclave.

- `current_memory_size_kb` ? `CurrentMemorySizeKb` (long?)
  - Memory used by the enclave in kilobytes.

- `total_evicted_session_count` ? `TotalEvictedSessionCount` (long?)
  - Total number of sessions evicted from the enclave (e.g., due to memory pressure).

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmColumnEncryptionEnclaveDataType` objects.
