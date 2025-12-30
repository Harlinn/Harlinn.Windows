# CheckConstraintsReader — reference

Overview

`CheckConstraintsReader` wraps `sys.check_constraints` (joined to `sys.columns`) and exposes check constraint metadata and definitions for constraints on tables and views.

Reader SQL

```
SELECT cc.[name]
    ,cc.[object_id]
    ,cc.[principal_id]
    ,cc.[schema_id]
    ,cc.[parent_object_id]
    ,cc.[type]
    ,cc.[type_desc]
    ,cc.[create_date]
    ,cc.[modify_date]
    ,cc.[is_ms_shipped]
    ,cc.[is_published]
    ,cc.[is_schema_published]
    ,cc.[is_disabled]
    ,cc.[is_not_for_replication]
    ,cc.[is_not_trusted]
    ,cc.[parent_column_id]
    ,cc.[definition]
    ,cc.[uses_database_collation]
    ,cc.[is_system_named]
    ,c.[name] AS [column_name]
FROM [sys].[check_constraints] cc
JOIN [sys].[columns] c ON cc.[parent_object_id] = c.[object_id] AND cc.[parent_column_id] = c.[column_id]
```

Selected columns (property mapping and brief meaning)

- `name` ? method: `GetName()` (string)
  - Constraint name.

- `object_id` ? method: `GetObjectId()` (int)
  - Object id of the constraint.

- `principal_id` ? method: `GetPrincipalId()` (int?)
  - Owner principal id.

- `schema_id` ? method: `GetSchemaId()` (int)
  - Schema containing the parent object.

- `parent_object_id` ? method: `GetParentObjectId()` (int)
  - Object id of the parent table/view.

- `type` / `type_desc` ? methods: `GetSchemaObjectType()` / `GetSchemaObjectTypeDesc()`
  - Type code and description for the constraint object.

- `create_date` / `modify_date` ? methods: `GetCreateDate()` / `GetModifyDate()`
  - Timestamps for creation and modification.

- `is_ms_shipped`, `is_published`, `is_schema_published` ? methods returning boolean flags documenting metadata.

- `is_disabled` ? method: `GetIsDisabled()` (bool)
  - Whether constraint is disabled.

- `is_not_for_replication` ? method: `GetIsNotForReplication()` (bool)
  - Not-for-replication flag.

- `is_not_trusted` ? method: `GetIsNotTrusted()` (bool)
  - Trust status of the constraint (untrusted constraints are not enforced for query optimizations).

- `parent_column_id` ? method: `GetParentColumnId()` (int)
  - Column id in the parent object the check references.

- `definition` ? method: `GetDefinition()` (string)
  - T-SQL expression that defines the check constraint.

- `uses_database_collation` ? method: `GetUsesDatabaseCollation()` (bool)
  - Whether constraint uses database collation settings.

- `is_system_named` ? method: `GetIsSystemNamed()` (bool)
  - Whether the constraint was system-named.

- `column_name` ? method: `GetColumnName()` (string?)
  - Name of the referenced column (if available via join).

Helpers

- `GetCheckConstraint()` constructs a `CheckConstraint` object for the current row.
- `GetCheckConstraints()` iterates and returns a list of `CheckConstraint` objects.
