# DmClusterEndpointsReader — reference

Overview

`DmClusterEndpointsReader` wraps `sys.dm_cluster_endpoints` and exposes cluster endpoint information used by SQL Server clustering features.

Reader SQL

```
SELECT
  dce0.[Name],
  dce0.[Description],
  dce0.[Endpoint],
  dce0.[protocol_desc]
FROM
  [sys].[dm_cluster_endpoints] dce0
```

Selected columns (property mapping and brief meaning)

- `Name` ? `Name` (string): Endpoint name.
- `Description` ? `Description` (string): Descriptive text for the endpoint.
- `Endpoint` ? `Endpoint` (string): Endpoint address or connection string used by the cluster service.
- `protocol_desc` ? `ProtocolDesc` (string?): Protocol description for the endpoint.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmClusterEndpointsDataType` objects.
