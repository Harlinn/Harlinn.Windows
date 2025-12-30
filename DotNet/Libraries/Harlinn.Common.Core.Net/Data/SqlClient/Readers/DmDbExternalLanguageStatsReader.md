# DmDbExternalLanguageStatsReader — reference

Overview

`DmDbExternalLanguageStatsReader` wraps `sys.dm_db_external_language_stats` and exposes whether external languages are installed for the database.

Reader SQL

```
SELECT
  ddels.[external_language_id],
  ddels.[is_installed]
FROM
  [sys].[dm_db_external_language_stats] ddels
```

Selected columns (property mapping and brief meaning)

- `external_language_id` ? `ExternalLanguageId` (int)
  - Identifier for external language (e.g., R, Python).

- `is_installed` ? `IsInstalled` (bool)
  - Whether the external language runtime is installed for the database.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmDbExternalLanguageStatsDataType` objects.
