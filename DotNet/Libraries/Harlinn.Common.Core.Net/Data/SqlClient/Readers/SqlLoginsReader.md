# SqlLoginsReader

Overview

`SqlLoginsReader` wraps `sys.sql_logins` and exposes SQL-authenticated login metadata.

Reader SQL

```
SELECT
  sl.[Name],
  sl.[principal_id],
  sl.[Sid],
  sl.[Type],
  sl.[type_desc],
  sl.[is_disabled],
  sl.[create_date],
  sl.[modify_date],
  sl.[default_database_name],
  sl.[default_language_name],
  sl.[credential_id],
  sl.[is_policy_checked],
  sl.[is_expiration_checked],
  sl.[password_hash]
FROM
  [sys].[sql_logins] sl
```

Columns and interpretation

- `Name` (string): Login name.
- `principal_id` (int): Principal id for the login.
- `Sid` (binary?): Security identifier mapped to the login.
- `Type` (string): Short type code for the principal.
- `type_desc` (string?): Human-readable type description.
- `is_disabled` (bool?): Whether the login is disabled.
- `create_date`, `modify_date` (DateTime): Timestamps for creation and modification.
- `default_database_name` (string?): Default database at connect time.
- `default_language_name` (string?): Default language for the login.
- `credential_id` (int?): Associated credential id.
- `is_policy_checked` (bool?): Whether password policy enforcement is enabled.
- `is_expiration_checked` (bool?): Whether password expiration enforcement is enabled.
- `password_hash` (binary?): Hashed password value (not reversible).

How to interpret

- `is_policy_checked` and `is_expiration_checked` indicate whether Windows/SQL password policies are enforced for the login. Inspect `credential_id` for linked external credentials.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SqlLoginsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SqlLoginsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Login:{r.Name} Disabled:{r.IsDisabled} Policy:{r.IsPolicyChecked}");
```

See also:

- [sys.sql_logins](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sql-logins)
