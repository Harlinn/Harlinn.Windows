# DmClrLoadedAssembliesReader — reference

Overview

`DmClrLoadedAssembliesReader` wraps `sys.dm_clr_loaded_assemblies` and exposes assemblies loaded into CLR appdomains.

Reader SQL

```
SELECT
  dcla.[assembly_id],
  dcla.[appdomain_address],
  dcla.[load_time]
FROM
  [sys].[dm_clr_loaded_assemblies] dcla
```

Selected columns (property mapping and brief meaning)

- `assembly_id` ? `AssemblyId` (int?): Identifier of the loaded assembly.
- `appdomain_address` ? `AppdomainAddress` (byte[]?): Address token of the appdomain where assembly is loaded.
- `load_time` ? `LoadTime` (DateTime?): Time when assembly was loaded.

Helpers

- `ToDataObject()` / `ToList()` convert rows into `Types.DmClrLoadedAssembliesDataType` objects.
