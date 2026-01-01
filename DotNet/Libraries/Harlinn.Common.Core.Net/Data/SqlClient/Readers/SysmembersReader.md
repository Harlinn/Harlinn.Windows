# SysmembersReader

Overview

`SysmembersReader` wraps `sys.sysmembers` (legacy) and exposes group membership relationships (often database role to member mappings) in older SQL Server systems.

Reader SQL

```
SELECT
  s29.[Memberuid],
  s29.[Groupuid]
FROM
  [sys].[sysmembers] s29
```

Columns and interpretation

- `Memberuid` (smallint?): Identifier (uid) of the member principal (user or role) within the database.
- `Groupuid` (smallint?): Identifier (uid) of the group or role the member belongs to.

How to interpret

- Join `Memberuid` and `Groupuid` to `sysusers` (or `sys.database_principals`) to resolve human-readable principal names.
- This view reflects legacy security metadata; prefer `sys.database_principals` and `sys.database_role_members` in modern versions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysmembersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysmembersReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"MemberUid:{r.Memberuid} GroupUid:{r.Groupuid}");
```

See also:

- [sys.sysmembers](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysmembers)
