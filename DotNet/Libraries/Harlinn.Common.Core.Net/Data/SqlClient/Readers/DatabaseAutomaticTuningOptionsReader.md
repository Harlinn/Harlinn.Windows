# DatabaseAutomaticTuningOptionsReader — reference

Overview

`DatabaseAutomaticTuningOptionsReader` wraps `sys.database_automatic_tuning_options` and exposes individual tuning option settings and states.

Reader SQL

```
SELECT
  dato.[Name],
  dato.[desired_state],
  dato.[desired_state_desc],
  dato.[actual_state],
  dato.[actual_state_desc],
  dato.[Reason],
  dato.[reason_desc]
FROM
  [sys].[database_automatic_tuning_options] dato
```

Selected columns (property mapping and brief meaning)

- `Name` ? `Name` (string?): Name of the tuning option (e.g., FORCE_LAST_GOOD_PLAN).
- `desired_state` ? `DesiredState` (short?): Desired state code for the option.
- `desired_state_desc` ? `DesiredStateDesc` (string?): Description of desired state.
- `actual_state` ? `ActualState` (short?): Actual state code.
- `actual_state_desc` ? `ActualStateDesc` (string?): Description of actual state.
- `Reason` ? `Reason` (short?): Numeric reason code for current state.
- `reason_desc` ? `ReasonDesc` (string?): Human-readable reason description.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseAutomaticTuningOptionsDataType` objects.
