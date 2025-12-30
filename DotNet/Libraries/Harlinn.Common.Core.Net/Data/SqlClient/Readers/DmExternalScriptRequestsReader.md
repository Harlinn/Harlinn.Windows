# DmExternalScriptRequestsReader — reference

Overview

`DmExternalScriptRequestsReader` wraps `sys.dm_external_script_requests` and shows details for active external script requests (R, Python) including request id, language, DOP and external user name.

Reader SQL

```
SELECT
  desr.[external_script_request_id],
  desr.[Language],
  desr.[degree_of_parallelism],
  desr.[external_user_name]
FROM
  [sys].[dm_external_script_requests] desr
```

Columns and interpretation

- `external_script_request_id` ? `ExternalScriptRequestId` (GUID)
  - Unique identifier for the external script execution request. Use to correlate with `dm_exec_requests` and other DMVs.

- `Language` ? `Language` (string?)
  - External language used for the request (for example `R` or `Python`). May be null if unspecified.

- `degree_of_parallelism` ? `DegreeOfParallelism` (int)
  - Degree of parallelism assigned to the external script execution.

- `external_user_name` ? `ExternalUserName` (string)
  - External user under which the script is executed.

How to interpret

- Use `ExternalScriptRequestId` to track script executions across DMVs and to debug failing or long-running external executions.
- `DegreeOfParallelism` indicates how many threads/processes the external runtime may use.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExternalScriptRequestsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmExternalScriptRequestsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Request {r.ExternalScriptRequestId} Lang:{r.Language} DOP:{r.DegreeOfParallelism} User:{r.ExternalUserName}");
}
```

See also:

- [sys.dm_external_script_requests](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-external-script-requests)