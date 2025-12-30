# ServersReader

Overview

`ServersReader` wraps `sys.servers` and exposes linked server definitions and server metadata.

Reader SQL

```
SELECT
  s5.[server_id],
  s5.[Name],
  s5.[Product],
  s5.[Provider],
  s5.[data_source],
  s5.[Location],
  s5.[provider_string],
  s5.[Catalog],
  s5.[connect_timeout],
  s5.[query_timeout],
  s5.[is_linked],
  s5.[is_remote_login_enabled],
  s5.[is_rpc_out_enabled],
  s5.[is_data_access_enabled],
  s5.[is_collation_compatible],
  s5.[uses_remote_collation],
  s5.[collation_name],
  s5.[lazy_schema_validation],
  s5.[is_system],
  s5.[is_publisher],
  s5.[is_subscriber],
  s5.[is_distributor],
  s5.[is_nonsql_subscriber],
  s5.[is_remote_proc_transaction_promotion_enabled],
  s5.[modify_date],
  s5.[is_rda_server]
FROM
  [sys].[servers] s5
```

Columns and interpretation

- `server_id` (int): Server identifier used internally.
- `Name` (string): Linked server name.
- `Product` (string): Product name of the remote server (e.g., 'SQL Server').
- `Provider` (string): OLE DB provider name.
- `data_source` (string?): Data source connection string or server name.
- `Location` (string?): Location description.
- `provider_string` (string?): Provider-specific connection string.
- `Catalog` (string?): Default catalog/database on the remote server.
- `connect_timeout`, `query_timeout` (int?): Timeout settings.
- `is_linked` (bool): Whether this is a linked server.
- `is_remote_login_enabled`, `is_rpc_out_enabled`, `is_data_access_enabled` (bool): Remote execution and data access capabilities.
- `is_collation_compatible`, `uses_remote_collation` (bool): Collation behavior between local and remote.
- `collation_name` (string?): Collation used when remote collation is considered.
- `lazy_schema_validation` (bool): Whether schema validation is deferred.
- `is_system` (bool): System-level server entry (cannot be dropped).
- `is_publisher`, `is_subscriber`, `is_distributor`, `is_nonsql_subscriber` (bool?): Replication roles.
- `is_remote_proc_transaction_promotion_enabled` (bool?): Whether remote proc transactions are promoted.
- `modify_date` (DateTime): Last modification timestamp.
- `is_rda_server` (bool?): Whether Remote Data Access (RDA) is enabled for the server.

How to interpret

- Use `Provider` and `DataSource` to construct connection semantics for linked servers. Replication flags indicate involvement in replication topologies.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ServersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ServersReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Server:{r.Name} Product:{r.Product} Linked:{r.IsLinked} Provider:{r.Provider}");
```

See also:

- [sys.servers](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-servers)
