# DmDbUncontainedEntitiesReader — reference

Overview

`DmDbUncontainedEntitiesReader` wraps `sys.dm_db_uncontained_entities` and reports entities (features) found in database code that are not contained within the database, such as references to objects in other databases or external features. Useful when assessing database portability and containment.

Reader SQL

```
SELECT
  ddue.[Class],
  ddue.[class_desc],
  ddue.[major_id],
  ddue.[statement_line_number],
  ddue.[statement_offset_begin],
  ddue.[statement_offset_end],
  ddue.[statement_type],
  ddue.[feature_name],
  ddue.[feature_type_name]
FROM
  [sys].[dm_db_uncontained_entities] ddue
```

Columns (detailed)

- `Class` ? `Class` (int)
  - Classification numeric code for the uncontained entity (e.g., object reference, external dependency).

- `class_desc` ? `ClassDesc` (string)
  - Description text for the class.

- `major_id` ? `MajorId` (int)
  - Identifier associated with the entity (object id or other).

- `statement_line_number` ? `StatementLineNumber` (int?)
  - Line number in the source where the uncontained reference appears.

- `statement_offset_begin` / `statement_offset_end` ? offsets (int?) indicating position in the statement text.

- `statement_type` ? `StatementType` (string?)
  - Type of statement containing the uncontained entity (e.g., CREATE PROCEDURE).

- `feature_name` ? `FeatureName` (string)
  - Name of the uncontained feature.

- `feature_type_name` ? `FeatureTypeName` (string)
  - Feature type category name.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbUncontainedEntitiesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new DmDbUncontainedEntitiesReader(reader, ownsReader: false);
while (r.Read())
{
    Console.WriteLine($"Class: {r.Class} {r.ClassDesc} MajorId: {r.MajorId}");
    Console.WriteLine($" Feature: {r.FeatureName} Type: {r.FeatureTypeName}");
    if (r.StatementLineNumber.HasValue)
        Console.WriteLine($" Location: line {r.StatementLineNumber} offsets {r.StatementOffsetBegin}-{r.StatementOffsetEnd}");
}
```

See also:

- [sys.dm_db_uncontained_entities](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-uncontained-entities)
