# SysprotectsReader

Overview

`SysprotectsReader` wraps the legacy `sys.sysprotects` view and exposes object-level permissions and protection metadata.

Reader SQL

```
SELECT
  s33.[Id],
  s33.[Uid],
  s33.[Action],
  s33.[Protecttype],
  s33.[Columns],
  s33.[Grantor]
FROM
  [sys].[sysprotects] s33
```

Columns and interpretation

- `Id` (int): Object id the protection applies to.
- `Uid` (smallint?): User id of the grantee principal.
- `Action` (tinyint?): Action code describing the permission type (internal encoding).
- `Protecttype` (tinyint?): Protection type code (for example, grant/deny/with_grant_option; legacy encoding).
- `Columns` (binary?): Bitmask or encoding of columns the permission applies to for column-level permissions.
- `Grantor` (smallint?): User id of the principal that granted the permission.

How to interpret

- `Id` can be joined to `sys.objects`/`sys.sysobjects` to resolve the object name.
- Column-level permissions are encoded in `Columns` and may require decoding or joining to column metadata; prefer modern `sys.database_permissions` for clearer representation.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysprotectsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysprotectsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Object:{r.Id} GranteeUid:{r.Uid} Action:{r.Action} ProtectType:{r.Protecttype} Grantor:{r.Grantor}");
```

See also:

- [sys.sysprotects](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysprotects)
