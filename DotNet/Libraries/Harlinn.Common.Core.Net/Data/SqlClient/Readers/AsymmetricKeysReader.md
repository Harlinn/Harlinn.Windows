# AsymmetricKeysReader — reference

Overview

`AsymmetricKeysReader` wraps `sys.asymmetric_keys` and exposes metadata for asymmetric keys stored in the server (used for cryptographic operations).

Reader SQL

```
SELECT
  ak.[Name],
  ak.[principal_id],
  ak.[asymmetric_key_id],
  ak.[pvt_key_encryption_type],
  ak.[pvt_key_encryption_type_desc],
  ak.[Thumbprint],
  ak.[Algorithm],
  ak.[algorithm_desc],
  ak.[key_length],
  ak.[Sid],
  ak.[string_sid],
  ak.[public_key],
  ak.[attested_by],
  ak.[provider_type],
  ak.[cryptographic_provider_guid],
  ak.[cryptographic_provider_algid]
FROM
  [sys].[asymmetric_keys] ak
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - Key name.

- `principal_id` ? property: `PrincipalId` (int?)
  - Owner principal id.

- `asymmetric_key_id` ? property: `AsymmetricKeyId` (int)
  - Unique key id.

- `pvt_key_encryption_type` / `pvt_key_encryption_type_desc` ? private key encryption metadata.

- `Thumbprint` ? property: `Thumbprint` (byte[])
  - Binary thumbprint for the key.

- `Algorithm` / `algorithm_desc` / `key_length` ? algorithm and key length metadata.

- `Sid` / `string_sid` ? security identifier binary and string representations.

- `public_key` ? property: `PublicKey` (byte[])
  - Public key blob.

- `attested_by`, `provider_type`, `cryptographic_provider_guid`, `cryptographic_provider_algid` ? provider and attestation metadata.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AsymmetricKeysDataType` objects.
