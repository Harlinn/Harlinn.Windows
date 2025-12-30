# SoapEndpointsReader

Overview

`SoapEndpointsReader` wraps `sys.soap_endpoints` and exposes SOAP endpoint configurations (deprecated in recent SQL Server versions).

Reader SQL

```
SELECT
  se0.[Name],
  se0.[endpoint_id],
  se0.[principal_id],
  se0.[Protocol],
  se0.[protocol_desc],
  se0.[Type],
  se0.[type_desc],
  se0.[State],
  se0.[state_desc],
  se0.[is_admin_endpoint],
  se0.[is_sql_language_enabled],
  se0.[wsdl_generator_procedure],
  se0.[default_database],
  se0.[default_namespace],
  se0.[default_result_schema],
  se0.[default_result_schema_desc],
  se0.[is_xml_charset_enforced],
  se0.[is_session_enabled],
  se0.[session_timeout],
  se0.[login_type],
  se0.[header_limit]
FROM
  [sys].[soap_endpoints] se0
```

Columns and interpretation

- `Name` (string): Endpoint name.
- `endpoint_id` (int): Endpoint identifier.
- `principal_id` (int?): Principal id for the endpoint.
- `Protocol`, `protocol_desc` (byte/string?): Protocol code and description.
- `Type`, `type_desc` (byte/string?): Endpoint type and description.
- `State`, `state_desc` (byte/string?): State and description.
- `is_admin_endpoint` (bool): Whether the endpoint is administrative.
- `is_sql_language_enabled` (bool): Whether SQL language over SOAP is enabled.
- `wsdl_generator_procedure` (string?): Procedure that generates WSDL for the endpoint.
- `default_database`, `default_namespace` (string?): Default database and XML namespace for the endpoint.
- `default_result_schema`, `default_result_schema_desc` (byte/string?): Default result schema type and description.
- `is_xml_charset_enforced` (bool): Whether XML charset is enforced.
- `is_session_enabled` (bool): Whether SOAP sessions are enabled.
- `session_timeout` (int): Session timeout in seconds.
- `login_type` (string?): Login type used for endpoint connections.
- `header_limit` (int): Limit for SOAP headers.

How to interpret

- SOAP endpoints are legacy; many environments will not have entries. Use `wsdl_generator_procedure` to locate service definitions and `is_session_enabled` to determine sessionized behavior.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SoapEndpointsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SoapEndpointsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"SoapEndpoint:{r.Name} Session:{r.IsSessionEnabled} WSDLProc:{r.WsdlGeneratorProcedure}");
```

See also:

- [sys.soap_endpoints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-soap-endpoints)
