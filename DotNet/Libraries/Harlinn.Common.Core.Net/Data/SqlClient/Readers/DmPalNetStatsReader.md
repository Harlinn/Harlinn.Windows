# DmPalNetStatsReader — reference

Overview

`DmPalNetStatsReader` wraps `sys.dm_pal_net_stats` and provides network interface statistics such as bytes/packets received, errors and drops.

Reader SQL

```
SELECT
  dpns.[Interface],
  dpns.[recv_bytes],
  dpns.[recv_packets],
  dpns.[Errors],
  dpns.[Drops],
  dpns.[Fifo],
  dpns.[Frame],
  dpns.[Compressed],
  dpns.[Multicast]
FROM
  [sys].[dm_pal_net_stats] dpns
```

Columns and interpretation

- `Interface` — network interface name.
- `recv_bytes` — number of bytes received.
- `recv_packets` — number of packets received.
- `Errors` — number of receive errors.
- `Drops` — number of dropped packets.
- `Fifo` — FIFO errors count.
- `Frame` — frame errors count.
- `Compressed` — number of compressed packets.
- `Multicast` — number of multicast packets.

How to interpret

- Use `recv_bytes` and `recv_packets` to calculate throughput.
- `Errors` and `Drops` indicate network issues; investigate NIC or driver problems.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmPalNetStatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmPalNetStatsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Iface:{r.Interface} Bytes:{r.RecvBytes} Packets:{r.RecvPackets} Errors:{r.Errors} Drops:{r.Drops}");
}
```

See also:

- [sys.dm_pal_net_stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-pal-net-stats)
