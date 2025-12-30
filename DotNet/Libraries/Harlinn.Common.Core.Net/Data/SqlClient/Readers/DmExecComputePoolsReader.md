# DmExecComputePoolsReader — reference

Overview

`DmExecComputePoolsReader` wraps `sys.dm_exec_compute_pools` and lists compute pools available on the instance. Each pool has an id, name and location string.

Reader SQL

```
SELECT
  decp0.[compute_pool_id],
  decp0.[Name],
  decp0.[Location]
FROM
  [sys].[dm_exec_compute_pools] decp0
```

Columns (interpretation)

- `compute_pool_id` ? pool identifier.
- `Name` ? pool name (string?).
- `Location` ? pool location string (logical or network address describing where the compute pool is hosted).

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecComputePoolsReader.Sql;
using var rdr = cmd.ExecuteReader();
var p = new DmExecComputePoolsReader(rdr, ownsReader:false);
while (p.Read())
{
    Console.WriteLine($"Pool {p.ComputePoolId}: {p.Name} at {p.Location}");
}
```

See also:

- [sys.dm_exec_compute_pools](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-compute-pools)
