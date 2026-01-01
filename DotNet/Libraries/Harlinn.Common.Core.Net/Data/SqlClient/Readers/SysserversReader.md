# SysserversReader

Overview

`SysserversReader` wraps the legacy `sys.sysservers` view and exposes linked server and remote server definitions and properties.

Reader SQL

```
SELECT
  s6.[Srvid],
  s6.[Srvstatus],
  s6.[Srvname],
  s6.[Srvproduct],
  s6.[Providername],
  s6.[Datasource],
  s6.[Location],
  s6.[Providerstring],
  s6.[Schemadate],
  s6.[Topologyx],
  s6.[Topologyy],
  s6.[Catalog],
  s6.[Srvcollation],
  s6.[Connecttimeout],
  s6.[Querytimeout],
  s6.[Srvnetname],
  s6.[Isremote],
  s6.[Rpc],
  s6.[Pub],
  s6.[Sub],
  s6.[Dist],
  s6.[Dpub],
  s6.[Rpcout],
  s6.[Dataaccess],
  s6.[Collationcompatible],
  s6.[System],
  s6.[Useremotecollation],
  s6.[Lazyschemavalidation],
  s6.[Collation],
  s6.[Nonsqlsub]
FROM
  [sys].[sysservers] s6
```

Columns and interpretation

- `Srvid` (smallint?): Remote server id.
- `Srvstatus` (smallint?): Status flags for the server entry.
- `Srvname` (string): Remote server name.
- `Srvproduct` (string): Product name of the remote server (e.g., 'SQL Server').
- `Providername` (string): Provider name (OLE DB provider) used for the remote server.
- `Datasource` (string?): Data source string for the server.
- `Location` (string?): Location string provided for the server.
- `Providerstring` (string?): Provider-specific connection string.
- `Schemadate` (datetime): Schema date for remote schema compatibility.
- `Topologyx`/`Topologyy` (int?): Topology coordinates (legacy/metadata for clustering or mapping).
- `Catalog` (string?): Default catalog/database on the remote server.
- `Srvcollation` (string?): Collation employed by the remote server.
- `Connecttimeout` (int?): Connect timeout in seconds for the linked server.
- `Querytimeout` (int?): Query timeout in seconds for the linked server queries.
- `Srvnetname` (string?): Network name of the server.
- `Isremote` (bit?): Whether the server is remote.
- `Rpc`/`Rpcout`/`Pub`/`Sub`/`Dist`/`Dpub` (bit): Flags indicating RPC, publication/subscription, distribution capabilities.
- `Dataaccess` (bit): Whether data access is allowed.
- `Collationcompatible` (bit): Whether collations are compatible.
- `System` (bit): Whether this is a system-defined server entry.
- `Useremotecollation` (bit): Whether to use remote collation.
- `Lazyschemavalidation` (bit): Lazy schema validation flag.
- `Collation` (string?): Explicit collation name.
- `Nonsqlsub` (bit?): Non-SQL subscription flag.

How to interpret

- This view describes linked server definitions; prefer `sys.servers` and `sys.linked_logins` for modern metadata.
- Use `Srvid` to reference server-specific mappings and options.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysserversReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysserversReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Server:{r.Srvname} Product:{r.Srvproduct} Provider:{r.Providername} DataSource:{r.Datasource}");
```

See also:

- [sys.sysservers](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysservers)
