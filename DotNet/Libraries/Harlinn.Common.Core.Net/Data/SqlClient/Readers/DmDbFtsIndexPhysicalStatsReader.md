# DmDbFtsIndexPhysicalStatsReader — reference

Overview

`DmDbFtsIndexPhysicalStatsReader` wraps the dynamic management view `sys.dm_db_fts_index_physical_stats` and exposes physical page counts for full-text related indexes for objects in the current database.

Reader SQL

```
SELECT
  ddfips.[object_id],
  ddfips.[fulltext_index_page_count],
  ddfips.[keyphrase_index_page_count],
  ddfips.[similarity_index_page_count]
FROM
  [sys].[dm_db_fts_index_physical_stats] ddfips
```

Columns

- `object_id` ? `ObjectId` (int)
  - Object identifier for the table or view that owns the full-text index. Use `OBJECT_NAME(object_id)` to get the object name.

- `fulltext_index_page_count` ? `FulltextIndexPageCount` (long?)
  - Number of pages used by the full-text index associated with the object. This is the physical page count in the full-text storage for the index. May be NULL if no full-text index exists for the object.

- `keyphrase_index_page_count` ? `KeyphraseIndexPageCount` (long?)
  - Number of pages used by the keyphrase index portion of the full-text index. The keyphrase index supports keyphrase-based searches and may be NULL when not applicable.

- `similarity_index_page_count` ? `SimilarityIndexPageCount` (long?)
  - Number of pages used by the similarity index portion (if supported) used for similarity searches. May be NULL if similarity index not present.

Example

The following example demonstrates querying the view and printing basic, human-readable information.

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbFtsIndexPhysicalStatsReader.Sql;
using var reader = cmd.ExecuteReader();
var ftsReader = new DmDbFtsIndexPhysicalStatsReader(reader, ownsReader: false);
while (ftsReader.Read())
{
    var name = ftsReader.ObjectId; // use OBJECT_NAME to translate if needed
    Console.WriteLine($"ObjectId: {ftsReader.ObjectId}");
    Console.WriteLine($" Full-text pages: {ftsReader.FulltextIndexPageCount ?? 0}");
    Console.WriteLine($" Keyphrase pages: {ftsReader.KeyphraseIndexPageCount ?? 0}");
    Console.WriteLine($" Similarity pages: {ftsReader.SimilarityIndexPageCount ?? 0}");
    Console.WriteLine();
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-fts-index-physical-stats
