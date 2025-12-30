# DmExecDmsServicesReader — reference

Overview

`DmExecDmsServicesReader` wraps `sys.dm_exec_dms_services` and reports DMS (Distributed Management Service) core services information, including core ids, compute node associations and status.

Reader SQL

```
SELECT
  deds.[dms_core_id],
  deds.[compute_node_id],
  deds.[Status],
  deds.[compute_pool_id]
FROM
  [sys].[dm_exec_dms_services] deds
```

Columns and interpretation

- `dms_core_id` ? `DmsCoreId` (int?)
  - Identifier for DMS core service instance.

- `compute_node_id` ? `ComputeNodeId` (int?)
  - Compute node id associated with the service instance.

- `Status` ? `Status` (string?)
  - Textual status of the service (Online/Offline/etc.).

- `compute_pool_id` ? `ComputePoolId` (int)
  - ID of the compute pool the service belongs to.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecDmsServicesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmExecDmsServicesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DMS Core {r.DmsCoreId} Node: {r.ComputeNodeId} Status: {r.Status} Pool: {r.ComputePoolId}");
}
```

See also:

- [sys.dm_exec_dms_services](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-dms-services)
