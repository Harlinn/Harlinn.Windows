# ServerAuditsReader

Overview

`ServerAuditsReader` wraps `sys.server_audits` and exposes configuration and state for server-level audits.

Reader SQL

```
SELECT
  sa.[audit_id],
  sa.[Name],
  sa.[audit_guid],
  sa.[create_date],
  sa.[modify_date],
  sa.[principal_id],
  sa.[Type],
  sa.[type_desc],
  sa.[on_failure],
  sa.[on_failure_desc],
  sa.[is_state_enabled],
  sa.[queue_delay],
  sa.[Predicate]
FROM
  [sys].[server_audits] sa
```

Columns and interpretation

- `audit_id` (int): Identifier of the server audit.
- `Name` (string): Audit name.
- `audit_guid` (Guid?): GUID of the audit.
- `create_date`, `modify_date` (DateTime): Timestamps.
- `principal_id` (int?): Owning principal id.
- `Type`, `type_desc` (string/string?): The audit target type and description (e.g., FILE, WINDOWS_AZURE_TABLE).
- `on_failure`, `on_failure_desc` (byte?/string?): Behavior on audit failure (e.g., continue, fail operation).
- `is_state_enabled` (bool?): Whether audit is enabled.
- `queue_delay` (int?): Queue delay in ms for synchronous targets.
- `Predicate` (string?): Optional filter predicate for the audit.

How to interpret

- The audit object defines where audit records are written and how the engine responds on failure.
- Use `queue_delay` and `on_failure` to evaluate reliability vs performance tradeoffs.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerAuditsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerAuditsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Audit:{r.Name} Type:{r.Type} Enabled:{r.IsStateEnabled} QueueDelay:{r.QueueDelay}");
```

See also:

- [sys.server_audits](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-audits)

