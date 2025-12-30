# DmDbDataPoolsReader — reference

Overview

`DmDbDataPoolsReader` wraps `sys.dm_db_data_pools` and exposes information about database data pools.

Reader SQL

```
SELECT
  dddp.[data_pool_id],
  dddp.[Name],
  dddp.[Location]
FROM
  [sys].[dm_db_data_pools] dddp
```

Selected columns (property mapping and brief meaning)

- `data_pool_id` ? `DataPoolId` (int)
  - Identifier of data pool.

- `Name` ? `Name` (string?)
  - Data pool name.

- `Location` ? `Location` (string)
  - Physical or logical location of the pool.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmDbDataPoolsDataType` objects.
