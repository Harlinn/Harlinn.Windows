# SymmetricKeysReader

Overview

`SymmetricKeysReader` wraps `sys.symmetric_keys` and exposes symmetric key metadata used for database encryption.

Reader SQL

```
SELECT
  sk.[Name],
  sk.[principal_id],
  sk.[symmetric_key_id],
  sk.[key_length],
  sk.[key_algorithm],
  sk.[algorithm_desc],
  sk.[create_date],
  sk.[modify_date],
  sk.[key_guid],
  sk.[key_thumbprint],
  sk.[provider_type],
  sk.[cryptographic_provider_guid],
  sk.[cryptographic_provider_algid]
FROM
  [sys].[symmetric_keys] sk
```

Columns and interpretation

- `Name` (string): Symmetric key name.
- `principal_id` (int?): Principal id that owns the key.
- `symmetric_key_id` (int): Identifier of the symmetric key.
- `key_length` (int): Key length in bits.
- `key_algorithm` (string): Algorithm name (e.g., AES_256).
- `algorithm_desc` (string?): Human-readable algorithm description.
- `create_date`, `modify_date` (DateTime): Timestamps for creation and modification.
- `key_guid` (Guid?): GUID of the key.
- `key_thumbprint` (object?): Provider-specific thumbprint value.
- `provider_type` (string?): Provider type name.
- `cryptographic_provider_guid` (Guid?): GUID of the cryptographic provider.
- `cryptographic_provider_algid` (object?): Provider algorithm id.

How to interpret

- These columns identify encryption keys and their provider metadata. `key_thumbprint` and provider GUIDs help map to external key stores and providers.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SymmetricKeysReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SymmetricKeysReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Key:{r.Name} Alg:{r.KeyAlgorithm} Length:{r.KeyLength} Created:{r.CreateDate}");
```

See also:

- [sys.symmetric_keys](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-symmetric-keys)
