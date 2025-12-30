# DmClrTasksReader — reference

Overview

`DmClrTasksReader` wraps `sys.dm_clr_tasks` and exposes CLR task (work item) telemetry.

Reader SQL

```
SELECT
  dct.[task_address],
  dct.[sos_task_address],
  dct.[appdomain_address],
  dct.[State],
  dct.[abort_state],
  dct.[Type],
  dct.[affinity_count],
  dct.[forced_yield_count]
FROM
  [sys].[dm_clr_tasks] dct
```

Selected columns (property mapping and brief meaning)

- `task_address` ? `TaskAddress` (byte[]?): Address token for the CLR task.
- `sos_task_address` ? `SosTaskAddress` (byte[]?): Address of the corresponding SOS task in SQL OS.
- `appdomain_address` ? `AppdomainAddress` (byte[]?): AppDomain token hosting the task.
- `State` ? `State` (string?): CLR task state.
- `abort_state` ? `AbortState` (string?): Abort/termination state if any.
- `Type` ? `Type` (string?): Task type.
- `affinity_count` ? `AffinityCount` (int?): Number of affinities assigned.
- `forced_yield_count` ? `ForcedYieldCount` (int?): Count of forced yields observed.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmClrTasksDataType` objects.
