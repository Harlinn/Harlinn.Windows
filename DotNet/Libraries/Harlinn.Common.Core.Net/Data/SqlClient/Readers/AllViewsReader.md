# AllViewsReader — reference

Overview

`AllViewsReader` wraps [`sys.all_views`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-all-views-transact-sql) and exposes metadata for views accessible to the current principal.

Reader SQL

```
SELECT
  av.[Name],
  av.[object_id],
  av.[principal_id],
  av.[schema_id],
  av.[parent_object_id],
  av.[Type],
  av.[type_desc],
  av.[create_date],
  av.[modify_date],
  av.[is_ms_shipped],
  av.[is_published],
  av.[is_schema_published],
  av.[is_replicated],
  av.[has_replication_filter],
  av.[has_opaque_metadata],
  av.[has_unchecked_assembly_data],
  av.[with_check_option],
  av.[is_date_correlation_view],
  av.[is_tracked_by_cdc],
  av.[has_snapshot]
FROM
  [sys].[all_views] av
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - View name.

- `object_id` ? property: `ObjectId` (int)
  - Object identifier for the view.

- `principal_id` ? property: `PrincipalId` (int?)
  - Owner principal id.

- `schema_id` ? property: `SchemaId` (int)
  - Schema id for the view.

- `parent_object_id` ? property: `ParentObjectId` (int)
  - Parent object id.

- `Type` / `type_desc` ? properties: `Type` (string), `TypeDesc` (string?)
  - Type code and description.

- `create_date` / `modify_date` ? properties: `CreateDate` (DateTime), `ModifyDate` (DateTime)
  - Creation and modification timestamps.

- `is_ms_shipped`, `is_published`, `is_schema_published` ? flags for shipping/publication.

- `is_replicated`, `has_replication_filter` ? replication-related metadata.

- `has_opaque_metadata`, `has_unchecked_assembly_data` ? assembly/opaque metadata flags.

- `with_check_option` ? property: `WithCheckOption` (bool?)
  - Whether view has WITH CHECK OPTION.

- `is_date_correlation_view` ? property: `IsDateCorrelationView` (bool?)
  - Date correlation view marker for CDC.

- `is_tracked_by_cdc` ? property: `IsTrackedByCdc` (bool?)
  - Change data capture tracking.

- `has_snapshot` ? property: `HasSnapshot` (bool?)
  - Snapshot presence flag.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AllViewsDataType` objects.

