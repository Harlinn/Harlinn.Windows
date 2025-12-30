# ExternalTableColumnsReader — reference

Overview

`ExternalTableColumnsReader` wraps `sys.external_table_columns` and returns metadata about columns in external tables such as column ids and whether they are partition or hash columns.

Reader SQL

```
SELECT
  etc.[object_id],
  etc.[column_id],
  etc.[partition_column_ordinal],
  etc.[hash_column_ordinal]
FROM
  [sys].[external_table_columns] etc
```

Columns and interpretation

- `object_id` — object id of the external table.
- `column_id` — column id within the table.
- `partition_column_ordinal` — ordinal position of the column within the partitioning key (nullable). If non-null, this column participates in partitioning.
- `hash_column_ordinal` — ordinal position of the column within a hash distribution key (nullable). If non-null, this column participates in hash distribution.

How to interpret

- Use `partition_column_ordinal` and `hash_column_ordinal` to determine distribution and partitioning behavior defined for the external table.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ExternalTableColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ExternalTableColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"TableObj:{r.ObjectId} ColId:{r.ColumnId} PartOrd:{r.PartitionColumnOrdinal} HashOrd:{r.HashColumnOrdinal}");
}
```

See also:

- [sys.external_table_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-external-table-columns)
