# DmTranTopVersionGeneratorsReader — reference

Overview

`DmTranTopVersionGeneratorsReader` wraps `sys.dm_tran_top_version_generators` and returns aggregated information about top version generators—rowsets that produce many versions.

Reader SQL

```
SELECT
  dttvg.[database_id],
  dttvg.[rowset_id],
  dttvg.[aggregated_record_length_in_bytes]
FROM
  [sys].[dm_tran_top_version_generators] dttvg
```

Columns and interpretation

- `database_id` — database id where the rowset exists (nullable short).
- `rowset_id` — identifier for the rowset generating versions.
- `aggregated_record_length_in_bytes` — aggregated length of records produced by the top generator, in bytes.

How to interpret

- Use to identify rowsets that generate a large volume of versioned records—helpful when diagnosing version store growth.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmTranTopVersionGeneratorsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmTranTopVersionGeneratorsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DB:{r.DatabaseId} Rowset:{r.RowsetId} AggBytes:{r.AggregatedRecordLengthInBytes}");
}
```

See also:

- [sys.dm_tran_top_version_generators](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-tran-top-version-generators)
