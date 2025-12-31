# SysprocessesReader

Reads rows from the `sys.sysprocesses` compatibility view. This view reports information about processes connected to SQL Server.

Columns and interpretation:

- `Spid` (short)
  - Description: Server process id.
  - Interpretation: Unique session id within the instance.
- `Kpid` (short)
  - Description: Kernel process id or worker id.
  - Interpretation: OS process id for the SQL Server worker.
- `Blocked` (short)
  - Description: SPID that this process is blocked by (0 if not blocked).
  - Interpretation: Helps identify blocking chains.
- `Waittype` (binary)
  - Description: Encoded wait type.
  - Interpretation: Binary code representing wait reason.
- `Waittime` (long)
  - Description: Time spent waiting.
  - Interpretation: Milliseconds or ticks depending on platform.
- `Lastwaittype` (string)
  - Description: Last textual wait type (human readable).
  - Interpretation: Use to diagnose wait reasons.
- `Waitresource` (string)
  - Description: Resource being waited on (e.g., 'RID:...').
  - Interpretation: Identifier describing the resource.
- `Dbid` (short)
  - Description: Database id for the session's current database.
  - Interpretation: Correlate with `sysdatabases`.
- `Uid` (short?, nullable)
  - Description: User id of the session's login in the database.
  - Interpretation: Database principal id.
- `Cpu` (int)
  - Description: CPU time consumed by the session.
  - Interpretation: Aggregate CPU usage (units may be ms).
- `physical_io` (long)
  - Description: I/O operations performed by the session.
  - Interpretation: Count of physical I/O operations.
- `Memusage` (int)
  - Description: Memory usage by the session.
  - Interpretation: Pages or memory units used.
- `login_time` (DateTime)
  - Description: When the session logged in.
  - Interpretation: Login timestamp.
- `last_batch` (DateTime)
  - Description: When the last batch was executed.
  - Interpretation: Timestamp of last activity.
- `Ecid` (short)
  - Description: Execution context id.
  - Interpretation: For parallel or nested requests.
- `open_tran` (short)
  - Description: Number of open transactions for the session.
  - Interpretation: Count of active transactions.
- `Status` (string)
  - Description: Human readable session status (running, sleeping, rollback, etc.).
  - Interpretation: Use to determine current state.
- `Sid` (binary)
  - Description: Security identifier for the login.
  - Interpretation: Map to server principal.
- `Hostname` (string)
  - Description: Client host name.
  - Interpretation: Machine name of client.
- `program_name` (string)
  - Description: Client program name.
  - Interpretation: Application name used by client connection.
- `Hostprocess` (string)
  - Description: Host process id or identifier.
  - Interpretation: PID or other reference on client.
- `Cmd` (string)
  - Description: Command currently executing.
  - Interpretation: T-SQL command type or name (e.g., 'SELECT', 'CREATE')
- `nt_domain` (string)
  - Description: Windows NT domain for the client.
  - Interpretation: Authentication domain.
- `nt_username` (string)
  - Description: Windows username for the client.
  - Interpretation: Authenticated user.
- `net_address` (string)
  - Description: Network address of the client.
  - Interpretation: IP or network address string.
- `net_library` (string)
  - Description: Network library used (e.g., TCP/IP).
  - Interpretation: Transport protocol.
- `Loginame` (string)
  - Description: Login name used.
  - Interpretation: SQL Server login.
- `context_info` (binary)
  - Description: Context information set by `SET CONTEXT_INFO`.
  - Interpretation: Application-defined binary blob.
- `sql_handle` (binary)
  - Description: Handle to the batch or cached plan.
  - Interpretation: Can be used with DMV to get SQL text or plan.
- `stmt_start` (int)
  - Description: Offset to statement start within batch.
  - Interpretation: Byte offset in the text.
- `stmt_end` (int)
  - Description: Offset to statement end within batch.
  - Interpretation: Byte offset in the text.
- `request_id` (int)
  - Description: Request id within a session (for MARS or parallel requests).
  - Interpretation: Use to map requests inside a connection.
- `page_resource` (binary?, nullable)
  - Description: Probably/guesswork: resource descriptor for page waits.
  - Interpretation: Internal representation of a page resource.

Example usage

```csharp
using var conn = new Microsoft.Data.SqlClient.SqlConnection("<connection-string>");
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = SysprocessesReader.Sql;
using var reader = cmd.ExecuteReader();
var r = new SysprocessesReader(reader);
while (r.Read())
{
    Console.WriteLine($"spid={r.Spid} status={r.Status} cpu={r.Cpu} io={r.PhysicalIo} blockedBy={r.Blocked} login={r.Loginame}");
}
```

See also:
- [sys.sysprocesses](https://learn.microsoft.com/en-us/sql/relational-databases/system-tables/sys-sysprocesses-transact-sql)
