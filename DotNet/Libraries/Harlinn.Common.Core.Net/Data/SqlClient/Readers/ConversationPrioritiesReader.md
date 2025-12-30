# ConversationPrioritiesReader — reference

Overview

`ConversationPrioritiesReader` wraps `sys.conversation_priorities` and exposes configured conversation priority entries for Service Broker.

Reader SQL

```
SELECT
  cp.[priority_id],
  cp.[Name],
  cp.[service_contract_id],
  cp.[local_service_id],
  cp.[remote_service_name],
  cp.[Priority]
FROM
  [sys].[conversation_priorities] cp
```

Selected columns (property mapping and brief meaning)

- `priority_id` ? property: `PriorityId` (int)
  - Identifier for the priority entry.

- `Name` ? property: `Name` (string)
  - Name assigned to the priority entry.

- `service_contract_id` ? property: `ServiceContractId` (int?)
  - Identifier of the service contract the priority applies to.

- `local_service_id` ? property: `LocalServiceId` (int?)
  - Local service identifier.

- `remote_service_name` ? property: `RemoteServiceName` (string?)
  - Remote service name for which the priority is defined.

- `Priority` ? property: `Priority` (byte)
  - Numeric priority value; higher numbers typically indicate higher priority.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ConversationPrioritiesDataType` objects.
