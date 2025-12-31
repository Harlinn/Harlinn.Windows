# SysfilegroupsReader

Reads rows from the `sys.sysfilegroups` compatibility view. Columns:

- `Groupid` (short?, nullable)
  - Description: Filegroup ID.
  - Interpretation: Numeric identifier of the filegroup within the database.
- `Allocpolicy` (short?, nullable)
  - Description: Probably/guesswork: allocation policy for the filegroup.
  - Interpretation: Encoded value describing allocation behavior (e.g., uniform, proportional).
- `Status` (int?, nullable)
  - Description: Probably/guesswork: status flags for the filegroup.
  - Interpretation: Indicate read-only, offline or other states.
- `Groupname` (string)
  - Description: Name of the filegroup.
  - Interpretation: Logical name used for filegroup creation and assignment.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysfilegroupsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysfilegroupsReader(reader);
while (r.Read())
{
    Console.WriteLine($"filegroup {r.Groupid}: {r.Groupname} allocPolicy={r.Allocpolicy} status={r.Status}");
}
```

See also:
- [sys.sysfilegroups](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysfilegroups-transact-sql)
