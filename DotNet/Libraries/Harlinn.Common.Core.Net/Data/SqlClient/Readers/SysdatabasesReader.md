# SysdatabasesReader

Reads rows from the `sys.sysdatabases` system view / compatibility view. This reader exposes the following columns:

- `Name` (string, nullable)
  - Description: The database name.
  - Interpretation: The logical name of the database.
- `Dbid` (short, nullable)
  - Description: Database ID.
  - Interpretation: Numeric identifier for the database within the SQL Server instance.
- `Sid` (binary, nullable)
  - Description: Probably/guesswork: security identifier (SID) associated with the database owner or principal.
  - Interpretation: Binary representation of a Windows or SQL Server principal SID; can be mapped to logins.
- `Mode` (short, nullable)
  - Description: Probably/guesswork: database mode flags (compatibility, single-user/multi-user, etc.).
  - Interpretation: Bitmask or encoded value indicating database settings.
- `Status` (int, nullable)
  - Description: Probably/guesswork: status flags for the database (online, offline, read-only, etc.).
  - Interpretation: Bitmask of status values; consult SQL Server documentation for exact meanings.
- `Status2` (int, nullable)
  - Description: Probably/guesswork: additional status flags introduced for backward compatibility.
  - Interpretation: Extended status flags; use SQL Server docs for interpretation.
- `Crdate` (DateTime)
  - Description: Creation date of the database.
  - Interpretation: UTC/local creation timestamp when the database was created.
- `Reserved` (DateTime, nullable)
  - Description: Probably/guesswork: date reserved or related timestamp for internal use.
  - Interpretation: Might be used internally; treat as informational.
- `Category` (int, nullable)
  - Description: Probably/guesswork: category identifier for the database.
  - Interpretation: Legacy classification value.
- `Cmptlevel` (byte)
  - Description: Compatibility level of the database.
  - Interpretation: Indicates the T-SQL compatibility level (e.g., 80, 90, 100, 110, 120, 130, 140, 150, 160).
- `Filename` (string, nullable)
  - Description: Primary data file name for the database (path).
  - Interpretation: File system path to the primary data file (.mdf) used by the database.
- `Version` (short, nullable)
  - Description: Probably/guesswork: database internal version number.
  - Interpretation: Internal version used by SQL Server.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysdatabasesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysdatabasesReader(reader);
while (r.Read())
{
    Console.WriteLine($"{r.Name} (id={r.Dbid}) created={r.Crdate} compat={r.Cmptlevel} file={r.Filename}");
}
```

See also:
- [sys.sysdatabases](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysdatabases-transact-sql)
