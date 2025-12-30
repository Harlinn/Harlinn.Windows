# DatabaseFilesReader — reference

Overview

`DatabaseFilesReader` wraps `sys.database_files` and exposes properties and LSN information for database files.

Reader SQL

```
SELECT
  df.[file_id],
  df.[file_guid],
  df.[Type],
  df.[type_desc],
  df.[data_space_id],
  df.[Name],
  df.[physical_name],
  df.[State],
  df.[state_desc],
  df.[Size],
  df.[max_size],
  df.[Growth],
  df.[is_media_read_only],
  df.[is_read_only],
  df.[is_sparse],
  df.[is_percent_growth],
  df.[is_name_reserved],
  df.[is_persistent_log_buffer],
  df.[create_lsn],
  df.[drop_lsn],
  df.[read_only_lsn],
  df.[read_write_lsn],
  df.[differential_base_lsn],
  df.[differential_base_guid],
  df.[differential_base_time],
  df.[redo_start_lsn],
  df.[redo_start_fork_guid],
  df.[redo_target_lsn],
  df.[redo_target_fork_guid],
  df.[backup_lsn]
FROM
  [sys].[database_files] df
```

Selected columns (property mapping and brief meaning)

- `file_id` ? `FileId` (int): File identifier within the database.
- `file_guid` ? `FileGuid` (Guid?): File GUID.
- `Type` / `type_desc` ? file type code and description (DATA, LOG, FILESTREAM etc.).
- `data_space_id` ? `DataSpaceId` (int): Filegroup or partition scheme id.
- `Name` ? `Name` (string): Logical file name.
- `physical_name` ? `PhysicalName` (string?): Physical path or location.
- `State` / `state_desc` ? state code and description for the file.
- `Size` ? `Size` (int): Current file size (pages or other units per SQL Server documentation).
- `max_size` ? `MaxSize` (int): Maximum size allowed.
- `Growth` ? `Growth` (int): Growth increment.
- `is_media_read_only` ? `IsMediaReadOnly` (bool): Media readonly flag.
- `is_read_only` ? `IsReadOnly` (bool): File readonly flag.
- `is_sparse` ? `IsSparse` (bool): Sparse file flag.
- `is_percent_growth` ? `IsPercentGrowth` (bool): Growth specified as percent.
- `is_name_reserved` ? `IsNameReserved` (bool): Name reserved flag.
- `is_persistent_log_buffer` ? `IsPersistentLogBuffer` (bool): Whether file is persistent log buffer.
- LSN-related columns (`create_lsn`, `drop_lsn`, `read_only_lsn`, `read_write_lsn`, `differential_base_lsn`, `redo_start_lsn`, `redo_target_lsn`, `backup_lsn`) ? decimal? values representing log sequence numbers for various file states.
- `differential_base_guid` ? `DifferentialBaseGuid` (Guid?): Guid for differential base.
- `differential_base_time` ? `DifferentialBaseTime` (DateTime?): Timestamp for differential base.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseFilesDataType` objects.
