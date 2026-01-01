# AssemblyReferencesReader — reference

Overview

`AssemblyReferencesReader` wraps [`sys.assembly_references`](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-assembly-references-transact-sql) and exposes relationships between assemblies (which assembly references another).

Reader SQL

```
SELECT
  ar0.[assembly_id],
  ar0.[referenced_assembly_id]
FROM
  [sys].[assembly_references] ar0
```

Selected columns (property mapping and brief meaning)

- `assembly_id` ? property: `AssemblyId` (int)
  - Referencing assembly id.

- `referenced_assembly_id` ? property: `ReferencedAssemblyId` (int)
  - Referenced assembly id.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AssemblyReferencesDataType` objects.
