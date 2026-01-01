# TcpEndpointsReader

Overview

`TcpEndpointsReader` wraps `sys.tcp_endpoints` and exposes TCP endpoint definitions for the SQL Server instance.

Reader SQL

```
SELECT
  te1.[Name],
  te1.[endpoint_id],
  te1.[principal_id],
  te1.[Protocol],
  te1.[protocol_desc],
  te1.[Type],
  te1.[type_desc],
  te1.[State],
  te1.[state_desc],
  te1.[is_admin_endpoint],
  te1.[Port],
  te1.[is_dynamic_port],
  te1.[ip_address]
FROM
  [sys].[tcp_endpoints] te1
```

Columns and interpretation

- `Name` (string): Endpoint name.
- `endpoint_id` (int): Endpoint id.
- `principal_id` (int?): Principal id for endpoint owner.
- `Protocol` (tinyint): Protocol code (e.g., TCP).
- `protocol_desc` (string?): Protocol description.
- `Type` (tinyint): Endpoint type code.
- `type_desc` (string?): Type description (e.g., DATABASE_MIRRORING, SERVICE_BROKER).
- `State` (tinyint?): State code of the endpoint.
- `state_desc` (string?): State description (e.g., STARTED, STOPPED).
- `is_admin_endpoint` (bit): Whether the endpoint is an admin endpoint.
- `Port` (int): TCP port number.
- `is_dynamic_port` (bit): Whether the port is dynamic.
- `ip_address` (string?): IP address bound to the endpoint.

How to interpret

- Endpoint definitions determine how SQL Server listens for network connections and service endpoints for features like Service Broker or Database Mirroring.
- `is_dynamic_port` indicates whether the port is dynamically assigned.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TcpEndpointsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TcpEndpointsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Endpoint:{r.Name} Port:{r.Port} Protocol:{r.ProtocolDesc} State:{r.StateDesc} Admin:{r.IsAdminEndpoint}");
```

See also:

- [sys.tcp_endpoints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-tcp-endpoints)
