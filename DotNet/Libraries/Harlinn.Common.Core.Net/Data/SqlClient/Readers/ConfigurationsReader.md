# ConfigurationsReader — reference

Overview

`ConfigurationsReader` wraps `sys.configurations` and exposes server configuration options and their current values.

Reader SQL

```
SELECT
  c2.[configuration_id],
  c2.[Name],
  c2.[Value],
  c2.[Minimum],
  c2.[Maximum],
  c2.[value_in_use],
  c2.[Description],
  c2.[is_dynamic],
  c2.[is_advanced]
FROM
  [sys].[configurations] c2
```

Selected columns (property mapping and brief meaning)

- `configuration_id` ? `ConfigurationId` (int): Unique id of the configuration option.
- `Name` ? `Name` (string): Configuration option name.
- `Value` ? `Value` (object?): Current configured value (may be different type depending on option).
- `Minimum` ? `Minimum` (object?): Minimum permitted value for the option.
- `Maximum` ? `Maximum` (object?): Maximum permitted value for the option.
- `value_in_use` ? `ValueInUse` (object?): Effective value currently in use by the server.
- `Description` ? `Description` (string): Human readable description of the option.
- `is_dynamic` ? `IsDynamic` (bool): Whether the option can be changed without restarting the server.
- `is_advanced` ? `IsAdvanced` (bool): Whether the option is an advanced configuration option.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.ConfigurationsDataType` objects.
