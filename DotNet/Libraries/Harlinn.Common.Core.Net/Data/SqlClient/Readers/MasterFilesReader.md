# MasterFilesReader — reference

Overview

`MasterFilesReader` wraps `sys.master_files` and returns information about database files across the server, including sizes, growth settings, LSNs and storage attributes.

Reader SQL

```
SELECT
  mf.[database_id],
  mf.[file_id],
  mf.[file_guid],
  mf.[Type],
  mf.[type_desc],
  mf.[data_space_id],
  mf.[Name],
  mf.[physical_name],
  mf.[State],
  mf.[state_desc],
  mf.[Size],
  mf.[max_size],
  mf.[Growth],
  mf.[is_media_read_only],
  mf.[is_read_only],
  mf.[is_sparse],
  mf.[is_percent_growth],
  mf.[is_name_reserved],
  mf.[is_persistent_log_buffer],
  mf.[create_lsn],
  mf.[drop_lsn],
  mf.[read_only_lsn],
  mf.[read_write_lsn],
  mf.[differential_base_lsn],
  mf.[differential_base_guid],
  mf.[differential_base_time],
  mf.[redo_start_lsn],
  mf.[redo_start_fork_guid],
  mf.[redo_target_lsn],
  mf.[redo_target_fork_guid],
  mf.[backup_lsn],
  mf.[credential_id]
FROM
  [sys].[master_files] mf
```

Columns and interpretation

- `database_id`, `file_id`, `file_guid` — identify the file and the database.
- `Type` / `type_desc` — type of file (ROWS, LOG, FILESTREAM, etc.).
- `data_space_id` — filegroup or data space id.
- `Name`, `physical_name` — logical name and physical path.
- `State` / `state_desc` — online/offline state and description.
- `Size`, `max_size`, `Growth` — current size (in 8KB pages), maximum size, and growth increment.
- Flags: `is_media_read_only`, `is_read_only`, `is_sparse`, `is_percent_growth`, `is_name_reserved`, `is_persistent_log_buffer`.
- LSN-related: `create_lsn`, `drop_lsn`, `read_only_lsn`, `read_write_lsn`, `differential_base_lsn`, `differential_base_guid`, `differential_base_time`, `redo_start_lsn`, `redo_start_fork_guid`, `redo_target_lsn`, `redo_target_fork_guid`, `backup_lsn` — used for replication, log shipping and recovery operations.
- `credential_id` — credential used for external storage operations (nullable).

How to interpret

- Sizes are in pages (typically 8KB); multiply by 8192 to get bytes. LSN and redo fields help diagnose restore/replication and recovery state.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = MasterFilesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new MasterFilesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DatabaseId} File:{r.FileId} Name:{r.Name} Physical:{r.PhysicalName} SizePages:{r.Size}");
}
```

See also:

- [sys.master_files](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-master-files)
