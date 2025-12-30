# SyscharsetsReader

Overview

`SyscharsetsReader` wraps `sys.syscharsets` and exposes character set metadata (legacy internal view).

Reader SQL

```
SELECT
  s23.[Type],
  s23.[Id],
  s23.[Csid],
  s23.[Status],
  s23.[Name],
  s23.[Description],
  s23.[Binarydefinition],
  s23.[Definition]
FROM
  [sys].[syscharsets] s23
```

Columns and interpretation

- `Type` (short): Internal type code.
- `Id` (byte): Charset id.
- `Csid` (byte): Collation or character set id.
- `Status` (short?): Status flags.
- `Name` (string): Charset name.
- `Description` (string): Description of the charset.
- `Binarydefinition` (binary?): Binary representation of the charset definition.
- `Definition` (binary?): Additional binary definition data.

How to interpret

- This view is legacy; modern SQL Server uses collations and `sys.fn_helpcollations` for collation metadata. Use `Name` to map to known character sets.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscharsetsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscharsetsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Charset:{r.Name} Id:{r.Id} Csid:{r.Csid}");
```

See also:

- sys.syscharsets (legacy)
- [Collation and character set documentation](https://learn.microsoft.com/en-us/sql/t-sql/statements/collations) (general guidance)
