# KeyEncryptionsReader — reference

Overview

`KeyEncryptionsReader` wraps `sys.key_encryptions` and returns encryption metadata for keys, including thumbprints and algorithm properties.

Reader SQL

```
SELECT
  ke.[key_id],
  ke.[Thumbprint],
  ke.[crypt_type],
  ke.[crypt_type_desc],
  ke.[crypt_property]
FROM
  [sys].[key_encryptions] ke
```

Columns and interpretation

- `key_id` — id of the key being encrypted.
- `Thumbprint` — binary thumbprint of the certificate or asymmetric key used to encrypt the key (nullable).
- `crypt_type` / `crypt_type_desc` — encryption type code and description used for the key encryption.
- `crypt_property` — binary blob containing encryption properties or additional metadata (nullable).

How to interpret

- Used to inspect how database encryption keys are protected (for example by certificates). `Thumbprint` allows correlating to certificates in `sys.certificates`.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = KeyEncryptionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new KeyEncryptionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"KeyId:{r.KeyId} ThumbLen:{(r.Thumbprint?.Length ?? 0)} Type:{r.CryptTypeDesc}");
}
```

See also:

- [sys.key_encryptions](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-key-encryptions)
