# SequencesReader

Overview

`SequencesReader` wraps `sys.sequences` and exposes metadata and runtime values for sequence objects.

Reader SQL

```
SELECT s.[name]
      ,s.[object_id]
      ,s.[principal_id]
      ,s.[schema_id]
      ,s.[parent_object_id]
      ,s.[type]
      ,s.[type_desc]
      ,s.[create_date]
      ,s.[modify_date]
      ,s.[is_ms_shipped]
      ,s.[is_published]
      ,s.[is_schema_published]
      ,s.[start_value]
      ,s.[increment]
      ,s.[minimum_value]
      ,s.[maximum_value]
      ,s.[is_cycling]
      ,s.[is_cached]
      ,s.[cache_size]
      ,s.[system_type_id]
      ,s.[user_type_id]
      ,s.[precision]
      ,s.[scale]
      ,s.[current_value]
      ,s.[is_exhausted]
      ,s.[last_used_value]
  FROM [sys].[sequences] s
```

Columns and interpretation

- `name` (string): Sequence object name.
- `object_id` (int): Object id of the sequence.
- `principal_id` (int?): Owner principal id.
- `schema_id` (int): Owning schema id.
- `parent_object_id` (int): Parent object id (usually 0 for sequences).
- `type`, `type_desc` (string): Object type and description (SEQUENCE_OBJECT).
- `create_date`, `modify_date` (DateTime): Timestamps.
- `is_ms_shipped`, `is_published`, `is_schema_published` (bool): Flags.
- `start_value`, `increment`, `minimum_value`, `maximum_value` (decimal): Sequence bounds and step.
- `is_cycling` (bool): Whether sequence cycles when limit reached.
- `is_cached` (bool): Whether sequence uses caching.
- `cache_size` (int?): Cache size when caching is enabled.
- `system_type_id` (byte): System type id for sequence values.
- `user_type_id` (int): User type id.
- `precision`, `scale` (byte): Numeric precision and scale.
- `current_value` (decimal?): Current cached/current value visible.
- `is_exhausted` (bool): Whether sequence has been exhausted (no more values if not cycling).
- `last_used_value` (decimal?): Last value handed out by the sequence.

How to interpret

- `current_value` may be NULL for sequences that have no allocated value yet.
- Use `is_exhausted` and `is_cycling` to determine whether new values will be available.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SequencesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SequencesReader(rdr, ownsReader:false);
foreach (var seq in r.GetSequences())
    Console.WriteLine($"{seq.GetName()} Current:{seq.GetCurrentValue()} Start:{seq.GetStartValue()} Increment:{seq.GetIncrement()}");
```

See also:

- [sys.sequences](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sequences)

