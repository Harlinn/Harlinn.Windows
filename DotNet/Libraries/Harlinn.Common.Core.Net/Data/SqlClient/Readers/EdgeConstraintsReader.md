# EdgeConstraintsReader — reference

Overview

`EdgeConstraintsReader` wraps `sys.edge_constraints` and returns metadata about graph edge constraints, including referential actions and publish flags.

Reader SQL

```
SELECT
  ec.[Name],
  ec.[object_id],
  ec.[principal_id],
  ec.[schema_id],
  ec.[parent_object_id],
  ec.[Type],
  ec.[type_desc],
  ec.[create_date],
  ec.[modify_date],
  ec.[is_ms_shipped],
  ec.[is_published],
  ec.[is_schema_published],
  ec.[is_disabled],
  ec.[is_not_trusted],
  ec.[is_system_named],
  ec.[delete_referential_action],
  ec.[delete_referential_action_desc]
FROM
  [sys].[edge_constraints] ec
```

Columns and interpretation

- `Name` — name of the edge constraint.
- `object_id` — object id of the constraint.
- `principal_id` — owner principal id (nullable).
- `schema_id` — schema id where the constraint is defined.
- `parent_object_id` — object id of the parent object (table) the constraint belongs to.
- `Type` / `type_desc` — type code and description.
- `create_date` / `modify_date` — timestamps for creation and modification.
- `is_ms_shipped`, `is_published`, `is_schema_published` — flags describing origin and publication/publishing status.
- `is_disabled` — whether the constraint is disabled.
- `is_not_trusted` — whether the constraint is not trusted by the optimizer (e.g., not validated).
- `is_system_named` — whether SQL Server assigned the name automatically.
- `delete_referential_action` / `delete_referential_action_desc` — referential action on delete (numeric code and description), e.g., NO_ACTION, CASCADE, SET_NULL.

How to interpret

- Check `delete_referential_action_desc` to understand cascade behavior when nodes are deleted.
- `is_not_trusted` indicates the constraint may not guarantee referential integrity for query optimization.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = EdgeConstraintsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new EdgeConstraintsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Constraint:{r.Name} Obj:{r.ObjectId} Parent:{r.ParentObjectId} DeleteAction:{r.DeleteReferentialActionDesc}");
}
```

See also:

- [sys.edge_constraints](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-edge-constraints)
