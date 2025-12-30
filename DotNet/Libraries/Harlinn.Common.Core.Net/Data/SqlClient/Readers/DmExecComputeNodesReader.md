# DmExecComputeNodesReader — reference

Overview

`DmExecComputeNodesReader` wraps `sys.dm_exec_compute_nodes` and lists compute nodes in scale-out compute pools. The view includes node id, type, name, address and associated compute pool.

Reader SQL

```
SELECT
  decn.[compute_node_id],
  decn.[Type],
  decn.[Name],
  decn.[Address],
  decn.[compute_pool_id]
FROM
  [sys].[dm_exec_compute_nodes] decn
```

Columns (interpretation)

- `compute_node_id` ? `ComputeNodeId` (int?)
  - Identifier for the compute node; use to correlate with node status and errors.

- `Type` ? `Type` (string?)
  - Node type (e.g., Compute, Control).

- `Name` ? `Name` (string?)
  - Node name.

- `Address` ? `Address` (string?)
  - Network address/endpoint for the node.

- `compute_pool_id` ? `ComputePoolId` (int)
  - Compute pool id this node belongs to.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecComputeNodesReader.Sql;
using var rdr = cmd.ExecuteReader();
var n = new DmExecComputeNodesReader(rdr, ownsReader:false);
while (n.Read())
{
    Console.WriteLine($"Node {n.ComputeNodeId} Name: {n.Name} Type: {n.Type} Address: {n.Address} Pool: {n.ComputePoolId}");
}
```

See also:

- [sys.dm_exec_compute_nodes](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-compute-nodes)
