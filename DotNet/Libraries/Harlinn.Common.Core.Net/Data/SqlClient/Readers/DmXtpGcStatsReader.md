# DmXtpGcStatsReader — reference

Overview

`DmXtpGcStatsReader` wraps `sys.dm_xtp_gc_stats` and returns aggregate statistics about the In-Memory OLTP (XTP) garbage collector activity such as sweep counts and rows expired.

Reader SQL

```
SELECT
  dxgs.[rows_examined],
  dxgs.[rows_no_sweep_needed],
  dxgs.[rows_first_in_bucket],
  dxgs.[rows_first_in_bucket_removed],
  dxgs.[rows_marked_for_unlink],
  dxgs.[parallel_assist_count],
  dxgs.[idle_worker_count],
  dxgs.[sweep_scans_started],
  dxgs.[sweep_scan_retries],
  dxgs.[sweep_rows_touched],
  dxgs.[sweep_rows_expiring],
  dxgs.[sweep_rows_expired],
  dxgs.[sweep_rows_expired_removed]
FROM
  [sys].[dm_xtp_gc_stats] dxgs
```

Columns and interpretation

- `rows_examined` — number of rows examined by GC sweeps.
- `rows_no_sweep_needed` — rows examined that did not need sweeping.
- `rows_first_in_bucket` — rows found as the first entry in their hash bucket.
- `rows_first_in_bucket_removed` — rows removed that were first in bucket.
- `rows_marked_for_unlink` — rows marked for unlinking (cleanup).
- `parallel_assist_count` — count of times parallel assistance was used.
- `idle_worker_count` — number of idle worker threads available to GC.
- `sweep_scans_started` — number of sweeps started.
- `sweep_scan_retries` — retries of sweep scans due to contention.
- `sweep_rows_touched` — rows touched during sweep scans.
- `sweep_rows_expiring` — rows identified as expiring.
- `sweep_rows_expired` — rows expired by sweeper.
- `sweep_rows_expired_removed` — expired rows removed from structures.

How to interpret

- High `sweep_scan_retries` or low `idle_worker_count` may indicate contention or insufficient GC resources.
- `rows_marked_for_unlink` and `sweep_rows_expired_removed` show progress of cleanup; mismatches indicate backlog.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXtpGcStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXtpGcStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Examined:{r.RowsExamined} ExpiredRemoved:{r.SweepRowsExpiredRemoved} SweepRetries:{r.SweepScanRetries}");
}
```

See also:

- [sys.dm_xtp_gc_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xtp-gc-stats)
