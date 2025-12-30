# SelectiveXmlIndexNamespacesReader

Overview

`SelectiveXmlIndexNamespacesReader` wraps `sys.selective_xml_index_namespaces` and exposes namespace declarations associated with selective XML indexes.

Reader SQL

```
SELECT
  sxin.[object_id],
  sxin.[index_id],
  sxin.[is_default_uri],
  sxin.[Uri],
  sxin.[Prefix]
FROM
  [sys].[selective_xml_index_namespaces] sxin
```

Columns and interpretation

- `object_id` (int): Object id of the XML-indexed table.
- `index_id` (int): Index id of the selective XML index.
- `is_default_uri` (bool?): Whether this namespace URI is the default namespace for the index.
- `Uri` (string?): The namespace URI declared.
- `Prefix` (string?): The prefix associated with the namespace in the index.

How to interpret

- Selective XML indexes can use namespace mappings; these rows list the prefix-to-URI bindings used for path definitions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SelectiveXmlIndexNamespacesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SelectiveXmlIndexNamespacesReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Index:{r.IndexId} URI:{r.Uri} Prefix:{r.Prefix} Default:{r.IsDefaultUri}");
```

See also:

- [sys.selective_xml_index_namespaces](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-selective-xml-index-namespaces)

