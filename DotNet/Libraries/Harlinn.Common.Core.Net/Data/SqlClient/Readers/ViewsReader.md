# ViewsReader

Overview

`ViewsReader` wraps `sys.views` and exposes metadata about views defined in the database, including replication and CDC-related flags.

Reader SQL

```
SELECT [name]
    ,[object_id]
    ,[principal_id]
    ,[schema_id]
    ,[parent_object_id]
    ,[type]
    ,[type_desc]
    ,[create_date]
    ,[modify_date]
    ,[is_ms_shipped]
    ,[is_published]
    ,[is_schema_published]
    ,[is_replicated]
    ,[has_replication_filter]
    ,[has_opaque_metadata]
    ,[has_unchecked_assembly_data]
    ,[with_check_option]
    ,[is_date_correlation_view]
    ,[is_tracked_by_cdc]
    ,[has_snapshot]
FROM [sys].[views]
```

Columns and interpretation

- `name` (sysname): View name.
- `object_id` (int): Object id of the view.
- `principal_id` (int?): Principal id (owner) for the view.
- `schema_id` (int): Schema id containing the view.
- `parent_object_id` (int): Parent object id if the view is derived or nested.
- `type`/`type_desc` (nvarchar): Object type and description.
- `create_date`/`modify_date` (datetime): Creation and last modification times.
- `is_ms_shipped` (bit): Whether the view is shipped by Microsoft.
- `is_published`/`is_schema_published` (bit): Publication flags for replication.
- `is_replicated` (bit): Whether the view participates in replication.
- `has_replication_filter` (bit): Whether replication filters exist for the view.
- `has_opaque_metadata` (bit): Opaque metadata flag for views with external or opaque definitions.
- `has_unchecked_assembly_data` (bit): Unchecked assembly data flag.
- `with_check_option` (bit): Whether the view was created WITH CHECK OPTION.
- `is_date_correlation_view` (bit): Date correlation view flag used in some change tracking scenarios.
- `is_tracked_by_cdc` (bit): Whether the view is tracked by change data capture.
- `has_snapshot` (bit): Snapshot related flag.

How to interpret

- Use this view for auditing and examining view-level properties, particularly those related to replication and change tracking.
- `with_check_option` indicates the view enforces checks on modifications that go through the view.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = ViewsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new ViewsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"View:{r.GetName()} ObjId:{r.GetObjectId()} Replicated:{r.GetIsReplicated()} CDC:{r.GetIsTrackedByCdc()}");
```

See also:

- [sys.views](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-views)
