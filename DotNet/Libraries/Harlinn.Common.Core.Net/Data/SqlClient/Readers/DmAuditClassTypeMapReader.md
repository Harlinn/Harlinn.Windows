# DmAuditClassTypeMapReader — reference

Overview

`DmAuditClassTypeMapReader` wraps `sys.dm_audit_class_type_map` and exposes mapping between audit class types and securable classes.

Reader SQL

```
SELECT
  dactm.[class_type],
  dactm.[class_type_desc],
  dactm.[securable_class_desc]
FROM
  [sys].[dm_audit_class_type_map] dactm
```

Selected columns (property mapping and brief meaning)

- `class_type` ? `ClassType` (string?): Audit class type code.
- `class_type_desc` ? `ClassTypeDesc` (string?): Description of the class type.
- `securable_class_desc` ? `SecurableClassDesc` (string?): Description of securable class associated with the class type.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmAuditClassTypeMapDataType` objects.
