# SystemViewsReader

Overview

`SystemViewsReader` wraps `sys.system_views` and exposes metadata for system-defined views, including replication and CDC tracking properties.

Reader SQL

```
SELECT ssv.[name]
    ,ssv.[object_id]
    ,ssv.[principal_id]
    ,ssv.[schema_id]
    ,ssv.[parent_object_id]
    ,ssv.[type]
    ,ssv.[type_desc]
    ,ssv.[create_date]
    ,ssv.[modify_date]
    ,ssv.[is_ms_shipped]
    ,ssv.[is_published]
    ,ssv.[is_schema_published]
    ,ssv.[is_replicated]
    ,ssv.[has_replication_filter]
    ,ssv.[has_opaque_metadata]
    ,ssv.[has_unchecked_assembly_data]
    ,ssv.[with_check_option]
    ,ssv.[is_date_correlation_view]
    ,ssv.[is_tracked_by_cdc]
    ,ssv.[has_snapshot]
    ,ss.[name] as SchemaName
FROM [sys].[system_views] ssv
LEFT JOIN [sys].[schemas] ss ON (ssv.[schema_id] = ss.[schema_id])
```

Columns and interpretation

- `name` (string): View name.
- `object_id` (int): Object id of the view.
- `principal_id` (int?): Principal id (owner) of the view.
- `schema_id` (int): Schema id containing the view.
- `parent_object_id` (int): Parent object id if the view is derived from another object.
- `type` (string): Object type code.
- `type_desc` (string): Description of the object type.
- `create_date` (datetime): Creation date.
- `modify_date` (datetime): Last modification date.
- `is_ms_shipped` (bit): Whether Microsoft shipped the view.
- `is_published` (bit): Publication flag.
- `is_schema_published` (bit): Schema publication flag.
- `is_replicated` (bit): Whether the view participates in replication.
- `has_replication_filter` (bit): Whether the view has a replication filter.
- `has_opaque_metadata` (bit): Whether the view has opaque metadata (e.g., external resources).
- `has_unchecked_assembly_data` (bit): Unchecked assembly data flag.
- `with_check_option` (bit): Whether the view was created WITH CHECK OPTION.
- `is_date_correlation_view` (bit): Date correlation view flag (used for change tracking/CDC patterns).
- `is_tracked_by_cdc` (bit): Whether the view is tracked by CDC.
- `has_snapshot` (bit): Snapshot-related flag.
- `SchemaName` (string): Name of the schema resolved from `schema_id`.

How to interpret

- Use `object_id` and `SchemaName` to find the definition and relate to other schema objects.
- Replication and CDC flags describe integration with data-change or distribution features.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SystemViewsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SystemViewsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"View:{r.GetName()} Schema:{r.GetSchemaName()} Replicated:{r.GetIsReplicated()} CDC:{r.GetIsTrackedByCdc()}");
```

See also:

- [sys.system_views](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-system-views)
