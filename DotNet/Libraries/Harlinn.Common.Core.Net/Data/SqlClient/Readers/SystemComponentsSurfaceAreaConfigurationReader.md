# SystemComponentsSurfaceAreaConfigurationReader

Overview

`SystemComponentsSurfaceAreaConfigurationReader` wraps `sys.system_components_surface_area_configuration` and exposes surface-area configuration settings for system components.

Reader SQL

```
SELECT
  scsac.[component_name],
  scsac.[database_name],
  scsac.[schema_name],
  scsac.[object_name],
  scsac.[State],
  scsac.[Type],
  scsac.[type_desc]
FROM
  [sys].[system_components_surface_area_configuration] scsac
```

Columns and interpretation

- `component_name` (string?): Name of the system component.
- `database_name` (string?): Database name the setting applies to (NULL for server-level components).
- `schema_name` (string?): Schema name the setting applies to (if applicable).
- `object_name` (string): Object name the setting applies to.
- `State` (tinyint?): State code representing whether the surface is enabled/disabled.
- `Type` (string): Component type code.
- `type_desc` (string?): Human-readable description of the component type.

How to interpret

- Use these rows to inspect server and database surface-area controls (features that can be enabled or disabled for security or compatibility).
- `State` often encodes enabled/disabled status; consult SQL Server surface area documentation for specific codes.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemComponentsSurfaceAreaConfigurationReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemComponentsSurfaceAreaConfigurationReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Component:{r.ComponentName} Object:{r.ObjectName} State:{r.State} Type:{r.Type} Desc:{r.TypeDesc}");
```

See also:

- [sys.system_components_surface_area_configuration](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-components-surface-area-configuration)
