# FulltextLanguagesReader — reference

Overview

`FulltextLanguagesReader` wraps `sys.fulltext_languages` and returns LCID mappings used by full-text search for language-specific processing.

Reader SQL

```
SELECT
  fl.[Lcid],
  fl.[Name]
FROM
  [sys].[fulltext_languages] fl
```

Columns and interpretation

- `Lcid` — language code identifier used by SQL Server's full-text engine.
- `Name` — language name corresponding to the LCID (e.g., `English`).

How to interpret

- Language LCIDs determine word breaking, stemming and stoplists used when indexing text. Use LCID to correlate language settings in full-text index columns.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextLanguagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextLanguagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"LCID:{r.Lcid} Name:{r.Name}");
}
```

See also:

- [sys.fulltext_languages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-languages)
