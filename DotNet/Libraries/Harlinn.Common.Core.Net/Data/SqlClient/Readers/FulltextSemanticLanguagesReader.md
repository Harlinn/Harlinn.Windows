# FulltextSemanticLanguagesReader — reference

Overview

`FulltextSemanticLanguagesReader` wraps `sys.fulltext_semantic_languages` and returns LCID mappings used by the semantic search components of full-text search.

Reader SQL

```
SELECT
  fsl.[Lcid],
  fsl.[Name]
FROM
  [sys].[fulltext_semantic_languages] fsl
```

Columns and interpretation

- `Lcid` — language code identifier used by semantic search.
- `Name` — name of the semantic language.

How to interpret

- Semantic languages are used by semantic search features for key phrase extraction and meaning-based processing. LCID maps to the language resources used by semantic components.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextSemanticLanguagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextSemanticLanguagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"LCID:{r.Lcid} Name:{r.Name}");
}
```

See also:

- [sys.fulltext_semantic_languages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-semantic-languages)
