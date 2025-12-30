# PlanGuidesReader — reference

Overview

`PlanGuidesReader` wraps `sys.plan_guides` and returns information about plan guides that force query hints or plans for specific statements.

Reader SQL

```
SELECT
  pg.[plan_guide_id],
  pg.[Name],
  pg.[create_date],
  pg.[modify_date],
  pg.[is_disabled],
  pg.[query_text],
  pg.[scope_type],
  pg.[scope_type_desc],
  pg.[scope_object_id],
  pg.[scope_batch],
  pg.[Parameters],
  pg.[Hints]
FROM
  [sys].[plan_guides] pg
```

Columns and interpretation

- `plan_guide_id` — unique id for the plan guide.
- `Name` — plan guide name.
- `create_date` / `modify_date` — timestamps.
- `is_disabled` — whether the plan guide is disabled.
- `query_text` — the targeted query text the plan guide applies to (nullable).
- `scope_type` / `scope_type_desc` — scope type (e.g., OBJECT, SQL) and description.
- `scope_object_id` — object id when scope applies to an object.
- `scope_batch` — batch text when scope is batch-scoped (nullable).
- `Parameters` — parameter list used for matching (nullable).
- `Hints` — hints or the XML plan used by the guide.

How to interpret

- Plan guides can force hints or plans for matching query text. Use `is_disabled` and `Hints` to see active guides and their enforced hints.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = PlanGuidesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new PlanGuidesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"PlanGuide:{r.Name} Id:{r.PlanGuideId} Disabled:{r.IsDisabled} Scope:{r.ScopeTypeDesc}");
}
```

See also:

- [sys.plan_guides](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-plan-guides)
