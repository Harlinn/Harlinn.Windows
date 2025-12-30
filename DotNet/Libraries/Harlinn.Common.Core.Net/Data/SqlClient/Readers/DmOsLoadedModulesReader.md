# DmOsLoadedModulesReader — reference

Overview

`DmOsLoadedModulesReader` wraps `sys.dm_os_loaded_modules` and lists loaded binary modules (DLLs/executables) for the SQL Server process along with version and build metadata.

Reader SQL

```
SELECT
  dolm.[base_address],
  dolm.[file_version],
  dolm.[product_version],
  dolm.[Debug],
  dolm.[Patched],
  dolm.[Prerelease],
  dolm.[private_build],
  dolm.[special_build],
  dolm.[Language],
  dolm.[Company],
  dolm.[Description],
  dolm.[Name]
FROM
  [sys].[dm_os_loaded_modules] dolm
```

Columns and interpretation

- `base_address` ? memory base address where module is loaded (binary token).
- `file_version` ? version string from the module file.
- `product_version` ? product version string.
- `Debug` / `Patched` / `Prerelease` / `private_build` / `special_build` ? boolean flags indicating build attributes.
- `Language` ? language code identifier for the module.
- `Company` ? company name from the module metadata.
- `Description` ? file description metadata.
- `Name` ? module file name.

How to interpret

- Use to audit loaded modules, check for unexpected DLLs, and confirm module versions for troubleshooting.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsLoadedModulesReader.Sql;
using var rdr = cmd.ExecuteReader();
var m = new DmOsLoadedModulesReader(rdr, ownsReader:false);
while (m.Read())
{
    Console.WriteLine($"Module:{m.Name} Version:{m.FileVersion} Product:{m.ProductVersion} Debug:{m.Debug} Patched:{m.Patched}");
}
```

See also:

- [sys.dm_os_loaded_modules](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-loaded-modules)
