# DmPalDiskStatsReader — reference

Overview

`DmPalDiskStatsReader` wraps `sys.dm_pal_disk_stats` and provides platform-specific disk I/O statistics such as reads/writes, sectors transferred and I/O timing.

Reader SQL

```
SELECT
  dpds.[dev_name],
  dpds.[major_num],
  dpds.[minor_num],
  dpds.[reads_completed],
  dpds.[reads_merged],
  dpds.[sectors_read],
  dpds.[read_time_ms],
  dpds.[writes_completed],
  dpds.[writes_merged],
  dpds.[sectors_written],
  dpds.[write_time_ms],
  dpds.[ios_in_progess],
  dpds.[io_time_ms],
  dpds.[weighted_io_time_ms]
FROM
  [sys].[dm_pal_disk_stats] dpds
```

Columns and interpretation

- `dev_name` — device name (e.g., physical disk or partition).
- `major_num` / `minor_num` — device major/minor numbers on Unix-like systems.
- `reads_completed` — number of read operations completed.
- `reads_merged` — number of reads merged by the OS.
- `sectors_read` — number of sectors read from the device.
- `read_time_ms` — cumulative read time in milliseconds.
- `writes_completed` — number of write operations completed.
- `writes_merged` — number of writes merged by the OS.
- `sectors_written` — number of sectors written to the device.
- `write_time_ms` — cumulative write time in milliseconds.
- `ios_in_progess` — number of I/O operations in progress.
- `io_time_ms` — cumulative time spent doing I/O in milliseconds.
- `weighted_io_time_ms` — weighted I/O time in milliseconds (accounts for concurrent I/O).

How to interpret

- Use reads/writes and time counters to compute throughput and average latency per I/O.
- High `ios_in_progress` combined with high `io_time_ms` can indicate saturated storage.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmPalDiskStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmPalDiskStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Device:{r.DevName} Reads:{r.ReadsCompleted} Writes:{r.WritesCompleted} IOms:{r.IoTimeMs}");
}
```

See also:

- [sys.dm_pal_disk_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-pal-disk-stats)
