# ExternalLibrarySetupErrorsReader — reference

Overview

`ExternalLibrarySetupErrorsReader` wraps `sys.external_library_setup_errors` and returns errors that occurred during installation or setup of external libraries in databases.

Reader SQL

```
SELECT
  else.[db_id],
  else.[principal_id],
  else.[external_library_id],
  else.[error_code],
  else.[error_timestamp],
  else.[error_message]
FROM
  [sys].[external_library_setup_errors] else
```

Columns and interpretation

- `db_id` — database id where the setup error occurred.
- `principal_id` — principal id associated with the setup operation.
- `external_library_id` — id of the external library for which setup failed.
- `error_code` — numeric error code returned by the setup process or runtime.
- `error_timestamp` — timestamp when the error was recorded.
- `error_message` — textual error message (nullable) describing the failure.

How to interpret

- Use `error_code` and `error_message` to diagnose why an external library failed to be installed or configured in a database. `db_id` helps locate the database in multi-database contexts.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalLibrarySetupErrorsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalLibrarySetupErrorsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DbId} Lib:{r.ExternalLibraryId} Code:{r.ErrorCode} Time:{r.ErrorTimestamp} Msg:{r.ErrorMessage}");
}
```

See also:

- [sys.external_library_setup_errors](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-library-setup-errors)
