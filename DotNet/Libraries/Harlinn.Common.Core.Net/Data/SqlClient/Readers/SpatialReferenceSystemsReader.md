# SpatialReferenceSystemsReader

Overview

`SpatialReferenceSystemsReader` wraps `sys.spatial_reference_systems` and exposes coordinate reference system definitions used by spatial types.

Reader SQL

```
SELECT
  srs.[spatial_reference_id],
  srs.[authority_name],
  srs.[authorized_spatial_reference_id],
  srs.[well_known_text],
  srs.[unit_of_measure],
  srs.[unit_conversion_factor]
FROM
  [sys].[spatial_reference_systems] srs
```

Columns and interpretation

- `spatial_reference_id` (int?): SRID used by geometry/geography columns.
- `authority_name` (string?): Authoritative body name (e.g., 'EPSG').
- `authorized_spatial_reference_id` (int?): Authority-specific SRID.
- `well_known_text` (string?): Well-Known Text (WKT) representation of the spatial reference system.
- `unit_of_measure` (string?): Unit of measure for the SRID (e.g., 'metre').
- `unit_conversion_factor` (double?): Conversion factor to meters (or base unit) depending on server definition.

How to interpret

- SRIDs determine coordinate math and computations. `well_known_text` provides full projection definition; `unit_conversion_factor` helps convert between units.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SpatialReferenceSystemsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SpatialReferenceSystemsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"SRID:{r.SpatialReferenceId} Authority:{r.AuthorityName} Unit:{r.UnitOfMeasure}");
```

See also:

- [sys.spatial_reference_systems](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-spatial-reference-systems)
