# DmExecQueryProfilesReader — reference

Overview

`DmExecQueryProfilesReader` wraps `sys.dm_exec_query_profiles` and provides operator-level profiling information for running or recently executed queries. It exposes per-operator counts, timing, IO and row metrics useful for detailed performance analysis.

Reader SQL

```
SELECT
  deqp.[session_id],
  deqp.[request_id],
  deqp.[sql_handle],
  deqp.[plan_handle],
  deqp.[physical_operator_name],
  deqp.[node_id],
  deqp.[thread_id],
  deqp.[task_address],
  deqp.[row_count],
  deqp.[rewind_count],
  deqp.[rebind_count],
  deqp.[end_of_scan_count],
  deqp.[estimate_row_count],
  deqp.[first_active_time],
  deqp.[last_active_time],
  deqp.[open_time],
  deqp.[first_row_time],
  deqp.[last_row_time],
  deqp.[close_time],
  deqp.[elapsed_time_ms],
  deqp.[cpu_time_ms],
  deqp.[database_id],
  deqp.[object_id],
  deqp.[index_id],
  deqp.[scan_count],
  deqp.[logical_read_count],
  deqp.[physical_read_count],
  deqp.[read_ahead_count],
  deqp.[write_page_count],
  deqp.[lob_logical_read_count],
  deqp.[lob_physical_read_count],
  deqp.[lob_read_ahead_count],
  deqp.[segment_read_count],
  deqp.[segment_skip_count],
  deqp.[actual_read_row_count],
  deqp.[estimated_read_row_count],
  deqp.[page_server_read_count],
  deqp.[page_server_read_ahead_count],
  deqp.[lob_page_server_read_count],
  deqp.[lob_page_server_read_ahead_count]
FROM
  [sys].[dm_exec_query_profiles] deqp
```

Columns and interpretation

- `session_id` / `request_id` ? session and request identifiers for the profiled query.
- `sql_handle` / `plan_handle` ? handles to retrieve SQL text and plan for the query.
- `physical_operator_name` ? operator name in the execution plan (e.g., Nested Loops, Hash Match).
- `node_id` / `thread_id` / `task_address` ? execution node, thread and internal task address for the operator occurrence.
- `row_count` ? actual rows produced by the operator.
- `rewind_count` / `rebind_count` / `end_of_scan_count` ? operator-specific counters indicating rescans, rebinds and end-of-scan events.
- `estimate_row_count` ? optimizer's estimated row count for the operator; compare with `row_count` to detect cardinality estimation issues.
- `first_active_time` / `last_active_time` / `open_time` / `first_row_time` / `last_row_time` / `close_time` ? timestamps (ms relative or absolute — check DMV docs) indicating operator activity windows.
- `elapsed_time_ms` / `cpu_time_ms` ? elapsed and CPU time consumed by the operator in ms.
- `database_id` / `object_id` / `index_id` ? storage object identifiers the operator accessed.
- `scan_count` / `logical_read_count` / `physical_read_count` / `read_ahead_count` ? IO counters for the operator.
- `write_page_count` ? number of pages written by the operator.
- `lob_*` counters ? LOB-specific IO metrics.
- `segment_read_count` / `segment_skip_count` ? columnstore segment operations counts.
- `actual_read_row_count` / `estimated_read_row_count` ? actual vs estimated rows read by the operator.
- `page_server_*` counters ? counts for page server reads in remote/page server scenarios.

How to interpret

- Use `estimate_row_count` vs `actual_read_row_count` to find cardinality estimation mismatches contributing to poor plans.
- Operator-level `elapsed_time_ms` and `cpu_time_ms` show where time is spent; focus optimization where these are high.
- High `physical_read_count` and `read_ahead_count` indicate IO-bound operators.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecQueryProfilesReader.Sql;
using var rdr = cmd.ExecuteReader();
var p = new DmExecQueryProfilesReader(rdr, ownsReader:false);
while (p.Read())
{
    Console.WriteLine($"Session:{p.SessionId} Req:{p.RequestId} Op:{p.PhysicalOperatorName} Rows:{p.RowCount} Est:{p.EstimateRowCount} Time(ms):{p.ElapsedTimeMs}");
}
```

See also:

- [sys.dm_exec_query_profiles](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-query-profiles)
