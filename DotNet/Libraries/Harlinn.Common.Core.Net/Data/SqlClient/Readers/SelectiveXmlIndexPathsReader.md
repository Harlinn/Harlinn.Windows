# SelectiveXmlIndexPathsReader

Overview

`SelectiveXmlIndexPathsReader` wraps `sys.selective_xml_index_paths` and exposes path definitions and type information for selective XML indexes.

Reader SQL

```
SELECT
  sxip.[object_id],
  sxip.[index_id],
  sxip.[path_id],
  sxip.[Path],
  sxip.[Name],
  sxip.[path_type],
  sxip.[path_type_desc],
  sxip.[xml_component_id],
  sxip.[xquery_type_description],
  sxip.[is_xquery_type_inferred],
  sxip.[xquery_max_length],
  sxip.[is_xquery_max_length_inferred],
  sxip.[is_node],
  sxip.[system_type_id],
  sxip.[user_type_id],
  sxip.[max_length],
  sxip.[Precision],
  sxip.[Scale],
  sxip.[collation_name],
  sxip.[is_singleton]
FROM
  [sys].[selective_xml_index_paths] sxip
```

Columns and interpretation

- `object_id` (int): Object id of the XML-indexed table.
- `index_id` (int): Index id of the selective XML index.
- `path_id` (int?): Identifier for the path entry.
- `Path` (string?): The XPath expression used in the selective index.
- `Name` (string?): Name assigned to this path (if any).
- `path_type` (byte?): Numeric path type code; `path_type_desc` gives text (e.g., ELEMENT, ATTRIBUTE).
- `path_type_desc` (string?): Description of the path type.
- `xml_component_id` (int?): Component id for xml indexing internals.
- `xquery_type_description` (string?): The XQuery type description inferred or specified for this path.
- `is_xquery_type_inferred` (bool?): Whether xquery type was inferred.
- `xquery_max_length` (int?): Max length determined for XQuery typed value.
- `is_xquery_max_length_inferred` (bool?): Whether max length was inferred.
- `is_node` (bool?): Whether the path returns an XML node rather than a scalar value.
- `system_type_id`, `user_type_id` (byte?/byte?): Type identifiers for resulting values.
- `max_length`, `Precision`, `Scale` (short?/byte?/byte?): Type-specific size and precision info.
- `collation_name` (string?): Collation for string typed paths.
- `is_singleton` (bool?): Whether the path returns a single value per document (singleton).

How to interpret

- These rows describe how selective XML index paths extract typed values from XML documents stored in the table.
- Use `Path` combined with namespace mappings from `selective_xml_index_namespaces` to fully resolve XPath expressions.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = SelectiveXmlIndexPathsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new SelectiveXmlIndexPathsReader(rdr, ownsReader:false);
while (r.Read())
    Console.WriteLine($"Index:{r.IndexId} Path:{r.Path} Type:{r.PathTypeDesc} Singleton:{r.IsSingleton}");
```

See also:

- [sys.selective_xml_index_paths](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-selective-xml-index-paths)

