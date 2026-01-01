# XmlSchemaTypesReader

Overview

`XmlSchemaTypesReader` wraps `sys.xml_schema_types` and exposes type definitions (simple and complex) within XML schema collections.

Reader SQL

```
SELECT
  xst.[xml_component_id],
  xst.[xml_collection_id],
  xst.[xml_namespace_id],
  xst.[is_qualified],
  xst.[Name],
  xst.[symbol_space],
  xst.[symbol_space_desc],
  xst.[Kind],
  xst.[kind_desc],
  xst.[Derivation],
  xst.[derivation_desc],
  xst.[base_xml_component_id],
  xst.[scoping_xml_component_id],
  xst.[is_abstract],
  xst.[allows_mixed_content],
  xst.[is_extension_blocked],
  xst.[is_restriction_blocked],
  xst.[is_final_extension],
  xst.[is_final_restriction],
  xst.[is_final_list_member],
  xst.[is_final_union_member]
FROM
  [sys].[xml_schema_types] xst
```

Columns and interpretation

- `xml_component_id` (int): Component id for the type definition.
- `xml_collection_id` (int): Collection id.
- `xml_namespace_id` (int): Namespace id.
- `is_qualified` (bit): Whether the type is namespace-qualified.
- `Name` (nvarchar?): Type name (may be NULL for anonymous types).
- `symbol_space`/`symbol_space_desc` (nvarchar): Internal symbol space classification and description.
- `Kind`/`kind_desc` (nvarchar): Kind and readable description indicating simple/complex type.
- `Derivation`/`derivation_desc` (nvarchar): Derivation method (restriction/extension) and description.
- `base_xml_component_id` (int?): Base type component id from which the type is derived.
- `scoping_xml_component_id` (int?): Component id that scopes the type.
- `is_abstract` (bit): Whether the type is abstract.
- `allows_mixed_content` (bit): Whether the type allows mixed content (elements + text).
- `is_extension_blocked`/`is_restriction_blocked` (bit): Blocking flags for derivation.
- `is_final_extension`/`is_final_restriction` (bit): Final flags preventing further derivation by extension or restriction.
- `is_final_list_member`/`is_final_union_member` (bit): Final flags related to list/union membership.

How to interpret

- Use type rows to understand the type system defined in XML schema collections, including derivation chains and content model constraints.
- Anonymous types will lack a `Name` and are scoped to the component that references them.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaTypesReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaTypesReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"TypeId:{r.XmlComponentId} Name:{r.Name} Abstract:{r.IsAbstract} Mixed:{r.AllowsMixedContent}");
```

See also:

- [sys.xml_schema_types](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-types)
