# DmTranVersionStoreSpaceUsageReader — reference

Overview

`DmTranVersionStoreSpaceUsageReader` wraps `sys.dm_tran_version_store_space_usage` and returns space usage metrics for the version store per database.

Reader SQL

```
SELECT
  dtvssu.[database_id],
  dtvssu.[reserved_page_count],
  dtvssu.[reserved_space_kb]
FROM
  [sys].[dm_tran_version_store_space_usage] dtvssu
```

Columns and interpretation

- `database_id` — database id for which the usage applies.
- `reserved_page_count` — number of pages reserved for the version store.
- `reserved_space_kb` — reserved space in KB for the version store.

How to interpret

- Use to monitor space usage by the version store; growth in reserved pages or KB signals retention issues or heavy versioning activity.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranVersionStoreSpaceUsageReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranVersionStoreSpaceUsageReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DatabaseId} ReservedPages:{r.ReservedPageCount} ReservedKB:{r.ReservedSpaceKb}");
}
```

See also:

- [sys.dm_tran_version_store_space_usage](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-version-store-space-usage)
