# FiletablesReader — reference

Overview

`FiletablesReader` wraps `sys.filetables` and returns information about filetable-enabled tables, including directory mapping and filename collation information.

Reader SQL

```
SELECT
  f.[object_id],
  f.[is_enabled],
  f.[directory_name],
  f.[filename_collation_id],
  f.[filename_collation_name]
FROM
  [sys].[filetables] f
```

Columns and interpretation

- `object_id` — object id of the filetable.
- `is_enabled` — whether the filetable feature is enabled for the table.
- `directory_name` — name of the directory exposed by the filetable.
- `filename_collation_id` — collation id used for filenames.
- `filename_collation_name` — collation name used for filenames.

How to interpret

- Filetables expose a Windows directory to the database; `directory_name` indicates that mapping. Collation controls filename comparison and sorting behavior.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FiletablesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FiletablesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} Dir:{r.DirectoryName} Enabled:{r.IsEnabled} Collation:{r.FilenameCollationName}");
}
```

See also:

- [sys.filetables](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-filetables)
