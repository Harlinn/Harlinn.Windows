# FunctionOrderColumnsReader — reference

Overview

`FunctionOrderColumnsReader` wraps `sys.function_order_columns` and returns column ordering information for table-valued function results that define ORDER BY columns.

Reader SQL

```
SELECT
  foc.[object_id],
  foc.[order_column_id],
  foc.[column_id],
  foc.[is_descending]
FROM
  [sys].[function_order_columns] foc
```

Columns and interpretation

- `object_id` — object id of the function.
- `order_column_id` — ordinal within the function's ORDER BY column list.
- `column_id` — column id in the returned rowset that corresponds to the ORDER BY entry.
- `is_descending` — nullable boolean indicating whether the ordering for that column is descending.

How to interpret

- Use this view to understand how a table-valued function declares ordering for its result columns; `order_column_id` gives order precedence.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FunctionOrderColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FunctionOrderColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"FuncObj:{r.ObjectId} OrderIdx:{r.OrderColumnId} ColId:{r.ColumnId} Desc:{r.IsDescending}");
}
```

See also:

- [sys.function_order_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-function-order-columns)
