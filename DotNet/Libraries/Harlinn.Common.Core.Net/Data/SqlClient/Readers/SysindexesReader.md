# SysindexesReader

Reads rows from the `sys.sysindexes` compatibility view. This view exposes a number of internal fields related to indexes.

Columns and interpretation:

- `Id` (int)
  - Description: Object id of the table or object that the index belongs to.
  - Interpretation: Use to correlate with `sysobjects` or catalog views to find the table.
- `Status` (int?, nullable)
  - Description: Probably/guesswork: index status flags.
  - Interpretation: Bitmask describing index options and state.
- `First` (binary?, nullable)
  - Description: Probably/guesswork: pointer to first page or internal root pointer.
  - Interpretation: Internal binary value used by SQL Server; not directly meaningful outside engine.
- `Indid` (short?, nullable)
  - Description: Index id within the object (0 = heap, 1 = clustered index, >1 = nonclustered indexes).
  - Interpretation: Identifies which index within the table.
- `Root` (binary?, nullable)
  - Description: Probably/guesswork: pointer to root page of the index.
  - Interpretation: Internal engine pointer.
- `Minlen` (short?, nullable)
  - Description: Probably/guesswork: minimum key length.
  - Interpretation: Size in bytes of the smallest index key.
- `Keycnt` (short?, nullable)
  - Description: Number of key columns in the index.
  - Interpretation: The count of columns that form the index key.
- `Groupid` (short?, nullable)
  - Description: Filegroup id where the index resides.
  - Interpretation: References `sysfilegroups` groupid.
- `Dpages` (int?, nullable)
  - Description: Number of data pages used by the index.
  - Interpretation: Page count used by the index structure.
- `Reserved` (int?, nullable)
  - Description: Probably/guesswork: reserved pages.
  - Interpretation: Internal allocation numbers.
- `Used` (int?, nullable)
  - Description: Pages currently used.
  - Interpretation: Internal usage metric.
- `Rowcnt` (long?, nullable)
  - Description: Number of rows covered by the index (approximate).
  - Interpretation: Row count for the underlying table or index.
- `Rowmodctr` (int?, nullable)
  - Description: Row modification counter.
  - Interpretation: Incremented on modifications; used for statistics.
- `Reserved3` (byte?, nullable)
  - Description: Probably/guesswork: internal flag.
  - Interpretation: Internal engine use.
- `Reserved4` (byte?, nullable)
  - Description: Probably/guesswork: internal flag.
  - Interpretation: Internal engine use.
- `Xmaxlen` (short?, nullable)
  - Description: Probably/guesswork: maximum key length.
  - Interpretation: Maximum bytes for the key.
- `Maxirow` (short?, nullable)
  - Description: Probably/guesswork: maximum rows per page or per allocation.
  - Interpretation: Internal.
- `Origfillfactor` (byte?, nullable)
  - Description: Original fill factor for the index.
  - Interpretation: Fill factor when the index was originally created.
- `Statversion` (byte?, nullable)
  - Description: Probably/guesswork: statistics version.
  - Interpretation: Internal versioning for stats.
- `Reserved2` (int?, nullable)
  - Description: Probably/guesswork: internal.
- `Firstiam` (binary?, nullable)
  - Description: Probably/guesswork: pointer to first IAM page.
  - Interpretation: Internal allocation map pointer.
- `Impid` (short?, nullable)
  - Description: Probably/guesswork: partition/impersonation id.
- `Lockflags` (short?, nullable)
  - Description: Probably/guesswork: lock flags configured for the index.
- `Pgmodctr` (int?, nullable)
  - Description: Page modification counter.
  - Interpretation: Internal change counter for pages.
- `Keys` (binary?, nullable)
  - Description: Binary representation of index keys or key metadata.
  - Interpretation: Internal format describing keys.
- `Name` (string?, nullable)
  - Description: Index name.
  - Interpretation: Name used for the index; NULL for heaps.
- `Statblob` (binary?, nullable)
  - Description: Serialized statistics blob.
  - Interpretation: Packed statistics data.
- `Maxlen` (int?, nullable)
  - Description: Probably/guesswork: maximum length for rows in index.
- `Rows` (int?, nullable)
  - Description: Probably/guesswork: number of rows (int sized) - older stores.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysindexesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysindexesReader(reader);
while (r.Read())
{
    Console.WriteLine($"object={r.Id} ind={r.Indid} name={r.Name} keys={r.Keycnt} rows={r.Rowcnt}");
}
```

See also:
- [sys.sysindexes](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysindexes-transact-sql)
