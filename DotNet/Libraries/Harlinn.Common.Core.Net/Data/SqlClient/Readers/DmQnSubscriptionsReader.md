# DmQnSubscriptionsReader — reference

Overview

`DmQnSubscriptionsReader` wraps `sys.dm_qn_subscriptions` and returns information about query notifications subscriptions such as subscription id, database, security identifier and status.

Reader SQL

```
SELECT
  dqs.[Id],
  dqs.[database_id],
  dqs.[Sid],
  dqs.[object_id],
  dqs.[Created],
  dqs.[Timeout],
  dqs.[Status]
FROM
  [sys].[dm_qn_subscriptions] dqs
```

Columns and interpretation

- `Id` — subscription identifier.
- `database_id` — ID of the database where subscription is registered.
- `Sid` — security identifier (binary) associated with the subscription.
- `object_id` — object id (table or view) associated with the subscription.
- `Created` — creation timestamp of the subscription.
- `Timeout` — timeout value for the subscription in seconds (or server-defined units).
- `Status` — numeric status of the subscription; interpret using server docs.

How to interpret

- Use `Status` to find expired or errored subscriptions.
- `Sid` can be mapped to a login or user for auditing who created the subscription.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmQnSubscriptionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmQnSubscriptionsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Id:{r.Id} DB:{r.DatabaseId} Obj:{r.ObjectId} Created:{r.Created} Timeout:{r.Timeout} Status:{r.Status}");
}
```

See also:

- [sys.dm_qn_subscriptions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-qn-subscriptions)
