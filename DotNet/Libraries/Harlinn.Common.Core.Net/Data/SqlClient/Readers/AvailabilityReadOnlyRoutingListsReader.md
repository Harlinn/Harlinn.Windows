# AvailabilityReadOnlyRoutingListsReader — reference

Overview

`AvailabilityReadOnlyRoutingListsReader` wraps `sys.availability_read_only_routing_lists` and exposes routing list mappings that define read-only routing priorities for replicas.

Reader SQL

```
SELECT
  arorl.[replica_id],
  arorl.[routing_priority],
  arorl.[read_only_replica_id]
FROM
  [sys].[availability_read_only_routing_lists] arorl
```

Selected columns (property mapping and brief meaning)

- `replica_id` ? property: `ReplicaId` (Guid)
  - The replica identifier owning the routing list.

- `routing_priority` ? property: `RoutingPriority` (int)
  - Numeric priority for routing; lower values typically mean higher preference.

- `read_only_replica_id` ? property: `ReadOnlyReplicaId` (Guid)
  - The read-only replica referenced by this routing entry.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AvailabilityReadOnlyRoutingListsDataType` objects.
