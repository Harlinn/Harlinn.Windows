# SyspermissionsReader

Overview

`SyspermissionsReader` wraps `sys.syspermissions` (legacy) and exposes permission bits for database objects and principals.

Reader SQL

```
SELECT
  s34.[Id],
  s34.[Grantee],
  s34.[Grantor],
  s34.[Actadd],
  s34.[Actmod],
  s34.[Seladd],
  s34.[Selmod],
  s34.[Updadd],
  s34.[Updmod],
  s34.[Refadd],
  s34.[Refmod]
FROM
  [sys].[syspermissions] s34
```

Columns and interpretation

- `Id` (int): Object id the permissions apply to (object-level permissions) or principal id for server-level entries.
- `Grantee` (smallint?): User id (uid) of the grantee principal.
- `Grantor` (smallint?): User id (uid) of the grantor principal.
- `Actadd` (smallint?): Action add flag (internal; indicates execute/act permissions granted).
- `Actmod` (smallint?): Action modify flag (internal modify permission representation).
- `Seladd` (binary?): Selection permissions bitmask or encoded representation.
- `Selmod` (binary?): Selection modification bitmask or encoded representation.
- `Updadd` (binary?): Update add bitmask.
- `Updmod` (binary?): Update modify bitmask.
- `Refadd` (binary?): Reference add bitmask (REFERENCES permission details).
- `Refmod` (binary?): Reference modify bitmask.

How to interpret

- These columns are a legacy compact representation of permissions; for modern systems use `sys.database_permissions`, `sys.database_principals`, and `sys.objects` for clearer semantics.
- Join `Id` to `sys.objects` or appropriate principal tables to resolve names.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyspermissionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyspermissionsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"ObjectId:{r.Id} Grantee:{r.Grantee} Grantor:{r.Grantor} SelMask:{(r.Seladd!=null?BitConverter.ToString(r.Seladd):"<null>")}");
```

See also:

- [sys.syspermissions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-syspermissions)
