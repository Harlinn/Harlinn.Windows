# DmReplSchemasReader — reference

Overview

`DmReplSchemasReader` wraps `sys.dm_repl_schemas` and exposes replication schema metadata including per-column and per-rowset characteristics used during replication.

Reader SQL

```
SELECT
  drs.[artcache_schema_address],
  drs.[Tabid],
  drs.[Indexid],
  drs.[Idsch],
  drs.[Tabschema],
  drs.[Cctabschema],
  drs.[Tabname],
  drs.[Cctabname],
  drs.[rowsetid_delete],
  drs.[rowsetid_insert],
  drs.[num_pk_cols],
  drs.[Pcitee],
  drs.[re_numtextcols],
  drs.[re_schema_lsn_begin],
  drs.[re_schema_lsn_end],
  drs.[re_numcols],
  drs.[re_colid],
  drs.[re_awcName],
  drs.[re_ccName],
  drs.[re_colattr],
  drs.[re_maxlen],
  drs.[re_prec],
  drs.[re_scale],
  drs.[re_collatid],
  drs.[re_xvtype],
  drs.[re_offset],
  drs.[re_bitpos],
  drs.[re_fNullable],
  drs.[re_fAnsiTrim],
  drs.[re_computed],
  drs.[se_rowsetid],
  drs.[se_schema_lsn_begin],
  drs.[se_schema_lsn_end],
  drs.[se_numcols],
  drs.[se_colid],
  drs.[se_maxlen],
  drs.[se_prec],
  drs.[se_scale],
  drs.[se_collatid],
  drs.[se_xvtype],
  drs.[se_offset],
  drs.[se_bitpos],
  drs.[se_fNullable],
  drs.[se_fAnsiTrim],
  drs.[se_computed],
  drs.[se_nullBitInLeafRows]
FROM
  [sys].[dm_repl_schemas] drs
```

Columns and interpretation

This DMV returns a wide set of replication schema attributes. Many fields are internal; where official docs are not explicit, notes are marked as "Probably/guesswork:".

- `artcache_schema_address` — Probably/guesswork: internal address for cached schema info.
- `Tabid` / `Indexid` — internal table and index identifiers.
- `Idsch` — Probably/guesswork: internal schema id.
- `Tabschema` / `Tabname` — schema and name of the table involved.
- `Cctabschema` / `Cctabname` — collation or coded name length fields (internal representation).
- `rowsetid_delete` / `rowsetid_insert` — identifiers for delete/insert rowset descriptors used in replication.
- `num_pk_cols` — number of primary key columns.
- `Pcitee` — Probably/guesswork: pointer to primary key column information.
- `re_*` prefixed columns — source (replication extract) column metadata: number of text columns, schema LSN range, column counts and attributes (`re_colid`, `re_awcName`, `re_colattr`, sizes, precision, scale, collation id, xml/SQL type code, offsets, bit positions, nullable and ANSI trim flags, computed indication).
- `se_*` prefixed columns — subscriber/external (apply) side column metadata (mirrors `re_*` for target side): rowset id, schema LSN range, column counts and attributes, and `se_nullBitInLeafRows` flag.

How to interpret

- Useful for deep inspection of replication schema differences between publisher and subscriber, and diagnosing replication schema-mapping issues.
- LSN ranges (`*_schema_lsn_begin`, `*_schema_lsn_end`) can help detect schema changes affecting replication.

Example

```csharp
using var conn = new SqlConnection(connectionString);
conn.Open();
using var cmd = conn.CreateCommand();
cmd.CommandText = DmReplSchemasReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmReplSchemasReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Table:{r.Tabschema}.{r.Tabname} PKcols:{r.NumPkCols} REcols:{r.ReNumcols} SEcols:{r.SeNumcols}");
}
```

See also:

- [sys.dm_repl_schemas](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-repl-schemas)
