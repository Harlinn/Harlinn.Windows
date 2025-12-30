# QueryStoreQueryReader — reference

Overview

`QueryStoreQueryReader` wraps `sys.query_store_query` and returns metadata and compile/optimization metrics for queries captured by Query Store.

Reader SQL

```
SELECT
  qsq.[query_id],
  qsq.[query_text_id],
  qsq.[context_settings_id],
  qsq.[object_id],
  qsq.[batch_sql_handle],
  qsq.[query_hash],
  qsq.[is_internal_query],
  qsq.[query_parameterization_type],
  qsq.[query_parameterization_type_desc],
  qsq.[initial_compile_start_time],
  qsq.[last_compile_start_time],
  qsq.[last_execution_time],
  qsq.[last_compile_batch_sql_handle],
  qsq.[last_compile_batch_offset_start],
  qsq.[last_compile_batch_offset_end],
  qsq.[count_compiles],
  qsq.[avg_compile_duration],
  qsq.[last_compile_duration],
  qsq.[avg_bind_duration],
  qsq.[last_bind_duration],
  qsq.[avg_bind_cpu_time],
  qsq.[last_bind_cpu_time],
  qsq.[avg_optimize_duration],
  qsq.[last_optimize_duration],
  qsq.[avg_optimize_cpu_time],
  qsq.[last_optimize_cpu_time],
  qsq.[avg_compile_memory_kb],
  qsq.[last_compile_memory_kb],
  qsq.[max_compile_memory_kb],
  qsq.[is_clouddb_internal_query]
FROM
  [sys].[query_store_query] qsq
```

Columns and interpretation

- `query_id`, `query_text_id`, `context_settings_id` — identifiers linking to query text and compile context.
- `object_id` — optional object id related to the query.
- `batch_sql_handle` / `query_hash` — handles and hash values useful to correlate batches and queries.
- `is_internal_query` — whether the query is internal to SQL Server.
- `query_parameterization_type` / `query_parameterization_type_desc` — parameterization classification.
- Compile/optimize metrics: `count_compiles`, `avg_compile_duration`, `last_compile_duration`, `avg_bind_duration`, `last_bind_duration`, `avg_optimize_duration`, `last_optimize_duration`, CPU times and memory metrics.
- Timestamps: `initial_compile_start_time`, `last_compile_start_time`, `last_execution_time`.
- `is_clouddb_internal_query` — cloud DB specific flag (nullable).

How to interpret

- Use these metrics to analyze compilation and optimization overhead for queries; correlate `query_text_id` to `sys.query_store_query_text` for the SQL text.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = QueryStoreQueryReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new QueryStoreQueryReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"QueryId:{r.QueryId} TextId:{r.QueryTextId} Compiles:{r.CountCompiles} AvgCompileMs:{r.AvgCompileDuration}");
}
```

See also:

- [sys.query_store_query](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-query-store-query)
