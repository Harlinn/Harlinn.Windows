# ViaEndpointsReader

Overview

`ViaEndpointsReader` reads `sys.via_endpoints` and exposes endpoints that use the VIA protocol (deprecated networking protocol for SQL Server).

Reader SQL

```
SELECT
  ve.[Name],
  ve.[endpoint_id],
  ve.[principal_id],
  ve.[Protocol],
  ve.[protocol_desc],
  ve.[Type],
  ve.[type_desc],
  ve.[State],
  ve.[state_desc],
  ve.[is_admin_endpoint],
  ve.[Discriminator]
FROM
  [sys].[via_endpoints] ve
```

Columns and interpretation

- `Name` (sysname): Endpoint name.
- `endpoint_id` (int): Endpoint id.
- `principal_id` (int?): Principal id owner of the endpoint.
- `Protocol` (tinyint): Protocol code (VIA protocol code).
- `protocol_desc` (nvarchar?): Protocol description.
- `Type` (tinyint): Endpoint type code.
- `type_desc` (nvarchar?): Type description.
- `State` (tinyint?): State code for the endpoint.
- `state_desc` (nvarchar?): Human readable state description.
- `is_admin_endpoint` (bit): Whether the endpoint is an administration endpoint.
- `Discriminator` (nvarchar?): Additional discriminator value used internally to categorize endpoints.

How to interpret

- VIA is a legacy protocol; modern SQL Server installations typically use TCP endpoints (`sys.tcp_endpoints`) instead.
- Use `is_admin_endpoint` to identify endpoints reserved for administrative purposes.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ViaEndpointsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ViaEndpointsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Endpoint:{r.Name} Id:{r.EndpointId} Protocol:{r.ProtocolDesc} State:{r.StateDesc} Admin:{r.IsAdminEndpoint}");
```

See also:

- [sys.via_endpoints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-via-endpoints)
