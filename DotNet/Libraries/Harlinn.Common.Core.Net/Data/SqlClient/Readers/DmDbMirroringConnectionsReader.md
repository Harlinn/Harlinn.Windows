# DmDbMirroringConnectionsReader — reference

Overview

`DmDbMirroringConnectionsReader` wraps `sys.dm_db_mirroring_connections` and exposes runtime information for database mirroring (or availability group replication) transport connections.

Reader SQL

```
SELECT
  ddmc.[connection_id],
  ddmc.[transport_stream_id],
  ddmc.[State],
  ddmc.[state_desc],
  ddmc.[connect_time],
  ddmc.[login_time],
  ddmc.[authentication_method],
  ddmc.[principal_name],
  ddmc.[remote_user_name],
  ddmc.[last_activity_time],
  ddmc.[is_accept],
  ddmc.[login_state],
  ddmc.[login_state_desc],
  ddmc.[peer_certificate_id],
  ddmc.[encryption_algorithm],
  ddmc.[encryption_algorithm_desc],
  ddmc.[receives_posted],
  ddmc.[is_receive_flow_controlled],
  ddmc.[sends_posted],
  ddmc.[is_send_flow_controlled],
  ddmc.[total_bytes_sent],
  ddmc.[total_bytes_received],
  ddmc.[total_fragments_sent],
  ddmc.[total_fragments_received],
  ddmc.[total_sends],
  ddmc.[total_receives],
  ddmc.[peer_arbitration_id],
  ddmc.[Address]
FROM
  [sys].[dm_db_mirroring_connections] ddmc
```

Columns (detailed)

- `connection_id` ? `ConnectionId` (Guid?)
  - Unique identifier for the mirroring connection.

- `transport_stream_id` ? `TransportStreamId` (Guid?)
  - Identifier for the transport stream used by the connection.

- `State` / `state_desc` ? `State` (short?), `StateDesc` (string?)
  - Numeric state code and human-readable description for the connection state.

- `connect_time` ? `ConnectTime` (DateTime?)
  - Time when the transport connection was established.

- `login_time` ? `LoginTime` (DateTime?)
  - Time when the login/authentication completed.

- `authentication_method` ? `AuthenticationMethod` (string?)
  - Authentication method used (e.g., Windows, certificate).

- `principal_name` / `remote_user_name` ? `PrincipalName` (string?), `RemoteUserName` (string?)
  - Local principal name and remote username for the connection.

- `last_activity_time` ? `LastActivityTime` (DateTime?)
  - Timestamp of the last activity on this connection.

- `is_accept` ? `IsAccept` (bool?)
  - Whether the connection is on the acceptor side.

- `login_state` / `login_state_desc` ? `LoginState` (short?), `LoginStateDesc` (string?)
  - Numeric login negotiation state and description.

- `peer_certificate_id` ? `PeerCertificateId` (int?)
  - Id of the peer certificate used for TLS, if any.

- `encryption_algorithm` / `encryption_algorithm_desc` ? `EncryptionAlgorithm` (short?), `EncryptionAlgorithmDesc` (string?)
  - Encryption algorithm used and its description.

- `receives_posted` / `sends_posted` ? `ReceivesPosted` (short?), `SendsPosted` (short?)
  - Counts of posted receives/sends pending processing.

- `is_receive_flow_controlled` / `is_send_flow_controlled` ? flow control flags (bool?)
  - Whether receive/send flow control is active.

- `total_bytes_sent` / `total_bytes_received` ? cumulative byte counters (long?)
  - Total bytes sent and received over the connection.

- `total_fragments_sent` / `total_fragments_received` ? fragment counters (long?)
  - Number of message fragments sent/received.

- `total_sends` / `total_receives` ? total the number of send/receive operations (long?)

- `peer_arbitration_id` ? `PeerArbitrationId` (Guid?)
  - Arbitration GUID used in peer arbitration scenarios.

- `Address` ? `Address` (string?)
  - Network address or endpoint information for the peer.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbMirroringConnectionsReader.Sql;
using var reader = cmd.ExecuteReader();
var mcReader = new DmDbMirroringConnectionsReader(reader, ownsReader: false);
while (mcReader.Read())
{
    Console.WriteLine($"Connection: {mcReader.ConnectionId} State: {mcReader.StateDesc}");
    Console.WriteLine($"  Connect time: {mcReader.ConnectTime}, Last activity: {mcReader.LastActivityTime}");
    Console.WriteLine($"  Bytes sent/received: {mcReader.TotalBytesSent}/{mcReader.TotalBytesReceived}");
    Console.WriteLine($"  Address: {mcReader.Address}");
    Console.WriteLine();
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-mirroring-connections
