# DmFtsSemanticSimilarityPopulationReader — reference

Overview

`DmFtsSemanticSimilarityPopulationReader` wraps `sys.dm_fts_semantic_similarity_population` and reports progress and status for semantic similarity population operations used by semantic search features.

Reader SQL

```
SELECT
  dfssp.[database_id],
  dfssp.[catalog_id],
  dfssp.[table_id],
  dfssp.[document_count],
  dfssp.[document_processed_count],
  dfssp.[completion_type],
  dfssp.[completion_type_description],
  dfssp.[worker_count],
  dfssp.[Status],
  dfssp.[status_description],
  dfssp.[start_time],
  dfssp.[incremental_timestamp]
FROM
  [sys].[dm_fts_semantic_similarity_population] dfssp
```

Columns and interpretation

- `database_id`, `catalog_id`, `table_id` ? identifiers for the semantic similarity population target.
- `document_count` ? total document count to process.
- `document_processed_count` ? number of documents processed so far.
- `completion_type` / `completion_type_description` ? completion behavior.
- `worker_count` ? number of worker threads assigned.
- `Status` / `status_description` ? numeric and text status for the population.
- `start_time` ? start time of population.
- `incremental_timestamp` ? timestamp token for incremental processing.

How to interpret

- Use `document_processed_count` vs `document_count` to monitor progress.
- `Status` and `StatusDescription` indicate current operational state and errors.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmFtsSemanticSimilarityPopulationReader.Sql;
using var rdr = cmd.ExecuteReader();
var p = new DmFtsSemanticSimilarityPopulationReader(rdr, ownsReader:false);
while (p.Read())
{
    Console.WriteLine($"Catalog:{p.CatalogId} Docs:{p.DocumentProcessedCount}/{p.DocumentCount} Status:{p.StatusDescription} Workers:{p.WorkerCount}");
}
```

See also:

- [sys.dm_fts_semantic_similarity_population](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-fts-semantic-similarity-population)
