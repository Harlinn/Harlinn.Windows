# SysmessagesReader

Reads rows from the `sys.sysmessages` compatibility view. This view contains error message definitions and localized descriptions.

Columns:

- `Error` (int)
  - Description: Error number.
  - Interpretation: The numeric error/severity code.
- `Severity` (byte?, nullable)
  - Description: Severity level for the message.
  - Interpretation: Standard severity levels used by SQL Server.
- `Dlevel` (short?, nullable)
  - Description: Probably/guesswork: detail level or state for the message.
  - Interpretation: Internal use for classification.
- `Description` (string?, nullable)
  - Description: Localized description text for the message.
  - Interpretation: Human readable message text.
- `Msglangid` (short)
  - Description: Language id for the message.
  - Interpretation: Indicates localization language for the message.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysmessagesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysmessagesReader(reader);
while (r.Read())
{
    Console.WriteLine($"{r.Error} (sev={r.Severity}) lang={r.Msglangid}: {r.Description}");
}
```

See also:
- [sys.sysmessages](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysmessages-transact-sql)
