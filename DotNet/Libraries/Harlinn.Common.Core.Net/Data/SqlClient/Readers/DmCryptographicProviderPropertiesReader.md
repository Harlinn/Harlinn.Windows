# DmCryptographicProviderPropertiesReader — reference

Overview

`DmCryptographicProviderPropertiesReader` wraps `sys.dm_cryptographic_provider_properties` and exposes capabilities and properties of cryptographic providers registered with SQL Server.

Reader SQL

```
SELECT
  dcpp.[provider_id],
  dcpp.[Guid],
  dcpp.[provider_version],
  dcpp.[sqlcrypt_version],
  dcpp.[friendly_name],
  dcpp.[authentication_type],
  dcpp.[symmetric_key_support],
  dcpp.[symmetric_key_persistance],
  dcpp.[symmetric_key_export],
  dcpp.[symmetric_key_import],
  dcpp.[asymmetric_key_support],
  dcpp.[asymmetric_key_persistance],
  dcpp.[asymmetric_key_export],
  dcpp.[asymmetric_key_import]
FROM
  [sys].[dm_cryptographic_provider_properties] dcpp
```

Selected columns (property mapping and brief meaning)

- `provider_id` ? `ProviderId` (int?)
  - Identifier of the cryptographic provider instance.

- `Guid` ? `Guid` (Guid?)
  - Provider GUID.

- `provider_version` ? `ProviderVersion` (string?)
  - Provider version string.

- `sqlcrypt_version` ? `SqlcryptVersion` (string?)
  - Version of SQL Crypt interface supported by provider.

- `friendly_name` ? `FriendlyName` (string?)
  - Human friendly provider name.

- `authentication_type` ? `AuthenticationType` (string?)
  - Authentication method supported/used by provider.

- `symmetric_key_support` ? `SymmetricKeySupport` (byte?)
  - Capability flags for symmetric key operations.

- `symmetric_key_persistance` ? `SymmetricKeyPersistance` (byte?)
  - Persistence support for symmetric keys.

- `symmetric_key_export` ? `SymmetricKeyExport` (byte?)
  - Export capabilities for symmetric keys.

- `symmetric_key_import` ? `SymmetricKeyImport` (byte?)
  - Import capabilities for symmetric keys.

- `asymmetric_key_support` ? `AsymmetricKeySupport` (byte?)
  - Capability flags for asymmetric key operations.

- `asymmetric_key_persistance` ? `AsymmetricKeyPersistance` (byte?)
  - Persistence support for asymmetric keys.

- `asymmetric_key_export` ? `AsymmetricKeyExport` (byte?)
  - Export capabilities for asymmetric keys.

- `asymmetric_key_import` ? `AsymmetricKeyImport` (byte?)
  - Import capabilities for asymmetric keys.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmCryptographicProviderPropertiesDataType` objects.
