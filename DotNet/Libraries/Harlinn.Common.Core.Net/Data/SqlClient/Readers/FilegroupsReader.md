# FilegroupsReader — reference

Overview

`FilegroupsReader` wraps `sys.filegroups` and returns information about database filegroups, including identifiers, type, and options like default and read-only status.

Reader SQL

```
SELECT
  f0.[Name],
  f0.[data_space_id],
  f0.[Type],
  f0.[type_desc],
  f0.[is_default],
  f0.[is_system],
  f0.[filegroup_guid],
  f0.[log_filegroup_id],
  f0.[is_read_only],
  f0.[is_autogrow_all_files]
FROM
  [sys].[filegroups] f0
```

Columns and interpretation

- `Name` — filegroup name.
- `data_space_id` — identifier for the data space (filegroup) in the database.
- `Type` / `type_desc` — filegroup type and textual description.
- `is_default` — whether this filegroup is the default for object allocation.
- `is_system` — whether this is a system-defined filegroup.
- `filegroup_guid` — unique GUID for the filegroup (nullable).
- `log_filegroup_id` — id of an associated log filegroup if any (nullable).
- `is_read_only` — whether the filegroup is set to read-only.
- `is_autogrow_all_files` — whether autogrow should affect all files in the group.

How to interpret

- Default filegroup receives new object allocations when no filegroup is specified. Read-only filegroups are used for static data.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FilegroupsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FilegroupsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"FG:{r.Name} Id:{r.DataSpaceId} Default:{r.IsDefault} ReadOnly:{r.IsReadOnly} GUID:{r.FilegroupGuid}");
}
```

See also:

- [sys.filegroups](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-filegroups)
