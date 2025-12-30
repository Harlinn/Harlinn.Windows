# ServiceBrokerEndpointsReader

Overview

`ServiceBrokerEndpointsReader` wraps `sys.service_broker_endpoints` and exposes Service Broker endpoint configurations.

Reader SQL

```
SELECT
  sbe.[Name],
  sbe.[endpoint_id],
  sbe.[principal_id],
  sbe.[Protocol],
  sbe.[protocol_desc],
  sbe.[Type],
  sbe.[type_desc],
  sbe.[State],
  sbe.[state_desc],
  sbe.[is_admin_endpoint],
  sbe.[is_message_forwarding_enabled],
  sbe.[message_forwarding_size],
  sbe.[connection_auth],
  sbe.[connection_auth_desc],
  sbe.[certificate_id],
  sbe.[encryption_algorithm],
  sbe.[encryption_algorithm_desc]
FROM
  [sys].[service_broker_endpoints] sbe
```

Columns and interpretation

- `Name` (string): Endpoint name.
- `endpoint_id` (int): Endpoint identifier.
- `principal_id` (int?): Principal id owning the endpoint.
- `Protocol`, `protocol_desc` (byte/string?): Protocol code and description (e.g., TSQL over TCP).
- `Type`, `type_desc` (byte/string?): Endpoint type and description.
- `State`, `state_desc` (byte/string?): Current state of the endpoint (started/stopped) and description.
- `is_admin_endpoint` (bool): Whether this is an administrative endpoint.
- `is_message_forwarding_enabled` (bool): Whether message forwarding is enabled.
- `message_forwarding_size` (int): Size threshold for forwarding messages.
- `connection_auth`, `connection_auth_desc` (byte/string?): Authentication method and description.
- `certificate_id` (int): Certificate id used for endpoint encryption.
- `encryption_algorithm`, `encryption_algorithm_desc` (byte/string?): Algorithm id and description for encryption.

How to interpret

- Use `protocol` and `connection_auth` to understand how Service Broker connections authenticate and encrypt traffic. `is_admin_endpoint` highlights endpoints reserved for admin operations.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServiceBrokerEndpointsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServiceBrokerEndpointsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Endpoint:{r.Name} Protocol:{r.ProtocolDesc} State:{r.StateDesc} Forwarding:{r.IsMessageForwardingEnabled}");
```

See also:

- [sys.service_broker_endpoints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-service-broker-endpoints)
