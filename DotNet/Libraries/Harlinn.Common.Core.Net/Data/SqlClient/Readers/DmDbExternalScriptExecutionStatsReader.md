# DmDbExternalScriptExecutionStatsReader — reference

Overview

`DmDbExternalScriptExecutionStatsReader` wraps `sys.dm_db_external_script_execution_stats` and exposes execution counters for external script runtimes.

Reader SQL

```
SELECT
  ddeses.[external_language_id],
  ddeses.[counter_name],
  ddeses.[counter_value]
FROM
  [sys].[dm_db_external_script_execution_stats] ddeses
```

Selected columns (property mapping and brief meaning)

- `external_language_id` ? `ExternalLanguageId` (int)
  - Identifier for the external language runtime.

- `counter_name` ? `CounterName` (string)
  - Name of the statistical counter (e.g., execution_count, error_count).

- `counter_value` ? `CounterValue` (long)
  - Value of the counter.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmDbExternalScriptExecutionStatsDataType` objects.
