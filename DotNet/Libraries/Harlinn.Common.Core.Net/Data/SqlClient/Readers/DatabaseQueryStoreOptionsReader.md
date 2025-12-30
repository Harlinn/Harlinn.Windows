# DatabaseQueryStoreOptionsReader — reference

Overview

`DatabaseQueryStoreOptionsReader` wraps `sys.database_query_store_options` and exposes Query Store settings and runtime statistics for a database.

Reader SQL

```
SELECT
  dqso.[desired_state],
  dqso.[desired_state_desc],
  dqso.[actual_state],
  dqso.[actual_state_desc],
  dqso.[readonly_reason],
  dqso.[current_storage_size_mb],
  dqso.[flush_interval_seconds],
  dqso.[interval_length_minutes],
  dqso.[max_storage_size_mb],
  dqso.[stale_query_threshold_days],
  dqso.[max_plans_per_query],
  dqso.[query_capture_mode],
  dqso.[query_capture_mode_desc],
  dqso.[capture_policy_execution_count],
  dqso.[capture_policy_total_compile_cpu_time_ms],
  dqso.[capture_policy_total_execution_cpu_time_ms],
  dqso.[capture_policy_stale_threshold_hours],
  dqso.[size_based_cleanup_mode],
  dqso.[size_based_cleanup_mode_desc],
  dqso.[wait_stats_capture_mode],
  dqso.[wait_stats_capture_mode_desc],
  dqso.[actual_state_additional_info]
FROM
  [sys].[database_query_store_options] dqso
```

Selected columns (property mapping and brief meaning)

- `desired_state` / `desired_state_desc` ? desired Query Store state and description.
- `actual_state` / `actual_state_desc` ? actual state and description.
- `readonly_reason` ? code indicating why Query Store is read-only.
- `current_storage_size_mb` ? current storage consumption in MB.
- `flush_interval_seconds` ? frequency of flushing in seconds.
- `interval_length_minutes` ? aggregation interval length in minutes.
- `max_storage_size_mb` ? configured maximum storage in MB.
- `stale_query_threshold_days` ? threshold in days after which queries are considered stale.
- `max_plans_per_query` ? maximum number of plans per query recorded.
- `query_capture_mode` / `query_capture_mode_desc` ? capture mode and description.
- `capture_policy_*` ? policies for capture based on execution/CPU thresholds and stale thresholds.
- `size_based_cleanup_mode` / `size_based_cleanup_mode_desc` ? cleanup behavior when size limits reached.
- `wait_stats_capture_mode` / `wait_stats_capture_mode_desc` ? wait stats capture settings.
- `actual_state_additional_info` ? textual extra info about actual state.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DatabaseQueryStoreOptionsDataType` objects.
