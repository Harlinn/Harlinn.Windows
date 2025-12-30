# EndpointWebmethodsReader — reference

Overview

`EndpointWebmethodsReader` wraps `sys.endpoint_webmethods` and returns configuration for web methods exposed by HTTP endpoints including aliases and result formats.

Reader SQL

```
SELECT
  ew.[endpoint_id],
  ew.[Namespace],
  ew.[method_alias],
  ew.[object_name],
  ew.[result_schema],
  ew.[result_schema_desc],
  ew.[result_format],
  ew.[result_format_desc]
FROM
  [sys].[endpoint_webmethods] ew
```

Columns and interpretation

- `endpoint_id` — endpoint id hosting the web method.
- `Namespace` — optional namespace bound to the method (nullable).
- `method_alias` — alias used to invoke the method.
- `object_name` — underlying object (stored procedure) name executed by the web method (nullable).
- `result_schema` / `result_schema_desc` — numeric code and description of the result schema type.
- `result_format` / `result_format_desc` — numeric code and description of the result format (XML, JSON, etc.).

How to interpret

- Use to map HTTP endpoint exposed method aliases to database objects and understand response formatting.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = EndpointWebmethodsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new EndpointWebmethodsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Endpoint:{r.EndpointId} Alias:{r.MethodAlias} Object:{r.ObjectName} Format:{r.ResultFormatDesc}");
}
```

See also:

- [sys.endpoint_webmethods](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-endpoint-webmethods)
