# SqlFeatureRestrictionsReader

Overview

`SqlFeatureRestrictionsReader` wraps `sys.sql_feature_restrictions` and exposes features that are restricted for particular database objects or classifications.

Reader SQL

```
SELECT
  sfr.[Class],
  sfr.[Object],
  sfr.[Feature]
FROM
  [sys].[sql_feature_restrictions] sfr
```

Columns and interpretation

- `Class` (string): The feature class that the restriction applies to (category or object type).
- `Object` (string?): The specific object name or identifier the restriction applies to (may be NULL for class-wide restrictions).
- `Feature` (string): The restricted feature name.

How to interpret

- Each row indicates that a named `Feature` is restricted for the given `Class` and optionally for a specific `Object`. Useful when determining why a feature cannot be used in a given context.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SqlFeatureRestrictionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SqlFeatureRestrictionsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Class:{r.Class} Object:{r.Object} Feature:{r.Feature}");
```

See also:

- [sys.sql_feature_restrictions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sql-feature-restrictions)
