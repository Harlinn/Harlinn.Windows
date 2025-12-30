# ServiceQueueUsagesReader

Overview

`ServiceQueueUsagesReader` wraps `sys.service_queue_usages` and exposes which services use which queues.

Reader SQL

```
SELECT
  squ.[service_id],
  squ.[service_queue_id]
FROM
  [sys].[service_queue_usages] squ
```

Columns and interpretation

- `service_id` (int): Identifier of the service.
- `service_queue_id` (int): Identifier of the queue used by the service.

How to interpret

- Join `service_id` to `sys.services` and `service_queue_id` to `sys.service_queues` to map services to their queues.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServiceQueueUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServiceQueueUsagesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Service:{r.ServiceId} Queue:{r.ServiceQueueId}");
```

See also:

- [sys.service_queue_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-service-queue-usages)
