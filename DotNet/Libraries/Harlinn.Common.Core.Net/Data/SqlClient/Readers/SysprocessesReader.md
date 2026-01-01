# SysprocessesReader

Overview

`SysprocessesReader` wraps the legacy `sys.sysprocesses` view and exposes information about active server processes and their session-level state.

Reader SQL

```
SELECT
  s8.[Spid],
  s8.[Kpid],
  s8.[Blocked],
  s8.[Waittype],
  s8.[Waittime],
  s8.[Lastwaittype],
  s8.[Waitresource],
  s8.[Dbid],
  s8.[Uid],
  s8.[Cpu],
  s8.[physical_io],
  s8.[Memusage],
  s8.[login_time],
  s8.[last_batch],
  s8.[Ecid],
  s8.[open_tran],
  s8.[Status],
  s8.[Sid],
  s8.[Hostname],
  s8.[program_name],
  s8.[Hostprocess],
  s8.[Cmd],
  s8.[nt_domain],
  s8.[nt_username],
  s8.[net_address],
  s8.[net_library],
  s8.[Loginame],
  s8.[context_info],
  s8.[sql_handle],
  s8.[stmt_start],
  s8.[stmt_end],
  s8.[request_id],
  s8.[page_resource]
FROM
  [sys].[sysprocesses] s8
```

Columns and interpretation

- `Spid` (smallint): Server process id for the session.
- `Kpid` (smallint): Kernel process id or worker id.
- `Blocked` (smallint): SPID that is blocking this session (0 if not blocked).
- `Waittype` (binary): Binary identifier of the wait type.
- `Waittime` (bigint): Time spent waiting in milliseconds.
- `Lastwaittype` (string): Text description of the last wait type.
- `Waitresource` (string): Resource being waited on, e.g., lock resource.
- `Dbid` (smallint): Database id of the session's current database.
- `Uid` (smallint?): User id of the session.
- `Cpu` (int): CPU time used by the session.
- `physical_io` (bigint): Physical IO count for the session.
- `Memusage` (int): Memory usage counter.
- `login_time` (datetime): Time the session logged in.
- `last_batch` (datetime): Time of last executed batch.
- `Ecid` (smallint): Execution context id within the session.
- `open_tran` (smallint): Number of open transactions (or indicator).
- `Status` (string): Session status text.
- `Sid` (binary): Security identifier for the session login.
- `Hostname` (string): Client host name.
- `program_name` (string): Client program name.
- `Hostprocess` (string): Client host process id.
- `Cmd` (string): Current command being executed.
- `nt_domain` (string): NT domain for the client principal.
- `nt_username` (string): NT username for the client principal.
- `net_address` (string): Network address of the client.
- `net_library` (string): Network library used by the client.
- `Loginame` (string): Login name.
- `context_info` (binary): Binary context info set by `SET CONTEXT_INFO`.
- `sql_handle` (binary): Handle for the currently executing SQL batch.
- `stmt_start` (int): Statement start offset within the batch.
- `stmt_end` (int): Statement end offset within the batch.
- `request_id` (int): Request id within the session.
- `page_resource` (binary?): Page resource identifier for IO/lock waits.

How to interpret

- Use `Spid` to correlate sessions with other diagnostic views and to take actions (KILL, DBCC, etc.).
- Prefer modern DMVs (`sys.dm_exec_sessions`, `sys.dm_exec_requests`, `sys.dm_exec_connections`) for richer and documented fields.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SysprocessesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SysprocessesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"SPID:{r.Spid} Status:{r.Status} DB:{r.Dbid} Host:{r.Hostname} Program:{r.ProgramName} BlockedBy:{r.Blocked}");
```

See also:

- [sys.sysprocesses](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-sysprocesses)
