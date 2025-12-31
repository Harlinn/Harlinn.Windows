# SysfulltextcatalogsReader

Reads rows from the `sys.sysfulltextcatalogs` compatibility view. Columns:

- `Ftcatid` (short?, nullable)
  - Description: Full-text catalog ID.
  - Interpretation: Numeric identifier for the full-text catalog.
- `Name` (string)
  - Description: Full-text catalog name.
  - Interpretation: Logical name of the catalog used by full-text features.
- `Status` (short?, nullable)
  - Description: Probably/guesswork: status flags for the catalog (populating, idle, etc.).
  - Interpretation: See SQL Server docs for status values and meanings.
- `Path` (string?, nullable)
  - Description: Filesystem path where the full-text catalog files are stored.
  - Interpretation: Directory path on disk for full-text catalog files.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysfulltextcatalogsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysfulltextcatalogsReader(reader);
while (r.Read())
{
    Console.WriteLine($"catalog {r.Ftcatid}: {r.Name} status={r.Status} path={r.Path}");
}
```

See also:
- [sys.sysfulltextcatalogs](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysfulltextcatalogs-transact-sql)
