# ChangeTrackingTablesReader — reference

Overview

`ChangeTrackingTablesReader` wraps `sys.change_tracking_tables` and exposes per-table change tracking metadata.

Reader SQL

```
SELECT
  ctt.[object_id],
  ctt.[is_track_columns_updated_on],
  ctt.[min_valid_version],
  ctt.[begin_version],
  ctt.[cleanup_version]
FROM
  [sys].[change_tracking_tables] ctt
```

Selected columns (property mapping and brief meaning)

- `object_id` ? property: `ObjectId` (int)
  - Object id for the tracked table.

- `is_track_columns_updated_on` ? property: `IsTrackColumnsUpdatedOn` (bool)
  - Indicates whether tracking includes which columns were updated.

- `min_valid_version` ? property: `MinValidVersion` (long?)
  - Minimum valid version for data retrieval.

- `begin_version` ? property: `BeginVersion` (long?)
  - Beginning version for change tracking.

- `cleanup_version` ? property: `CleanupVersion` (long?)
  - Cleanup version applied.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ChangeTrackingTablesDataType` objects.
