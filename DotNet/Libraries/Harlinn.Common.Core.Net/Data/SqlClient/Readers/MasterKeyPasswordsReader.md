# MasterKeyPasswordsReader — reference

Overview

`MasterKeyPasswordsReader` wraps `sys.master_key_passwords` and returns information about master key password families used to protect database master keys.

Reader SQL

```
SELECT
  mkp.[credential_id],
  mkp.[family_guid]
FROM
  [sys].[master_key_passwords] mkp
```

Columns and interpretation

- `credential_id` — id of the credential used to protect the master key.
- `family_guid` — GUID grouping related master key passwords into a family.

How to interpret

- The view helps identify how the database master key is protected (credential and family grouping). GUID links to internal family identifiers.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = MasterKeyPasswordsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new MasterKeyPasswordsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Credential:{r.CredentialId} Family:{r.FamilyGuid}");
}
```

See also:

- [sys.master_key_passwords](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-master-key-passwords)
