# EdgeConstraintClausesReader — reference

Overview

`EdgeConstraintClausesReader` wraps `sys.edge_constraint_clauses` and returns the mapping between an edge constraint and the object ids defining the from/to boundaries in graph tables.

Reader SQL

```
SELECT
  ecc.[object_id],
  ecc.[clause_number],
  ecc.[from_object_id],
  ecc.[to_object_id]
FROM
  [sys].[edge_constraint_clauses] ecc
```

Columns and interpretation

- `object_id` — object id of the edge constraint definition.
- `clause_number` — ordinal number of the clause within the constraint.
- `from_object_id` — object id of the 'from' node/table referenced by the constraint.
- `to_object_id` — object id of the 'to' node/table referenced by the constraint.

How to interpret

- Use to inspect graph edge constraints to see which node tables are allowed as endpoints for edges.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = EdgeConstraintClausesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new EdgeConstraintClausesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"ConstraintObj:{r.ObjectId} Clause:{r.ClauseNumber} From:{r.FromObjectId} To:{r.ToObjectId}");
}
```

See also:

- [sys.edge_constraint_clauses](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-edge-constraint-clauses)
