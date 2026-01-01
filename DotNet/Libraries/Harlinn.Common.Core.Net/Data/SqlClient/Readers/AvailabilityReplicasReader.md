# AvailabilityReplicasReader — reference

Overview

`AvailabilityReplicasReader` wraps [`sys.availability_replicas`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-availability-replicas-transact-sql) and exposes information about replicas that participate in availability groups.

Reader SQL

```
SELECT
  ar.[replica_id],
  ar.[group_id],
  ar.[replica_metadata_id],
  ar.[replica_server_name],
  ar.[owner_sid],
  ar.[endpoint_url],
  ar.[availability_mode],
  ar.[availability_mode_desc],
  ar.[failover_mode],
  ar.[failover_mode_desc],
  ar.[session_timeout],
  ar.[primary_role_allow_connections],
  ar.[primary_role_allow_connections_desc],
  ar.[secondary_role_allow_connections],
  ar.[secondary_role_allow_connections_desc],
  ar.[create_date],
  ar.[modify_date],
  ar.[backup_priority],
  ar.[read_only_routing_url],
  ar.[seeding_mode],
  ar.[seeding_mode_desc],
  ar.[read_write_routing_url]
FROM
  [sys].[availability_replicas] ar
```

Selected columns (property mapping and brief meaning)

- `replica_id` ? property: `ReplicaId` (Guid?)
  - Unique identifier of the replica.

- `group_id` ? property: `GroupId` (Guid?)
  - Availability group identifier this replica belongs to.

- `replica_metadata_id` ? property: `ReplicaMetadataId` (int?)
  - Internal metadata id referencing replica metadata store.

- `replica_server_name` ? property: `ReplicaServerName` (string?)
  - Network name of the replica server.

- `owner_sid` ? property: `OwnerSid` (byte[]?)
  - Security identifier of the owner.

- `endpoint_url` ? property: `EndpointUrl` (string?)
  - Replica endpoint URL.

- `availability_mode` / `availability_mode_desc` ? properties: `AvailabilityMode` (byte?), `AvailabilityModeDesc` (string?)
  - Mode of availability (synchronous/asynchronous) and description.

- `failover_mode` / `failover_mode_desc` ? properties: `FailoverMode` (byte?), `FailoverModeDesc` (string?)
  - Automatic/manual failover mode and description.

- `session_timeout` ? property: `SessionTimeout` (int?)
  - Session timeout in seconds.

- `primary_role_allow_connections` / `primary_role_allow_connections_desc` ? primary role connection policy.

- `secondary_role_allow_connections` / `secondary_role_allow_connections_desc` ? secondary role connection policy.

- `create_date` / `modify_date` ? timestamps.

- `backup_priority` ? property: `BackupPriority` (int?)
  - Priority for performing backups on this replica.

- `read_only_routing_url` ? property: `ReadOnlyRoutingUrl` (string?)
  - Routing URL for read-only workloads.

- `seeding_mode` / `seeding_mode_desc` ? seeding mode metadata.

- `read_write_routing_url` ? property: `ReadWriteRoutingUrl` (string?)
  - Routing URL for read-write workloads.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AvailabilityReplicasDataType` objects.
