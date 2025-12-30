# ExternalLibrariesReader — reference

Overview

`ExternalLibrariesReader` wraps `sys.external_libraries` and returns information about external libraries registered in the database, including their id, name, owner, associated language, and scope.

Reader SQL

```
SELECT
  el0.[external_library_id],
  el0.[Name],
  el0.[principal_id],
  el0.[Language],
  el0.[Scope],
  el0.[scope_desc]
FROM
  [sys].[external_libraries] el0
```

Columns and interpretation

- `external_library_id` — unique identifier for the external library in the database.
- `Name` — name of the external library (nullable).
- `principal_id` — database principal id that owns the library (nullable).
- `Language` — name of the external language associated with the library (nullable), e.g., `Python`, `R`.
- `Scope` — numeric scope code indicating where the library is available (for example database-level or server-level depending on SQL Server feature set).
- `scope_desc` — textual description of the scope.

How to interpret

- Use `Language` and `ScopeDesc` to understand where and how the library is usable. `principal_id` indicates the owner security context.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalLibrariesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalLibrariesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Id:{r.ExternalLibraryId} Name:{r.Name} Lang:{r.Language} Scope:{r.ScopeDesc} Owner:{r.PrincipalId}");
}
```

See also:

- [sys.external_libraries](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-libraries)
