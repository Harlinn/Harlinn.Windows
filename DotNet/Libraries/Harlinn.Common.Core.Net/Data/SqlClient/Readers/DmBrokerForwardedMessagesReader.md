# DmBrokerForwardedMessagesReader — reference

Overview

`DmBrokerForwardedMessagesReader` wraps `sys.dm_broker_forwarded_messages` and exposes metadata about messages forwarded through Service Broker.

Reader SQL

```
SELECT
  dbfm.[conversation_id],
  dbfm.[is_initiator],
  dbfm.[to_service_name],
  dbfm.[to_broker_instance],
  dbfm.[from_service_name],
  dbfm.[from_broker_instance],
  dbfm.[adjacent_broker_address],
  dbfm.[message_sequence_number],
  dbfm.[message_fragment_number],
  dbfm.[hops_remaining],
  dbfm.[time_to_live],
  dbfm.[time_consumed],
  dbfm.[message_id]
FROM
  [sys].[dm_broker_forwarded_messages] dbfm
```

Selected columns (property mapping and brief meaning)

- `conversation_id` ? `ConversationId` (Guid?): Conversation identifier.
- `is_initiator` ? `IsInitiator` (bool?): Whether message is from the initiator side.
- `to_service_name` / `to_broker_instance` ? destination service and broker instance.
- `from_service_name` / `from_broker_instance` ? source service and broker instance.
- `adjacent_broker_address` ? `AdjacentBrokerAddress` (string?): Address of adjacent broker that forwarded the message.
- `message_sequence_number` ? `MessageSequenceNumber` (long?): Sequence number for message ordering.
- `message_fragment_number` ? `MessageFragmentNumber` (int?): Fragment number when message was fragmented.
- `hops_remaining` ? `HopsRemaining` (byte?): Remaining hops before message expiration.
- `time_to_live` ? `TimeToLive` (int?): TTL in seconds or other unit.
- `time_consumed` ? `TimeConsumed` (int?): Time spent in forwarding (unit depends on DM view).
- `message_id` ? `MessageId` (Guid?): Unique message identifier.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmBrokerForwardedMessagesDataType` objects.
