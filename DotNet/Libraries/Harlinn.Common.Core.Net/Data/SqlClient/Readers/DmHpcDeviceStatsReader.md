# DmHpcDeviceStatsReader — reference

Overview

`DmHpcDeviceStatsReader` wraps `sys.dm_hpc_device_stats` and reports stats for HPC devices that may be used by SQL Server for offloading or parallel computation (GPUs/FPGAs/etc.).

Reader SQL

```
SELECT
  dhds.[device_logical_id],
  dhds.[device_type],
  dhds.[device_provider],
  dhds.[device_physical_id],
  dhds.[Version],
  dhds.[compute_units],
  dhds.[max_thread_proxies],
  dhds.[clock_frequency],
  dhds.[device_memory_bytes],
  dhds.[rows_handled],
  dhds.[cycles_used],
  dhds.[device_to_host_bytes],
  dhds.[host_to_device_bytes],
  dhds.[device_ready]
FROM
  [sys].[dm_hpc_device_stats] dhds
```

Columns and interpretation

- `device_logical_id` ? logical identifier assigned to the device.
- `device_type` ? numeric type code for the device (GPU, FPGA, etc.).
- `device_provider` ? provider id or vendor code.
- `device_physical_id` ? physical device identifier.
- `Version` ? driver/hardware version.
- `compute_units` ? number of compute units available on the device.
- `max_thread_proxies` ? maximum thread proxies supported.
- `clock_frequency` ? clock frequency in Hz.
- `device_memory_bytes` ? amount of device memory in bytes.
- `rows_handled` ? number of rows processed by the device.
- `cycles_used` ? cycles used (device time metric).
- `device_to_host_bytes` / `host_to_device_bytes` ? data transfer metrics.
- `device_ready` ? whether the device is ready for computations.

How to interpret

- Useful for monitoring compute offload capabilities and data transfer bottlenecks.
- `rows_handled` and `cycles_used` indicate utilization; `device_ready` indicates availability.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHpcDeviceStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var d = new DmHpcDeviceStatsReader(rdr, ownsReader:false);
while (d.Read())
{
    Console.WriteLine($"Device:{d.DeviceLogicalId} Type:{d.DeviceType} Provider:{d.DeviceProvider} ComputeUnits:{d.ComputeUnits} Mem:{d.DeviceMemoryBytes} Ready:{d.DeviceReady}");
}
```

See also:

- [sys.dm_hpc_device_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hpc-device-stats)
