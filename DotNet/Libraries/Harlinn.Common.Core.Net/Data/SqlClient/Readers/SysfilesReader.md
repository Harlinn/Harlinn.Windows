# SysfilesReader

Reads rows from the `sys.sysfiles` compatibility view. Columns:

- `Fileid` (short?, nullable)
  - Description: File ID.
  - Interpretation: Numeric identifier for the file within the database.
- `Groupid` (short?, nullable)
  - Description: Filegroup ID that owns the file.
  - Interpretation: References a filegroup `groupid`.
- `Size` (int)
  - Description: Size of the file in pages.
  - Interpretation: Number of 8 KB pages allocated to the file.
- `Maxsize` (int)
  - Description: Maximum size of the file.
  - Interpretation: Maximum number of pages or special values for unlimited growth.
- `Growth` (int)
  - Description: Growth increment for the file.
  - Interpretation: Growth in pages or percentage depending on how configured.
- `Status` (int?, nullable)
  - Description: Probably/guesswork: status flags for the file (online/offline).
  - Interpretation: Bitmask for file state.
- `Perf` (int?, nullable)
  - Description: Probably/guesswork: performance related flags.
  - Interpretation: Internal performance settings.
- `Name` (string)
  - Description: Logical name of the file.
  - Interpretation: Name used by SQL Server to reference the file.
- `Filename` (string?, nullable)
  - Description: Physical file path.
  - Interpretation: File system path to the file (.mdf, .ndf, .ldf).

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysfilesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysfilesReader(reader);
while (r.Read())
{
    Console.WriteLine($"{r.Name} (id={r.Fileid}) size={r.Size} max={r.Maxsize} growth={r.Growth} file={r.Filename}");
}
```

See also:
- [sys.sysfiles](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysfiles-transact-sql)
