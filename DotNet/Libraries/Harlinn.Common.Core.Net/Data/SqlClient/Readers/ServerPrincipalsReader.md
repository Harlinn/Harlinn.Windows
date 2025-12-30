# ServerPrincipalsReader

Overview

`ServerPrincipalsReader` wraps `sys.server_principals` and exposes server-level principals (logins, server roles, certificates, etc.).

Reader SQL

```
SELECT
  sp3.[Name],
  sp3.[principal_id],
  sp3.[Sid],
  sp3.[Type],
  sp3.[type_desc],
  sp3.[is_disabled],
  sp3.[create_date],
  sp3.[modify_date],
  sp3.[default_database_name],
  sp3.[default_language_name],
  sp3.[credential_id],
  sp3.[owning_principal_id],
  sp3.[is_fixed_role]
FROM
  [sys].[server_principals] sp3
```

Columns and interpretation

- `Name` (string): Principal name (login or role name).
- `principal_id` (int): Unique id for the server principal.
- `Sid` (binary?): Security Identifier (SID) for Windows logins or certificates. Useful to map to OS accounts.
- `Type` (string): Short code for principal type (e.g., S = SQL login, R = server role).
- `type_desc` (string?): Human-readable type description.
- `is_disabled` (bool?): Whether the principal is disabled (for logins).
- `create_date`, `modify_date` (DateTime): Timestamps for creation and last modification.
- `default_database_name` (string?): Default database for the login when connecting.
- `default_language_name` (string?): Default language for the login.
- `credential_id` (int?): Id of an associated credential (for SQL authenticated principals using credentials).
- `owning_principal_id` (int?): Owning principal id for principals that are owned by another principal.
- `is_fixed_role` (bool): Whether this principal is a fixed server role.

How to interpret

- Use `Sid` to match Windows SIDs.
- `Type` and `type_desc` determine whether the row represents a login, group, or server role. `is_fixed_role` indicates built-in server roles that cannot be dropped.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServerPrincipalsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServerPrincipalsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"{r.Name} (id={r.PrincipalId}) Type={r.Type} Disabled={r.IsDisabled}");
```

See also:

- [sys.server_principals](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-server-principals)
