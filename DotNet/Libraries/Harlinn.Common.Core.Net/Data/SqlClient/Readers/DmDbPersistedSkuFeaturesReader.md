# DmDbPersistedSkuFeaturesReader — reference

Overview

`DmDbPersistedSkuFeaturesReader` wraps `sys.dm_db_persisted_sku_features` and exposes SKU feature flags persisted for the database. These reflect features that may be toggled or recorded for compatibility and licensing.

Reader SQL

```
SELECT
  ddpsf.[feature_name],
  ddpsf.[feature_id]
FROM
  [sys].[dm_db_persisted_sku_features] ddpsf
```

Columns

- `feature_name` ? `FeatureName` (string?)
  - Name of the persisted SKU feature.

- `feature_id` ? `FeatureId` (int)
  - Numeric identifier for the feature.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbPersistedSkuFeaturesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbPersistedSkuFeaturesReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Feature: {r.FeatureName} (Id: {r.FeatureId})");
}
```

See also:

- [sys.dm_db_persisted_sku_features](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-persisted-sku-features)
