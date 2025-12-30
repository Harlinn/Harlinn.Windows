# DmOsWorkerLocalStorageReader — reference

Overview

`DmOsWorkerLocalStorageReader` wraps `sys.dm_os_worker_local_storage` and reveals worker-local pointers and addresses for various per-worker subsystems.

Reader SQL

```
SELECT
  dowls.[worker_address],
  dowls.[comp_exec_ctxt_address],
  dowls.[ec_address],
  dowls.[broker_address],
  dowls.[task_proxy_address],
  dowls.[msqlxact_address],
  dowls.[sql_prof_address],
  dowls.[stack_checker_address],
  dowls.[host_task_address],
  dowls.[sni_error_address],
  dowls.[queryscan_address],
  dowls.[diag_address],
  dowls.[query_driver_address],
  dowls.[federatedxact_address],
  dowls.[filestream_address],
  dowls.[qe_cc_address],
  dowls.[xtp_address],
  dowls.[gq_address],
  dowls.[extensibility_ctxt_address]
FROM
  [sys].[dm_os_worker_local_storage] dowls
```

Columns and interpretation

- Each column returns a binary address or pointer to a per-worker data structure used internally by SQL Server. Examples:
  - `worker_address` — address of the worker structure.
  - `comp_exec_ctxt_address` — compiled execution context address.
  - `ec_address` — execution context address.
  - `broker_address` — service broker related structure address.
  - `task_proxy_address` — task proxy structure address.
  - `msqlxact_address` — MSQL transaction structure address.
  - `sql_prof_address` — SQL profiling structure address.
  - `stack_checker_address` — stack checker structure address.
  - `host_task_address` — host task structure address.
  - `sni_error_address` — SNI error tracking address.
  - `queryscan_address` — query scan context address.
  - `diag_address` — diagnostics context address.
  - `query_driver_address` — query driver context address.
  - `federatedxact_address` — federated transaction context address.
  - `filestream_address` — filestream context address.
  - `qe_cc_address` — query execution concurrency context address.
  - `xtp_address` — In-memory OLTP (XTP) context address.
  - `gq_address` — gated queue or global queue context address.
  - `extensibility_ctxt_address` — extensibility context address.

How to interpret

- These addresses are primarily useful for low-level debugging and correlation between DMVs; they map to internal SQL Server structures and are not directly meaningful without symbols or internal knowledge.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmOsWorkerLocalStorageReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmOsWorkerLocalStorageReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Worker:{BitConverter.ToString(r.WorkerAddress)} EC:{BitConverter.ToString(r.EcAddress)} TaskProxy:{BitConverter.ToString(r.TaskProxyAddress)}");
}
```

See also:

- [sys.dm_os_worker_local_storage](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-os-worker-local-storage)
