# DmOsHostInfoReader — reference

Overview

`DmOsHostInfoReader` wraps `sys.dm_os_host_info` and provides information about the underlying host environment for SQL Server, including platform, distribution, release, service pack, SKU and architecture.

Reader SQL

```
SELECT
  dohi.[host_platform],
  dohi.[host_distribution],
  dohi.[host_release],
  dohi.[host_service_pack_level],
  dohi.[host_sku],
  dohi.[os_language_version],
  dohi.[host_architecture]
FROM
  [sys].[dm_os_host_info] dohi
```

Columns and interpretation

- `host_platform` ? host OS platform (string) — e.g., "Windows", "Linux".
- `host_distribution` ? distribution name (string) — for Linux, distribution like "Ubuntu"; on Windows may be the edition.
- `host_release` ? OS release version string.
- `host_service_pack_level` ? service pack or patch level string.
- `host_sku` ? SKU numeric code where applicable (nullable int).
- `os_language_version` ? OS language/culture version id (int).
- `host_architecture` ? CPU architecture string (x64, x86, ARM64, etc.).

How to interpret

- Useful for telemetry and compatibility checks, especially in cross-platform deployments.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsHostInfoReader.Sql;
using var rdr = cmd.ExecuteReader();
var h = new DmOsHostInfoReader(rdr, ownsReader:false);
if (h.Read())
{
    Console.WriteLine($"Platform:{h.HostPlatform} Distro:{h.HostDistribution} Release:{h.HostRelease} Arch:{h.HostArchitecture}");
}
```

See also:

- [sys.dm_os_host_info](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-host-info)
