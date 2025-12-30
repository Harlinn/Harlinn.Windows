# FulltextStoplistsReader — reference

Overview

`FulltextStoplistsReader` wraps `sys.fulltext_stoplists` and returns metadata about stoplists used by full-text indexes, including creation/modify dates and owner.

Reader SQL

```
SELECT
  fs0.[stoplist_id],
  fs0.[Name],
  fs0.[create_date],
  fs0.[modify_date],
  fs0.[principal_id]
FROM
  [sys].[fulltext_stoplists] fs0
```

Columns and interpretation

- `stoplist_id` — id of the stoplist.
- `Name` — stoplist name.
- `create_date` / `modify_date` — timestamps.
- `principal_id` — principal id owner (nullable).

How to interpret

- Stoplists define stopwords for full-text indexing; this view lists available stoplists and ownership.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextStoplistsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextStoplistsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Stoplist:{r.Name} Id:{r.StoplistId} Created:{r.CreateDate} Modified:{r.ModifyDate}");
}
```

See also:

- [sys.fulltext_stoplists](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-stoplists)
