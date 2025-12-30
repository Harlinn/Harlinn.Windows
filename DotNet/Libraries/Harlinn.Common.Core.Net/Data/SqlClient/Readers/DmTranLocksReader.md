# DmTranLocksReader — reference

Overview

`DmTranLocksReader` wraps `sys.dm_tran_locks` and returns detailed information about current locks held or requested by transactions, including resource type, mode and owner.

Reader SQL

```
SELECT
  dtl.[resource_type],
  dtl.[resource_subtype],
  dtl.[resource_database_id],
  dtl.[resource_description],
  dtl.[resource_associated_entity_id],
  dtl.[resource_lock_partition],
  dtl.[request_mode],
  dtl.[request_type],
  dtl.[request_status],
  dtl.[request_reference_count],
  dtl.[request_lifetime],
  dtl.[request_session_id],
  dtl.[request_exec_context_id],
  dtl.[request_request_id],
  dtl.[request_owner_type],
  dtl.[request_owner_id],
  dtl.[request_owner_guid],
  dtl.[request_owner_lockspace_id],
  dtl.[lock_owner_address]
FROM
  [sys].[dm_tran_locks] dtl
```

Columns and interpretation

- `resource_type` — type of resource locked (e.g., OBJECT, KEY, PAGE, RANGE).
- `resource_subtype` — subtype or more detailed classification of the resource.
- `resource_database_id` — database id of the resource.
- `resource_description` — textual description of the resource (e.g., object name or key value).
- `resource_associated_entity_id` — associated entity id (object id, hobt id) for the resource.
- `resource_lock_partition` — partition number of the lock manager.
- `request_mode` — lock mode requested or held (e.g., S, X, U, IS, IX).
- `request_type` — request type (e.g., CONVERT, ACQUIRE).
- `request_status` — status of the lock request (GRANTED, WAITING).
- `request_reference_count` — reference count for the request.
- `request_lifetime` — lifetime classification for the request (e.g., TRANSACTION, SESSION).
- `request_session_id` — session id owning the lock request.
- `request_exec_context_id` — execution context id for the request.
- `request_request_id` — internal request id.
- `request_owner_type` — owner type (e.g., TRANSACTION, SPID).
- `request_owner_id` — owner id (transaction id or other numeric id).
- `request_owner_guid` — owner GUID when applicable.
- `request_owner_lockspace_id` — lockspace identifier for ownership grouping.
- `lock_owner_address` — internal address of the lock owner (binary).

How to interpret

- Inspect `request_status` and `request_mode` to identify blocking and wait chains. Combine with session and request ids to map to `sys.dm_exec_sessions` and `sys.dm_exec_requests` for further diagnostics.
- `resource_description` can be parsed to identify the object or key being contended.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranLocksReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranLocksReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Resource:{r.ResourceType}/{r.ResourceSubtype} DB:{r.ResourceDatabaseId} Mode:{r.RequestMode} Status:{r.RequestStatus} Session:{r.RequestSessionId} Desc:{r.ResourceDescription}");
}
```

See also:

- [sys.dm_tran_locks](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-locks)
