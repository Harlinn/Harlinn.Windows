# SysopentapesReader

Reads rows from the `sys.sysopentapes` compatibility view. This view lists locations for open tape devices or tape drives used for backups.

Columns:

- `Opentape` (string)
  - Description: Device or path for the open tape.
  - Interpretation: Path or logical name for tape device.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysopentapesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysopentapesReader(reader);
while (r.Read())
{
    Console.WriteLine($"open tape: {r.Opentape}");
}
```

See also:
- [sys.sysopentapes](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysopentapes-transact-sql)
