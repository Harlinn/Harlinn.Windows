# CryptographicProvidersReader — reference

Overview

`CryptographicProvidersReader` wraps `sys.cryptographic_providers` and exposes registered cryptographic providers on the instance.

Reader SQL

```
SELECT
  cp1.[provider_id],
  cp1.[Name],
  cp1.[Guid],
  cp1.[Version],
  cp1.[dll_path],
  cp1.[is_enabled]
FROM
  [sys].[cryptographic_providers] cp1
```

Selected columns (property mapping and brief meaning)

- `provider_id` ? property: `ProviderId` (int)
  - Identifier for the cryptographic provider.

- `Name` ? property: `Name` (string)
  - Provider name.

- `Guid` ? property: `Guid` (Guid?)
  - GUID of the provider if available.

- `Version` ? property: `Version` (string?)
  - Provider version string.

- `dll_path` ? property: `DllPath` (string?)
  - Filesystem path to the provider DLL.

- `is_enabled` ? property: `IsEnabled` (bool)
  - Whether the provider is enabled for use.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.CryptographicProvidersDataType` objects.
