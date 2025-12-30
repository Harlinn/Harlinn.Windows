# DatabaseMirroringReader — reference

Overview

`DatabaseMirroringReader` wraps `sys.database_mirroring` and exposes mirroring status and configuration for databases.

Reader SQL

```
SELECT
  dm.[database_id],
  dm.[mirroring_guid],
  dm.[mirroring_state],
  dm.[mirroring_state_desc],
  dm.[mirroring_role],
  dm.[mirroring_role_desc],
  dm.[mirroring_role_sequence],
  dm.[mirroring_safety_level],
  dm.[mirroring_safety_level_desc],
  dm.[mirroring_safety_sequence],
  dm.[mirroring_partner_name],
  dm.[mirroring_partner_instance],
  dm.[mirroring_witness_name],
  dm.[mirroring_witness_state],
  dm.[mirroring_witness_state_desc],
  dm.[mirroring_failover_lsn],
  dm.[mirroring_connection_timeout],
  dm.[mirroring_redo_queue],
  dm.[mirroring_redo_queue_type],
  dm.[mirroring_end_of_log_lsn],
  dm.[mirroring_replication_lsn]
FROM
  [sys].[database_mirroring] dm
```

Selected columns (property mapping and brief meaning)

- `database_id` ? `DatabaseId` (int): Database identifier.
- `mirroring_guid` ? `MirroringGuid` (Guid?): Mirroring session GUID.
- `mirroring_state` / `mirroring_state_desc` ? state code and description.
- `mirroring_role` / `mirroring_role_desc` ? role code and description (principal/partner/witness).
- `mirroring_role_sequence` ? `MirroringRoleSequence` (int?): Sequence number for role changes.
- `mirroring_safety_level` / `mirroring_safety_level_desc` ? safety level code and description (FULL/ASYNC etc.).
- `mirroring_safety_sequence` ? sequence number for safety changes.
- `mirroring_partner_name` / `mirroring_partner_instance` ? partner server and instance names.
- `mirroring_witness_name` / `mirroring_witness_state` / `mirroring_witness_state_desc` ? witness info.
- `mirroring_failover_lsn`, `mirroring_end_of_log_lsn`, `mirroring_replication_lsn` ? LSN tracking values.
- `mirroring_connection_timeout` ? connection timeout value.
- `mirroring_redo_queue`, `mirroring_redo_queue_type` ? redo queue size and type.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseMirroringDataType` objects.
