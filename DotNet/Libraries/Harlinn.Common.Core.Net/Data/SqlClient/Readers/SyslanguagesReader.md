# SyslanguagesReader

Reads rows from the `sys.syslanguages` compatibility view. Columns:

- `Langid` (short)
  - Description: Language identifier for the language entry.
  - Interpretation: Numeric id used by SQL Server for language settings.
- `Dateformat` (string)
  - Description: Date format string used by the language (e.g., "mdy").
  - Interpretation: Shows the default date format ordering for the language.
- `Datefirst` (byte)
  - Description: First day of week for the language (1 = Monday ... 7 = Sunday depending on SQL Server mapping).
  - Interpretation: Use to determine week start for date functions.
- `Upgrade` (int?, nullable)
  - Description: Probably/guesswork: internal upgrade flag or version.
  - Interpretation: Internal use.
- `Name` (string)
  - Description: Formal language name.
  - Interpretation: Language display name.
- `Alias` (string)
  - Description: Alias for language (short name).
  - Interpretation: Short label used in system messages.
- `Months` (string?, nullable)
  - Description: Probably/guesswork: comma separated full month names.
  - Interpretation: Localized month names.
- `Shortmonths` (string?, nullable)
  - Description: Probably/guesswork: comma separated abbreviated month names.
  - Interpretation: Localized abbreviated month names.
- `Days` (string?, nullable)
  - Description: Probably/guesswork: comma separated day names.
  - Interpretation: Localized day names.
- `Lcid` (int)
  - Description: Windows locale identifier corresponding to the language.
  - Interpretation: Use to map to .NET culture info.
- `Msglangid` (short)
  - Description: Message language id used for system messages.
  - Interpretation: Used for system message localization.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SyslanguagesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SyslanguagesReader(reader);
while (r.Read())
{
    Console.WriteLine($"{r.Langid}: {r.Name} alias={r.Alias} dateFormat={r.Dateformat} dateFirst={r.Datefirst} lcid={r.Lcid}");
}
```

See also:
- [sys.syslanguages](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-syslanguages-transact-sql)
