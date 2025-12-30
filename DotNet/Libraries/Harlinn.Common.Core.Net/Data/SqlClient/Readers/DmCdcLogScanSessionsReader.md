# DmCdcLogScanSessionsReader — reference

Overview

`DmCdcLogScanSessionsReader` wraps `sys.dm_cdc_log_scan_sessions` and exposes information about CDC log-scan sessions.

Reader SQL

```
SELECT
  dclss.[session_id],
  dclss.[start_time],
  dclss.[end_time],
  dclss.[Duration],
  dclss.[scan_phase],
  dclss.[error_count],
  dclss.[start_lsn],
  dclss.[current_lsn],
  dclss.[end_lsn],
  dclss.[tran_count],
  dclss.[last_commit_lsn],
  dclss.[last_commit_time],
  dclss.[log_record_count],
  dclss.[schema_change_count],
  dclss.[command_count],
  dclss.[first_begin_cdc_lsn],
  dclss.[last_commit_cdc_lsn],
  dclss.[last_commit_cdc_time],
  dclss.[Latency],
  dclss.[empty_scan_count],
  dclss.[failed_sessions_count]
FROM
  [sys].[dm_cdc_log_scan_sessions] dclss
```

Selected columns (property mapping and brief meaning)

- `session_id` ? `SessionId` (int?): Log scan session id.
- `start_time` ? `StartTime` (DateTime?): Start time for the session.
- `end_time` ? `EndTime` (DateTime?): End time for the session.
- `Duration` ? `Duration` (int?): Duration in seconds or milliseconds (check DM docs).
- `scan_phase` ? `ScanPhase` (string?): Phase name of log scanning.
- `error_count` ? `ErrorCount` (int?): Number of errors during session.
- `start_lsn` / `current_lsn` / `end_lsn` ? LSN markers for session progress.
- `tran_count` ? `TranCount` (long?): Number of transactions scanned.
- `last_commit_lsn` / `last_commit_time` ? last commit position/time processed.
- `log_record_count` ? `LogRecordCount` (long?): Number of log records scanned.
- `schema_change_count` ? `SchemaChangeCount` (int?): Number of schema change records.
- `command_count` ? `CommandCount` (long?): Number of commands processed.
- `first_begin_cdc_lsn` / `last_commit_cdc_lsn` / `last_commit_cdc_time` ? CDC LSN/time markers.
- `Latency` ? `Latency` (int?): Latency metric (probably milliseconds).
- `empty_scan_count` ? `EmptyScanCount` (int?): Number of scans that found no records.
- `failed_sessions_count` ? `FailedSessionsCount` (int?): Number of failed sessions observed.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmCdcLogScanSessionsDataType` objects.

Notes

- Where exact units are unclear, assume common DM semantics (lsn as varbinary/hex string, duration/latency in ms) — prefix with "Probably/guesswork:" when you need absolute certainty.
