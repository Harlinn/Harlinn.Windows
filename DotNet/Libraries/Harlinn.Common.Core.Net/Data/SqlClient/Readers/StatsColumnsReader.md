# StatsColumnsReader

Overview

`StatsColumnsReader` wraps `sys.stats_columns` and exposes which columns belong to a particular statistics object.

Reader SQL

```
SELECT
  sc2.[object_id],
  sc2.[stats_id],
  sc2.[stats_column_id],
  sc2.[column_id]
FROM
  [sys].[stats_columns] sc2
```

Columns and interpretation

- `object_id` (int): Object id of the table or indexed view the statistics belong to.
- `stats_id` (int): Identifier of the statistics object.
- `stats_column_id` (int?): Ordinal position of the column within the statistics object.
- `column_id` (int?): Column id within the table.

How to interpret

- Join to `sys.stats` and `sys.columns` using `object_id` and `column_id` to find human-readable names and statistic properties.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = StatsColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new StatsColumnsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Object:{r.ObjectId} Stats:{r.StatsId} Column:{r.ColumnId} (pos:{r.StatsColumnId})");
```

See also:

- [sys.stats_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-stats-columns)
