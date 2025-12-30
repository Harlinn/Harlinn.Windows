# DmExecSessionsReader — reference

Overview

`DmExecSessionsReader` wraps `sys.dm_exec_sessions` and returns information about all active user and internal sessions on the SQL Server instance. Includes login information, resource usage, session settings and activity timestamps.

Reader SQL

```
SELECT
  des.[session_id],
  des.[login_time],
  des.[host_name],
  des.[program_name],
  des.[host_process_id],
  des.[client_version],
  des.[client_interface_name],
  des.[security_id],
  des.[login_name],
  des.[nt_domain],
  des.[nt_user_name],
  des.[Status],
  des.[context_info],
  des.[cpu_time],
  des.[memory_usage],
  des.[total_scheduled_time],
  des.[total_elapsed_time],
  des.[endpoint_id],
  des.[last_request_start_time],
  des.[last_request_end_time],
  des.[Reads],
  des.[Writes],
  des.[logical_reads],
  des.[is_user_process],
  des.[text_size],
  des.[Language],
  des.[date_format],
  des.[date_first],
  des.[quoted_identifier],
  des.[Arithabort],
  des.[ansi_null_dflt_on],
  des.[ansi_defaults],
  des.[ansi_warnings],
  des.[ansi_padding],
  des.[ansi_nulls],
  des.[concat_null_yields_null],
  des.[transaction_isolation_level],
  des.[lock_timeout],
  des.[deadlock_priority],
  des.[row_count],
  des.[prev_error],
  des.[original_security_id],
  des.[original_login_name],
  des.[last_successful_logon],
  des.[last_unsuccessful_logon],
  des.[unsuccessful_logons],
  des.[group_id],
  des.[database_id],
  des.[authenticating_database_id],
  des.[open_transaction_count],
  des.[page_server_reads]
FROM
  [sys].[dm_exec_sessions] des
```

Columns and interpretation

- `session_id` ? session identifier.
- `login_time`, `login_name`, `nt_domain`, `nt_user_name` ? authentication details and login timestamps.
- `host_name`, `program_name`, `host_process_id`, `client_version`, `client_interface_name` ? client environment context.
- `security_id`, `original_security_id`, `original_login_name` ? security context and impersonation origin.
- `Status` ? session state (e.g., running, sleeping).
- Resource usage: `cpu_time`, `memory_usage`, `total_scheduled_time`, `total_elapsed_time`.
- Activity timestamps: `last_request_start_time`, `last_request_end_time`.
- IO counters: `Reads`, `Writes`, `logical_reads`.
- Session SET options and defaults (ANSI flags, date_format, quoted_identifier) are included for context.
- `unsuccessful_logons`, `last_successful_logon`, `last_unsuccessful_logon` ? audit-related session data.
- `open_transaction_count` ? number of open transactions for the session.
- `page_server_reads` ? page server read count for remote page activity.

How to interpret

- Use `cpu_time`, `memory_usage`, and IO counters to identify heavy sessions.
- `login_time` and client info help map sessions to application instances and users.
- `open_transaction_count` helps identify sessions holding long-lived transactions that can block others.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmExecSessionsReader.Sql;
using var rdr = cmd.ExecuteReader();
var s = new DmExecSessionsReader(rdr, ownsReader:false);
while (s.Read())
{
    Console.WriteLine($"Sess:{s.SessionId} Login:{s.LoginName} Host:{s.HostName} Program:{s.ProgramName} CPU:{s.CpuTime} Mem:{s.MemoryUsage}");
}
```

See also:

- [sys.dm_exec_sessions](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-exec-sessions)
