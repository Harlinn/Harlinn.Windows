# ConversationEndpointsReader — reference

Overview

`ConversationEndpointsReader` wraps `sys.conversation_endpoints` and exposes Service Broker conversation endpoint metadata.

Reader SQL

```
SELECT
  ce.[conversation_handle],
  ce.[conversation_id],
  ce.[is_initiator],
  ce.[service_contract_id],
  ce.[conversation_group_id],
  ce.[service_id],
  ce.[Lifetime],
  ce.[State],
  ce.[state_desc],
  ce.[far_service],
  ce.[far_broker_instance],
  ce.[principal_id],
  ce.[far_principal_id],
  ce.[outbound_session_key_identifier],
  ce.[inbound_session_key_identifier],
  ce.[security_timestamp],
  ce.[dialog_timer],
  ce.[send_sequence],
  ce.[last_send_tran_id],
  ce.[end_dialog_sequence],
  ce.[receive_sequence],
  ce.[receive_sequence_frag],
  ce.[system_sequence],
  ce.[first_out_of_order_sequence],
  ce.[last_out_of_order_sequence],
  ce.[last_out_of_order_frag],
  ce.[is_system],
  ce.[Priority]
FROM
  [sys].[conversation_endpoints] ce
```

Selected columns (property mapping and brief meaning)

- `conversation_handle` ? `ConversationHandle` (Guid): Unique conversation handle.
- `conversation_id` ? `ConversationId` (Guid): Conversation id.
- `is_initiator` ? `IsInitiator` (bool): Whether endpoint is initiator side.
- `service_contract_id` ? `ServiceContractId` (int): Service contract id.
- `conversation_group_id` ? `ConversationGroupId` (Guid): Conversation group id.
- `service_id` ? `ServiceId` (int): Service id for the endpoint.
- `Lifetime` ? `Lifetime` (DateTime): Lifetime timestamp for endpoint.
- `State` ? `State` (string): Endpoint state code.
- `state_desc` ? `StateDesc` (string?): Human description of state.
- `far_service` ? `FarService` (string): Remote service name.
- `far_broker_instance` ? `FarBrokerInstance` (string?): Remote broker instance.
- `principal_id` / `far_principal_id` ? principal ids.
- `outbound_session_key_identifier` / `inbound_session_key_identifier` ? session key GUIDs.
- `security_timestamp` ? `SecurityTimestamp` (DateTime): Security timestamp.
- `dialog_timer` ? `DialogTimer` (DateTime): Dialog timer.
- `send_sequence`, `last_send_tran_id`, `end_dialog_sequence`, `receive_sequence`, `receive_sequence_frag`, `system_sequence`, `first_out_of_order_sequence`, `last_out_of_order_sequence`, `last_out_of_order_frag` ? sequence and transaction tracking fields.
- `is_system` ? `IsSystem` (bool): System endpoint flag.
- `Priority` ? `Priority` (byte): Priority level.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ConversationEndpointsDataType` objects.
