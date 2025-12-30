# EndpointsReader — reference

Overview

`EndpointsReader` wraps `sys.endpoints` and returns configuration and state for SQL Server network and service endpoints, including protocol, type and administrative endpoints.

Reader SQL

```
SELECT
  e1.[Name],
  e1.[endpoint_id],
  e1.[principal_id],
  e1.[Protocol],
  e1.[protocol_desc],
  e1.[Type],
  e1.[type_desc],
  e1.[State],
  e1.[state_desc],
  e1.[is_admin_endpoint]
FROM
  [sys].[endpoints] e1
```

Columns and interpretation

- `Name` — endpoint name.
- `endpoint_id` — numeric id for the endpoint.
- `principal_id` — principal id owning the endpoint (nullable).
- `Protocol` / `protocol_desc` — numeric code and textual protocol (e.g., TCP, HTTP, SOAP).
- `Type` / `type_desc` — endpoint type and description (DATABASE_MIRRORING, SERVICE_BROKER, etc.).
- `State` / `state_desc` — operational state of the endpoint (STARTED, STOPPED).
- `is_admin_endpoint` — flag indicating whether the endpoint is an administrative endpoint (management-only).

How to interpret

- Use when diagnosing connectivity or service binding issues; admin endpoints are restricted for management.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = EndpointsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new EndpointsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Endpoint:{r.Name} Id:{r.EndpointId} Protocol:{r.ProtocolDesc} Type:{r.TypeDesc} State:{r.StateDesc} Admin:{r.IsAdminEndpoint}");
}
```

See also:

- [sys.endpoints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-endpoints)
