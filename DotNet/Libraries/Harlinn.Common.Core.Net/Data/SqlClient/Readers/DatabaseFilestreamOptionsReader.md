# DatabaseFilestreamOptionsReader — reference

Overview

`DatabaseFilestreamOptionsReader` wraps `sys.database_filestream_options` and exposes FILESTREAM configuration for databases.

Reader SQL

```
SELECT
  dfo.[database_id],
  dfo.[non_transacted_access],
  dfo.[non_transacted_access_desc],
  dfo.[directory_name]
FROM
  [sys].[database_filestream_options] dfo
```

Selected columns (property mapping and brief meaning)

- `database_id` ? `DatabaseId` (int): Database identifier.
- `non_transacted_access` ? `NonTransactedAccess` (byte): Code indicating non-transacted access policy.
- `non_transacted_access_desc` ? `NonTransactedAccessDesc` (string): Description of non-transacted access policy.
- `directory_name` ? `DirectoryName` (string?): Root directory name for FILESTREAM data.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseFilestreamOptionsDataType` objects.
