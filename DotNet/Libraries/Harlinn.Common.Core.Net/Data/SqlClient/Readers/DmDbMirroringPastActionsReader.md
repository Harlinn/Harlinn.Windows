# DmDbMirroringPastActionsReader — reference

Overview

`DmDbMirroringPastActionsReader` wraps `sys.dm_db_mirroring_past_actions` and shows historic state-machine actions for database mirroring or availability group workflows.

Reader SQL

```
SELECT
  ddmpa.[mirroring_guid],
  ddmpa.[state_machine_name],
  ddmpa.[action_type],
  ddmpa.[Name],
  ddmpa.[current_state],
  ddmpa.[action_sequence]
FROM
  [sys].[dm_db_mirroring_past_actions] ddmpa
```

Columns (detailed)

- `mirroring_guid` ? `MirroringGuid` (Guid?)
  - Unique identifier for the mirroring session or configuration.

- `state_machine_name` ? `StateMachineName` (string?)
  - Name of the mirroring state machine component that executed the action.

- `action_type` ? `ActionType` (string?)
  - Type of the action performed (e.g., role change, failover, connect/disconnect).

- `Name` ? `Name` (string?)
  - Name or identifier of the action.

- `current_state` ? `CurrentState` (string?)
  - State of the state machine after the action.

- `action_sequence` ? `ActionSequence` (int)
  - Sequence number for ordering past actions.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmDbMirroringPastActionsReader.Sql;
using var reader = cmd.ExecuteReader();
var paReader = new DmDbMirroringPastActionsReader(reader, ownsReader: false);
while (paReader.Read())
{
    Console.WriteLine($"Mirroring: {paReader.MirroringGuid} Seq: {paReader.ActionSequence}");
    Console.WriteLine($"  StateMachine: {paReader.StateMachineName}, Action: {paReader.ActionType} / {paReader.Name}");
    Console.WriteLine($"  Current state: {paReader.CurrentState}");
}
```

See also

- https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-db-mirroring-past-actions
