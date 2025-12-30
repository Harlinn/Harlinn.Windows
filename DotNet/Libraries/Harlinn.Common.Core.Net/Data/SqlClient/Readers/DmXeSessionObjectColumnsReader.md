# DmXeSessionObjectColumnsReader — reference

Overview

`DmXeSessionObjectColumnsReader` wraps `sys.dm_xe_session_object_columns` and returns column configuration for objects within event sessions (e.g., which columns are collected for events).

Reader SQL

```
SELECT
  dxsoc.[event_session_address],
  dxsoc.[column_name],
  dxsoc.[column_id],
  dxsoc.[column_value],
  dxsoc.[object_type],
  dxsoc.[object_name],
  dxsoc.[object_package_guid]
FROM
  [sys].[dm_xe_session_object_columns] dxsoc
```

Columns and interpretation

- `event_session_address` — binary address for the event session instance.
- `column_name` — name of the column configured.
- `column_id` — numeric id of the column.
- `column_value` — optional configured value expression for the column (nullable string).
- `object_type` — type of object holding the column (EVENT, ACTION, TARGET).
- `object_name` — name of the object.
- `object_package_guid` — GUID of the package for the object.

How to interpret

- Use to inspect which columns are being captured by a session and whether any expressions or values are configured for them.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = DmXeSessionObjectColumnsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new DmXeSessionObjectColumnsReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"Session:{BitConverter.ToString(r.EventSessionAddress)} Object:{r.ObjectName} Column:{r.ColumnName} Value:{r.ColumnValue}");
}
```

See also:

- [sys.dm_xe_session_object_columns](https://learn.microsoft.com/en-us/sql/relational-databases/system-dynamic-management-views/sys-dm-xe-session-object-columns)
