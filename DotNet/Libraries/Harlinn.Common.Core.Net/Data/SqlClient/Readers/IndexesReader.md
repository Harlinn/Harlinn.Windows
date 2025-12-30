# IndexesReader — reference

Overview

`IndexesReader` wraps `sys.indexes` and returns index-level metadata for all indexes in the database, including uniqueness, storage options, filters and maintenance hints.

Reader SQL

```
SELECT [object_id]
    ,[name]
    ,[index_id]
    ,[type]
    ,[type_desc]
    ,[is_unique]
    ,[data_space_id]
    ,[ignore_dup_key]
    ,[is_primary_key]
    ,[is_unique_constraint]
    ,[fill_factor]
    ,[is_padded]
    ,[is_disabled]
    ,[is_hypothetical]
    ,[is_ignored_in_optimization]
    ,[allow_row_locks]
    ,[allow_page_locks]
    ,[has_filter]
    ,[filter_definition]
    ,[compression_delay]
    ,[suppress_dup_key_messages]
    ,[auto_created]
    ,[optimize_for_sequential_key]
FROM [sys].[indexes]
```

Columns and interpretation

- `object_id`, `name`, `index_id` — identify the index.
- `type` / `type_desc` — index type (clustered, nonclustered, columnstore, etc.).
- `is_unique` — whether the index enforces uniqueness.
- `data_space_id` — filegroup or partition scheme id.
- `ignore_dup_key` — setting to ignore duplicate key errors.
- `is_primary_key`, `is_unique_constraint` — whether the index supports constraints.
- `fill_factor` — data fill factor for the index.
- `is_padded` — whether fill padding is enabled.
- `is_disabled` — whether the index is disabled.
- `is_hypothetical` — hypothetical index flag used by tuning tools.
- `is_ignored_in_optimization` — optimizer ignore flag.
- `allow_row_locks` / `allow_page_locks` — locking options.
- `has_filter` / `filter_definition` — filtered index flag and predicate.
- `compression_delay` — delay before compression takes effect (nullable).
- `suppress_dup_key_messages` — whether duplicate key messages are suppressed.
- `auto_created` — whether the index was auto-created by SQL Server.
- `optimize_for_sequential_key` — whether the index is optimized for sequential key inserts.

How to interpret

- Use `has_filter` and `filter_definition` to identify filtered indexes and their predicates. `is_disabled` indicates indexes that need rebuild before use. `optimize_for_sequential_key` benefits workloads with ascending key inserts.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = IndexesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new IndexesReader(rdr, ownsReader:false);
while (r.Read())
{
    var idx = r.GetIndex();
    Console.WriteLine($"Obj:{idx.ObjectId} Index:{idx.IndexId} Name:{idx.Name} Unique:{idx.IsUnique} Type:{idx.TypeDesc}");
}
```

See also:

- [sys.indexes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-indexes)
