# ExternalLanguageFilesReader — reference

Overview

`ExternalLanguageFilesReader` wraps `sys.external_language_files` and returns information about external language binary files registered for external languages (e.g., CLR or external runtime files), including content and platform details.

Reader SQL

```
SELECT
  elf.[external_language_id],
  elf.[Content],
  elf.[file_name],
  elf.[Platform],
  elf.[platform_desc],
  elf.[Parameters],
  elf.[environment_variables]
FROM
  [sys].[external_language_files] elf
```

Columns and interpretation

- `external_language_id` — id of the external language.
- `Content` — binary content of the file (nullable), typically the binary payload.
- `file_name` — name of the file (nullable).
- `Platform` / `platform_desc` — numeric platform code and textual description (Windows/Linux etc.)
- `Parameters` — command-line parameters used when launching the external language runtime (nullable).
- `environment_variables` — environment variables configured for runtime invocation (nullable).

How to interpret

- Useful for deployment and diagnostics of external languages and runtimes used by external libraries and languages.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalLanguageFilesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalLanguageFilesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"LangId:{r.ExternalLanguageId} File:{r.FileName} Platform:{r.PlatformDesc} ContentLen:{(r.Content?.Length ?? 0)}");
}
```

See also:

- [sys.external_language_files](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-language-files)
