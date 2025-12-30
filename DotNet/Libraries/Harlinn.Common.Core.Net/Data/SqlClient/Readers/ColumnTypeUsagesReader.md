# ColumnTypeUsagesReader — reference

Overview

`ColumnTypeUsagesReader` wraps `sys.column_type_usages` and exposes usages of user-defined types by columns.

Reader SQL

```
SELECT sctu.[object_id]
      ,sctu.[column_id]
      ,sctu.[user_type_id]
FROM [sys].[column_type_usages] sctu
```

Selected columns (method mapping and brief meaning)

- `object_id` ? `GetObjectId()` (int): Object id containing the column.
- `column_id` ? `GetColumnId()` (int): Column id within the object.
- `user_type_id` ? `GetUserTypeId()` (int): User-defined type id used by the column (references `sys.types`).

Helpers

- `GetColumnTypeUsage()` returns a `ColumnTypeUsage` instance for the current row.
- `GetColumnTypeUsages()` reads all rows and returns a list.
