# DmOsThreadsReader — reference

Overview

`DmOsThreadsReader` wraps `sys.dm_os_threads` and exposes information about OS threads used by SQL Server including stack addresses, CPU time and status.

Reader SQL

```
SELECT
  dot.[thread_address],
  dot.[started_by_sqlservr],
  dot.[os_thread_id],
  dot.[Status],
  dot.[instruction_address],
  dot.[creation_time],
  dot.[kernel_time],
  dot.[usermode_time],
  dot.[stack_base_address],
  dot.[stack_end_address],
  dot.[stack_bytes_committed],
  dot.[stack_bytes_used],
  dot.[Affinity],
  dot.[Priority],
  dot.[Locale],
  dot.[Token],
  dot.[is_impersonating],
  dot.[is_waiting_on_loader_lock],
  dot.[fiber_data],
  dot.[thread_handle],
  dot.[event_handle],
  dot.[scheduler_address],
  dot.[worker_address],
  dot.[fiber_context_address],
  dot.[self_address],
  dot.[processor_group]
FROM
  [sys].[dm_os_threads] dot
```

Columns and interpretation

- `thread_address` — binary identifier for the thread.
- `started_by_sqlservr` — boolean indicating if SQL Server created the thread.
- `os_thread_id` — OS-level thread ID.
- `Status` — numeric code representing thread status.
- `instruction_address` — address of the current instruction pointer for the thread (may be NULL).
- `creation_time` — timestamp when the thread was created.
- `kernel_time` — cumulative kernel-mode CPU time used by the thread in milliseconds.
- `usermode_time` — cumulative user-mode CPU time used by the thread in milliseconds.
- `stack_base_address` — base address of the thread's stack.
- `stack_end_address` — end address of the thread's stack (may be NULL).
- `stack_bytes_committed` — committed stack size in bytes.
- `stack_bytes_used` — number of bytes currently used on the stack.
- `Affinity` — CPU affinity mask for the thread.
- `Priority` — thread priority.
- `Locale` — thread locale identifier.
- `Token` — security token data (binary, may be NULL).
- `is_impersonating` — indicator if the thread is impersonating a security context.
- `is_waiting_on_loader_lock` — indicator if the thread is waiting on the loader lock.
- `fiber_data` — fiber-related data when using fibers.
- `thread_handle` — handle to the thread (binary, may be NULL).
- `event_handle` — handle to an event object associated with the thread (binary, may be NULL).
- `scheduler_address` — address of the scheduler associated with the thread.
- `worker_address` — address of the worker associated with the thread.
- `fiber_context_address` — address of fiber context (if applicable).
- `self_address` — address representing the thread's internal structure.
- `processor_group` — processor group number for the thread.

How to interpret

- Use `kernel_time` and `usermode_time` to find CPU usage per thread.
- `instruction_address` and stack addresses can help diagnose hangs or crashes when combined with symbols.
- `started_by_sqlservr` separates SQL Server internal threads from external ones.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsThreadsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsThreadsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Thread:{BitConverter.ToString(r.ThreadAddress)} OSID:{r.OsThreadId} StartedBySql:{r.StartedBySqlservr} KernelMs:{r.KernelTime} UserMs:{r.UsermodeTime}");
}
```

See also:

- [sys.dm_os_threads](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-threads)
