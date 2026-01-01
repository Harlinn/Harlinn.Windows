# XmlSchemaElementsReader

Overview

`XmlSchemaElementsReader` wraps `sys.xml_schema_elements` and exposes information about element components defined in XML schema collections.

Reader SQL

```
SELECT
  xse.[xml_component_id],
  xse.[xml_collection_id],
  xse.[xml_namespace_id],
  xse.[is_qualified],
  xse.[Name],
  xse.[symbol_space],
  xse.[symbol_space_desc],
  xse.[Kind],
  xse.[kind_desc],
  xse.[Derivation],
  xse.[derivation_desc],
  xse.[base_xml_component_id],
  xse.[scoping_xml_component_id],
  xse.[is_default_fixed],
  xse.[is_abstract],
  xse.[is_nillable],
  xse.[must_be_qualified],
  xse.[is_extension_blocked],
  xse.[is_restriction_blocked],
  xse.[is_substitution_blocked],
  xse.[is_final_extension],
  xse.[is_final_restriction],
  xse.[default_value]
FROM
  [sys].[xml_schema_elements] xse
```

Columns and interpretation

- `xml_component_id` (int): Id of the element component.
- `xml_collection_id` (int): Id of the xml schema collection.
- `xml_namespace_id` (int): Namespace id where the element is defined.
- `is_qualified` (bit): Whether the element is namespace-qualified.
- `Name` (nvarchar?): Local name of the element.
- `symbol_space` (nvarchar): Internal classification for component symbols.
- `symbol_space_desc` (nvarchar?): Description of symbol space.
- `Kind`/`kind_desc` (nvarchar): Kinds and descriptions, typically indicating element component.
- `Derivation`/`derivation_desc` (nvarchar): Derivation method and description for type derivation if applicable.
- `base_xml_component_id` (int?): Base type component id if the element's type is derived.
- `scoping_xml_component_id` (int?): Id of the scoping component that contains the element (complex type, model group, etc.).
- `is_default_fixed` (bit): Whether default value is fixed.
- `is_abstract` (bit): Whether the element is abstract.
- `is_nillable` (bit): Whether the element is nillable (xsi:nil allowed).
- `must_be_qualified` (bit): Whether the element must be namespace-qualified.
- `is_extension_blocked`/`is_restriction_blocked`/`is_substitution_blocked` (bit): Blocking flags for derivation and substitution.
- `is_final_extension`/`is_final_restriction` (bit): Final derivation prohibitions.
- `default_value` (nvarchar?): Default value if defined.

How to interpret

- Use these rows to inspect element declarations, their typing and substitution/blocking constraints, and defaulting/nillability rules relevant for validating XML instances.

Example

```csharp
using var cmd = conn.CreateCommand();
cmd.CommandText = XmlSchemaElementsReader.Sql;
using var rdr = cmd.ExecuteReader();
var r = new XmlSchemaElementsReader(rdr, ownsReader: false);
while (r.Read())
    Console.WriteLine($"ElemId:{r.XmlComponentId} Name:{r.Name} Nillable:{r.IsNillable} Abstract:{r.IsAbstract} Default:{r.DefaultValue}");
```

See also:

- [sys.xml_schema_elements](https://learn.microsoft.com/en-us/sql/relational-databases/system-catalog-views/sys-xml-schema-elements)
