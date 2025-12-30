# DatabaseAuditSpecificationDetailsReader — reference

Overview

`DatabaseAuditSpecificationDetailsReader` wraps `sys.database_audit_specification_details` and exposes detailed audit actions configured in database audit specifications.

Reader SQL

```
SELECT
  dasd.[database_specification_id],
  dasd.[audit_action_id],
  dasd.[audit_action_name],
  dasd.[Class],
  dasd.[class_desc],
  dasd.[major_id],
  dasd.[minor_id],
  dasd.[audited_principal_id],
  dasd.[audited_result],
  dasd.[is_group]
FROM
  [sys].[database_audit_specification_details] dasd
```

Selected columns (property mapping and brief meaning)

- `database_specification_id` ? `DatabaseSpecificationId` (int): Identifier of the database audit specification.
- `audit_action_id` ? `AuditActionId` (string): Action id code for the audited action.
- `audit_action_name` ? `AuditActionName` (string?): Human-friendly name for the audited action.
- `Class` / `class_desc` ? class code and description indicating the type of object the action applies to.
- `major_id` / `minor_id` ? object identifiers narrowing the scope (for example object_id and column_id).
- `audited_principal_id` ? `AuditedPrincipalId` (int): Principal id that is audited.
- `audited_result` ? `AuditedResult` (string?): Result filter for audit (e.g., SUCCESS, FAILURE).
- `is_group` ? `IsGroup` (bool?): Indicates whether the entry represents a group of actions.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseAuditSpecificationDetailsDataType` objects.
