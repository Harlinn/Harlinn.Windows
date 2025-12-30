# SensitivityClassificationsReader

Overview

`SensitivityClassificationsReader` wraps `sys.sensitivity_classifications` and exposes data classification labels applied to database objects and columns.

Reader SQL

```
SELECT
  sc0.[Class],
  sc0.[class_desc],
  sc0.[major_id],
  sc0.[minor_id],
  sc0.[Label],
  sc0.[label_id],
  sc0.[information_type],
  sc0.[information_type_id],
  sc0.[Rank],
  sc0.[rank_desc]
FROM
  [sys].[sensitivity_classifications] sc0
```

Columns and interpretation

- `Class` (int): Securable class code the classification applies to (see `sys.securable_classes`).
- `class_desc` (string): Description of the class.
- `major_id` (int): Major identifier, typically object id.
- `minor_id` (int): Minor identifier, typically column id for column-level classifications.
- `Label` (object?): Label text or user-defined classification label.
- `label_id` (object?): Internal id for the label.
- `information_type` (object?): Information type description (e.g., 'Credit Card Number').
- `information_type_id` (object?): Internal id for the information type.
- `Rank` (object?): Sensitivity rank value (e.g., PA, PII levels).
- `rank_desc` (string?): Descriptive rank text.

How to interpret

- Use `major_id`/`minor_id` together with `Class` to map the classification to a specific object or column.
- `Label`, `InformationType`, and `Rank` describe the sensitivity metadata applied by classification.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SensitivityClassificationsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SensitivityClassificationsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Object:{r.MajorId} Column:{r.MinorId} Label:{r.Label} Rank:{r.RankDesc}");
```

See also:

- [sys.sensitivity_classifications](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sensitivity-classifications)

