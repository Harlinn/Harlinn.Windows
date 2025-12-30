# AssemblyFilesReader — reference

Overview

`AssemblyFilesReader` wraps `sys.assembly_files` and exposes file-level metadata and binary content for assembly files associated with registered CLR assemblies.

Reader SQL

```
SELECT
  af.[assembly_id],
  af.[Name],
  af.[file_id],
  af.[Content]
FROM
  [sys].[assembly_files] af
```

Selected columns (property mapping and brief meaning)

- `assembly_id` ? property: `AssemblyId` (int)
  - Assembly identifier this file belongs to.

- `Name` ? property: `Name` (string?)
  - File name within assembly.

- `file_id` ? property: `FileId` (int)
  - Identifier for the file inside the assembly registration.

- `Content` ? property: `Content` (byte[]?)
  - Binary content (blob) of the assembly file.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.AssemblyFilesDataType` objects.
