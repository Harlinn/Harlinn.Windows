# DmBrokerActivatedTasksReader — reference

Overview

`DmBrokerActivatedTasksReader` wraps `sys.dm_broker_activated_tasks` and exposes information about activations for Service Broker queues.

Reader SQL

```
SELECT
  dbat.[Spid],
  dbat.[database_id],
  dbat.[queue_id],
  dbat.[procedure_name],
  dbat.[execute_as]
FROM
  [sys].[dm_broker_activated_tasks] dbat
```

Selected columns (property mapping and brief meaning)

- `Spid` ? `Spid` (int?): Server process id running the activation task.
- `database_id` ? `DatabaseId` (short?): Database id hosting the queue.
- `queue_id` ? `QueueId` (int?): Identifier of the Service Broker queue.
- `procedure_name` ? `ProcedureName` (string?): Name of the stored procedure executed for activation.
- `execute_as` ? `ExecuteAs` (int?): Principal id under which the activation runs.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmBrokerActivatedTasksDataType` objects.
