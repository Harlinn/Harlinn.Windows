# FulltextIndexColumnsReader — reference

Overview

`FulltextIndexColumnsReader` wraps `sys.fulltext_index_columns` and returns column-level configuration for full-text indexes including the language and type column used for document type identification.

Reader SQL

```
SELECT
  fic.[object_id],
  fic.[column_id],
  fic.[type_column_id],
  fic.[language_id],
  fic.[statistical_semantics]
FROM
  [sys].[fulltext_index_columns] fic
```

Columns and interpretation

- `object_id` — object id of the table containing the full-text column.
- `column_id` — column id of the full-text indexed column.
- `type_column_id` — column id used to store document type information (nullable).
- `language_id` — language id (LCID) used for word breaker and stemmer for the column.
- `statistical_semantics` — numeric flag or code indicating whether statistical semantics are applied to this column for semantic search features.

How to interpret

- `language_id` maps to full-text languages used to process text. `type_column_id` is used when the column stores document type values used by filters.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextIndexColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextIndexColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} Col:{r.ColumnId} Lang:{r.LanguageId} TypeCol:{r.TypeColumnId} Stats:{r.StatisticalSemantics}");
}
```

See also:

- [sys.fulltext_index_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-index-columns)
