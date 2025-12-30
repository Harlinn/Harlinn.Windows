# ChangeTrackingDatabasesReader — reference

Overview

`ChangeTrackingDatabasesReader` wraps `sys.change_tracking_databases` and exposes database-level change tracking configuration.

Reader SQL

```
SELECT
  ctd.[database_id],
  ctd.[is_auto_cleanup_on],
  ctd.[retention_period],
  ctd.[retention_period_units],
  ctd.[retention_period_units_desc],
  ctd.[max_cleanup_version]
FROM
  [sys].[change_tracking_databases] ctd
```

Selected columns (property mapping and brief meaning)

- `database_id` ? property: `DatabaseId` (int)
  - Database id.

- `is_auto_cleanup_on` ? property: `IsAutoCleanupOn` (byte?)
  - Indicates whether automatic cleanup of change tracking information is enabled.

- `retention_period` ? property: `RetentionPeriod` (int?)
  - Retention window value.

- `retention_period_units` ? property: `RetentionPeriodUnits` (byte?)
  - Units code for retention period (e.g., minutes/hours/days).

- `retention_period_units_desc` ? property: `RetentionPeriodUnitsDesc` (string?)
  - Description of the retention units.

- `max_cleanup_version` ? property: `MaxCleanupVersion` (long?)
  - Maximum cleanup version available.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ChangeTrackingDatabasesDataType` objects.
