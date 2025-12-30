# SpatialIndexTessellationsReader

Overview

`SpatialIndexTessellationsReader` wraps `sys.spatial_index_tessellations` and exposes tessellation grid details for spatial indexes.

Reader SQL

```
SELECT
  sit.[object_id],
  sit.[index_id],
  sit.[tessellation_scheme],
  sit.[bounding_box_xmin],
  sit.[bounding_box_ymin],
  sit.[bounding_box_xmax],
  sit.[bounding_box_ymax],
  sit.[level_1_grid],
  sit.[level_1_grid_desc],
  sit.[level_2_grid],
  sit.[level_2_grid_desc],
  sit.[level_3_grid],
  sit.[level_3_grid_desc],
  sit.[level_4_grid],
  sit.[level_4_grid_desc],
  sit.[cells_per_object]
FROM
  [sys].[spatial_index_tessellations] sit
```

Columns and interpretation

- `object_id`, `index_id` (int): Identify the index this tessellation applies to.
- `tessellation_scheme` (string?): Tessellation scheme identifier.
- `bounding_box_xmin`, `bounding_box_ymin`, `bounding_box_xmax`, `bounding_box_ymax` (double?): Bounding box coordinates for the tessellation grid.
- `level_n_grid` (short?): Grid size (number of cells across) for tessellation level n.
- `level_n_grid_desc` (string?): Description of the grid at level n.
- `cells_per_object` (int?): Typical number of grid cells mapped to a single object.

How to interpret

- Tessellations define how spatial space is partitioned for indexing. Grid levels provide multi-resolution indexing; bounding box bounds the spatial index coverage.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SpatialIndexTessellationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SpatialIndexTessellationsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Index:{r.IndexId} Scheme:{r.TessellationScheme} Levels:{r.Level1Grid}/{r.Level2Grid}/{r.Level3Grid}/{r.Level4Grid}");
```

See also:

- [sys.spatial_index_tessellations](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-spatial-index-tessellations)
