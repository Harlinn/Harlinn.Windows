# DmResourceGovernorResourcePoolVolumesReader — reference

Overview

`DmResourceGovernorResourcePoolVolumesReader` wraps `sys.dm_resource_governor_resource_pool_volumes` and returns I/O statistics per volume for resource pools.

Reader SQL

```
SELECT
  drgrpv.[pool_id],
  drgrpv.[volume_name],
  drgrpv.[read_io_queued_total],
  drgrpv.[read_io_issued_total],
  drgrpv.[read_io_completed_total],
  drgrpv.[read_io_throttled_total],
  drgrpv.[read_bytes_total],
  drgrpv.[read_io_stall_total_ms],
  drgrpv.[read_io_stall_queued_ms],
  drgrpv.[write_io_queued_total],
  drgrpv.[write_io_issued_total],
  drgrpv.[write_io_completed_total],
  drgrpv.[write_io_throttled_total],
  drgrpv.[write_bytes_total],
  drgrpv.[write_io_stall_total_ms],
  drgrpv.[write_io_stall_queued_ms],
  drgrpv.[io_issue_violations_total],
  drgrpv.[io_issue_delay_total_ms],
  drgrpv.[io_issue_ahead_total_ms],
  drgrpv.[reserved_io_limited_by_volume_total],
  drgrpv.[io_issue_delay_non_throttled_total_ms]
FROM
  [sys].[dm_resource_governor_resource_pool_volumes] drgrpv
```

Columns and interpretation

- `pool_id` — resource pool identifier.
- `volume_name` — name of the storage volume.
- `read_io_*`, `write_io_*` — counts of queued/issued/completed/throttled I/O operations.
- `read_bytes_total`, `write_bytes_total` — total bytes read/written.
- `*_io_stall_*` — cumulative stall times for I/O operations, measured in milliseconds.
- `io_issue_violations_total` — count of I/O issuance violations detected.
- `io_issue_delay_total_ms`, `io_issue_ahead_total_ms` — cumulative delay/ahead times related to I/O issuing and throttling.
- `reserved_io_limited_by_volume_total` — count of times reserved I/O was limited by volume constraints.
- `io_issue_delay_non_throttled_total_ms` — delay experienced for non-throttled I/O issues.

How to interpret

- Use volume-level metrics to pinpoint storage hotspots affecting a specific resource pool.
- High `*_io_stall_*` values indicate I/O latency impacting the pool; `io_issue_violations_total` suggests capacity policy breaches.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmResourceGovernorResourcePoolVolumesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmResourceGovernorResourcePoolVolumesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Pool:{r.PoolId} Volume:{r.VolumeName} ReadBytes:{r.ReadBytesTotal} WriteBytes:{r.WriteBytesTotal} ReadStallMs:{r.ReadIoStallTotalMs}");
}
```

See also:

- [sys.dm_resource_governor_resource_pool_volumes](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-resource-governor-resource-pool-volumes)
