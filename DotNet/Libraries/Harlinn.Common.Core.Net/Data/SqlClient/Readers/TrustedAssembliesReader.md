# TrustedAssembliesReader

Overview

`TrustedAssembliesReader` wraps `sys.trusted_assemblies` and exposes information about assemblies registered as trusted for CLR integration.

Reader SQL

```
SELECT
  ta.[Hash],
  ta.[Description],
  ta.[create_date],
  ta.[created_by]
FROM
  [sys].[trusted_assemblies] ta
```

Columns and interpretation

- `Hash` (varbinary?): Binary hash of the assembly used to identify the trusted assembly entry.
- `Description` (nvarchar?): Human readable description of the assembly or purpose.
- `create_date` (datetime): When the trusted assembly entry was created.
- `created_by` (nvarchar): Principal that created the entry.

How to interpret

- `Hash` corresponds to the fingerprint of the assembly; it is used to identify and verify the exact binary that is trusted.
- Use `created_by` and `create_date` to audit when a trusted assembly was added and by whom.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = TrustedAssembliesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new TrustedAssembliesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Created:{r.CreateDate} By:{r.CreatedBy} Desc:{r.Description} HashLen:{(r.Hash?.Length ?? 0)}");
```

See also:

- [sys.trusted_assemblies](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-trusted-assemblies)
