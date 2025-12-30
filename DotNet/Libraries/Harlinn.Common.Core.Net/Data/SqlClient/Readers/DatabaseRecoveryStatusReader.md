# DatabaseRecoveryStatusReader — reference

Overview

`DatabaseRecoveryStatusReader` wraps `sys.database_recovery_status` and exposes recovery and backup LSN and fork GUIDs for databases.

Reader SQL

```
SELECT
  drs0.[database_id],
  drs0.[database_guid],
  drs0.[family_guid],
  drs0.[last_log_backup_lsn],
  drs0.[recovery_fork_guid],
  drs0.[first_recovery_fork_guid],
  drs0.[fork_point_lsn]
FROM
  [sys].[database_recovery_status] drs0
```

Selected columns (property mapping and brief meaning)

- `database_id` ? `DatabaseId` (int): Database identifier.
- `database_guid` ? `DatabaseGuid` (Guid?): Database GUID.
- `family_guid` ? `FamilyGuid` (Guid?): Family GUID linking related backups.
- `last_log_backup_lsn` ? `LastLogBackupLsn` (decimal?): LSN of the last log backup.
- `recovery_fork_guid` ? `RecoveryForkGuid` (Guid?): GUID of the recovery fork.
- `first_recovery_fork_guid` ? `FirstRecoveryForkGuid` (Guid?): GUID of the first recovery fork.
- `fork_point_lsn` ? `ForkPointLsn` (decimal?): LSN indicating fork point for recovery.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseRecoveryStatusDataType` objects.
