# DmOsWindowsInfoReader — reference

Overview

`DmOsWindowsInfoReader` wraps `sys.dm_os_windows_info` and provides Windows OS information such as release, service pack and SKU recognized by SQL Server.

Reader SQL

```
SELECT
  dowi.[windows_release],
  dowi.[windows_service_pack_level],
  dowi.[windows_sku],
  dowi.[os_language_version]
FROM
  [sys].[dm_os_windows_info] dowi
```

Columns and interpretation

- `windows_release` — OS release string (e.g., "Windows Server 2019").
- `windows_service_pack_level` — service pack level text.
- `windows_sku` — numeric SKU identifier for the Windows edition (may be NULL).
- `os_language_version` — OS language version identifier.

How to interpret

- Useful for inventory, troubleshooting OS-specific behavior and verifying compatibility.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsWindowsInfoReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsWindowsInfoReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"{r.WindowsRelease} SP:{r.WindowsServicePackLevel} SKU:{r.WindowsSku} LangVer:{r.OsLanguageVersion}");
}
```

See also:

- [sys.dm_os_windows_info](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-windows-info)
