# ProceduresReader — reference

Overview

`ProceduresReader` wraps `sys.procedures` and returns metadata about stored procedures, including ownership, schema and replication flags.

Reader SQL

```
SELECT sp.[name]
      ,sp.[object_id]
      ,sp.[principal_id]
      ,sp.[schema_id]
      ,sp.[parent_object_id]
      ,sp.[type]
      ,sp.[type_desc]
      ,sp.[create_date]
      ,sp.[modify_date]
      ,sp.[is_ms_shipped]
      ,sp.[is_published]
      ,sp.[is_schema_published]
      ,sp.[is_auto_executed]
      ,sp.[is_execution_replicated]
      ,sp.[is_repl_serializable_only]
      ,sp.[skips_repl_constraints]
  FROM [sys].[procedures] sp
```

Columns and interpretation

- `name`, `object_id` — procedure name and object id.
- `principal_id`, `schema_id`, `parent_object_id` — owner, schema and parent object id.
- `type` / `type_desc` — object type and description.
- `create_date` / `modify_date` — timestamps.
- `is_ms_shipped`, `is_published`, `is_schema_published` — metadata flags.
- Execution/replication flags: `is_auto_executed`, `is_execution_replicated`, `is_repl_serializable_only`, `skips_repl_constraints`.

How to interpret

- Use to inventory procedures and inspect replication/auto-execution behavior. `parent_object_id` can indicate linked object context.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ProceduresReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ProceduresReader(rdr, ownsReader:false);
while (r.Read())
{
    var p = r.GetProcedure();
    Console.WriteLine($"Proc:{p.Name} Obj:{p.ObjectId} SchemaId:{p.SchemaId} Replicated:{p.IsExecutionReplicated}");
}
```

See also:

- [sys.procedures](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-procedures)
