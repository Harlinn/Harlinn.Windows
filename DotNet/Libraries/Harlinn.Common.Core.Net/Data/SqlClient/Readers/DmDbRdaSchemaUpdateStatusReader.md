# DmDbRdaSchemaUpdateStatusReader — reference

Overview

`DmDbRdaSchemaUpdateStatusReader` wraps `sys.dm_db_rda_schema_update_status` and provides information about schema update tasks executed as part of RDA operations.

Reader SQL

```
SELECT
  ddrsus.[table_id],
  ddrsus.[database_id],
  ddrsus.[task_id],
  ddrsus.[task_type],
  ddrsus.[task_type_desc],
  ddrsus.[task_state],
  ddrsus.[task_state_desc],
  ddrsus.[start_time_utc],
  ddrsus.[end_time_utc],
  ddrsus.[error_number],
  ddrsus.[error_severity],
  ddrsus.[error_state]
FROM
  [sys].[dm_db_rda_schema_update_status] ddrsus
```

Columns

- `table_id` ? `TableId` (int?) — Table the schema update applies to.
- `database_id` ? `DatabaseId` (int?) — Database id.
- `task_id` ? `TaskId` (long?) — Identifier for the schema update task.
- `task_type` ? `TaskType` (int?) — Numeric code for task type.
- `task_type_desc` ? `TaskTypeDesc` (string?) — Textual description of task type.
- `task_state` ? `TaskState` (int?) — Numeric state code for the task.
- `task_state_desc` ? `TaskStateDesc` (string?) — Human readable state description.
- `start_time_utc` / `end_time_utc` ? DateTime? — Start and end times for the task.
- `error_number` / `error_severity` / `error_state` ? int? — Error information if the task failed.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbRdaSchemaUpdateStatusReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbRdaSchemaUpdateStatusReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Table: {r.TableId} Task: {r.TaskId} Type: {r.TaskTypeDesc} State: {r.TaskStateDesc}");
}
```

See also:

- [sys.dm_db_rda_schema_update_status](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-rda-schema-update-status)
