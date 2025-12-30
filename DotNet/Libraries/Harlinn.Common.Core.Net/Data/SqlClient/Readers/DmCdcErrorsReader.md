# DmCdcErrorsReader — reference

Overview

`DmCdcErrorsReader` wraps `sys.dm_cdc_errors` and exposes Change Data Capture (CDC) error records.

Reader SQL

```
SELECT
  dce.[session_id],
  dce.[phase_number],
  dce.[entry_time],
  dce.[error_number],
  dce.[error_severity],
  dce.[error_state],
  dce.[error_message],
  dce.[start_lsn],
  dce.[begin_lsn],
  dce.[sequence_value]
FROM
  [sys].[dm_cdc_errors] dce
```

Selected columns (property mapping and brief meaning)

- `session_id` ? `SessionId` (int?): CDC session identifier where the error occurred.
- `phase_number` ? `PhaseNumber` (int?): Phase number within CDC processing.
- `entry_time` ? `EntryTime` (DateTime?): When the error was logged.
- `error_number` ? `ErrorNumber` (int?): Numeric error code.
- `error_severity` ? `ErrorSeverity` (int?): Severity level of the error.
- `error_state` ? `ErrorState` (int?): State code for the error.
- `error_message` ? `ErrorMessage` (string?): Error message text.
- `start_lsn` ? `StartLsn` (string?): LSN where scan started.
- `begin_lsn` ? `BeginLsn` (string?): LSN marking the beginning of the relevant transaction.
- `sequence_value` ? `SequenceValue` (string?): Sequence value associated with the error (CDC internal sequence).

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmCdcErrorsDataType` objects.
