# DmBrokerQueueMonitorsReader — reference

Overview

`DmBrokerQueueMonitorsReader` wraps `sys.dm_broker_queue_monitors` and exposes monitoring information about Service Broker queue activity.

Reader SQL

```
SELECT
  dbqm.[database_id],
  dbqm.[queue_id],
  dbqm.[State],
  dbqm.[last_empty_rowset_time],
  dbqm.[last_activated_time],
  dbqm.[tasks_waiting]
FROM
  [sys].[dm_broker_queue_monitors] dbqm
```

Selected columns (property mapping and brief meaning)

- `database_id` ? `DatabaseId` (int?): Database identifier that hosts the queue.
- `queue_id` ? `QueueId` (int?): Identifier of the Service Broker queue being monitored.
- `State` ? `State` (string?): Current state of the queue monitor (e.g., ACTIVE/IDLE).
- `last_empty_rowset_time` ? `LastEmptyRowsetTime` (DateTime?): Time when the queue was observed empty.
- `last_activated_time` ? `LastActivatedTime` (DateTime?): Last time an activation occurred for this queue.
- `tasks_waiting` ? `TasksWaiting` (int?): Number of activation tasks currently waiting to run.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmBrokerQueueMonitorsDataType` objects.
