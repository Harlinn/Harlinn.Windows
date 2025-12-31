# SysdependsReader

Reads rows from the `sys.sysdepends` compatibility view. The reader exposes columns returned by the view:

- `Id` (int)
  - Description: ID of the object that has a dependency.
  - Interpretation: Object identifier (object id) referencing the dependent object.
- `Depid` (int)
  - Description: ID of the object being depended on.
  - Interpretation: Object id of the referenced object.
- `Number` (short, nullable)
  - Description: Probably/guesswork: number identifying a sub-part (e.g., column number) of the `Id` object.
  - Interpretation: Use when dependencies are on specific columns or subcomponents.
- `Depnumber` (short, nullable)
  - Description: Probably/guesswork: number identifying a sub-part of the `Depid` object.
  - Interpretation: Use when referenced object is a column or similar.
- `Status` (short, nullable)
  - Description: Probably/guesswork: status flags about the dependency entry.
  - Interpretation: May indicate validity, deferred resolution, or other internal state.
- `Deptype` (byte)
  - Description: Probably/guesswork: dependency type indicator.
  - Interpretation: Encoded type of dependency (e.g., object, column, expression).
- `Depdbid` (short, nullable)
  - Description: Probably/guesswork: database ID where the dependent object resides.
  - Interpretation: If cross-database, indicates database id.
- `Depsiteid` (short, nullable)
  - Description: Probably/guesswork: site ID or partition ID for databases with siting.
  - Interpretation: Internal use; rarely needed.
- `Selall` (bool)
  - Description: Probably/guesswork: whether the dependency covers all columns (e.g., SELECT *).
  - Interpretation: True if dependency includes all columns.
- `Resultobj` (bool)
  - Description: Probably/guesswork: whether the dependency refers to a result set object.
  - Interpretation: True if referencing a derived result object.
- `Readobj` (bool)
  - Description: Probably/guesswork: whether the dependency is a read-only dependency.
  - Interpretation: True for read access dependencies.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysdependsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysdependsReader(reader);
while (r.Read())
{
    Console.WriteLine($"object {r.Id}/{r.Number} depends on {r.Depid}/{r.Depnumber} type={r.Deptype} selAll={r.Selall}");
}
```

See also:
- [sys.sysdepends](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysdepends-transact-sql)
