# AvailabilityDatabasesClusterReader — reference

Overview

`AvailabilityDatabasesClusterReader` wraps `sys.availability_databases_cluster` and exposes cluster-level availability group database metadata.

Reader SQL

```
SELECT
  adc.[group_id],
  adc.[group_database_id],
  adc.[database_name],
  adc.[truncation_lsn]
FROM
  [sys].[availability_databases_cluster] adc
```

Selected columns (property mapping and brief meaning)

- `group_id` ? property: `GroupId` (Guid)
  - Availability group identifier.

- `group_database_id` ? property: `GroupDatabaseId` (Guid)
  - Database id within the availability group cluster.

- `database_name` ? property: `DatabaseName` (string?)
  - Name of the database in the group.

- `truncation_lsn` ? property: `TruncationLsn` (decimal?)
  - Log sequence number used for truncation tracking.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AvailabilityDatabasesClusterDataType` objects.
