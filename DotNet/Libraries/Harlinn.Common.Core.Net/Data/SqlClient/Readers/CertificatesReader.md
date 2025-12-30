# CertificatesReader — reference

Overview

`CertificatesReader` wraps `sys.certificates` and exposes certificate metadata stored in the instance.

Reader SQL

```
SELECT
  c.[Name],
  c.[certificate_id],
  c.[principal_id],
  c.[pvt_key_encryption_type],
  c.[pvt_key_encryption_type_desc],
  c.[is_active_for_begin_dialog],
  c.[issuer_name],
  c.[cert_serial_number],
  c.[Sid],
  c.[string_sid],
  c.[Subject],
  c.[expiry_date],
  c.[start_date],
  c.[Thumbprint],
  c.[attested_by],
  c.[pvt_key_last_backup_date],
  c.[key_length]
FROM
  [sys].[certificates] c
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - Certificate name.

- `certificate_id` ? property: `CertificateId` (int)
  - Certificate identifier.

- `principal_id` ? property: `PrincipalId` (int?)
  - Owner principal id.

- `pvt_key_encryption_type` / `pvt_key_encryption_type_desc` ? private key encryption metadata.

- `is_active_for_begin_dialog` ? property: `IsActiveForBeginDialog` (bool?)
  - Indicates whether certificate is active for service broker dialogs.

- `issuer_name` ? property: `IssuerName` (string?)
  - Issuer distinguished name.

- `cert_serial_number` ? property: `CertSerialNumber` (string?)
  - Serial number string.

- `Sid` / `string_sid` ? SID binary and string representation.

- `Subject` ? property: `Subject` (string?)
  - Certificate subject DN.

- `expiry_date` / `start_date` ? properties: `ExpiryDate` (DateTime?), `StartDate` (DateTime?)
  - Validity timestamps.

- `Thumbprint` ? property: `Thumbprint` (byte[])
  - Binary thumbprint of certificate.

- `attested_by` ? property: `AttestedBy` (string?)
  - Attestation information.

- `pvt_key_last_backup_date` ? property: `PvtKeyLastBackupDate` (DateTime?)
  - Last backup timestamp of private key.

- `key_length` ? property: `KeyLength` (int?)
  - Key length in bits.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.CertificatesDataType` objects.
