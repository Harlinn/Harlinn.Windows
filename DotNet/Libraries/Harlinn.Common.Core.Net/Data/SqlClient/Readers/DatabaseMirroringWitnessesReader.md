# DatabaseMirroringWitnessesReader — reference

Overview

`DatabaseMirroringWitnessesReader` wraps `sys.database_mirroring_witnesses` and exposes witness information for mirrored databases.

Reader SQL

```
SELECT
  dmw.[database_name],
  dmw.[principal_server_name],
  dmw.[mirror_server_name],
  dmw.[safety_level],
  dmw.[safety_level_desc],
  dmw.[safety_sequence_number],
  dmw.[role_sequence_number],
  dmw.[mirroring_guid],
  dmw.[family_guid],
  dmw.[is_suspended],
  dmw.[is_suspended_sequence_number],
  dmw.[partner_sync_state],
  dmw.[partner_sync_state_desc]
FROM
  [sys].[database_mirroring_witnesses] dmw
```

Selected columns (property mapping and brief meaning)

- `database_name` ? `DatabaseName` (string): Database name.
- `principal_server_name` ? `PrincipalServerName` (string?): Principal server name.
- `mirror_server_name` ? `MirrorServerName` (string?): Mirror server name.
- `safety_level` / `safety_level_desc` ? safety level code and description.
- `safety_sequence_number` ? `SafetySequenceNumber` (int): Safety sequence number.
- `role_sequence_number` ? `RoleSequenceNumber` (int): Role sequence number.
- `mirroring_guid` ? `MirroringGuid` (Guid): Mirroring session GUID.
- `family_guid` ? `FamilyGuid` (Guid): Family GUID grouping related databases.
- `is_suspended` ? `IsSuspended` (bool?): Whether mirroring is suspended.
- `is_suspended_sequence_number` ? sequence number when suspended.
- `partner_sync_state` / `partner_sync_state_desc` ? partner synchronization state and description.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseMirroringWitnessesDataType` objects.
