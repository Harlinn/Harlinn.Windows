# SynonymsReader

Overview

`SynonymsReader` wraps `sys.synonyms` and exposes synonym definitions that provide alternate names for database objects.

Reader SQL

```
SELECT
  s3.[Name],
  s3.[object_id],
  s3.[principal_id],
  s3.[schema_id],
  s3.[parent_object_id],
  s3.[Type],
  s3.[type_desc],
  s3.[create_date],
  s3.[modify_date],
  s3.[is_ms_shipped],
  s3.[is_published],
  s3.[is_schema_published],
  s3.[base_object_name]
FROM
  [sys].[synonyms] s3
```

Columns and interpretation

- `Name` (string): Synonym name.
- `object_id` (int): Object id assigned to the synonym.
- `principal_id` (int?): Principal id owning the synonym.
- `schema_id` (int): Schema id of the synonym.
- `parent_object_id` (int): Parent object id (usually 0 for synonyms).
- `Type`, `type_desc` (string?): Type code and description.
- `create_date`, `modify_date` (DateTime): Timestamps.
- `is_ms_shipped`, `is_published`, `is_schema_published` (bool): Flags for system-shipped, replication publishing, and schema publishing.
- `base_object_name` (string?): The four-part base object name that the synonym references.

How to interpret

- Use `base_object_name` to resolve the actual object the synonym points to. Synonyms are useful for indirection across databases or servers.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SynonymsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SynonymsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Synonym:{r.Name} -> {r.BaseObjectName}");
```

See also:

- [sys.synonyms](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-synonyms)
