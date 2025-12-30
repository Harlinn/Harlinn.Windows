# DmHadrClusterReader — reference

Overview

`DmHadrClusterReader` wraps `sys.dm_hadr_cluster` and reports cluster-level quorum configuration and state.

Reader SQL

```
SELECT
  dhc.[cluster_name],
  dhc.[quorum_type],
  dhc.[quorum_type_desc],
  dhc.[quorum_state],
  dhc.[quorum_state_desc]
FROM
  [sys].[dm_hadr_cluster] dhc
```

Columns and interpretation

- `cluster_name` ? cluster name.
- `quorum_type` / `quorum_type_desc` ? quorum configuration type and description.
- `quorum_state` / `quorum_state_desc` ? current quorum state and textual description.

How to interpret

- Quorum type and state inform whether the cluster has sufficient votes to operate and can surface cluster-level problems.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrClusterReader.Sql;
using var rdr = cmd.ExecuteReader();
var c = new DmHadrClusterReader(rdr, ownsReader:false);
while (c.Read())
{
    Console.WriteLine($"Cluster:{c.ClusterName} QuorumType:{c.QuorumTypeDesc} State:{c.QuorumStateDesc}");
}
```

See also:

- [sys.dm_hadr_cluster](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-cluster)
