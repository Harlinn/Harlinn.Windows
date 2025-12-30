# FulltextIndexCatalogUsagesReader — reference

Overview

`FulltextIndexCatalogUsagesReader` wraps `sys.fulltext_index_catalog_usages` and returns which full-text catalog a table or index uses.

Reader SQL

```
SELECT
  ficu.[object_id],
  ficu.[index_id],
  ficu.[fulltext_catalog_id]
FROM
  [sys].[fulltext_index_catalog_usages] ficu
```

Columns and interpretation

- `object_id` — object id of the table using a full-text index.
- `index_id` — index id of the full-text index (nullable if not associated with an index id).
- `fulltext_catalog_id` — id of the full-text catalog used by the object.

How to interpret

- Use to map full-text index ownership to catalogs; useful when moving or auditing catalogs.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextIndexCatalogUsagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextIndexCatalogUsagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Obj:{r.ObjectId} Index:{r.IndexId} Catalog:{r.FulltextCatalogId}");
}
```

See also:

- [sys.fulltext_index_catalog_usages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-index-catalog-usages)
