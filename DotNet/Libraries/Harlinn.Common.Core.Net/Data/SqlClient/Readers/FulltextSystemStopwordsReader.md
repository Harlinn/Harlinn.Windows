# FulltextSystemStopwordsReader — reference

Overview

`FulltextSystemStopwordsReader` wraps `sys.fulltext_system_stopwords` and returns the built-in (system) stopwords used by the full-text engine for different languages.

Reader SQL

```
SELECT
  fss.[Stopword],
  fss.[language_id]
FROM
  [sys].[fulltext_system_stopwords] fss
```

Columns and interpretation

- `Stopword` — the stopword (word that is ignored during full-text indexing) as text. May be NULL for unusual entries.
- `language_id` — LCID (locale identifier) representing the language the stopword applies to. Use this to map stopwords to language-specific indexing behavior.

How to interpret

- System stopwords are global to the SQL Server instance and are used by full-text indexes when a stoplist references the system stoplist. Use `language_id` to select stopwords appropriate for a language.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextSystemStopwordsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextSystemStopwordsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"LCID:{r.LanguageId} Stopword:{r.Stopword}");
}
```

See also:

- [sys.fulltext_system_stopwords](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-system-stopwords)
