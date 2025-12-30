# DmOsChildInstancesReader — reference

Overview

`DmOsChildInstancesReader` wraps `sys.dm_os_child_instances` and returns information about child instances of SQL Server in multi-instance deployments including ownership, pipe name and process details.

Reader SQL

```
SELECT
  doci.[owning_principal_name],
  doci.[owning_principal_sid],
  doci.[owning_principal_sid_binary],
  doci.[instance_name],
  doci.[instance_pipe_name],
  doci.[OS_process_id],
  doci.[OS_process_creation_date],
  doci.[heart_beat]
FROM
  [sys].[dm_os_child_instances] doci
```

Columns and interpretation

- `owning_principal_name` ? `OwningPrincipalName` (string?)
  - Principal that owns the child instance.

- `owning_principal_sid` ? `OwningPrincipalSid` (string?)
  - SID string for the owning principal.

- `owning_principal_sid_binary` ? `OwningPrincipalSidBinary` (binary?)
  - Binary SID for the owning principal.

- `instance_name` ? `InstanceName` (string?)
  - Named instance name.

- `instance_pipe_name` ? `InstancePipeName` (string?)
  - Named pipe used for inter-instance communication.

- `OS_process_id` ? `OsProcessId` (int?)
  - OS process id of the child instance.

- `OS_process_creation_date` ? `OsProcessCreationDate` (DateTime?)
  - Creation time of the OS process.

- `heart_beat` ? `HeartBeat` (string?)
  - Heartbeat or status string reported by the child instance.

How to interpret

- Use to discover and monitor child SQL Server instances that are started under the same service host, including process id correlation and communication pipe names.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsChildInstancesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsChildInstancesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Instance:{r.InstanceName} Pipe:{r.InstancePipeName} PID:{r.OsProcessId} Owner:{r.OwningPrincipalName} Heart:{r.HeartBeat}");
}
```

See also:

- [sys.dm_os_child_instances](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-child-instances)
