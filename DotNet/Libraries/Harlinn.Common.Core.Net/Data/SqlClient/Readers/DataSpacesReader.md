# DataSpacesReader — reference

Overview

`DataSpacesReader` wraps `sys.data_spaces` and exposes named data spaces (filegroups, partition schemes) defined in the database.

Reader SQL

```
SELECT
  ds.[Name],
  ds.[data_space_id],
  ds.[Type],
  ds.[type_desc],
  ds.[is_default],
  ds.[is_system]
FROM
  [sys].[data_spaces] ds
```

Selected columns (property mapping and brief meaning)

- `Name` ? `Name` (string): Logical name of the data space (filegroup or partition scheme).
- `data_space_id` ? `DataSpaceId` (int): Identifier of the data space.
- `Type` ? `Type` (string): Type code for the data space.
- `type_desc` ? `TypeDesc` (string?): Descriptive text for the data space type.
- `is_default` ? `IsDefault` (bool): Indicates default data space for new objects.
- `is_system` ? `IsSystem` (bool?): Whether this is a system-defined data space.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DataSpacesDataType` objects.
