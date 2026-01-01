# TriggersReader

Overview

`TriggersReader` wraps `sys.triggers` and exposes metadata about triggers defined in the database.

Reader SQL

```
SELECT
  t1.[Name],
  t1.[object_id],
  t1.[parent_class],
  t1.[parent_class_desc],
  t1.[parent_id],
  t1.[Type],
  t1.[type_desc],
  t1.[create_date],
  t1.[modify_date],
  t1.[is_ms_shipped],
  t1.[is_disabled],
  t1.[is_not_for_replication],
  t1.[is_instead_of_trigger]
FROM
  [sys].[triggers] t1
```

Columns and interpretation

- `Name` (sysname): Trigger name.
- `object_id` (int): Object id of the trigger itself.
- `parent_class` (tinyint): Parent class code (indicates whether trigger is DML, DDL, or logon, etc.).
- `parent_class_desc` (nvarchar?): Description of the parent class.
- `parent_id` (int): Object id of the object the trigger is defined on (table, view, database, or server-level depending on parent_class).
- `Type` (nvarchar): Object type code.
- `type_desc` (nvarchar?): Object type description.
- `create_date` (datetime): Creation date.
- `modify_date` (datetime): Last modification date.
- `is_ms_shipped` (bit): Whether the trigger is shipped by Microsoft.
- `is_disabled` (bit): Whether the trigger is disabled.
- `is_not_for_replication` (bit): Whether the trigger is not executed for replication agents.
- `is_instead_of_trigger` (bit): Whether the trigger is an INSTEAD OF trigger.

How to interpret

- Use `parent_id` and `parent_class` to find the object the trigger operates on; for DML triggers `parent_id` is the table/view object id.
- `is_instead_of_trigger` distinguishes INSTEAD OF triggers from AFTER triggers.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TriggersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TriggersReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Trigger:{r.Name} ObjectId:{r.ObjectId} Parent:{r.ParentId} Disabled:{r.IsDisabled} InsteadOf:{r.IsInsteadOfTrigger}");
```

See also:

- [sys.triggers](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-triggers)
