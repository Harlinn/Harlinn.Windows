# DmHadrInstanceNodeMapReader — reference

Overview

`DmHadrInstanceNodeMapReader` wraps `sys.dm_hadr_instance_node_map` and maps instance node ids to cluster/instance names for Always On environments.

Reader SQL

```
SELECT
  dhinm.[instance_name],
  dhinm.[node_id],
  dhinm.[node_name]
FROM
  [sys].[dm_hadr_instance_node_map] dhinm
```

Columns and interpretation

- `instance_name` ? SQL instance name.
- `node_id` ? numeric node identifier within the instance/cluster.
- `node_name` ? cluster node name.

How to interpret

- Use this mapping to relate instance and cluster node identifiers when correlating cluster and SQL diagnostics.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrInstanceNodeMapReader.Sql;
using var rdr = cmd.ExecuteReader();
var m = new DmHadrInstanceNodeMapReader(rdr, ownsReader:false);
while (m.Read())
{
    Console.WriteLine($"Instance:{m.InstanceName} NodeId:{m.NodeId} Node:{m.NodeName}");
}
```

See also:

- [sys.dm_hadr_instance_node_map](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-instance-node-map)
