# FulltextIndexesReader — reference

Overview

`FulltextIndexesReader` wraps `sys.fulltext_indexes` and returns metadata about full-text indexes defined on tables, including change tracking, crawl information, stoplist and property list ids.

Reader SQL

```
SELECT
  fi.[object_id],
  fi.[unique_index_id],
  fi.[fulltext_catalog_id],
  fi.[is_enabled],
  fi.[change_tracking_state],
  fi.[change_tracking_state_desc],
  fi.[has_crawl_completed],
  fi.[crawl_type],
  fi.[crawl_type_desc],
  fi.[crawl_start_date],
  fi.[crawl_end_date],
  fi.[incremental_timestamp],
  fi.[stoplist_id],
  fi.[property_list_id],
  fi.[data_space_id]
FROM
  [sys].[fulltext_indexes] fi
```

Columns and interpretation

- `object_id` — object id of the table containing the full-text index.
- `unique_index_id` — id of the unique index used by the full-text index.
- `fulltext_catalog_id` — id of the catalog the index belongs to (nullable).
- `is_enabled` — whether the full-text index is enabled.
- `change_tracking_state` / `change_tracking_state_desc` — change tracking mode and description (AUTO, MANUAL, OFF).
- `has_crawl_completed` — whether an initial crawl has completed successfully.
- `crawl_type` / `crawl_type_desc` — type of crawl (FULL, INCREMENTAL) and description.
- `crawl_start_date` / `crawl_end_date` — timestamps for last crawl start/end (nullable).
- `incremental_timestamp` — binary timestamp used for incremental crawls (nullable).
- `stoplist_id` — stoplist id used for the index (nullable).
- `property_list_id` — property list id used for indexed properties (nullable).
- `data_space_id` — data space id where index is stored.

How to interpret

- `change_tracking_state_desc` indicates how changes are propagated to the full-text index; AUTO requires less manual maintenance. `has_crawl_completed` and `crawl_*` dates show crawls' progress.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextIndexesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextIndexesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} Enabled:{r.IsEnabled} ChangeTracking:{r.ChangeTrackingStateDesc} Stoplist:{r.StoplistId}");
}
```

See also:

- [sys.fulltext_indexes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-indexes)
