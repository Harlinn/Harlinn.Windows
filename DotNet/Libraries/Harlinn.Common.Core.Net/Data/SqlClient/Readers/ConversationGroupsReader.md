# ConversationGroupsReader — reference

Overview

`ConversationGroupsReader` wraps `sys.conversation_groups` and exposes Service Broker conversation group entries.

Reader SQL

```
SELECT
  cg.[conversation_group_id],
  cg.[service_id],
  cg.[is_system]
FROM
  [sys].[conversation_groups] cg
```

Selected columns (property mapping and brief meaning)

- `conversation_group_id` ? property: `ConversationGroupId` (Guid)
  - Unique identifier for the conversation group.

- `service_id` ? property: `ServiceId` (int)
  - Identifier of the service that owns or is associated with the conversation group.

- `is_system` ? property: `IsSystem` (bool?)
  - Indicates whether the conversation group is a system group (internal to Service Broker).

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ConversationGroupsDataType` objects.
