# AvailabilityGroupsClusterReader — reference

Overview

`AvailabilityGroupsClusterReader` wraps [`sys.availability_groups_cluster`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-availability-groups-cluster-transact-sql) and exposes cluster-level availability group metadata.

Reader SQL

```
SELECT
  agc.[group_id],
  agc.[Name],
  agc.[resource_id],
  agc.[resource_group_id],
  agc.[failure_condition_level],
  agc.[health_check_timeout],
  agc.[automated_backup_preference],
  agc.[automated_backup_preference_desc]
FROM
  [sys].[availability_groups_cluster] agc
```

Selected columns (property mapping and brief meaning)

- `group_id` ? property: `GroupId` (Guid)
  - Availability group identifier.

- `Name` ? property: `Name` (string?)
  - Availability group name.

- `resource_id` ? property: `ResourceId` (string?)
  - Resource identifier in the cluster.

- `resource_group_id` ? property: `ResourceGroupId` (string?)
  - Resource group identifier.

- `failure_condition_level` ? property: `FailureConditionLevel` (int?)
  - Level at which failure is detected for health checks.

- `health_check_timeout` ? property: `HealthCheckTimeout` (int?)
  - Timeout value for health checks (seconds).

- `automated_backup_preference` ? property: `AutomatedBackupPreference` (byte?)
  - Automated backup preference code.

- `automated_backup_preference_desc` ? property: `AutomatedBackupPreferenceDesc` (string?)
  - Description of automated backup preference.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AvailabilityGroupsClusterDataType` objects.
