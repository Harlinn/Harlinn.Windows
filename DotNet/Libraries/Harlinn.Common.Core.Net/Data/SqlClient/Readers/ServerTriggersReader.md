# ServerTriggersReader

Overview

`ServerTriggersReader` wraps `sys.server_triggers` and exposes server-scoped trigger metadata.

Reader SQL

```
SELECT
  st.[Name],
  st.[object_id],
  st.[parent_class],
  st.[parent_class_desc],
  st.[parent_id],
  st.[Type],
  st.[type_desc],
  st.[create_date],
  st.[modify_date],
  st.[is_ms_shipped],
  st.[is_disabled]
FROM
  [sys].[server_triggers] st
```

Columns and interpretation

- `Name` (string): Trigger name.
- `object_id` (int): Object id of the trigger.
- `parent_class` (byte): Parent class code indicating the level the trigger applies to (server, database, etc.).
- `parent_class_desc` (string?): Description of the parent class.
- `parent_id` (int): Parent object id.
- `Type`, `type_desc` (string/string?): Trigger type code and description.
- `create_date`, `modify_date` (DateTime): Timestamps.
- `is_ms_shipped` (bool): Whether the trigger is shipped by Microsoft.
- `is_disabled` (bool): Whether the trigger is disabled.

How to interpret

- Use `parent_class` and `parent_id` to map the trigger to the object it is attached to. `is_disabled` indicates whether the trigger is active.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerTriggersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerTriggersReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Trigger:{r.Name} ParentClass:{r.ParentClassDesc} Disabled:{r.IsDisabled}");
```

See also:

- [sys.server_triggers](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-triggers)
