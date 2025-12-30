# FulltextDocumentTypesReader — reference

Overview

`FulltextDocumentTypesReader` wraps `sys.fulltext_document_types` and returns metadata about document types that the full-text search engine can index, including class GUIDs and version/manufacturer for filters.

Reader SQL

```
SELECT
  fdt.[document_type],
  fdt.[class_id],
  fdt.[Path],
  fdt.[Version],
  fdt.[Manufacturer]
FROM
  [sys].[fulltext_document_types] fdt
```

Columns and interpretation

- `document_type` — file/document extension or document type name.
- `class_id` — GUID identifying the filter class used for this document type.
- `Path` — path to the filter or handler (nullable).
- `Version` — version string for the document type handler.
- `Manufacturer` — manufacturer or vendor of the handler (nullable).

How to interpret

- This view helps determine which document types are supported by full-text filters and which handler class is used to parse documents.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = FulltextDocumentTypesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new FulltextDocumentTypesReader(rdr, ownsReader:false);
while (r.Read())
{
    Console.WriteLine($"DocType:{r.DocumentType} Class:{r.ClassId} Version:{r.Version} Manufacturer:{r.Manufacturer}");
}
```

See also:

- [sys.fulltext_document_types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-fulltext-document-types)
