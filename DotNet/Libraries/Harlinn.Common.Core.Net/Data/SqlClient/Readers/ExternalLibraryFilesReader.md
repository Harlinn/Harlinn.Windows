# ExternalLibraryFilesReader — reference

Overview

`ExternalLibraryFilesReader` wraps `sys.external_library_files` and returns binary content and platform metadata for files that make up external libraries.

Reader SQL

```
SELECT
  elf0.[external_library_id],
  elf0.[Content],
  elf0.[Platform],
  elf0.[platform_desc]
FROM
  [sys].[external_library_files] elf0
```

Columns and interpretation

- `external_library_id` — identifier of the external library the file belongs to.
- `Content` — binary content of the file (nullable); may contain the binary payload stored in the catalog.
- `Platform` — numeric platform code (nullable) indicating target platform for the file (e.g., Windows, Linux).
- `platform_desc` — textual description of the platform.

How to interpret

- `Content` can be used to extract the stored file. `PlatformDesc` helps determine which runtime the file targets.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalLibraryFilesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalLibraryFilesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"LibId:{r.ExternalLibraryId} Platform:{r.PlatformDesc} ContentLen:{(r.Content?.Length ?? 0)}");
}
```

See also:

- [sys.external_library_files](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-library-files)
