# SecurityPoliciesReader

Overview

`SecurityPoliciesReader` wraps `sys.security_policies` and exposes information about row-level security policies defined in the database.

Reader SQL

```
SELECT
  sp0.[Name],
  sp0.[object_id],
  sp0.[principal_id],
  sp0.[schema_id],
  sp0.[parent_object_id],
  sp0.[Type],
  sp0.[type_desc],
  sp0.[create_date],
  sp0.[modify_date],
  sp0.[is_ms_shipped],
  sp0.[is_enabled],
  sp0.[is_not_for_replication],
  sp0.[uses_database_collation],
  sp0.[is_schema_bound]
FROM
  [sys].[security_policies] sp0
```

Columns and interpretation

- `Name` (string): Name of the security policy.
- `object_id` (int): Object id of the security policy object.
- `principal_id` (int?): Owning principal id.
- `schema_id` (int): Owning schema id.
- `parent_object_id` (int): Parent object id if applicable.
- `Type` (string?): Type code.
- `type_desc` (string?): Descriptive type text.
- `create_date` (DateTime): Creation timestamp.
- `modify_date` (DateTime): Last modification timestamp.
- `is_ms_shipped` (bool): Whether the policy is Microsoft-shipped.
- `is_enabled` (bool): Whether the policy is enabled.
- `is_not_for_replication` (bool): Whether the policy is disabled for replication.
- `uses_database_collation` (bool?): Whether the policy uses database collation.
- `is_schema_bound` (bool): Whether the policy is schema bound.

How to interpret

- Row-level security policies restrict row visibility or modification; `is_enabled` indicates whether the policy is in effect.
- `is_schema_bound` indicates if the policy's associated functions are schema-bound (affects maintenance and changes).

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SecurityPoliciesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SecurityPoliciesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Policy:{r.Name} Enabled:{r.IsEnabled} SchemaBound:{r.IsSchemaBound}");
```

See also:

- [sys.security_policies](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-security-policies)

