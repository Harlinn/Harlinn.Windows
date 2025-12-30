# FulltextSemanticLanguageStatisticsDatabaseReader — reference

Overview

`FulltextSemanticLanguageStatisticsDatabaseReader` wraps `sys.fulltext_semantic_language_statistics_database` and returns registration metadata for semantic language statistics in the database.

Reader SQL

```
SELECT
  fslsd.[database_id],
  fslsd.[register_date],
  fslsd.[registered_by],
  fslsd.[Version]
FROM
  [sys].[fulltext_semantic_language_statistics_database] fslsd
```

Columns and interpretation

- `database_id` — database id where semantic language statistics are registered.
- `register_date` — date/time when the semantic language statistics were registered.
- `registered_by` — principal id that performed the registration.
- `Version` — version string of the registered statistics.

How to interpret

- Indicates whether semantic language statistics (used by semantic search) are registered and when; useful for audit and compatibility checks.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextSemanticLanguageStatisticsDatabaseReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextSemanticLanguageStatisticsDatabaseReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DatabaseId} Registered:{r.RegisterDate} By:{r.RegisteredBy} Version:{r.Version}");
}
```

See also:

- [sys.fulltext_semantic_language_statistics_database](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-semantic-language-statistics-database)
