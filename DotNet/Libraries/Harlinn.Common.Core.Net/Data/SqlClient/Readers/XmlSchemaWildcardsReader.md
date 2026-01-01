# XmlSchemaWildcardsReader

Overview

`XmlSchemaWildcardsReader` wraps `sys.xml_schema_wildcards` and exposes wildcard components (<any> or <anyAttribute>) defined in XML schema collections.

Reader SQL

```
SELECT
  xsw.[xml_component_id],
  xsw.[xml_collection_id],
  xsw.[xml_namespace_id],
  xsw.[is_qualified],
  xsw.[Name],
  xsw.[symbol_space],
  xsw.[symbol_space_desc],
  xsw.[Kind],
  xsw.[kind_desc],
  xsw.[Derivation],
  xsw.[derivation_desc],
  xsw.[base_xml_component_id],
  xsw.[scoping_xml_component_id],
  xsw.[process_content],
  xsw.[process_content_desc],
  xsw.[disallow_namespaces]
FROM
  [sys].[xml_schema_wildcards] xsw
```

Columns and interpretation

- `xml_component_id` (int): Wildcard component id.
- `xml_collection_id` (int): Collection id.
- `xml_namespace_id` (int): Namespace id context.
- `is_qualified` (bit): Qualification flag.
- `Name` (nvarchar?): Name of the wildcard component if named.
- `symbol_space`/`symbol_space_desc` (nvarchar): Internal symbol space/classification and description.
- `Kind`/`kind_desc` (nvarchar): Kind code and description indicating wildcard component.
- `Derivation`/`derivation_desc` (nvarchar): Derivation info.
- `base_xml_component_id` (int?): Base component id.
- `scoping_xml_component_id` (int?): Scoping component id where wildcard applies.
- `process_content` (nvarchar): ProcessContents setting for wildcard (strict, lax, skip).
- `process_content_desc` (nvarchar?): Description of process content behavior.
- `disallow_namespaces` (bit): Whether namespace tokens like ##other are disallowed.

How to interpret

- Wildcard rows describe how permissive content matching is for elements/attributes not explicitly declared in the schema; use `process_content` and namespace rules to determine validation behavior.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaWildcardsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaWildcardsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"Wildcard:{r.XmlComponentId} Process:{r.ProcessContent} DisallowNamespaces:{r.DisallowNamespaces}");
```

See also:

- [sys.xml_schema_wildcards](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-wildcards)
