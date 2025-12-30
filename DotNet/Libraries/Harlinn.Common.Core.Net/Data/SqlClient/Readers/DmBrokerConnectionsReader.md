# DmBrokerConnectionsReader — reference

Overview

`DmBrokerConnectionsReader` wraps `sys.dm_broker_connections` and exposes runtime statistics and status for Service Broker connections.

Reader SQL

```
SELECT
  dbc.[connection_id],
  dbc.[transport_stream_id],
  dbc.[State],
  dbc.[state_desc],
  dbc.[connect_time],
  dbc.[login_time],
  dbc.[authentication_method],
  dbc.[principal_name],
  dbc.[remote_user_name],
  dbc.[last_activity_time],
  dbc.[is_accept],
  dbc.[login_state],
  dbc.[login_state_desc],
  dbc.[peer_certificate_id],
  dbc.[encryption_algorithm],
  dbc.[encryption_algorithm_desc],
  dbc.[receives_posted],
  dbc.[is_receive_flow_controlled],
  dbc.[sends_posted],
  dbc.[is_send_flow_controlled],
  dbc.[total_bytes_sent],
  dbc.[total_bytes_received],
  dbc.[total_fragments_sent],
  dbc.[total_fragments_received],
  dbc.[total_sends],
  dbc.[total_receives],
  dbc.[peer_arbitration_id]
FROM
  [sys].[dm_broker_connections] dbc
```

Selected columns (property mapping and brief meaning)

- `connection_id` ? `ConnectionId` (Guid?): Connection unique identifier.
- `transport_stream_id` ? `TransportStreamId` (Guid?): Transport stream identifier for multiplexed transports.
- `State` / `state_desc` ? state code and description for connection.
- `connect_time` / `login_time` ? timestamps when connection established and authenticated.
- `authentication_method` ? `AuthenticationMethod` (string?): Method used for authentication.
- `principal_name` / `remote_user_name` ? principal and remote username for connection.
- `last_activity_time` ? last activity timestamp.
- `is_accept` ? whether connection is an acceptor side.
- `login_state` / `login_state_desc` ? login negotiation state and description.
- `peer_certificate_id` ? id of peer certificate used.
- `encryption_algorithm` / `encryption_algorithm_desc` ? encryption algorithm used and description.
- `receives_posted`, `sends_posted` ? counts of posted receives/sends.
- `is_receive_flow_controlled`, `is_send_flow_controlled` ? flow control flags.
- `total_bytes_sent`, `total_bytes_received` ? cumulative byte counters.
- `total_fragments_sent`, `total_fragments_received` ? fragment counters.
- `total_sends`, `total_receives` ? send/receive counters.
- `peer_arbitration_id` ? GUID for peer arbitration.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmBrokerConnectionsDataType` objects.
