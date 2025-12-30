# SyscscontainersReader

Overview

`SyscscontainersReader` wraps `sys.syscscontainers` and exposes blob container metadata used for cloud storage integration (e.g., for FILESTREAM or external blob storage).

Reader SQL

```
SELECT
  s.[blob_container_id],
  s.[blob_container_url],
  s.[blob_container_type]
FROM
  [sys].[syscscontainers] s
```

Columns and interpretation

- `blob_container_id` (short): Identifier for the blob container.
- `blob_container_url` (string?): URL or connection string for the blob container.
- `blob_container_type` (byte?): Type code describing the container type (e.g., Azure Blob Storage).

How to interpret

- Use `blob_container_url` to access the external storage endpoint; `blob_container_type` indicates the provider type. This view supports features where SQL Server stores large objects externally.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SyscscontainersReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SyscscontainersReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Container:{r.BlobContainerId} URL:{r.BlobContainerUrl} Type:{r.BlobContainerType}");
```

See also:

- sys.syscscontainers (internal/legacy)
