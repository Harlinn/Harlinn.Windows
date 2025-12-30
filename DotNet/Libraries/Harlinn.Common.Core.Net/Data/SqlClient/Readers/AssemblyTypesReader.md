# AssemblyTypesReader — reference

Overview

`AssemblyTypesReader` wraps `sys.assembly_types` and exposes type metadata for user-defined types supplied by CLR assemblies.

Reader SQL

```
SELECT
  at.[Name],
  at.[system_type_id],
  at.[user_type_id],
  at.[schema_id],
  at.[principal_id],
  at.[max_length],
  at.[Precision],
  at.[Scale],
  at.[collation_name],
  at.[is_nullable],
  at.[is_user_defined],
  at.[is_assembly_type],
  at.[default_object_id],
  at.[rule_object_id],
  at.[assembly_id],
  at.[assembly_class],
  at.[is_binary_ordered],
  at.[is_fixed_length],
  at.[prog_id],
  at.[assembly_qualified_name],
  at.[is_table_type]
FROM
  [sys].[assembly_types] at
```

Selected columns (property mapping and brief meaning)

- `Name` ? property: `Name` (string)
  - Type name.

- `system_type_id` / `user_type_id` ? properties: `SystemTypeId` (byte), `UserTypeId` (int)
  - Type identifiers.

- `schema_id` / `principal_id` ? properties: `SchemaId` (int), `PrincipalId` (int?)
  - Ownership and schema details.

- `max_length`, `Precision`, `Scale`, `collation_name` ? sizing/collation metadata.

- `is_nullable`, `is_user_defined`, `is_assembly_type` ? flags about type behavior and origin.

- `default_object_id`, `rule_object_id` ? default/rule object references.

- `assembly_id`, `assembly_class`, `assembly_qualified_name` ? linkage to the implementing assembly.

- `is_binary_ordered`, `is_fixed_length`, `prog_id`, `is_table_type` ? additional attributes and progID.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AssemblyTypesDataType` objects.
