# PeriodsReader — reference

Overview

`PeriodsReader` wraps `sys.periods` and returns information about system-period definitions (temporal table periods), including start and end column ids.

Reader SQL

```
SELECT
  p.[Name],
  p.[period_type],
  p.[period_type_desc],
  p.[object_id],
  p.[start_column_id],
  p.[end_column_id]
FROM
  [sys].[periods] p
```

Columns and interpretation

- `Name` — period name (nullable).
- `period_type` / `period_type_desc` — internal code and description of period type.
- `object_id` — object id of the object that defines the period (typically a table).
- `start_column_id` / `end_column_id` — column ids that define the system time period (start and end columns).

How to interpret

- Temporal tables use PERIOD FOR SYSTEM_TIME defined on two datetime columns. Use this view to find the column ids that represent the period bounds.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = PeriodsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new PeriodsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Period:{r.Name} Obj:{r.ObjectId} StartCol:{r.StartColumnId} EndCol:{r.EndColumnId}");
}
```

See also:

- [sys.periods](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-periods)
