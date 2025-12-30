# BackupDevicesReader — reference

Overview

`BackupDevicesReader` wraps `sys.backup_devices` and exposes configured backup devices known to the instance.

Reader SQL

```
SELECT
  bd.[Name],
  bd.[Type],
  bd.[type_desc],
  bd.[physical_name]
FROM
  [sys].[backup_devices] bd
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - Logical name of the backup device.

- `Type` ? property: `Type` (byte?)
  - Numeric device type code.

- `type_desc` ? property: `TypeDesc` (string?)
  - Description of the device type (e.g. DISK, TAPE).

- `physical_name` ? property: `PhysicalName` (string?)
  - Physical path or identifier for the device.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.BackupDevicesDataType` objects.
