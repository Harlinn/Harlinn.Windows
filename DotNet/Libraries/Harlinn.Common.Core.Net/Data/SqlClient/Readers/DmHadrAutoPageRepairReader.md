# DmHadrAutoPageRepairReader — reference

Overview

`DmHadrAutoPageRepairReader` wraps `sys.dm_hadr_auto_page_repair` and exposes detected page-level corruption events and their repair status for HADR environments.

Reader SQL

```
SELECT
  dhapr.[database_id],
  dhapr.[file_id],
  dhapr.[page_id],
  dhapr.[error_type],
  dhapr.[page_status],
  dhapr.[modification_time]
FROM
  [sys].[dm_hadr_auto_page_repair] dhapr
```

Columns and interpretation

- `database_id`, `file_id`, `page_id` ? identify the page that experienced an error.
- `error_type` ? type of error detected on the page.
- `page_status` ? status of the page repair (e.g., pending, repaired).
- `modification_time` ? timestamp when the error or repair status was recorded.

How to interpret

- Monitor this view to detect automated repairs and to escalate pages that fail automatic repair.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmHadrAutoPageRepairReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmHadrAutoPageRepairReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DatabaseId} File:{r.FileId} Page:{r.PageId} Error:{r.ErrorType} Status:{r.PageStatus} Time:{r.ModificationTime}");
}
```

See also:

- [sys.dm_hadr_auto_page_repair](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-hadr-auto-page-repair)
