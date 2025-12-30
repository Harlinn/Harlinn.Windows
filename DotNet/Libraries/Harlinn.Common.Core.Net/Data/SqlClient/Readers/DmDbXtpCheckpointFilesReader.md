# DmDbXtpCheckpointFilesReader — reference

Overview

`DmDbXtpCheckpointFilesReader` wraps `sys.dm_db_xtp_checkpoint_files` and exposes metadata about checkpoint files used by In-Memory OLTP (XTP) for persistent checkpointing. This includes file identifiers, sizes, TSN ranges, checkpoint ids and encryption status.

Reader SQL

```
SELECT
  ddxcf.[container_id],
  ddxcf.[container_guid],
  ddxcf.[checkpoint_file_id],
  ddxcf.[relative_file_path],
  ddxcf.[file_type],
  ddxcf.[file_type_desc],
  ddxcf.[internal_storage_slot],
  ddxcf.[checkpoint_pair_file_id],
  ddxcf.[file_size_in_bytes],
  ddxcf.[file_size_used_in_bytes],
  ddxcf.[logical_row_count],
  ddxcf.[State],
  ddxcf.[state_desc],
  ddxcf.[lower_bound_tsn],
  ddxcf.[upper_bound_tsn],
  ddxcf.[begin_checkpoint_id],
  ddxcf.[end_checkpoint_id],
  ddxcf.[last_updated_checkpoint_id],
  ddxcf.[encryption_status],
  ddxcf.[encryption_status_desc]
FROM
  [sys].[dm_db_xtp_checkpoint_files] ddxcf
```

Columns (detailed)

- `container_id` ? `ContainerId` (int)
  - Numeric container identifier for the checkpoint file group.

- `container_guid` ? `ContainerGuid` (Guid)
  - GUID representing the container.

- `checkpoint_file_id` ? `CheckpointFileId` (Guid)
  - Unique identifier for the checkpoint file.

- `relative_file_path` ? `RelativeFilePath` (string)
  - Relative path of the checkpoint file within the container.

- `file_type` ? `FileType` (short)
  - Numeric code for the file type (primary, secondary, delta, etc.).

- `file_type_desc` ? `FileTypeDesc` (string)
  - Text description of the file type.

- `internal_storage_slot` ? `InternalStorageSlot` (int?)
  - Internal storage slot used by the file, if applicable.

- `checkpoint_pair_file_id` ? `CheckpointPairFileId` (Guid?)
  - Paired checkpoint file id for redundancy.

- `file_size_in_bytes` ? `FileSizeInBytes` (long)
  - Total size allocated for the checkpoint file in bytes.

- `file_size_used_in_bytes` ? `FileSizeUsedInBytes` (long?)
  - Bytes currently used within the file.

- `logical_row_count` ? `LogicalRowCount` (long?)
  - Number of logical rows accounted in the checkpoint file.

- `State` / `state_desc` ? `State` (short), `StateDesc` (string)
  - Numeric state and descriptive state name for the checkpoint file (active, archived, pending purge, etc.).

- `lower_bound_tsn` / `upper_bound_tsn` ? TSN bounds (long?)
  - Transaction sequence number range covered by the checkpoint file.

- `begin_checkpoint_id` / `end_checkpoint_id` / `last_updated_checkpoint_id` ? checkpoint identifiers (long?)
  - Identifiers for checkpoint operations that created/closed/updated the file.

- `encryption_status` ? `EncryptionStatus` (short?)
  - Numeric code indicating whether the file is encrypted and encryption state.

- `encryption_status_desc` ? `EncryptionStatusDesc` (string?)
  - Textual description of the encryption status.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbXtpCheckpointFilesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbXtpCheckpointFilesReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Checkpoint file: {r.CheckpointFileId} Container: {r.ContainerId} ({r.ContainerGuid})");
    Console.WriteLine($" Path: {r.RelativeFilePath} Type: {r.FileTypeDesc} Size: {r.FileSizeInBytes:N0} used: {r.FileSizeUsedInBytes:N0}");
    Console.WriteLine($" TSN range: {r.LowerBoundTsn}-{r.UpperBoundTsn} Checkpoints: {r.BeginCheckpointId}-{r.EndCheckpointId} LastUpdated: {r.LastUpdatedCheckpointId}");
    Console.WriteLine();
}
```

See also:

- [sys.dm_db_xtp_checkpoint_files](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm_db_xtp_checkpoint_files)
