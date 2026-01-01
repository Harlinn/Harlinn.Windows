# AssemblyModulesReader — reference

Overview

`AssemblyModulesReader` wraps [`sys.assembly_modules`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-assembly-modules-transact-sql) and exposes metadata for assembly-based modules (CLR stored procedures, functions) defined in assemblies.

Reader SQL

```
SELECT
  am.[object_id],
  am.[assembly_id],
  am.[assembly_class],
  am.[assembly_method],
  am.[null_on_null_input],
  am.[execute_as_principal_id]
FROM
  [sys].[assembly_modules] am
```

Selected columns (property mapping and brief meaning)

- `object_id` ? property: `ObjectId` (int)
  - Object id of the assembly module (mapped SQL object).

- `assembly_id` ? property: `AssemblyId` (int)
  - Assembly id that contains the module.

- `assembly_class` ? property: `AssemblyClass` (string?)
  - CLR class name that implements the module.

- `assembly_method` ? property: `AssemblyMethod` (string?)
  - CLR method name to execute.

- `null_on_null_input` ? property: `NullOnNullInput` (bool?)
  - Whether method returns null when input is null.

- `execute_as_principal_id` ? property: `ExecuteAsPrincipalId` (int?)
  - Principal id for EXECUTE AS context.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AssemblyModulesDataType` objects.
