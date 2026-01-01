# TriggerEventTypesReader

Overview

`TriggerEventTypesReader` wraps `sys.trigger_event_types` and provides mappings of trigger event type codes to names and parent relationships.

Reader SQL

```
SELECT
  tet.[Type],
  tet.[type_name],
  tet.[parent_type]
FROM
  [sys].[trigger_event_types] tet
```

Columns and interpretation

- `Type` (int): Numeric code representing the trigger event type.
- `type_name` (nvarchar): Human readable name of the trigger event type.
- `parent_type` (int?): Numeric code for a parent type if this type is a specialization.

How to interpret

- Use `type_name` to display or configure triggers; `parent_type` helps form a hierarchy of event types when present.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TriggerEventTypesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TriggerEventTypesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Type:{r.Type} Name:{r.TypeName} Parent:{r.ParentType}");
```

See also:

- [sys.trigger_event_types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-trigger-event-types)
