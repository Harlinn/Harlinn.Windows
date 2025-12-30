# RoutesReader

Overview

`RoutesReader` wraps `sys.routes` and exposes Service Broker route definitions.

Reader SQL

```
SELECT
  r.[Name],
  r.[route_id],
  r.[principal_id],
  r.[remote_service_name],
  r.[broker_instance],
  r.[Lifetime],
  r.[Address],
  r.[mirror_address]
FROM
  [sys].[routes] r
```

Columns and interpretation

- `Name` (string): Name of the route object.
- `route_id` (int): Route identifier.
- `principal_id` (int?): Owner principal for the route.
- `remote_service_name` (string?): Name of the remote service this route targets.
- `broker_instance` (string?): Broker instance name used for addressing.
- `Lifetime` (DateTime?): Lifetime of the route; may indicate expiration.
- `Address` (string?): Address of the remote service broker endpoint.
- `mirror_address` (string?): Mirror address if configured for routing to mirrors.

How to interpret

- Service Broker routes determine where messages for remote services are delivered. `Address` and `broker_instance` are used for network addressing.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = RoutesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new RoutesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Route:{r.Name} RemoteService:{r.RemoteServiceName} Address:{r.Address}");
}
```

See also:

- [sys.routes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-routes)

