# SysindexesReader

Overview

`SysindexesReader` wraps `sys.sysindexes` (legacy) and exposes index metadata for tables.

Reader SQL

```
SELECT
  s36.[Id],
  s36.[Status],
  s36.[First],
  s36.[Indid],
  s36.[Root],
  s36.[Minlen],
  s36.[Keycnt],
  s36.[Groupid],
  s36.[Dpages],
  s36.[Reserved],
  s36.[Used],
  s36.[Rowcnt],
  s36.[Rowmodctr],
  s36.[Reserved3],
  s36.[Reserved4],
  s36.[Xmaxlen],
  s36.[Maxirow],
  s36.[Origfillfactor],
  s36.[Statversion],
  s36.[Reserved2],
  s36.[Firstiam],
  s36.[Impid],
  s36.[Lockflags],
  s36.[Pgmodctr],
  s36.[Keys],
  s36.[Name],
  s36.[Statblob],
  s36.[Maxlen],
  s36.[Rows]
FROM
  [sys].[sysindexes] s36
```

Columns and interpretation

- `Id` (int): Object id of the table or indexed view the index belongs to.
- `Status` (int?): Status bitmask for index properties (internal flags for clustered, unique, padded, etc.).
- `First` (binary?): Internal pointer to first page or first key (internal binary format).
- `Indid` (smallint?): Index id within the object (0 = heap, 1 = clustered, >1 nonclustered index ids).
- `Root` (binary?): Internal pointer to root page for the index (internal binary format).
- `Minlen` (smallint?): Minimum key length for the index keys.
- `Keycnt` (smallint?): Number of key columns in the index.
- `Groupid` (smallint?): Filegroup id or partition group for the index.
- `Dpages` (int?): Data pages count used by the index.
- `Reserved` (int?): Reserved pages count.
- `Used` (int?): Used pages count.
- `Rowcnt` (bigint?): Row count estimate for the index/table.
- `Rowmodctr` (int?): Row modification counter.
- `Reserved3` (byte?): Internal reserved field.
- `Reserved4` (byte?): Internal reserved field.
- `Xmaxlen` (smallint?): Maximum key length.
- `Maxirow` (smallint?): Maximum row size allowed for the index.
- `Origfillfactor` (byte?): Original fill factor set when index was created.
- `Statversion` (byte?): Statistics version for index.
- `Reserved2` (int?): Internal reserved field.
- `Firstiam` (binary?): Internal pointer to first IAM page.
- `Impid` (smallint?): Implicit id for internal structures.
- `Lockflags` (smallint?): Lock flags used by the index.
- `Pgmodctr` (int?): Page modification counter.
- `Keys` (binary?): Encoded key info (internal binary data describing keys).
- `Name` (string?): Index name (may be NULL for heaps or internal indexes).
- `Statblob` (binary?): Statistics blob for indexed column statistics.
- `Maxlen` (int?): Maximum length of index keys in bytes.
- `Rows` (int?): Deprecated/legacy row count field.

How to interpret

- `Id` joined to `sys.objects` (or `sys.sysobjects`) gives the table name.
- `Indid` identifies the type of index: `0` = heap, `1` = clustered index, `>1` = nonclustered.
- Many binary fields (`First`, `Root`, `Keys`, `Firstiam`) are internal pointers and not intended for direct interpretation; use modern catalog views (`sys.indexes`, `sys.index_columns`, `sys.dm_db_index_physical_stats`) for detailed index information.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysindexesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysindexesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.Id} IndexId:{r.Indid} Name:{r.Name} KeyCols:{r.Keycnt} Rows:{r.Rowcnt}");
```

See also:

- [sys.sysindexes](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysindexes)
