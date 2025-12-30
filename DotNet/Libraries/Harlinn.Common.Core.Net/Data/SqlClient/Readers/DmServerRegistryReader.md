# DmServerRegistryReader — reference

Overview

`DmServerRegistryReader` wraps `sys.dm_server_registry` and exposes selected Windows registry values as seen by the SQL Server service.

Reader SQL

```
SELECT
  dsr.[registry_key],
  dsr.[value_name],
  dsr.[value_data]
FROM
  [sys].[dm_server_registry] dsr
```

Columns and interpretation

- `registry_key` — full registry key path.
- `value_name` — name of the registry value under the key.
- `value_data` — the stored value data; type varies (string, numeric, binary) and is returned as SQL variant/object.

How to interpret

- Use to inspect server-specific registry settings that can influence SQL Server behavior; values may include paths, flags and configuration settings.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmServerRegistryReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmServerRegistryReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Key:{r.RegistryKey} Name:{r.ValueName} Data:{r.ValueData}");
}
```

See also:

- [sys.dm_server_registry](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-server-registry)
