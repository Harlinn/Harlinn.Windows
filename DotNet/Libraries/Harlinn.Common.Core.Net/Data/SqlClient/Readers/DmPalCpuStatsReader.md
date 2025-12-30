# DmPalCpuStatsReader — reference

Overview

`DmPalCpuStatsReader` wraps `sys.dm_pal_cpu_stats` and returns platform abstraction layer CPU statistics such as uptime, load average, and various CPU time counters.

Reader SQL

```
SELECT
  dpcs.[uptime_secs],
  dpcs.[loadavg_1min],
  dpcs.[user_time_cs],
  dpcs.[nice_time_cs],
  dpcs.[system_time_cs],
  dpcs.[idle_time_cs],
  dpcs.[iowait_time_cs],
  dpcs.[irq_time_cs],
  dpcs.[softirq_time_cs],
  dpcs.[interrupt_cnt],
  dpcs.[csw_cnt],
  dpcs.[boot_time_secs],
  dpcs.[total_forks_cnt],
  dpcs.[proc_runable_cnt],
  dpcs.[proc_ioblocked_cnt],
  dpcs.[C3_time],
  dpcs.[C2_time],
  dpcs.[C1_time],
  dpcs.[C3_count],
  dpcs.[C2_count],
  dpcs.[C1_count]
FROM
  [sys].[dm_pal_cpu_stats] dpcs
```

Columns and interpretation

- `uptime_secs` — seconds since system boot.
- `loadavg_1min` — 1-minute load average (platform-dependent calculation).
- `user_time_cs` — user CPU time in centiseconds.
- `nice_time_cs` — nice (lower priority) CPU time in centiseconds.
- `system_time_cs` — system/kernel CPU time in centiseconds.
- `idle_time_cs` — idle CPU time in centiseconds.
- `iowait_time_cs` — I/O wait time in centiseconds.
- `irq_time_cs` — IRQ time in centiseconds.
- `softirq_time_cs` — soft IRQ time in centiseconds.
- `interrupt_cnt` — number of interrupts handled.
- `csw_cnt` — context switch count.
- `boot_time_secs` — system boot time in seconds since epoch.
- `total_forks_cnt` — total number of fork operations (process creations) observed.
- `proc_runable_cnt` — number of runnable processes.
- `proc_ioblocked_cnt` — number of processes blocked on I/O.
- `C3_time`, `C2_time`, `C1_time` — CPU C-state times (C3, C2, C1) in unspecified units (centiseconds or similar).
- `C3_count`, `C2_count`, `C1_count` — counts of transitions into respective C-states.

How to interpret

- Useful for OS-level CPU health and utilization diagnostics on non-Windows platforms (PAL = platform abstraction layer).
- `loadavg_1min` combined with `proc_runable_cnt` helps identify CPU contention.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmPalCpuStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmPalCpuStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Uptime:{r.UptimeSecs}s Load:{r.Loadavg1min} UserCs:{r.UserTimeCs} SystemCs:{r.SystemTimeCs}");
}
```

See also:

- [sys.dm_pal_cpu_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-pal-cpu-stats)
