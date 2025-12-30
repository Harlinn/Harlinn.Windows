# DefaultConstraintsReader — reference

Overview

`DefaultConstraintsReader` wraps `sys.default_constraints` and exposes metadata for default constraints defined in the database.

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
    ,[parent_column_id]
    ,[definition]
    ,[is_system_named]
FROM [sys].[default_constraints]
```

Selected columns (method mapping and brief meaning)

- `name` ? `GetName()` (string): Constraint name.
- `object_id` ? `GetObjectId()` (int): Object id of constraint.
- `principal_id` ? `GetPrincipalId()` (int?): Principal who created the constraint.
- `schema_id` ? `GetSchemaId()` (int): Schema id where constraint resides.
- `parent_object_id` ? `GetParentObjectId()` (int): Object id of the parent table or object.
- `type` / `type_desc` ? type code and description for the constraint object.
- `create_date` / `modify_date` ? timestamps.
- `is_ms_shipped` ? `GetIsMsShipped()` (bool): Whether the constraint is shipped by Microsoft.
- `is_published` / `is_schema_published` ? publication flags.
- `parent_column_id` ? `GetParentColumnId()` (int): Column id that the default applies to.
- `definition` ? `GetDefinition()` (string): T-SQL expression defining the default value.
- `is_system_named` ? `GetIsSystemNamed()` (bool): Whether the system generated the constraint name.

Helpers

- `GetDefaultConstraint()` maps current row to a `DefaultConstraint` instance.
- `GetDefaultConstraints()` reads all rows into a list.
