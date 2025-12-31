# SysmembersReader

Reads rows from the `sys.sysmembers` compatibility view. This view shows membership relationships between principals.

Columns:

- `Memberuid` (short?, nullable)
  - Description: UID of the member principal.
  - Interpretation: Maps to a principal id within the database.
- `Groupuid` (short?, nullable)
  - Description: UID of the group principal.
  - Interpretation: The group role or principal that contains the member.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysmembersReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysmembersReader(reader);
while (r.Read())
{
    Console.WriteLine($"member {r.Memberuid} in group {r.Groupuid}");
}
```

See also:
- [sys.sysmembers](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysmembers-transact-sql)
