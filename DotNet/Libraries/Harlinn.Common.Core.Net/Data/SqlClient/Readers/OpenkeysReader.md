# OpenkeysReader — reference

Overview

`OpenkeysReader` wraps `sys.openkeys` and returns information about database symmetric keys that are currently open in the instance, including the time opened and status.

Reader SQL

```
SELECT
  o.[database_id],
  o.[database_name],
  o.[key_id],
  o.[key_name],
  o.[key_guid],
  o.[opened_date],
  o.[Status]
FROM
  [sys].[openkeys] o
```

Columns and interpretation

- `database_id` — id of the database where the key is open (nullable).
- `database_name` — database name (nullable).
- `key_id` — id of the symmetric key.
- `key_name` — name of the key.
- `key_guid` — GUID of the key.
- `opened_date` — when the key was opened.
- `Status` — numeric status code describing the open state (nullable). Consult server docs for specific codes.

How to interpret

- Open keys are used for encryption operations; this view helps audit which keys are currently available in memory and by whom.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = OpenkeysReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new OpenkeysReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DatabaseName} Key:{r.KeyName} Opened:{r.OpenedDate} Status:{r.Status}");
}
```

See also:

- [sys.openkeys](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-openkeys)
