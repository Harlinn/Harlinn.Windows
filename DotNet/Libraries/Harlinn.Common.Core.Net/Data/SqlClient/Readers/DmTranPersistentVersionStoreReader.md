# DmTranPersistentVersionStoreReader — reference

Overview

`DmTranPersistentVersionStoreReader` wraps `sys.dm_tran_persistent_version_store` and exposes entries in the persistent version store for versioned data, including row images and chain links.

Reader SQL

```
SELECT
  dtpvs.[xdes_ts_push],
  dtpvs.[xdes_ts_tran],
  dtpvs.[subid_push],
  dtpvs.[subid_tran],
  dtpvs.[rowset_id],
  dtpvs.[sec_version_rid],
  dtpvs.[min_len],
  dtpvs.[seq_num],
  dtpvs.[prev_row_in_chain],
  dtpvs.[row_version]
FROM
  [sys].[dm_tran_persistent_version_store] dtpvs
```

Columns and interpretation

- `xdes_ts_push`, `xdes_ts_tran` — internal transaction timestamps for the version push and transaction.
- `subid_push`, `subid_tran` — subtransaction ids for push and transaction (nullable).
- `rowset_id` — identifier for the rowset (long).
- `sec_version_rid` — secondary version RID (binary), used internally to locate versions.
- `min_len` — minimum length for the versioned row.
- `seq_num` — sequence number for the version entry.
- `prev_row_in_chain` — binary pointer to the previous row in the version chain.
- `row_version` — binary image of the row version stored.

How to interpret

- This DMV is used for low-level inspection of version store entries and is mainly useful for debugging versioning and retention behavior.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranPersistentVersionStoreReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranPersistentVersionStoreReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Rowset:{r.RowsetId} Seq:{r.SeqNum} RowVersionLen:{r.RowVersion.Length}");
}
```

See also:

- [sys.dm_tran_persistent_version_store](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-persistent-version-store)
