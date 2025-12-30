# ServicesReader

Overview

`ServicesReader` wraps `sys.services` and exposes Service Broker service definitions.

Reader SQL

```
SELECT
  s1.[Name],
  s1.[service_id],
  s1.[principal_id],
  s1.[service_queue_id]
FROM
  [sys].[services] s1
```

Columns and interpretation

- `Name` (string): Service name.
- `service_id` (int): Service identifier.
- `principal_id` (int?): Principal id associated with the service.
- `service_queue_id` (int): Identifier of the queue used by the service.

How to interpret

- Services route messages to queues and are participants in contracts. Use `service_queue_id` to find the queue backing the service.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServicesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServicesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Service:{r.Name} QueueId:{r.ServiceQueueId} Principal:{r.PrincipalId}");
```

See also:

- [sys.services](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-services)
