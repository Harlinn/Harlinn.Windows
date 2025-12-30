# StatsReader

Overview

`StatsReader` wraps `sys.stats` and exposes statistics objects defined on tables and indexed views.

Reader SQL

```
SELECT
  s4.[object_id],
  s4.[Name],
  s4.[stats_id],
  s4.[auto_created],
  s4.[user_created],
  s4.[no_recompute],
  s4.[has_filter],
  s4.[filter_definition],
  s4.[is_temporary],
  s4.[is_incremental],
  s4.[has_persisted_sample],
  s4.[stats_generation_method],
  s4.[stats_generation_method_desc]
FROM
  [sys].[stats] s4
```

Columns and interpretation

- `object_id` (int): Object id of the table or indexed view the statistics belong to.
- `Name` (string?): Name of the statistics object.
- `stats_id` (int): Identifier of the statistics object.
- `auto_created` (bool?): Whether the statistics were created automatically by the engine.
- `user_created` (bool?): Whether created explicitly by user via CREATE STATISTICS.
- `no_recompute` (bool?): Whether automatic recomputation is disabled.
- `has_filter` (bool?): Whether the statistics are filtered.
- `filter_definition` (string?): The filter predicate if `has_filter` is true.
- `is_temporary` (bool?): Whether statistics are temporary.
- `is_incremental` (bool?): Whether statistics are incremental (for partitioned tables).
- `has_persisted_sample` (bool?): Whether a persisted sample exists.
- `stats_generation_method` (int): Internal code describing how statistics were generated.
- `stats_generation_method_desc` (string): Human-readable description of generation method.

How to interpret

- Use these flags to understand maintenance behavior for statistics. `no_recompute` prevents automatic updates; `is_incremental` applies to partitioned tables.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = StatsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new StatsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Stats:{r.Name} Auto:{r.AutoCreated} NoRecompute:{r.NoRecompute} Filter:{r.FilterDefinition}");
```

See also:

- [sys.stats](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-stats)
