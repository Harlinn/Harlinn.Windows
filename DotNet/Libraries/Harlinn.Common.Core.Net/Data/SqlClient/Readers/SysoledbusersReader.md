# SysoledbusersReader

Reads rows from the `sys.sysoledbusers` compatibility view. This view contains information about OLE DB users for linked servers or remote servers.

Columns:

- `Rmtsrvid` (short?, nullable)
  - Description: Remote server id.
  - Interpretation: Identifier of the linked/remote server.
- `Rmtloginame` (string?, nullable)
  - Description: Remote login name used on the remote server.
  - Interpretation: Username for remote authentication.
- `Rmtpassword` (string?, nullable)
  - Description: Probably/guesswork: password for remote login (may be stored or hashed historically).
  - Interpretation: Do not rely on plaintext; treat as legacy field.
- `Loginsid` (binary?, nullable)
  - Description: SID of the local login mapped to remote login.
  - Interpretation: Use to map local principal.
- `Status` (short?, nullable)
  - Description: Status flags for the mapping.
  - Interpretation: Encoded values indicating enable/disable etc.
- `Changedate` (DateTime)
  - Description: Date the mapping was last changed.
  - Interpretation: Timestamp for last modification.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysoledbusersReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysoledbusersReader(reader);
while (r.Read())
{
    Console.WriteLine($"remote server={r.Rmtsrvid} local login SID={BitConverter.ToString(r.Loginsid ?? new byte[0])} remoteLogin={r.Rmtloginame}");
}
```

See also:
- [sys.sysoledbusers](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysoledbusers-transact-sql)
