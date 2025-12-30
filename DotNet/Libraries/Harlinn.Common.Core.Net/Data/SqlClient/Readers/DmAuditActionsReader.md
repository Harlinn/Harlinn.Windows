# DmAuditActionsReader — reference

Overview

`DmAuditActionsReader` wraps `sys.dm_audit_actions` and exposes audit action metadata used by SQL Server auditing.

Reader SQL

```
SELECT
  daa.[action_id],
  daa.[Name],
  daa.[class_desc],
  daa.[covering_action_name],
  daa.[parent_class_desc],
  daa.[covering_parent_action_name],
  daa.[configuration_level],
  daa.[containing_group_name],
  daa.[action_in_log]
FROM
  [sys].[dm_audit_actions] daa
```

Selected columns (property mapping and brief meaning)

- `action_id` ? `ActionId` (string?): Identifier for the audit action (action code).
- `Name` ? `Name` (string?): Human-friendly action name.
- `class_desc` ? `ClassDesc` (string?): Description of the class the action applies to.
- `covering_action_name` ? `CoveringActionName` (string?): Name of an action that covers this action.
- `parent_class_desc` ? `ParentClassDesc` (string?): Description of parent class in hierarchy.
- `covering_parent_action_name` ? `CoveringParentActionName` (string?): Parent covering action name.
- `configuration_level` ? `ConfigurationLevel` (string?): Indicates configuration level for the action (SERVER/DATABASE etc.).
- `containing_group_name` ? `ContainingGroupName` (string?): Name of the group that contains this action.
- `action_in_log` ? `ActionInLog` (bool): Whether the action is recorded in the log.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmAuditActionsDataType` objects.

Note: Some descriptions are best verified against Microsoft Docs for `sys.dm_audit_actions`.
