# ExternalLibrariesInstalledReader — reference

Overview

`ExternalLibrariesInstalledReader` wraps `sys.external_libraries_installed` and returns metadata for external libraries installed into a database for use by external languages and packages.

Reader SQL

```
SELECT
  eli.[db_id],
  eli.[principal_id],
  eli.[language_id],
  eli.[external_library_id],
  eli.[Name],
  eli.[Mdversion]
FROM
  [sys].[external_libraries_installed] eli
```

Columns and interpretation

- `db_id` — database id where the library is installed.
- `principal_id` — owning principal id for the installed library.
- `language_id` — external language id associated with the library.
- `external_library_id` — id of the installed external library.
- `Name` — library name.
- `Mdversion` — binary metadata/version information for the library.

How to interpret

- Use to track which external libraries are present in each database and their associated external language and owner.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalLibrariesInstalledReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalLibrariesInstalledReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DbId} Library:{r.Name} LangId:{r.LanguageId} Owner:{r.PrincipalId}");
}
```

See also:

- [sys.external_libraries_installed](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-libraries-installed)
