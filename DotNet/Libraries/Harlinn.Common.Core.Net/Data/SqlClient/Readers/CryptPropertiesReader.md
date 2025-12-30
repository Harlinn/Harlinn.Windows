# CryptPropertiesReader — reference

Overview

`CryptPropertiesReader` wraps `sys.crypt_properties` and exposes cryptographic metadata associated with objects (thumbprints, cryptographic properties).

Reader SQL

```
SELECT
  cp0.[Class],
  cp0.[class_desc],
  cp0.[major_id],
  cp0.[Thumbprint],
  cp0.[crypt_type],
  cp0.[crypt_type_desc],
  cp0.[crypt_property]
FROM
  [sys].[crypt_properties] cp0
```

Selected columns (property mapping and brief meaning)

- `Class` ? property: `Class` (byte)
  - Class code indicating the object class the crypt property is associated with.

- `class_desc` ? property: `ClassDesc` (string?)
  - Description of the class.

- `major_id` ? property: `MajorId` (int)
  - Major identifier of the object within the class (e.g., object_id).

- `Thumbprint` ? property: `Thumbprint` (byte[])
  - Binary thumbprint associated with the cryptographic object.

- `crypt_type` ? property: `CryptType` (string)
  - Cryptographic type code.

- `crypt_type_desc` ? property: `CryptTypeDesc` (string?)
  - Description of the crypt type.

- `crypt_property` ? property: `CryptProperty` (byte[])
  - Property blob with cryptographic metadata.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.CryptPropertiesDataType` objects.
