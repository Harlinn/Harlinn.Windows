# FulltextCatalogsReader — reference

Overview

`FulltextCatalogsReader` wraps `sys.fulltext_catalogs` and returns information about full-text catalogs, including path, default flag, accent sensitivity, and import status.

Reader SQL

```
SELECT
  fc.[fulltext_catalog_id],
  fc.[Name],
  fc.[Path],
  fc.[is_default],
  fc.[is_accent_sensitivity_on],
  fc.[data_space_id],
  fc.[file_id],
  fc.[principal_id],
  fc.[is_importing]
FROM
  [sys].[fulltext_catalogs] fc
```

Columns and interpretation

- `fulltext_catalog_id` — id of the full-text catalog.
- `Name` — catalog name.
- `Path` — file system path where catalog data is stored (nullable).
- `is_default` — whether this catalog is the default full-text catalog for the database.
- `is_accent_sensitivity_on` — whether accent sensitivity is enabled for the catalog.
- `data_space_id` — data space id related to the catalog storage.
- `file_id` — file id if catalog is stored in a specific file (nullable).
- `principal_id` — principal id owner of the catalog (nullable).
- `is_importing` — whether a catalog import operation is in progress.

How to interpret

- Catalogs are the storage containers for full-text indexes; `Path` shows storage location. `is_importing` indicates active import state.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextCatalogsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextCatalogsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Catalog:{r.Name} Id:{r.FulltextCatalogId} Path:{r.Path} Default:{r.IsDefault} Accent:{r.IsAccentSensitivityOn}");
}
```

See also:

- [sys.fulltext_catalogs](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-catalogs)
