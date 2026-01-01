# TimeZoneInfoReader

Overview

`TimeZoneInfoReader` wraps `sys.time_zone_info` and exposes available time zone information on the SQL Server host.

Reader SQL

```
SELECT
  tzi.[Name],
  tzi.[current_utc_offset],
  tzi.[is_currently_dst]
FROM
  [sys].[time_zone_info] tzi
```

Columns and interpretation

- `Name` (string): Time zone name (Windows time zone identifier).
- `current_utc_offset` (string): Current UTC offset in hours/minutes as a string (format depends on SQL Server representation).
- `is_currently_dst` (bit): Whether the time zone is currently observing Daylight Saving Time.

How to interpret

- Use the `Name` to map to .NET `TimeZoneInfo` or Windows time zone identifiers for conversions.
- `current_utc_offset` is the current offset; for historical or future offsets consult system time zone data.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TimeZoneInfoReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TimeZoneInfoReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"TZ:{r.Name} Offset:{r.CurrentUtcOffset} DST:{r.IsCurrentlyDst}");
```

See also:

- [sys.time_zone_info](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-time-zone-info)
