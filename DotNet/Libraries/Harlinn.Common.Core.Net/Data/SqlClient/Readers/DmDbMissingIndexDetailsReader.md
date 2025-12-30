# DmDbMissingIndexDetailsReader — reference

Overview

`DmDbMissingIndexDetailsReader` wraps `sys.dm_db_missing_index_details` and provides the missing index details recorded by the query optimizer. This helps identify candidate indexes to improve query performance.

Reader SQL

```
SELECT
  ddmid.[index_handle],
  ddmid.[database_id],
  ddmid.[object_id],
  ddmid.[equality_columns],
  ddmid.[inequality_columns],
  ddmid.[included_columns],
  ddmid.[Statement]
FROM
  [sys].[dm_db_missing_index_details] ddmid
```

Columns (detailed)

- `index_handle` ? `IndexHandle` (int)
  - Internal handle that identifies the missing index recommendation group. Use together with `dm_db_missing_index_groups` and `dm_db_missing_index_group_stats` to find usage stats and queries.

- `database_id` ? `DatabaseId` (short)
  - ID of the database where the missing index was suggested.

- `object_id` ? `ObjectId` (int)
  - Object id (table or view) the missing index pertains to.

- `equality_columns` ? `EqualityColumns` (string?)
  - Comma-separated list of columns that would be ideal in the index key as equality predicates (WHERE col = ...).

- `inequality_columns` ? `InequalityColumns` (string?)
  - Columns better suited for inequality predicates (WHERE col > ... or col BETWEEN ...).

- `included_columns` ? `IncludedColumns` (string?)
  - Columns to include (non-key) in the index to cover queries and avoid lookups.

- `Statement` ? `Statement` (string?)
  - The SQL statement text or fragment that produced the recommendation.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbMissingIndexDetailsReader.Sql;
using var reader = cmd.ExecuteReader();
var missReader = new DmDbMissingIndexDetailsReader(reader, ownsReader: false);
while (missReader.Read())
{
    Console.WriteLine($"IndexHandle: {missReader.IndexHandle} DB: {missReader.DatabaseId} Object: {missReader.ObjectId}");
    Console.WriteLine($" Equality: {missReader.EqualityColumns}");
    Console.WriteLine($" Inequality: {missReader.InequalityColumns}");
    Console.WriteLine($" Included: {missReader.IncludedColumns}");
    Console.WriteLine($" Sample statement: {missReader.Statement}\n");
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-missing-index-details
