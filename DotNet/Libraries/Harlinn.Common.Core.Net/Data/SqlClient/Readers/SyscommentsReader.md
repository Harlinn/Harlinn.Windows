# SyscommentsReader

Overview

`SyscommentsReader` wraps `sys.syscomments` and exposes legacy text fragments for object definitions (e.g., object text split into chunks).

Reader SQL

```
SELECT
  s41.[Id],
  s41.[Number],
  s41.[Colid],
  s41.[Status],
  s41.[Ctext],
  s41.[Texttype],
  s41.[Language],
  s41.[Encrypted],
  s41.[Compressed],
  s41.[Text]
FROM
  [sys].[syscomments] s41
```

Columns and interpretation

- `Id` (int): Object id the text fragment belongs to.
- `Number` (short?): Sequence number for the text fragments.
- `Colid` (short): Column id when applicable.
- `Status` (short): Status flags.
- `Ctext` (binary?): Binary text fragment for older storage formats.
- `Texttype` (short?): Type code for the text chunk.
- `Language` (short?): Language id.
- `Encrypted`, `Compressed` (bool): Flags indicating encryption/compression of the text.
- `Text` (string?): The textual content of the fragment (may be NULL when stored as `Ctext`).

How to interpret

- `sys.syscomments` historically stored large object definitions split into multiple rows; modern systems use `sys.sql_modules.definition`. Reassemble fragments by ordering on `Number` to obtain full object text.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscommentsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscommentsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Id:{r.Id} Seq:{r.Number} Encrypted:{r.Encrypted} TextLen:{r.Text?.Length}");
```

See also:

- sys.syscomments (legacy)
- [sys.sql_modules](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sql-modules) (modern replacement for module text)
