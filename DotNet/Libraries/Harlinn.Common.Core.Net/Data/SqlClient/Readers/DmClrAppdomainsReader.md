# DmClrAppdomainsReader — reference

Overview

`DmClrAppdomainsReader` wraps `sys.dm_clr_appdomains` and exposes CLR AppDomain telemetry inside SQL Server.

Reader SQL

```
SELECT
  dca.[appdomain_address],
  dca.[appdomain_id],
  dca.[appdomain_name],
  dca.[creation_time],
  dca.[db_id],
  dca.[user_id],
  dca.[State],
  dca.[strong_refcount],
  dca.[weak_refcount],
  dca.[Cost],
  dca.[Value],
  dca.[compatibility_level],
  dca.[total_processor_time_ms],
  dca.[total_allocated_memory_kb],
  dca.[survived_memory_kb]
FROM
  [sys].[dm_clr_appdomains] dca
```

Selected columns (property mapping and brief meaning)

- `appdomain_address` ? `AppdomainAddress` (byte[]?): Address token for the appdomain in CLR.
- `appdomain_id` ? `AppdomainId` (int?): Numeric id of the appdomain.
- `appdomain_name` ? `AppdomainName` (string?): Friendly name of the appdomain.
- `creation_time` ? `CreationTime` (DateTime?): When the appdomain was created.
- `db_id` ? `DbId` (int?): Database id associated with the appdomain.
- `user_id` ? `UserId` (int?): User id under which appdomain runs.
- `State` ? `State` (string?): CLR appdomain state.
- `strong_refcount` ? `StrongRefcount` (int?): Count of strong CLR references.
- `weak_refcount` ? `WeakRefcount` (int?): Count of weak CLR references.
- `Cost` ? `Cost` (int?): Cost metric (probably internal CLR resource cost).
- `Value` ? `Value` (int?): Value metric (probably internal ranking/value).
- `compatibility_level` ? `CompatibilityLevel` (int?): DB compatibility level associated.
- `total_processor_time_ms` ? `TotalProcessorTimeMs` (long?): Cumulative processor time used by the appdomain (ms).
- `total_allocated_memory_kb` ? `TotalAllocatedMemoryKb` (long?): Allocated memory in KB.
- `survived_memory_kb` ? `SurvivedMemoryKb` (long?): Memory that survived GC in KB.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmClrAppdomainsDataType` objects.

Note

- Some metrics like `Cost` and `Value` are internal CLR metrics; documentation may be sparse — treat as implementation-specific.
