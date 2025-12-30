# IndexColumnsReader — reference

Overview

`IndexColumnsReader` wraps `sys.index_columns` joined with `sys.columns` to return column-level information for indexes, including key order, inclusion, and columnstore order.

Reader SQL

```
SELECT ic.[object_id]
    ,ic.[index_id]
    ,ic.[index_column_id]
    ,ic.[column_id]
    ,ic.[key_ordinal]
    ,ic.[partition_ordinal]
    ,ic.[is_descending_key]
    ,ic.[is_included_column]
    ,ic.[column_store_order_ordinal]
    , c.[name] AS [column_name]
FROM [sys].[index_columns] ic
INNER JOIN sys.columns c ON ic.object_id = c.object_id AND ic.column_id = c.column_id
```

Columns and interpretation

- `object_id`, `index_id`, `index_column_id` — identify the index and the column within it.
- `column_id` — id of the column in the table.
- `key_ordinal` — ordinal position of the column in the index key (signed byte).
- `partition_ordinal` — ordinal used for partitioning (signed byte).
- `is_descending_key` — whether the index key ordering for this column is descending.
- `is_included_column` — whether the column is included (non-key) in a nonclustered index.
- `column_store_order_ordinal` — ordinal for columnstore order (byte).
- `column_name` — name of the column joined from `sys.columns`.

How to interpret

- The `key_ordinal` distinguishes key columns vs included columns. Included columns have `is_included_column = true` and typically `key_ordinal = 0`.
- `column_store_order_ordinal` is relevant for columnstore indexes to determine ordering of columns.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = IndexColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new IndexColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    var ic = r.GetIndexColumn();
    Console.WriteLine($"Obj:{ic.ObjectId} Idx:{ic.IndexId} Col:{ic.ColumnName} KeyOrd:{ic.KeyOrdinal} Included:{ic.IsIncludedColumn}");
}
```

See also:

- [sys.index_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-index-columns)
- [sys.columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-columns)
