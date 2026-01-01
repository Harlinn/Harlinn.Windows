# AvailabilityGroupListenersReader — reference

Overview

`AvailabilityGroupListenersReader` wraps [`sys.availability_group_listeners`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-availability-group-listeners-transact-sql) and exposes listener configuration details for availability groups.

Reader SQL

```
SELECT
  agl.[group_id],
  agl.[listener_id],
  agl.[dns_name],
  agl.[Port],
  agl.[is_conformant],
  agl.[ip_configuration_string_from_cluster]
FROM
  [sys].[availability_group_listeners] agl
```

Selected columns (property mapping and brief meaning)

- `group_id` ? property: `GroupId` (Guid)
  - Availability group identifier.

- `listener_id` ? property: `ListenerId` (string?)
  - Listener id.

- `dns_name` ? property: `DnsName` (string?)
  - DNS name for the listener.

- `Port` ? property: `Port` (int?)
  - Port used for listener endpoint.

- `is_conformant` ? property: `IsConformant` (bool)
  - Whether listener supports the expected network configuration.

- `ip_configuration_string_from_cluster` ? property: `IpConfigurationStringFromCluster` (string?)
  - Raw IP configuration string as provided by cluster.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AvailabilityGroupListenersDataType` objects.
