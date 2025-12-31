# SysindexkeysReader

Reads rows from the `sys.sysindexkeys` compatibility view. Columns:

- `Id` (int)
  - Description: Object id of the table that contains the index.
  - Interpretation: Correlate with `sysobjects` or catalog views.
- `Indid` (short?, nullable)
  - Description: Index id within the object.
  - Interpretation: 0 = heap, 1 = clustered, >1 nonclustered.
- `Colid` (short?, nullable)
  - Description: Column id participating in the index.
  - Interpretation: Column number within the table (use `syscolumns` to map id to column name).
- `Keyno` (short?, nullable)
  - Description: Ordinal position of the column within the index key.
  - Interpretation: 1-based position of the column in the index.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysindexkeysReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysindexkeysReader(reader);
while (r.Read())
{
    Console.WriteLine($"obj={r.Id} ind={r.Indid} col={r.Colid} pos={r.Keyno}");
}
```

See also:
- [sys.sysindexkeys](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysindexkeys-transact-sql)
