# AllObjectsReader — reference

Overview

`AllObjectsReader` wraps a query on `sys.all_objects` and exposes metadata about database objects (tables, views, procedures, etc.) visible to the current principal.

Reader SQL

```
SELECT
  ao.[Name],
  ao.[object_id],
  ao.[principal_id],
  ao.[schema_id],
  ao.[parent_object_id],
  ao.[Type],
  ao.[type_desc],
  ao.[create_date],
  ao.[modify_date],
  ao.[is_ms_shipped],
  ao.[is_published],
  ao.[is_schema_published]
FROM
  [sys].[all_objects] ao
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - Object name.

- `object_id` ? property: `ObjectId` (int)
  - Object identifier.

- `principal_id` ? property: `PrincipalId` (int?)
  - Owner principal id.

- `schema_id` ? property: `SchemaId` (int)
  - Schema id that contains the object.

- `parent_object_id` ? property: `ParentObjectId` (int)
  - Parent object id (for child objects).

- `Type` ? property: `Type` (string?)
  - Short type code (one-letter type code used by SQL Server).

- `type_desc` ? property: `TypeDesc` (string?)
  - Descriptive type string (e.g. USER_TABLE, VIEW, SQL_STORED_PROCEDURE).

- `create_date` ? property: `CreateDate` (DateTime)
  - Creation timestamp.

- `modify_date` ? property: `ModifyDate` (DateTime)
  - Last modification timestamp.

- `is_ms_shipped` ? property: `IsMsShipped` (bool?)
  - Whether object is shipped with Microsoft.

- `is_published` ? property: `IsPublished` (bool?)
  - Publication metadata.

- `is_schema_published` ? property: `IsSchemaPublished` (bool?)
  - Schema publication metadata.

Usage

Use the reader's typed properties to access object metadata or convert rows to `Types.AllObjectsDataType` / `Types.SchemaObject` instances via `ToDataObject()` / `ToList()` / `GetSchemaObject()`.

---
