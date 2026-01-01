# SysindexkeysReader

Overview

`SysindexkeysReader` wraps `sys.sysindexkeys` (legacy) and exposes mapping between indexes and the columns that make up those indexes.

Reader SQL

```
SELECT
  s35.[Id],
  s35.[Indid],
  s35.[Colid],
  s35.[Keyno]
FROM
  [sys].[sysindexkeys] s35
```

Columns and interpretation

- `Id` (int): Object id of the table or indexed view the index belongs to.
- `Indid` (smallint?): Index id within the object (index identifier).
- `Colid` (smallint?): Column id within the table that participates in the index.
- `Keyno` (smallint?): Ordinal position of the column within the index (1-based order).

How to interpret

- Join `Id` to `sys.objects` (or `sys.sysobjects`) to resolve the table name.
- Join `Colid` to `sys.columns` to resolve the column name.
- Combine with `Indid` and `Keyno` to rebuild the index column ordering for multi-column indexes.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysindexkeysReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysindexkeysReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.Id} IndexId:{r.Indid} ColumnId:{r.Colid} Ordinal:{r.Keyno}");
```

See also:

- [sys.sysindexkeys](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysindexkeys)
