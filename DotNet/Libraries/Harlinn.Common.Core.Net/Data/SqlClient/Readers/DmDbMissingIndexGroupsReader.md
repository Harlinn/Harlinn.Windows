# DmDbMissingIndexGroupsReader — reference

Overview

`DmDbMissingIndexGroupsReader` wraps `sys.dm_db_missing_index_groups` and maps missing index group handles to their constituent missing index detail handles.

Reader SQL

```
SELECT
  ddmig.[index_group_handle],
  ddmig.[index_handle]
FROM
  [sys].[dm_db_missing_index_groups] ddmig
```

Columns (detailed)

- `index_group_handle` ? `IndexGroupHandle` (int)
  - Group handle that aggregates missing index recommendations that are related. Use with `dm_db_missing_index_group_stats` to find aggregated statistics per group.

- `index_handle` ? `IndexHandle` (int)
  - Handle of the missing index detail record that belongs to the group. Join with `dm_db_missing_index_details` to get column recommendations.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbMissingIndexGroupsReader.Sql;
using var reader = cmd.ExecuteReader();
var grpReader = new DmDbMissingIndexGroupsReader(reader, ownsReader: false);
while (grpReader.Read())
{
    Console.WriteLine($"Group: {grpReader.IndexGroupHandle}, IndexHandle: {grpReader.IndexHandle}");
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-missing-index-groups
