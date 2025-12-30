# DatabaseScopedConfigurationsReader — reference

Overview

`DatabaseScopedConfigurationsReader` wraps `sys.database_scoped_configurations` and exposes database-level scoped configuration values.

Reader SQL

```
SELECT
  dsc.[configuration_id],
  dsc.[Name],
  dsc.[Value],
  dsc.[value_for_secondary],
  dsc.[is_value_default]
FROM
  [sys].[database_scoped_configurations] dsc
```

Selected columns (property mapping and brief meaning)

- `configuration_id` ? `ConfigurationId` (int?): Identifier of the configuration option.
- `Name` ? `Name` (string?): Configuration name.
- `Value` ? `Value` (object?): Current value for primary.
- `value_for_secondary` ? `ValueForSecondary` (object?): Value applied to secondary replicas if applicable.
- `is_value_default` ? `IsValueDefault` (bool?): Indicates whether the value is the default.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseScopedConfigurationsDataType` objects.
