# ServiceQueuesReader

Overview

`ServiceQueuesReader` wraps `sys.service_queues` and exposes Service Broker queue configuration.

Reader SQL

```
SELECT
  sq.[Name],
  sq.[object_id],
  sq.[principal_id],
  sq.[schema_id],
  sq.[parent_object_id],
  sq.[Type],
  sq.[type_desc],
  sq.[create_date],
  sq.[modify_date],
  sq.[is_ms_shipped],
  sq.[is_published],
  sq.[is_schema_published],
  sq.[max_readers],
  sq.[activation_procedure],
  sq.[execute_as_principal_id],
  sq.[is_activation_enabled],
  sq.[is_receive_enabled],
  sq.[is_enqueue_enabled],
  sq.[is_retention_enabled],
  sq.[is_poison_message_handling_enabled]
FROM
  [sys].[service_queues] sq
```

Columns and interpretation

- `Name` (string): Queue name.
- `object_id` (int): Object id of the queue table.
- `principal_id` (int?): Principal id owning the queue.
- `schema_id`, `parent_object_id` (int): Schema and parent object ids.
- `Type`, `type_desc` (string?): Queue type and description.
- `create_date`, `modify_date` (DateTime): Timestamps.
- `is_ms_shipped`, `is_published`, `is_schema_published` (bool): Flags.
- `max_readers` (short?): Max concurrent activation readers.
- `activation_procedure` (string?): Procedure to execute for activation.
- `execute_as_principal_id` (int?): Principal id for execute-as context.
- `is_activation_enabled`, `is_receive_enabled`, `is_enqueue_enabled`, `is_retention_enabled` (bool): Feature toggles.
- `is_poison_message_handling_enabled` (bool?): Whether poison message handling is enabled.

How to interpret

- Activation properties determine whether stored procedures are used to process messages. Retention and poison handling affect message lifecycle.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServiceQueuesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServiceQueuesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Queue:{r.Name} Activation:{r.IsActivationEnabled} MaxReaders:{r.MaxReaders} ActivationProc:{r.ActivationProcedure}");
```

See also:

- [sys.service_queues](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-service-queues)
