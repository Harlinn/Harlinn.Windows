# SysfulltextcatalogsReader

Overview

`SysfulltextcatalogsReader` wraps `sys.sysfulltextcatalogs` (legacy) and exposes information about full-text catalogs.

Reader SQL

```
SELECT
  s37.[Ftcatid],
  s37.[Name],
  s37.[Status],
  s37.[Path]
FROM
  [sys].[sysfulltextcatalogs] s37
```

Columns and interpretation

- `Ftcatid` (smallint?): Full-text catalog id.
- `Name` (string): Full-text catalog name.
- `Status` (smallint?): Status flag for the catalog (internal state information such as populated, crawling, etc.).
- `Path` (string?): Physical path for the catalog files.

How to interpret

- Use `Ftcatid` to relate the catalog to full-text index usage or catalog-specific settings.
- `Path` indicates the physical file system location where the catalog stores data.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysfulltextcatalogsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysfulltextcatalogsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Catalog:{r.Name} Id:{r.Ftcatid} Path:{r.Path} Status:{r.Status}");
```

See also:

- [sys.sysfulltextcatalogs](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysfulltextcatalogs)
