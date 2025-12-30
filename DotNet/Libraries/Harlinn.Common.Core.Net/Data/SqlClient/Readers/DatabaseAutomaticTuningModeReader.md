# DatabaseAutomaticTuningModeReader — reference

Overview

`DatabaseAutomaticTuningModeReader` wraps `sys.database_automatic_tuning_mode` and exposes automatic tuning desired and actual state for the database.

Reader SQL

```
SELECT
  datm.[desired_state],
  datm.[desired_state_desc],
  datm.[actual_state],
  datm.[actual_state_desc]
FROM
  [sys].[database_automatic_tuning_mode] datm
```

Selected columns (property mapping and brief meaning)

- `desired_state` ? `DesiredState` (short?): Desired automatic tuning state code for the database.
- `desired_state_desc` ? `DesiredStateDesc` (string?): Description of the desired state.
- `actual_state` ? `ActualState` (short?): Actual effective tuning state.
- `actual_state_desc` ? `ActualStateDesc` (string?): Description of the actual state.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseAutomaticTuningModeDataType` objects.
