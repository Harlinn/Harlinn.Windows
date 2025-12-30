# RemoteServiceBindingsReader

Overview

`RemoteServiceBindingsReader` wraps `sys.remote_service_bindings` and exposes bindings for remote service broker services.

Reader SQL

```
SELECT
  rsb.[Name],
  rsb.[remote_service_binding_id],
  rsb.[principal_id],
  rsb.[remote_service_name],
  rsb.[service_contract_id],
  rsb.[remote_principal_id],
  rsb.[is_anonymous_on]
FROM
  [sys].[remote_service_bindings] rsb
```

Columns and interpretation

- `Name` (string): Name of the remote service binding object.
- `remote_service_binding_id` (int): Unique id of the binding.
- `principal_id` (int?): Owning principal id, if any.
- `remote_service_name` (string?): Name of the remote service.
- `service_contract_id` (int): Identifier of the service contract associated.
- `remote_principal_id` (int?): Remote principal id if specified.
- `is_anonymous_on` (bool): Whether anonymous access is allowed by this binding.

How to interpret

- Use these rows to inspect Service Broker remote bindings and their permissions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = RemoteServiceBindingsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new RemoteServiceBindingsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Binding:{r.Name} RemoteService:{r.RemoteServiceName} Anonymous:{r.IsAnonymousOn}");
}
```

See also:

- [sys.remote_service_bindings](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-remote-service-bindings)

