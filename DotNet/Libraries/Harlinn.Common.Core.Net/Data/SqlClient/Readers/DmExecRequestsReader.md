# DmExecRequestsReader — reference

Overview

`DmExecRequestsReader` wraps `sys.dm_exec_requests` and returns one row per request currently executing on the server. It provides detailed runtime state including execution progress, waits, resource usage and session-level settings.

Reader SQL

```
SELECT
  der.[session_id],
  der.[request_id],
  der.[start_time],
  der.[Status],
  der.[Command],
  der.[sql_handle],
  der.[statement_start_offset],
  der.[statement_end_offset],
  der.[plan_handle],
  der.[database_id],
  der.[user_id],
  der.[connection_id],
  der.[blocking_session_id],
  der.[wait_type],
  der.[wait_time],
  der.[last_wait_type],
  der.[wait_resource],
  der.[open_transaction_count],
  der.[open_resultset_count],
  der.[transaction_id],
  der.[context_info],
  der.[percent_complete],
  der.[estimated_completion_time],
  der.[cpu_time],
  der.[total_elapsed_time],
  der.[scheduler_id],
  der.[task_address],
  der.[Reads],
  der.[Writes],
  der.[logical_reads],
  der.[text_size],
  der.[Language],
  der.[date_format],
  der.[date_first],
  der.[quoted_identifier],
  der.[Arithabort],
  der.[ansi_null_dflt_on],
  der.[ansi_defaults],
  der.[ansi_warnings],
  der.[ansi_padding],
  der.[ansi_nulls],
  der.[concat_null_yields_null],
  der.[transaction_isolation_level],
  der.[lock_timeout],
  der.[deadlock_priority],
  der.[row_count],
  der.[prev_error],
  der.[nest_level],
  der.[granted_query_memory],
  der.[executing_managed_code],
  der.[group_id],
  der.[query_hash],
  der.[query_plan_hash],
  der.[statement_sql_handle],
  der.[statement_context_id],
  der.[Dop],
  der.[parallel_worker_count],
  der.[external_script_request_id],
  der.[is_resumable],
  der.[page_resource],
  der.[page_server_reads]
FROM
  [sys].[dm_exec_requests] der
```

Columns and interpretation

- `session_id`, `request_id` ? identifiers for the request.
- `start_time`, `Status`, `Command` ? timing and textual state of the request.
- `sql_handle`, `plan_handle` ? handles for plan and SQL text.
- Statement offsets identify the statement inside a batch.
- `database_id`, `user_id`, `connection_id` ? security and connection context.
- Blocking and wait columns (`blocking_session_id`, `wait_type`, `wait_time`, `last_wait_type`, `wait_resource`) help diagnose blocking and wait scenarios.
- `open_transaction_count`, `transaction_id` ? transaction context for the request.
- Progress indicators: `percent_complete`, `estimated_completion_time` for long-running operations.
- Resource usage: `cpu_time`, `total_elapsed_time`, `Reads`, `Writes`, `logical_reads`.
- Session options and SET settings (ANSI flags, date format, etc.) are included for context.
- Parallelism: `Dop`, `parallel_worker_count` indicate degree of parallelism for the request.
- `external_script_request_id` ? correlation id for external script (R/Python) execution requests.
- `is_resumable` ? whether an operation (e.g., resumable index rebuild) can be resumed.
- `page_resource`, `page_server_reads` ? page server related data for remote paging.

How to interpret

- Use `wait_type` and `wait_resource` with `WAIT_TIME` to prioritize blocking/waiting issues.
- `percent_complete` and `estimated_completion_time` are useful for monitoring long-running queries (e.g., backups, restores, index operations).
- `granted_query_memory` and `page_server_reads` indicate resource consumption relevant to tuning grants and remote page activity.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecRequestsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmExecRequestsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Sess:{r.SessionId} Req:{r.RequestId} Cmd:{r.Command} Status:{r.Status} Start:{r.StartTime}");
    Console.WriteLine($" CPU:{r.CpuTime} Elapsed:{r.TotalElapsedTime} Reads:{r.Reads} Writes:{r.Writes} Wait:{r.WaitType} ({r.WaitTime}ms)");
}
```

See also:

- [sys.dm_exec_requests](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-requests)
