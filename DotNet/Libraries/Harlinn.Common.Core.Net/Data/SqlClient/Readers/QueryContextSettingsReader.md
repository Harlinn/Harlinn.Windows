# QueryContextSettingsReader — reference

Overview

`QueryContextSettingsReader` wraps `sys.query_context_settings` and returns details about saved query compilation/plan context, including SET options, language and cursor options.

Reader SQL

```
SELECT
  qcs.[context_settings_id],
  qcs.[set_options],
  qcs.[language_id],
  qcs.[date_format],
  qcs.[date_first],
  qcs.[Status],
  qcs.[required_cursor_options],
  qcs.[acceptable_cursor_options],
  qcs.[merge_action_type],
  qcs.[default_schema_id],
  qcs.[is_replication_specific],
  qcs.[is_contained]
FROM
  [sys].[query_context_settings] qcs
```

Columns and interpretation

- `context_settings_id` — unique id for the context settings.
- `set_options` — binary blob representing SET options for the context (e.g., QUOTED_IDENTIFIER, ANSI_NULLS).
- `language_id` — language id for the session.
- `date_format` — numeric code for date format.
- `date_first` — first day of week setting.
- `Status` — binary status blob describing additional flags.
- `required_cursor_options` / `acceptable_cursor_options` — bitmask of cursor options required/acceptable.
- `merge_action_type` — code referencing merge action type behavior.
- `default_schema_id` — default schema id associated with the context.
- `is_replication_specific` — whether context was created for replication scenarios.
- `is_contained` — binary/flag indicating containment state.

How to interpret

- This view allows correlating query texts and plans to the session options used at compile time, important for reproducible plan behavior. Binary blobs (SET options, Status) must be decoded according to server bitmask definitions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = QueryContextSettingsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new QueryContextSettingsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"ContextId:{r.ContextSettingsId} Lang:{r.LanguageId} DateFmt:{r.DateFormat} DefaultSchema:{r.DefaultSchemaId}");
}
```

See also:

- [sys.query_context_settings](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-query-context-settings)
