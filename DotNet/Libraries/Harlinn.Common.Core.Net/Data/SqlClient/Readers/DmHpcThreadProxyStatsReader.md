# DmHpcThreadProxyStatsReader — reference

Overview

`DmHpcThreadProxyStatsReader` wraps `sys.dm_hpc_thread_proxy_stats` and returns per-thread-proxy statistics for HPC devices used by SQL Server (for example GPUs) including rows processed, cycles used and I/O bytes.

Reader SQL

```
SELECT
  dhtps.[device_logical_id],
  dhtps.[device_type],
  dhtps.[device_provider],
  dhtps.[proxy_id],
  dhtps.[rows_handled],
  dhtps.[cycles_used],
  dhtps.[host_to_device_bytes],
  dhtps.[device_to_host_bytes],
  dhtps.[device_memory_bytes],
  dhtps.[session_id],
  dhtps.[request_id],
  dhtps.[Active]
FROM
  [sys].[dm_hpc_thread_proxy_stats] dhtps
```

Columns and interpretation

- `device_logical_id` ? `DeviceLogicalId` (int)
  - Logical identifier for the device as assigned by SQL Server.

- `device_type` ? `DeviceType` (int)
  - Numeric code for the device type (GPU, FPGA, etc.).

- `device_provider` ? `DeviceProvider` (int)
  - Numeric code identifying device provider/vendor.

- `proxy_id` ? `ProxyId` (int)
  - Identifier for the thread proxy on the device.

- `rows_handled` ? `RowsHandled` (long)
  - Number of rows processed by this proxy.

- `cycles_used` ? `CyclesUsed` (long)
  - Device cycles consumed by the proxy (relative measure of compute work).

- `host_to_device_bytes` ? `HostToDeviceBytes` (long)
  - Amount of data transferred from host to device in bytes.

- `device_to_host_bytes` ? `DeviceToHostBytes` (long)
  - Amount of data transferred from device back to host in bytes.

- `device_memory_bytes` ? `DeviceMemoryBytes` (long)
  - Amount of device memory used by this proxy in bytes.

- `session_id` ? `SessionId` (short)
  - SQL session id associated with the workload using the proxy.

- `request_id` ? `RequestId` (int)
  - Request id within the session associated with this activity.

- `Active` ? `Active` (bool)
  - Whether this proxy is currently active.

How to interpret

- Use `RowsHandled`, `CyclesUsed` and transfer bytes to gauge device utilization and identify bottlenecks in offloaded computations.
- `SessionId` and `RequestId` allow correlating device activity back to SQL sessions/requests.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHpcThreadProxyStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmHpcThreadProxyStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Device:{r.DeviceLogicalId} Proxy:{r.ProxyId} Rows:{r.RowsHandled} Cycles:{r.CyclesUsed} H->D:{r.HostToDeviceBytes} D->H:{r.DeviceToHostBytes} Active:{r.Active}");
}
```

See also:

- [sys.dm_hpc_thread_proxy_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hpc-thread-proxy-stats)
