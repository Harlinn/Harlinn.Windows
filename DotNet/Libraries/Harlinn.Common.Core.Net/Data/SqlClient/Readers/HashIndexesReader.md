# HashIndexesReader — reference

Overview

`HashIndexesReader` wraps `sys.hash_indexes` and returns metadata about hash indexes (used by memory-optimized tables), including bucket count, filter, and index options.

Reader SQL

```
SELECT
  hi.[object_id],
  hi.[Name],
  hi.[index_id],
  hi.[Type],
  hi.[type_desc],
  hi.[is_unique],
  hi.[data_space_id],
  hi.[ignore_dup_key],
  hi.[is_primary_key],
  hi.[is_unique_constraint],
  hi.[fill_factor],
  hi.[is_padded],
  hi.[is_disabled],
  hi.[is_hypothetical],
  hi.[is_ignored_in_optimization],
  hi.[allow_row_locks],
  hi.[allow_page_locks],
  hi.[has_filter],
  hi.[filter_definition],
  hi.[bucket_count],
  hi.[auto_created]
FROM
  [sys].[hash_indexes] hi
```

Columns and interpretation

- `object_id` — object id of the table that contains the index.
- `Name` — index name (nullable).
- `index_id` — index id.
- `Type` / `type_desc` — internal index type and description.
- `is_unique` — whether the index enforces uniqueness (nullable).
- `data_space_id` — data space id for index storage.
- `ignore_dup_key` — whether duplicate key errors are ignored.
- `is_primary_key` — whether index is a primary key.
- `is_unique_constraint` — whether index implements a unique constraint.
- `fill_factor` — fill factor percent for the index.
- `is_padded` — whether padding is applied.
- `is_disabled` — whether the index is disabled.
- `is_hypothetical` — whether the index is hypothetical (used for tuning).
- `is_ignored_in_optimization` — whether the optimizer ignores the index.
- `allow_row_locks` / `allow_page_locks` — locking options.
- `has_filter` / `filter_definition` — filtered index flag and predicate (nullable).
- `bucket_count` — number of hash buckets used by the index (important for hash index scalability).
- `auto_created` — whether the index was auto-created by the engine.

How to interpret

- For memory-optimized hash indexes, `bucket_count` is critical: choose bucket count close to expected unique hash keys to avoid hash collisions.
- `is_ignored_in_optimization` indicates indexes that should not be considered by the query optimizer.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = HashIndexesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new HashIndexesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Table:{r.ObjectId} Index:{r.IndexId} Name:{r.Name} Buckets:{r.BucketCount} Unique:{r.IsUnique}");
}
```

See also:

- [sys.hash_indexes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-hash-indexes)
