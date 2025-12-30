# MessagesReader — reference

Overview

`MessagesReader` wraps `sys.messages` and returns error and informational messages defined in the server's message catalog, including text and severity.

Reader SQL

```
SELECT
  m.[message_id],
  m.[language_id],
  m.[Severity],
  m.[is_event_logged],
  m.[Text]
FROM
  [sys].[messages] m
```

Columns and interpretation

- `message_id` — numeric message identifier.
- `language_id` — language LCID for the message text.
- `Severity` — severity level associated with the message.
- `is_event_logged` — whether occurrences of this message are logged to the Windows event log.
- `Text` — the message text.

How to interpret

- Use `message_id` and `language_id` to look up localized message text. `Severity` helps classify message criticality.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = MessagesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new MessagesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Msg:{r.MessageId} Lang:{r.LanguageId} Sev:{r.Severity} Text:{r.Text}");
}
```

See also:

- [sys.messages](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-messages)
