# SpatialIndexesReader

Overview

`SpatialIndexesReader` wraps `sys.spatial_indexes` and exposes metadata for spatial indexes on geometry/geography columns.

Reader SQL

```
SELECT
  si.[object_id],
  si.[Name],
  si.[index_id],
  si.[Type],
  si.[type_desc],
  si.[is_unique],
  si.[data_space_id],
  si.[ignore_dup_key],
  si.[is_primary_key],
  si.[is_unique_constraint],
  si.[fill_factor],
  si.[is_padded],
  si.[is_disabled],
  si.[is_hypothetical],
  si.[is_ignored_in_optimization],
  si.[allow_row_locks],
  si.[allow_page_locks],
  si.[spatial_index_type],
  si.[spatial_index_type_desc],
  si.[tessellation_scheme],
  si.[has_filter],
  si.[filter_definition],
  si.[auto_created]
FROM
  [sys].[spatial_indexes] si
```

Columns and interpretation

- `object_id` (int): Object id of the table containing the spatial column.
- `Name` (string?): Index name.
- `index_id` (int): Index id.
- `Type`, `type_desc` (byte/string?): Index type and description (CLUSTERED/NONCLUSTERED etc.).
- `is_unique`, `is_primary_key`, `is_unique_constraint` (bool?): Uniqueness flags.
- `data_space_id` (int): Filegroup or partition scheme id where the index resides.
- `ignore_dup_key` (bool?): Whether duplicate keys are ignored.
- `fill_factor` (byte): Fill factor percentage.
- `is_padded`, `is_disabled`, `is_hypothetical`, `is_ignored_in_optimization` (bool?): Various index states.
- `allow_row_locks`, `allow_page_locks` (bool?): Locking options.
- `spatial_index_type`, `spatial_index_type_desc` (int/string?): Spatial index algorithm type and description.
- `tessellation_scheme` (string?): Tessellation scheme used (e.g., GEOMETRY_GRID or GEOGRAPHY_GRID with levels).
- `has_filter` (bool): Whether the index is filtered.
- `filter_definition` (string?): Filter predicate defining filtered index rows.
- `auto_created` (bool?): Whether the index was auto-created by the optimizer.

How to interpret

- Spatial index properties determine query performance for spatial predicates. `tessellation_scheme` and `spatial_index_type_desc` indicate how spatial data is indexed internally.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SpatialIndexesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SpatialIndexesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Index:{r.Name} Object:{r.ObjectId} Tessellation:{r.TessellationScheme} AutoCreated:{r.AutoCreated}");
```

See also:

- [sys.spatial_indexes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-spatial-indexes)
