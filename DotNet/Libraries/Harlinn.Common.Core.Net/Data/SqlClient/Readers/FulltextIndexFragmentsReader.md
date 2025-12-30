# FulltextIndexFragmentsReader — reference

Overview

`FulltextIndexFragmentsReader` wraps `sys.fulltext_index_fragments` and returns statistics about full-text index fragments such as size and row counts, status and timestamp.

Reader SQL

```
SELECT
  fif.[table_id],
  fif.[fragment_id],
  fif.[fragment_object_id],
  fif.[Timestamp],
  fif.[Status],
  fif.[data_size],
  fif.[row_count]
FROM
  [sys].[fulltext_index_fragments] fif
```

Columns and interpretation

- `table_id` — object id of the table the fragment belongs to.
- `fragment_id` — fragment identifier within the index.
- `fragment_object_id` — object id representing the fragment in the database.
- `Timestamp` — binary timestamp of fragment creation or last update.
- `Status` — numeric status code indicating the fragment state (e.g., online/offline/merging).
- `data_size` — size in bytes of the fragment.
- `row_count` — number of rows indexed in the fragment.

How to interpret

- Fragment statistics are useful for monitoring storage usage and balancing. High `data_size` or uneven `row_count` among fragments may indicate fragmentation or imbalance.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextIndexFragmentsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextIndexFragmentsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Table:{r.TableId} Frag:{r.FragmentId} Obj:{r.FragmentObjectId} Size:{r.DataSize} Rows:{r.RowCount} Status:{r.Status}");
}
```

See also:

- [sys.fulltext_index_fragments](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-index-fragments)
