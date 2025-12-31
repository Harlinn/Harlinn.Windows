# SysforeignkeysReader

Reads rows from the `sys.sysforeignkeys` compatibility view. Columns:

- `Constid` (int)
  - Description: Constraint ID for the foreign key.
  - Interpretation: Identifier that groups the foreign key constraint rows.
- `Fkeyid` (int)
  - Description: ID of the foreign key's table (object id of the referencing table).
  - Interpretation: Object id identifying the table that has the foreign key.
- `Rkeyid` (int)
  - Description: ID of the referenced table (object id of the primary key table).
  - Interpretation: Object id identifying the referenced table.
- `Fkey` (short?, nullable)
  - Description: Probably/guesswork: column id in the referencing table.
  - Interpretation: Column number in the referencing table that participates in the foreign key.
- `Rkey` (short?, nullable)
  - Description: Probably/guesswork: column id in the referenced table.
  - Interpretation: Column number in the referenced table that is referenced.
- `Keyno` (short?, nullable)
  - Description: Probably/guesswork: ordinal position within the key.
  - Interpretation: Position of the column within the key.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysforeignkeysReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysforeignkeysReader(reader);
while (r.Read())
{
    Console.WriteLine($"fk const={r.Constid} fromTable={r.Fkeyid} toTable={r.Rkeyid} col={r.Fkey} -> {r.Rkey}");
}
```

See also:
- [sys.sysforeignkeys](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysforeignkeys-transact-sql)
