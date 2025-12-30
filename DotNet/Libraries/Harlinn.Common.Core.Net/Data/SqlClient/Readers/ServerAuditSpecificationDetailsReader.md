# ServerAuditSpecificationDetailsReader

Overview

`ServerAuditSpecificationDetailsReader` wraps `sys.server_audit_specification_details` and exposes the individual audit actions configured in server audit specifications.

Reader SQL

```
SELECT
  sasd.[server_specification_id],
  sasd.[audit_action_id],
  sasd.[audit_action_name],
  sasd.[Class],
  sasd.[class_desc],
  sasd.[major_id],
  sasd.[minor_id],
  sasd.[audited_principal_id],
  sasd.[audited_result],
  sasd.[is_group]
FROM
  [sys].[server_audit_specification_details] sasd
```

Columns and interpretation

- `server_specification_id` (int): Identifier of the server audit specification the action belongs to.
- `audit_action_id` (string): Identifier of the audit action (internal code).
- `audit_action_name` (string?): Human readable name of the audit action.
- `Class` (byte): Securable class code related to the action.
- `class_desc` (string?): Description of the class.
- `major_id` (int): Major id (object id) the action targets.
- `minor_id` (int): Minor id (e.g., column id) the action targets.
- `audited_principal_id` (int): Principal id being audited, if any.
- `audited_result` (string?): Result filter string (e.g., success/failure) for the action.
- `is_group` (bool?): Whether the action represents a group of actions.

How to interpret

- Use these rows to enumerate what specific audit actions are captured by a server audit specification.
- Join `server_specification_id` to `sys.server_audit_specifications` to get specification name.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerAuditSpecificationDetailsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerAuditSpecificationDetailsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Spec:{r.ServerSpecificationId} Action:{r.AuditActionName} Class:{r.ClassDesc} Result:{r.AuditedResult}");
```

See also:

- [sys.server_audit_specification_details](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-audit-specification-details)

