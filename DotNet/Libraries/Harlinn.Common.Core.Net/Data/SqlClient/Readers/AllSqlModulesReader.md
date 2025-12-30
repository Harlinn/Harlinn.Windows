# AllSqlModulesReader — reference

Overview

`AllSqlModulesReader` wraps `sys.all_sql_modules` and exposes the definitions and metadata for SQL modules (views, stored procedures, functions, triggers) visible to the current principal.

Reader SQL

```
SELECT
  asm.[object_id],
  asm.[Definition],
  asm.[uses_ansi_nulls],
  asm.[uses_quoted_identifier],
  asm.[is_schema_bound],
  asm.[uses_database_collation],
  asm.[is_recompiled],
  asm.[null_on_null_input],
  asm.[execute_as_principal_id],
  asm.[uses_native_compilation],
  asm.[inline_type],
  asm.[is_inlineable]
FROM
  [sys].[all_sql_modules] asm
```

Selected columns (property mapping and brief meaning)

- `object_id` ? property: `ObjectId` (int)
  - Object id of the module (e.g. procedure, view).

- `Definition` ? property: `Definition` (string?)
  - T-SQL definition text of the module.

- `uses_ansi_nulls` ? property: `UsesAnsiNulls` (bool?)
  - Module defined with ANSI_NULLS ON/OFF.

- `uses_quoted_identifier` ? property: `UsesQuotedIdentifier` (bool?)
  - Module defined with QUOTED_IDENTIFIER ON/OFF.

- `is_schema_bound` ? property: `IsSchemaBound` (bool?)
  - Whether module is schema bound.

- `uses_database_collation` ? property: `UsesDatabaseCollation` (bool?)
  - Whether uses database collation.

- `is_recompiled` ? property: `IsRecompiled` (bool?)
  - Recompile option flag.

- `null_on_null_input` ? property: `NullOnNullInput` (bool?)
  - Null-on-null-input option for functions.

- `execute_as_principal_id` ? property: `ExecuteAsPrincipalId` (int?)
  - Principal id for EXECUTE AS clause.

- `uses_native_compilation` ? property: `UsesNativeCompilation` (bool?)
  - Indicates natively compiled module.

- `inline_type` ? property: `InlineType` (bool?)
  - Inline type flag (related to inline TVFs).

- `is_inlineable` ? property: `IsInlineable` (bool?)
  - Whether the module is inlineable.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AllSqlModulesDataType` objects.

---
