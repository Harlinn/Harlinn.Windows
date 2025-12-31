# SysdevicesReader

Reads rows from the `sys.sysdevices` compatibility view. Columns:

- `Name` (string)
  - Description: Device name.
  - Interpretation: Logical device identifier used by SQL Server.
- `Size` (int?, nullable)
  - Description: Size of the device (units depend on SQL Server internal representation).
  - Interpretation: Typically number of pages or blocks.
- `Low` (int?, nullable)
  - Description: Probably/guesswork: lowest allocation unit or low water mark.
  - Interpretation: Internal allocation boundary.
- `High` (int?, nullable)
  - Description: Probably/guesswork: high allocation unit or high water mark.
  - Interpretation: Internal allocation boundary.
- `Status` (short?, nullable)
  - Description: Probably/guesswork: status flags for the device.
  - Interpretation: Indicates online/offline/disabled.
- `Cntrltype` (short?, nullable)
  - Description: Probably/guesswork: control type for the device (backup, tape, disk).
  - Interpretation: Encoded device type.
- `Phyname` (string?, nullable)
  - Description: Physical name or path of the device.
  - Interpretation: File system path or device identifier.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysdevicesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysdevicesReader(reader);
while (r.Read())
{
    Console.WriteLine($"{r.Name}: size={r.Size} status={r.Status} path={r.Phyname}");
}
```

See also:
- [sys.sysdevices](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysdevices-transact-sql)
