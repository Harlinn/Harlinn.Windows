# DmTranVersionStoreReader — reference

Overview

`DmTranVersionStoreReader` wraps `sys.dm_tran_version_store` and returns version store entries for versioned rows including image parts and status.

Reader SQL

```
SELECT
  dtvs.[transaction_sequence_num],
  dtvs.[version_sequence_num],
  dtvs.[database_id],
  dtvs.[rowset_id],
  dtvs.[Status],
  dtvs.[min_length_in_bytes],
  dtvs.[record_length_first_part_in_bytes],
  dtvs.[record_image_first_part],
  dtvs.[record_length_second_part_in_bytes],
  dtvs.[record_image_second_part]
FROM
  [sys].[dm_tran_version_store] dtvs
```

Columns and interpretation

- `transaction_sequence_num` — sequence number of the transaction that generated the version.
- `version_sequence_num` — sequence number for the version entry.
- `database_id` — database id for the versioned row.
- `rowset_id` — rowset id associated with the versioned row.
- `Status` — status byte indicating version state.
- `min_length_in_bytes` — minimum length of the stored version.
- `record_length_first_part_in_bytes` / `record_length_second_part_in_bytes` — lengths of the first and second parts of the stored row image.
- `record_image_first_part` / `record_image_second_part` — binary data containing the row image parts.

How to interpret

- Use status and sequence numbers to track versions retained by long-running transactions. Combining with snapshot sequence numbers and transaction information helps locate retention causes.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranVersionStoreReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranVersionStoreReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"TxSeq:{r.TransactionSequenceNum} VersSeq:{r.VersionSequenceNum} DB:{r.DatabaseId} Rowset:{r.RowsetId} Status:{r.Status}");
}
```

See also:

- [sys.dm_tran_version_store](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-version-store)
