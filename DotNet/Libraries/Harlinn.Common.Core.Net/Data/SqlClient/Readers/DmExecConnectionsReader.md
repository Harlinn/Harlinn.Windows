# DmExecConnectionsReader — reference

Overview

`DmExecConnectionsReader` wraps `sys.dm_exec_connections` and provides information about client connections to SQL Server, including transport, endpoints, encryption and network addresses.

Reader SQL

```
SELECT
  dec.[session_id],
  dec.[most_recent_session_id],
  dec.[connect_time],
  dec.[net_transport],
  dec.[protocol_type],
  dec.[protocol_version],
  dec.[endpoint_id],
  dec.[encrypt_option],
  dec.[auth_scheme],
  dec.[node_affinity],
  dec.[num_reads],
  dec.[num_writes],
  dec.[last_read],
  dec.[last_write],
  dec.[net_packet_size],
  dec.[client_net_address],
  dec.[client_tcp_port],
  dec.[local_net_address],
  dec.[local_tcp_port],
  dec.[connection_id],
  dec.[parent_connection_id],
  dec.[most_recent_sql_handle]
FROM
  [sys].[dm_exec_connections] dec
```

Columns (interpretation)

- `session_id` / `most_recent_session_id` ? session ids related to the connection. `most_recent_session_id` is the latest session attached to the connection.
- `connect_time` ? time connection was established.
- `net_transport` ? network transport (TCP, Named pipes, Shared memory).
- `protocol_type` / `protocol_version` ? TDS protocol details.
- `endpoint_id` ? endpoint identifier for the connection.
- `encrypt_option` ? encryption state (TRUE/FALSE/REQUESTED).
- `auth_scheme` ? authentication scheme used for login (e.g., NTLM, KERBEROS, SQL).
- `node_affinity` ? numeric affinity to a node—used in scaled environments.
- `num_reads` / `num_writes` ? number of reads/writes on the connection.
- `last_read` / `last_write` ? timestamps for the last IO activity.
- `net_packet_size` ? negotiated packet size for the connection.
- `client_net_address` / `client_tcp_port` ? remote client IP and port.
- `local_net_address` / `local_tcp_port` ? local endpoint address and port.
- `connection_id` / `parent_connection_id` ? GUIDs identifying connection and its parent.
- `most_recent_sql_handle` ? plan handle for most recent SQL on this connection.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecConnectionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var c = new DmExecConnectionsReader(rdr, ownsReader:false);
while (c.Read())
{
    Console.WriteLine($"Conn {c.ConnectionId} Session: {c.SessionId} ConnectTime: {c.ConnectTime} Transport: {c.NetTransport}");
    Console.WriteLine($" Client: {c.ClientNetAddress}:{c.ClientTcpPort} Local: {c.LocalNetAddress}:{c.LocalTcpPort} Encrypt: {c.EncryptOption}");
}
```

See also:

- [sys.dm_exec_connections](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-connections)
