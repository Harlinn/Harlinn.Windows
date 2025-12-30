# DmReplTraninfoReader — reference

Overview

`DmReplTraninfoReader` wraps `sys.dm_repl_traninfo` and provides detailed information about replication transactions including LSNs, origin, command counts and processing state.

Reader SQL

```
SELECT
  drt0.[fp2p_pub_exists],
  drt0.[db_ver],
  drt0.[comp_range_address],
  drt0.[textinfo_address],
  drt0.[fsinfo_address],
  drt0.[begin_lsn],
  drt0.[commit_lsn],
  drt0.[Dbid],
  drt0.[Rows],
  drt0.[Xdesid],
  drt0.[artcache_table_address],
  drt0.[Server],
  drt0.[server_len_in_bytes],
  drt0.[Database],
  drt0.[db_len_in_bytes],
  drt0.[Originator],
  drt0.[originator_len_in_bytes],
  drt0.[orig_db],
  drt0.[orig_db_len_in_bytes],
  drt0.[cmds_in_tran],
  drt0.[is_boundedupdate_singleton],
  drt0.[begin_update_lsn],
  drt0.[delete_lsn],
  drt0.[last_end_lsn],
  drt0.[Fcomplete],
  drt0.[Fcompensated],
  drt0.[Fprocessingtext],
  drt0.[max_cmds_in_tran],
  drt0.[begin_time],
  drt0.[commit_time],
  drt0.[session_id],
  drt0.[session_phase],
  drt0.[is_known_cdc_tran],
  drt0.[error_count]
FROM
  [sys].[dm_repl_traninfo] drt0
```

Columns and interpretation

- `fp2p_pub_exists` — flag indicating if a peer-to-peer publication exists for this transaction.
- `db_ver` — internal database version identifier.
- `comp_range_address`, `textinfo_address`, `fsinfo_address` — Probably/guesswork: internal addresses for component ranges, text metadata, and filestream info.
- `begin_lsn` / `commit_lsn` — LSNs marking transaction begin and commit.
- `Dbid` — database id where the transaction was recorded.
- `Rows` — number of rows affected in the transaction.
- `Xdesid` — transaction descriptor id.
- `artcache_table_address` — Probably/guesswork: address of the article cache table entry related to transaction.
- `Server`, `Database`, `Originator`, `OrigDb` — textual names for server, database and originator; `*_len_in_bytes` denote stored lengths.
- `cmds_in_tran` — number of commands in the transaction.
- `is_boundedupdate_singleton` — flag indicating bounded-update singleton optimization.
- `begin_update_lsn`, `delete_lsn`, `last_end_lsn` — LSN markers for update/delete boundaries.
- `Fcomplete`, `Fcompensated`, `Fprocessingtext` — flags for completion, compensation and text-processing state.
- `max_cmds_in_tran` — maximum commands observed.
- `begin_time`, `commit_time` — timestamps for begin and commit.
- `session_id`, `session_phase` — session association and phase.
- `is_known_cdc_tran` — flag if known as CDC transaction.
- `error_count` — number of errors observed processing the transaction.

How to interpret

- Useful for tracking replication transaction lifecycle, diagnosing missed commits or compensated transactions.
- LSN and timestamp fields help correlate replication latency and apply progress.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmReplTraninfoReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmReplTraninfoReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"BeginLSN:{r.BeginLsn} CommitLSN:{r.CommitLsn} DB:{r.Database} Rows:{r.Rows} Cmds:{r.CmdsInTran} ErrorCount:{r.ErrorCount}");
}
```

See also:

- [sys.dm_repl_traninfo](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-repl-traninfo)
