# SyspermissionsReader

Reads rows from the `sys.syspermissions` compatibility view. This view contains permission entries.

Columns:

- `Id` (int)
  - Description: Object id or securable id the permission applies to.
  - Interpretation: Map to the securable (object, table, etc.).
- `Grantee` (short?, nullable)
  - Description: UID of the grantee principal.
  - Interpretation: Principal within the database who receives the permission.
- `Grantor` (short?, nullable)
  - Description: UID of the grantor principal.
  - Interpretation: Principal who granted the permission.
- `Actadd` (short?, nullable)
  - Description: Probably/guesswork: action add flag for permissions.
  - Interpretation: Encoded permission action bits.
- `Actmod` (short?, nullable)
  - Description: Probably/guesswork: action modify flag.
- `Seladd` (binary?, nullable)
  - Description: Probably/guesswork: selector add bitmask for SELECT permission.
  - Interpretation: Binary representation of permission details.
- `Selmod` (binary?, nullable)
  - Description: Probably/guesswork: selector modify bitmask.
- `Updadd` (binary?, nullable)
  - Description: Probably/guesswork: update add bitmask.
- `Updmod` (binary?, nullable)
  - Description: Probably/guesswork: update modify bitmask.
- `Refadd` (binary?, nullable)
  - Description: Probably/guesswork: reference add bitmask.
- `Refmod` (binary?, nullable)
  - Description: Probably/guesswork: reference modify bitmask.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SyspermissionsReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SyspermissionsReader(reader);
while (r.Read())
{
    Console.WriteLine($"securable={r.Id} grantee={r.Grantee} grantor={r.Grantor}");
}
```

See also:
- [sys.syspermissions](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-syspermissions-transact-sql)
