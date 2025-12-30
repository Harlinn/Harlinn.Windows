# DmDbMirroringAutoPageRepairReader — reference

Overview

`DmDbMirroringAutoPageRepairReader` wraps `sys.dm_db_mirroring_auto_page_repair` and reports pages that have been automatically repaired as part of database mirroring/availability group page repair functionality.

Reader SQL

```
SELECT
  ddmapr.[database_id],
  ddmapr.[file_id],
  ddmapr.[page_id],
  ddmapr.[error_type],
  ddmapr.[page_status],
  ddmapr.[modification_time]
FROM
  [sys].[dm_db_mirroring_auto_page_repair] ddmapr
```

Columns (detailed)

- `database_id` ? `DatabaseId` (int)
  - Database identifier where the page repair event occurred.

- `file_id` ? `FileId` (int)
  - File id within the database identifying the file containing the affected page.

- `page_id` ? `PageId` (long)
  - Page number within the file that was subject to auto-repair.

- `error_type` ? `ErrorType` (short)
  - Code representing the error type detected on the page (IO error, checksum, torn page, etc.). Use SQL Server docs to map codes to meaning.

- `page_status` ? `PageStatus` (byte)
  - Status code for the page (repaired, pending repair, etc.). Convert to textual meaning via documentation.

- `modification_time` ? `ModificationTime` (DateTime)
  - Timestamp when the page repair event occurred or was last modified.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbMirroringAutoPageRepairReader.Sql;
using var reader = cmd.ExecuteReader();
var repairReader = new DmDbMirroringAutoPageRepairReader(reader, ownsReader: false);
while (repairReader.Read())
{
    Console.WriteLine($"DB: {repairReader.DatabaseId}, File: {repairReader.FileId}, Page: {repairReader.PageId}");
    Console.WriteLine($" Error type: {repairReader.ErrorType}, Page status: {repairReader.PageStatus}");
    Console.WriteLine($" Time: {repairReader.ModificationTime}");
    Console.WriteLine();
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-mirroring-auto-page-repair
