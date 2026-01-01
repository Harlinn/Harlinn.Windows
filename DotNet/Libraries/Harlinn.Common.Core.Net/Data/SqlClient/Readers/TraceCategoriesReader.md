# TraceCategoriesReader

Overview

`TraceCategoriesReader` wraps the `sys.trace_categories` catalog view that lists trace event categories (groupings of trace events).

Reader SQL

```
SELECT
  tc0.[category_id],
  tc0.[Name],
  tc0.[Type]
FROM
  [sys].[trace_categories] tc0
```

Columns and interpretation

- `category_id` (smallint): Numeric identifier for the trace category. Use this to group or filter trace events by category.
- `Name` (nvarchar): Human readable name of the category.
- `Type` (tinyint): Type code for category; internal code indicating category classification.

How to interpret

- Join `category_id` with `sys.trace_events` rows to get event names for a category.
- `Type` is an internal classification; treat as opaque unless mapping is required.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TraceCategoriesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TraceCategoriesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"CategoryId:{r.CategoryId} Name:{r.Name} Type:{r.Type}");
```

See also:

- [sys.trace_categories](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-trace-categories)
