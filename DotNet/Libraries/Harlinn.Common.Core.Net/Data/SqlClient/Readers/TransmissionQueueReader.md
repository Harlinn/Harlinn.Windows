# TransmissionQueueReader

Overview

`TransmissionQueueReader` wraps `sys.transmission_queue` and exposes messages queued for Service Broker transmission.

Reader SQL

```
SELECT
  tq.[conversation_handle],
  tq.[to_service_name],
  tq.[to_broker_instance],
  tq.[from_service_name],
  tq.[service_contract_name],
  tq.[enqueue_time],
  tq.[message_sequence_number],
  tq.[message_type_name],
  tq.[is_conversation_error],
  tq.[is_end_of_dialog],
  tq.[message_body],
  tq.[transmission_status],
  tq.[Priority]
FROM
  [sys].[transmission_queue] tq
```

Columns and interpretation

- `conversation_handle` (uniqueidentifier): Unique identifier for the Service Broker conversation.
- `to_service_name` (nvarchar?): Destination service name for the message.
- `to_broker_instance` (nvarchar?): Broker instance of the destination, if targeting a specific instance.
- `from_service_name` (nvarchar?): Originating service name.
- `service_contract_name` (nvarchar?): Contract name used for the message.
- `enqueue_time` (datetime): Time when the message was enqueued for transmission.
- `message_sequence_number` (bigint): Sequence number of the message in the conversation.
- `message_type_name` (nvarchar?): Message type name.
- `is_conversation_error` (bit): Whether the message represents a conversation error message.
- `is_end_of_dialog` (bit): Whether the message marks the end of the dialog/conversation.
- `message_body` (varbinary?): The binary message body; may contain XML or other payload depending on message type.
- `transmission_status` (nvarchar?): Human readable status about transmission (e.g., queued, suspended).
- `Priority` (tinyint): Transmission priority; lower or higher values indicate send priority based on implementation.

How to interpret

- Use `conversation_handle` to correlate queue messages to `sys.conversation_endpoints` and other Service Broker views.
- `transmission_status` and `is_conversation_error` help diagnose failed or suspended transmissions.
- `message_body` may require decoding according to the message type (XML, binary, etc.).

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TransmissionQueueReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TransmissionQueueReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Conv:{r.ConversationHandle} To:{r.ToServiceName} Seq:{r.MessageSequenceNumber} Enqueued:{r.EnqueueTime} Status:{r.TransmissionStatus}");
```

See also:

- [sys.transmission_queue](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-transmission-queue)
