# SysperfinfoReader

Reads rows from the `sys.sysperfinfo` compatibility view. This view surfaces Windows performance counter data exposed to SQL Server.

Columns:

- `ObjectName` (string)
  - Description: Name of the performance object (e.g., "SQLServer:Buffer Manager").
  - Interpretation: Top-level performance object category.
- `CounterName` (string)
  - Description: Name of the specific performance counter under the object.
  - Interpretation: The counter being measured (e.g., "Page reads/sec").
- `InstanceName` (string?, nullable)
  - Description: Counter instance, if applicable (e.g., database name, filegroup name).
  - Interpretation: Instance qualifier for counters that support instances.
- `CntrValue` (long)
  - Description: Numeric value of the counter.
  - Interpretation: Value as reported by the performance subsystem.
- `CntrType` (int)
  - Description: Counter type code (how to interpret the `CntrValue`, e.g., rate, raw, fraction).
  - Interpretation: Use with `CntrValue` to compute derived values per performance counter semantics.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysperfinfoReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysperfinfoReader(reader);
while (r.Read())
{
    Console.WriteLine($"{r.ObjectName} - {r.CounterName} ({r.InstanceName}): {r.CntrValue} type={r.CntrType}");
}
```

See also:
- [sys.sysperfinfo](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysperfinfo-transact-sql)
