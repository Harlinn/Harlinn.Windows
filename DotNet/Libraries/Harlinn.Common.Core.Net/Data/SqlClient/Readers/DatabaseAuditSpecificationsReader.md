# DatabaseAuditSpecificationsReader — reference

Overview

`DatabaseAuditSpecificationsReader` wraps `sys.database_audit_specifications` and exposes configured database audit specifications.

Reader SQL

```
SELECT
  das.[database_specification_id],
  das.[Name],
  das.[create_date],
  das.[modify_date],
  das.[audit_guid],
  das.[is_state_enabled]
FROM
  [sys].[database_audit_specifications] das
```

Selected columns (property mapping and brief meaning)

- `database_specification_id` ? `DatabaseSpecificationId` (int): Identifier of the database audit specification.
- `Name` ? `Name` (string): Specification name.
- `create_date` / `modify_date` ? timestamps for creation and last modification.
- `audit_guid` ? `AuditGuid` (Guid?): Unique identifier for the associated audit object.
- `is_state_enabled` ? `IsStateEnabled` (bool?): Whether the specification is enabled.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseAuditSpecificationsDataType` objects.
