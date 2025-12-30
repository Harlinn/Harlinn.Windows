# DmClrPropertiesReader — reference

Overview

`DmClrPropertiesReader` wraps `sys.dm_clr_properties` and exposes CLR-related name/value properties for the SQL instance.

Reader SQL

```
SELECT
  dcp.[Name],
  dcp.[Value]
FROM
  [sys].[dm_clr_properties] dcp
```

Selected columns (property mapping and brief meaning)

- `Name` ? `Name` (string?): Property name.
- `Value` ? `Value` (string?): Property value as text.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmClrPropertiesDataType` objects.

Note

- These are diagnostic properties exposed by CLR integration; contents vary by SQL Server version and CLR configuration.
