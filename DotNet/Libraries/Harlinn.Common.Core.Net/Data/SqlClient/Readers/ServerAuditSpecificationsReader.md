# ServerAuditSpecificationsReader

Overview

`ServerAuditSpecificationsReader` wraps `sys.server_audit_specifications` and exposes server audit specification metadata.

Reader SQL

```
SELECT
  sas.[server_specification_id],
  sas.[Name],
  sas.[create_date],
  sas.[modify_date],
  sas.[audit_guid],
  sas.[is_state_enabled]
FROM
  [sys].[server_audit_specifications] sas
```

Columns and interpretation

- `server_specification_id` (int): Identifier of the server audit specification.
- `Name` (string): Specification name.
- `create_date`, `modify_date` (DateTime): Timestamps for creation and modification.
- `audit_guid` (Guid?): GUID of the associated server audit (if linked).
- `is_state_enabled` (bool?): Whether the specification is currently enabled.

How to interpret

- Server audit specifications define sets of audit actions that are applied by a server audit.
- Use `server_specification_id` to join to `server_audit_specification_details` for the actions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerAuditSpecificationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerAuditSpecificationsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Spec:{r.ServerSpecificationId} Name:{r.Name} Enabled:{r.IsStateEnabled}");
```

See also:

- [sys.server_audit_specifications](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-audit-specifications)

