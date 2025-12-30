# HttpEndpointsReader — reference

Overview

`HttpEndpointsReader` wraps `sys.http_endpoints` and returns configuration for HTTP endpoints exposed by SQL Server (used by the HTTP endpoint feature).

Reader SQL

```
SELECT
  he.[Name],
  he.[endpoint_id],
  he.[principal_id],
  he.[Protocol],
  he.[protocol_desc],
  he.[Type],
  he.[type_desc],
  he.[State],
  he.[state_desc],
  he.[is_admin_endpoint],
  he.[Site],
  he.[url_path],
  he.[is_clear_port_enabled],
  he.[clear_port],
  he.[is_ssl_port_enabled],
  he.[ssl_port],
  he.[is_anonymous_enabled],
  he.[is_basic_auth_enabled],
  he.[is_digest_auth_enabled],
  he.[is_kerberos_auth_enabled],
  he.[is_ntlm_auth_enabled],
  he.[is_integrated_auth_enabled],
  he.[authorization_realm],
  he.[default_logon_domain],
  he.[is_compression_enabled]
FROM
  [sys].[http_endpoints] he
```

Columns and interpretation

- `Name` — endpoint name.
- `endpoint_id` — endpoint identifier.
- `principal_id` — principal id owning the endpoint (nullable).
- `Protocol` / `protocol_desc` — protocol code and description (e.g., HTTP/HTTPS).
- `Type` / `type_desc` — endpoint type and description.
- `State` / `state_desc` — state code and description (enabled/disabled).
- `is_admin_endpoint` — whether endpoint is administrative.
- `Site` — site name associated with the endpoint (nullable).
- `url_path` — base URL path for the endpoint (nullable).
- `is_clear_port_enabled` / `clear_port` — whether clear (non-SSL) port is enabled and the port number.
- `is_ssl_port_enabled` / `ssl_port` — whether SSL port is enabled and the port number.
- Authentication flags: `is_anonymous_enabled`, `is_basic_auth_enabled`, `is_digest_auth_enabled`, `is_kerberos_auth_enabled`, `is_ntlm_auth_enabled`, `is_integrated_auth_enabled`.
- `authorization_realm` — realm used for authorization (nullable).
- `default_logon_domain` — default domain used for logon (nullable).
- `is_compression_enabled` — whether response compression is enabled.

How to interpret

- Use to audit HTTP endpoint configuration, enabled ports and authentication modes. Ports and SSL flags indicate whether traffic is encrypted.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = HttpEndpointsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new HttpEndpointsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Endpoint:{r.Name} Id:{r.EndpointId} Protocol:{r.ProtocolDesc} SSL:{r.IsSslPortEnabled} Port:{r.SslPort}");
}
```

See also:

- [sys.http_endpoints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-http-endpoints)
