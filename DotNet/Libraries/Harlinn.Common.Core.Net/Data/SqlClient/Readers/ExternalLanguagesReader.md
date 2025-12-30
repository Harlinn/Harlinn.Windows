# ExternalLanguagesReader — reference

Overview

`ExternalLanguagesReader` wraps `sys.external_languages` and returns registered external languages available in the SQL Server instance, such as language name and creation metadata.

Reader SQL

```
SELECT
  el.[external_language_id],
  el.[Language],
  el.[create_date],
  el.[principal_id]
FROM
  [sys].[external_languages] el
```

Columns and interpretation

- `external_language_id` — id of the external language registration.
- `Language` — name of the external language (e.g., 'Python', 'Java').
- `create_date` — date/time when the language registration was created.
- `principal_id` — owning principal id (nullable).

How to interpret

- Use to enumerate external language support in the server and to see when they were registered.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalLanguagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalLanguagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"LangId:{r.ExternalLanguageId} Language:{r.Language} Created:{r.CreateDate}");
}
```

See also:

- [sys.external_languages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-languages)
