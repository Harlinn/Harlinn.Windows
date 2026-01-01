# AvailabilityGroupsReader — reference

Overview

`AvailabilityGroupsReader` wraps [`sys.availability_groups`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-availability-groups-transact-sql) and exposes availability group configuration and status information at the database instance level.

Reader SQL

```
SELECT
  ag.[group_id],
  ag.[Name],
  ag.[resource_id],
  ag.[resource_group_id],
  ag.[failure_condition_level],
  ag.[health_check_timeout],
  ag.[automated_backup_preference],
  ag.[automated_backup_preference_desc],
  ag.[Version],
  ag.[basic_features],
  ag.[dtc_support],
  ag.[db_failover],
  ag.[is_distributed],
  ag.[cluster_type],
  ag.[cluster_type_desc],
  ag.[required_synchronized_secondaries_to_commit],
  ag.[sequence_number],
  ag.[is_contained]
FROM
  [sys].[availability_groups] ag
```

Selected columns (property mapping and brief meaning)

- `group_id` ? property: `GroupId` (Guid)
  - Availability group identifier.

- `Name` ? property: `Name` (string?)
  - Availability group name.

- `resource_id` / `resource_group_id` ? properties: `ResourceId` (string?), `ResourceGroupId` (string?)
  - Cluster resource identifiers.

- `failure_condition_level` ? property: `FailureConditionLevel` (int?)
  - Failover detection sensitivity level.

- `health_check_timeout` ? property: `HealthCheckTimeout` (int?)
  - Health check timeout.

- `automated_backup_preference` / `automated_backup_preference_desc` ? automated backup preference metadata.

- `Version` ? property: `Version` (short?)
  - Cluster/AG version.

- `basic_features` / `dtc_support` / `db_failover` / `is_distributed` ? feature/support flags.

- `cluster_type` / `cluster_type_desc` ? cluster type code and description.

- `required_synchronized_secondaries_to_commit` ? property: `RequiredSynchronizedSecondariesToCommit` (int?)
  - Quorum requirement for synchronous commits.

- `sequence_number` ? property: `SequenceNumber` (long?)
  - Sequence number for AG configuration changes.

- `is_contained` ? property: `IsContained` (bool?)
  - Containment flag for AG databases.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AvailabilityGroupsDataType` objects.
