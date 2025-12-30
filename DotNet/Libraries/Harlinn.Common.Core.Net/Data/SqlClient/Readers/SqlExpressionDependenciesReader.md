# SqlExpressionDependenciesReader

Overview

`SqlExpressionDependenciesReader` wraps `sys.sql_expression_dependencies` and exposes dependencies found inside SQL expressions (views, computed columns, functions, etc.).

Reader SQL

```
SELECT
  sed.[referencing_id],
  sed.[referencing_minor_id],
  sed.[referencing_class],
  sed.[referencing_class_desc],
  sed.[is_schema_bound_reference],
  sed.[referenced_class],
  sed.[referenced_class_desc],
  sed.[referenced_server_name],
  sed.[referenced_database_name],
  sed.[referenced_schema_name],
  sed.[referenced_entity_name],
  sed.[referenced_id],
  sed.[referenced_minor_id],
  sed.[is_caller_dependent],
  sed.[is_ambiguous]
FROM
  [sys].[sql_expression_dependencies] sed
```

Columns and interpretation

- `referencing_id`, `referencing_minor_id` (int): Object and minor id (e.g., column) that contains the expression.
- `referencing_class`, `referencing_class_desc` (byte/string?): Class code and description for the referencing object.
- `is_schema_bound_reference` (bool): True when the reference is schema-bound.
- `referenced_class`, `referenced_class_desc` (byte/string?): Class code and description for the referenced object.
- `referenced_server_name`, `referenced_database_name`, `referenced_schema_name`, `referenced_entity_name` (string?): Names for the referenced object; may be NULL for local references.
- `referenced_id`, `referenced_minor_id` (int?): Object and minor ids of the referenced object.
- `is_caller_dependent` (bool): True when evaluation depends on the caller context.
- `is_ambiguous` (bool): True when the reference could map to multiple objects (e.g., same name in multiple schemas without qualification).

How to interpret

- This view is useful for detailed dependency analysis; schema-bound references prevent dropping or altering referenced objects without updating dependents.
- `is_ambiguous` warns when referenced names are not fully qualified and could resolve differently.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SqlExpressionDependenciesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SqlExpressionDependenciesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Ref:{r.ReferencingId}.{r.ReferencingMinorId} -> {r.ReferencedDatabaseName}.{r.ReferencedSchemaName}.{r.ReferencedEntityName} SchemaBound:{r.IsSchemaBoundReference}");
```

See also:

- [sys.sql_expression_dependencies](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sql-expression-dependencies)
