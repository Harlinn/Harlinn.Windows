# FulltextStopwordsReader — reference

Overview

`FulltextStopwordsReader` wraps `sys.fulltext_stopwords` and returns stopwords that are part of stoplists for full-text indexing.

Reader SQL

```
SELECT
  fs.[stoplist_id],
  fs.[Stopword],
  fs.[Language],
  fs.[language_id]
FROM
  [sys].[fulltext_stopwords] fs
```

Columns and interpretation

- `stoplist_id` — id of the stoplist containing the stopword.
- `Stopword` — the stopword string.
- `Language` — textual language name for which the stopword applies.
- `language_id` — LCID of the language.

How to interpret

- Stopwords are ignored during full-text indexing and searching; this view lists stopwords by language and stoplist.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextStopwordsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextStopwordsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Stoplist:{r.StoplistId} Lang:{r.Language} LCID:{r.LanguageId} Word:{r.Stopword}");
}
```

See also:

- [sys.fulltext_stopwords](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-stopwords)
