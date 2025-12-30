# SecurityPredicatesReader

Overview

`SecurityPredicatesReader` wraps `sys.security_predicates` and exposes predicate metadata used by row- or column-level security predicates.

Reader SQL

```
SELECT
  sp.[object_id],
  sp.[security_predicate_id],
  sp.[target_object_id],
  sp.[predicate_definition],
  sp.[predicate_type],
  sp.[predicate_type_desc],
  sp.[Operation],
  sp.[operation_desc]
FROM
  [sys].[security_predicates] sp
```

Columns and interpretation

- `object_id` (int): Object id of the security predicate object.
- `security_predicate_id` (int): Unique identifier for the predicate row.
- `target_object_id` (int): Object id of the target object (table/view) the predicate applies to.
- `predicate_definition` (string?): T-SQL expression text that defines the predicate (e.g., WHERE clause expression used by the security predicate).
- `predicate_type` (int?): Numeric code for predicate type; use `predicate_type_desc` for human-readable type (e.g., FILTER, BLOCK).
- `predicate_type_desc` (string?): Description of the predicate type.
- `Operation` (int?): Numeric code for the operation the predicate applies to (select/insert/update/delete); `operation_desc` provides readable name.
- `operation_desc` (string?): Text description of operation (e.g., SELECT, INSERT).

How to interpret

- Each row ties a predicate definition to a target object and operation. Use `target_object_id` to join `sys.objects` for object names.
- `predicate_definition` is the actual logic applied to enforce security; read it carefully before relying on it for access decisions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SecurityPredicatesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SecurityPredicatesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Target:{r.TargetObjectId} Operation:{r.OperationDesc} Predicate:{r.PredicateDefinition}");
```

See also:

- [sys.security_predicates](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-security-predicates-transact-sql)

