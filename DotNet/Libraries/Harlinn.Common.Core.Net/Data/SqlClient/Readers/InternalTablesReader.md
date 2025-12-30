# InternalTablesReader — reference

Overview

`InternalTablesReader` wraps `sys.internal_tables` and returns metadata for internal system tables that SQL Server creates to support features (for example, internal lob or history tables).

Reader SQL

```
SELECT
  it.[Name],
  it.[object_id],
  it.[principal_id],
  it.[schema_id],
  it.[parent_object_id],
  it.[Type],
  it.[type_desc],
  it.[create_date],
  it.[modify_date],
  it.[is_ms_shipped],
  it.[is_published],
  it.[is_schema_published],
  it.[internal_type],
  it.[internal_type_desc],
  it.[parent_id],
  it.[parent_minor_id],
  it.[lob_data_space_id],
  it.[filestream_data_space_id]
FROM
  [sys].[internal_tables] it
```

Columns and interpretation

- `Name`, `object_id` — name and id of the internal table.
- `principal_id`, `schema_id`, `parent_object_id` — ownership and parent relations.
- `Type` / `type_desc` — object type and textual description.
- `create_date` / `modify_date` — timestamps.
- `is_ms_shipped`, `is_published`, `is_schema_published` — flags about origin and publication.
- `internal_type` / `internal_type_desc` — internal table type and description.
- `parent_id`, `parent_minor_id` — identifiers linking the internal table to its parent object and minor id where relevant.
- `lob_data_space_id`, `filestream_data_space_id` — data space ids for LOB or FILESTREAM storage.

How to interpret

- Internal tables are not user tables but may appear in metadata; use parent fields to link them back to the owning object.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = InternalTablesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new InternalTablesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"InternalTable:{r.Name} Obj:{r.ObjectId} Parent:{r.ParentObjectId} Type:{r.InternalTypeDesc}");
}
```

See also:

- [sys.internal_tables](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-internal-tables)
