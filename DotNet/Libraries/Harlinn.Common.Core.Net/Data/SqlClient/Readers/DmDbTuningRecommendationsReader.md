# DmDbTuningRecommendationsReader — reference

Overview

`DmDbTuningRecommendationsReader` wraps `sys.dm_db_tuning_recommendations` and exposes tuning recommendations produced by the automatic tuning or advisor features. This includes metadata about recommendation validity, state, execution/revertability, score and detailed recommendation content.

Reader SQL

```
SELECT
  ddtr.[Name],
  ddtr.[Type],
  ddtr.[Reason],
  ddtr.[valid_since],
  ddtr.[last_refresh],
  ddtr.[State],
  ddtr.[is_executable_action],
  ddtr.[is_revertable_action],
  ddtr.[execute_action_start_time],
  ddtr.[execute_action_duration],
  ddtr.[execute_action_initiated_by],
  ddtr.[execute_action_initiated_time],
  ddtr.[revert_action_start_time],
  ddtr.[revert_action_duration],
  ddtr.[revert_action_initiated_by],
  ddtr.[revert_action_initiated_time],
  ddtr.[Score],
  ddtr.[Details]
FROM
  [sys].[dm_db_tuning_recommendations] ddtr
```

Columns (detailed)

- `Name` ? `Name` (string?)
  - Name of the recommendation.

- `Type` ? `Type` (string?)
  - Recommendation type (e.g., create index, drop index, force plan, etc.).

- `Reason` ? `Reason` (string?)
  - Short reason or category describing why recommendation was made.

- `valid_since` ? `ValidSince` (DateTime?)
  - Timestamp since the recommendation is considered valid.

- `last_refresh` ? `LastRefresh` (DateTime?)
  - Last time the recommendation was refreshed or re-evaluated.

- `State` ? `State` (string?)
  - Current recommendation state (e.g., Pending, Applied, Reverted).

- `is_executable_action` ? `IsExecutableAction` (bool?)
  - Whether the recommendation can be executed by the system (automated actions).

- `is_revertable_action` ? `IsRevertableAction` (bool?)
  - Whether the executed action can be reverted automatically.

- `execute_action_start_time` / `execute_action_duration` ? `ExecuteActionStartTime` (DateTime?), `ExecuteActionDuration` (DateTime?)
  - When execution started and duration; duration may be represented as a datetime delta in this view.

- `execute_action_initiated_by` / `execute_action_initiated_time` ? who initiated execution and when.

- `revert_action_*` ? same as execute action but for revert operations.

- `Score` ? `Score` (int?)
  - Numeric score rating the importance/benefit of the recommendation.

- `Details` ? `Details` (string?)
  - JSON or textual details describing the recommendation and its objects.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbTuningRecommendationsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbTuningRecommendationsReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Recommendation: {r.Name} Type: {r.Type} Score: {r.Score}");
    Console.WriteLine($"  State: {r.State} Valid since: {r.ValidSince}");
    Console.WriteLine($"  Details: {r.Details}\n");
}
```

See also:

- [sys.dm_db_tuning_recommendations](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-tuning-recommendations)
