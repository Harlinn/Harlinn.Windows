# DmTcpListenerStatesReader — reference

Overview

`DmTcpListenerStatesReader` wraps `sys.dm_tcp_listener_states` and returns information about TCP listeners used by SQL Server (IP, port, type and state).

Reader SQL

```
SELECT
  dtls.[listener_id],
  dtls.[ip_address],
  dtls.[is_ipv4],
  dtls.[Port],
  dtls.[Type],
  dtls.[type_desc],
  dtls.[State],
  dtls.[state_desc],
  dtls.[start_time]
FROM
  [sys].[dm_tcp_listener_states] dtls
```

Columns and interpretation

- `listener_id` — listener identifier.
- `ip_address` — IP address being listened on (string).
- `is_ipv4` — boolean indicating IPv4 (true) vs IPv6.
- `Port` — TCP port number.
- `Type` / `type_desc` — numeric and textual listener type (e.g., dedicated, shared).
- `State` / `state_desc` — numeric and textual state (e.g., LISTENING, STOPPED).
- `start_time` — time listener started.

How to interpret

- Use to verify which addresses and ports SQL Server is listening on and whether listeners are active.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTcpListenerStatesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTcpListenerStatesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Listener:{r.ListenerId} IP:{r.IpAddress} Port:{r.Port} State:{r.StateDesc} Started:{r.StartTime}");
}
```

See also:

- [sys.dm_tcp_listener_states](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tcp-listener-states)
